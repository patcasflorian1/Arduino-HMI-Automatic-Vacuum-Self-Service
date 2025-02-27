#include <avr/wdt.h>
#include "DataVariabile.h"
#include "DwinHmi.h"
#include "SwitchPages.h"
#include "Lcd.h"
#include "Coin.h"
#include "Keyboard.h"
#include "Led.h"
#include "Scanner.h"
#include "SetupMenu.h"
#include "FunctionStation.h"
#include  "StartProgram.h"

void setup() {
  
  startSetup();
  setupLcd();
  displayLcd1(0,0,"WashCleanForRl");
  displayLcd1(0,1,"Sn02B8-02/25 ");
  delay(3000); 
  lcd1.clear();
  attachInterrupt(digitalPinToInterrupt(3), coinInterrupt, LOW);
  pcf8574InitKeyboard();
  ledDriverInit();
  wdt_enable(WDTO_8S);
 Serial.println("Resetează!");
 keyChanged = false;
 switchPage(0);
 Serial.print("keyChanged "); Serial.println(keyChanged);
  displayPriceAspirat(1,timeCoin1/60,timeCoin1%60);
 displayPriceParfum(1,timeCoin2/60,timeCoin2%60);
 displayPriceNegruCauciuc(1,timeCoin3/60,timeCoin3%60);
 displayPriceAerComp(1,timeCoin4/60,timeCoin4%60);
 displayCredit(coin);
 displayLcd1(0,0,"Auto WashClean2B ");
  displayLcd1(0,1,"Sn02 Service ");
}

void loop() {
   wdt_reset();

        if((timeElapsedLed>=interval)&&(ledState == 0)){
    ledState = 1;
      ledDriver.digitalWrite(led[ledCount], HIGH); 
      ledDriver.digitalWrite(led[ledCount+4], HIGH); 
      timeElapsedLed=0;
      //ledCount++;
     }
      if ((timeElapsedLed>= interval)&&(ledState == 1)) {
      ledState = 0;
      ledDriver.digitalWrite(led[ledCount], LOW); 
      ledDriver.digitalWrite(led[ledCount+4], LOW); 
      timeElapsedLed=0;
      ledCount++;
    }
   
   if(ledCount>3){
    ledCount = 0;
  }  
    //activare meniu reglaje
  if (digitalRead(meniuButton[0]) == LOW)
  {
   
    meniuprog();
  }
  
  if(coin > 0){
   // displayCredit(coin);
   switchPage(1);
    eraseText(0x20, 250);
    eraseText(0x21, 250);
    vacuumCleaner();;  
  }
  
}
