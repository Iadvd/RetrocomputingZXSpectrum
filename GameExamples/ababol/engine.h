// Motor.h
// Contiene las cosas del motor para la churrera, a saber:

// 1.- Inicializaciones (de enemigos y de cosas varias).
// 2.- Movimiento del prota.
// 3.- Movimiento de los enemigos/plataformas moviles.
// 4.- Dibujado de la pantalla (depacking/render).

#define EST_NORMAL 		0
#define EST_PARP 		2
#define EST_MUR 		4
#define sgni(n)			(n < 0 ? -1 : 1)

// Codigo para joystick virtual Android compatible con Spectranet (comienzo)
extern char __LIB__              *strstr(char *, char *);
extern void __LIB__              *memset(void *, unsigned char, uint);
int sockfd, connfd, polled, rc;
struct sockaddr_in my_addr;
char rxdata[30];
struct pollfd p;        /* the poll information structure */
int sent_ack_first_time;
int simulate_key_press = 0;

unsigned char read_vjoystick_tcpip ();

int init_tcpip () {
	char keypressed = 0;
	char res = 1;
	int i;
	int j;
	
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
	
	sent_ack_first_time = -1;
	
	while((sent_ack_first_time == -1)&&(keypressed!=1))
	{
			read_vjoystick_tcpip ();
			if (sp_GetKey ()) {
				keypressed = 1;	
			}
	}
	
	return 0;
}

unsigned char read_vjoystick_tcpip () {
	char *retV;
	struct sockaddr_in* tmpsck = NULL;
	socklen_t * tmplen = NULL;
	unsigned char no_action=255;
	unsigned char accumulated_actions=255;
	
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
					sockclose(sockfd);
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
					
					retV=strstr(rxdata, "UP");
					if(retV != NULL) {
						//00000001
						accumulated_actions = accumulated_actions & ~sp_UP;
					}
					
					retV=strstr(rxdata, "DOWN");
					if(retV != NULL) {
						//00000010
						accumulated_actions = accumulated_actions & ~sp_DOWN;
					}
					
					retV=strstr(rxdata, "LEFT");
					if(retV != NULL) {
						//00000100
						simulate_key_press = 1;
						accumulated_actions = accumulated_actions & ~sp_LEFT;
					}
					
					retV=strstr(rxdata, "RIGHT");
					if(retV != NULL) {
						//00001000
						simulate_key_press = 2;
						accumulated_actions = accumulated_actions & ~sp_RIGHT;
					}
					
					retV=strstr(rxdata, "BUTTON1");
					if(retV != NULL) {
						//10000000
						accumulated_actions = accumulated_actions & ~sp_FIRE;
					}
					
					retV=strstr(rxdata, "BUTTON2");
					if(retV != NULL) {
						//10000000
						accumulated_actions = accumulated_actions & ~sp_FIRE;
					}
					
					retV=strstr(rxdata, "BUTTON3");
					if(retV != NULL) {
						//10000000
						accumulated_actions = accumulated_actions & ~sp_FIRE;
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

// Codigo para joystick virtual Android compatible con Spectranet (final)

typedef struct {
	int x, y, cx;
	int vx, vy;
	char g, ax, rx;
	unsigned char salto, cont_salto;
	unsigned char *current_frame, *next_frame;
	unsigned char saltando;
	unsigned char frame, subframe, facing;
	unsigned char estado;
	unsigned char ct_estado;
	unsigned char gotten;
	unsigned char life, objs, keys;
} INERCIA;

INERCIA player;

typedef struct {
	unsigned char frame;
	unsigned char count;
	unsigned char *current_frame, *next_frame;
} ANIMADO;

ANIMADO en_an [3];

// atributos de la pantalla: Contiene información
// sobre qué tipo de tile hay en cada casilla
unsigned char map_attr [150];
unsigned char map_buff [150];

// posición del objeto (hotspot). Para no objeto,
// se colocan a 240,240, que está siempre fuera de pantalla.
unsigned char hotspot_x;
unsigned char hotspot_y;
unsigned char orig_tile;	// Tile que había originalmente bajo el objeto

unsigned char pant_final;

// Funciones:

void srand (unsigned int new_seed) {
	seed [0] = new_seed;	
}

unsigned char rand () {
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

void step () {
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

void cortina () {
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
	// Estoy llorando 
}

// Game

char espera_activa (int espera) {
	
	// jL
	
	// Esta función espera un rato o hasta que se pulse una tecla.
	// Si se pulsa una tecla, devuelve 0
	
	// Esta función sólo funciona en Spectrum.
	// en CPC no hay una interrupción cada 20ms, asín que esto no
	// sirve "pa ná".
	
	char res = 1;
	int i;
	int j;
	
	// Codigo para joystick virtual Android compatible con Spectranet (comienzo)
	unsigned char r;
	
	for (i = 0; i < espera && res; i ++) {
		for (j = 0; j < 250; j ++) {
			res = 1;
		}
		
		// Codigo para joystick virtual Android compatible con Spectranet (comienzo)
		r = read_vjoystick_tcpip ();
		if (r==255){
			if (sp_GetKey ()) 
			res = 0;
		}else{
			res = 0;
		}
		
	}
	
	return res;
}

void attr (char x, char y) {
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	if (x < 0 || y < 0) return 2;
	return map_attr [x + (y << 4) - y];	
}

void qtile (unsigned char x, unsigned char y) {
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	return map_buff [x + (y << 4) - y];	
}

void draw_life () {
	sp_PrintAtInv (LIFE_Y, LIFE_X, 69, 16 + player.life / 100);
	sp_PrintAtInv (LIFE_Y, 1 + LIFE_X, 69, 16 + (player.life % 100) / 10);
	sp_PrintAtInv (LIFE_Y, 2 + LIFE_X, 69, 16 + player.life % 10);
}

void draw_objs () {
	sp_PrintAtInv (OBJECTS_Y, OBJECTS_X, 69, 16 + player.objs / 10);
	sp_PrintAtInv (OBJECTS_Y, 1 + OBJECTS_X, 69, 16 + player.objs % 10);
}

void draw_keys () {
	sp_PrintAtInv (KEYS_Y, KEYS_X, 69, 16 + player.keys / 10);
	sp_PrintAtInv (KEYS_Y, 1 + KEYS_X, 69, 16 + player.keys % 10);
}

void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t) {
	unsigned char *pointer;
	unsigned char xx, yy;
	
#ifdef USE_AUTO_SHADOWS
	xx = (x - VIEWPORT_X) >> 1;
	yy = (y - VIEWPORT_Y) >> 1;	
	if (attr (xx, yy) < 2 && (t < 16 || t == 19)) {
		t = 64 + (t << 2);
		pointer = (unsigned char *) &tileset [2048 + t];
		sp_PrintAtInv (y, x, attr (xx - 1, yy - 1) == 2 ? (pointer[0] & 7)-1 : pointer [0], t);
		sp_PrintAtInv (y, x + 1, attr (xx, yy - 1) == 2 ? (pointer[1] & 7)-1 : pointer [1], t + 1);
		sp_PrintAtInv (y + 1, x, attr (xx - 1, yy) == 2 ? (pointer[2] & 7)-1 : pointer [2], t + 2);
		sp_PrintAtInv (y + 1, x + 1, pointer [3], t + 3);
	} else {
#endif

#ifdef USE_AUTO_TILE_SHADOWS
	xx = (x - VIEWPORT_X) >> 1;
	yy = (y - VIEWPORT_Y) >> 1;	
	if (attr (xx, yy) < 2 && (t < 16 || t == 19)) {
		t = 64 + (t << 2);
		pointer = (unsigned char *) &tileset [2048 + t];
		if (attr (xx - 1, yy - 1) == 2) {
			sp_PrintAtInv (y, x, pointer [128], 128 + t);
		} else {
			sp_PrintAtInv (y, x, pointer [0], t);
		}
		if (attr (xx, yy - 1) == 2) {
			sp_PrintAtInv (y, x + 1, pointer [129], 129 + t);
		} else {
			sp_PrintAtInv (y, x + 1, pointer [1], t + 1);
		}
		if (attr (xx - 1, yy) == 2) {
			sp_PrintAtInv (y + 1, x, pointer [130], 130 + t);
		} else {
			sp_PrintAtInv (y + 1, x, pointer [2], t + 2);
		} 
		sp_PrintAtInv (y + 1, x + 1, pointer [3], t + 3);
	} else {
#endif
		t = 64 + (t << 2);
		pointer = (unsigned char *) &tileset [2048 + t];
		sp_PrintAtInv (y, x, pointer [0], t);
		sp_PrintAtInv (y, x + 1, pointer [1], t + 1);
		sp_PrintAtInv (y + 1, x, pointer [2], t + 2);
		sp_PrintAtInv (y + 1, x + 1, pointer [3], t + 3);
#ifdef USE_AUTO_SHADOWS
	}
#endif

#ifdef USE_AUTO_TILE_SHADOWS
	}
#endif
	
}

void game_ending () {
	unsigned char x;
	
	sp_UpdateNow();
	unpack ((unsigned int) (s_ending));
	
	for (x = 0; x < 4; x ++) {
		peta_el_beeper (1);
		peta_el_beeper (0);
	}
	peta_el_beeper (5);
	
	espera_activa (500);
}

void game_over () {
	unsigned char x, y;
	for (y = 11; y < 14; y ++)
		for (x = 10; x < 22; x ++)
			sp_PrintAtInv (y, x, 72, 0);
			
	sp_PrintAtInv (12, 11, 79, 39);
	sp_PrintAtInv (12, 12, 79, 33);
	sp_PrintAtInv (12, 13, 79, 45);
	sp_PrintAtInv (12, 14, 79, 37);
	sp_PrintAtInv (12, 16, 79, 53);
	sp_PrintAtInv (12, 17, 79, 46);
	sp_PrintAtInv (12, 18, 79, 36);
	sp_PrintAtInv (12, 19, 79, 37);
	sp_PrintAtInv (12, 20, 79, 50);

	sp_UpdateNow ();
		
	for (x = 0; x < 4; x ++) {
		peta_el_beeper (0);
		peta_el_beeper (1);
	}
	peta_el_beeper (5);
	
	espera_activa (500);
}

void clear_cerrojo (unsigned char np, unsigned char x, unsigned char y) {
	unsigned char i;
	
	// search & toggle
		
	for (i = 0; i < MAX_CERROJOS; i ++) 
		if (cerrojos [i].x == x && cerrojos [i].y == y && cerrojos [i].np == np)
			cerrojos [i].st = 0;
}

void init_cerrojos () {
	unsigned char i;
	
	// Activa todos los cerrojos
	
	for (i = 0; i < MAX_CERROJOS; i ++)
		cerrojos [i].st = 1;	
}

unsigned char move (unsigned char n_pant) {
	unsigned char xx, yy;
	unsigned char x, y;
	unsigned char i, allpurp;

	// Codigo para joystick virtual Android compatible con Spectranet (comienzo)
	i = read_vjoystick_tcpip ();
	if (i==255){
		i = (joyfunc) (&keys); // Leemos del teclado
	}	

	/* Por partes. Primero el movimiento vertical. La ecuación de movimien-
	   to viene a ser, en cada ciclo:

	   1.- vy = vy + g
	   2.- y = y + vy

	   O sea la velocidad afectada por la gravedad. 
	   Para no colarnos con los nmeros, ponemos limitadores:
	*/

	if (player.vy < PLAYER_MAX_VY_CAYENDO)
		player.vy += player.g;
	else
		player.vy = PLAYER_MAX_VY_CAYENDO;

	if (player.gotten) player.vy = 0;
		
	player.y += player.vy;
	
	// Safe
		
	if (player.y < 0)
		player.y = 0;
		
	if (player.y > 9216)
		player.y = 9216;
	
	/* El problema es que no es tan fácil... Hay que ver si no nos chocamos.
	   Si esto pasa, hay que "recular" hasta el borde del obstáculo.

	   Por eso miramos el signo de vy, para que los cálculos sean más sencillos.
	   De paso vamos a precalcular un par de cosas para que esto vaya más rápido.
	*/

	x = player.x >> 6;				// dividimos entre 64 para pixels, y luego entre 16 para tiles.
	y = player.y >> 6;
	xx = x >> 4;
	yy = y >> 4;
	
	// Paréntesis, aprovechando las variables para ahorrar... 
	// Tiles que te matan. 
	// Joer, qué ofuscao... Pero es corto y bello.
	
	if (attr (xx, yy) == 1 || 
		((x & 15) != 0 && attr (xx + 1, yy) == 1) ||
		((y & 15) != 0 && attr (xx, yy + 1) == 1) ||
		((x & 15) != 0 && (y & 15) != 0 && attr (xx + 1, yy + 1) == 1)) {
		if (player.life > 0) {
			peta_el_beeper (4);
			player.life --;	
			draw_life ();
			if (player.vy < 0) {
				player.vy = PLAYER_MAX_VX;
				player.y = (yy + 1) << 10;
				y = player.y >> 6;
				yy = y >> 4;
			} else {
				player.vy = -PLAYER_MAX_VX;
				player.y = yy << 10;
				y = player.y >> 6;
				yy = y >> 4;
			}
		}
	}
	
	// Ya	

	if (player.vy < 0) { 			// estamos ascendiendo
		//if (player.y >= 1024)
			if (attr (xx, yy) > 1 || ((x & 15) != 0 && attr (xx + 1, yy) > 1)) {
				// paramos y ajustamos:
				player.vy = 0;
				player.y = (yy + 1) << 10;
			}
	} else if (player.vy > 0) { 	// estamos descendiendo
		if (player.y < 9216)
			if (attr (xx, yy + 1) > 1 || ((x & 15) != 0 && attr (xx + 1, yy + 1) > 1))
			{
				// paramos y ajustamos:
				player.vy = 0;
				player.y = yy << 10;
			}
	}

	/* Salto: El salto se reduce a dar un valor negativo a vy. Esta es la forma más
	   sencilla. Sin embargo, para más control, usamos el tipo de salto "mario bros".
	   Para ello, en cada pulsación dejaremos decrementar vy hasta un mínimo, y de-
	   tectando que no se vuelva a pulsar cuando estemos en el aire. Juego de banderas ;)
	*/

	if ( ((i & sp_UP) == 0 || (i & sp_FIRE) == 0) && ((player.vy == 0 && player.saltando == 0 && (attr (xx, yy + 1) > 1 || ((x & 15) != 0 && attr (xx + 1, yy + 1) > 1))) || player.gotten)) {
		player.saltando = 1;
		player.cont_salto = 0;
		peta_el_beeper (3);
	}

	if ( ((i & sp_UP) == 0 || (i & sp_FIRE) == 0) && player.saltando ) {
		player.vy -= (player.salto + PLAYER_INCR_SALTO - (player.cont_salto>>1));
		if (player.vy < -PLAYER_MAX_VY_SALTANDO) player.vy = -PLAYER_MAX_VY_SALTANDO;

#ifndef PLAYER_JUMP_UNLIMITED
		player.cont_salto ++;
		if (player.cont_salto == 8)
			player.saltando = 0;
#endif
	}

	if ( (i & sp_UP) != 0 && (i & sp_FIRE) != 0)
		player.saltando = 0;
	
	// ------ ok con el movimiento vertical.

	/* Movimiento horizontal:

	   Mientras se pulse una tecla de dirección, 
	   
	   x = x + vx
	   vx = vx + ax

	   Si no se pulsa nada:

	   x = x + vx
	   vx = vx - rx
	*/

	if ( ! ((i & sp_LEFT) == 0 || (i & sp_RIGHT) == 0))
		if (player.vx > 0) {
			player.vx -= player.rx;
			if (player.vx < 0)
				player.vx = 0;
		} else if (player.vx < 0) {
			player.vx += player.rx;
			if (player.vx > 0)
				player.vx = 0;
		}

	if ((i & sp_LEFT) == 0)
		if (player.vx > -PLAYER_MAX_VX) {
			player.facing = 0;
			player.vx -= player.ax;
		}

	if ((i & sp_RIGHT) == 0)
		if (player.vx < PLAYER_MAX_VX) {
			player.vx += player.ax;
			player.facing = 1;
		}

	player.x = player.x + player.vx;
	
	// Safe
	
	if (player.x < 0)
		player.x = 0;
		
	if (player.x > 14336)
		player.x = 14336;
		
	/* Ahora, como antes, vemos si nos chocamos con algo, y en ese caso
	   paramos y reculamos */

	y = player.y >> 6;
	x = player.x >> 6;
	yy = y >> 4;
	xx = x >> 4;
	
	if (player.vx < 0) {
		if (attr (xx, yy) > 1 || ((y & 15) != 0 && attr (xx, yy + 1) > 1)) {
			// paramos y ajustamos:
			player.vx = 0;
			player.x = (xx + 1) << 10;
		}
	} else {
		if (attr (xx + 1, yy) > 1 || ((y & 15) != 0 && attr (xx + 1, yy + 1) > 1)) {
			// paramos y ajustamos:
			player.vx = 0;
			player.x = xx << 10;
		}
	}

	// Abrir cerrojo
	if ((x & 15) == 0 && (y & 15) == 0) {
		if (qtile (xx + 1, yy) == 15 && player.keys > 0) {
			map_attr [15 * yy + xx + 1] = 0;
			map_buff [15 * yy + xx + 1] = 0;
			clear_cerrojo (n_pant, xx + 1, yy);
			draw_coloured_tile (VIEWPORT_X + xx + xx + 2, VIEWPORT_Y + yy + yy, 0);
			player.keys --;
			draw_keys ();
			peta_el_beeper (1);
		} else if (qtile (xx - 1, yy) == 15 && player.keys > 0) {
			map_attr [15 * yy + xx - 1] = 0;
			map_buff [15 * yy + xx - 1] = 0;
			clear_cerrojo (n_pant, xx - 1, yy);
			draw_coloured_tile (VIEWPORT_X + xx + xx - 2, VIEWPORT_Y + yy + yy, 0);
			player.keys --;
			draw_keys ();
			peta_el_beeper (1);
		}
	}
	
	// Calculamos el frame que hay que poner:
 
	if (player.vy != 0) {
		if (player.facing == 0)
			player.next_frame = sprite_8_a;
		else
			player.next_frame = sprite_4_a;
	} else {
		if (player.vx == 0) {
			if (player.facing == 0)
				player.next_frame = sprite_6_a;
			else
				player.next_frame = sprite_2_a;
		} else {
			player.subframe ++;
			
			if (player.subframe == 4) {
				player.subframe = 0;
				player.frame = (player.frame + 1) & 3;
				step ();
			}
			if (player.facing == 0) {
				if (player.frame == 1 || player.frame == 3)
					player.next_frame = sprite_6_a;
				else if (player.frame == 0)
					player.next_frame = sprite_5_a;
				else if (player.frame == 2)
					player.next_frame = sprite_7_a;
			} else {
				if (player.frame == 1 || player.frame == 3)
					player.next_frame = sprite_2_a;
				else if (player.frame == 0)
					player.next_frame = sprite_1_a;
				else if (player.frame == 2)
					player.next_frame = sprite_3_a;
			}
		}	
	}
}

void init_player () {
	// Inicializa player con los valores iniciales
	// (de ahí lo de inicializar).
	
	player.x = 			PLAYER_INI_X << 10;
	player.y = 			PLAYER_INI_Y << 10;
	player.vy = 		0;
	player.g = 			PLAYER_G; 
	player.vx = 		0;
	player.ax = 		PLAYER_AX;
	player.rx = 		PLAYER_RX;
	player.salto = 		PLAYER_VY_INICIAL_SALTO;
	player.cont_salto = 1;
	player.saltando = 	0;
	player.frame = 		0;
	player.subframe = 	0;
	player.facing = 	1;
	player.estado = 	EST_NORMAL;
	player.life = 		PLAYER_LIFE;
	player.objs =		0;
	player.keys = 		0;
	
	pant_final = SCR_FIN;
}

void init_hotspots () {
	unsigned char i;
	for (i = 0; i < MAP_W * MAP_H; i ++)
		hotspots [i].act = 1;
}

void draw_scr (unsigned char n_pant) {
	// Desempaqueta y dibuja una pantalla, actualiza el array map_attr
	// y hace algunas otras cosillas más (cambiar sprites de enemigos/plataformas, etc)
	
	unsigned char x = 0, y = 0, i, d, t1, t2;
	unsigned int idx = n_pant * 75;
	unsigned char location;
	
	for (i = 0; i < 75; i ++) {
		location = 15 * (y >> 1) + (x >> 1);
		d = mapa [idx++];
		t1 = d >> 4;
		t2 = d & 15;
		map_attr [location] = comportamiento_tiles [t1];
		if ((rand () & 15) < 2 && t1 == 0 && map_buff [location - 16] == 0)
			t1 = 19;
		draw_coloured_tile (VIEWPORT_X + x, VIEWPORT_Y + y, t1);
		map_buff [location] = t1;
		x += 2;
		if (x == 30) {
			x = 0;
			y += 2;
		}
		location ++;
		map_attr [location] = comportamiento_tiles [t2];
		if ((rand () & 15) < 2 && t2 == 0 && map_buff [location - 16] == 0)
			t2 = 19;
		draw_coloured_tile (VIEWPORT_X + x, VIEWPORT_Y + y, t2);
		map_buff [location] = t2;
		x += 2;
		if (x == 30) {
			x = 0;
			y += 2;
		}
	}
	
	// ¿Hay objeto en esta pantalla?
	
	hotspot_x = hotspot_y = 240;
	if (hotspots [n_pant].act == 1) {
		if (hotspots [n_pant].tipo != 0) {
			// Sacamos la posición a nivel de tiles del objeto
			x = (hotspots [n_pant].xy >> 4);
			y = (hotspots [n_pant].xy & 15);
			// Convertimos la posición almacenada en píxels
			hotspot_x = x << 4;
			hotspot_y = y << 4;
			// Guardamos el tile que hay originalmente
			orig_tile = map_buff [15 * y + x];
			// Pintamos el incono del objeto
			draw_coloured_tile (VIEWPORT_X + x + x, VIEWPORT_Y + y + y, 16 + hotspots [n_pant].tipo);
		}
	} else if (hotspots [n_pant].act == 0) {
		// Aleatoriamente, ponemos una recarga de vida si no hay objeto activo.	
		if (rand () % 3 == 2) {
			// Sacamos la posición a nivel de tiles del objeto
			x = (hotspots [n_pant].xy >> 4);
			y = (hotspots [n_pant].xy & 15);
			// Convertimos la posición almacenada en píxels
			hotspot_x = x << 4;
			hotspot_y = y << 4;
			// Guardamos el tile que hay originalmente
			orig_tile = map_buff [15 * y + x];
			// Pintamos el incono del objeto
			draw_coloured_tile (VIEWPORT_X + x + x, VIEWPORT_Y + y + y, 16);	
		}
	}
	
	// Borramos los cerrojos abiertos
	for (i = 0; i < MAX_CERROJOS; i ++) {
		if (cerrojos [i].np == n_pant && !cerrojos [i].st) {
			draw_coloured_tile (VIEWPORT_X + cerrojos [i].x + cerrojos [i].x, VIEWPORT_Y + cerrojos [i].y + cerrojos [i].y, 0);
			location = 15 * cerrojos [i].y + cerrojos [i].x;
			map_attr [location] = 0;
			map_buff [location] = 0;
		}
	}
	
	// Movemos y cambiamos a los enemigos según el tipo que tengan
	enoffs = n_pant * 3;
	
	for (i = 0; i < 3; i ++) {
		en_an [i].frame = 0;
		en_an [i].count = 0;
		switch (malotes [enoffs + i].t) {
			case 0:
				sp_MoveSprAbs (sp_moviles [i], spritesClip, 0, 22, 0, 0, 0);
				break;
			case 1:
				en_an [i].next_frame = sprite_9_a;
				break;
			case 2:
				en_an [i].next_frame = sprite_11_a;
				break;
			case 3:
				en_an [i].next_frame = sprite_13_a;
				break;
			case 4:
				en_an [i].next_frame = sprite_15_a;
		}
	}
}

// From beepola. Phaser engine by Shiru.
#include "music.h"

// Esto se emplea en el menú
// 1 KEYS
// 2 KEMPSTON
// 3 SINCLAIR

void select_joyfunc () {
	unsigned int key_1, key_2, key_3;
	unsigned char terminado = 0;

	key_1 = sp_LookupKey('1');
	key_2 = sp_LookupKey('2');
	key_3 = sp_LookupKey('3');
	
	// Codigo para joystick virtual Android compatible con Spectranet
	// Instead the code below, loaded the same music with the game Trabajo Basura's approach
	// by saving the music from beepola in asm format and including the music.h header
	// Play music! (Generated with beepola).
	//#asm
	//	call 59000
	//	di
	//#endasm
	
	#asm
		; Music generated by beepola
		call musicstart
	#endasm
	
	while (!terminado) {
		if (sp_KeyPressed (key_1)) {
			terminado = 1;
			joyfunc = sp_JoyKeyboard;
		} else if (sp_KeyPressed (key_2)) {
			terminado = 1;
			joyfunc = sp_JoyKempston;
		} else if (sp_KeyPressed (key_3)) {
			terminado = 1;
			joyfunc = sp_JoySinclair1;
		}			
	}
}

void mueve_bicharracos () {
	// Vamos a mover un frame todos los bicharracos activos.
	
	unsigned char i, enoffsmasi, x, y, xx, yy;
	player.gotten = 0;
	
	for (i = 0; i < 3; i ++) {
		enoffsmasi = enoffs + i;
		if (malotes [enoffsmasi].t != 0) {
			malotes [enoffsmasi].x += malotes [enoffsmasi].mx;
			malotes [enoffsmasi].y += malotes [enoffsmasi].my;
						
			en_an [i].count ++; 
			if (en_an [i].count == 4) {
				en_an [i].count = 0;
				en_an [i].frame = !en_an [i].frame;
				
				switch (malotes [enoffsmasi].t) {
					case 1:
						en_an [i].next_frame = en_an [i].frame ? sprite_9_a : sprite_10_a;
						break;
					case 2:
						en_an [i].next_frame = en_an [i].frame ? sprite_11_a : sprite_12_a;
						break;
					case 3:
						en_an [i].next_frame = en_an [i].frame ? sprite_13_a : sprite_14_a;
						break;
					case 4:
						en_an [i].next_frame = en_an [i].frame ? sprite_15_a : sprite_16_a;
				}	
			}
			
			// Arrastrar plataforma:
			x = player.x >> 6;
			y = player.y >> 6;
			if (malotes [enoffsmasi].t == 4) {
				xx = player.x >> 10;
				// Vertical
				if (malotes [enoffsmasi].my < 0) {
					// Subir.
					if (x >= malotes [enoffsmasi].x - 15 && x <= malotes [enoffsmasi].x + 15 && y >= malotes [enoffsmasi].y - 16 && y <= malotes [enoffsmasi].y - 11 && player.vy >= -(PLAYER_INCR_SALTO)) {
						player.gotten = 1;
						player.y = (malotes [enoffsmasi].y - 16) << 6;
						player.vy = 0;						
						yy = player.y >> 10;
						// No nos estaremos metiendo en un tile ¿no?
						if (player.y > 1024)
							if (attr (xx, yy) > 1 || ((x & 15) != 0 && attr (xx + 1, yy) > 1)) {
								// ajustamos:
								player.y = (yy + 1) << 10;
							}
					}
				} else if (malotes [enoffsmasi].my > 0) {
					// bajar
					if (x >= malotes [enoffsmasi].x - 15 && x <= malotes [enoffsmasi].x + 15 && y >= malotes [enoffsmasi].y - 20 && y <= malotes [enoffsmasi].y - 14 && player.vy >= 0) {
						player.gotten = 1;
						player.y = (malotes [enoffsmasi].y - 16) << 6;
						player.vy = 0;
						yy = player.y >> 10;
						// No nos estaremos metiendo en un tile ¿no?
						if (player.y < 9216)
							if (attr (xx, yy + 1) > 1 || ((x & 15) != 0 && attr (xx + 1, yy + 1) > 1)) {
								// ajustamos:
								player.y = yy << 10;
							}
					}
				}
				y = player.y >> 6;
				yy = player.y >> 10;
				// Horizontal
				if (malotes [enoffsmasi].mx != 0 && x >= malotes [enoffsmasi].x - 15 && x <= malotes [enoffsmasi].x + 15 && y >= malotes [enoffsmasi].y - 16 && y <= malotes [enoffsmasi].y - 11 && player.vy >= 0) {
					player.gotten = 1;
					player.y = (malotes [enoffsmasi].y - 16) << 6;
					yy = player.y >> 10;
					x = x + malotes [enoffsmasi].mx;
					player.x = x << 6;
					xx = player.x >> 10;
					if (malotes [enoffsmasi].mx < 0) {
						if (attr (xx, yy) > 1 || ((y & 15) != 0 && attr (xx, yy + 1) > 1)) {
							// paramos y ajustamos:
							player.vx = 0;
							player.x = (xx + 1) << 10;
						}
					} else if (malotes [enoffsmasi].mx > 0) {
						if (attr (xx + 1, yy) > 1 || ((y & 15) != 0 && attr (xx + 1, yy + 1) > 1)) {
							// paramos y ajustamos:
							player.vx = 0;
							player.x = xx << 10;
						}
					}					
				}
			// Colisión matadora
			} else if (malotes [enoffsmasi].x >= x - 15 && malotes [enoffsmasi].x <= x + 15 && malotes [enoffsmasi].y >= y - 15 && malotes [enoffsmasi].y <= y + 15) {
				if (player.life > 0) {
					peta_el_beeper (4);
					player.life --;	
					draw_life ();
					// Repulsión: Empuja en la dirección mx, my del movimiento del malote
					// incrementando vy con PLAYER_MAX_VX con el signo correcto.
					if (malotes [enoffsmasi].mx > 0) player.vx = (PLAYER_MAX_VX + PLAYER_MAX_VX);
					if (malotes [enoffsmasi].mx < 0) player.vx = -(PLAYER_MAX_VX + PLAYER_MAX_VX);
					if (malotes [enoffsmasi].my > 0) player.vy = (PLAYER_MAX_VX + PLAYER_MAX_VX);
					if (malotes [enoffsmasi].my < 0) player.vy = -(PLAYER_MAX_VX + PLAYER_MAX_VX);
				}
			}
			
			// Límites de trayectoria.
			
			if (malotes [enoffsmasi].x == malotes [enoffsmasi].x1 || malotes [enoffsmasi].x == malotes [enoffsmasi].x2)
				malotes [enoffsmasi].mx = -malotes [enoffsmasi].mx;
			if (malotes [enoffsmasi].y == malotes [enoffsmasi].y1 || malotes [enoffsmasi].y == malotes [enoffsmasi].y2)
				malotes [enoffsmasi].my = -malotes [enoffsmasi].my;
		}
	}
}
