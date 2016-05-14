
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

   // attachInterrupt(InterruptNumber, interruptServiceRoutine, TriggerMode);
   // attachInterrupt(InterruptNumber2, interruptServiceRoutineSecond, TriggerMode);
}

void loop()
{
   carManager->start();
   // Serial.println(RCtime(12));
   // delay(10);
}

void interruptServiceRoutine(){
   Serial.println("interruptServiceRoutine");
   carManager->RCBoundaryCalibration();
}

void interruptServiceRoutineSecond(){
   carManager->_startFlag = !carManager->_startFlag;

}

long RCtime(int sensPin){
   long result = 0;
   pinMode(sensPin, OUTPUT);       // make pin OUTPUT
   digitalWrite(sensPin, HIGH);    // make pin HIGH to discharge capacitor - study the schematic
   delay(1);                       // wait a  ms to make sure cap is discharged

   pinMode(sensPin, INPUT);        // turn pin into an input and time till pin goes low
   digitalWrite(sensPin, LOW);     // turn pullups off - or it won't work
   while(digitalRead(sensPin)){    // wait for pin to go low
      result++;
   }

   return result;                   // report results   
}