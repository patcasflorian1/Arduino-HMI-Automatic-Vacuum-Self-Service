
#include "Arduino.h"
#include "HardwareSerial.h"
#include "CommonFunctions.h"
elapsedMillis timeElapsedSt2Reel; //declare global if you don't want it reset every time loop runs
unsigned int intervalSt2Reel = 15;
unsigned int timeDelay2 = 2000;

 //int  pinReel2[] = {8,9,0,1}; //(asp2,aerComp2,negruCauciuc2,Parf2)
// Set i2c address
//PCF8574 pinReelSt2(0x24); //24

void reelDriverInit(){
 //reelDriver.begin();
  // Set pinMode to OUTPUT
 for(int i=0; i<4;i++){
   wdt_reset();
pinMode(pinReelSt2[i], OUTPUT);
digitalWrite(pinReelSt2[i],LOW);
delay(5);
 }
 }
//Set time-price for aspirator
void aspiratorSt2( ){
 
     if(programSelector2!=1){
           for(int i=0;i<4;i++){
        
      bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt2Reel>=intervalSt2Reel){
        digitalWrite(pinReelSt2[i],LOW);
        reelState = false;
        timeElapsedSt2Reel = 0;
      }
      }
      }
         bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt2Reel>=timeDelay2){
       digitalWrite(pinReelSt2[0],HIGH);
        reelState = false;
        timeElapsedSt2Reel = 0;
      }
      }
       switch(programSelector2){

         case 0 :{
            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
            totalTimeCoin2 = coin*timeCoin1;
            totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = (coin*timeCoin1)/60;
     secundeRamase2 = ((coin*timeCoin1)%60);
     programSelector2 = 1;
     coin = 0;
     //digitalWrite(inhibitCoin,LOW);   
     isOk2 = true;
  // pinReelSt2.digitalWrite(0,HIGH);
         }break;
         case 2 :{
            newCoin2 = ((float)totalTimeCoin2/(float)timeCoin2);
       totalTimeCoin2 =  newCoin2* timeCoin1;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2 / 60;
     secundeRamase2 =totalTimeCoin2 % 60;
      programSelector2=1;
     // pinReelSt2.digitalWrite(0,HIGH);
         }break;
      case 3 :{
            newCoin2 = ((float)totalTimeCoin2/(float)timeCoin3);
      totalTimeCoin2 =  newCoin2 * timeCoin1;
      totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2 / 60;
     secundeRamase2 =totalTimeCoin2 % 60;
      programSelector2=1;
     // pinReelSt2.digitalWrite(0,HIGH);
         }break;
        case 4 :{
            newCoin2 = ((float)totalTimeCoin2/(float)timeCoin4);
       totalTimeCoin2 =  newCoin2 * timeCoin1;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2 / 60;
     secundeRamase2 =totalTimeCoin2 % 60;
      programSelector2=1;
     // pinReelSt2.digitalWrite(0,HIGH);
         }break; 
       }
     } 
      
}
//__end void aspirator 
 //Set time-price for Parfum
 void parfumSt2(){
     if(programSelector2!=2){
          for(int i=0;i<4;i++){
     bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt2Reel>=intervalSt2Reel){
       digitalWrite(pinReelSt2[i],LOW);
        reelState = false;
        timeElapsedSt2Reel = 0;
      }
      }
      }
         bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt2Reel>=timeDelay2){
      digitalWrite(pinReelSt2[1],HIGH);
        reelState = false;
        timeElapsedSt2Reel = 0;
      }
      }
       switch(programSelector2){
         case 0 :{
            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
          totalTimeCoin2 = coin*timeCoin2;
          totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = (coin*timeCoin2)/60;
     secundeRamase2 =((coin*timeCoin2)%60);
     coin = 0;
     isOk2 = true;
     programSelector2 = 2;
      // pinReelSt2.digitalWrite(1,HIGH);
         }break;
         case 1 :{
            newCoin = ((float)totalTimeCoin2/(float)timeCoin1);
       totalTimeCoin2 =  newCoin* timeCoin2;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2 / 60;
     secundeRamase2 =totalTimeCoin2 % 60;
      programSelector2 = 2; 
     // pinReelSt2.digitalWrite(1,HIGH);
         }break;
      case 3 :{
            newCoin = ((float)totalTimeCoin2/(float)timeCoin3);
       totalTimeCoin2 =  newCoin* timeCoin2;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2/60;
     secundeRamase2 =totalTimeCoin2%60;
      programSelector2 = 2;
     // pinReelSt2.digitalWrite(1,HIGH);
         }break;
        case 4 :{
            newCoin = ((float)totalTimeCoin2/(float)timeCoin4);
       totalTimeCoin2 =  newCoin* timeCoin2;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2/60;
     secundeRamase2 =totalTimeCoin2%60;
      programSelector2 = 2;
      newCoin = 0;
     // pinReelSt2.digitalWrite(1,HIGH);
         }break; 
       
       }
     }
      
 }
 //__end void parfum  

 //Set time-price for Cauciuc
 void cauciucSt2(){
     if(programSelector2!=3){
          for(int i=0;i<4;i++){
    bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt2Reel>=intervalSt2Reel){
        digitalWrite(pinReelSt2[i],LOW);
        reelState = false;
        timeElapsedSt2Reel = 0;
      }
      }
      }
           bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt2Reel>=timeDelay2){
       digitalWrite(pinReelSt2[2],HIGH);
        reelState = false;
        timeElapsedSt2Reel = 0;
      }
      }
       switch(programSelector2){
         case 0 :{

            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
            totalTimeCoin2 = coin*timeCoin3;
            totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = (coin*timeCoin3)/60;
     secundeRamase2 =((coin*timeCoin3)%60);
     coin = 0;
     isOk2 = true;
     programSelector2=3; 
         }break;
         case 1 :{
            newCoin = ((float)totalTimeCoin2/(float)timeCoin1);
       totalTimeCoin2 =  newCoin* timeCoin3;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2/60;
     secundeRamase2 =totalTimeCoin2%60;
      programSelector2=3;
      newCoin = 0;
      // pinReelSt2.digitalWrite(2,HIGH);
         }break;
      case 2 :{
            newCoin = ((float)totalTimeCoin2/(float)timeCoin2);
       totalTimeCoin2 =  newCoin* timeCoin3;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2/60;
     secundeRamase2 =totalTimeCoin2%60;
      programSelector2=3;
      newCoin = 0;
      // pinReelSt2.digitalWrite(2,HIGH);
         }break;
        case 4 :{
            newCoin = ((float)totalTimeCoin2/(float)timeCoin4);
       totalTimeCoin2 =  newCoin* timeCoin3;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2/60;
     secundeRamase2 =totalTimeCoin2%60;
      programSelector2=3;
      newCoin = 0;
      // pinReelSt2.digitalWrite(2,HIGH);
         }break; 
       }
     }
      
 }
 //__end void cauciuc

//Set time-price for AerComprimat
 void aerComprimatSt2(){
     if(programSelector2!=4){
       for(int i=0;i<4;i++){
     bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt2Reel>=intervalSt2Reel){
       digitalWrite(pinReelSt2[i],LOW);
        reelState = false;
        timeElapsedSt2Reel = 0;
      }
      }
      }

          bool reelState = true;
      while(reelState ==true){
         wdt_reset();
      if(timeElapsedSt2Reel>=timeDelay2){
        digitalWrite(pinReelSt2[3],HIGH);
        reelState = false;
        timeElapsedSt2Reel = 0;
      }
      }
       switch(programSelector2){
         case 0 :{
            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
            totalTimeCoin2 = coin*timeCoin4;
            totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = (coin*timeCoin4)/60;
     secundeRamase2 =((coin*timeCoin4)%60);
     coin = 0;
     isOk2 = true;
     programSelector2=4;   
      //pinReelSt2.digitalWrite(3,HIGH);
         }break;
         case 1 :{
            newCoin = ((float)totalTimeCoin2/(float)timeCoin1);
       totalTimeCoin2 =  newCoin* timeCoin4;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2/60;
     secundeRamase2 =totalTimeCoin2%60;
      programSelector2=4;
     newCoin = 0;
       //pinReelSt2.digitalWrite(3,HIGH);
         }break;
      case 2 :{
            newCoin = ((float)totalTimeCoin2/(float)timeCoin2);
       totalTimeCoin2 = newCoin* timeCoin4;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2/60;
     secundeRamase2 =totalTimeCoin2%60;
      programSelector2=4;
      newCoin = 0;
     // pinReelSt2.digitalWrite(3,HIGH);
         }break;
        case 3 :{
           newCoin = ((float)totalTimeCoin2/(float)timeCoin3);
       totalTimeCoin2 = newCoin* timeCoin4;
       totalTimeCoin2 = validateTimeValue(totalTimeCoin2); // Validare după actualizare
     minuteRamase2 = totalTimeCoin2/60;
     secundeRamase2 =totalTimeCoin2%60;
      programSelector2=4;
     newCoin = 0;
       //pinReelSt2.digitalWrite(3,HIGH);
         }break; 
       }
     }
      
 }
 //__end void aerComprimat
