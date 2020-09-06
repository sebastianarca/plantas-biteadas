#ifndef IO_DHT22_h
#define IO_DHT22_h

#include "../config/config.h"
#include <DHT.h>
#define DHTTYPE DHT11  //DHT

class IoDht22{
    private:
        float temperatura;
        float humedad;
    public:
        void setup();
        void loop();
        void debug();
        float getTemp();
        float getHum();
};

#endif