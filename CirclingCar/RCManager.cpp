
#include "RCManager.h"

RCManager::RCManager()
   :_sensorPin(2), _boundary(0), _whiteCalibrate(0), _blackCalibrate(0){}

RCManager::RCManager(int sensorPin)
   :_sensorPin(sensorPin), _boundary(0), _whiteCalibrate(0), _blackCalibrate(0){
   _samples = new RunningMedian(SIZE_OF_IR_MEDIAN_FILTER);
}

RCManager::~RCManager(){
   _sensorPin = 0;
   delete _samples;
}

long RCManager::RCtime(int sensorPin){
   long result = 0;
   pinMode(sensorPin, OUTPUT);       // make pin OUTPUT
   digitalWrite(sensorPin, HIGH);    // make pin HIGH to discharge capacitor - study the schematic
   delay(1);                       // wait a  ms to make sure cap is discharged

   pinMode(sensorPin, INPUT);        // turn pin into an input and time till pin goes low
   digitalWrite(sensorPin, LOW);     // turn pullups off - or it won't work
   while(digitalRead(sensorPin)){    // wait for pin to go low
      result++;
   }

   return result;                   // report results   
}

bool RCManager::isOnLine(){
   _samples->clear();
   for (int i = 0; i < SIZE_OF_IR_MEDIAN_FILTER; ++i){
      _samples->add(RCtime(_sensorPin));
   }
   Serial.print(_samples->getMedian());
   Serial.print("  ");

   return _samples->getMedian() > _boundary;
}

void RCManager::calibrateWhite(){
   // long bigResult = 0;
   // int T = 30;
   // while(T--){
   //    bigResult += RCtime();
   //    Serial.println(RCtime());
   // }  
   // _whiteCalibrate = bigResult / 30;
   // Serial.println(_whiteCalibrate);
   _samples->clear();
   for (int i = 0; i < SIZE_OF_IR_CALI_MEDIAN_FILTER; ++i){
      long rcTime = RCtime(_sensorPin);
      Serial.println(rcTime);
      _samples->add(rcTime);
   }
   _whiteCalibrate = (long) _samples->getMedian();
   Serial.print("_whiteCalibrate = ");
   Serial.println(_whiteCalibrate);
}

void RCManager::calibrateBlack(){
   // long bigResult = 0;
   // int T = 30;
   // while(T--){
   //    bigResult += RCtime();
   // }  
   // _blackCalibrate = bigResult / 30;

   _samples->clear();
   for (int i = 0; i < SIZE_OF_IR_CALI_MEDIAN_FILTER; ++i){
      long rcTime = RCtime(_sensorPin);
      Serial.println(rcTime);
      _samples->add(rcTime);
   }
   _blackCalibrate = (long) _samples->getMedian();
   Serial.print("_blackCalibrate = ");
   Serial.println(_blackCalibrate);

   _boundary = (_whiteCalibrate + _blackCalibrate) / 2;
   Serial.print("_boundary = ");
   Serial.println(_boundary);
}
