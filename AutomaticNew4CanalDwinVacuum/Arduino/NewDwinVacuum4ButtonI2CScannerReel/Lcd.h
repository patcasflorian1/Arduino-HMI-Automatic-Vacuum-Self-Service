#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x26);  // set the LCD address to 0x26 ori 0x3F for a 20 chars and 4 line display
LiquidCrystal_PCF8574 lcd1(0x27);  // set the LCD address to 0x27 ori 0x3F for a 16 chars and 2 line display
void setupLcd(){
   //set LCD instance
  lcd.begin(20, 4);
  lcd.setBacklight(HIGH); 
  lcd1.begin(16, 2);
  lcd1.setBacklight(HIGH); 

}
void displayLcd(int column,int row,String textDisplay){
  lcd.setCursor(column, row);
  lcd.print(textDisplay);
}

void displayLcd1(int column,int row,String textDisplay){
  lcd1.setCursor(column, row);
  lcd1.print(textDisplay);
}

void displayPrice(){
       displayLcd(0,0,"Pr1:1RON=");
     displayLcd(9,0,String(timeCoin1/60)+":");
      if((timeCoin1%60)>10){
    displayLcd(11,0,String(timeCoin1%60)+"mm:ss");
  }
 else{
    displayLcd(11,0,"0"+String(timeCoin1%60)+"mm:ss");
 }

      displayLcd(0,1,"Pr2:1RON=");
     displayLcd(9,1,String(timeCoin2/60)+":");
     
  if((timeCoin2%60)>10){    
    displayLcd(11,1,String(timeCoin2%60)+"mm:ss");
 }
  else{
    displayLcd(11,1,"0"+String(timeCoin2%60)+"mm:ss");
  }
        displayLcd(0,2,"Pr3:1RON=");
    displayLcd(9,2,String(timeCoin3/60)+":");    
  if((timeCoin3%60)>10){    
    displayLcd(11,2,String(timeCoin3%60)+"mm:ss");
  }
  else{
    displayLcd(11,2,"0"+String(timeCoin3%60)+"mm:ss");
  }
        displayLcd(0,3,"Pr4:1RON=");
     displayLcd(9,3,String(timeCoin4/60)+":");     
  if((timeCoin4%60)>10){    
    displayLcd(11,3,String(timeCoin4%60)+"mm:ss");
  }
  else{
    displayLcd(11,3,"0"+String(timeCoin4%60)+"mm:ss");
  }
}