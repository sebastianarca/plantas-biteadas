#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

#include "src/Display/Display.h"
#include "src/ApiJSON/CultivoJSON.h"
#include "src/IO/DHT22.h"
#include "src/Network/Network.h"

IoDht22 io_ambiente;
WifiNetwork wifi;
CultivoJson api_json;
Display display;

long lastMsg    = 0;
bool ventanaProcesamiento(){
    unsigned long now   = millis();
    if ((now - lastMsg) > 5000) {
        lastMsg = now;
        return true;
    } else {
        return false;
    }
}


void setup(){
    Serial.begin(115200);
    display.setup();
    wifi.setup();
    wifi.debug();
    api_json.setup();
    io_ambiente.setup();
}

void loop() {
    wifi.loop();
    if(!ventanaProcesamiento()){
        return;
    }
    io_ambiente.loop();
    api_json.updateSensor("hum", io_ambiente.getHum());
    api_json.updateSensor("temp", io_ambiente.getTemp());

    io_ambiente.debug();
    Display::loop();
}