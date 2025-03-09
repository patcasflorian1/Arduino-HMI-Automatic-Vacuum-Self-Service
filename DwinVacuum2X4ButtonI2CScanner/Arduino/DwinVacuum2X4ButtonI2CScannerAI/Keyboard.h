#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Arduino.h>
#include <elapsedMillis.h>

// Constante
//const int ARDUINO_UNO_INTERRUPTED_PIN = 2;
const int NUM_BUTTONS = 8;

const uint8_t BUTTON_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7};
const unsigned long KEYBOARD_READ_DELAY = 2;    // Delay mic pentru citire stabilă
const unsigned long KEYBOARD_DEBOUNCE_TIME = 50; // Timp de debounce pentru butoane
const uint8_t WAIT_LOOPS = 5;                   // Număr de bucle pentru întârziere

// Variabile pentru tracking starea butoanelor
elapsedMillis buttonDebounceTimer[NUM_BUTTONS] = {0};
bool lastButtonState[NUM_BUTTONS] = {HIGH};     // Starea anterioară a butoanelor
bool currentButtonState[NUM_BUTTONS] = {HIGH};  // Starea curentă a butoanelor

void pcf8574InitKeyboard() {
    pinMode(ARDUINO_UNO_INTERRUPTED_PIN, INPUT_PULLUP);
    pcf8574.begin();
    digitalWrite(ARDUINO_UNO_INTERRUPTED_PIN, HIGH);
    
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pcf8574.pinMode(BUTTON_PINS[i], INPUT);
        pcf8574.digitalWrite(BUTTON_PINS[i], HIGH);
        buttonDebounceTimer[i] = 0;
        lastButtonState[i] = HIGH;
        currentButtonState[i] = HIGH;
    }
    
    Serial.print("Init pcf8574...");
    if (pcf8574.begin()) {
        Serial.println("OK-Keyboard");
    } else {
        Serial.println("KO-Key");
    }
}

void processButtons(int startIndex, int endIndex, int& keyPinOut, int& programSelector) {
    unsigned long currentMillis = millis();
    
    for(int i = startIndex; i < endIndex; i++) {
        bool reading = pcf8574.digitalRead(i);
        
        if (reading != lastButtonState[i]) {
            buttonDebounceTimer[i] = 0;
        }
        
        if ((currentMillis - buttonDebounceTimer[i]) > KEYBOARD_DEBOUNCE_TIME) {
            if (reading != currentButtonState[i]) {
                currentButtonState[i] = reading;
                
                if (currentButtonState[i] == LOW && programSelector != (i - startIndex + 1)) {
                    keyPinOut = i - startIndex + 1;
                    erase = true;
                }
            }
        }
        
        lastButtonState[i] = reading;
    }
}

void pcf8574Run() {
    processButtons(0, 4, keyPinOut, programSelector);
    digitalWrite(ARDUINO_UNO_INTERRUPTED_PIN, HIGH);
    keyChanged = false;
    wdt_reset();
}

void pcf8574RunSt2() {
    processButtons(4, 8, keyPinOutSt2, programSelectorSt2);
    digitalWrite(ARDUINO_UNO_INTERRUPTED_PIN, HIGH);
    keyChanged = false;
    wdt_reset();
}

#endif // KEYBOARD_H
