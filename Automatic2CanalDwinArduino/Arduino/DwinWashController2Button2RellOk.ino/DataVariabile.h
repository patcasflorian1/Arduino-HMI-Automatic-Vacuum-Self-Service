#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <elapsedMillis.h>
#include <LiquidCrystal_PCF8574.h>
#include <avr/wdt.h>
#include <OneWire.h>
const byte rxPin = 0; //rx
const byte txPin = 2; // 1 tx
SoftwareSerial dwinSerial(rxPin,txPin);
//Hmi Variabile
#define DGUS_BAUD     115200
 unsigned char   pretAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x50 , 0x00, 0x00, 0x00};
unsigned char   pretMinuteAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x51 , 0x00, 0x00, 0x00};
unsigned char    pretSecundeAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x52, 0x00, 0x00, 0x00};
 unsigned char   pretAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x53 , 0x00, 0x00, 0x00};
unsigned char   pretMinuteAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x54 , 0x00, 0x00, 0x00};
unsigned char    pretSecundeAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x55, 0x00, 0x00, 0x00};

unsigned char    credit[8] = {0x5A, 0xA5, 0x05, 0x82, 0x56, 0x00, 0x00, 0x00};
unsigned char    minuteRamaseVaccum[8] = {0x5A, 0xA5, 0x05, 0x82, 0x57, 0x00, 0x00, 0x00};
unsigned char    secundeRamaseVaccum[8] = {0x5A, 0xA5, 0x05, 0x82, 0x58, 0x00, 0x00, 0x00};
unsigned char    minuteRamaseAir[8] = {0x5A, 0xA5, 0x05, 0x82, 0x59, 0x00, 0x00, 0x00};
unsigned char    secundeRamaseAir[8] = {0x5A, 0xA5, 0x05, 0x82, 0x60, 0x00, 0x00, 0x00};
elapsedMillis timeElapsedLux; //declare global if you don't want it reset every time loop runs
elapsedMillis timeCoinElapse; //declare global if you don't want it reset every time loop runs
// delay in milliseconds between blinks of the LED
unsigned int intervalLux = 1000;
int  meniu = 1;
//setare in-out Pini
int next = 5;
int inc = 6;
int startProgram =7;
int startProgramAer =8;
volatile int coinPin = 3;
int inhibitCoin = 4;
int outputRell = 9;
int outputRel2 = 10;
int ledOutput = 11;
int ledOutput2 = 12;

int limitCoin = 50;
volatile int coin = 0 ;

int timeCoin = 0,timeCoin2 = 0,totalCoin=0;
// rezervare zone de memorie in eeprom
int totalCoins = 100,timeCoins = 110,timeCoins2 = 120; 
bool lcdOk = true,lcdOk1 = true,luxOk = true,activeVaccum = false,activeAir = false;
void startSetup(){
    Serial.begin(9600); 
  // Wire.begin();
    dwinSerial.begin(115200);
 //eraseText(100);
 //Set pin mode Arduino nano
  pinMode(inc, INPUT);
  pinMode(next, INPUT);
  pinMode(startProgram,INPUT);
  pinMode(startProgramAer,INPUT);
  pinMode(coinPin, INPUT);
  pinMode(inhibitCoin, OUTPUT);
  pinMode(outputRell, OUTPUT);
  pinMode(ledOutput, OUTPUT);
   pinMode(ledOutput2, OUTPUT);
   pinMode(outputRel2, OUTPUT);
  pinMode(ledOutput2, OUTPUT);
  //Set val Pin Arduino nano
 digitalWrite(coinPin,HIGH);
  digitalWrite(inhibitCoin,LOW);
  digitalWrite(ledOutput,HIGH);
  digitalWrite(ledOutput2,LOW);
  digitalWrite(outputRell,HIGH);
  digitalWrite(outputRel2,HIGH);
  digitalWrite(next, HIGH);
  digitalWrite(inc, HIGH);
  digitalWrite(startProgram,HIGH);
  digitalWrite(startProgramAer,HIGH);
 timeCoin = EEPROM.get(timeCoins,timeCoin);
timeCoin2 = EEPROM.get(timeCoins2,timeCoin2);
}