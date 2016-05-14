
#include "RCManager.h"

RCManager::RCManager()
   :_sensorPin(2), _boundary(0), _whiteCalibrate(0), _blackCalibrate(0), _result(0){}

RCManager::RCManager(int sensorPin)
   :_sensorPin(sensorPin), _boundary(0), _whiteCalibrate(0), _blackCalibrate(0), _result(0){}

RCManager::~RCManager(){
   _sensorPin = 0;
   _result = 0;
}

long RCManager::RCtime(){
   long result = 0;
   pinMode(_sensorPin, OUTPUT);       // make pin OUTPUT
   digitalWrite(_sensorPin, HIGH);    // make pin HIGH to discharge capacitor - study the schematic
   delay(1);                       // wait a  ms to make sure cap is discharged

   pinMode(_sensorPin, INPUT);        // turn pin into an input and time till pin goes low
   digitalWrite(_sensorPin, LOW);     // turn pullups off - or it won't work
   while(digitalRead(_sensorPin)){    // wait for pin to go low
      result++;
   }

   return result;                   // report results   
}

bool RCManager::isOnLine(){
   return RCtime() > _boundary;
}

void RCManager::calibrateWhite(){
   long bigResult = 0;
   int T = 30;
   while(T--){
      bigResult += RCtime();
      Serial.println(RCtime());
   }  
   _whiteCalibrate = bigResult / 30;
   Serial.println(_whiteCalibrate);
}

void RCManager::calibrateBlack(){
   long bigResult = 0;
   int T = 30;
   while(T--){
      bigResult += RCtime();
   }  
   _blackCalibrate = bigResult / 30;

   _boundary = (_whiteCalibrate + _blackCalibrate) / 2;
}
