# MuCho Engine 3.0 Customization tryouts by Furillo Productions.

An example of the application of these explanations are in this same repository (the "Javi versus Parrish" .tap games): 

- JaviVersusParrish_Furillo_2023EN.tap

- JaviVersusParrish_Furillo_2023ES.tap

This folder will contain my customizations of the MuCho engine 3.0 by Jari Komppa. The original versions are at these links:

https://github.com/jarikomppa/speccy/tree/master/mucho

https://github.com/jarikomppa/speccy/tree/master/mackarel

My customizations will be updated from time to time, and I provide the contents "as is", a work in progress, hoping someone may find it useful. As these are specializations of Jari Komppa's great work, I am accepting and following the same license agreement:

 * Released under the unlicense, see http://unlicense.org (practically public domain)

# Objectives of my customization.

Basically the initial 3 main objective of my customizations are:

1. Creating a MuCho engine with a Spanish interface

2. Create a variation of the English interface of the original engine (just a simple rewording)

3. Add some music to the engine, using Shiru's Beepola engine Phaser 1 type asm player and include a Main Menu (first room, starting game) music, and a final room (bad or good end) music, and interface (up,down,select) sounds. As everybody knows, MuCho is already able to add sounds, but it does not include a music asm player. 

Thus, the initial targer ouput is creating a MuCHo engine 3.0 + Beepola Phaser 1 music that generates MuCho games for ZX Spectrum 48k including some music and menu selection (musical) sound effects. 

The contents will be an example of how to create it, so the readers of this document - in other words, you ;) - can make their own version of the musical contents. 

This customization implies rebuilding the core of the MuCHo engine core archive, which is included into a file named "crt0.ihx". This file is used by the Mackarel application of the same MuCho suite to create the final MuCho game .tap file.

For this purpose the output of this initial project will be two files:

A "crt0.ihx" core MuCHo engine 3.0 with a Spanish language interface + Beepola music.

A "crt0.ihx" core MuCHo engine 3.0 with an English language interface (just a very simple rewording) + Beepola music.

Initially in our first approach, the data of the music is harcoded INSIDE the build of the "crt0.ihx" file, so you will need to rebuild the core file each time you make a new game to ad the specific music or interface effects of the game. A possible future enhancemente could be a way of having only the asm of the Beepola player without music data inside the "crt0.ihx"  build and the finding a way to insert only the music data later, so it is not required a rebuild of the core MuCHo engine "crt0.ihx" each time we want to add (or modify) new music or interface effects to a new game.

As a side note, including this kind of player plus some simple but effective music should not take more that2 or 3K's depending on the music and effects created, so the final game should not suffer many restrictions regarding the texts or images that can be added. A quick comparison is that the size of the player plus music data has approximately the same size than one $I image of the engine (32x10 screen cells), around 2-3K's. So if we add music, probably we will balance texts+images+music again tohave a perfect mix when the final game is released. 

# Requirements (compilers, tools...)

You will require exactly the same setup to rebuild the "crt0.ihx" as described by the original MuCho project:

https://github.com/jarikomppa/speccy/tree/master

I am performing this project using a Windows machine, so I just can provide information about my current setup. I am not familiar with other SO setups for this project, so I apologize beforehand.

You will require:

SDCC - Small Device C Compiler which includes (apologizes beforehand if this is wrong) the sdasz80 tool and the sdcc compiler tool.
It can be obtained via installing MinGW(32 or 64 depending on your machine)
https://www.mingw-w64.org/
(mingw-get-setup.exe)

Once you have it installed and included in the path of your Windows OS, you should be able to run the "m.bat" file that recreates the core "crt0.ihx" file. 

That file must replace the file with the same name that exists in the folder where the "mackarel.exe" file of the MuCHo suite is.
After that point you can create the .tap file as it is done usually using Mackarel (this final part does not change at all).

So basically we recreate the core MuCho "crt0.ihx" file so Mackarel will use it to create the final .tap file of the game which is including the modified engine that we prepared beforehand.

Also you will require Shiru's Beepola application to create your music and export to asm the data. The engine will work ONLY with the "Phaser 1" Beepola set. If you make songs or menu sounds with other Beepola's engine it will NOT work. Only Phaser 1. I also assume that you are familiar with this music engine (it is not very difficult to learn how to use it).

http://shiru.untergrund.net/1bit/pivot/entry.php?id=40

# How to build the Spanish / English MuCho v3 + Beepola 48k engine using the default music samples included.

1. Download the standard MuCho core creator project from Jari Komppa's master:
   
https://github.com/jarikomppa/speccy/tree/master/mucho

2. Rename with a backup name the original "app.c" and "m.bat" files to another name, and copy this repository "app.c" and "m.bat" instead of them.
   
3. Copy also the "music.h" file OF THIS REPOSITORY to the MuCho project folder.

4. If the SDCC compiler is correctly installed, once you run "m.bat" in some seconds you will have a new "crt0.ihx" MuCho engine core file available. This version is the Spanish version of the engine. If you want to do the English version, open "app.c" and comment the line #define DO_SPANISH as //#define DO_SPANISH, save and run again "m.bat". That will give you the English version.
   
5. Install the MuCho engine suite from Jari Komppa's site:

https://solhsa.com/mucho/mucho.html

6. Now replace the "crt0.ihx" file of the installed suite with your new generated "crt0.ihx" core file.
   
7. And create the .tap file using Mackarel as usually is done with MuCho, just following the standard instructions as usual (I am assuming you are familiar with the standard version of MuCho 3.0)

8. If the game is correctly done (no errors) then the .tap file must appear and can be run. The sample music we have added should sound:

  - At the beginning of the game (first room or screen)
  - At the end of the game (bad or good end)
  - When pressing Q,A or Space to make a selection through the standard MuCho interface inside the game.

# Can I use my own music or menu musical effects?

Of course, we are including only two songs, one for the first screen and other for the bad or good end screens, plus the up, down, select actions. So you can make your own examples. 

You have our Beepola file samples in this same repository, these files are the ones we exported using Beepola to asm data and copy pasted to the "music.h" file. Be careful because the asm syntax of the export and the asm syntax of SDCC are DIFFERENT, so you need to replace thte define byte or define word commands and use .db or .dw asm tags instead... also the label names are a little bit special and must be renamed to _smallletters: and the numbers must start with the # symbol , e.g.   .db #0,#23,#14  is the correct way of defining three consecutive bytes in memory, being those numbers in decimal format. If there are hexadecimal data in the Beepola export like $BD it must be converted to decimal, for instan .db $BD would be .db #189 so any data should be in decimal format. You can convert from hex to dec using this link: 

https://www.rapidtables.com/convert/number/hex-to-decimal.html

If you just copy paste the musica data (NOT the player) then you will just have to make those little changes. 

We will explain a little bit more further about how to create your own music and sounds later (work in progress).

In the current repository we have added three example Beepola files:

- up.bbsong
- down.bbsong
- select.bbsong
- end.bbsong

These are the Beepola files that I have prepared for the example and are already integrated into the "music.h" file so you do not need to make them again, but they are useful if you want to understand how to make new musical effects for the engine. The starting music is not included, but you can create another one as well. When those bbsong files are opened with Beepola you can then export them to asm data only.

