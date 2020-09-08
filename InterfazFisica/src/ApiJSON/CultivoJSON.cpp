//Cambiar Nombre a CultivoData
#include "CultivoJSON.h"
const size_t capacity = JSON_OBJECT_SIZE(2) + 3 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5);
DynamicJsonDocument jsonData(capacity);
/**
 * Interfaz que debe tener las publicaciones del ESP866
 {
    'id': String,
    'titulo': String,
    'schema': {
        'sensores': {
            'sensor_label_1': 'Sensor Nombre 1',
            'sensor_label_2': 'Sensor Nombre 2',
        },
        'acciones': 4
    },
    'data': {
        'sensor_label_1': float,
        'sensor_label_2': float,
    },
    acciones: {
        0: true,
        1: false,
        2: false,
        3: false,
    }
 }
 *
 * ================ Ejemplo 2222 =============== TODO hacer API ======
 {
   "id": "locoto",
   "titulo": "Descripcion del cultivo",
   "schema": {
       "sensores": {"hum":"humedad", "temp":"temperatura", "hum_tierra": "humedad"},
       "acciones": 4,
    },
    "data": {
       "hum": 50.75,
       "hum_tierra": 80.4,
       "temp": 20
    },
    "acciones":{
       "0": "Bomba Agua",
       "1": "Ventilador",
       "2": "Luces"
    }
 }
 */

char CultivoJson::output[1024];

void CultivoJson::setup()
{
    jsonData["id"]                  = "locoto";
    jsonData["titulo"]              = "Descripcion del cultivo";

    schema = jsonData.createNestedObject("schema");

    schema_sensores = schema.createNestedObject("sensores");
    schema_sensores["hum"]          = "Humedad Ambiente";
    schema_sensores["temp"]         = "Temperatura Ambiente";
    schema_sensores["hum_tierra"]   = "humedad";
    schema["acciones"]              = 4;

    data = jsonData.createNestedObject("data");
    data["hum"]         = 0.1;
    data["hum_tierra"]  = 0.1;
    data["temp"]        = 1;

    acciones = jsonData.createNestedObject("acciones");
    acciones["0"] = "Bomba Agua";
    acciones["1"] = "Ventilador";
    acciones["2"] = "Luces";
    serializeJson(jsonData, CultivoJson::output);
};
// se usa char *variable` para no tener que especificar el tamaño de la cadema de caracteres.
char *CultivoJson::getJSON()
{
    serializeJson(jsonData, CultivoJson::output);
    return CultivoJson::output;
}
void CultivoJson::updateSensor(String label, float value){
    data[label] = value;
}