// Motor.h
void step (void);
void speakup_character(unsigned char *message1, unsigned char *message2, int mc);
void speakup(int who, int x, int y, unsigned char textx, unsigned char texty, unsigned char color, unsigned char *message);

#ifdef ANDROID_TCP_IP

extern char __LIB__              *strstr(char *, char *);
extern void __LIB__              *memset(void *, unsigned char, uint);
int sockfd, connfd, polled, rc;
struct sockaddr_in my_addr;
char rxdata[128];
struct pollfd p;        /* the poll information structure */
int sent_ack_first_time=-1;
int selected_android = 0;
int configured_android = 0;
int client_is_joystick = 0;
int simulate_key_d = 0;
unsigned char res_rnd = 0;

unsigned char read_vjoystick_tcpip (int initialize);
	
int init_tcpip () {
	char keypressed = 0;
	unsigned char x=0;
	
	sent_ack_first_time=-1;
	
	while(sent_ack_first_time == -1){
		
		if (create_socket()==-1){
			return -1;
		}
		
		read_vjoystick_tcpip (1);
		
		if (sent_ack_first_time == -1){
			sockclose(sockfd);
		}
		
	}
	
	return 1;
}

int create_socket () {
	/* Create the socket */
	/* The first argument, AF_INET is the family. The Spectranet only
	   supports AF_INET at present. SOCK_STREAM in this context is
	   for a TCP connection. */
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
			//printf("Could not open the socket - rc=%d\n", sockfd);
			sp_Border (RED);
			return -1;
	}

	/* Now set up the sockaddr_in structure. */
	/* Zero it out so that any fields we don't set are set to
	   NULL (the structure also contains the local address to bind to). 
	   We will listne to port 8081. */
	   
	
	memset(&my_addr, 0, sizeof(my_addr));   /* zero out all fields */
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(8081);           /* Port 8081 */

	if(bind(sockfd, &my_addr, sizeof(my_addr)) < 0)
	{
			sp_Border (RED);
			sockclose(sockfd);
			return -1;
	}
				
	/* The socket should now listen. The Spectranet hardware in
	   its present form doesn't support changing the backlog, but
	   the second argument to listen should still be a sensible value */
	if(listen(sockfd, 1) < 0)
	{
			//printf("listen failed.\n");
			sp_Border (RED);
			sockclose(sockfd);
			return -1;
	}
	
	return 0;
}

unsigned char read_vjoystick_tcpip (int initialize) {
	
	char *retV;
	struct sockaddr_in* tmpsck = NULL;
	socklen_t * tmplen = NULL;
	unsigned char accumulated_actions=255;
	unsigned char no_action=255;
	char res = 1;
	int i,j=0;
	
	if (initialize==1){
		espera_pasiva(20);
	}
		
	/* pollall() fills a pollfd struct when something happens.
	   It returns the socket descriptor on which that something
	   happened */
	polled=pollall(&p);

	/* Was the socket descriptor the listening socket? */
	if(polled == sockfd)
	{
			/* Yes. So accept the incoming connection. */
			//printf("Accepting a new connection...\n");
			connfd=accept(sockfd, tmpsck, tmplen);
			polled=pollall(&p);
			client_is_joystick=0;
	}
	/* if any other socket descriptor returned status, then
	   something happened on a communication socket */
	else if(polled > 0)
	{
			/* Did the other end hang up on us? */
			if(p.revents & POLLHUP)
			{
					//printf("Remote host disconnected\n");
					
					/* ...so close our end too and free the fd */
					sockclose(polled);
					
					/* Close the listening socket and exit while. */
					//sockclose(sockfd);
					return no_action;
			}
			/* No, the other end didn't hang up */
			else
			{
					/* Some data is ready to collect */
					rc=recv(polled, rxdata, sizeof(rxdata)-1, 0);
					if(rc < 0)
					{
							//printf("recv failed!\n");
							sockclose(polled);
							
							/* Close the listening socket and exit while. */
							sockclose(sockfd);
							return no_action;
					}
	
					/* Ensure there's a null on the end */
					*(rxdata+rc)=0;
					
					retV=strstr(rxdata, "START");
					if(retV != NULL) {
						client_is_joystick=1;
					}
					
					// Not used in this game
					//retV=strstr(rxdata, "UP");
					//retV=strstr(rxdata, "U");
					//if(retV != NULL) {
					//	//00000001
					//	accumulated_actions = accumulated_actions & ~sp_UP;
					//}
					
					//retV=strstr(rxdata, "DOWN");
					retV=strstr(rxdata, "D");
					if(retV != NULL) {
						//00000010
						accumulated_actions = accumulated_actions & ~sp_DOWN;
					}
					
					//retV=strstr(rxdata, "LEFT");
					retV=strstr(rxdata, "L");
					if(retV != NULL) {
						//00000100
						accumulated_actions = accumulated_actions & ~sp_LEFT;
					}
					
					//retV=strstr(rxdata, "RIGHT");
					retV=strstr(rxdata, "R");
					if(retV != NULL) {
						//00001000
						accumulated_actions = accumulated_actions & ~sp_RIGHT;
					}
					
					//retV=strstr(rxdata, "BUTTON1");
					retV=strstr(rxdata, "B");
					if(retV != NULL) {
						//10000000
						if (simulate_key_d<2){
							simulate_key_d++;
						}//else{
							//simulate_key_d=simulate_key_d+1;
						//}
						
						//accumulated_actions = accumulated_actions & ~sp_FIRE;
					}//else{
						//simulate_key_d=0;
					//}
					
					// Not used in this game
					//retV=strstr(rxdata, "BUTTON2");
					//if(retV != NULL) {
					//	//10000000
					//	//accumulated_actions = accumulated_actions & ~sp_FIRE;
					//}
					
					//retV=strstr(rxdata, "BUTTON3");
					//if(retV != NULL) {
					//	//10000000
					//	accumulated_actions = accumulated_actions & ~sp_FIRE;
					//}
					
					if (client_is_joystick==0){
						// We do not want this connection!
						/* ...so close our end too and free the fd */
						sockclose(polled);
				
						/* Close the listening socket and exit while. */
						sockclose(sockfd);
						
						//sp_Border (BLUE);
						
						return no_action;
					}
										
					/* Send ID to client. This will verify that I am the correct IP */
					if (sent_ack_first_time==-1){
						rc=send(polled, "TCPIPJOYSTICKSPECTRUM\r\n", 25, 0);
						if(rc < 0)
						{
							sockclose(polled);
							sockclose(sockfd);
							return no_action;
						}else{
							sent_ack_first_time=1;
							return sp_FIRE;
						}	
						
					}

					return accumulated_actions;
			}
	}
	
	return no_action;
}
#endif

void speakup_character(unsigned char *message1, unsigned char *message2, int mc){
	int i;
	
	if (mc){
		i=0;
		speakup(1,4,0,9,i++,colorM1,message1);
		if (*message2){
			speakup(1,4,0,9,i,colorM1,message2);
		}
	}else{
		i=3;
		speakup(n_pant,26,3,1,i++,colorM2,message1);
		if (*message2){
			speakup(n_pant,26,3,1,i,colorM2,message2);
		}
	}
	espera_pasiva(ESPERA_PASIVA);
}

int speakup_clear(int posx){
	int i,j;
	
	
	i=(posx==9?0:3);
	for (j=i;j<(i+2);j++){
		print_str (posx, j, colorM2, action_text_46);
	}
	sp_UpdateNow();	
	
}

void speakup(int who, int x, int y, unsigned char textx, unsigned char texty, unsigned char color, unsigned char *message){
	
	int which_face=0;
	
	draw_coloured_tile (x-2, y, 1); // Face frame
	draw_coloured_tile (x+2, y, 1); // Face frame
	
	while (*message) {
		sp_PrintAtInv (texty, textx ++, color, (*message ++) - 32);
		if (who<9){
			draw_coloured_tile (x, y, which_face<4? 15+who:31+who); // Face stand	
		}else if (who==9){
			draw_coloured_tile (x, y, which_face<4? 2:5); // Face stand
		}else if (who==10){
			draw_coloured_tile (x, y, which_face<4? 39:30); // Face stand
		}		
		which_face=(which_face+1)%8;		
		espera_pasiva(1);
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

#ifdef ANDROID_TCP_IP
	unsigned char *enem_frames [] = {
		sprite_9_a, sprite_10_a, sprite_11_a, sprite_12_a
	};

	unsigned char *enem_framesB [] = {
		Bsprite_9_a, Bsprite_10_a, Bsprite_11_a, Bsprite_12_a
	};
#else
	unsigned char *enem_frames [] = {
		sprite_9_a, sprite_10_a, sprite_11_a, sprite_12_a, sprite_13_a, sprite_14_a
	};

	unsigned char *enem_framesB [] = {
		Bsprite_9_a, Bsprite_10_a, Bsprite_11_a, Bsprite_12_a, Bsprite_13_a, Bsprite_14_a
	};
#endif

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
#ifndef ANDROID_TCP_IP
	
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
#else
	return res_rnd++%18;
#endif
}

void cortina (void) {
#ifndef ANDROID_TCP_IP
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
#else
	blackout();
#endif
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
	for (i = 0; i < espera; i ++) {
		for (j = 0; j < 250; j ++) { 
		}
	}
}

void game_over (void) {
	int k=0;
#ifndef ANDROID_TCP_IP	
	for (k=0;k<4;k++){
		print_str (2, 9+k, 79, text_game_over[k]);
	}
#else
	print_str (2, 10, 79, text_game_over[0]);
#endif
	sp_UpdateNow ();
	espera_pasiva(200);
}

// Engine globals (for speed) & size!
unsigned char gpx, gpy, gpd, gpc, gpt;
unsigned char gpxx, gpyy;
unsigned char gpen_x, gpen_y, gpen_cx, gpen_cy, gpen_xx, gpen_yy;
unsigned char tocado, active;
unsigned char gpit, gpjt;
unsigned char enoffsmasi;
unsigned char *map_pointer;

void read_keys_joystick_helper(void){
#ifdef ANDROID_TCP_IP
	if (selected_android==1){
		gpit = read_vjoystick_tcpip (0);
		if (gpit==255){
			gpit = (joyfunc) (&keys); // Leemos del teclado
		}
	}else{
		gpit = (joyfunc) (&keys); // Leemos del teclado
	}
#else
	gpit = (joyfunc) (&keys); // Leemos del teclado
#endif	
}

unsigned char move (void) {
	
	read_keys_joystick_helper();

	// sin movimiento vertical 
	if (player.vy < PLAYER_MAX_VY_CAYENDO)
		player.vy += PLAYER_G;
	else
		player.vy = PLAYER_MAX_VY_CAYENDO;
	
	player.y += player.vy;
	
	gpx = player.x >> 6; // dividimos entre 64 para pixels, y luego entre 16 para tiles.
	gpy = player.y >> 6;
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
	
	player.vy = 0;
	player.y = gpyy << 10;
	
	// Movimiento horizontal:
	if ( ! ((gpit & sp_LEFT) == 0 || (gpit & sp_RIGHT) == 0)) {
		if (player.vx > 0) {
			player.vx -= PLAYER_RX;
			if (player.vx < 0)
				player.vx = 0;
		} else if (player.vx < 0) {
			player.vx += PLAYER_RX;
			if (player.vx > 0)
				player.vx = 0;
		}
	}

	if ((gpit & sp_LEFT) == 0) {
		if (player.vx > -PLAYER_MAX_VX) {
			player.facing = 0;
			player.vx -= PLAYER_AX;
		}
	}

	if ((gpit & sp_RIGHT) == 0) {
		if (player.vx < PLAYER_MAX_VX) {
			player.vx += PLAYER_AX;
			player.facing = 1;
		}
	}

	player.x = player.x + player.vx;
	
	// Safe
	
	if (player.x < 0)
		player.x = 0;
		
	if (player.x > 14336)
		player.x = 14336;
	
	// Select animation frame 	
	gpit = player.facing << 2;
	if (player.vx == 0) {
		player.next_frame = player_frames [gpit + 1];
		playerB.next_frame = player_framesB [gpit + 1];
	} else {
		player.subframe ++;
		if (player.subframe == 4) {
			player.subframe = 0;
			player.frame = (player.frame + 1) & 3;
			step ();
		}
		player.next_frame = player_frames [gpit + player.frame];
		playerB.next_frame = player_framesB [gpit + player.frame];
	}

}

void draw_scr () {
	// Desempaqueta y dibuja una pantalla, actualiza el array map_attr
	// y hace algunas otras cosillas más (cambiar sprites de enemigos/plataformas, etc)
	
	map_pointer = mapa + (n_pant * 30);
	
	gpx = gpy = 0;	

	// Draw 6*15=90 tiles
	
	for (gpit = 0; gpit < 90; gpit ++) {	//90
		if (gpit<60){
			// Mapa tipo PACKED
			if (!(gpit & 1)) {
				gpc = *map_pointer ++;
				gpd = gpc >> 4;
			} else {
				gpd = gpc & 15;
			}
		}else{
			// Optimization via peculiarity of this map: the last two rows are floor
			// every room is exactly the same, so we can avoid the use of the map data
			// reducing the size of the map
			gpd=3;
		}
		//map_attr [gpit] = comportamiento_tiles [gpd];
		if (gpd==3){
			
		}
		map_attr [gpit] = gpd==3? 4:0; // easy for this game
		map_buff [gpit] = gpd;		
		draw_coloured_tile (VIEWPORT_X + gpx, VIEWPORT_Y + gpy, gpd);	
		gpx += 2;
		if (gpx == 30) {
			gpx = 0;
			gpy += 2;
		}	
	}
	
	// Movemos y cambiamos a los enemigos según el tipo que tengan
	enoffs = n_pant;

	// only one extra walking character per screen due to memory/engine limitations	
	en_an [0].frame = 0;
	en_an [0].count = 3;
	en_an [0].base_frame = (malotes [enoffs + 0].t - 1) << 1;
	
}

void Setup_Tileset_Sprites(void){
	int i=0;
	
	// Load tileset
	unsigned char *allpurposepuntero;
	
	allpurposepuntero = tileset;
	for (i = 0; i < 256; i++) {
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
	sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	sp_playerB = sp_CreateSpr (sp_MASK_SPRITE, 3, Bsprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_playerB, Bsprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_playerB, Bsprite_2_c, TRANSPARENT);
	
	player.current_frame = player.next_frame = sprite_2_a;
	playerB.current_frame = playerB.next_frame = Bsprite_2_a;

	// Walking persons
	sp_moviles [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a, 2, TRANSPARENT);
	sp_AddColSpr (sp_moviles [gpit], sprite_9_b, TRANSPARENT);
	sp_AddColSpr (sp_moviles [gpit], sprite_9_c, TRANSPARENT);	
	en_an [gpit].current_frame = en_an [gpit].next_frame = sprite_9_a;
	sp_movilesB [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, Bsprite_9_a, 2, TRANSPARENT);
	sp_AddColSpr (sp_movilesB [gpit], Bsprite_9_b, TRANSPARENT);
	sp_AddColSpr (sp_movilesB [gpit], Bsprite_9_c, TRANSPARENT);	
	en_anB [gpit].current_frame = en_anB [gpit].next_frame = Bsprite_9_a;					
}
	
void select_joyfunc () {
	
#ifdef ANDROID_TCP_IP
	unsigned char i;
	selected_android = 0;
#endif

	gpit = 0;
	
#ifndef ANDROID_TCP_IP
	#asm
		; Music generated by beepola
		call musicstart
	#endasm
#endif
	
	while (!gpit) {
		
#ifndef ANDROID_TCP_IP
		#asm
			; Music generated by beepola
			call nextnote
		#endasm
#endif

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
#ifdef ANDROID_TCP_IP
			case '4':
				peta_el_beeper (9);
				if (configured_android==0){
					if (init_tcpip () == -1){
						peta_el_beeper (9);
					}else{
						selected_android = 1;
						configured_android = 1;
						gpit = 1;
						joyfunc = sp_JoyKeyboard;
					}
				}else{
					selected_android = 1;
					configured_android = 1;
					gpit = 1;
					joyfunc = sp_JoyKeyboard;
				}
				break;
			
#endif		
			case '5':
				ending = (ending+1)%2;
				if (ending){
					speakup(1, 15, 4, 17, 16, colorM3, texts_menu[10]);	
				}else{
					speakup(1, 15, 4, 17, 16, colorM3, texts_menu[6]);
				}
				
				break;
		}	

#ifdef ANDROID_TCP_IP
		if (configured_android==1){
			i = read_vjoystick_tcpip (0);
			if (i==~sp_FIRE){
				selected_android = 1;
				gpit = 1;
				joyfunc = sp_JoyKeyboard;
			}	
		}		
#endif		

	}
	
	peta_el_beeper(9);
	
	#asm
		di
	#endasm
	
}
		
void mueve_bicharracos (void) {
	
	gpx = player.x >> 6;
	gpy = player.y >> 6;
	
	tocado = 0;
	// gpit=0 controls the walking fan or the Chef 
	gpit = 0; // only one extra walking character per screen due to memory/engine limitations	
	enoffsmasi = enoffs + gpit;
	gpen_x = malotes [enoffsmasi].x;
	gpen_y = malotes [enoffsmasi].y;		
	gpt = malotes [enoffsmasi].t;
	
	// gpt = 4 ALWAYS
	active = 1;
	malotes [enoffsmasi].x += malotes [enoffsmasi].mx;
	malotes [enoffsmasi].y += malotes [enoffsmasi].my;
	gpen_cx = malotes [enoffsmasi].x;
	gpen_cy = malotes [enoffsmasi].y;
	gpen_xx = gpen_cx >> 4;
	gpen_yy = gpen_cy >> 4;
	if (gpen_cx == malotes [enoffsmasi].x1 || gpen_cx == malotes [enoffsmasi].x2)
		malotes [enoffsmasi].mx = -malotes [enoffsmasi].mx;
	if (gpen_cy == malotes [enoffsmasi].y1 || gpen_cy == malotes [enoffsmasi].y2)
		malotes [enoffsmasi].my = -malotes [enoffsmasi].my;
	
	// Animate
	en_an [gpit].count ++; 
	if (en_an [gpit].count == 4) {
		en_an [gpit].count = 0;
		en_an [gpit].frame = !en_an [gpit].frame;
		en_an [gpit].next_frame = enem_frames [en_an [gpit].base_frame + en_an [gpit].frame];
		en_anB [gpit].next_frame = enem_framesB [en_an [gpit].base_frame + en_an [gpit].frame];
	}
	
}
