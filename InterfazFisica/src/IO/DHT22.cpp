#include "DHT22.h"
#ifndef CONFIGURACION_h
    #include "../config/config.h"
#endif

DHT dht(IO_DHT22_PIN, DHTTYPE); 

void IoDht22::setup(){
    pinMode(IO_DHT22_PIN, INPUT);
}

/**
 * Lee los valores del sensor y los almacena en las variables.
 * Si la lectura es erronea (falla en conexion, intermitencia, etc) el valor guardado es tendiente a 0
*/
void IoDht22::loop(){
    float aux_temp  = dht.readTemperature();
    float aux_hum   = dht.readHumidity();
    
    if(aux_temp > -10){
        temperatura = aux_temp;
        humedad     = aux_hum;
    } else {
        temperatura = 1;
        humedad     = 0.1;
    }
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
    } else {
        Serial.println();
        Serial.print("DHT Temp: ");
        Serial.println(temperatura);
        Serial.print("DHT Hum: ");
        Serial.println(humedad);
    }
}