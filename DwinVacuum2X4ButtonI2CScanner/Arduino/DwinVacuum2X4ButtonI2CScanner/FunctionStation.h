
elapsedMillis timeElapsedSt1Reel; //declare global if you don't want it reset every time loop runs
unsigned int intervalSt1Reel = 95;
unsigned int timeDelay = 500;

//Set time-price for startProgram
void startProgram(int priceCoin,int selectProgram,int selectReel){
     int i = 0;
      if((coin>0)||(totalTimeCoin>0)){
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
     oldCoin = 0;
     displayCredit(coin);        
         } break;
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
      
         } break;
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
        programSelector = keyPinOut;
        keyPinOut = 0;
       }
  }
//__end void startProgram 
//Start Prog St2
//Set time-price for startProgram
void startProgramSt2(int priceCoin,int selectProgramSt2,int selectReel){
     int i = 4; 
     if((coin>0)||(totalTimeCoinSt2>0)){   
      while(i < 8){
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
      
       switch(selectProgramSt2){ 
         case 0:
         {     
           totalCoin  =  EEPROM.get(totalCoins,totalCoin);
          totalCoin = totalCoin+coin;
          EEPROM.put(totalCoins,totalCoin);           
            totalTimeCoinSt2 = coin*priceCoin;
            if(totalTimeCoinSt2 > 30000){
               totalTimeCoinSt2 = 60;
                    }
             if(totalTimeCoinSt2 <= 0){
               totalTimeCoinSt2 = 10;
                    }       
     minuteRamaseSt2 = totalTimeCoinSt2/60;
     secundeRamaseSt2 =totalTimeCoinSt2%60;
     coin = 0;
     oldCoin = 0;
     displayCredit(coin); 
         } break;
          case 1:
         {
          
            newCoin = ((float)totalTimeCoinSt2/(float)timeCoin1);
       totalTimeCoinSt2 =  newCoin* priceCoin;
       if(totalTimeCoinSt2 > 30000){
               totalTimeCoinSt2 = 60;
                    }
                if(totalTimeCoinSt2 <= 0){
               totalTimeCoinSt2 = 10;
                    }      
     minuteRamaseSt2 = totalTimeCoinSt2/60;
     secundeRamaseSt2 =totalTimeCoinSt2%60;
         } 
         break;
         case 2:
         {
          
            newCoin = ((float)totalTimeCoinSt2/(float)timeCoin2);
       totalTimeCoinSt2 =  newCoin* priceCoin;
       if(totalTimeCoinSt2 > 30000){
               totalTimeCoinSt2 = 60;
                    }
                if(totalTimeCoinSt2 <= 0){
               totalTimeCoinSt2 = 10;
                    }      
     minuteRamaseSt2 = totalTimeCoinSt2/60;
     secundeRamaseSt2 =totalTimeCoinSt2%60;
      
         } break;
               case 3:
                {
            newCoin = ((float)totalTimeCoinSt2/(float)timeCoin3);
       totalTimeCoinSt2 =  newCoin* priceCoin;
       if(totalTimeCoinSt2 > 30000){
               totalTimeCoinSt2 = 60;
                    }
                if(totalTimeCoinSt2 <= 0){
               totalTimeCoinSt2 = 10;
                    }      
     minuteRamaseSt2 = totalTimeCoinSt2/60;
     secundeRamaseSt2 =totalTimeCoinSt2%60;
         } 
         break;
          case 4:
         {
          
            newCoin = ((float)totalTimeCoinSt2/(float)timeCoin4);
       totalTimeCoinSt2 =  newCoin* priceCoin;
       if(totalTimeCoinSt2 > 30000){
               totalTimeCoinSt2 = 60;
                    }
                if(totalTimeCoinSt2 <= 0){
               totalTimeCoinSt2 = 10;
                    }      
     minuteRamaseSt2 = totalTimeCoinSt2/60;
     secundeRamaseSt2 =totalTimeCoinSt2%60;
      
         } 
         break;
       }
        programSelectorSt2 = keyPinOutSt2;
        keyPinOutSt2 = 0;
     }
  }

 