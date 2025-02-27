void displayProgram(int selectProg){
  switch (selectProg){
    case 1:{
      displayLcd(0,0,"Program : Aspirare ");
      displayLcd(1,1,"  Timp Ramas");
      displayLcd(5,2,String(minuteRamase)+":"+String(secundeRamase)+" mm:ss");
    } break;
    case 2:{
      displayLcd(0,0,"Program : Parfum");
      displayLcd(1,1,"  Timp Ramas");
      displayLcd(5,2,String(minuteRamase)+":"+String(secundeRamase)+" mm:ss");
    } break;
    case 3:{
      displayLcd(0,0,"Program:NegruCauciuc");
      displayLcd(1,1,"  Timp Ramas");
      displayLcd(5,2,String(minuteRamase)+":"+String(secundeRamase)+" mm:ss");
    } break;
    case 4:{
      displayLcd(0,0,"Program:AerComprimat");
      displayLcd(1,1,"  Timp Ramas");
      displayLcd(5,2,String(minuteRamase)+":"+String(secundeRamase)+" mm:ss");
    } break;
  }
}

void displayHmiProgram(int selectProg){

//Serial.print(" SelectProg ");Serial.println(selectProg);
  switch (selectProg){
    case 1:{
      switchPage(1);
      displayTimeVaccum(coin,minuteRamase,secundeRamase);
      if(erase == true){
       printf_dwin(0x2000,"ASPIRARE     ");

      // printf_dwin(0x2100,"RE");
      }
    } break;
    case 2:{
      switchPage(1);
     displayTimeParfum(coin,minuteRamase,secundeRamase);
     if(erase == true){
     printf_dwin(0x2000,"PARFUM       ");
     }
    } break;
    case 3:{
      switchPage(1);
      displayTimeNegruCauciuc(coin,minuteRamase,secundeRamase);
      if(erase == true){
      printf_dwin(0x2000,"NEGRU CAUCIUC");
      //printf_dwin(0x2100,"CAUCIUC");
      }
    } break;
    case 4:{
      switchPage(1);
     displayTimeAir(coin,minuteRamase,secundeRamase);
     if(erase == true){
     printf_dwin(0x2000,"AER COMPRIMAT");
    // printf_dwin(0x2100,"MPRIMAT");
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
    lcd.print(" Credit 0");
    delay(1200);
    return;
  }
   lcd.clear();
   while(isOk == false){
   wdt_reset();
   ledDriverRunVaccum();
    displayLcd(0,0," Credit:");
     displayLcd(8,0,String(coin));
      displayLcd(11,0,"Jet");
     displayLcd(0,1,"Alegeti Program");
     if(keyChanged==true){
    pcf8574Run();
     }
    switch(keyPinOut){
    case 1:{
      lcd.clear();
       startProgram(timeCoin1,programSelector,0);
       isOk = true;   
    }break;
    case 2:{     
      lcd.clear();
       startProgram(timeCoin2,programSelector,3);
       isOk = true;  
    }break;
    case 3:{   
      lcd.clear();
       startProgram(timeCoin3,programSelector,2);
       isOk = true;   
    }break;
    case 4:{   
      lcd.clear();  
       startProgram(timeCoin4,programSelector,1);
       isOk = true;  
    }break;
  }
  displayCredit(coin);
   }
  while(isOk == true){
    wdt_reset();
    ledDriverRunVaccum();
    displayProgram(programSelector);
    displayHmiProgram(programSelector);
     if(keyChanged==true){
   pcf8574Run();
     }
  switch(keyPinOut){
    case 1:{
      lcd.clear();
      Serial.print("keyPinOut1 "); Serial.println(keyPinOut);   
       startProgram(timeCoin1,programSelector,0);
       
    }break;
    case 2:{  
      lcd.clear();   
       Serial.print("keyPinOut2 "); Serial.println(keyPinOut);  
       startProgram(timeCoin2,programSelector,3);
      
    }break;
    case 3:{  
      lcd.clear(); 
      Serial.print("keyPinOut3 "); Serial.println(keyPinOut);
       startProgram(timeCoin3,programSelector,2); 
         
    }break;
    case 4:{ 
      lcd.clear();    
      Serial.print("keyPinOut4 "); Serial.println(keyPinOut); 
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

      totalTimeCoin--;  
      if(totalTimeCoin > 30000){
    totalTimeCoin = 60;
   }
    if(totalTimeCoin <=0 ){
      switchPage(0);
      isOk = false;
      totalTimeCoin = 0;
      timeContor =0;
      programSelector=0;
      digitalWrite(inhibitCoin,LOW);
      lcd.clear();
       for(int i = 0 ; i<4 ; i ++){
    digitalWrite(pinReel[i],LOW);
    delay(15);
  }
      }
    }
 }
}