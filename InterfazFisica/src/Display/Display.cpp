#include "Display.h"
#ifdef U8X8_HAVE_HW_SPI
    #include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
    #include <Wire.h>
#endif

/**
 * Con el tamaño de letra de 8px, entran solo 16 caracteres en la pantalla
*/

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

char Display::texto_linea1[16];
char Display::texto_linea2[16];
char Display::texto_linea3[16];

void Display::setup(){
    u8g2.begin();
}
void Display::loop(){
    u8g2.clearBuffer();

    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 8, Display::texto_linea1);
    u8g2.drawStr(0, 18, Display::texto_linea2);
    u8g2.drawStr(0, 28, Display::texto_linea3);
    u8g2.sendBuffer();
}

void Display::setLinea1(String texto){
    strcpy(Display::texto_linea1, texto.c_str());
}
void Display::setLinea2(String texto){
    strcpy(Display::texto_linea2, texto.c_str());
}
void Display::setLinea3(String texto){
    strcpy(Display::texto_linea3, texto.c_str());
}