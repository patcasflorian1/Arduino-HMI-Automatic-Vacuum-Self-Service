// setare timp/coin
void coin_time(int memoryCoins){
  boolean isOk = true;
 int timeForCoin ;
  timeForCoin = EEPROM.get(memoryCoins,timeForCoin);
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Set Timp/Jeton");
  
  while(isOk){
    wdt_reset();
    delay(250);
    if(digitalRead(meniuButton[0])==LOW){
      delay(250);
      timeForCoin ++;
      if(timeForCoin > 600){
        timeForCoin = 0;
      }
    }


   if(timeForCoin/60<10){
    lcd1.setCursor(0,1);
    lcd1.print("1Jet=");
    lcd1.print("0");
    lcd1.print(timeForCoin/60);
    lcd1.print("M");
    }else{
       lcd1.setCursor(0,1);
    lcd1.print("1Jet=");
    lcd1.print(timeForCoin/60);
    lcd1.print("M");
      }
      lcd1.setCursor(8,1);
    lcd1.print("+");
    lcd1.setCursor(10,1);
    lcd1.print("Sec:");
    if((timeForCoin%60)>9){
      lcd1.setCursor(13,1);
   lcd1.print(timeForCoin%60);
    }else{
      lcd1.setCursor(13,1);
      lcd1.print("0");
      lcd1.print(timeForCoin%60);   
    }
     if(digitalRead(meniuButton[2]) ==LOW){ 
     
        timeForCoin = 0;
         lcd1.clear();
          lcd1.setCursor(0,0);
  lcd1.print("SetPretTimp/Jet");
     }
    if(digitalRead(meniuButton[1]) ==LOW){
    
      EEPROM.put(memoryCoins,timeForCoin);
      isOk=false;
      lcd1.clear();
    }
  }
}

// afisare contabilitate
void displayConta(){
  delay(900);
  boolean isOk = true;
while(isOk){
  wdt_reset();
  lcd1.clear();
 lcd1.print (" Total incasare :");
  lcd1.setCursor(3,1);
 totalCoin =  EEPROM.get(totalCoins,totalCoin);
  lcd1.print(totalCoin);
  lcd1.print(" Jetoane");
  delay(900);
  lcd1.clear();
  lcd1.print("Iesire => Meniu");
  lcd1.setCursor(0,1);
  lcd1.print("Reset => +/Set ");
  delay(900);
  if(digitalRead(meniuButton[1])==LOW){
    lcd1.clear();
    lcd1.print("Stergere conta....");
    EEPROM.put(totalCoins,0);
    delay(900);
    }
    if(digitalRead(meniuButton[0])==LOW){
      isOk = false;
      lcd1.clear();
    }
}
}

//Meniu Program
void meniuprog()
{
  delay(600);
   int meniu = 8;
  lcd1.clear();
  while (meniu == 8) {
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
        if (digitalRead(meniuButton[1]) == LOW) { 
          delay(200);
          lcd1.clear();
          lcd1.noBlink();
          coin_time(timeCoins1);
           meniu = 2;
        } 
        if (digitalRead(meniuButton[0]) == LOW) 
          {
            delay(200);
          meniu = 2;
          lcd1.clear();
          }
      }while(meniu==1);
       

 delay(400);
    
      lcd1.print(" * SetProg2/Timp  " );
      lcd1.setCursor(1, 1);
      lcd1.print(" SetProg3/Timp");
      lcd1.setCursor(1,0); 
      lcd1.blink();   
      do
      {

        wdt_reset();
        if (digitalRead(meniuButton[1]) == LOW) { 
          delay(200);
          lcd1.noBlink();
            coin_time(timeCoins2);
          meniu = 3;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(meniuButton[0]) == LOW) {
          delay(200);
          meniu = 3;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 2);   
    delay(400);  
     lcd1.print(" * SetProg3/Timp  " );
      lcd1.setCursor(1, 1);
      lcd1.print(" SetProg4/Timp");
      lcd1.setCursor(1,0); 
      lcd1.blink();
     do
      {
        wdt_reset();
        if (digitalRead(meniuButton[1]) == LOW) { 
          delay(200);
          lcd1.noBlink();
            coin_time(timeCoins3);
          meniu = 4;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(meniuButton[0]) == LOW) {
          delay(200);
          meniu = 4;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 3);
            delay(400);
    
     lcd1.print(" * SetProg4/Timp  " );
      lcd1.setCursor(1, 1);
      lcd1.print(" Set/Conta");
      lcd1.setCursor(1,0); 
      lcd1.blink();
     do
      {
        wdt_reset();
        if (digitalRead(meniuButton[1]) == LOW) { 
          delay(200);
          lcd1.noBlink();
            coin_time(timeCoins4);
          meniu = 5;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(meniuButton[0]) == LOW) {
          delay(200);
          meniu = 5;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 4);


        lcd1.print( " * AfisConta ");
      lcd1.setCursor(1, 1);
      lcd1.print(" ScannDevice");
      lcd1.setCursor(1,0); 
      lcd1.blink();
         do
      {
        wdt_reset();
        if (digitalRead(meniuButton[1]) == LOW) { 
          delay(400);
          lcd1.noBlink();
            displayConta();
          meniu = 6;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(meniuButton[0]) == LOW) {
          delay(400);
          meniu = 6;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 5);
     
      lcd1.print( " *ScannDevice ");
      lcd1.setCursor(1, 1);
      lcd1.print(" Exit");
      lcd1.setCursor(1,0); 
      lcd1.blink();
         do
      {
        wdt_reset();
        if (digitalRead(meniuButton[1]) == LOW) { 
          delay(400);
          lcd1.noBlink();
            scannerRun();
          meniu = 7;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(meniuButton[0]) == LOW) {
          delay(400);
          meniu = 7;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 6);
      lcd1.print( " * EXIT");
      lcd1.setCursor(0, 1);
      lcd1.print("   MENIU ");
      lcd1.setCursor(1,0);
      lcd1.blink();
    
      do
    {
      wdt_reset();
          if (digitalRead(meniuButton[1]) == LOW)
        {
          lcd1.noBlink();
          meniu = 9;
          delay(200);
          lcd1.clear();
        }
        if (digitalRead(meniuButton[0]) == LOW) {
        delay(300);
          meniu = 8;
          lcd1.clear();
          
     
      }
    } while (meniu == 7);
   
  } 
 delay(200);
  setup();
}

