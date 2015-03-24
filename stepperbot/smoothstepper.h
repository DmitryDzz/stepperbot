#ifndef SmoothStepper_h
#define SmoothStepper_h

// library interface description
class SmoothStepper {
  public:
    SmoothStepper(int number_of_full_steps, int substeps_in_step, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

    void setSpeed(long whatSpeed);

    void step(int number_of_full_steps);

  private:
    void stepMotor(int this_substep);
    
    int direction;        // Direction of rotation
    int speed;          // Speed in RPMs
    unsigned long substep_delay;    // delay between steps, in ms, based on speed
    int number_of_substeps;
    int substeps_in_step;
    int substep_number;        // which step the motor is on
    
    // motor pin numbers:
    int motor_pin_1;
    int motor_pin_2;
    int motor_pin_3;
    int motor_pin_4;
    
    long last_substep_time;      // time stamp in ms of when the last step was taken
    
    unsigned short HIGH_A;
    unsigned short LOW_A;
    unsigned short MID_A;
};

#endif

