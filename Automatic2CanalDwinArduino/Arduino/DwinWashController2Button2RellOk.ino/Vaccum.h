

// activare releu vacuumCleaner
void vacuumCleaner(){
long totalTimeCoin = 0;
int minuteRamase = 0;
int secundeRamase = 0;
 float newCoin = 0;
 float newTimeCoin = 0;
boolean isOk =false;
  elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs
// delay in milliseconds between blinks of the LED
unsigned int interval = 1000;
  lcd.noBlink();
  if(coin == 0){
    lcd.print(" Credit 0");
    delay(1200);
    displayTimeVaccum(0,0,0);
    displayTimeAir(0,0,0);
    return;
  }
   lcd.clear();
  delay(10);
  timeCoin = EEPROM.get(timeCoins,timeCoin);
  timeCoin2 = EEPROM.get(timeCoins2,timeCoin2);
 while(isOk==false){
   wdt_reset();
  lcd.setCursor(0,0);
   lcd.print(" Credit:");
   lcd.setCursor(8,0);
   lcd.print(coin);
   lcd.setCursor(11,0);
   lcd.print("Jet");
    lcd.setCursor(0,1);
    lcd.print("Alegeti Program");
     digitalWrite(ledOutput,LOW);
    digitalWrite(ledOutput2,LOW);
  if((digitalRead(startProgram)==LOW)&&(activeVaccum == false)){
   totalTimeCoin = coin*timeCoin;
     minuteRamase = (coin*timeCoin)/60;
     secundeRamase =((coin*timeCoin)%60);
     activeVaccum=true;
     isOk=true;
     lcd.clear();
     digitalWrite(outputRell,LOW);
     digitalWrite(ledOutput,LOW);
     digitalWrite(ledOutput2,HIGH);
      totalCoin =  EEPROM.get(totalCoins,totalCoin);
  totalCoin = totalCoin+coin;
  EEPROM.put(totalCoins,totalCoin);
  Serial.print("minuteRamase ");
     Serial.println(minuteRamase);
      Serial.print("secundeRamase ");
     Serial.println(secundeRamase);
  coin = 0;
  switchPage(1);
  displayTimeVaccum(coin,minuteRamase,secundeRamase);
  }
  //Program Vaccum
   if((digitalRead(startProgramAer)==LOW)&&(activeAir == false)){
   totalTimeCoin = coin*timeCoin2;
    minuteRamase = (coin*timeCoin2)/60;
    secundeRamase =((coin*timeCoin2)%60);    
    activeAir=true;
     isOk=true;
     lcd.clear();
     digitalWrite(outputRel2,LOW);
     digitalWrite(ledOutput2,LOW);
      digitalWrite(ledOutput,HIGH);
      totalCoin =  EEPROM.get(totalCoins,totalCoin);
  totalCoin = totalCoin+coin;
  EEPROM.put(totalCoins,totalCoin);
  Serial.print("minuteRamase ");
     Serial.println(minuteRamase);
      Serial.print("secundeRamase ");
     Serial.println(secundeRamase);
  coin = 0;
  switchPage(2);
  displayTimeAir(coin,minuteRamase,secundeRamase);
  }
 displayTimeVaccum(coin,minuteRamase,secundeRamase);
 }
   digitalWrite(inhibitCoin,HIGH);

 // totalTimeCoin--;
  if((minuteRamase>0)&&(secundeRamase==0)){
    minuteRamase--;
    secundeRamase=59;
  }
     timeCoin = EEPROM.get(timeCoins,timeCoin);
  timeCoin2 = EEPROM.get(timeCoins2,timeCoin2); 
   do{
     if((digitalRead(startProgram)==LOW)&&(activeAir==true)){
       
       newCoin = ((float)totalTimeCoin/(float)timeCoin2);
      // newTimeCoin = (timeCoin/60)+(((float)(timeCoin%10)/100));
      //totalTimeCoin =(int)((newCoin*newTimeCoin)*60);
       totalTimeCoin =  newCoin* timeCoin;
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
     
     newCoin = 0;
     newTimeCoin = 0;
     coin = 0;
     activeVaccum=true;
     activeAir = false;
      digitalWrite(outputRel2,HIGH);
     digitalWrite(ledOutput2,HIGH);
      delay(500);
     digitalWrite(outputRell,LOW);
     digitalWrite(ledOutput,LOW);
      lcd.clear();
    }
    //Program Aer Comprimat
     if((digitalRead(startProgramAer)==LOW)&&(activeVaccum==true)){
    
       newCoin = ((float)totalTimeCoin/(float)timeCoin);
    totalTimeCoin =  newCoin* timeCoin2;
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      newCoin = 0;
     newTimeCoin = 0;
     coin = 0;
     
     activeVaccum=false;
     activeAir = true;
     digitalWrite(outputRell,HIGH);
      digitalWrite(ledOutput,HIGH);
       delay(500);
     digitalWrite(outputRel2,LOW);
     digitalWrite(ledOutput2,LOW);
      lcd.clear();
    }
   
  lcd.setCursor(0,0);
  if(activeVaccum==true){
   lcd.print("TimpPresiune:");
    switchPage(1);
  displayTimeVaccum(coin,minuteRamase,secundeRamase);
  }
  if(activeAir == true){
    lcd.print("TimpCarpet: ");
    switchPage(2);
  displayTimeAir(coin,minuteRamase,secundeRamase);
  }
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
    if(totalTimeCoin<=0){
      totalTimeCoin = 0;
      timeElapsed =0;
       newCoin = 0;
       newTimeCoin = 0;
       activeVaccum = false;
       activeAir = false;
      isOk = false;
    }
    wdt_reset();
     } while(isOk==true);
    

 lcd.clear();
 lcd1.clear();
    digitalWrite(inhibitCoin,LOW);
     digitalWrite(outputRell,HIGH);
     digitalWrite(ledOutput,HIGH);
     digitalWrite(outputRel2,HIGH);
     digitalWrite(ledOutput2,HIGH);
     coin = 0;
}
