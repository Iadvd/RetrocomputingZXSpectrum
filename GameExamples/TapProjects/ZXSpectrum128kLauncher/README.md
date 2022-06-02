# "ZX Spectrum 128k game launcher for Windows setup / ZX Spectrum 128k lanzajuegos .exe para Windows"

(Spanish version below the English version / versión en castellano debajo de la versión en inglés)

<b>English version</b>

<b>Important: this is a customization of the great JSpeccy Emulator
(https://github.com/jsanchezv/JSpeccy) by José Luis Sánchez.
It can be used ONLY for non-profit projects: i.e. the piece of software must be 
downloadable for free without paying anything.</b>

<b>Short description:</b>

<b>ZX Spectrum 128k game launcher setup</b> will convert your ZX Spectrum 128k .tap file into a 
single .exe Windows file. The single file contains both the .tap 
file and the Spectrum emulator. So no external ZX Spectrum emulator 
is required to play your game. 

<b>Requirements:</b> Java 9 or greater version and the Java Runtime Environment (JRE)
must be installed in the PC.

<b>With gratitude to my friends that volunteered as testers
(in alphabetical order):</b>

Javi Ortiz: https://www.youtube.com/c/ElSpectrumeroJaviOrtiz

Roolandoo: https://roolandoo.itch.io/

# "ZX Spectrum 128k game launcher setup"

<b>1 Tap file (48k or 128k) = 1 Windows Exe file (Java applet .jar wrapped)</b>

<b>The aim of this tool is providing the ZX Spectrum .tap developers a new
format to distribute their works. In this case for instance, 
you can distribute your .tap file in your website, or at itch.io, etc.
but also you can provide the .tap file as a a Windows .exe file as well. 
(the target is Windows 10 and other former Windows versions, 
excluding XP and probably Windows 7 - untested -)</b>

With this tool you will be able to convert one ZX Spectrum 48/128k .tap file 
to a Java applet file that will be wrapped into a single Windows .exe file. 

This project is a customization of the great JSpeccy Emulator
(https://github.com/jsanchezv/JSpeccy) by José Luis Sánchez.
It can be used ONLY for non-profit projects: i.e. the piece of software must be 
downloadable for free without paying anything.

When the file is executed in Windows, the emulator screen 
is directly opening the .tap file into a single Windows screen,
so you can play it without the requirement of an external 
emulator program (because everything is already included
inside the file). 

<b>Requirements:</b> the file will be able to run in a Windows PC if the 
Java (version 9 or greater) Runtime Environment (JRE) is aleady instaled. 

The tool is a Java project, to be built with Maven. 

<b>The explanation is as follows:</b>

1. Follow the instructions to create the JSpeccy jar file as 
explained by JSpeccy:

https://github.com/jsanchezv/JSpeccy

2. Once you get the environment working so you can build the
emulator, do the following changes.

2.1 Put your desired .tap file into the src\main\resources folder

src\main\resources

e.g let's imagine that the name is
"mytapfile.tap"

2.2 Put your desired .jar file icon into src\main\resources\icons folder

src\main\resources\icons

for instance we have added "launchericon.png"

2.3 replace the original src\main\java\gui\JSpeccy.java file with the
one we have modified.

This is the list of changes in this file from the original JSpeccy file:

2.3.1. A splash popup welcome message is added, including credits to the JSpeccy project and its author.

2.3.2. Only the main emulator screen of JSpeecy will appear, and the game will be loaded automatically.

2.3.3. funcion initEmulator is set to machine 128k, border mode 1, zoom 3.

2.3.4. You will have to modify the following places (search for them in the file):

	2.3.4.1 Put the same name as the .tap file you put in /resources folder:
	
	i = classLoader.getResourceAsStream("mytapfile.tap");
	
	2.3.4.2 Uncomment and rewrite this content according to your game requierements:
	
	// English version
	//setTitle("\"Name of your game\" by YourName (year) Spectrum 48/128K (credits to JSpeccy / José Luis Sánchez https://github.com/jsanchezv/JSpeccy)");
	
	// Spanish version
	//setTitle("\"Nombre de tu juego\" por TuNombre (año) Spectrum 48/128K (créditos a JSpeccy / José Luis Sánchez https://github.com/jsanchezv/JSpeccy)");
       
	2.3.4.3 Uncomment and rewrite this content according to your game requirements:
	
	// English version
	//JOptionPane.showMessageDialog(getContentPane(), "Welcome, and thanks for playing our games!  (^_^)\n\nPlease download this program for FREE ONLY from URL OF YOUR SITE \n\nWe do NOT distribute this program through other websites and we are NOT aware of them.\n\nThis ZX Spectrum game launcher is a customization of the JSpeccy Emulator\nhttps://github.com/jsanchezv/JSpeccy (by José Luis Sánchez)\n.\n\nWe hope you enjoy the experience!", JOptionPane.INFORMATION_MESSAGE );
	
	// Spanish version
	//JOptionPane.showMessageDialog(getContentPane(), "¡Bienvenido/a, y gracias por jugar a nuestros juegos!  (^_^)\n\nPor favor descarga este programa UNICAMENTE y de forma GRATUITA desde\nURL DE TUS JUEGOS\n\nNO distribuimos este programa desde otras páginas y NO sabemos de su existencia.\n\nEste lanzador de juegos de ZX Spectrum es una personalización del emulador\nJSpeccy https://github.com/jsanchezv/JSpeccy de José Luis Sánchez\n.\n\n¡Esperamos que disfrutes la experiencia!","\"Nombre de tu juego\" ZX Spectrum 48/128k", JOptionPane.INFORMATION_MESSAGE );

And that is all! No more changes really. Just build again the .jar file and that's it!
This version of the project when launched will open directly the .tap file included in the project.

3. To create a wrapped Windows .exe file you can use 
"launch4j" or other free wrapper of your choice.

Caveat #1: sometimes, depending on the PC the
JRE installer is not able to add the 
HOME_JRE system variable. Usually this is something 
automatic, but in some cases the user must set 
the variable manually. In the following url there is an explanation 
about how to do that step. 

https://confluence.atlassian.com/doc/setting-the-java_home-variable-in-windows-8895.html 

Caveat #2: is a very well known issue that 
some antivirus are very strict regarding the
wrapped .jar .exe files and sometimes a
false warning of virus detection appears. 
It does not happen usually, only sometimes
(depending on the antivirus, the level of
strictness of the rules is different) 
happens. This is a common issue for Java developers (as the
reader probably knows if is used to the 
Java development)

<b>Versión en castellano</b>

<b>Importante: este proyecto es una personalización del gran emulador JSpeccy
(https://github.com/jsanchezv/JSpeccy) de José Luis Sánchez.
SOLO puede ser usado en proyectos en los que el software pueda descargarse de forma gratuita.</b>

<b>Descripción corta:</b>

<b>ZX Spectrum 128k lanzajuegos .exe para Windows</b>. El objetivo es convertir 
un archivo .tap de ZX Spectrum 48k o 128k en un único archivo .exe ejecutable en 
Windows 10. El archivo único contiene el archivo .tap y el emulador. 
no es necesario ningun otro archivo más para jugar.

<b>Requerimientos:</b> Java 9 o superior y el Java Runtime Environment (JRE)
instalado correctamente en el pc.

<b>Con agradecimiento a los testers 
(en orden alfabético):</b>

Javi Ortiz: https://www.youtube.com/c/ElSpectrumeroJaviOrtiz

Roolandoo: https://roolandoo.itch.io/

# "ZX Spectrum 128k lanzajuegos .exe para Windows"

<b>1 archivo .tap file (48k o 128k) = 1 archivo .exe de Windows 10 (es un applet Java .jar convertido a .exe)</b>

<b>El objetivo de esta herramienta es aportar a los desarrolladores de juegos (o aplicaciones) en formato .tap para 
emulador de ZX Spectrum 48/128k un nuevo formato alternativo para distribuir su trabajo. Por ejemplo, puedes distribuir 
tu archivo .tap en tu página web, o en Itch.io, etc. y habilitar para descarga aparte del archivo .tap un archivo 
ejecutable con el juego en formato .exe de Windows. El archivo .exe funciona en Windows 10 o en versiones previas 
que sean más o menos actuales; por tanto, queda excluído Windows XP y probablemente Windows 7 - que no hemos testeado -.</b>

<b>Importante: este proyecto es una personalización del gran emulador JSpeccy
(https://github.com/jsanchezv/JSpeccy) de José Luis Sánchez.
SOLO puede ser usado en proyectos en los que el software pueda descargarse de forma gratuita.</b>

When the file is executed in Windows, the emulator screen 
is directly opening the .tap file into a single Windows screen,
so you can play it without the requirement of an external 
emulator program (because everything is already included
inside the file). 

<b>Requerimientos:</b> Windows 10 y Java (version 9 o superior) con su Runtime Environment (JRE) correctamente habilitado. 

Es un proyecto de Java construido con Maven.

<b>Sigue estos pasos:</b>

1. Primero crea el .jar de JSpeccy tal y como lo explica su autor en su proyecto:

https://github.com/jsanchezv/JSpeccy

2. Una vez hayas conseguido crear el archivo .jar de JSpeccy, haz los siguientes cambios en el proyecto Java.

2.1 Primero pon el archivo .tap que quieres lanzar en la carpeta del proyecto src\main\resources\

src\main\resources

Por ejemplo "mytapfile.tap"

2.2 Pon tu icono favorito para la aplicación .jar en src/main/resources/icons

src\main\resources\icons

Por ejemplo el nuestro es "launchericon.png"

2.3 Cambiar el archivo src/main/java/gui/JSpeccy.java por el que te ponemos en este directorio.

Esta es la lista de cambios de nuestra version de JSpeccy.java:

2.3.1. Aparece un ensaje popup al ejecutar, incluyendo créditos al proyecto JSpeccy y a su autor.

2.3.2. Se abre la pantalla principal del emulador, y el juego se lanza(carga) automáticamente.

2.3.3. La funcion "initEmulator" se ha fijado a emular 128k, mode border 1, zoom 3.

2.3.4. Ya sólo queda personalizar este código (búscalo dentro del archivo):

	2.3.4.1 Nombre del archivo .tap que esta en /resources:
	
	i = classLoader.getResourceAsStream("mytapfile.tap");
	
	2.3.4.2 Quita comentarios y escribe correctamente este contenido conforme a tu juego:
	
	// English version
	//setTitle("\"Name of your game\" by YourName (year) Spectrum 48/128K (credits to JSpeccy / José Luis Sánchez https://github.com/jsanchezv/JSpeccy)");
	
	// Spanish version
	//setTitle("\"Nombre de tu juego\" por TuNombre (año) Spectrum 48/128K (créditos a JSpeccy / José Luis Sánchez https://github.com/jsanchezv/JSpeccy)");
       
	2.3.4.3 Quita comentarios y escribe correctamente este contenido conforme a tu juego:
	
	// English version
	//JOptionPane.showMessageDialog(getContentPane(), "Welcome, and thanks for playing our games!  (^_^)\n\nPlease download this program for FREE ONLY from URL OF YOUR SITE \n\nWe do NOT distribute this program through other websites and we are NOT aware of them.\n\nThis ZX Spectrum game launcher is a customization of the JSpeccy Emulator\nhttps://github.com/jsanchezv/JSpeccy (by José Luis Sánchez)\n.\n\nWe hope you enjoy the experience!", JOptionPane.INFORMATION_MESSAGE );
	
	// Spanish version
	//JOptionPane.showMessageDialog(getContentPane(), "¡Bienvenido/a, y gracias por jugar a nuestros juegos!  (^_^)\n\nPor favor descarga este programa UNICAMENTE y de forma GRATUITA desde\nURL DE TUS JUEGOS\n\nNO distribuimos este programa desde otras páginas y NO sabemos de su existencia.\n\nEste lanzador de juegos de ZX Spectrum es una personalización del emulador\nJSpeccy https://github.com/jsanchezv/JSpeccy de José Luis Sánchez\n.\n\n¡Esperamos que disfrutes la experiencia!","\"Nombre de tu juego\" ZX Spectrum 48/128k", JOptionPane.INFORMATION_MESSAGE );

¡Y eso es todo! No hace falta nada más. ¡Construye de nuevo el archivo .jar y se acabó!
Esta versión del .jar de JSpeccy abrirá directamente el archivo .tap incluido en el proyecto.

3. Para crear un archivo .exe de Windows 10 puedes usar 
"launch4j" u otra aplicación similar.

Consideración #1: algunas veces, dependiendo del grado de seguridad del PC donde se instala JRE, el programa que instala JRE no es capaz de incluir la variable de sistema HOME_JRE que apunta a la carpeta donde esta instalado el Java Runtime Environment. Normalmente esto no sucede, pero en el caso de que pase, el usuario deberá incluir dicha variable manualmente en el sistema. En esta página web explican como hacerlo (en inglés): 

https://confluence.atlassian.com/doc/setting-the-java_home-variable-in-windows-8895.html 

Consideración #2: un tema conocido por los desarrolladores Java que hacen Applets emebebidos en .exe para Windows es que algunos programas antivirus son muy estrictos y marcan algunas veces los archivos .exe creados con este método como portadores de virus. No sucede muy habitualmente, depende de la marca del antivirus, del nivel de restricciones que se haya marcado, etc. las reglas varían mucho entre antivirus. Este es un tema conocido por los desarrolladores de Java embebido en archivos .exe pero la realidad es que cuando ocurre poco se puede hacer, excepto que el usuario marque el archivo de cara al antivirus como falso positivo para poder utilizarlo.

