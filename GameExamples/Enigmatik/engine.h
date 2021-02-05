// Motor.h

void Setup_Tileset_Sprites(void){
	int i=-1;
	// Load tileset
	allpurposepuntero = tileset;
	while(i++<255){
		sp_TileArray (i, allpurposepuntero);
		allpurposepuntero += 8;
	}
}

int espera_pasiva (int espera) {
	int i,j = 0;
	for (i = 0; i < espera; ++i) {
		for (j = 0; j < 250; ++j) { 
		}
	}
}

int rand (void) {
	
	unsigned char res;
	
	#asm // 46 bytes
		.rand16
			ld	hl, _seed
			ld	a, (hl)
			ld	e, a
			inc	hl
			ld	a, (hl)
			ld	d, a
			
			;; Ahora DE = [SEED]
						
			ld	a,	d
			ld	h,	e
			ld	l,	253
			or	a
			sbc	hl,	de
			sbc	a, 	0
			sbc	hl,	de
			ld	d, 	0
			sbc	a, 	d
			ld	e,	a
			sbc	hl,	de
			jr	nc,	nextrand
			inc	hl
		.nextrand
			ld	d,	h
			ld	e,	l
			ld	hl, _seed
			ld	a,	e
			ld	(hl), a
			inc	hl
			ld	a,	d
			ld	(hl), a
			
			;; Ahora [SEED] = HL
		
			ld 	hl, _asm_int
			ld	a,	e	
			ld	(hl), a
			inc	hl
			ld	a,	d
			ld	(hl), a
			
			;; Ahora [ASM_INT] = HL
	#endasm
	
	res = asm_int [0];	
	return res;
	
}
