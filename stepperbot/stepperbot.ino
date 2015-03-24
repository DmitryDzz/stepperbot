#include "smoothstepper.h"

#define stepsPerRevolution 20    // steps per revolution (limited to 315°)
#define LED_PIN 13

SmoothStepper stepper(stepsPerRevolution, FULL_STEP, 2, 3, 4, 5);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);
  stepper.zero();
  delay(3000);
  digitalWrite(LED_PIN, LOW);

  stepper.start(5000, 3, millis());
}

void loop() {
  stepper.update(millis());
}

