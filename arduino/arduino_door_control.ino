/**
 * Arduino sketch for a facial recognition access control system.
 *
 * This sketch controls a door using a servo motor, provides visual feedback
 * via an LCD, and audio feedback via a buzzer. It communicates with a host
 * system via serial communication to determine access status and display 
 * relevant messages.
 */

#include <Servo.h>
#include <LiquidCrystal.h>
#include <Buzzer.h>

// Pin definitions for hardware components
LiquidCrystal lcd(8, 7, 3, 4, 5, 6); 
Servo servoMotor; 
int buzzerPin = 2;
Buzzer buzzer(buzzerPin);

// Arduino setup function
void setup() {
  Serial.begin(9600);         // 9600 baud rate
  servoMotor.attach(10);      // Attach servo to pin 10
  lcd.begin(16, 2);           // LCD with 16 columns and 2 rows
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
}

// Structure to store key-value pairs for known individuals.
struct KeyValue {
  const char* key; // Person's name
  int value;       // Signal ID for the person
};

// Dictionary of known people: maps signal IDs to names
KeyValue dictionary[] = {
  {"aryan", 2},
  {"tharun", 3},
  {"aryabhatta", 4}
};

/**
 * Arduino loop function.
 * Continuously checks for incoming serial data and reacts based on the signal.
 * Controls door, LCD messages, and buzzer sounds.
 */
void loop() {
  // Process incoming serial data
  if (Serial.available() > 0) {
    char signal = Serial.read(); 

    Serial.print("Received Signal: ");
    Serial.println(signal);

    // Handle signals for access control
    if(signal == '0') {
        // No face detected
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Shhhhh");
    }
    else if(signal == '1') {
      // Access denied
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access Denied");

      // Sound alarm (three short beeps)
      for (int i = 0; i < 3; i++) {
        buzzer.begin(2000);
        delay(200);
        buzzer.end(2000);
        delay(200);
      }
    }
    else {
      // Person recognized
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome, ");
      lcd.print(dictionary[signal].key); // Display name from dictionary

      // Play welcome tone
      tone(buzzerPin, 1000, 500);

      // Open door (servo to 90 degrees)
      servoMotor.write(90);
      delay(3000); // Keep door open

      // Play short beeps for door action
      for (int i = 0; i < 3; i++) {
        buzzer.begin(1000);
        delay(100);
        buzzer.end(1000);
        delay(50);
      }
      servoMotor.write(0); // Close door (servo to 0 degrees)
    }
  }
}
