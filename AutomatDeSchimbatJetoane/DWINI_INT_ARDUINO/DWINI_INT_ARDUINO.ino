#include <SoftwareSerial.h>
const byte rxPin = 2; //rx
const byte txPin = 3; //tx
SoftwareSerial dwinSerial(rxPin, txPin);
#define temp_address   0x50
#define hum_address     0x51
#define tempF_address   0x52
#define jeton_address   0x53
#define minute_address   0x54
#define secunde_address   0x55
#define text_address   0x20
 char textString[10] ="Aspirare  ";
 char textString2[100] ="Parfum";
 int vpAddresss = 20;
 int textLengths = 100;
int nrA = 0,nrB = 0,nrC =0;
unsigned char   Temperature[8] = {0x5A, 0xA5, 0x05, 0x82, temp_address , 0x00, 0x00, 0x00};
unsigned char   TemperatureF[8] = {0x5A, 0xA5, 0x05, 0x82, tempF_address , 0x00, 0x00, 0x00};
unsigned char    Humidity[8] = {0x5A, 0xA5, 0x05, 0x82, hum_address, 0x00, 0x00, 0x00};
unsigned char    Jeton[8] = {0x5A, 0xA5, 0x05, 0x82, jeton_address, 0x00, 0x00, 0x00};
unsigned char    Minute[8] = {0x5A, 0xA5, 0x05, 0x82, minute_address, 0x00, 0x00, 0x00};
unsigned char    Secunde[8] = {0x5A, 0xA5, 0x05, 0x82, secunde_address, 0x00, 0x00, 0x00};
unsigned char    eraseTexts[10] = {0x5A, 0xA5, 0x07, 0x82, text_address, 0x00, 0x20,0x20, 0xff, 0xff};
bool isOk = true;
void setup() {
  Serial.begin(115200);
    dwinSerial.begin(115200);

}

void loop() {
  for(int i= 0;i<100;i++){
    nrA = 1;
    nrB = 30;
    nrC = 10;
    Serial.print("NrA ");
    Serial.println(nrA);
    Serial.print("NrB ");
    Serial.println(nrB);
    Serial.print("NrC ");
    Serial.println(nrC);
    delay(1000);
    Data_Arduino_to_Display();
    sendText(textString);
    delay(1000);
    eraseText( 0x20,100);
   //dwinSerial.write(eraseTexts,10);
   delay(500);
   sendText(textString2);
    delay(1000);
    eraseText( 0x20,100);
    //dwinSerial.write(eraseTexts,10);
  
    delay(50);
  }
}
void Data_Arduino_to_Display() {
  delay(100);
  
  int t = nrA;
  int tF =nrB;
  int h = 1;
  int min = 13;
  int sec = 30;
  /*------Send Data to Display------*/

  Temperature[6] = highByte(t);
  Temperature[7]= lowByte(t);
  dwinSerial.write(Temperature, 8);

  TemperatureF[6] = highByte(tF);
  TemperatureF[7]= lowByte(tF);
  dwinSerial.write(TemperatureF, 8);

  Humidity[6] = highByte(h);
  Humidity[7] = lowByte(h);
  dwinSerial.write(Humidity, 8);

   Jeton[6] = highByte(nrC);
  Jeton[7] = lowByte(nrC);
  dwinSerial.write(Jeton, 8);
  Minute[6] = highByte(min);
  Minute[7] = lowByte(min);
  dwinSerial.write(Minute, 8);
  Secunde[6] = highByte(sec);
  Secunde[7] = lowByte(sec);
  dwinSerial.write(Secunde, 8);
  /*
  if(isOk ==true){
    isOk = false;
    textString[6] = "Parfum";
    eraseText(0x20, 20); //EraseDisplay
     // memset(textString,0,sizeof(textString));
  }
  if(isOk == false){
    textString[9] = "Aspirare";
    isOk = true;
    eraseText(0x20, 20); //EraseDisplay
      //memset(textString,0,sizeof(textString));
  }
  */
  delay(500);
  
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

void eraseText( int vpAddress,int textLength){

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