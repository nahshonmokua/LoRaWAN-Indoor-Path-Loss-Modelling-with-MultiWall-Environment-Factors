# 🛰️ LoRaWAN Indoor Path Loss Modeling with Environmental Factors 📡

Welcome! I'm <a href="https://nahshonmokua.github.io/" target="_blank">Nahshon Obiri</a>, a Research Associate at the <a href="https://ubi29.informatik.uni-siegen.de/usi/" target="_blank">Ubicomp Group</a> of the <a href="https://www.uni-siegen.de/" target="_blank">University of Siegen</a>. This repository provides data and models for understanding **LoRaWAN signal behavior in indoor environments**, focusing on how factors like humidity, temperature, and CO₂ levels impact path loss and shadowing. Our goal is to optimize indoor LoRaWAN networks for smart IoT applications, enhancing both **signal reliability and network planning**.

<div align="center">
    <img src="design.png" alt="LoRaWAN Indoor Network Deployment Overview" width="70%">
</div>

---

## 🌐 Project Overview
Indoor environments present unique challenges for **LoRaWAN network performance** due to various obstacles such as walls, human activity, and environmental changes. This project provides a detailed dataset and proposes two models for predicting **path loss**:
1. **Log-Distance Path Loss Model with Multi-Wall (LDPLM-MW)**: Incorporates structural obstacles like walls for predicting signal degradation.
2. **Enhanced Log-Distance Path Loss Model with Multi-Wall and Environmental Parameters (LDPLM-MW-EP)**: Adds environmental factors (e.g., humidity, CO₂, PM2.5) to improve prediction accuracy.

These models help address **signal attenuation** in complex indoor settings, offering practical insights for IoT developers and network planners.

---

## 📊 Dataset
The dataset includes measurements of:
- **Environmental Parameters**: Temperature, humidity, CO₂, PM2.5, and pressure.
- **Signal Characteristics**: RSSI, SNR, Spreading Factor, and Time on Air.
- **Deployment Conditions**: Distance to the gateway, wall types, and transmitter power.

📥 <a href="https://github.com/nahshonmokua/LoRaWAN-Indoor-Path-Loss-Modelling-with-MultiWall-Environment-Factors/tree/main" target="_blank"><strong>Download the Dataset</strong></a>

---

## 🛠️ Methodology
### 1. **Data Collection**
   - **Sensor Deployment**: Six end devices were strategically placed on the University of Siegen campus to capture a wide range of conditions.  
   - **Environmental Monitoring**: Measurements include CO₂ levels, humidity, temperature, and PM2.5 concentrations.
   - **Data Transmission**: The data was collected using a LoRaWAN network with transmissions to an InfluxDB database via MQTT.

### 2. **Path Loss Models**
   - **LDPLM-MW**: Considers structural walls, providing a baseline for understanding indoor signal behavior.
   - **LDPLM-MW-EP**: Enhances the baseline model by integrating **dynamic environmental factors** to account for real-time variations, significantly improving prediction accuracy in fluctuating conditions.

### 3. **Data Analysis**
   - Models are trained and validated using the dataset, with performance metrics such as **Root Mean Square Error (RMSE)** and **R-squared** to evaluate accuracy. 
   - Comparative analysis between LDPLM-MW and LDPLM-MW-EP is performed to demonstrate the improvement.

---

## 📈 Results
- **Improved Accuracy with LDPLM-MW-EP**: The enhanced model outperforms the standard one, especially in scenarios with significant environmental variability.
- **Environmental Factors Matter**: Variables like **humidity and CO₂** notably impact signal strength, suggesting that **dynamic model adjustments** are crucial for robust indoor LoRaWAN networks.

### Visual Insights
Later!

---

## 🔍 Publications and Talks
- <a href="https://www.techrxiv.org/users/838699/articles/1231060-a-survey-of-lorawan-integrated-wearable-sensor-networks-for-human-activity-recognition-applications-challenges-and-possible-solutions" target="_blank">A Survey of LoRaWAN-integrated Wearable Sensor Networks for Human Activity Recognition: Applications, Challenges and Possible Solutions</a>
- Presented a light talk at the <a href="https://www.uni-siegen.de/zess/kombibox/zess_phd_forum_2024.html" target="_blank"><strong>ZESS PhD Forum 2024</strong></a>: "LoRaWAN Path Loss Measurements in an Indoor Setting, including Human and Environmental Effects."
- Data descriptor and full details available ...later...

---

## 🤝 Get Involved
🚀 **Want to collaborate?** Whether you're an IoT enthusiast, network planner, or researcher, let's connect and explore sustainable tech innovations!  
Connect with me <a href="https://nahshonmokua.github.io/" target="_blank">here</a>!

---

## 📝 How to Use This Repository
1. **Clone the repository**:  
   ```bash
   git clone https://github.com/nahshonmokua/LoRaWAN-Indoor-Path-Loss-Modelling-with-MultiWall-Environment-Factors.git


2. **Download the dataset** and explore the data.
3. **Run the analysis scripts** to replicate the model results or modify them for your scenarios.
4. **Contribute**: Submit pull requests to suggest improvements or new features.

---

## 📜 License
⚠️ *This project does not have a license. Contributions are welcome, but please contact me for permission if you intend to use it commercially.*

---