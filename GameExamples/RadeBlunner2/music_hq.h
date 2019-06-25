#asm

ORG 40000

; *****************************************************************************
; * Phaser1 Engine, with synthesised drums
; *
; * Original code by Shiru - .http//shiru.untergrund.net/
; * Modified by Chris Cowley
; *
; * Produced by Beepola v1.05.01
; ******************************************************************************
 
.musicstart
             LD    HL,MUSICDATA         ;  <- Pointer to Music Data. Change
.common_engine

			 ; INGAME MUSIC CODE BEGIN
			 LD A, 10
			 LD (WAIT_COUNTER),A
			 ; INGAME MUSIC CODE END
			 
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
             
			 ; INGAME MUSIC CODE BEGIN
			 LD A,(PATTERN_PTR)
			 SUB 8
			 JR NZ, ISNOTZEROPAT
			 
			 XOR  A
			 LD   (PATTERN_PTR),A                ; Set the pattern pointer to zero
			 LD   H,A
			 LD   L,A
			 LD   (NOTE_PTR),HL                  ; Set the note offset (within this pattern) to 0
.isnotzeropat			 
             LD   H,A
             LD   L,A
			 ; INGAME MUSIC CODE END

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
             JP   NC,DRUM_TYPE_1
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
			 
			 ; INGAME MUSIC CODE BEGIN
             //XOR  A
             //IN   A,($FE)
             //OR   $E0
             //INC  A

.player_wait_key
             //JR   NZ,EXIT_PLAYER
			 
			 LD A, (WAIT_COUNTER)
			 DEC A
			 jp nz, CONTINUE_PLAYER 
			 //LD  A,(NOTE_PTR)
			 //DEC A
			 //LD  (NOTE_PTR),A
             JP EXIT_PLAYER
			 
.continue_player			 
			 LD (WAIT_COUNTER),A
			 ; INGAME MUSIC CODE END
			 
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
; * DRUM type 1 - Digital
; ************************************************************
.drum_type_1
             SUB  $74                          ; 
             LD   B,A
             LD   A,$80
.l822c       RLA                               ;
             DJNZ L822C                        ; Rotates the drum number, giving us the appropriately-set bit in A

.DRUM_DIGITAL
             LD   (DRUM_SAMPLE),A
             LD   A,$0
             LD   D,A
             LD   HL,SAMPLE_DATA
             LD   BC,1024                      ; Drums are all 1024 samples long, and striped into a byte
.NEXT_SAMPLE
             LD   A,(HL)

             DEFB $E6                          ; AND n
.DRUM_SAMPLE
             DEFB $8

             LD   A,D                          ; Put border colour bits into A
             JR   NZ,L8247                     ; Sample bit set
             JR   Z,L8249                      ; Sample bit not set
.L8247       OR   $10
.L8249       OUT  ($FE),A
             LD   E,$04
.L824D       DEC  E
             JR   NZ,L824D
             INC  HL
             DEC  BC
             LD   A,B
             OR   C
             JR   NZ,NEXT_SAMPLE
             JP   MAIN_LOOP

.pattern_addr   DEFW  $0000
.pattern_ptr    DEFB  0
.note_ptr       DEFW  $0000

; INGAME MUSIC CODE BEGIN
.wait_counter   DEFB  0
; INGAME MUSIC CODE END

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
; * Digital Drum Samples - 8 * 1024bit samples, striped into bytes
; *****************************************************************
.SAMPLE_DATA
             DEFB $02,$02,$02,$02,$00,$00,$02,$00,$0E,$00,$00,$00,$00,$00,$00,$00
			 DEFB $0C,$00,$00,$00,$8,$10,$10,$10,$18,$70,$70,$70,$70,$70,$70,$70
             DEFB $74,$70,$50,$50,$D8,$D0,$D0,$D0,$D4,$D0,$D0,$D0,$D0,$D0,$D0,$D0
             DEFB $D4,$D1,$D1,$D1,$5D,$41,$41,$41,$41,$41,$41,$41,$4D,$41,$41,$41
             DEFB $49,$41,$41,$41,$47,$41,$41,$60,$6C,$22,$20,$20,$2E,$22,$20,$20
             DEFB $22,$22,$22,$22,$26,$32,$32,$32,$36,$32,$32,$32,$36,$B2,$B2,$B2
             DEFB $B2,$B2,$32,$32,$3E,$32,$32,$B2,$B2,$B2,$B2,$B2,$BE,$12,$12,$11
             DEFB $17,$13,$93,$93,$97,$83,$83,$C3,$CB,$C3,$C3,$C3,$CB,$C3,$C1,$C1
             DEFB $C9,$C1,$C1,$C1,$C5,$C1,$C1,$C1,$41,$41,$41,$41,$4D,$41,$41,$41
             DEFB $41,$40,$40,$40,$6C,$60,$70,$70,$78,$70,$70,$70,$7C,$70,$70,$70
             DEFB $74,$70,$70,$70,$70,$70,$70,$70,$34,$30,$30,$30,$38,$30,$30,$30
             DEFB $38,$30,$30,$B0,$B8,$B0,$B0,$B0,$A4,$A0,$A0,$A0,$84,$80,$80,$80
             DEFB $8C,$80,$80,$80,$8C,$82,$82,$82,$8C,$80,$82,$82,$8E,$83,$81,$83
             DEFB $8F,$83,$83,$83,$87,$83,$83,$83,$87,$D3,$D3,$D3,$D7,$D3,$D3,$53
             DEFB $53,$53,$73,$73,$77,$73,$73,$73,$7B,$73,$73,$73,$73,$73,$73,$73
             DEFB $73,$73,$73,$73,$77,$73,$73,$73,$7D,$73,$73,$71,$6D,$61,$60,$60
             DEFB $6C,$62,$62,$62,$62,$60,$60,$60,$64,$60,$60,$20,$00,$00,$00,$00
             DEFB $8,$00,$00,$00,$00,$00,$00,$00,$04,$00,$00,$00,$04,$00,$90,$90
             DEFB $1C,$10,$10,$10,$90,$90,$90,$90,$18,$10,$10,$10,$90,$90,$90,$10
             DEFB $1C,$10,$10,$10,$1C,$30,$30,$30,$34,$B0,$B0,$B0,$34,$30,$F0,$F0
             DEFB $F4,$F0,$E0,$E0,$E4,$E0,$E0,$60,$68,$E0,$E0,$E0,$E0,$E2,$E2,$E2
             DEFB $E6,$E0,$E2,$E0,$E6,$E3,$E3,$E3,$E3,$61,$63,$E3,$E7,$E3,$43,$43
             DEFB $4F,$41,$41,$41,$43,$53,$53,$53,$57,$53,$53,$53,$57,$53,$53,$53
             DEFB $13,$13,$13,$13,$17,$13,$13,$13,$1B,$13,$13,$11,$19,$13,$13,$11
             DEFB $11,$11,$13,$11,$11,$11,$11,$13,$1B,$33,$33,$A1,$A3,$A1,$A1,$A1
             DEFB $21,$21,$A1,$A1,$A9,$A0,$A0,$A0,$A0,$A0,$20,$20,$28,$20,$A0,$A0
             DEFB $A0,$20,$20,$A0,$E0,$E0,$60,$E0,$E0,$E0,$E0,$E0,$E8,$60,$60,$70
             DEFB $78,$F0,$F0,$F0,$D8,$50,$50,$50,$58,$50,$50,$50,$50,$50,$50,$50
             DEFB $50,$50,$50,$50,$58,$50,$50,$50,$50,$50,$50,$50,$50,$50,$50,$50
             DEFB $5C,$50,$50,$50,$54,$40,$42,$40,$00,$02,$00,$00,$00,$00,$20,$20
             DEFB $20,$22,$22,$22,$22,$22,$20,$22,$2A,$20,$22,$22,$22,$20,$22,$22
             DEFB $26,$22,$20,$22,$26,$22,$20,$22,$22,$22,$A2,$B2,$B8,$B0,$B0,$B2
             DEFB $B2,$B2,$B2,$32,$32,$B2,$B0,$B2,$B0,$B0,$32,$90,$90,$92,$52,$51
             DEFB $51,$51,$D1,$D1,$D9,$D1,$51,$51,$51,$51,$53,$D1,$D9,$51,$51,$D3
             DEFB $D3,$51,$41,$C1,$C1,$C1,$C1,$C1,$C9,$C1,$C1,$C1,$41,$41,$C1,$C1
             DEFB $C9,$C1,$C1,$41,$C9,$C1,$C1,$61,$69,$E1,$E1,$E1,$61,$61,$61,$61
             DEFB $61,$61,$61,$61,$29,$21,$21,$21,$25,$31,$31,$31,$35,$31,$31,$31
             DEFB $39,$B1,$B1,$31,$31,$31,$31,$31,$31,$B1,$32,$30,$B0,$B0,$30,$30
             DEFB $34,$30,$32,$32,$14,$10,$10,$10,$10,$10,$10,$10,$10,$90,$92,$12
             DEFB $10,$92,$82,$02,$00,$00,$00,$02,$8A,$02,$02,$02,$CE,$40,$40,$40
             DEFB $40,$42,$40,$42,$4A,$C2,$C2,$42,$40,$40,$40,$40,$48,$C2,$42,$42
             DEFB $48,$40,$60,$60,$EA,$62,$62,$E2,$EA,$60,$70,$70,$70,$70,$F0,$F0
             DEFB $70,$70,$72,$70,$7A,$72,$70,$70,$F0,$F0,$70,$F0,$F0,$70,$70,$F0
             DEFB $F2,$70,$F0,$B0,$3C,$30,$30,$30,$34,$30,$30,$30,$30,$B0,$B0,$30
             DEFB $B0,$90,$10,$00,$00,$00,$00,$80,$82,$02,$00,$00,$00,$00,$00,$00
             DEFB $00,$00,$00,$00,$04,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
             DEFB $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$50,$50,$50
             DEFB $58,$72,$70,$70,$70,$70,$70,$70,$70,$70,$70,$72,$7A,$72,$72,$70
             DEFB $F8,$F0,$F0,$F2,$7A,$70,$70,$70,$F0,$F0,$F0,$70,$70,$70,$72,$F2
             DEFB $F0,$70,$70,$F2,$F2,$F0,$F0,$E0,$E8,$E2,$60,$60,$E0,$E0,$E2,$E2
             DEFB $EA,$C0,$C2,$C2,$C2,$42,$00,$82,$82,$82,$80,$82,$80,$80,$80,$80
             DEFB $80,$80,$00,$02,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
             DEFB $8,$00,$10,$10,$10,$10,$10,$10,$18,$10,$10,$10,$12,$10,$10,$10
             DEFB $10,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$70
             DEFB $70,$70,$70,$70,$70,$70,$70,$70,$70,$70,$70,$70,$70,$70,$60,$60
             DEFB $60,$60,$60,$60,$60,$60,$60,$60,$68,$60,$60,$60,$60,$60,$60,$60
             DEFB $68,$60,$60,$C0,$C8,$C0,$C0,$C0,$C0,$40,$40,$40,$40,$C0,$C0,$40
             DEFB $40,$42,$40,$C2,$C8,$C0,$40,$42,$C2,$C2,$10,$10,$98,$90,$92,$92
             DEFB $12,$12,$10,$10,$10,$10,$10,$10,$9A,$92,$90,$90,$98,$90,$90,$90
             DEFB $12,$12,$92,$90,$B0,$B0,$30,$30,$38,$30,$30,$30,$38,$30,$30,$30
             DEFB $3A,$30,$32,$30,$30,$30,$20,$22,$20,$A0,$A0,$20,$28,$A0,$A2,$A2
             DEFB $A0,$20,$20,$20,$20,$60,$60,$60,$60,$60,$62,$60,$68,$E0,$E0,$E0
             DEFB $E0,$E0,$60,$60,$60,$60,$E0,$E0,$40,$40,$40,$40,$40,$40,$40,$40
             DEFB $48,$40,$40,$40,$58,$50,$50,$50,$58,$50,$D0,$D0,$50,$50,$50,$50
			
.musicdata
             DEFB 0  ; Pattern loop begin * 2
             DEFB 10  ; Song length * 2
             DEFW 4         ; Offset to start of song (length of instrument table)
             DEFB 0      ; Multiple
             DEFW 3      ; Detune
             DEFB 0      ; Phase
             
.patterndata        DEFW      PAT0
                    DEFW      PAT1
                    DEFW      PAT2
                    DEFW      PAT3 ; Avoid loops with same patterns when INGAME MUSIC CODE 
					DEFW      PAT4 ; Empty end INGAME

; *** Pattern data - $00 marks the end of a pattern ***
.pat0
         DEFB $BD,0
         DEFB 145
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 161
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 159
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 161
         DEFB 140
     DEFB 6
         DEFB 157
         DEFB 145
         DEFB 119
     DEFB 2
         DEFB 152
     DEFB 3
         DEFB 162
         DEFB 140
     DEFB 6
         DEFB 190
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 161
         DEFB 140
     DEFB 6
         DEFB 157
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 190
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 140
     DEFB 3
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 190
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 155
         DEFB 143
     DEFB 6
         DEFB 190
         DEFB 138
         DEFB 118
     DEFB 5
         DEFB 154
         DEFB 143
     DEFB 6
         DEFB 152
         DEFB 138
         DEFB 119
     DEFB 5
         DEFB 150
         DEFB 143
     DEFB 6
         DEFB 150
         DEFB 138
         DEFB 118
     DEFB 5
         DEFB 154
         DEFB 143
     DEFB 6
         DEFB 190
         DEFB 138
         DEFB 119
     DEFB 5
         DEFB 152
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 119
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 119
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB $00
		 
.pat1
         DEFB $BD,0
         DEFB 145
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 161
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 159
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 161
         DEFB 140
     DEFB 6
         DEFB 157
         DEFB 145
         DEFB 119
     DEFB 2
         DEFB 152
     DEFB 3
         DEFB 162
         DEFB 140
     DEFB 6
         DEFB 190
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 161
         DEFB 140
     DEFB 6
         DEFB 157
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 190
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 140
     DEFB 3
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 190
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 155
         DEFB 143
     DEFB 6
         DEFB 190
         DEFB 138
         DEFB 118
     DEFB 5
         DEFB 154
         DEFB 143
     DEFB 6
         DEFB 152
         DEFB 138
         DEFB 119
     DEFB 5
         DEFB 150
         DEFB 143
     DEFB 6
         DEFB 150
         DEFB 138
         DEFB 118
     DEFB 5
         DEFB 159
         DEFB 143
     DEFB 6
         DEFB 190
         DEFB 138
         DEFB 119
     DEFB 5
         DEFB 157
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 119
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 119
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB $00
		 
.pat2
         DEFB $BD,0
         DEFB 154
         DEFB 150
         DEFB 118
     DEFB 5
         DEFB 150
         DEFB 138
     DEFB 6
         DEFB 157
         DEFB 150
         DEFB 119
     DEFB 5
         DEFB 154
         DEFB 138
     DEFB 6
         DEFB 160
         DEFB 150
         DEFB 118
     DEFB 5
         DEFB 157
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 119
     DEFB 5
         DEFB 160
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 118
     DEFB 5
         DEFB 159
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 119
     DEFB 5
         DEFB 157
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 138
     DEFB 3
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 190
         DEFB 150
         DEFB 119
     DEFB 5
         DEFB 154
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 118
     DEFB 5
         DEFB 150
         DEFB 138
     DEFB 6
         DEFB 157
         DEFB 150
         DEFB 119
     DEFB 5
         DEFB 154
         DEFB 138
     DEFB 6
         DEFB 160
         DEFB 150
         DEFB 118
     DEFB 5
         DEFB 157
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 119
     DEFB 5
         DEFB 190
         DEFB 138
     DEFB 6
         DEFB 160
         DEFB 150
         DEFB 118
     DEFB 5
         DEFB 162
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 119
     DEFB 5
         DEFB 162
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 118
     DEFB 2
         DEFB 159
         DEFB 119
     DEFB 2
         DEFB 160
         DEFB 138
     DEFB 6
         DEFB 190
         DEFB 150
         DEFB 119
     DEFB 5
         DEFB 190
         DEFB 138
     DEFB 6
         DEFB $00

.pat3
         DEFB $BD,0
		 
         DEFB 145
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 161
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 159
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 161
         DEFB 140
     DEFB 6
         DEFB 157
         DEFB 145
         DEFB 119
     DEFB 2
         DEFB 152
     DEFB 3
         DEFB 162
         DEFB 140
     DEFB 6
         DEFB 190
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 161
         DEFB 140
     DEFB 6
         DEFB 157
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 152
         DEFB 140
     DEFB 6
         DEFB 190
         DEFB 145
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 140
     DEFB 3
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 190
         DEFB 145
         DEFB 119
     DEFB 5
         DEFB 155
         DEFB 143
     DEFB 6
         DEFB 190
         DEFB 138
         DEFB 118
     DEFB 5
         DEFB 154
         DEFB 143
     DEFB 6
         DEFB 152
         DEFB 138
         DEFB 119
     DEFB 5
         DEFB 150
         DEFB 143
     DEFB 6
         DEFB 150
         DEFB 138
         DEFB 118
     DEFB 5
         DEFB 159
         DEFB 143
     DEFB 6
         DEFB 190
         DEFB 138
         DEFB 119
     DEFB 5
         DEFB 157
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 118
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 119
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 118
     DEFB 2
         DEFB 190
         DEFB 119
     DEFB 2
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB 190
         DEFB 140
         DEFB 119
     DEFB 5
         DEFB 190
         DEFB 145
     DEFB 6
         DEFB $00

.pat4
         DEFB $00
		 
#endasm