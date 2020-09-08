Nota para compilar Arduino:
 - Cada vez que se compila el proyecto es necesario borrar el contenido de la carpeta "build", a veces hay que repetir la compilacion porque falla al encontrar los archivos. Pero anda tal cual, solo hay que tener paciencia.
 

## Control de Cultivo

El proyecto consta de distintas partes:

 - Interfaz con planta: ESP8266 + API Web con respuesta JSON
 - - Se encarga de sensar y ejecutar acciones.
 - Proyecto proxy backend NodeJS
 - - Dar de alta, almacenar y mappear cada interfaz de cultivo.
 - - Leer y almacenar los datos de los sensores
 - - Envia peticion de acciones (prender o apagar reles mapeados)
 - - Ejecutar reglas. Sera una rutina que se ejecute durante cada ciclo de sensado, y actuara o no en base a las condiciones establecidas.
 - - API de intereccion para otros proyectos (Bot Telegram, Web en PHP o React)
 - Proyecto para la interfaz de usuario del sistema de cultivo.
 - Dockerizacion para ejecutar la base de datos y codigo del proxy y de las posible interfaces de usuario.


### Interfaz con planta

Codigo escrito en C++ usando la plaqueta ESP8266 basado en Arduino.

Se implementa un API de comunicacion RESTFull API levantando un servidor HTTP dentro del ESP8266.
Tanto las consultas de datos como las peticiones de acciones, se realizan mediante el mismo protocolo.

Parte del objetivo sera que este componente pueda ser autonomo. Y disponga de una pantalla para leer los datos sin interfaz web.   
En primer instancia el circuito estara montado en una protoboard pero la idea es que pueda estar montado en una caja resistente a pequeñas salpicaduras de agua y sea medianamenten simple conectarlo a la planta que se quiera sensar.

### Implementacion de la interfaz proxy

La interfaz con la planta recibe los datos del API y adapta su comportamiento a la cantidad de cultivos disponibles, tanto como la cantidad de sensores y actuadores.

Esta informacion es procesada, para almacenarse en una base de datos y poder ofrecer a posterior una interfaz grafica de usuario. Aunque tambien puede enviar los datos a un un proyecto de hogar automatizado como ser Mozilla Gateway.

Sin embargo la idea es aprovechar el estandar para tener un servicio en NodeJS que consulte cada 5 segundos el estado de los sensores, y almacene dicha informacion en un base de datos para a posterior realizar estadisticas.   

### Interfaz de usuario

Una web que permita visualizar los datos de los sensores y de los actuadores al momento de la consulta, y tambien disponer de estadisticas por periodo de tiempo.

Una posible alternativa de interfaz es usar un bot de Telegram para la consulta de:
 - Valores actuales de los sensores por cada cultivo registrado
 - Valores actuales de los actuadores por cada cultivo registrado
 - Promedio de los valores de los sensores en un periodo de semanas.