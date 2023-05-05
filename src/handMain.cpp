#include <Arduino.h>
#include <freertos/FreeRTOS.h>
//#include <DS_handstate.h>
#include <DS_RF24L01.h>

#define STATE_PHYSICAL_THERAPY 32
#define STATE_HAND_SUPPORT 33

#define NRF_CE  25
#define NRF_CS  15

#define MIN_ANGLE   80
#define MAX_ANGLE   100
#define MIN_ANGLE_PWM   1300
#define MAX_ANGLE_PWM   1600

byte ADDRESS_TX[6] = "ZZZZZ";
byte ADDRESS_RX[6] = "A0000";

TaskHandle_t hand_support;
TaskHandle_t hand_physical_therapy;
TaskHandle_t selection_option;
TaskHandle_t check_state_test;
TaskHandle_t receive_data;
TaskHandle_t send_data;

//HandState _ds_handstate(MIN_ANGLE, MAX_ANGLE, MIN_ANGLE_PWM, MAX_ANGLE_PWM);
SPIClass spiNrf(HSPI);
RF rf(NRF_CE, NRF_CS);

uint8_t stateTest = 0;

// void checkSensor();


// void checkSensor() {
//   _ds_handstate.updateSensor(rf.readData());
// }

// void Task_Receive_Data(void* Parameters) {

// }

// void Task_Send_Data(void* Parameters) {

// }

// void Task_Hand_Support(void* Parameters) {
//   vTaskSuspend(selection_option);
//   vTaskSuspend(check_state_test);
//   for (;;) {
//     checkSensor();
//     _ds_handstate.update();
//     vTaskDelay(1);
//   }
//   vTaskResume(selection_option);
//   vTaskResume(check_state_test);
// }

// void Task_Hand_Physical_Therapy(void* Parameters) {
//   vTaskSuspend(selection_option);
//   vTaskSuspend(check_state_test);
//   for (;;) {

//   }
//   vTaskResume(selection_option);
//   vTaskResume(check_state_test);
// }

// void Task_Check_State(void* Parameters) {
//   for (;;) {
//     if (digitalRead(STATE_HAND_SUPPORT) == 1) {
//       stateTest = 1;
//     }else {

//     }
//     if (digitalRead(STATE_PHYSICAL_THERAPY) == 1) {
//       stateTest = 2;
//     }else {

//     }
//     vTaskDelay(10);
//   }
// }

// void Task_Selection_Option(void* Parameters) {
//   for (;;) {
//     switch (stateTest)
//     {
//       case 1:                   // HAND SUPPORT
//         {
//           xTaskCreatePinnedToCore(Task_Hand_Support, "Task_Hand_Support", 10000, NULL, 7, &hand_support, 0);
//           xTaskCreatePinnedToCore(Task_Receive_Data, "Task_Receive_Data", 5000, NULL, 1, &receive_data, 0);
//           stateTest = 0;
//           break;
//         }
//       case 2:                   // HAND PHYSICAL THERAPY
//         {
//           xTaskCreatePinnedToCore(Task_Receive_Data, "Task_Receive_Data", 5000, NULL, 1, &receive_data, 0);
//           xTaskCreatePinnedToCore(Task_Send_Data, "Task_Send_Data", 5000, NULL, 1, &send_data, 0);
//           xTaskCreatePinnedToCore(Task_Hand_Physical_Therapy, "Task_Hand_Physical_Therapy", 10000, NULL, 7, &hand_physical_therapy, 0);
//           stateTest = 0;
//           break;
//         }
//     default:
//       stateTest = 0;
//       break;
//     }
//     vTaskDelay(1);
//   }
// }




void setup() {
  Serial.begin(115200);
  //pinMode(33,OUTPUT);
  //_ds_handstate.begin();
  rf.begin(ADDRESS_TX, ADDRESS_RX, &spiNrf ,true);
  Serial.println("oke");
  // pinMode(STATE_PHYSICAL_THERAPY, INPUT);
  // pinMode(STATE_HAND_SUPPORT, INPUT);
  
  // xTaskCreatePinnedToCore(Task_Hand_Support, "Task_Hand_Support", 10000, NULL, 7, &hand_support, 0);
  // xTaskCreatePinnedToCore(Task_Receive_Data, "Task_Receive_Data", 5000, NULL, 1, &receive_data, 0);
  // xTaskCreatePinnedToCore(Task_Send_Data, "Task_Send_Data", 5000, NULL, 1, &send_data, 0);
  // xTaskCreatePinnedToCore(Task_Hand_Physical_Therapy, "Task_Hand_Physical_Therapy", 10000, NULL, 7, &hand_physical_therapy, 0);
  // xTaskCreatePinnedToCore(Task_Check_State, "Task_Check_State", 2000, NULL, 1, &check_state_test, 0);
  // xTaskCreatePinnedToCore(Task_Selection_Option, "Task_Selection_Option", 2000, NULL, 1, &selection_option, 1);
}

void loop() {
  //digitalWrite(33,HIGH);
  rf.readData();
  //delay(300);
  //digitalWrite(33,LOW);
  //delay(300);
}