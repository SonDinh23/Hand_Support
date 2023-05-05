#include <DS_handstate.h>

HandState::HandState() {}

void HandState::begin() {
    if (!_ina219.begin()) {
        Serial.println("Failed to find INA219 chip");
    }
    pref.begin("hand-info", false);

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    servo_Thumb_Finger.attach(PIN_THUMB_FINGER);
    servo_Index_Finger.attach(PIN_INDEX_FINGER);
    servo_Middel_Finger.attach(PIN_MIDDEL_FINGER);
    servo_Ring_Finger.attach(PIN_RING_FINGER);
    servo_Pinky_Finger.attach(PIN_PINKY_FINGER);

    delay(10);

    // minAngle = pref.getUShort("minAngle", minAngle);
	// maxAngle = pref.getUShort("maxAngle", maxAngle);
    // startAngle = ((maxAngle + minAngle)/2);

    // minAnglePwm = pref.getUShort("minAnglePwm", minAnglePwm);
    // maxAnglePwm = pref.getUShort("maxAnglePwm", maxAnglePwm);

    _neo_pixel.setBright(100);
    for (int i = 0; i < 3; i++) {
        _neo_pixel.showPixel(i, ledRGB[0], ledRGB[0], ledRGB[0]);
        delay(1);
    }
    _neo_pixel.showPixel(3, ledRGB[1], ledRGB[1], ledRGB[1]);
}

void HandState::updateSensor(char pchar) {
    switch (pchar)
    {
        case 'a':
            {
                // Serial.println("Open");
                goAngle = true;
                angleFactor = angleOpen * openSpeed;

                angleFactorThumb = angleOpenThumb * openSpeed;
                angleFactorIndex = angleOpenIndex * openSpeed;
                angleFactorMiddel = angleOpenMiddel * openSpeed;
                angleFactorRing = angleOpenRing * openSpeed;
                angleFactorPinky = angleOpenPinky * openSpeed;
                _neo_pixel.showPixel(0, ledRGB[0], ledRGB[1], ledRGB[0]);
                break;
            }
        
        case 'b':
            {
                // Serial.println("CLose");
                goAngle = true;
                angleFactor = angleClose * closeSpeed;

                angleFactorThumb = angleCloseThumb * closeSpeed;
                angleFactorIndex = angleCloseIndex * closeSpeed;
                angleFactorMiddel = angleCloseMiddel * closeSpeed;
                angleFactorRing = angleCloseRing * closeSpeed;
                angleFactorPinky = angleClosePinky * closeSpeed;
                _neo_pixel.showPixel(0, ledRGB[0], ledRGB[0], ledRGB[1]);
                break;
            }
        case 'c':
            {
                // Serial.println("Stop");
                goAngle = false;
                angleFactor = 0;
                angleFactorThumb = 0;
                angleFactorIndex = 0;
                angleFactorMiddel = 0;
                angleFactorRing = 0;
                angleFactorPinky = 0;
                _neo_pixel.showPixel(0, ledRGB[0], ledRGB[0], ledRGB[0]);
                break;
            }
    default:
        // Serial.println("Stop");
        goAngle = false;
        angleFactor = 0;
        angleFactorThumb = 0;
        angleFactorIndex = 0;
        angleFactorMiddel = 0;
        angleFactorRing = 0;
        angleFactorPinky = 0;
        break;
    }
}

void HandState::update() {
    setServo();
}

void HandState::setServo() {
    static bool stateDetach;
    // pwmValueThumb = get_PwmThumb();
    // pwmValueIndex = get_PwmIndex();
    // pwmValueMiddle = get_PwmMiddle();
    // pwmValueRing = get_PwmRing();
    // pwmValuePinky = get_PwmPinky();
    if (goAngle) {
        
        pwmValueThumb = constrain(pwmValueThumb + angleFactorThumb, pwmMinAngle, pwmMaxAngle);
        pwmValueIndex = constrain(pwmValueIndex + angleFactorIndex, pwmMinAngle, pwmMaxAngle);
        pwmValueMiddle = constrain(pwmValueMiddle + angleFactorMiddel, pwmMinAngle, pwmMaxAngle);
        pwmValueRing = constrain(pwmValueRing + angleFactorRing, pwmMinAngle, pwmMaxAngle);
        pwmValuePinky = constrain(pwmValuePinky + angleFactorPinky, pwmMinAngle, pwmMaxAngle);
        // pwmValueThumb +=angleFactorThumb;
        Serial.print("Angle:\t");
        Serial.print(angleFactorThumb);
        Serial.print("\tThumb:\t");
        Serial.print(pwmValueThumb);
        Serial.print("\t");
        vTaskDelay(5);
        stateDetach = true;
    }else {
        stateDetach = false;
    }
    if(stateDetach) {
        Serial.println("Angle");
        servo_Thumb_Finger.writeMicroseconds(pwmValueThumb);
        servo_Thumb_Finger.writeMicroseconds(pwmValueThumb);
        servo_Thumb_Finger.writeMicroseconds(pwmValueThumb);
        servo_Thumb_Finger.writeMicroseconds(pwmValueThumb);
        servo_Thumb_Finger.writeMicroseconds(pwmValueThumb);
        vTaskDelay(5);
    }
}

void HandState::setServoClose() {

}

void HandState::setServoOpen() {

}

uint16_t HandState::get_PwmThumb() {
    uint16_t pwm = servo_Thumb_Finger.readMicroseconds();
    return 1200;
}

uint16_t HandState::get_PwmIndex() {
    uint16_t pwm = servo_Index_Finger.readMicroseconds();
    return pwm;
}

uint16_t HandState::get_PwmMiddle() {
    uint16_t pwm = servo_Middel_Finger.readMicroseconds();
    return pwm;
}

uint16_t HandState::get_PwmRing() {
    uint16_t pwm = servo_Ring_Finger.readMicroseconds();
    return pwm;
}

uint16_t HandState::get_PwmPinky() {
    uint16_t pwm = servo_Pinky_Finger.readMicroseconds();
    return pwm;
}

void HandState::checkState() {
  
}