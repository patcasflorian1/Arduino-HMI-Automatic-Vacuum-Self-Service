#ifndef VACUUM_H
#define VACUUM_H

#include "HardwareSerial.h"
#include "Arduino.h"



// activare releu vacuumCleaner
void vacuumCleaner(){
elapsedMillis timeDelay; //declare global if you don't want it reset every time loop runs
elapsedMillis timeContor; //declare global if you don't want it reset every time loop runs
elapsedMillis timeContor2; //declare global if you don't want it reset every time loop runs
elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs
// delay in milliseconds between blinks of the LED
   unsigned int interval = 1000;
 programSelector = 0;
 programSelector2 = 0;
 //Extract from memory price of coin
   timeCoin1 =  EEPROM.get(timeCoinsEeprom1,timeCoin1);
   timeCoin2 = EEPROM.get(timeCoinsEeprom2,timeCoin2);
   timeCoin3 = EEPROM.get(timeCoinsEeprom3,timeCoin3);
   timeCoin4 = EEPROM.get(timeCoinsEeprom4,timeCoin4);
   limitCoin = EEPROM.get(coinLimitZone,limitCoin);
   //unsigned long returnArray[4];
//Return if coin = 0
   //lcd.noBlink();
   if(coin == 0){
    return;
       }
     
   eraseText(0x20, 250);
    eraseText(0x21, 250);
    displayTimeHmi(0,0);
    displayTimeHmiSt2(0,0);
       while((isOk1 == false)&&(isOk2==false)){
      wdt_reset();
    displayCredit(coin); 
    ledDriverRunVaccum();
      if(coin>limitCoin){
      digitalWrite(inhibitCoin,LOW);
     }
     else{
      digitalWrite(inhibitCoin,HIGH);
    
     }
       timeDelay = timeDelay +1;
        timeElapsed =timeElapsed+1;
       
         if(keyChanged == true){
          pcf8574Run();       
         }
         
       if((keyPinOut>0)&&(keyPinOut<5)){
          totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
        isOk1=true;
        digitalWrite(inhibitCoin,HIGH);
         programSelector=0;
         timeContor=0;
        displayCredit(coin);
       }
      if((keyPinOut>4)&&(keyPinOut<9)){
          totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
        isOk2=true;
        digitalWrite(inhibitCoin,HIGH);
         programSelector2=0;
         timeContor2=0;
          displayCredit(coin);
       }
       }
       
       while((isOk1==true)||(isOk2==true)||(coin>0)){
         wdt_reset();
            ledDriverRunVaccum();

            if((isOk1 == false)||(isOk2 == false)&&(coin>0)){
                displayCredit(coin);  
                              }

 if((isOk1 == true) || (coin>0)){   
    switch (keyPinOut) {
    case 1 :{
  // Set time-price for 
          keyPinOut = 0;
       aspirator();
          displayCredit(coin); 
              if((totalTimeCoin > 3000)||(totalTimeCoin < 0)||(isnan(totalTimeCoin))){
            totalTimeCoin = 60;
           }  
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;    
              }break;
      case 2 :{
 //Set time-price for Parfum
          keyPinOut = 0;
     parfum();
     displayCredit(coin);
      if((totalTimeCoin > 150)||(totalTimeCoin < 0)||(isnan(totalTimeCoin))){
            totalTimeCoin = 10;
           }
    minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      }  break; 
      case 3 :{
        //Set time-price for Cauciuc  
keyPinOut = 0;
      cauciuc(); 
      displayCredit(coin);
      if((totalTimeCoin > 850)||(totalTimeCoin < 0)||(isnan(totalTimeCoin))){
            totalTimeCoin = 90;
           }
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      }  break;
      case 4 :{
       //Set time-price for AerComprimat
keyPinOut = 0;
     aerComprimat();
     displayCredit(coin);
      if((totalTimeCoin > 4500)||(totalTimeCoin < 0)||(isnan(totalTimeCoin))){
            totalTimeCoin = 90;
           }
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      }  break;
    }
   
     }
      if((isOk2 == true) || (coin>0)){   
    switch (keyPinOut) {
    case 5 :{
  // Set time-price for 
  keyPinOut = 0;
       aspiratorSt2();
       displayCredit(coin);
       if((totalTimeCoin2 > 3000)||(totalTimeCoin2 < 0)||(isnan(totalTimeCoin2))){
            totalTimeCoin2 = 60;
           }  
    minuteRamase2 = totalTimeCoin2/60;
    secundeRamase2 =totalTimeCoin2%60;
              }break;
      case 6 :{
 //Set time-price for Parfum
 keyPinOut = 0;
     parfumSt2();
     displayCredit(coin);
     if((totalTimeCoin2 > 150)||(totalTimeCoin2 < 0)||(isnan(totalTimeCoin2))){
            totalTimeCoin2 = 10;
           }
    minuteRamase2 = totalTimeCoin2/60;
    secundeRamase2 =totalTimeCoin2%60;
      }  break; 
      case 7 :{
        //Set time-price for Cauciuc
       keyPinOut = 0; 
      cauciucSt2(); 
      displayCredit(coin);
       if((totalTimeCoin2 > 850)||(totalTimeCoin2 < 0)||(isnan(totalTimeCoin2))){
            totalTimeCoin2 = 90;
           }
     minuteRamase2 = totalTimeCoin2/60;
    secundeRamase2 =totalTimeCoin2%60;
      }  break;
      case 8 :{
       //Set time-price for AerComprimat
       keyPinOut = 0;
     aerComprimatSt2();
     displayCredit(coin);
        if((totalTimeCoin2 > 4500)||(totalTimeCoin2 < 0)||(isnan(totalTimeCoin2))){
            totalTimeCoin2 = 90;
           }
    minuteRamase2 = totalTimeCoin2/60;
    secundeRamase2 =totalTimeCoin2%60;
      }  break;
    }
    
     }
         if(keyChanged == true){
             pcf8574Run();            
            }
            
   //__End Set time-Price
//Display Time

   switch(programSelector){
     case 1:{
        printf_dwin(0x2000,"ASPIRARE     ");
     }break;
     case 2: {
       printf_dwin(0x2000,"PARFUM       ");
     }break;
     case 3 :{
         printf_dwin(0x2000,"NEGRU CAUCIUC");
     }break;
     case 4 :{
        printf_dwin(0x2000,"AER COMPRIMAT");
     }break;
   }

   //Display Time St2
 
   switch(programSelector2){
     case 1:{
     printf_dwin(0x2100,"ASPIRARE     ");
      
     }break;
     case 2: {
       printf_dwin(0x2100,"PARFUM       ");
       
     }break;
     case 3 :{
        printf_dwin(0x2100,"NEGRU CAUCIUC");
      
     }break;
     case 4 :{
       printf_dwin(0x2100,"AER COMPRIMAT");
     
     }break;
   }

//Timer for St1
if((programSelector>0)&&(isOk1 == true))
{

  if(timeContor>interval){
    if((secundeRamase <=0)&&(minuteRamase>0)){
    minuteRamase--;
   secundeRamase = 59;
    }
    secundeRamase--;
    totalTimeCoin--;
    timeContor =0;
    }
     if(secundeRamase < 0)
     secundeRamase = 0;
   displayTimeHmi(minuteRamase,secundeRamase);
    if(totalTimeCoin<=0){
      totalTimeCoin = 0;
      timeContor =0;
      programSelector=0;
       eraseText(0x20, 250);
     // coin = 0;
      isOk1 = false;
      for(int i=0;i<4;i++){
        
      digitalWrite(pinReel[i],LOW);
      }
      digitalWrite(inhibitCoin,HIGH);
    }
    
}
//end Timer for St1

   //Timer for St2
  if((programSelector2>0)&&(isOk2 == true)){
  
 if(timeContor2>interval){
    if((secundeRamase2 <=0)&&(minuteRamase2>0)){
    minuteRamase2--;
   secundeRamase2 = 59;
    }
    secundeRamase2--;
    totalTimeCoin2--;
    timeContor2 =0;
    }
    if(secundeRamase2 < 0)
     secundeRamase2 = 0;
    displayTimeHmiSt2(minuteRamase2,secundeRamase2);
    if(totalTimeCoin2<=0){
      totalTimeCoin2 = 0;
      programSelector2=0;
      eraseText(0x21, 250);
      isOk2 = false;
      for(int i=0;i<4;i++){
        
      digitalWrite(pinReelSt2[i],LOW);
      }
      digitalWrite(inhibitCoin,HIGH);
    }
   
  }
  //end Timer for St2
if((isOk1 ==true)&&(isOk2 == true)){
  digitalWrite(inhibitCoin, LOW);
}
if((isOk1 ==false)&&(isOk2 == false)){
  digitalWrite(inhibitCoin, HIGH);
  displayCredit(coin);
  switchPage(0);
  eraseText(0x20, 250);
  eraseText(0x21, 250);
}
  } 
}

#endif // VACUUM_H