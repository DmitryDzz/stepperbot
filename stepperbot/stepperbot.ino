#include "smoothstepper.h"

#define stepsPerRevolution 20    // steps per revolution (limited to 315°)
#define LED_PIN 13

SmoothStepper stepper(stepsPerRevolution, QUARTER_STEP, 2, 3, 4, 5);
//SmoothStepper stepper(stepsPerRevolution, HALF_STEP, 2, 3, 4, 5);

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);
  stepper.zero(50);
  delay(1000);
  digitalWrite(LED_PIN, LOW);

//  stepper.start(100, 30, millis());
}

long period = 4000;
long lastTimestamp = 0;
long clockwise = 1;

void loop() {
//  stepper.update(millis());
  long timestamp = millis();
  
  stepper.update(timestamp);

  if (timestamp - lastTimestamp >= period) {
    stepper.start(1000, 120 * clockwise, timestamp);
    clockwise *= -1;
    lastTimestamp = timestamp;
  }
}

