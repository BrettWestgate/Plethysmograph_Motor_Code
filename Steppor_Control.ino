#include "Motor.h"
//#include "Control.h"

#define Forward_Con 2 
#define Backward_Con 4
#define Home_Con 12

#define Forward_Send 7
#define Backward_Send 8                                     //Defines which pins will be used

#include <Adafruit_MotorShield.h>


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);   //Connects to Motorshield/Stepper motor

//Control LabView (Forward_Con, Backward_Con, Home_Con);                             //Creates Instance in the control class

Pleth_Motor Motor (myMotor, Forward_Send, Backward_Send, Forward_Con, Backward_Con, Home_Con);                       //Creates Instance in the motor class

int M;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
    }

  Serial.println("Motor Shield found.");

  myMotor->setSpeed(10);  // 10 rpm                           //Signals motor is ready to begin
  Motor.init_Pleth();
  myMotor->step(10, FORWARD, SINGLE);
}

void loop() {
  // put your main code here, to run repeatedly:
  M=Motor.ReadInputs();                             //Checks if a front step input has been recieved
    //Motor.off();
    delay(250);
    PlotPins();
  }

void PlotPins() {
  Serial.print("V3:");
  Serial.print(digitalRead(Home_Con));
  Serial.print(",");
  Serial.print("V2:");
  Serial.print(digitalRead(Backward_Con));
  Serial.print(",");
  Serial.print("V1:");
  Serial.println(digitalRead(Forward_Con));
}