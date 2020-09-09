#ifndef NETWORK_h
#define NETWORK_h

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

class WifiNetwork {
    public:
        static ESP8266WebServer server;
        static void handleNotFound();
        static void ApiRouter();
        static void getHelloWord();
        static String formularioWeb();
        static void ApiRouterWeb();

        void setup();
        void loop();
        void debug();
};

#endif