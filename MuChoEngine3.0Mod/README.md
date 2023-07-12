# MuCho Engine 3.0 Customization tryouts by Furillo Productions.

An example of the application of these explanations are in this same repository (the "Javi versus Parrish" .tap games): 

JaviVersusParrish_Furillo_2023EN.tap

JaviVersusParrish_Furillo_2023ES.tap

This folder will contain my customizations of the MuCho engine 3.0 by Jari Komppa. The original versions are at these links:

https://github.com/jarikomppa/speccy/tree/master/mucho

https://github.com/jarikomppa/speccy/tree/master/mackarel

My customizations will be updated from time to time, and I provide the contents "as is", a work in progress, hoping someone may find it useful. As these are specializations of Jari Komppa's great work, I am accepting and following the same license agreement:

 * released under the unlicense, see http://unlicense.org (practically public domain)

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

