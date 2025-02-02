#include <DHT.h>
#include "DataVariabile.h"
#include "DwinHmi.h"
#include "SwitchPages.h"
#include "Coin.h"
#include "LcdSet.h"
#include "Meniu.h"
#include "Vaccum.h"
#include "Led.h"



void setup() {
   startSetup();
   lcdBegin();
  attachInterrupt(digitalPinToInterrupt(3), coinInterrupt, LOW);
  wdt_enable(WDTO_8S);
 Serial.println("Resetează!");
}

void loop() {
  wdt_reset();
  switchPage(0);
lcd1Display(0,0,"Auto WashClean2B ");
lcd1Display(0,1,"Sn02 Service ");
  //activare meniu reglaje
  if (digitalRead(inc) == LOW)
  {
   
    meniuprog();
  }
//afisare contabilitate rapid
  if(digitalRead(next)==LOW){
    totalCoin =  EEPROM.get(totalCoins,totalCoin);
      lcd1.clear();
 lcd1Display(0,0," Total incasare :");     
  lcd1.setCursor(3,1);
  lcd1.print(totalCoin);
  lcd1.print(" RON");
  delay(1200);
  lcd1.clear();
  }

//afisare credit/pret
  if(coin>0){  
    lcd.clear();
   vacuumCleaner();
  }
    displayPrice();
 displayPriceAspirat(1,timeCoin/60,timeCoin%60);
 displayPriceAerComp(1,timeCoin2/60,timeCoin2%60);
led();
}
