#ifndef DS_BLE_HAND_TASK_H
#define DS_BLE_HAND_TASK_H

#define BUTTON_USING_PRACTICE       25
#define BUTTON_USING_HAND           26
#define BUTTON_CONNECT_PHONE        27

class DS_BLEHandTask {
    public:
        DS_BLEHandTask();

        void begin();

        void test_TIM();
        void test_RP();
        void tesk_All_finger();

        bool getStateButtonU_P();
        bool getStateButtonU_H();
        bool getStateButtonC_P();


        bool getUsingHand();
        bool getConnectPhone();
        bool getUsingPractice();

        void setUsingHand(bool _data);
        void setConnectPhone(bool _data);
        void setUsingPractice(bool _data);

    private:

        bool usingHand = true;
        bool connectPhone = false;
        bool usingPractice = false;

};

#endif