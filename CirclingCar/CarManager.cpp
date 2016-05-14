

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
   if (_startFlag == false){
      _rightMotor->stop();
      _leftMotor->stop();
      return;
   }

   bool isLeftOnLine, isRightOnLine;

   // Read from RCMangager
   _isLeftOnLine = _leftRC->isOnLine();
   _isRightOnLine = _rightRC->isOnLine();

   // Change Motor according to RC
   // _leftMotor->drive(LeftVelocity);
   // _rightMotor->drive(RightVelocity);
   _leftMotor->stop();
   _rightMotor->stop();

   // if(_isLeftOnLine){ // Modify toward left when left on line
   //    _rightMotor->drive(RightVelocity);
   //    _leftMotor->stop();
   // } else if(_isRightOnLine){ // Modify toward right when right on line
   //    _leftMotor->drive(LeftVelocity);
   //    _rightMotor->stop();
   // } else {   // Go Forward
   //    _leftMotor->drive(LeftVelocity);
   //    _rightMotor->drive(RightVelocity);
   // }

}

void CarManager::RCBoundaryCalibration(){
   Serial.println("Before Left White Calibration");
   _leftRC->calibrateWhite();
   Serial.println("Before Right White Calibration");
   _rightRC->calibrateWhite();
   delay(1000);
   while(digitalRead(InterruptPin) == HIGH);
   Serial.println("Before Left Black Calibration");
   _leftRC->calibrateBlack();
   Serial.println("Before Right Black Calibration");
   _rightRC->calibrateBlack();
}
