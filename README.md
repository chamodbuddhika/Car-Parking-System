# IoT-Based Smart Car Parking System

## Overview
The **IoT-Based Smart Car Parking System** is designed to efficiently manage parking spaces using IoT technology. This system helps to detect available parking slots and provides real-time updates, improving parking efficiency and reducing congestion.

## Features
- **RFID-Based Access Control**: Uses RFID cards to allow entry into the parking area.
- **Real-time Parking Slot Detection**: Uses IR sensors to detect available parking spots.
- **Automated Entry & Exit System**: Controls the gate using a servo motor.
- **LCD Display (20x4)**: Shows real-time parking slot availability and gate status.
- **Notifications & Alerts**: Displays messages like 'Gate Opening' and 'Parking Full'.

## Technologies Used
- **Hardware**:
  - Ultrasonic/IR Sensors
  - RFID Module (MFRC522)
  - Servo Motor
  - LiquidCrystal_I2C LCD (20x4)
  - Arduino Board
- **Software**:
  - Arduino IDE (C++)
  - SPI & Wire Library (for communication)
  - MFRC522 Library (for RFID handling)

## Installation Guide
1. **Hardware Setup**:
   - Connect IR sensors to detect vehicle presence.
   - Configure RFID module for access control.
   - Connect the servo motor for gate control.
   - Wire up the LCD display for real-time slot updates.
   
2. **Software Setup**:
   - Clone the repository:
     ```bash
     git clone [repository-link]
     cd car-parking-system
     ```
   - Open the Arduino IDE and upload the provided sketch (`car_parking.ino`) to the Arduino board.
   - Ensure necessary libraries (`SPI`, `Wire`, `MFRC522`, `Servo`, `LiquidCrystal_I2C`) are installed.

## Usage
- The system scans RFID cards to grant entry.
- IR sensors detect if parking slots are occupied or empty.
- The LCD displays the number of available slots.
- The servo motor operates the gate automatically based on the vehicle's presence.

## Contributing
Feel free to contribute to the project by submitting issues or pull requests.

## License
This project is licensed under the MIT License.



