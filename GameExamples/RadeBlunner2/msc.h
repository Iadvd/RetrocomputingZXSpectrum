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
extern unsigned char msccf_0 [];
extern unsigned char msccf_1 [];
extern unsigned char msccf_2 [];
extern unsigned char msccf_3 [];
 
unsigned char *e_scripts [] = {
    mscce_0, 0, mscce_1, mscce_2, 0, mscce_3, 0, mscce_4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, mscce_5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, mscce_6, mscce_7, 0, 0, 0, 0
};
 
unsigned char *f_scripts [] = {
    0, 0, 0, msccf_0, 0, 0, 0, msccf_1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, msccf_2, msccf_3, 0, 0, 0, 0, 0
};
 
#asm
._mscce_0

    defb 0x0F, 0xF0, 0xFF, 0x20, 0x00, 0x00, 0x1A, 0x20, 0x01, 0x00, 0x19, 0x20, 0x02, 0x00, 0x1A, 0xFF
    defb 0xFF

._mscce_1

    defb 0x0B, 0xF0, 0xFF, 0x20, 0x06, 0x02, 0x15, 0x20, 0x08, 0x02, 0x15, 0xFF, 0xFF

._mscce_2

    defb 0x0B, 0xF0, 0xFF, 0x20, 0x08, 0x03, 0x15, 0x20, 0x08, 0x05, 0x14, 0xFF, 0xFF

._mscce_3

    defb 0x13, 0xF0, 0xFF, 0x20, 0x0D, 0x00, 0x19, 0x20, 0x0E, 0x00, 0x1A, 0x20, 0x0D, 0x01, 0x1B, 0x20
    defb 0x0E, 0x01, 0x1C, 0xFF, 0x06, 0x10, 0x01, 0x11, 0xFF, 0xF1, 0xFF, 0xFF

._mscce_4

    defb 0x0B, 0xF0, 0xFF, 0x20, 0x0A, 0x04, 0x15, 0x20, 0x0A, 0x06, 0x14, 0xFF, 0xFF

._mscce_5

    defb 0x0B, 0xF0, 0xFF, 0x20, 0x06, 0x03, 0x15, 0x20, 0x08, 0x03, 0x15, 0xFF, 0xFF

._mscce_6

    defb 0x0B, 0xF0, 0xFF, 0x20, 0x02, 0x06, 0x15, 0x20, 0x02, 0x08, 0x14, 0xFF, 0xFF

._mscce_7

    defb 0x0B, 0xF0, 0xFF, 0x20, 0x05, 0x06, 0x15, 0x20, 0x05, 0x08, 0x14, 0xFF, 0xFF

._msccf_0

    defb 0x0A, 0x21, 0x71, 0x8F, 0x22, 0x51, 0x6F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_1

    defb 0x0A, 0x21, 0x91, 0xAF, 0x22, 0x51, 0x6F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_2

    defb 0x0A, 0x21, 0x11, 0x2F, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

._msccf_3

    defb 0x0A, 0x21, 0x41, 0x5F, 0x22, 0x71, 0x8F, 0xFF, 0xE0, 0x00, 0xFF, 0xFF

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
 
void put_tile(unsigned char x, unsigned char y, unsigned char n){
	map_buff [x + (y << 4) - y] = n;
	map_attr [x + (y << 4) - y] = comportamiento_tiles [n];
	draw_coloured_tile (VIEWPORT_X + x + x, VIEWPORT_Y + y + y, n);
}

// Ejecutamos el script apuntado por *script:
unsigned char run_script () {
    unsigned char res = 0;
    unsigned char terminado = 0;
    unsigned char continuar = 0;
    unsigned char x, y, n, m, c;
    unsigned char *next_script;
 
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
                    case 0x20:
                        // SET TILE (x, y) = n
                        // Opcode: 20 x y n
						x = read_vbyte ();
                        y = read_vbyte ();
                        n = read_vbyte ();
						
						switch (n_pant) {
							case 0:
								put_tile(0,6,26);
								put_tile(1,6,25);
								put_tile(2,6,26);
								put_tile(0,7,31);
								put_tile(1,7,31);
								put_tile(2,7,30);
								put_tile(1,8,31);
								break;
							case 2:
								// Follow the marks screen A
								put_tile(6,2,n+ojo_izA_pos);
								put_tile(8,2,n+ojo_dcA_pos);
								break;
							case 18:
								// Follow the marks screen B
								put_tile(6,3,n+ojo_izB_pos);
								put_tile(8,3,n+ojo_dcB_pos);
								break;
							case 3:
								// Switch vault
								put_tile(8,4,21+ojo_dcA_pos_switch);
								put_tile(8,6,20);
								break;
							case 7:
								// Switch vault
								put_tile(10,4,21+ojo_izA_pos_switch);
								put_tile(10,6,20);
								break;
							case 32:
								// Switch vault
								put_tile(2,6,21+ojo_izB_pos_switch);
								put_tile(2,8,20);
								break;
							case 33:
								// Switch vault
								put_tile(5,6,21+ojo_dcB_pos_switch);
								put_tile(5,8,20);
								break;
						};
                    case 0xE0:
                        // SOUND n
                        // Opcode: E0 n
                        
						n = read_vbyte ();
						switch (n) {
							case 0:
								switch (n_pant) {
									case 3: 
										// Switch vault
										ojo_dcA_pos_switch=(ojo_dcA_pos_switch+1)%4;
										put_tile(8,4,21+ojo_dcA_pos_switch);
										peta_el_beeper (1); 
										break;
									case 7: 
										// Switch vault
										ojo_izA_pos_switch=(ojo_izA_pos_switch+1)%4;
										put_tile(10,4,21+ojo_izA_pos_switch);
										peta_el_beeper (1); 
										break;
									case 32: 
										// Switch vault
										ojo_izB_pos_switch=(ojo_izB_pos_switch+1)%4;
										put_tile(2,6,21+ojo_izB_pos_switch);
										peta_el_beeper (1); 
										break;
									case 33: 
										// Switch vault
										ojo_dcB_pos_switch=(ojo_dcB_pos_switch+1)%4;
										put_tile(5,6,21+ojo_dcB_pos_switch);
										peta_el_beeper (1); 
										break;
								};
						};
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
