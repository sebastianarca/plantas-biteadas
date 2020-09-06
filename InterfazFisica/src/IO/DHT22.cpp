#include "./DHT22.h"

DHT dht(IO_DHT22_PIN, DHTTYPE); 

void IoDht22::setup(){
    pinMode(IO_DHT22_PIN, INPUT);
}

void IoDht22::loop(){
    temperatura = dht.readTemperature();
    humedad     = dht.readHumidity();
}
float IoDht22::getTemp(){
    return temperatura;
}
float IoDht22::getHum(){
    return humedad;
}

void IoDht22::debug(){
    if (isnan(temperatura) || isnan(humedad)){
        Serial.println();
        Serial.print("Error DHT:");
        Serial.println();    
    }
}