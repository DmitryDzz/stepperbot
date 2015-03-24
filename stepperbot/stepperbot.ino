#include "smoothstepper.h"

#define stepsPerRevolution 20    // steps per revolution (limited to 315°)
#define LED_PIN 13

SmoothStepper stepper(stepsPerRevolution, 2, 2, 3, 4, 5);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  stepper.setSpeed(1);    // set the motor speed to 30 RPM (360 PPS aprox.).

  testMotor();
  testMotor();
  testMotor();
}

void loop() {
}

void testMotor() {
  // step one revolution  in one direction:
  digitalWrite(LED_PIN, HIGH);
  stepper.step(stepsPerRevolution);
  delay(1000);
  
   // step one revolution in the other direction:
  digitalWrite(LED_PIN, LOW);
  stepper.step(-stepsPerRevolution);
  delay(1000); 
}  
