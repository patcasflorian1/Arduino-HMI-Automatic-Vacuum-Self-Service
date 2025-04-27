#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H
// Constante pentru validare timp
const unsigned long MAX_TIME_COIN = 4500; // Timp maxim permis (1 oră în secunde)
const unsigned long MIN_TIME_COIN = 0;    // Timp minim permis

// Funcție pentru validarea și corecția timpului
unsigned long validateTimeValue(unsigned long timeValue)
{
  // Verificare pentru NAN folosind isnan() din Arduino
  if (isnan(timeValue))
  {
    return 0; // Resetare la 0 dacă este NAN
  }

  // Verificare pentru valori în afara limitelor
  if (timeValue > MAX_TIME_COIN || timeValue < MIN_TIME_COIN)
  {
    return 0; // Resetare la 0 dacă este în afara limitelor
  }

  return timeValue; // Returnare valoare validă
}

#endif // COMMON_FUNCTIONS_H 