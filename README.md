# 🦾 Text-to-Braille Converter

**My Role:** Core C++ Firmware Developer & Hardware Logic
*Project developed in collaboration with Suyash Sharthi.*

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![Hardware](https://img.shields.io/badge/Hardware-PCB-orange?style=for-the-badge)

---

## 📖 Project Overview
This project utilizes an **Arduino-driven system** with servo motors to replicate Braille dots, translating English text into tactile Braille script in real-time. It was engineered to address the accessibility gap for visually impaired individuals through an innovative, low-cost hardware implementation.

## ⚙️ Technical Implementation
I wrote the **C++ firmware** for the Arduino microcontroller to:
1.  **Interpret Data:** Read English text input from an SD Card.
2.  **Translation Logic:** Map ASCII characters to specific Braille dot patterns.
3.  **Hardware Control:** Precisely actuate **six servo motors** to emulate the dots physically.

The entire system was integrated into a custom **PCB board**, transforming the concept into a practical working prototype for usability testing.

---

## 🔌 Circuit & Pinout Scheme

The system connects 6 Servo motors and an SD Card module to the Arduino.

### Servo Motor Connections
| Component | Arduino Pin | Wire Type |
| :--- | :--- | :--- |
| **Servo 1** | Pin 2 | Signal |
| **Servo 2** | Pin 3 | Signal |
| **Servo 3** | Pin 4 | Signal |
| **Servo 4** | Pin 5 | Signal |
| **Servo 5** | Pin 6 | Signal |
| **Servo 6** | Pin 7 | Signal |
| **All Servos** | 5V | Power (VCC) |
| **All Servos** | GND | Ground |

### SD Card Module Connections
| SD Module Pin | Arduino Pin | Function |
| :--- | :--- | :--- |
| **CS** | Pin 10 | Chip Select |
| **MOSI** | Pin 11 | Master Out Slave In |
| **MISO** | Pin 12 | Master In Slave Out |
| **SCK** | Pin 13 | Serial Clock |
| **VCC/GND** | 5V / GND | Power |

---

## 🛠️ Components Used
* **Microcontroller:** Arduino Uno/Nano
* **Actuators:** 6x Micro Servo Motors
* **Storage:** SD Card Module
* **Power:** 5V External Supply
* **Integration:** Custom PCB
