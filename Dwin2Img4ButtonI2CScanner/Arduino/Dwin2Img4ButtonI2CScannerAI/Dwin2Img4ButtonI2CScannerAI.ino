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
#include <avr/pgmspace.h> // Pentru stocarea șirurilor în memoria program

// Definim șirurile constante în memoria program
const char str1[] PROGMEM = "WashCleanForRl";
const char str2[] PROGMEM = "Sn02B4-01/25 ";
const char str3[] PROGMEM = "Auto WashClean4B ";
const char str4[] PROGMEM = "Sn01 ServiceAI";



void setup() {
  // Dezactivăm întreruperile în timpul configurării
 // noInterrupts();
  setupLcd();
  startSetup();
   // Folosim buffer pentru a copia din PROGMEM
  char buffer[20];
  
  strcpy_P(buffer, str1);
  displayLcd1(0,0,buffer);
  strcpy_P(buffer, str2);
  displayLcd1(0,1,buffer);
  //displayLcd1(0,0,"WashCleanForRl");
 // displayLcd1(0,1,"Sn01B4-02/25 ");
  delay(3000); 
  lcd1.clear();
   // Configurăm întreruperea pentru monedă
  attachInterrupt(digitalPinToInterrupt(3), coinInterrupt, LOW);
  pcf8574InitKeyboard();
  ledDriverInit();
  wdt_enable(WDTO_8S);
 Serial.println("Resetează!");
 switchPage(0);
  // Actualizăm display-ul o singură dată
  displayPriceAspirat(1,timeCoin1/60,timeCoin1%60);
 displayPriceParfum(1,timeCoin2/60,timeCoin2%60);
 displayPriceNegruCauciuc(1,timeCoin3/60,timeCoin3%60);
 displayPriceAerComp(1,timeCoin4/60,timeCoin4%60);
 displayCredit(coin);
  strcpy_P(buffer, str3);
  displayLcd1(0,0,buffer);
  strcpy_P(buffer, str4);
  displayLcd1(0,1,buffer);
   // Reactivăm întreruperile
  //interrupts();
}

void loop() {
 wdt_reset();
  
  // Optimizăm logica LED-urilor folosind un singur if și operatori bit
  static uint8_t ledState = 0;
  if(timeElapsedLed >= interval) {
    timeElapsedLed = 0;
    ledState ^= 1; // Toggle stare folosind XOR
    
    // Setăm ambele LED-uri într-o singură operație
    ledDriver.digitalWrite(led[ledCount], ledState);
    ledDriver.digitalWrite(led[ledCount+4], ledState);
    
    if(!ledState) {
      if(++ledCount > 3) ledCount = 0;
    }
  }
  
  // ledDriverRun();
    //activare meniu reglaje
  if (digitalRead(meniuButton[0]) == LOW)
  {
   
    meniuprog();
  }
  
  if(coin > 0){
  displayCredit(coin);
   //switchPage(1);
   // eraseText(0x20, 250);
    vacuumCleaner();;  
  }
}
