#ifndef CAR_MANAGER
#define CAR_MANAGER

#include <Arduino.h>
#include "MotorManager.h"
#include "RCManager.h"
#include "macro.h"

class CarManager
{
public:
   CarManager(int leftRCPin, int rightRCPin, int leftMotorPin, int rightMotorPin);
   ~CarManager();
   
   bool _startFlag;
   void start();
   void RCBoundaryCalibration();
private:
   MotorManager *_leftMotor, *_rightMotor;
   RCManager *_leftRC, *_rightRC;
   bool _isLeftOnLine, _isRightOnLine;
};

#endif
