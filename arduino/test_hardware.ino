/**
 * Arduino sketch for testing various hardware components.
 *
 * This sketch provides a menu-driven interface via the serial monitor to
 * individually test a buzzer, an LCD 16x2 display, a 9G micro servo,
 * and an Adafruit NeoPixel LED. It helps in verifying the functionality
 * and wiring of these components.
 */

#include "Arduino.h"
#include "Buzzer.h"
#include "LiquidCrystal.h"
#include "Adafruit_NeoPixel.h"
#include "Servo.h"
// #include "pitches.h" 

// Pin Definitions
#define BUZZER_PIN_SIG  2
#define LCD_PIN_RS  8
#define LCD_PIN_E 7
#define LCD_PIN_DB4 3
#define LCD_PIN_DB5 4
#define LCD_PIN_DB6 5
#define LCD_PIN_DB7 6
#define LEDRGB_PIN_DIN  9
#define SERVO9G_PIN_SIG 10

#define LedRGB_NUMOFLEDS 1
const int servo9gRestPosition   = 20;  // Servo's rest position
const int servo9gTargetPosition = 150; // Servo's target position

// Object declarations for hardware components
Buzzer buzzer(BUZZER_PIN_SIG);
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_E, LCD_PIN_DB4, LCD_PIN_DB5, LCD_PIN_DB6, LCD_PIN_DB7);
Adafruit_NeoPixel LedRGB(LedRGB_NUMOFLEDS, LEDRGB_PIN_DIN, NEO_GRB + NEO_KHZ800);
Servo servo9g;

// Variables for the testing menu functionality
const int timeout = 10000;
char menuOption = 0;    // Stores user's menu selection
long time0;             // Time when menu was displayed


// Arduino setup() function
void setup()
{
    Serial.begin(9600); // Initialize serial communication
    while (!Serial) ;   // Wait for serial port to connect
    Serial.println("start");

    lcd.begin(16, 2);           // Initialize LCD (16 columns, 2 rows)
    LedRGB.begin();             // Initialize NeoPixel library
    LedRGB.show();              // Turn off all NeoPixels
    servo9g.attach(SERVO9G_PIN_SIG); // Attach servo
    servo9g.write(servo9gRestPosition); // Move servo to rest position
    delay(100);
    servo9g.detach();           // Detach servo to conserve power

    menuOption = menu(); // Display menu and get initial selection
}

/**
 * Arduino loop function.
 * Continuously runs the selected component test based on `menuOption`.
 * Resets to the menu if no input is received within the timeout period.
 */
void loop()
{
    if(menuOption == '1') {
        // Buzzer Test: Plays a melody
        buzzer.begin(100);
        buzzer.sound(NOTE_E7, 80);
        buzzer.sound(NOTE_E7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_E7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_C7, 80);
        buzzer.sound(NOTE_E7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_G7, 80);
        buzzer.sound(0, 240);
        buzzer.sound(NOTE_G6, 80);
        buzzer.sound(0, 240);
        buzzer.sound(NOTE_C7, 80);
        buzzer.sound(0, 160);
        buzzer.sound(NOTE_G6, 80);
        buzzer.sound(0, 160);
        buzzer.sound(NOTE_E6, 80);
        buzzer.sound(0, 160);
        buzzer.sound(NOTE_A6, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_B6, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_AS6, 80);
        buzzer.sound(NOTE_A6, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_G6, 100);
        buzzer.sound(NOTE_E7, 100);
        buzzer.sound(NOTE_G7, 100);
        buzzer.sound(NOTE_A7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_F7, 80);
        buzzer.sound(NOTE_G7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_E7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_C7, 80);
        buzzer.sound(NOTE_D7, 80);
        buzzer.sound(NOTE_B6, 80);
        buzzer.sound(0, 160);
        buzzer.sound(NOTE_C7, 80);
        buzzer.sound(0, 160);
        buzzer.sound(NOTE_G6, 80);
        buzzer.sound(0, 160);
        buzzer.sound(NOTE_E6, 80);
        buzzer.sound(0, 160);
        buzzer.sound(NOTE_A6, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_B6, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_AS6, 80);
        buzzer.sound(NOTE_A6, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_G6, 100);
        buzzer.sound(NOTE_E7, 100);
        buzzer.sound(NOTE_G7, 100);
        buzzer.sound(NOTE_A7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_F7, 80);
        buzzer.sound(NOTE_G7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_E7, 80);
        buzzer.sound(0, 80);
        buzzer.sound(NOTE_C7, 80);
        buzzer.sound(NOTE_D7, 80);
        buzzer.sound(NOTE_B6, 80);
        buzzer.sound(0, 160);

        buzzer.end(2000);
    }
    else if(menuOption == '2') {
        // LCD 16x2 Test: Displays message and toggles visibility
        lcd.setCursor(0, 0);
        lcd.print("Circuito Rocks !");
        lcd.noDisplay();
        delay(500);
        lcd.display();
        delay(500);
    }
    else if(menuOption == '3') {
        // 9G Micro Servo Test: Rotates between two positions
        servo9g.attach(SERVO9G_PIN_SIG);
        servo9g.write(servo9gTargetPosition);
        delay(500);
        servo9g.write(servo9gRestPosition);
        delay(500);
        servo9g.detach();
    }

    // Return to menu if no input within timeout
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
}

/**
 * Displays a menu on the serial monitor for selecting components to test.
 * Waits for user input and returns the selected option.
 */
char menu()
{
    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Buzzer"));
    Serial.println(F("(2) LCD 16x2"));
    Serial.println(F("(3) 9G Micro Servo"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor
    while (Serial.available())
    {
        char c = Serial.read();
        if (isAlphaNumeric(c))
        {
            if(c == '1')
                Serial.println(F("Now Testing Buzzer"));
            else if(c == '2')
                Serial.println(F("Now Testing LCD 16x2"));
            else if(c == '3')
                Serial.println(F("Now Testing 9G Micro Servo"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
    return 0;
}
