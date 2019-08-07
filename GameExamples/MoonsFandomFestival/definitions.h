struct sp_UDK keys;
void *joyfunc;				// Puntero a la funciÛn de manejo seleccionada.

void *my_malloc(uint bytes) {
   return sp_BlockAlloc(0);
}

void *u_malloc = my_malloc;
void *u_free = sp_FreeBlock;

// Globales muy globalizadas

struct sp_SS *sp_player;
struct sp_SS *sp_playerB;
struct sp_SS *sp_moviles [3];
struct sp_SS *sp_movilesB [3];
struct sp_Rect spritesClipValues;
struct sp_Rect *spritesClip;

unsigned char enoffs;

#define EST_NORMAL 		0
#define WBOTTOM 2
#define WLEFT 3
#define WRIGHT 4

typedef struct {
	int x, y;
	int vx, vy;
	unsigned char *current_frame, *next_frame;
	unsigned char frame, subframe, facing;
	unsigned char estado;
} INERCIA;

INERCIA player, playerB;

typedef struct {
	unsigned char base_frame;
	unsigned char frame;
	unsigned char count;
	unsigned char *current_frame, *next_frame;
} ANIMADO;

ANIMADO en_an [3], en_anB [3];

// atributos de la pantalla: Contiene informaciÛn
// sobre quÅEtipo de tile hay en cada casilla
unsigned char map_attr [90];
unsigned char map_buff [90];
unsigned char n_pant,n_pant_precalc;

// Aux

extern unsigned int asm_int [1];
extern unsigned int seed [1];
//extern unsigned int values_col [11];
//extern unsigned int values_row [11];
extern unsigned int values_col_menu [11];
extern unsigned int values_row_menu [11];
extern unsigned int values_color_menu [11];
extern unsigned int perso_face_pos_x [8];
extern unsigned int perso_face_pos_y [8];
extern unsigned int perso_face_tile [8];
extern unsigned int interact_z [32];
extern unsigned int interact_value [32];
extern unsigned int knowledge_characters_1 [12];
extern unsigned int knowledge_characters_2 [30];
extern unsigned int knowledge_characters_3 [30];
extern unsigned int booths_texts_pos [16];
extern unsigned int common_fan_items [24];

#asm
._asm_int
	defw 0
	
._seed	
	defw 0	

//._values_col
//	defw 7,0,6,11,4,4,5,3,7,2,1
//._values_row
//	defw 0,7,8,10,12,13,14,15,17,19,21

._values_col_menu
	defw 4,6,6,6,6,6,17,6,5,24
._values_row_menu
	defw 0,8,10,12,14,16,16,18,20,20
._values_color_menu
	defw colorM1,colorM2,colorM3,colorM4
#ifdef ANDROID_TCP_IP
	defw colorM5
#else
	defw 0
#endif
	defw colorM3,colorM3,colorM2,colorM5,colorM3

._perso_face_pos_x
	defw 0,14,18,20,8,4,16,8
._perso_face_pos_y
	defw 24,6,4,6,0,12,24,20
._perso_face_tile
	defw 20,24,8,10,16,24,6,24
._booths_texts_pos
	defw 3,13,13,15,5,3,11,3
	defw 10,11,14,15
	defw colorM2,colorM1,colorM3,colorM3
._common_fan_items
	defw 24,20,16 // special use: in 10 will be hamburguer
	defw 6,24,18
	defw 4,8,14
	defw 6,10,16
	defw 0,16,12
	defw 12,24,8
	defw 24,6,12
	defw 20,24,4
	
._interact_z
	defw 0,8,10,12
	defw 3,7,9,12
	defw 2,4,7,9
	defw 3,5,8,10
	defw 0,4,6,8
	defw 2,4,6,12
	defw 3,6,8,12
	defw 2,4,10,12
._interact_value
	defw 0,3,4,1
	defw 1,2,3,4
	defw 1,4,3,5
	defw 1,4,3,6
	defw 1,7,3,4
	defw 8,3,1,4
	defw 4,3,10,1
	defw 3,11,1,4

._knowledge_characters_1
	defw 0,0,0,0,0,0 //given correct pocket thing
	defw 0,0,0,0,0,0 //given correct icon item
._knowledge_characters_2  //given knowledge
	defw 0,0,0,0,0
	defw 0,0,0,0,0
	defw 0,0,0,0,0
	defw 0,0,0,0,0
	defw 0,0,0,0,0
	defw 0,0,0,0,0
._knowledge_characters_3  //given knowledge
	defw 8,16,22,26,32
	defw 0,2,38,40,42
	defw 4,6,44,46,50
	defw 28,30,48,52,54
	defw 12,14,56,58,60
	defw 34,36,62,64,66

#endasm

//################ TEXTS ################################################################
//################ TEXTS ################################################################
//################ TEXTS ################################################################
//################ TEXTS ################################################################

#ifndef SPANISH_VER

// ENGLISH VERSION ;)

// MENU
char * texts_menu []={
"- MOON'S FANDOM FESTIVAL -","1, KEYBOARD,",
"2, KEMPSTON JOYSTICK,","3, SINCLAIR JOYSTICK,",
"4, ANDROID JOYSTICK,","5, ENDING:",
"NIHILIST, ",
"MADE WITH MGA-MK BY","GITHUB,COM / IADVD","2019",
"RECURRENT,"
};

// Booths
char * texts_booths_sp []={
"  CHEZ TOMIKA'S   "," HAMBURGUER HOUSE ","   YOU'LL NEVER   ","   STOP EATING!!  "
};
char * texts_booths []={
"  MOON'S  "," ZX GAMES "," WE LOVE  ","  SPECCY! ",
" PWIN     ","    TEAKS "," BLACK    ","    LODGE ",
" PARRY    ","   HOTTER "," MISTERY  ","     TOUR ",
"  ZAZINGER  ","   - M -    ","  MECHA     ","    ATTACK! ",
" RADE     ","  BLUNNER ","ARE YOU A ","LEPRICANT?",
"  ZORK'S    ","   GALAXY   "," I WANT TO  ","   BELIEVE! ",
"  NUCK CHORRIS'   "," ROUNDHOUSE KICK  ","   HE CAN SLAM    "," A REVOLVING DOOR!"
};

// ACTION TEXTS
char * status_perso []={
"\\",
"*",
"FRIENDSHIP: ",
"FAV, ITEM : ",
"HUNGRY    : "
};

char * texts_interact []={
"                          ","TALK TO EXCITED FAN","SIT IN YOUR BOOTH",
"GET/PUT ICON","TALK TO HAPPY FAN","TALK/GIVE TO BOB",
"TALK/GIVE TO GERMIONE","TALK/GIVE TO KOJI BAKUTO","TALK/GIVE TO DICK RECKARD",
"OPEN THE LOCKER","TALK/GIVE TO ZORK","TALK/GIVE TO JOHN DOE",
"READ THE PAMPHLETS","ENTER THE ROOM","OPEN THE FILE CABINET",
"READ THE MAGAZINE","POKE THE PLANTS",
"MY SPECCY AND MY GAME!!","A VERY OLD SYMBOLOGY,","A PARRY HOTTER CARD!",
"A COOL MECHA DESIGN,","KOIGHT-VAMPFF TESTER,","SHINY UFO ARTIFACT,,,",
"AN AUTOGRAPHED PHOTO!","TAKE A HAMBURGUER,"
};

// CONVERSATION TEXTS GENERIC
char action_text_24 [21] = "ARE YOU HAVING FUN??";
char action_text_28 [22] = "I STILL DON'T HAVE MY";
char action_text_29 [20] = "SPECCY AND MY GAME!";
char action_text_39 [22] = "DO YOU KNOW SOMETHING";
char action_text_40 [12] = "AMAZING,,,?";
char action_text_46 [22] = "                     ";
char action_text_66 [17] = "I DON'T HAVE THE";
char action_text_67 [10] = "CODE YET!";
char action_text_81 [18] = "I NEED THE ACCESS";
char action_text_82 [6] = "CARD!";
char action_text_91 [17] = "THANKS! I'LL ASK";
char action_text_92 [19] = "YOU AGAIN LATER!!!";
char action_text_97 [20] = "I LIKE GARDENING!!!";
char action_text_98 [22] = "NOTHING. KEEP TRYING,";
char action_text_99 [22] = "WELL.ALREADY GOT ONE,";
char action_text_100 [10] = "L-R/DOWN:";
char action_text_101 [21] = "- RECEIVED NUMBERS -";
char action_text_102 [17] = "MY SPECCY AND MY";
char action_text_103 [16] = "GAME. HOORAY!!!";
char action_text_104 [22] = "I CAN GO TO MY BOOTH!";
char action_text_111 [9] = "POCKETS:";

// ending recurrent
char action_text_105 [19] = "I DID IT! OK LET'S";
char action_text_106 [15] = "PLAY THE GAME!";
char action_text_107 [19] = "TAPE LOADING,,,OH.";
char action_text_108 [16] = "LOOK! THE MENU!";

// ending nihilist
char action_text_109 [18] = "HERE IS THE TAPE!";
char action_text_110 [18] = "I'M SO EXCITED!!!";
char action_text_112 [16] = "R: TAPE LOADING";
char action_text_113 [19] = "ERROR 0:1. NOOO,,,";
 
// TEXTS INITIAL EXPLANATION

char action_text_87 [20] = "WELL. I HOPE TO END";
char action_text_88 [21] = "MY QUEST QUICKLY,,,";
char action_text_89 [18] = "I FEEL AS IF I'VE";
char action_text_90 [22] = "DONE ALL THIS BEFORE!";

char * texts_taking_icons []={
"ERUS!",
",,,TAHT HCUOT T'NOD","ESAELP",
"SURE!",
"PLEASE DON'T TOUCH","THAT,,,",
"I'LL TAKE THIS,,,","I'LL PUT IT HERE,,,",
"NOTHING TO GET/PUT,"
};

// CONVERSATION TEXTS CHARACTERS
char * texts_start_conv []={
"ER,,,HI!","",
"IS THAT A REAL CAT?!","",
"THAT'S AN AMAZING","HELMET. VERY COOL!",
"I'M A LEPRICANT!","NO. NOT REALLY,,,",
"DO YOU LIKE OUR","PLANET?",
"AREN'T YOU THE REAL","NUCK CHORRIS?!",
"TSAP TI SI RO TNESERP","TI SI?",
"OF COURSE! SORCERERS","NEED ALWAYS ONE,",
"WAIT TO SEE THE MECHA.","IT'S PARKED OUTSIDE!",
"LEPRICANTS ARE LIKE","ANY OTHER MACHINE,",
"ZORK HAS SEEN BETTER","DUMPS. FEEBLE HUMAN!",
"OH. NOT AT ALL! IT'S","JUST A COINCIDENCE!",
"TIARTROP S'YDUJ","YM SI EREHW?",
"HAVE YOU SEEN MY","PARRY HOTTER CARD?",
"I'M LOOKING FOR","MY MECHA DESIGN!",
"I NEED A KOIGHT-VAMPFF","MACHINE,,,",
"WHERE IS MY ANTI-","GRAVITY DEVICE???",
"SOMEBODY TOOK MY","AUTOGRAPHED PHOTO,,,",
"TI EVRESED OUY",". EDOC RUOY SI EREH!",
"THANKS! I'M NOW","A PERFECT SORCERER!",
"YOU'VE HELPED","ME A LOT. THANKS!!",
"YOU AREN'T A","LEPRICANT! GOOD JOB!",
"NOT SO BAD FOR A","FEEBLE LIFEFORM!",
"YOU WON A 1ST DAN AS","MY FRIEND. CONGRATS!"
};

#ifndef ANDROID_TCP_IP
	char * texts_initial_explanation []={
	"RECOVER MY SPECCY ", "AND MY NEW GAME",
	"FROM THE LOCKERS,", "MY COLLEAGUES HAVE",
	"THE CODE: GAIN THEIR", "RESPECT, LET'S TALK",
	"TO EVERYBODY. AND","SEARCH FOR KNOWLEDGE,",
	"I CAN REMEMBER ONLY","3 PIECES OF INFO,",
	"MY POCKETS STORE THE","LAST 3 ITEMS I FOUND,",
	"WHEN I REVISIT A ROOM","THERE'S NEW INFO,",
	"FILE CABINETS HAVE A","LOT OF THINGS. SEARCH",
	"MORE THAN ONCE,","LET'S GO!!"
	};
	char * texts_start_joke []={
	"YNNUF! SDRAWKCAB","GNIKAEPS UOY ERA?",
	"YOU DON'T LOOK LIKE","A REAL SORCERER,,,",
	"THAT MECHA? IS MADE","OF PLASTIC!!!",
	"WELL. WHAT IF I'M","REALLY A LEPRICANT?",
	"YOUR FACE IS A MASK","ISN'T IT? C'MON!",
	"I BET YOU CAN'T DO A","ROUNDHOUSE KICK!",
	"NIAGA TERCES YM","LLET T'NOD ESAELP",
	"DON'T SAY THAT AGAIN,","I'M REALLY GOOD!!!",
	"HOW DO YOU DARE?","DON'T SAY THAT AGAIN,",
	"TELL ME THAT AGAIN AND","YOU'LL KNOW IT,,,",
	"DON'T SAY THAT AGAIN","FEEBLE HUMAN,,,",
	"PLEASE DON'T ASK ME","AGAIN OR I'LL DO IT,,,",
	",,,SRAEY 52 NI OUY EES","EGDOL KCALB EHT OT!",
	"OK. YOU ASKED IT,,,","A-LA-KA-ZOOOM!!!",
	"PLEASE. ENJOY THIS", "SHRINKING RAY,,,",
	"I WILL SWITCH YOU","OFF. SKINJOB!",
	"HAVE A NICE FLIGHT.","CARBON BASED LIFEFORM!",
	"SURE. MY FRIEND,,,","ROUNDHOUSE KIIICK!!!"
	};
	char * text_game_over []={
	"                            ",
	"  WELL. IT SEEMS SOMEBODY   ",
	"  GOT ANGRY,,,GAME OVER!    ",
	"                            "
	};
	char * texts_things []={
	"I TOOK A HAMBURGUER!","OH. GARMONBOZZIA!!",
	"I TOOK A BUG!","OH. A DOOMED RING,,,",
	"I TOOK A WOODEN WAND!","A SMALL SCREWDRIVER,",
	"AN EMPATHY BOX!","A MOBILE PHONE!",
	"I'VE FOUND A PEN!","A URL! GITHUB/IADVD",
	"A MR, POTATO HEAD,","A KEMPSTON JOYSTICK!",
	"A USED NAPKIN,,,","AN ACCESS CARD!!!"
	};
	char * texts_given []={
	"SIHT ROF GNIKOOL","SAW I, OUY KNAHT!",//RING
	"OH. WHAT A NICE","WAND. THANK YOU!",//WAND
	"JUST WHAT I NEEDED","TO FIX MY MECHA!!!",//SCREWDRIVER
	"VERY APPRECIATED!","I'M A MERCERIST,,,",//EMPATHY BOX
	"THANK YOU HUMAN.","I'LL CALL HOME NOW!",//MOBILE PHONE
	"THIS IS A WEAPON OF","DESTRUCTION. THANKS!",//PEN	
	"UOY KNAHT TUB","GNIZAMA OS TON!", // BOB
	"NOT SO AMAZING","BUT THANK YOU!", // GERMIONE
	"WELL, NOT SO FUNNY","BUT THANK YOU!", // KOJI
	"NOT VERY USEFUL. BUT","I'LL KEEP IT HERE,,,", // DICK
	"INSANE PLASTIC. I'LL","RECYCLE IT,,,", // ZORK
	"WELL,,,ER,,,","THANKS. BUT USELESS,", // JOHN
	",,,SUOICILED!!!","MONMONMO, MONMONMO", // BOB
	"OMNOMNOM. OH SO","TASTY! THANKS!!", // GERMIONE
	"HERE WE GO. CALORIES!","OMNOMNOM,,,!!!", // KOJI
	"IS IT ARTIFICIAL?","OMNOMNOM,,,YUMMY!", // DICK
	"OMNOMNOM. PATHETIC","HUMAN. OMNOMNOM,", // ZORK
	"OH. WHAT A TASTY","TOFU VEGGIEBURGER!!!" // JOHN
	};
	char * texts_start_knew_didnt_knew_it []={
	"ECIWT SGNIHT GNIRAEH","EKIL TON SEOD BOB!",
	"WELL. EVERYBODY KNOWS","THAT,,,BOOORING!",
	"EVEN A CHILD KNOWS IT.","TRY HARDER MY FRIEND,",
	"I'VE SEEN LEPRICANTS","WITH BETTER MEMORIES!",
	"YOU KNOWLEDGE IS ","RIDICULOUS. HUMAN,",
	"ER. WELL,,, YES,,,","SO,,,???",
	"LLA TA YDUJ TOUBA","KLAT TON ER'EW!",
	"OH. TELL ME MORE.","YOU KNOW SO MUCH!",
	"YES. YES! THAT IS","EXACTLY WHAT I THINK,",
	"HOW DID YOU KNOW THAT?","YOU ARE INTERESTING,",
	"THE FORCE IS STRONG","WITH YOU. HUMAN,",
	"YES! EXACTLY!!!","AMAZING. ISN'T IT?!"	
	};
#else
	char * texts_start_joke []={
	"YNNUF! SDRAWKCAB,","",
	"YOU DON'T LOOK LIKE","A REAL SORCERER,,,",
	"THAT MECHA? IS PLASTIC!","",
	"WELL. WHAT IF I'M","REALLY A LEPRICANT?",
	"YOUR FACE IS A MASK!","",
	"I BET YOU CAN'T DO A","ROUNDHOUSE KICK!",
	"NIAGA TERCES YM","LLET T'NOD ESAELP",
	"DON'T SAY THAT AGAIN,","",
	"HOW DO YOU DARE?","",
	"TELL ME THAT AGAIN,,,","",
	"DON'T SAY THAT AGAIN,","",
	"PLEASE DON'T ASK ME,","",
	",,,SRAEY 52 NI OUY EES","",
	"A-LA-KA-ZOOOM!!!","",
	"SHRINKING RAY,,,!!!", "",
	"BYE BYE. SKINJOB!","",
	"HAVE A NICE ABDUCTION.","",
	"ROUNDHOUSE KIIICK!!!",""
	};
	char * text_game_over []={
	"  SORRY MOON,,,GAME OVER!    ",
	};
	char * texts_things []={
	"A HAMBURGUER!","GARMONBOZZIA!!",
	"A BUG!","A DOOMED RING,,,",
	"A WOODEN WAND!","A SCREWDRIVER,",
	"AN EMPATHY BOX!","A PHONE!",
	"A PEN!","A URL! GITHUB/IADVD",
	"A MR, POTATO HEAD,","A JOYSTICK!",
	"A USED NAPKIN,,,","AN ACCESS CARD!!!"
	};
	char * texts_given []={
	"SIHT ROF GNIKOOL","SAW I, OUY KNAHT!",//RING
	"NICE WAND.","THANKS!",//WAND
	"I NEEDED THIS","TO FIX MY MECHA!",//SCREWDRIVER
	"APPRECIATED!","I'M A MERCERIST,",//EMPATHY BOX
	"THANK YOU HUMAN.","I'LL CALL HOME!",//MOBILE PHONE
	"A WEAPON OF","DESTRUCTION. THANKS!",//PEN	
	"UOY KNAHT TUB","GNIZAMA OS TON!", // BOB
	"NOT SO AMAZING","BUT THANKS!", // GERMIONE
	"WELL, NOT SO FUNNY","BUT THANKS!", // KOJI
	"NOT VERY USEFUL. BUT","I'LL KEEP IT HERE,,,", // DICK
	"INSANE PLASTIC. I'LL","RECYCLE IT,,,", // ZORK
	"ER,,,","THANKS. BUT USELESS,", // JOHN
	",,,SUOICILED!!!","MONMONMO, MONMONMO", // BOB
	"OMNOMNOM. TASTY!","THANKS!!", // GERMIONE
	"HERE WE GO. CALORIES!","OMNOMNOM,,,!!!", // KOJI
	"IS IT ARTIFICIAL?","OMNOMNOM,,,", // DICK
	"OMNOMNOM. PATHETIC","HUMAN. OMNOMNOM,", // ZORK
	"OH. A TASTY","TOFU VEGGIEBURGER!" // JOHN
	};
	char * texts_start_knew_didnt_knew_it []={
	"ECIWT SGNIHT GNIRAEH","EKIL TON SEOD BOB!",
	"EVERYBODY KNOWS","THAT! BOORING!",
	"EVEN A CHILD KNOWS IT.","TRY HARDER,",
	"I'VE SEEN LEPRICANTS","WITH BETTER MEMORIES!",
	"YOU KNOWLEDGE IS ","RIDICULOUS. HUMAN,",
	"WELL,,, YES,","SO,,,?",
	"LLA TA YDUJ TOUBA","KLAT TON ER'EW!",
	"TELL ME MORE.","YOU KNOW SO MUCH!",
	"YES! THAT IS","WHAT I THINK!",
	"HOW DID YOU KNOW THAT?","INTERESTING,,,",
	"THE FORCE IS STRONG","WITH YOU. HUMAN,",
	"YES! EXACTLY!","AMAZING. ISN'T IT?"	
	};
#endif

char action_text_47 [7] = ",,,???";

char * first_conv_rade []={
"THEY'RE EITHER A",
"BENEFIT OR A HAZARD",
"IF THEY'RE A BENEFIT",
"IT'S NOT MY PROBLEM,",
"VERY FRIENDLY,,,",
"WELL. SEE YA!"
};

char * first_conv_john []={
"BUT THOSE GLASSES",
"ARE JUST A FRAME,,,",
"GULP. I'M BUSY NOW,,,",
"- MUMBLE -"
};

char * garbo_text []={
"WAIT,,, THIS IS NOT A","RESTROOM! THIS IS",
"A ROOM ABOVE A","CONVENIENCE STORE!!!",
"THE JANITOR IS HERE!","WHAT?! CREAMED CORN?"
};

char * texts_things_reduced []={
"\"",//HAMBURGUER
"#",//GARMONBOZZIA
"$",//BUG
"=",//RING
";",//WAND
"&",//SCREWDRIVER
"(",//EMPATHY BOX
")",//MOBILE PHONE
"%",//PEN
"<",//GITHUB/IADVD
">",//POTATO
"@",//JOYSTICK
"[",//NAPKIN
"^"//CARD
};

char * texts_start_do_not_care []={
",,,SEMITEMOS DEROB TEG","SEITITNE LIVE NEVE",
"HA. HA. HA,,,","NOT FUNNY AT ALL!",
"YOU'RE KIND OF OUT","OF DATE, YAAAAWN!",
"THANKS. CAPT, OBVIOUS.","YOU MADE MY DAY,,,",
"SIGH. HUMANS ARE SO","PREDICTABLY BORING,,,",
"STARING AT A CACTUS","IS FUNNIER THAN YOU,",	
};

char * texts_fans []={
"HEARING VOICES ISN'T","A GOOD SIGN,",
"WOLDEMORT IS MY PAST.","PRESENT AND FUTURE,,,",
"THE WORLD WILL SEE","DR,HEL'S POWER,",
"HURRY, GET ZAZINGER","I'LL DEAL WITH THIS,",
"YEAH! I HAVE THE FURY","OF MY OWN MOMENTUM,",
"WHO YOU GONNA CALL?","GHASTBUSTERS,,,!!!",
"I'VE VISITED AREA 51","AND J-ROD IS NICE!",
"THEY ARE TEACHING US","A TONAL VOCABULARY,",
"THROUGH THE DARKNESS","FIRE WALK WITH ME,",
"THE JANITOR IS","HIDDEN SOMEWHERE,,,",
"I LOVE HAMBURGUERS:","VEGGIE HAMBURGUERS,",
"OWLS ARE NOT","WHAT THEY SEEM,",
"LOL YEAH!","BWAHAHAHAHAHA,,,",
"HOW'S ANNY,,,?","HOW'S ANNY,,,?",
"I'VE GOT 4 SKIN JOBS","WALKING THE STREETS,",
"I'VE SEEN THINGS YOU","WOULDN'T BELIEVE,",
"SOMEONE MANUFACTURED","YOU,,,",
"NUCK CHORRIS COUNTED","TO INFINITY 3 TIMES!",
"NUCK CHORRIS DOESN'T","SLEEP, HE WAITS,",
"THE HOWGARTS EXPRESS","IS AT PLATFORM 9'3/4!",
"BAD DOBY!","BAD DOBY!",
"OUR CHOICES SHOW","WHAT WE TRULY ARE,",
"BOSS! COME ON. BOSS","WAKE UP!",
"ONLY WITH PHOTON","POWER WE'LL SURVIVE!",
"YOU'RE TALKING","ABOUT MEMORIES,",
"IN ANY CASE GOOD","LUCK FOR THE BATTLE,",
"SUSHI,THAT'S WHAT MY","EX-WIFE CALLED ME,",
"YOU'VE DONE A MAN'S","JOB. SIR!",
"ARE YOU FAMILIAR","WITH THE X-FLIES?",
"FLYING SAUCER,DO YOU","BELIEVE IN THAT?",
"OTHER PLANETS, WANNA","CHECK SOME OUT?",
"NUCK CHORRIS","CAN DIVIDE BY ZERO,",
"NUCK CHORRIS KILLED","2 STONES WITH 1 BIRD,",
"THE DARK IS AFRAID","OF NUCK CHORRIS,,,",
"YOU'VE BEEN","RACKROLLED,,,"
};

#else

// SPANISH VERSION ;)
	
// MENU
char * texts_menu []={
"- MOON EN EL FANDOM FEST -","1, TECLADO,",
"2, KEMPSTON JOYSTICK,","3, SINCLAIR JOYSTICK,",
"4, ANDROID JOYSTICK,","5, FINAL:",
"NIHILISTA, ",
"HECHO CON MGA-MK POR","GITHUB,COM / IADVD","2019",
"RECURRENTE,"
};

// Booths
char * texts_booths_sp []={
"   CASA  TOMIKA   ","  HAMBURGUESERIA  "," +NO PODRAS DEJAR ","    DE COMERLAS!  "
};
char * texts_booths []={
" JUEGOS   ","  ZX MOON "," VIVA EL  "," SPECTRUM ",
" PWIN     ","    TEAKS "," LOGIA    ","    NEGRA ",
" PARRY    ","   HOTTER "," VIAJE    ","   MAGICO ",
"  ZAZINGER  ","   - M -    ","+LAS BESTIAS"," MECANICAS! ",
" RADE     ","  BLUNNER ","  ERES UN ","PERRICANTE",
" LA GALAXIA ","  DE ZORK   "," +QUIERO    ","     CREER! ",
"  LA PATADA DE    ","     NUCK CHORRIS "," EL COSMOS NO SE  ","EXPANDE.HUYE DE EL"
};

// ACTION TEXTS
char * status_perso []={
"\\",
"*",
"AMISTAD   : ",
"NECESITA  : ",
"HAMBRE    : "
};

char * texts_interact []={
"                          ","HABLA CON FAN MUY EXCITADO","SIENTATE EN TU ESTAND",
"COGE/DEJA ICONO","HABLA CON FAN FELIZ","HABLA/DA A BOB",
"HABLA/DA A GERMIONE","HABLA/DA A KOJI BAKUTO","HABLA/DA A DICK RECKARD",
"ABRE LA CONSIGNA","HABLA/DA A ZORK","HABLA/DA A JUAN NADIE",
"LEE LOS PANFLETOS","ENTRA A LA HABITACION","REBUSCA EN LA CAJONERA",
"LEE LA REVISTA","TOCA LAS PLANTAS",
"+MI ESPECTRUM Y MI JUEGO!","UNA SIMBOLOGIA ANTIGUA","TARJETA DE PARRY HOTTER",
"UN DISE_O DE ROBOT CHULO","UNA MAQUINA KOIGHT-VAMPFF","UN OBJETO EXTRATERRESTRE",
"+UNA FOTO CON AUTOGRAFO!","COGE UNA HAMBURGUESA"
};

// CONVERSATION TEXTS GENERIC
char action_text_24 [17] = "]]TE DIVIERTES??";
char action_text_28 [21] = "+TODAVIA NO TENGO MI";
char action_text_29 [21] = "SPECTRUM Y MI JUEGO!";
char action_text_39 [12] = "]SABES ALGO";
char action_text_40 [16] = "INTERESANTE,,,?";
char action_text_46 [22] = "                     ";
char action_text_66 [13] = "+NO TENGO LA";
char action_text_67 [15] = "CLAVE TODAVIA!";
char action_text_81 [21] = "+NECESITO LA TARJETA";
char action_text_82 [11] = "DE ACCESO!";
char action_text_91 [22] = "+GRACIAS! TE PREGUNTO";
char action_text_92 [18] = "MAS LUEGO. ]VALE?";
char action_text_97 [22] = "+ADORO LA JARDINERIA!";
char action_text_98 [22] = "NADA.PRUEBA OTRA VEZ,";
char action_text_99 [18] = "+NO NECESITO DOS!";
char action_text_100 [10] = "I-D/ABJO:";
char action_text_101 [21] = "- CLAVES OBTENIDAS -";
char action_text_102 [17] = "MI SPECTRUM Y MI";
char action_text_103 [18] = "JUEGO. ++VIVAAA!!";
char action_text_104 [21] = "+PUEDO IR AL ESTAND!";
char action_text_111 [9] = "LLEVAS :";

// ending recurrent
char action_text_105 [19] = "+LO CONSEGUI! VALE";
char action_text_106 [16] = "+VAMOS A JUGAR!";
char action_text_107 [21] = "CARGANDO LA CINTA,,,";
char action_text_108 [20] = "+OH MIRA! +EL MENU!";

// ending nihilist
char action_text_109 [20] = "AQUI ESTA LA CINTA!";
char action_text_110 [18] = "+++QUE EMOCION!!!";
char action_text_112 [16] = "R: TAPE LOADING";
char action_text_113 [20] = "ERROR 0:1. +NOOO,,,";
 
// TEXTS INITIAL EXPLANATION

char action_text_87 [21] = "BUENO. ESPERO ACABAR";
char action_text_88 [22] = "MI BUSQUEDA RAPIDO,,,";
char action_text_89 [22] = "TENGO LA SENSACION DE";
char action_text_90 [22] = "YA HABER HECHO ESTO, ";

char * texts_taking_icons []={
"+ORALC!",
",,,SEUQOT OL ON","ROVAF ROP",
"+CLARO!",
"POR FAVOR NO LO","TOQUES,,,",
"COGERE ESTO,,,","PONDRE ESTO AQUI,,,",
"NADA QUE COGER/DEJAR,"
};

// CONVERSATION TEXTS CHARACTERS
char * texts_start_conv []={
"ESTO,,,+HOLA!","",
"+]ES ESO UN GATO","DE VERDAD?!",
"+LLEVAS UN CASCO","DE LO MAS CHULO!",
"+SOY UNA PERRICANTE!","QUE NO.+QUE ES TROLA!",
"]TE GUSTA NUESTRO","PLANETA?",
"]NO ERES EL VERDADERO","NUCK CHORRIS?",
"]ODASAP LE O ETNESERP","LE SE?",
"+PUES CLARO!LOS MAGOS","SIEMPRE LLEVAMOS UNO,",
"EL ROBOT MOLA MAS.","+ESTA APARCADO FUERA!",
"UN PERRICANTE ES COMO","CUALQUIER MAQUINA,",
"+HE VISTO MEJORES","VERTEDEROS. HUMANA!",
"+QUE VA. ES SOLO","CASUALIDAD!",
"]YDUJ ED OTARTER","IM ATSE EDNOD?",
"]HAS VISTO MI TARJETA","DE PARRY HOTTER?",
"+BUSCO MI DISE_O","DEL ROBOT! AYUDAME,,,",
"NECESITO UNA MAQUINA","KOIGHT-VAMPFF,,,",
"BUSCO MI DISPOSITIVO","ANTIGRAVEDAD,,,",
"ALGUIEN SE LLEVO MI","FOTO AUTOGRAFIADA,,,",
"+SECEREM AL ET. EVALC","UT SENEIT IUQA!",
"+GRACIAS. AHORA SOY","UNA MAGA PERFECTA!",
"ME AYUDASTE MUCHISIMO","++MIL GRACIAS!!",
"NO ERES PERRICANTE.","++BUEN TRABAJO!!",
"+NO ESTA MAL PARA UN","SER TAN DEBILUCHO!",
"GANASTE EL 1ER DAN DE","MI AMISTAD. +GRACIAS!"
};

char * texts_initial_explanation []={
"RECUPERA MI SPECTRUM", "Y MI JUEGO NUEVO",
"DE LA CONSIGNA,", "MIS COLEGAS TIENEN",
"LA CLAVE, GANATE SU", "RESPETO, HABLEMOS",
"CON TODOS: CONSIGUE","INFORMACION,",
"SOLO PUEDO RECORDAR","3 DATOS A LA VEZ,",
"SOLO PUEDO LLEVAR","3 COSAS Y UN ICONO,",
"CUANDO VUELVO A UN","LUGAR HAY INFO NUEVA,",
"LAS CAJONERAS TIENEN","MUCHAS COSAS. BUSCA",
"MAS DE UNA VEZ,","++VAMOS!!"
};
char * texts_start_joke []={
"+ODITREVID! ]SARTA","AICAH ODNALBAH SATSE?",
"NO PARECES UNA MAGA","DE VERDAD,,,",
"]EL ROBOT?+PERO SI ES","DE PLASTICO!",
"VALE. ]Y SI SOY UNA","PERRICANTE DE VERDAD?",
"TU CARA ES UNA CARETA","]VERDAD? +RECONOCELO!",
"]A QUE NO SABES HACER","UNA PATADA VOLADORA?",
"+OVEUN ED OTERCES IM","SAGID ON ROVAF ROP!",
"NO DIGAS ESO OTRA VEZ","+++SOY MUY BUENA!!!",
"]COMO TE ATREVES? NO","DIGAS ESO OTRA VEZ,",
"DILO DE NUEVO Y","LO AVERIGUARAS,,,",
"NO DIGAS ESO OTRA VEZ","HUMANA DEBILUCHA,,,",
"NO ME LO PIDAS OTRA","VEZ. QUE LO HAGO,,,",
"+AICNATSE UT ATURFSID","ARGEN AIGOL AL A!",
"TE LO HAS BUSCADO...","+++AAABRACADABRAAA!!!",
"POR FAVOR. DISFRUTA", "MI RAYO REDUCTOR,,,",
"TE VOY A DESACTIVAR","+PELLEJUDA!",
"ABDUCCION EN 3.2.1,,,","+DISFRUTA EL VIAJE!",
"PUES VALE,,,","+PATAAADAA VOLADORAA!"
};
char * text_game_over []={
"                            ",
"  VAYA. PARECE QUE ALGUIEN  ",
"  SE ENFADO CONTIGO. +FIN!  ",
"                            "
};
char * texts_things []={
"+UNA HAMBURGUESA!","OH. +GARMONBOZZIA!",
"+ENCONTRE UN BICHO!","OH.UN ANILLO MALDITO,",
"UNA VARITA DE MADERA","UN DESTORNILLADOR,",
"+UNA CAJA DE EMPATIA!","+UN TELEFONO MOVIL!",
"+ENCONTRE UN BOLI!","OH. GITHUB/IADVD",
"UN MISTER POTATO,","UN JOYSTICK KEMPSTON",
"UNA SERVILLETA USADA,","LA TARJETA DE ACCESO"
};
char * texts_given []={
"OTSE ODNACSUB","ABATSE +SAICARG!",//RING	
"OH. QUE VARITA TAN","BONITA. +GRACIAS!",//WAND
"+LO NECESITABA PARA","ARREGLAR MI ROBOT!",//SCREWDRIVER
"+MUY AGRADECIDO!","SOY MERCERISTA,,,",//EMPATHY BOX
"GRACIAS HUMANA.","+VOY A LLAMAR A CASA!",//MOBILE PHONE
"ESTO ES UN ARMA DE","DESTRUCCION.+GRACIAS!",//PEN		
"+SAICARG OREP","ETNASERETNI YUM ON!", // BOB	
"+NO MUY DIVERTIDO","PERO GRACIAS!", // GERMIONE
"BAH. +NO ES GRAN COSA","PERO GRACIAS!", // KOJI
"NO MUY UTIL. PERO LO","DEJARE POR AQUI,,,", // DICK
"PLASTICO. COMO NO,","LO RECICLARE,,,", // ZORK
"BUENO,,,ESTO,,,","GRACIAS. PERO INUTIL,", // JOHN
"+OSOICILED!",",,,MA_MA_MA_", // BOB
"_AM_AM_AM. +PERO","QUE RICA! +GRACIAS!", // GERMIONE
"+CALORIAS. ALLA VOY!","+_AM_AM_AM,,,!", // KOJI
"]ES ARTIFICIAL?","+_AM_AM_AM,,,RICA!", // DICK
"_AM_AM_AM. HUMANA","PATETICA. _AM_AM_AM,", // ZORK
"+OH. QUE DELICIOSA","TOFUHAMBURGUESA!" // JOHN
};
char * texts_start_knew_didnt_knew_it []={
"+SECEV 2 OMSIM OL RIO","ATSUG EL ON BOB A!",
"BUENO. TODO EL MUNDO","LO SABE, +QUE ROOLLO!",
"HASTA UN BEBE LO SABE.","TIENES QUE MEJORAR,",
"+HE VISTO PERRICANTES","CON MEJORES RECUERDOS!",
"TU CONOCIMIENTO ES ","RIDICULO. HUMANA,",
"ESTO. BUENO,,, SI,,,","]]]Y,,,???",
"+YDUJ ED RALBAH","A SOMAV ON!",
"OH. DIME MAS COSAS.","+SABES TANTO!",
"+SI. SI! ESO ES","JUSTO LO QUE PIENSO,",
"]COMO LO SABIAS?","ERES CURIOSA,,,",
"LA FUERZA ES INTENSA","EN TI. HUMANA,",
"+SI! +++EXACTO!!!","+]A QUE MOLA?!"	
};

char action_text_47 [10] = "]]],,,???";

char * first_conv_rade []={
"O SON UN BENEFICIO",
"O UN PELIGRO",
"SI SON UN BENEFICIO",
"NO SON ASUNTO MIO,",
"QUE SIMPATICO,,,",
"BUENO. +TALUEGO!"
};

char * first_conv_john []={
"PERO SI ESAS GAFAS",
"SON SOLO UN MARCO,,,",
"ESTOO. AHORA ESTOY",
"OCUPADO,,, UYUYUI,,,"
};

char * garbo_text []={
"+NO ES EL SERVICIO!","+ES UNA HABITACION",
"SOBRE UNA TIENDA","DE UNA GASOLINERA!",
"+ESTA EL CONSERJE!","]QUE? +MAIZ CREMOSO!"
};

char * texts_things_reduced []={
"\"",//HAMBURGUER
"#",//GARMONBOZZIA
"$",//BUG
"=",//RING
";",//WAND
"&",//SCREWDRIVER
"(",//EMPATHY BOX
")",//MOBILE PHONE
"%",//PEN
"<",//GITHUB/IADVD
">",//POTATO
"@",//JOYSTICK
"[",//NAPKIN
"^"//CARD
};

char * texts_start_do_not_care []={
"SECEV A SOMIRRUBA SON","SODAVLAM SETNE SOL",
"JA. JA. JA,,,","+QUE RISA. FELISA!",
"ESTAS UN POCO","ANTICUADA, +BAH!",
"HUY SI. BLABLABLA,,,","ME SALVASTE DE NUEVO,",
"AY. LOS HUMANOS SOIS","TAN PREDECIBLES,,,",
"HABLAR CON UN CACTUS","ES MAS EMOCIONANTE,",
};

char * texts_fans []={
"OIR VOCES NO","ES BUEN AUGURIO,",
"WOLDEMORT. MI PASADO.","PRESENTE Y FUTURO,,,",
"EL MUNDO CONOCERA","EL PODER DEL DR,HEL,",
"COGE A ZAZINGER. +YO","ME OCUPO DE ESTO!",
"+SI! TENGO LA FURIA","DE MI PROPIO MOMENTO,",
"]A QUIEN LLAMARAS?","+A LOS COSAFANTASMAS!",
"+ESTUVE EN EL AREA 51","Y J-ROD ES MAJO!",
"NOS ESTAN ENSE_ANDO","UN VOCABULARIO TONAL,",
"EN LA OSCURIDAD","FUEGO CAMINA CONMIGO,",
"EL CONSERJE ESTA","ESCONDIDO,,,",
"AMO LAS HAMBURGUESAS.","PERO VEGETARIANAS,",
"LOS BUHOS NO SON","LO QUE PARECEN,",
"+SII! +SIII!","JUAJUAJUAJUAAAA,,,",
"]COMO ESTA ANNY,,,?","]COMO ESTA ANNY,,,?",
"TENGO A 4 PELLEJUDOS","POR LAS CALLES,,,",
"HE VISTO COSAS QUE","VOSOTROS NO CREERIAIS",
"ALGUIEN TE","HA CREADO,,,",
"+NUCK CHORRIS CONTO","AL INFINITO 3 VECES!",
"NUCK CHORRIS NO","DUERME. ESPERA,,,",
"]EL EXPRESO HOWGARTS?","+PLATAFORMA 9'3/4!",
"+DOBY MALO!","+DOBY MALO!",
"NUESTRAS ELECCIONES","MUESTRAN LO QUE SOMOS",
"+BOSS! VAMOS. BOSS","+DESPIERTA!",
"+SOLO CON EL PODER","FOTONICO GANAREMOS!",
"ESTA HABLANDO","DE RECUERDOS,",
"DE TODAS FORMAS.BUENA","SUERTE EN LA LUCHA,",
"SUSHI, ASI ME LLAMABA","MI EXMUJER,",
"+HA HECHO UN TRABAJO","DE HOMBRES!",
"]TIENE ACCESO A","LOS EXPELIENTES X?",
"PLATILLOS VOLANTES,,,","]CREE EN ELLOS?",
"OTROS PLANETAS.]DESEA","VER ALGUNOS?",
"NUCK CHORRIS","PUEDE DIVIDIR POR 0,",
"NUCK CHORRIS MATO","2 TIROS DE 1 PAJARO,",
"LA OSCURIDAD TEME","A NUCK CHORRIS,,,",
"HAS SIDO","RACKROLEADO,,,"
};
	
#endif
