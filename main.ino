#include "dropper.h"

uint16_t pwm_val = 0, pwm_last_val = 0;
bool wait = false;

// Flaga - wysoki PWM (2000)
bool checkPwm (){ 
  if ((pwm_val > 1800 && pwm_val < 2200)){
    return true;
  }
  return false;
}

void setup() {
  // Inicjalizacja modulu zrzutu
  dropper_attach();
  // Pin do nasluchu PWM
  pinMode(PWM_IN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Odczyt wypelnienia PWM
  pwm_val = pulseIn(PWM_IN, HIGH);
  // Sprawdzenie i ewentualne zamkniecie komor
  dropper_close();
  // Zrzut MSK
  if(checkPwm() && !wait){
    wait = !wait;
    drop_nr++;
    printf("DROP: %d\n", drop_nr);
    dropper_drop();
    delay(DROP_TIMEOUT);
  }
  // Zabezpieczenie przed zrzutem kolejnego
  if(pwm_val > 800 && pwm_val < 1200 && wait)
    wait = !wait;
  //Serial.println(wait);
  delay(100);
}