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
	
#ifdef ANDROID_TCP_IP
	#asm
		CALL 0DAFh;

		; Data
		line: 
			defb 'A','n','d','r','o','i','d',' ','V','i','r','t','u','a','l',' ','J','o','y','s','t','i','c','k',' ','c','o','m','p','a','t','i','b','l','e',' ','v','e','r','s','i','o','n','.',' ','W','a','i','t',' ','o','r',' ','a','n','y',' ','k','e','y',' ','t','o',' ','c','a','n','c','e','l','.','.','.',13,'$'			
			
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
	
	if (init_tcpip () == -1){
		return;
	};
	
#endif
	
	do_game ();
}

// From beepola. Phaser engine by Shiru.
#include "music.h"
