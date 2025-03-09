//interrupt
void coinInterrupt() {
  limitCoin =  EEPROM.get(coinLimitZone,limitCoin);
while(digitalRead(coinPin) == LOW){
  if(coin>limitCoin){
      digitalWrite(inhibitCoin,HIGH);
     }
     else{
      digitalWrite(inhibitCoin,LOW);
       
     }
  if(timeCoinElapse>60){ 
 
     coin ++ ;
     timeCoinElapse = 0;
    }
   }
 }

/*
 //interrupt
void coinInterrupt() {
  

  limitCoin =  EEPROM.get(coinLimitZone,limitCoin);
// Serial.print("TimeCoin1 "); Serial.println(timeCoinMill);
while((digitalRead(coinPin) == LOW)||(timeCoinMill<50)){
    timeCoinMill++;
   // Serial.print("TimeCoin "); Serial.println(timeCoinMill);
}
  if((timeCoinMill>60)&&(digitalRead(coinPin) == HIGH)){ 
 
    coin ++ ;
    timeCoinMill = 0;
    digitalWrite(coinPin,HIGH);
     if(coin>limitCoin){
      digitalWrite(inhibitCoin,HIGH);
     }
     else{
      digitalWrite(inhibitCoin,LOW);
       
     }

  // Serial.println(coin);
 // Serial.println();
      insert = true;
}
  }
*/