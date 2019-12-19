struct sp_UDK keys;
void *joyfunc;				// Puntero a la función de manejo seleccionada.

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

#define EST_NORMAL 		0
#define WBOTTOM 2
#define WLEFT 3
#define WRIGHT 4

#define colorM1 4
#define colorM2 5	
#define colorM3 7
#define colorM4 6
#define colorM5 3
#define ESPERA_PASIVA 50

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

ANIMADO en_an, en_anB;

// atributos de la pantalla: Contiene información
// sobre que tipo de tile hay en cada casilla
unsigned char map_attr [90];
unsigned char map_buff [90];
unsigned char n_pant,n_pant_precalc;

// Aux

// Next steps: array to mark the knowledge that
// was correctly given to a character, so it
// does not appear again... and if all the 
// knowledge in one of the types of objects has_denorm
// been exhausted, then show a message like "I DO NOT NEED TO CHECK THESE BOOKS AGAIN"

// Next steps: flags can be bits and no bytes (check)

// Position of each special item when the game start
int in_pant_of_character_i_there_is_perso_item[]={-1,7,6,5,3,4,2};
// Priority 3 interactions array
int priority3_interact[]={0,0,34,0,16,0,0,0,12,15,0,14};
// Objects on screen
int objects_on_screen[]={7,6,6,8,3,4,5,7,9}; 
int hungry[7];
int confidence[7];
int conversation_character[6];
int joke_times[6];
int scroll_texts = 0;
int boat_has_oars=0;
int fan_i_told[3];
int info_found[3];
int my_memory[3];
int pocket_counter, memory_counter;
int pocket_things[3]; //take-give pocket
int pocket_item; //get-put icon pocket
int face_looper[3], which_face[3];
int mirror_tile=0;
int was_mirrored=0;
int selection = 0;
int entering_pos_right=12400;
int entering_pos_left=(1<<10)+((1<<10)/2);//one and a half tiles
int intermediate_screen_from = 0;
int coconut_in_the_water=0;
unsigned interact, last_interact;

extern unsigned int asm_int [1];
extern unsigned int asm_int_b [1];
extern unsigned int asm_int_c [1];
extern unsigned int seed [1];
extern unsigned int values_col_menu [11];
extern unsigned int values_row_menu [11];
extern unsigned int values_color_menu [11];
extern unsigned int perso_face_pos_x [8];
extern unsigned int perso_face_pos_y [8];
extern unsigned int interact_z [32];
extern unsigned int interact_value [32];
extern unsigned int knowledge_characters_1 [12];
extern unsigned int knowledge_characters_2 [30];
extern unsigned int knowledge_characters_3 [30];
extern unsigned int booths_texts_pos [16];
extern unsigned int common_fan_items [24];
extern unsigned int common_fan_items_y_pos [24];
char * texts_menu_tmp =" "; // To give some animation to the main menu

#asm
._asm_int
	defw 0

._asm_int_b
	defw 0

._asm_int_c
	defw 0
	
._seed	
	defw 0	

._values_col_menu
	defw 4,6,6,6,6,6,16,6,5,24
._values_row_menu
	defw 0,8,10,12,14,16,16,18,20,20
._values_color_menu
	defw colorM4,colorM1,colorM2,colorM3
	defw 0
	defw colorM4,colorM4,colorM1,colorM5,colorM3

._perso_face_pos_x // main characters face pos x
	defw VIEWPORT_X+0,VIEWPORT_X+14,VIEWPORT_X+22,VIEWPORT_X+10,VIEWPORT_X+8,VIEWPORT_X+6,VIEWPORT_X+18,VIEWPORT_X+10,VIEWPORT_X+0

._perso_face_pos_y // main characters face pos y
	defw VIEWPORT_Y+6,VIEWPORT_Y+6,VIEWPORT_Y+6,VIEWPORT_Y+6,VIEWPORT_Y+6,VIEWPORT_Y+6,VIEWPORT_Y+6,VIEWPORT_Y+2,VIEWPORT_Y+6

._booths_texts_pos // in this games these are the position of the sails
	defw 3,15,13,15,5,3,11,11
	defw 6
	defw 56 //56

._common_fan_items
	// PosInformer1,PosInformer2,Item of n_pant body x pos for n_pant=1
	defw VIEWPORT_X+22,VIEWPORT_X+18,15   // special use: in 16 will be grogl and cannon dep. on screen
	defw VIEWPORT_X+6,VIEWPORT_X+22,VIEWPORT_X+18  	
	defw VIEWPORT_X+4,VIEWPORT_X+26,VIEWPORT_X+18
	defw VIEWPORT_X+6,VIEWPORT_X+20,VIEWPORT_X+14 	
	defw VIEWPORT_X+24,VIEWPORT_X+20,VIEWPORT_X+12 	
	defw VIEWPORT_X+14,VIEWPORT_X+18,VIEWPORT_X+10 	
	defw VIEWPORT_X+8,VIEWPORT_X+4,VIEWPORT_X+14 
	defw VIEWPORT_X+12,VIEWPORT_X+16,VIEWPORT_X+20
	defw VIEWPORT_X+24,VIEWPORT_X+6,VIEWPORT_X+0 	

._common_fan_items_y_pos
	// PosInformer1,PosInformer2,Item of n_pant body y pos for n_pant=1
	defw VIEWPORT_Y+6,VIEWPORT_Y+6,VIEWPORT_Y+6	// special use: in 16 will be grogl and cannon dep. on screen
	defw VIEWPORT_Y+4,VIEWPORT_Y+6,VIEWPORT_Y+6	
	defw VIEWPORT_Y+4,VIEWPORT_Y+6,VIEWPORT_Y+4
	defw VIEWPORT_Y+4,VIEWPORT_Y+6,VIEWPORT_Y+4
	defw VIEWPORT_Y+4,VIEWPORT_Y+6,VIEWPORT_Y+4
	defw VIEWPORT_Y+4,VIEWPORT_Y+6,VIEWPORT_Y+4
	defw VIEWPORT_Y+4,VIEWPORT_Y+6,VIEWPORT_Y+4	
	defw VIEWPORT_Y+8,VIEWPORT_Y+8,VIEWPORT_Y
	defw VIEWPORT_Y+6,VIEWPORT_Y+4,VIEWPORT_Y+6	

// Priority 2 BEGIN: Interactions with characters 
// that can speak and the special items of each screen
._interact_z
	defw 3,7,9,11
	defw 3,6,11,0
	defw 2,9,11,13
	defw 3,5,7,10
	defw 4,6,10,12
	defw 3,5,7,9
	defw 2,4,7,9
	defw 5,6,8,9
	defw 3,5,7,12
._interact_value
	defw 0,17,1,4
	defw 4,9,1,0
	defw 4,3,5,1
	defw 4,6,3,1
	defw 7,3,1,4
	defw 8,3,4,1
	defw 1,4,3,10
	defw 11,4,1,3
	defw 1,0,0,4
// Priority 2 END

// Pockets and Knowledge BEGIN
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

//given knowledge...
//see texts_fans texts to set the correct index
._knowledge_characters_3 
	defw 8,14,16,18,24 		// character of n_pant=2
	defw 0,2,30,32,34		// character of n_pant=3
	defw 4,6,36,38,42		// character of n_pant=4
	defw 20,22,40,44,46		// character of n_pant=5
	defw 10,12,48,50,52		// character of n_pant=6
	defw 26,28,54,56,58		// character of n_pant=7
	
// Pockets and Knowledge END
	
#endasm

//################ TEXTS ################################################################
//################ TEXTS ################################################################
//################ TEXTS ################################################################
//################ TEXTS ################################################################

#ifndef SPANISH_VER

// ENGLISH VERSION ;)

// MENU
char * texts_menu []={
":: MOON AND THE PIRATES ::","1. KEYBOARD.",
"2. KEMPSTON JOYSTICK.","3. SINCLAIR JOYSTICK.",
"4. ANDROID JOYSTICK.","5. TEXTS: ",
"AUTOSCROLL. ",
"MADE WITH MGA-MK BY","GITHUB.COM / IADVD","2019",
"PRESS SPACE."
};

	
// ACTION TEXTS
char * status_perso []={
"\\",
"*",
"FRIENDSHIP: ",
"FAV. ITEM : ",
"THIRSTY   : "
};

char * texts_interact []={
"                          ","TALK TO SEADOG","TO THE FERRY!",
"GET/PUT ICON","TALK TO GRUMPY BOATSWAIN","TALK/GIVE TO BUCCANEER",
"TALK/GIVE TO CAPT. SOCKS","TALK/GIVE TO PRIESTESS","TALK/GIVE TO THE COOK",
"OPEN THE BOOTY CHEST","TALK/GIVE TO THE CABIN BOY","TALK/GIVE TO THE LOOKOUT",
"READ THE TREASURE MAP","LOOK INTO THE WATER","OPEN THE BASKET",
"READ THE CAPTAIN'S LOGBOOK","OPEN THE CHEST",
"TAKE A JAR OF GROG","THE TICKET FOR THE FERRY!","THE TURKISH EYE AMULET!",
"A FUNNY PARROT!","A FOUR-EYED VOODOO SKULL!","A PIRATE'S RECIPE BOOK",
"A LITTLE FANCY RAT","THE CORSAIR'S SPYGLASS","TAKE A CANNONBALL",
"TO THE ORLOP","TO THE MIDDLE DECK","TO THE UPPER DECK",
"TO THE CROW'S NEST","DOWN TO THE UPPER DECK","TO COCONUTS ISLAND",
"BACK TO THE SHIP","FIRE THE CANNON!","RUMMAGE IN THE BARREL"
};


// CONVERSATION TEXTS GENERIC

char * action_text_24 = {"AHOY, MATEY!"};
char * action_text_25 = {"ANY NEWS?"};
char * action_text_28 = {"I STILL DON'T HAVE"};
char * action_text_29 = {"A BOARDING TICKET!"};
char * action_text_39 = {"YO HO HO! DO YE KNOW"};
char * action_text_40 = {"SOMETHING AMAZING?"};
char * action_text_46 = {"                     "};
char * action_text_47 = {"I'LL TRY TO HELP!"};
char * action_text_66 = {"I STILL DON'T HAVE"};
char * action_text_67 = {"THE KEYS!!"};
char * action_text_81 = {"I NEED THE OARS"};
char * action_text_82 = {"OF THE BOAT!"};
char * action_text_91 = {"BLIMEY! I'LL ASK"};
char * action_text_92 = {"YE AGAIN LATER!"};
char * action_text_97 = {"NOT SURE,CHECK AGAIN!"};
char * action_text_98 = {"TRY AGAIN, NOT SURE."};
char * action_text_99 = {"WELL,ALREADY GOT ONE."};
char * action_text_100 = {"L-R/DOWN:"};
char * action_text_101 = {"-  RECEIVED  KEYS  -"};
char * action_text_102 = {"THE TICKET FOR THE"};
char * action_text_103 = {"FERRY, HOORAY!"};
char * action_text_104 = {"LET'S SCAPE NOW!"};
char * action_text_111 = {"POCKETS:"};
char * action_text_114 = {"I DON'T NEED MORE!"};
char * action_text_115 = {"A COCONUT FELL DOWN!"};
char * action_text_116 = {"IT'S NEAR THE SHIP!"};
char * action_text_117 = {"I NEED A CANNONBALL!"};
char * action_text_118 = {"FIRE IN THE HOLE!"};
 
// CONVERSATION TEXTS CHARACTERS
char * texts_start_conv []={
"AHOY, MATEY!","YE SEEM BORED...",
"AHOY, CAPTAIN!","MAY I HELP YE?",
"DO YE MAKE POTIONS,","OR SOMETHING ELSE?",
"AHOY COOK! WHAT","DO YE HAVE TODAY?",
"AHOY, LASSIE! ARE YE","DOIN' YER DUTIES?",
"I'D DARE TO SAY YE","SUNBATHED TOO MUCH!",
"INDEED I AM! I'D LIKE","TO HAVE SOME FUN!",
"MATEY, I AM LOOKING","FOR A TREASURE!",
"DIDN'T YE MEET THE","VOODOO LOOKOUT I DID?",
"SCRAMBLED EGGS! WELL,","IF I FIND MY TOOLS.",
"AYE MA'AM! BUT NO ONE","LISTENS TO ME!",
"DO YE THINK SO? I","FEEL VERY HEALTHY!",
"I CAN'T FIND MY","GOOD LUCK CHARM!",
"HAVE YE SEEN LONG JOHN","SILVER? FIND HIM!",
"I'VE LOST A VERY","IMPORTANT ARTIFACT!",
"CAN YE HELP ME? I'VE","LOST THE COOKBOOK!",
"MY PRECIOUS PET","IS LOST!!!",
"HAVE YE SEEN","MY SPYGLASS?",
"OH MATEY, YE MADE ME","HAPPY! HERE'S MY KEY!",
"READY TO GO! THAN YE","MATEY, YE HAVE MY KEY!",
"SINK ME! YE FIND IT!","MY KEY IS YERS!",
"YO HO HO! LUNCH WILL","BE READY!HERE,MY KEY!",
"OH MA'AM, YE HELPED ME","SO MUCH! HAVE MY KEY!",
"I'D CRY BUT I HAVE NO","EYES! MY KEY, FOR YE!"
};

char * texts_initial_explanation []={
"SIGH,I SHOULD'VE DONE","THE BANANA BOAT TRIP!",
"RECOVER THE TICKET", "FOR THE FERRY FROM",
"THE BOOTY CHEST.", "THE PIRATES HAVE",
"THE KEYS: GAIN THEIR", "RESPECT. LET'S TALK",
"TO EVERYBODY AND","SEARCH FOR KNOWLEDGE.",
"I CAN REMEMBER ONLY","3 PIECES OF INFO.",
"MY POCKETS STORE THE","LAST 3 ITEMS I FOUND.",
"WHEN I REVISIT A ROOM","THERE'S NEW INFO.",
"BASKETS AND CHESTS","HIDE LOTS OF THINGS.",
"SEARCH MORE THAN","ONCE. LET'S GO!"
};

char * text_game_over []={
"##                        ##",
"    AAARRR! HANG'ER FROM    ",
"  THE YARDARM!  GAME OVER!  ",
"##                        ##",
};

char * texts_taking_icons []={
"AYE, AYE!",
"DON'T TOUCH IT OR YE","WILL FEED THE FISHES!",
"I'LL TAKE THIS...","I'LL PUT IT HERE...",
"NOTHING TO GET/PUT,"
};

char * texts_things []={
"I TOOK A JAR OF GROG!","I'VE FOUND A COCONUT!",
"A VOODOO POTION!","OH, AN UNFAIR DICE!",
"I'VE FOUND A HOOK!","AHA! VOODOO NEEDLES.",
"AH, A WOODEN SPOON.","WHAT? A FAKE BEARD!",
"A VOODOO DOLL!","THE OARS OF THE BOAT!",
"","",
"I TOOK A CANNONBALL!",""
};

char * garbo_text []={
"TO THE ISLAND! ROW,","ROW, ROW THE BOAT...!"
};

char * end_text []={
"CONGRATULATIONS!","FINALLY WE DID IT!",
"IT WAS A NIGHTMARE!", "WAIT, THIS FERRY IS",
"THE FLYING DUTCHMAN?","A GHOST SHIP? NOOO!"
};

char * first_conv_cabin_boy []={
"CORSAIRS ARE SUPPOSED",
"TO BE RUDE! JUST TRY!",
"GULP. I'LL TRY, ERR...",
"AAARR!!! AAAARR...?",
"WELL...NEVER MIND."
};

char * texts_start_joke []={
"I'VE SEEN PRAWNS","FUNNIER THAN YE!",
"THIS SHIP IS A DUMP!","WHAT A MESS!",
"DO YE PRACTICE","BODYPAINTING? LOL!",
"IS THAT AN EGG ON","YER HEAD...?",
"YE SHOULD GO BACK","TO KINDERGARDEN, LOL!",
"YE ARE TOO SKINNY","TO BE A LOOKOUT!",
"SAY THAT AGAIN AND YE","WILL MEET THE PRAWNS!",
"DEAD MEN TELL NO TALES","SAVVY? -GRUNT-",
"SAY IT AGAIN AND YE","WILL DANCE WITH JACK!",
"PLEASE DON'T ASK ME,","IT'S A SAD HISTORY!",
"DON'T SAY THAT AGAIN","MA'AM OR I'LL BE BAD!",
"OH, LAUGHING AT ME","DESERVES A CORRECTION!",
"SURE TAR! THEN, MEET","THE PRAWNS!",
"BY JOLLY ROGER, THAT","WAS TOO MUCH!",
"PLEASE,ENJOY THIS HEAD", "SHRINKING POTION!",
"THAT HURT MY FEELINGS!","GOOD BYE, SCALLYWAG!",
"BOOHOOO! -SOB-","CAPTAIN SOOOCKS!",
"ENOUGH! ENJOY THE","BOTTOM OF THE SEA!"
};

char * texts_given []={
"BLOW ME DOWN! YE ARE","VERY KIND, MATEY!",//UNFAIR DICE
"AVAST YE! WITH THIS","HOOK I'LL BE FEARED!",//HOOK
"THANK YE! THESE ARE","MY WORKING TOOLS!",//VOODOO NEEDLES
"OH, I WAS LOOKING FOR","IT, THANK YE!",//WOODEN SPOON
"SO GENTLE! EVERYBODY","WILL RESPECT ME NOW!",//FAKE BEARD
"I FEEL THAT THIS WILL","KEEP ME AWAKE, THANKS!",//VOODO DOLL
"BY JOLLY ROGER! I DO","NOT NEED THIS!", // BORED BUCCANEER
"THIS ISN'T VERY","USEFUL, MATEY!", // CAPT. SOCKS
"I CAN'T DO ANYTHING","WITH THIS!!", // VOODOO PRIESTESS
"NOT VERY USEFUL, LAD.","I'LL KEEP IT HERE!", // COOK
"I DON'T KNOW WHAT TO","DO WITH IT, MA'AM.", // CABIN BOY
"LANDLUBBER GIRL! THIS","IS USELESS TO ME!", // LOOKOUT
"GROG, THE WATER OF THE","SEADOGS! GLUGLUGLUG...", // BORED BUCCANEER
"HERE'S TO YE, LITTLE","LASSIE! GLUGLUGLUG...", // CAPT. SOCKS
"VOODOO MAGICAL DRINK?","GROG IT IS! GLUGLUG...", // VOODOO PRIESTESS
"THANKS MATEY! I WILL","ADD IT TO THE STEW!", // COOK
"THANK YE MA'AM! I LOVE","COCONUT WATER!", // CABIN BOY
"I WAS THIRSTY!","WHAT A STRANGE COLOR!" // LOOKOUT
};

char * texts_start_knew_didnt_knew_it []={
"NOT FUNNY! YE REPEAT","YERSELF VERY MUCH!",
"I HEARD THAT HISTORY","LONG TIME AGO, TAR.",
"ANY VOODOO APPRENTICE","KNOWS THOSE THIGS!",
"YER CHITCHAT IS BORING","HAVE YE DRINK GROG?",
"MA'AM, EVERYBODY KNOWS","THAT! EVEN ME!",
"ER, WELL... YES...","SO...?",
"OH, FINALLY SOMETHING","FUNNY! THANK YE!",
"AYE, I CAN SMELL THE","DOUBLOONS, LASSIE!",
"THAT KNOWLEDGE WILL","MAKE ME WISER!",
"OH, I DIDN'T KNOW","THAT RECIPE! THANKS!",
"SHIVER ME TIMBERS!","MA'AM THAT'S AMAZING!",
"OH, THANKS! I DIDN'T","SEE THAT ONE COMING!"
};
	
char * texts_things_reduced []={
"\"",//GROG
"#",//A COCONUT
"$",//VOODOO BEVERAGE
"=",//DICES
";",//GARFIO
"&",//ALFILERES
"(",//CUCHARA PALO
")",//BARBA DE PALO
"%",//MUNYECO VUDU
"^",//OARS OF THE BOAT
"<",//SILHOUETTE OF A SHIP
">",//ARROW UP
"@",//CANONBALL
"["//SHIP FRAME DRAWING
};

char * texts_start_do_not_care []={
"THAT MADE ME FEEL","WORST! SIGH!",
"MORE BAD ADVICES AND","YE'LL BE SHARK BAIT!",
"SIGH, I SHOULD USE YE","AS MY ZOMBIE SLAVE!",
"ARE YE RUNNING A RIG","ON ME, PRIVATEER?",
"MA'AM THAT'S NONSENSE","IN BASIC!",
"NOT USEFUL AT ALL,","SCURVY DOG!",	
};

//https://en.wikipedia.org/wiki/Category:Voodoo_gods
//https://www.piratevoyages.com/pirate-lingo/
//https://www.history.com/news/8-real-life-pirates-who-roved-the-high-seas
//https://www.nationalgeographic.com/culture/food/the-plate/2014/08/19/eat-like-a-pirate/
char * texts_fans []={
"THERE IS A TREASURE","AT COCONUTS ISLAND!",		//n_pant=3
"WALK 90 STEPS TO THE","EAST AND HEAD SOUTH.",		//n_pant=3
"PRAY TO DIEJUSTE AND","SLING YER HOOK!",			//n_pant=4		
"L'INGLESOU WILL CRUSH","THOSE TELLING SECRETS",	//n_pant=4		
"PLAYING MARIASCH IS ","VERY AMUSING!",				//n_pant=2
"SIR FRANCIS DRAKE IS","A LEGENDARY PIRATE!",		//n_pant=6
"L'OLONNAIS IS A VERY","CRAZY BUCCANEER!",			//n_pant=6
"LET'S PLAY A BONE-ACE","GAME WITH THE MATEYS!",	//n_pant=2
"DICES ARE A","MUST FOR A PIRATE!",					//n_pant=2
"LET'S THROW SOME","KNIVES TO THE MAST!",			//n_pant=2
"BREAD AND BEEF","IS A DAILY NEED!",				//n_pant=5
"A DOLLOP OF BUTTER","AND CHEESE, YUMMY!",			//n_pant=5
"WE CAN SING SOME","PIRATE CHANTEYS!",				//n_pant=2
"SAIL, HO! A SHIP IS","COMING CLOSER!",				//n_pant=7
"THAR SHE BLOWS! A BIG","WHALE TO THE NORTH!",		//n_pant=7
"WALK 15 STEPS AHEAD,","GO DOWN THE HILL.",			//n_pant=3
"THERE IS A SHOVEL IN","THE CAVE, TAKE IT!",		//n_pant=3
"JOLLY ROGER WILL MARK","THE CHEST OF GOLD!",		//n_pant=3
"MARINE SALT, TRITON","EYES:SEASICKNESS BYE!",		//n_pant=4
"TO AVOID DEADLY RAINS","TO MOMBU YE'LL PRAY!",		//n_pant=4
"WILLIAM DAMPIER MADE","A PIRATE'S COOKBOOK!",		//n_pant=5
"OGUN, GIVE US RUM!","AND MIGHTY SWORDS!",			//n_pant=4
"COCONUT WATER IS GOOD","FOR COOKING BEEF STEW",	//n_pant=5
"OH, MY FAVOURITE DISH","IS SALMAGUNDI!",			//n_pant=5
"HENRY MORGAN ATTACKED","PUERTO PRINCIPE!",			//n_pant=6
"CAPT. KIDD IS FEARED","BY THE EAST COMPANY!",		//n_pant=6
"MADAME CHENG RULED","OVER 70000 PIRATES!",			//n_pant=6
"LAND AHOY!!!","COCONUTS ISLAND!",					//n_pant=7
"AHOY! STRIKE COLORS!","THEY SURRENDER!",			//n_pant=7
"A RED ENSIGN! BRING A","SPRING UPON'ER!"			//n_pant=7
};
#else

// SPANISH VERSION ;)

// MENU
char * texts_menu []={
"::  MOON Y LOS PIRATAS  ::","1. TECLADO.",
"2. KEMPSTON JOYSTICK.","3. SINCLAIR JOYSTICK.",
"4. ANDROID JOYSTICK.","5. TEXTOS: ",
"AUTOSCROLL.   ",
"HECHO CON MGA-MK POR","GITHUB.COM / IADVD","2019",
"PULSA ESPACIO."
};

	
// ACTION TEXTS
char * status_perso []={
"\\",
"*",
"AMISTAD   : ",
"NECESITA  : ",
"SEDIENTO  : "
};

char * texts_interact []={
"                          ","HABLA CON LOBO DE MAR","+AL FERRY!",
"COGE/DEJA ICONO","HABLA CON OFICIAL","HABLA/DA A BUCANERO",
"HABLA/DA A CAP. SOCKS","HABLA/DA A HECHICERA","HABLA/DA A COCINERO",
"ABRE EL COFRE DEL TESORO","HABLA/DA A GRUMETE","HABLA/DA A VIGIA",
"LEE EL MAPA DEL TESORO","MIRA EN EL AGUA","ABRE LA CESTA",
"LEE EL DIARIO DEL CAPITAN","ABRE EL ARCON",
"+COGE UNA JARRA DE GROG!","+EL BILLETE PARA EL FERRY!","+UN AMULETO!+EL OJO TURCO!",
"+UN LORO GRACIOSO!","+UNA CALAVERA MISTERIOSA!","UN LIBRO DE COCINA",
"UNA RATITA","EL CATALEJO DEL CORSARIO","COGE UNA BOLA DE CA_ON",
"A LA CUBIERTA INFERIOR","A LA SEGUNDA CUBIERTA","A LA CUBIERTA SUPERIOR",
"A LA COFA","BAJAR A LA CUBIERTA","A ISLA DE COCOS",
"AL BARCO","+DISPARA EL CA_ON!","REBUSCA EN EL BARRIL"
};


// CONVERSATION TEXTS GENERIC

char * action_text_24 = {"+SALUDOS, AMIGO!"};
char * action_text_25 = {"]ALGUNA NOVEDAD...?"};
char * action_text_28 = {"+TODAVIA NO TENGO"};
char * action_text_29 = {"UN BILLETE!"};
char * action_text_39 = {"+POR VENTURA! ]SABES"};
char * action_text_40 = {"ALGO INTERESANTE...?"};
char * action_text_46 = {"                     "};
char * action_text_47 = {"+INTENTARE AYUDARTE!"};
char * action_text_66 = {"+TODAVIA NO TENGO"};
char * action_text_67 = {"LAS LLAVES!"};
char * action_text_81 = {"+NECESITO LOS REMOS"};
char * action_text_82 = {"DEL BOTE!"};
char * action_text_91 = {"+RAYOS! TE PREGUNTO"};
char * action_text_92 = {"MAS LUEGO, +GRACIAS!"};
char * action_text_97 = {"+REBUSCA UN POCO MAS!"};
char * action_text_98 = {"MMM...MIRA OTRA VEZ."};
char * action_text_99 = {"+NO NECESITO DOS!"};
char * action_text_100 = {"I-D/ABJO:"};
char * action_text_101 = {"- LLAVES RECIBIDAS -"};
char * action_text_102 = {"EL BILLETE PARA EL"};
char * action_text_103 = {"FERRY, +BIEEEN!"};
char * action_text_104 = {"+HUYAMOS AHORA!"};
char * action_text_111 = {"LLEVAS :"};
char * action_text_114 = {"+NO NECESITO MAS!"};
char * action_text_115 = {"+CAYO UN COCO Y"};
char * action_text_116 = {"LLEGO HASTA EL BARCO!"};
char * action_text_117 = {"]Y LA BOLA DE CA_ON?"};
char * action_text_118 = {"+FUEGOOO!"};
 
char * texts_taking_icons []={
"+A LA ORDEN!",
"+SI LO TOCAS IRAS","A LOS TIBURONES!",
"COGERE ESTO...","PONDRE ESTO AQUI...",
"NADA QUE COGER/DEJAR,"
};

// CONVERSATION TEXTS CHARACTERS
char * texts_start_conv []={
"+SALUDOS, AMIGO!","PARECES ABURRIDO...",
"+SALUDOS, CAPITAN!","]PUEDO AYUDAR?",
"]CREAS SOLO POCIONES,","O MAS COSAS?",
"+COCINERO! ]QUE VAS","A PREPARAR HOY?",
"+HOLA,GRUMETE! ]ESTAS","HACIENDO TU LABOR?",
"OSARIA DECIR QUE","TOMASTE MUCHO SOL...",
"+LO ESTOY! NECESITO","DIVERTIRME UN POCO...",
"AMIGA, +ESTOY","BUSCANDO UN TESORO!",
"]NO HAS VISTO EL","VIGIA VUDU QUE HICE?",
"+HUEVOS REVUELTOS!","SI LOS ENCUENTRO...",
"+SI HE_ORA, PERO","NADIE MESCUCHA!",
"]VOS CREEIS? +ME","SIENTO SANISIMO!",
"NO ENCUENTRO MI","AMULETO DE LA SUERTE.",
"]HAS VISTO A LONG JOHN","SILVER? BUSCALO...",
"HE PERDIDO UN OBJETO","MUY IMPORTANTE...",
"]PUEDES AYUDARME? HE","PERDIDO EL RECETARIO...",
"MI QUERIA MAJCOTA","TA NALGUN SITIO...",
"]VIO MI CATALEJO EN","ALGUN LUGAR?",
"+OH AMIGO, ME HICISTE","FELIZ! +MI LLAVE!",
"+LISTO PARA PARTIR!","+TOMA MI LLAVE!",
"+ALBRICIAS!+MI CALIZ!","+MI LLAVE ES TUYA!",
"+SII!+LA COMIDA ESTARA","LISTA! +TEN MI LLAVE!",
"+HE_ORA, MAYUDASTE","MUSHO!+TENGA MI LLAVE!",
"+LLORARIA SI TUVIERA","OJOS! +TOME MI LLAVE!"
};

char * texts_initial_explanation []={
"+AY! +DEBERIA HABER","IDO AL BOTE BANANA!",
"RECUPERA EL BILLETE", "PARA EL FERRY DEL",
"COFRE DEL TESORO.", "LOS PIRATAS TIENEN",
"LAS LLAVES: GANATE SU", "RESPETO.",
"HABLEMOS CON TODOS:","CONSIGUE INFORMACION.",
"SOLO PUEDO RECORDAR","3 DATOS A LA VEZ.",
"SOLO PUEDO LLEVAR","3 COSAS Y UN ICONO.",
"CUANDO VUELVO A UN","LUGAR HAY INFO NUEVA.",
"LAS CESTAS Y COFRES","TIENEN MUCHAS COSAS.",
"BUSCA MAS DE UNA VEZ.","+VAMOS!"
};

char * texts_start_joke []={
"+HE VISTO GAMBAS MAS","ALEGRES QUE TU!",
"+ESTE BARCO ES UN","VERTEDERO! +QUE ASCO!",
"VA, EL VERDE ES","PINTURA, ]A QUE SI?",
"]LLEVAS UN HUEVO EN","LA CABEZA? ]EN SERIO?",
"DEBERIAS VOLVER A LA","GUARDERIA, +JUAS!",
"+DEMASIADO ESMIRRIADO","PARA SER VIGIA!",
"+DILO DE NUEVO Y","VERAS A LAS GAMBAS!",
"LOS MUERTOS NO CUENTAN","CUENTOS, ]SABES? -GRR-",
"+DILO OTRA VEZ Y TE ","COLGARE DEL MASTIL!",
"ES ALGO TRAUMATICO...","PREFIERO OLVIDARLO...",
"+NO DIGA EHO DE NUEVO","HE_ORA, O SERE MALO!",
"+OH, SE RIE ME MI!","+MERECE UN CASTIGO!",
"+CLARO QUE SI!+PUES A","VISITAR A LAS GAMBAS!",
"+POR LOS SIETE MARES,","YA ES SUFICIENTE!",
"+DISFRUTA ESTA POCION", "REDUCTORA DE CABEZAS!",
"+ESO ME DOLIO!","+ADIOS MEQUETREFE!",
"+BUAAAAA! -SNIF-","+CAPITAN SOOOCKS!",
"+INSOLENTE GRUMETE!","+AL FONDO DEL MAR!"
};

char * text_game_over []={
"###                      ###",
"   +ARRRRR! +QUE LA PASEN   ",
"    POR LA QUILLA! +FIN!    ",
"###                      ###",
};

char * texts_things []={
"+UNA JARRA DE GROG!","+ENCONTRE UN COCO!",
"+UNA POCION VUDU!","OH,UN DADO TRUCADO...",
"OH, +HAY UN GARFIO!","+HUY! AGUJAS VUDU.",
"+UNA CUCHARA DE PALO!","]+UNA BARBA FALSA!?",
"+UN MU_ECO VUDU!","+REMOS PARA LA BARCA!",
"","",
"+UNA BOLA DE CA_ON!",""
};

char * texts_given []={
"+QUE ME ASPEN, GANARE","MUCHA PLATA!",//UNFAIR DICE
"+ALBRICIAS! +CON ESTE","GARFIO SERE TEMIDO!",//HOOK
"+MIS HERRAMIENTAS DE","TRABAJO, GRACIAS!",//VOODOO NEEDLES
"OH, +LO ESTABA","BUSCANDO, GRACIAS!",//WOODEN SPOON
"+QUE GENTIL,TOL MUNDO","ME REJPETARA!",//FAKE BEARD
"+SIENTO QUE ESTO ME","MANTENDRA DESPIERTO!",//VOODO DOLL
"+POR NEPTUNO!","+NO LO NECESITO!", // BORED BUCCANEER
"+ESTO NO ES MUY","UTIL COMPA_ERA!", // CAPT. SOCKS
"+NO PUEDO HACER","NADA CON ESTO!", // VOODOO PRIESTESS
"NO ES UTIL, AMIGA.","LO GUARDARE AQUI...", // COOK
"+NO SE CACER CON","EJTO HE_ORA!", // CABIN BOY
"+RENACUAJA! +ESTO","NO VALE PARA NADA!", // LOOKOUT
"+EL AGUA DE LOS LOBOS","DE MAR! GLUGLUGLU...", // BORED BUCCANEER
"+A TU SALUD,INTREPIDA","GRUMETILLA! GLUGLU...", // CAPT. SOCKS
"+GROG, MAGICA BEBIDA!","GLUGLUGLU...", // VOODOO PRIESTESS
"+GRACIAS AMIGA! +LO","A_ADIRE AL ESTOFADO!", // COOK
"+GRACIA HE_ORA! +AMO","L'AGUA DE COCO!", // CABIN BOY
"+ESTABA SEDIENTO!","+QUE EXTRA_O COLOR!" // LOOKOUT
};

char * texts_start_knew_didnt_knew_it []={
"+ABURRIDO! TE REPITES","MUCHO, +BAH!",
"OI ESA HISTORIA HACE","TIEMPO, MARINERA.",
"+TODO APRENDIZ DE","VUDU SABE ESAS COSAS!",
"]PERO QUE DICES?","]HAS TOMADO GROG?",
"HE_ORA,TOL MUNDO SABE","ESO, +YO TAMBIE!",
"PUES SI, BUENO...","]]]Y QUE...???",
"+POR FIN ME DIVIERTO!","+GRACIAS!",
"+YA PUEDO OLER EL","ORO, GRUMETILLA!",
"+ESE CONOCIMIENTO ME","HARA MAS SABIA!",
"OH, +NO CONOCIA ESA","RECETA! +GRACIAS!",
"+POR EL TRIDENTE DE ","NEPTUNO! +ALUSINANTE!",
"+OH, GRACIAS! +NO ME","DI CUENTA A TIEMPO!"
};
	
char * first_conv_cabin_boy []={
"+LOS CORSARIOS DEBEN",
"SER RUDOS!+INTENTALO!",
"GLUP. BUENO, EJTOO...",
"+AAARR! ]AAAARR...?",
"BAH...OLVIDALO..."
};

char * garbo_text []={
"+A LA ISLA! +A REMAR,","MARINERO DE SAN JUAN!"
};

char * end_text []={
"+FELICIDADES,LOGRAMOS","HUIR DEL BARCO!",	
"++VAMONOS!! ]COMO?","EL FERRY SE LLAMA...",
"]EL HOLANDES ERRANTE?","+++NOOOOOOOO...!!!"
};

char * texts_things_reduced []={
"\"",//GROG
"#",//A COCONUT
"$",//VOODOO BEVERAGE
"=",//DICES
";",//GARFIO
"&",//ALFILERES
"(",//CUCHARA PALO
")",//BARBA DE PALO
"%",//MUNYECO VUDU
"^",//OARS OF THE BOAT
"<",//SILHOUETTE OF A SHIP
">",//ARROW UP
"@",//CANONBALL
"["//SHIP FRAME DRAWING
};

char * texts_start_do_not_care []={
"ESO ME HIZO SENTIR","PEOR... +AY!",
"+COMO SIGAS ASI SERAS","CEBO DE TIBURON!",
"+AY,DEBERIA HACERTE MI","ESCLAVA ZOMBI!",
"]ME ESTAS TOMANDO EL","PELO, CORSARIA?",
"HE_ORA, ESO NO TIE ","SENTIO EN BASIC...",
"+NO ME INTERESA NADA,","PEQUE_A PETIMETRE!",
};

//https://en.wikipedia.org/wiki/Category:Voodoo_gods
//https://www.piratevoyages.com/pirate-lingo/
//https://www.history.com/news/8-real-life-pirates-who-roved-the-high-seas
//https://www.nationalgeographic.com/culture/food/the-plate/2014/08/19/eat-like-a-pirate/
char * texts_fans []={
"+HAY UN TESORO EN","ISLA DE COCOS!",				//n_pant=3
"CAMINA 90 PASOS AL","ESTE Y VE AL SUR.",			//n_pant=3
"+REZA A DIEJUSTE","Y LEVA ANCLAS!",				//n_pant=4		
"L'INGLESOU ANIQUILARA","A LOS TRAIDORES.",			//n_pant=4		
"+MARIASCH ES UN JUEGO","MUY ENTRETENIDO!",			//n_pant=2
"+SIR FRANCIS DRAKE ES","UN PIRATA LEGENDARIO!",	//n_pant=6
"+L'OLONNAIS ES UN","BUCANERO PELIGROSO!",			//n_pant=6
"+JUGUEMOS UN BONE-ACE","CON LOS COLEGAS!",			//n_pant=2
"+PARA UN PIRATA JUGAR","DADOS ES ALGO BASICO!",		//n_pant=2
"+LANCEMOS CUCHILLOS","AL MASTIL!",					//n_pant=2
"CARNE Y PAN TODOS","LOS DIAS COMERAS...",			//n_pant=5
"UN TROZO DE QUESO Y","MANTEQUILLA, +RICOO!",		//n_pant=5
"+PODEMOS CANTAR","CANCIONES PIRATA!",				//n_pant=2
"+BARCO A LA VISTA!","+SE ACERCA UN NAVIO!",		//n_pant=7
"+POR ALLI SOPLA! +UNA","BALLENA AL NORTE!",		//n_pant=7
"CAMINA 15 PASOS RECTO","Y BAJA LA COLINA.",		//n_pant=3
"HAY UNA PALA EN","LA CUEVA, +COGELA!",				//n_pant=3
"+LA BANDERA PIRATA","SE_ALA EL TESORO!",			//n_pant=3
"SAL MARINA, OJOS DE","MERO,+ADIOS AL MAREO!",		//n_pant=4
"A MOMBU REZARAS Y","LAS LLUVIAS PARARAS.",			//n_pant=4
"WILL DAMPIER ESCRIBIO","UN RECETARIO PIRATA.",		//n_pant=5
"+OGUN, DANOS RON!","+Y TEMIBLES ESPADAS!",			//n_pant=4
"+EL AGUA DE COCO ES","BUENA PARA UN GUISO!",		//n_pant=5
"+MI PLATO FAVORITO","ES...SALMAGUNDI!",			//n_pant=5
"+HENRY MORGAN ATACO","PUERTO PRINCIPE!",			//n_pant=6
"TEMIDO ES EL CAP.KIDD","POR LOS INGLESES...",		//n_pant=6
"+MADAME CHENG REINO","SOBRE 70000 PIRATAS!",		//n_pant=6
"+TIEERRA A LA VISTAA!","+ISLA DE COCOS!",			//n_pant=7
"+ARRIAN LA BANDERA!","+EL ENEMIGO SE RINDE!",		//n_pant=7
"+INSIGNIA ENEMIGA!","+TODO A BABOR!"				//n_pant=7
};
	
#endif
