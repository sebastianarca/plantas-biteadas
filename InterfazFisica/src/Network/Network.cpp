// #include "../config/config.h"
#include "Network.h"
#include "../ApiJSON/CultivoJSON.h"
#include "../Display/Display.h"
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
    int check_count = 0;
    int check_limit = 50;
    while (WiFi.status() != WL_CONNECTED && check_count < check_limit) {
        delay(500);
        Serial.print(".");
        Display::setLinea1("Conectando ....");
        Display::loop();
        check_count++;
    }
    IPAddress myIP;
    if(check_count == check_limit){
        WiFi.mode(WIFI_SHUTDOWN);
        WiFi.softAP(hostname, NULL, 1);
        myIP = WiFi.softAPIP();

        Display::setLinea1("Wifi modo AP");

        Serial.print("AP IP address: ");
        Serial.println(myIP);
    } else {
        myIP    = WiFi.localIP();
        
        Display::setLinea1("Wifi modo client");
    }
    if (MDNS.begin(hostname, myIP)) {
        Serial.println("MDNS responder started");
    }
    
    if(check_count == check_limit){
        ApiRouterWeb();
    } else {
        ApiRouter();
    }

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
    WifiNetwork::server.send(404, "text/plain", message);
}

// static method
void WifiNetwork::ApiRouter() {
    WifiNetwork::server.on("/", HTTP_GET, []() {
        WifiNetwork::server.send(200, F("text/json"), CultivoJson::getJSON());
    });
}

// static method
void WifiNetwork::ApiRouterWeb() {
    WifiNetwork::server.on("/", HTTP_GET, []() {
        WifiNetwork::server.send(200, F("text/html"), WifiNetwork::formularioWeb());
    });
    WifiNetwork::server.on(F("/guardar"), HTTP_POST, []() {
        String message = "";
        message += "URI: ";
        message += WifiNetwork::server.uri();
        message += "\nMethod: ";
        message += (WifiNetwork::server.method() == HTTP_GET) ? "GET" : "POST";
        message += "\nArguments: ";
        message += WifiNetwork::server.args();
        message += "\n";
        for (uint8_t i = 0; i < WifiNetwork::server.args(); i++) {
            message += " " + WifiNetwork::server.argName(i) + ": " + WifiNetwork::server.arg(i) + "\n";
        }
        WifiNetwork::server.send(200, "text/plain", message);
    });
}

// static method
String WifiNetwork::formularioWeb(){
    String html = "<!DOCTYPE html><html><head><meta charset='utf-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><title>Planta Biteada</title><meta name='viewport' content='width=device-width, initial-scale=1'><style>.text-center{text-align: center;}html{font-family:sans-serif;-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}body{margin:0}article,aside,details,figcaption,figure,footer,header,hgroup,main,menu,nav,section,summary{display:block}audio,canvas,progress,video{display:inline-block;vertical-align:baseline}audio:not([controls]){display:none;height:0}[hidden],template{display:none}a{background-color:transparent}a:active,a:hover{outline:0}abbr[title]{border-bottom:none;text-decoration:underline;text-decoration:underline dotted}b,strong{font-weight:bold}dfn{font-style:italic}h1{font-size:2em;margin:0.67em 0}mark{background:#ff0;color:#000}small{font-size:80%}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}sup{top:-0.5em}sub{bottom:-0.25em}img{border:0}svg:not(:root){overflow:hidden}figure{margin:1em 40px}hr{-webkit-box-sizing:content-box;-moz-box-sizing:content-box;box-sizing:content-box;height:0}pre{overflow:auto}code,kbd,pre,samp{font-family:monospace, monospace;font-size:1em}button,input,optgroup,select,textarea{color:inherit;font:inherit;margin:0}button{overflow:visible}button,select{text-transform:none}button,html input[type=\"button\"],input[type=\"reset\"],input[type=\"submit\"]{-webkit-appearance:button;cursor:pointer}button[disabled],html input[disabled]{cursor:default}button::-moz-focus-inner,input::-moz-focus-inner{border:0;padding:0}input{line-height:normal}input[type=\"checkbox\"],input[type=\"radio\"]{-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box;padding:0}input[type=\"number\"]::-webkit-inner-spin-button,input[type=\"number\"]::-webkit-outer-spin-button{height:auto}input[type=\"search\"]{-webkit-appearance:textfield;-webkit-box-sizing:content-box;-moz-box-sizing:content-box;box-sizing:content-box}input[type=\"search\"]::-webkit-search-cancel-button,input[type=\"search\"]::-webkit-search-decoration{-webkit-appearance:none}fieldset{border:1px solid #c0c0c0;margin:0 2px;padding:0.35em 0.625em 0.75em}</style></head><body><div class=\"text-center\"><h1 class=\"text-center\">Bienvenida a Planta Biteada</h1><p class=\"text-center\">En esta pantalla usted debe configurar su cultivo</p></div><form method=\"POST\" action=\"guardar\" class=\"text-center\" class=\"text-center\"><fieldset><legend>Configuracion Wifi</legend><div class=\"text-left padding-left\"><label for=\"ssid\">Nombre de la red Wifi</label><input type=\"text\" name=\"ssid\" placeholder=\"Wifi de casa\"/></div><div class=\"text-left padding-left\"><label for=\"pass\">Clave Wifi</label><input type=\"text\" name=\"pass\" placeholder=\"12345678\"/></div><div><input type=\"submit\" value=\"Guardar\" /></div></fieldset></form></body></html>";
    return html;
}