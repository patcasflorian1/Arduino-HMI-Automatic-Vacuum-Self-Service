
void displayHmiProgram(int selectProg){

//Serial.print(" SelectProg ");Serial.println(selectProg);
  switch (selectProg){
    case 1:{
      
      //displayTimeHmi(minuteRamase,secundeRamase);
      if(erase == true){
       printf_dwin(0x2000,"ASPIRARE     ");
      }
    } break;
    case 2:{
     //displayTimeHmi(minuteRamase,secundeRamase);
     if(erase == true){
     printf_dwin(0x2000,"PARFUM       ");
     }
    } break;
    case 3:{
      //switchPage(1);
      //displayTimeHmi(minuteRamase,secundeRamase);
      if(erase == true){
      printf_dwin(0x2000,"NEGRU CAUCIUC");
      //printf_dwin(0x2100,"CAUCIUC");
      }
    } break;
    case 4:{
    //  switchPage(1);
    // displayTimeHmi(minuteRamase,secundeRamase);
     if(erase == true){
     printf_dwin(0x2000,"AER COMPRIMAT");
     }
    } break;
  }
}
  void displayHmiProgramSt2(int selectProg){

//Serial.print(" SelectProg ");Serial.println(selectProg);
  switch (selectProg){
    case 1:{
      
      //displayTimeHmi(minuteRamase,secundeRamase);
      if(erase == true){
       printf_dwin(0x2100,"ASPIRARE     ");
      }
    } break;
    case 2:{
      
     //displayTimeHmi(minuteRamase,secundeRamase);
     if(erase == true){
     printf_dwin(0x2100,"PARFUM       ");
     }
    } break;
    case 3:{
      //switchPage(1);
      //displayTimeHmi(minuteRamase,secundeRamase);
      if(erase == true){
      printf_dwin(0x2100,"NEGRU CAUCIUC");
      //printf_dwin(0x2100,"CAUCIUC");
      }
    } break;
    case 4:{
    //  switchPage(1);
    // displayTimeHmi(minuteRamase,secundeRamase);
     if(erase == true){
     printf_dwin(0x2100,"AER COMPRIMAT");
     }
    } break;
  }
}


void vacuumCleaner(){
boolean isOk =false;
timeCoin1 = EEPROM.get(timeCoins1,timeCoin1);
timeCoin2 = EEPROM.get(timeCoins2,timeCoin2);
timeCoin3= EEPROM.get(timeCoins3,timeCoin3);
timeCoin4 = EEPROM.get(timeCoins4,timeCoin4);
// Serial.print(" timeCoin1 "); Serial.println(timeCoin1);
//  Serial.print(" timeCoin2 "); Serial.println(timeCoin2);
 // Serial.print(" timeCoin3 "); Serial.println(timeCoin3);
 // Serial.print(" timeCoin4 "); Serial.println(timeCoin4);
elapsedMillis timeContor; //declare global if you don't want it reset every time loop runs
elapsedMillis timeContorSt2; //declare global if you don't want it reset every time loop runs
   unsigned int interval = 1000;
 programSelector = 0;
  if(coin == 0){
    return;
  }
   eraseText(0x20, 250);
    eraseText(0x21, 250);
    displayTimeHmi(0,0);
    displayTimeHmiSt2(0,0);
   
   while(isOk == false){
   wdt_reset();
     if((timeElapsedLed>=interval)&&(ledState == 0)){
    ledState = 1;
      ledDriver.digitalWrite(led[ledCount], HIGH); 
      ledDriver.digitalWrite(led[ledCount+4], HIGH); 
      timeElapsedLed=0;
     }
      wdt_reset();
      if ((timeElapsedLed>= interval)&&(ledState == 1)) {
      ledState = 0;
      ledDriver.digitalWrite(led[ledCount], LOW); 
      ledDriver.digitalWrite(led[ledCount+4], LOW); 
      timeElapsedLed=0;
      ledCount++;
    }
     if(ledCount>3){
    ledCount =0;
  } 
   if(coin>oldCoin){
    oldCoin = coin;
    displayCredit(coin);
   }
   
     if(keyChanged==true){
    pcf8574Run();
    oldCoin = 0;
    displayCredit(oldCoin);
     }
    switch(keyPinOut){
    case 1:{
     displayHmiProgram(keyPinOut);
       startProgram(timeCoin1,programSelector,0);
       isOk = true;   
    }break;
    case 2:{     
    displayHmiProgram(keyPinOut);
       startProgram(timeCoin2,programSelector,3);
       isOk = true;  
    }break;
    case 3:{   
     displayHmiProgram(keyPinOut);
       startProgram(timeCoin3,programSelector,2);
       isOk = true;   
    }break;
    case 4:{   
    displayHmiProgram(keyPinOut);
       startProgram(timeCoin4,programSelector,1);
       isOk = true;  
    }break;
    }

    //St2
     switch(keyPinOutSt2){
     case 1:{
     displayHmiProgramSt2(keyPinOutSt2);
       startProgramSt2(timeCoin1,programSelectorSt2,4);
       isOk = true;   
    }break;
    case 2:{     
    displayHmiProgramSt2(keyPinOutSt2);
       startProgramSt2(timeCoin2,programSelectorSt2,5);
       isOk = true;  
    }break;
    case 3:{   
     displayHmiProgramSt2(keyPinOutSt2);
       startProgramSt2(timeCoin3,programSelectorSt2,6);
       isOk = true;   
    }break;
    case 4:{   
    displayHmiProgramSt2(keyPinOutSt2);
       startProgramSt2(timeCoin4,programSelectorSt2,7);
       isOk = true;  
    }break;
  }
   }
  while(isOk == true){
    wdt_reset();
  ledDriverRunVaccum();
    if(coin>oldCoin){
    oldCoin = coin;
    displayCredit(coin);
   }
  
 if((totalTimeCoin ==0)&&(coin == 0)){
  keyPinOut = 0;
 }  
    if((totalTimeCoin > 0)||(coin>0)){  
  switch(keyPinOut){
    case 1:{        
        displayHmiProgram(keyPinOut);
    startProgram(timeCoin1,programSelector,0);
      
    }break;
    case 2:{        
        displayHmiProgram(keyPinOut);
      startProgram(timeCoin2,programSelector,3);
             
    }break;
    case 3:{     
       displayHmiProgram(keyPinOut);       
      startProgram(timeCoin3,programSelector,2);
        
    }break;
    case 4:{ 
       
       displayHmiProgram(keyPinOut);      
        startProgram(timeCoin4,programSelector,1);
         
    }break;
  }
    }
  //St2
 if((totalTimeCoinSt2 ==0)&&(coin == 0)){
  keyPinOutSt2 = 0;
 }
  if((totalTimeCoinSt2 > 0)||(coin>0)){
  switch(keyPinOutSt2){    
     case 1:{              
       displayHmiProgramSt2(keyPinOutSt2);  
     startProgramSt2(timeCoin1,programSelectorSt2,4);
         
    }break;
  case 2:{           
       displayHmiProgramSt2(keyPinOutSt2);      
       startProgramSt2(timeCoin2,programSelectorSt2,5);
      
    }break;
    case 3:{ 
       displayHmiProgramSt2(keyPinOutSt2);       
            startProgramSt2(timeCoin3,programSelectorSt2,6);
        
    }break;
    case 4:{  
       displayHmiProgramSt2(keyPinOutSt2);   
      startProgramSt2(timeCoin4,programSelectorSt2,7);
       
    }break;
  }
  }
   if(keyChanged==true){
    pcf8574Run();
    
     }
  //St1
  if(totalTimeCoin > 0){
    if(timeContor>interval){     
      if((secundeRamase <=0)&&(minuteRamase >0)){
    minuteRamase--;
   secundeRamase = 59;
    }
    secundeRamase--;
    timeContor =0;
    if((secundeRamase < 0)&&(minuteRamase <= 0)){
   secundeRamase = 0;
    }
    displayTimeHmi(minuteRamase,secundeRamase);
      totalTimeCoin--;  
      if(totalTimeCoin > 30000){
    totalTimeCoin = 60;
   }
    if(totalTimeCoin <=0 ){
      displayTimeHmi(0,0);
      //switchPage(0);
      totalTimeCoin = 0;
      timeContor =0;
      programSelector=0;
      digitalWrite(inhibitCoin,LOW);
       for(int i = 0 ; i<4 ; i ++){
    digitalWrite(pinReel[i],LOW);
    delay(15);
  }
      }
    }  
    }
    //St2
    
    if(totalTimeCoinSt2 > 0){
     if(timeContorSt2>interval){      
      if((secundeRamaseSt2 <=0)&&(minuteRamaseSt2 >0)){
    minuteRamaseSt2--;
   secundeRamaseSt2 = 59;
    }
    secundeRamaseSt2--;
    timeContorSt2 =0;
    if((secundeRamaseSt2 < 0)&&(minuteRamaseSt2 <= 0)){
   secundeRamaseSt2 = 0;
    }
    displayTimeHmiSt2(minuteRamaseSt2,secundeRamaseSt2);
      totalTimeCoinSt2--;  
      if(totalTimeCoinSt2 > 30000){
    totalTimeCoinSt2 = 60;
   }
    if(totalTimeCoinSt2 <=0 ){
      displayTimeHmi(0,0);
      totalTimeCoinSt2 = 0;
      timeContorSt2 =0;
      programSelectorSt2=0;
      digitalWrite(inhibitCoin,LOW);
       for(int i = 4 ; i<8 ; i ++){
    digitalWrite(pinReel[i],LOW);
    delay(15);
  }
      }
     }  
    }
    if((totalTimeCoin>0)&&(totalTimeCoinSt2 > 0)){
digitalWrite(inhibitCoin,HIGH);
    }else{
      digitalWrite(inhibitCoin,LOW);
    }
    if((totalTimeCoin<=0)&&(totalTimeCoinSt2 <= 0)){
      keyPinOut = 0;
      keyPinOutSt2 = 0;
      displayCredit(coin);
       switchPage(0);
       digitalWrite(inhibitCoin,LOW);
      isOk = false;
    }
 }
}