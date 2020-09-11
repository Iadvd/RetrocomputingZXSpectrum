# FlappyClive (¡80th birthday special!) by Furillo Productions (SP & EN)

FlappyClive (¡especial 80 cumpleaños!) hecho por Furillo Productions.

>The game & source will be released here on 2020/09/12 (SAT)

>El juego y el código fuente se publicarán por aquí el sábado 12/09/2020.

![alt text](https://raw.githubusercontent.com/Iadvd/RetrocomputingZXSpectrum/master/GameExamples/FlappyClive/FlappyClive_Caratula_CasetteCover.jpg)

Furillo Productions team somos: Molomazo e IADVD (este es mi Github)

IMPORTANTE: Este juego se presenta al MojonConcurso 2020 de los Mojon Twins y Retromaniac:

Furillo Productions team are: Molomazo and IADVD (owner of this Github site)

IMPORTANT: This game will be sent to the MojonConcurso 2020 by the Mojon Twins
and Retromaniac:

http://www.retromaniac.es/2020/03/mojonconcurso-la-vista-sacale-punta-la.html

# Powered by MK1 (La Churrera by The Mojon Twins) and copyleft under a CC BY-NC-SA 3.0 license.

This folder contains the game FlappyClive, in two versions: English and Spanish.
En esta carpeta hay dos versiones del juego: castellano e ingléís.

This is a first release, is you find bugs please let us know (should be fine, we have tested it, but who knows...)
Si encuentras fallos en el juego, por favor avísanos (debería estar bien, pero quién sabe...)

# Technical details (EN)

Game concept: IADVD (inspired by the Sinclair QL TV commercial, the Flappy Bird ZX game by Rafal Miazga and Aleksandr Rostunovand, and Zosya Entertaiment's Valley of Rains).

Loading and tiles: Molomazo & IADVD.

Sprites: IADVD.

Music: IADVD.

Sounds: BeepFX (by Shiru).

Version: Spectrum 48K (or 128K in 48K mode / o 128k en modo 48k)

Powered by MGA by Iadvd + La Churrera by The Mojon Twins and splib2 by Alvin Albrecht:

https://github.com/mojontwins/MK1

Uses aPPack decompressor by dwedit, adapted by Utopian & optimized by Metalbrain
Music tracks composed in Beepola

# New Features for the MK1 / Nuevas funcionalidades para el MK1 (SP & EN)

This game presents three new features for the MK1: a trophy/achievements/badges engine, a
"sticker screen" over the loading screen (to avoid showing the loading game while is being 
drawn), and a simple scroll-to-the-cell (bytewise) implementation with two levels of depth. 
It is not a pixel to pixel scroll because 1) we wanted some color inside the game; 2) a full 
screen pixel by pixel monochrome scroll for this game was slower than the current full 
color solution.

We will reuse the trophy engine in our future games!

Este juego presenta tres nuevas funcionalidades para el MK1: un motor de trofeos/logros, una
"pantalla pegatina" que es una imagen de baja resolucion de carga rapida para ocultar el proceso
de dibujo de la pantalla de carga, y un scroll sencillo (al byte, de 8 en 8 pixels) implementado 
con dos niveles de profundidad. No es un scroll al pixel porque 1) queriamos algo de colorido 
en el juego; 2) un scroll al pixel en pantalla completa era mas lento para este juego que la 
solución con color. 

¡Tenemos pensado utilizar a partir de ahora el motor de trofeos/logros en nuestros futuros juegos!

# Story & The Game (SP & EN)

A picture is worth a thousand words, so check the video:

Una imagen vale más que mil palabras, así que echa un vistazo al vídeo:

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/as6hSAqJ_g4/0.jpg)](https://www.youtube.com/watch?v=as6hSAqJ_g4)

(Credis to "2ombieboy's vhs vault" youtube channel for keeping a copy of the Sinclair QL TV commercial)

(Créditos al canal de "2ombieboy's VHS Vault" por mantener un vídeo del anuncio del Sinclair QL)

Help your favorite genius to reach his dreams!

¡Ayuda a tu genio favorito a conseguir sus sueños!

Unlock Clive's 40 trophies while you fly taking (or not) things and avoiding (or not) the competitors' computers.

Desbloquea los 40 trofeos de Clive mientras aleteas cogiendo (o no) cosas y evitando (o no) chocar contra los ordenadores de la competencia.

There are also trophies that are unlocked when you do things (or not) on the Main Menu and the Trophy Room!

¡También hay trofeos secretos que se desbloquean en el menú principal y en la sala de trofeos!

There are two type of games: 

Hay dos tipos de juegos:

- Take items games: hearts, coins, cakes and Speccies are waiting for you. 

- Coger cosas: corazones, dinero, tartas y Spectrums te esperan.

- Take a secret word games: take the letters of a secret word in the correct order and bump against a computer to unblock the trophy.

- Coger palabras: coge en el orden correcto las letras de la palabra secreta y choca contra un ordenador para desbloquear el trofeo.

![alt text](https://raw.githubusercontent.com/Iadvd/RetrocomputingZXSpectrum/master/GameExamples/FlappyClive/FlappyClive_Instrucciones_Instructions.jpg)

# How to play the .tap file? (EN)

Just open the file "FlappyClive_en_FurilloProductions2020.tap" (English ver.) or "FlappyClive_sp_FurilloProductions2020.tap" (Spanish ver.) in your Spectrum emulator (mode 48K) and have fun! If you have a real Spectrum 48K or greater, and you have a .tap loading peripheral, you can load this game too! 

The controls are:

    SPACE: star the game / flap / see the trophies at the Trophy Room.

    T: enter the Trophy Room from the Main Menu.

    R: return to the Main Menu from the Trophy Room.

    D: change the difficulty at the Main Menu (easy: blue devil / difficult: red devil).

At the right-top side of the Main Menu there is an icon of a devil. If it is blue, you are playing the easy mode. If it is red, you are playing the difficult mode.

	  
# For developers: How to compile/reuse the .tap file again? (not required to play the game)

1. In your Z88dk folder (e.g. C:\z88dk10) copy the contents of this folder. You should be using The Mojon Twins adapted version of the compiler (all credits to The Mojon Twins):

https://github.com/mojontwins/MK1

2. Use "make_with_loading_scr.bat flappyclive" command to create again the .tap file if you wish so.
