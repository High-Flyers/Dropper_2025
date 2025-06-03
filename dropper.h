#include <ESP32Servo.h>

#include "params.h"

Servo _servo1, _servo2, _servo3, _servo4;

uint8_t _getBeaconNumber();

uint8_t map_beacon_pins [4] = {18, 20, 19, 17};
bool beacon_state [4];
bool beacon_last_state [4]; 

uint8_t drop_nr = 0;

// Inicjalizacja
void dropper_attach() {
    pinMode(BEACON_1_DETECT, INPUT);
    pinMode(BEACON_2_DETECT, INPUT);
    pinMode(BEACON_3_DETECT, INPUT);
    pinMode(BEACON_4_DETECT, INPUT);

    _servo1.setPeriodHertz(50);
    _servo2.setPeriodHertz(50);
    _servo3.setPeriodHertz(50);
    _servo4.setPeriodHertz(50);

    pinMode(SERVO_1, OUTPUT);
    pinMode(SERVO_2, OUTPUT);
    pinMode(SERVO_3, OUTPUT);
    pinMode(SERVO_4, OUTPUT);
}

// Detekcja obecnosci i ewentualne zamkniecie
void dropper_close(){
  //
  for(int i = 0; i < 4; i++){
    beacon_last_state[i] = beacon_state[i];
    beacon_state[i] = digitalRead(map_beacon_pins[i]);
  }
  // Servo 1
  if(!beacon_state[0] && beacon_last_state[0]){
    delay(500);
    _servo1.attach(SERVO_1);
    _servo1.writeMicroseconds(LOCKED_SERVO_US);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    _servo1.detach();
    Serial.println("ARMED: 1");
    drop_nr = 0;
  }
  // Servo 2
  if(!beacon_state[1] && beacon_last_state[1]){
    delay(500);
    _servo2.attach(SERVO_2);
    _servo2.writeMicroseconds(LOCKED_SERVO_US);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    _servo2.detach();
    Serial.println("ARMED: 2");
    drop_nr = 0;
  }
  // Servo 3
  if(!beacon_state[2] && beacon_last_state[2]){
    delay(500);
    _servo3.attach(SERVO_3);
    _servo3.writeMicroseconds(LOCKED_SERVO_US);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    _servo3.detach();
    Serial.println("ARMED: 3");
    drop_nr = 0;
  }
  // Servo 4
  if(!beacon_state[3] && beacon_last_state[3]){
    delay(500);
    _servo4.attach(SERVO_4);
    _servo4.writeMicroseconds(LOCKED_SERVO_US);
   vTaskDelay(100 / portTICK_PERIOD_MS);
    _servo4.detach();
    Serial.println("ARMED: 4");
    drop_nr = 0;
  }
}

// Zrzut MSK
void dropper_drop() {
    //uint8_t availableBeacon = _getBeaconNumber();
    switch (drop_nr) {
        case 1:
            _servo1.attach(SERVO_1);
            _servo1.writeMicroseconds(UNLOCKED_SERVO_US);
            log_i("Dropped beacon: 1");
            vTaskDelay(DROP_TIMEOUT / portTICK_PERIOD_MS);
            _servo1.detach();
            break;
        case 2:
            _servo2.attach(SERVO_2);
            _servo2.writeMicroseconds(UNLOCKED_SERVO_US);
            log_i("Dropped beacon: 2");
            vTaskDelay(DROP_TIMEOUT / portTICK_PERIOD_MS);
            _servo2.detach();
            break;
        case 3:
            _servo3.attach(SERVO_3);
            _servo3.writeMicroseconds(UNLOCKED_SERVO_US);
            log_i("Dropped beacon: 3");
            vTaskDelay(DROP_TIMEOUT / portTICK_PERIOD_MS);
            _servo3.detach();
            break;
        case 4:
            _servo4.attach(SERVO_4);
            _servo4.writeMicroseconds(UNLOCKED_SERVO_US);
            log_i("Dropped beacon: 4");
            vTaskDelay(DROP_TIMEOUT / portTICK_PERIOD_MS);
            _servo4.detach();
            break;
        default:
            log_e("No beacons present. Cannot drop...");
            break;
    }
}

uint8_t  _getBeaconNumber() {
    if (digitalRead(BEACON_1_DETECT) == LOW) {
        return 1;
    }
    if (digitalRead(BEACON_2_DETECT) == LOW) {
        return 2;
    }
    if (digitalRead(BEACON_3_DETECT) == LOW) {
        return 3;
    }
    if (digitalRead(BEACON_4_DETECT) == LOW) {
        return 4;
    }

    return 0;
}