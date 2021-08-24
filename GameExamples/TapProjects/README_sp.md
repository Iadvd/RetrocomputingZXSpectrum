# Proyectos "SpectrumTap2WindowsExe" y "SpectrumTaps2WindowsExeLauncher" 

<b>Importante: estos proyectos son especializaciones, realizadas bajo una licencia a GPL-2.0, 
del genial emulador "Qaop ZX Spectrum Emulator" (https://github.com/ukwa/qaop) de Jan Bobrowski </b>

<b>Descripciones breves:</b>

<b>SpectrumTap2WindowsExe</b> convierte tu archivo .tap de ZX Spectrum en un
único archivo Windows .exe ejecutable. Dicho archivo contiene el emulador y
el archivo .tap. Por tanto, no es necesario ningún emulador externo para jugar el juego.

<b>SpectrumTaps2WindowsExeLauncher</b> es una plantilla para crear un 
único ejecutable .exe de Windows que contiene un menú principal desde el cual puedes mostrar
todos tus juegos ZX Spectrum y el usuario puede jugarlos simplemente haciendo click en 
los iconos del menú, abriéndolos en ventanas independientes dentro de la misma aplicación. 
El único archivo .exe contiene tanto el emulador como los archivos .tap así que no es necesario
ningún emulador externo o archivo extra. 

<b>Requerimientos:</b> el entorno Java Runtime Environment (JRE)
debe estar instalado en el PC.

<b>Con gratitud a mis amigos que se presentaron voluntarios para probar estas herramientas:
(en orden alfabético):</b>

Greenweb Sevilla: https://greenwebsevilla.itch.io/ 

Javi Ortiz: https://www.youtube.com/c/ElSpectrumeroJaviOrtiz

Roolandoo: https://roolandoo.itch.io/

# "SpectrumTap2WindowsExe"

<b>1 archivo Tap (48k) = 1 archivo Windows Exe (embebido en un applet Java .jar)</b>

<b>El objetivo de esta herramienta es aportar a los desarrolladores de juegos
(o aplicaciones) en formato .tap para emulador de ZX Spectrum 48k un nuevo formato alternativo 
para distribuir su trabajo. Por ejemplo, puedes distribuir tu archivo .tap en tu
página web, o en Itch.io, etc. y habilitar para descarga aparte del archivo .tap un 
archivo ejecutable con el juego en formato .exe de Windows. 
El archivo .exe funciona en Windows 10 o en versiones previas que sean más o menos actuales;
por tanto, queda excluído Windows XP y probablemente Windows 7 - que no hemos testeado -.</b>

Con esta herramienta es posible convertir un archivo ZX Spectrum 48k .tap
en un applet de Java embebido en un único archivo ejecutable .exe de Windows. 

El proyecto es una especializacion, realizada bajo una licencia a GPL-2.0,
del genial emulador "Qaop ZX Spectrum Emulator" (https://github.com/ukwa/qaop) de Jan Bobrowski </b>

Cuando el archivo se ejecuta en Windows, la pantalla del emulador aparece y se abre
directamente el archivo .tap en una única ventana de Windows, en la que se puede
jugar (o usar la aplicación que sea) sin la necesidad de un emulador externo. 

<b>Requerimientos:</b> el archivo .exe funcionará sólo si el PC tiene instalado 
el entorno Java Runtime Environment (JRE). Si no está instalado, el programa 
al ser ejecutado lo detecta y te permitirá descargar el JRE de la página 
oficial de Java (deberás instalarlo manualmente, pero se tarda 1 minuto).
Una vez instalado al ejecutar de nuevo el archivo .exe ya deberá aparecer
el juego en pantalla.

Esta herramienta es un proyecto Java, que se construye (build) mediante Maven mediante
línea de comandos (sin IDE). Proporcionamos los archivos fuente del proyecto, asi como 
los archivos batch necesarios para ejecutar las llamadas a Maven y crear el applet de Java.

https://Maven.apache.org/download.cgi

<b>El proceso se explica a continuación:</b>

1. Copia la carpeta del proyecto "SpectrumTap2WindowsExe" incluyendo subcarpetas
a tu PC en un directorio local.

2. Incluye tu archivo .tap en el directorio "resources":

src\main\resources

Por ejemplo, tu archivo .tap sería por ejemplo:
"mi_archivo_tap.tap"

En nuestro ejemplo del código fuente es "TheHoarder_en.tap"

2.1 Edita el archivo:

src\main\java\uk\bl\wa\access\qaop\Qaop.java

- Busca la línea de código que pone...

tapname="";

...que debe ser cambiada por el nombre de tu archivo .tap, por ejemplo

tapname="mi_archivo_tap.tap";

- Busca la línea de código que pone...

f.setTitle("This is the title of the screen");

...y cambia ese texto por el título de cabecera que quieres que salga en la parte superior
de la ventana del programa (por ejemplo puede ser el nombre del juego).

Eso es todo lo que hay que tocar en el código.

3. Instala Maven en una carpeta en el mismo nivel que el proyecto Java
(por ejemplo, en nuestro código fuente verás que hay una carpeta "apache-maven-3.8.1".
Es un ejemplo del sitio donde se debe instalar Maven, pero el nombre de la carpeta
cambiará dependiendo de la versión de Maven que instales).

4. En la carpeta superior del proyecto hay tres archivos .bat:

4.1. "mvn_cleaninstall.bat" verifica que el applet se puede construír 
sin errores de sintáxis o de librerías faltantes. Si el proceso
acaba correctamente, entonces ya puedes testear el applet localmente o crear el 
applet .jar definitivo que vas a distribuir, que luego se convertira en
un posterior paso en un archivo .exe de Windoes.. 

El contenido del archivo .bat es la llamada siguiente:

.\apache-maven-3.8.1\bin\mvn clean install

4.2 "mvn_execjava.bat" sirve para testear el applet de Java localmente.
Lanza el applet de Java en una ventana y por tanto deberías poder 
ver el juego y jugar con el correctamente, de la misma forma que
se podrá posteriormente al crear el archivo .exe definitivo. 
No es necesario cargar el juego con load "". Aparece directamente.
Si el juego no aparece o hay algún error de visualización,
vuelve al paso 4.1 y verifica tu código.

Restricción: el emulador utilizado como base, Qaop ZX Spectrum emulator,
no permite el uso de pantalla completa, por lo que el juego se mostrará 
en el máximo tamaño posible que permite el emulador.

El contenido del archivo .bat es la llamada siguiente:

.\apache-maven-3.8.1\bin\mvn exec:java

4.3 Finalmente, "mvn_package.bat" construye el Applet 
de Java en formato .jar distribuíble que incluye todo lo necesario
para poder ser ejecutado en un PC Windows. Como es un Applet
de Java .jar requiere un PC con el entorno Java Runtime Environment
(JRE) instalado previamente. 

El contenido del archivo .bat es la llamada siguiente:

.\apache-maven-3.8.1\bin\mvn clean package

5. El archivo applet .jar definitivo aparecerá en el directorio "target"
con el nombre: 

"qaop-1.4.1-SNAPSHOT-jar-with-dependencies.jar"

6. Para crear el .exe de Windows definitivo, sigue estos pasos:

6.1 Intala JSmooth en tu PC:

http://jsmooth.sourceforge.net/download.php

Abre el programa y pon estos parámetros:

6.1.1 "Skeleton": 

- "Windowed Wrapper"

- "Message": escribe un mensaje de bienvenida que aparecerá cuando se detecte que el PC
todavia no tiene instalado el Java Runtime Environment (JRE). Por ejemplo:

Bienvenido/a. No se encuentra el entorno Java JRE en tu PC y este programa lo necesita 
para funcionar. Para descargarlo, pulsa en el botón y se abrirá tu navegador web
en la página oficial de Java (tendrás que instalarlo manualmente):

https://www.java.com/es/download

- "URL": escribe https://www.java.com/es/download

- Marca "Launch java app in the exe process" 

- Marca "Single instance" 

- No marques otras opciones

6.1.2 "Executable":

- "Executable Binary": escribe el nombre que tendrá tu archivo .exe,
por ejemplo, "SpectrumTap2WindowsExe_game_example.exe"

- "Executable Icon": puedes crear una imagen .png que no sea muy grande y
será mostrada como icono de la aplicación (por ejemplo 120x120 pixels), 
no es necesario que sea un archivo .ico. 

- Marca "Sets the executable folder as current directory of the application"

6.1.3 "Application"

- "Embedded jar settings": marca "Use an embedded jar" y selecciona el
archivo applet de Java .jar que creaste en el directorio "target"
en el paso 5.

- "Main class": haz click en "..." y selecciona la clase
"uk.bl.wa.access.qaop.Qaop"

- "Application Arguments" y "Class path" deben quedar vacíos.

6.1.4 No toques otros parámetros o submenús de JSmooth. 

6.1.5 Pulsa en el botón con el dibujo de un engranaje
y una ventana aparecerá. Si todo va bien un mensaje "Done"
aparecerá y ya tienes disponible tu archivo .exe para
distribuir.

En nuestro ejemplo de código fuente el archivo .exe generado es:

"SpectrumTap2WindowsExe_game_example.exe"

7. Ya tienes un applet de Java .jar embebido en un archivo .exe de Windows. 
Este es el archivo que puedes distribuir. Si la persona que descarga el .exe
no tiene Java Runtime Environment (JRE) instalado en su PC, el
archivo .exe lo detectará y abrirá la página web oficial de Java. 
El usuario debe descargar e instalar manualmente JRE, una vez hecho,
si de nuevo ejecuta el archivo .exe del juego ya debe salir en
pantalla y se puede jugar normalmente.

Consideración #1: algunas veces, dependiendo del grado de seguridad
del PC donde se instala JRE, el programa que instala JRE no es capaz
de incluir la variable de sistema HOME_JRE que apunta a la
carpeta donde esta instalado el Java Runtime Environment. 
Normalmente esto no sucede, pero en el caso de que pase, 
el usuario deberá incluir dicha variable manualmente en el 
sistema. En esta página web explican como hacerlo (en inglés):

https://confluence.atlassian.com/doc/setting-the-java_home-variable-in-windows-8895.html 

Consideración #2: un tema conocido por los desarrolladores Java 
que hacen Applets emebebidos en .exe para Windows es que
algunos programas antivirus son muy estrictos y marcan 
algunas veces los archivos .exe creados con este método como
portadores de virus. No sucede muy habitualmente, 
depende de la marca del antivirus, del nivel de 
restricciones que se haya marcado, etc. las reglas varían 
mucho entre antivirus. Este es un tema conocido por los
desarrolladores de Java embebido en archivos .exe pero la realidad es
que cuando ocurre poco se puede hacer, excepto que el usuario
marque el archivo de cara al antivirus como falso positivo para poder utilizarlo. 

8. Siguientes pasos:

Crear una solución para archivos 128k.


# "SpectrumTaps2WindowsExeLauncher"

<b>Muchos archivo .tap = 1 único archivo .exe de Windows con un lanza juegos 
(applet de Java .jar embebido en un archivo .exe de Windows)</b>

<b>El objetivo de esta herramienta es proporcionar a los desarrolladores
de juegos (o programas) en formato .tap para ZX Spectrum 48k de una
forma complementaria / alternativa de distribuir sus trabajos.
En esta caso por ejemplo puedes dsitribuir TODOS tus archivos .tap 
en un UNICO archivo .exe, que incluye un menú de carga donde se
puede elegir el juego, que aparecerá en una ventana independiente. 
También incluye un icono para abrir la página web que incluye
la información del juego (controles, historia, etc.).
Es muy práctico para hacer compilaciones de juegos. El archivo .exe 
funciona en Windows 10 o en versiones previas que sean más o menos actuales;
por tanto, queda excluído Windows XP y probablemente Windows 7 - que no hemos testeado -.

Este proyecto incluye todos los archivos fuente de Java necesarios para 
poder crear un Applet distribuíble, y <b>hay un ejemplo de uso en itch.io 
en este enlace</b>: 

https://furilloproductions.itch.io/furillo-productions-all-in-one-48k-2019-2021

El proyecto es una especializacion, realizada bajo una licencia a GPL-2.0,
del genial emulador "Qaop ZX Spectrum Emulator" (https://github.com/ukwa/qaop) de Jan Bobrowski </b>

Cuando el archivo .exe se ejecuta en Windows, aparece el menú principal
del lanza juegos y se pueden jugar todos los juegos incluídos sin necesidad
de un emulador de ZX Spectrum externo.

<b>Requerimientos:</b> el archivo .exe funcionará sólo si el PC tiene instalado 
el entorno Java Runtime Environment (JRE). Si no está instalado, el programa 
al ser ejecutado lo detecta y te permitirá descargar el JRE de la página 
oficial de Java (deberás instalarlo manualmente, pero se tarda 1 minuto).
Una vez instalado al ejecutar de nuevo el archivo .exe ya deberá aparecer
el juego en pantalla.

Esta herramienta es un proyecto Java, que se construye (build) mediante Maven mediante
línea de comandos (sin IDE). Proporcionamos los archivos fuente del proyecto, asi como 
los archivos batch necesarios para ejecutar las llamadas a Maven y crear el applet de Java.

https://Maven.apache.org/download.cgi

<b>El proceso se explica a continuación:</b>

1. Copia la carpeta del proyecto "SpectrumTap2WindowsExe" incluyendo subcarpetas
a tu PC en un directorio local.

2. Incluye tus archivos .tap en el directorio "resources":

src\main\resources

(en nuestro código fuente de ejemplo verás que hay dos archivos .tap)

Tambien incluye la imagen de fondo del menú principal del lanza juegos y 
el icono (.png) que usará el archivo .exe de Windows. 
Por ejemplo, en nuestro código fuente son éstos:

launcherbkg.png
launchericon.png

La imagen puede ser como desees, pero en este ejemplo 
contiene dos filas de juegos en varios lenguajes y con 
enlaces a las páginas web (i) que incluyen la información 
sobre como jugar, controles, etc. En el código fuente de 
ejemplo sólo funciona el juego "The Hoarder", los otros
no están presentes.

2.1 Edita el archivo:

src\main\java\uk\bl\wa\access\qaop\Qaop.java

Tienes que personalizar estas partes del código:

2.1.1 Líneas 562 and 594
.setTitle("This is the title of your game launcher");

Escribe el título que aparece en la parte superior de la ventana del lanza juegos.

2.1.2 Línea 584
//System.out.println(e.getX() + "," + e.getY());
Quita el comentario // y ejecuta el juego para poder 
saber la posición del ratón en pantalla
cuando hagas click. Es necesario para que puedas personalizar
el evento de click en la imagen del menú principal, ya que
dicho evento abre el archivo .tap que corresponda a tu diseño
en concreto, así que debes personalizar los clicks en pantalla.

2.1.3 Línea 581
public void mousePressed(MouseEvent e) {

Dentro de este evento, se controla que cuando 
haces click con el ratón en el menú, dependiendo de la
posición del ratón en pantalla se abra un archivo .tap o un enlace web. 
En nuestro código fuente verás que están programados los puntos
de click del juego "The Hoarder" así como la página web de
información. 

2.1.4 Mensaje de bienvenida (ventana flotante):

- Busca estos comentarios... 

// English version 
// Spanish version

...y cambia los mensajes que aparecen de bienvenida al abrir el
lanza juegos, en su versión en castellano e inglés. 

Nota: por supuesto puedes hacer una sola version en el 
idioma que quieras. 

Necesitarás un poco de tiempo para hacer tu propia 
versión del lanza juegos, pero técnicamente esto es
todo lo que hay que modificar del código.

3. Instala Maven en una carpeta en el mismo nivel que el proyecto Java
(por ejemplo, en nuestro código fuente verás que hay una carpeta "apache-maven-3.8.1".
Es un ejemplo del sitio donde se debe instalar Maven, pero el nombre de la carpeta
cambiará dependiendo de la versión de Maven que instales).

4. En la carpeta superior del proyecto hay tres archivos .bat:

4.1. "mvn_cleaninstall.bat" verifica que el applet se puede construír 
sin errores de sintáxis o de librerías faltantes. Si el proceso
acaba correctamente, entonces ya puedes testear el applet localmente o crear el 
applet .jar definitivo que vas a distribuir, que luego se convertira en
un posterior paso en un archivo .exe de Windoes.. 

El contenido del archivo .bat es la llamada siguiente:

.\apache-maven-3.8.1\bin\mvn clean install

4.2 "mvn_execjava.bat" sirve para testear el applet de Java localmente.
Lanza el applet de Java en una ventana y por tanto deberías poder 
ver el lanza juegos y jugar a los juegos correctamente, de la misma forma que
se podrá posteriormente al crear el archivo .exe definitivo. 
Si el lanza juegos no aparece o hay algún error de visualización,
vuelve al paso 4.1 y verifica tu código.

Restricción: el emulador utilizado como base, Qaop ZX Spectrum emulator,
no permite el uso de pantalla completa, por lo que los juegos se mostrarán 
en el máximo tamaño posible que permite el emulador en ventanas independientes.

El contenido del archivo .bat es la llamada siguiente:

.\apache-maven-3.8.1\bin\mvn exec:java

4.3 Finalmente, "mvn_package.bat" construye el Applet 
de Java en formato .jar distribuíble que incluye todo lo necesario
para poder ser ejecutado en un PC Windows. Como es un Applet
de Java .jar requiere un PC con el entorno Java Runtime Environment
(JRE) instalado previamente. 

El contenido del archivo .bat es la llamada siguiente:

.\apache-maven-3.8.1\bin\mvn clean package

5. El archivo applet .jar definitivo aparecerá en el directorio "target"
con el nombre: 

"qaop-1.4.1-SNAPSHOT-jar-with-dependencies.jar"

6. Para crear el .exe de Windows definitivo, sigue estos pasos:

6.1 Intala JSmooth en tu PC:

http://jsmooth.sourceforge.net/download.php

Abre el programa y pon estos parámetros:

6.1.1 "Skeleton": 

- "Windowed Wrapper"

- "Message": escribe un mensaje de bienvenida que aparecerá cuando se detecte que el PC
todavia no tiene instalado el Java Runtime Environment (JRE). Por ejemplo:

Bienvenido/a. No se encuentra el entorno Java JRE en tu PC y este programa lo necesita 
para funcionar. Para descargarlo, pulsa en el botón y se abrirá tu navegador web
en la página oficial de Java (tendrás que instalarlo manualmente):

https://www.java.com/es/download

- "URL": escribe https://www.java.com/es/download

- Marca "Launch java app in the exe process" 

- Marca "Single instance" 

- No marques otras opciones

6.1.2 "Executable":

- "Executable Binary": escribe el nombre que tendrá tu archivo .exe,
por ejemplo, "SpectrumTaps2WindowsExeLauncher_Example.exe"

- "Executable Icon": puedes crear una imagen .png que no sea muy grande y
será mostrada como icono de la aplicación (por ejemplo 120x120 pixels), 
no es necesario que sea un archivo .ico. 

- Marca "Sets the executable folder as current directory of the application"

6.1.3 "Application"

- "Embedded jar settings": marca "Use an embedded jar" y selecciona el
archivo applet de Java .jar que creaste en el directorio "target"
en el paso 5.

- "Main class": haz click en "..." y selecciona la clase
"uk.bl.wa.access.qaop.Qaop"

- "Application Arguments" y "Class path" deben quedar vacíos.

6.1.4 No toques otros parámetros o submenús de JSmooth. 

6.1.5 Pulsa en el botón con el dibujo de un engranaje
y una ventana aparecerá. Si todo va bien un mensaje "Done"
aparecerá y ya tienes disponible tu archivo .exe para
distribuir.

En nuestro ejemplo de código fuente el archivo .exe generado es:

"SpectrumTaps2WindowsExeLauncher_Example.exe"

Consideración #1: algunas veces, dependiendo del grado de seguridad
del PC donde se instala JRE, el programa que instala JRE no es capaz
de incluir la variable de sistema HOME_JRE que apunta a la
carpeta donde esta instalado el Java Runtime Environment. 
Normalmente esto no sucede, pero en el caso de que pase, 
el usuario deberá incluir dicha variable manualmente en el 
sistema. En esta página web explican como hacerlo (en inglés):

https://confluence.atlassian.com/doc/setting-the-java_home-variable-in-windows-8895.html 

Consideración #2: un tema conocido por los desarrolladores Java 
que hacen Applets emebebidos en .exe para Windows es que
algunos programas antivirus son muy estrictos y marcan 
algunas veces los archivos .exe creados con este método como
portadores de virus. No sucede muy habitualmente, 
depende de la marca del antivirus, del nivel de 
restricciones que se haya marcado, etc. las reglas varían 
mucho entre antivirus. Este es un tema conocido por los
desarrolladores de Java embebido en archivos .exe pero la realidad es
que cuando ocurre poco se puede hacer, excepto que el usuario
marque el archivo de cara al antivirus como falso positivo para poder utilizarlo. 
