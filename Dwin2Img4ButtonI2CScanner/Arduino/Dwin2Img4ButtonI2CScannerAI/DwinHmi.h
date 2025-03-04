
void eraseText(int vpAddress,int textLength){
dwinSerial.write(0x5A);  //Header
dwinSerial.write(0xA5);  //Header
dwinSerial.write(3 + textLength);  //Length (3:write,address low and high bytes)
dwinSerial.write(0x82);  //Write command
dwinSerial.write(lowByte(vpAddress));  //write address
dwinSerial.write(highByte(vpAddress));  //write address
for(int i = 0;i<textLength;i ++){
  dwinSerial.write((byte)0x20); //write message (0x20 is ASCII code for space)
}
}
void printf_dwin(uint16_t vp_address,String words)
{
  Serial.print("erase ");Serial.println(erase);
  if(erase == true){
    erase = false;
    //eraseText(0x20, 250);
  }
  int numByte = words.length()+1;
  unsigned char textString[numByte];
  words.toCharArray(textString,numByte);
  dwinSerial.write(0x5A); //Header
   dwinSerial.write(0xA5); //Header
   dwinSerial.write(strlen(textString) + 4); 
   dwinSerial.write(0x82);
   dwinSerial.write(vp_address>>8);
   dwinSerial.write(vp_address);
   dwinSerial.write(0x20);
   dwinSerial.write(textString,strlen(textString));

}
void displayCredit(int coinEnter){
  credit[6] = highByte(coinEnter);
  credit[7]= lowByte(coinEnter);
  dwinSerial.write(credit, 8);
delay(10);
}
void displayTimeHmi(int minutes,int seconds){
  minuteRamaseDisplay[6] = highByte(minutes);
  minuteRamaseDisplay[7]= lowByte(minutes);
  dwinSerial.write(minuteRamaseDisplay, 8);

  secundeRamaseDisplay[6] = highByte(seconds);
  secundeRamaseDisplay[7] = lowByte(seconds);
  dwinSerial.write(secundeRamaseDisplay, 8);
}


void displayPriceAspirat(int priceAspirat,int minutesAspirat,int secondsAspirat){
 // pretAspirat[6] = highByte(priceAspirat);
  pretAspirat[7]= priceAspirat;
  dwinSerial.write(pretAspirat, 8);
//delay(10);
 // pretMinuteAspirat[6] = highByte(minutesAspirat);
  pretMinuteAspirat[7]= minutesAspirat;
  dwinSerial.write(pretMinuteAspirat, 8);
//delay(10);
 // pretSecundeAspirat[6] = highByte(secondsAspirat);
  pretSecundeAspirat[7] = secondsAspirat;
  dwinSerial.write(pretSecundeAspirat, 8);
//delay(10);
}

void displayPriceParfum(int priceParfum,int minutesParfum,int secondsParfum){
 pretParfum[6] = highByte(priceParfum);
  pretParfum[7]= lowByte(priceParfum);
  dwinSerial.write(pretParfum, 8);
//delay(10);
  pretMinuteParfum[6] = highByte(minutesParfum);
  pretMinuteParfum[7]= lowByte(minutesParfum);
  dwinSerial.write(pretMinuteParfum, 8);
//delay(10);
  pretSecundeParfum[6] = highByte(secondsParfum);
  pretSecundeParfum[7] = lowByte(secondsParfum);
  dwinSerial.write(pretSecundeParfum, 8);
//delay(10);
}

void displayPriceNegruCauciuc(int priceNegruCauciuc,int minutesNegruCauciuc,int secondsNegruCauciuc){
 // pretAspirat[6] = highByte(priceAspirat);
  pretNegruCauciuc[7]= priceNegruCauciuc;
  dwinSerial.write(pretNegruCauciuc, 8);
//delay(10);
 // pretMinuteAspirat[6] = highByte(minutesAspirat);
  pretMinuteNegruCauciuc[7]= minutesNegruCauciuc;
  dwinSerial.write(pretMinuteNegruCauciuc, 8);
//delay(10);
 // pretSecundeAspirat[6] = highByte(secondsAspirat);
  pretSecundeNegruCauciuc[7] = secondsNegruCauciuc;
  dwinSerial.write(pretSecundeNegruCauciuc, 8);
//delay(10);
}

void displayPriceAerComp(int priceAerComp,int minutesAerComp,int secondsAerComp){
  //pretAerComprimat[6] = highByte(priceAerComp);
  pretAerComprimat[7]= priceAerComp;
  dwinSerial.write(pretAerComprimat, 8);
//delay(10);
 // pretMinuteAerComprimat[6] = highByte(minutesAerComp);
  pretMinuteAerComprimat[7]= minutesAerComp;
  dwinSerial.write(pretMinuteAerComprimat, 8);
//delay(10);
  //pretSecundeAerComprimat[6] = highByte(secondsAerComp);
  pretSecundeAerComprimat[7] = secondsAerComp;
  dwinSerial.write(pretSecundeAerComprimat, 8);
//delay(10);
}
