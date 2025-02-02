/* How to use the DHT-22 sensor with Arduino uno
   Temperature and humidity sensor
   More info: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
   Dev: Michalis Vasilakis // Date: 1/7/2015 // www.ardumotive.com */

//Libraries
#include <DHT.h>;
#include <SoftwareSerial.h>
const byte rxPin = 3; //rx
const byte txPin = 4; //tx
SoftwareSerial dwinSerial(rxPin, txPin);

//Constants
#define DHTPIN 8     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float humid;  //Stores humidity value
float temp; //Stores temperature value
float tempF;
#define temp_address   0x52
#define hum_address     0x50
#define tempF_address   0x51

unsigned char   Temperature[8] = {0x5A, 0xA5, 0x05, 0x82, temp_address , 0x00, 0x00, 0x00};
unsigned char   TemperatureF[8] = {0x5A, 0xA5, 0x05, 0x82, tempF_address , 0x00, 0x00, 0x00};
unsigned char    Humidity[8] = {0x5A, 0xA5, 0x05, 0x82, hum_address, 0x00, 0x00, 0x00};
void setup()
{
    Serial.begin(115200);
    dwinSerial.begin(115200);
	dht.begin();

}

void loop()
{
    //Read data and store it to variables hum and temp
    humid = dht.readHumidity();
    temp= dht.readTemperature();
    tempF = ((temp*9.0)/5.0+32.0);   // Convert celsius to fahrenheit
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(humid);
    Serial.println(" %");
    Serial.print(" Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.print(tempF);  
  Serial.println("°F ");
    delay(2000); //Delay 2 sec.
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
