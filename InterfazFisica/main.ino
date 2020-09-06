#include <config.h>
#include "./src/IO/DHT22.h"

IoDht22 io_ambiente;
void setup(){
    Serial.begin(115200);
    io_ambiente.setup();
}

void loop() {
    io_ambiente.loop();
}