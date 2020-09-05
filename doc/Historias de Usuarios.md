## Historias de Usuario


-------------------------------------------


### #1
**Titulo: _Interfaz de lectura y consulta de sensores_**   
**Complejidad: _5_**   
**Dependencia: _--_**   
**Contexto: _ESP8266_**   

**Que necesito:**   
Necesito disponer de una interfaz implementada con la libreria Mozilla Gateway, que permita sensar los componentes perifericos. Estos datos seran pasado al API para posterior acceso a su consulta.

Evaluar en que me momento se realiza el sensado; si cuando se hace la peticion de consulta, o cada X segundos.

En esta etapa los sensores seran:
 - Temperatura ambiente
 - Humedad ambiente
 - Humedad en tierra

**Para que:**   
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

