//Cambiar Nombre a CultivoData
#ifndef CultivoJson_h
#define CultivoJson_h

#include <ArduinoJson.h>

class CultivoJson {
    private:
        JsonObject schema;
        JsonObject schema_sensores;
        JsonObject data;
        JsonObject acciones;
    public:
        static char output[1024];
        void updateSensor(String label, float value);
        static char *getJSON();
        void setup();
};

#endif