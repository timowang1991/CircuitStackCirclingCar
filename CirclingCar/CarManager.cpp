

#include "CarManager.h"

CarManager::CarManager(int leftRCPin, int rightRCPin, int leftMotorPin, int rightMotorPin){
   _leftMotor = new MotorManager(LeftMotorPin);
   _rightMotor = new MotorManager(RightMotorPin);
   _leftRC = new RCManager(LeftRCPin);
   _rightRC = new RCManager(RightRCPin);
   _isLeftOnLine = false;
   _isRightOnLine = false;
   _startFlag = true;
}

void CarManager::start(){
   // Serial.println("start : first line");
   if (_startFlag == false){
      _rightMotor->stop();
      _leftMotor->stop();
      return;
   }
   // Serial.println("start : after _startFlag");

   if (digitalRead(InterruptPin) == LOW){
      // Serial.println("InterruptPin pushed");
      RCBoundaryCalibration();
   }

   // Serial.println("InterruptPin not pushed");

   // Read from RCMangager

   // Change Motor according to RC
   // _leftMotor->drive(LeftVelocity);
   // _rightMotor->drive(RightVelocity);
   _leftMotor->stop();
   _rightMotor->stop();

   if(_leftRC->isOnLine()){ // Modify toward left when left on line
      // _rightMotor->drive(RightVelocity);
      // _leftMotor->stop();
      Serial.println();
      Serial.println("left is on line");
   } else if(_rightRC->isOnLine()){ // Modify toward right when right on line
      // _leftMotor->drive(LeftVelocity);
      // _rightMotor->stop();
      Serial.println();
      Serial.println("right is on line");
   } else {   // Go Forward
      // _leftMotor->drive(LeftVelocity);
      // _rightMotor->drive(RightVelocity);
      Serial.println("both are not on line");
   }

}

void CarManager::RCBoundaryCalibration(){
   _rightMotor->stop();
   _leftMotor->stop();
   delay(1000);
   while(digitalRead(InterruptPin) == HIGH);
   // Serial.println("Before Left White Calibration");
   _leftRC->calibrateWhite();
   // Serial.println("Before Right White Calibration");
   _rightRC->calibrateWhite();
   delay(1000);
   while(digitalRead(InterruptPin) == HIGH);
   // Serial.println("Before Left Black Calibration");
   _leftRC->calibrateBlack();
   // Serial.println("Before Right Black Calibration");
   _rightRC->calibrateBlack();
}
