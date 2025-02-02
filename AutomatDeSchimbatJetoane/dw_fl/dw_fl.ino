#include <DHT.h>
#include <SoftwareSerial.h>
const byte rxPin = 3; //rx
const byte txPin = 4; //tx
SoftwareSerial dwinSerial(rxPin, txPin);

float temp;
float tempF;
float humid;


#define DHTTYPE DHT11     // DHT 11
#define DHTPIN 8          // D8  pin connected with DHT

DHT dht(DHTPIN, DHTTYPE);

/* Adresses of all sensors  temp vp 5200 , temp F 5100 , humid  5000 */

#define temp_address   0x52
#define hum_address     0x50
#define tempF_address   0x51

unsigned char   Temperature[8] = {0x5A, 0xA5, 0x05, 0x82, temp_address , 0x00, 0x00, 0x00};
unsigned char   TemperatureF[8] = {0x5A, 0xA5, 0x05, 0x82, tempF_address , 0x00, 0x00, 0x00};
unsigned char    Humidity[8] = {0x5A, 0xA5, 0x05, 0x82, hum_address, 0x00, 0x00, 0x00};

void setup() {
  Serial.begin(115200);
  dwinSerial.begin(115200);

  dht.begin();
  
}

void loop() {

  temp = dht.readTemperature();
  tempF = ((temp*9.0)/5.0+32.0);   // Convert celsius to fahrenheit
  humid = dht.readHumidity();
  
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" *C   :");

  Serial.print(tempF);  
  Serial.println("°F ");

  Serial.print("Humidity: ");
  Serial.print(humid);
  Serial.println(" %");
  
  Serial.println();
   delay(2000);
  Data_Arduino_to_Display();
  
}

void Data_Arduino_to_Display() {
  delay(100);
  
  int t = temp*100;
  int tF =tempF*100;
  int h = humid*100;

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
 
}

 
  

