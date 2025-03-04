
void displayHmiProgram(int selectProg){
  switch (selectProg){
    case 1:{
      if(erase == true){
       printf_dwin(0x2000,"ASPIRARE     ");
      }
    } break;
    case 2:{
     if(erase == true){
     printf_dwin(0x2000,"PARFUM       ");
     }
    } break;
    case 3:{
      if(erase == true){
      printf_dwin(0x2000,"NEGRU CAUCIUC");   
      }
    } break;
    case 4:{     
     if(erase == true){
     printf_dwin(0x2000,"AER COMPRIMAT");
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
elapsedMillis timeContor; //declare global if you don't want it reset every time loop runs
   unsigned int interval = 1000;
 programSelector = 0;
  if(coin == 0){
    return;
  }
   while(isOk == false){
   wdt_reset();
   ledDriverRunVaccum();
    if(keyChanged==true){
    pcf8574Run();
    
    }

    switch(keyPinOut){
    case 1:{
      switchPage(1);
       startProgram(timeCoin1,programSelector,0);
       isOk = true;   
    }break;
    case 2:{   
      switchPage(1);  
       startProgram(timeCoin2,programSelector,3);
       isOk = true;  
    }break;
    case 3:{ 
      switchPage(1);   
       startProgram(timeCoin3,programSelector,2);
       isOk = true;   
    }break;
    case 4:{   
    switchPage(1);
       startProgram(timeCoin4,programSelector,1);
       isOk = true;  
    }break;
  }
  
  displayCredit(coin);
   }
  while(isOk == true){
    wdt_reset();
    ledDriverRunVaccum();
    displayHmiProgram(programSelector);
     if(keyChanged==true){
   pcf8574Run();
     }
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
      switchPage(0);
      isOk = false;
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
}