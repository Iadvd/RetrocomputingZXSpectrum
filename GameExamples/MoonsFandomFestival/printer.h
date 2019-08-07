// Printing functions

void attr (char x, char y) {
	return (x < 0 || y < 0 || x > 14 || y > 9)? 0:map_attr [x + (y << 4) - y];
}

// Función que pinta un tile para mapas packed
void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t) {
	unsigned char *pointer;
	int i;
	
		t = 64 + (t << 2);
		pointer = (unsigned char *) &tileset [2048 + t];
		for (i=0;i<4;i++){
			sp_PrintAtInv (y+(i<2?0:1), x+(i%2), pointer [i], t+i);
		}
		
}

void print_number1(unsigned char x, unsigned char y, unsigned char c, unsigned char number) {
	sp_PrintAtInv (y, x + 1, c, 16 + number);
}

void print_str (unsigned char x, unsigned char y, unsigned char c, unsigned char *s) {
	while (*s)	{
		sp_PrintAtInv (y, x ++, c, (*s ++) - 32);
	}
}

void blackout_area () {
	// blackens gameplay area
	asm_int [0] = 22528;// + 32 * VIEWPORT_Y + VIEWPORT_X;
	#asm
		ld	hl, _asm_int
		ld	a, (hl)
		ld	e, a
		inc	hl
		ld	a, (hl)
		ld	d, a
		
		ld b, 6;//20
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

