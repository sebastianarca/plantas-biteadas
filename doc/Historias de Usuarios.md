## Historias de Usuario


-------------------------------------------


### #1
**Titulo: _Interfaz de lectura y consulta de sensores_**   
**Complejidad: _5_**   
**Dependencia: _--_**   
**Contexto: _ESP8266_**   

**Que necesito:**   

Necesito que el ESP se conecte a la red wifi y luego de obtener un IP dinamica, escuchar en el puerto 80 las peticiones realizadas.
Se debe crear un serie rutas que permitan las consultas de datos cuya respuesta sea tipo JSON.

Evaluar en que me momento se realiza el sensado; si cuando se hace la peticion de consulta, o cada X segundos.

En esta etapa los sensores seran:
 - Temperatura ambiente
 - Humedad ambiente
 - Humedad en tierra

**Para que:**   
Disponer de un API para la consulta de tipos de sensores y sus valores.
Para que al realizar la consulta por http con el cultivo especificado, obtener los valores de cada sensor individualmente.

**Objetivos:**   
Disponer mediante URL http://ip_esp8266:puerto los datos de los sensores anteriormente listados.    
Que los datos de los sensores cambien sus valores segun correspondan.    
En lo posible disponer del listado de sensores disponibles.


-------------------------------------------


### #2
**Titulo: _Interfaz de acciones_**   
**Complejidad: _5_**   
**Dependencia: _#1_**   
**Contexto: _ESP8266_**   

**Que necesito:**   
Expandiendo la HU #1, necesito poder mapear y controlar el estado de los Reles.
De momento solo se contara con 4 reles de accion.

**Para que:**   
Para que al realizar la peticion por http, cambie el estado de los reles y tambien poder saber el estado en el que se encuentran.

**Objetivos:**   
Disponer mediante URL http://ip_esp8266:puerto una forma de especificar que Rele quiero cambiar de estado, y a que estado setearlo.

Que los datos de los reles estan disponibles para consultar.

-------------------------------------------


### #3
**Titulo: _Inicializacion WIFI_**   
**Complejidad: _5_**   
**Dependencia: _--_**   
**Contexto: _ESP8266_**   

**Que necesito:**   
En el momento Cero (primer inicio), necesito que el ESP se active con el modo Wifi AP (Access Point), que al conectarse desde un dispositivo, provea una pagina web con formulario para completar los datos:

 - SSID (Nombre de la red Wifi Hogareña)
 - Clave Wifi
 - Hostname (URL) del cultivo
 - Titulo cultivo
 - Titulo Accion (uno por cada accion disponible)

Al completar estos datos y enviarlos de nuevo al servidor, se deberan guardar en la memoria interna EEPROM.
Utilizando estos valores, se reinicia el ESP entrando en modo cliente y conectandose a la red wifi del hogar. Caso de no poder concretar la operacion, debe volver a iniciarse en modo AP.

**Para que:**   
Para poder configurar los valores mediante interfaz web

**Objetivos:**   
Ante la falta de conecion de la red wifi hogareña, configurar el ESP en modo AP para proveer de una interfaz web que permita llenar un formulario para configurar los datos requeridos.

