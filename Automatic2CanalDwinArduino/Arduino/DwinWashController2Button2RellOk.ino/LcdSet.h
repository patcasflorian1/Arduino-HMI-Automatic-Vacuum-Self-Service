

LiquidCrystal_PCF8574 lcd(0x26);  // set the LCD address to 0x26 ori 0x3F for a 20 chars and 4 line display
LiquidCrystal_PCF8574 lcd1(0x27);  // set the LCD address to 0x27 ori 0x3F for a 16 chars and 2 line display

void lcdBegin(){
  //set LCD instance
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH); 
  lcd.setCursor(0, 0);
  lcd.print("Auto WashClean ");
  lcd.setCursor(0, 1);
  lcd.print(" V 1.00EE ");
 
  
  lcd1.begin(20, 4);
  lcd1.setBacklight(HIGH); 
  lcd1.setCursor(0, 0);
  lcd1.print("WashCleanForTr");
  lcd1.setCursor(0, 1);
  lcd1.print("Sn02B2-08/24 "); //(SerialNr - Luna/an Tip)
  delay(3000); 
  lcd.clear();
  lcd1.clear();
}

void lcdDisplay(uint8_t col,uint8_t row,String text){
  lcd.setCursor( col, row);
  lcd.print(text);
}

void lcd1Display(uint8_t col,uint8_t row,String text){
  lcd1.setCursor( col, row);
  lcd1.print(text);
}
void displayPrice(){
//Pret1 display
    lcd.setCursor(0,0);
  lcd.print("Prog1:1RON=");
  lcd.setCursor(11,0);
  lcd.print(timeCoin/60);
   lcd.print("M"); 
  lcd.setCursor(13,0);  
  lcd.print(",");
  lcd.setCursor(14,0);
   if((timeCoin%60)>10){
    lcd.print(timeCoin%60);
  }
  else{
    lcd.print("0");
    lcd.print(timeCoin%60);
  }
   //Pret2 display
  lcd.setCursor(0,1);
  lcd.print("Prog2:1RON=");
  lcd.setCursor(11,1);
  lcd.print(timeCoin2/60); 
  lcd.print("M");
  lcd.setCursor(13,1);  
  lcd.print(",");
  lcd.setCursor(14,1);
  if((timeCoin2%60)>10){
    lcd.print(timeCoin2%60);
  }
  else{
    lcd.print("0");
    lcd.print(timeCoin2%60);
  }

}