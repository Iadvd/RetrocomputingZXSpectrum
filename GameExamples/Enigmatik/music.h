#asm

; *****************************************************************************
; * Special FX Music Player Engine
; *
; * Based on code written by Jonathan Smith for the Special FX game, Firefly.
; * Modified by Chris Cowley
; *
; * Produced by Beepola v1.08.01
; ******************************************************************************
 
MUSICSTART:     DI
                EXX
                PUSH  HL                    ; Preserve HL'' for return to BASIC
                CALL  PLAY_MUSIC
                IM    1
                POP   HL
                EXX
                EI
                RET

PLAY_MUSIC:
                CALL  MAKE_VECTOR_TABLE
                CALL  INIT_ISR
                IM    2
                LD    A,65024 / 256
                LD    I,A

                LD    HL,MUSICDATA         ;  <- Pointer to Music Data. Change
                                           ;     this to play a different song
                LD    E,(HL)
                INC   HL
                LD    D,(HL)
                INC   HL
                LD    (NEXT_PATT_PTR),HL
                LD    (NEXT_PERC_PATT_PTR),DE
                LD    (SAVED_SP),SP
                LD    HL,PLAYER_ISR
                LD    ($FFF5),HL           ; Set up the JP instruction to point
                                           ; to our player ISR
                LD    A,0
                LD    (OUT_VAL1),A         ; Beeper out values for chan1
                LD    (OUT_VAL2),A         ; Beeper out values for chan1
                LD    (OUT_VAL3),A         ; Beeper out values for chan2
                LD    (OUT_VAL4),A         ; Beeper out values for chan2
				CALL  SET_NEXT_PATT
                CALL  SET_NEXT_PERC_PATT
                LD    C,$01
                EXX
                LD    BC,$0101
                EI
                HALT
NEXT_NOTE:      // some lively animation BEGIN
				push hl
				ld hl,22528+(32*13)+12
				ld a,(hl)
				cp 64
				jp c,ESMENOR
				//esmayor
				sub 64
				jp CONT_MUS
				ESMENOR: add 64
				CONT_MUS: 
				ld (hl),a
				ld hl,22528+(32*1)+8
				ld (hl),a
				ld hl,22528+(32*8)+29
				ld (hl),a
				pop hl
				// some lively animation END
				CALL  C,LF02C 
                LD    A,B
                OR    A
                JR    NZ,LEF99
LEF61:          DEFB  $21               ; LD HL,nn
CURR_PATT_CH1:
                DEFW  $0000             ; Current Pattern for chan1
LEF64:          LD    A,(HL)
                OR    A
                JP    M,LEB9B           ; bit7 set - command (sustain, pattern end, etc)
                CALL  LF0F6
                LD    (LEFA2),A
                SRL   A
                SRL   A
                SRL   A
                LD    D,A
                LD    (LEFAD),A
                XOR   A
                LD    (LF02D),A
                INC   A
                LD    (LEFA4),A
                LD    A,(OUT_VAL1)      ; Adjust the EAR and MIC bits of this
                OR    $18               ; port output value for the tone
                LD    (OUT_VAL1),A      ; generator
                INC   HL
POST_MUTE1:     LD    A,(HL)
                LD    (LEF96),A
                INC   HL
                LD    (CURR_PATT_CH1),HL
                DEFB  $06               ; LD    B,n
LEF96:          DEFB  $54
                JR    LEF9E
LEF99:          LD    A,$03
LEF9B:          DEC   A
                JR    NZ,LEF9B
LEF9E:          DEC   D
                JR    NZ,LEFB5

                DEFB  $16               ; LD D,n
LEFA2:          DEFB  $3B
                DEFB  $3E               ; LD A,n
LEFA4:          DEFB  $07
LEFA5:          DEC   A
                JR    NZ,LEFA5

                DEFB  $3E               ; LD A,n
OUT_VAL1:       DEFB  $0
                OUT   ($FE),A
                DEFB  $3E               ; LD A,n
LEFAD:          DEFB  $01               ; frequency counter for CH1
LEFAE:          DEC   A
                JR    NZ,LEFAE

                DEFB  $3E               ; LD A,n
OUT_VAL2:       DEFB  $00
                OUT   ($FE),A
LEFB5:          LD    A,C
                OR    A
                JR    NZ,LEFEF

                DEFB  $21               ; LD HL,nn
CURR_PATT_CH2:  DEFW  $0000             ; Current pattern for CH2
LEFBC:          LD    A,(HL)
                OR    A
                JP    M,LEBA6           ; bit7 set - command (sustain, pattern end, etc)
                CALL  LF0F6
                LD    (LEFF9),A
                SRL   A
                SRL   A
                LD    (LF004),A
                LD    E,A
                XOR   A
                LD    (LF045),A
                INC   A
                LD    (LEFFB),A
                LD    A,(OUT_VAL3)
                OR    $18
                LD    (OUT_VAL3),A
                INC   HL
POST_MUTE2:     LD    A,(HL)
                LD    (LEFEC),A
                INC   HL
                LD    (CURR_PATT_CH2),HL
                DEFB  $0E               ; LD C,n
LEFEC:          DEFB  $0E
                JR    LEFF4

LEFEF:          LD    A,$03
LEFF1:          DEC   A
                JR    NZ,LEFF1
LEFF4:          DEC   E
                JP    NZ,NEXT_NOTE

                DEFB  $1E               ; LD E,n
LEFF9:          DEFB  $3B
                DEFB  $3E               ; LD A,n
LEFFB:          DEFB  $02
LEFFC:          DEC   A
                JR    NZ,LEFFC

                DEFB  $3E               ; LD A,n
OUT_VAL3:       DEFB  $18
                OUT   ($FE),A
                DEFB  $3E               ; LD A,n
LF004:          DEFB  $0D               ; ch2 note frequency
LF005:          DEC   A
                JR    NZ,LF005

                DEFB  $3E
OUT_VAL4:       DEFB  $0
                OUT   ($FE),A
                JP    NEXT_NOTE

LF00F:
                POP   HL
                LD    A,(HL)
                LD    (LF033),A
                INC   HL
                JP    LEF64

LF018:          POP   HL
                LD    A,(HL)
                LD    (LF04B),A
                INC   HL
                JR    LEFBC

MUTE_CH1:       POP   HL
                LD    A,(OUT_VAL1)
                AND   $07
                LD    (OUT_VAL1),A
                JP    POST_MUTE1

MUTE_CH2:       POP   HL
                LD    A,(OUT_VAL3)
                AND   $07
                LD    (OUT_VAL3),A
                JP    POST_MUTE2
NULL_NOTE1:     POP   HL
                JP    POST_MUTE1
NULL_NOTE2:     POP   HL
                JP    POST_MUTE2

LF021:
                POP   HL
                CALL  SET_NEXT_PATT
                JP    LEF61

LF02C:          DEFB  $3E
LF02D:          DEFB  $00
                INC   A
                LD    (LF02D),A
                DEFB  $FE               ; CP
LF033:          DEFB  $02
                JR    C,LF044
                XOR   A
                LD    (LF02D),A
                LD    HL,LEFAD
                DEC   (HL)
                JR    Z,LF043
                LD    HL,LEFA4
LF043:          INC   (HL)

LF044:          DEFB  $3E               ; LD A,n
LF045:          DEFB  $00
                INC   A
                LD    (LF045),A
                DEFB  $FE               ; CP
LF04B:          DEFB  $04
                RET   C
                XOR   A
                LD    (LF045),A
                LD    HL,LF004
                DEC   (HL)
                JR    Z,LF05A
                LD    HL,LEFFB
LF05A:          INC   (HL)
                RET

LF0F6:          PUSH  HL
                PUSH  DE
                LD    HL,FREQ_TABLE
                LD    E,A
                LD    D,$0
                ADD   HL,DE
                LD    A,(HL)
                POP   DE
                POP   HL
                RET
				
; ** Reads and sets up the next melody pattern to play
SET_NEXT_PATT:
               DEFB  $21   ; LD HL,nn
NEXT_PATT_PTR: DEFW  $0000              ; holds a pointer to the
                                        ; next pattern in the patter list
GET_PATT_ADDR: LD    E,(HL)
               INC   HL
               LD    D,(HL)
               INC   HL
               LD    A,E
               OR    D
               JR    NZ,STORE_NEXT_P
               JP    ISR_KEY_PRESSED
STORE_NEXT_P:  LD    (NEXT_PATT_PTR),HL
               EX    DE,HL
               LD    E,(HL)
               INC   HL
               LD    D,(HL)
               INC   HL
               LD    (CURR_PATT_CH1),HL
               LD    (CURR_PATT_CH2),DE
               RET

; ** Reads and sets up the next percussion pattern to play
SET_NEXT_PERC_PATT:
               DEFB  $21   ; LD HL,nn
NEXT_PERC_PATT_PTR:
               DEFW  $0000
GET_PERC_ADDR: LD    E,(HL)
               INC   HL
               LD    D,(HL)
               INC   HL
               LD    (NEXT_PERC_PATT_PTR),HL
               LD    (PERC_PATT),DE
               LD    A,E
               OR    D
               RET   NZ
               LD    E,(HL)
               INC   HL
               LD    D,(HL)
               EX    DE,HL
               JR    GET_PERC_ADDR
               CALL  SET_NEXT_PERC_PATT
               JR    PLAY_PERC

LEB9B:
               INC   HL
               PUSH  HL
               AND   $7F
               CALL  JUMP_PERC_ADDR
               DEFW  LF021
               DEFW  LF00F
               DEFW  MUTE_CH1
               DEFW  NULL_NOTE1

LEBA6:         INC   HL
               PUSH  HL
               AND   $7F
               CALL  JUMP_PERC_ADDR
               DEFW  LF021
               DEFW  LF018
               DEFW  MUTE_CH2
               DEFW  NULL_NOTE2

PLAY_PERC:
               DEFB  $21                   ; LD HL,nn
PERC_PATT:     DEFW  $0000                 ; Address of the percussion data
               LD    A,(HL)
               INC   HL
               LD    C,(HL)
               INC   HL
               LD    (PERC_PATT),HL        ; Point PERC_PATT at next datum
               AND   $7F
               CALL  JUMP_PERC_ADDR
               DEFW  DRUM00                ; F094
               DEFW  DRUM01                ; F09A
               DEFW  DRUM02                ; F0AC
               DEFW  DRUM03                ; F0BB
               DEFW  DRUM04                ; F0D4
               DEFW  DRUM05                ; F07C

JUMP_PERC_ADDR:
               POP   HL                    ; F0ED
               ADD   A,A
               ADD   A,L
               LD    L,A
               LD    A,(HL)
               INC   HL
               LD    H,(HL)
               LD    L,A
               JP    (HL)

DRUM00:        CALL  SET_NEXT_PERC_PATT
               JR    PLAY_PERC

DRUM01:        LD    E,$0A
               LD    A,0
               LD    HL,$0100
DRUM01NOISE:   XOR   $18
               OUT   ($FE),A
               LD    B,(HL)
DRUM01LOOP:    DJNZ  DRUM01LOOP
               INC   HL
               DEC   E
               JR    NZ,DRUM01NOISE
               RET

DRUM02:        LD    HL,$005A
DRUM02LOOP:    LD    A,(HL)
               OR    A
               RET   Z
               AND   $18
               OR    0
               OUT   ($FE),A
               INC   HL
               JR    DRUM02LOOP

DRUM03:        LD    HL,$0F18
               LD    D,$0A
DRUM03LOOP3:   LD    B,(HL)
DRUM03LOOP:    DJNZ  DRUM03LOOP
               LD    A,$18
               OR    0
               OUT   ($FE),A
               INC   HL
               LD    B,(HL)
DRUM03LOOP2:   DJNZ  DRUM03LOOP2
               LD    A,0
               OUT   ($FE),A
               INC   HL
               DEC   D
               JR    NZ,DRUM03LOOP3
               RET

DRUM04:        LD    E,$3F
               LD    D,$05
DRUM04LOOP3:   LD    B,E
DRUM04LOOP:    DJNZ  DRUM04LOOP
               LD    A,$18
               OR    0
               OUT   ($FE),A
               LD    A,E
               RRCA
               LD    E,A
               LD    B,A
DRUM04LOOP2:   DJNZ  DRUM04LOOP2
               LD    A,0
               OUT   ($FE),A
               DEC   D
               JR    NZ,DRUM04LOOP3
DRUM05:        RET

; ** Creates a vector table of 257 0xFF bytes at the location specified
; ** by VECTOR_TABLE_LOC
MAKE_VECTOR_TABLE:
                LD    HL,65024
                LD    DE,65024 + 1
                LD    BC,$0100
                LD    (HL),$FF
                LDIR
                RET

; *** The IM 2 service routine active throughout the life of the player
; *** updates counters, plays any active percussion sounds, and checks for
; *** keypresses or Kempston joystick fire button to terminate
PLAYER_ISR:
                PUSH  AF
                PUSH  DE
                PUSH  HL
                DEC   C
                DEC   B
                EXX
                DEC   C
                CALL  Z,PLAY_PERC          ; EBB1
                ; Read keyboard
                XOR   A
                
				push hl
				push de				
				push bc
				push af
				call _read_keys_helper
				pop af
				pop bc
				pop de
				pop hl
				
				IN    A,($FE)
                CPL
                AND   $1F
				JR    NZ,ISR_KEY_PRESSED
                XOR   A
                IN    A,($1F)
                BIT   5,A
                JR    NZ,END_PLAYER_ISR
                BIT   4,A
                JR    NZ,ISR_FIRE_PRESSED
END_PLAYER_ISR: EXX
                POP   HL
                POP   DE
                POP   AF
                SCF
                EI
				RETI
ISR_FIRE_PRESSED:
ISR_KEY_PRESSED:
                DEFB  $31                  ; LD SP,nn
SAVED_SP:       DEFW  $0000                ;
                EI
                RETI

; ** Sets up everything for our IM2 service routine. Specifically, copies a JR
; ** instruction to $FFFF and a JP $F0FF to $FFF4
INIT_ISR:
                LD    HL,$FFFF
                LD    (HL),$18               ; Copies in our JR for JR FFF4
                LD     HL,$FFF4
                LD    (HL),$C3               ; JP (jump address filled-in
                                             ; during player initialization)
                RET


; *** DATA ***
FREQ_TABLE:          DEFB $FD,$EE,$E1,$D4,$C8,$BD,$B2,$A8,$9F,$96,$8E,$86,$7E
                     DEFB $77,$70,$6A,$64,$5E,$59,$54,$4F,$4B,$47,$43,$3F
                     DEFB $3B,$38,$35,$32,$2F,$2C,$2A,$27,$25,$23,$21,$1F
                     DEFB $1D,$1C,$1B,$19,$17,$16,$15,$13,$12,$11,$10,$0F
                     DEFB $0E,$0D,$0C,$01,$00


MUSICDATA:        DEFW      PERCSTART
SONGSTART:        DEFW      PAT0
                  DEFW      PAT1
                  DEFW      PAT2
                  DEFW      PAT3
                  DEFW      PAT4
                  DEFW      PAT5
                  DEFW      PAT6
                  DEFW      PAT7
                  DEFW      PAT4
                  DEFW      PAT5
                  DEFW      PAT6
                  DEFW      PAT7
                  DEFW      $0000
                  DEFW      SONGSTART

PAT0:     DEFW  PAT0C2
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB $80
PAT0C2:
     DEFB 131,7
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,7
     DEFB $80
PAT1:     DEFW  PAT1C2
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB $80
PAT1C2:
     DEFB 131,7
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,7
     DEFB $80
PAT2:     DEFW  PAT2C2
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB $80
PAT2C2:
     DEFB 131,7
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,7
     DEFB $80
PAT3:     DEFW  PAT3C2
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB $80
PAT3C2:
     DEFB 131,7
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,7
     DEFB $80
PAT4:     DEFW  PAT4C2
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB 6,14
     DEFB $80
PAT4C2:
     DEFB 18,7
     DEFB 18,7
     DEFB 18,7
     DEFB 13,7
     DEFB 16,7
     DEFB 18,7
     DEFB 16,7
     DEFB 13,7
     DEFB 18,7
     DEFB 16,7
     DEFB 13,7
     DEFB 13,7
     DEFB 11,7
     DEFB 13,7
     DEFB 16,7
     DEFB 18,7
     DEFB $80
PAT5:     DEFW  PAT5C2
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB 9,14
     DEFB $80
PAT5C2:
     DEFB 18,7
     DEFB 16,7
     DEFB 13,7
     DEFB 23,7
     DEFB 23,7
     DEFB 21,7
     DEFB 18,7
     DEFB 21,7
     DEFB 18,7
     DEFB 23,7
     DEFB 21,7
     DEFB 18,7
     DEFB 16,7
     DEFB 13,7
     DEFB 11,7
     DEFB 13,7
     DEFB $80
PAT6:     DEFW  PAT6C2
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB 11,14
     DEFB $80
PAT6C2:
     DEFB 23,7
     DEFB 23,7
     DEFB 23,7
     DEFB 21,7
     DEFB 18,7
     DEFB 21,7
     DEFB 23,7
     DEFB 18,7
     DEFB 21,7
     DEFB 23,7
     DEFB 21,7
     DEFB 18,7
     DEFB 21,7
     DEFB 18,7
     DEFB 16,7
     DEFB 13,7
     DEFB $80
PAT7:     DEFW  PAT7C2
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB 13,14
     DEFB $80
PAT7C2:
     DEFB 25,7
     DEFB 23,7
     DEFB 20,7
     DEFB 23,7
     DEFB 25,7
     DEFB 20,7
     DEFB 23,7
     DEFB 28,7
     DEFB 25,7
     DEFB 23,7
     DEFB 25,7
     DEFB 23,7
     DEFB 20,7
     DEFB 18,7
     DEFB 16,7
     DEFB 13,7
     DEFB $80
PERCSTART:   DEFW      DRM0
             DEFW      DRM0
             DEFW      DRM0
             DEFW      DRM0
             DEFW      DRM4
             DEFW      DRM4
             DEFW      DRM4
             DEFW      DRM4
             DEFW      DRM4
             DEFW      DRM4
             DEFW      DRM4
             DEFW      DRM4
             DEFW      $0000
             DEFW      PERCSTART

DRM0:
     DEFB 133,14
     DEFB 130,28
     DEFB 130,28
     DEFB 130,21
     DEFB 130,7
     DEFB 130,14
     DEFB $80
DRM4:
     DEFB 129,14
     DEFB 130,14
     DEFB 129,14
     DEFB 130,14
     DEFB 129,14
     DEFB 130,14
     DEFB 129,14
     DEFB 130,14
     DEFB $80
	 
#endasm