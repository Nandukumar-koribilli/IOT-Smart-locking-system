#include <LiquidCrystal.h>
#include <Keypad.h>

// LCD Configuration (pins: RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Ultrasonic Sensor Pins
const int trigPin = 9;
const int echoPin = 10;

// Keypad Configuration
const byte ROWS = 4; // 4 rows
const byte COLS = 3; // 3 columns
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; // Connect to row pins
byte colPins[COLS] = {6, 7, 8}; // Connect to column pins
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password Configuration
const String correctPassword = "1234";
String enteredPassword = "";

// Relay and Buzzer Pins
const int relayPin = 13;
const int buzzerPin = A4;

// Ultrasonic distance threshold (in cm)
const int distanceThreshold = 10;

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

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
        if (key == '#') { // Submit password
          if (enteredPassword == correctPassword) {
            lcd.clear();
            lcd.print("Access Granted");
            digitalWrite(relayPin, HIGH); // Turn on relay
            delay(5000); // Keep relay on for 5 seconds
            digitalWrite(relayPin, LOW); // Turn off relay
            break;
          } else {
            lcd.clear();
            lcd.print("Wrong Password");
            lcd.setCursor(0, 1);
            lcd.print("Try Again");
            digitalWrite(buzzerPin, HIGH); // Turn on buzzer
            delay(2000); // Buzzer on for 2 seconds
            digitalWrite(buzzerPin, LOW); // Turn off buzzer
            break;
          }
        } else if (key != '*') { // Ignore '*' key
          enteredPassword += key;
          lcd.setCursor(0, 1);
          lcd.print(enteredPassword);
        }
      }
    }
  }
}