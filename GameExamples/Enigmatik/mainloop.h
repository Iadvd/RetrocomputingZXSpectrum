// mainloop.h

// Churrera copyleft 2011 by The Mojon Twins.
unsigned char give_me_rand_key(void);
	
void do_game (void) {
	unsigned int i;
	unsigned char x,y;
	
	// splib2 initialization
	sp_Initialize (7, 0);
	
	Setup_Tileset_Sprites();
	
	#asm
		di
	#endasm
	
	aux_peb5();
	#asm
		ld hl,22528+(32*15)+6
		#ifdef DEFEN
			ld a,21
		#endif
		#ifdef DEFPT
			ld a,20
		#endif
		#ifdef DEFRU
			ld a,16
		#endif
		#ifdef DEFSP
			ld a,18
		#endif
		rep_print:
			cp a,0
			jp z,end_print
			ld (hl),74-64
			inc hl
			dec a
			jp rep_print
		end_print:
	#endasm
	while (sp_GetKey()==0){
		fx_lights();
		seed[0]=(seed[0]+1)%1000;
		heart_rate=40;
		do_heartbeat(0);
	}
	
	sp_UpdateNow();	
	
	while (1){

		aux_peb7();
		prepare_screen((unsigned int) (s_title));
		
		//seals[0]=10;seals[1]=10;seals[2]=10;seals[3]=10;//test
		for (i=0;i<4;i++){
			if (seals[i]==10){
				char_buffer[0]=values_s[i]+32;
				print_str(values_scx[i],values_scy[i],values_sc[i],char_buffer);
			}
		}
		sp_UpdateNow();
		
		aux_fx_lights();
		
		for (i=0;i<4;i++){
			if (seals[i]!=10){
				// the seals are lost unless it was completely sealed or there was a bonus
				if (seals_bu[i]==15){
					seals[i]=0; 
				}else{
					seals[i]=seals_bu[i];
				}
			}
			sacrifice[i]=0;
		}
		
		if (check_finished()){
			//finale
			gpit3=19;
			border_fx();
			blackout_area();
			clear_all();
			to_buffer_screen(creepypasta);
			espera_pasiva(80);
			for (i=0;i<200;i++){
				if (i%((10-(i/20))+1)==0){
					aux_creepypasta_show(rand()%4);
				}else{
					espera_pasiva(1);
				}
			}
			// level==32  >> IQ=127   
			// level>=120 >> IQ=115 
			// lwidth=120-32=88
			// iqwidth=127-125=12
			// iq_1_step_penalty=lwidth/iqwidth=88/12=7
			// level<32+7 IQ=127
			// level>=120 IQ=115 
			// else IQ=127-((level-32)/7)
			iq=127;
			if (level>=120){
				iq=115;
			}else if (level>32){
				iq=127-((level-32)/7);
			}
			print_number1(16,11,2,iq);
			sp_UpdateNow();
			#asm
				ld a,0
				call peta_el_beeper
			#endasm	
			show_finale();
		}
		
		gpit3=23;
		border_fx();
		
		// write a random sequence
		current_seq=rand()%10;
		print_str(0,22,2+64,series_n[current_seq]);
		sp_UpdateNow();
		
		// unlock sequence
		pressed_key=0;
		#asm
			call musicstart
		#endasm
		if (pressed_key==series_s[current_seq]){
			level=(levelbu>0?levelbu:0);
			while ((level%4)!=0){
				level++; // so in case of backup must guess keys again
			}
			playing_status=1;
			aux_peb5();
			heart_rate=1;
			juego=0;
			while (playing_status){
				aux_cc();
				if ((level%4==0)){ // redefine keys each 4 games
					//prepare_screen((unsigned int) (w_title));
					last_wins=0;
					aux_print_level();
					aux_print_seals();
					randomize_keys();
				}else{
					aux_cc2();
				}
				if ((level%4!=0)||((level%4==0)&&guess_keys())){
					flash_arrows(120);
					gpit3=20;
					if (level%4==0){
						border_fx(); // only when coming from redefine keys
					}
					snake_souls=10; // play_labyrinth and play_sudoku' safeguard
					to_buffer_screen(creepypasta);
					
					while (seals[juego]==10){
						juego=(juego+1)%4; // do not play if already sealed
					}
					//play_labyrinth
					snake_sacrifice=0;
					if ((juego==0)?play_labyrinth():((juego==1)?play_snake():((juego==2)?play_sudoku():play_musiket()))){
					//if ((juego==0)?play_musiket():((juego==1)?play_musiket():((juego==2)?play_musiket():play_musiket()))){ //test
						// because finish_detected==1
						if (snake_souls!=10){
							// coming from play_snake or play_musiket and didn't win
							bloody_ending();
							playing_status=1;
							if (snake_sacrifice==1){
								++last_wins;
							}
						}else{
							++last_wins;
							sp_UpdateNow();
							aux_fx_lights();
							gpit3=20;
							border_fx();
						}
						if (((level%4)==3) && (last_wins>2) && (!check_finished())){ // at least 3 games win in this loop
							bonus_up=1;
							play_bonus();
							bonus_up=0;
						}
						++level;
					}else{
						bloody_ending();
						break;
					}
					juego=(juego+1)%4;
					if (check_finished()){
						playing_status=0;
					}
				}else{
					bloody_ending();
				}
			}
		}else{
			bloody_ending();
		}
		
	}
			
}

int aux_fx_lights(void){
	int i;
	for (i=0;i<2500;i++){
		if (i%200==0){
			//asm_int[0]=22527;
			//asm_int_d[0]=768;
			fx_lights();
		}
	}
}

int check_finished(void){
	return (seals[0]==10)&&(seals[1]==10)&&(seals[2]==10)&&(seals[3]==10);
}

int aux_cc(void){
	clean_center=1;
	prepare_screen((unsigned int) (w_title));
	clean_center=0;
}

int aux_cc2(void){
	gpit=32+64;
	for (guess_key=0;guess_key<4;guess_key++){
		show_color_guide();
	}
}
										
int fx_lights(void){
	#asm
		ld hl,22527
		ld de,768
		nextonek:
			inc hl
			ld a,(hl)
			add 0
			cp 64
			jp c,ponerbrillo
			sub 64
			ld (hl),a
			jp seguirsub
			ponerbrillo:
				add 64
				ld (hl),a
			seguirsub:
				dec de
				ld a,d
				add 0
				cp 0
				jp nz,nextonek
				ld a,e
				add 0
				cp 0
				jp nz,nextonek
	#endasm
}

int bloody_ending(void){
	int i;
	#asm
		ld hl,16384+6144
		ld de,_screen_buffer
		ld bc,768
		ldir
	#endasm
	playing_status=0;
	for (icx=0;icx<32;icx++){
		i=rand()%19;
		for (icy=0;icy<=5+i;icy++){
			asm_int[0]=((unsigned int)(screen_buffer))+(32*icy)+icx;//22528+(32*icy)+icx;
			gpit=18+(i%2?64:0);
			#asm
				ld hl,(_asm_int)
				ld a,(_gpit)
				ld (hl),a
			#endasm
		}
	}
	#asm
		ld hl,_screen_buffer
		ld de,16384+6144
		ld bc,768
		ei
		halt
		ldir
		di
	#endasm
	#asm
		ld a,0
		call peta_el_beeper
	#endasm
	gpit3=18;
	border_fx();
}

int border_fx(void){
	unsigned int i;
	for (i=0;i<41;i++){
		asm_int_d[0]=1750-(i*30);
		#asm
			ld a,10
			call _play_frequence
		#endasm
	}	
}

int read_keys_helper(void){
	pressed_key=sp_GetKey()-32;
}

int randomize_keys(void){
	int i=-1;
	while (++i<4){
		// Assign randomly a key for l,r,u,d
		key_pad[i]=0;
		//16 to 25 and 33 to 58 incl (+32 to coordinate with MK1)
		while (eq_prev(i)||!accepted_key(key_pad[i])){
			key_pad[i]=give_me_rand_key();
		}
		key_pad_was_guessed[i]=0;
	}
	return 1;
}

int eq_prev(int i){
	int j=-1,res=0;
	while (++j<i){
		res=(res||(key_pad[i]==key_pad[j]));
	}
	return res;
}

unsigned char give_me_rand_key(void){
	return (rand()%64)+32;
}

int guess_keys(void){
	unsigned char guessed_all=0;
	heart_looper=0;
	internal_loops=0;
	guess_key=0; //0=l,1=r,2=u,3=d
	penalty=0;
	while ((guessed_all==0)&&(heart_rate<13)){	
		gpit = 0;
		while (!accepted_key(gpit)&&(heart_rate<13)){
			do_heartbeat(1);
			flash_arrows(internal_loops);
			aux_getKey();
			//test
			//print_str(18,20,2,"000");
			//print_number1(20,20,2,gpit);
			//sp_UpdateNow();
		}
		if (heart_rate!=13){
			if (gpit==key_pad[guess_key]){
				key_pad_was_guessed[guess_key]=1;
				gpit=32+64;
				show_color_guide();// Green=Success
				heart_decelerates(1);
				sp_UpdateNow();
				aux_peb7();
			}else if ((gpit==key_pad[0])||(gpit==key_pad[1])||(gpit==key_pad[2])||(gpit==key_pad[3])){
				gpit=48+64;
				show_color_guide();// Yellow=Hint:wrong place
				aux_peb5();
			}else{
				if (penalty==4){
					heart_accelerates(1); // penalty
					penalty=0;
				}
				++penalty;
				gpit=16+64;
				show_color_guide();// Red=not here, pal
				aux_peb5();
			}
			
			if ((key_pad_was_guessed[0]==1)&&(key_pad_was_guessed[1]==1)&&(key_pad_was_guessed[2]==1)&&(key_pad_was_guessed[3]==1)){
				// guessed all
				guessed_all=1;
				break;
			}
			// still something to guess
			flash_arrows(120); // any value>100 forces showing the current arrow before changing
			guess_key=(guess_key+1)%4;
			while (key_pad_was_guessed[guess_key]==1){
				guess_key=(guess_key+1)%4;
			}
		}
	}
	if (heart_rate!=13){
		flash_arrows(120);
		aux_fx_lights();
	}
	return (heart_rate!=13);
}

int do_heartbeat(int with_beat){
	if ((heart_looper==0)||(heart_looper==(300/heart_rate))){
		#asm
			ld a,6
			call peta_el_beeper
		#endasm	
		if (with_beat){
			if(heart_looper==0){
				
				#asm
					ld hl,22528+(32*2)+4
					ld a,0
					ld (hl),a
				#endasm
			}else{
				#asm
					ld hl,22528+(32*2)+4
					ld a,2+64
					ld (hl),a
				#endasm
			}
		}		
	}
	++heart_looper;
	++internal_loops;
	if (internal_loops==10000){
		heart_accelerates(1);
	}
	if (heart_looper==(1000/heart_rate)){
		heart_looper=0;
	}
	
}
			
int heart_accelerates(int qty){
	int i;
	for (i=0;i<qty;i++){
		++heart_rate;
		heart_looper=0;
		internal_loops=0;
		asm_int[0]=18-heart_rate;
		aux_reduce_rh();
	}	
}

int heart_decelerates(int how_much){
	int i;
	old_heart_rate=heart_rate;
	if (heart_rate>=(how_much+1)){
		heart_rate-=how_much;
	}else{
		heart_rate=1;
	}
	char_buffer[0]=9+32;
	heart_looper=0;
	internal_loops=0;
	for (i=heart_rate;i<=old_heart_rate;i++){
		print_str(17-i,2,color_code[12-i],char_buffer);
	}
	if (no_sound==0){
		aux_peb5();
	}
}

int flash_arrows(int internal_loops){
	asm_int[0]=22528+(32*22)+6+(guess_key*5);
	if ((internal_loops%200)<100){
		#asm
			ld hl,(_asm_int)
			ld a,0
			ld (hl),a
		#endasm
	}else{
		#asm
			ld hl,(_asm_int)
			ld a,5+64;
			ld (hl),a
		#endasm
	}
}
			
int show_color_guide(void){
	//16+64=red, 48+64=Yellow, 32+64=Green
	//guess_key
	asm_int[0]=22528+(32*22)+aux_array_scg[guess_key];
	#asm
		ld hl,(_asm_int)
		ld a,(_gpit)
		ld (hl),a
		inc hl
		ld (hl),a
		inc hl
		ld (hl),a
		inc hl
		ld (hl),a
	#endasm
	if (gpit==32+64){
		char_buffer[0]=key_pad[guess_key];
		print_str(aux_table[guess_key],22,gpit+1,char_buffer);
	}
	sp_UpdateNow();
}

int play_bonus(void){
	int i,prev_current_seq;
	
	aux_cc();
	aux_cc2();
	char_buffer[0]=3+32;
	print_str(8,1,0,char_buffer);
	print_str(29,8,1+64,char_buffer);
	print_str(12,13,1+64,char_buffer);
	aux_print_level();
	
	// write a random sequence
	counterbonus=0;
	for (i=0;i<5;i++){
		prev_current_seq=current_seq;
		while (prev_current_seq==current_seq){
			current_seq=rand()%15;
		}
		print_str(4,8,0,"                       ");
		print_str(4,8,3+64,series_bonus_n[current_seq]);
		sp_UpdateNow();
		pressed_key=0;
		#asm 
			call musicstart
		#endasm
		gpit=pressed_key;
		aux_aux_gk(); // if caps
		if (gpit>26){
			gpit=gpit-32; // numbers do not require correction
		}
		//print_number1(20,19,2,pressed_key); //test
		//print_number1(20,20,3,gpit);
		//print_number1(20,21,4,series_sb[current_seq]);
		//sp_UpdateNow();
		espera_pasiva(30);
		if (gpit==series_sb[current_seq]){
			++counterbonus;
			aux_peb5();
			espera_pasiva(30);
		}else{
			break;
		}
	}
	if (counterbonus==5){
		// bonus prize health +1 and a random seal
		aux_peb5();
		heart_decelerates(2);
		i=rand()%4;
		while(seals[i]==10){
			i=rand()%4;
		}
		++seals[i]; // accumulate seals
		for (i=0;i<4;i++){
			// a backup of the game is done automatically
			seals_bu[i]=seals[i];
			levelbu=level;
		}
		aux_print_seals_number();
		gpit3=20;
		border_fx();
	}else{
		bloody_ending();
		playing_status=1;
	}
}						

int play_snake(void){
	int i;
	
	for (i=0;i<10;i++){
		snake_x[i]=255; // out of the board pos
		snake_y[i]=255; // out of the board pos
	}
	// open the board with empty screen
	// show random souls
	// take 5 to end
	// creepy images appear
	// en 4,4 tiene 24 por 13
	
	// 4 > seal
	// 10 > totems
	// 32 > soul
	// 62 > being
	// 0 > path
	
	// attr 3 = being / crash
	// attr 6 = soul (can walk and take it)
	// attr 5 = path (can walk)
	// attr 4 = totems
	// attr 4+64 seal
	
	char_buffer[0]=0+32;
	gpit=5;
	draw_empty_field();
	
	// totems
	aux_snake_totems_x[0]=rand()%12; //0..11
	aux_snake_totems_y[0]=rand()%7; //0..6
	aux_snake_totems_x[1]=12+rand()%12;//12..23
	aux_snake_totems_y[1]=rand()%7; //0..6
	aux_snake_totems_x[2]=rand()%12; //0..11
	aux_snake_totems_y[2]=7+rand()%6; //7..12
	aux_snake_totems_x[3]=12+rand()%12;//12..23
	aux_snake_totems_y[3]=7+rand()%6; //7..12
	
	// start
	snake_x[0]=0;
	snake_y[0]=rand()%13;
	while ((snake_y[0]==aux_snake_totems_y[0])||(snake_y[0]==aux_snake_totems_y[1])||(snake_y[0]==aux_snake_totems_y[2])||(snake_y[0]==aux_snake_totems_y[3])){
		snake_y[0]=rand()%13;
	}
	char_buffer[0]=62+32; // being is at the start position
	print_str(4,4+snake_y[0],3,char_buffer);
	
	char_buffer[0]=10+32;
	for (i=0;i<4;i++){
		print_str(4+aux_snake_totems_x[i],4+aux_snake_totems_y[i],4,char_buffer);
	}
	
	invoke_soul();
	
	aux_print_level();
	
	finish_detected=0;
	snake_souls=0;
	last_snake_direction=key_pad[1];
	while (heart_rate!=13 && finish_detected==0){
		do_heartbeat(1);
		if (internal_loops%40==0){
			aux_getKey();
			if (gpit==0){
				gpit=last_snake_direction;
			}
			for (i=0;i<4;i++){
				if (gpit==key_pad[i]){
					last_snake_direction=gpit;
					move_snake(i); //l,r,u,d
				}
			}			
		}
		creepypasta_show(1);//1
	}
	if (heart_rate!=13){
		//print_number1(20,20,2,snake_souls); //test
		//sp_UpdateNow();
		if (snake_souls==10){
			heart_decelerates(2);
		}else{
			heart_accelerates(2);
		}
	}
	if (heart_rate>=13){
		heart_rate=13;
	}
	return (heart_rate!=13);
}

int play_sudoku(void){
	int idx,i,j,k,l,t;
	// create a new one
	for (i=0;i<rand()%10;i++){
		// rotar vals
		k=values_s[0];
		for (j=0;j<3;j++){
			values_s[j]=values_s[j+1];
		}
		values_s[3]=k;
	}
	for (i=0;i<16;i++){
		sudoku[i]=values_s[sudokut[i]];
	}
	for (i=0;i<rand()%10;i++){
		// rotar huecos en plantilla
		k=sudokuz[0];
		for (j=0;j<15;j++){
			sudokuz[j]=sudokuz[j+1];
		}
		sudokuz[15]=k;
	}
	for (i=0;i<15;i++){
		if (sudokuz[i]==0){
			sudoku[i]=0;
		}
	}
	
	// open the board with empty screen
	// show sudoku
	// creepy images appear
	
	char_buffer[0]=0+32;
	gpit=5;
	draw_empty_field();
	
	print_str(10,5,6+64,"@@@@@@@@@@@@");
	print_str(10,6,6+64,"@          @");
	print_str(10,7,6+64,"@ @@@@@@@@ @");
	for (i=0;i<6;i++){
		print_str(10,8+i,6+64,"@ @      @ @");
	}
	print_str(10,14,6+64,"@ @@@@@@@@ @");
	print_str(10,15,6+64,"@          @");
	print_str(10,16,6+64,"@@@@@@@@@@@@");
	for (i=0;i<16;i++){
		char_buffer[0]=sudoku[i]+32;
		print_str(14+(i%4),9+(i/4),sudoku[i],char_buffer);
		if (sudoku[i]==0){
			print_str(14+(i%4),9+(i/4),7+64,"?");
		}
	}
	
	aux_print_level();
	
	finish_detected=0;
	cx=0; // abs position in sudoku left-top to down-rigth
	if (find_next_open((cx+1)%16,16)==0){
		find_next_open(0,cx);
	}
	while (heart_rate!=13 && finish_detected==0){
		do_heartbeat(1);
		if (internal_loops%35==0){
			if (internal_loops%210==0){
				asm_int[0]=22528+(32*icy)+icx;
				#asm
					ld hl,(_asm_int)
					ld a,(hl)
					ld (_gpit),a
				#endasm
				if (gpit>64){
					// hide 
					#asm
						ld hl,(_asm_int)
						ld a,0
						ld (hl),a
					#endasm
				}else{
					write_again_symbol();
				}
				
			}
			aux_getKey();
			for (i=0;i<4;i++){
				if (gpit==key_pad[i]){
					aux_peb7();
					move_sudoku(i); //l,r,u,d
					break;
				}
			}	
			sp_UpdateNow();			
		}
		creepypasta_show(2);
	}
	if (heart_rate<13){
		heart_decelerates(2);
	}else{
		heart_rate=13;
	}
	return (heart_rate!=13);
}

int play_musiket(void){
	int i,j,k;
	// create a new musiket
	for (i=0;i<8;i++){
		musiket[i]=rand()%4;
	}
	
	// open the board with empty screen
	// show musiket
	// creepy images appear
	
	char_buffer[0]=0+32;
	gpit=0;
	draw_empty_field();
	
	aux_print_level();
	
	finish_detected=0;
	musiket_pos=0;
	musiketted=0;
	musiket_sub_pos=0;
	j=-1;
	while ((heart_rate!=13) && (musiket_pos<8) && (finish_detected==0)){
		do_heartbeat(1);
		if (musiketted==0){
			// shows once per success
			for (i=0;i<=musiket_pos;i++){
				aux_creepypasta_show(musiket[i]);
				if (j>=0){
					asm_int[0]=22528+(32*22)+6+(j*5);
					#asm
						ld hl,(_asm_int)
						ld (hl),5+64;
					#endasm
					j=-1;
				}
				j=musiket[i];
				asm_int[0]=22528+(32*22)+6+(musiket[i]*5);
				#asm
					ld hl,(_asm_int)
					ld (hl),6+64
				#endasm
				espera_pasiva(30);
			}				
			musiketted=1;
		}
		
		aux_getKey();
		for (gpit3=0;gpit3<4;gpit3++){
			// check if key equals to one of the arrows
			if (gpit==key_pad[gpit3]){
				aux_creepypasta_show(gpit3);
				espera_pasiva(30);
				if (gpit3!=musiket[musiket_sub_pos]){
					finish_detected=1;
				}else{
					if (musiket_sub_pos==musiket_pos){
						if (musiket_pos<8){
							// next cycle
							++musiket_pos;
							musiket_sub_pos=0;
							musiketted=0;
						}else{
							finish_detected=1;
						}
					}else{
						++musiket_sub_pos;
					}	
				}
				break;
			}	
		}
		
	}
	if (heart_rate!=13){
		if (musiket_pos<8){
			heart_accelerates(4); // penalty
			snake_souls=0; // use this trick
		}else{
			heart_decelerates(2);
			bonus_sacrifice();
		}	
		//bonus_sacrifice();
	}
	if (heart_rate>=13){
		heart_rate=13;
	}
	return (heart_rate!=13);
}

int bonus_sacrifice(void){
	int bonus_index;
	// sacrifice
	bonus_index=rand()%4; //0,1,2,3
	print_str(15,10,(bonus_index==0?2:(bonus_index==1?4:(bonus_index==2?5:3)))+64,(bonus_index==0?"\"":(bonus_index==1?"$":(bonus_index==2?"%":"("))));
	print_str(17,10,6+64,"?");
	sp_UpdateNow();
	
	found_back=-1;
	while (found_back==-1){
		aux_detect_musiket();
	};
	espera_pasiva(30);
	if (found_back==bonus_index){
		// sacrifice done
		if (seals[3]<10){
			++seals[3]; // accumulate seals
			aux_print_seals_number();
			if (seals[3]==10){
				levelbu=level;
			}
		}
	}
}
			
int aux_detect_musiket(void){
	int i;	
	aux_getKey();
	for (i=0;i<4;i++){
		if (gpit==key_pad[i]){
			found_back=i;
			aux_creepypasta_show(i);
			return;
		}
	}
}

int write_again_symbol(void){
	if (sudoku[cx]==0){
		// print question mark +64
		print_str(icx,icy,7+64,"?");
	}else{
		// show; sudoku[] has the correct attr + 64
		char_buffer[0]=sudoku[cx]-32;
		print_str(icx,icy,sudoku[cx],char_buffer);
	}
}

int find_next_open(int i, int e){
	int idx;
	for (idx=i;idx<e;idx++){
		icx=14+(idx%4);
		icy=9+(idx/4);
		asm_int[0]=22528+(32*icy)+icx;
		#asm
			ld hl,(_asm_int)
			ld a,(hl)
			ld (_gpit),a
		#endasm
		if (gpit>64||gpit==0){
			cx=idx;
			return 1;
		}
	}
	return 0;
}

int find_prev_open(int i, int e){
	int idx;
	for (idx=i-1;idx>=e;idx--){
		icx=14+(idx%4);
		icy=9+(idx/4);
		asm_int[0]=22528+(32*icy)+icx;
		#asm
			ld hl,(_asm_int)
			ld a,(hl)
			ld (_gpit),a
		#endasm
		if (gpit>64||gpit==0){
			cx=idx;
			return 1;
		}
	}
	return 0;
}

int draw_empty_field(void){
	// empty field
	for (hx=0;hx<24;hx++){
		for (hy=0;hy<13;hy++){
			print_str(4+hx,4+hy,gpit,char_buffer);
		}
	}
}
	
int aux_getKey(void){
	gpit=sp_GetKey();
	aux_aux_gk();
}

int aux_aux_gk(void){
	if ((gpit>=97)&&(gpit<=122)){
		// Caps to low
		gpit=gpit-32;
	}
}

int invoke_soul(void){
	int i,found=1;
	// a new soul arrives
	while (found==1){
		icx=rand()%24;
		icy=rand()%13;
		while (
			(icx==aux_snake_totems_x[0])&&(icy==aux_snake_totems_y[0])||
			(icx==aux_snake_totems_x[1])&&(icy==aux_snake_totems_y[1])||
			(icx==aux_snake_totems_x[2])&&(icy==aux_snake_totems_y[2])||
			(icx==aux_snake_totems_x[3])&&(icy==aux_snake_totems_y[3])
		){
			icx=rand()%24;
			icy=rand()%13;
		}
		found=0;
		for (i=0;i<10;i++){
			if ((icx==snake_x[i])&&(icy=snake_y[i])){
				found=1;
				break;
			}
		}		
	}
	char_buffer[0]=32+32; // soul
	print_str(4+icx,4+icy,6,char_buffer);
}

int play_labyrinth(void){
	int i;
	// open the board creating a random path
	// with a start finish hearth paths
	// walkable if attr is 6
	// check time success or not success
	// en 4,4 tiene 24 por 13
	
	// 3 > heart
	// 9 > finish
	// 62 > being
	// 9 > start
	// 30 > walls
	// 0 > path
	
	// attr 1 = wall (can't walk)
	// attr 2 = heart (can walk and take it)
	// attr 6 = finish (can walk)
	// attr 4 = start (can walk)
	// attr 3 = being (just it's there!)
	// attr 5 = path (can walk)
	
	// empty field
	char_buffer[0]=30+32;
	gpit=1;
	draw_empty_field();
	
	// start
	//sx=0
	sy=1+(rand()%11);
	char_buffer[0]=62+32; // being is at the start position
	print_str(4,4+sy,3,char_buffer);
	char_buffer[0]=0+32; // path
	print_str(5,4+sy,5,char_buffer); 
	
	// finish
	//fx=23
	fy=1+(rand()%11);
	char_buffer[0]=9+32;
	print_str(4+23,4+fy,6,char_buffer);
	char_buffer[0]=0+32; // path
	print_str(4+22,4+fy,5,char_buffer); 
	
	// backwards & forward map of exit
	cx=22;
	cy=fy;
	aux_dbf();
		
	// heart
	hx=14+(rand()%7);
	if (hx%2==1){
		++hx; // force the even position
	}
	hy=1+(rand()%11);
	
	// backwards map of heart
	char_buffer[0]=0+32; // path
	cx=hx;
	cy=hy;
	aux_dbf();
	
	// finally write the heart
	char_buffer[0]=3+32; 
	print_str(4+hx,4+hy,2,char_buffer);

	// and the seal if available
	if (sacrifice[0]==1){
		sacrifice[0]=0;
		char_buffer[0]=2+32; // seal
		print_str(4+slx,4+sly,2+64,char_buffer);
	}
	
	// and cx,cy will have the current position of the beign
	cx=0;
	cy=sy;
	
	aux_print_level();
	
	finish_detected=0;
	sacrifice[0]=2; // to detect sacrifice or not
	while (heart_rate!=13 && finish_detected==0){
		do_heartbeat(1);
		if (internal_loops%2==0){
			aux_getKey();
			for (i=0;i<4;i++){
				if (gpit==key_pad[i]){
					move(i); //l,r,u,d
				}
			}
		}
		creepypasta_show(0);
	}
	if (sacrifice[0]==2){
		sacrifice[0]=1; // next time will show seal
	}
	if (heart_rate>=13){
		heart_rate=13;
	}
	return (heart_rate!=13);
}

int aux_dbf(void){
	draw_backwards_forward(0,&cx,&cy);
	prepare_forward_map(); // forward map
}
	
int prepare_forward_map(void){
	// forward map
	icx=1;
	icy=sy;
	draw_backwards_forward(1,&icx,&icy);
	adjust();
}
	
int creepypasta_show(int who){
	// 0=p
	// 1=g
	// 2=r
	// 3=g
	if (rand()==0){
		++creepy_counter;
		if (creepy_counter<10){
			return;
		}
		creepy_counter=0;
		aux_creepypasta_show(who);
	}
}

int aux_creepypasta_show(int who){
	save_screen_attr();
	// puedo usar hasta _screen_buffer+6143 inclusive
	switch(who){
		case 0:
			#asm
				ld hl,_screen_buffer
				ld bc,512
			#endasm
		break;
		case 1:
			#asm
				ld hl,_screen_buffer+512
				ld bc,544
			#endasm
		break;
		case 2:
			#asm
				ld hl,_screen_buffer+512+544
				ld bc,544
			#endasm
		break;
		case 3:
			#asm
				ld hl,_screen_buffer+512+544+544
				ld bc,544
			#endasm
		break;
		/*
		case 4: // finale
			#asm
				ld hl,_screen_buffer+512+544+544+544
				ld bc,768
			#endasm
		break;
		case 5: // finale
			#asm
				ld hl,_screen_buffer+512+544+544+544+768
				ld bc,768
			#endasm
		break;
		*/
	}
	creep();
	gpit=who+1;
	#asm
		ld a,(_gpit)
		call peta_el_beeper
	#endasm
	//while (sp_GetKey()==0){};//test
	return_screen_attr();
}

int creep(void){
	// creep 1 24000 512 
	// creep 1 24512 544 
	#asm
		//put creepy image 1
		ld de,16384+6144
		ei
		halt
		ldir
		di
	#endasm
}

int save_screen_attr(void){
	#asm
		ld hl,16384+6144
		ld de,_screen_buffer+6144
		ld bc,544 // the biggest
		ldir
	#endasm
}

int return_screen_attr(void){
	#asm
		ld hl,_screen_buffer+6144
		ld de,16384+6144
		ld bc,544 // the biggest
		ei
		halt
		ldir
		di
	#endasm
}

int aux_print_level(void){
	int i;
	unsigned int prev_heart_rate;
	
	print_str(23,2,3,"00000");
	print_number1(27,2,3,level);
	prev_heart_rate=heart_rate;
	heart_rate=12;
	no_sound=1;
	heart_decelerates(12-prev_heart_rate);
	no_sound=0;
	aux_print_seals_number();
}

int aux_print_seals_number(void){
	print_str(3,19,6+64,"00");
	print_number1(4,19,6+64,seals[0]);
	print_str(10,19,6+64,"00");
	print_number1(11,19,6+64,seals[1]);
	print_str(18,19,6+64,"00");
	print_number1(19,19,6+64,seals[2]);
	print_str(25,19,6+64,"00");
	print_number1(26,19,6+64,seals[3]);
	sp_UpdateNow();
}

int aux_print_seals(void){
	int i,j,c1,c2,c3,c4,c5;
	for (i=0;i<4;i++){
		for (j=0;j<seals[i];j++){
			c5=(i<2?4:23)+(2*(j%3));
			
			c2=4+(2*(j/3));
			c1=(j<9?8+c2:14);
			c3=(j<9?c5:(i==0?6:25));
			c4=(j<9?c5:(i==1?10:21));
			
			switch (i){
				case 0:
					char_buffer[0]=2+32; 
					print_str(c3,c2,2+64,char_buffer);
					break;
				case 1:
					char_buffer[0]=4+32; 
					print_str(c4,c1,4+64,char_buffer);
					break;
				case 2:
					char_buffer[0]=5+32; 
					print_str(c3,c2,5+64,char_buffer);
					break;
				case 3:
					char_buffer[0]=8+32; 
					print_str(c4,c1,3+64,char_buffer);
					break;
			}
		}
	}
	sp_UpdateNow();
}

int aux_reduce_rh(void){
	#asm
		ld de,(_asm_int)
		ld hl,22528+(32*2)
		add hl,de
		ld a,0
		ld (hl),a
	#endasm
}

int move(int direction){ //l,r,u,d
	// cx,cy current pos of being
	// icx,icy next pos of being
	int i,attrpos=22528+(32*(cy+4))+cx+4;
	asm_int[0]=attrpos;
	icx=cx;icy=cy;
	
	//print_number1(20,20,2,direction); // test
	switch (direction){
		case 0: //l
			if (cx!=0){
				asm_int[0]=asm_int[0]-1;
				--icx;
			}
			break;
		case 1: //r
			if (cx!=23){
				asm_int[0]=asm_int[0]+1;
				++icx;
			}
			break;
		case 2: //u
			if (cy!=0){
				asm_int[0]=asm_int[0]-32;
				--icy;
			}
			break;
		case 3: //d
			if (cy!=12){
				asm_int[0]=asm_int[0]+32;
				++icy;
			}
			break;
	}
	
	#asm
		ld hl,(_asm_int)
		ld a,(hl)
		ld (_gpit),a
	#endasm
	
	// gpit has the attr of the next position
	// attr 1 = wall (can't walk)
	// attr 2 = heart (can walk and take it)
	// attr 6 = finish (can walk)
	// attr 3 = being (just it's there!)
	// attr 4 = start (can walk)
	// attr 5 = path (can walk)
	
	finish_detected=0;
	//print_number1(20,21,3,heart_rate); //test
	switch (gpit){
		case 2:
			// move and make a sound taking the heart
			heart_decelerates(2);
			sacrifice[0]=0; // did not sacrifice the heart
			break;
		case 2+64:
			// move and make a sound taking the seal
			if (seals[0]<10){
				++seals[0]; // accumulate seals
				aux_print_seals_number();
				if (seals[0]==10){
					levelbu=level;
				}
			}
			aux_creepypasta_show(0); // appears as a signal that something happened
			break;
		case 6:
			// move and detect finish
			aux_peb7();
			finish_detected=1;
			break;
		case 4:
		case 5:
			// path, just walk
			break;
		default:
			// don't move
			icx=cx;
			icy=cy;
			break;
	}
	if (icx!=cx || icy!=cy){
		// has moved
		if ((cx==0)&&(cy==sy)){
			// reprint start
			char_buffer[0]=9+32;
			print_str(4+cx,4+cy,4,char_buffer);
		}else{
			// reprint path
			char_buffer[0]=0+32;
			print_str(4+cx,4+cy,5,char_buffer);
		}
		char_buffer[0]=62+32; // being is at the start position
		print_str(4+icx,4+icy,3,char_buffer);
		cx=icx; //update pos
		cy=icy; //update pos
		sp_UpdateNow();		
	}
	
}

int move_snake(int direction){ //l,r,u,d
	// snake_x[0],snake_y[0] current pos of being
	// icx,icy current pos of a soul
	int i,attrpos=22528+(32*(snake_y[0]+4))+snake_x[0]+4;
	asm_int[0]=attrpos;
	
	// si no soul borro ultimo que no sea 255,255
	// desplazo a derecha
	// meto nueva pos en index 0
	cx=snake_x[0];
	cy=snake_y[0];
	
	//print_number1(20,20,2,direction); // test
	switch (direction){
		case 0: //l
			if (cx>0){
				asm_int[0]=asm_int[0]-1;
				--cx;
			}else{
				asm_int[0]=asm_int[0]+23;
				cx=23;
			}
			break;
		case 1: //r
			if (cx<23){
				asm_int[0]=asm_int[0]+1;
				++cx;
			}else{
				asm_int[0]=asm_int[0]-23;
				cx=0;
			}
			break;
		case 2: //u
			if (cy>0){
				asm_int[0]=asm_int[0]-32;
				--cy;
			}else{
				asm_int[0]=asm_int[0]+(32*12);
				cy=12;
			}
			break;
		case 3: //d
			if (cy!=12){
				asm_int[0]=asm_int[0]+32;
				++cy;
			}else{
				asm_int[0]=asm_int[0]-(32*12);
				cy=0;
			}
			break;
	}
	
	#asm
		ld hl,(_asm_int)
		ld a,(hl)
		ld (_gpit),a
	#endasm
	
	// gpit has the attr of the next position
	// attr 6 = soul (can walk and take it)
	// attr 3 = being (crash with itself!)
	// attr 5 = path (can walk)
	
	//print_number1(20,21,3,heart_rate); //test
	switch (gpit){
		case 6:
			// move and make a sound taking the soul
			++snake_souls;
			if (snake_souls==10){
				finish_detected=1;
			}else if (snake_souls==9){
				i=rand()%4;
				char_buffer[0]=4+32;
				print_str(4+aux_snake_totems_x[i],4+aux_snake_totems_y[i],4+64,char_buffer);
			}
			aux_peb5();
			invoke_soul();
			break;
		case 5:
			// path, just walk
			for (i=9;i>=0;i--){
				if (snake_x[i]!=255){
					// is not empty, clear
					char_buffer[0]=0+32;
					print_str(4+snake_x[i],4+snake_y[i],5,char_buffer);
					snake_x[i]=255;
					snake_y[i]=255;
					break;
				}
			}
			break;
		default:
			// crash with itself or a totem or the seal
			if (gpit==4+64){
				// sacrifice taken
				if (seals[1]<10){
					++seals[1]; // last item was the entity's symbol, you win it
					aux_print_seals_number();
					snake_sacrifice=1;
					if (seals[1]==10){
						levelbu=level;
					}
				}
			}
			finish_detected=1;
			break;
	}
	
	// desplazar a dcha
	for (i=0;i<9;i++){
		snake_x[9-i]=snake_x[8-i];
		snake_y[9-i]=snake_y[8-i];
	}
	snake_x[0]=cx;
	snake_y[0]=cy;
	
	// reprint current status
	char_buffer[0]=62+32; // being
	print_str(4+cx,4+cy,3,char_buffer);
	
	//reprint soul
	char_buffer[0]=32+32; // soul
	print_str(4+icx,4+icy,6,char_buffer);
	
	sp_UpdateNow();		
	
}

int move_sudoku(int direction){ //l,r,u,d
	// cx current index in sudoku
	// icx,icy attr pos of current index
	int i,j,k,l;
	switch (direction){
		case 0: //l
			write_again_symbol();
			if (find_prev_open((cx==0?16:cx),0)==0){
				find_prev_open(16,cx+1);
			}
			break;
		case 1: //r
			write_again_symbol();
			if (find_next_open((cx+1)%16,16)==0){
				find_next_open(0,cx);
			}
			break;
		case 2: //u
			//0,2+64,4+64,5+64,8+64;
			if (sudoku[cx]==0){
				sudoku[cx]=2+64;
			}else if (sudoku[cx]==2+64){
				sudoku[cx]=4+64;
			}else if (sudoku[cx]==4+64){
				sudoku[cx]=5+64;
			}else if (sudoku[cx]==5+64){
				sudoku[cx]=8+64;
			}else{
				sudoku[cx]=0;
			}
			write_again_symbol();
			break;
		case 3: //d
			if (sudoku[cx]==0){
				sudoku[cx]=8+64;
			}else if (sudoku[cx]==2+64){
				sudoku[cx]=0;
			}else if (sudoku[cx]==4+64){
				sudoku[cx]=2+64;
			}else if (sudoku[cx]==5+64){
				sudoku[cx]=4+64;
			}else{
				sudoku[cx]=5+64;
			}
			write_again_symbol();
			break;
	}
	
	// detect sudoku is correct
	i=up(sudoku[0])+up(sudoku[1])+up(sudoku[2])+up(sudoku[3]);
	j=up(sudoku[4])+up(sudoku[5])+up(sudoku[6])+up(sudoku[7]);
	k=up(sudoku[8])+up(sudoku[9])+up(sudoku[10])+up(sudoku[11]);
	l=up(sudoku[12])+up(sudoku[13])+up(sudoku[14])+up(sudoku[15]);
	if ((i==j) && (i==k) && (i==l)){
		i=up(sudoku[0])+up(sudoku[4])+up(sudoku[8])+up(sudoku[12]);
		j=up(sudoku[1])+up(sudoku[5])+up(sudoku[9])+up(sudoku[13]);
		k=up(sudoku[2])+up(sudoku[6])+up(sudoku[10])+up(sudoku[14]);
		l=up(sudoku[3])+up(sudoku[7])+up(sudoku[11])+up(sudoku[15]);
		if ((i==j) && (i==k) && (i==l)){
			i=up(sudoku[0])+up(sudoku[1])+up(sudoku[4])+up(sudoku[5]);
			j=up(sudoku[2])+up(sudoku[3])+up(sudoku[6])+up(sudoku[7]);
			k=up(sudoku[8])+up(sudoku[9])+up(sudoku[12])+up(sudoku[13]);
			l=up(sudoku[10])+up(sudoku[11])+up(sudoku[14])+up(sudoku[15]);
			if ((i==j) && (i==k) && (i==l)){
				finish_detected=1;
				if (sudoku[cx]==5+64){
					if (seals[2]<10){
						++seals[2]; // last item was the entity's symbol, you win it
						aux_print_seals_number();
						if (seals[2]==10){
							levelbu=level;
						}
					}
				}
			}
		}
	}
	
}

int up(int c){
	return (c>64?c:c+64);
}

int draw_backwards_forward(int b_f,int *cx, int *cy){ //b=0 f=1
	while (*cx!=(12-b_f)){
		//0=l,1=u,2=d
		switch (rand()%3){
			case 0:
				if (b_f==0){
					*cx-=2;
				}else{
					*cx+=2;
				}
				//print_str(4+(*cx),4+(*cy),5,char_buffer); 
				print_str(4+(*cx)+(b_f==0?1:-1),4+(*cy),5,char_buffer); 
				break;
			case 1:
				if ((*cy)-2>0){
					*cy-=2;
				}
				//print_str(4+(*cx),4+(*cy),5,char_buffer); 
				print_str(4+(*cx),4+(*cy)+1,5,char_buffer); 
				break;
			case 2:
				if ((*cy)+2<12){
					*cy+=2;
				}
				//print_str(4+(*cx),4+(*cy),5,char_buffer); 
				print_str(4+(*cx),4+(*cy)-1,5,char_buffer); 
				break;
		}
		print_str(4+(*cx),4+(*cy),5,char_buffer); 
		//char_buffer[0]=0+32; // path
	}
}

int adjust(void){
	while (icy!=cy){
		if (icy<cy){
			++icy;
		}else{
			--icy;
		}
		if (sacrifice[0]==1){
			slx=icx;
			sly=icy;
		}
		print_str(4+icx,4+icy,5,char_buffer);
	}
}
	
int accepted_key(unsigned char key_test){
	// 0..9 or A..Z or space ;)
	return ((key_test>=16+32 && key_test<=25+32)||(key_test>=33+32 && key_test<=58+32)||key_test==32);
}

int prepare_screen(unsigned int screen) {
	
	// the following made instead of unpack (screen, 16384);
	// we use this memory buffer below instead of unpacking the main menu
	// directly to the screen memory address because when we unpack 
	// the main menu directly to screen memory address, 
	// specially when the we come from the initial loading screen,
	// we observe blinkings (not enough time to put the whole screen on time)
	// curiously, unpaking the main menu first in an internal buffer and then copying
	// the buffer to the screen memory avoids the blinkings... 
	// I guess is somehow a little bit faster probably due to the 
	// position of the halt command at our ldir routine
	// unpack (screen, screen_buffer);
	// calling directly the unpack asm routine
	
	ram_address [0] = screen;
	ram_destination [0] = (unsigned int)(screen_buffer);
	
	blackout_area();
	
	#asm
		ld hl, (_ram_address)
		ld de, (_ram_destination)
		call depack
	#endasm
	if (((clean_center==1)&&(level%4!=0))||(bonus_up==1)){
		// from 4x4 to 4x27
		// up to 4x16 to 27,16 
		#asm
			ld hl,_screen_buffer+6144+(32*4)+4
			ld a,13
			next_clean_loop: 
				push af
				ld a,23
				call continue_clean
				pop af
				ld bc,9
				add hl,bc
				dec a
				cp a,0
				jp nz,next_clean_loop
			jp end_clean_loop
				continue_clean: 
					ld (hl),0
					cp a,0
					jp z, final_cc
					inc hl
					dec a
					jp continue_clean
				final_cc: ret
			end_clean_loop:
		#endasm
	}
	#asm
		// first attributes, then pixels
		ld hl,_screen_buffer+6144
		ld de,16384+6144
		ld bc,768
		ei
		halt
		ldir
		di
		ld hl,_screen_buffer
		ld de,16384
		ld bc,6144 //6912-768
		ei
		halt
		ldir
		di
	#endasm	
	
}

int to_buffer_screen(unsigned int screen) {
	
	ram_address [0] = screen;
	ram_destination [0] = (unsigned int)(screen_buffer);
	
	#asm
		ld hl, (_ram_address)
		ld de, (_ram_destination)
		call depack
	#endasm	
	
}

int clear_all(void){
	int i;
	for (i=0;i<24;i++){
		print_str(0,i,0,"                                ");
	}
	sp_UpdateNow();
}
	
int show_finale(void){
	int i;
	clear_all();
	for (i=0;i<24;i++){
		asm_int[0]=32*(i+1);
		asm_int_d[0]=16384+6144+((23-i)*32);
		#asm
			ld hl,_screen_buffer+512+544+544+544
			ld bc,(_asm_int)
			//put creepy image
			ld de,(_asm_int_d)
			ei
			halt
			ldir
			di
		#endasm
	}
	aux_fx_lights();
	//espera_pasiva(40);
	#asm
		ld hl,_screen_buffer+512+544+544+544+768
		ld bc,768
		//put creepy image
		ld de,16384+6144
		ei
		halt
		ldir
		di
	#endasm
	#asm
		ld a,8
		call peta_el_beeper
		ld a,0
		call peta_el_beeper
	#endasm	//espera_pasiva(10);
	#asm
		jp 0 // bye!
	#endasm
	
}
