// Config.h
// Churrera v.4
// Copyleft 2010, 2011 The Mojon Twins

// ============================================================================
// I. General configuration
// ============================================================================

// In this section we define map dimmensions, initial and authomatic ending conditions, etc.

#define MAP_W					9		//
#define MAP_H					1		// Map dimmensions in screens
#define SCR_INICIO				6		// Initial screen 6
#define PLAYER_INI_X			13		//
#define PLAYER_INI_Y			3		// Initial tile coordinates
#define SCR_FIN 				99		// Last screen. 99 = deactivated.
#define PLAYER_FIN_X			99		//
#define PLAYER_FIN_Y			99		// Player tile coordinates to finish game
#define PLAYER_NUM_OBJETOS		99		// Objects to get to finish game
#define PLAYER_LIFE 			99		// Max and starting life gauge. //35
#define PLAYER_REFILL			99		// Life recharge

// ============================================================================
// II. Engine type
// ============================================================================

// This section is used to define the game engine behaviour. Many directives are related,
// and others are mutually exclusive. I think this will be pretty obvious when you look at them. 

// Right now the shooting engine is only compatible with the side-view engine.

// Bounding box size
// -----------------
										// Comment both for normal 16x16 bounding box
#define BOUNDING_BOX_8_BOTTOM			// 8x8 aligned to bottom center in 16x16

// General directives:
// -------------------

#define PLAYER_AUTO_CHANGE_SCREEN		// Player changes screen automaticly (no need to press direction)
#define DIRECT_TO_PLAY				    // If defined, title screen is also the game frame.
#define DEACTIVATE_KEYS				// If defined, keys are not present.
#define DEACTIVATE_OBJECTS			// If defined, objects are not present.
#define DEACTIVATE_EVIL_TILE			// If defined, no killing tiles (behaviour 1) are detected.
#define FULL_BOUNCE						// If defined, evil tile bounces equal MAX_VX, otherwise v/2

// ============================================================================
// III. Screen configuration
// ============================================================================

// This sections defines how stuff is rendered, where to show counters, etcetera

#define VIEWPORT_X				1		//
#define VIEWPORT_Y				8		// Viewport character coordinates 14

// ============================================================================
// IV. Player movement configuration
// ============================================================================

// This section is used to define which constants are used in the gravity/acceleration engine.
// If a side-view engine is configured, we have to define vertical and horizontal constants
// separately. If a top-view engine is configured instead, the horizontal values are also
// applied to the vertical component, vertical values are ignored.

// IV.1. Vertical movement. Only for side-view.

#define PLAYER_MAX_VY_CAYENDO	512 	// Max falling speed (512/64 = 8 pixels/frame)
#define PLAYER_G				48		// Gravity acceleration (32/64 = 0.5 píxeles/frame^2)

#define PLAYER_VY_INICIAL_SALTO 96		// Initial junp velocity (64/64 = 1 píxel/frame)
#define PLAYER_MAX_VY_SALTANDO	312 	// Max jump velocity (320/64 = 5 píxels/frame)
#define PLAYER_INCR_SALTO		48		// acceleration while JUMP is pressed (48/64 = 0.75 píxeles/frame^2)

#define PLAYER_INCR_JETPAC		32		// Vertical jetpac gauge
#define PLAYER_MAX_VY_JETPAC	256 	// Max vertical jetpac speed

// IV.2. Horizontal (side view) or general (top view) movement.

#define PLAYER_MAX_VX			256 	// Max velocity (192/64 = 3 píxels/frame)
#define PLAYER_AX				48		// Acceleration (24/64 = 0,375 píxels/frame^2)
#define PLAYER_RX				64		// Friction (32/64 = 0,5 píxels/frame^2)

// ============================================================================
// V. Tile behaviour
// ============================================================================

// Defines the behaviour for each tile. Remember that if keys are activated, tile #15 is a bolt
// and, therefore, it should be made a full obstacle!

// 0 = Walkable (no action)
// 1 = Walkable and kills.
// 2 = Walkable and hides.
// 4 = Platform (only stops player if falling on it)
// 8 = Full obstacle (blocks player from all directions)
// 10 = special obstacle (pushing blocks OR locks!)
//unsigned char comportamiento_tiles [] = {
//	0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//};

//#define SPANISH_VER					// Spanish version! ;)
