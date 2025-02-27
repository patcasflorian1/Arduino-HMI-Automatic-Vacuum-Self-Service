#include "Arduino.h"
#include <elapsedMillis.h> 

 void ledDriverInit(){
// Set pinMode to OUTPUT


  Serial.print("Init ledDriver...");
  if (ledDriver.begin()){
    Serial.println("OK-LED");
  }else{
    Serial.println("KO-LED");
  }
  
 for(int i=0; i<8;i++){
ledDriver.pinMode(i, OUTPUT);
ledDriver.digitalWrite(i,HIGH);
delay(1);
 }
 }

 void ledDriverRunVaccum(){
 unsigned int intervalBlink =500;
 wdt_reset();
 if(timeElapsedLed>intervalBlink){
     for(int i=0; i<8;i++){ 
    ledDriver.digitalWrite(led[i], HIGH);
     }
     if(timeElapsedLed>(intervalBlink*2)){
    timeElapsedLed=0;
     }
    }
    else{
       for(int i=0; i<8;i++){
      ledDriver.digitalWrite(led[i], LOW);
       }
    }
 }

