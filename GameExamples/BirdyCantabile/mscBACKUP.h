// msc.h
// Generado por Mojon Script Compiler de la Churrera
// Copyleft 2011 The Mojon Twins
 
// Script data & pointers
extern unsigned char mscce_0 [];
extern unsigned char mscce_1 [];
extern unsigned char mscce_2 [];
extern unsigned char mscce_3 [];
extern unsigned char mscce_4 [];
extern unsigned char mscce_5 [];
extern unsigned char mscce_6 [];
extern unsigned char mscce_7 [];
extern unsigned char mscce_8 [];
extern unsigned char msccf_0 [];
extern unsigned char msccf_1 [];
extern unsigned char msccf_2 [];
extern unsigned char msccf_3 [];
extern unsigned char msccf_4 [];
extern unsigned char msccf_5 [];
extern unsigned char msccf_6 [];
extern unsigned char msccf_7 [];
extern unsigned char msccf_8 [];
 
unsigned char *e_scripts [] = {
    mscce_0, mscce_1, mscce_2, mscce_3, mscce_4, mscce_5, mscce_6, mscce_7, mscce_8, 0, 0
};
 
unsigned char *f_scripts [] = {
    msccf_1, msccf_2, msccf_3, msccf_4, msccf_0, msccf_5, msccf_6, msccf_7, msccf_8, 0, 0, 0
};
 
#asm
._mscce_0

    defb 0x07, 0xF0, 0xFF, 0x20, 0x06, 0x08, 0x14, 0xFF, 0xFF

._mscce_1

    defb 0x07, 0xF0, 0xFF, 0x20, 0x0C, 0x08, 0x14, 0xFF, 0xFF

._mscce_2

    defb 0x07, 0xF0, 0xFF, 0x20, 0x0A, 0x08, 0x14, 0xFF, 0xFF

._mscce_3

    defb 0x07, 0xF0, 0xFF, 0x20, 0x0B, 0x08, 0x14, 0xFF, 0xFF

._mscce_4

    defb 0x0B, 0xF0, 0xFF, 0x20, 0x07, 0x02, 0x14, 0x20, 0x07, 0x03, 0x15, 0xFF, 0x06, 0x10, 0x01, 0x08
    defb 0xFF, 0xF1, 0xFF, 0xFF

._mscce_5

    defb 0x07, 0xF0, 0xFF, 0x20, 0x03, 0x08, 0x14, 0xFF, 0xFF

._mscce_6

    defb 0x07, 0xF0, 0xFF, 0x20, 0x06, 0x08, 0x14, 0xFF, 0xFF

._mscce_7

    defb 0x07, 0xF0, 0xFF, 0x20, 0x08, 0x08, 0x14, 0xFF, 0xFF

._mscce_8

    defb 0x07, 0xF0, 0xFF, 0x20, 0x03, 0x08, 0x14, 0xFF, 0xFF

._msccf_0

    defb 0x10, 0x21, 0x6C, 0x84, 0x22, 0x30, 0x40, 0x40, 0xFF, 0x10, 0x01, 0x01, 0x41, 0x01, 0xE0, 0x07
    defb 0xFF, 0x06, 0x10, 0x01, 0x08, 0xFF, 0xF1, 0xFF, 0xFF

._msccf_1

    defb 0x0A, 0x21, 0x51, 0x6F, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_2

    defb 0x0A, 0x21, 0xB1, 0xCF, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_3

    defb 0x0A, 0x21, 0x87, 0xA5, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_4

    defb 0x0A, 0x21, 0x96, 0xB4, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_5

    defb 0x0A, 0x21, 0x1E, 0x3C, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_6

    defb 0x0A, 0x21, 0x51, 0x6F, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_7

    defb 0x0A, 0x21, 0x69, 0x87, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_8

    defb 0x0A, 0x21, 0x1E, 0x3C, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

#endasm
 
unsigned char *script;
 
void msc_init_all () {
    unsigned char i;
    for (i = 0; i < MAX_FLAGS; i ++)
        flags [i] = 0;
}
 
unsigned char read_byte () {
    unsigned char c;
    c = script [0];
    script ++;
    return c;
}
 
unsigned char read_vbyte () {
    unsigned char c;
    c = read_byte ();
    if (c & 128) return flags [c & 127];
    return c;
}
 
// Ejecutamos el script apuntado por *script:
unsigned char run_script () {
    unsigned char res = 0;
    unsigned char terminado = 0;
    unsigned char continuar = 0;
    unsigned char x, y, n, m, c;
    unsigned char *next_script;
	unsigned char npantfix;
 
    if (script == 0)
        return; 
 
    script_something_done = 0;
 
    while (1) {
        c = read_byte ();
        if (c == 0xFF) break;
        next_script = script + c;
        terminado = continuar = 0;
        while (!terminado) {
            c = read_byte ();
            switch (c) {
                case 0x10:
                    // IF FLAG x = n
                    // Opcode: 10 x n
                    x = read_vbyte ();
                    n = read_vbyte ();
                    if (flags [x] != n)
                        terminado = 1;
                    break;
                case 0x21:
                    // IF PLAYER_IN_X x1, x2
                    // Opcode: 21 x1 x2
                    x = read_byte ();
                    y = read_byte ();
                    if (!((player.x >> 6) >= x && (player.x >> 6) <= y))
                        terminado = 1;
                    break;
                case 0x22:
                    // IF PLAYER_IN_Y y1, y2
                    // Opcode: 22 y1 y2
                    x = read_byte ();
                    y = read_byte ();
                    if (!((player.y >> 6) >= x && (player.y >> 6) <= y))
                        terminado = 1;
                    break;
                case 0x40:
                     // IF PLAYER_HAS_OBJECTS
                     // Opcode: 40
                     if (player.objs == 0)
                         terminado = 1;
                     break;
                case 0xF0:
                     // IF TRUE
                     // Opcode: F0
                     break;
                case 0xFF:
                    // THEN
                    // Opcode: FF
                    terminado = 1;
                    continuar = 1;
                    script_something_done = 1;
                    break;
            }
        }
        if (continuar) {
            terminado = 0;
            while (!terminado) {
                c = read_byte ();
                switch (c) {
                    case 0x10:
                        // INC FLAG x, n
                        // Opcode: 10 x n
                        x = read_vbyte ();
                        n = read_vbyte ();
						flags [x] += n;
                        break;
                    case 0x20:
                        // SET TILE (x, y) = n
                        // Opcode: 20 x y n
                        x = read_vbyte ();
                        y = read_vbyte ();
                        n = read_vbyte ();
                        map_buff [x + (y << 4) - y] = n;
                        map_attr [x + (y << 4) - y] = comportamiento_tiles [n];
                        draw_coloured_tile (VIEWPORT_X + x + x, VIEWPORT_Y + y + y, n);
                        break;
                    case 0x41:
                        // DEC OBJECTS n
                        // Opcode: 41 n
                        n = read_vbyte ();
                        player.objs -= n;
                        draw_objs ();
                        break;
                    case 0xE0:
						// Show birdy always
						x = player.x >> 6;
						y = player.y >> 6;
						sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);
						sp_UpdateNow();
								
						// SOUND n
                        // Opcode: E0 n
                        n = read_vbyte ();
						if (n==0){
								peta_el_beeper (7);
								sp_UpdateNow();
								npantfix = n_pant;
								if (npantfix>4){
									npantfix=npantfix-1;
								}
								switch (in_room_is_score_n[npantfix]){
									case 0:
										if (concert_song==0){
											#asm
												; Music generated by beepola
												call musicstartConcert0
											#endasm	
										}
										else{
											#asm
												; Music generated by beepola
												call musicstartConcertB0
											#endasm	
										}
										print_str (11, 22, 122, "1ST PAGE");
										break;
									case 1:
										if (concert_song==0){
											#asm
												; Music generated by beepola
												call musicstartConcert1
											#endasm	
										}
										else{
											#asm
												; Music generated by beepola
												call musicstartConcertB1
											#endasm	
										}
										print_str (11, 22, 122, "2ND PAGE");
										break;
									case 2:
										if (concert_song==0){
											#asm
												; Music generated by beepola
												call musicstartConcert2
											#endasm	
										}
										else{
											#asm
												; Music generated by beepola
												call musicstartConcertB2
											#endasm	
										}
										print_str (11, 22, 122, "3RD PAGE");
										break;	
									case 3:
										if (concert_song==0){
											#asm
												; Music generated by beepola
												call musicstartConcert3
											#endasm	
										}
										else{
											#asm
												; Music generated by beepola
												call musicstartConcertB3
											#endasm	
										}
										print_str (11, 22, 122, "4TH PAGE");
										break;
									case 4:
										if (concert_song==0){
											#asm
												; Music generated by beepola
												call musicstartConcert4
											#endasm	
										}
										else{
											#asm
												; Music generated by beepola
												call musicstartConcertB4
											#endasm	
										}
										print_str (11, 22, 122, "5TH PAGE");
										break;
									case 5:
										if (concert_song==0){
											#asm
												; Music generated by beepola
												call musicstartConcert5
											#endasm	
										}
										else{
											#asm
												; Music generated by beepola
												call musicstartConcertB5
											#endasm	
										}
										print_str (11, 22, 122, "6TH PAGE");
										break;
									case 6:
										if (concert_song==0){
											#asm
												; Music generated by beepola
												call musicstartConcert6
											#endasm	
										}
										else{
											#asm
												; Music generated by beepola
												call musicstartConcertB6
											#endasm	
										}
										print_str (11, 22, 122, "7TH PAGE");
										break;
									case 7:
										if (concert_song==0){
											#asm
												; Music generated by beepola
												call musicstartConcert7
											#endasm	
										}
										else{
											#asm
												; Music generated by beepola
												call musicstartConcertB7
											#endasm	
										}
										print_str (11, 22, 122, "8TH PAGE");										
										break;
									else: 
										break;
								}
								
								if (in_room_is_score_n[npantfix]==current_taken+1){
									// If the score in this room is exactly the
									// one in the correct order to be taken then 
									// little birds will like it
									print_str (11, 21, 122, "GOOD!THE");
									peta_el_beeper (10); //"oukei..." 
									#asm
										di
									#endasm
									happiness = 1;
								}else{
									// If the score in this room is not the
									// one in the correct order to be taken then 
									// little birds will not like it
									print_str (11, 21, 122, "NOPE!THE");
									peta_el_beeper (6); //"no,no..."
									#asm
										di
									#endasm
									happiness = 0;
								}
						}else{
							peta_el_beeper (n);
							#asm
								di
							#endasm
						}
						break;
                    case 0xF1:
                        script_result = 1;
                        terminado = 1;
                        break;
                    case 0xFF:
                        terminado = 1;
                        break;
                }
            }
        }
        script = next_script;
    }
 
    return res;
}
