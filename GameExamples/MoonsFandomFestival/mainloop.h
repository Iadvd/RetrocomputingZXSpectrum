// mainloop.h
// Churrera copyleft 2011 by The Mojon Twins.

void saca_a_todo_el_mundo_de_aqui (int only_me) {
	sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);				
	sp_MoveSprAbs (sp_playerB, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);				
	if (!only_me){
		if (malotes [enoffs].t != 0){
			sp_MoveSprAbs (sp_moviles [0], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
			sp_MoveSprAbs (sp_movilesB [0], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
		}	
	}
	sp_UpdateNow();
}

void do_game (void) {
	unsigned char playing;
	unsigned char x, y, yB, z, t;
	unsigned char success=0;
	
	int starting_speech,i;
	
	#asm
		di
	#endasm
	
	blackout();
	
	// splib2 initialization
	sp_Initialize (7, 0);
	sp_Border (BLACK);
	sp_AddMemory(0, 56, 14, AD_FREE);
	
	// Define keys and default controls
	keys.down  = sp_LookupKey('a');
	keys.left  = sp_LookupKey('o');
	keys.right = sp_LookupKey('p');
	keys.fire  = sp_LookupKey(' ');
	joyfunc = sp_JoyKeyboard;

	Setup_Tileset_Sprites();
	
	while (1) {
		
		// Create Main Menu BEGIN
		if (ending!=1){
			for (i=2;i<=14;i++){
				draw_coloured_tile (i*2, 22, 13); // BG			
			}
			for (i=0;i<10;i++){
				speakup(1, 15, 4, values_col_menu[i], values_row_menu[i], values_color_menu[i], texts_menu[i]);
			}
			select_joyfunc ();
		}
		// Create Main Menu END
		
		cortina ();
		blackout();
		
		// Let's do it.
		playing = 1;
		init_player ();
		n_pant = SCR_INICIO;
		n_pant_precalc = n_pant-2;
				
		// Entering game
		
		// Initializations
		for (i=0;i<30;i++){
			// little trick...
			knowledge_characters_1[i]=0; //overwrites knowledge_characters_2 ;)
			knowledge_characters_2[i]=0;
			// another trick: repetition but less bytes!
			pocket_things[i%3]=-1;
			my_memory[i%3]=-1;
			conversation_character[i%6]=0;
			joke_times[i%6]=0;
			confidence[i%7]=0;
			hungry[i%7]=0;
		}
		
		pocket_item = starting_speech = last_interact = -1;
		pocket_counter = memory_counter = 0;
		success = moon_is_seated = which_face = which_facef= which_facef2 = 0;
		
		// non-random icons...
		in_pant_of_character_i_there_is_perso_item[0] = -1;
		in_pant_of_character_i_there_is_perso_item[1] = 4;
		in_pant_of_character_i_there_is_perso_item[2] = 6;
		in_pant_of_character_i_there_is_perso_item[3] = 2;
		in_pant_of_character_i_there_is_perso_item[4] = 1;
		in_pant_of_character_i_there_is_perso_item[5] = 3;
		in_pant_of_character_i_there_is_perso_item[6] = 5;
		pocket_item=-1;
		
		redraw_new_screen(player.x);
		
		while (playing) {
			
			move_perso_face(perso_face_pos_x[n_pant],perso_face_pos_y[n_pant],perso_face_tile[n_pant]);
			move ();
			mueve_bicharracos ();	
			
			// Render	
			yB = 3 << 4;
			x = malotes [enoffs].x;
			y = malotes [enoffs].y;
			sp_MoveSprAbs (sp_moviles [0], spritesClip, en_an [0].next_frame - en_an [0].current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3),x & 7, y & 7);
			en_an [0].current_frame = en_an [0].next_frame;
			if (n_pant==0){
				yB = 1 << 4;
			}
			sp_MoveSprAbs (sp_movilesB [0], spritesClip, en_anB [0].next_frame - en_anB [0].current_frame, VIEWPORT_Y + (yB >> 3), VIEWPORT_X + (x >> 3),x & 7, yB & 7);
			en_anB [0].current_frame = en_anB [0].next_frame;
			
			yB = 3 << 4;
			// Precalc this, comes handy:
			x = player.x >> 6;
			y = player.y >> 6;
			
			sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);				
			sp_MoveSprAbs (sp_playerB, spritesClip, playerB.next_frame - playerB.current_frame, VIEWPORT_Y + (yB >> 3), VIEWPORT_X + (x >> 3), x & 7, yB & 7);
			
			player.current_frame = player.next_frame;
			playerB.current_frame = playerB.next_frame;			
			
			// Shows possible interactions according to the current pos BEGIN
			z = player.x>>10;
			interact=0;
			if (n_pant==5 && z==8){
				interact=9;
			}
			for (i=n_pant*4;i<(n_pant*4)+4;i++){
				if (interact_z[i]==z){
					interact = interact_value[i];
				}
			}
			if (interact==0){
				for (t = (player.y>>10)-2;t<(player.y>>10);t++){	
					// Texts of pamphlets, door, file cabinet, book, plant
					i = map_buff [z + (t << 4) - t];
					if (i>7 && i<14 && i!=12){
						interact = i + 4 - (i==13? 1:0);
						break;
					}else{
						print_str (3, 22, colorM4, texts_interact[0]);
					}
				}				
			}
			if (starting_speech==-1){
				sp_UpdateNow();
				if (ending){
					speakup_character(action_text_89,action_text_90,1);
				}else{
					speakup_character(action_text_87,action_text_88,1);
				}
				
#ifndef ANDROID_TCP_IP
				for (i=0;i<9;i++){
					speakup_clear(9);
					speakup_character(texts_initial_explanation[i*2],texts_initial_explanation[(i*2)+1],1);
					espera_pasiva(ESPERA_PASIVA);
				}
#endif

				espera_pasiva(ESPERA_PASIVA);
				blackout_area();
				sp_UpdateNow();	
				starting_speech++;
			}else if (moon_is_seated==1){
				saca_a_todo_el_mundo_de_aqui(1);
				draw_coloured_tile (VIEWPORT_X + 14, VIEWPORT_Y+4, 16);	
				sp_UpdateNow();	
				speakup_character(action_text_105,action_text_106,1);
				espera_pasiva(40);
				speakup_clear(9);
				if (ending){
					// Ending recurrent
					speakup_character(action_text_107,action_text_108,1);
					espera_pasiva(40);
					peta_el_beeper (0);
					success=1;
					playing=0;
				}else{
					// Ending nihilist
					speakup_character(action_text_109,action_text_110,1);
					espera_pasiva(40);
					speakup_clear(9);
					speakup_character(action_text_112,action_text_113,1);
					peta_el_beeper (6);
					espera_pasiva(100);
					#asm
						jp 0
					#endasm
				}	
			}
			print_interact_text();
			// Shows possible interactions according to the current pos END
			
			// Update to screen
			sp_UpdateNow();
			
			// Flick screen checks and scripting related stuff			
			gpit = (joyfunc) (&keys);
					
#ifdef ANDROID_TCP_IP
			// Codigo para joystick virtual Android compatible con Spectranet (simulate_key_d==1)
			if (((gpit & sp_FIRE) == 0 || simulate_key_d==2) && interact){
				simulate_key_d=0;
#else
			if ((gpit & sp_FIRE) == 0 && interact) {
#endif		
			// Interaction control
				Interaction();
				gpit=0;
			}
			
			if (n_pant_precalc>=0 && joke_times[n_pant_precalc]==2){
				// oh no...
				if (n_pant>=4&&n_pant<=6){
					peta_el_beeper (0);
				}
				saca_a_todo_el_mundo_de_aqui (1);
				peta_el_beeper (6);
				playing = 0;
				success = 0;
			}
			
			if (player.x == 0 && player.vx < 0) {
				n_pant --;
				i=entering_pos_right;
				if (n_pant==0){
					n_pant=7;
				}else if (n_pant==-1){
					n_pant=7;
					i=13400;
				}
				redraw_new_screen(i);
			}
			if (player.x == entering_pos_right && player.vx > 0) {
				n_pant ++;
				if (n_pant==1){
					n_pant=7;
					redraw_new_screen(13400);
				}else{
					if (n_pant==8){
						n_pant=1;
					}	
					redraw_new_screen(0);
				}
			}
			
			n_pant_precalc=n_pant-2;
			
		}
		
		saca_a_todo_el_mundo_de_aqui(0);
		sp_UpdateNow ();
		
		if (!success) {
			game_over ();
			ending=0;
		}
		cortina ();

	}
			
}

int redraw_new_screen(int posx){
	int i;
	int pos = (n_pant-1)*4;

	draw_scr ();
	player.x = posx;

	face_looper = face_looperf = face_looperf2 = 0;
	
	for (i=0;i<=14;i++){
		fan_i_told[i%3]=-1;// little trick
		info_found[i%3]=-1;// little trick
		draw_coloured_tile (VIEWPORT_X + (i*2), VIEWPORT_Y-2, 13); // BG
		// Draw Booth Texts with a little trick
		print_str (booths_texts_pos[n_pant], booths_texts_pos[(i%4)+8]-(!n_pant&&(i%4)<2?2:0), booths_texts_pos[(i%4)+12], texts_booths[pos+(i%4)]);
	}

	if (n_pant==1){
		draw_coloured_tile (VIEWPORT_X + 0, VIEWPORT_Y-2, 1); // BG
		draw_coloured_tile (VIEWPORT_X + 2, VIEWPORT_Y-2, 0); // BG
		draw_coloured_tile (VIEWPORT_X + 4, VIEWPORT_Y-2, 0); // BG
		draw_coloured_tile (VIEWPORT_X + 6, VIEWPORT_Y-2, 0); // BG
		draw_coloured_tile (VIEWPORT_X + 2, VIEWPORT_Y+2, 40); // BG
	}else if (n_pant==7){ 
		draw_coloured_tile (VIEWPORT_X + 24, VIEWPORT_Y-2, 0); // BG
		draw_coloured_tile (VIEWPORT_X + 26, VIEWPORT_Y-2, 1); // BG
		draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y-2, 0); // BG
		draw_coloured_tile (VIEWPORT_X + 26, VIEWPORT_Y+2, 41); // BG
	}
	
	draw_common_fan_items(common_fan_items[n_pant*3],common_fan_items[(n_pant*3)+1],common_fan_items[(n_pant*3)+2]);
		
}

int move_perso_face(int posx1,int posx2,int posx3){
	
	if (face_looper==0 && n_pant>1){
		draw_coloured_tile (VIEWPORT_X + posx1, VIEWPORT_Y+4, which_face==0? n_pant+15:n_pant+40); // Face stand
		which_face=(which_face+1)%2;
	}
	if (face_looperf==0){
		draw_coloured_tile (VIEWPORT_X + posx2, VIEWPORT_Y+4, which_facef==0? 2:5); // Face fan
		which_facef=(which_facef+1)%2;
	}
	if (face_looperf2==0){
		draw_coloured_tile (VIEWPORT_X + posx3, VIEWPORT_Y+4, which_facef2==0? 30:39); // Face fan
		which_facef2=(which_facef2+1)%2;
	}
	
	face_looper=(face_looper+1)%45;
	face_looperf=(face_looperf+1)%35;
	face_looperf2=(face_looperf2+1)%40;
		
	sp_UpdateNow ();
	
}

int draw_common_fan_items(int dx1, int dx2, int dx3){
	int i;
	
	draw_coloured_tile (VIEWPORT_X + dx1, VIEWPORT_Y+6, 7); // fan body 1
	draw_coloured_tile (VIEWPORT_X + dx2, VIEWPORT_Y+6, 31); // fan body 2
	if (n_pant==0){
		for (i=0;i<3;i++){
			print_str (common_fan_items[2]+i, 13, 50, texts_things_reduced[0]);
		}
		print_str (common_fan_items[2]+1, 12, 50, texts_things_reduced[0]);
	}else if (in_pant_of_character_i_there_is_perso_item[n_pant-1]!=-1){
		draw_coloured_tile (VIEWPORT_X + dx3, VIEWPORT_Y+4, 23+in_pant_of_character_i_there_is_perso_item[n_pant-1]);	
	}
}
						
int print_interact_text(void){
	int i;
	
	print_str (3, 21, colorM4, texts_interact[0]);
	if (interact==3 && n_pant==0){
		print_str (3, 21, colorM4, texts_interact[24]);	
	}else{
		print_str (3, 21, colorM4, texts_interact[interact]);	
	}
	
	if (interact==9){
		// show those who already gave the code or ??
		print_str (6, VIEWPORT_Y-8, 7, action_text_101);
		for (i=1; i<7; i++){
			if (in_pant_of_character_i_there_is_perso_item[i]!=i){
				print_str (8+(i*2), VIEWPORT_Y-6, i, "?");
				print_str (9+(i*2), VIEWPORT_Y-6, i, "?");
				print_str (8+(i*2), VIEWPORT_Y-5, i, "?");
				print_str (9+(i*2), VIEWPORT_Y-5, i, "?");
			}else{
				draw_coloured_tile (8+(i*2), VIEWPORT_Y-6, i+16); // Faces
			}
		}
	}else if (interact>4 && interact<12){
		for (i=0; i<5; i++){
			print_str (3, i%3, colorM1, status_perso[(i%3)+2]);// little trick
			if (confidence[n_pant-1]>i){
				print_str (15+(i*2), 0, 2, status_perso[1]);	
			}else{
				print_str (15+(i*2), 0, 7, status_perso[0]);	
			}	
			if (hungry[n_pant-1]>i){
				print_str (15+(i*2), 2, 6, n_pant==2? texts_things_reduced[1]:n_pant==6? texts_things_reduced[2]:texts_things_reduced[0]);
			}else{
				print_str (15+(i*2), 2, 3, status_perso[0]);	
			}
		}
		if (knowledge_characters_1[n_pant_precalc]==1){
			print_str (15, 1, 3, texts_things_reduced[n_pant+1]);	
		}else{
			print_str (15, 1, 5, "?");	
		}
	}else if (last_interact=-1 || (last_interact!=-1 && last_interact!=interact)){
		blackout_area();
	}
	last_interact = interact;
	
	// Text of special items
	print_str (3, 22, colorM4, texts_interact[0]);
	if (n_pant!=0 && interact==3 && in_pant_of_character_i_there_is_perso_item[n_pant-1]+1){
		// character i = 0..7 => Moon, Bob, Germione, Koji, Dick, Zork, John
		print_str (3, 22, colorM3, texts_interact[17+in_pant_of_character_i_there_is_perso_item[n_pant-1]]);
	}
	
}

int Interaction(void){
	int i;
	int all_ok;
	
	blackout_area();
	
	if (interact==3 && n_pant==0){
		// special case: take hamburguer
		add_to_pockets_helper(0);
		interact=0;
	}

	switch (interact){
		case 1: // talk to excited fan
			peta_el_beeper (3);	
			talk_to_fan_helper(action_text_24,"",0);
			break;
		case 4: // talk to happy fan
			peta_el_beeper (3);	
			talk_to_fan_helper(action_text_39,action_text_40,1);
			break;
		case 2: // sit in your booth
			peta_el_beeper (3);	
			if (in_pant_of_character_i_there_is_perso_item[0]==0){
				moon_is_seated=1;
			}else{
				speakup_character(action_text_28,action_text_29,1);	
			}
			break;
		case 3: // get/put icon of booth
			// take or leave a booth's icon
			peta_el_beeper (3);	
			speakup_character(texts_taking_icons[in_pant_of_character_i_there_is_perso_item[n_pant-1]!=-1?6:pocket_item!=-1?7:8],"",1);
			if (in_pant_of_character_i_there_is_perso_item[n_pant-1]!=-1 || pocket_item!=-1){
				if (n_pant>1){
					//texts_taking_icons
					if (hungry[n_pant-1]==5 && 
					    confidence[n_pant-1]==5 && 
						knowledge_characters_1[n_pant_precalc]==1 &&
						in_pant_of_character_i_there_is_perso_item[n_pant-1]!=n_pant-1){
					// Test
					//if (in_pant_of_character_i_there_is_perso_item[n_pant-1]!=n_pant-1){
						speakup_character(texts_taking_icons[n_pant_precalc==0? 0:3],"",0);
						redraw_icons();		
					}else{
						speakup_character(texts_taking_icons[n_pant_precalc==0? 1:4],texts_taking_icons[n_pant_precalc==0? 2:5],0);
					}
				}else{
					redraw_icons();
				}					
			}
			break;
		case 5: // talk to Bob			
		case 6: // talk to Germione
		case 7: // talk to Koji Bakuto
		case 8: // talk to Dick Reckard
		case 10: // talk to Zork
		case 11: // talk to John Doe
			peta_el_beeper (3);	
			show_conversation_interface();
			break;
		case 9: // open the locker
			all_ok=1;
			for (i=1; i<7; i++){
				if (in_pant_of_character_i_there_is_perso_item[i]!=i){
					all_ok=0;
					break;
				}				
			}
			if (all_ok && pocket_item!=0){
				// my speccy and my game!!
				peta_el_beeper (8);
				speakup_character(action_text_102,action_text_103,1);
				pocket_item=0;
				draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y+14, 23);
				speakup_clear(9);
				speakup_character(action_text_104,"",1);
			}else if (all_ok){
				peta_el_beeper (3);	
				speakup_character(action_text_104,"",1);
			}else{
				peta_el_beeper (3);	
				speakup_character(action_text_66,action_text_67,1);	
			}
			break;
		case 13: // door
			if (pocket_things[0]==13||pocket_things[1]==13||pocket_things[2]==13){
				// if I have the access card I can open doors
				if (n_pant==1){
					speakup_character(garbo_text[0],garbo_text[1],1);
					speakup_clear(9);
					speakup_character(garbo_text[2],garbo_text[3],1);
					speakup_clear(9);
					speakup_character(garbo_text[4],garbo_text[5],1);
					speakup_clear(9);
					add_to_pockets_helper(1);					
				}else{
					// access to the restaurant
					n_pant=0;
					peta_el_beeper (8);
					redraw_new_screen(13400);
				}
			}else{
				peta_el_beeper (3);	
				speakup_character(action_text_81,action_text_82,1);	
			}
			break;
		case 12: // pamphlets
			perform_actions_pamphlet_book(0);
			break;
		case 15: // book
			perform_actions_pamphlet_book(2);
			break;
		case 14: // file cabinet
		case 16: // plant
			if ((rand()%6)){
				info_found[1]= -1;
				speakup_character(interact>14?action_text_97:action_text_98,"",1);
			}else{
				add_to_pockets_helper(interact>14?2:(rand()%11)+3); // 13 = access card
			}
			break;		
	}
	espera_pasiva(ESPERA_PASIVA);
	blackout_area();
	sp_UpdateNow();	
}

int redraw_icons(void){
	int i;
	peta_el_beeper (8);
	if (pocket_item!=-1){
		// interchange
		i=in_pant_of_character_i_there_is_perso_item[n_pant-1];
		in_pant_of_character_i_there_is_perso_item[n_pant-1]=pocket_item;
		pocket_item=i;
		// show the new one
		draw_coloured_tile (VIEWPORT_X + common_fan_items[(n_pant*3)+2], VIEWPORT_Y+4, 23+in_pant_of_character_i_there_is_perso_item[n_pant-1]);	
	}else { 
		// just take
		pocket_item=in_pant_of_character_i_there_is_perso_item[n_pant-1];
		in_pant_of_character_i_there_is_perso_item[n_pant-1]=-1;
		// empty tile 14
		draw_coloured_tile (VIEWPORT_X + common_fan_items[(n_pant*3)+2], VIEWPORT_Y+4, 14);	
	}
	if (pocket_item!=-1){
		// show the one I took
		draw_coloured_tile (VIEWPORT_X + 28, VIEWPORT_Y+14, 23+pocket_item);	
	}else{
		// nothing taken, pocket is empty
		print_str (29, 22, colorM4, "  ");
		print_str (29, 23, colorM4, "  ");
	}
	if (in_pant_of_character_i_there_is_perso_item[n_pant-1]==n_pant-1 && n_pant>1){
		speakup_character(texts_start_conv[36+(n_pant_precalc*2)],texts_start_conv[37+(n_pant_precalc*2)],0);
	}
}				
					
int talk_to_fan_helper(char * text1, char * text2, int fan_id){
	speakup_character(text1,text2,1);			
	peta_el_beeper (9);
	// 0..34 (6x5 + 5 no effect)
	fan_i_told[fan_id]= fan_i_told[fan_id]==-1? (rand()%18)*2 : fan_i_told[fan_id];
	speakup(9+fan_id, 26, 3, 1, 3, colorM2, texts_fans[fan_i_told[fan_id]]);
	speakup(9+fan_id, 26, 3, 1, 4, colorM2, texts_fans[fan_i_told[fan_id]+1]);
	espera_pasiva(20);
	speakup_clear(9);
	speakup_character(action_text_91,action_text_92,1);
	update_memory(fan_i_told[fan_id]);
}

int add_to_pockets_helper(int what_thing){
	peta_el_beeper (9);
	info_found[1]= what_thing;
	speakup_character(texts_things[info_found[1]],"",1);
	add_to_pockets_things(info_found[1]);
}
										
int perform_actions_pamphlet_book(int pos){
	if (info_found[pos]==-1){
		info_found[pos]=((rand()%17)+18)*2;
	}
	peta_el_beeper (9);
	speakup_character(texts_fans[info_found[pos]],texts_fans[info_found[pos]+1],1);
	update_memory(info_found[pos]);
}
			
int update_memory(int info_found){
	int not_added = 1;
	int i=0;
	
	for (i=0;i<3;i++){
		if (my_memory[i]==info_found){
			// already knew it
			return;
		}
	}
	
	memory_counter=0;
		
	for (i=0;i<3;i++){
		memory_counter=memory_counter+1;
		if (my_memory[i]==-1){
			my_memory[i]=info_found;
			not_added = 0;
			break;
		}
	}
	if (memory_counter==3 && not_added){
		my_memory[0]=my_memory[1];
		my_memory[1]=my_memory[2];
		my_memory[2]=info_found;
	}	
	
}

int add_to_pockets_things(int thing_found){
	int not_added = 1;
	int i=0;
	
	for (i=0;i<3;i++){
		if(pocket_things[i]==thing_found && thing_found>2){
			// already_got_it
			speakup_clear(9);
			speakup_character(action_text_99,"",1);
			return 0;
		}
	}
	pocket_counter=0;
	for (i=0;i<3;i++){
		pocket_counter=pocket_counter+1;
		if (pocket_things[i]==-1){
			pocket_things[i]=thing_found;
			not_added = 0;
			break;
		}
	}
	if (pocket_counter==3 && not_added){
		pocket_things[0]=pocket_things[1];
		pocket_things[1]=pocket_things[2];
		pocket_things[2]=thing_found;
	}
	
	print_current_pockets();
	
}

int give_thing_from_pocket(int given_thing){
	int i=0;
	
	pocket_things[given_thing]=-1;
	for (i=given_thing;i<3;i++){
		pocket_things[i]=pocket_things[i+1];
	}
	pocket_things[2]=-1;
	
	pocket_counter=0;
	for (i=0;i<3;i++){
		if (pocket_things[i]==-1){
			break;
		}
		pocket_counter++;
	}
	print_current_pockets();
}

int print_current_pockets(void){
	int i=0;
	
	if (pocket_things[0]!=-1){
		print_str (3, 23, colorM1, action_text_111);
		for (i=0;i<3;i++){
			print_str (12+(3*i), 23, i+2, pocket_things[i]==-1?" ":texts_things_reduced[pocket_things[i]]);
		}	
	}else{
		print_str (3, 23, colorM1, texts_interact[0]);
	}
}
	
int show_conversation_interface(void){
	int i,j=0;
	
	selection = 0;
	print_str (3, 21, colorM4, texts_interact[0]);
	//if (conversation_character[n_pant_precalc]==0){
	//	// first greetings
	//	conversation_character[n_pant_precalc]=1;
	//	first_convertation_character();
	//}else 
	if (hungry[n_pant-1]==5 && 
	          confidence[n_pant-1]==5 && 
			  knowledge_characters_1[n_pant_precalc]==1){
		if (in_pant_of_character_i_there_is_perso_item[n_pant-1]!=n_pant-1){
			// no more conversation, just want the booth item!
			peta_el_beeper (7);
			speakup_character(texts_start_conv[24+(n_pant_precalc*2)],texts_start_conv[25+(n_pant_precalc*2)],0);	
		}else{
			// final thanks text of this character
			speakup_character(texts_start_conv[36+(n_pant_precalc*2)],texts_start_conv[37+(n_pant_precalc*2)],0);	
		}
	}else{
		if (conversation_character[n_pant_precalc]==0){
			// first greetings
			conversation_character[n_pant_precalc]=1;
			first_convertation_character();
			espera_pasiva(ESPERA_PASIVA);
			blackout_area();
		}
		print_str (3, 21, colorM4, action_text_100);
		write_selection_list_text();
		conversation_selection_engine();
		// The conversation starts
		switch (selection){
			case 0: 
				// Initial greetz
				first_convertation_character();
				break;
			case 1: 
				// Joke end...
				joke_times[n_pant_precalc]++;
				i = n_pant_precalc * 2;
				speakup_character(texts_start_joke[i],texts_start_joke[i+1],1);
				if (joke_times[n_pant_precalc]<2){
					speakup_character(texts_start_joke[i+12],texts_start_joke[i+13],0);
				}else{
					speakup_character(texts_start_joke[i+24],texts_start_joke[i+25],0);
				}
				break;
			default:
				if (selection-1 <= memory_counter){
					// it is certainly knowledge
					speakup_character(texts_fans[my_memory[selection-2]],texts_fans[my_memory[selection-2]+1],1);
					j=-1;
					for (i=n_pant_precalc*5;i<(n_pant_precalc*5)+5;i++){
						if (knowledge_characters_3[i]==my_memory[selection-2]){
							j++;
							if (knowledge_characters_2[i]==0){
								// Didn't know it!
								peta_el_beeper (8);
								knowledge_characters_2[i]=1;
								confidence[n_pant-1]++;
								j++;
							}
							speakup_character(texts_start_knew_didnt_knew_it[(n_pant_precalc*2)+(12*j)],texts_start_knew_didnt_knew_it[(n_pant_precalc*2)+1+(12*j)],0);
							break;
						}	
					}
					if (j==-1){
						// Useless knowledge...
						speakup_character(texts_start_do_not_care[n_pant_precalc*2],texts_start_do_not_care[(n_pant_precalc*2)+1],0);
					}
				}else{
					// we are giving something from the pocket
					i = pocket_things[(selection-2-memory_counter)%3];
					give_thing_from_pocket((selection-2-memory_counter)%3);
					speakup_character(texts_things[i],texts_things_reduced[i],1);
					j=0;
					if (n_pant==i-1){
						knowledge_characters_1[n_pant_precalc]=1; // the character has his pocket item
						peta_el_beeper (8);
					}else if ((i==2 && n_pant==6)||(i==1 && n_pant==2)||(n_pant!=6 && n_pant!=2 && i==0)){
						// 0: hamburg (Others), 1: gab., (Bob) 2: bug (Zork)
						if (hungry[n_pant-1]<5){
							hungry[n_pant-1]++;
						}
						j=j+2;
						peta_el_beeper (7);
					}else{
						j++;
					}
					speakup_character(texts_given[(n_pant_precalc*2)+(12*j)],texts_given[(n_pant_precalc*2)+1+(12*j)],0);
				}
				break;				
		}
	}
}

int conversation_selection_engine(void){
	int prev_selection = -1;
	int i=0;
	
	selection=0;

	read_keys_joystick_helper();

	while ((gpit & sp_DOWN) != 0){
		#ifdef ANDROID_TCP_IP	
			for (i=0;i<3;i++){ // there is repetition in the sending of commands
				read_keys_joystick_helper();
			}
		#else
			read_keys_joystick_helper();
		#endif
		if ((gpit & sp_RIGHT) == 0) {
			selection = (selection+1==(2+pocket_counter+memory_counter))? selection : selection+1;
			peta_el_beeper (3);
		}
		else if ((gpit & sp_LEFT) == 0) {
			selection = (selection-1<0)? 0:selection-1;
			peta_el_beeper (3);
		}
		write_selection_list_text();
		if ((prev_selection==-1) || ((prev_selection!=-1) && prev_selection!=selection)){
			step();
			espera_pasiva(10);
			for (i=0;i<2;i++){
				print_str (3, 22+i, colorM3, texts_interact[0]);
			}
			switch (selection){
				case 0: // Initial greetz
					print_str (3, 22, colorM3, texts_start_conv[n_pant_precalc*2]);
					print_str (3, 23, colorM3, texts_start_conv[(n_pant_precalc*2)+1]);
					break;
				case 1: // Joke
					print_str (3, 22, colorM3, texts_start_joke[n_pant_precalc*2]);
					print_str (3, 23, colorM3, texts_start_joke[(n_pant_precalc*2)+1]);
					break;
				default:
					if (selection-1 <= memory_counter){
						// it is certainly knowledge
						print_str (3, 22, colorM3, texts_fans[my_memory[selection-2]]);
						print_str (3, 23, colorM3, texts_fans[my_memory[selection-2]+1]);
					}else{
						// we are giving something from the pocket
						print_str (3, 22, colorM3, texts_things[pocket_things[(selection-2-memory_counter)%3]]);
						print_str (3, 23, colorM3, texts_things_reduced[pocket_things[(selection-2-memory_counter)%3]]);
					}
					break;
			}	
		}
		prev_selection = selection;
	}
	peta_el_beeper (3);
	for (i=0;i<3;i++){
		print_str (3, 21+i, colorM4, texts_interact[0]);
	}
	print_current_pockets();
}

int write_selection_list_text(void){
	int i=0;
	
	for (i=0; i<(2+pocket_counter+memory_counter); i++){
		//selected is flash colorM4 (128+6), unselected is colorM5 
		// initial greetz, joke, knowdlegde 1-2-3, give pocket content 1-2-3
		print_number1(12+i, 21,i==selection?134:colorM5,i+1);
	}
	sp_UpdateNow();	
}

int first_convertation_character(void){
	int i=n_pant_precalc*2;
	
	// show first default starting text of Moon and other character
	speakup_character(texts_start_conv[i],texts_start_conv[i+1],1);
	speakup_character(texts_start_conv[i+12],texts_start_conv[i+13],0);
	switch (n_pant){
		case 2:
			speakup_clear(9);
			speakup_character(action_text_47,"",1);	
			break;
		case 5:
			speakup_clear(1);
			speakup_character(first_conv_rade[0],first_conv_rade[1],0);
			speakup_clear(1);
			speakup_character(first_conv_rade[2],first_conv_rade[3],0);
			speakup_clear(9);
			speakup_character(first_conv_rade[4],first_conv_rade[5],1);
			break;
		case 7:
			speakup_clear(9);
			speakup_character(first_conv_john[0],first_conv_john[1],1);
			speakup_clear(1);
			speakup_character(first_conv_john[2],first_conv_john[3],0);
			break;
	}
}
