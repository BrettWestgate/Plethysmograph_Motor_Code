#ifndef MY_MOTOR_H
#define MY_MOTOR_H

#include <Arduino.h>
#include <Adafruit_MotorShield.h>
//#include <Adafruit_MotorShield.cpp>


class Pleth_Motor {

  private:
  byte pinFLabView;               //Output Pin Variable
  byte pinBLabView;
  byte Forwardpin;
  byte Backwardpin;
  byte Homepin;
  byte state;
  byte LastForVal;
  byte LastBackVal;
  byte LastHomeVal;
  byte CurForVal;
  byte CurBackVal;
  byte CurHomeVal;
  int p;   
  Adafruit_StepperMotor* PlethMotor;                       //Steps/Position Variable
  

  public:
  Pleth_Motor(Adafruit_StepperMotor* PlethMotor, byte pinFLabView, byte pinBLabView, byte Forwardpin, byte Backwardpin, byte Homepin);

  Pleth_Motor();                  //Method to set up Pin outs
  void init_Pleth();                    //Method to assign the Pin outs
  void step_F();                  //Method for forward step
  void step_B();                  //Method for backward step
  void off();                     //Method for release/output signalling release
  void Position(int p) {          //Method for steps tracking
    this->p = p;
  }
  void GoHome();                  //Method for returning to beginnning position
  int ReadInputs();
};

#endif
