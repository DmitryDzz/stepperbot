#include "Arduino.h"
#include "smoothstepper.h"

SmoothStepper::SmoothStepper(int motorFullStepsNumber, StepperMode stepperMode, int motorPinA1, int motorPinA2, int motorPinB1, int motorPinB2) {
  this->started = false;
  this->motorFullStepsNumber = motorFullStepsNumber;
  this->stepperMode = stepperMode;
  
  this->motorPinA1 = motorPinA1;
  this->motorPinA2 = motorPinA2;
  this->motorPinB1 = motorPinB1;
  this->motorPinB2 = motorPinB2;

  pinMode(this->motorPinA1, OUTPUT);
  pinMode(this->motorPinA2, OUTPUT);
  pinMode(this->motorPinB1, OUTPUT);
  pinMode(this->motorPinB2, OUTPUT);
  
  HIGH_ANALOG = 255;
  LOW_ANALOG = 0;
  MID_ANALOG = 0;
}

void SmoothStepper::zero() {
  this->updateMotor(0);
}

void SmoothStepper::start(long period, long substeps, long millis) {
  if (substeps > 0) {
    this->direction = 1;
  } else if (substeps < 0) {
    this->direction = -1;
  } else {
    stop();
    return;
  }

  this->substepDelay = period / (motorFullStepsNumber * stepperMode);  
  this->substeps = substeps;
  this->currentSubstep = 0;
  this->lastSubstepTime = millis;
  this->started = true;
}

void SmoothStepper::stop() {
  this->started = false;
}

void SmoothStepper::update(long millis) {
  if (!this->started) {
    return;
  }
  
  if (millis - this->lastSubstepTime < this->substepDelay) {
    return;
  }
  
  this->lastSubstepTime = millis;
  
  if (this->substeps - this->currentSubstep == 0) {
    this->stop();
    return;
  }
  
  if (this->direction > 0) {
    this->updateMotor(this->currentSubstep % (4 * this->stepperMode));
  } else {
    this->updateMotor((this->currentSubstep - this->substeps) % (4 * this->stepperMode));
  }
  
  this->currentSubstep += this->direction;
}

void SmoothStepper::updateMotor(long phase) {
  Serial.println(phase);
  
  switch (this->stepperMode) {
    case FULL_STEP:
      switch (phase) {
        case 0:    // 1010
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 1:    // 0110
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 2:    //0101
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 3:    //1001
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
      }
      break;
    case HALF_STEP:
      switch (phase) {
        case 0:    // 1010
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 1:    // 0010
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 2:    //0110
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 3:    //0100
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 4:    // 0101
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 5:    // 0001
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 6:    //1001
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 7:    //1000
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
      }
      break;
    case QUARTER_STEP:
      break;
  } 
}

