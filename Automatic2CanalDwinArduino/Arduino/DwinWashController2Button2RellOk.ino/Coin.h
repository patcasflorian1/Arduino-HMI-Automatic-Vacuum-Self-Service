



//interrupt
void coinInterrupt() {
while(digitalRead(coinPin) == LOW){
  if(timeCoinElapse>60){ 
 
     coin ++ ;
     timeCoinElapse = 0;
   // lcdOk=true;
     if(coin>limitCoin){
      digitalWrite(inhibitCoin,HIGH);
     }
     else{
      digitalWrite(inhibitCoin,LOW);
     }
    }
   }
 }
