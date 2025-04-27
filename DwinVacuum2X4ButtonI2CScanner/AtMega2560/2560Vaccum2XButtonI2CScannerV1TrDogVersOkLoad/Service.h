//int meniuButton[3] = {5,6,7}; // Meniu,Set, Conta

 void buttonInit()
 {
  for(int i=0;i<3;i++){
     wdt_reset();
    pinMode(meniuButton[i], INPUT);
    digitalWrite(meniuButton[i],HIGH);
    delay(10);
  }
 }