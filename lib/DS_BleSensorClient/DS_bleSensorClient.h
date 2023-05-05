#ifndef DS_BLE_SENSOR_CLIENT_H
#define DS_BLE_SENSOR_CLIENT_H

#include <BLEDevice.h>
#include <BLEUUID.h>
#include <Preferences.h>
#include <DS_Neo_Pixel.h>

#define SERVICE_UUID "bdd651e8-dbc0-11ed-afa1-0242ac120002"

#define SENSOR_LEG_CONTROL_UUID      "09ffd5e8-dbb3-11ed-afa1-0242ac120002"
#define CHANGE_NAME_SENSOR_UUID      "ba1b0f58-e322-11ed-b5ea-0242ac120002"
#define NOTIFY_BATTERY_UUID          "9906b416-e359-11ed-b5ea-0242ac120002"


static char SENSOR_SERVER[] = "SENSOR_LEG";
static bool deviceConnected = false;
static bool oldDeviceConnected = false;
static Preferences pref;

class DS_bleSensorClient {

    public:
        DS_bleSensorClient();
        void begin();
        void setUpBle();
        void checkControl(uint8_t* _data);
        void checkStop(uint8_t* _data);
        void checkPower(uint16_t* _data);


        void ledAdv();
        void ledConnectedBle();
        void disconnectedBle();
        void replayAdv();
        void updateConnect();

        
    private:
    /* data */
        
        DS_Neo_pixel _Neo_Pixel;
        BLEServer* pServer = NULL;
        BLECharacteristic* sensorLegCT = NULL;
        BLECharacteristic* changeName = NULL;
        BLECharacteristic* notifyBattery = NULL;
        
        uint32_t lastSendMillis = millis();
        uint32_t lastStopMillis = millis();
        // led RGB
        uint8_t ledRGB[2] = {0, 250};

};

#endif