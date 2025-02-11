
//interrupt
void coinInterrupt() {
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