#include "Arduino.h"
#include "HardwareSerial.h"
#include "CommonFunctions.h"
elapsedMillis timeElapsedSt1Reel; //declare global if you don't want it reset every time loop runs
unsigned int intervalSt1Reel = 15;
unsigned int timeDelay = 2000;




//Set time-price for aspirator
void aspirator(){
     if(programSelector!=1){
           for(int i=0;i<4;i++){ 
      bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt1Reel>=intervalSt1Reel){
        digitalWrite(pinReel[i],LOW);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
      }
        bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt1Reel>=timeDelay){
        digitalWrite(pinReel[0],HIGH);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
       switch(programSelector){
         case 0 :{
            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
         isOk1=true;
            totalTimeCoin = coin*timeCoin1;
           totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = (coin*timeCoin1)/60;
     secundeRamase =((coin*timeCoin1)%60);
     coin = 0;    
     programSelector=1;
 
          // digitalWrite(pinReel[0],HIGH);
         }break;
         case 2 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin2);
       totalTimeCoin =  newCoin* timeCoin1;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=1;
      
   //  digitalWrite(pinReel[0],HIGH);
         }break;
      case 3 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin3);
       totalTimeCoin =  newCoin* timeCoin1;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=1;
      
     // digitalWrite(pinReel[0],HIGH);
         }break;
        case 4 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin4);
       totalTimeCoin =  newCoin* timeCoin1;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=1;
      
    //  digitalWrite(pinReel[0],HIGH);
         }break; 
       }
     } 

}
//__end void aspirator 
 //Set time-price for Parfum
 void parfum(){
 
     if(programSelector!=2){
          for(int i=0;i<4;i++){
       bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt1Reel>=intervalSt1Reel){
        digitalWrite(pinReel[i],LOW);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
      }
         bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt1Reel>=timeDelay){
        digitalWrite(pinReel[1],HIGH);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
       switch(programSelector){
         case 0 :{
            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
         isOk1=true;
            totalTimeCoin = coin*timeCoin2;
             totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = (coin*timeCoin2)/60;
     secundeRamase =((coin*timeCoin2)%60);
     coin = 0;
     programSelector=2;
     
           
     // digitalWrite(pinReel[1],HIGH);
         }break;
         case 1 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin1);
       totalTimeCoin =  newCoin* timeCoin2;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=2;
      
     // digitalWrite(pinReel[1],HIGH);
         }break;
      case 3 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin3);
       totalTimeCoin =  newCoin* timeCoin2;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=2;
      
            
     // digitalWrite(pinReel[1],HIGH);
         }break;
        case 4 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin4);
       totalTimeCoin =  newCoin* timeCoin2;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=2;
      
      newCoin = 0;
      //digitalWrite(pinReel[1],HIGH);
         }break; 
       
       }
     }
 }
 //__end void parfum  

 //Set time-price for Cauciuc
 void cauciuc(){
     
     if(programSelector!=3){
          for(int i=0;i<4;i++){
       bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt1Reel>=intervalSt1Reel){
        digitalWrite(pinReel[i],LOW);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
      }
         bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt1Reel>=timeDelay){
        digitalWrite(pinReel[2],HIGH);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
       switch(programSelector){
         case 0 :{
            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
         isOk1=true;
            totalTimeCoin = coin*timeCoin3;
             totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = (coin*timeCoin3)/60;
     secundeRamase =((coin*timeCoin3)%60);
     coin = 0;     
     programSelector=3;
     
           
         }break;
         case 1 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin1);
       totalTimeCoin =  newCoin* timeCoin3;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=3;
      
       
      newCoin = 0;
     // digitalWrite(pinReel[2],HIGH);
         }break;
      case 2 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin2);
       totalTimeCoin =  newCoin* timeCoin3;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=3;
      
       
      newCoin = 0;
     // digitalWrite(pinReel[2],HIGH);
         }break;
        case 4 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin4);
       totalTimeCoin =  newCoin* timeCoin3;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=3;
      
       
      newCoin = 0;
     // digitalWrite(pinReel[2],HIGH);
         }break; 
       }
     }
 }
 //__end void cauciuc

//Set time-price for AerComprimat
 void aerComprimat(){
         
     if(programSelector!=4){
       for(int i=0;i<4;i++){       
      bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt1Reel>=intervalSt1Reel){
        digitalWrite(pinReel[i],LOW);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
      }
          bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt1Reel>=timeDelay){
        digitalWrite(pinReel[3],HIGH);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
       switch(programSelector){
         case 0 :{
            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
         isOk1=true;
            totalTimeCoin = coin*timeCoin4;
             totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = (coin*timeCoin4)/60;
     secundeRamase =((coin*timeCoin4)%60);
     coin = 0;  
  digitalWrite(inhibitCoin,LOW);
     programSelector=4;
     
    //  digitalWrite(pinReel[3],HIGH);
         }break;
         case 1 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin1);
       totalTimeCoin =  newCoin* timeCoin4;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=4;
      
       
     newCoin = 0;
     // digitalWrite(pinReel[3],HIGH);
         }break;
      case 2 :{
            newCoin = ((float)totalTimeCoin/(float)timeCoin2);
       totalTimeCoin = newCoin* timeCoin4;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=4;
      
       
      newCoin = 0;
    // digitalWrite(pinReel[3],HIGH);
         }break;
        case 3 :{
           newCoin = ((float)totalTimeCoin/(float)timeCoin3);
       totalTimeCoin = newCoin* timeCoin4;
        totalTimeCoin = validateTimeValue(totalTimeCoin); // Validare după actualizare
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=4;
      
       
     newCoin = 0;
     // digitalWrite(pinReel[3],HIGH);
         }break; 
       }
     }
 }
 //__end void aerComprimat
