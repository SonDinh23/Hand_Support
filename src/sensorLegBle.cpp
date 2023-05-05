#include <Arduino.h>
#include <DS_bleSensorClient.h>

#define BATTERY       35
#define BUTTON_OPEN   32
#define BUTTON_CLOSE  33
#define LED           25

#define MAX_BATTERY   4200 
#define MIN_BATTERY   3300

#define BUTTON_PIN_BITMASK 0x300000000  // 2^pin + ...

uint32_t lastTime = 0;
uint16_t timerDelay = 1000;
uint32_t lastTimeSleep = millis();
uint8_t stateSleep = 0;
bool setUp = true;
DS_bleSensorClient _BleSensorClient;
                            
void battery_Alarm();
void sendStop();
void IRAM_ATTR sendOpen();
void IRAM_ATTR sendClose();
void checkSleep();

uint8_t data[3] = {1, 2, 3};

void setup() {
    Serial.begin(115200);
    _BleSensorClient.begin();
    _BleSensorClient.setUpBle();
    pinMode(BUTTON_OPEN, INPUT_PULLUP);
    pinMode(BUTTON_CLOSE, INPUT_PULLUP);
    // pinMode(LED, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON_OPEN), sendOpen, ONLOW);
    attachInterrupt(digitalPinToInterrupt(BUTTON_CLOSE), sendClose, ONLOW);

    // while(setUp) {
    //   Serial.println("Chua1");
    //   digitalWrite(LED, HIGH);
    //   delay(300);
    //   digitalWrite(LED, LOW);
    //   delay(300);
    // }
}

void loop() {
  // Serial.println(digitalRead(BUTTON_OPEN));
  // attachInterrupt(BUTTON_OPEN, sendOpen, ONLOW);
  
  // attachInterrupt(BUTTON_CLOSE, sendClose, LOW);
  //checkSleep();
  // _BleSensorClient.checkControl(&data[0]);
  _BleSensorClient.checkPower(&timerDelay);
}

void IRAM_ATTR sendOpen() {
  // ets_printf("OPEN\n");
  stateSleep = 0;
  setUp = false;
  _BleSensorClient.checkControl(&data[0]);
  sendStop();
}

void IRAM_ATTR sendClose() {
  // ets_printf("CLOSE\n");
  stateSleep = 0;
  setUp = false;
  _BleSensorClient.checkControl(&data[1]);
  sendStop();
}

void sendStop() {
  for (uint8_t i = 0; i < 20 && (digitalRead(BUTTON_OPEN)) && (digitalRead(BUTTON_CLOSE)) ;i++) {
    ets_printf("OPEN\n");
    _BleSensorClient.checkStop(&data[2]);
    digitalWrite(LED, HIGH);
  }
}

void checkSleep() {
  if (millis() - lastTimeSleep > 1000) {
    stateSleep++;
    lastTimeSleep = millis();
  }

  if (stateSleep == 20) {
    esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ALL_LOW);
    Serial.println("Going to sleep now");
    delay(100);
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
  }
}

void battery_Alarm() {
  static uint16_t Vin = analogRead(BATTERY);
  uint16_t battery = (Vin - MIN_BATTERY) / (MAX_BATTERY - MIN_BATTERY) * 100;
  battery = constrain(battery, 0, 100);
  if (battery < 20) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
  _BleSensorClient.checkPower(&battery);
}


