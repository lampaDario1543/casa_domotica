#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute =11;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper myStepper(stepsPerRevolution, 10, 12, 11, 13);
const int add=650;
void setup() {
  myStepper.setSpeed(rolePerMinute);
  myStepper.step(-(stepsPerRevolution+add));
  //myStepper.step(-(1619));
  delay(5000);
  myStepper.step((stepsPerRevolution+add));
  //myStepper.step((1619));
  //myStepper.step(stepsPerRevolution);
}

void loop() {
}
