/* C source file created by SevenuP v1.20                                */
/* SevenuP (C) Copyright 2002-2006 by Jaime Tejedor Gomez, aka Metalbrain*/

/*
GRAPHIC DATA:
Pixel Size:      (256,  64)
Char Size:       ( 32,   8)
Sort Priorities: Char line, X char, Y char
Data Outputted:  Gfx+Attr
Interleave:      Sprite
Mask:            No
*/

unsigned char tileset[2304] = {
  0,  0,  0,  0,  0,  0,  0,  0,
 64, 64, 64, 64, 64,  0, 64,  0,
 32,252, 32, 60,106,178,100,  0,
  0,136,132,130,130, 80, 32,  0,
124,  0,124,130,  2,  4,112,  0,
 60,  0,124,  8, 24, 40, 70,  0,
 32,244, 34, 60, 98,162,108,  0,
 32, 32,244, 42, 74, 72,176,  0,
 16,124,  8,126, 36, 64, 60,  0,
  4,  8, 48, 64, 48,  8,  4,  0,
136,136,190,136,136,136, 16,  0,
  0,124,  0,  0, 64,128,126,  0,
  0,  0,  0,  0,  0, 64, 32,  0,
  0,  0,  0, 96,146, 12,  0,  0,
  0,  0,  0,  0, 32, 80, 32,  0,
 16, 16,254, 16, 72,128,120,  0,
 64, 64, 64, 64, 64, 68, 56,  0,
  8,254, 24, 40, 24,  8, 16,  0,
 36, 36,254, 36, 44, 32, 30,  0,
 60,  8, 16,126, 16, 16, 12,  0,
 32,240, 46, 64, 72, 80,142,  0,
 16,252, 32, 56, 68,  4, 56,  0,
  0, 60,194,  2,  2,  2, 60,  0,
 14,116,  8, 16, 16,  8,  6,  0,
 32, 32, 38, 24, 32, 64, 62,  0,
 32,244, 34, 68,156, 38, 24,  0,
  0,  0, 56,196,  4,  4, 56,  0,
128,156,128,128,144,160,158,  0,
  8, 72, 92,106,178,166, 86,  0,
 32, 44,242, 34,102,170, 36,  0,
  0, 56, 84,146,162, 68, 24,  0,
 60, 66,  2, 12, 16,  0, 16,  0,
132,132,190,132,156,164,154,  0,
 40,228, 38, 68, 68, 68, 56,  0,
 16,  8, 16, 16, 76, 74,178,  0,
  0, 32, 80,136,  6,  0,  0,  0,
128,190,136,190,136,188,186,  0,
  8,126,  8,126,  8,124,122,  0,
112, 16, 36,124,166,196, 24,  0,
 32,244, 34, 96,160, 98, 60,  0,
  8, 72, 92,106,178,162, 84,  0,
 16,124, 32,124, 34, 34, 28,  0,
 72, 92,226, 36, 32, 16, 16,  0,
 16,188,210,146,188, 16, 32,  0,
  8,  8, 14,  8, 56, 76, 50,  0,
 56,128,176,200,  4,  4,120,  0,
  0, 68, 68, 84,100, 68,  8,  0,
124,  8, 28, 34, 74, 20,  8,  0,
 32, 32,232, 52,100,166, 32,  0,
124,  8, 28, 34, 66,  4, 24,  0,
 32, 44,242, 34, 98,162, 44,  0,
 16,124, 32,118,152, 40, 30,  0,
 16, 16, 32, 32, 80, 82,140,  0,
  0, 80, 88,228, 40, 32, 16,  0,
  0, 32,176,232,168, 48, 64,  0,
  0, 16, 16, 24,112,144,104,  0,
160,160,160,  0,  0,  0,  0,  0,
 64,160, 64,  0,  0,  0,  0,  0,
  0,  0, 16, 48, 16, 16, 56,  0,
  0,  0, 48,  8, 16, 32, 56,  0,
  0,  0, 48,  8, 16,  8, 48,  0,
  0, 32,240, 40, 96,144,104,  0,
  0,  0, 56, 68, 68, 68, 56,  0,
  0,  0, 68, 40, 16, 40, 68,  0,
119,136,128, 64, 35, 67, 74,143,
248,  4,  2,  2,153,253,117, 37,
 13,199,230,243,220,159, 63, 36,
 37,253, 10,247, 15,253,220, 34,
 32, 64,130,132,128,128,136,145,
 17, 33,  1,  5,  1, 97,241, 49,
130,138,154,158,163, 95, 44, 23,
209,213,221,253, 26,250,244,136,
240,239,207,191,123,109,119,127,
 31,231,251,173,254,254,222,190,
125,105,105,104,120,124,191,223,
 22, 22, 22,  5, 69, 11, 31,239,
  0, 21, 63, 45,109,112,191,  0,
  0,180,218, 85,218,181,170, 21,
109,109,119,127, 94, 97, 63, 31,
 80,170,239,213,237,218,182, 52,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  7,  4,  4,  4,  4,  4,  4,  4,
  4,  4,  4,  4,  4,  4,  4,  4,
  4,  4,  4,  4,  4,  4,  4,  4,
  4,  4,  4,  4,  4,  4,  4,  4,
  4,  4,  4,  4,  4,  4,  4,  4,
  4,  4,  4,  4,  4,  4,  4,  4,
  4,  4,  4,  4,  4,  4,  4,  4,
  4,  4,  4,  4,  4,  4,  4,  4,
 71, 71, 69, 69, 68, 68, 70, 70,
 96, 96,112,112, 69, 69, 70, 70,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6,
  6,  6,  6,  6,  6,  6,  6,  6};