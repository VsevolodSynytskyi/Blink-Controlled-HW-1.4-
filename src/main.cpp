#include <Arduino.h>

// LED pins
const int BLUE_LED_PIN = 15;
const int RED_LED_PIN = 16;

// External button pin
const int BUTTON_PIN = 17;

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  Serial.println("Board started!");
}

int lastButtonState = -1;

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    // Pressed
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
  }
  else
  {
    // Not Pressed
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
  }

  // Log only when the state changes (one message per press/release)
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      Serial.println("Button pressed -> BLUE on");
    } else {
      Serial.println("Button not pressed -> RED on");
    }
    lastButtonState = buttonState;
  }
}
