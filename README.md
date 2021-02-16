# ESD-Final-Project

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
The graphical LCD works on SPI protocol t transmit messages to the screen. Whenever the D/C line is low, the data byte is selected and the following data bits are stored in the display data ram. After each data byte the address increments automatically. The data or instruction field is sent byte by byte from MSB to LSB.

-    DC MOTOR CONTROL USING PWM:
DC motor converts electrical energy into mechanical energy. The direction of the dc motor can be reversed by changing the direct current through the motor. This can be done by using a motor driver which has a H- bridge circuit as is present in Motor driver L293d.
The change in voltage applied to the motor results in changing the speed with the motor rotates, for which we use the PWM technique.

-    4*3 Keypad:
The 4*3 Keypad is used for taking input from the user along with the keyboard input which is required for the reprogrammable functionality of the remote. In this driver code, we make all rows zero initially and all columns as one. Whenever a button is pressed column and the row corresponding to the button gets shorted and hence the column related to that row becomes zero.

-    Seven segment Display:
Seven segment display consists of a number of LED segments, which need to switch on individually to display different patterns or numerical digits. It can be a common anode or common cathode. WE use the common anode 7 segment where the positive elements are left alone and the led segments which are switched on are made 0. For example, the binary code for digit zero will be 11000000 that is 0xC0 in hexadecimal. This needs to be sent to the port pin where seven segment display is connected to display the correct number pressed. In the project, seven segment display is used to display all the numbers or characters which are taken as input from the user.

# Features 
* Controlled 4 peripheral devices like DC motor, LED, GLCD, seven-segment with infrared communication on 8051
* Reprogramable functionality

# Hardware Compoenents
* Atmel AT89C51
* TSOP 38238 IR Receiver
* NOKIA 5110 GRAPHICAL LCD
* L293DNE Motor driver and Dc motor
* 4*3 Keypad Interface
* Seven Segment Display

# Block Diagram
![](https://github.com/HARSH1911RATHORE/IOT_final_project_spring_2020/blob/master/BLOCK_DIAGRAM_IOT.png)

## [](https://github.com/HARSH1911RATHORE/IOT_final_project_spring_2020/tree/1262f5e660c0273681406807c0b4457386b7123b#project-status)Project
•	Aimed at controlling the peripheral devices like DC motor, LED, GLCD, seven-segment with the help of infrared communication
•	Installed TSOP 38238 IR receiver to decode the address, command bits of keys pressed on remote using NEC protocol
•	Featured reprogrammable remote functionality 
•	Implemented SPI protocol for the graphical LCD and used PWM to control speed and direction of DC motor

# Documentation
## HARSH RATHORE [](https://github.com/HARSH1911RATHORE/IOT_final_project_spring_2020/tree/1262f5e660c0273681406807c0b4457386b7123b#google-drive-link)[Google drive link](https://drive.google.com/drive/u/1/folders/1FM8G4nL0fplihENYMFtwnbRBXwX1w5KG)
