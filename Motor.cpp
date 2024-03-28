#include "Motor.h"



Pleth_Motor::Pleth_Motor(Adafruit_StepperMotor* PlethMotor, byte pinFLabView, byte pinBLabView, byte Forwardpin, byte Backwardpin, byte Homepin) {      
  this->PlethMotor = PlethMotor;
  this->pinFLabView = pinFLabView;            //Assigns the variable to it's own changing value
  this->pinBLabView = pinBLabView;
  this->Forwardpin = Forwardpin;               //Assigns the variable to it's own changing value
  this->Backwardpin = Backwardpin;
  this->Homepin = Homepin;
  init_Pleth();                                     //Starts the initiation/Pin out set up method
}

Pleth_Motor::Pleth_Motor() {
  this->pinFLabView = 8;            //Assigns the variable to it's own changing value
  this->pinBLabView = 7;
  this->Forwardpin = 2;               //Assigns the variable to it's own changing value
  this->Backwardpin = 4;
  this->Homepin = 12;
  init_Pleth();
}

void Pleth_Motor::init_Pleth() {              
  pinMode(pinFLabView, OUTPUT);               //Assigns the pin out to the output signals
  pinMode(pinBLabView, OUTPUT);               //Assigns the pin out to the output signals
  pinMode(Forwardpin, INPUT_PULLUP);                        //Assigns pins as input pins
  pinMode(Backwardpin, INPUT_PULLUP);                        //Assigns pins as input pins
  pinMode(Homepin, INPUT_PULLUP); 
  LastForVal = LOW;
  LastBackVal= LOW;
  LastHomeVal = LOW;
                                        //Starts the release Method to set up motor
}

void Pleth_Motor::step_F() {
  Serial.println("Step F");
  PlethMotor->step(50, FORWARD, MICROSTEP);          //Object takes one turn forward
  digitalWrite(pinFLabView, HIGH);            //Relays output signal about successful step
  p=p+1;                                        //Increases the Position tracker
}

void Pleth_Motor::step_B() {
  Serial.println("Step B");
  PlethMotor->step(50, BACKWARD, MICROSTEP);         //Object takes one turn backward
  digitalWrite(pinBLabView, HIGH);            //Relays output signal about successful step
  p=p-1;                                        //Decreases the Position tracker
}

//void Pleth_Motor::off() {
  //digitalWrite(pinFLabView, LOW);             //Relays that motor is now off and not moving
  //digitalWrite(pinBLabView, LOW);             //Relays that motor is now off and not moving
//}

void Pleth_Motor::GoHome() { 
  Serial.println(p);   
  if (p > 0) {                                //Checks position value
    PlethMotor->step((50*p), BACKWARD, MICROSTEP);
    LastHomeVal = LOW;
    return 1;       //Backs the motor up towards the inital position
  }
  if (p < 0) {                                //Checks position value
    p = (0 - p);                                //Assigns absolute value of position
    PlethMotor->step((50*p), FORWARD, MICROSTEP);
    LastHomeVal = LOW;
    return 1;        //Moves the motor towards the intial position
  }
  else 
    Serial.println("At Home");
    LastHomeVal = LOW;
    //off();  
    return 0;                                  //Relays that motor has stopped moving

}

int Pleth_Motor::ReadInputs() {
  CurForVal=digitalRead(Forwardpin);
  CurBackVal=digitalRead(Backwardpin);
  CurHomeVal=digitalRead(Homepin);
  if (!LastForVal && CurForVal) {
    LastForVal = CurForVal;
    Serial.println("Recieved 1");
    step_F();
    //delay(100);
    Serial.println("Forward");
    
    return 1;
  }
  if (!LastBackVal && CurBackVal) {
    LastBackVal = CurBackVal;
    Serial.println("Recieved 2");
    step_B(); 
    //delay(100);
    Serial.println("Backward");
    
    return 1;
  }
  else if (!LastHomeVal && CurHomeVal) {
    LastHomeVal=CurHomeVal;
    Serial.println("Recieved 3");
    GoHome();
    //delay(100);
    
  }
  else {
    LastForVal = LOW;
    LastBackVal= LOW;
    LastHomeVal = LOW;
      return 0;
  }
}