# Retrocomputing ZX Spectrum
Example applications and games, most of them to be used with the TCP/IP Virtual Joystick for Android application, others just for fun!

These examples are ZX Spectrum (48K or above) emulation files, most of them to test the functionalities of the TCP/IP Virtual Joystick for Android application. So you will need our TCP/IP Virtual Joystick for Android app. to test them (its totally free!). Download it for your Android device at:

https://play.google.com/store/apps/details?id=com.iadvd.android.tcpipvirtualjoystick

The TCP/IP Virtual Joystick for Android app. will ask you for an IP address of your local network where there must be an application (for instance see tcpipsrv_basic.c) already listening to the 8081 port to negotiate a TCP connection with the Android Virtual Joystick.

There are three interviews in Spanish talking about this project at "El Spectrumero" Javi Ortiz's Videoblog (click on the image):

2019/08/18:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/gfIxj7Wk8Kk/0.jpg)](https://www.youtube.com/watch?v=gfIxj7Wk8Kk)

2019/05/26:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/CVln3tfyNt0/0.jpg)](https://www.youtube.com/watch?v=CVln3tfyNt0)

2020/05/25:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/3n2i4w2jnVA/0.jpg)](https://www.youtube.com/watch?v=3n2i4w2jnVA)

2020/08/01:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/lYe5c4uJvLY/0.jpg)](https://www.youtube.com/watch?v=lYe5c4uJvLY)

2020/09/12:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/NmSLXDoSBLE/0.jpg)](https://www.youtube.com/watch?v=NmSLXDoSBLE)

# Basic ZX Spectrum TCP/IP Server Project

The example file "tcpipsrv_basic.c" when compiled creates the tcpipsrv_basic.tap file (ZX Spectrum emulated program) that is a server side TCP/IP listener on the port 8081 for a ZX Spectrum computer. The tcpipsrv_basic.tap file (is already available in the repository if you do not want to compile it again by yourself) can be run in the Fuse Spectrum Emulator with the Spectranet peripheral emulation. It is expected also to run in a real ZX Spectrum with a real Spectranet peripheral (if converted to a tape or a wav file for the EAR input channel of the ZX Spectrum).

You will need to install in your computer both the Fuse Spectrum emulator:

http://fuse-emulator.sourceforge.net/

and its Spectranet peripheral emulator:

https://sourceforge.net/p/fuse-emulator/wiki/Spectranet%20Emulation/

The Spectranet preripheral is a ZX Spectrum device able to provide network connection for a ZX Spectrum machine. More info here:

http://spectrum.alioth.net/doc/index.php/Main_Page

So basically, a ZX Spectrum (emulated or real) with a Spectranet peripheral can manage a TCP/IP connection, thus we can use the TCP/IP Virtual Joystick for Android app. to send the information of the actions of the joystick to the Spectrum application (usually it is an 8-bit game, of course!).

We use several tools to make the examples, but the main ones are the Spectranet socket libraries and the Z80 Development Kit:

https://www.z88dk.org/forum/

https://sourceforge.net/projects/z88dk/files/

Remark: the library used by the Spectranet C projects, libsocket, needs to be recopiled if it is going to be used with newer versions of the compiler (as the one we link above). For this reason we are including the compiler too in those example projects where the latest version will not work, because there are compatibility issues between old libraries (not so well mantained currently) and new compiler versions.

Please review the comments on each project to understand the correct environment for the compiler. 

We are providing the .tap files directly so you do not need to recompile the projects, but if you want to learn or reuse the code, go ahead, under a copyleft license CC BY-NC-SA 3.0. So please refer us in your future projects if you reuse these libraries with a link to this Github repository. Thank you!

https://creativecommons.org/licenses/by-nc-sa/3.0/es/

# Ok, let us test the Virtual Joystick! How does tcpipsrv_basic.c (ZX Spectrum program tcpipsrv_basic.tap file) works? 

The TCP/IP Virtual Joystick for Android app. is able to connect to a TCP/IP server application listening at port 8081. And that is what tcpipsrv_basic.tap does. 

The connection protocol is as follows:

1) First start (open in Fuse emulator that has the Spectranet peripheral emulator working and the TCP/IP port 8081 open without firewalls) the server side application tcpipsrv_basic.tap, that will be listening to the port 8081.

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/tcpipsrv_basic.tap_image1.png)

2) Then open the TCP/IP Virtual Joystick for Android app.

3) The Virtual Joystick app. will look for a valid TCP connection into the provided IP (where the ZX Spectrum machine or the Fuse emulator is), at port 8081.

4) The server side app. tcpipsrv_basic.tap will detect the request for connection and will create a TCP/IP socket and will open it. Once the connection is obtained, the Virtual Joystick will send a test message to the server side app. with the word 'START'. Then tcpipsrv_basic.tap can use that first incoming message to know that the connected aplication is a TCP/IP Virtual Joystick for Android app. (in the example tcpipsrv_basic.tap we are just accepting the message and assuming that it is a Virtual Joystick without any special check).

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/tcpipsrv_basic.tap_image2.png)

5) Then the Virtual Joystick will expect the server side app. tcpipsrv_basic.tap to send the word 'TCPIPJOYSTICK' or 'TCPIPJOYSTICKSPECTRUM' in this case (to show a nice background image in the Android application side).

6) If the word arrives, then we have found a server side Virtual Joystick application; in other case, it is not a correct TCP connection so the Virtual Joystick will close the connection.

7) Once the correct connection has been confirmed, the TCP/IP Virtual Joystick for Android application will start sending messages to the server side app. tcpipsrv_basic.tap each time an event happens (UP, RIGHT, BUTTON1, etc.)\n\n8. tcpipsrv_basic.tap will read those messages and will show the actions on the ZX Spectrum monitor screen (Fuse emulator window or a TV in case of using a real machine). 

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/tcpipsrv_basic.tap_image3.png)

If the TCP connection is lost, the server application tcpipsrv_basic.tap detects it and enter again in a listening for a new connection status. You will need to close the TCP/IP Virtual Joystick for Android app. (at least in the present version), and then open it again to create again a TCP/IP channel with the server side application.

So we are controling the ZX Spectrum program from a smaller Android device, where the TCP/IP Virtual Joystick is installed. 

You just need the Android device where the Virtual Joystick is running connected to your WiFi local network and put your server side app. tcpipsrv_basic.tap in the same network.

Be aware that you will need to review if the server side application computer (e.g. if you are using Fuse Zpectrum emulator this can happen) is using a firewall. You will need to open at least the TCP port 8081 if there is a firewall. If not, the application will not be able to negotiate the TCP/IP protocol.

# Great, but I want to play games! Are there cool games adapted to use the TCP/IP Virtual Joystick for Android app.? 

Yes!!!! It is possible to play homebrew games that have been adapted to this TCP/IP interface, connected through the Spectranet peripheral (e.g. if your 8-bit game can be played by using a keyboard, a Kempston Joystick or a Sinclair Joystick you can also add another option for a TCP/IP Virtual Joystick for Android app.). It should work as well with a real ZX Spectrum computer and a real Spectranet peripheral.

And here they are the first ones! We have adapted several games from the famous Spanish Spectrum scene group The Mojon Twins:

http://www.mojontwins.com/juegos_mojonos/

All of them Powered by The Mojon Twins La Churrera and also copyleft The Mojon Twins under a CC BY-NC-SA 3.0 license. So all credits go to them. These are the games: 

1. "Trabajo Basura (Dire Job)" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/tb

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/trabajo-basura-dire-job/

2. "Sir Ababol" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/ababol

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/sir-ababol/

3. "Cheril Perils" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/perils

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/cheril_perils/

4. "Horace Goes To The Tower" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/horace

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/1773-2/

5. "Zombie Calavera" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/calavera

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/zombie-calavera-prologue/

6. "Cadàveriön" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/cadaver

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/cadaverion/

7. "Viaje al Centro de la Napia" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/viaje

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/viaje-al-centro-de-la-napia/

8. "Tenebra Macabre" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/tm

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/2013/10/31/tenebra-macabre-nuestro-juego-para-halloween/

9. "Lala Prologue" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/lala

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/lala-prologue/

10. "Moggy Adventure" TCP/IP Virtual Joystick for Android compatible version:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/moggya

Original version from the Mojon Twins (not compatible with the TCP/IP Virtual Joystick for Android app.) including an explanation of the game):

http://www.mojontwins.com/juegos_mojonos/moggy-adventure/

In the same way, you can download and reuse our code for your own projects (copyleft license CC BY-SA 4.0).

We have also developed the following games (well, so far three!) explicity to promote the use of the TCP/IP Virtual Joystick for Android app. and show that is quite easy to prepare some games to use the wireless joystick:

1. "Rade Blunner Ep.1" TCP/IP Virtual Joystick for Android compatible version (in case you do not have the Android joystick we have prepared as well a .tap file with a "classical" version for the usual Keyboard, Kempston and Sinclair joysticks, so everybody can play this game!):

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/RadeBlunner

2. "Birdy Cantabile" TCP/IP Virtual Joystick for Android compatible version (in case you do not have the Android joystick we have prepared as well a .tap file with a "classical" version for the usual Keyboard, Kempston and Sinclair joysticks, so everybody can play this game!):

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/BirdyCantabile

3. "Rade Blunner Ep.2" TCP/IP Virtual Joystick for Android compatible version (in case you do not have the Android joystick we have prepared as well a .tap file with a "classical" version for the usual Keyboard, Kempston and Sinclair joysticks, so everybody can play this game!):

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/RadeBlunner2

4. "Moon's Fandom Festival" mini graphic adventure, TCP/IP Virtual Joystick for Android compatible version (in case you do not have the Android joystick we have prepared as well a .tap file with a "classical" version for the usual Keyboard, Kempston and Sinclair joysticks, so everybody can play this game!):

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/MoonsFandomFestival

# Do you have more games apart from those above? 

Yes but they are not compatible with the TCP/IP Virtual Joystick. So far:

1. "Moon and The Pirates" mini graphic adventure, including a .tap file with a "classical" version for the usual Keyboard, Kempston and Sinclair joysticks, so everybody can play this game, in English or Spanish!:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/MoonAndThePirates

2. "Federation Z", a space adventure, done under the Furillo Productions team (Molomazo & IADVD) including a .tap file with a "classical" version for the usual Keyboard, Kempston and Sinclair joysticks, so everybody can play this game, in English or Spanish!:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/FederationZ

3. "FlappyClive, 80th birthday special", a "Flappy Bird" style game featuring a badges/trophies/achievements extension for the MK1-La Churrera engine, done under the Furillo Productions team (Molomazo & IADVD) including a .tap file with a "classical" version for the usual Keyboard, Kempston and Sinclair joysticks, so everybody can play this game, in English or Spanish!:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/FlappyClive

4. "ENIGMATIK / ЭНИГМАТИК", the most difficult brain-teaser of 2020, made with La Churrera engine, and done under the Furillo Productions team (Molomazo & IADVD with the collaboration of Jae Tanaka and Furichan) including a .tap file in English, Spanish, Portuguese and Russian!:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/Enigmatik

# I can see games in my tv screen and play wireless with the app. Spectacol for Android + Google Chromecast... so what is the point of using the TCP/IP Virtual Joystick for Android app.?

We really love and enjoy Spectacol! It is a great emulator for Android (indeed is based on the Fuse emulator), and you can use it to play wireless using Google Chromecast to share your device screen with your TV screen. The difference is that in that case, a) Spectacle is the owner of the virtual joystick, and it is emulating a Kempston, Sinclair or other type of joystick, it is not adding a new interface. And b) you will see in the screen the virtual joystick under the game, and that sometimes will not let you focus on playing the game. 

In the case of the TCP/IP Virtual Joystick for Android app., it is directly the Spectrum game / application the owner of the control of the peripheral, so you will not see the virtual joystick over the image of the game. The joystick remains in your Android device, and the television or the Fuse simulator screen will only show the game (as it happens with the standard / classical joysticks, you do not see them on the screen, because they are physically in your hand while you play!). 

Besides, our application and the adapted games can be played in a real ZX Spectrum using a Spectranet peripheral, so you can play wireless using a real ZX Spectrum machine and not an emulation. We think that this is an interesting and new approach.

# The TCP/IP Virtual Joystick for Android application is Spectranet 8-bit Network File System compatible

Yes!! The TCP/IP Virtual Joystick for Android app. has a 8-bit Spectranet-compatible local network File Server. Please check the details in this link:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/SpectranetTNFS

# A final message to ZX Spectrum game developers

The TCP/IP Virtual Joystick for Android compatible functions are written in C for the z88dk compiler. They are really very easy to use, do not be afraid and add them to your Spectrum games, it is cool to have a wireless joystick version, isn't it? If you make some Spectrum 8-bit games or apps. using our code please let us know, we will be very happy to know that this is useful for retrocomputing fans!
