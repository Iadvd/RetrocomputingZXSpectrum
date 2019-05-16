// churromain.c
// Esqueleto de juegos de la churrera
// Copyleft 2010-2013 The Mojon Twins

// version FORK 3.99b

#include <spritepack.h>

#pragma output STACKPTR=61952
#define AD_FREE			60655

// MAX BINARY SIZE = 35655 (make @ 25000) or 36155 (make @ 24500)

// Optimal place to compile if using COMPRESSED_LEVELS:
// 23296 + MAP_W * MAP_H * (108) + MAX_CERROJOS * 4 + 49

#include "config.h"

#ifdef ANDROID_TCP_IP
#include <sys/socket.h>
#include <sockpoll.h>
#endif

int score_n_is_in_room[8];
int in_room_is_score_n[8];
int score_set_in_pos_i_was_in_room_r[8];
int current_taken;
int happiness = -1;
int concert_song=-1;
int tile_color=-1;
unsigned int random_seed=0;

// Cosas del juego:

#include "definitions.h"
#ifdef ACTIVATE_SCRIPTING
#include "msc-config.h"
#endif
#include "aplib.h"
#include "pantallas.h"
#ifdef COMPRESSED_LEVELS
#include "levels.h"
#else
#include "mapa.h"
#endif
#include "tileset.h"
#include "sprites.h"
#include "extrasprites.h"
#ifndef COMPRESSED_LEVELS
#include "enems.h"
#endif
#include "beeper.h"
#include "printer.h"
#ifdef ACTIVATE_SCRIPTING
#include "msc.h"
#endif
#include "engine.h"
#include "mainloop.h"

// Y el main

void main (void) {	

	#asm
		CALL 0DAFh;
		
		; Data
		line: 
			defb 'W','a','k','e',' ','u','p',' ','B','i','r','d','y','!',' ','Y','o','u','r',' ','c','o','n','c','e','r','t',' ','i','s',' ',' ','t','o','d','a','y','!',' ','P','r','e','s','s',' ','a','n','y',' ','k','e','y','.','.','.',13,'$'
			
		start:
			ld      a, 2                  ; channel 2 = "S" for screen
			call    $1601                 ; Select print channel using ROM

			ld hl,line                    ; Print line
			call printline
			ret                        

		printline:                     	  ; Routine to print out a line
			ld a,(hl)                     ; Get character to print
			cp '$'                        ; See if it '$' terminator
			jp z,printend                 ; 
			rst 16                        ; Spectrum: Print the character in 'A'
			inc hl                        ; Move onto the next character
			jp printline                  ; Loop round
		
		printend:
		
	#endasm
	
	while (!sp_GetKey ()){
		random_seed=random_seed+1;
		random_seed=random_seed%1000;
	};	
	peta_el_beeper (8);
	srand(random_seed);
	
	do_game ();
}

// From beepola. Phaser engine by Shiru.
#include "music.h"
