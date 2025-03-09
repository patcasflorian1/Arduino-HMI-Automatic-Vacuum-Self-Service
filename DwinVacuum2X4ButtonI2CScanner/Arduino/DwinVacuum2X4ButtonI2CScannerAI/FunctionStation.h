#ifndef FUNCTION_STATION_H
#define FUNCTION_STATION_H

#include <Arduino.h>
#include <EEPROM.h>
#include <elapsedMillis.h>
#include "DataVariabile.h"

// Constante pentru timp și limite
const unsigned int REEL_INTERVAL = 95; // Interval pentru rotația rolei
const unsigned int REEL_DELAY = 500;   // Delay pentru oprirea rolei

// Array pentru timpii monedelor
extern int timeCoins[4];

// Variabile pentru timp
elapsedMillis timeElapsedSt1Reel;
unsigned int intervalSt1Reel = REEL_INTERVAL;
unsigned int timeDelay = REEL_DELAY;

// Funcție pentru controlul rolei
void controlReel(int startPin, int endPin, int targetPin, bool targetState) {
    for (int i = startPin; i < endPin; i++) {
        if (timeElapsedSt1Reel >= intervalSt1Reel) {
            digitalWrite(pinReel[i], !targetState);
            timeElapsedSt1Reel = 0;
        }
    }
    
    while (timeElapsedSt1Reel < timeDelay) {
        // Așteptăm delay-ul
    }
    digitalWrite(pinReel[targetPin], targetState);
    timeElapsedSt1Reel = 0;
}

// Funcție pentru calculul timpului rămas
void calculateRemainingTime(unsigned long& totalTime, int& minutes, int& seconds) {
    if (totalTime > MAX_TIME) {
        totalTime = MAX_TIME;
    }
    if (totalTime <= 0) {
        totalTime = MIN_TIME;
    }
    minutes = totalTime / 60;
    seconds = totalTime % 60;
}

// Funcție pentru procesarea programului
void processProgram(int program, unsigned long& totalTimeCoin, int& minutes, int& seconds) {
                     Serial.print("ProgramSelector "); Serial.println(programSelector);
                     Serial.print("program "); Serial.println(program);
                    
                      Serial.print("keyPinOut "); Serial.println(keyPinOut);
                      float newCoin = 0;
                      int priceCoin = 0;
                       switch(keyPinOut) {
            case 1:
                priceCoin =  timeConfig.timeCoin1;
                break;
            case 2:
                priceCoin =  timeConfig.timeCoin2;
                break;
            case 3:
                priceCoin =  timeConfig.timeCoin3;
                break;
            case 4:
                priceCoin = timeConfig.timeCoin4;
                break;
          
        }
        Serial.print("priceCoin "); Serial.println(priceCoin);
    if (program == 0) {
        // Program nou - calculăm timpul bazat pe credit și prețul programului
        timeConfig.totalCoin = EEPROM.get(EEPROM_ADDRESSES[0], timeConfig.totalCoin);
        timeConfig.totalCoin += coin;
        EEPROM.put(EEPROM_ADDRESSES[0], timeConfig.totalCoin);
       
        // Calculăm timpul bazat pe programul selectat și credit
        switch(keyPinOut) {
            case 1:
                totalTimeCoin = coin * timeConfig.timeCoin1;
                break;
            case 2:
                totalTimeCoin = coin * timeConfig.timeCoin2;
                break;
            case 3:
                totalTimeCoin = coin * timeConfig.timeCoin3;
                break;
            case 4:
                totalTimeCoin = coin * timeConfig.timeCoin4;
                break;
           
        }
        
        coin = 0;
        oldCoin = 0;
        displayCredit(coin);
    } else if (program >= 1 && program <= 4) {
        // Program existent - actualizăm timpul rămas
       
        switch(programSelector) {
            case 1:{
             
              Serial.print("totalTimeCoinIni "); Serial.println(totalTimeCoin);
              newCoin = ((float)totalTimeCoin / (float)timeConfig.timeCoin1);
                totalTimeCoin = newCoin * priceCoin;
                 Serial.print("totalTimeCoin "); Serial.println(totalTimeCoin);
                  Serial.print("timeConfig.timeCoin1 "); Serial.println(timeConfig.timeCoin1);
                   Serial.print("newCoin "); Serial.println(newCoin);
            }
                break;
            case 2:
            {
              Serial.print("totalTimeCoinIni "); Serial.println(totalTimeCoin);
              newCoin = ((float)totalTimeCoin / (float)timeConfig.timeCoin2);
                totalTimeCoin = newCoin * priceCoin;
                 Serial.print("totalTimeCoin "); Serial.println(totalTimeCoin);
                  Serial.print("timeConfig.timeCoin2 "); Serial.println(timeConfig.timeCoin2);
                   Serial.print("newCoin "); Serial.println(newCoin);
            }
                break;
            case 3:
            {
              Serial.print("totalTimeCoinIni "); Serial.println(totalTimeCoin);
              newCoin = ((float)totalTimeCoin /(float) timeConfig.timeCoin3);
                totalTimeCoin = newCoin * priceCoin;
                 Serial.print("totalTimeCoin "); Serial.println(totalTimeCoin);
                  Serial.print("timeConfig.timeCoin3 "); Serial.println(timeConfig.timeCoin3);
                   Serial.print("newCoin "); Serial.println(newCoin);
            }
                break;
            case 4:
            {
               Serial.print("totalTimeCoinIni "); Serial.println(totalTimeCoin);
              newCoin = ((float)totalTimeCoin / (float)timeConfig.timeCoin4);
                totalTimeCoin = newCoin * timeConfig.timeCoin4;
                 Serial.print("totalTimeCoin "); Serial.println(totalTimeCoin);
                  Serial.print("timeConfig.timeCoin4 "); Serial.println(timeConfig.timeCoin4);
                   Serial.print("newCoin "); Serial.println(newCoin);
            }
                break;
        }
    }
    calculateRemainingTime(totalTimeCoin, minutes, seconds);
}

// Funcție pentru pornirea programului pentru prima stație
void startProgram(int priceCoin, int selectProgram, int selectReel) {
    if (coin > 0 || totalTimeCoin > 0) {
       
        controlReel(0, 4, selectReel, HIGH);
        processProgram(selectProgram, totalTimeCoin, minuteRamase, secundeRamase);
        programSelector = keyPinOut;
        keyPinOut = 0;
    }
}

// Funcție pentru pornirea programului pentru a doua stație
void startProgramSt2(int priceCoin, int selectProgramSt2, int selectReel) {
    if (coin > 0 || totalTimeCoinSt2 > 0) {
        controlReel(4, 8, selectReel, LOW);
        processProgram(selectProgramSt2, totalTimeCoinSt2, minuteRamaseSt2, secundeRamaseSt2);
        programSelectorSt2 = keyPinOutSt2;
        keyPinOutSt2 = 0;
    }
}

#endif // FUNCTION_STATION_H
 