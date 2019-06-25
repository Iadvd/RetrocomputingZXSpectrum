struct sp_UDK keys;
void *joyfunc;				// Puntero a la función de manejo seleccionada.

void *my_malloc(uint bytes) {
   return sp_BlockAlloc(0);
}

void *u_malloc = my_malloc;
void *u_free = sp_FreeBlock;

// Globales muy globalizadas

struct sp_SS *sp_player;
struct sp_SS *sp_moviles [3];
struct sp_Rect spritesClipValues;
struct sp_Rect *spritesClip;

unsigned char enoffs;

// Aux

extern unsigned int asm_int [1];

#ifndef ANDROID_TCP_IP
extern unsigned int asm_int_B [1];
extern unsigned int asm_int_C [1];
extern unsigned int asm_int_D [1];
extern unsigned int asm_int_E [1];
extern unsigned int asm_int_F [1];
extern unsigned int asm_int_dir [36];
extern unsigned int asm_int_mask1 [1];
extern unsigned int asm_int_mask2 [36];
extern unsigned int asm_int_mask3 [36];
extern char pant_msg [33];
#endif

extern unsigned int seed [1];
unsigned char half_life;

#asm
._asm_int
	defw 0
._seed	
	defw 0

#ifndef ANDROID_TCP_IP
._asm_int_B
	defw 0
._asm_int_C
	defw 0
._asm_int_D
	defw 0
._asm_int_E
	defw 0
._asm_int_F
	defw 0
._asm_int_dir //120+
	defw 129,129,130,130,131,131
	defw 129,129,130,130,131,131
	defw 161,161,162,162,163,163
	defw 161,161,162,162,163,163
	defw 193,193,194,194,195,195
	defw 193,193,194,194,195,195
._asm_int_mask1
	defw 0
._asm_int_mask2
	defw 60,3,240,3,240,3
	defw 60,3,60,3,240,3
	defw 60,3,252,3,60,3
	defw 60,3,252,3,60,3
	defw 60,3,252,3,240,3
	defw 60,3,240,3,252,3
._asm_int_mask3
	defw 0,0,32,0,32,2
	defw 32,0,32,0,0,2
	defw 0,0,0,2,0,2
	defw 32,0,0,0,0,2
	defw 32,0,0,0,32,2
	defw 0,0,0,0,0,0
._pant_msg 
defb 'O','B','T','A','I','N','E','D',':',' ',0
defb ' ','C','L','I','V','E',$27,'S',' ',' ',0
defb ' ','T','H','E',' ','D','O','O','R',' ',0
defb ' ','I','S',' ','O','P','E','N','!','!',0
defb ' ','A',' ','B','L','O','C','K','E','D',0
defb ' ',' ',' ','D','O','O','R','!','!',' ',0
#endif
	
#endasm

#define EST_NORMAL 		0
#define EST_PARP 		2
#define EST_MUR 		4
#define sgni(n)			(n < 0 ? -1 : 1)
#define saturate(n)		(n < 0 ? 0 : n)
#define WTOP 1
#define WBOTTOM 2
#define WLEFT 3
#define WRIGHT 4

typedef struct {
	int x, y, cx;
	int vx, vy;
	char g, ax, rx;
	unsigned char salto, cont_salto;
	unsigned char *current_frame, *next_frame;
	unsigned char saltando;
	unsigned char frame, subframe, facing;
	unsigned char estado;
	unsigned char ct_estado;
	unsigned char gotten;
	unsigned char life, objs, keys;
	unsigned char killed;
	unsigned char facing_v, facing_h;
} INERCIA;

INERCIA player;

#define FACING_RIGHT 0
#define FACING_LEFT 2
#define FACING_UP 4
#define FACING_DOWN 6

typedef struct {
	unsigned char base_frame;
	unsigned char frame;
	unsigned char count;
	unsigned char *current_frame, *next_frame;
} ANIMADO;

ANIMADO en_an [3];

// atributos de la pantalla: Contiene información
// sobre qué tipo de tile hay en cada casilla
unsigned char map_attr [150];
unsigned char map_buff [150];

// posición del objeto (hotspot). Para no objeto,
// se colocan a 240,240, que está siempre fuera de pantalla.
unsigned char hotspot_x;
unsigned char hotspot_y;
unsigned char orig_tile;	// Tile que había originalmente bajo el objeto

unsigned char pant_final;

// Flags para scripting
#ifdef ACTIVATE_SCRIPTING
#define MAX_FLAGS 2
unsigned char flags[MAX_FLAGS];
#endif

unsigned char n_pant;

