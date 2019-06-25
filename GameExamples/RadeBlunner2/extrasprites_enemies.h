// Extrasprites.h
// Contiene sprites extra para el modo de matar enemigos de la churrera
// Sólo se incluirá (tras los sprites) si se define PLAYER_KILLS_ENEMIES
// Copyleft 2010 The Mojon Twins

// Frames extra por si se pueden eliminar los enemigos:


extern unsigned char sprite_11Bis_a []; 
extern unsigned char sprite_11Bis_b []; 
//extern unsigned char sprite_11Bis_c []; 
extern unsigned char sprite_12Bis_a []; 
extern unsigned char sprite_12Bis_b []; 
//extern unsigned char sprite_12Bis_c []; 
extern unsigned char sprite_13Bis_a []; 
extern unsigned char sprite_13Bis_b []; 
//extern unsigned char sprite_13Bis_c []; 
extern unsigned char sprite_14Bis_a []; 
extern unsigned char sprite_14Bis_b []; 
//extern unsigned char sprite_14Bis_c []; 

#asm 
    ._sprite_11Bis_a
        defb 0, 224
        defb 13, 128
        defb 51, 0
        defb 67, 0
        defb 131, 24
        defb 3, 48
        defb 7, 224
        defb 15, 192
        defb 31, 128
        defb 55, 0
        defb 111, 0
        defb 95, 0
        defb 255, 0
        defb 255, 0
        defb 199, 0
        defb 195, 0
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_11Bis_b
        defb 0, 3
        defb 216, 1
        defb 228, 0
        defb 226, 0
        defb 225, 8
        defb 224, 4
        defb 240, 3
        defb 248, 1
        defb 252, 0
        defb 238, 0
        defb 247, 0
        defb 251, 0
        defb 255, 0
        defb 255, 0
        defb 135, 0
        defb 7, 0
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 /*
    ._sprite_11Bis_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 */
    ._sprite_12Bis_a
        defb 0, 192
        defb 27, 128
        defb 39, 0
        defb 71, 0
        defb 135, 16
        defb 7, 32
        defb 15, 192
        defb 31, 128
        defb 63, 0
        defb 119, 0
        defb 239, 0
        defb 223, 0
        defb 255, 0
        defb 255, 0
        defb 225, 0
        defb 224, 0
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_12Bis_b
        defb 0, 7
        defb 176, 1
        defb 204, 0
        defb 194, 0
        defb 193, 24
        defb 192, 12
        defb 224, 7
        defb 240, 3
        defb 248, 1
        defb 236, 0
        defb 246, 0
        defb 250, 0
        defb 255, 0
        defb 255, 0
        defb 227, 0
        defb 195, 0
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 /*
    ._sprite_12Bis_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
*/
    ._sprite_13Bis_a
        defb 0, 248
        defb 3, 192
        defb 29, 128
        defb 45, 128
        defb 48, 0
        defb 192, 0
        defb 48, 0
        defb 243, 0
        defb 242, 0
        defb 112, 0
        defb 152, 0
        defb 103, 0
        defb 56, 0
        defb 31, 128
        defb 3, 192
        defb 0, 248
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_13Bis_b
        defb 0, 31
        defb 192, 3
        defb 184, 1
        defb 180, 1
        defb 12, 0
        defb 99, 0
        defb 60, 0
        defb 63, 0
        defb 63, 0
        defb 62, 0
        defb 57, 0
        defb 226, 0
        defb 12, 0
        defb 248, 1
        defb 192, 3
        defb 0, 31
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 /*
    ._sprite_13Bis_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 */
    ._sprite_14Bis_a
        defb 0, 248
        defb 3, 192
        defb 29, 128
        defb 45, 128
        defb 48, 0
        defb 198, 0
        defb 60, 0
        defb 252, 0
        defb 252, 0
        defb 124, 0
        defb 156, 0
        defb 71, 0
        defb 48, 0
        defb 31, 128
        defb 3, 192
        defb 0, 248
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_14Bis_b
        defb 0, 31
        defb 192, 3
        defb 184, 1
        defb 180, 1
        defb 12, 0
        defb 3, 0
        defb 12, 0
        defb 207, 0
        defb 79, 0
        defb 14, 0
        defb 25, 0
        defb 230, 0
        defb 28, 0
        defb 248, 1
        defb 192, 3
        defb 0, 31
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 /*
    ._sprite_14Bis_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 */
#endasm

