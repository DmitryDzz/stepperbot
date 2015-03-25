#ifndef SmoothStepper_h
#define SmoothStepper_h

enum StepperMode {
  FULL_STEP = 1,
  HALF_STEP = 2,
  QUARTER_STEP = 4
};

class SmoothStepper {
  public:
    SmoothStepper(int motorFullStepsNumber, StepperMode stepperMode, int motorPinA1, int motorPinA2, int motorPinB1, int motorPinB2);

    void zero(long substepDelay);
    void start(long period, long substeps, long timestamp);
    void stop();
    void update(long timestamp);

  private:
    bool started;
    int motorFullStepsNumber;
    StepperMode stepperMode;

    signed short direction;
    long substepDelay;
    long lastTimestamp;
    long substeps;
    long currentSubstep;
    long currentPhase;
    
    // motor pin numbers:
    int motorPinA1;
    int motorPinA2;
    int motorPinB1;
    int motorPinB2;
    
    unsigned short HIGH_ANALOG;
    unsigned short LOW_ANALOG;
    unsigned short MID_ANALOG;
    
    void updateMotor(long phase);
};

#endif

