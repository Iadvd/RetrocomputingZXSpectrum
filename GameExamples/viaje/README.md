# Viaje al Centro de la Napia

# Powered by The Mojon Twins La Churrera and also copyleft The Mojon Twins under a CC BY-NC-SA 3.0 license. So all credits go to them.

This folder contains the game Trabajo Basura (Dire Job), Android TCP/IP Virtual Joystick compatible version. Caveat: It does not include the main music theme.

Original version from the Mojon Twins (including an explanation of the game): 

http://www.mojontwins.com/juegos_mojonos/viaje-al-centro-de-la-napia/

# How to play the .tap file?

1. Install Fuse ZX Spectrum emulator (use the emulation of the 48K version)  + Spectranet emulator. If Spectranet is correctly installed you will get a local IP for the Spectrum. You will need to verify that the computer is not using a firewall or at least that the port 8081 is open and available to be used for a TCP/IP protocol connection. And of course: if you are the lucky possesor of a real Spectrum 48k machine (or greater version) and a real Spectranet peripheral, then you can also continue to step 2!!

2. Download viaje.tap and load it into Fuse. You will see the loading screen and then a text screen saying: "Viaje al Centro de la Napia. Android Virtual Joystick compatible version. Wait or any key to cancel." (if you press any kay in this moment, the game will not use the Virtual Joystick, so just wait). And again, if you are the lucky possesor of a real Spectrum + Spectranet (not an emulation) then you will need any program able to conver the .tap file into a wav / sound file, so you can load it through the EAR input in the classical way, or if you have a .tap loader device in the expansion port, justo copy the .tap file to your peripheral and load it to memory from there.

3. Now open your Android TCP/IP Virtual Joystick application. Your Android device must be in the same local network (using WiFi) than the computer where the Fuse emulator is or the ZX Spectrum connected through Spectranet is. The application will ask you the IP that Spectranet is using (or if you do not know it you can write an IP of the same local network to start searching from it).

4. When the Virtual Joystick app. arrives to the IP that is using Spectranet, the game wil detect the joystick and connect to it. The game's Main Menu will appear. 

5. Select keyboard or any other input, it does not matter, the virtual joystick will be available in any case. The controls are:

      O / joystick left: run left.

      P / joystick right: run right.

      Q,SPACE / joystick fire (Red Button or Green Button): jump.

6. If you close the Android application, the connection is lost. You will need to load again the game and start from step 2.

# For developers: How to compile/reuse the .tap file again? (not required to play the game)

1. In your Z88dk folder (e.g. C:\z88dk10) unrar directly the content of "Mojon-Twins--Viaje-al-centro-de-la-napia--src.rar". You should be using The Mojon Twins adapted version of the compiler (all credits to The Mojon Twins):

https://github.com/mojontwins/MK1

2. Then download the rest of individual files and copy them to the same folder (this will overwrite some files, do not worry).

3. Use "make.bat viaje" command to create again the .tap file if you wish so.


