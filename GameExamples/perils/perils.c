// churromain.c
// Esqueleto de juegos de la churrera
// Copyleft 2010 The Mojon Twins

// Renombrar a tujuego.c o lo que sea para que quede más bello
// y to la pesca.

// Super mega hiper disclaimer: como verás, el código es una 
// paranoia de la hostia. El tema está en que se reaprovecha
// mucho para poder hacer distintos tipos de juego con dife-
// rentes características, pero no todo el código es usable
// en todos los tipos de juego. Para ahorrar, se usan direc-
// tivas que incluyen sólo el código necesario, dejando fuera
// todo lo que no se usa... Por eso es tan zapatiéstico.

// Y sí, es el mismo motor que Uwol o Phantomasa 2, pero
// mejorado, tuneado, modularizado y hipervitaminado.

#include <spritepack.h>

/*
#pragma output STACKPTR=61440
#define AD_FREE			60000
*/
// Tighten it even more... Gaining about 1.1 extra Kb 
#pragma output STACKPTR=61952
#define AD_FREE			61050

struct sp_UDK keys;
void *joyfunc;				// Puntero a la función de manejo seleccionada.

void *my_malloc(uint bytes) {
   return sp_BlockAlloc(0);
}

void *u_malloc = my_malloc;
void *u_free = sp_FreeBlock;

// Globales muy globalizadas

unsigned char kempston_is_attached;
struct sp_SS *sp_player;
struct sp_SS *sp_moviles [3];
struct sp_Rect spritesClipValues;
struct sp_Rect *spritesClip;

unsigned char enoffs;


// Aux

extern char asm_number[1];
extern unsigned int asm_int [1];
extern unsigned int asm_int_2 [1];
extern unsigned int seed [1];
unsigned char half_life;

#asm
._asm_number 
	defb 0
._asm_int
	defw 0
._asm_int_2
	defw 0
._seed	
	defw 0
#endasm

// Codigo para joystick virtual Android compatible con Spectranet (comienzo)
#include <sys/socket.h>
#include <sockpoll.h>
#include <sys/compiler.h>
// Codigo para joystick virtual Android compatible con Spectranet (final)

// Cosas del juego:

#include "aplib.h"
#include "pantallas.h"
#include "config.h"
#include "mapa.h"
#include "tileset.h"
#include "sprites.h"
#ifdef PLAYER_KILLS_ENEMIES
#include "extrasprites.h"
#endif
#include "enems.h"
#include "beeper.h"
#include "engine.h"

// Y el main

void main (void) {
	int j;
	unsigned char *allpurposepuntero;
	unsigned char i;
	unsigned char playing;
	unsigned char n_pant;
	unsigned char maincounter;
	unsigned char x, y;
	unsigned char success;
	
	// Para uso exclusivo con Spectranet, configura puerto 8081 TCP/IP con Joystick virtual
	// El juego no cargara hasta que detecte conexion de joystick o se pulse una tecla
	#asm
		CALL 0DAFh;
		
		; Data
		line: 
			defb 'C','h','e','r','i','l',' ','P','e','r','i','l','s','.',' ','A','n','d','r','o','i','d',' ','V','i','r','t','u','a','l',' ','J','o','y','s','t','i','c','k',' ','c','o','m','p','a','t','i','b','l','e',' ','v','e','r','s','i','o','n','.','W','a','i','t',' ','o','r',' ','a','n','y',' ','k','e','y',' ','t','o',' ','c','a','n','c','e','l','.','.','.',13,'$'
			
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
	
	// Primero detecto el kempston
	
	#asm
		halt
		in	a, (31)
		inc a
		ld	(_kempston_is_attached), a
		di
	#endasm
	
	// Inicializo splib2
	
	sp_Initialize (7, 0);
	sp_Border (BLACK);
	sp_AddMemory(0, 50, 14, AD_FREE);
	
	// Defino las teclas y el control por defecto
	
	keys.up    = sp_LookupKey('q');
	keys.down  = sp_LookupKey('a');
	keys.left  = sp_LookupKey('o');
	keys.right = sp_LookupKey('p');
	keys.fire  = sp_LookupKey(' ');
	
	joyfunc = sp_JoyKeyboard;

	// Cargo el tileset
		
	allpurposepuntero = tileset;
	for (j = 0; j < 255; j++) {
		sp_TileArray (j, allpurposepuntero);
		allpurposepuntero += 8;
	}

	// Rectángulo de clipping

	spritesClipValues.row_coord = VIEWPORT_Y;
	spritesClipValues.col_coord = VIEWPORT_X;
	spritesClipValues.height = 20;
	spritesClipValues.width = 30;
	spritesClip = &spritesClipValues;
	
	// Creamos los sprites
	
	sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	player.current_frame = player.next_frame = sprite_2_a;
	
	for (i = 0; i < 3; i ++) {
		sp_moviles [i] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a, 2, TRANSPARENT);
		sp_AddColSpr (sp_moviles [i], sprite_9_b, TRANSPARENT);
		sp_AddColSpr (sp_moviles [i], sprite_9_c, TRANSPARENT);	
		en_an [i].current_frame = sprite_9_a;
	}
	
	while (1) {
		// Aquí la pantalla de título
		sp_UpdateNow();
		unpack ((unsigned int) (s_title));
		select_joyfunc ();
		
#ifndef DIRECT_TO_PLAY
		// Si no está definido DIRECT_TO_PLAY, entonces borramos la pantalla de
		// título y colocamos el marco
		cortina ();
		sp_UpdateNow();
		unpack ((unsigned int) (s_marco));
#endif

		// Empezamos.

		playing = 1;
		init_player ();
		init_hotspots ();
		init_cerrojos ();
#ifdef PLAYER_KILLS_ENEMIES
		init_malotes ();
#endif
		
		n_pant = SCR_INICIO;
		maincounter = 0;
		
		draw_scr (n_pant);
		draw_life ();
#ifndef	DEACTIVATE_OBJECTS
		draw_objs ();
#endif
		draw_keys ();
#ifdef PLAYER_KILLS_ENEMIES
		draw_killed ();
		
		sp_PrintAtInv (KILLED_Y, 2 + KILLED_X, 71, 15);// Poner total
		sp_PrintAtInv (KILLED_Y, 3 + KILLED_X, 71, 16 + BADDIES_COUNT / 10);
		sp_PrintAtInv (KILLED_Y, 4 + KILLED_X, 71, 16 + BADDIES_COUNT % 10);
#endif
		
		half_life = 0;
		
		while (playing) {
			maincounter ++;
			half_life = !half_life;
			
			// Mover player
			
			if ( !(player.estado & EST_MUR) )
				move (n_pant);
			else {
				// ?
			}
			
			// Mover enemigos
			
			mueve_bicharracos (n_pant);
			
			// Precalc para cálculos (eh?)
			
			x = player.x >> 6;
			y = player.y >> 6;
			
			// Render
			
			if ( !(player.estado & EST_PARP) || !(half_life) )
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);
			else
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, -2, -2, 0, 0);
			
			player.current_frame = player.next_frame;
			
			for (i = 0; i < 3; i ++) {
				if (malotes [enoffs + i].t != 0) {		// Esto sólo es necesario si hay habitaciones con menos de 3.
					sp_MoveSprAbs (sp_moviles [i], spritesClip, en_an [i].next_frame - en_an [i].current_frame, VIEWPORT_Y + (malotes [enoffs + i].y >> 3), VIEWPORT_X + (malotes [enoffs + i].x >> 3), malotes [enoffs + i].x & 7, malotes [enoffs + i].y & 7);
					en_an [i].current_frame = en_an [i].next_frame;
				}
			}
			
			// Update to screen
			
			sp_UpdateNow();

#ifdef PLAYER_FLICKERS
			// parpadeo
			if (player.estado == EST_PARP) {
				player.ct_estado --;
				if (player.ct_estado == 0)
					player.estado = EST_NORMAL;	
			}
#endif			
			
			// Coger objeto
			
			if (x >= hotspot_x - 15 && x <= hotspot_x + 15 && y >= hotspot_y - 15 && y <= hotspot_y + 15) {
				// restauramos el tile de fondo
				draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), orig_tile);
				// Desactivamos el hotspot:
				hotspot_x = hotspot_y = 240;
				// ¿Sumamos un objeto, una llave, o vida?
				if (hotspots [n_pant].act == 0) {
					player.life += PLAYER_REFILL;
					if (player.life > PLAYER_LIFE)
						player.life = PLAYER_LIFE;
					draw_life ();
					hotspots [n_pant].act = 2;
#ifndef DEACTIVATE_OBJECTS
				} else if (hotspots [n_pant].tipo == 1) {
					player.objs ++;
					draw_objs ();	
					hotspots [n_pant].act = 0;
#endif
				} else if (hotspots [n_pant].tipo == 2) {
					player.keys ++;
					draw_keys ();
					hotspots [n_pant].act = 0;
				} 
				// PLOP!!
				peta_el_beeper (0);			
			}
			
			// Comprobaciones
			
			// Codigo para joystick virtual Android compatible con Spectranet (comienzo)
			i = (joyfunc) (&keys); // Leemos del teclado
	
#ifdef PLAYER_AUTO_CHANGE_SCREEN
			if (player.x == 0 && player.vx < 0) {
				n_pant --;
				draw_scr (n_pant);
				player.x = 14336;
			}
			if (player.x == 14336 && player.vx > 0) {
				n_pant ++;
				draw_scr (n_pant);
				player.x = 0;
			}
#else
			// Codigo para joystick virtual Android compatible con Spectranet (simulate_key_press)
			if (player.x == 0 && (((i & sp_LEFT) == 0) || simulate_key_press==1)) {
				simulate_key_press=0;
				n_pant --;
				draw_scr (n_pant);	
				player.x = 14336;
			}
			if (player.x == 14336 && (((i & sp_RIGHT) == 0) || simulate_key_press==2)) {		// 14336 = 224 * 64
				simulate_key_press=0;
				n_pant ++;
				draw_scr (n_pant);
				player.x = 0;
			}
#endif
			if (player.y == 0 && player.vy < 0 && n_pant >= MAP_W) {
				n_pant -= MAP_W;
				draw_scr (n_pant);
				player.y = 9216;	
			}
			if (player.y == 9216 && player.vy > 0) {				// 9216 = 144 * 64
				n_pant += MAP_W;
				draw_scr (n_pant);
				player.y = 0;
			}
			
			// llegarse al final
			
			if (player.objs == PLAYER_NUM_OBJETOS) {
				success = 0;
				if (n_pant == pant_final) {
					if ((player.x >> 10) == PLAYER_FIN_X && (player.y >> 10) == PLAYER_FIN_Y) 
						success = 1;
				} else if (pant_final == 99) {
					success = 1;
				}
				if (success) {
					cortina ();
					game_ending ();
					playing = 0;
					cortina ();
				}
			}
			
			// game over
			
			if (player.life == 0) {
				
				// ¡Saca a todo el mundo de aquí!
				sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);				
				for (i = 0; i < 3; i ++) {
					if (malotes [enoffs + i].t != 0)
						sp_MoveSprAbs (sp_moviles [i], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
				}
				
				game_over ();
				playing = 0;
				cortina ();
			}
		}	
	}
}
