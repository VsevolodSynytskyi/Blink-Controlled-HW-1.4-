#include <Arduino.h>

// LED pins
const int BLUE_LED_PIN = 15;
const int RED_LED_PIN = 16;

// External button: external pull-down + wired to 3.3V, so pressed = HIGH
const int BUTTON_PIN = 17;       // external button -> FASTER blinking
// BOOT button: on-board pull-up + button to GND, so pressed = LOW
const int BOOT_BUTTON_PIN = 0;   // BOOT button     -> SLOWER blinking

// Blink speeds (delay in milliseconds; smaller = faster)
const int FAST_DELAY = 150;
const int SLOW_DELAY = 800;

// Current blink speed (start slow)
int blinkDelay = SLOW_DELAY;

// Read the buttons and switch mode if one is pressed.
// A short delay() after detecting a press debounces the contact bounce.
void checkButtons() {
  // External button -> FAST mode (pressed = HIGH, external pull-down)
  if (digitalRead(BUTTON_PIN) == HIGH) {
    delay(50);  // debounce
    if (digitalRead(BUTTON_PIN) == HIGH && blinkDelay != FAST_DELAY) {
      blinkDelay = FAST_DELAY;
      Serial.println("External button -> FAST mode");
    }
  }

  // BOOT button -> SLOW mode
  if (digitalRead(BOOT_BUTTON_PIN) == LOW) {
    delay(50);  // debounce
    if (digitalRead(BOOT_BUTTON_PIN) == LOW && blinkDelay != SLOW_DELAY) {
      blinkDelay = SLOW_DELAY;
      Serial.println("BOOT button -> SLOW mode");
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);            // external pull-down on the board
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP); // on-board pull-up

  Serial.println("Board started! Mode: SLOW");
}

void loop() {
  // Both LEDs ON
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(BLUE_LED_PIN, HIGH);
  checkButtons();
  delay(blinkDelay);

  // Both LEDs OFF
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
  checkButtons();
  delay(blinkDelay);
}
