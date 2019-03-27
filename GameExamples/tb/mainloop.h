void do_game () {
	int j;
	unsigned char *allpurposepuntero;
	unsigned char i;
	unsigned char playing;
	unsigned char n_pant;
	unsigned char maincounter;
	unsigned char objs_old, keys_old, life_old, killed_old;
	int key_m;
#ifdef RANDOM_RESPAWN
	int x, y;
#else
	unsigned char x, y;
#endif
	unsigned char success;
	
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
	sp_AddMemory(0, 56, 14, AD_FREE);
	
	// Defino las teclas y el control por defecto
	
	keys.up    = sp_LookupKey('q');
	keys.down  = sp_LookupKey('a');
	keys.left  = sp_LookupKey('o');
	keys.right = sp_LookupKey('p');
	keys.fire  = sp_LookupKey(' ');

	key_m = sp_LookupKey ('m');
		
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
	
#ifdef NO_MASKS
	sp_player = sp_CreateSpr (sp_OR_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	player.current_frame = player.next_frame = sprite_2_a;
	
	for (i = 0; i < 3; i ++) {
		sp_moviles [i] = sp_CreateSpr(sp_OR_SPRITE, 3, sprite_9_a, 1, TRANSPARENT);
		sp_AddColSpr (sp_moviles [i], sprite_9_b, TRANSPARENT);
		sp_AddColSpr (sp_moviles [i], sprite_9_c, TRANSPARENT);	
		en_an [i].current_frame = sprite_9_a;
	}
#else
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
#endif

#ifdef PLAYER_CAN_FIRE
	for (i = 0; i < MAX_BULLETS; i ++) {
		sp_bullets [i] = sp_CreateSpr (sp_OR_SPRITE, 2, sprite_19_a, 1, TRANSPARENT);
		sp_AddColSpr (sp_bullets [i], sprite_19_b, TRANSPARENT);
	}
#endif

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
#ifndef DEACTIVATE_KEYS
		init_cerrojos ();
#endif
#if defined(PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
		init_malotes ();
#endif
#ifdef PLAYER_CAN_FIRE
		init_bullets ();
#endif	
			
		n_pant = SCR_INICIO;
		maincounter = 0;
		
#ifdef ACTIVATE_SCRIPTING		
		script_result = 0;
		msc_init_all ();
#endif
		
		draw_scr (n_pant);
		draw_life ();
#ifndef	DEACTIVATE_OBJECTS
		draw_objs ();
#endif
#ifndef DEACTIVATE_KEYS
		draw_keys ();
#endif

#if defined(PLAYER_KILLS_ENEMIES) || defined(PLAYER_CAN_FIRE)
		draw_killed ();
#endif
#ifdef PLAYER_KILLS_ENEMIES		
#ifdef SHOW_TOTAL
		sp_PrintAtInv (KILLED_Y, 2 + KILLED_X, 71, 15);// Poner total
		sp_PrintAtInv (KILLED_Y, 3 + KILLED_X, 71, 16 + BADDIES_COUNT / 10);
		sp_PrintAtInv (KILLED_Y, 4 + KILLED_X, 71, 16 + BADDIES_COUNT % 10);
#endif
#endif
		
		half_life = 0;
				
		//objs_old = keys_old = life_old = killed_old = 0;

		while (playing) {
			
			if (player.objs != objs_old) {
				draw_objs ();
				objs_old = player.objs;
			}
			
			if (player.life != life_old) {
				draw_life ();
				life_old = player.life;
			}
			
			if (player.keys != keys_old) {
				draw_keys ();
				keys_old = player.keys;
			}
			
			if (player.killed != killed_old) {
				draw_killed ();
				killed_old = player.killed;	
			}
			
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

#ifdef PLAYER_CAN_FIRE
			// Mover balas
				
			mueve_bullets ();
#endif

			// Render			

			for (i = 0; i < 3; i ++) {
				if (malotes [enoffs + i].t != 0) {		// Esto sólo es necesario si hay habitaciones con menos de 3.
#ifdef RANDOM_RESPAWN
					if (en_an [i].fanty_activo) {
						x = en_an [i].x >> 6;
						y = en_an [i].y >> 6;
					} else {
#endif
						x = malotes [enoffs + i].x;
						y = malotes [enoffs + i].y;
#ifdef RANDOM_RESPAWN
					}
#endif
					sp_MoveSprAbs (sp_moviles [i], spritesClip, en_an [i].next_frame - en_an [i].current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3),x & 7, y & 7);
					en_an [i].current_frame = en_an [i].next_frame;
				}
			}

			// Precalc para cálculos (eh?)
			
			x = player.x >> 6;
			y = player.y >> 6;
			
			if ( !(player.estado & EST_PARP) || !(half_life) )
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);
			else
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, -2, -2, 0, 0);
			
			player.current_frame = player.next_frame;
			
			
#ifdef PLAYER_CAN_FIRE
			for (i = 0; i < MAX_BULLETS; i ++) {
				if (bullets [i].estado == 1) {
					sp_MoveSprAbs (sp_bullets [i], spritesClip, 0, VIEWPORT_Y + (bullets [i].y >> 3), VIEWPORT_X + (bullets [i].x >> 3), bullets [i].x & 7, bullets [i].y & 7);
				} else {
					sp_MoveSprAbs (sp_bullets [i], spritesClip, 0, -2, -2, 0, 0);
				}
			}
#endif			
			
			// Update to screen
			
			sp_UpdateNow();
			
#ifdef PLAYER_CAN_FIRE
			for (i = 0; i < 3; i ++)
				if (en_an [i].morido == 1) {
					peta_el_beeper (1);
					en_an [i].morido = 0;
				} 	
#endif

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
				// Desactivamos el hotspot:
				draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), orig_tile);
				// ¿Sumamos un objeto, una llave, o vida?
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
						i = 1;
						player.objs ++;
						hotspots [n_pant].act = 0;
						peta_el_beeper (9);	
					} else {
						i = 0;
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
			
			// Comprobaciones
			
			
			i = (joyfunc) (&keys); // Leemos del teclado
			
#ifdef ACTIVATE_SCRIPTING		
#ifdef SCRIPTING_KEY_M			
			if (sp_KeyPressed (key_m)) {
#endif
#ifdef SCRIPTING_DOWN
			// Codigo para joystick virtual Android compatible con Spectranet (simulate_key_d==1)
			if ((i & sp_DOWN) == 0 || simulate_key_d==1) {
#endif

				simulate_key_d=0;
				
				// Vemos si hay algún script por ejecutar
				script = f_scripts [n_pant];
				run_script ();
			}
#endif

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
			if (player.x == 0 && ((i & sp_LEFT) == 0)) {
				n_pant --;
				draw_scr (n_pant);	
				player.x = 14336;
			}
			if (player.x == 14336 && ((i & sp_RIGHT) == 0)) {		// 14336 = 224 * 64
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
				if (n_pant < MAP_W * MAP_H - MAP_W) {
					n_pant += MAP_W;
					draw_scr (n_pant);
					player.y = 0;
				} else {
					player.vy = -PLAYER_MAX_VY_CAYENDO;	
					if (player.life > 0) {
						peta_el_beeper (4);
						player.life --;	
					}
				}
			}
			
			// llegarse al final
#ifdef ACTIVATE_SCRIPTING
			if (player.objs == PLAYER_NUM_OBJETOS || script_result == 1) {
#else			
			if (player.objs == PLAYER_NUM_OBJETOS) {
#endif
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

#ifdef ACTIVATE_SCRIPTING
			if (player.life == 0 || script_result == 2) {
#else
			if (player.life == 0) {
#endif
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
