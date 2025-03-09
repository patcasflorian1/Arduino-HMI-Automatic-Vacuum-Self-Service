#ifndef DATA_VARIABILE_H
#define DATA_VARIABILE_H

#include <Arduino.h>
#include <avr/wdt.h>
#include <Wire.h>
#include <EEPROM.h>
#include <elapsedMillis.h>
#include "PCF8574.h"
#include <SoftwareSerial.h>
#include "HardwareSerial.h"

// Constante pentru configurare
#define DGUS_BAUD 115200
#define COIN_LIMIT 50
#define LED_INTERVAL 400
#define EEPROM_START_ADDR 100
#define DISPLAY_INTERVAL 1000
#define DISPLAY_ADDR_ST1 0x2000
#define DISPLAY_ADDR_ST2 0x2100

// Constante pentru timp
#define MAX_TIME 30000  // 30 minute în secunde
#define MIN_TIME 10     // 10 secunde minim

// Structuri pentru configurare
struct TimeConfig {
    int timeCoin1;
    int timeCoin2;
    int timeCoin3;
    int timeCoin4;
    int totalCoin;
};

struct StationTime {
    long totalTimeCoin;
    int minuteRamase;
    int secundeRamase;
    float newCoin;
};

struct ProgramConfig {
    const char* name;
    int timeCoin;
    int reelPin;
};

// Array cu configurațiile programelor
extern const ProgramConfig PROGRAMS[];

// Configurare pini
const byte RX_PIN = 0;
const byte TX_PIN = 13;
const byte COIN_PIN = 3;
const byte INHIBIT_COIN_PIN = 4;
const byte ARDUINO_UNO_INTERRUPTED_PIN = 2;

// Adrese I2C
const byte PCF8574_KEYBOARD_ADDR = 0x39;
const byte PCF8574_LED_ADDR = 0x38;

// Variabile pentru timp și monedă
extern unsigned long totalTimeCoin  ;
extern unsigned long totalTimeCoinSt2 ;
extern int minuteRamase;
extern int secundeRamase;
extern int minuteRamaseSt2;
extern int secundeRamaseSt2;
extern int coin;
extern int oldCoin;
extern int timeCoins[4];

// Variabile pentru display și HMI
extern SoftwareSerial dwinSerial;
extern bool erase;
extern unsigned char pretAspirat[8];
extern unsigned char pretMinuteAspirat[8];
extern unsigned char pretSecundeAspirat[8];
extern unsigned char pretParfum[8];
extern unsigned char pretMinuteParfum[8];
extern unsigned char pretSecundeParfum[8];
extern unsigned char pretNegruCauciuc[8];
extern unsigned char pretMinuteNegruCauciuc[8];
extern unsigned char pretSecundeNegruCauciuc[8];
extern unsigned char pretAerComprimat[8];
extern unsigned char pretMinuteAerComprimat[8];
extern unsigned char pretSecundeAerComprimat[8];
extern unsigned char credit[8];
extern unsigned char minuteRamaseDisplay[8];
extern unsigned char secundeRamaseDisplay[8];
extern unsigned char minuteRamaseDisplaySt2[8];
extern unsigned char secundeRamaseDisplaySt2[8];

// Variabile pentru timp și control
extern elapsedMillis timeElapsedLed;
extern elapsedMillis timeCoinElapse;
extern elapsedMillis timeDisplayElapse;
extern elapsedMillis timeKeypadElapse;

// Variabile pentru monedă și control
extern volatile int coinPin;
extern int limitCoin;
extern int timeCoin1;
extern int timeCoin2;
extern int timeCoin3;
extern int timeCoin4;
extern int totalCoin;
extern float newCoin;
extern float newCoinSt2;

// Variabile pentru EEPROM
extern int totalCoins;
extern int timeCoins1;
extern int timeCoins2;
extern int timeCoins3;
extern int timeCoins4;

// Variabile pentru LED și tastatură
extern int ledState;
extern int ledCount;
extern int keyPinOut;
extern int keyPinOutSt2;
extern String unitDisplay;
extern int led[8];
extern const long interval;

// Stare sistem
extern bool keyChanged;
extern bool switchLed;
extern bool switchDisplay;
extern int programSelector;
extern int programSelectorSt2;

// Configurare pini și control
extern int meniuButton[3];
extern int keyboardPin[8];
extern int pinReel[8];
extern const byte inhibitCoin;

// Structuri pentru timp și monedă
extern TimeConfig timeConfig;
extern StationTime station1;
extern StationTime station2;

// Adrese EEPROM
extern const int EEPROM_ADDRESSES[5];

// Instanțe PCF8574
extern PCF8574 pcf8574;
extern PCF8574 ledDriver;

// Declarații de funcții
void keyChangedOnPCF8574();
bool isValidTime(int time);
void startSetup();

#endif // DATA_VARIABILE_H