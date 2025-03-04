
 void scannerRun(){
  
  int test = 0;
  while(test==0){
  wdt_reset();
 lcd1.print("Scanning...");
  byte error, address; //variable for error and I2C address
  int nDevices;
delay(400);
 lcd1.clear();
  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      
  lcd1.print(address, HEX);     
      nDevices++;
    }
  }
  if (nDevices == 0){
    lcd1.print("No I2C devices found\n");
  }
  lcd1.setCursor(0,1);
 lcd1.print("Exit => Meniu");
  delay(2500); // wait 5 seconds for the next I2C scan
  lcd1.clear();
   //pcf8574Run(); //read the keypad
   
        if (digitalRead(meniuButton[0]) ==LOW) // Set
        { 
          delay(200);
          lcd1.clear();
           test=1;
        }
        
  }
 }