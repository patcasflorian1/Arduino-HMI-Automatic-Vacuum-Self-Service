
#include "DataVariabile.h"
#include "DwinHmi.h"
#include "SwitchPages.h"
#include "Lcd.h"
#include "Coin.h"
#include "FunctionStation.h"
#include "Keyboard.h"
#include "Led.h"
#include "Scanner.h"
#include "SetupMenu.h"
#include  "StartProgram.h"

void setup() {
  setupLcd();
  startSetup();
  displayLcd(2,0,"Auto WashClean ");
  displayLcd(2,1," V 1.00EE ");

  displayLcd1(0,0,"WashCleanForRl");
  displayLcd1(0,1,"Sn02B4-02/25 ");
  delay(3000); 
  lcd.clear();
  lcd1.clear();
  attachInterrupt(digitalPinToInterrupt(3), coinInterrupt, LOW);
  pcf8574InitKeyboard();
  ledDriverInit();
  wdt_enable(WDTO_8S);
 Serial.println("Resetează!");
 switchPage(0);
}

void loop() {
   wdt_reset();
   ledDriverRun();
   displayPriceAspirat(1,timeCoin1/60,timeCoin1%60);
 displayPriceParfum(1,timeCoin2/60,timeCoin2%60);
 displayPriceNegruCauciuc(1,timeCoin3/60,timeCoin3%60);
 displayPriceAerComp(1,timeCoin4/60,timeCoin4%60);
 displayCredit(coin);
    //activare meniu reglaje
  if (digitalRead(meniuButton[0]) == LOW)
  {
   
    meniuprog();
  }
  displayLcd1(0,0,"Auto WashClean2B ");
  displayLcd1(0,1,"Sn02 Service ");


  if((timeDisplayElapse > 1500)&&(switchDisplay == true)){
    lcd.clear();
  displayLcd(2,0,"Introdu Credit");
  displayLcd(2,2,"Credit =  ");
  displayLcd(11,2,String(coin));
  displayLcd(13,2,unitDisplay);
  timeDisplayElapse = 0;
  if(coin == 0){
  switchDisplay = false;
      }
  }  
  if((timeDisplayElapse > 950)&&(switchDisplay == false)){
    lcd.clear();
   displayPrice();
 timeDisplayElapse = 0;
  switchDisplay = true;
  
  }
  if(coin == 0){
   // digitalWrite(ledOutput,HIGH);  
  }
  else{
    vacuumCleaner();
  }
}
