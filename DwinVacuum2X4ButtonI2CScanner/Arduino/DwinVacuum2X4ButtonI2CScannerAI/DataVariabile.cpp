#include "DataVariabile.h"

// Array cu configurațiile programelor
const ProgramConfig PROGRAMS[] = {
    {"ASPIRARE     ", timeCoin1, 0},
    {"PARFUM       ", timeCoin2, 3},
    {"NEGRU CAUCIUC", timeCoin3, 2},
    {"AER COMPRIMAT", timeCoin4, 1}
};

// Definirea variabilelor pentru timp și monedă
unsigned long totalTimeCoin = 0;
unsigned long totalTimeCoinSt2 = 0;
int minuteRamase = 0;
int secundeRamase = 0;
int minuteRamaseSt2 = 0;
int secundeRamaseSt2 = 0;
int coin = 0;
int oldCoin = 0;

// Array pentru timpii monedelor
int timeCoins[4] = {0, 0, 0, 0};

// Instanțe SoftwareSerial
SoftwareSerial dwinSerial(RX_PIN, TX_PIN);
bool erase = false;

// Definirea comenzilor HMI
unsigned char pretAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x50, 0x00, 0x00, 0x00};
unsigned char pretMinuteAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x51, 0x00, 0x00, 0x00};
unsigned char pretSecundeAspirat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x52, 0x00, 0x00, 0x00};
unsigned char pretParfum[8] = {0x5A, 0xA5, 0x05, 0x82, 0x53, 0x00, 0x00, 0x00};
unsigned char pretMinuteParfum[8] = {0x5A, 0xA5, 0x05, 0x82, 0x54, 0x00, 0x00, 0x00};
unsigned char pretSecundeParfum[8] = {0x5A, 0xA5, 0x05, 0x82, 0x55, 0x00, 0x00, 0x00};
unsigned char pretNegruCauciuc[8] = {0x5A, 0xA5, 0x05, 0x82, 0x56, 0x00, 0x00, 0x00};
unsigned char pretMinuteNegruCauciuc[8] = {0x5A, 0xA5, 0x05, 0x82, 0x57, 0x00, 0x00, 0x00};
unsigned char pretSecundeNegruCauciuc[8] = {0x5A, 0xA5, 0x05, 0x82, 0x58, 0x00, 0x00, 0x00};
unsigned char pretAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x59, 0x00, 0x00, 0x00};
unsigned char pretMinuteAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x60, 0x00, 0x00, 0x00};
unsigned char pretSecundeAerComprimat[8] = {0x5A, 0xA5, 0x05, 0x82, 0x61, 0x00, 0x00, 0x00};
unsigned char credit[8] = {0x5A, 0xA5, 0x05, 0x82, 0x62, 0x00, 0x00, 0x00};
unsigned char minuteRamaseDisplay[8] = {0x5A, 0xA5, 0x05, 0x82, 0x63, 0x00, 0x00, 0x00};
unsigned char secundeRamaseDisplay[8] = {0x5A, 0xA5, 0x05, 0x82, 0x64, 0x00, 0x00, 0x00};
unsigned char minuteRamaseDisplaySt2[8] = {0x5A, 0xA5, 0x05, 0x82, 0x65, 0x00, 0x00, 0x00};
unsigned char secundeRamaseDisplaySt2[8] = {0x5A, 0xA5, 0x05, 0x82, 0x66, 0x00, 0x00, 0x00};

// Variabile pentru timp
elapsedMillis timeElapsedLed;
elapsedMillis timeCoinElapse;
elapsedMillis timeDisplayElapse;
elapsedMillis timeKeypadElapse;

// Variabile pentru monedă
volatile int coinPin = COIN_PIN;
int limitCoin = COIN_LIMIT;
int timeCoin1 = 0;
int timeCoin2 = 0;
int timeCoin3 = 0;
int timeCoin4 = 0;
int totalCoin = 0;
float newCoin = 0;
float newCoinSt2 = 0;

// rezervare zone de memorie in eeprom
int totalCoins = 100;
int timeCoins1 = 110;
int timeCoins2 = 120;
int timeCoins3 = 140;
int timeCoins4 = 160;

// Variabile pentru LED și tastatură
int ledState = 0;
int ledCount = 0;
int keyPinOut = 0;
int keyPinOutSt2 = 0;
String unitDisplay = "Jeton";
int led[8] = {0, 1, 2, 3, 4, 5, 6, 7};
const long interval = LED_INTERVAL;

// Stare sistem
bool keyChanged = false;
bool switchLed = true;
bool switchDisplay = true;
int programSelector = 0;
int programSelectorSt2 = 0;

// Configurare pini
int meniuButton[3] = {5, 6, 7}; // Meniu,Set, Conta
int keyboardPin[8];
int pinReel[8] = {9, 10, 11, 12, A0, A1, A2, A3};
const byte inhibitCoin = INHIBIT_COIN_PIN;

// Structuri pentru timp și monedă
TimeConfig timeConfig = {0, 0, 0, 0, 0};
StationTime station1 = {0, 0, 0, 0};
StationTime station2 = {0, 0, 0, 0};

// Adrese EEPROM
const int EEPROM_ADDRESSES[5] = {
    EEPROM_START_ADDR,      // totalCoins
    EEPROM_START_ADDR + 10, // timeCoins1
    EEPROM_START_ADDR + 20, // timeCoins2
    EEPROM_START_ADDR + 40, // timeCoins3
    EEPROM_START_ADDR + 60  // timeCoins4
};

// Instanțe PCF8574
PCF8574 pcf8574(PCF8574_KEYBOARD_ADDR, ARDUINO_UNO_INTERRUPTED_PIN, keyChangedOnPCF8574);
PCF8574 ledDriver(PCF8574_LED_ADDR);

// Implementarea funcțiilor
void keyChangedOnPCF8574() {
    keyChanged = true;
}

bool isValidTime(int time) {
    return time > 0 && time < MAX_TIME;
}

void startSetup() {
    Wire.begin();
    //Serial.begin(9600);
    dwinSerial.begin(DGUS_BAUD);
    
    // Inițializare variabile
    keyPinOut = 0;
    keyPinOutSt2 = 0;
    
    // Configurare pin interrupt
    pinMode(ARDUINO_UNO_INTERRUPTED_PIN, INPUT);
    digitalWrite(ARDUINO_UNO_INTERRUPTED_PIN, HIGH);
    attachInterrupt(digitalPinToInterrupt(ARDUINO_UNO_INTERRUPTED_PIN), keyChangedOnPCF8574, FALLING);
    
    // Configurare butoane meniu
    for(int i = 0; i < 3; i++) {
        pinMode(meniuButton[i], INPUT_PULLUP);
        delay(50);
    }
    
    // Configurare pinuri role
    for(int i = 0; i < 8; i++) {
        pinMode(pinReel[i], OUTPUT);
        digitalWrite(pinReel[i], i < 4 ? HIGH : LOW);
        delay(15);
    }
    
    // Configurare pinuri monedă
    pinMode(coinPin, INPUT);
    pinMode(inhibitCoin, OUTPUT);
    digitalWrite(coinPin, HIGH);
    digitalWrite(inhibitCoin, LOW);
    
    // Citire configurare din EEPROM
    timeConfig.timeCoin1 = EEPROM.get(EEPROM_ADDRESSES[1], timeConfig.timeCoin1);
    timeConfig.timeCoin2 = EEPROM.get(EEPROM_ADDRESSES[2], timeConfig.timeCoin2);
    timeConfig.timeCoin3 = EEPROM.get(EEPROM_ADDRESSES[3], timeConfig.timeCoin3);
    timeConfig.timeCoin4 = EEPROM.get(EEPROM_ADDRESSES[4], timeConfig.timeCoin4);
    
    // Validare timp
    if(!isValidTime(timeConfig.timeCoin1)) timeConfig.timeCoin1 = 60;
    if(!isValidTime(timeConfig.timeCoin2)) timeConfig.timeCoin2 = 60;
    if(!isValidTime(timeConfig.timeCoin3)) timeConfig.timeCoin3 = 60;
    if(!isValidTime(timeConfig.timeCoin4)) timeConfig.timeCoin4 = 60;
    
    keyChanged = false;
} 