#ifndef MOTOR_MANAGER
#define MOTOR_MANAGER

#include <Arduino.h>
#include <Servo.h>
#include "macro.h"

class MotorManager
{
public:
   MotorManager(int pin);
   ~MotorManager();

   void drive(int velocity);
   void stop();
private:
   int _stop_position;
   Servo _servo;
};

#endif
