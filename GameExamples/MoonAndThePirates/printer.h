// Printing functions

void attr (char x, char y) {
	return map_attr [x + (y << 4) - y]; //bona fide
}

// Función que pinta un tile para mapas packed
int draw_coloured_tile_in_viewport (unsigned char x, unsigned char y, unsigned char t) {
	draw_coloured_tile (VIEWPORT_X+x, VIEWPORT_Y+y, t);
}

int draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t) {
	unsigned char *pointer;
	unsigned char i,j,k;
	
		t = 64 + (t << 2);
		pointer = (unsigned char *) &tileset [2048 + t];
		// tileset has 2048 tiles and their 256 attr values
		for (i=0;i<4;++i){
			j=y+(i<2?0:1);
			if (mirror_tile==1 && which_face[0]==1){
				k=x+1-(i%2);
				// sp_PrintAtInv (scr_y,scr_x,attrs,tile_no-alrrady loaded with sp_TileArray)
				// Step 2: Print inverted tiles
				sp_PrintAtInv (j, k, pointer [i], t+i);
			}else{
				sp_PrintAtInv (j, x+(i%2), pointer [i], t+i);
			}
		}
		if (mirror_tile==1 && which_face[0]==1){
			// Special case: move face of characters by code
			// because we are using the fixed tiles for other purposes
			// Step 1: Invert bits
			mirror_tile_scr();
			was_mirrored=1;
			sp_UpdateNow();	
		}else if (mirror_tile==1){
			// Special case: move face of characters by code
			// Step 3: Invert bits again (back to normal pos)
			check_and_restore();
		}
}

int check_and_restore(void){
	if (was_mirrored==1){
		// Special case: move face of characters by code
		// Step 3: Invert bits again (back to normal pos)
		was_mirrored=0;
		mirror_tile_scr();
		sp_UpdateNow();	
	}
}

// Mirror horizontally the tiles (e.g. the face of a character) inside the tileset array
int mirror_tile_scr(void){
	// in my case the characters are in the array starting from this position 180*8=1440
	//int starting_pos = tileset+1440+((n_pant-2)*32);
	int starting_pos = tileset+1376+32*n_pant;
	asm_int_b[0]=(unsigned char) starting_pos;      // LO
	asm_int_c[0]=(unsigned char) (starting_pos>>8); // HI
	#asm
		ld a,(_asm_int_b)
		ld e,a 		// beginning of the desired tile LO
		ld a,(_asm_int_c)
		ld d,a 		// beginning of the desired tile HI
		ld a,32 	//4 tiles of 8 bytes each... implies mirroring 32 bytes
		next_byte:
			ld c,a
			ld b,8
			ld a,(de) 
			ld l,a
			revloop:
				rl l
				rra
				djnz revloop
			//ld a,0 //test
			ld (de),a
			inc de
			ld a,c
			dec a
			jp nz,next_byte
	#endasm
}

void print_number1(unsigned char x, unsigned char y, unsigned char c, unsigned char number) {
	sp_PrintAtInv (y, x + 1, c, 16 + number);
}

int print_str_in_viewport(unsigned char x, unsigned char y, unsigned char c, unsigned char *s) {
	print_str (VIEWPORT_X+x, VIEWPORT_Y+y, c, s);
}

int print_str (unsigned char x, unsigned char y, unsigned char c, unsigned char *s) {
	while (*s)	{
		sp_PrintAtInv (y, x ++, c, (*s ++) - 32);
	}
}

void blackout_area () {
	// blackens gameplay area
	//8800H=22528
	#asm
		ld e,00
		ld d,88
		ld b, 6;
	.bal1
		push bc
		push de
		pop hl
		ld	(hl), 0
		inc de
		ld bc, 29
		ldir
		inc de
		inc de
		pop bc
		djnz bal1	
	#endasm
}


void blackout (void) {
	#asm
		ld hl, 22528
		ld (hl), 0
		push hl
		pop de
		inc de
		ld bc, 767
		ldir
	#endasm
}

