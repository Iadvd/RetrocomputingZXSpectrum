// Pantallas.h
// Carga las pantallas fijas
// Copyleft 2010 The Mojon Twins

extern unsigned char s_title [];
extern unsigned char s_marco [];
extern unsigned char s_ending [];

#asm
	._s_title
#ifdef ANDROID_TCP_IP
		BINARY "title_androidjoystick.bin"
#else
		BINARY "title.bin"
#endif
	._s_marco
#endasm
#ifndef DIRECT_TO_PLAY
#asm
		BINARY "marco.bin"
#endasm
#endif
#asm
	._s_ending
		BINARY "ending.bin"
#endasm

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
