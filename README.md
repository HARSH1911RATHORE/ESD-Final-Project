# ESD-Final-Project
# [](https://github.com/HARSH1911RATHORE/IOT_final_project_spring_2020/tree/1262f5e660c0273681406807c0b4457386b7123b#iot_final_project_spring_2020)IOT_final_project_spring_2020

# [](https://github.com/HARSH1911RATHORE/IOT_final_project_spring_2020/tree/1262f5e660c0273681406807c0b4457386b7123b#pollution-monituring-system)Pollution Monitoring System

# Overview
The purpose of the project is to control various peripheral devices using the IR remote. The system is based on Atmel AT89C51 Microcontroller. The system is integrated with various other sensors, actuators, and displays that form the core of the system design. The inputs are the keypad 4*3, UART and remote control which is based on NEC protocol. TSOP 38238 is an Infrared receiver used to detect the pulses of the required frequency of 38 kHz used for communication with the microcontroller and other peripherals on the board. We use the external Rom address starting from 0XF000 to for LCD 16*4 l working and configuration. The Microcontroller Ports P0, P1, P2 and P3 are used for connecting the various board peripherals. The various peripherals along with the IR receiver sensor are connected to the microcontroller

**Firmware Design:**

-   IR Remote Control Driver:
The remote driver consists of writing functions to decode the NEC protocol's pulses and pulse widths. The protocol as seen in the figure consists of 13.5 ms start of the frame where 9ms is pulse burst and 4.5ms is the space before the address and command bits. The start of frame is followed by 32-bit pulses which are in the following order:
1. 8-bit address
2. 8-bit inverse of the address
3. 8-bit command field
4. 8-bit inverse of the command
5. 562.5 uS period end pulse.

-    GRAPHICAL LCD DRIVER:



# Features 
* Interfacing CCS811 air quality sensor and on board humidity sensor
* Sends sensor values to the client mobile application
* Records the maximum sensor reading in the persistent memory which is displayed on the lcd through a button press after bonding has been established
* State machines utilising non polling mode and polling mode otherwise

# Hardware Compoenents
* SI LABS bluegecko13 board
* CCS811 Sensor and Si7021 sensor
* Mobile 

# Block Diagram
![](https://github.com/HARSH1911RATHORE/IOT_final_project_spring_2020/blob/master/BLOCK_DIAGRAM_IOT.png)

## [](https://github.com/HARSH1911RATHORE/IOT_final_project_spring_2020/tree/1262f5e660c0273681406807c0b4457386b7123b#project-status)Project

-   The Air quality sensor has been interfaced to the board with Pin number P31 for PD 13, SCL and Pin number P33 for PD 14, SDA. State machine for Humidity based sensor was created with data being measured in no hold master mode .
-   Gpio even based interrupt was configured which gets the status of button press. This button press will be used for bonding the board with the client to prevent man in the middle attack.
-   Persistent data was stored in the flash. The data will be stored for every value of data which exceeds the previous maximum value for that particular sensor. This data will be displayed on the server board every time a external button pb0 is pressed.
-   Communication was established between the board and the mobile application and was verified

# Documentation
## HARSH RATHORE [](https://github.com/HARSH1911RATHORE/IOT_final_project_spring_2020/tree/1262f5e660c0273681406807c0b4457386b7123b#google-drive-link)[Google drive link](https://drive.google.com/drive/u/1/folders/1FM8G4nL0fplihENYMFtwnbRBXwX1w5KG)
