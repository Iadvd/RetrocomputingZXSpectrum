# MuCho 128k Beta version.

Spanish manual after English manual (below)

Download the zip file and after unzipping it, move it to the c:\ root or another easy to find place. 1 zip file = 1 game project (English & Spanish). You can change the name of the main folder of the engine, for instance you can put the name of your game. For the rest of things, follow the manual. Good luck! :)

Descarga el archivo zip y tras descomprimir pon la carpeta principal del motor en la raíz de c:\ o en otro lugar sencillo de encontrar. Cada juego que hagas tendrá su propia carpeta, de hecho puedes cambiar el nombre de la carpeta principal de MuCho 128k por el nombre que desees, por ejemplo el nombre del juego. Para las demás cosas por favor revisa el manual, espero que sea de ayuda. ¡Buena suerte!

# ENGLISH MANUAL

MuCho 128k Beta version

manual ver. 1.0

by IADVD (Furillo Productions)

https://furilloproductions.itch.io/

Chapter 1. Foreword.

Chapter 2: Welcome to the MuCho 128k -MK1 Boosted- manual!

Chapter 3. What can I do with the 128k engine?

Chapter 4: Let's migrate a game.

Chapter 5: How to configure the images (.scr files)

Chapter 6: How to configure the music.

Chapter 7: Config File.

ANNEX 1: the directory structure.

--------------------------------------------------------------------------

Chapter 1: Foreword.

MuCho 128k is an extension of Jari Komppa's MuCho Multiple Choice engine for the ZX Spectrum 48k:

https://github.com/jarikomppa/speccy

It will make ZX Spectrum 128k games using the MuCho engine. It will not be able to make 48k games. If you want to make 48k games you will need to use the standard original engine.

The extension has been possible thanks to the libraries and framework of The Mojon Twins' MK1 La Churrera engine:

https://github.com/mojontwins/MK1

Thus we will license this extension following their same license agreements:

For MuCho 128k (based on MuCHo 48k):

Unlicense license 

For the included MK1 framework:

GPL-2.0 license 

Please review the above links for more information about each license.

IADVD message: dear all, this is a BETA version and probably it will be forever, as unfortunately I do not have much time lately for maintenance. 

Anyone can modify the source code and make better versions, so please make your own wonderful versions when you whish.

--------------------------------------------------------------------------

Chapter 2: Welcome to the MuCho 128k -MK1 Boosted- manual!

Dear reader, here you will find all the information regarding the MuCho 128k engine. This is an extension of the original MuCho 48k engine, made by Jari Komppa.

So first things first :)

This engine is intended for those friends that are already familiar with the original Jari Komppa's MuCho 48k engine. So if you want to get results with this 128k version first you have to learn to use the 48k version. Trying to use the 128k version without knowing how to make games with the 48k version will lead to frustration. So my very humble suggestion is to start making a nice MuCho 48k game to undestand how it works. 

The rules to make a 128k game are an extension of those to make an original MuCho 48k game, so you will need to understand / play with the original engine before trying to get a nice result with the MuCho 128k version. 

So my first suggestion is visiting the official MuCho 48k website and making a game with the 48k engine, following the standard rules of the engine:

https://solhsa.com/mucho/mucho.html

Once you make a little MuCho 48k game, so you feel confortable with the engine, my suggestion would be migrating that game to the 128k engine in order to learn step by step how it works. 

In general, my suggestion is to make first the 48k version of the game and then migrating it to the 128k engine. 

--------------------------------------------------------------------------

Chapter 3: What can I do with the 128k engine?

1. I have added the MK1 engine framework able to manage the music and the Spectrum 128k RAM banks, so you will have RAM1 available to add the music of the game (up to 6 melodies) and the rest of RAM banks to add more images to the game. 

2. The in-game music is done with the WYZ tracker, but it is not the latest version, is the same version that uses the MK1 engine (at least up to 2023). I will add that version ZIPped to the Github repository so there is no possible mistake. It also includes sounds for the menu actions (up down select) and a configurable sound for those rooms where we want to express that something important has been found. 

3. The 128k engine adds the possibility of having two intro full screen images (visible until a key is pressed) and also having what we name "flash screens" which are full screens that are shown when the player enters to a certain room. There is no limit of flash screens, as long as you have enough space in the RAM banks of course.

4. There are other small features, linked to the images that are stored in the banks. There is for instance a "do not reload" feature for certain kind of images, that keeps, the image that is already visible on the top of the screen when we are in a room in which the texts are longer that the current screen space. So when you press to continue reading the rest of the text, the image is not reloaded again (because is the same one, so we avoid the blink of the reloading process)

5. The mc.exe application has a new parameter to decide the quantity of bytes reserved for the optimization dictionary (from 512bytes to 1k). In the original 48k engine is is 1k fixed, but the results very depending on that value, so I have added that parameter as a command line option, so if you are in need of it, you can play with it to save around 50 to 100 bytes (sometimes that means a lot specially when you are using the whole 48k base memory!!). Furthermore, after a comma you do not have to enter a space, the engine does it by default, sometimes saving up to 100 bytes of memory.

6. So basically, the more images you put into the ZX Spectrum 128k extra RAM banks, the more 48k base memory you have to write more rooms, more history, more texts, more conditions, etc. Anyway, you still can have images at the 48k base memory, no problem at all. 

7. It is able to generate the English and Spanish version of the engine messages, so you can create the English and Spanish versions of your game if you whish. 

8. Kempston and Sinclair-1 joystick support.
   
Ok, I think I do not forget anything, so let's go one by one.

--------------------------------------------------------------------------

Chapter 4: Let's migrate a game

GOLDEN RULE: just mofidy the files written below. Do not change or remove any other existing files, because they are part of the automation proccess. If you remove or change the name of one of those files, the whole process will not work as expected.

Let's suppose that you have made a MuCho 48k game and you want to migrate it to the 128k version so you can add in-game music and extra rooms and texts. 

First thing is to migrate the current contents, then adapt them to the rules of the 128k version and finally once it is stable and you can create a basic 128k tap file, then extend the game adding more images, or more texts etc.

STEP 1:

Edit the file 

[MUCHO128k_MK1boost/dev/NAME_OF_THE_GAME.bat]

to add the name of the game, max. 10 characteres (this is the name that appears when a LOAD "" is done, so max. 8 character). We will use this name to create the .tap files as well.

Then copy the content of the text file of your MuCho 48k game inside:

[MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE/your_game_in_english.txt]

or inside

[MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE/your_game_in_spanish.txt]

depending if your project is an English written or Spanish written game.

Important: please do not rename the files, we need the names as they are, so the scripts will find them. Do not worry about the generic names.

STEP 2:

Initially, copy all the .scr files to 

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE/

Important: please do not remove or rename any other existing files.

Remember to edit 

MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE\buildEN.bat

and 

MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE\buildEN.bat

To customize the fonts, selector image, and divider, as you usually do for a MuCho 48k game. Please do not change any other contents of these files, everything is requiered as it is, or the scripts will not work properly.

STEP 3: first thing we need to adapt

RULE OF THE FIRST IMAGE: Due to the nature of the engine, it is required for the first $Q of the game to have an image of 10 cells of height at the very beginning of the game.

So it is required to start the game with something like a first $Q room (or place) containing ONLY one image of 80 pixels (10 ZX Spectrum screen file cells) of height and will be written in this way (this way of writing the tags is a MuCho 128k feature):

$Q startingroom

#I yourstartingroomimage.scr

$I libraries.scr

...then the rest of the $Q content as usual...

this is the only mandatory requirement to be able to use MuCho 128k. It is required a first image in the first screen.

[yourstartingroomimage.scr] is an image (the name could be the one you want) that will work as a "welcome to the main menu" image, and it is covering the  loading of several libraries that are required to manage the music and images stored at the extra RAM banks, that are inside the false image named "libraries.scr".

The [yourstartingroomimage.scr] must be located at the [MUCHO128k_MK1boost/gfx/] folder, it does not need to be located at the  [MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE] folder anymore, because this image will be stored at the ZX Spectrum 128k extra RAM banks.

We will see this later on, but basically:

a) Images that will NOT be in the extra RAM banks of the ZX Spectrum 128k will remain in the 

[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE]

folder as the standard MuCho 48k image files. 

And the will be written as a normal MuCho 48k $I tag 

$I yourstartingroomimage.scr

b) Images that will be in the extra RAM banks of the ZX Spectrum 128k will be located / moved to the [MUCHO128k_MK1boost/gfx/] folder, and will be written as follows at the game text file, so MuCho 128k will know that this screen will be stored at the extra RAM banks of the ZX SPectrum 128k:

#I yourstartingroomimage.scr

$I libraries.scr

The fixed line [$I libraries.scr] will always appear as it is, the engine uses it to detect that the current image to be shown must be taken from the extra RAM banks and not from the base 48k memory.

It is tricky, but believe me: it's worth it ;) please remember not removing or changing the name of "libraries.scr" in case you see it, keep it as it is.

Please review:

Chapter 5: How to configure the images (.scr files)

In order to understand how to manage the screen images of the MuCho 128k games.

STEP 4: add your music tunes

MuCHo128k is able to play up to 6 different in-game tunes. You will have to create them by using the XYZ tracker version 0.5.0.2 (newer versions are NOT
compatible). There is a template that you can use as a base at the [MUCHO128k_MK1boost\mus] folder (template.wyz). The way of creating and adding the images is exacly the same as that of the MK1 La Churrera engine.

Please review:

Chapter 6: How to configure the music.

In order to understand how to manage the music of the MuCho 128k games.

STEP 5: run the script

\dev\CREATE_GAME_TAP_EN.bat

to create the English .tap file 

or 

\dev\CREATE_GAME_TAP_ES.bat

to create the Spanish .tap file 

The process takes around 25 seconds, a windows cmd black screen appears and the scripts build the .tap file. If everything goes fine, the .tap file (English or Spanish) will be ready at the [dev\GAME_TAP_IS_HERE] folder.

--------------------------------------------------------------------------

Chapter 5: How to configure the images (.scr files)

The .scr files can be stored at the base 48k memory, as if they were standard MuCho 48k images, or they can be stored at the extra RAM banks of the ZX Spectrum 128k using the new features of MuCho 128k.

As we mentioned in the previous chapter:

a) Images .scr that will NOT be in the extra RAM banks of the ZX Spectrum 128k will remain in the  

[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE]

folder as the standard MuCho 48k image files. 

And the will be written as a normal MuCho 48k $I tag, for instance:

$I yourstartingroomimage.scr

This is as the usual MuCho 48k engine.

b) Images that will be in the extra RAM banks of the ZX Spectrum 128k will be located / moved to the 

[MUCHO128k_MK1boost/gfx/] 

folder, and will be written as follows at the game text file, so MuCho 128k will know that this screen will be stored at the extra RAM banks of the ZX Spectrum 128k:

#I yourstartingroomimage.scr

$I libraries.scr

The fixed line [$I libraries.scr] will always appear as it is, the engine uses it to detect that the current image to be shown must be taken from the extra RAM banks and not from the base 48k memory.

It is tricky, but believe me: it's worth it ;) please remember not removing or changing the name of "libraries.scr" in case you see it, keep it as it is.

So basically the screen .scr images are split into two different folders depending on where they will be stored:

Images to be stored at the base 48k memory as MuCho 48k engine images will be at 

[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE]

And images that we want to put at the extra RAM banks will be at

[MUCHO128k_MK1boost\gfx\]

They just need to be in one of both folders. 

How do we write the tags in the game texts? There are two ways, depending on the type of image:

A) If the image will be located at the base 48k memory, as it was a MuCho 48k image (thus, using the same memory than the texts and variables) it will appear
as usual:

$I nameofmyscreenimage.scr

B) If the image will be located at the extra RAM banks, it will appear as follows:

#I nameofmyscreenimage.scr

$I libraries.scr

As we mentioned before, The fixed line [$I libraries.scr] will always appear as it is, the engine uses it to detect that the current image to be shown must be taken from the extra RAM banks and not from the base 48k memory.

As this is a MuCho 128k BETA version, there are some rules regarding the images to have in mind. Here they are ;)

A) RULE OF THE FIRST IMAGE: 

As we mentioned at the previous chapter, due to the nature of the engine, it is required for the first $Q of the game to have an image of 10 cells of 
height at the very beginning of the game.

So it is required to start the game with something like a first $Q room (or place) containing ONLY one image of 80 pixels (10 ZX Spectrum screen file cells) of height and will be written in this way (this way of writing the tags is a MuCho 128k feature):

$Q startingroom

#I yourstartingroomimage.scr

$I libraries.scr

...then the rest of the $Q content as usual...

this is the only mandatory requirement to be able to use MuCho 128k. It is required a first image in the first screen.

[yourstartingroomimage.scr] is an image (the name could be the one you want) that will work as a "welcome to the main menu" image, and it is covering the 
loading of several libraries that are required to manage the music and images stored at the extra RAM banks, that are inside the false image named "libraries.scr".

The [yourstartingroomimage.scr] must be located at the [MUCHO128k_MK1boost/gfx/] folder, it does not need to be located at the 

[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE]

folder anymore, because this image will be stored at the ZX Spectrum 128k extra RAM banks.

B) RULE OF THE SINGLE IMAGE:

If you have a $Q that uses a screen image that is stored at the extra RAM banks, so it is at the [MUCHO128k_MK1boost/gfx/] folder, that $Q CANNOT HAVE MORE images than that one. Good news are: we can keep the image visible through a multiple text pages room $Q at the top until we leave the room (this is a MuCho 128k feature).

And, in the other hand, a $Q can have as much $I tags as you whish as long as they are stored in the MuCho 48k standard way, at the 48k base memory, but in that case you cannot have any extra RAM bank image at the same $Q.

C) RULE OF THE DIVIDER BAR

If you are using a divider bar between the game texts and the selection menu, it must be written fixed inside the images that are stored at the
extra RAM banks. If the image is a normal MuCho 48k image it does not matter, this rule is just for those images at the extra RAM banks that will appear  inside a $Q.

Draw the divider bar at the 20th row of the screen .scr image.

If you are NOT using (or you are hiding it to black) a divider image, then you do not need to add it to the image.

D) RULE OF THE EMPTINESS:

It is important that the cells of the ZX Spectrum screen stored at your screen files .scr are TOTALLY EMPTY (paper 0, ink 0, bright 0) in those places where you are not showing an image. E.g. let us imagine you have a nice image of a building and the drawing has something up to the 15th row of the screen (couting from the top). In that case you must be careful and wipe any pixels in other cells under the 15th row up to the 20th row if you are using a divider, or up to the 24th row -bottom of the screen- if you are not using a divider bar. The MuCho 128k engine looks for the first row of the image starting from the bottom that has som pixels and color, and that will be determined to be the last row of the image at the screen, so the engine can decide where will be written the texts under the end of the image.

And that is all regarding the management of the images. Now let us check the new features:

FEATURE 1: You can add up to 2 full screen intro images at the beginning of the game. They will appear full screen and the will dissapear when a key is pressed. The in-game music configured for the first $Q will be sounding as the background music of the intro screens.

how to use this feature? At the very begining of the game text file write:

#INTRO1 intro1.scr

#INTRO2 intro2.scr

This commands are telling that you want to intro screens to appear when the loading of the game finishes. The first one is named intro1.scr and the second one intro2.scr, but the names can be the ones you whish.

Those files MUST BE LOCATED at the 

[MUCHO128k_MK1boost/gfx/] 

folder

FEATURE 2: You can add full screen images that will appear until you press a key when you enter to a $Q room or place. This works for any $Q except the
first $Q of the game (for the first $Q you can use the INTRO1 and INTRO2 new features). The image will appear, then when you press a key fades out and the usual $Q content appears.

how to use this feature? Below the $Q tag write as follows:

$Q name_of_the_q_id

#F nameoftheflashscreen.scr

Those files MUST BE LOCATED at the [MUCHO128k_MK1boost/gfx/] folder

FEATURE 3: The extra RAM bank images can have the desired height without limit, it does not matter if you have an image of 15,17,18 screen cells of height (that is 15 cells = 15*8 pixels of length). The text will be located at the proper position under the image. Just have in mind that if the image is way too long you will break the menu, but you will notice that when you test the .tap file. If happens, just reduce the height of the image. Just take care of the [RULE OF THE EMPTINESS] I mentiond before.

And that is all, making a good use of the images at the RAM banks and images you will liberate a good amount of bytes of the 48k base memory, and that means, more texts, more conditions, a longer game.

--------------------------------------------------------------------------

Chapter 6: How to configure the music.

As we mentioned before, a maximum of 6 in-game tunes can be added to the game. There are also fixed menu sounds for the menu options (up down and select) and a fixed sound #S that can be used to express that something important has happened when entering to a $Q or that something has been found, etc. 

The management of the chiptune in-game music is done as a standard MK1 La Churrera project. So everything explained for the MK1 stands here:

https://github.com/mojontwins/MK1/blob/master/docs/tutorial-cap14.md

Just one thing: a "SAMPLE.wyz" XYZ tracker template file is provided at the [\mus\] folder. Please use it to create the wyz files.

The tracker version must be the one I put at the 

[\mus\WYZtracker] folder

More recent version of the tracker will not work. 

The basic steps to add music are:

1. Create up to 6 songs with the WYZ tracker using our template. You cannot change the default instruments or sounds. If you do it you will have to modify the .asm file, it is also recommended for advanced developers. 

2. Put the wyx files at the \mus\ folder

3. Using the WYZ tracker export the music files as .mus files at the same \mus\ folder with the same names as the .wyz files. 

4. Edit the \mus\pack_music.bat file and add the names of your .mus files

5. Edit the [WYZproPlay47aZXc.ASM] search around the 1129 row and yoi will find something like this:

SONG_0:

	INCBIN "SAMPLE.bin"

SONG_1:

    INCBIN "NAME_OF_ANOTHER_SONG_IF_EXISTS_1.bin"
SONG_2:
    
    INCBIN "NAME_OF_ANOTHER_SONG_IF_EXISTS_2.bin"
    
SONG_3:
    
    INCBIN "NAME_OF_ANOTHER_SONG_IF_EXISTS_3.bin"
    
SONG_4:
    
    INCBIN "NAME_OF_ANOTHER_SONG_IF_EXISTS_4.bin"

and later a line like this
	
TABLA_SONG:     DW      SONG_0, SONG_1, SONG_2, SONG_3, SONG_4

Replace the .bin filenames by the name of your music files. You can have up to 6 in-game tunes, so as the first music is numbered 0, it means that you can have up to SONG_5:

SONG_5:

	INCBIN "nameofthe6thsong.bin"

You can have 1 only if you one... but it is mandatory to have at least one. It can be EMPTY so there will be NOT music at all, but it must exist.

remember to modify this line, so it has as much music ids as you imported:

TABLA_SONG:     DW      SONG_0, SONG_1, SONG_2, SONG_3, SONG_4

if you have six songs it will be like this e.g.

TABLA_SONG:     DW      SONG_0, SONG_1, SONG_2, SONG_3, SONG_4, SONG_5

Save the file and that is all. 

Once you create the .tap file by calling

MUCHO128k_MK1boost\dev\CREATE_GAME_TAP_EN.bat

(English version if you did it)

or

MUCHO128k_MK1boost\dev\CREATE_GAME_TAP_ES.bat

(Spanish version if you did it)

The scripts will add the music to the extra RAM 1 bank. And they will sound following the #M0 up to #M5 commands that you will include below each $Q tag.

Well, initially that's all. Good luck!

--------------------------------------------------------------------------

Capítulo 7: Config File.

There is a small config file (English and Spanish) located at:

"\dev\Scripts\configEN.txt"

(English)

"\dev\Scripts\configES.txt"

(Spanish)

Currently there are three parameters that can be modified, just change the values, please do not change the content, or the order because the engine will not work.

1. Mucho128k menu language (the messages of the MuCho engine). It is configured to the correct language, but you can "cross" the language is you wish.

#IDIOMA / NO MODIFICAR (INGLES=0, CASTELLANO=1)

2. Waitkey. If you write a char different from 0, for instance a semi-colon ; then each time it appears written in the texts of the game, the engine will wait for the player to press a key.

Example:

#WAITKEY: IF THIS CHAR APPEARS IN THE TEXTS WILL BE REPLACED BY A PRESS KEY EVENT, WILL WAIT FOR PLAYER TO PRESS A KEY (0=OFF)

;

3. Divider flash effect. If you are using a menu divider bar, you can make it flash a little bit by activating this fx.

#FLASHBAR: WILL INCREASE/DECREASE THE BRIGHT PARAMETER OF THE MENU SEPARATOR BAR (0=OFF)

1

--------------------------------------------------------------------------

ANNEX 1: the directory structure.

MuCho 128k has a lot of directories, but do not worry, you just need to modify two or three places. The rest of directories are there because they are part of the automatizacion. So do not worry about the contents. 

There is a gold rule:

Do not modify the name of any existing file, do not remove any existing file, they are required as they are right now. If you remove something, the scripts probably will not work.

This is the directory structure:

MUCHO128k_MK1boost/ 

Here you will find this manual :)

MUCHO128k_MK1boost/bin

This folder is used sutomatically to create the binary files of the music and images that are stored into 128k extra RAM banks. This folder is part of the MK1 framework. Do not need to do anything here, just let it be. :)

MUCHO128k_MK1boost/gfx

Here you will put all the .scr screen files of your game that you want to put in the extra ZX Spectrum 128k RAM banks. The images that are put in this folder will not use part of the 48k base memory. So the more you put here, the more you can add more rooms, texts, conditions to the game (texts are stored in the 48k base memory, as the standard MuCho 48k engine does). So basically you will add here the .scr screens. You can modify the content :)

MUCHO128k_MK1boost/mus

Here you will put the WYZ tracker files that you will use as in-game music. There is a template that you can use to create your own tunes. This folder is from the MK1 128k standard framework, so you need to learn to add the songs in this folder in ths same way that MK1 does. I will explain later the details here, but for any doubts it must be done as for the MK1 engine (check the MK1 Github manual). So basically you can add here the .wyx files and the exported .mus files and you will need to modify some files to add the tunes. I will explain later.

MUCHO128k_MK1boost/utils

This is standard MK1 128k. These tools are used by the scripts to create the tap file. So you do not need to do nothing in this folder. Just let it be like it is now. Everything inside is required.


MUCHO128k_MK1boost/dev

In this folder you will find the scrips and the MuCho 128k sub-engine

This is the content:

MUCHO128k_MK1boost/dev/NAME_OF_THE_GAME.bat

Edit this file to add the name of the game, max. 8 characteres (this is the name that appears when a LOAD "" is done, so max. 8 character). We will use this name to create the .tap files as well.


MUCHO128k_MK1boost/dev/GAME_TAP_IS_HERE

As the name implies, once the tap file is generated by the scripts it will appear here. There will be one for the English version and one for the Spanish  version, depending on which script you run. The name will use the 8 characters name you wrote at the NAME_OF_THE_GAME.bat file. 

Once is generated, you can rename the file as you want. No problem at all.


MUCHO128k_MK1boost/dev/CREATE_GAME_TAP_ES.bat

MUCHO128k_MK1boost/dev/CREATE_GAME_TAP_EN.bat

The two files are bout are the MAIN scripts. Once you have put all the required files of the English game in their correct places when you double click [CREATE_GAME_TAP_EN.bat] 

The .tap file is generated at the [GAME_TAP_IS_HERE] folder. 

Same for the Spanish game if you use [CREATE_GAME_TAP_ES.bat]


MUCHO128k_MK1boost/dev/Scripts

This folder contains the main scripts of the MuCho 128k engine. Please keep it as it is, do not remove or rename any file inside. 

It includes also the "configEN.txt" and "configES.txt" files that you can modify (see Chapter 7).

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod

You will find inside the .exe files of the MuCho engine. Please as usual: do not modify the names or remove these files. 

The content of this folder will be familiar for those of you that already used the MuCho 48k standard engine. Inside this folder is the usual structure of the 48k MuCho engine, containing the usual folders:

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/dividers

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/fonts

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/manual

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/selectors

The purpose of these four folders about is exactly the same one as in the MuCho 48k engine. So I will not add further explanation.

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/github_author128kProject

This is the source code of the 128k engine. It includes the source code of the mnodified MuCho 48k engine core, the mc.exe and the mackarel.exe, all of them modified to be able to work with the ZX Spectrum 128k. If you are a C, C++ developer, please go ahead and feel free to use and enhance them as you require.  If you are not a programmer and you just want to make a game, you will not use this folder at all. But if you want to make your own version of the engine,
you will need to build again the executables. Unfortunately I do not have much time to help with further enhancements, but it is open and ready for your new ideas.

Caveat: when building the executables be careful with .exe Windows 32 and 64 versions... they are really tricky!

And... finally!!

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE

This is the folder where the MuCho standard game is here you will find those screen .scr that you will NOT put in the extra ZX Spectrum 128k RAM banks and the text of the game (this is as the MuCho 48k engine).

Here you can add or remove your .scr files and you can modify the CONTENT of the files

your_game_in_english.txt

your_game_in_spanish.txt

Please this is importat: do NOT modify the NAME of the files. It is an automated proccess so the scripts are looking for thise two files with those names.

So basically the texts of your MuCho 48k game are copy pasted into the

your_game_in_english.txt

or

your_game_in_spanish.txt

files.

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE/fillers

Please do not remove this folder or delete or rename any file inside here, the engine will not work.



#

# MANUAL EN CASTELLANO
MuCho 128k versión Beta

Manual ver. 1.0

por IADVD (Furillo Productions)

https://furilloproductions.itch.io/

Capítulo 1. Prólogo.

Capítulo 2: ¡Bienvenido al manual de MuCho 128k -MK1 Boosted-!

Capítulo 3. ¿Qué puedo hacer con el motor 128k?

Capítulo 4. Migremos un juego.

Capítulo 5: Cómo configurar las imágenes (archivos .scr)

Capítulo 6: Cómo configurar la música.

Capítulo 7: Archivo de configuración.

ANEXO 1: La estructura de directorios.

--------------------------------------------------------------------------

Capítulo 1: Prólogo.

MuCho 128k es una extensión del motor MuCho Multiple Choice de Jari Komppa para el ZX Spectrum 48k:

https://github.com/jarikomppa/speccy

Permitirá crear juegos para ZX Spectrum 128k utilizando el motor MuCho. No podrá crear juegos para 48k. Si quieres crear juegos para 48k, necesitarás utilizar el motor original estándar.

La extensión ha sido posible gracias a las bibliotecas y el framework del motor MK1 La Churrera de los Mojon Twins:

https://github.com/mojontwins/MK1

Por lo tanto, licenciaremos esta extensión siguiendo sus mismos acuerdos de licencia:

Para MuCho 128k (basado en MuCho 48k):

Licencia Unlicense

Para el framework MK1 incluido:

Licencia GPL-2.0

Por favor, revisa los enlaces de arriba para obtener más información sobre cada licencia.

Mensaje de IADVD: queridos todos, esta es una versión BETA y probablemente lo será para siempre, ya que desafortunadamente no tengo mucho tiempo últimamente para el mantenimiento. Cualquiera puede modificar el código fuente y hacer mejores versiones, así que por favor, no dudes en mejorar el motor.

--------------------------------------------------------------------------

Capítulo 2: ¡Bienvenido al manual de MuCho 128k -MK1 Boosted-!

Estimado lector, aquí encontrarás toda la información relativa al motor MuCho 128k. Esta es una extensión del motor original MuCho 48k, creado por Jari Komppa.

Así que lo primero es lo primero :)

Este motor está dirigido a aquellos amigos que ya están familiarizados con el motor original MuCho 48k de Jari Komppa. Así que si quieres obtener resultados con esta versión 128k, primero tienes que aprender a usar la versión 48k. Intentar usar la versión 128k sin saber cómo hacer juegos con la versión 48k te llevará a la frustración. Así que mi humilde sugerencia es que empieces haciendo un buen juego de MuCho 48k para entender cómo funciona.

Las reglas para hacer un juego de 128k son una extensión de las que hay que seguir para hacer un juego original de MuCho 48k, por lo que tendrás que entender/jugar con el motor original antes de intentar obtener un buen resultado con la versión de MuCho 128k.

Así que mi primera sugerencia es visitar la página web oficial de MuCho 48k y hacer un juego con el motor 48k, siguiendo las reglas estándar del motor:

https://solhsa.com/mucho/mucho.html

Una vez que hagas un pequeño juego de MuCho 48k, y te sientas cómodo con el motor, mi sugerencia sería migrar ese juego al motor 128k para aprender paso a paso cómo funciona. En general, recomiendo hacer primero la versión 48k del juego y luego migrarla al motor 128k.

--------------------------------------------------------------------------

Capítulo 3: ¿Qué puedo hacer con el motor 128k?

1. He añadido el framework del motor MK1 capaz de gestionar la música y los bancos de RAM del Spectrum 128k, por lo que tendrás el banco extra RAM1 disponible para añadir la música del juego (hasta 6 melodías) y el resto de bancos extra de RAM para añadir más imágenes al juego.

2. La música del juego se realiza con el tracker WYZ, pero no es la última versión, es la misma versión que utiliza el motor MK1 (al menos hasta 2023). Añadiré esa versión en ZIP al repositorio de Github para que no haya ningún error posible. También incluye sonidos para las acciones del menú (subir, bajar, seleccionar) y un sonido configurable para que suene en aquellas habitaciones donde queremos expresar que se ha encontrado algo importante.

3. El motor 128k añade la posibilidad de tener dos imágenes de introducción a pantalla completa (visibles hasta que se pulse una tecla) y también tener lo que llamo "pantallas flash", que son pantallas completas que se muestran cuando el jugador entra en una determinada habitación. No hay límite de pantallas flash, siempre que tengas suficiente espacio en los bancos de RAM, por supuesto.

4. Hay otras pequeñas características, relacionadas con las imágenes que se almacenan en los bancos. Por ejemplo, hay una función de "no recargar" para cierto tipo de imágenes, que mantiene la imagen que ya está visible en la parte superior de la pantalla cuando estamos en una habitación en la que los textos son más largos que el espacio actual de la pantalla. Así, cuando pulsas para continuar leyendo el resto del texto, la imagen no se vuelve a cargar (porque es la misma, por lo que evitamos el parpadeo del proceso de recarga).

5. La aplicación mc.exe tiene un nuevo parámetro para decidir la cantidad de bytes reservados para el diccionario de optimización (de 512 bytes a 1k). En el motor original de 48k es de 1k fijo, pero los resultados varían mucho dependiendo de ese valor, así que he añadido ese parámetro como una opción de línea de comandos, para que si lo necesitas, puedas jugar con él para ahorrar alrededor de 50 a 100 bytes (¡a veces eso significa mucho, especialmente cuando estás usando toda la memoria base de 48k!). Además después de una coma no hay que introducir espacio, el motor lo hace por defecto, ahorrando a veces hasta 100 bytes de memoria. 

6. Básicamente, cuantas más imágenes pongas en los bancos de RAM extra del ZX Spectrum 128k, más memoria base de 48k tendrás para escribir más habitaciones, más historia, más textos, más condiciones, etc. De todos modos, todavía puedes tener imágenes en la memoria base de 48k, no hay ningún problema.

7. Es capaz de generar la versión en inglés y español de los mensajes del motor, por lo que puedes crear las versiones en inglés y español de tu juego si lo deseas.

8. Soporte para Kempston y Sinclair-1 joysticks.
   
Ok, creo que no me olvido de nada, así que vamos uno por uno.

--------------------------------------------------------------------------

Capítulo 4: Migremos un juego

REGLA DE ORO: solo modifica los archivos que se indican a continuación. No cambies ni elimines ningún otro archivo existente, ya que forman parte del proceso de automatización. Si eliminas o cambias el nombre de uno de esos archivos, todo el proceso no funcionará como se espera.

Supongamos que has hecho un juego de MuCho 48k y quieres migrarlo a la versión 128k para poder añadir música en el juego y habitaciones y textos adicionales.

Lo primero es migrar el contenido actual, luego adaptarlo a las reglas de la versión 128k y finalmente, una vez que sea estable y puedas crear un archivo tap básico de 128k, ampliar el juego añadiendo más imágenes, más textos, etc.

PASO 1:

Edita el archivo:

[MUCHO128k_MK1boost/dev/NAME_OF_THE_GAME.bat]

para añadir el nombre del juego, con un máximo de 10 caracteres (este es el nombre que aparece cuando se realiza un LOAD "", por lo que el máximo es de 8 caracteres). Usaremos este nombre para crear los archivos .tap también.

A continuación, copia el contenido del archivo de texto de tu juego MuCho 48k dentro de:

[MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE/your_game_in_english.txt]

o dentro de:

[MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE/your_game_in_spanish.txt]

dependiendo de si tu proyecto es un juego escrito en inglés o en español.

Importante: por favor, no renombres los archivos, necesitamos los nombres tal y como están, para que los scripts los encuentren. No te preocupes por los nombres genéricos.

PASO 2:

Inicialmente, copia todos los archivos .scr a:

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE/

Importante: por favor, no elimines ni renombres ningún otro archivo existente.

Recuerda editar:

MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE\buildEN.bat

y

MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE\buildES.bat

para personalizar las fuentes, la imagen del selector y el divisor, como haces normalmente para un juego de MuCho 48k. Por favor, no cambies ningún otro contenido de estos archivos, todo es necesario tal y como está, o los scripts no funcionarán correctamente.

PASO 3: Lo primero que debemos adaptar

REGLA DE LA PRIMERA IMAGEN: Debido a la naturaleza del motor, es necesario que el primer $Q del juego tenga una imagen de 10 celdas de altura al principio del juego.

Por lo tanto, es necesario comenzar el juego con algo como una primera habitación (o lugar) $Q que contenga SOLO una imagen de 80 píxeles (10 celdas de archivo de pantalla del ZX Spectrum) de altura y se escribirá de esta manera (esta forma de escribir las etiquetas es una característica de MuCho 128k):

$Q startingroom

#I yourstartingroomimage.scr

$I libraries.scr

...luego el resto del contenido de $Q como de costumbre...

Este es el único requisito obligatorio para poder utilizar MuCho 128k. Se requiere una primera imagen en la primera pantalla.

[yourstartingroomimage.scr] es una imagen (el nombre puede ser el que quieras) que funcionará como una imagen de "bienvenida al menú principal", y está cubriendo la carga de varias bibliotecas que son necesarias para gestionar la música y las imágenes almacenadas en los bancos de RAM extra, que están dentro de la falsa imagen llamada "libraries.scr".

El archivo [yourstartingroomimage.scr] debe estar ubicado en la carpeta [MUCHO128k_MK1boost/gfx/], ya no es necesario que esté ubicado en la carpeta 
[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE], porque esta imagen se almacenará en los bancos de RAM extra del ZX Spectrum 128k.

Veremos esto más adelante, pero básicamente:

a) Las imágenes que NO estarán en los bancos de RAM extra del ZX Spectrum 128k permanecerán en la carpeta 

[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE] 

como los archivos de imagen estándar de MuCho 48k. Y se escribirán como una etiqueta $I normal de MuCho 48k, por ejemplo:

$I your_room_image.scr

b) Las imágenes que estarán en los bancos de RAM extra del ZX Spectrum 128k se ubicarán/moverán a la carpeta [MUCHO128k_MK1boost/gfx/], y se escribirán de la siguiente manera en el archivo de texto del juego, para que MuCho 128k sepa que esta pantalla se almacenará en los bancos de RAM extra del ZX Spectrum 128k, por ejemplo:

#I your_room_image.scr

$I libraries.scr

La línea fija [$I libraries.scr] siempre aparecerá tal cual, el motor la utiliza para detectar que la imagen actual que se va a mostrar debe ser tomada de los bancos de RAM extra y no de la memoria base de 48k.

Parece un poco complicado al principio, pero una vez te acostumbras créeme: ¡merece la pena! ;)

Por favor, recuerda no eliminar o cambiar el nombre de "libraries.scr" en caso de que lo veas, mantenlo como está.

Por favor, revisa:

Capítulo 5: Cómo configurar las imágenes (archivos .scr)

para entender cómo gestionar las imágenes de pantalla de los juegos de MuCho 128k.

PASO 4: añade tus melodías

MuCho 128k es capaz de reproducir hasta 6 melodías diferentes en el juego. Tendrás que crearlas utilizando la versión 0.5.0.2 del tracker XYZ (las versiones más recientes NO son compatibles). Hay una plantilla que puedes utilizar como base en la carpeta [MUCHO128k_MK1boost\mus] (template.wyz). La forma de crear y añadir las imágenes es exactamente la misma que la del motor MK1 La Churrera.

Por favor, revisa:

Capítulo 6: Cómo configurar la música.

para entender cómo gestionar la música de los juegos de MuCho 128k.

PASO 5: ejecuta el script

\dev\CREATE_GAME_TAP_EN.bat

para crear el archivo .tap en inglés

o

\dev\CREATE_GAME_TAP_ES.bat

para crear el archivo .tap en español

El proceso tarda unos 25 segundos, aparece una pantalla negra de cmd de Windows y los scripts construyen el archivo .tap. Si todo va bien, el archivo .tap (en inglés o español) estará listo en la carpeta [dev\GAME_TAP_IS_HERE].

--------------------------------------------------------------------------

Capítulo 5: Cómo configurar las imágenes (archivos .scr)

Los archivos .scr pueden almacenarse en la memoria base de 48k, como si fueran imágenes estándar de MuCho 48k, o pueden almacenarse en los bancos de RAM extra del ZX Spectrum 128k utilizando las nuevas características de MuCho 128k.

Como mencionamos en el capítulo anterior:

a) Las imágenes .scr que NO estarán en los bancos de RAM extra del ZX Spectrum 128k permanecerán en la carpeta 

[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE] 

como los archivos de imagen estándar de MuCho 48k.

Y se escribirán como una etiqueta $I normal de MuCho 48k, por ejemplo:

$I yourstartingroomimage.scr

Esto es como el motor habitual de MuCho 48k.

b) Las imágenes que estarán en los bancos de RAM extra del ZX Spectrum 128k se ubicarán/moverán a la carpeta [MUCHO128k_MK1boost/gfx/], y se escribirán de la siguiente manera en el archivo de texto del juego, para que MuCho 128k sepa que esta pantalla se almacenará en los bancos de RAM extra del ZX Spectrum 128k:

#I yourstartingroomimage.scr

$I libraries.scr

La línea fija [$I libraries.scr] siempre aparecerá tal cual, el motor la utiliza para detectar que la imagen actual que se va a mostrar debe ser tomada de los bancos de RAM extra y no de la memoria base de 48k.

Parece inicialmente un poco complicado, pero créeme: ¡merece la pena! ;)

Por favor, recuerda no eliminar o cambiar el nombre de "libraries.scr" en caso de que lo veas, mantenlo como está.

Básicamente, las imágenes de pantalla .scr se dividen en dos carpetas diferentes dependiendo de dónde se almacenarán:

Las imágenes que se almacenarán en la memoria base de 48k como imágenes del motor MuCho 48k estarán en:

[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE]

Las imágenes que queremos poner en los bancos de RAM extra estarán en:

[MUCHO128k_MK1boost\gfx\]

Solo necesitan estar en una de las dos carpetas.

¿Cómo escribimos las etiquetas en los textos del juego? Hay dos maneras, dependiendo del tipo de imagen:

A) Si la imagen se ubicará en la memoria base de 48k, como si fuera una imagen de MuCho 48k (utilizando la misma memoria que los textos y las variables), 
aparecerá como de costumbre:

$I nameofmyscreenimage.scr

B) Si la imagen se ubicará en los bancos de RAM extra, aparecerá de la siguiente manera:

#I nameofmyscreenimage.scr

$I libraries.scr

Como mencionamos antes, la línea fija [$I libraries.scr] siempre aparecerá tal cual, el motor la utiliza para detectar que la imagen actual que se va a mostrar debe ser tomada de los bancos de RAM extra y no de la memoria base de 48k.

Como esta es una versión BETA de MuCho 128k, hay algunas reglas con respecto a las imágenes que hay que tener en cuenta. Aquí están ;)

A) REGLA DE LA PRIMERA IMAGEN:

Como mencionamos en el capítulo anterior, debido a la naturaleza del motor, es necesario que el primer $Q del juego tenga una imagen de 10 celdas de altura al principio del juego.

Por lo tanto, es necesario comenzar el juego con algo como una primera habitación (o lugar) $Q que contenga SOLO una imagen de 80 píxeles (10 celdas de archivo de pantalla del ZX Spectrum) de altura y se escribirá de esta manera (esta forma de escribir las etiquetas es una característica de MuCho 128k):

$Q startingroom

#I yourstartingroomimage.scr

$I libraries.scr

...luego el resto del contenido de $Q como de costumbre...

Este es el único requisito obligatorio para poder utilizar MuCho 128k. Se requiere una primera imagen en la primera pantalla.

[yourstartingroomimage.scr] es una imagen (el nombre puede ser el que quieras) que funcionará como una imagen de "bienvenida al menú principal", y está cubriendo la carga de varias bibliotecas que son necesarias para gestionar la música y las imágenes almacenadas en los bancos de RAM extra, que están dentro de la falsa imagen llamada "libraries.scr".

El archivo [yourstartingroomimage.scr] debe estar ubicado en la carpeta [MUCHO128k_MK1boost/gfx/], ya no es necesario que esté ubicado en la carpeta 
[MUCHO128k_MK1boost\dev\MuCho_engine_v3_mod\YOUR_MUCHO_GAME_HERE], porque esta imagen se almacenará en los bancos de RAM extra del ZX Spectrum 128k.

B) REGLA DE LA IMAGEN ÚNICA:

Si tienes un $Q que utiliza una imagen de pantalla que está almacenada en los bancos de RAM extra, por lo que está en la carpeta [MUCHO128k_MK1boost/gfx/], ese $Q NO PUEDE TENER MÁS imágenes que esa. La buena noticia es que podemos mantener la imagen visible a través de una habitación $Q de varias páginas de texto en la parte superior hasta que salgamos de la habitación (esta es una característica de MuCho 128k).

Y, por otro lado, un $Q puede tener tantas etiquetas $I como quieras siempre que estén almacenadas de la forma estándar de MuCho 48k, en la memoria base de 48k, pero en ese caso no puedes tener ninguna imagen de banco de RAM extra en el mismo $Q.

C) REGLA DE LA BARRA DIVISORA:

Si estás utilizando una barra divisora entre los textos del juego y el menú de selección, debe estar escrita fija dentro de las imágenes que se almacenan en los bancos de RAM extra. Si la imagen es una imagen normal de MuCho 48k no importa, esta regla es solo para aquellas imágenes en los bancos de RAM extra que aparecerán dentro de un $Q.

Dibuja la barra divisora en la fila 20 de la imagen de pantalla .scr.

Si NO estás utilizando (o estás ocultando a negro) una imagen de división, entonces no necesitas agregarla a la imagen.

D) REGLA DEL VACÍO:

Es importante que las celdas de la pantalla del ZX Spectrum almacenadas en tus archivos de pantalla .scr estén TOTALMENTE VACÍAS (paper 0, ink 0, bright 0) 
en aquellos lugares donde no estés mostrando una imagen. Por ejemplo, imaginemos que tienes una bonita imagen de un edificio y el dibujo llega hasta la fila 15 de la pantalla (contando desde arriba). 

En ese caso, debes tener cuidado y borrar cualquier píxel en otras celdas debajo de la fila 15 hasta la fila 20 si estás utilizando un divisor, o hasta la fila 24 -fondo de la pantalla- si no estás utilizando una barra divisoria. El motor MuCho 128k busca la primera fila de la imagen comenzando desde abajo que tenga píxeles y color, y eso determinará la última fila de la imagen en la pantalla, para que el motor pueda decidir dónde se escribirán los textos debajo del final de la imagen.

Y eso es todo en cuanto a la gestión de las imágenes. Ahora vamos a revisar las nuevas características:

CARACTERÍSTICA 1: Puedes añadir hasta 2 imágenes de introducción a pantalla completa al comienzo del juego. Aparecerán a pantalla completa y desaparecerán cuando se presione una tecla. La música del juego configurada para el primer $Q sonará como música de fondo de las pantallas de introducción.

¿Cómo usar esta característica? Al principio del archivo de texto del juego escribe:

#INTRO1 intro1.scr

#INTRO2 intro2.scr

Estos comandos indican que deseas que aparezcan pantallas de introducción cuando termine la carga del juego. La primera se llama intro1.scr y la segunda intro2.scr, pero los nombres pueden ser los que desees.

Esos archivos DEBEN ESTAR UBICADOS en la carpeta [MUCHO128k_MK1boost/gfx/].

CARACTERÍSTICA 2: Puedes añadir imágenes a pantalla completa que aparecerán hasta que se presione una tecla al entrar en un lugar o habitación $Q. Esto funciona para cualquier $Q excepto el primer $Q del juego (para el primer $Q puedes usar las nuevas características INTRO1 e INTRO2). La imagen aparecerá y luego, al presionar una tecla, se desvanecerá y aparecerá el contenido habitual de $Q.

¿Cómo usar esta característica? Debajo de la etiqueta $Q escribe lo siguiente:

$Q nombre_del_identificador_de_la_q

#F nombre_de_la_pantalla_flash.scr

Estos archivos DEBEN ESTAR UBICADOS en la carpeta [MUCHO128k_MK1boost/gfx/].

CARACTERÍSTICA 3: Las imágenes de los bancos de RAM extra pueden tener la altura deseada sin límite, no importa si tienes una imagen de 15, 17, 18 celdas de pantalla de altura (es decir, 15 celdas = 15*8 píxeles de longitud). El texto se ubicará en la posición adecuada debajo de la imagen. Solo ten en cuenta que si la imagen es demasiado larga, romperás el menú, pero te darás cuenta cuando pruebes el archivo .tap. Si eso sucede, simplemente reduce la altura de la imagen. Solo cuida la [REGLA DEL VACÍO] que mencioné antes.

Y eso es todo, haciendo un buen uso de las imágenes en los bancos de RAM y las imágenes liberarás una buena cantidad de bytes de la memoria base de 48k, y eso significa más textos, más condiciones, un juego más largo.

--------------------------------------------------------------------------

Capítulo 6: Cómo configurar la música.

Como mencionamos antes, se pueden agregar hasta 6 melodías dentro del juego al juego. También hay sonidos fijos de menú para las opciones del menú (arriba, abajo y seleccionar) y un sonido fijo #S que se puede utilizar para expresar que algo importante ha sucedido al entrar en un $Q o que se ha encontrado algo, etc.

La gestión de la música de chiptune dentro del juego se realiza como un proyecto estándar MK1 La Churrera. Por lo tanto, todo lo explicado para el MK1 se aplica aquí:

https://github.com/mojontwins/MK1/blob/master/docs/tutorial-cap14.md

Solo una cosa: se proporciona un archivo "SAMPLE.wyz" de plantilla del tracker XYZ en la carpeta [\mus]. Úsalo para crear los archivos wyz.

La versión del tracker debe ser la que puse en la carpeta \mus\WYZtracker. Las versiones más recientes del tracker no funcionarán.

Los pasos básicos para agregar música son:

1. Crea hasta 6 canciones con el tracker WYZ utilizando nuestra plantilla. No puedes cambiar los instrumentos o sonidos predeterminados. Si lo haces, tendrás que modificar el archivo .asm, lo que también se recomienda para desarrolladores avanzados.

2. Coloca los archivos wyx en la carpeta \mus.

3. Utilizando el tracker WYZ, exporta los archivos de música como archivos .mus en la misma carpeta \mus\ con los mismos nombres que los archivos .wyz.

4. Edita el archivo \mus\pack_music.bat y agrega los nombres de tus archivos .mus.

5. Edita el [WYZproPlay47aZXc.ASM] busca alrededor de la fila 1129 y encontrarás algo como esto (los nombres son ejemplos):

SONG_0:

	INCBIN "SAMPLE.bin"

SONG_1:

    INCBIN "NOMBRE_DE_OTRA_CANCION_SI_EXISTE_1.bin"

SONG_2:

    INCBIN "NOMBRE_DE_OTRA_CANCION_SI_EXISTE_2.bin"

SONG_3:

    INCBIN "NOMBRE_DE_OTRA_CANCION_SI_EXISTE_3.bin"

SONG_4:

    INCBIN "NOMBRE_DE_OTRA_CANCION_SI_EXISTE_4.bin"

y más adelante una línea como esta

makefile

TABLA_SONG:     DW      SONG_0, SONG_1, SONG_2, SONG_3, SONG_4

Reemplaza los nombres de archivo .bin por el nombre de tus archivos de música. Puedes tener hasta 6 melodías dentro del juego, así que como la primera música se numera como 0, significa que puedes tener hasta SONG_5:

makefile

SONG_5:

    INCBIN "nombre_del_sexto_archivo.bin"

Puedes tener solo 1 si quieres... pero es obligatorio tener al menos uno. Puede estar VACÍO, por lo que no habrá música en absoluto, pero debe existir.

Recuerda modificar esta línea, para que tenga tantos IDs de música como importaste:

makefile

TABLA_SONG:     DW      SONG_0, SONG_1, SONG_2, SONG_3, SONG_4

si tienes seis canciones, será así, por ejemplo:

makefile

TABLA_SONG:     DW      SONG_0, SONG_1, SONG_2, SONG_3, SONG_4, SONG_5

Guarda el archivo y eso es todo.

Una vez que creas el archivo .tap llamando a

MUCHO128k_MK1boost\dev\CREATE_GAME_TAP_EN.bat

(Versión en inglés si lo hiciste)

o

MUCHO128k_MK1boost\dev\CREATE_GAME_TAP_ES.bat

(Versión en español si lo hiciste)

Los scripts agregarán la música al banco de RAM extra 1. Y sonarán siguiendo los comandos #M0 hasta #M5 que incluirás debajo de cada etiqueta $Q.

Bueno, inicialmente eso es todo. ¡Buena suerte!

--------------------------------------------------------------------------

Capítulo 7: Archivo de configuración.

Existen dos pequeños archivos de configuración en

"\dev\Scripts\configEN.txt"

(para la versión inglesa)

"\dev\Scripts\configES.txt"

(para la versión en castellano)

Por ahora se pueden configurar tres acciones, sólo se pueden cambiar los valores, por favor no borres o cambies de orden el contenio del archivo o dejará de funcionar.

1. Idioma del menu de Mucho128k (los mensajes del motor de la parte inferior)

Por defecto está configurado el del idioma adecuado, pero puedes forzar el idioma que quieras.

#LANGUAGE / DO NOT MODIFY (ENGLISH=0, SPANISH=1)

2. Waitkey / Tecla de espera. Si pones un carácter distinto de 0, por ejemplo un punto y coma ; entonces cada vez que aparezca un punto y coma en los textos del juego, la pantalla se quedara en pausa hasta que el jugador pulse una tecla.

Ejemplo:

WAITKEY: SI ES UN CARACTER DISTINTO DE 0 SE USARA PARA DETENER EL TEXTO HASTA QUE SE PULSA UNA TECLA (0 SI NO SE USA WAITKEY)

;

3. Efecto de flash sobre la barra divisora del menú. Hace que el divisor entre los textos y el menú inferior de selección tenga un efecto de parpadeo suave, es un pequeño fx.

#FLASHBAR: HACE QUE LA BARRA DE SEPARACION DE LA PANTALLA DE LECTURA Y EL MENU CAMBIE DE BRILLO (0 SI NO SE USA)

1

--------------------------------------------------------------------------

ANEXO 1: Estructura del directorio.

MuCho 128k tiene muchos directorios, pero no te preocupes, solo necesitas modificar dos o tres lugares. El resto de los directorios están allí porque son parte de la automatización. Así que no te preocupes por el contenido.

Hay una regla de oro:

No modifiques el nombre de ningún archivo existente, no elimines ningún archivo existente, son necesarios tal como están ahora. Si eliminas algo, es probable que los scripts no funcionen.

Esta es la estructura del directorio:

MUCHO128k_MK1boost/

¡Aquí encontrarás este manual!

MUCHO128k_MK1boost/bin

Esta carpeta se utiliza automáticamente para crear los archivos binarios de la música e imágenes que se almacenan en los bancos de RAM extra de 128k. Esta carpeta es parte del framework MK1. No necesitas hacer nada aquí, ¡solo déjala así! :)

MUCHO128k_MK1boost/gfx

Aquí colocarás todos los archivos de pantalla .scr de tu juego que desees poner en los bancos de RAM extra de ZX Spectrum 128k. Las imágenes que se colocan en esta carpeta no utilizan parte de la memoria base de 48k. Así que cuanto más pongas aquí, más podrás añadir más habitaciones, textos, condiciones al juego (los textos se almacenan en la memoria base de 48k, como lo hace el motor estándar MuCho 48k). Básicamente añadirás aquí los archivos .scr de las pantallas. ¡Puedes modificar el contenido! :)

MUCHO128k_MK1boost/mus

Aquí colocarás los archivos del tracker WYZ que utilizarás como música dentro del juego. Hay una plantilla que puedes usar para crear tus propias melodías. Esta carpeta es del framework estándar MK1 128k, así que necesitas aprender a agregar las canciones en esta carpeta de la misma manera que lo hace MK1. Explicaré más tarde los detalles aquí, pero para cualquier duda, debe hacerse como para el motor MK1 (consulta el manual de MK1 en Github). Básicamente puedes añadir aquí los archivos .wyx y los archivos .mus exportados, y necesitarás modificar algunos archivos para añadir las melodías. Lo explicaré más tarde.

MUCHO128k_MK1boost/utils

Esto es estándar MK1 128k. Estas herramientas son utilizadas por los scripts para crear el archivo .tap. Así que no necesitas hacer nada en esta carpeta. ¡Solo déjala como está ahora! Todo lo que hay dentro es necesario.

MUCHO128k_MK1boost/dev

En esta carpeta encontrarás los scripts y el sub-motor MuCho 128k.

Este es el contenido:

MUCHO128k_MK1boost/dev/NAME_OF_THE_GAME.bat

Edita este archivo para añadir el nombre del juego, máximo 8 caracteres (este es el nombre que aparece cuando se hace LOAD ""). Usaremos este nombre para crear los archivos .tap también.

MUCHO128k_MK1boost/dev/GAME_TAP_IS_HERE

Como su nombre indica, una vez que se genera el archivo .tap mediante los scripts, aparecerá aquí. Habrá uno para la versión en inglés y otro para la versión en español, dependiendo de qué script ejecutes. El nombre usará los 8 caracteres que escribiste en el archivo NAME_OF_THE_GAME.bat.

Una vez generado, puedes renombrar el archivo como quieras. Sin problema alguno.

MUCHO128k_MK1boost/dev/CREATE_GAME_TAP_ES.bat

MUCHO128k_MK1boost/dev/CREATE_GAME_TAP_EN.bat

Los dos archivos son los scripts PRINCIPALES.

Una vez que hayas colocado todos los archivos requeridos del juego en inglés en sus lugares correctos, al hacer doble clic en [CREATE_GAME_TAP_EN.bat], se generará el archivo .tap en la carpeta [GAME_TAP_IS_HERE]. Lo mismo para el juego en español si usas [CREATE_GAME_TAP_ES.bat].

MUCHO128k_MK1boost/dev/Scripts

Esta carpeta contiene los scripts principales del motor MuCho 128k. Por favor, mantenla como está, no elimines ni cambies el nombre de ningún archivo dentro.

También incluye los archivos de configuración "configEN.txt" y "configES.txt" que puedes moficiar tal y como se explica en el capítulo 7.

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod

Encontrarás aquí los archivos .exe del motor MuCho. Por favor, como siempre, no modifiques los nombres ni elimines estos archivos.

El contenido de esta carpeta será familiar para aquellos que ya hayan utilizado el motor estándar MuCho 48k. Dentro de esta carpeta está la estructura habitual del motor MuCho 48k, que contiene las carpetas habituales:

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/dividers

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/fonts

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/manual

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/selectors

El propósito de estas cuatro carpetas es exactamente el mismo que en el motor MuCho 48k. Así que no agregaré más explicaciones.

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/github_author128kProject

Este es el código fuente del motor de 128k. Incluye el código fuente del núcleo del motor MuCho 48k modificado, el mc.exe y el mackarel.exe, todos ellos modificados para poder trabajar con el ZX Spectrum 128k. Si eres un desarrollador de C, C++, adelante, siéntete libre de usarlos y mejorarlos según lo requieras. Si no eres un programador y solo quieres hacer un juego, no utilizarás esta carpeta en absoluto. Pero si quieres hacer tu propia versión del motor, necesitarás compilar nuevamente los ejecutables. 

Desafortunadamente, no tengo mucho tiempo para ayudar con mejoras adicionales, pero está abierto y listo para tus nuevas ideas.

Aviso: al compilar los ejecutables ten cuidado con las versiones .exe de Windows 32 y 64... ¡a veces dan problemas de compatibilidad!

¡Y... finalmente!

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE

Esta es la carpeta donde está el juego estándar de MuCho. Aquí encontrarás esas pantallas .scr que NO colocarás en los bancos de RAM extra de ZX Spectrum 128k y el texto del juego (esto es como el motor MuCho 48k). Aquí puedes añadir o eliminar tus archivos .scr y modificar el CONTENIDO de los archivos

your_game_in_english.txt

your_game_in_spanish.txt

Por favor, esto es importante: NO modifiques el NOMBRE de los archivos. Es un proceso automatizado, por lo que los scripts están buscando esos dos archivos con esos nombres.

Básicamente, los textos de tu juego MuCho 48k se copian y pegan en los archivos

your_game_in_english.txt

o

your_game_in_spanish.txt

Por favor, asegúrate de mantener los nombres de los archivos exactamente como están indicados para evitar problemas con el proceso de automatización.

MUCHO128k_MK1boost/dev/MuCho_engine_v3_mod/YOUR_MUCHO_GAME_HERE/fillers

Por favor no borres esta carpeta o elimines o cambies de nombre los archivos que hay, porque el motor dejará de funcionar.
