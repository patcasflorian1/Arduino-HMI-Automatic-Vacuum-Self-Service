#include <OneWire.h>

/* ----- C Program for Arduino based Alarm Clock ---- */
#include <avr/wdt.h>
#include <Wire.h>
#include<EEPROM.h>
#include <elapsedMillis.h>
#include <LiquidCrystal_PCF8574.h>
#include <SoftwareSerial.h>
const byte rxPin = 0; //rx
const byte txPin = 1; //tx
SoftwareSerial dwinSerial(rxPin, txPin);
LiquidCrystal_PCF8574 lcd(0x26);  // set the LCD address to 0x27 ori 0x3F for a 20 chars and 4 line display
LiquidCrystal_PCF8574 lcd1(0x27);  // set the LCD address to 0x27 ori 0x3F for a 16 chars and 2 line display

elapsedMillis timeElapsedLux; //declare global if you don't want it reset every time loop runs
elapsedMillis timeElapsedCoin; //declare global if you don't want it reset every time loop runs
// delay in milliseconds between blinks of the LED

#define price_address   0x50
#define min_address     0x51
#define sec_address   0x52
#define jeton_address   0x53
#define minute_address   0x54
#define secunde_address   0x55
#define text_address   0x20
unsigned int intervalLux = 50000;
char textString[10] ="ASPIRARE  ";
int vpAddresss = 20;
 int textLengths = 100;
 unsigned char   pret[8] = {0x5A, 0xA5, 0x05, 0x82, price_address , 0x00, 0x00, 0x00};
unsigned char   pretMinute[8] = {0x5A, 0xA5, 0x05, 0x82, min_address , 0x00, 0x00, 0x00};
unsigned char    pretSecunde[8] = {0x5A, 0xA5, 0x05, 0x82, sec_address, 0x00, 0x00, 0x00};
unsigned char    credit[8] = {0x5A, 0xA5, 0x05, 0x82, jeton_address, 0x00, 0x00, 0x00};
unsigned char    minuteRamase[8] = {0x5A, 0xA5, 0x05, 0x82, minute_address, 0x00, 0x00, 0x00};
unsigned char    secundeRamase[8] = {0x5A, 0xA5, 0x05, 0x82, secunde_address, 0x00, 0x00, 0x00};
unsigned char    eraseTexts[10] = {0x5A, 0xA5, 0x07, 0x82, text_address, 0x00, 0x20,0x20, 0xff, 0xff};

int  meniu = 1;
//setare in-out Pini
int next = 5;
int inc = 6;
int secretPin = 8;
int startProgram =7;
volatile int coinPin = 3;
int inhibitCoin = 9;
int outputRell = 10;
int ledOutput = 11;
//............................
//set variabile globale
//int timeMillsec = millis();
long timeCoinMill = 0;
int limitCoin = 50;
int timeCoin = 0,totalCoin = 0 ;
 int16_t masterCoin = 0;
int minuteRamas1=0;
 int secundar1 =0;
volatile int coin = 0 ;
//unsigned int minuteRamas;
volatile boolean insert = false;
// rezervare zone de memorie in eeprom
int totalCoins = 100,timeCoins = 110;
int16_t  masterCoins = 120;
// ...................................
bool lcdOk = true,lcdOk1=true;
int lux = 250;
boolean luxOk = true;
char textWelcome[9] ="AutoClean";

void setup() {
 Serial.begin(9600); 
   dwinSerial.begin(115200);
 eraseText(100);
 //Set pin mode Arduino nano
  pinMode(inc, INPUT);
  pinMode(next, INPUT);
  pinMode(startProgram,INPUT);
  pinMode(coinPin, INPUT);
  pinMode(secretPin, INPUT);
  pinMode(inhibitCoin, OUTPUT);
  pinMode(outputRell, OUTPUT);
  pinMode(ledOutput, OUTPUT);
  //Set val Pin Arduino nano
 digitalWrite(coinPin,HIGH);
 digitalWrite(secretPin,HIGH);
  digitalWrite(inhibitCoin,LOW);
  analogWrite(ledOutput,lux);
  digitalWrite(outputRell,HIGH);
  digitalWrite(next, HIGH);
  digitalWrite(inc, HIGH);
  digitalWrite(startProgram,HIGH);
   attachInterrupt(digitalPinToInterrupt(3), coinInterrupt, LOW);
 
//set LCD instance
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH); 
  lcd.setCursor(0, 0);
  lcd.print("Auto WashClean ");
  lcd.setCursor(0, 1);
  lcd.print(" V 2.00EE ");
  sendText(textWelcome); 
  lcd1.begin(16, 2);
  lcd1.setBacklight(HIGH); 
  lcd1.setCursor(0, 0);
  lcd1.print("Auto WashClean ");
  lcd1.setCursor(0, 1);
  lcd1.print("Sn01-11/24 ForTr "); //(SerialNr - Luna/an Tip)
  delay(3000); 
  lcd.clear();
  lcd1.clear();
  eraseText(100);
  delay(25);
  wdt_enable(WDTO_8S);
 Serial.println("Resetează!");
  timeCoin = EEPROM.get(timeCoins,timeCoin);

}

void loop() {
 
  timeCoin = EEPROM.get(timeCoins,timeCoin);
 
    wdt_reset();
  //activare meniu reglaje
  if (digitalRead(inc) == LOW)
  {
   
    meniuprog();
  }
 lcd1.setCursor(0, 0);
lcd1.print("Auto WashClean ");
  lcd1.setCursor(0, 1);
  lcd1.print("Sn01.11.24 Serv. ");
  //afisare contabilitate Master
  if(digitalRead(secretPin)==LOW){
      lcd1.clear();
 lcd1.print (" Master incasare :");
  lcd1.setCursor(3,1);
 masterCoin =  EEPROM.get(masterCoins,masterCoin);
 
  lcd1.print( masterCoin);
  lcd1.print("RON");
  delay(1200);
  lcd1.clear();
  }
  //afisare contabilitate rapid
  if(digitalRead(next)==LOW){
      lcd1.clear();
 lcd1.print (" Total incasare :");
  lcd1.setCursor(3,1);
 totalCoin =  EEPROM.get(totalCoins,totalCoin);
 
  lcd1.print(totalCoin);
  lcd1.print(" RON");
  delay(1200);
  lcd1.clear();
  }
  
  
     //afisare credit/pret
  if(coin>0){
    if(lcdOk==true){
      lcdOk=false;
      lcd.clear();
      eraseText(100);
    }
     minuteRamas1=(coin*timeCoin)/60;
     secundar1 =((coin*timeCoin)%60);
      delay(25);
    lcd.setCursor(0,0);
  lcd.print("Credit = ");   
  lcd.print(coin);
  lcd.print(" Ron");
  lcd.setCursor(0,1);
  lcd.print("Timp:");
  lcd.setCursor(5,1);
  lcd.print(minuteRamas1);
   lcd.setCursor(7,1);
   lcd.print("M+");
   lcd.setCursor(9,1);
   lcd.print(secundar1);
    lcd.setCursor(11,1);
    lcd.print(" Sec");
    displayTime(coin,minuteRamas1,secundar1);
  }
  else{
     delay(25);
      if(lcdOk1==true){
      lcdOk1=false;
      lcd.clear();
      eraseText(100);
    }
    lcd.setCursor(0,0);
  lcd.print(" Pret Impuls");   
  lcd.setCursor(0,1);
  lcd.print("1Ron=");
   lcd.setCursor(5,1);
  lcd.print(timeCoin/60);
   lcd.setCursor(7,1);
   lcd.print("Min+");
    lcd.setCursor(11,1);
   lcd.print(timeCoin%60);
    lcd.setCursor(13,1);
    lcd.print("Sec");
    displayPrice(1,timeCoin/60,timeCoin%60);
  }
      //activare program releu aspirator
  if(digitalRead(startProgram)==LOW){
    lcd.clear();
    vacuumCleaner();
    
  }
  if(coin>0){
    if((timeElapsedCoin>=500)&&(luxOk==true)){
      luxOk=false;
    analogWrite(ledOutput,255); 
    timeElapsedCoin=0;
    }
   if((timeElapsedCoin>=500)&&(luxOk==false)){
      luxOk=true;
    analogWrite(ledOutput,0);
     timeElapsedCoin=0;
    }

  }
   if(timeElapsedCoin>=5000){
    timeElapsedCoin=0;
   }
   if((timeElapsedLux<=intervalLux)&&(coin ==0)){
   
       if(luxOk==true){
      lux=lux-5;
     analogWrite(ledOutput,lux);
    }

    if(luxOk==false){
      lux=lux+5;
      analogWrite(ledOutput,lux);
    }
       if(lux<=0){
        luxOk = false;
       // timeElapsedLux=0;
       delay(300);
       }
      if(lux>=255){
        luxOk=true;
        //timeElapsedLux=0;
        delay(300);
      }
    
   }
    if(timeElapsedLux>intervalLux){
      timeElapsedLux=0;
    }
 //Serial.println("TimeElapse");
 // Serial.println(timeElapsedCoin);
 // Serial.println("luxOk");
 // Serial.println(luxOk);
//analogWrite(ledOutput,lux);
//
}

//interrupt
void coinInterrupt() {

while(digitalRead(coinPin) == LOW){
    timeCoinMill++;
    wdt_reset();
}
  if(timeCoinMill>0){ 
 
     coin ++ ;
    lcdOk=true;
     if(coin>limitCoin){
      digitalWrite(inhibitCoin,HIGH);
     }
     else{
      digitalWrite(inhibitCoin,LOW);
     }
 
  insert = true;
  
 
 }
 // lcd.clear();
}

//Meniu Program
void meniuprog()
{
  delay(600);
  meniu = 5;
  lcd1.clear();
  while (meniu == 5) {
    wdt_reset();
    meniu = 1;
           delay(400);      
         lcd1.setCursor(0, 0);  
          lcd1.print(" * SetProg/Timp  "  );
          
          lcd1.setCursor(1, 1); 
          lcd1.print(" AfisConta");
          delay(400);  
          lcd1.setCursor(1,0);
          lcd1.blink();
 do{
        wdt_reset();
        if (digitalRead(next) == LOW) { 
          delay(200);
          lcd1.clear();
          lcd1.noBlink();
          coin_time();
           meniu = 2;
        } 
        if (digitalRead(inc) == LOW) 
          {
            delay(200);
          meniu = 2;
          lcd1.clear();
          }
      }while(meniu==1);
       

 delay(400);
    
      lcd1.print( " * AfisConta ");
      lcd1.setCursor(1, 1);
      lcd1.print("  Exit");
      lcd1.setCursor(1,0); 
      lcd1.blink();
                                                                         
      
      do
      {
        wdt_reset();
        if (digitalRead(next) == LOW) { 
          delay(200);
          lcd1.noBlink();
            displayConta();
          meniu = 3;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(inc) == LOW) {
          delay(200);
          meniu = 3;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 2);
    
     
      lcd1.print( " * EXIT");
      lcd1.setCursor(0, 1);
      lcd1.print("   MENIU ");
      lcd1.setCursor(1,0);
      lcd1.blink();
    
      do
    {
      wdt_reset();

          if (digitalRead(next) == LOW)
        {
          lcd1.noBlink();
          meniu = 1;
          delay(200);
          lcd1.clear();
          lcd.clear();
        }
        if (digitalRead(inc) == LOW) {
        delay(300);
          meniu = 5;
          lcd1.clear();
     
      }
    } while (meniu == 3);
   
  } 
 delay(200);
  
}
// activare releu vacuumCleaner
void vacuumCleaner(){
        wdt_reset();
        // dwinSerial.write(eraseTexts,10);
         eraseText(100);
         delay(10);
  elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs
// delay in milliseconds between blinks of the LED
unsigned int interval = 1000;
  lcd.noBlink();
  if(coin == 0){
    lcd.print(" Credit 0");
    delay(1200);
    lcd.clear();
    displayTime(0,0,0);
    return;
  }
   digitalWrite(outputRell,HIGH);
   digitalWrite(inhibitCoin,HIGH);
   totalCoin =  EEPROM.get(totalCoins,totalCoin);
  totalCoin = totalCoin+coin;
  EEPROM.put(totalCoins,totalCoin);
    digitalWrite(inhibitCoin,HIGH);     
    masterCoin =  EEPROM.get(masterCoins,masterCoin);
 masterCoin = masterCoin+coin;
  EEPROM.put(masterCoins,masterCoin);
    digitalWrite(inhibitCoin,HIGH);     
  timeCoin = EEPROM.get(timeCoins,timeCoin);
   boolean isOk =true;
  int minuteRamase = (coin*timeCoin)/60;
  int secundeRamase =((coin*timeCoin)%60);
 long totalTimeCoin = coin*timeCoin;
  coin=0;
  totalTimeCoin--;
  if((minuteRamase>0)&&(secundeRamase==0)){
    minuteRamase--;
    secundeRamase=59;
  }
  digitalWrite(inhibitCoin,HIGH);
     digitalWrite(outputRell,LOW);
     digitalWrite(ledOutput,LOW);
   do{
    wdt_reset();
    sendText(textString);
  lcd.setCursor(0,0);
  lcd.print("TimpRamas : ");
  lcd.setCursor(0,1);
   lcd.print("Min :");
   if((minuteRamase-1)>=10){
     lcd.print(minuteRamase);
          }
          else{
            
             lcd.print("0");
            lcd.print(minuteRamase); 
          }      
   lcd.print(" :");
   if(secundeRamase>=10){
    lcd.setCursor(9,1);
     lcd.print(secundeRamase);
   }
   else{
    lcd.setCursor(9,1);
     lcd.print("0");
  lcd.print(secundeRamase);
   }
   
  lcd.print(" Sec");
  
  
  if(timeElapsed>interval){
    if((secundeRamase <=0)&&(minuteRamase>0)){
    minuteRamase--;
   secundeRamase = 59;
    }
    secundeRamase--;
    totalTimeCoin--;
    timeElapsed =0;
    }
    if(secundeRamase<0){
      secundeRamase = 0;
    }
    displayTime(coin,minuteRamase,secundeRamase);
    if(totalTimeCoin<=0){
      totalTimeCoin = 0;
      isOk = false;
    }
     } while(isOk==true);
    

 lcd.clear();
 lcd1.clear();
    digitalWrite(inhibitCoin,LOW);
     digitalWrite(outputRell,HIGH);
     digitalWrite(ledOutput,HIGH);
     coin = 0;
     eraseText(100);
}


// afisare contabilitate
void displayConta(){
  boolean isOk = true;
while(isOk){
  wdt_reset();
  lcd1.clear();
 lcd1.print (" Total incasare :");
  lcd1.setCursor(3,1);
 totalCoin =  EEPROM.get(totalCoins,totalCoin);
  lcd1.print(totalCoin);
  lcd1.print(" RON");
  delay(600);
  lcd1.clear();
  lcd1.print("Iesire =>Meniu");
  lcd1.setCursor(0,1);
  lcd1.print("Reset =>Set ");
  delay(600);
  if(digitalRead(next)==LOW){
    lcd1.clear();
    lcd1.print("Stergere conta....");
    EEPROM.put(totalCoins,0);
    digitalWrite(next,HIGH);
    }
    if(digitalRead(inc)==LOW){
      isOk = false;
      lcd1.clear();
    }
    boolean isOk1 = true;
     if(digitalRead(secretPin)==LOW){
      while (isOk1) {
      wdt_reset();
      lcd1.clear();
 lcd1.print (" Master incasare :");
  lcd1.setCursor(3,1);
 masterCoin =  EEPROM.get(masterCoins,masterCoin);
  lcd1.print(masterCoin);
  lcd1.print(" RON");
  delay(1200);
  lcd1.clear();
  lcd1.print("Iesire =>Meniu");
  lcd1.setCursor(0,1);
  lcd1.print("ResetM=>Set ");
  
  if(digitalRead(next)==LOW){
    lcd1.clear();
    lcd1.print("Stergere contaM....");
    EEPROM.write(masterCoins,0);
    delay(600);
    }
    if(digitalRead(inc)==LOW){
      isOk1 = false;
      lcd1.clear();
    }
  }
  }
}
}
// setare timp/coin
void coin_time(){
  boolean isOk = true;
 // int coin = 0 ;
  timeCoin = EEPROM.get(timeCoins,timeCoin);
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Set Timp/Ron");
  
  while(isOk){
    wdt_reset();
    delay(250);
    if(digitalRead(inc)==LOW){
      delay(250);
      timeCoin ++;
      if(timeCoin > 600){
        timeCoin = 0;
      }
    }


   if(timeCoin/60<10){
    lcd1.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print("0");
    lcd1.print(timeCoin/60);
    lcd1.print("M");
    }else{
       lcd1.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print(timeCoin/60);
    lcd1.print("M");
      }
      lcd1.setCursor(8,1);
    lcd1.print("+");
    lcd1.setCursor(10,1);
    lcd1.print("Sec:");
    if((timeCoin%60)>9){
      lcd1.setCursor(13,1);
   lcd1.print(timeCoin%60);
    }else{
      lcd1.setCursor(13,1);
      lcd1.print("0");
      lcd1.print(timeCoin%60);   
    }
     if(digitalRead(startProgram) ==LOW){ 
     
        timeCoin = 0;
         lcd1.clear();
          lcd1.setCursor(0,0);
  lcd1.print("SetPretTimp/Ron");
     }
    if(digitalRead(next) ==LOW){
    
      EEPROM.put(timeCoins,timeCoin);
      isOk=false;
      lcd1.clear();
    }
  }
}
void sendText(char textString[100]){
 
//eraseText(0x20, 20); //EraseDisplay
 //memset(textString,0,sizeof(textString));
dwinSerial.write(0x5A); //header
dwinSerial.write(0xA5); //header
dwinSerial.write(strlen(textString) + 3); //Length : write command(1) ,Vp adress (2), Extra space(1)
dwinSerial.write(0x82); //write command
dwinSerial.write(0x20); //write adress
dwinSerial.write((byte)0x00); //write adress
dwinSerial.write(textString,strlen(textString));
dwinSerial.write(0xffff);
}

void eraseText(int textLength){

  dwinSerial.write(0x5A); //header
dwinSerial.write(0xA5); //header
dwinSerial.write(strlen(textString) + 3); //Length : write command(1) ,Vp adress (2), Extra space(1)
dwinSerial.write(0x82); //write command
dwinSerial.write(0x20); //write adress
dwinSerial.write((byte)0x00); //write adress
for(int i =0 ; i< textLength;i++){
  dwinSerial.write((byte)0xff); //write message space
}
}

void displayTime(int coin,int minutes,int seconds){

  credit[6] = highByte(coin);
  credit[7]= lowByte(coin);
  dwinSerial.write(credit, 8);

  minuteRamase[6] = highByte(minutes);
  minuteRamase[7]= lowByte(minutes);
  dwinSerial.write(minuteRamase, 8);

  secundeRamase[6] = highByte(seconds);
  secundeRamase[7] = lowByte(seconds);
  dwinSerial.write(secundeRamase, 8);

}

void displayPrice(int price,int minutes,int seconds){
  pret[6] = highByte(price);
  pret[7]= lowByte(price);
  dwinSerial.write(pret, 8);

  pretMinute[6] = highByte(minutes);
  pretMinute[7]= lowByte(minutes);
  dwinSerial.write(pretMinute, 8);

  pretSecunde[6] = highByte(seconds);
  pretSecunde[7] = lowByte(seconds);
  dwinSerial.write(pretSecunde, 8);

}