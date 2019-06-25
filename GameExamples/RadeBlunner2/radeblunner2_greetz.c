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

// Cosas del juego:

#include "definitions.h"
#include "aplib.h"
#include "pantallas_greetz.h"

#include "mapa.h"
#include "tileset.h"
#include "extrasprites.h"
#include "extrasprites_enemies.h"
#include "beeper.h"
#include "printer.h"

// Y el main

extern char pant_msgGreetz [0];

char espera_activa (int espera) {
	char res = 1;
	int i;
	int j;
	
	for (i = 0; i < espera && res; i ++) {
		for (j = 0; j < 250; j ++) { 
			res = 1; 
		}
		//if (sp_GetKey ()) res = 0;
	}	
	
	return res;
}

void main (void) {	
	unsigned char x=0;
	unsigned char *allpurposepuntero;
	char grettztxt[22]; //21 y 0
	int curr_pos=0;
	int itj;
	int first_time=1;
	
	#asm
		di
	#endasm
	
	// splib2 initialization
	sp_Initialize (7, 0);
	sp_Border (BLACK);
	sp_AddMemory(0, 56, 14, AD_FREE);
	
	// Load tileset
	allpurposepuntero = tileset;
	for (itj = 0; itj < 256; itj++) {
		sp_TileArray (itj, allpurposepuntero);
		allpurposepuntero += 8;
	}
	
	// Here the title screen
	sp_UpdateNow();
	blackout ();
	unpack ((unsigned int) (s_title), 16384);
	//#asm
	//	; Music generated by beepola
	//	call musicstart
	//#endasm
	
	grettztxt[21]=0;
	
	while (x!='c') {
		
		for (itj = 0; itj < 21; itj++) {
			if (pant_msgGreetz[curr_pos+itj]==0){
				curr_pos = 0;
			}
			grettztxt[itj]=pant_msgGreetz[curr_pos+itj];
		}
		
		curr_pos=curr_pos+1;
		print_str (9, 22, 4, grettztxt);
		
		sp_UpdateNow();
	
		if (first_time==1){
			peta_el_beeper (0);
			first_time=0;
		}
		#asm
			; Music generated by beepola
			call musicstart
		#endasm
	
		x = sp_GetKey ();
	
	}
		
	#asm
		call LOADERCALL
	#endasm

}
	
// From beepola. Phaser engine by Shiru.
#include "music_hq.h"


#asm
	.loadercall
		ret		
	._pant_msgGreetz
		defb '2','U','-','F','O','R','O',',','S','P','E','C','C','Y',',','O','R','G','-'
		defb 'E','L',' ','M','U','N','D','O',' ','D','E','L',' ','S','P','E','C','T','R','U','M','-'
		defb 'P','L','A','N','E','T','A',' ','S','I','N','C','L','A','I','R','-'
		defb 'R','Z','X',' ','A','R','C','H','I','V','E','-'
		defb 'S','P','E','C','T','R','U','M',' ','C','O','M','P','U','T','I','N','G',' ','F','O','R','U','M','S','-'
		defb 'S','P','E','C','T','R','A','N','E','T',' ','G','R','O','U','P','@','F','A','C','E','B','O','O','K','-'
		defb 'M','O','J','O','N',' ','T','W','I','N','S','-'
		defb 'E','L',' ','S','P','E','C','T','R','U','M','E','R','O',' ','J','A','V','I',' ','O','R','T','I','Z','-'
		defb 'D','A','R','I','O',' ','R','U','E','L','L','A','N','-'
		defb 'A','R','N','A','U',' ','J','E','S','S','-'
		defb 'A','L','E','S','S','A','N','D','R','O',' ','G','R','U','S','S','U','-'
		defb 'S','A','B','E','R','M','A','N','-','P','A','V','E','L',' ','P','L','I','V','A','-'
		defb 'D','A','R','E','N','-',0
#endasm

