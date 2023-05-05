#ifndef DS_RF24L01_H
#define DS_RF24L01_H

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

class RF {
    public:
        RF(uint8_t nrfPinCE, uint8_t nrfPinCS);
        void begin(byte txAddr[], byte rxAddr[], SPIClass *_spi ,bool checkRX_TX);
        void setTxAddr(byte txAddr[]);
        void setRxAddr(byte rxAddr[]);
        char readData();
        void sendData(const void* buff, uint8_t length); 

    private:
        char text[1] = {0};
        RF24 radio;
};

#endif