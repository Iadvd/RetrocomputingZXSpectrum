# Federation Z, a space adventure by Furillo Productions

Federation Z, una aventura espacial hecha por Furillo Productions.

Furillo Productions team somos: Molomazo and IADVD (este es mi Github)

IMPORTANTE: Este juego se presenta al MojonConcurso 2020 de los Mojon Twins y Retromaniac,
asi que el codigo fuente no lo vamos a publicar aqui hasta que el concurso acabe y 
se publiquen oficialmente todos los juegos y codigos en el sitio del concurso:

Furillo Productions team are: Molomazo and IADVD (owner of this Github site)

IMPORTANT: This game has been presented to the MojonConcurso 2020 by the Mojon Twins
and Retromaniac, so the code will no be published here until the results of the contest
are known and the code and games are published at the contest site (Spanish):

http://www.retromaniac.es/2020/03/mojonconcurso-la-vista-sacale-punta-la.html

# Powered by MGA (Mini Graphic Adventure engine, by Iadvd) + MK1 (La Churrera by The Mojon Twins) and copyleft Iadvd under a CC BY-NC-SA 3.0 license.

This folder contains the game Federation Z, in two versions: English and Spanish.

If you really want to enjoy the game and understand all the available features, read the manual, it is in pdf format:

Esta carpeta contiene el juego Federation Z, en dos versiones: ingles y castellano.

Si quieres disfrutar plénamente del juego, lee primero el manual para entender todas las características disponibles, esta en formato pdf:


This is a first release, is you find bugs please let us know (should be fine, we have tested it, but who knows...)

# Technical details:

Game concept: IADVD (inspired by the ideas of great games like Star Raiders II, Retroinvaders, Extreme, Cheesy Chase - Moritz And The Mildewed Moon, Redshift, Exolon, Dark Fusion, Cyclone, Encyclopaedia Galactica, and the wonderful first Civilization game).

Loading and story screens: Molomazo.

Sprites and tiles: Iadvd (characters, sprites and tiles).

Music: Iadvd.

Sounds: BeepFX (by Shiru).

Version: Spectrum 48K (or 128K in 48K mode: this program uses the printer buffer for storing data, so take care!!)

Tester:  André Leão (thank you very much for the great insights!) from the beloved Planeta Sinclair (http://planetasinclair.blogspot.com/)

Powered by MGA by Iadvd + La Churrera by The Mojon Twins and splib2 by Alvin Albrecht:

https://github.com/mojontwins/MK1

Uses aPPack decompressor by dwedit, adapted by Utopian & optimized by Metalbrain
Music tracks composed in Beepola

# Story

Koji Bakuto is an earthling mecha robot designer. After participating in Ciudad Petunia's Fandom Festival(*) a colleague invited him to join the Zork Federation. They needed a reputed starship captain to continue their expansion through the Omega sector. Koji accepted the invitation and started his career as a starship captain.

(*) This game is part of the "Mooniverse": see "Moon's Fandom Festival" Game here:

https://github.com/Iadvd/RetrocomputingZXSpectrum/tree/master/GameExamples/MoonsFandomFestival

# The Game

As the Captain Koji Bakuto, ride the A9K-2 Starship through the Omega sector following the orders and advices of General Zork, and completing the seven missions of the game. You can be a hero, or finish your days floating in the cold space forever.

Our reports inform us that there are two native races living at the Omega sector; one of them is pacific and neutral and will accept interactions with the Zork Federation. The other one is aggresive and controls the sector with their technological weapons and ships.

There are also several abandoned worlds that were already obliterated by the aggressive race. Our scientists confirm that they can be colonized again.

There are also Ufomart stores where you can buy modules for your ship that gradually will help you to finish your missions. 

Finally, our scientists have detected a big amount of strontium, iridium, goldium and selenium comets that could be a source of funds for us.

You have an initial amount of energy and beams. Be careful because the energy is not infinite. Be also careful with the asteroids moving freely along the whole sector.

# How to play the .tap file?

Just open the file "FederationZ_en_FurilloProductions2020.tap" (English ver.) or "FederationZ_sp_FurilloProductions2020.tap" (Spanish ver.) in your Spectrum emulator (mode 48K) and have fun! If you have a real Spectrum 48K or greater, and you have a .tap loading peripheral, you can load this game too! 

The controls are:

    O / joystick left: navigate left / left.

  	P / joystick right: navigate right / right. 

  	Q / joystick up: navigate up.

  	A / joystick down: navigate down / select an option from the SHOP menu.

  	SPACE / joystick fire: action / select.
	
	H: set the/jump to Hyperspace
	
	M: open/close the galactic Map
	  
# For developers: How to compile/reuse the .tap file again? (not required to play the game)

1. In your Z88dk folder (e.g. C:\z88dk10) copy the contents of this folder. You should be using The Mojon Twins adapted version of the compiler (all credits to The Mojon Twins):

https://github.com/mojontwins/MK1

2. Use "make_with_loading_scr.bat federation" command to create again the .tap file if you wish so.
