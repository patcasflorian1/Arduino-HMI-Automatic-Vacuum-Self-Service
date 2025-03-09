#ifndef START_PROGRAM_H
#define START_PROGRAM_H

#include <Arduino.h>
#include <EEPROM.h>
#include <elapsedMillis.h>
#include "DataVariabile.h"

// Constante pentru display
#define DISPLAY_INTERVAL 1000
#define DISPLAY_ADDR_ST1 0x2000
#define DISPLAY_ADDR_ST2 0x2100

// Adrese pentru afișarea timpului rămas
#define TIME_ADDR_ST1 0x6500  // Adresa pentru timpul rămas stația 1
#define TIME_ADDR_ST2 0x6600  // Adresa pentru timpul rămas stația 2

// Funcție pentru afișarea programului pe HMI
void displayHmiProgram(int selectProg, bool isStation2 = false) {
    if (erase && selectProg >= 1 && selectProg <= 4) {
        printf_dwin(isStation2 ? DISPLAY_ADDR_ST2 : DISPLAY_ADDR_ST1, PROGRAMS[selectProg - 1].name);
    }
}

// Funcție pentru afișarea timpului rămas pe HMI
void displayRemainingTimeHmi(int minutes, int seconds, bool isStation2 = false) {
    if (isStation2) {
        displayTimeHmiSt2(minutes, seconds);
    } else {
        displayTimeHmi(minutes, seconds);
    }
}

// Funcție pentru verificarea și resetarea programului
void checkAndResetProgram(int& keyPin, unsigned long& totalTime, int& coin) {
    if (totalTime == 0 && coin == 0) {
        keyPin = 0;
    }
}

// Funcție pentru verificarea dacă toate programele sunt terminate
bool allProgramsFinished() {
    return (totalTimeCoin == 0 && totalTimeCoinSt2 == 0 && coin == 0);
}

// Funcție pentru revenirea la pagina 0
void returnToPage0() {
     switchPage(0);  // Comandă pentru revenire la pagina 0
}

// Funcție pentru procesarea unui program
void processProgramSelection(int keyPin, int& programSelector, unsigned long& totalTime, 
                          const ProgramConfig& program, bool isStation2) {
                            
    if (keyPin > 0) {
        displayHmiProgram(keyPin, isStation2);
        if (isStation2) {
            startProgramSt2(program.timeCoin, programSelector, program.reelPin);
        } else {
            startProgram(program.timeCoin, programSelector, program.reelPin);
        }
    }
}

// Funcție pentru actualizarea timpului rămas
void updateRemainingTime(int& minutes, int& seconds) {
    if (seconds <= 0 && minutes > 0) {
        minutes--;
        seconds = 59;
    }
    seconds--;
}

// Funcție principală pentru aspirator
void vacuumCleaner() {
    // Citire configurare din EEPROM
    timeCoin1 = EEPROM.get(timeCoins1, timeCoin1);
    timeCoin2 = EEPROM.get(timeCoins2, timeCoin2);
    timeCoin3 = EEPROM.get(timeCoins3, timeCoin3);
    timeCoin4 = EEPROM.get(timeCoins4, timeCoin4);

    // Inițializare variabile
    elapsedMillis timeContor;
    elapsedMillis timeContorSt2;
    bool isOk = false;
    programSelector = 0;
    programSelectorSt2 = 0;

    // Verificare monedă
    if (coin == 0) {
        return;
    }

    // Resetare display
    eraseText(0x20, 250);
    eraseText(0x21, 250);
    displayTimeHmi(0, 0);
    displayTimeHmiSt2(0, 0);

    // Bucla principală de selecție program
    while (!isOk) {
        wdt_reset();
        
        // Control LED
        if (timeElapsedLed >= DISPLAY_INTERVAL) {
            ledState = !ledState;
            ledDriver.digitalWrite(led[ledCount], ledState ? HIGH : LOW);
            ledDriver.digitalWrite(led[ledCount + 4], ledState ? HIGH : LOW);
            timeElapsedLed = 0;
            
            if (ledState == 0) {
                ledCount = (ledCount + 1) % 4;
            }
        }

        // Actualizare credit
        if (coin > oldCoin) {
            oldCoin = coin;
            displayCredit(coin);
        }

        // Procesare tastatură
        if (keyChanged) {
            pcf8574Run();
            pcf8574RunSt2();
            oldCoin = 0;
            displayCredit(oldCoin);
        }

        // Procesare programe stația 1
        if (keyPinOut >= 1 && keyPinOut <= 4) {
            processProgramSelection(keyPinOut, programSelector, totalTimeCoin, 
                                 PROGRAMS[keyPinOut - 1], false);
            isOk = true;
        }

        // Procesare programe stația 2
        if (keyPinOutSt2 >= 1 && keyPinOutSt2 <= 4) {
            processProgramSelection(keyPinOutSt2, programSelectorSt2, totalTimeCoinSt2,
                                 PROGRAMS[keyPinOutSt2 - 1], true);
            isOk = true;
        }
    }

    // Bucla de execuție program
    while (isOk) {
        wdt_reset();
        ledDriverRunVaccum();

        // Actualizare credit
        if (coin > oldCoin) {
            oldCoin = coin;
            displayCredit(coin);
        }

        // Verificare și resetare programe
        checkAndResetProgram(keyPinOut, totalTimeCoin, coin);
        checkAndResetProgram(keyPinOutSt2, totalTimeCoinSt2, coin);

        // Procesare programe active
        if (totalTimeCoin > 0 || coin > 0) {
            for (int i = 1; i <= 4; i++) {
                if (keyPinOut == i) {
                    processProgramSelection(keyPinOut, programSelector, totalTimeCoin,
                                         PROGRAMS[i - 1], false);
                }
            }
        }

        if (totalTimeCoinSt2 > 0 || coin > 0) {
            for (int i = 1; i <= 4; i++) {
                if (keyPinOutSt2 == i) {
                    processProgramSelection(keyPinOutSt2, programSelectorSt2, totalTimeCoinSt2,
                                         PROGRAMS[i - 1], true);
                }
            }
        }

        // Procesare tastatură
        if (keyChanged) {
            pcf8574Run();
            pcf8574RunSt2();
        }

        // Actualizare timp rămas și afișare pe HMI
        if (totalTimeCoin > 0 && timeContor > DISPLAY_INTERVAL) {
            updateRemainingTime( minuteRamase, secundeRamase);
            displayRemainingTimeHmi(minuteRamase, secundeRamase, false);
            totalTimeCoin --;
            timeContor = 0;
           
            if (secundeRamase < 0 && minuteRamase <= 0) {
                // Program terminat pentru stația 1
                keyPinOut = 0;
                totalTimeCoin = 0;
                displayRemainingTimeHmi(0, 0, false);
            }
        }

        if (totalTimeCoinSt2 > 0 && timeContorSt2 > DISPLAY_INTERVAL) {
            updateRemainingTime(minuteRamaseSt2, secundeRamaseSt2);
            displayRemainingTimeHmi(secundeRamaseSt2, true);
            Serial.print("totalTimeCoinSt2 "); Serial.println(totalTimeCoinSt2);
            timeContorSt2 = 0;
            minuteRamaseSt2 --;
            if (secundeRamaseSt2 < 0 && minuteRamaseSt2 <= 0) {
                // Program terminat pentru stația 2
                keyPinOutSt2 = 0;
                totalTimeCoinSt2 = 0;
                displayRemainingTimeHmi(0, 0, true);
            }
        }

        // Verificare dacă toate programele sunt terminate
        if (allProgramsFinished()) {
            isOk = false;
            returnToPage0();
            break;
        }
    }
}

#endif // START_PROGRAM_H