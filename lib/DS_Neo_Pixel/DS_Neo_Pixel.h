#ifndef DS_NEO_PIXEL_H
#define DS_NEO_PIXEl_H

#include <Adafruit_NeoPixel.h>

#define LED_PIN 33
#define LED_COUNT 3

class DS_Neo_pixel {
    private:
        Adafruit_NeoPixel pixel = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); 
    public:
        DS_Neo_pixel(/* args */);
        void begin();
        void setBright(uint8_t brightNess);
        void showPixel(uint8_t pinLed, uint8_t pRed, uint8_t pGreen, uint8_t pBlue);
        void clear();
};
#endif