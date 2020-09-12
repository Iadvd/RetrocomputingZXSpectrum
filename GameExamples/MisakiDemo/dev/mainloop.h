// mainloop.h

// Churrera copyleft 2011 by The Mojon Twins.

void do_game (void) {
	unsigned int i;
	unsigned char x,y;
	
	// save intro image
	#asm
		ld hl,22528
		ld de,_first_image
		ld bc,768
		ldir
	#endasm
	
	// splib2 initialization
	sp_Initialize (7, 0);
	
	#asm
		di
	#endasm
	
	Setup_Tileset_Sprites();
	
	while (1){
		
		// 1. Intro image effect BEGIN
		gpit=232;
		set_tempo();
		#asm
			ld hl,_first_image
			ld de,22528
			ld bc,768
			ei
			halt
			ldir
			di
			call musicstart
		#endasm	
		for (i=0;i<63;i++){
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
				call nextnote
			#endasm
		}
		// 1. Intro image effect END
		
		blackout_area();
		sp_UpdateNow();
		
		// 2. Lluvia/matrix effect hiragana BEGIN
		gpit=234;
		set_tempo();
		main_looper=0;
		while (main_looper<64){
			#asm
				call nextnote
			#endasm
			//  mover abajo
			for (i=0;i<30;i++){
				char_buffer[0]=lines_char[i];
				print_str(lines_x[i],lines_y[i],1,char_buffer);
				++lines_y[i];
				if (lines_y[i]==24){
					lines_y[i]=0;
					lines_char[i]=(rand()%64)+32;
				}
				print_str(lines_x[i],lines_y[i],68,char_buffer);
			}
			++main_looper;
			sp_UpdateNow();
		}
		// 2. Lluvia/matrix effect hiragana END
		
		
		// 3. Foco hiragana BEGIN
		gpit=230;
		set_tempo();
		prepare_screen((unsigned int) (s_title),0);
		main_looper=0;
		x=2;
		y=2;
		while (main_looper<(64*2)){
			#asm
				call nextnote
			#endasm
			do_focus_things(x,y);
			do_focus_things(31-x,23-y);
			++main_looper;
			if (main_looper%2==0){
				switch(rand()%6){
					case 0: //lu
						--x;
						--y;
						break;
					case 1: //ru
					case 2:
						++x;
						--y;
						break;
					case 3: //ld
						--x;
						++y;
						break;
					case 4: //rd
					case 5:
						++x;
						++y;
						break;
				}
				if (x<2){
					x=2;
				}
				if (x>29){
					x=29;
				}
				if (y<2){
					y=2;
				}
				if (y>21){
					y=21;
				}
			}
		}
		// 3. Foco hiragana END
		
		// 4. Ejemplo de conversacion juego BEGIN
		prepare_screen((unsigned int) (w_title),1);
		main_looper=0;
		while (main_looper<64*2){
			#asm
				call nextnote
			#endasm
			if (main_looper==0){
				draw_coloured_tile(1,1,0);
				print_str(4,1,2,action_texts[0]);
				print_str(4,2,2,action_texts[1]);
				sp_UpdateNow();
			}
			if (main_looper==32){
				draw_coloured_tile(29,5,1);
				print_str(1,5,3,action_texts[2]);
				print_str(1,6,3,action_texts[3]);
				sp_UpdateNow();
			}
			if (main_looper==64){
				draw_coloured_tile(7,11,2);
				print_str(10,11,4,action_texts[4]);
				print_str(10,12,4,action_texts[5]);
				sp_UpdateNow();
			}
			if (main_looper==96){
				draw_coloured_tile(29,15,3);
				print_str(14,15,5,action_texts[6]);
				print_str(14,16,5,action_texts[7]);
				sp_UpdateNow();
			}
			++main_looper;
		}
		// 4. Ejemplo de conversacion juego BEGIN
		
		blackout_area();
		sp_UpdateNow();
	}
			
}

int set_tempo(void){
	#asm
		ld a,(_gpit)
		ld hl,PAT0
		ld (hl),a
		ld hl,PAT1
		ld (hl),a
		ld hl,PAT2
		ld (hl),a
		ld hl,PAT3
		ld (hl),a
	#endasm
}
		
int do_focus_things(int x,int y){
	asm_int[0]=22528+(y*32)+x-2;
	focus();
	++asm_int[0];
	focus();
	++asm_int[0];
	focus();
	++asm_int[0];
	focus();
	++asm_int[0];
	focus();
	
	asm_int[0]=22528+((y-1)*32)+x-1;
	focus();
	++asm_int[0];
	focus();
	++asm_int[0];
	focus();
	++asm_int[0];
	
	asm_int[0]=22528+((y-2)*32)+x;
	focus();
	++asm_int[0];
	
	asm_int[0]=22528+((y+1)*32)+x-1;
	focus();
	++asm_int[0];
	focus();
	++asm_int[0];
	focus();
	++asm_int[0];
	
	asm_int[0]=22528+((y+2)*32)+x;
	focus();
	++asm_int[0];
}
				
				
int focus(void){
	#asm
		// poner pos actual color
		ld hl,(_asm_int)
		ld a,(hl)
		add 0
		cp 0
		jp nz,compare1
		ld a,4
		ld (hl),a
		jp endproc
		compare1:
		cp 1
		jp nz,compare4
		ld a,4
		ld (hl),a
		jp endproc
		compare4:
			add 0
			cp 4
			jp nz, endproc
			ld a,1
			ld (hl),a
		endproc:
	#endasm	
}

int prepare_screen(unsigned int screen, int prev_attrs) {
	
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
		ld a,0
		ld (23693),a 
		call 3503 
		ld hl, (_ram_address)
		ld de, (_ram_destination)
		call depack
	#endasm
	
	if (prev_attrs==1){
		#asm
			ld hl,_screen_buffer
			ld de,16384
			ld bc,6912
			ei
			halt
			ldir
			di
		#endasm	
	}else{
		// first attributes, then pixels
		#asm
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
	
}
