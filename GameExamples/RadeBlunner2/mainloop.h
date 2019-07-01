// mainloop.h
// Churrera copyleft 2011 by The Mojon Twins.

void saca_a_todo_el_mundo_de_aqui (void) {
	sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);				
	for (gpit = 0; gpit < 3; gpit ++) {
		if (malotes [enoffs + gpit].t != 0){
			sp_MoveSprAbs (sp_moviles [gpit], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
		}
	}
}

int itj;
unsigned char objs_old, keys_old, life_old, killed_old;

void do_game (void) {
	unsigned char *allpurposepuntero;
	unsigned char playing;
#ifdef SCRIPTING_KEY_M
	int key_m;
#endif
	unsigned char x, y;
	unsigned char success;

	int pantalla_nueva, i, starting_speech;
	int swapped = 0;
	
	#asm
		di
	#endasm
	
	//cortina ();
	
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
	
	// Sprites creation Begin
	sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_6_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_6_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_6_c, TRANSPARENT);
	player.current_frame = player.next_frame = sprite_6_a;
	for (gpit = 0; gpit < 3; gpit ++) {
		sp_moviles [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a, 2, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_b, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_c, TRANSPARENT);	
		en_an [gpit].current_frame = en_an [gpit].next_frame = sprite_9_a;
	}
	// Sprites creation End
		
	while (1) {
		
		// Here the title screen
		sp_UpdateNow();
		blackout ();
		unpack ((unsigned int) (s_title), 16384);
		select_joyfunc ();
				
		// Let's do it.
		playing = 1;
		init_player ();
		init_hotspots ();		
		init_cerrojos ();
		init_malotes ();
		n_pant = SCR_INICIO;
		script_result = 0;
		msc_init_all ();		
		
		// force look left for initial speech
		move (1);
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
		
		// If last game finished in a boss screen I need to change de sprite set to the default one
		if (swapped==1){
			swapped=0;
			swap_sprites_enemies();
		}
		
		pantalla_nueva = 1;
		starting_speech = -1;
		pant11killed = pant15killed = pant35killed = 0;
		
		ojo_izA_pos=ojo_izA_pos_switch=ojo_dcA_pos=ojo_dcA_pos_switch=-1;
		ojo_izB_pos=ojo_izB_pos_switch=ojo_dcB_pos=ojo_dcB_pos_switch=-1;
							
		while (playing) {

			seed[0]=(seed[0]+1)%1000;
			
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
			half_life = !half_life;
			
			if (pantalla_nueva==1){
				
				if (n_pant==15 || n_pant==35 || n_pant==11){
					swap_sprites_enemies();
					swapped = 1;
				}else if (swapped==1){
					swapped=0;
					swap_sprites_enemies();
				}
				
				pantalla_nueva = 0;
				
#ifndef ANDROID_TCP_IP	
				// Full featured version (except Android TCP/IP Virtual Joystick)
				switch (n_pant) {
					case 0:
						print_panel_msg(" TO THE   "," VAULTS!  ");
						draw_coloured_tile (VIEWPORT_X + 6, VIEWPORT_Y + 16, 29);
						map_attr [122] = 8;
						break;
					case 1:
						if (ojo_izA_pos==-1){
							set_rand_values(&ojo_izA_pos,&ojo_izA_pos_switch);
							set_rand_values(&ojo_dcA_pos,&ojo_dcA_pos_switch);
							set_rand_values(&ojo_izB_pos,&ojo_izB_pos_switch);
							set_rand_values(&ojo_dcB_pos,&ojo_dcB_pos_switch);	
						}						
						break;
					case 2:
					case 18:
						print_panel_msg("  FOLLOW  ","THE MARKS!");
						break;
					case 3:
					case 7:
					case 32:
					case 33:
						print_panel_msg(" AN EYED  "," SWITCH!! ");
						break;
					case 5:
						starting_speech=5;			
						peta_el_beeper (6); //"no,no..."
						print_panel_msg("THE FINAL ","SHOWDOWN!!");
						put_tile(1,4,25);
						put_tile(2,4,26);
						put_tile(3,4,25);
						put_tile(1,5,31);
						put_tile(2,5,31);
						put_tile(3,5,30);
						put_tile(1,6,28);
						put_tile(2,6,27);
						put_tile(3,6,31);
						put_tile(4,6,31);
						break;
					case 11:
						if (pant11killed==3){
							print_panel_msg(pant_msg,"INCEPT DAY");
							draw_coloured_tile (VIEWPORT_X + 22, VIEWPORT_Y + 2, 3);
							map_attr [26] = 0;
						}
						else{
							peta_el_beeper (6); //"no,no..."
							print_panel_msg("  NOSY    ","  PLACE!!");
						}
						break;
					case 14:
						if (ojo_izA_pos==ojo_izA_pos_switch && 
							ojo_dcA_pos==ojo_dcA_pos_switch
							){
							print_panel_msg(pant_msg+22,pant_msg+33);
							draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y + 16, 0);
							map_attr [134] = 0;
						}else{ 
							peta_el_beeper (10); //"areee..." 
							print_panel_msg(pant_msg+44,pant_msg+55);
							draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y + 16, 29);
							map_attr [134] = 8;
						}
						break;
					case 15:
						if (pant15killed==3){
							print_panel_msg(pant_msg,"MORPHOLOGY");
							draw_coloured_tile (VIEWPORT_X + 26, VIEWPORT_Y + 18, 0);
							map_attr [148] = 0;
						}
						else{
							peta_el_beeper (6); //"no,no..."
							print_panel_msg(pant_msg+11," ATTACK!! ");
						}
						break;
					case 17:
						print_panel_msg("SUSPICIOUS","  WALL,,,");
						draw_coloured_tile (VIEWPORT_X + 0, VIEWPORT_Y + 12, 33);
						map_attr [90] = 0;
						break;
					case 34:
						if (ojo_izB_pos==ojo_izB_pos_switch && 
							ojo_dcB_pos==ojo_dcB_pos_switch
							){
							print_panel_msg(pant_msg+22,pant_msg+33);
							draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y + 16, 0);
							map_attr [134] = 0;
						}else{
							peta_el_beeper (10); //"areee..." 
							//" A BLOCKED"
							//"   DOOR!! "
							print_panel_msg(pant_msg+44,pant_msg+55);
							draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y + 16, 29);
							map_attr [134] = 8;
						}
						break;
					case 35:
						if (pant35killed==3){
							print_panel_msg(pant_msg,"LONGEVITY ");
							draw_coloured_tile (VIEWPORT_X + 26, VIEWPORT_Y + 0, 0);
							map_attr [13] = 0;
						}
						else{
							peta_el_beeper (6); //"no,no..."
							//" CLIVE'S  "
							print_panel_msg(pant_msg+11," REVENGE!! ");
						}
						break;
					default:
						print_panel_msg("  CAREFUL ","   HERE!  ");
						break;
				}
				draw_map();	
#else
				// Android TCP/IP Virtual Joystick version
				switch (n_pant) {
					case 1:
						if (ojo_izA_pos==-1){
							set_rand_values(&ojo_izA_pos,&ojo_izA_pos_switch);
							set_rand_values(&ojo_dcA_pos,&ojo_dcA_pos_switch);
							set_rand_values(&ojo_izB_pos,&ojo_izB_pos_switch);
							set_rand_values(&ojo_dcB_pos,&ojo_dcB_pos_switch);	
						}						
						break;
					case 5:
						starting_speech=5;			
						
						peta_el_beeper (6); //"no,no..."
						put_tile(1,5,25);
						put_tile(2,5,26);
						put_tile(3,5,25);
						put_tile(1,6,28);
						put_tile(2,6,27);
						put_tile(3,6,31);
						
						break;
					case 11:
						if (pant11killed==3){
							draw_coloured_tile (VIEWPORT_X + 22, VIEWPORT_Y + 2, 3);
							map_attr [26] = 0;
						}
						break;
					case 14:
						if (ojo_izA_pos==ojo_izA_pos_switch && 
							ojo_dcA_pos==ojo_dcA_pos_switch
							){
							draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y + 16, 0);
							map_attr [134] = 0;
						}else{ 
							draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y + 16, 29);
							map_attr [134] = 8;
						}
						break;
					case 15:
						if (pant15killed==3){
							draw_coloured_tile (VIEWPORT_X + 26, VIEWPORT_Y + 18, 0);
							map_attr [148] = 0;
						}
						break;
					case 17:
						draw_coloured_tile (VIEWPORT_X + 0, VIEWPORT_Y + 12, 33);
						map_attr [90] = 0;
						break;
					case 34:
						if (ojo_izB_pos==ojo_izB_pos_switch && 
							ojo_dcB_pos==ojo_dcB_pos_switch
							){
							draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y + 16, 0);
							map_attr [134] = 0;
						}else{
							draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y + 16, 29);
							map_attr [134] = 8;
						}
						break;
					case 35:
						if (pant35killed==3){
							draw_coloured_tile (VIEWPORT_X + 26, VIEWPORT_Y + 0, 0);
							map_attr [13] = 0;
						}
						break;
				}
				
#endif

			}

	
			if (starting_speech<5){
#ifndef ANDROID_TCP_IP
				switch (starting_speech){
					case -1: 
						put_tile(1,8,27);
						print_panel_msg("LONGEVITY.","MORPHO,,, ");
						break;
					case 0: 
						peta_el_beeper(0);
						espera_activa (50);
						print_panel_msg("YES.I WILL"," BRING IT!");
						break;
					case 1: 
						peta_el_beeper(6);
						espera_activa (50);
						put_tile(1,8,32);
						print_panel_msg("WE ARE ON "," STRIKE!!!");
						break;
					case 2: 
						peta_el_beeper(0);
						espera_activa (50);
						print_panel_msg("YOU CANNOT"," GO HOME!!");
						break;
					case 3: 
						peta_el_beeper(0);
						espera_activa (50);
						put_tile(1,8,31);
						pantalla_nueva = 1;
						print_panel_msg("SURE. WAIT","AND SEE,,,");
						break;
					case 4: 
						peta_el_beeper(10);
						espera_activa (50);
						break;
				}
#endif
				starting_speech = starting_speech+1;
				
			}else if (n_pant == pant_final && ((player.x >> 10) == 3 && (player.y >> 10) == 6) && starting_speech<9){
#ifndef ANDROID_TCP_IP

					// Show hero always
					half_life = 0;
					player.estado = EST_NORMAL;	
							
					switch (starting_speech){
						case 5: 
							print_panel_msg("THANK YOU ","FOR THE   ");
							break;
						case 6: 
							peta_el_beeper(0);
							espera_activa (50);
							if ((player.objs == 28)&&(player.killed == 30)){
								print_panel_msg("DOCS.WHEH. "," GO HOME! ");
							}else{
								print_panel_msg("DOCS.WHEH. "," BUT STILL");
							}
							break;
						case 7: 
							peta_el_beeper(0);
							espera_activa (50);
							if ((player.objs == 28)&&(player.killed == 30)){
								print_panel_msg("PHEW! FREE"," AT LAST!!");
								draw_coloured_tile (VIEWPORT_X + 8, VIEWPORT_Y + 8, 0);
								map_attr [64] = 0;
							}else{
								print_panel_msg("YOU CANNOT","GO HOME,,,");
							}
							break;
						case 8: 
							peta_el_beeper(10);
							espera_activa (50);
							break;
					}
#else
					switch (starting_speech){
						case 7: 
							peta_el_beeper(0);
							if ((player.objs == 28)&&(player.killed == 30)){
								draw_coloured_tile (VIEWPORT_X + 8, VIEWPORT_Y + 8, 0);
								map_attr [64] = 0;
							}
							break;
					}
					
#endif
					starting_speech = starting_speech+1;
				
			}else{
					// Move player
					move (0);
			}
			
			// Move enemies
			mueve_bicharracos ();	
			
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
			
			if ( !(player.estado & EST_PARP) || !(half_life) ){
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);				
			}else{
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, -2, -2, 0, 0);
			}
			player.current_frame = player.next_frame;
						
			// Update to screen
			sp_UpdateNow();
			
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
					player.objs ++;
					hotspots [n_pant].act = 0;
					peta_el_beeper (9);
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
				n_pant --;
				draw_scr ();
				player.x = 14336;
			}
			if (player.x == 14336 && player.vx > 0) {
				pantalla_nueva = 1;
				n_pant ++;
				draw_scr ();
				player.x = 0;
			}
#else
			if (player.x == 0 && ((gpit & sp_LEFT) == 0)) {
				pantalla_nueva = 1;
				n_pant --;
				draw_scr ();	
				player.x = 14336;
			}
			if (player.x == 14336 && ((gpit & sp_RIGHT) == 0)) {		// 14336 = 224 * 64
				pantalla_nueva = 1;
				n_pant ++;
				draw_scr ();
				player.x = 0;
			}
#endif
			if (player.y == 0 && player.vy < 0 && n_pant >= MAP_W) {
				pantalla_nueva = 1;
				n_pant -= MAP_W;
				draw_scr ();
				player.y = 9216;	
			}
			if (player.y == 9216 && player.vy > 0) {				// 9216 = 144 * 64
				if (n_pant < MAP_W * MAP_H - MAP_W) {
					pantalla_nueva = 1;
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
			
			// Win game condition
			if ((n_pant == pant_final)&&
			    (((player.x >> 10) == PLAYER_FIN_X && (player.y >> 10) == PLAYER_FIN_Y) || pant_final == 99)) 
			{
				success = 1;
				playing = 0;					
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
	//cortina ();
#else
		if (success) game_ending (); else game_over ();
		//cortina ();
#endif
	}
			
}

int set_rand_values(int *mark_wall, int *switch_pos){
#ifndef ANDROID_TCP_IP
	*mark_wall = rand() % 4;
	*switch_pos = rand() % 4;
	while (*switch_pos == *mark_wall){
		*switch_pos = rand() % 4;
	}
#else
	// Android ver. does not use random (not enought memory!)
	*mark_wall = 3;
	*switch_pos = 0;
#endif
	
}

int swap_sprites_enemies(void){
	sp_Swap(sprite_11_a,sprite_11Bis_a,96);
	sp_Swap(sprite_12_a,sprite_12Bis_a,96);
	sp_Swap(sprite_13_a,sprite_13Bis_a,96);
	sp_Swap(sprite_14_a,sprite_14Bis_a,96);
}

