#ifndef DS_HAND_STATE_H
#define DS_HAND_STATE_H

#include <Wire.h>
#include <ESP32Servo.h>
#include <DS_Neo_Pixel.h>
#include <Adafruit_INA219.h>
#include <Preferences.h>

#define PIN_THUMB_FINGER    25 
#define PIN_INDEX_FINGER    26
#define PIN_MIDDEL_FINGER   27
#define PIN_RING_FINGER     32
#define PIN_PINKY_FINGER    33

#define LED_PIN     23
#define LED_COUNT   4

class HandState
{
    private:
        /* data */
        Preferences pref;

        DS_Neo_pixel _neo_pixel;

        Adafruit_INA219 _ina219;

        Servo servo_Thumb_Finger;
        Servo servo_Index_Finger;
        Servo servo_Middel_Finger;
        Servo servo_Ring_Finger;
        Servo servo_Pinky_Finger;

        uint8_t minAngle;
        uint8_t maxAngle;
        uint16_t pwmMaxAngle = 1501;
        uint16_t pwmMinAngle = 1001;

        uint8_t ledRGB[2] = {0, 255};

        int8_t angleOpen = 1;
        int8_t angleClose = -1;

        int8_t angleOpenThumb = 1;
        int8_t angleOpenIndex = 1;
        int8_t angleOpenMiddel = 1;
        int8_t angleOpenRing = 1;
        int8_t angleOpenPinky = 1;

        int8_t angleCloseThumb = -1;
        int8_t angleCloseIndex = -1;
        int8_t angleCloseMiddel = -1;
        int8_t angleCloseRing = -1;
        int8_t angleClosePinky = -1;
    
        uint8_t openSpeed = 1;
        uint8_t closeSpeed = 1;
        uint8_t startAngle = 80;

        uint8_t angle = startAngle;
        uint8_t openAngle = 80;
        uint8_t closeAngle = 100;

        int angleFactor;
        
        int angleFactorThumb;
        int angleFactorIndex;
        int angleFactorMiddel;
        int angleFactorRing;
        int angleFactorPinky;

        uint16_t pwmFactor;
        uint8_t angleValue;

        uint16_t pwmValueThumb = 1200;
        uint16_t pwmValueIndex;
        uint16_t pwmValueMiddle;
        uint16_t pwmValueRing;
        uint16_t pwmValuePinky;

        uint8_t stateTest;
        bool goAngle;
    public:
        HandState();
        void begin();
        void updateSensor(char pchar);
        void update();

        void setServo();
        void setServoOpen();
        void setServoClose();

        // get Pwm servo pin finger
        uint16_t get_PwmThumb();
        uint16_t get_PwmIndex();
        uint16_t get_PwmMiddle();
        uint16_t get_PwmRing();
        uint16_t get_PwmPinky();

        //hand physical therapy exercises
        void test_Thumb_Index();
        void test_Index_Middel();
        void test_Ring_Pinky();
        void test_Hand_Contraction();

        void checkState();

        uint8_t stateHand_Support;
        uint8_t stateHand_physical_therapy;
        uint8_t stateHand_Out;
};

#endif