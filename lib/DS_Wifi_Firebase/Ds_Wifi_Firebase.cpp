#include <Ds_Wifi_Firebase.h>

Ds_Wifi_Firebase::Ds_Wifi_Firebase() {

}

void Ds_Wifi_Firebase::beginWifi_Server(const char* SSID_ESP, const char* PASSWORD_ESP) {
    WiFi.softAP(SSID_ESP, PASSWORD_ESP);
}

void Ds_Wifi_Firebase::beginWifi_Client(const char* SSID, const char* PASSWORD) {
    WiFi.begin(SSID, PASSWORD);
    uint8_t x = 0;
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        x++;
        if(x == 20) {
            Serial.println("disconnect");
            break; 
        }
        delay(300);
    }
}

void Ds_Wifi_Firebase::beginFB(String FIREBASE_HOST, String FIREBASE_AUTH) {
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    // Serial.println("Connection");
    if(!Firebase.beginStream(firebaseData, path)) {
        Serial.println("Reason: " + firebaseData.errorReason());
        Serial.println();
    }
}

void Ds_Wifi_Firebase::sendStrdata(String keyFB, String data) {
    Firebase.setString(firebaseData, path + keyFB, data);
}

void Ds_Wifi_Firebase::sendIntdata(String keyFB, int data) {
    Firebase.setInt(firebaseData, path + keyFB, data);
}

void Ds_Wifi_Firebase::sendFloatdata(String keyFB, float data) {
    Firebase.setFloat(firebaseData, path + keyFB, data);
}

int32_t Ds_Wifi_Firebase::getIntdata(String keyFB) {
    int32_t x;
    if(Firebase.getInt(firebaseData, path + keyFB)) x = firebaseData.intData();
    return x;
}

String Ds_Wifi_Firebase::getStrdata(String keyFB) {
    String x;
    if(Firebase.getString(firebaseData, path + keyFB)) x = firebaseData.stringData();
    return x;
}

float_t Ds_Wifi_Firebase::getFloatdata(String keyFB) {
    float_t x;
    if(Firebase.getFloat(firebaseData, path + keyFB)) x = firebaseData.floatData();
    return x;
}

void Ds_Wifi_Firebase::testFirebase() {
    sendStrdata("alo", "5");
}