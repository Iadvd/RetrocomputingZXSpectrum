// churromain.c
// Esqueleto de juegos de la churrera
// Copyleft 2010-2013 The Mojon Twins

// version FORK 3.99b

#include <spritepack.h>
#pragma output STACKPTR=61952
#define AD_FREE			60655

#include "config.h"

#ifdef ANDROID_TCP_IP
#include <sys/socket.h>
#include <sockpoll.h>
#endif

#define colorM1 4
#define colorM2 5	
#define colorM3 7
#define colorM4 6
#define colorM5 3
#define ESPERA_PASIVA 50

int in_pant_of_character_i_there_is_perso_item[7];
int hungry[7];
int confidence[7];
int conversation_character[6];
int joke_times[6];
int ending = 0;
int moon_is_seated=0;
int fan_i_told[3];
int info_found[3];
int my_memory[3];
int pocket_counter, memory_counter;
int pocket_things[3]; //take-give pocket
int pocket_item; //get-put icon pocket
int face_looper, face_looperf, face_looperf2, which_face, which_facef, which_facef2;
int selection = 0;
int entering_pos_right=14336;
unsigned interact, last_interact;
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

#ifndef ANDROID_TCP_IP
// From beepola. Phaser engine by Shiru.
#include "music.h"
#endif



