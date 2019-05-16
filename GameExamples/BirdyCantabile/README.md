# Birdy Cantabile: A Musical Puzzle

# Powered by The Mojon Twins La Churrera and also copyleft Iadvd under a CC BY-NC-SA 3.0 license.

(A presentation in Spanish of this game is available in this link https://foro.speccy.org/viewtopic.php?f=6&t=5336)

This folder contains the game Birdy Cantabile in two versions: the Android TCP/IP Virtual Joystick compatible version and a normal version for those who do not have the Spectranet compatible TCP/IP Virtual Joystick.

This is a first release, is you find bugs please let us know (should be fine, we have tested it, but who knows...)

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/GameExamples/BirdyCantabile/BCT1g.png)

# Technical details:

Game concept: Iadvd (after seeing a sparrow bathing in a pond...)

Loading, Title and Ending Screens: Iadvd (Powered by La Churrera by The Mojon Twins)

Sprites and Tiles: Iadvd based on samples from La Churrera by The Mojon Twins.

Music: Iadvd

"Volga" song: inspired on some Russian style piano C# scales.

"Spain" song: inspired on Spanish Composer Manuel de Falla's moods and motifs.

Sounds: BeepFX (by Shiru)

Version: Spectrum 48K (or greater in 48K mode)

Powered by La Churrera by The Mojon Twins and splib2 by Alvin Albrecht:

https://github.com/mojontwins/MK1

Dylan Smith's Spectranet compatible:

http://spectrum.alioth.net/doc/index.php/Main_Page

Iadvd's Android TCP/IP Virtual Joystick compatible:

https://play.google.com/store/apps/details?id=com.iadvd.android.tcpipvirtualjoystick

Uses aPPack decompressor by dwedit, adapted by Utopian & optimized by Metalbrain
Music tracks composed in Beepola

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/GameExamples/BirdyCantabile/BCT2.png)

# Story

Birdy is a little sparrow who wants to become a music conductor. Today is his first concert! After a lot of rehearsal, all the little birds gathered in the Main Hall to watch Birdy's performance.

But what is this...!? Due to the flapping wings of all the little birds the score has flown away! Each page of the score is somewhere in the eight rehearsal halls.

Birdy needs to recover the eight pages and put them in the music stand in the correct order, but how can we know which page is the good one?

Fortunately, some little birds are helping Birdy. On each hall there is a little music stand, there you can listen to the page of the score that is lost in that room. The birds will tell you if it is the page you need to take!

Be careful to take the pages of the score in the correct order. If not, when you finally play the score, the music will not make the little birds so happy. 

Somebody has left anti-roosting spike strips here and there! What a shame! Be careful, we are sure you will prevail with the kind support of the little birds. 

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/GameExamples/BirdyCantabile/BC1.png)

# The Game

Each time you play, you need to solve a musical puzzle. There are two different songs / scores (the name of the song that will be played in the next game is shown in the main menu). Each time you play the game the score will be one of those two. The pages of the score are randomly spread along the halls, so each game is a totally different puzzle! 

Find the eight pages of the music score with the help of the little birds. If you put the pages in the correct order, you will succeed in your performance. If you are not so good do not worry: there are different endings depending on your performance. Try them all for fun! 

Be careful getting too close to the anti-roosting spike strips or you will lose your energy. The little birds will show you their support leaving some red hearts here and there. Take them when you find them to recover your energy.

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/GameExamples/BirdyCantabile/BC2.png)

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/GameExamples/BirdyCantabile/BC3.png)


# How to play the .tap file?

If you do not have an Android TCP/IP device just open the file BirdyCantabile_by_iadvd_2019_classic_ver.tap in your Spectrum emulator (mode 48K) and have fun! If you have a real Spectrum 48K or greater, and you have a .tap loading peripheral, you can load this game too! If you want to use an Android device as a wireless joystick do as follows:

1. Install Fuse ZX Spectrum emulator (use the emulation of the 48K version)  + Spectranet emulator. If Spectranet is correctly installed you will get a local IP for the Spectrum. You will need to verify that the computer is not using a firewall or at least that the port 8081 is open and available to be used for a TCP/IP protocol connection. And of course: if you are the lucky possesor of a real Spectrum 48k machine (or greater version) and a real Spectranet peripheral, then you can also continue to step 2!!

2. Download BirdyCantabile_by_iadvd_2019_Spectranet_AndroidTCPIPVJoystick_ver.tap and load it into Fuse. You will see in the title screen the option 4 (A), which is the Android TCP/IP Virtual Joystick option. If you press 4, the game will wait for you to launch the Android TCP/IP Virtual Joystick application and press its welcome screen OK button. This will make the Virtual Joystick application to connect to the game!. Now you can play normally with your wireless joystick. And again, if you are the lucky possesor of a real Spectrum + Spectranet (not an emulation) then you will need any program able to conver the .tap file into a wav / sound file, so you can load it through the EAR input in the classical way, or if you have a .tap loader device in the expansion port, just copy the .tap file to your peripheral and load it to memory from there. 

Remark: If you want to use the file server available with the Android TCP/IP Virtual Joystick, follow the instructions in this link (and you can use the birdycantabile.tap or birdycantabileA.tap files there, they are the same .tap files but with a shorter name: birdycantabileA.tap is compatible with the Android TCP/IP Virtual Joystick and the other one only uses Keyboard, Kempston or Sinclair emulations):

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/SpectranetTNFS

3. Now launch (if it is not already launched!) your Android TCP/IP Virtual Joystick application. Your Android device must be in the same local network (using WiFi) than the computer where the Fuse emulator is or the ZX Spectrum connected through Spectranet is. The application will ask you the IP that Spectranet is using (or if you do not know it you can write an IP of the same local network to start searching from it).

4. When the Virtual Joystick app. arrives to the IP that is using Spectranet, the game wil detect the joystick and connect to it. The game's Main Menu will appear. 

5. At the main menu, please select option 4 (A = Android TCP/IP Virtual Joystick) and the virtual joystick will be available. The controls are:

      O / joystick left: run left.

      P / joystick right: run right.

      Q, SPACE / joystick fire (Red or Green button): jump.
	  
	  A / joystick fire (Green button): hear a part of the score or put the score in the music stand.

6. If you close the Android application, the connection is lost. You will need to load again the game and start from step 2.

![alt text](https://github.com/Iadvd/RetrocomputingZXSpectrum/blob/master/GameExamples/BirdyCantabile/BC4.png)

# For developers: How to compile/reuse the .tap file again? (not required to play the game)

1. In your Z88dk folder (e.g. C:\z88dk10) copy the contents of this folder. You should be using The Mojon Twins adapted version of the compiler (all credits to The Mojon Twins):

https://github.com/mojontwins/MK1

2. If you want to compile the Spectranet+Android TCP/IP Virtual Joystick version, the last line in "config.h" file must be uncommented:

#define ANDROID_TCP_IP			// Spectranet Android TCP/IP Joystick

3. If you want to compile the "classic" (keyboard, Kempston Joystick, Sinclair Joustick only) version, the last line in "config.h" file must commented out:

//#define ANDROID_TCP_IP			// Spectranet Android TCP/IP Joystick

4. Use "make.bat birdycantabile" command to create again the .tap file if you wish so.
