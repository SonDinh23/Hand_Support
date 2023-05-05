#include <DS_bleHandClient.h>
#include <Arduino.h>

DS_bleHandClient::DS_bleHandClient() {

}

void DS_bleHandClient::setUp() {
    
}

void DS_bleHandClient::begin() {
    class MyServerCallbacks: public BLEServerCallbacks {
        void onConnect(BLEServer* pServer) {
            deviceConnected = true;
        };
        void onDisconnect(BLEServer* pServer) {
            deviceConnected = false;
        }
    };

    BLEDevice::init(HAND_CLIENT);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService* handService = pServer->createService(SERVICE_UUID);
    changeWifi = handService->createCharacteristic(CHANGEWIFI_UUID, BLECharacteristic::PROPERTY_NOTIFY);
    // sensorLegCT->addDescriptor(new BLE2902());

    handService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // set value to 0x00 to not advertise this parameter
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    //Serial.println("Waiting a client connection to notify...");
    uint8_t data = 2;
    for (;;) {
        if (deviceConnected) {
            //Serial.println("connected access");
            changeWifi->setValue((uint8_t*)&data, 1);
            changeWifi->notify();
            delay(100); 
        }
        // disconnecting
        if (!deviceConnected && oldDeviceConnected) {
            //delay(500); // give the bluetooth stack the chance to get things ready
            pServer->startAdvertising(); // restart advertising
            //Serial.println("start advertising");
            oldDeviceConnected = deviceConnected;
        }
    // connecting
        if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
            oldDeviceConnected = deviceConnected;
        }
    }
}