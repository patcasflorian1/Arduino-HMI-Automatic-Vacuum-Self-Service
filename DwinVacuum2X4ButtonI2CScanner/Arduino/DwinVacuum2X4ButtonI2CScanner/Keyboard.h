
 void pcf8574InitKeyboard(){
   pinMode(ARDUINO_UNO_INTERRUPTED_PIN, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(ARDUINO_UNO_INTERRUPTED_PIN), keyChangedOnPCF8574, FALLING);
   
 pcf8574.pinMode(0, INPUT);
  pcf8574.pinMode(1, INPUT);
  pcf8574.pinMode(2, INPUT);
  pcf8574.pinMode(3, INPUT);
  pcf8574.pinMode(4, INPUT);
  pcf8574.pinMode(5, INPUT);
  pcf8574.pinMode(6, INPUT);
  pcf8574.pinMode(7, INPUT);
  pcf8574.begin();
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
 
    for(int i =0; i<8;i++){
 keyboardPin[i] = pcf8574.digitalRead(i);
 delay(6);
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
    //Keyboard for st2
    if((keyboardPin[4]==0)&&(programSelectorSt2 != 1)){ 
     keyPinOutSt2 = 1;  
     erase = true; 
    }
     if((keyboardPin[5]==0)&&(programSelectorSt2 != 2)){  
      keyPinOutSt2 =2;
      erase = true;
    }
    if((keyboardPin[6]==0)&&(programSelectorSt2!= 3)){ 
      keyPinOutSt2 = 3;
      erase = true;   
    }
    if((keyboardPin[7]==0)&&(programSelectorSt2 != 4)){ 
       keyPinOutSt2 = 4;
       erase = true;
    }
    keyChanged = false;
   //Serial.print("keyPinOut= ");  Serial.println(keyPinOut);
 }

