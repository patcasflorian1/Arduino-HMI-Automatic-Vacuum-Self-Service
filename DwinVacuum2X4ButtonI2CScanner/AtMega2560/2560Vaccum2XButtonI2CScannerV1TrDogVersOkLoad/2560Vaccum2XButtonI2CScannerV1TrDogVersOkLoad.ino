#include <avr/wdt.h>
#include "VariabileData.h"
#include "DwinHmi.h"
#include "Display.h"
#include "Service.h"
#include "Coin.h"
#include "Keyboard.h"
#include "Led.h"
#include "Scanner.h"
#include "Contabilitate.h"
#include "SetTimeCoin.h"
#include "Meniu.h"
#include "FunctionSt1.h"
#include "FunctionSt2.h"
#include "Vacuum.h"

void setup() {
 //Serial.begin(9600); 
dwinSerial.begin(DGUS_BAUD);
  Wire.begin();
 // Wire.setClock(400000L);
  reelDriverInit();
   buttonInit();
  pinMode(coinPin, INPUT);
  pinMode(inhibitCoin, OUTPUT);
  //Set val Pin Arduino nano
  digitalWrite(coinPin,HIGH);
  digitalWrite(inhibitCoin,LOW);
  pcf8574InitKeyboard();
 ledDriverInit();
  attachInterrupt(digitalPinToInterrupt(coinPin), coinInterrupt, LOW); //SetCoinPin
//set LCD instance
 switchPage(0);
   lcd1.begin(16, 2);
  lcd1.setBacklight(HIGH); 
  lcd1.setCursor(0, 0);
  lcd1.print("2KbSerialWithScannerV1");
  delay(2000); 
  lcd1.clear();

 displayCredit(coin);
     for(int i=0;i<4;i++){
    pinMode(pinReel[i],OUTPUT);
    digitalWrite(pinReel[i],LOW);
 
  }
  pinMode(ARDUINO_UNO_INTERRUPTED_PIN,INPUT);
  digitalWrite(ARDUINO_UNO_INTERRUPTED_PIN,HIGH);
   attachInterrupt(digitalPinToInterrupt(ARDUINO_UNO_INTERRUPTED_PIN), keyChangedOnPCF8574, FALLING);
    
 Serial.println("Resetează!");
 //Extract from memory price of coin
   timeCoin1 =  EEPROM.get(timeCoinsEeprom1,timeCoin1);
   timeCoin2 = EEPROM.get(timeCoinsEeprom2,timeCoin2);
   timeCoin3 = EEPROM.get(timeCoinsEeprom3,timeCoin3);
   timeCoin4 = EEPROM.get(timeCoinsEeprom4,timeCoin4);
    displayPriceAspirat(1,timeCoin1/60,timeCoin1%60);
 displayPriceParfum(1,timeCoin2/60,timeCoin2%60);
 displayPriceNegruCauciuc(1,timeCoin3/60,timeCoin3%60);
 displayPriceAerComp(1,timeCoin4/60,timeCoin4%60);
 
   //Afisare lcd Secundar
lcd1.setCursor(0, 0);
  lcd1.print("Vacuum4X2Fun.HMI");
  lcd1.setCursor(0, 1);
  lcd1.print("SN02.04.25SetMen");
 digitalWrite(inhibitCoin,HIGH);
 wdt_enable(WDTO_4S);
}

void loop() {
 wdt_reset();

  ledDriverRun();
//Serial.print("Coin ");Serial.println(coin);
if(coin>0){
  //Serial.print("Coin ");Serial.println(coin);
  //start program ReelComand
  switchPage(1);
vacuumCleaner();
lcd1.setCursor(0, 0);
  lcd1.print("Vacuum4X2Fun.HMI");
  lcd1.setCursor(0, 1);
  lcd1.print("SN02.04.25SetMen");
}

  //activare meniu reglaje
  if (digitalRead(meniuButton[0]) ==LOW)
  {

  meniuprog();
  lcd1.setCursor(0, 0);
  lcd1.print("Vacuum4X2Fun.HMI");
  lcd1.setCursor(0, 1);
  lcd1.print("SN02.04.25SetMen");
  }
  if(digitalRead(meniuButton[2]) ==LOW){
     
     
      setConta(totalCoin,totalCoins,inhibitCoin);
      lcd1.setCursor(0, 0);
  lcd1.print("Vacuum4X2Fun.HMI");
  lcd1.setCursor(0, 1);
  lcd1.print("SN02.04.25SetMen");
  }


  
  // Afisare Lista Preturi


   
}



