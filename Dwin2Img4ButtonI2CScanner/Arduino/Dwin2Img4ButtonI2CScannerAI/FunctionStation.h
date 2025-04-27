// Constante pentru limite și valori
#define MAX_TOTAL_TIME 3000
#define MIN_TOTAL_TIME 10
#define SAFETY_TIME 60
#define MAX_SECONDS 59
#define MIN_SECONDS 0
#define MAX_TIMEOUT 1000 // Timeout maxim pentru operații (ms)
#define MAX_RETRIES 3    // Numărul maxim de încercări pentru operații critice
#define RETRY_DELAY 50   // Timpul între încercări (ms)

// Stări pentru vacuumCleaner
enum VacuumState
{
     IDLE,
     STARTING,
     RUNNING,
     STOPPING,
     ERROR
};

elapsedMillis timeElapsedSt1Reel;
elapsedMillis operationTimeout;
elapsedMillis retryTimer;
elapsedMillis vacuumTimer;
unsigned int intervalSt1Reel = 95;
unsigned int timeDelay = 500;

// Structură pentru a ține evidența stării operațiilor
struct PinOperationState
{
     bool inProgress;
     uint8_t pin;
     uint8_t targetState;
     unsigned long startTime;
     int retryCount;
};

PinOperationState pinState = {false, 0, 0, 0, 0};

// Variabile pentru vacuumCleaner
static VacuumState currentVacuumState = IDLE;
static int currentProgram = 0;
static bool programStarted = false;
static elapsedMillis programTimer;
static bool emergencyStop = false;

// Funcție pentru verificarea stării pinului cu timeout
bool checkPinState(uint8_t pin, uint8_t expectedState, unsigned long timeout)
{
     if (digitalRead(pin) == expectedState)
     {
          return true;
     }
     return false;
}

// Funcție pentru setarea pinului cu retry
bool setPinWithRetry(uint8_t pin, uint8_t state, unsigned long timeout)
{
     // Dacă nu există o operație în curs, inițializăm una nouă
     if (!pinState.inProgress)
     {
          pinState.inProgress = true;
          pinState.pin = pin;
          pinState.targetState = state;
          pinState.startTime = millis();
          pinState.retryCount = 0;
          digitalWrite(pin, state);
          return false;
     }

     // Verificăm dacă operația curentă este pentru pinul și starea dorită
     if (pinState.pin != pin || pinState.targetState != state)
     {
          return false;
     }

     // Verificăm dacă pinul a ajuns la starea dorită
     if (checkPinState(pin, state, timeout))
     {
          pinState.inProgress = false;
          return true;
     }

     // Verificăm timeout-ul
     if (millis() - pinState.startTime >= timeout)
     {
          // Dacă nu am depășit numărul maxim de încercări, încercăm din nou
          if (pinState.retryCount < MAX_RETRIES)
          {
               pinState.retryCount++;
               pinState.startTime = millis();
               digitalWrite(pin, state);
               return false;
          }
          // Dacă am depășit numărul maxim de încercări, resetăm starea
          pinState.inProgress = false;
          return false;
     }

     return false;
}

// Funcție pentru protecția și calculul timpului
void calculateAndProtectTime(float totalTime, int &minutes, int &seconds)
{
     // Protecție pentru totalTimeCoin
     if (isnan(totalTime) || totalTime < 0)
     {
          totalTime = MIN_TOTAL_TIME;
     }

     if (totalTime > MAX_TOTAL_TIME)
     {
          totalTime = SAFETY_TIME;
     }

     if (totalTime <= 0)
     {
          totalTime = MIN_TOTAL_TIME;
     }

     minutes = (int)(totalTime / 60);
     seconds = (int)(totalTime - (minutes * 60));

     // Protecție pentru minuteRamase și secundeRamase
     if (isnan(minutes) || minutes < 0)
     {
          minutes = MIN_SECONDS;
     }
     if (isnan(seconds) || seconds < 0)
     {
          seconds = MIN_SECONDS;
     }
     if (seconds >= 60)
     {
          seconds = MAX_SECONDS;
     }
}

// Set time-price for startProgram
void startProgram(int priceCoin, int selectProgram, int selectReel)
{
     int i = 0;
     while (i < 4)
     {
          if (timeElapsedSt1Reel >= intervalSt1Reel)
          {
               digitalWrite(pinReel[i], LOW);
        i++;
        timeElapsedSt1Reel = 0;
      }
      }
        bool reelState = true;
     while (reelState == true)
     {
          if (timeElapsedSt1Reel >= timeDelay)
          {
               digitalWrite(pinReel[selectReel], HIGH);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
      
     switch (selectProgram)
     {
         case 0:
         {
          totalCoin = EEPROM.get(totalCoins, totalCoin);
          totalCoin = totalCoin + coin;
          EEPROM.put(totalCoins, totalCoin);
          totalTimeCoin = coin * priceCoin;
          if (totalTimeCoin > 3000)
          {
               totalTimeCoin = 60;
                    }
          if (totalTimeCoin <= 0)
          {
               totalTimeCoin = 10;
                    }       
          minuteRamase = totalTimeCoin / 60;
          secundeRamase = totalTimeCoin % 60;
     coin = 0;    
         } 
         break;
          case 1:
         {
          newCoin = ((float)totalTimeCoin / (float)timeCoin1);
          totalTimeCoin = newCoin * priceCoin;
          if (totalTimeCoin > 3000)
          {
               totalTimeCoin = 60;
                    }
          if (totalTimeCoin <= 0)
          {
               totalTimeCoin = 10;
                    }      
          minuteRamase = totalTimeCoin / 60;
          secundeRamase = totalTimeCoin % 60;
         } 
         break;
         case 2:
         {
          newCoin = ((float)totalTimeCoin / (float)timeCoin2);
          totalTimeCoin = newCoin * priceCoin;
          if (totalTimeCoin > 3000)
          {
               totalTimeCoin = 60;
                    }
          if (totalTimeCoin <= 0)
          {
               totalTimeCoin = 10;
                    }      
          minuteRamase = totalTimeCoin / 60;
          secundeRamase = totalTimeCoin % 60;
         } 
         break;
               case 3:
         {
          newCoin = ((float)totalTimeCoin / (float)timeCoin3);
          totalTimeCoin = newCoin * priceCoin;
          if (totalTimeCoin > 3000)
          {
               totalTimeCoin = 60;
                    }
          if (totalTimeCoin <= 0)
          {
               totalTimeCoin = 10;
                    }      
          minuteRamase = totalTimeCoin / 60;
          secundeRamase = totalTimeCoin % 60;
         } 
         break;
          case 4:
         {
          newCoin = ((float)totalTimeCoin / (float)timeCoin4);
          totalTimeCoin = newCoin * priceCoin;
          if (totalTimeCoin > 3000)
          {
               totalTimeCoin = 60;
                    }
          if (totalTimeCoin <= 0)
          {
               totalTimeCoin = 10;
                    }      
          minuteRamase = totalTimeCoin / 60;
          secundeRamase = totalTimeCoin % 60;
         } 
         break;
       }
        programSelector = keyPinOut;
        keyPinOut = 0;
     digitalWrite(inhibitCoin, HIGH);
  }
//__end void startProgram 
