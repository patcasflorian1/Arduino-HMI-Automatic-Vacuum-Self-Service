

 void pcf8574InitKeyboard(){
  // pinMode(ARDUINO_UNO_INTERRUPTED_PIN, INPUT_PULLUP);
 // attachInterrupt(digitalPinToInterrupt(ARDUINO_UNO_INTERRUPTED_PIN), keyChangedOnPCF8574, FALLING);
   //pcf8574.begin();
  pcf8574.pinMode(0, INPUT);
  pcf8574.pinMode(1, INPUT);
  pcf8574.pinMode(2, INPUT);
  pcf8574.pinMode(3, INPUT);
  Serial.print("Init pcf8574...");
  if (pcf8574.begin()){
    Serial.println("OK-Keyboard");
  }else{
    Serial.println("KO-Key");
  }
  
 }
void pcf8574Run(){
  timeKeypadElapse = 0;
 //Serial.print("keyChanged "); Serial.println(keyChanged);
 
    for(int i =0; i<4;i++){
 keyboardPin[i] = pcf8574.digitalRead(i);
 delay(2);
 // Serial.print("keyPinOut "); Serial.print(i);Serial.print(" = ");  Serial.println(keyboardPin[i]);
  }
  wdt_reset();
  //Keyboard for st1
  if((keyboardPin[0]==0)&&(programSelector != 1)){ 
     keyPinOut = 1; 
     erase = true;  
    }
     if((keyboardPin[1]==0)&&(programSelector != 2)){  
      keyPinOut = 2;
      erase = true;
    }
    if((keyboardPin[2]==0)&&(programSelector != 3)){ 
      keyPinOut = 3;
      erase = true;   
    }
    if((keyboardPin[3]==0)&&(programSelector != 4)){ 
       keyPinOut = 4;
       erase = true;
    } 
   keyChanged = false; 
   
   //Serial.print("keyPinOut= ");  Serial.println(keyPinOut);
 }

