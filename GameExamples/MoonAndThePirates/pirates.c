// churromain.c
// Esqueleto de juegos de la churrera
// Copyleft 2010-2013 The Mojon Twins

// version FORK 3.99b

#include <spritepack.h>
// https://tcyr.wordpress.com/2007/11/21/memoria-dinamica-en-splib2/
// Stack of the program, the space above is required by sp_lib
// the program stack grows downwards
#pragma output STACKPTR=61952 
// Free space for the game, out of the stack and sp_lib space
// theoretically = 61952-512-(40*14) = 60880 but the stack is not growing up to 512, so...
#define AD_FREE			60928 

#include "config.h"

// Cosas del juego:

#include "definitions.h"
#include "mapa.h"
#include "tileset.h"
#include "printer.h"
#include "enems.h"
#include "sprites.h"
#include "spritesB.h"
#include "engine.h"
#include "mainloop.h"
#include "beeper.h"

// Y el main
void main (void) {	
	do_game ();
}

// From beepola. Phaser engine by Shiru.
#include "music.h"




