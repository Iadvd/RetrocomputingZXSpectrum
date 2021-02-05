// Printing functions

// Función que pinta un tile para mapas packed

// uses special_color
int draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t) {
	unsigned char k;
	
	t = 64 + (t << 2);
	allpurposepuntero = (unsigned char *) &tileset [2048 + t];
	// tileset has 2048 tiles and their 256 attr values
	#asm 
		ld a,0
		ld (_gpit),a
	#endasm
	while(gpit<4){
		sp_PrintAtInv (y+(gpit<2?0:1), x+(gpit%2), allpurposepuntero [gpit], t+(gpit++));
	}
	
}

int print_str (unsigned char x, unsigned char y, unsigned char c, unsigned char *s) {
	while (*s)	{
		sp_PrintAtInv (y, x ++, c, (*s ++) - 32);
	}
}

// writes from right to left
void print_number1(unsigned char x, unsigned char y, unsigned char c, unsigned int number) {
	if (number>0){
		sp_PrintAtInv (y, x, c, 16 + (number%10));
		print_number1(x-1,y,c,number/10);
	}
}

void blackout_area () {
	// blackens gameplay area for LEVEL XX display
	#asm
		ld hl, 22528
		ld bc,768
		loop_bout:
			ld (hl),0
			inc hl
			dec bc
			ld a,b
			add 0
			jp nz,loop_bout
			ld a,c
			add 0
			jp nz,loop_bout
			ret
	#endasm
}
