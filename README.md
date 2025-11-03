🧠 IoT-Based Industrial Machine State Monitoring System

📘 Overview

The Industrial Machine State Monitoring System is an IoT-enabled platform designed to continuously track and analyze real-time machine parameters such as voltage, current, temperature, and pressure using an ESP32 microcontroller system enables continuous machine health monitoring, fault detection, and predictive maintenance, powered by ADS1115, INA219, and Blynk IoT Cloud.
It supports both manual and automatic operation modes, ensuring operational reliability and remote accessibility.


⚙️ Features

Real-time monitoring of machine state (Voltage, Current, Temperature, Pressure)

Dual operation modes: Manual / Automatic

Start/Stop control via Blynk IoT (Web & Mobile)

Status indicator for fault detection and health status

Data visualization and cloud storage using Blynk IoT

High-accuracy sensing via ADS1115 (ADC) and INA219 (Current/Voltage Sensor)

Dual Wi-Fi operation using ESS (Extended Service Set) mode

Remote access to system data over both local and internet networks



🌐 Network Architecture — ESS Mode (Extended Service Set)

The system utilizes the ESP32’s dual Wi-Fi capability to operate simultaneously as:

 1) Station (STA) Mode – connects to an existing Wi-Fi router for cloud access (Blynk IoT).

 2) Access Point (AP) Mode – creates a local network to directly communicate with nearby devices (e.g., technicians or maintenance apps).

Together, these two modes form an Extended Service Set (ESS) — a configuration where multiple access points share the same SSID or network domain to extend connectivity.
This ensures seamless data accessibility, whether on-site (local AP) or remotely (Blynk Cloud).


🧩 System Architecture

Core Components:

Microcontroller: ESP32

Sensors:

ADS1115 – Precision ADC for analog signals

INA219 – Current and Voltage measurement

Cloud Platform: Blynk IoT

Network Layer: ESS using ESP32 AP + STA dual-mode

User Interface: Blynk Web & Mobile dashboards


🖥️ Blynk IoT Integration

The system uses Blynk Cloud to send and receive real-time data.

Web dashboard for analytics and system status

Mobile app for remote control

Virtual pins for sensor readings and button inputs

DataStream for each parameter (Voltage, Current, Temperature, etc.)

📲 Software Requirements

Arduino IDE or Platform IO

Blynk IoT Library

WiFi Credentials (for Blynk connection)


🚀 How It Works

ESP32 reads real-time data from ADS1115 and INA219.

Data is processed and transmitted to Blynk Cloud via Wi-Fi (Station Mode).

ESP32 also hosts a local access point (AP Mode) for direct monitoring without the internet.

Machine control (Start/Stop) and mode switching are handled via Blynk or local interface.

In ESS configuration, both modes run simultaneously for uninterrupted connectivity.


📊 Future Enhancements

Integration with MQTT and SCADA systems

Predictive maintenance using ML algorithms

Graphical trend analysis and local data logging

Multi-node ESS network for factory-wide monitoring

Email/SMS fault alerts via Blynk automations
