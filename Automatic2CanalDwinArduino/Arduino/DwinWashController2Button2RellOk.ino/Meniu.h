
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
  lcd1.print("Reset =>Next ");
  delay(600);
  if(digitalRead(next)==LOW){
    lcd1.clear();
    lcd1.print("Stergere conta....");
    EEPROM.put(totalCoins,0);
    }
    if(digitalRead(inc)==LOW){
      isOk = false;
      lcd1.clear();
    }
}
}

// setare timp1/coin
void coin_time1(){
  boolean isOk = true;
 // int coin = 0 ;
  timeCoin = EEPROM.get(timeCoins,timeCoin);
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Set Timp/Jeton");
  
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
    lcd1.print("1Jet=");
    lcd1.print("0");
    lcd1.print(timeCoin/60);
    lcd1.print("M");
    }else{
       lcd1.setCursor(0,1);
    lcd1.print("1Jet=");
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
  lcd1.print("SetPret1Timp/Jet");
     }
    if(digitalRead(next) ==LOW){
    
      EEPROM.put(timeCoins,timeCoin);
      isOk=false;
      lcd1.clear();
    }
  }
}

// setare timp2/coin
void coin_time2(){
  boolean isOk = true;
 // int coin = 0 ;
  timeCoin2 = EEPROM.get(timeCoins2,timeCoin2);
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Set Timp2/Jet");
  
  while(isOk){
    wdt_reset();
    delay(250);
    if(digitalRead(inc)==LOW){
      delay(250);
      timeCoin2 ++;
      if(timeCoin2 > 600){
        timeCoin2 = 0;
      }
    }


   if(timeCoin2/60<10){
    lcd1.setCursor(0,1);
    lcd1.print("1Jet=");
    lcd1.print("0");
    lcd1.print(timeCoin2/60);
    lcd1.print("M");
    }else{
       lcd1.setCursor(0,1);
    lcd1.print("1Jet=");
    lcd1.print(timeCoin2/60);
    lcd1.print("M");
      }
      lcd1.setCursor(8,1);
    lcd1.print("+");
    lcd1.setCursor(10,1);
    lcd1.print("Sec:");
    if((timeCoin2%60)>9){
      lcd1.setCursor(13,1);
   lcd1.print(timeCoin2%60);
    }else{
      lcd1.setCursor(13,1);
      lcd1.print("0");
      lcd1.print(timeCoin2%60);   
    }
     if(digitalRead(startProgram) ==LOW){ 
     
        timeCoin2 = 0;
         lcd1.clear();
          lcd1.setCursor(0,0);
  lcd1.print("SetPret2Timp/Jet");
     }
    if(digitalRead(next) ==LOW){
    
      EEPROM.put(timeCoins2,timeCoin2);
      isOk=false;
      lcd1.clear();
    }
  }
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
          lcd1.print(" * SetProg1/Timp  "  );
          
          lcd1.setCursor(1, 1); 
          lcd1.print(" SetProg2/Timp  ");
          delay(400);  
          lcd1.setCursor(1,0);
          lcd1.blink();
 do{
   wdt_reset();
        if (digitalRead(next) == LOW) { 
          delay(200);
          lcd1.clear();
          lcd1.noBlink();
          coin_time1();
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
    
      lcd1.print(" * SetProg2/Timp  " );
      lcd1.setCursor(1, 1);
      lcd1.print(" AfisConta");
      lcd1.setCursor(1,0); 
      lcd1.blink();
                                                                         
      
      do
      {

        wdt_reset();
        if (digitalRead(next) == LOW) { 
          delay(200);
          lcd1.noBlink();
            coin_time2();
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
          meniu = 4;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(inc) == LOW) {
          delay(200);
          meniu = 4;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 3);
     
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
        }
        if (digitalRead(inc) == LOW) {
        delay(300);
          meniu = 5;
          lcd1.clear();
     
      }
    } while (meniu == 4);
   
  } 
 delay(200);
  
}

