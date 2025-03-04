#include "Arduino.h"
#include <elapsedMillis.h> 





 void ledDriverInit(){
// Set pinMode to OUTPUT
//ledDriver.begin();
 for(int i=0; i<8;i++){
ledDriver.pinMode(i, OUTPUT);
ledDriver.digitalWrite(i,HIGH);
delay(1);
 }

  Serial.print("Init ledDriver...");
  if (ledDriver.begin()){
    Serial.println("OK-LED");
  }else{
    Serial.println("KO-LED");
  }
 }

 void ledDriverRun(){
  int ledState = 0;
 // int intervalBlink =1000;
wdt_reset();
     for(int i=0; i<4;i++){ 
       while(ledState == 0){
      
        if((timeElapsedLed>=interval)&&(ledState == 0)){
    ledState = 1;
      ledDriver.digitalWrite(led[i], HIGH); //delay(400);
      timeElapsedLed=0;
     }
    }
    while(ledState == 1){
      wdt_reset();
      if ((timeElapsedLed>= interval)&&(ledState == 1)) {
      ledState = 0;
      ledDriver.digitalWrite(led[i], LOW); //delay(400);
      timeElapsedLed=0;
    }
    }
  }  
 }

 void ledDriverRunVaccum(){
 unsigned int intervalBlink =500;
 wdt_reset();
 if(timeElapsedLed>intervalBlink){
     for(int i=0; i<4;i++){ 
    ledDriver.digitalWrite(led[i], HIGH);
     }
     if(timeElapsedLed>(intervalBlink*2)){
    timeElapsedLed=0;
     }
    }
    else{
       for(int i=0; i<4;i++){
      ledDriver.digitalWrite(led[i], LOW);
       }
    }
 }

