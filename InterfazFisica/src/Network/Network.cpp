// #include "../config/config.h"
#include "Network.h"
#include "../ApiJSON/CultivoJSON.h"
#ifndef CONFIG_NETWORK_h
    #include "../config/config_network.h"
#endif

const char* wifi_ssid   = ESP_WIFI_SSID;
const char* wifi_pass   = ESP_WIFI_PASS;
const char* hostname    = ESP_HOSTNAME;

ESP8266WebServer WifiNetwork::server(80);


void WifiNetwork::setup(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    if (MDNS.begin(hostname)) {
      Serial.println("MDNS responder started");
    }
    ApiRouter();

    WifiNetwork::server.onNotFound(WifiNetwork::handleNotFound);
    WifiNetwork::server.begin();
}

void WifiNetwork::loop(){
    WifiNetwork::server.handleClient();
    MDNS.update();
}

void WifiNetwork::debug(){
    Serial.println(WiFi.localIP());
}

// static method
void WifiNetwork::handleNotFound() {
    String message = "{\"data\": false}";
    // message += "URI: ";
    // message += WifiNetwork::server.uri();
    // message += "\nMethod: ";
    // message += (WifiNetwork::server.method() == HTTP_GET) ? "GET" : "POST";
    // message += "\nArguments: ";
    // message += WifiNetwork::server.args();
    // message += "\n";
    // for (uint8_t i = 0; i < WifiNetwork::server.args(); i++) {
    //     message += " " + WifiNetwork::server.argName(i) + ": " + WifiNetwork::server.arg(i) + "\n";
    // }
    WifiNetwork::server.send(404, "text/plain", message);
}

// static method
void WifiNetwork::ApiRouter() {
    WifiNetwork::server.on("/", HTTP_GET, []() {
        WifiNetwork::server.send(200, F("text/json"), CultivoJson::getJSON());
    });
    
    // WifiNetwork::server.on("/", HTTP_GET, []() {
    //     WifiNetwork::server.send(200, F("text/html"),
    //         F("Welcome to the REST Web Server"));
    // });
    // WifiNetwork::server.on(F("/helloWorld"), HTTP_GET, WifiNetwork::getHelloWord);
}

// static method
// void WifiNetwork::getHelloWord() {
//     WifiNetwork::server.send(200, "text/json", "{\"name\": \"Hello world\"}");
// }