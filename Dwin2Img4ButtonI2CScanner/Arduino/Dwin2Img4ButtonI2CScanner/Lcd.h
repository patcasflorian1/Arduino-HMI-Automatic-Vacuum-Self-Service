#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd1(0x27);  // set the LCD address to 0x27 ori 0x3F for a 16 chars and 2 line display
void setupLcd(){
   //set LCD instance
  lcd1.begin(16, 2);
  lcd1.setBacklight(HIGH); 

}


void displayLcd1(int column,int row,String textDisplay){
  lcd1.setCursor(column, row);
  lcd1.print(textDisplay);
}
