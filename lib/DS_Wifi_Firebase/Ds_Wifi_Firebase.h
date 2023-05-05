#ifndef DS_WIFI_FIREBASE
#define DS_WIFI_FIREBASE

#include <WiFi.h>
#include <FirebaseESP32.h>

class Ds_Wifi_Firebase {
    public:
        Ds_Wifi_Firebase();
        void beginWifi_Client(const char* SSID, const char* PASSWORD);
        void beginWifi_Server(const char* SSID_ESP, const char* PASSWORD_ESP);
        void beginFB(String FIREBASE_HOST, String FIREBASE_AUTH);
    
        // send data to firebase
        void sendStrdata(String keyFB, String data);
        void sendIntdata(String keyFB, int data);
        void sendFloatdata(String keyFB, float data);

        // give data to firebase
        int32_t getIntdata(String keyFB);
        String getStrdata(String keyFB);
        float_t getFloatdata(String keyFB);

        void testFirebase();

        void changeWifi();

        uint8_t statePractice();
    private:
        
        FirebaseData firebaseData;
        String path = "/";

        uint8_t practiceServer =  0;

        String addrServer =     "/Hand_Support";

        //Hand"
        String addrOpHand =     "/Hand";
        
        String addrOpThreshold_Hand =       "/Logic_Threshold";
        String addrShrink_Speed =           "/Shrink_Speed";
        String addrStretch_Speed =          "/Stretch_Speed";

        String addrOpPractice =             "/Practice_Hand";
        String addrPr_All_Fingers =         "/Practice_All_Fingers";
        String addrPr_Ring_Pinkey =         "/Practice_Ring_Pinkey";
        String addrPr_Thumb_Index_Middle =  "/Practice_Thumb_Index_Middle";
        String addrTargetSet =              "/Set_Target_Set";


        String addrCountAF =    "/Count_Target_Set_AF";
        String addrCountRP =    "/Count_Target_RP";
        String addrCountTIM =   "/Count_Target_TIM";

        String addrOpLogic_Hand =                "/State";
        String addrStateControl =           "/state_Control";
        String addrStateChangerPr =         "/state_change_Practice";

        String addrOpWifi =                 "/Wifi_Hand";
        String addrSSID =                   "/SSID_Hand";
        String addrPASSWORD =               "/PASSWORD_Hand";

        //"Hand

        //Myo Band"
        String addrOpMyo =              "/Myo_Band";

        String addrOpLogic_Myo =        "/Logic";
        String addrThreshold_Logic =    "/Threshold_logic";
        String addrThreshold_Muscle =   "/Threshold_Muscle";

        //"Myo Band
};

#endif