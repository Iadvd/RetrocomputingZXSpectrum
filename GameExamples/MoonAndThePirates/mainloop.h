// mainloop.h
// Churrera copyleft 2011 by The Mojon Twins.

void saca_a_todo_el_mundo_de_aqui () {
	saca_a_todo_el_mundo_de_aqui_helper(sp_player);
	saca_a_todo_el_mundo_de_aqui_helper(sp_playerB);
	if (malotes [n_pant].t != 0){
		saca_a_todo_el_mundo_de_aqui_helper(sp_moviles [0]);
		saca_a_todo_el_mundo_de_aqui_helper(sp_movilesB [0]);
	}	
	sp_UpdateNow();
}

int saca_a_todo_el_mundo_de_aqui_helper(struct sp_SS * who){
	sp_MoveSprAbs (who, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);				
}

void do_game (void) {
	unsigned char playing;
	unsigned char x, y, yB, t;
	unsigned char success=0;
	unsigned char who=0;
	int starting_speech,i;
	
	#asm
		di
	#endasm
	
	blackout();
	
	// splib2 initialization
	sp_Initialize (7, 0);
	//sp_Border (BLACK);	
	sp_AddMemory(0, 40, 14, AD_FREE); // reserva 40 bloques de 14 bytes a partir de dir 61952
	
	// Define keys and default controls
	keys.up  = sp_LookupKey('q');
	keys.down  = sp_LookupKey('a');
	keys.left  = sp_LookupKey('o');
	keys.right = sp_LookupKey('p');
	keys.fire  = sp_LookupKey(' ');
	joyfunc = sp_JoyKeyboard;

	Setup_Tileset_Sprites();
	
	while (1) {
		
		// Position of each special item when the game start
		in_pant_of_character_i_there_is_perso_item[0]=-1;
		in_pant_of_character_i_there_is_perso_item[1]=7;
		in_pant_of_character_i_there_is_perso_item[2]=6;
		in_pant_of_character_i_there_is_perso_item[3]=5;
		in_pant_of_character_i_there_is_perso_item[4]=3;
		in_pant_of_character_i_there_is_perso_item[5]=4;
		in_pant_of_character_i_there_is_perso_item[6]=2;
		
		for (i=0;i<100;++i){
			// Add some animation to the main menu
			colorize_texts(i%26);
			
			draw_coloured_tile (((i%13)+2)*2, 22, 13); // BG
			
			// little trick - variables initialization...
			knowledge_characters_1[i%30]=0; //overwrites knowledge_characters_2 ;)
			knowledge_characters_2[i%30]=0;
			// another trick: repetition but less bytes!
			pocket_things[i%3]=-1;
			my_memory[i%3]=-1;
			conversation_character[i%6]=0;
			joke_times[i%6]=0;
			confidence[i%7]=0;
			hungry[i%7]=0;
			which_face[i%3]=0;			
		}
		who=(who%7)+1;
		for (i=1;i<10;++i){
			speakup(who, 15, 4, values_col_menu[i], values_row_menu[i], values_color_menu[i], texts_menu[i]);
		}
		
		select_joyfunc ();
		// Create Main Menu END
		
		cortina ();
		
		// Let's do it.
		playing = 1;
		init_player ();
		n_pant = SCR_INICIO;
		n_pant_precalc = n_pant-2;
				
		// Entering game
		
		// Initializations
		pocket_item = starting_speech = last_interact = -1;
		pocket_counter = memory_counter = coconut_in_the_water = 0;
		success = boat_has_oars = was_mirrored = 0;
		
		redraw_new_screen(player.x);
		
		while (playing) {
			
			move_perso_face();
			move ();
			
			mueve_bicharracos ();	
			// Render friend & foes
			x = malotes [n_pant].x;
			y = malotes [n_pant].y;
			yB=y-16;
			sp_MoveSprAbs (sp_moviles [0], spritesClip, en_an.next_frame - en_an.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3),x & 7, y & 7);
			sp_MoveSprAbs (sp_movilesB [0], spritesClip, en_anB.next_frame - en_anB.current_frame, VIEWPORT_Y + (yB >> 3), VIEWPORT_X + (x >> 3),x & 7, yB & 7);
			en_an.current_frame = en_an.next_frame;
			en_anB.current_frame = en_anB.next_frame;
			
			// Render main character
			x = player.x >> 6;
			y = player.y >> 6;
			yB = y-16;
			sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);				
			sp_MoveSprAbs (sp_playerB, spritesClip, playerB.next_frame - playerB.current_frame, VIEWPORT_Y + (yB >> 3), VIEWPORT_X + (x >> 3), x & 7, yB & 7);
			player.current_frame = player.next_frame;
			playerB.current_frame = playerB.next_frame;				
			
			// Shows possible interactions according to the current pos BEGIN
			x = player.x >> 10;
			y = player.y >> 10;
			
			interact=0;
			
			// Screen Interactions BEGIN
			print_str (3, 22, colorM4, texts_interact[0]);
			// Priority 1: Special interactions...
			switch (n_pant){
				case 0:	if (x==0){
							interact=32; //Return to the ship
						}else if (x>=13){
							interact=2; //Go to the ferry (end of game)
						}
						break;
				case 1:
						if (x<=2){
							interact=26; //Go down
							if (y<3){
								interact=31; //Go to the beach
							}
						}else if (x==6){
							interact=9; // Open the final treasure chest
						}
						break;
				case 2:		
						if (x==7 && y==3){
							interact=29; //Go up
						}else if (x==1 && y==2){
							interact=33; //Fire a cannonball
						}
						break;
				case 3: 
						if (x>11 && y>3){
							interact=27; //Go down
						}else if (x==1 && y<3){
							interact=13; //Look in the water
						}
						break;
				case 4:
				case 6:
						if (x<2 && y>3){
							interact=28; //Go up
						}
						break;
				case 7:
						if (x==7){
							interact=30; //Go down
						}
						break;
				case 8: if (x==6){
							interact=25; //Get a cannonball
						}
						break;
			}
			
			// Priority 2: Characters that can speak and 
			// the special items of each screen
			for (i=n_pant*4;i<(n_pant*4)+4;++i){
				if (interact_z[i]==x){
					interact = interact_value[i];
					break;
				}
			}
			
			// Priority 3: Other interactive elements of the screen
			if (interact==0){
				for (t = y-2;t<y;++t){	
					// Texts of books and maps, door, basket, chest
					i = map_buff [x + (t << 4) - t];
					if (i==4 && n_pant==1){
						continue;
					}else if (i<=11){
						interact=priority3_interact[i];
						if (interact>0){
							break;
						}
					}
				}				
			}
			
			// Screen Interactions END
			
			// beginning of the game
			if (starting_speech==-1){
				for (i=0;i<10;i++){
					speakup_character(texts_initial_explanation[i*2],texts_initial_explanation[(i*2)+1],1);
				}
				blackout_area();
				++starting_speech;
			}
			
			if (boat_has_oars==2){
				print_str (29, 22, colorM4, "  ");
				print_str (29, 23, colorM4, "  ");
				speakup_character(end_text[0],end_text[1],1);
				speakup_character(end_text[2],end_text[3],1);
				speakup_character(end_text[4],end_text[5],1);
				scroll_management(100);
				success=1;
				playing=0;
			}
			
			print_interact_text();
			// Shows possible interactions according to the current pos END
			
			// Update to screen
			sp_UpdateNow();
			
			// Flick screen checks and scripting related stuff			
			gpit = (joyfunc) (&keys);
					
			if ((gpit & sp_FIRE) == 0 && interact) {
			// Interaction control
				Interaction();
				gpit=0;
			}
			
			if (n_pant_precalc>=0 && joke_times[n_pant_precalc]==2){
				playing = 0;
				success = 0;
			}
			
			if (player.vx < 0){
				if (player.x <= entering_pos_left) {
					switch (n_pant){
						case 0:
						case 7:
							if (player.x == 0) {
								player.vx=0;
							}
							break;
						case 2:
						case 3:
						case 5:
						case 8:
							if (player.x == 0) {
								check_and_restore();
								n_pant --;
								switch (n_pant){
									case 1:
									case 2:
										intermediate_screen_from=n_pant;
										n_pant=8;
										break;
									case 7:
										n_pant=intermediate_screen_from;
										break;
								}
								redraw_new_screen(14336);								
							}
							break;
						case 1:
						case 6:
						case 4:
							player.vx=0;
							player.x=entering_pos_left;
							break;
					}
					
				}
			}else if (player.vx > 0){
				if (player.x >= entering_pos_right && n_pant==3) {
					player.vx=0;
					player.x=entering_pos_right;
				}else if (player.x == 14336) {
					switch (n_pant){
						case 1:
						case 2:
						case 4:
						case 8:
							check_and_restore();
							++n_pant;
							switch (n_pant){
								case 2:
								case 3:
									intermediate_screen_from=n_pant-1;
									n_pant=8;
									redraw_new_screen(0);
									break;
								case 9:
									n_pant=intermediate_screen_from+1;
								case 5:
									redraw_new_screen(0);
									break;
							}
							break;
						else:
							player.vx=0;
							break;
					}
				}
			}
			n_pant_precalc=n_pant-2;
		}
		
		peta_el_beeper (6);
		saca_a_todo_el_mundo_de_aqui();
		if (!success) {
			game_over ();
		}
		musical_end();
		cortina ();
	}
			
}

int redraw_new_screen_helper(int posx,int posy){
	print_str_in_viewport (posx, posy, 16, "[[");//optimization
}

int redraw_new_screen(int posx){
	int i;	
	draw_scr ();
	player.x = posx;

	for (i=0;i<=14;++i){
		face_looper[i%3]=0;
		fan_i_told[i%3]=-1;// little trick
		info_found[i%3]=-1;// little trick
		if (n_pant!=0){
			//Ship frame
			redraw_new_screen_helper(i*2,n_pant==7?10:11);
		}
		//Sky background
		draw_coloured_tile_in_viewport(i*2,-2,15);
		
		switch (n_pant){
			case 4:
			case 5:
				// Canyons and hull
				draw_coloured_tile_in_viewport(i*2,-2,i%4==1?15:6);
				if (i%4==1){
					// Ship frame
					redraw_new_screen_helper(i*2,-2);
				}
				break;
			case 6:
				// Hull
				draw_coloured_tile_in_viewport(i*2,-2,6);
				break;
		}
	}
	
	// Details by screen
	switch (n_pant){
		case 0:
			player.y = 4 << 10;
			// Clouds
			draw_helper(2,28,28,43,43,43);// the third is repeated but reduces mem. use
			// Silhouette of the ship
			print_str_in_viewport(24,-2,69,texts_things_reduced[10]);
			// Grog
			for (i=0;i<8;++i){
				print_str (23+i, 18, 70, texts_things_reduced[11]);//70amcla//71blcla//7bl
				print_str (common_fan_items[2]+i, 13, 50, texts_things_reduced[0]);
				print_str (common_fan_items[2]+1+(i%2), 12, 50, texts_things_reduced[0]);
			}
			break;
		case 1:
			if (posx==(2<<10)){
				player.y = 2 << 10;
			}
			// Clouds and island
			draw_helper(2,28,26,43,43,14);
			break;
		case 2:
			if (posx==(6<<10)){
				player.y = 3 << 10;
			}
			// Clouds and island
			draw_helper(24,6,8,43,14,43);
			for (i=13;i<17;++i){
				print_str (i, 14+(i<15?2:0), 6, texts_things_reduced[11]);//70amcla//71blcla//7bl
			}
			break;
		case 3:
			// Clouds and island
			draw_helper(28,2,4,43,14,43);
			break;
		case 7:
			player.y = 1 << 10;
			// Clouds and island
			draw_helper(24,6,8,43,14,43);
			break;
		case 8:
			if (intermediate_screen_from==1){
				// Clouds and island
				draw_helper(18,7,20,14,43,43);
			}else{
				// Clouds and island
				draw_helper(26,4,6,43,14,43);
			}
			break;
	}
	
	for (i=-1;i<=(n_pant>3?4:5);++i){
		switch (n_pant){
			case 1:
			case 2:
			case 3:
				// Sails
				draw_coloured_tile_in_viewport(booths_texts_pos[n_pant]-1+(i*2),-2,1);
				break;
			case 4:
			case 6:
				// Ladder
				draw_coloured_tile_in_viewport(0,i*2,47);
				break;
		}
	}
	
	draw_common_character_items();
					
}

int draw_helper (int i, int j, int k, int l, int m, int n){
	draw_coloured_tile_in_viewport(i,-2,l);
	draw_coloured_tile_in_viewport(j,-2,m);
	draw_coloured_tile_in_viewport(k,-2,n);
}

int move_perso_face(){
	
	if (face_looper[0]==0 && n_pant>1 && n_pant<8){
		// Main characters turn head
		mirror_tile=1;
		draw_coloured_tile (perso_face_pos_x[n_pant], perso_face_pos_y[n_pant]-2, n_pant+27); 
		mirror_tile=0;
		which_face[0]=!which_face[0];
	}
	if (face_looper[1]==0){
		// Informers type 1 turn head
		draw_coloured_tile (common_fan_items[n_pant*3], common_fan_items_y_pos[n_pant*3]-2, 17+which_face[1]);
		which_face[1]=!which_face[1];
	}
	if (face_looper[2]==0){
		// Informers type 2 turn head
		draw_coloured_tile (common_fan_items[(n_pant*3)+1], common_fan_items_y_pos[(n_pant*3)+1]-2, 19+which_face[2]);
		which_face[2]=!which_face[2];
	}
	
	face_looper[0]=(face_looper[0]+1)%35;
	face_looper[1]=(face_looper[1]+1)%25;
	face_looper[2]=(face_looper[2]+1)%30;
	
	sp_UpdateNow ();
	
}

int draw_common_character_items(){
	int i,j;
	
	for (i=0;i<2;++i){
		draw_coloured_tile (common_fan_items[(n_pant*3)+i], common_fan_items_y_pos[(n_pant*3)+i], 16); // info character bodies
	}
	
	if (n_pant>1&&n_pant<8){
		draw_coloured_tile (perso_face_pos_x[n_pant], perso_face_pos_y[n_pant], n_pant%2?12:44); // Body of main characters		
		if (in_pant_of_character_i_there_is_perso_item[n_pant-1]!=-1){
			// item if any in current screen
			draw_coloured_tile (common_fan_items[(n_pant*3)+2], common_fan_items_y_pos[(n_pant*3)+2], 20+in_pant_of_character_i_there_is_perso_item[n_pant-1]);	
		}
	}else if (n_pant==8){
		for (j=0;j<7;++j){
			for (i=-6+j;i<6-j-1;++i){
				print_str (common_fan_items[2]+i, 16-j, 7, texts_things_reduced[12]);//56
			}			
		}
	}
	
}
						
int print_interact_text(void){
	int i;
	
	// clear
	print_str (3, 21, colorM4, texts_interact[0]);
	
	// interaction text
	print_str (3, 21, colorM4, texts_interact[(interact==3 && n_pant==0?24:interact)]);	
	
	if (interact==9){
		// show those who already gave the code or ??
		print_str (6, VIEWPORT_Y-8, 7, action_text_101);
		for (i=1; i<7; ++i){
			asm_int[0]=8+(i*2);//safe here
			//in_pant_of_character_i_there_is_perso_item[n_pant-1]==n_pant
			if (in_pant_of_character_i_there_is_perso_item[i]!=i+1){
				print_str (asm_int[0], VIEWPORT_Y-6, i, "??");
				print_str (asm_int[0], VIEWPORT_Y-5, i, "??");
			}else{
				draw_coloured_tile (asm_int[0], VIEWPORT_Y-6, i+28); // Faces
			}
		}
	}else if (interact>4 && interact<12){
		for (i=0; i<5; ++i){
			print_str (3, i%3, colorM1, status_perso[(i%3)+2]);// little trick
			asm_int[0]=15+(i*2);//safe here
			if (confidence[n_pant-1]>i){
				print_str (asm_int[0], 0, 2, status_perso[1]);	
			}else{
				print_str (asm_int[0], 0, 7, status_perso[0]);	
			}	
			if (hungry[n_pant-1]>i){
				print_str (asm_int[0], 2, 6, n_pant==7? texts_things_reduced[2]:n_pant==6? texts_things_reduced[1]:texts_things_reduced[0]);
			}else{
				print_str (asm_int[0], 2, 3, status_perso[0]);	
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
		// character i = 0..7 => Moon, Bored, Capt.Socks, Sorcerer, Cook, Cabin boy, Lookout
		print_str (3, 22, colorM3, texts_interact[17+in_pant_of_character_i_there_is_perso_item[n_pant-1]]);
	}
	
}

int Interaction(void){
	int i;
	int all_ok;
	
	blackout_area();
	
	switch (interact){
		case 1: // talk to excited fan
			peta_el_beeper (3);	
			talk_to_fan_helper(action_text_24,action_text_25,1);
			break;
		case 4: // talk to happy fan
			peta_el_beeper (3);	
			talk_to_fan_helper(action_text_39,action_text_40,0);
			break;
		case 2: // enter the ferry!
			peta_el_beeper (3);	
			if (pocket_item==0){
				boat_has_oars=2;
			}else{
				speakup_character(action_text_28,action_text_29,1);	
			}
			break;
		case 3: // get/put icon of booth
			// take or leave a booth's icon
			peta_el_beeper (3);	
			speakup_character(texts_taking_icons[in_pant_of_character_i_there_is_perso_item[n_pant-1]!=-1?3:pocket_item!=-1?4:5],"",1);
			if (in_pant_of_character_i_there_is_perso_item[n_pant-1]!=-1 || pocket_item!=-1){
				if (n_pant>1){
					//texts_taking_icons
					if (hungry[n_pant-1]==5 && 
					    confidence[n_pant-1]==5 && 
						knowledge_characters_1[n_pant_precalc]==1 &&
						in_pant_of_character_i_there_is_perso_item[n_pant-1]!=n_pant){
					// Test
					//if (in_pant_of_character_i_there_is_perso_item[n_pant-1]!=n_pant){
						speakup_character(texts_taking_icons[0],"",0);
						redraw_icons();		
					}else{
						speakup_character(texts_taking_icons[1],texts_taking_icons[2],0);
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
			for (i=1; i<7; ++i){
				if (in_pant_of_character_i_there_is_perso_item[i]!=i+1){
					all_ok=0;
					break;
				}				
			}
			//all_ok=1; test
			if (all_ok && pocket_item!=0){
				// my speccy and my game!!
				peta_el_beeper (8);
				speakup_character(action_text_102,action_text_103,1);
				pocket_item=0;
				draw_coloured_tile_in_viewport(28,14,21);
				speakup_character(action_text_104,"",1);
			}else{
				peta_el_beeper (3);
				if (all_ok){
					speakup_character(action_text_104,"",1);
				}else{
					speakup_character(action_text_66,action_text_67,1);	
				}
			}
			break;
		case 13: // check out the water
			if (coconut_in_the_water>0){
				--coconut_in_the_water;
				// take the coconut
				add_to_pockets_helper(1);
			}else{
				peta_el_beeper (3);	
				speakup_character(action_text_98,"",1);	
			}
			break;
		case 12: // pamphlets
			perform_actions_pamphlet_book(0);
			break;
		case 15: // book
			perform_actions_pamphlet_book(2);
			break;
		case 14: // basket
		case 16: // chest
			if (rand()%3){
				info_found[1]= -1;
				speakup_character(interact>15?action_text_97:action_text_98,"",1);
			}else{
				add_to_pockets_helper(objects_on_screen[n_pant]); //9 = oars of the boat
			}
			break;
		case 17:
			// take grog
			add_to_pockets_helper(0);
			break;
		case 25: 
			// take the cannonball
			add_to_pockets_helper(12);
			break;
		case 26: // down to the orlop
			scr_jmp_helper(6,player.x);
			break;
		case 27: // down to the middle deck
			scr_jmp_helper(4,entering_pos_left);
			break;
		case 28: // down to upper deck
			peta_el_beeper (9);	
			check_and_restore();
			n_pant=n_pant==6?1:3;
			redraw_new_screen(n_pant==1?entering_pos_left:entering_pos_right);
			break;
		case 29: // up to the crow's nest
			scr_jmp_helper(7,7<<10);
			break;
		case 30: // down to the deck
			scr_jmp_helper(2,6<<10);
			break;
		case 31: // to Coconut's island
			for (i=0;i<3;++i){
				if (pocket_things[i]==9){
					give_thing_from_pocket(i);
					// if I have the oars of the boat I can go to the island
					boat_has_oars=1;
					break;
				}
			}
			if (boat_has_oars==1){
				// access to Coconuts island
				peta_el_beeper (8);
				n_pant=0;
				// Moon speaks
				speakup_character(garbo_text[0],garbo_text[1],1);
				redraw_new_screen((1<<10)/2);
			}else{
				peta_el_beeper (3);	
				speakup_character(action_text_81,action_text_82,1);	
			}
			break;
		case 32: // return to the ship
			peta_el_beeper (9);	
			n_pant=1;
			redraw_new_screen(2<<10);
			break;
		case 33: // fire a cannonball!
			peta_el_beeper (9);	
			for (i=0;i<3;++i){
				if (pocket_things[i]==12){
					asm_int[0]=3;
					speakup_character(action_text_118,"",1);
					peta_el_beeper (8);	
					blackout_area();
					++coconut_in_the_water;
					speakup_character(action_text_115,action_text_116,1);
					give_thing_from_pocket(i);
					interact=0;
					break;
				}
			}
			if (interact){//not found trick
				speakup_character(action_text_117,"",1);
			}
			break;
		case 34: // rummage in the barrel
			if (rand()%4){
				info_found[1]= -1;
				speakup_character(action_text_98,"",1);
			}else{
				add_to_pockets_helper(2); // VOODOO BEVERAGE
			}
			break;
	}
	espera_pasiva(ESPERA_PASIVA);
	blackout_area();
}

int scr_jmp_helper(int pant,int posx){
	peta_el_beeper (9);	
	check_and_restore();
	n_pant=pant;
	redraw_new_screen(posx);
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
		i=20+in_pant_of_character_i_there_is_perso_item[n_pant-1];
	}else { 
		// just take
		pocket_item=in_pant_of_character_i_there_is_perso_item[n_pant-1];
		in_pant_of_character_i_there_is_perso_item[n_pant-1]=-1;
		i=13; // empty tile 13
	}
	draw_coloured_tile (common_fan_items[(n_pant*3)+2], common_fan_items_y_pos[(n_pant*3)+2], i);		
	
	if (pocket_item!=-1){
		// show the one I took
		draw_coloured_tile_in_viewport(28,14,20+pocket_item);
	}else{
		// nothing taken, pocket is empty
		print_str (29, 22, colorM4, "  ");
		print_str (29, 23, colorM4, "  ");
	}
	if (in_pant_of_character_i_there_is_perso_item[n_pant-1]==n_pant && n_pant>1){
		speakup_character(texts_start_conv[36+(n_pant_precalc*2)],texts_start_conv[37+(n_pant_precalc*2)],0);
	}
}				
					
int talk_to_fan_helper(char * text1, char * text2, int fan_id){
	speakup_character(text1,text2,1);			
	peta_el_beeper (9);
	// 0..29
	fan_i_told[fan_id]= fan_i_told[fan_id]==-1? (rand()%15)*2 : fan_i_told[fan_id];
	speakup(9+fan_id, 26, 3, 1, 3, colorM2, texts_fans[fan_i_told[fan_id]]);
	speakup(9+fan_id, 26, 3, 1, 4, colorM2, texts_fans[fan_i_told[fan_id]+1]);
	scroll_management(20);
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
		info_found[pos]=((rand()%15)*2)+30;
	}
	peta_el_beeper (9);
	speakup_character(texts_fans[info_found[pos]],texts_fans[info_found[pos]+1],1);
	update_memory(info_found[pos]);
}
			
int update_memory(int info_found){
	int not_added = 1;
	int i=0;
	
	for (i=0;i<3;++i){
		if (my_memory[i]==info_found){
			// already knew it
			return;
		}
	}
	
	memory_counter=0;
		
	for (i=0;i<3;++i){
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
	
	if (thing_found==9 && boat_has_oars==1){
		// already got oars for the boat
		speakup_character(action_text_114,"",1);
		return 0;	
	}
	
	if (thing_found!=12){ // if it is not a cannonball
		for (i=0;i<3;++i){
			if(pocket_things[i]==thing_found && thing_found>2){ // and is not a drink or food
				// already_got_it
				speakup_character(action_text_99,"",1);
				return 0;
			}
		}			
	}
	pocket_counter=0;
	for (i=0;i<3;++i){
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
	for (i=given_thing;i<3;++i){
		pocket_things[i]=pocket_things[i+1];
	}
	pocket_things[2]=-1;
	pocket_counter=pocket_counter-1;
	print_current_pockets();
}

int print_current_pockets(void){
	int i=0;
	
	if (pocket_things[0]!=-1){
		print_str (3, 23, colorM1, action_text_111);
		for (i=0;i<3;++i){
			print_str (12+(3*i), 23, i+2, pocket_things[i]==-1?"  ":texts_things_reduced[pocket_things[i]]);
		}	
	}else{
		print_str (3, 23, colorM1, texts_interact[0]);
	}
}
	
int show_conversation_interface(void){
	int i,j=0;
	
	selection = 0;
	print_str (3, 21, colorM4, texts_interact[0]);
	if (hungry[n_pant-1]==5 && 
	          confidence[n_pant-1]==5 && 
			  knowledge_characters_1[n_pant_precalc]==1){
		if (in_pant_of_character_i_there_is_perso_item[n_pant-1]!=n_pant){
			// no more conversation, just want the booth item!
			peta_el_beeper (8);
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
				++joke_times[n_pant_precalc];
				i = n_pant_precalc * 2;
				speakup_character(texts_start_joke[i],texts_start_joke[i+1],1);
				if (joke_times[n_pant_precalc]<2){
					// one more and out!
					speakup_character(texts_start_joke[i+12],texts_start_joke[i+13],0);
				}else{
					// it really happened... then end
					speakup_character(texts_start_joke[i+24],texts_start_joke[i+25],0);
				}
				break;
			default:
				if (selection-1 <= memory_counter){
					// it is certainly knowledge
					speakup_character(texts_fans[my_memory[selection-2]],texts_fans[my_memory[selection-2]+1],1);
					j=-1;
					for (i=n_pant_precalc*5;i<(n_pant_precalc*5)+5;++i){
						if (knowledge_characters_3[i]==my_memory[selection-2]){
							++j;
							if (knowledge_characters_2[i]==0){
								// Didn't know it!
								peta_el_beeper (8);
								knowledge_characters_2[i]=1;
								++confidence[n_pant-1];
								++j;
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
					}else if ((i==2 && n_pant==7)||(i==1 && n_pant==6)||(n_pant!=6 && n_pant!=7 && i==0)){
						// Food / Beverage rules here...
						// 0: grog (Others),  1: coconut (Cabin boy), 2: voodoo beverage, (Lookout)
						if (hungry[n_pant-1]<5){
							++hungry[n_pant-1];
						}
						j=j+2;
						peta_el_beeper (8);
					}else{
						++j;
					}
					speakup_character(texts_given[(n_pant_precalc*2)+(12*j)],texts_given[(n_pant_precalc*2)+1+(12*j)],0);
				}
				break;				
		}
	}
}

int conversation_selection_engine(void){
	int prev_selection = -1;
	int i;
	
	selection=0;

	read_keys_joystick_helper();

	while ((gpit & sp_DOWN) != 0){
		read_keys_joystick_helper();
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
			conversation_selection_engine_helper(texts_interact[0],texts_interact[0]);
			switch (selection){
				case 0: // Initial greetz
					conversation_selection_engine_helper(
						texts_start_conv[n_pant_precalc*2],
						texts_start_conv[(n_pant_precalc*2)+1]);
					break;
				case 1: // Joke
					conversation_selection_engine_helper(
						texts_start_joke[n_pant_precalc*2],
						texts_start_joke[(n_pant_precalc*2)+1]);
					break;
				default:
					if (selection-1 <= memory_counter){
						// it is certainly knowledge
						conversation_selection_engine_helper(
							texts_fans[my_memory[selection-2]],
							texts_fans[my_memory[selection-2]+1]);
					}else{
						// we are giving something from the pocket
						conversation_selection_engine_helper(
							texts_things[pocket_things[(selection-2-memory_counter)%3]],
							texts_things_reduced[pocket_things[(selection-2-memory_counter)%3]]);
					}
					break;
			}	
		}
		prev_selection = selection;
	}
	peta_el_beeper (3);
	for (i=0;i<3;++i){
		print_str (3, 21+i, colorM4, texts_interact[0]);
	}
	print_current_pockets();
}

int conversation_selection_engine_helper(char * text1, char * text2){
	print_str (3, 22, colorM3, text1);
	print_str (3, 23, colorM3, text2);
}

int write_selection_list_text(void){
	int i=0;
	
	for (i=0; i<(2+pocket_counter+memory_counter); ++i){
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
			speakup_character(action_text_47,"",1);	
			break;
		case 6:
			speakup_character(first_conv_cabin_boy[0],first_conv_cabin_boy[1],1);
			speakup_character(first_conv_cabin_boy[2],first_conv_cabin_boy[3],0);
			speakup_character(first_conv_cabin_boy[4],"",1);
			break;
	}
}
