#include "smoothstepper.h"

#define stepsPerRevolution 20    // steps per revolution (limited to 315°)
#define LED_PIN 13

//const StepperMode STEPPER_MODE = FULL_STEP;
//const StepperMode STEPPER_MODE = HALF_STEP;
const StepperMode STEPPER_MODE = QUARTER_STEP;

SmoothStepper stepper(stepsPerRevolution, STEPPER_MODE, 2, 3, 4, 5);

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);
  stepper.zero(50);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

long period = 4000;
long lastTimestamp = 0;
long clockwise = 1;

void loop() {
  long timestamp = millis();
  
  stepper.update(timestamp);

  if (timestamp - lastTimestamp >= period) {
    stepper.start(1000, 60 * STEPPER_MODE * clockwise, timestamp); // 3 revolutions
    clockwise *= -1;
    lastTimestamp = timestamp;
  }
}

