#include <DS_RF24L01.h>

RF::RF(uint8_t nrfPinCE, uint8_t nrfPinCS) {
    radio = RF24(nrfPinCE, nrfPinCS);
}

void RF::begin(byte txAddr[], byte rxAddr[], SPIClass *_spi, bool checkRX_TX) {
    _spi->begin();
    radio.begin(_spi);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_HIGH);
    radio.setPayloadSize(1);
    radio.setRetries(15, 15);
    radio.openWritingPipe(txAddr);
    radio.openReadingPipe(0, rxAddr);

    if (checkRX_TX) {
        radio.startListening();
    }else {
        radio.stopListening();
    }
}

void RF::setTxAddr(byte txAddr[]) {
    radio.openWritingPipe(txAddr);
}

void RF::setRxAddr(byte rxAddr[]) {
    radio.openReadingPipe(0, rxAddr);
}

char RF::readData() {
    if(!radio.available()) {
        radio.read(&text, 1);
        Serial.println("Gia tri");
        Serial.println(text[0]);
    }
    
    return text[0];
}

void RF::sendData(const void* buff, uint8_t length) {
    radio.write(buff, length);
}