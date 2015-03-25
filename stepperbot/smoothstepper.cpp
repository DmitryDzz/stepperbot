#include "Arduino.h"
#include "smoothstepper.h"

SmoothStepper::SmoothStepper(int motorFullStepsNumber, StepperMode stepperMode, int motorPinA1, int motorPinA2, int motorPinB1, int motorPinB2) {
  this->started = false;
  this->motorFullStepsNumber = motorFullStepsNumber;
  this->stepperMode = stepperMode;
  this->currentPhase = 0;
  
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
  MID_ANALOG = 192;
}

void SmoothStepper::zero(long substepDelay) {
//Serial.println("Zero begin");
//Serial.println("mode=" + String(this->stepperMode));
  for (long i = 4 * this->stepperMode - 1; i >= 0; i--) {
//Serial.println("i=" + String(i));
    this->currentPhase = i;
    this->updateMotor(this->currentPhase);
    delay(substepDelay);
  }
//Serial.println("Zero end");
}

void SmoothStepper::start(long period, long substeps, long timestamp) {
  if (substeps > 0) {
    this->direction = 1;
  } else if (substeps < 0) {
    this->direction = -1;
  } else {
    stop();
    return;
  }

  this->substepDelay = period / (this->motorFullStepsNumber * this->stepperMode);  
  
  this->substeps = substeps + this->currentPhase;
  this->currentSubstep = this->currentPhase;  
  
  this->lastTimestamp = timestamp;
  this->started = true;
}

void SmoothStepper::stop() {
  this->started = false;
}

void SmoothStepper::update(long timestamp) {
  if (!this->started) {
    return;
  }
  
  if (timestamp - this->lastTimestamp < this->substepDelay) {
    return;
  }
  
  this->lastTimestamp = timestamp;
  
  if (this->substeps - this->currentSubstep == 0) {
    this->stop();
    return;
  }
  
  this->currentSubstep += this->direction;
  this->updateMotor(this->currentSubstep % (4 * this->stepperMode));
}

void SmoothStepper::updateMotor(long phase) {
  if (phase < 0) {
    phase += 4 * this->stepperMode;
  }
  
  this->currentPhase = phase;
//Serial.println("Phase=" + String(phase));
  
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
      switch (phase) {
        case 0:    // 1010
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 1:
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, MID_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 2:    // 0010
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 3:
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, MID_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 4:    //0110
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 5:
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, MID_ANALOG);
          break;
        case 6:    //0100
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 7:
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, MID_ANALOG);
          break;
        case 8:    // 0101
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, HIGH_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 9:
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, MID_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 10:    // 0001
          analogWrite(motorPinA1, LOW_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 11:
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, MID_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 12:    //1001
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, HIGH_ANALOG);
          break;
        case 13:
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, MID_ANALOG);
          break;
        case 14:    //1000
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, LOW_ANALOG);
          analogWrite(motorPinB2, LOW_ANALOG);
          break;
        case 15:
          analogWrite(motorPinA1, HIGH_ANALOG);
          analogWrite(motorPinA2, LOW_ANALOG);
          analogWrite(motorPinB1, HIGH_ANALOG);
          analogWrite(motorPinB2, MID_ANALOG);
          break;
      }
      break;
  } 
}

