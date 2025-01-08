/*
 * This program reads data from environmental sensors (BME280, SCD4x, SPS30) 
 * and sends the collected measurements (pressure, CO2, temperature, humidity, PM2.5) 
 * via LoRaWAN using adaptive data rate. It cycles through data rates after 
 * a set number of transmissions to optimize network performance.
 */

#include <MKRWAN.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SensirionI2CScd4x.h>
#include <sps30.h> 

#define SEALEVELPRESSURE_HPA (1017.95)  // Adjust for local sea-level pressure

// Sensor and LoRaWAN declarations
Adafruit_BME280 bme;               // BME280 environmental sensor
SensirionI2CScd4x scd4x;           // SCD4x CO2 sensor
LoRaModem modem;                   // LoRaWAN modem

int16_t ret;                       // Return value for SPS30 operations
uint8_t auto_clean_days = 4;       // Auto-cleaning interval for SPS30 fan
struct sps30_measurement m;        // SPS30 measurement struct
uint16_t data_ready;               // SPS30 data ready flag

// LoRaWAN OTAA credentials
String appEui = "xxxxxxxxxxxx";     // Application EUI
String appKey = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";  // Application Key

// Data rate (DR) and transmission tracking
int currentDR = 0;                 // Initial LoRaWAN data rate
int transmissionCount = 0;         // Count transmissions at current DR
unsigned long packetsSent = 0;     // Total packets sent

/*
 * setup()
 * Initializes I2C communication, sensors (BME280, SCD4x, SPS30), 
 * and LoRaWAN modem. It sets sensor auto-clean intervals, 
 * starts measurements, and joins the LoRaWAN network using OTAA.
 */
void setup() {
    Wire.begin();

    scd4x.begin(Wire);
    scd4x.startPeriodicMeasurement();

    if (!bme.begin(0x77)) {  // Check BME280 I2C address
        while (1);
    }

    // Initialize the I2C communication (required for the sensor)
    sensirion_i2c_init();

    // Probe the SPS30 sensor until it responds
    while (sps30_probe() != 0) {
        delay(500); // Wait for 500 milliseconds before retrying
    }

    // Set the auto-cleaning interval for the fan
    ret = sps30_set_fan_auto_cleaning_interval_days(auto_clean_days);
    if (ret) {
        // Error handling can be improved here if needed
    }

    // Start SPS30 measurement
    ret = sps30_start_measurement();
    if (ret < 0) {
        // Error handling can be improved here
    }

    if (!modem.begin(EU868)) {
        while (true);
    }

    if (!modem.joinOTAA(appEui, appKey)) {
        while (true);
    }

    modem.setPort(3);
    modem.setADR(true);  // Enable Adaptive Data Rate
}

/*
 * sendPacket()
 * Prepares and sends a data packet via LoRaWAN. 
 * It encodes sensor readings and the packet count into 
 * a payload, sends the packet, and adjusts the data rate 
 * after a fixed number of transmissions.
 */
void sendPacket(float pressure, uint16_t co2, float temperature, float humidity, float pm25, unsigned long packetCount) {
    modem.dataRate(currentDR);

    // Constructing the payload
    uint8_t payload[18];
    int16_t values[] = {
        static_cast<int16_t>(pressure * 100),
        co2,
        static_cast<int16_t>(temperature * 100),
        static_cast<int16_t>(humidity * 100),
        static_cast<int16_t>(pm25 * 100) // PM2.5 value
    };

    for (int i = 0; i < 5; i++) {
        payload[i * 2] = values[i] >> 8;
        payload[i * 2 + 1] = values[i] & 0xFF;
    }

    // Adding the packet count to the payload (4 bytes)
    payload[10] = (packetCount >> 24) & 0xFF; // High byte
    payload[11] = (packetCount >> 16) & 0xFF; // Second byte
    payload[12] = (packetCount >> 8) & 0xFF;  // Third byte
    payload[13] = packetCount & 0xFF;         // Low byte

    modem.beginPacket();
    modem.write(payload, sizeof(payload));
    int err = modem.endPacket(true);

    // Increment the transmission count and adjust data rate if needed
    transmissionCount++;
    if (transmissionCount >= 5) {
        transmissionCount = 0;
        currentDR++;
        if (currentDR > 5) {
            currentDR = 0;
        }
    }
}

/*
 * loop()
 * Continuously reads sensor data from BME280, SCD4x, and SPS30, 
 * then packages and sends the data via LoRaWAN. 
 * Delays one minute between transmissions.
 */
void loop() {
    // Read pressure from BME280 sensor
    float pressure = bme.readPressure() / 100.0F;

    // Read CO2, temperature, and humidity from SCD4x
    uint16_t co2 = 0;
    float temperature = 0.0f;
    float humidity = 0.0f;
    bool dataReady = false;
    scd4x.getDataReadyFlag(dataReady);
    if (dataReady) {
        scd4x.readMeasurement(co2, temperature, humidity);
    }

    // Read PM2.5 from SPS30
    float pm25 = 0.0;
    ret = sps30_read_data_ready(&data_ready);
    if (ret >= 0 && data_ready) {
        ret = sps30_read_measurement(&m);
        if (ret >= 0) {
            pm25 = m.mc_2p5;
        }
    }

    // Send the packet with sensor data and packet count
    sendPacket(pressure, co2, temperature, humidity, pm25, packetsSent);

    // Increment the packet count
    packetsSent++;

    delay(60000); // Delay between data transmissions
}
