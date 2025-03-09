#include <avr/wdt.h>
#include <Wire.h>
#include<EEPROM.h>
#include <elapsedMillis.h>
#include "PCF8574.h"
#include <SoftwareSerial.h>
#include "HardwareSerial.h"

const byte rxPin = 0; //rx
const byte txPin = 13; // 13 tx
SoftwareSerial dwinSerial(rxPin,txPin);
bool erase = false;
//Hmi Variabile
#define DGUS_BAUD     115200
 unsigned char   pretAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x50 , 0x00, 0x00, 0x00};
unsigned char   pretMinuteAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x51 , 0x00, 0x00, 0x00};
unsigned char    pretSecundeAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x52, 0x00, 0x00, 0x00};

unsigned char   pretParfum[8] = {0x5A, 0xA5, 0x05, 0x82, 0x53 , 0x00, 0x00, 0x00};
unsigned char   pretMinuteParfum[8] = {0x5A, 0xA5, 0x05, 0x82, 0x54 , 0x00, 0x00, 0x00};
unsigned char    pretSecundeParfum[8] = {0x5A, 0xA5, 0x05, 0x82, 0x55, 0x00, 0x00, 0x00};

unsigned char   pretNegruCauciuc[8] = {0x5A, 0xA5, 0x05, 0x82, 0x56 , 0x00, 0x00, 0x00};
unsigned char   pretMinuteNegruCauciuc[8] = {0x5A, 0xA5, 0x05, 0x82, 0x57 , 0x00, 0x00, 0x00};
unsigned char    pretSecundeNegruCauciuc[8] = {0x5A, 0xA5, 0x05, 0x82, 0x58, 0x00, 0x00, 0x00};

 unsigned char   pretAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x59 , 0x00, 0x00, 0x00};
unsigned char   pretMinuteAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x60 , 0x00, 0x00, 0x00};
unsigned char    pretSecundeAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x61, 0x00, 0x00, 0x00};

unsigned char    credit[8] = {0x5A, 0xA5, 0x05, 0x82, 0x62, 0x00, 0x00, 0x00};
//St1 HMI
unsigned char    minuteRamaseDisplay[8] = {0x5A, 0xA5, 0x05, 0x82, 0x63, 0x00, 0x00, 0x00};
unsigned char    secundeRamaseDisplay[8] = {0x5A, 0xA5, 0x05, 0x82, 0x64, 0x00, 0x00, 0x00};

//St2 HMI

unsigned char    minuteRamaseDisplaySt2[8] = {0x5A, 0xA5, 0x05, 0x82, 0x65, 0x00, 0x00, 0x00};
unsigned char    secundeRamaseDisplaySt2[8] = {0x5A, 0xA5, 0x05, 0x82, 0x66, 0x00, 0x00, 0x00};


elapsedMillis timeElapsedLed; //declare global if you don't want it reset every time loop runs
//elapsedMillis timeElapsedLux; //declare global if you don't want it reset every time loop runs
elapsedMillis timeCoinElapse; //declare global if you don't want it reset every time loop runs
elapsedMillis timeDisplayElapse; //declare global if you don't want it reset every time loop runs
elapsedMillis timeKeypadElapse; //declare global if you don't want it reset every time loop runs

volatile int coinPin = 3;
volatile int coin = 0 ;
int oldCoin = 0;
int inhibitCoin = 4; 
int limitCoin = 50;
 int ledState = 0;
 int ledCount=0;
//Keyboard
int keyPinOut = 0 ;
int keyPinOutSt2 = 0 ;
String unitDisplay = "Jeton";
// constants won't change:
int led[8]={0,1,2,3,4,5,6,7};
const long interval = 400;
bool keyChanged = false;
bool switchLed = true;
bool switchDisplay = true;
int programSelector = 0;
int programSelectorSt2 = 0;
int meniuButton[3] = {5,6,7}; // Meniu,Set, Conta
int keyboardPin[8];
int  pinReel[] = {9,10,11,12,A0,A1,A2,A3}; //(asp,aerComp,negruCauciuc,Parf),(asp2,aerComp2,negruCauciuc2,Parf2)
int timeCoin1 = 0,timeCoin2 = 0,timeCoin3 = 0,timeCoin4 = 0,totalCoin=0;
//St1
long totalTimeCoin = 0;
int minuteRamase = 0;
int secundeRamase = 0;
float newCoin = 0;
//St2
long totalTimeCoinSt2 = 0;
int minuteRamaseSt2 = 0;
int secundeRamaseSt2 = 0;
float newCoinSt2 = 0;

// rezervare zone de memorie in eeprom
int totalCoins = 100,timeCoins1 = 110,timeCoins2 = 120,timeCoins3 = 140,timeCoins4 = 160;
//For arduino uno only pin 1 and 2 are interrupted
const int ARDUINO_UNO_INTERRUPTED_PIN = 2;
// Function interrupt
 void keyChangedOnPCF8574(){
 // Interrupt called (No Serial no read no wire in this function, and DEBUG disabled on PCF library)
   keyChanged = true;
}
// Set i2c address
PCF8574 pcf8574(0x39, ARDUINO_UNO_INTERRUPTED_PIN, keyChangedOnPCF8574);
// Set i2c address
PCF8574 ledDriver(0x38); //38 ;21


void startSetup(){
 Wire.begin(); // Wire communication begin 
//Serial.begin(9600);
 dwinSerial.begin(115200);
 keyPinOut = 0;
 keyPinOutSt2 = 0;
  pinMode(ARDUINO_UNO_INTERRUPTED_PIN,INPUT);
  digitalWrite(ARDUINO_UNO_INTERRUPTED_PIN,HIGH);
   attachInterrupt(digitalPinToInterrupt(ARDUINO_UNO_INTERRUPTED_PIN), keyChangedOnPCF8574, FALLING);
  for(int i=0;i<3;i++){
    pinMode(meniuButton[i], INPUT_PULLUP);
    delay(50);
  }
  for(int i = 0 ; i<8 ; i ++){
    pinMode(pinReel[i],OUTPUT);
    if(i<4){
digitalWrite(pinReel[i],HIGH);
    }else{
digitalWrite(pinReel[i],LOW);
    }
    
    delay(35);
  }
  pinMode(coinPin, INPUT);
  pinMode(inhibitCoin, OUTPUT);
  digitalWrite(coinPin,HIGH);
  digitalWrite(inhibitCoin,LOW);
  keyChanged = false;
  timeCoin1 = EEPROM.get(timeCoins1,timeCoin1);
timeCoin2 = EEPROM.get(timeCoins2,timeCoin2);
timeCoin3 = EEPROM.get(timeCoins3,timeCoin3);
timeCoin4 = EEPROM.get(timeCoins4,timeCoin4);
    if((timeCoin1 >= 30000)||(timeCoin1 <= 0)){
    timeCoin1 = 60;
   }
   if((timeCoin2 >= 30000)||(timeCoin2 <= 0)){
    timeCoin2 = 60;
   }
   if((timeCoin3 >= 30000)||(timeCoin3 <= 0)){
    timeCoin3 = 60;
   }
   if((timeCoin4 >= 30000)||(timeCoin4 <= 0)){
    timeCoin4 = 60;
   }
}