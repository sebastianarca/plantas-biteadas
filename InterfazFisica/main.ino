#include <config.h>
#include "./src/IO/DHT22.h"

IoDht22 io_ambiente;
long lastMsg    = 0;

void setup(){
    Serial.begin(115200);
    io_ambiente.setup();
}

bool ventanaProcesamiento(){
    unsigned long now   = millis();
    if ((now - lastMsg) > 5000) {
        lastMsg = now;
        return true;
    } else {
        return false;
    }
}

void loop() {
    if(!ventanaProcesamiento()){
        return;
    }
   
    io_ambiente.loop();
    io_ambiente.debug();
}