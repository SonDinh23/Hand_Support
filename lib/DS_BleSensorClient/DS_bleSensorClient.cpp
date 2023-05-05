#include <DS_bleSensorClient.h>
#include <Arduino.h>
DS_bleSensorClient::DS_bleSensorClient() {}

static void readPrefName() {
    pref.putString("Name", SENSOR_SERVER);
    
}

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer) {
        deviceConnected = true;
    };
    void onDisconnect(BLEServer *pServer) {
        deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        strcpy(SENSOR_SERVER, value.c_str());
        if (value.length() > 0) {
            Serial.println("*********");
            Serial.print("New value: ");
            for (int i = 0; i < value.length(); i++)
                Serial.print(value[i]);

            Serial.println();
            Serial.println("*********");
            Serial.println(SENSOR_SERVER);
            readPrefName();
            ESP.restart();
        }
    }
};

void DS_bleSensorClient::begin() {
    _Neo_Pixel.begin();
    _Neo_Pixel.setBright(100);
    pref.begin("Sensor_box", false); 
}

void DS_bleSensorClient::setUpBle() {
    String a = pref.getString("Name", SENSOR_SERVER);
    Serial.println(a);
    strcpy(SENSOR_SERVER, a.c_str());
    BLEDevice::init(SENSOR_SERVER);
    Serial.println(SENSOR_SERVER);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *sensorLegService = pServer->createService(SERVICE_UUID);
    sensorLegCT = sensorLegService->createCharacteristic(SENSOR_LEG_CONTROL_UUID, BLECharacteristic::PROPERTY_NOTIFY);
    changeName = sensorLegService->createCharacteristic(CHANGE_NAME_SENSOR_UUID, BLECharacteristic::PROPERTY_WRITE);
    notifyBattery = sensorLegService->createCharacteristic(NOTIFY_BATTERY_UUID, BLECharacteristic::PROPERTY_NOTIFY);
    changeName->setCallbacks(new MyCallbacks());
    sensorLegService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // set value to 0x00 to not advertise this parameter
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
    
    // ledAdv();
}

void DS_bleSensorClient::checkStop(uint8_t *_data) {
    if (deviceConnected)
    {
        // ets_printf("ACCESS\n");
        if (millis() - lastStopMillis > 30) {
            
            sensorLegCT->setValue((uint8_t *)_data, 1);
            sensorLegCT->notify();
            lastStopMillis = millis();
        }
    }
    replayAdv();
}

void DS_bleSensorClient::checkControl(uint8_t *_data) {
    if (deviceConnected)
    {
        // ets_printf("ACCESS\n");
        if (millis() - lastSendMillis > 50) {
            
            sensorLegCT->setValue((uint8_t *)_data, 1);
            sensorLegCT->notify();
            lastSendMillis = millis();
        }
    }
    replayAdv();
}

void DS_bleSensorClient::checkPower(uint16_t *_data) {
    if (deviceConnected)
    {
        // ets_printf("ACCESS\n");
        notifyBattery->setValue((uint8_t *)_data, 2);
        notifyBattery->notify();
        vTaskDelay(10);
        // delay(3);
    }
    replayAdv();
}

void DS_bleSensorClient::replayAdv() {
    // disconnecting
    if (!deviceConnected && oldDeviceConnected)
    {
        vTaskDelay(500);                  // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        // Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
        // ledAdv();
    }
    updateConnect();
}

void DS_bleSensorClient::updateConnect() {
    // connecting
    if (deviceConnected && !oldDeviceConnected)
    {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

void DS_bleSensorClient::ledAdv() {
    while (deviceConnected == false) {
        // Serial.println("Sang");
        _Neo_Pixel.showPixel(0, ledRGB[1], ledRGB[1], ledRGB[1]);
        delay(300);
        // Serial.println("Toi");
        _Neo_Pixel.showPixel(0, ledRGB[0], ledRGB[0], ledRGB[0]);
        delay(300);
    }
    Serial.println("connected access");
}