#include <Arduino.h>

// LED pins
const int BLUE_LED_PIN = 15;
const int RED_LED_PIN = 16;

// External button: external pull-down + wired to 3.3V, so pressed = HIGH
const int BUTTON_PIN = 17;       // external button -> FASTER blinking
// BOOT button: on-board pull-up + button to GND, so pressed = LOW
const int BOOT_BUTTON_PIN = 0;   // BOOT button     -> SLOWER blinking

// Blink intervals (ms; smaller = faster)
const unsigned long FAST_INTERVAL = 150;
const unsigned long SLOW_INTERVAL = 800;

// Current blink interval (start slow)
unsigned long blinkInterval = SLOW_INTERVAL;

// Non-blocking blink state
unsigned long previousMillis = 0;  // last time the LEDs toggled
bool ledsOn = false;               // current LED state

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);             // external pull-down on the board
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP); // on-board pull-up

  Serial.println("Board started! Mode: SLOW");
}

void loop() {
  // 1) Check buttons on EVERY loop (non-blocking, instant response)
  if (digitalRead(BUTTON_PIN) == HIGH) {          // external button pressed
    if (blinkInterval != FAST_INTERVAL) {
      blinkInterval = FAST_INTERVAL;
      Serial.println("External button -> FAST mode");
    }
  }
  if (digitalRead(BOOT_BUTTON_PIN) == LOW) {      // BOOT button pressed
    if (blinkInterval != SLOW_INTERVAL) {
      blinkInterval = SLOW_INTERVAL;
      Serial.println("BOOT button -> SLOW mode");
    }
  }

  // 2) Toggle the LEDs only once enough time has passed
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    ledsOn = !ledsOn;
    digitalWrite(RED_LED_PIN, ledsOn);
    digitalWrite(BLUE_LED_PIN, ledsOn);
  }
}
