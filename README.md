# Smart Door Locking System

## Overview
The Smart Door Locking System is an IoT-based project developed using an Arduino Uno to provide secure and automated door access control. It integrates a keypad for password entry, an ultrasonic sensor for proximity detection, a servo motor for locking/unlocking, and a buzzer for feedback. The system is designed for enhanced security and user convenience in home or office environments.

## Features
- **Password-Based Access**: Unlock the door by entering a predefined password via a 4x3 keypad.
- **Proximity Detection**: Uses an ultrasonic sensor (HC-SR04) to detect nearby objects and prompt for password entry.
- **Audible Feedback**: A buzzer provides alerts for incorrect passwords or system actions.
- **Visual Feedback**: An LCD display shows system status and user prompts.
- **Automated Locking**: A servo motor controls the physical locking mechanism.

## Components
- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- 4x3 Keypad
- Servo Motor
- Piezoelectric Buzzer
- LCD Display (16x2)
- Breadboard and Jumper Wires
- A-to-B USB Cable
- 5V Power Supply

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Nandukumar-koribilli/SmartDoorLockingSystem.git
   ```
2. **Install Arduino IDE**:
   - Download and install the Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software).
3. **Install Libraries**:
   - Install `LiquidCrystal` and `Keypad` libraries via the Arduino IDE Library Manager.
4. **Connect Hardware**:
   - Wire components as per the schematic (see images below).
   - Connect the Arduino Uno to your computer via the A-to-B USB cable.
5. **Upload Code**:
   - Open the `SmartDoorLock.ino` file in the Arduino IDE.
   - Upload the code to the Arduino Uno.

## Usage
1. **Power the System**: Connect the Arduino to a 5V power supply or USB.
2. **Proximity Detection**: Approach the door (within 10 cm) to trigger the ultrasonic sensor.
3. **Enter Password**: Use the keypad to input the password (default: `1234`).
4. **Access Control**:
   - Correct password: Servo motor unlocks the door, LCD displays "Access Granted," and the relay activates for 5 seconds.
   - Incorrect password: Buzzer sounds, LCD displays "Wrong Password."
5. **Monitor Status**: The LCD shows real-time system status.

## Project Structure
- `SmartDoorLock.ino`: Main Arduino code for the system.
- `images/`: Contains project schematics and setup images.
- `docs/`: Documentation, including circuit diagrams and component details.

## Code Snippet
```cpp
#include <LiquidCrystal.h>
#include <Keypad.h>

// LCD Configuration
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Ultrasonic Sensor Pins
const int trigPin = 9;
const int echoPin = 10;

// Keypad Configuration
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {6, 7, 8};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password and Pins
const String correctPassword = "1234";
String enteredPassword = "";
const int relayPin = 13;
const int buzzerPin = A4;
const int distanceThreshold = 10;

void setup() {
  lcd.begin(16, 2);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  long distance = getDistance();
  if (distance < distanceThreshold) {
    lcd.clear();
    lcd.print("Enter Password");
    enteredPassword = "";
    while (true) {
      char key = keypad.getKey();
      if (key) {
        if (key == '#') {
          if (enteredPassword == correctPassword) {
            lcd.clear();
            lcd.print("Access Granted");
            digitalWrite(relayPin, HIGH);
            delay(5000);
            digitalWrite(relayPin, LOW);
            break;
          } else {
            lcd.clear();
            lcd.print("Wrong Password");
            lcd.setCursor(0, 1);
            lcd.print("Try Again");
            digitalWrite(buzzerPin, HIGH);
            delay(2000);
            digitalWrite(buzzerPin, LOW);
            break;
          }
        }
      }
    }
  }
}
```

## Images
![Circuit Schematic](images/circuit_schematic.jpg)
![Project Setup](images/project_setup.jpg)
![Team Working](images/team_working.jpg)

## Future Improvements
- Add RFID module for card-based access.
- Integrate Bluetooth (HC-05) for smartphone control.
- Implement fingerprint recognition for enhanced security.
- Use a more durable locking mechanism for long-term use.

## Contributing
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-branch`).
3. Commit changes (`git commit -m "Add feature"`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- **Guide**: Sri K. Natraju, Sr. Assistant Professor, Dept. of Electronics
- **HoD**: Dr. D. Sreedevi, Dept. of Electronics
- **Institution**: Gayatri Vidya Parishad College for Degree and PG Courses, Visakhapatnam
