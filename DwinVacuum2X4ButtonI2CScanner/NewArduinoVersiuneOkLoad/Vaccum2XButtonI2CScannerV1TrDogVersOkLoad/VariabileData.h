#include <avr/wdt.h>
#include "HardwareSerial.h"
#include <SoftwareSerial.h>
#include "Arduino.h"
#include "PCF8574.h"
#include <OneWire.h>
#include <Wire.h>
#include<EEPROM.h>
#include <elapsedMillis.h>

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


//For arduino uno only pin 1 and 2 are interrupted
#define ARDUINO_UNO_INTERRUPTED_PIN 2

// Function interrupt
void keyChangedOnPCF8574();

// Set i2c address
PCF8574 pcf8574(0x39, ARDUINO_UNO_INTERRUPTED_PIN, keyChangedOnPCF8574); //Keyboard
//PCF8574::DigitalInput di;
bool keyChanged = false;
 
int pin[8];
//PCF8574 pcf8574(0x);0x39 ;20
//Led.h
elapsedMillis timeElapsedLed; //declare global if you don't want it reset every time loop runs
elapsedMillis timeCoinElapse; //declare global if you don't want it reset every time loop runs
int P[8]={0,1,2,3,4,5,6,7};
int ledAdressZone;

// Set i2c address
PCF8574 ledDriver(0x38); //38 ;21 Led
//millis() rollover simulation
extern volatile unsigned long timer0_millis;
// Variables will change:
int ledState = 0;             // ledState used to set the LED
//Keyboard
int keyPinOut = 0 ;
// delay between blinks of the LED
unsigned long KeyInterval = 62500;
//declare these global if you don't want them reset every time loop runs

elapsedMicros DelayKey;
int count = 0 ;
//Coin
// constants won't change:
const long interval = 400;           // interval at which to blink (milliseconds)
//EndLed.h
volatile int coinPin = 18;  //3
int inhibitCoin = 19;  //4
long timeCoinMill = 0;
int limitCoin ;
volatile int coin = 0;
bool insert = false;
//int pasCoin = 0;
int coinPasZone = 310,coinLimitZone = 320;
//End Coin
//Station1
// new statia1
// Variabila total bani incasati
int totalCoin;
//Variabile timp VaccumClean
int minuteRamase = 0;
int secundeRamase = 0;
int programSelector = 0;
unsigned long int totalTimeCoin = 0;
  int meniuButton[3] = {5,6,7}; // Meniu,Set, Conta
int  pinReel[] = {9,10,11,12}; //(asp,Parf,negruCauciuc,aerComp)
 int  pinReelSt2[] = {A0,A3,A2,A1}; //(asp2,aerComp2,negruCauciuc2,ParfSt2)
//variable for price time/Ron
float newCoin = 0;
// rezervare zone de memorie in eeprom
int totalCoins = 10; // zona memorare total bani incasati
 int timeCoin1 = 0,timeCoin2 = 0,timeCoin3 = 0,timeCoin4 = 0;
//.........zona minute/RON.................
//.........zona minute/RON.................
int timeCoinsEeprom1 = 20; 
int timeCoinsEeprom2 = 30;
int timeCoinsEeprom3 = 40;
int timeCoinsEeprom4 = 50;
//boolean active1 = false;
boolean isOk1 =false;
//EndStation1
//Station2
int keyAdressVar ;
//String pressedCharacter="*";
// new statia2
float newCoin2 = 0;
boolean isOk2=false;
//Variabile timp VaccumClean
int minuteRamase2 = 0;
int secundeRamase2 = 0;
int programSelector2 = 0;
unsigned long int totalTimeCoin2 = 0;

//Endstation2
