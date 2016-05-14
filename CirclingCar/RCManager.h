#ifndef RC_MANAGER
#define RC_MANAGER


#include <Arduino.h>

class RCManager
{
public:
   RCManager();
   RCManager(int sensorPin);
   ~RCManager();
   long RCtime();
   void calibrateWhite();
   void calibrateBlack();
   bool isOnLine();
private:
   int _sensorPin;
   long _boundary, _whiteCalibrate, _blackCalibrate;
   long _result;
};

#endif
