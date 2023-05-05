#include <Arduino.h>
#include <DS_RF24L01.h>

#define NRF_CE  25
#define NRF_CS  15

#define OPEN_PIN    2
#define CLOSE_PIN   3

#define LED     27

byte ADDRESS_TX[6] = "A0000";
byte ADDRESS_RX[6] = "ZZZZZ";

char data[3] = {'a', 'b', 'c'};

bool onSetup = true;
SPIClass spiNrf(HSPI);
RF rf(NRF_CE, NRF_CS);

void send_Stop();
void send_Open();
void send_Close();

void send_Stop() {
    // for (int i = 0; i < 20 && digitalRead(OPEN_PIN) == 1 && digitalRead(CLOSE_PIN) == 1; i++) {
    // rf.sendData(&data[2], 1);
    // digitalWrite(8, HIGH);
    // }

    if (digitalRead(OPEN_PIN) == 1 && digitalRead(CLOSE_PIN) == 1) {
        rf.sendData(&data[2], 1);
    }
}

void send_Open() {
    digitalWrite(LED, HIGH);
    onSetup = false;
    rf.sendData(&data[0], 1);
    digitalWrite(LED, LOW);
    send_Stop();
}

void send_Close() {
    digitalWrite(LED, HIGH);
    onSetup = false;
    rf.sendData(&data[1], 1);
    digitalWrite(LED, LOW);
    send_Stop();
}

void setup() {
    Serial.begin(115200);
    
    rf.begin(ADDRESS_TX, ADDRESS_RX, &spiNrf, false);
    Serial.println("oke");
    pinMode(33,OUTPUT);
    // attachInterrupt(0, send_Open, LOW);
    // attachInterrupt(1, send_Close, LOW); 

    // pinMode(LED, OUTPUT);
    // pinMode(OPEN_PIN, INPUT_PULLUP);
    // pinMode(CLOSE_PIN, INPUT_PULLUP);

    // while (onSetup) {
    //     digitalWrite(LED, HIGH);
    //     delay(200);
    //     digitalWrite(LED, LOW);
    //     delay(200);
    // }
    // digitalWrite(LED, LOW);
}

void loop() {
    // attachInterrupt(0, send_Open, LOW);
    // attachInterrupt(1, send_Close, LOW);  
    // attachInterrupt(0, send_Open, LOW);
    // attachInterrupt(1, send_Close, LOW); 
    
    delay(500);  
    digitalWrite(33,HIGH);
    //Serial.println(rf.readData());
    rf.sendData(&data[1], 1);
    Serial.println(data[1]);
    delay(300);
    digitalWrite(33,LOW);
    delay(300);
}