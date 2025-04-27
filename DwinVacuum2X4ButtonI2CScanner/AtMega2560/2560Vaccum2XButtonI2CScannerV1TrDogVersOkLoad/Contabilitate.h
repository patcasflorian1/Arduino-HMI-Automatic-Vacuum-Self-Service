

// setare conabilitate
void setConta(int totalCoin,int totalCoins,int inhibitCoin){
  lcd1.clear();
  digitalWrite(inhibitCoin,HIGH);
  delay(350);
  boolean set1 = true;
  totalCoin = EEPROM.get(totalCoins,totalCoin);
  while(set1){
     wdt_reset();
   // pcf8574Run(); //read the keypad
    lcd1.setCursor(1,0);
    lcd1.print("Total : ");
    lcd1.print(totalCoin);
     lcd1.setCursor(0,1);
    
   if ((digitalRead(meniuButton[0]) ==LOW)&&(totalCoin>=100))
  {
  // pressedCharacter = " ";
      totalCoin = totalCoin-50;
      delay(250);
      if(totalCoin<=50){
         totalCoin=0;
          }
      }
      lcd1.print("Exit=>Set");
   if (digitalRead(meniuButton[1]) ==LOW)
  {
 
      EEPROM.put(totalCoins,totalCoin);
      set1=false;
      digitalWrite(inhibitCoin,LOW);
      lcd1.clear();
      delay(300);
     }
    }
    
  }

  // afisare contabilitate
void displayConta(){
 //int totalTimeCoin;
 int totalCoin;
// rezervare zone de memorie in eeprom
int totalCoinsConta = 10; // zona memorare total bani incasati 
  boolean isOk = true;
while(isOk){
  wdt_reset();
  lcd1.clear();
  lcd1.setCursor(0,0);
 lcd1.print ("Total incasare :");
  lcd1.setCursor(1,1);
 totalCoin =  EEPROM.get(totalCoinsConta,totalCoin);
  lcd1.print(totalCoin);
  lcd1.print(" RON");
  delay(600);
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("Iesire =>Meniu");
  lcd1.setCursor(0,1);
  lcd1.print("Reset =>SET ");
  delay(600);
  if(digitalRead(meniuButton[1]) ==LOW){
    
    lcd1.clear();
    lcd1.print("Stergere conta....");
    EEPROM.put(totalCoinsConta,0);
    }
    if(digitalRead(meniuButton[0]) ==LOW){
      
      isOk = false;
      lcd1.clear();
    }
}
}