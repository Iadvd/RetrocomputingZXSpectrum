// Pantallas.h
// Carga las pantallas fijas
// Copyleft 2010 The Mojon Twins

extern unsigned char s_title [];

#asm
	._s_title
		BINARY "title_1.bin"
#endasm

extern unsigned char w_title [];

#asm
	._w_title
		BINARY "title_2.bin"
#endasm

