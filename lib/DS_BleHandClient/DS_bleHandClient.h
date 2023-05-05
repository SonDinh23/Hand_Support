#ifndef DS_BLE_HAND_CLIENT_H
#define DS_BLE_HAND_CLIENT_H

#include <BLEDevice.h>
#include <BLEUUID.h>
#include <Preferences.h>
// #include <DS_Neo_Pixel.h>

// #define HAND_SUPPORT "Hand_Support"

#define SERVICE_UUID                "30bafc7f-b22e-4261-be57-f6a4d07ebd09"

#define CHANGEWIFI_UUID             "2e15a1d6-e213-11ed-b5ea-0242ac120002"
#define NOTIFY_BATTERY_UUID         "a8713c0b-c86b-4949-9439-d996d48193fe"
#define CHANGE_NAME_UUID            "cd7bb15e-e4d2-11ed-b5ea-0242ac120002"
#define SPEED_HAND_UUID             "d9117792-e4d2-11ed-b5ea-0242ac120002"
#define CHANGE_LED_RGB_UUID         "dd49d034-e4d2-11ed-b5ea-0242ac120002"

#define NOTIFY_TARGET_SET_UUID          "05a1103a-e805-11ed-a05b-0242ac120003"
#define NOTIFY_LOGIC_PRACTICE_UUID      "09c78d4c-e805-11ed-a05b-0242ac120003"
#define NOTIFY_SPEED_PRACTICE_UUID      "0dd4410a-e805-11ed-a05b-0242ac120003"    

#define NOTIFY_RECOVER_UUID              "3b4d0cb8-e803-11ed-a05b-0242ac120003"
#define NOTIFY_PRACTICE_TIM_UUID         "935e5124-e802-11ed-a05b-0242ac120003"
#define NOTIFY_PRACTICE_RP_UUID          "9a3a8d82-e802-11ed-a05b-0242ac120003"
#define NOTIFY_PRACTICE_ALL_F_UUID       "9f61ce56-e802-11ed-a05b-0242ac120003"
#define CHANGE_TARGET_SET_UUID           "bd64fe6e-e802-11ed-a05b-0242ac120003"
#define CHANGE_LOGIC_PRACTICE_UUID       "d8572454-e802-11ed-a05b-0242ac120003"
#define CHANGE_SPEED_PRACTICE_UUID       "f56e8668-e802-11ed-a05b-0242ac120003"

static char HAND_CLIENT[] = "HAND_DS";
static char ssid_Wifi[] = "BO DAM CHO";
static char password_Wifi[] = "0902kochoddau795hoilamgif5570mowddi";
static char speed_Hand[] = "5";
static char change_LedRGB[] = "1";

static char change_TargetSet[] = "100";

static bool deviceConnected = false;
static bool oldDeviceConnected = false; 
static Preferences pref;

class DS_bleHandClient {
    public:
        DS_bleHandClient(/* args */);
        void setUp();
        void begin();
        
        void checkPowerBle(uint16_t* _data);
        void checkRecover(uint8_t* _data);
        void check_Pr_All_F(uint16_t* _data);
        void check_Pr_RP(uint16_t* _data);
        void check_Pr_TIM(uint16_t* _data);
    private:
        // DS_Neo_pixel _Neo_Pixel;

        BLEServer* pServer =                NULL;
        BLECharacteristic* changeWifi =     NULL;
        BLECharacteristic* changeName =     NULL;
        BLECharacteristic* notifyBattery =  NULL;
        BLECharacteristic* logicHand =      NULL;
        BLECharacteristic* speedHand =      NULL;

        BLECharacteristic* notifyRecover =      NULL;
        BLECharacteristic* practiceAll_F =      NULL;
        BLECharacteristic* practiceRP =         NULL;
        BLECharacteristic* practiceTIM =        NULL;

        BLECharacteristic* targetSetPractice =      NULL;      
        BLECharacteristic* logicPractice =          NULL; 
        BLECharacteristic* speedPractice =          NULL;   

        BLECharacteristic* targetSetNotify =        NULL;      
        BLECharacteristic* logicPrNotify =          NULL; 
        BLECharacteristic* speedPrNotify =          NULL; 

        uint32_t lastSendMillis = millis();
        uint32_t lastStopMillis = millis();
        // led RGB
        uint8_t ledRGB[2] = {0, 250};
};


#endif