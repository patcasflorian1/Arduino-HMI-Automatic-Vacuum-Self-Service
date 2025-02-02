
void led(){
     if((timeElapsedLux>intervalLux)&&(luxOk==true)){
   
      
     
      digitalWrite(ledOutput,LOW);
       digitalWrite(ledOutput2,HIGH);
       luxOk = false;
      timeElapsedLux=0;
    }
        if((timeElapsedLux>intervalLux)&&(luxOk==false)){
     
      digitalWrite(ledOutput,HIGH);
      digitalWrite(ledOutput2,LOW);
      luxOk=true;
      timeElapsedLux=0;
    }
}