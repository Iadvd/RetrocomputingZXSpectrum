# Trabajo Basura (Dire Job)

# Powered by The Mojon Twins La Churrera and also copyleft The Mojon Twins under a CC BY-NC-SA 3.0 license. So all credits go to them.

This folder contains the game Trabajo Basura (Dire Job), Android TCP/IP Virtual Joystick compatible version.

Original version from the Mojon Twins (including an explanation of the game): http://www.mojontwins.com/juegos_mojonos/trabajo-basura-dire-job/

# How to play the .tap file?

1. Install Fuse ZX Spectrum emulator + Spectranet emulator. Of Spectranet is correctly installed you will get a local IP for the Spectrum.

2. Download tb.tap and load it into Fuse. You will see the loading screen and then a text screen saying: "Trabajo Basura. Android Virtual Joystick compatible version. Wait or any key to cancel."

3. Now open your Android TCP/IP Virtual Joystick application. Your Android device must be in the same local network (using WiFi) than the computer where the Fuse emulator is or the ZX Spectrum connected through Spectranet is. The application will ask you the IP that Spectranet is using (or if you do not know it you can write an IP of the same local network to start searching from it).

4. When the Virtual Joystick app. arrives to the IP that is using Spectranet, the game wil detect the joystick and connect to it. The game's Main Menu will appear. 

5. Select keyboard or any other input, it does not matter, the virtual joystick will be available in any case.

6. If you close the Android application, the connection is lost. You will need to load again the game and start from step 2.

# For developers: How to compile/reuse the .tap file again? (not required to play the game)

1. In your Z88dk folder (e.g. C:\z88dk10) unrar or unzip directly the content of "Mojon-Twins--Trabajo-Basura--src.zip". You should be using The Mojon Twins adapted version of the compiler (all credits to The Mojon Twins):

https://github.com/mojontwins/MK1

2. Then download the rest of individual files and copy them to the same folder (this will overwrite some files, do not worry).

3. Use "make.bat tb" command to create again the .tap file if you wish so.

