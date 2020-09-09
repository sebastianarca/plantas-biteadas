#ifndef DISPLAY_U8G2_h
#define DISPLAY_U8G2_h

#include <U8g2lib.h>

class Display {
    public:
        void setup();
        void loop();
        static char texto_linea1[16];
        static char texto_linea2[16];
        static char texto_linea3[16];
        static void setLinea1(String texto);
        static void setLinea2(String texto);
        static void setLinea3(String texto);
};
#endif