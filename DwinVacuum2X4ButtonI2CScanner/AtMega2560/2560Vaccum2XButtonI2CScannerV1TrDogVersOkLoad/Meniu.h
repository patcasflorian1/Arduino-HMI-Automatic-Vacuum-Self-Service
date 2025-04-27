


//Meniu Program
void meniuprog(){
  //.........zona minute/RON.................

//int totalCoin;
  digitalWrite(inhibitCoin,HIGH);
  //Set Time 
  delay(600);
 
  int meniu = 7;
  lcd1.clear();
  while (meniu == 7) {
      wdt_reset();
    meniu = 1;
           delay(600);      
         lcd1.setCursor(0, 0);  
          lcd1.print(" * SetProg/Timp  "  );
          lcd1.setCursor(0, 1); lcd1.print(" AfisConta");delay(600);  
          lcd1.setCursor(1,0); lcd1.blink();
 do{
        wdt_reset();
        if (digitalRead(meniuButton[1]) ==LOW) { 
          delay(200);
          lcd1.clear();
          lcd1.noBlink();
          
          coin_time();
           meniu = 2;
        } 
        if (digitalRead(meniuButton[0]) ==LOW) 
          {
            delay(200);
            
          meniu = 2;
          lcd1.clear();
          }
      }while(meniu==1);

      
       //Display Device
        delay(600);      
         lcd1.setCursor(0, 0);  
          lcd1.print(" * Display Device  "  );
          lcd1.setCursor(0, 1); lcd1.print(" AfisConta");delay(600);  
          lcd1.setCursor(1,0); lcd1.blink();
 do{
 wdt_reset();
        if (digitalRead(meniuButton[1]) ==LOW) { 
          delay(200);
          lcd1.clear();
          lcd1.noBlink();
          
         scannerRun();
           meniu = 3;
        } 
        if (digitalRead(meniuButton[0]) ==LOW) 
          {
            delay(200);
           
          meniu = 3;
          lcd1.clear();
          }
      }while(meniu==2);

      
      //Display Conta

 delay(400);
    
      lcd1.print( " * AfisConta ");
      lcd1.setCursor(0, 1);
      lcd1.print("  SetCoin");
      lcd1.setCursor(1,0); 
      lcd1.blink();
                                                                         
      
      do {
        wdt_reset();
        if (digitalRead(meniuButton[1]) ==LOW) { 
          delay(200);
          lcd1.noBlink();
          
            displayConta();
          meniu = 4;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(meniuButton[0]) ==LOW) {
          delay(200);
          
          meniu = 4;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 3);

//Set CoinPas
 delay(400);
    
      lcd1.print( " * SetCoin ");
      lcd1.setCursor(0, 1);
      lcd1.print("TestReelSt1");
      lcd1.setCursor(1,0); 
      lcd1.blink();


      do {
       wdt_reset();
        if (digitalRead(meniuButton[1]) ==LOW) { 
          delay(200);
          lcd1.noBlink();
          
            setCoin();
          meniu = 5;
          lcd1.clear();
        }
           delay(200);
        if (digitalRead(meniuButton[0]) ==LOW) {
          delay(200);
          
          meniu = 5;
           delay(200);
          lcd1.clear();
        }
      } while (meniu == 4);
      do
      {
         wdt_reset();
      lcd1.print( " * EXIT ");
      lcd1.setCursor(0, 1); 
      lcd1.print("  MENIU ");
      lcd1.setCursor(1,0);
      lcd1.blink(); 
      delay(200);
        if (digitalRead(meniuButton[1]) ==LOW) {
         lcd1.noBlink();
          meniu = 6;
          digitalWrite(inhibitCoin,LOW);
          delay(200);
          lcd1.clear();
        }
        delay(150);
        if (digitalRead(meniuButton[0]) ==LOW) {
            delay(300);
            
          meniu = 7;
          lcd1.clear();
         }
      } while (meniu == 5);

  } 
 delay(200);
  digitalWrite(inhibitCoin,LOW);
  //Extract from memory price of coin
   timeCoin1 =  EEPROM.get(timeCoinsEeprom1,timeCoin1);
   timeCoin2 = EEPROM.get(timeCoinsEeprom2,timeCoin2);
   timeCoin3 = EEPROM.get(timeCoinsEeprom3,timeCoin3);
   timeCoin4 = EEPROM.get(timeCoinsEeprom4,timeCoin4);
   setup();
}
