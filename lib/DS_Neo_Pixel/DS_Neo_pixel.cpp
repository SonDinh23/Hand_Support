#include <DS_Neo_Pixel.h>

DS_Neo_pixel::DS_Neo_pixel() {
    
}

void DS_Neo_pixel::begin() {
    pixel.begin();
}

void DS_Neo_pixel::setBright(uint8_t brightNess) {
    pixel.setBrightness(brightNess);
}

void DS_Neo_pixel::showPixel(uint8_t pinLed, uint8_t pRed, uint8_t pGreen, uint8_t pBlue) {
    pixel.setPixelColor(pinLed, pixel.Color(pRed, pGreen, pBlue));
    pixel.show();
}

void DS_Neo_pixel::clear() {
    
}