# RetrocomputingZXSpectrum
Example applications to be use with Android TCP/IP Virtual Joystick

This examples are ZX Spectrum (48K or above) emulation files, to test the functionalities of the Android TCP/IP Virtual Joystick application. So you will need our Android TCP/IP Virtual Joystick to test them (its totally free!). Download it for your Android device at:



The Android TCP/IP Virtual Joystick will ask you for an IP address of your local network where there must be an application (for instance see tcpipsrv_basic.c) already listening to the 8081 port to negotiate a TCP connection with the Android Virtual Joystick.

The example file "tcpipsrv_basic.c" when compiled creates a .tap file that is a server side TCP/IP listener on the port 8081 for a ZX Spectrum computer. The tcpipsrv_basic.tap file (is already available in the repository if you do not want to compile it again by yourself) can be run in the Fuse Spectrum Emulator with the Spectranet peripheral emulation. It is expected also to run in a real ZX Spectrum with a real Spectranet peripheral (if converted to a tape or a wav file for the EAR input channel of the ZX Spectrum).

You will need to install in your computer both the Fuse Spectrum emulator:

http://fuse-emulator.sourceforge.net/

and its Spectranet peripheral emulator:

https://sourceforge.net/p/fuse-emulator/wiki/Spectranet%20Emulation/

The Spectranet preripheral is a ZX Spectrum device able to provide network connection for a ZX Spectrum machine. More info here:

http://spectrum.alioth.net/doc/index.php/Main_Page

So basically, a ZX Spectrum (emulated or real) with a Spectranet peripheral can manage a TCP/IP connection, thus we can use an Android TCP/IP Virtual Joystick and send the information of the actions of the joystick to the Spectrum application (usually it is an 8-bit game, of course!).

We use several tools to make the examples, but the main ones are the Spectranet socket libraries and the Z80 Development Kit:

https://www.z88dk.org/forum/

Remark: the library used by the Spectranet C projects, libsocket, needs to be recopiled if it is going to be used with newer versions of the compiler. For this reason we are including the compiler too in the projects, because there are compatibility issues between old libraries (not so well mantained currently) and new compiler versions.

Please review the comments on each project to understand the correct environment for the compiler. 

We are providing the .tap files directly so you do not need to recompile the projects, but if you want to learn or reuse the code, go ahead, under a copyleft license CC BY-NC-SA 3.0. So please refer us in your future projects if you reuse these libraries with a link to this Github repository. Thank you!

https://creativecommons.org/licenses/by-nc-sa/3.0/es/

# Ok, let us test the Virtual Joystick! how does tcpipsrv_basic.c (ZX Spectrum program tcpipsrv_basic.tap file) works? 

The Android TCP/IP Virtual Joystick is able to connect to a TCP/IP server application listening at port 8081. And that is what tcpipsrv_basic.tap does. 

The connection protocol is as follows:

1) First start (open in Fuse emulator) the server side application tcpipsrv_basic.tap, that will be listening to the port 8081.

2) Then open the Android TCP/IP Virtual Joystick.

3) The Virtual Joystick app. will look for a valid TCP connection into the provided IP, port 8081.

4) Once the connection is obtained, it will send a test message to the server side app. with the word 'START'. tcpipsrv_basic.tap can use that first incoming message to know that the connected aplication is an Android TCP/IP Virtual Joystick (in the example we are just accepting the message and assuming that it is a Virtual Joystick).

5) Then the Virtual Joystick will expect the server side app. tcpipsrv_basic.tap to send the word 'TCPIPJOYSTICK' or 'TCPIPJOYSTICKSPECTRUM' in this case (to show a nice background image in the Android application side).

6) If the word arrives, then we have found a server side Virtual Joystick application; in other case, it is not a correct TCP connection so the Virtual Joystick will close the connection.

7) Once the correct connection has been confirmed, the Android TCP/IP Virtual Joystick application will start sending messages to the server side app. tcpipsrv_basic.tap each time an event happens (UP, RIGHT, BUTTON1, etc.)\n\n8. tcpipsrv_basic.tap will read those messages and will show the actions on the ZX Spectrum monitor screen (Fuse emulator window or a TV in case of using a real machine). 

If the TCP connection is lost, the server application tcpipsrv_basic.tap detects it and enter again in a listening for a new connection status. You will need to close the Android TCP/IP Virtual Joystick app. (at least in the present version), and then open it again to create again a TCP/IP channel with the server side application.

So we are controling the ZX Spectrum program from a smaller Android device, where the TCP/IP Virtual Joystick is installed. 

You just need the Android device where the Virtual Joystick is running connected to your WiFi local network and put your server side app. tcpipsrv_basic.tap in the same network.

Be aware that you will need to review if the server side application computer (e.g. if you are using Fuse Zpectrum emulator this can happen) is using a firewall. You will need to open at least the TCP port 8081 if there is a firewall. If not, the application will not be able to negotiate the TCP/IP protocol.

It is possible to play homebrew games that have been adapted to this TCP/IP interface, connected through the Spectranet peripheral (e.g. if your 8-bit game can be played by using a keyboard, a Kempston Joystick or a Sinclair Joystick you can also add another option for an Android TCP/IP Virtual Joystick). It should work as well with a real ZX Spectrum computer and a real Spectranet peripheral.

For instance, we are adapted several games from the famous Spanish Spectrum scene group The Mojon Twins:

http://www.mojontwins.com/juegos_mojonos/

All of them Powered by The Mojon Twins La Churrera and also copyleft The Mojon Twins under a CC BY-NC-SA 3.0 license. So all credits go to them. 

In the same way, you can download and reuse our code for your own projects (copyleft license CC BY-SA 4.0).

If you make some Spectrum 8-bit games or apps. using these libraries please let us know, we will be very happy to know if this is useful for retrocomputing fans!
