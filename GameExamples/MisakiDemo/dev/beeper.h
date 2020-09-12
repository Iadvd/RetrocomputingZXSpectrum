// Churrera Engine
// ===============
// Copyleft 2010, 2011, 2012, 2013 by The Mojon Twins

// beeper.h
// Cointains Beeper sound effects

// Most effects have been taken off BeepFX's demo project.
// So I guess they should be credited to Shiru again ;)

#asm

.sound_play
   
   ld hl, soundEffectsData   ;address of sound effects data

   ;di
   push iy

   ld b,0
   ld c,a
   add hl,bc
   add hl,bc
   ld a,(hl)
   inc hl
   ld h,(hl)
   ld l,a
   push hl
   pop ix         ;put it into ix

.readData
   ld a,(ix+0)      ;read block type
   or a
   jr nz,readData_sound
   pop iy
   ;ei
   ret
   
.readData_sound
   ld c,(ix+1)      ;read duration 1
   ld b,(ix+2)
   ld e,(ix+3)      ;read duration 2
   ld d,(ix+4)
   push de
   pop iy

   dec a
   jr nz,sfxRoutineNoise



;this routine generate tone with many parameters

.sfxRoutineTone
   ld e,(ix+5)      ;freq
   ld d,(ix+6)
   ld a,(ix+9)      ;duty
   ld (sfxRoutineTone_duty + 1),a
   ld hl,0

.sfxRoutineTone_l0
   push bc
   push iy
   pop bc
.sfxRoutineTone_l1
   add hl,de
   ld a,h
.sfxRoutineTone_duty
   cp 0
   sbc a,a
   and 16
.sfxRoutineTone_border
   or 0
   out ($fe),a

   dec bc
   ld a,b
   or c
   jr nz,sfxRoutineTone_l1

   ld a,(sfxRoutineTone_duty + 1)
   add a,(ix+10)   ;duty change
   ld (sfxRoutineTone_duty + 1),a

   ld c,(ix+7)      ;slide
   ld b,(ix+8)
   ex de,hl
   add hl,bc
   ex de,hl

   pop bc
   dec bc
   ld a,b
   or c
   jr nz,sfxRoutineTone_l0

   ld c,11
.nextData
   add ix,bc      ;skip to the next block
   jr readData

;this routine generate noise with two parameters

.sfxRoutineNoise
   ld e,(ix+5)      ;pitch

   ld d,1
   ld h,d
   ld l,d
.sfxRoutineNoise_l0
   push bc
   push iy
   pop bc
.sfxRoutineNoise_l1
   ld a,(hl)
   and 16
.sfxRoutineNoise_border
   or 0
   out ($fe),a
   dec d
   jr nz,sfxRoutineNoise_l2
   ld d,e
   inc hl
   ld a,h
   and $1f
   ld h,a
.sfxRoutineNoise_l2
   dec bc
   ld a,b
   or c
   jr nz,sfxRoutineNoise_l1

   ld a,e
   add a,(ix+6)   ;slide
   ld e,a

   pop bc
   dec bc
   ld a,b
   or c
   jr nz,sfxRoutineNoise_l0

   ld c,7
   jr nextData
   
.soundEffectsData
   defw soundEffectsData_sfx0
   defw soundEffectsData_sfx1
   defw soundEffectsData_sfx2
   defw soundEffectsData_sfx3
   defw soundEffectsData_sfx4
   defw soundEffectsData_sfx5
   defw soundEffectsData_sfx6
   defw soundEffectsData_sfx7
   
.soundEffectsData_sfx0
   defb 1 ;tone
   defw 20,50,2000,65486,128
   defb 0
.soundEffectsData_sfx1
   defb 1 ;tone
   defw 10,100,2000,100,128
   defb 0
.soundEffectsData_sfx2
   defb 1 ;tone
   defw 100,20,500,2,128
   defb 0
.soundEffectsData_sfx3
   defb 1 ;tone
   defw 50,100,200,65531,128
   defb 0
.soundEffectsData_sfx4
   defb 1 ;tone
   defw 1,1000,1000,0,128
   defb 1 ;pause
   defw 1,1000,0,0,0
   defb 1 ;tone
   defw 1,2000,2000,0,128
   defb 1 ;tone
   defw 1,2000,2000,0,16
   defb 0
.soundEffectsData_sfx5
   defb 1 ;tone
   defw 5,2000,200,100,128
   defb 0
.soundEffectsData_sfx6
   defb 1 ;tone
   defw 20,500,200,5,272
   defb 1 ;pause
   defw 1,1000,0,0,0
   defb 1 ;tone
   defw 30,500,200,8,272
   defb 0
.soundEffectsData_sfx7
   defb 1 ;tone
   defw 10,500,400,0,128
   defb 1 ;tone
   defw 10,500,400,0,128
   defb 1 ;tone
   defw 10,1000,450,0,128
   defb 1 ;tone
   defw 10,1000,400,0,128
   defb 1 ;tone
   defw 10,1000,530,0,128
   defb 1 ;tone
   defw 10,2000,510,0,128
   /* if not enough room cut here :) BEGIN */
   defb 1 ;tone
   defw 10,500,400,0,128
   defb 1 ;tone
   defw 10,500,400,0,128
   defb 1 ;tone
   defw 10,1000,450,0,128
   defb 1 ;tone
   defw 10,1000,400,0,128
   defb 1 ;tone
   defw 10,1000,600,0,128
   defb 1 ;tone
   defw 10,2000,530,0,128
   /* if not enough room cut here :) END */
   defb 0
   
/*
   TABLA DE SONIDOS

   n   Sonido
   ----------
   0	twitt/pio
   1	twitt/pio
   2	volar/flap
   3	hostion/bump
   4	get coins / pillar monedas
   5    get heart /  pillar corazon
   6    surprise / sorpresa   
   7    happy birthday
*/
   
peta_el_beeper: 
	  push ix
      push iy
      call sound_play
      pop ix
      pop iy
	  ret
	  
#endasm

int aux_peb5(void){
	#asm
		ld a,5
		call peta_el_beeper
	#endasm																				
}

int aux_peb4(void){
	#asm
		ld a,4
		call peta_el_beeper
	#endasm																				
}

int play_frequence(void){
	#asm // around 30 bytes
		// Credits: https://www.chibiakumas.com/z80/platform3.php#LessonP23
		//ld a,10
		ld h,a
		xor a
		loopy:
			push af
			ld a,(_gpit3)
			ld d,a
			pop af
			xor d; //18 S-BBB S=Sound B=Border
			out (254),a //&fe
			ld bc,(_asm_int_d) //; Lower number = high pitch
			push af
			ld a,h
			dec a
			jp z,finish_sound
			ld h,a
			pop af
		pausey:
			dec c
			jr nz,pausey
			dec b
			jr nz, pausey
			jr loopy
		finish_sound:
			pop af
	#endasm
}
				