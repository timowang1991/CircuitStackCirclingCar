
#include <Servo.h>
#include "CarManager.h"

CarManager * carManager;

void setup()
{
   // Set sensorPin for leftRC, rightRC, leftMotor, rightMotor, respectively
   Serial.begin(9600);
   pinMode(InterruptPin, INPUT_PULLUP);
   pinMode(InterruptPin2, INPUT_PULLUP);
   carManager = new CarManager(LeftRCPin, RightRCPin, LeftMotorPin, RightMotorPin);

   attachInterrupt(InterruptNumber, interruptServiceRoutine, TriggerMode);
   attachInterrupt(InterruptNumber2, interruptServiceRoutineSecond, TriggerMode);
}

void loop()
{
   carManager->start();

   delay(500);
}

void interruptServiceRoutine(){
   Serial.println("interruptServiceRoutine");
   carManager->RCBoundaryCalibration();
}

void interruptServiceRoutineSecond(){
   carManager->_startFlag = !carManager->_startFlag;

}
