#include <DS_BLEHandTask.h>
#include <Arduino.h>

DS_BLEHandTask::DS_BLEHandTask() {}

void DS_BLEHandTask::begin() {
    pinMode(BUTTON_USING_PRACTICE, INPUT_PULLUP);
    pinMode(BUTTON_USING_HAND, INPUT_PULLUP);
    pinMode(BUTTON_CONNECT_PHONE, INPUT_PULLUP);
}



void DS_BLEHandTask::test_TIM() {

}
void DS_BLEHandTask::test_RP() {

}
void DS_BLEHandTask::tesk_All_finger() {
    
}

bool DS_BLEHandTask::getStateButtonU_P() {
    return digitalRead(BUTTON_USING_PRACTICE);
}
bool DS_BLEHandTask::getStateButtonU_H() {
    return digitalRead(BUTTON_USING_HAND);
}
bool DS_BLEHandTask::getStateButtonC_P() {
    return digitalRead(BUTTON_CONNECT_PHONE);
}


bool DS_BLEHandTask::getUsingHand() {
    return usingHand;
}
bool DS_BLEHandTask::getConnectPhone() {
    return connectPhone;
}
bool DS_BLEHandTask::getUsingPractice() {
    return usingPractice;
}


void DS_BLEHandTask::setUsingHand(bool _data) {
    usingHand = _data;
}
void DS_BLEHandTask::setConnectPhone(bool _data) {
    connectPhone = _data;
}
void DS_BLEHandTask::setUsingPractice(bool _data) {
    usingPractice = _data;
}