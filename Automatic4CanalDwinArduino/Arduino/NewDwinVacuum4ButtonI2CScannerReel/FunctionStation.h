
elapsedMillis timeElapsedSt1Reel; //declare global if you don't want it reset every time loop runs
unsigned int intervalSt1Reel = 25;
unsigned int timeDelay = 200;

//Set time-price for startProgram
void startProgram(int priceCoin,int selectProgram,int selectReel){
  
     int i = 0;
      while(i < 4){
      if(timeElapsedSt1Reel >= intervalSt1Reel){
       digitalWrite(pinReel[i],LOW);
        i++;
        timeElapsedSt1Reel = 0;
      }
      }
        bool reelState = true;
      while(reelState ==true){
      if(timeElapsedSt1Reel>=timeDelay){
         digitalWrite(pinReel[selectReel],HIGH);
        reelState = false;
        timeElapsedSt1Reel = 0;
      }
      }
      
       switch(selectProgram){ 
         case 0:
         {
          
            totalCoin =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);
            totalTimeCoin = coin*priceCoin;
            if(totalTimeCoin > 30000){
               totalTimeCoin = 60;
                    }
             if(totalTimeCoin <= 0){
               totalTimeCoin = 10;
                    }       
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
     coin = 0;    
         } 
         break;
          case 1:
         {
          
            newCoin = ((float)totalTimeCoin/(float)timeCoin1);
       totalTimeCoin =  newCoin* priceCoin;
       if(totalTimeCoin > 30000){
               totalTimeCoin = 60;
                    }
                if(totalTimeCoin <= 0){
               totalTimeCoin = 10;
                    }      
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
         } 
         break;
         case 2:
         {
          
            newCoin = ((float)totalTimeCoin/(float)timeCoin2);
       totalTimeCoin =  newCoin* priceCoin;
       if(totalTimeCoin > 30000){
               totalTimeCoin = 60;
                    }
                if(totalTimeCoin <= 0){
               totalTimeCoin = 10;
                    }      
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      programSelector=1;
         } 
         break;
               case 3:
         {
          
            newCoin = ((float)totalTimeCoin/(float)timeCoin3);
       totalTimeCoin =  newCoin* priceCoin;
       if(totalTimeCoin > 30000){
               totalTimeCoin = 60;
                    }
                if(totalTimeCoin <= 0){
               totalTimeCoin = 10;
                    }      
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
         } 
         break;
          case 4:
         {
          
            newCoin = ((float)totalTimeCoin/(float)timeCoin4);
       totalTimeCoin =  newCoin* priceCoin;
       if(totalTimeCoin > 30000){
               totalTimeCoin = 60;
                    }
                if(totalTimeCoin <= 0){
               totalTimeCoin = 10;
                    }      
     minuteRamase = totalTimeCoin/60;
     secundeRamase =totalTimeCoin%60;
      
         } 
         break;
       }
        programSelector = selectReel+1;
        keyPinOut = 0;
        digitalWrite(inhibitCoin,HIGH);
  }
//__end void startProgram 


