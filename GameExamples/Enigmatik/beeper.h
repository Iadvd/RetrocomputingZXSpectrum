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
   defw soundEffectsData_sfx8
   
.soundEffectsData_sfx0
   defb 2 ;noise
   defw 80,2000,33025
   defb 0
.soundEffectsData_sfx1
   defb 1 ;tone
   defw 10,300,10000,65531,1294
   defb 0
.soundEffectsData_sfx2
   defb 1 ;tone
   defw 30,100,10000,65486,52736
   defb 0
.soundEffectsData_sfx3
   defb 1 ;tone
   defw 5,600,2000,900,39956
   defb 0
.soundEffectsData_sfx4
   defb 1 ;tone
   defw 20,150,800,65516,40036
   defb 0
.soundEffectsData_sfx5
   defb 1 ;tone
   defw 5,2000,200,100,128
   defb 0
.soundEffectsData_sfx6
   defb 1 ;tone
   defw 50,100,200,65531,128
   defb 0
.soundEffectsData_sfx7  
   defb 1 ;tone
   defw 1,1000,1000,0,128
   defb 1 ;pause
   defw 1,1000,0,0,0
   defb 1 ;tone
   defw 1,2000,2000,0,128
   defb 1 ;tone
   defw 1,2000,2000,0,16
   defb 0
.soundEffectsData_sfx8
   defb 1 ;tone
   defw 7000,40,1,1,63231
   defb 0
     
   Sample0Data:
	defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
	defb 255,255,255,255,255,255,255,255,255,255,247,247,255,237,219,182
	defb 105,239,190,251,125,107,237,107,90,214,251,90,215,107,125,174
	defb 214,107,181,218,236,247,107,183,221,174,215,74,165,82,169,90
	defb 173,85,170,85,169,90,181,173,107,86,189,246,171,219,90,213
	defb 235,233,90,182,190,173,91,218,218,181,106,171,90,214,181,107
	defb 86,181,237,90,213,171,171,86,245,173,90,170,149,173,42,234
	defb 86,170,245,107,74,250,214,191,213,173,170,251,87,234,182,212
	defb 170,181,109,107,107,85,234,213,74,223,90,218,155,91,235,93
	defb 106,173,117,172,189,87,255,239,91,235,173,117,238,189,126,174
	defb 253,213,191,189,245,223,183,215,123,235,85,111,174,189,122,173
	defb 237,189,111,174,181,119,173,239,173,122,238,251,215,122,171,254
	defb 247,222,182,245,253,251,238,255,215,255,239,213,255,174,181,85
	defb 253,235,175,85,171,175,111,95,234,239,93,94,175,239,93,122
	defb 239,91,87,250,251,83,122,222,245,87,94,219,213,106,238,251
	defb 222,250,203,91,234,174,235,155,59,95,91,234,255,91,223,250
	defb 223,87,250,174,183,214,253,191,173,251,223,85,221,255,91,253
	defb 255,213,247,95,109,123,235,239,95,95,255,187,254,235,247,223
	defb 239,175,191,255,191,255,255,247,255,253,127,191,255,247,254,255
	defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
	defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
	defb 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
	defb 255,255
	
/*
   TABLA DE SONIDOS

   n   Sonido
   ----------
   0	end
   1	p
   2	g
   3	s
   4	r
   5    take
   6 	heartbit
   7	detect
   8	siren
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

int aux_peb7(void){
	#asm
		ld a,7
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
				