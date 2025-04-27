//Setare limitCoin
void setCoin(){
  // pasCoin =  EEPROM.get(coinPasZone,pasCoin);
    boolean isOk = true;
   
   
     limitCoin =  EEPROM.get(coinLimitZone,limitCoin);
     lcd1.clear();
      delay(300);

while(isOk){
   wdt_reset();
   if(digitalRead(meniuButton[2]) ==LOW){
    lcd1.clear();
      limitCoin=1;
    }
  lcd1.setCursor(0,0);
 lcd1.print ("SetatiLimitaCr :");
  lcd1.setCursor(1,1);
  lcd1.print("CreditMax : ");
  lcd1.print(limitCoin);

//delay(300);
  if(digitalRead(meniuButton[1]) ==LOW){
    //lcd1.clear();
    limitCoin ++;
    delay(100);
    if(limitCoin>200){
      limitCoin=0;
    }
   
    EEPROM.put(coinLimitZone,limitCoin);
    delay(300);
    }
    if(digitalRead(meniuButton[0]) ==LOW){
      isOk = false;
      lcd1.clear();
      delay(300);
      
    }
}
}

// setare timp/coin
void coin_time(){

  int isOk = 0;
  boolean isOk1 = true;
  int timeCoinsEeprom1 = 20; 
 int timeCoinsEeprom2 = 30;
 int timeCoinsEeprom3 = 40;
 int timeCoinsEeprom4 = 50;
  //int coin = 0 ;
   int timeCoin1 =  EEPROM.get(timeCoinsEeprom1,timeCoin1);
  int  timeCoin2 = EEPROM.get(timeCoinsEeprom2,timeCoin2);
  int  timeCoin3 = EEPROM.get(timeCoinsEeprom3,timeCoin3);
  int timeCoin4 = EEPROM.get(timeCoinsEeprom4,timeCoin4);
  
   lcd1.clear();
    delay(250);
    do{
 wdt_reset();
       while(isOk==0){
         wdt_reset();
   lcd1.setCursor(0,0);
  lcd1.print("Pt.Iesire = *Meniu");
  delay(250);
   if(digitalRead(meniuButton[0]) ==LOW){
     delay(250);
      isOk=9;
      isOk1=false;
      lcd1.clear();
    }
    
    lcd1.setCursor(0,1);
    lcd1.print("Pt.Setare = *Set");
    delay(850);
    lcd1.clear();
     lcd1.setCursor(0,0);
    lcd1.print("Pt. Next = *Conta");
    lcd1.setCursor(0,1);
  lcd1.print("Set Pret1 Timp/Ron");
  
     if(digitalRead(meniuButton[1]) ==LOW){
      delay(250);
      isOk=1;
      lcd1.clear();
    }
     if(digitalRead(meniuButton[2]) ==LOW){
      delay(250);
      isOk=2;
      lcd1.clear();
    }
    delay(850);
    lcd1.clear();
}
 //SetPret1   
     
      if(isOk==1){
   lcd1.setCursor(0,0);
  lcd1.print("Set Pret1 Timp/Ron");
      }
  while(isOk==1){
     wdt_reset();
    delay(50);
 
    if(digitalRead(meniuButton[0]) ==LOW){
      
      delay(250);  
     timeCoin1 = timeCoin1 +1;
      if(timeCoin1 > 600){
        timeCoin1 = 0;
      }
    }
    if(timeCoin1/60<10){
    lcd1.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print("0");
    lcd1.print(timeCoin1/60);
    lcd1.print("M");
    }else{
       lcd1.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print(timeCoin1/60);
    lcd1.print("M");
      }
      lcd1.setCursor(8,1);
    lcd1.print("+");
    lcd1.setCursor(10,1);
    lcd1.print("Sec:");
    if((timeCoin1%60)>9){
      lcd1.setCursor(13,1);
   lcd1.print(timeCoin1%60);
    }else{
      lcd1.setCursor(13,1);
      lcd1.print("0");
      lcd1.print(timeCoin1%60);   
    }
     if(digitalRead(meniuButton[2]) ==LOW){ 
    
        timeCoin1 = 0;
         lcd1.clear();
          lcd1.setCursor(0,0);
  lcd1.print("SetP1Timp/Ron");
     }
    if(digitalRead(meniuButton[1]) ==LOW){
    
      EEPROM.put(timeCoinsEeprom1,timeCoin1);
      isOk=2;
      lcd1.clear();
    }
  }
    delay(250);
while(isOk==2){
   delay(50);
  wdt_reset();
   lcd1.setCursor(0,0);
  lcd1.print("Pt.Iesire=Meniu");
  delay(250);
   if(digitalRead(meniuButton[0]) ==LOW){
     delay(250);
      isOk=9;
      isOk1=false;
      lcd1.clear();
    }
    
    lcd1.setCursor(0,1);
    lcd1.print("Pt.Setare=*Set");
    delay(850);
    lcd1.clear();
     lcd1.setCursor(0,0);
    lcd1.print("Pt.Next=Conta");
    lcd1.setCursor(0,1);
  lcd1.print("Set Pret2 Timp/Ron");
     if(digitalRead(meniuButton[1]) ==LOW){
      delay(250);
    
      isOk=3;
      lcd1.clear();
    }
     if(digitalRead(meniuButton[2]) ==LOW){
      delay(250);
      //pressedCharacter = " ";
      isOk=4;
      lcd1.clear();
    }
    delay(850);
    lcd1.clear();
}

  //SetPret2
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("SetPret2 Timp/Ron");
   delay(250);
 
  while(isOk==3){
    delay(50);
     wdt_reset();
     
    if(digitalRead(meniuButton[0]) ==LOW){ 
     delay(250);
     timeCoin2 = timeCoin2 +1;
      if(timeCoin2 > 600){
        timeCoin2 = 0;
      }
    
    }
    if(timeCoin2/60<10){
    lcd1.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print("0");
    lcd1.print(timeCoin2/60);
    lcd1.print("M");
    }else{
       //lcd.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print(timeCoin2/60);
    lcd1.print("M");
      }
      lcd1.setCursor(8,1);
    lcd1.print("+");
    lcd1.setCursor(10,1);
    lcd1.print("Sec");
  if((timeCoin2%60)>9){
    lcd1.setCursor(13,1);
   lcd1.print(timeCoin2%60);
    }else{
       lcd1.setCursor(13,1);
      lcd1.print("0");
      lcd1.print(timeCoin2%60);   
    }
    if(digitalRead(meniuButton[2]) ==LOW){ 
        timeCoin2 = 0;
         lcd1.clear();
          lcd1.setCursor(0,0);
  lcd1.print("SetP2Timp/Ron");
     }
    if(digitalRead(meniuButton[1]) ==LOW){
      EEPROM.put(timeCoinsEeprom2,timeCoin2);
      isOk=4;
      lcd1.clear();
    }
  }
  
   delay(250);
while(isOk==4){
   delay(50);
    wdt_reset();
  //pcf8574Run(); //read the keypad
   lcd1.setCursor(0,0);
  lcd1.print("Pt.Iesire=Meniu");
  delay(250);
   if(digitalRead(meniuButton[0]) ==LOW){
     delay(250);
      isOk1=false;
      isOk=9;
      lcd1.clear();
    }
    
   lcd1.setCursor(0,1);
    lcd1.print("Pt.Setare=*Set");
    delay(850);
    lcd1.clear();
     lcd1.setCursor(0,0);
    lcd1.print("Pt.Next=*Conta");
    lcd1.setCursor(0,1);
  lcd1.print("SetPret3Timp/Ron");
     if(digitalRead(meniuButton[1]) ==LOW){
      delay(250);
     
      isOk=5;
      lcd1.clear();
    }
     if(digitalRead(meniuButton[2]) ==LOW){
      delay(250);
     
      isOk=6;
      lcd1.clear();
    }
    delay(850);
    lcd1.clear();
}

  //Set Pret3
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("SetP3Timp/Ron");
   delay(250);
 while(isOk==5){
   wdt_reset();
  delay(50);
  //pcf8574Run(); //read the keypad
     
    if(digitalRead(meniuButton[0]) ==LOW){ 
      delay(250);
      
     timeCoin3 = timeCoin3 +1;
      if(timeCoin3 > 600){
        timeCoin3 = 0;
      }
    }
    if(timeCoin3/60<10){
    lcd1.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print("0");
    lcd1.print(timeCoin3/60);
    lcd1.print("M");
    }else{
      // lcd.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print(timeCoin3/60);
    lcd1.print("M");
      }
      lcd1.setCursor(8,1);
    lcd1.print("+");
    lcd1.setCursor(10,1);
    lcd1.print("Sec:");
   if((timeCoin3%60)>9){
     lcd1.setCursor(13,1);
   lcd1.print(timeCoin3%60);
    }else{
       lcd1.setCursor(13,1);
      lcd1.print("0");
      lcd1.print(timeCoin3%60);   
    }
    if(digitalRead(meniuButton[2]) ==LOW){ 
      
        timeCoin3 = 0;
         lcd1.clear();
          lcd1.setCursor(0,0);
  lcd1.print("SetP3Timp/Ron");
     }
    if(digitalRead(meniuButton[1]) ==LOW){
      
      EEPROM.put(timeCoinsEeprom3,timeCoin3);
      isOk=6;
      lcd1.clear();
    }
  }
   delay(250);
while(isOk==6){
   wdt_reset();
  delay(50);
   lcd1.setCursor(0,0);
  lcd1.print("Pt.Iesire=*Meniu");
  delay(250);
   if(digitalRead(meniuButton[0]) ==LOW){
   
     delay(250);
      isOk1=false;
      isOk=9;
      lcd1.clear();
    }
    
  lcd1.setCursor(0,1);
    lcd1.print("Pt.Setare=*Set");
     //lcd.setCursor(0,1);
    //lcd.print("Pt.Next=*Conta");
     delay(850);
    lcd1.clear();
    lcd1.setCursor(0,1);
  lcd1.print("SetPret4Timp/Ron");
     if(digitalRead(meniuButton[1]) ==LOW){
      delay(250);
     
      isOk=7;
      lcd1.clear();
    }
     if(digitalRead(meniuButton[2]) ==LOW){
      delay(250);
    
      isOk=0;
      lcd1.clear();
    }
    delay(850);
    lcd1.clear();
}

  //Set Pret4
  lcd1.clear();
  lcd1.setCursor(0,0);
  lcd1.print("SetP4Timp/Ron");
   delay(250);
  while(isOk==7){
    delay(50);
    wdt_reset(); 
    if(digitalRead(meniuButton[0]) == LOW){ 
      delay(250);  
     timeCoin4 = timeCoin4 + 1;
      if(timeCoin4 > 600){
        timeCoin4 = 0;
      }
    }
    if(timeCoin4 / 60 < 10){
    lcd1.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print("0");
    lcd1.print(timeCoin4 / 60);
    lcd1.print("M");
    }else{
       lcd1.setCursor(0,1);
    lcd1.print("1Ron=");
    lcd1.print(timeCoin4 / 60);
    lcd1.print("M");
      }
      lcd1.setCursor(8,1);
    lcd1.print("+");
    lcd1.setCursor(10,1);
    lcd1.print("Sec");
   if((timeCoin4 % 60 ) > 9){
     lcd1.setCursor(13,1);
   lcd1.print(timeCoin4 % 60 );
    }else{
       lcd1.setCursor(13,1);
      lcd1.print("0");
      lcd1.print(timeCoin4 % 60 );   
    }
    if(digitalRead(meniuButton[2]) ==LOW){ 
     
        timeCoin4 = 0;
         lcd1.clear();
          lcd1.setCursor(0,0);
  lcd1.print("SetP4Timp/Ron");
     }
    if(digitalRead(meniuButton[1]) ==LOW){
      
      EEPROM.put(timeCoinsEeprom4 , timeCoin4  );
      isOk=8;
      lcd1.clear();
    }
  }
   delay(250);
while(isOk==8){
   wdt_reset();
   lcd1.setCursor(0,0);
  lcd1.print("Pt.Next=*MENIU");
  delay(250);
   if(digitalRead(meniuButton[0]) ==LOW){ 
      
     delay(250);
     isOk1=false;
      isOk=9;
      lcd1.clear();
    }
    
    lcd1.setCursor(0,1);
    lcd1.print("Pt.Setare=*Set");
     if(digitalRead(meniuButton[1]) ==LOW){ 
      
      delay(250);
      isOk=0;
      isOk1=true;
      lcd1.clear();
    }
}
delay(250);
 wdt_reset();
}while(isOk1==true);
lcd1.clear();
}
