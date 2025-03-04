#include "Arduino.h"
#include <elapsedMillis.h> 
// Constante
const uint8_t PCF8574_LED_ADDRESS = 0x38;
const int NUM_LEDS = 4;
const unsigned long LED_BLINK_INTERVAL = 400;

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
 static uint8_t ledState = 0;
  static uint8_t currentLed = 0;
  static uint8_t direction = 1;  // 1 pentru dreapta, 0 pentru stânga
  
  wdt_reset();
  
  if (timeElapsedLed >= LED_BLINK_INTERVAL) {
    // Stingem toate LED-urile
    for (int i = 0; i < NUM_LEDS; i++) {
      ledDriver.digitalWrite(led[i], HIGH);
    }
    
    // Aprindem LED-ul curent
    ledDriver.digitalWrite(led[currentLed], LOW);
    
    // Actualizăm poziția următorului LED
    if (direction) {
      currentLed++;
      if (currentLed >= NUM_LEDS) {
        currentLed = NUM_LEDS - 1;
        direction = 0;
      }
    } else {
      currentLed--;
      if (currentLed >= NUM_LEDS) {  // Verificare pentru underflow
        currentLed = 0;
        direction = 1;
      }
    }
    
    timeElapsedLed = 0;
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

