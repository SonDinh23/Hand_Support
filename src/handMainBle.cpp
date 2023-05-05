#include <Arduino.h>
#include <BLEDevice.h>
// #include <BLEScan.h>
#include <DS_bleHandClient.h>
#include <Ds_Wifi_Firebase.h>
#include <DS_BLEHandTask.h>
#include <DS_handstate.h>

#define TIME_SCAN   5

TaskHandle_t change_wifi_via_ble;

TaskHandle_t test_thumb_index_middle;
TaskHandle_t test_ring_pinky;
TaskHandle_t test_all_finger;
TaskHandle_t menu_server;
TaskHandle_t send_receive_Server;

TaskHandle_t ble_hand_server;
TaskHandle_t hand_support;

TaskHandle_t option_use;
TaskHandle_t control_use;

// char SSID_WIFI[] = "BO DAM CHO";
// char PASSWORD_WIFI[] = "0902kochoddau795hoilamgif5570mowddi";

String FB_AUTH = "3ca5gUtn7tfIVLLvYshljI7k8RyiW8yiyzA3E6dT";
String FB_HOST = "handsupport-dd1ee-default-rtdb.firebaseio.com";

static BLEUUID      service("bdd651e8-dbc0-11ed-afa1-0242ac120002");
static BLEUUID      sensor_leg("09ffd5e8-dbb3-11ed-afa1-0242ac120002");

Ds_Wifi_Firebase _Wifi_Firebase;
DS_BLEHandTask  _BleHandTask;
DS_bleHandClient _BleHandClient;
HandState _HandState;

uint8_t stateControlUse = 0;

void checkSensor();
void setUpBle();
void scanBle();

bool firstSetupBLe_CL = true;
char _Sensor = 'c';
uint32_t lastTimeScanBLE = millis();
bool stateScan = false;
static boolean doConnect = false;
static boolean connected = false;
// static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;

static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
    switch (*pData) {
        case 1:
            // Serial.println("Open");
            _Sensor = 'a';
            break;
        case 2:
            // Serial.println("Close");
            _Sensor = 'b';
            break;
        case 3:
            // Serial.println("Stop");
            _Sensor = 'c';
            break;
    default :
        // Serial.println("Stop");
        break;
    }
}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
    connected = true;
    stateScan = false;
    BLEDevice::getScan()->stop();
    Serial.println("Connected");
  }
  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

bool connectToServer() {
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(service);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(service.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");


    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(sensor_leg);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(sensor_leg.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    if(pRemoteCharacteristic->canRead()) {
      std::string value = pRemoteCharacteristic->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristic->canNotify())
      pRemoteCharacteristic->registerForNotify(notifyCallback);

    connected = true;
    return true;
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
 /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(service)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
    //   doScan = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks

void test_TIM(void* Parameters) {
    vTaskSuspend(test_thumb_index_middle);
    for (;;) {
        
        _BleHandTask.test_TIM();
        vTaskDelay(30);
    }
}

void test_RP(void* Parameters) {
    vTaskSuspend(test_ring_pinky);
    for (;;) {
        
        _BleHandTask.test_RP();
        vTaskDelay(30);
    }
}

void test_All_finger(void* Parameters) {
    vTaskSuspend(test_all_finger);
    for (;;) {
        
        vTaskDelay(30);
    }
}

void menu(void* Parameters) {
    vTaskSuspend(menu_server);
    for (;;) {
        Serial.println("menu");
        // switch (_Wifi_Firebase.statePractice()) {
        //     case 1:
        //         Serial.println("Test TIM");
        //         vTaskSuspend(test_ring_pinky);
        //         vTaskSuspend(test_all_finger);
        //         vTaskResume(test_thumb_index_middle);
        //         break;
        //     case 2:
        //         Serial.println("Test RP");
        //         vTaskSuspend(test_all_finger);
        //         vTaskSuspend(test_thumb_index_middle);
        //         vTaskResume(test_ring_pinky);
        //         break;
        //     case 3:
        //         Serial.println("Test ALL");
        //         vTaskSuspend(test_thumb_index_middle);
        //         vTaskSuspend(test_ring_pinky);
        //         vTaskResume(test_all_finger);
        //         break;
        //     default:
        //         Serial.println("No Test");
        //         break;
        // }
        vTaskDelay(5);
    }
}

void onServer(void* Parameters) {
    vTaskSuspend(send_receive_Server);
    for (;;) {
        Serial.println("OnServer");
        vTaskDelay(1);
    }
}

void bleHandServer(void* Parameters) {
    vTaskSuspend(ble_hand_server);
    for (;;) {
        if (firstSetupBLe_CL) {
            setUpBle();
            firstSetupBLe_CL = false;
        }
        if (doConnect == true) {
            Serial.println("access");
            if (connectToServer()) {
                Serial.println(connected);
                Serial.println("Connected to the BLE Server.");
            } else {
                Serial.println("We have failed to connect to the server; there is nothin more we will do.");
            }
            doConnect = false;
        }

        if (connected == false) {
            if (stateScan == false) {
                scanBle();
                stateScan = true;
            }
        }

        if (stateScan == true) {
            if (millis() - lastTimeScanBLE > TIME_SCAN * 1000) {
                scanBle();
            }
        }
        vTaskDelay(100);
    }
}

void checkSensor() {
    _HandState.updateSensor(_Sensor);
}

void handSupport(void* Parameters) {
    vTaskSuspend(hand_support);
    for (;;) {
        checkSensor();
        _HandState.update();
        vTaskDelay(1);
    }
}

void changeWifi_Via_Ble(void* Parameters) {
    vTaskSuspend(change_wifi_via_ble);
    for (;;) {
        Serial.println("ChangeWIFI");
        vTaskDelay(1);
    }
}

void control_Use(void* Parameters) {
    for (;;) {
        if (_BleHandTask.getStateButtonU_P() == false) {
            stateControlUse = 3;
        }
        if (_BleHandTask.getStateButtonU_H() == false) {
            stateControlUse = 1;
        }
        if (_BleHandTask.getStateButtonC_P() == false) {
            stateControlUse = 2;
        }
        vTaskDelay(1);
    }
}

void option(void* Parameters) {
    for (;;) {
        // Serial.println(stateControlUse);
        switch (stateControlUse)
        {
            case 1:
                // ets_printf("Using Hand\n");
                vTaskSuspend(send_receive_Server);
                vTaskSuspend(menu_server);
                vTaskSuspend(change_wifi_via_ble);

                vTaskResume(hand_support);
                vTaskResume(ble_hand_server);

                // vTaskSuspend(option_use);
                break;
            case 2:
                // ets_printf("Connect Phone\n");
                vTaskSuspend(send_receive_Server);
                vTaskSuspend(menu_server);
            
                vTaskSuspend(hand_support);
                vTaskSuspend(ble_hand_server);

                vTaskResume(change_wifi_via_ble);
                // vTaskSuspend(option_use);
                break;
            case 3:
                // ets_printf("Practice\n");
                vTaskSuspend(hand_support);
                vTaskSuspend(ble_hand_server);
                vTaskSuspend(change_wifi_via_ble);

                vTaskResume(send_receive_Server);
                vTaskResume(menu_server);
            
                // vTaskSuspend(option_use);
                break;
        default:
            ets_printf("NOON\n");
            break;
        }
        vTaskDelay(1);
    }
}

void setup() {
    Serial.begin(115200);
    _HandState.begin();
    _Wifi_Firebase.beginWifi_Client(ssid_Wifi, password_Wifi);
    _Wifi_Firebase.beginFB(FB_HOST, FB_AUTH);
    _Wifi_Firebase.testFirebase();
    // _BleHandClient.begin();
    // _BleHandTask.begin();
    
    // xTaskCreatePinnedToCore(option, "option", 5000, NULL, 1, &option_use, 1);
    // xTaskCreatePinnedToCore(control_Use, "control_Use", 5000, NULL, 1, &control_use, 1);
    // xTaskCreatePinnedToCore(changeWifi_Via_Ble, "change_wifi", 5000, NULL, 3, &change_wifi_via_ble, 0);

    // xTaskCreatePinnedToCore(bleHandServer, "ble_Hand_client", 5000, NULL, 2, &ble_hand_server, 1);
    // xTaskCreatePinnedToCore(handSupport, "hand_Support", 5000, NULL, 8, &hand_support, 1);
    
    // xTaskCreatePinnedToCore(test_TIM, "test_Thumb_Index_Middle", 5000, NULL, 2, &test_thumb_index_middle, 1);
    // xTaskCreatePinnedToCore(test_RP, "test_Ring_Pinky", 5000, NULL, 2, &test_ring_pinky, 1);
    // xTaskCreatePinnedToCore(test_All_finger, "test_Thumb_Index_Middle", 5000, NULL, 2, &test_all_finger, 1);

    // xTaskCreatePinnedToCore(menu, "menu", 5000, NULL, 3, &menu_server, 1);
    // xTaskCreatePinnedToCore(onServer, "on_server", 5000, NULL, 3, &send_receive_Server, 0);
}

void loop() {
    vTaskDelete(NULL);
}

void setUpBle() {
    Serial.println("Starting Hand Support BLE...");
    BLEDevice::init("");
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setInterval(1349);
    pBLEScan->setWindow(449);
    pBLEScan->setActiveScan(true);
    pBLEScan->start(TIME_SCAN, true);
    stateScan = true;
    lastTimeScanBLE = millis();
}

void scanBle() {
    Serial.println("Rescan Ble");
    BLEDevice::getScan()->clearResults();
    BLEDevice::getScan()->start(TIME_SCAN, true);
    lastTimeScanBLE = millis();
}

