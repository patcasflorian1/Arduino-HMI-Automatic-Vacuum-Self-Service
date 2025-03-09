#include "HardwareSerial.h"
#include "Arduino.h"

 void pcf8574InitKeyboard(){
   //pcf8574.begin();
  pcf8574.pinMode(0, INPUT);
  pcf8574.pinMode(1, INPUT);
  pcf8574.pinMode(2, INPUT);
  pcf8574.pinMode(3, INPUT);

  pcf8574.pinMode(4, INPUT);
  pcf8574.pinMode(5, INPUT);
  pcf8574.pinMode(6, INPUT);
  pcf8574.pinMode(7, INPUT);
  pcf8574.digitalWrite(0, HIGH);
  pcf8574.digitalWrite(1, HIGH);
  pcf8574.digitalWrite(2, HIGH);
  pcf8574.digitalWrite(3, HIGH);
  pcf8574.digitalWrite(4, HIGH);
  pcf8574.digitalWrite(5, HIGH);
  pcf8574.digitalWrite(6, HIGH);
  pcf8574.digitalWrite(7, HIGH);
 
  Serial.print("Init pcf8574...");
  if (pcf8574.begin()){
    Serial.println("OK-Keyboard");
  }else{
    Serial.println("KO-Key");
  }
  
 }

void pcf8574Run(){
//pcf8574.begin();
   if(keyChanged==true){
    // Serial.print("KeyChange ");Serial.println(keyChanged);
     if (DelayKey >= KeyInterval)
  {
    for(int i =0; i<8;i++){
       wdt_reset();
 pin[i] = pcf8574.digitalRead(i);
 delay(1);
if(pin[i]==1){
  count++;
}
// Serial.print("Pin "); Serial.print(i);Serial.print(" = ");Serial.println(pin[i]);
    
  }
  //Keyboard for st1
    if(pin[0]==0){
     
     keyPinOut = 1;
    }
     if(pin[1]==0){
    
     keyPinOut = 2;
    }
    if(pin[2]==0){
    
     keyPinOut = 3;
    }
    if(pin[3]==0){
   
     keyPinOut = 4;
    }
//Keyboard for st2
       if(pin[4]==0){
     
       keyPinOut = 5;
    }
     if(pin[5]==0){
     
      keyPinOut = 6;
    }
    if(pin[6]==0){
     
      keyPinOut = 7;
    }
    if(pin[7]==0){
     
      keyPinOut = 8;
    }
     DelayKey = 0; 
  }
    keyChanged = false;
    //Serial.print("KeyChange1 ");Serial.println(keyChanged);
   }
  // Serial.print("count ");Serial.println(count);
    if(count == 8){
      keyPinOut = 0 ;
    }
    count = 0 ;
   // delay(5);
 }

 void keyChangedOnPCF8574(){
 // Interrupt called (No Serial no read no wire in this function, and DEBUG disabled on PCF library)
   keyChanged = true;
}
