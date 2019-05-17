// mainloop.h
// Churrera copyleft 2011 by The Mojon Twins.

void saca_a_todo_el_mundo_de_aqui (void) {
	//sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
	for (gpit = 0; gpit < 3; gpit ++) {
		if (malotes [enoffs + gpit].t != 0)
			sp_MoveSprAbs (sp_moviles [gpit], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
	}
}

int itj;
unsigned char objs_old, keys_old, life_old, killed_old;
#ifdef COMPRESSED_LEVELS
unsigned char *level_str = "LEVEL 0X";
#endif

void do_game (void) {
	unsigned char *allpurposepuntero;
	unsigned char playing;
#ifdef COMPRESSED_LEVELS
	unsigned char mlplaying, level;
#endif	
#ifdef SCRIPTING_KEY_M
	int key_m;
#endif
#ifdef RANDOM_RESPAWN
	int x, y;
#else
	unsigned char x, y;
#endif
	unsigned char success;

#ifndef ANDROID_TCP_IP
	int cambiar=0;
#else
	int x2;
#endif

	int entrar_bucle = 1;
	int pantalla_nueva = 0;
	int i,j,part,found;
	unsigned char npantfix;
	
	#asm
		di
	#endasm
	
	cortina ();
	
	// splib2 initialization
	sp_Initialize (7, 0);
	sp_Border (BLACK);
	sp_AddMemory(0, 56, 14, AD_FREE);
	
	// Define keys and default controls
	keys.up    = sp_LookupKey('q');
	keys.down  = sp_LookupKey('a');
	keys.left  = sp_LookupKey('o');
	keys.right = sp_LookupKey('p');
	keys.fire  = sp_LookupKey(' ');
#ifdef SCRIPTING_KEY_M
	key_m = sp_LookupKey ('m');
#endif
	joyfunc = sp_JoyKeyboard;

	// Load tileset
	allpurposepuntero = tileset;
	for (itj = 0; itj < 256; itj++) {
		sp_TileArray (itj, allpurposepuntero);
		allpurposepuntero += 8;
	}

	// Clipping rectangle
	spritesClipValues.row_coord = VIEWPORT_Y;
	spritesClipValues.col_coord = VIEWPORT_X;
	spritesClipValues.height = 20;
	spritesClipValues.width = 30;
	spritesClip = &spritesClipValues;
	
	// Sprite creation
#ifdef NO_MASKS
	sp_player = sp_CreateSpr (sp_OR_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	player.current_frame = player.next_frame = sprite_2_a;
	
	for (gpit = 0; gpit < 3; gpit ++) {
		sp_moviles [gpit] = sp_CreateSpr(sp_OR_SPRITE, 3, sprite_9_a, 1, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_b, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_c, TRANSPARENT);	
		en_an [gpit].current_frame = sprite_9_a;
	}
#else
	sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	player.current_frame = player.next_frame = sprite_2_a;
	
	for (gpit = 0; gpit < 3; gpit ++) {
		sp_moviles [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a, 2, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_b, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_c, TRANSPARENT);	
		en_an [gpit].current_frame = en_an [gpit].next_frame = sprite_9_a;
	}
#endif

#ifdef PLAYER_CAN_FIRE
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
		sp_bullets [gpit] = sp_CreateSpr (sp_OR_SPRITE, 2, sprite_19_a, 1, TRANSPARENT);
		sp_AddColSpr (sp_bullets [gpit], sprite_19_b, TRANSPARENT);
	}
#endif

	while (1) {
		// Here the title screen
		sp_UpdateNow();
		blackout ();
		unpack ((unsigned int) (s_title), 16384);
		
		concert_song=(concert_song+1)%2;
		
		if (concert_song==0){
			print_str (11, 21, 122, "CONCERT:");
			print_str (11, 22, 122, "  VOLGA ");
		}else{
			print_str (11, 21, 122, "CONCERT:");
			print_str (11, 22, 122, "  SPAIN ");
		}
		
		sp_UpdateNow();
	
		select_joyfunc ();
		
#ifdef COMPRESSED_LEVELS
		mlplaying = 1;
		level = 0;
#ifndef REFILL_ME
		player.life = PLAYER_LIFE;
#endif
		while (mlplaying) {
			prepare_level (level);
			blackout_area ();
			level_str [7] = 49 + level;
			print_str (12, 12, 71, level_str);
			sp_UpdateNow ();
			peta_el_beeper (7);
			espera_activa (100);
#endif
				
#ifndef DIRECT_TO_PLAY

		// Clear screen and show game frame
		cortina ();
		sp_UpdateNow();
		unpack ((unsigned int) (s_marco));		
#endif

		// Let's do it.

		playing = 1;
		init_player ();

				
#ifndef COMPRESSED_LEVELS		
		init_hotspots ();
#endif
		
#ifndef COMPRESSED_LEVELS		
#ifndef DEACTIVATE_KEYS
		init_cerrojos ();
#endif
#endif		
		
#if defined(PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
		init_malotes ();
#endif
#ifdef PLAYER_CAN_FIRE
		init_bullets ();
#endif	
		
#ifndef COMPRESSED_LEVELS	
		n_pant = SCR_INICIO;
#endif		
		maincounter = 0;
		
		tile_color = (tile_color+1)%2;
		if (tile_color==0){
			tileset[911]=34;
			tileset[1158]=85;
			tileset[2126]=3;
			tileset[2127]=3;
			tileset[2136]=67;
			tileset[2137]=67;
			tileset[2138]=3;
			tileset[2139]=3;
			tileset[2140]=70;
			tileset[2141]=70;
			tileset[2142]=70;
			tileset[2143]=70;
			tileset[2144]=70;
			tileset[2145]=70;
			tileset[2146]=70;
			tileset[2147]=70;
			tileset[2148]=70;
			tileset[2149]=70;
			tileset[2150]=70;
			tileset[2151]=70;
			tileset[2152]=70;
			tileset[2153]=70;
			tileset[2154]=70;
			tileset[2155]=70;
			tileset[2166]=3;
			tileset[2167]=3;
			tileset[2170]=3;
			tileset[2171]=3;
			tileset[2174]=3;
			tileset[2175]=3;
			tileset[2186]=3;
			tileset[2187]=3;
			tileset[2193]=68;
			tileset[2194]=68;
			tileset[2195]=4;
			tileset[2196]=68;
			tileset[2197]=68;
			tileset[2198]=4;
			tileset[2199]=4;
			tileset[2202]=3;
			tileset[2203]=3;
		}else{
			tileset[911]=98;
			tileset[1158]=93;
			tileset[2126]=4;
			tileset[2127]=4;
			tileset[2136]=4;
			tileset[2137]=4;
			tileset[2138]=4;
			tileset[2139]=4;
			tileset[2140]=67;
			tileset[2141]=67;
			tileset[2142]=67;
			tileset[2143]=67;
			tileset[2144]=67;
			tileset[2145]=67;
			tileset[2146]=67;
			tileset[2147]=67;
			tileset[2148]=67;
			tileset[2149]=67;
			tileset[2150]=67;
			tileset[2151]=67;
			tileset[2152]=67;
			tileset[2153]=67;
			tileset[2154]=67;
			tileset[2155]=67;
			tileset[2166]=4;
			tileset[2167]=4;
			tileset[2170]=4;
			tileset[2171]=4;
			tileset[2174]=4;
			tileset[2175]=4;
			tileset[2186]=4;
			tileset[2187]=4;
			tileset[2193]=70;
			tileset[2194]=70;
			tileset[2195]=6;
			tileset[2196]=6;
			tileset[2197]=6;
			tileset[2198]=6;
			tileset[2199]=6;
			tileset[2202]=4;
			tileset[2203]=4;
		}
		
#ifdef ACTIVATE_SCRIPTING		
		script_result = 0;
		msc_init_all ();
#endif
		
		draw_scr ();
		
#ifdef PLAYER_KILLS_ENEMIES		
#ifdef SHOW_TOTAL
		// Show total of enemies next to the killed amount.

		sp_PrintAtInv (KILLED_Y, 2 + KILLED_X, 71, 15);
		sp_PrintAtInv (KILLED_Y, 3 + KILLED_X, 71, 16 + BADDIES_COUNT / 10);
		sp_PrintAtInv (KILLED_Y, 4 + KILLED_X, 71, 16 + BADDIES_COUNT % 10);
#endif
#endif
		
		half_life = 0;
			
		// Entering game
#ifdef ACTIVATE_SCRIPTING
		script = e_scripts [MAP_W * MAP_H];
		run_script ();
#endif

		objs_old = keys_old = life_old = killed_old = 0xff;
		success = 0;

		entrar_bucle = 1;
		pantalla_nueva = 1;
		current_taken=-1;
		happiness=-1;
		
		for (i=0; i<8;i++){
			score_set_in_pos_i_was_in_room_r[i]=-1;
		}
		// ESTO ASEGURA NO REPETIR ROOM PERO NO ASEGURA NO REPETIR SCORE!!
		for (i=0; i<8;i++){
			part = rand() % 8;
			found=1;
			while (found==1){
				found=0;
				for (j=0; j<i;j++){
					if (in_room_is_score_n[j]==part){
						part = rand() % 8;
						found=1;
						break;
					}
				}	
			}
			if (found==0){
				// random score order
				in_room_is_score_n[i]=part;
				score_n_is_in_room[part]=i;
			}
		}
		
		while (playing) {

#ifndef DEACTIVATE_OBJECTS
			if (player.objs != objs_old) {
				draw_objs ();
				objs_old = player.objs;
			}
#endif
			
			if (player.life != life_old) {
				print_number2 (LIFE_X, LIFE_Y, player.life);
				life_old = player.life;
			}
			
#ifndef DEACTIVATE_KEYS
			if (player.keys != keys_old) {
				print_number2 (KEYS_X, KEYS_Y, player.keys);
				keys_old = player.keys;
			}
#endif

#if defined(PLAYER_KILLS_ENEMIES) || defined(PLAYER_CAN_FIRE)
#ifdef PLAYER_SHOW_KILLS
			if (player.killed != killed_old) {
				print_number2 (KILLED_X, KILLED_Y, player.killed);
				killed_old = player.killed;	
			}
#endif
#endif
			maincounter ++;
			half_life = !half_life;
			
#ifndef ANDROID_TCP_IP
			// Backgroud birdies dynamic draw
			cambiar=cambiar%8;
			if (cambiar==0){
				switch (n_pant) {
					case 0:
						main_loop_background_dynamics(5,8,9,0,0);
						break;
					case 1:
						main_loop_background_dynamics(11,14,9,0,0);
						break;
					case 2:
						main_loop_background_dynamics(9,12,9,0,0);
						break;
					case 3:
						main_loop_background_dynamics(10,13,9,0,0);
						break;
					case 4:
						main_loop_background_dynamics(1,5,1,1,entrar_bucle);
						main_loop_background_dynamics(9,14,1,1,entrar_bucle);
						main_loop_background_dynamics(1,6,7,1,entrar_bucle);
						main_loop_background_dynamics(9,14,7,1,entrar_bucle);
						main_loop_background_dynamics(1,6,8,1,entrar_bucle);
						main_loop_background_dynamics(9,14,8,1,entrar_bucle);
						break;
					case 5:
						main_loop_background_dynamics(2,5,9,0,0);
						break;
					case 6:
						main_loop_background_dynamics(5,8,9,0,0);
						break;
					case 7:
						main_loop_background_dynamics(7,10,9,0,0);
						break;
					case 8:
						main_loop_background_dynamics(2,5,9,0,0);
						break;
					break;	
				}
			}
			cambiar=cambiar+1;
#endif

/*
#ifdef ANDROID_TCP_IP
			if (happiness == 1){
				switch (n_pant){
					case 0:
						x2=6;
						break;
					case 1:
						x2=12;
						break;
					case 2:
						x2=10;
						break;
					case 3:
						x2=11;
						break;
					case 5:
						x2=3;
						break;
					case 6:
						x2=6;
						break;
					case 7:
						x2=8;
						break;
					case 8:
						x2=3;
						break;
				}	
				map_buff [x2 + (y << 4) - y] = 15;
				draw_coloured_tile (VIEWPORT_X + x2 + x2, VIEWPORT_Y + 9 + 9, 18);
			}
#endif
*/
			
			// hall names
			if (pantalla_nueva==1){
				pantalla_nueva = 0;
				switch (n_pant) {
					case 0:
						print_str (11, 21, 122, "BIRDHAND");
						break;
					case 1:
						print_str (11, 21, 122, "FEATHER ");
						break;
					case 2:
						print_str (11, 21, 122, "BIRDTRAP");
						break;
					case 3:
						print_str (11, 21, 122, "ONE WING");
						break;
					case 4:
						print_str (11, 21, 122, "THE MAIN");
						break;
					case 5:
						print_str (11, 21, 122, "PEACOCK ");
						break;
					case 6:
						print_str (11, 21, 122, "SWALLOW ");
						break;
					case 7:
						print_str (11, 21, 122, "EAGLEFLY");
						break;
					case 8:
						print_str (11, 21, 122, "BIRDCAGE");
						break;
					break;	
				}
				print_str (11, 22, 122, "- HALL -");
			}
			
			// Move player
			move ();
			
			// Move enemies
			mueve_bicharracos ();
			
#ifdef PLAYER_CAN_FIRE
			// Move bullets				
			mueve_bullets ();
#endif

			// Render		
			for (gpit = 0; gpit < 3; gpit ++) {
#ifdef RANDOM_RESPAWN
				if (en_an [gpit].fanty_activo) {
					x = en_an [gpit].x >> 6;
					y = en_an [gpit].y >> 6;
				} else {
#endif
					x = malotes [enoffs + gpit].x;
					y = malotes [enoffs + gpit].y;
#ifdef RANDOM_RESPAWN
				}
#endif
				sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an [gpit].next_frame - en_an [gpit].current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3),x & 7, y & 7);
				en_an [gpit].current_frame = en_an [gpit].next_frame;
			}

			// Precalc this, comes handy:
			x = player.x >> 6;
			y = player.y >> 6;
			
			if ( !(player.estado & EST_PARP) || !(half_life) )
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);
			else
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, -2, -2, 0, 0);
			
			player.current_frame = player.next_frame;
			
			
#ifdef PLAYER_CAN_FIRE
			for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
				if (bullets [gpit].estado == 1) {
					sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, VIEWPORT_Y + (bullets [gpit].y >> 3), VIEWPORT_X + (bullets [gpit].x >> 3), bullets [gpit].x & 7, bullets [gpit].y & 7);
				} else {
					sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, -2, -2, 0, 0);
				}
			}
#endif			
			
			if (entrar_bucle==1){
				// small fix
				map_buff [6 + (0 << 4) - 0] = 1;	
				map_attr [6 + (0 << 4) - 0] = comportamiento_tiles [14];
				draw_coloured_tile (VIEWPORT_X + 6 + 6, VIEWPORT_Y + 0 + 0, 1);
			}
			
			// Update to screen
			sp_UpdateNow();
			
#ifdef PLAYER_CAN_FIRE
			for (gpit = 0; gpit < 3; gpit ++)
				if (en_an [gpit].morido == 1) {
					peta_el_beeper (1);
					en_an [gpit].morido = 0;
				} 	
#endif

#ifdef PLAYER_FLICKERS
			// Flickering
			if (player.estado == EST_PARP) {
				player.ct_estado --;
				if (player.ct_estado == 0)
					player.estado = EST_NORMAL;	
			}
#endif			
			
			// Hotspot interaction.
			if (x >= hotspot_x - 15 && x <= hotspot_x + 15 && y >= hotspot_y - 15 && y <= hotspot_y + 15) {
				// Deactivate hotspot
				draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), orig_tile);
				// Was it an object, key or life boost?
				if (hotspots [n_pant].act == 0) {
					player.life += PLAYER_REFILL;
					if (player.life > PLAYER_LIFE)
						player.life = PLAYER_LIFE;
					hotspots [n_pant].act = 2;
					peta_el_beeper (8);
#ifndef DEACTIVATE_OBJECTS
				} else if (hotspots [n_pant].tipo == 1) {
#ifdef ONLY_ONE_OBJECT
					if (player.objs == 0) {
						player.objs ++;
						current_taken=current_taken+1;
						npantfix=n_pant;
						if (npantfix>3){
							npantfix=npantfix-1;
						}
						score_set_in_pos_i_was_in_room_r[current_taken]=npantfix;
						hotspots [n_pant].act = 0;
						peta_el_beeper (9);	
					} else {
						peta_el_beeper (4);	
						draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), 17);
					}
#else
					player.objs ++;
					hotspots [n_pant].act = 0;
					peta_el_beeper (9);
#endif
#endif
#ifndef DEACTIVATE_KEYS
				} else if (hotspots [n_pant].tipo == 2) {
					player.keys ++;
					hotspots [n_pant].act = 0;
					peta_el_beeper (7);
#endif
				} 
				// PLOP!!
				hotspot_x = hotspot_y = 240;
			}
			
			// Flick screen checks and scripting related stuff
			gpit = (joyfunc) (&keys);
			
#ifdef ACTIVATE_SCRIPTING		
#ifdef SCRIPTING_KEY_M			
			if (sp_KeyPressed (key_m)) {
#endif
#ifdef SCRIPTING_DOWN
#ifdef ANDROID_TCP_IP
			// Codigo para joystick virtual Android compatible con Spectranet (simulate_key_d==1)
			if ((gpit & sp_DOWN) == 0 || simulate_key_d==1) {
#else
			if ((gpit & sp_DOWN) == 0) {
#endif				
#endif
				// Any scripts to run in this screen?
				script = f_scripts [n_pant];
				run_script ();
			}
#endif

#ifdef PLAYER_AUTO_CHANGE_SCREEN
			if (player.x == 0 && player.vx < 0) {
				pantalla_nueva = 1;
				happiness=-1;
				n_pant --;
				draw_scr ();
				player.x = 14336;
			}
			if (player.x == 14336 && player.vx > 0) {
				pantalla_nueva = 1;
				happiness=-1;
				n_pant ++;
				draw_scr ();
				player.x = 0;
			}
#else
			if (player.x == 0 && ((gpit & sp_LEFT) == 0)) {
				pantalla_nueva = 1;
				happiness=-1;
				n_pant --;
				draw_scr ();	
				player.x = 14336;
			}
			if (player.x == 14336 && ((gpit & sp_RIGHT) == 0)) {		// 14336 = 224 * 64
				pantalla_nueva = 1;
				happiness=-1;
				n_pant ++;
				draw_scr ();
				player.x = 0;
			}
#endif
			if (player.y == 0 && player.vy < 0 && n_pant >= MAP_W) {
				pantalla_nueva = 1;
				happiness=-1;
				n_pant -= MAP_W;
				draw_scr ();
				player.y = 9216;	
			}
			if (player.y == 9216 && player.vy > 0) {				// 9216 = 144 * 64
				if (n_pant < MAP_W * MAP_H - MAP_W) {
					pantalla_nueva = 1;
					happiness=-1;
					n_pant += MAP_W;
					draw_scr ();
					player.y = 0;
					if (player.vy > 256) player.vy = 256;
#ifdef MAP_BOTTOM_KILLS
				} else {
					player.vy = -PLAYER_MAX_VY_CAYENDO;	
					if (player.life > 0) {
						peta_el_beeper (4);
						player.life --;	
					}
#endif
				}
			}
			
			if (entrar_bucle==1){
				
				map_buff [6 + (0 << 4) - 0] = 1;	
				map_attr [6 + (0 << 4) - 0] = comportamiento_tiles [14];
				draw_coloured_tile (VIEWPORT_X + 6 + 6, VIEWPORT_Y + 0 + 0, 1);
			
				#asm
; Music generated by beepola
					call musicstart2
				#endasm
				entrar_bucle=0;
				#asm
					di
				#endasm
			}
			
			// Win game condition
#ifdef ACTIVATE_SCRIPTING
			if (player.objs == PLAYER_NUM_OBJETOS || script_result == 1) {
#else			
			if ((player.objs == PLAYER_NUM_OBJETOS)&&(player.killed == BADDIES_COUNT)) {
#endif
				if (n_pant == pant_final){
					draw_coloured_tile (VIEWPORT_X + (0), VIEWPORT_Y + (16), 5);
				}
				
				if (
					(n_pant == pant_final && ((player.x >> 10) == PLAYER_FIN_X && (player.y >> 10) == PLAYER_FIN_Y)) ||
					pant_final == 99
				) {
					success = 1;
					playing = 0;					
				}
			}
			
			// Game over condition
#ifdef ACTIVATE_SCRIPTING
			if (player.life == 0 || script_result == 2) {
#else
			if (player.life == 0) {
#endif
				playing = 0;				
			}
			
		}
		
		saca_a_todo_el_mundo_de_aqui ();
		sp_UpdateNow ();
		
#ifdef COMPRESSED_LEVELS
		if (success) {
			level ++;
			if (level == MAX_LEVELS) {
				game_ending ();
				mlplaying = 0;
			}
		} else {
			game_over ();
			mlplaying = 0;
		}
	}
	cortina ();
#else
		if (success) {
			//sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);
			game_ending ();
		} else {
			game_over ();
		}
		cortina ();
#endif
	}
			
}
