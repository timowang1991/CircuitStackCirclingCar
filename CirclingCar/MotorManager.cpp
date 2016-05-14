#include "MotorManager.h"

MotorManager::MotorManager(int pin){
   _stop_position = 90;
   _servo.attach(pin);
}

void MotorManager::drive(int velocity){
   _servo.write(_stop_position - velocity);
   // delay(20);
}

void MotorManager::stop(){
   _servo.write(_stop_position);
   // delay(20);
}


