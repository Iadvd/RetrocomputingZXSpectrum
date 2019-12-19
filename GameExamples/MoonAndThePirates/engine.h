// Motor.h

// Engine globals (for speed) & size!
unsigned char gpx, gpy, gpd, gpc;
unsigned char gpxx, gpyy;
unsigned char gpen_cx, gpen_cy;
unsigned char gpit, gpjt;
unsigned char *map_pointer;

void step (void);
void speakup_character(unsigned char *message1, unsigned char *message2, int mc);
void speakup(int who, int x, int y, unsigned char textx, unsigned char texty, unsigned char color, unsigned char *message);
unsigned char rand (void);
	
int scroll_management(int time){
	if (scroll_texts){
		read_keys_joystick_helper();
		while ((gpit & sp_FIRE) != 0){
			read_keys_joystick_helper();
		}
	}else{
		espera_pasiva(time);
	}
}
										
void speakup_character(unsigned char *message1, unsigned char *message2, int mc){
	if (mc){
		speakup_clear(9);
		speakup(1,4,0,9,0,colorM1,message1);
		if (*message2){
			speakup(1,4,0,9,1,colorM1,message2);
		}
	}else{
		speakup_clear(1);
		speakup(n_pant,26,3,1,3,colorM2,message1);
		if (*message2){
			speakup(n_pant,26,3,1,4,colorM2,message2);
		}
	}
	scroll_management(ESPERA_PASIVA);
}

int speakup_clear(int posx){
	int i,j;
	
	i=(posx==9?0:3);
	for (j=i;j<(i+2);++j){
		print_str (posx, j, colorM2, action_text_46);
	}
	sp_UpdateNow();	
	
}

void speakup(int who, int x, int y, unsigned char textx, unsigned char texty, unsigned char color, unsigned char *message){
	
	int which_face=0;
	
	// character face must be returned to chat position
	if (who>1 && who<9 && was_mirrored==1){
		// Special case: move face of characters by code
		// Step 3: Invert bits again (back to normal pos)
		was_mirrored=0;
		mirror_tile_scr();
		draw_coloured_tile (perso_face_pos_x[n_pant], perso_face_pos_y[n_pant]-2, n_pant+27); // Face stand
		sp_UpdateNow();	
	}
	
	draw_coloured_tile (x-2, y, 14); // around face tiling 1
	draw_coloured_tile (x+2, y, 43); // around face tiling 2
	
	while (*message) {
		sp_PrintAtInv (texty, textx ++, color, (*message ++) - 32);
		
		asm_int_b[0]=27+who;//default
		asm_int_c[0]=34+who;//default
		if (who==9){
			asm_int_b[0]=17;
			asm_int_c[0]=18;
		}else if (who==10){
			asm_int_b[0]=19;
			asm_int_c[0]=20;
		}
		draw_coloured_tile (x, y, which_face<4? asm_int_b[0]:asm_int_c[0]); 
		
		which_face=(which_face+1)%8;		
		espera_pasiva(2);
		step();
		sp_UpdateNow();	
	}
	
}

// Normal animation:
// 0 1 2 3 + facing: walk, 1 = stand. 8 + facing = jump/fall
unsigned char *player_frames [] = {
	sprite_5_a, sprite_6_a, sprite_7_a, sprite_6_a,
	sprite_1_a, sprite_2_a, sprite_3_a, sprite_2_a
};
unsigned char *player_framesB [] = {
	Bsprite_5_a, Bsprite_6_a, Bsprite_7_a, Bsprite_6_a,
	Bsprite_1_a, Bsprite_2_a, Bsprite_3_a, Bsprite_2_a
};

unsigned char *enem_frames [] = {
	sprite_9_a, sprite_10_a
};

unsigned char *enem_framesB [] = {
	Bsprite_9_a, Bsprite_10_a
};

// Funciones:

void init_player () {
	// Inicializa player con los valores iniciales
	// (de ahí lo de inicializar).
	player.x = 			PLAYER_INI_X << 10;
	player.y = 			PLAYER_INI_Y << 10;
	player.vy = 		0;
	player.vx = 		0;
	player.frame = 		0;
	player.subframe = 	0;
	player.facing = 	1;
}

unsigned char rand (void) {
	unsigned char res;
	
	#asm
		.rand16
			ld	hl, _seed
			ld	a, (hl)
			ld	e, a
			inc	hl
			ld	a, (hl)
			ld	d, a
			
			;; Ahora DE = [SEED]
						
			ld	a,	d
			ld	h,	e
			ld	l,	253
			or	a
			sbc	hl,	de
			sbc	a, 	0
			sbc	hl,	de
			ld	d, 	0
			sbc	a, 	d
			ld	e,	a
			sbc	hl,	de
			jr	nc,	nextrand
			inc	hl
		.nextrand
			ld	d,	h
			ld	e,	l
			ld	hl, _seed
			ld	a,	e
			ld	(hl), a
			inc	hl
			ld	a,	d
			ld	(hl), a
			
			;; Ahora [SEED] = HL
		
			ld 	hl, _asm_int
			ld	a,	e	
			ld	(hl), a
			inc	hl
			ld	a,	d
			ld	(hl), a
			
			;; Ahora [ASM_INT] = HL
	#endasm
	
	res = asm_int [0];
	
	return res;
	
}

void cortina (void) {
	#asm
		;; Antes que nada vamos a limpiar el PAPER de toda la pantalla
		;; para que no queden artefactos feos
		
		ld	de, 22528			; Apuntamos con DE a la zona de atributos
		ld	b,	3				; Procesamos 3 tercios
	.clearb1
		push bc
		
		ld	b, 255				; Procesamos los 256 atributos de cada tercio
	.clearb2
	
		ld	a, (de)				; Nos traemos un atributo
		and	199					; Le hacemos la máscara 11000111 y dejamos PAPER a 0
		ld	(de), a				; Y lo volvemos a poner
		
		inc de					; Siguiente atributo
	
		djnz clearb2
		
		pop bc
		djnz clearb1
		
		;; Y ahora el código original que escribí para UWOL:	
	
		ld	a,	8
	
	.repitatodo
		ld	c,	a			; Salvamos el contador de "repitatodo" en 'c'
	
		ld	hl, 16384
		ld	a,	12
	
	.bucle
		ld	b,	a			; Salvamos el contador de "bucle" en 'b'
		ld	a,	255
	
	.bucle1
		sla (hl)
		inc hl
		dec a
		jr	nz, bucle1
			
		ld	a,	255
	.bucle2
		srl (hl)
		inc hl
		dec a
		jr	nz, bucle2
			
		ld	a,	b			; Restituimos el contador de "bucle" a 'a'
		dec a
		jr	nz, bucle
	
		ld	a,	c			; Restituimos el contador de "repitatodo" a 'a'
		dec a
		jr	nz, repitatodo
	#endasm	
}

// Game

void step (void) {
	#asm
		ld a, 16
		out (254), a
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		xor 16
		out (254), a
	#endasm	
}

int espera_pasiva (int espera) {
	int i,j = 0;
	for (i = 0; i < espera; ++i) {
		for (j = 0; j < 250; ++j) { 
		}
	}
}

void game_over (void) {
	int k=0;
	for (k=0;k<4;++k){
		print_str (2, 9+k, 79, text_game_over[k]);
	}
	sp_UpdateNow ();
}

int musical_end(void){
	int k=0;
#asm
	ld HL,PATTERN_PTR
	ld (HL),2
	ld HL,NOTE_PTR
	ld (HL),99
#endasm	
	for (k=1;k<16;++k){
		#asm
		call nextnote
		#endasm
	}
}

int read_keys_joystick_helper(void){
	if (selected_android==1){
		gpit = read_vjoystick_tcpip (0);
		if (gpit==255){
			gpit = (joyfunc) (&keys); // Leemos del teclado
		}
	}else{
		gpit = (joyfunc) (&keys); // Leemos del teclado
	}
}

unsigned char move (void) {
	
	int i,j=0;
	
	read_keys_joystick_helper();

	gpx = player.x >> 6; // dividimos entre 64 para pixels, y luego entre 16 para tiles.
	gpy = player.y >> 6;
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
	i=gpx & 15;
	j=gpy & 15;
	
	player.vy = 0;
	
	// Movimiento vertical no inercial pero efectivo:
	if ( (gpit & sp_UP) == 0 && (gpyy > 2)) {
		// estamos ascendiendo
		if (i >= 12 || attr (gpxx, gpyy - 1 ) <= 7){
		   if (i <= 4 || attr (gpxx + 1, gpyy - 1 ) <= 7) {
			player.y=player.y-1024;
			playerB.y=playerB.y-1024;
			player.vy = -1;
		   }
		}
	}else if ( (gpit & sp_DOWN) == 0 && (gpyy < 4)) {
		// estamos descendiendo
		if (j >= 8){
			move_helper();
		}else if (i >= 12 || attr (gpxx, gpyy + 1) <= 7){
			if (i <= 4 || attr (gpxx + 1, gpyy + 1) <= 7){
				move_helper();
			}
		}
	}
	
	// Horizontal movement
	if (((gpit & sp_LEFT) == 0)&&(player.vx > -PLAYER_MAX_VX)) {
		// move left
		player.facing = 0;
		player.vx -= PLAYER_AX;
	}else if (((gpit & sp_RIGHT) == 0)&&(player.vx < PLAYER_MAX_VX)) {
		// move right
		player.vx += PLAYER_AX;
		player.facing = 1;
	}else{
		// don't move (remove inertia)
		if (player.vx > 0) {
			player.vx -= PLAYER_RX;
			if (player.vx < 0){
				player.vx = 0;
			}
		} else if (player.vx < 0) {
			player.vx += PLAYER_RX;
			if (player.vx > 0){
				player.vx = 0;
			}
		}
	}

	if (player.vx < 0 && i < 12) {
		if ( (j < 8 && attr (gpxx, gpyy) > 7) || (j && attr (gpxx, gpyy + 1) > 7)) {
			player.vx = 0;
			player.x += 128;
		} 
	} else if (i >= 4) {
		if ( (j < 8 && attr (gpxx + 1, gpyy) > 7) || (j && attr (gpxx + 1, gpyy + 1) > 7)) {
			player.vx = 0;
			player.x -= 128;
		} 
	}
	
	player.x = player.x + player.vx;
	
	// Safe
	
	if (player.x < 0){
		player.x = 0;
	}
		
	if (player.x > 14336)
		player.x = 14336;
	
	// Select animation frame 	
	gpit = player.facing << 2;
	
	if (player.vx == 0 && player.vy == 0) {
		player.next_frame = player_frames [gpit + 1];
		playerB.next_frame = player_framesB [gpit + 1];
	} else {
		++player.subframe;
		if (player.subframe == 4) {
			player.subframe = 0;
			player.frame = (player.frame + 1) & 3;
			step ();
		}
		player.next_frame = player_frames [gpit + player.frame];
		playerB.next_frame = player_framesB [gpit + player.frame];
	}

}

int move_helper(){
	player.y=player.y+1024;
	playerB.y=playerB.y+1024;
	player.vy = 1;
}

void draw_scr () {
	// Desempaqueta y dibuja una pantalla, actualiza el array map_attr
	// y hace algunas otras cosillas más (cambiar sprites de enemigos/plataformas, etc)
	
	print_str (3, 21, colorM4, texts_interact[0]); // clean interaction text 
	
	//map_pointer = mapa + (n_pant * 45);
	// trick to reduce memory, last row is same tile always except screens 0 and 7
	// so we remove from mapa.h the last files from those screens and set directly
	map_pointer = mapa;
	if (n_pant>0){
		map_pointer = map_pointer + (n_pant * 38) + 7 + ((n_pant/8)*7);//optimization
	}
	
	// Draw 6*15=90 tiles
	for (gpit = 0; gpit < 90; ++gpit) {	//90
		
		gpd=3;
		
		if (n_pant==0 || n_pant==7 || gpit<75) {
			// Mapa tipo PACKED
			gpd = gpc & 15; // default
			if (!(gpit & 1)) { // decompress case
				gpc = *map_pointer ++;
				gpd = gpc >> 4;
			}
		}
		
		switch (n_pant){
			case 1:
				switch (gpit){
					case 60:
						gpd=45;
						break;
					case 61:
						gpd=46;
						break;
				};
				break;
			case 3:
				switch (gpit){
					case 73:
						gpd=45;
						break;
					case 74:
						gpd=46;
						break;
				};
				break;
		}
		
		map_attr [gpit] = gpd==3?4:8; // easy for this game
		
		if (n_pant==0 && gpd==3){
			gpd=42;
			map_attr [59] = 8; // do not go there...
		}
		map_buff [gpit] = gpd;
		
		draw_coloured_tile_in_viewport((gpit%15)*2,(gpit/15)*2,gpd);
		
	}
	
}

void Setup_Tileset_Sprites(void){
	int i=0;
	
	// Load tileset
	unsigned char *allpurposepuntero;
	
	allpurposepuntero = tileset;
	for (i = 0; i < 256; ++i) {
		sp_TileArray (i, allpurposepuntero);
		allpurposepuntero += 8;
	}

	// Clipping rectangle
	spritesClipValues.row_coord = VIEWPORT_Y;
	spritesClipValues.col_coord = VIEWPORT_X;
	spritesClipValues.height = 12;
	spritesClipValues.width = 30;
	spritesClip = &spritesClipValues;
	
	// Sprite creation
	sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a, 2, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	sp_playerB = sp_CreateSpr (sp_MASK_SPRITE, 3, Bsprite_2_a, 2, TRANSPARENT);
	sp_AddColSpr (sp_playerB, Bsprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_playerB, Bsprite_2_c, TRANSPARENT);
	
	player.current_frame = player.next_frame = sprite_2_a;
	playerB.current_frame = playerB.next_frame = Bsprite_2_a;

	// Other walking characters
	sp_moviles [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_moviles [gpit], sprite_9_b, TRANSPARENT);
	sp_AddColSpr (sp_moviles [gpit], sprite_9_c, TRANSPARENT);	
	en_an.current_frame = en_an.next_frame = sprite_9_a;
	sp_movilesB [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, Bsprite_9_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_movilesB [gpit], Bsprite_9_b, TRANSPARENT);
	sp_AddColSpr (sp_movilesB [gpit], Bsprite_9_c, TRANSPARENT);	
	en_anB.current_frame = en_anB.next_frame = Bsprite_9_a;					
	
}

void colorize_texts (int posi){
//	// Add some animation to the main menu
	*texts_menu_tmp=*((texts_menu[0])+posi);
	print_str (4+posi, 0, (rand()%6)+2, texts_menu_tmp);
	sp_UpdateNow();
}

void select_joyfunc () {
	
	unsigned char i;
	selected_android = 0;

	gpit = 0;
	
	#asm
		; Music generated by beepola
		call musicstart
	#endasm

	while (!gpit) {

		// Add some animation to the main menu
		i=(i+1)%26;
		colorize_texts(i);
		
		#asm
			; Music generated by beepola
			call nextnote
		#endasm

		seed[0]=(seed[0]+1)%1000;
	
		gpjt = sp_GetKey ();
		
		switch (gpjt) {
			case '1':
				gpit = 1;
				joyfunc = sp_JoyKeyboard;
				break;
			case '2':
				gpit = 1;
				joyfunc = sp_JoyKempston;				
				break;
			case '3':
				gpit = 1;
				joyfunc = sp_JoySinclair1;
				break;
			case '5':
				scroll_texts = !scroll_texts;
				speakup(1, 15, 4, 16, 16, colorM4, texts_menu[scroll_texts?10:6]);	
				break;
		}	
	}
	
	peta_el_beeper(9);
	
	#asm
		di
	#endasm
	
}

void mueve_bicharracos (void) {
	int i;
	MALOTE *malote_obj = &(malotes[n_pant]);
	
	(*malote_obj).x += (*malote_obj).mx;
	gpen_cx = (*malote_obj).x;
	if (gpen_cx == (*malote_obj).x1 || gpen_cx == (*malote_obj).x2){
		(*malote_obj).mx = -((*malote_obj).mx);
	}
		
	(*malote_obj).y += (*malote_obj).my;
	gpen_cy = (*malote_obj).y;
	if (gpen_cy == (*malote_obj).y1 || gpen_cy == (*malote_obj).y2){
		(*malote_obj).my = -((*malote_obj).my);
	}
		
	// Animate
	++en_an.count;
	if (en_an.count == 4) {
		en_an.count = 0;
		en_an.frame = !en_an.frame;
		i=en_an.base_frame + en_an.frame;
		en_an.next_frame = enem_frames [i];
		en_anB.next_frame = enem_framesB [i];
	}
	
}
