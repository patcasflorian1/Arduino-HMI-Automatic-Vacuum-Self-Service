#ifndef KEYBOARD_H
#define KEYBOARD_H

// Constante
//const int ARDUINO_UNO_INTERRUPTED_PIN = 2;
const int NUM_BUTTONS = 4;

const uint8_t BUTTON_PINS[] = {0, 1, 2, 3};
const unsigned long KEYBOARD_READ_DELAY = 5; // Delay mic pentru citire stabilă
const unsigned long KEYBOARD_DEBOUNCE_TIME = 250; // Timp de debounce pentru butoane
const uint8_t WAIT_LOOPS = 10; // Număr de bucle pentru întârziere

// Variabile

bool buttonStates[NUM_BUTTONS] = {false};
bool lastButtonStates[NUM_BUTTONS] = {false};
bool buttonProcessed[NUM_BUTTONS] = {false};
int keyboardPin[NUM_BUTTONS] = {0};

unsigned long lastKeyboardRead = 0;
elapsedMillis buttonDebounceTimer[NUM_BUTTONS] = {0};


void pcf8574InitKeyboard() {
  pcf8574.begin();
   digitalWrite(ARDUINO_UNO_INTERRUPTED_PIN,HIGH);
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pcf8574.pinMode(BUTTON_PINS[i], INPUT);
    pcf8574.digitalWrite(BUTTON_PINS[i], HIGH);
    buttonDebounceTimer[i] = 0;
  }
  
  if (pcf8574.begin()) {
    Serial.println("OK-Keyboard");
  } else {
    Serial.println("KO-Key");
  }
}


void pcf8574Run(){
  timeKeypadElapse = 0;
// Serial.print("keyChanged "); Serial.println(keyChanged);
if(keyChanged){
    for(int i =0; i<4;i++){
 keyboardPin[i] = pcf8574.digitalRead(i);
 delay(10);
 // Serial.print("keyPinOut "); Serial.print(i);Serial.print(" = ");  Serial.println(keyboardPin[i]);
  }
}
  wdt_reset();
  //Keyboard for st1
  if((keyboardPin[0]==0)&&(programSelector != 1)){ 
     keyPinOut = 1; 
     erase = true;  
    }
     if((keyboardPin[1]==0)&&(programSelector != 2)){  
      keyPinOut = 2;
      erase = true;
    }
    if((keyboardPin[2]==0)&&(programSelector != 3)){ 
      keyPinOut = 3;
      erase = true;   
    }
    if((keyboardPin[3]==0)&&(programSelector != 4)){ 
       keyPinOut = 4;
       erase = true;
    } 
   keyChanged = false; 
   digitalWrite(ARDUINO_UNO_INTERRUPTED_PIN,HIGH);
   //Serial.print("keyPinOut= ");  Serial.println(keyPinOut);
 }


#endif // KEYBOARD_H