#include "Arduino.h"
#include "smoothstepper.h"

SmoothStepper::SmoothStepper(int number_of_full_steps, int substeps_in_step, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4)
{
  this->substep_number = 0;      // which step the motor is on
  this->speed = 0;        // the motor speed, in revolutions per minute
  this->direction = 0;      // motor direction
  this->last_substep_time = 0;    // time stamp in ms of the last step taken
  this->number_of_substeps = number_of_full_steps * substeps_in_step;    // total number of substeps for this motor
  this->substeps_in_step = substeps_in_step;
  
  // Arduino pins for the motor control connection:
  this->motor_pin_1 = motor_pin_1;
  this->motor_pin_2 = motor_pin_2;
  this->motor_pin_3 = motor_pin_3;
  this->motor_pin_4 = motor_pin_4;

  // setup the pins on the microcontroller:
  pinMode(this->motor_pin_1, OUTPUT);
  pinMode(this->motor_pin_2, OUTPUT);
  pinMode(this->motor_pin_3, OUTPUT);
  pinMode(this->motor_pin_4, OUTPUT);
  
  HIGH_A = 255;
  LOW_A = 0;
  MID_A = 0;
}

void SmoothStepper::setSpeed(long whatSpeed)
{
  this->substep_delay = 60L * 1000L / this->number_of_substeps / whatSpeed / this->substeps_in_step;
}

/*
  Moves the motor steps_to_move steps.  If the number is negative, 
   the motor moves in the reverse direction.
 */
void SmoothStepper::step(int number_of_full_steps)
{  
  int substeps_left = abs(number_of_full_steps * this->substeps_in_step);  // how many substeps to take
  
  // determine direction based on whether steps_to_mode is + or -:
  if (number_of_full_steps > 0) {this->direction = 1;}
  if (number_of_full_steps < 0) {this->direction = 0;}
    
    
  // decrement the number of steps, moving one step each time:
  while(substeps_left > 0) {
    // move only if the appropriate delay has passed:
    if (millis() - this->last_substep_time >= this->substep_delay) {
      // get the timeStamp of when you stepped:
      this->last_substep_time = millis();
      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == 1) {
        this->substep_number++;
        if (this->substep_number == this->number_of_substeps) {
          this->substep_number = 0;
        }
      } 
      else { 
        if (this->substep_number == 0) {
          this->substep_number = this->number_of_substeps;
        }
        this->substep_number--;
      }
      // decrement the steps left:
      substeps_left--;
      // step the motor to step number 0, 1, 2, or 3:
      stepMotor(this->substep_number % (4 * this->substeps_in_step));
    }
  }
}

/*
 * Moves the motor forward or backwards.
 */
void SmoothStepper::stepMotor(int thisStep)
{
  switch (this->substeps_in_step) {
    case 1:
      switch (thisStep) {
        case 0:    // 1010
          analogWrite(motor_pin_1, HIGH_A);
          analogWrite(motor_pin_2, LOW_A);
          analogWrite(motor_pin_3, HIGH_A);
          analogWrite(motor_pin_4, LOW_A);
          break;
        case 1:    // 0110
          analogWrite(motor_pin_1, LOW_A);
          analogWrite(motor_pin_2, HIGH_A);
          analogWrite(motor_pin_3, HIGH_A);
          analogWrite(motor_pin_4, LOW_A);
          break;
        case 2:    //0101
          analogWrite(motor_pin_1, LOW_A);
          analogWrite(motor_pin_2, HIGH_A);
          analogWrite(motor_pin_3, LOW_A);
          analogWrite(motor_pin_4, HIGH_A);
          break;
        case 3:    //1001
          analogWrite(motor_pin_1, HIGH_A);
          analogWrite(motor_pin_2, LOW_A);
          analogWrite(motor_pin_3, LOW_A);
          analogWrite(motor_pin_4, HIGH_A);
          break;
      }
      break;
    case 2:
      switch (thisStep) {
        case 0:    // 1010
          analogWrite(motor_pin_1, HIGH_A);
          analogWrite(motor_pin_2, LOW_A);
          analogWrite(motor_pin_3, HIGH_A);
          analogWrite(motor_pin_4, LOW_A);
          break;
        case 1:    // 0010
          analogWrite(motor_pin_1, LOW_A);
          analogWrite(motor_pin_2, LOW_A);
          analogWrite(motor_pin_3, HIGH_A);
          analogWrite(motor_pin_4, LOW_A);
          break;
        case 2:    //0110
          analogWrite(motor_pin_1, LOW_A);
          analogWrite(motor_pin_2, HIGH_A);
          analogWrite(motor_pin_3, HIGH_A);
          analogWrite(motor_pin_4, LOW_A);
          break;
        case 3:    //0100
          analogWrite(motor_pin_1, LOW_A);
          analogWrite(motor_pin_2, HIGH_A);
          analogWrite(motor_pin_3, LOW_A);
          analogWrite(motor_pin_4, LOW_A);
          break;
        case 4:    // 0101
          analogWrite(motor_pin_1, LOW_A);
          analogWrite(motor_pin_2, HIGH_A);
          analogWrite(motor_pin_3, LOW_A);
          analogWrite(motor_pin_4, HIGH_A);
          break;
        case 5:    // 0001
          analogWrite(motor_pin_1, LOW_A);
          analogWrite(motor_pin_2, LOW_A);
          analogWrite(motor_pin_3, LOW_A);
          analogWrite(motor_pin_4, HIGH_A);
          break;
        case 6:    //1001
          analogWrite(motor_pin_1, HIGH_A);
          analogWrite(motor_pin_2, LOW_A);
          analogWrite(motor_pin_3, LOW_A);
          analogWrite(motor_pin_4, HIGH_A);
          break;
        case 7:    //1000
          analogWrite(motor_pin_1, HIGH_A);
          analogWrite(motor_pin_2, LOW_A);
          analogWrite(motor_pin_3, LOW_A);
          analogWrite(motor_pin_4, LOW_A);
          break;
      }
      break;
    case 4:
      break;
  } 
}

