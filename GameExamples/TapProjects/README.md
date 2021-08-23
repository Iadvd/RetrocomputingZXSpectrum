# "SpectrumTap2WindowsExe" and "SpectrumTaps2WindowsExeLauncher" projects

<b>Important: these projects are customizations of the great Qaop ZX Spectrum Emulator
(https://github.com/ukwa/qaop) by Jan Bobrowski under a GPL-2.0 License.</b>

<b>Short descriptions:</b>
(versión en castellano se incluirá en breve)

<b>SpectrumTap2WindowsExe</b> will convert your ZX Spectrum .tap file into a 
single .exe Windows file. The single file contains both the .tap 
file and the Spectrum emulator. So no external ZX Spectrum emulator 
is required to play your game. 

<b>SpectrumTaps2WindowsExeLauncher</b> is a tamplate to create a 
single .exe Windows file that will have a main menu where you
can show all your ZX Spectrum games and the user can click one
and play it. The single file contains both the .tap files 
and the Spectrum emulator. So no external ZX Spectrum emulator is required. 

<b>Requirements:</b> the Java Runtime Environment (JRE)
must be installed in the PC.

<b>With gratitude to my friends that volunteered as testers
(in alphabetical order):</b>

Greenweb Sevilla: https://greenwebsevilla.itch.io/ 

Javi Ortiz: https://www.youtube.com/c/ElSpectrumeroJaviOrtiz

Roolandoo: https://roolandoo.itch.io/

# "SpectrumTap2WindowsExe"

<b>1 Tap file (48k) = 1 Windows Exe file (Java applet .jar wrapped)</b>

<b>The aim of this tool is providing the ZX Spectrum .tap developers a new
format to distribute their works. In this case for instance, 
you can distribute your .tap file in your website, or at itchi.io, etc.
but also you can provide the .tap file as a a Windows .exe file as well. 
(the target is Windows 10 and other former Windows versions, 
excluding XP and probably Windows 7 - untested -)</b>

With this tool you will be able to convert one ZX Spectrum 48k .tap file 
to a Java applet file that will be wrapped into a single Windows .exe file. 

This project is a customization of the great Qaop ZX Spectrum Emulator
(https://github.com/ukwa/qaop) by Jan Bobrowski under a GPL-2.0 License.

When the file is executed in Windows, the emulator screen 
is directly opening the .tap file into a single Windows screen,
so you can play it without the requirement of an external 
emulator program (because everything is already included
inside the file). 

<b>Requirements:</b> the file will be able to run in a Windows PC if the 
Java Runtime Environment (JRE) is aleady instaled. If it is not installed, 
the Exe file will let you download the JRE installer from the official 
Java site. The navigator will open and the download/install process
are manual.

The tool is a Java project, to be built with Maven via online 
commands. We provide both the Java project and the batch files
to run a Maven build.

https://Maven.apache.org/download.cgi

<b>The explanation is as follows:</b>

1. Copy the project folder "SpectrumTap2WindowsExe" including subfolders 
in your local PC

2. Put your desired .tap file into the resouces folder

src\main\resources

e.g let's imagine that the name is
"this_is_the_name_of_the_tap_file_at_resources_folder.tap"

In our example it is "TheHoarder_en.tap"

2.1 Edit the file:
src\main\java\uk\bl\wa\access\qaop\Qaop.java

- look for the following line...

tapname="";

...and change it with the name of your .tap .file , e.g.

tapname="this_is_the_name_of_the_tap_file_at_resources_folder.tap";

- look for the following line...

f.setTitle("This is the title of the screen");

...and change name of the title of the application screen.

that's all regarding the code.

3. Install Maven in a folder at the same level of the Java project
(i.e. in our example the name of the folder is "apache-maven-3.8.1"
but it will change depending on the version of Maven you
will install)

4. In the root of the project you will find three .bat files.

4.1. "mvn_cleaninstall.bat" is the one to test that the Java project does not
have syntax / library problems. If it finish correctly, 
then you can test the program or create the Applet .jar
file (that will be converted into a wrapped Windows .exe
file later). In our case the .bat contains this call:

.\apache-maven-3.8.1\bin\mvn clean install

4.2 "mvn_execjava.bat" is the one to test the application. It will 
run the .jar applet into a screen, so you can 
see the same result that later on happens when
you open the final Windows .exe file. Basically a Windows
screen opens and shows directly the game. No need
to make a Spectrum load "". etc. The emulator 
shows directly the main menu of the game. 
If the game appears and you can play smoothly
then the test is good. If the game does not
appear then there is a problem somewhere
in the code. 

Caveat: the base Qaop ZX Spectrum emulator Java applet 
does not let a full screen emulation due to image 
restrictions, so the game appears inside a screen with the
maximum playable size. 

In out case the .bat file contains this call:

.\apache-maven-3.8.1\bin\mvn exec:java

4.3 Finally "mvn_package.bat" will build the distributable 
Applet .jar that will include all the necessary 
files to be run as the independent .jar Applet
in a Windows PC. As it is a .jar Applet
it requires the Java Runtime Environment
installed on the PC where is going to be 
used. 

In out case, the .bat file contains this call:

.\apache-maven-3.8.1\bin\mvn clean package

5. The .jar file will appear in the "target"
folder with the name: 

"qaop-1.4.1-SNAPSHOT-jar-with-dependencies.jar"

6. To create a wrapped Windows .exe file do 
as follows:

6.1 Intall JSmooth in your PC:

http://jsmooth.sourceforge.net/download.php

Open it and make the following settings:

6.1.1 Skeleton: 

- Select "Windowed Wrapper"

- Message write a welcome message that will appear when it is required
to install the Java Runtime Environment. E.g.:

Welcome! Java JRE has not been found on your computer and it is required
to run this program. Do you want to download it? Click below and your
default web browser will open the official Java page:

https://www.java.com/es/download

- URL must have this address: https://www.java.com/es/download

- Check "Launch java app in the exe process" 

- Check "Single instance" 

- Other options unchecked

6.1.2 Executable:

- Executable Binary: write the name of the final .exe file,
e.g. "SpectrumTap2WindowsExe_game_example.exe"

- Executable Icon: you can create a small .png image file to be
shown as the application icon (e.g. 120x120 pixel), a .ico file 
is not required. 

- Check "Sets the executable folder as current directory of the application"

6.1.3 Application

- Embedded jar settings: check "Use an embedded jar" and add the 
file you built at step 5 inside the Embedded jar text box.

- Main class: click in to the "..." button and select 
uk.bl.wa.access.qaop.Qaop

- Application Arguments and Class path must remain empty.

6.1.4 Do not touch the default settings of other submenus 
of JSmooth. 

6.1.5 Click on the top "Compile" button (toothed gear icon)
and a small Window will appear and if everything is fine
a final "Done" message will appear and your .exe file 
is ready!

In our source code the .exe file is:

"SpectrumTap2WindowsExe_game_example.exe"

7. Now you have a .jar file wrapped into a Windows .exe
file. This is the file you can distribute. If the person
that downloads the .exe file does not have the Java
Runtime Environment (JRE) installed in the PC, the
.exe file will detect it and open the download
page. The user must install the JRE and the 
when the .exe file is started again the program
should work fine. 

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

8. Next steps:

Providing a .tap 128k solution.


# "SpectrumTaps2WindowsExeLauncher"

<b>Multiple .tap files = 1 Windows .exe Game Launcher file (Java applet .jar wrapped) Tool</b>

<b>The aim of this tool is providing the .tap developers a new
format to distribute their works. In this case for instance, 
you can distribute ALL your .tap files in ONE single .exe file
including a main menu where the user can select the game
to be launched. It is very useful to make compilations of games, 
for instance if you are a developer and you want to make 
an all-in-one game launcher of your titles. It will work 
with Windows 10 and other former versions, excluding XP and 
probably Windows 7 -untested-.</b>

This tool will create a Java applet file wrapped into 
a single Windows .exe file contaning the game launcher,
which is basically a first menu that appears when the application
is started and lets you select one of the games of your list,
that will be opened into a emulator screen in a new window. The
main menu also provides the "information" icon that will open
the default browser of your PC and will open the website where
the instructions of your game and controls are explained. 
We provide a complete Java source template to do this, 
and <b>there is an example of use at itch.io at this link</b>: 

https://furilloproductions.itch.io/furillo-productions-all-in-one-48k-2019-2021

This project is a customization of the great Qaop ZX Spectrum Emulator
(https://github.com/ukwa/qaop) by Jan Bobrowski under a GPL-2.0 License.

When the file is executed in Windows, the emulator screen 
is directly opening the game launcher into a single Windows screen,
so you can play all the games without the requirement of an external 
emulator program (because everything is already included
inside the single .exe file). 

<b>Requirements:</b> the file will be able to run in a Windows PC if the 
Java Runtime Environment is aleady instaled. If it is not installed, 
the Exe file will let you download the JRE installer from the official 
Java site. The navigator will open and the download/install process
are manual.

The tool is a Java project, to be built with Maven via online 
commands. We provide both the project and the batch files.

https://Maven.apache.org/download.cgi

<b>The explanation is as follows:</b>

1. Copy the project folder in your local PC

2. Put your desired .tap files into the Resouces folder
(in the source example we are providing just two 
.tap files as an example of use)

src\main\resources

Also put your launcher main menu background image and
the icon to be use for the application window there. 
i.e. in our source code these ones:

launcherbkg.png
launchericon.png

This image can be as you whish but in this example
it contains two lines of games including several
languages and information links. In our source code
example, the only link that will work is the 
game "The Hoarder", the others are not present.

2.1 Edit the file:

src\main\java\uk\bl\wa\access\qaop\Qaop.java

Here you will need to customize the following parts of the code:

2.1.1 Line 562 and 594
.setTitle("This is the title of your game launcher");

2.1.2 Line 584
//System.out.println(e.getX() + "," + e.getY());
Uncomment this line to know the position of the mouse 
when a click is done. It is required to customize 
the position of the icons on the screen depending
on your desing. 

2.1.3 Line 581
public void mousePressed(MouseEvent e) {

Inside this event we control the mouse clicks on the
screen, so they will open a second window with the .tap
file or the web browser showing the webpage including the
information of the game. In our source you can 
see three .tap files and one link available. 

You must customize these clicks in order to 
make then work in the places of your launcherbkg.png
file where you put the icons, so they will open
the .tap files you put at the "resources" folder.

2.1.4 Welcome message:

- Look for... 

// English version 
// Spanish version

...and change the welcome message that will appear when the main menu
of the game launcher is shown for the first time.

You need to use some time to make your own 
customization, but technically, that's all 
regarding the code.

3. Install Maven in a folder at the same level of the Java project
(i.e. in our example the name of the folder is "apache-maven-3.8.1")

4. In the root of the project you will see three .bat files.

4.1. "mvn_cleaninstall.bat" is one to test that the Java project does not
have syntax / library problems. If it finish correctly, 
then you can test the program or create the Applet .jar
file (that will be converted into a wrapped Windows .exe
file)

4.2 "mvn_execjava.bat" is the one to test the application. It will 
run the .jar applet into a screen, so you can 
see the same result than later on happens when
you open the final .exe file. Basically a Windows
screen opens and shows directly the main menu of the
game launcher. Then you can click the icons and
open the games into different screens or open the
information website of each game into your 
default web browser. No need to make a Spectrum load "". etc. 
The application shows directly the main menu of the launcher
and just clicking the game will start. 
If the main menu and the games appears and you can play smoothly
then the test is good. If not, there is a problem somewhere. 

Caveat: Qaop does not let a full screen 
emulation due to image restrictions, so 
the games will be shown into a screen with the
maximum playable size. 

4.3 Finally "mvn_package.bat" will build the distributable 
Applet .jar it includes all the necessary 
files to be run as independent .jar Applet
into a Windows PC. As it is a .jar Applet
it requires the Java Runtime Environment
installed on the PC where is going to be 
used. 

5. The .jar file will appear in the "target"
folder with the name 

"qaop-1.4.1-SNAPSHOT-jar-with-dependencies.jar"

6. To create a wrapped Windows .exe file do 
as follows:

6.1 Intall JSmooth in your PC:

http://jsmooth.sourceforge.net/download.php

Open it and make the following settings:

6.1.1 Skeleton: 

- Select "Windowed Wrapper"

- Message write a welcome message that will appear when it is required
to install the Java Runtime Environment. E.g.:

Welcome! Java JRE has not been found on your computer and it is required
to run this program. Do you want to download it? Click below and your
default web browser will open the official Java page:

https://www.java.com/es/download

- URL mast have this address: https://www.java.com/es/download

- Check "Launch java app in the exe process" 

- Check "Single instance" 

- Other options unchecked

6.1.2 Executable:

- Executable Binary: write the name of the final .exe file,
e.g. "My_Spectrum_games_launcher.exe"

- Executable Icon: you can create a small .png image file to be
shown as the application icon (e.g. 120x120 pixel), a .ico file 
is not required. 

- Check "Sets the executable folder as current directory of the application"

6.1.3 Application

- Embedded jar settings: check "Use an embedded jar" and add the 
file you built at step 5 inside the Embedded jar text box.

- Main class: click in to the "..." button and select 
uk.bl.wa.access.qaop.Qaop

- Application Arguments and Class path must remain empty

6.1.4 Do not touch the default settings of other submenus 
of JSmooth. 

6.1.5 Click on the top "Compile" button (toothed gear icon)
and a small Window will appear and if everything is fine
a final "Done" message will appear and your .exe file 
is ready!

7. Now you have a .jar file wrapped into a Windows .exe
file. This is the file you can distribute. If the person
that downloads the .exe file does not have the Java
Runtime Environment (JRE) installed in the PC, the
.exe file will detect it and open the download
page. The user must install the JRE and the 
when the .exe file is started again the program
should work fine. 

The name of the file in our example is:

"SpectrumTaps2WindowsExeLauncher_Example.exe"

<b>Caveat #1:</b> sometimes, depending on the PC the
JRE installer is not able to add the 
HOME_JRE system variable. Usually this is 
something automatic, but in some cases
the user must set the variable manually.
In the following url there is an explanation 
about how to do that step. 

https://confluence.atlassian.com/doc/setting-the-java_home-variable-in-windows-8895.html 

<b>Caveat #2:</b> is a very well known issue that 
some antivirus are very strict regarding the
wrapped .jar .exe files and sometimes a
false warning of virus detection appears. 
It does not happen usually, only sometimes
(depending on the antivirus, the level of
strictness of the rules is different) 
happens. This is a common issue for Java developers (as the
reader probably knows if is used to the 
Java development)

