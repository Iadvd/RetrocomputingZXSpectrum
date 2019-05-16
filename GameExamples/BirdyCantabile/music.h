#asm
; *****************************************************************************
; * Phaser1 Engine, with synthesised drums
; *
; * Original code by Shiru - .http//shiru.untergrund.net/
; * Modified by Chris Cowley
; *
; * Produced by Beepola v1.05.01
; ******************************************************************************

; MUSICDATA = birdycantabileInitial
; MUSICDATA2 = birdycantabileInitialStart
 
.musicstart
             LD    HL,MUSICDATA         ;  <- Pointer to Music Data. Change
			 JP    COMMON_ENGINE
.musicstart2
             LD    HL,MUSICDATA2         ;  <- Pointer to Music Data Win. Change
			 JP    COMMON_ENGINE										
.musicstart3
             LD    HL,MUSICDATA3         ;  <- Pointer to Music Data Win. Change
			 JP    COMMON_ENGINE										
.musicstart4
             LD    HL,MUSICDATA4         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcert0
             LD    HL,MUSICDATACONCERT0         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcert1
             LD    HL,MUSICDATACONCERT1         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcert2
             LD    HL,MUSICDATACONCERT2         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcert3
             LD    HL,MUSICDATACONCERT3         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcert4
             LD    HL,MUSICDATACONCERT4         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcert5
             LD    HL,MUSICDATACONCERT5         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcert6
             LD    HL,MUSICDATACONCERT6         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcert7
             LD    HL,MUSICDATACONCERT7         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcertB0
             LD    HL,MUSICDATACONCERTB0         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcertB1
             LD    HL,MUSICDATACONCERTB1         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcertB2
             LD    HL,MUSICDATACONCERTB2         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcertB3
             LD    HL,MUSICDATACONCERTB3         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcertB4
             LD    HL,MUSICDATACONCERTB4         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcertB5
             LD    HL,MUSICDATACONCERTB5         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcertB6
             LD    HL,MUSICDATACONCERTB6         ;  <- Pointer to Music Data Win. Change			
			 JP    COMMON_ENGINE										
.musicstartConcertB7
             LD    HL,MUSICDATACONCERTB7         ;  <- Pointer to Music Data Win. Change			
		 
.common_engine
             LD   A,(HL)                         ; Get the loop start pointer
             LD   (PATTERN_LOOP_BEGIN),A
             INC  HL
             LD   A,(HL)                         ; Get the song end pointer
             LD   (PATTERN_LOOP_END),A
             INC  HL
             LD   E,(HL)
             INC  HL
             LD   D,(HL)
             INC  HL
             LD   (INSTRUM_TBL),HL
             LD   (CURRENT_INST),HL
             ADD  HL,DE
             LD   (PATTERN_ADDR),HL
             XOR  A
             LD   (PATTERN_PTR),A                ; Set the pattern pointer to zero
             LD   H,A
             LD   L,A
             LD   (NOTE_PTR),HL                  ; Set the note offset (within this pattern) to 0

.player
             DI
             PUSH IY
             ;LD   A,BORDER_COL
             xor a
             LD   H,$00
             LD   L,A
             LD   (CNT_1A),HL
             LD   (CNT_1B),HL
             LD   (DIV_1A),HL
             LD   (DIV_1B),HL
             LD   (CNT_2),HL
             LD   (DIV_2),HL
             LD   (OUT_1),A
             LD   (OUT_2),A
             JR   MAIN_LOOP

; ********************************************************************************************************
; * NEXT_PATTERN
; *
; * Select the next pattern in sequence (and handle looping if weve reached PATTERN_LOOP_END
; * Execution falls through to PLAYNOTE to play the first note from our next pattern
; ********************************************************************************************************
.next_pattern
                          LD   A,(PATTERN_PTR)
                          INC  A
                          INC  A
                          DEFB $FE                           ; CP n
.pattern_loop_end         DEFB 0
                          JR   NZ,NO_PATTERN_LOOP
                          ; Handle Pattern Looping at and of song
                          DEFB $3E                           ; LD A,n
.pattern_loop_begin       DEFB 0
						  JP   EXIT_PLAYER
.no_pattern_loop          LD   (PATTERN_PTR),A
                          LD   HL,$0000
                          LD   (NOTE_PTR),HL   ; Start of pattern (NOTE_PTR = 0)

.main_loop
             LD   IYL,0                        ; Set channel = 0

.read_loop
             LD   HL,(PATTERN_ADDR)
             LD   A,(PATTERN_PTR)
             LD   E,A
             LD   D,0
             ADD  HL,DE
             LD   E,(HL)
             INC  HL
             LD   D,(HL)                       ; Now DE = Start of Pattern data
             LD   HL,(NOTE_PTR)
             INC  HL                           ; Increment the note pointer and...
             LD   (NOTE_PTR),HL                ; ..store it
             DEC  HL
             ADD  HL,DE                        ; Now HL = address of note data
             LD   A,(HL)
             OR   A
             JR   Z,NEXT_PATTERN               ; select next pattern

             BIT  7,A
             JP   Z,RENDER                     ; Play the currently defined note(S) and drum
             LD   IYH,A
             AND  $3F
             CP   $3C
             JP   NC,OTHER                     ; Other parameters
             ADD  A,A
             LD   B,0
             LD   C,A
             LD   HL,FREQ_TABLE
             ADD  HL,BC
             LD   E,(HL)
             INC  HL
             LD   D,(HL)
             LD   A,IYL                        ; IYL = 0 for channel 1, or = 1 for channel 2
             OR   A
             JR   NZ,SET_NOTE2
             LD   (DIV_1A),DE
             EX   DE,HL

             DEFB $DD,$21                      ; LD IX,nn
.current_inst
             DEFW $0000

             LD   A,(IX+$00)
             OR   A
             JR   Z,L809B                      ; Original code jumps into byte 2 of the DJNZ (invalid opcode FD)
             LD   B,A
.l8098       ADD  HL,HL
             DJNZ L8098
.l809b       LD   E,(IX+$01)
             LD   D,(IX+$02)
             ADD  HL,DE
             LD   (DIV_1B),HL
             LD   IYL,1                        ; Set channel = 1
             LD   A,IYH
             AND  $40
             JR   Z,READ_LOOP                  ; No phase reset

             LD   HL,OUT_1                     ; Reset phaser
             RES  4,(HL)
             LD   HL,$0000
             LD   (CNT_1A),HL
             LD   H,(IX+$03)
             LD   (CNT_1B),HL
             JR   READ_LOOP

.set_note2
             LD   (DIV_2),DE
             LD   A,IYH
             LD   HL,OUT_2
             RES  4,(HL)
             LD   HL,$0000
             LD   (CNT_2),HL
             JP   READ_LOOP

.set_stop
             LD   HL,$0000
             LD   A,IYL
             OR   A
             JR   NZ,SET_STOP2
             ; Stop channel 1 note
             LD   (DIV_1A),HL
             LD   (DIV_1B),HL
             LD   HL,OUT_1
             RES  4,(HL)
             LD   IYL,1
             JP   READ_LOOP
.set_stop2
             ; Stop channel 2 note
             LD   (DIV_2),HL
             LD   HL,OUT_2
             RES  4,(HL)
             JP   READ_LOOP

.other       CP   $3C
             JR   Z,SET_STOP                   ; Stop note
             CP   $3E
             JR   Z,SKIP_CH1                   ; No changes to channel 1
             INC  HL                           ; Instrument change
             LD   L,(HL)
             LD   H,$00
             ADD  HL,HL
             LD   DE,(NOTE_PTR)
             INC  DE
             LD   (NOTE_PTR),DE                ; Increment the note pointer

             DEFB $01                          ; LD BC,nn
.instrum_tbl
             DEFW $0000

             ADD  HL,BC
             LD   (CURRENT_INST),HL
             JP   READ_LOOP

.skip_ch1
             LD   IYL,$01
             JP   READ_LOOP

.exit_player
             LD   HL,$2758
             EXX
             POP  IY
             EI
             RET

.render
             AND  $7F                          ; L813A
             CP   $76
             JP   NC,DRUMS
             LD   D,A
             EXX
             DEFB $21                          ; LD HL,nn
.cnt_1a      DEFW $0000
             DEFB $DD,$21                      ; LD IX,nn
.cnt_1b      DEFW $0000
             DEFB $01                          ; LD BC,nn
.div_1a      DEFW $0000
             DEFB $11                          ; LD DE,nn
.div_1b      DEFW $0000
             DEFB $3E                          ; LD A,n
.out_1       DEFB $0
             EXX
             EX   AF,AF ; beware!
             DEFB $21                          ; LD HL,nn
.cnt_2       DEFW $0000
             DEFB $01                          ; LD BC,nn
.div_2       DEFW $0000
             DEFB $3E                          ; LD A,n
.out_2       DEFB $00

.play_note
             ; Read keyboard
             LD   E,A
             XOR  A
             IN   A,($FE)
             OR   $E0
             INC  A

.player_wait_key
             JR   NZ,EXIT_PLAYER
             LD   A,E
             LD   E,0

.l8168       EXX
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  ($FE),A
             JR   C,L8171
             JR   L8173
.l8171       XOR  $10
.l8173       ADD  IX,DE
             JR   C,L8179
             JR   L817B
.l8179       XOR  $10
.l817b       EX   AF,AF ; beware!
             OUT  ($FE),A
             EXX
             ADD  HL,BC
             JR   C,L8184
             JR   L8186
.l8184       XOR  $10
.l8186       NOP
             JP   L818A

.l818a       EXX
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  ($FE),A
             JR   C,L8193
             JR   L8195
.l8193       XOR  $10
.l8195       ADD  IX,DE
             JR   C,L819B
             JR   L819D
.l819b       XOR  $10
.l819d       EX   AF,AF ; beware!
             OUT  ($FE),A
             EXX
             ADD  HL,BC
             JR   C,L81A6
             JR   L81A8
.l81a6       XOR  $10
.l81a8       NOP
             JP   L81AC

.l81ac       EXX
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  ($FE),A
             JR   C,L81B5
             JR   L81B7
.l81b5       XOR  $10
.l81b7       ADD  IX,DE
             JR   C,L81BD
             JR   L81BF
.l81bd       XOR  $10
.l81bf       EX   AF,AF ; beware!
             OUT  ($FE),A
             EXX
             ADD  HL,BC
             JR   C,L81C8
             JR   L81CA
.l81c8       XOR  $10
.l81ca       NOP
             JP   L81CE

.l81ce       EXX
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  ($FE),A
             JR   C,L81D7
             JR   L81D9
.l81d7       XOR  $10
.l81d9       ADD  IX,DE
             JR   C,L81DF
             JR   L81E1
.l81df       XOR  $10
.l81e1       EX   AF,AF ; beware!
             OUT  ($FE),A
             EXX
             ADD  HL,BC
             JR   C,L81EA
             JR   L81EC
.l81ea       XOR  $10

.l81ec       DEC  E
             JP   NZ,L8168

             EXX
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  ($FE),A
             JR   C,L81F9
             JR   L81FB
.l81f9       XOR  $10
.l81fb       ADD  IX,DE
             JR   C,L8201
             JR   L8203
.l8201       XOR  $10
.l8203       EX   AF,AF ; beware!
             OUT  ($FE),A
             EXX
             ADD  HL,BC
             JR   C,L820C
             JR   L820E
.l820c       XOR  $10

.l820e       DEC  D
             JP   NZ,PLAY_NOTE

             LD   (CNT_2),HL
             LD   (OUT_2),A
             EXX
             EX   AF,AF ; beware!
             LD   (CNT_1A),HL
             LD   (CNT_1B),IX
             LD   (OUT_1),A
             JP   MAIN_LOOP

; ************************************************************
; * DRUMS - Synthesised
; ************************************************************
.drums
             ADD  A,A                          ; On entry A=$75+Drum number (i.e. $76 to $7E)
             LD   B,0
             LD   C,A
             LD   HL,DRUM_TABLE - 236
             ADD  HL,BC
             LD   E,(HL)
             INC  HL
             LD   D,(HL)
             EX   DE,HL
             JP   (HL)

.drum_tone1  LD   L,16
             JR   DRUM_TONE
.drum_tone2  LD   L,12
             JR   DRUM_TONE
.drum_tone3  LD   L,8
             JR   DRUM_TONE
.drum_tone4  LD   L,6
             JR   DRUM_TONE
.drum_tone5  LD   L,4
             JR   DRUM_TONE
.drum_tone6  LD   L,2
.drum_tone
             LD   DE,3700
             LD   BC,$0101
             //LD   A,BORDER_COL
             xor a
.dt_loop0    OUT  ($FE),A
             DEC  B
             JR   NZ,DT_LOOP1
             XOR  16
             LD   B,C
             EX   AF,AF ; beware!
             LD   A,C
             ADD  A,L
             LD   C,A
             EX   AF,AF ; beware!
.dt_loop1    DEC  E
             JR   NZ,DT_LOOP0
             DEC  D
             JR   NZ,DT_LOOP0
             JP   MAIN_LOOP

.drum_noise1 LD   DE,2480
             LD   IXL,1
             JR   DRUM_NOISE
.drum_noise2 LD   DE,1070
             LD   IXL,10
             JR   DRUM_NOISE
.drum_noise3 LD   DE,365
             LD   IXL,101
.drum_noise
             LD   H,D
             LD   L,E
             //LD   A,BORDER_COL
             xor a
             LD   C,A
.dn_loop0    LD   A,(HL)
             AND  16
             OR   C
             OUT  ($FE),A
             LD   B,IXL
.dn_loop1    DJNZ DN_LOOP1
             INC  HL
             DEC  E
             JR   NZ,DN_LOOP0
             DEC  D
             JR   NZ,DN_LOOP0
             JP   MAIN_LOOP

.pattern_addr   DEFW  $0000
.pattern_ptr    DEFB  0
.note_ptr       DEFW  $0000

; **************************************************************
; * Frequency Table
; **************************************************************
.freq_table
             DEFW 178,189,200,212,225,238,252,267,283,300,318,337
             DEFW 357,378,401,425,450,477,505,535,567,601,637,675
             DEFW 715,757,802,850,901,954,1011,1071,1135,1202,1274,1350
             DEFW 1430,1515,1605,1701,1802,1909,2023,2143,2270,2405,2548,2700
             DEFW 2860,3030,3211,3402,3604,3818,4046,4286,4541,4811,5097,5400

; *****************************************************************
; * Synth Drum Lookup Table
; *****************************************************************
.drum_table
             DEFW DRUM_TONE1,DRUM_TONE2,DRUM_TONE3,DRUM_TONE4,DRUM_TONE5,DRUM_TONE6
             DEFW DRUM_NOISE1,DRUM_NOISE2,DRUM_NOISE3


.musicdata
             DEFB 0  ; Pattern loop begin * 2
             DEFB 2  ; Song length * 2
             DEFW 4         ; Offset to start of song (length of instrument table)
             DEFB 1      ; Multiple
             DEFW 0      ; Detune
             DEFB 0      ; Phase
             
.patterndata        DEFW      PAT0

; *** Pattern data - $00 marks the end of a pattern ***
.pat0
         DEFB $BD,0
         DEFB 157
         DEFB 181
         DEFB 119
     DEFB 11
         DEFB $BD,0
         DEFB 159
         DEFB 176
     DEFB 6
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 161
         DEFB 178
         DEFB 119
     DEFB 11
         DEFB 164
         DEFB 159
         DEFB 119
     DEFB 11
         DEFB $00

.musicdata2
             DEFB 0  ; Pattern loop begin * 2
             DEFB 2  ; Song length * 2
             DEFW 4         ; Offset to start of song (length of instrument table)
             DEFB 1      ; Multiple
             DEFW 0      ; Detune
             DEFB 0      ; Phase
             
.patterndata2        DEFW      PATE

; *** Pattern data - $00 marks the end of a pattern ***
.pate
         DEFB $BD,0
         DEFB 180
         DEFB 176
     DEFB 12
         DEFB 181
         DEFB 178
     DEFB 2
         DEFB 180
         DEFB 176
     DEFB 2
         DEFB 181
         DEFB 178
     DEFB 2
         DEFB 180
         DEFB 176
     DEFB 2
         DEFB 181
         DEFB 178
     DEFB 2
         DEFB 180
         DEFB 176
     DEFB 2
         DEFB 181
         DEFB 178
     DEFB 2
         DEFB 180
         DEFB 176
     DEFB 2
         DEFB 181
         DEFB 178
     DEFB 2
         DEFB 180
         DEFB 176
     DEFB 2
         DEFB 181
         DEFB 178
     DEFB 2
         DEFB 183
         DEFB 176
     DEFB 2
         DEFB 185
         DEFB 180
     DEFB 2
         DEFB 183
         DEFB 176
     DEFB 14
         DEFB $00	 
		 
.musicdata3
             DEFB 0  ; Pattern loop begin * 2
             DEFB 2  ; Song length * 2
             DEFW 4         ; Offset to start of song (length of instrument table)
             DEFB 1      ; Multiple
             DEFW 0      ; Detune
             DEFB 0      ; Phase

.patterndata3        DEFW      PATST0

; *** Pattern data - $00 marks the end of a pattern ***
.patst0
         DEFB $BD,0
         DEFB 181
         DEFB 181
     DEFB 3
         DEFB 190
         DEFB 176
     DEFB 3
         DEFB 183
         DEFB 172
     DEFB 3
         DEFB 190
         DEFB 169
     DEFB 3
         DEFB 184
         DEFB 176
     DEFB 3
         DEFB 190
         DEFB 172
     DEFB 3
         DEFB 183
         DEFB 169
     DEFB 3
         DEFB 190
         DEFB 164
     DEFB 3
         DEFB 181
         DEFB 169
     DEFB 3
         DEFB 190
         DEFB 164
     DEFB 3
         DEFB 179
         DEFB 160
     DEFB 3
         DEFB 190
         DEFB 157
     DEFB 3
         DEFB 176
         DEFB 164
     DEFB 3
         DEFB 190
         DEFB 160
     DEFB 3
         DEFB 174
         DEFB 157
     DEFB 3
         DEFB 190
         DEFB 152
     DEFB 3
         DEFB 171
     DEFB 42
         DEFB $00
		 
.musicdata4
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4         ; Offset to start of song (length of instrument table)
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndata4        DEFW      PATDT40

; *** Pattern data - $00 marks the end of a pattern ***
.patdt40
         DEFB $BD,0
         DEFB 185
         DEFB 181
     DEFB 12
         DEFB 181
         DEFB 176
     DEFB 3
         DEFB 183
         DEFB 178
     DEFB 3
         DEFB 181
         DEFB 176
     DEFB 3
         DEFB 180
         DEFB 174
     DEFB 3
         DEFB 178
         DEFB 173
     DEFB 3
         DEFB 176
         DEFB 171
     DEFB 3
         DEFB 181
         DEFB 176
     DEFB 3
         DEFB 174
         DEFB 171
     DEFB 3
         DEFB 173
         DEFB 176
     DEFB 3
         DEFB 173
         DEFB 169
     DEFB 24
         DEFB $00

.musicdataconcert0
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 8         ; Offset to start of song (length of instrument table)
 DEFB 0      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndataconcert0 DEFW      PATCONC0
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconc0
         DEFB $BD,2
         DEFB 181
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 164
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 184
         DEFB 157
     DEFB 6
         DEFB 183
         DEFB 160
     DEFB 6
         DEFB 181
         DEFB 164
     DEFB 6
         DEFB 180
         DEFB 160
     DEFB 6
         DEFB 181
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 176
         DEFB 164
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB $00

.musicdataconcert1
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 8         ; Offset to start of song (length of instrument table)
 DEFB 0      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndataconcert1 DEFW      PATCONC1
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconc1
         DEFB $BD,2
         DEFB 181
         DEFB 157
     DEFB 6
         DEFB 176
         DEFB 160
     DEFB 6
         DEFB 177
         DEFB 150
     DEFB 6
         DEFB 177
         DEFB 153
     DEFB 6
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 177
         DEFB 153
     DEFB 6
         DEFB 177
         DEFB 150
     DEFB 6
         DEFB 181
         DEFB 153
     DEFB 6
         DEFB 177
         DEFB 157
     DEFB 6
         DEFB 179
         DEFB 153
     DEFB 6
         DEFB 176
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB $00

.musicdataconcert2
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 8         ; Offset to start of song (length of instrument table)
 DEFB 0      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndataconcert2 DEFW      PATCONC2
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconc2
         DEFB 190
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 6
         DEFB $BD,2
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 181
         DEFB 157
     DEFB 6
         DEFB 181
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 164
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 184
         DEFB 157
     DEFB 6
         DEFB 183
         DEFB 160
     DEFB 6
         DEFB 181
         DEFB 164
     DEFB 6
         DEFB 180
         DEFB 160
     DEFB 6
         DEFB 181
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB $00

.musicdataconcert3
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 8         ; Offset to start of song (length of instrument table)
 DEFB 0      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndataconcert3 DEFW      PATCONC3
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconc3
         DEFB $BD,2
         DEFB 176
         DEFB 164
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 181
         DEFB 164
     DEFB 6
         DEFB 176
         DEFB 160
     DEFB 6
         DEFB 177
         DEFB 150
     DEFB 6
         DEFB 190
         DEFB 153
     DEFB 6
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 177
         DEFB 153
     DEFB 6
         DEFB 177
         DEFB 150
     DEFB 6
         DEFB 181
         DEFB 153
     DEFB 6
         DEFB 177
         DEFB 157
     DEFB 6
         DEFB 179
         DEFB 153
     DEFB 6
         DEFB $00

.musicdataconcert4
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 8         ; Offset to start of song (length of instrument table)
 DEFB 0      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndataconcert4 DEFW      PATCONC4
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconc4
         DEFB $BD,2
         DEFB 176
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 174
         DEFB 149
     DEFB 6
         DEFB 174
         DEFB 153
     DEFB 6
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 153
     DEFB 6
         DEFB 174
         DEFB 149
     DEFB 6
         DEFB 177
         DEFB 153
     DEFB 6
         DEFB $00

.musicdataconcert5
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 8         ; Offset to start of song (length of instrument table)
 DEFB 0      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndataconcert5 DEFW      PATCONC5
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconc5
         DEFB $BD,2
         DEFB 176
         DEFB 157
     DEFB 6
         DEFB 174
         DEFB 153
     DEFB 6
         DEFB 172
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 169
         DEFB 164
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 172
         DEFB 164
     DEFB 6
         DEFB 169
         DEFB 160
     DEFB 6
         DEFB 171
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 6
         DEFB 171
         DEFB 156
     DEFB 6
         DEFB $00

.musicdataconcert6
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 8         ; Offset to start of song (length of instrument table)
 DEFB 0      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndataconcert6 DEFW      PATCONC6
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconc6
         DEFB $BD,2
         DEFB 172
         DEFB 152
     DEFB 6
         DEFB 171
         DEFB 156
     DEFB 6
         DEFB 169
         DEFB 159
     DEFB 6
         DEFB 168
         DEFB 156
     DEFB 6
         DEFB 169
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 164
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 164
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 181
         DEFB 157
     DEFB 3
         DEFB 176
         DEFB 160
     DEFB 3
         DEFB 181
         DEFB 164
     DEFB 3
         DEFB 176
         DEFB 160
     DEFB 3
         DEFB $00

.musicdataconcert7
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 8         ; Offset to start of song (length of instrument table)
 DEFB 0      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase
 DEFB 1      ; Multiple
 DEFW 0      ; Detune
 DEFB 0      ; Phase

.patterndataconcert7 DEFW      PATCONC7
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconc7
         DEFB $BD,2
         DEFB 172
         DEFB 164
     DEFB 3
         DEFB 169
         DEFB 169
     DEFB 3
         DEFB 164
         DEFB 164
     DEFB 3
         DEFB 169
         DEFB 169
     DEFB 3
         DEFB 164
         DEFB 172
     DEFB 3
         DEFB 160
         DEFB 169
     DEFB 3
         DEFB 157
         DEFB 172
     DEFB 3
         DEFB 160
         DEFB 176
     DEFB 3
         DEFB 157
         DEFB 172
     DEFB 3
         DEFB 148
         DEFB 176
     DEFB 3
         DEFB 145
         DEFB 181
     DEFB 54
         DEFB $00

.musicdataconcertb0
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4  ; Offset to start of song (length of instrument table)
 DEFB 1  ; Multiple
 DEFW 0  ; Detune
 DEFB 0  ; Phase

.patterndataconcertb0 DEFW      PATCONCB0
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconcb0
         DEFB $BD,0
         DEFB 183
         DEFB 152
     DEFB 6
         DEFB 180
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB 181
         DEFB 157
         DEFB 118
     DEFB 5
         DEFB 183
         DEFB 160
     DEFB 6
         DEFB 180
         DEFB 152
     DEFB 6
         DEFB 176
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 177
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 179
         DEFB 160
     DEFB 6
         DEFB 177
         DEFB 152
     DEFB 3
         DEFB 179
     DEFB 3
         DEFB 176
         DEFB 156
     DEFB 6
         DEFB $00

.musicdataconcertb1
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4  ; Offset to start of song (length of instrument table)
 DEFB 1  ; Multiple
 DEFW 0  ; Detune
 DEFB 0  ; Phase

.patterndataconcertb1 DEFW      PATCONCB1
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconcb1
         DEFB 190
         DEFB 159
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 157
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 190
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 183
         DEFB 152
     DEFB 6
         DEFB 180
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 186
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB $00

.musicdataconcertb2
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4  ; Offset to start of song (length of instrument table)
 DEFB 1  ; Multiple
 DEFW 0  ; Detune
 DEFB 0  ; Phase

.patterndataconcertb2 DEFW      PATCONCB2
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconcb2
         DEFB 184
         DEFB 157
         DEFB 118
     DEFB 5
         DEFB 183
         DEFB 160
     DEFB 6
         DEFB 180
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 177
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB 179
         DEFB 157
     DEFB 6
         DEFB 177
         DEFB 160
     DEFB 3
         DEFB 179
     DEFB 3
         DEFB 176
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 157
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB $00

.musicdataconcertb3
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4  ; Offset to start of song (length of instrument table)
 DEFB 1  ; Multiple
 DEFW 0  ; Detune
 DEFB 0  ; Phase

.patterndataconcertb3 DEFW      PATCONCB3
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconcb3
         DEFB 190
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
     DEFB 6
         DEFB 172
         DEFB 147
     DEFB 6
         DEFB 172
         DEFB 152
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 155
         DEFB 118
     DEFB 2
         DEFB 174
     DEFB 3
         DEFB 176
         DEFB 147
     DEFB 6
         DEFB 190
         DEFB 152
         DEFB 118
     DEFB 5
         DEFB 172
         DEFB 155
     DEFB 6
         DEFB 174
         DEFB 146
     DEFB 3
         DEFB 176
     DEFB 3
         DEFB 171
         DEFB 149
         DEFB 118
     DEFB 5
         DEFB $00

.musicdataconcertb4
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4  ; Offset to start of song (length of instrument table)
 DEFB 1  ; Multiple
 DEFW 0  ; Detune
 DEFB 0  ; Phase

.patterndataconcertb4 DEFW      PATCONCB4
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconcb4
         DEFB 190
         DEFB 155
         DEFB 118
     DEFB 5
         DEFB 174
         DEFB 146
     DEFB 6
         DEFB 190
         DEFB 149
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 155
     DEFB 3
         DEFB 171
     DEFB 3
         DEFB 172
         DEFB 153
     DEFB 6
         DEFB 169
         DEFB 157
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 160
         DEFB 118
     DEFB 5
         DEFB 172
         DEFB 153
     DEFB 6
         DEFB 190
         DEFB 157
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 152
     DEFB 3
         DEFB 169
     DEFB 3
         DEFB 168
         DEFB 156
     DEFB 3
         DEFB 169
     DEFB 3
         DEFB 171
         DEFB 159
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 152
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB $00

.musicdataconcertb5
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4  ; Offset to start of song (length of instrument table)
 DEFB 1  ; Multiple
 DEFW 0  ; Detune
 DEFB 0  ; Phase

.patterndataconcertb5 DEFW      PATCONCB5
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconcb5
         DEFB 190
         DEFB 159
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 152
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 156
     DEFB 6
         DEFB 190
         DEFB 159
         DEFB 118
     DEFB 5
         DEFB 172
         DEFB 147
     DEFB 6
         DEFB 172
         DEFB 152
     DEFB 6
         DEFB 190
         DEFB 155
         DEFB 118
     DEFB 2
         DEFB 174
     DEFB 3
         DEFB 176
         DEFB 147
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 152
     DEFB 6
         DEFB 172
         DEFB 155
         DEFB 118
     DEFB 5
         DEFB 174
         DEFB 146
     DEFB 6
         DEFB $00

.musicdataconcertb6
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4  ; Offset to start of song (length of instrument table)
 DEFB 1  ; Multiple
 DEFW 0  ; Detune
 DEFB 0  ; Phase

.patterndataconcertb6 DEFW      PATCONCB6
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconcb6
         DEFB 171
         DEFB 150
     DEFB 6
         DEFB 190
         DEFB 155
         DEFB 118
     DEFB 5
         DEFB 174
         DEFB 146
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 150
     DEFB 6
         DEFB 171
         DEFB 155
         DEFB 118
     DEFB 5
         DEFB 172
         DEFB 153
     DEFB 6
         DEFB 169
         DEFB 157
     DEFB 6
         DEFB 190
         DEFB 160
         DEFB 118
     DEFB 5
         DEFB 172
         DEFB 153
         DEFB 118
     DEFB 5
         DEFB 171
         DEFB 157
     DEFB 3
         DEFB 169
     DEFB 3
         DEFB 167
         DEFB 160
         DEFB 118
     DEFB 2
         DEFB 165
     DEFB 3
         DEFB 176
         DEFB 164
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 162
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 177
         DEFB 160
         DEFB 118
     DEFB 5
         DEFB $00

.musicdataconcertb7
 DEFB 0  ; Pattern loop begin * 2
 DEFB 2  ; Song length * 2
 DEFW 4  ; Offset to start of song (length of instrument table)
 DEFB 1  ; Multiple
 DEFW 0  ; Detune
 DEFB 0  ; Phase

.patterndataconcertb7 DEFW      PATCONCB7
                    
; *** Pattern data - $00 marks the end of a pattern ***
.patconcb7
         DEFB 190
         DEFB 159
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 179
         DEFB 155
     DEFB 3
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 153
     DEFB 27
         DEFB 177
     DEFB 3
         DEFB 176
         DEFB 152
     DEFB 33
         DEFB 190
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 118
     DEFB 5
         DEFB $00

#endasm
