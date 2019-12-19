#asm

; *****************************************************************************
; * The Music Box Player Engine
; *
; * Based on code written by Mark Alexander for the utility, The Music Box.
; * Modified by Chris Cowley
; *
; * Produced by Beepola v1.08.01
; ******************************************************************************
.musicstart
			LD    HL,MUSICDATA         ;  <- Pointer to Music Data. Change
		.mainengine               
			LD   A,(HL)                         ; Get the loop start pointer
			LD   (PATTERN_LOOP_BEGIN),A
			INC  HL
			LD   A,(HL)                         ; Get the song end pointer
			LD   (PATTERN_LOOP_END),A
			INC  HL
			LD   (PATTERNDATA1),HL
			LD   (PATTERNDATA2),HL
			LD   A,254
			LD   (PATTERN_PTR),A                ; Set the pattern pointer to zero
			//DI
			CALL  NEXT_PATTERN
			//EI
			RET
			
.nextnote
						  //DI
						  
                          CALL  PLAYNOTE
                          
						  //EI
                          RET                                      ; Return from playing tune

.pattern_ptr              DEFB 0
.note_ptr                 DEFB 0


; ********************************************************************************************************
; * NEXT_PATTERN
; *
; * Select the next pattern in sequence (and handle looping if we''ve reached PATTERN_LOOP_END
; * Execution falls through to PLAYNOTE to play the first note from our next pattern
; ********************************************************************************************************
.next_pattern
                          LD   A,(PATTERN_PTR)
                          INC  A
                          INC  A
                          DEFB $FE                           ; CP n
.pattern_loop_end         DEFB 0
                          JR   NZ,NO_PATTERN_LOOP
                          DEFB $3E                           ; LD A,n
.pattern_loop_begin       DEFB 0
.no_pattern_loop          LD   (PATTERN_PTR),A
			                    DEFB $21                            ; LD HL,nn
.patterndata1             DEFW $0000
                          LD   E,A                            ; (this is the first byte of the pattern)
                          LD   D,0                            ; and store it at TEMPO
                          ADD  HL,DE
                          LD   E,(HL)
                          INC  HL
                          LD   D,(HL)
                          LD   A,(DE)                         ; Pattern Tempo -> A
	                	      LD   (TEMPO),A                      ; Store it at TEMPO

                          LD   A,1
                          LD   (NOTE_PTR),A

.playnote 
			                    DEFB $21                            ; LD HL,nn
.patterndata2             DEFW $0000
                          LD   A,(PATTERN_PTR)
                          LD   E,A
                          LD   D,0
                          ADD  HL,DE
                          LD   E,(HL)
                          INC  HL
                          LD   D,(HL)                         ; Now DE = Start of Pattern data
                          LD   A,(NOTE_PTR)
                          LD   L,A
                          LD   H,0
                          ADD  HL,DE                          ; Now HL = address of note data
                          LD   D,(HL)
                          LD   E,1

; IF D = $0 then we are at the end of the pattern so increment PATTERN_PTR by 2 and set NOTE_PTR=0
                          LD   A,D
                          AND  A                              ; Optimised CP 0
                          JR   Z,NEXT_PATTERN

                          PUSH DE
                          INC  HL
                          LD   D,(HL)
                          LD   E,1

                          LD   A,(NOTE_PTR)
                          INC  A
                          INC  A
                          LD   (NOTE_PTR),A                   ; Increment the note pointer by 2 (one note per chan)

                          POP  HL                             ; Now CH1 freq is in HL, and CH2 freq is in DE

                          LD   A,H
                          DEC  A
                          JR   NZ,OUTPUT_NOTE

                          LD   A,D                            ; executed only if Channel 2 contains a rest
                          DEC  A                              ; if DE (CH1 note) is also a rest then..
                          JR   Z,PLAY_SILENCE                 ; Play silence

.output_note              LD   A,(TEMPO)
                          LD   C,A
                          LD   B,0
                          LD   A,$0
                          EX   AF,AF ; beware!
                          LD   A,$0                   ; So now BC = TEMPO, A and A'' = $0
                          LD   IXH,D
                          LD   D,$10
.eae5                     NOP
                          NOP
.eae7                     EX   AF,AF ; beware!
                          DEC  E
                          OUT  ($FE),A
                          JR   NZ,EB04

                          LD   E,IXH
                          XOR  D
                          EX   AF,AF ; beware!
                          DEC  L
                          JP   NZ,EB0B

.eaf5                     OUT  ($FE),A
                          LD   L,H
                          XOR  D
                          DJNZ EAE5

                          INC  C
                          JP   NZ,EAE7

                          RET

.eb04
                          JR   Z,EB04
                          EX   AF,AF ; beware!
                          DEC  L
                          JP   Z,EAF5
.eb0b
                          OUT  ($FE),A
                          NOP
                          NOP
                          DJNZ EAE5
                          INC  C
                          JP   NZ,EAE7
                          RET

.play_silence
                          LD   A,(TEMPO)
                          CPL
                          LD   C,A
.silence_loop2            PUSH BC
                          PUSH AF
                          LD   B,0
.silence_loop             PUSH HL
                          LD   HL,0000
                          SRA  (HL)
                          SRA  (HL)
                          SRA  (HL)
                          NOP
                          POP  HL
                          DJNZ SILENCE_LOOP
                          DEC  C
                          JP   NZ,SILENCE_LOOP
                          POP  AF
                          POP  BC
                          RET


; *** DATA ***
.tempo                    DEFB 230

.musicdata
                    DEFB 0   ; Loop start point * 2
                    DEFB 6   ; Song Length * 2

.patterndata        DEFW      PAT0
                    DEFW      PAT1
                    DEFW      PAT2

; *** Pattern data consists of pairs of frequency values CH1,CH2 with a single $0 to
; *** Mark the end of the pattern, and $01 for a rest
.pat0
         DEFB 230  ; Pattern tempo
             DEFB 91,23
             DEFB 1,23
             DEFB 72,27
             DEFB 1,27
             DEFB 61,30
             DEFB 1,30
             DEFB 45,27
             DEFB 1,30
             DEFB 91,86
             DEFB 1,76
             DEFB 72,64
             DEFB 1,54
             DEFB 61,51
             DEFB 1,43
             DEFB 45,38
             DEFB 1,32
             DEFB 91,23
             DEFB 1,23
             DEFB 72,27
             DEFB 1,27
             DEFB 61,30
             DEFB 1,30
             DEFB 45,27
             DEFB 1,30
             DEFB 91,171
             DEFB 1,151
             DEFB 72,128
             DEFB 1,114
             DEFB 61,102
             DEFB 1,86
             DEFB 45,76
             DEFB 1,64
         DEFB $0
		 
.pat1
		 DEFB 230  ; Pattern tempo
             DEFB 136,17
             DEFB 1,17
             DEFB 108,20
             DEFB 1,20
             DEFB 91,23
             DEFB 1,23
             DEFB 68,20
             DEFB 1,23
             DEFB 136,25
             DEFB 1,28
             DEFB 108,32
             DEFB 1,38
             DEFB 91,43
             DEFB 1,51
             DEFB 68,57
             DEFB 1,64
             DEFB 136,17
             DEFB 1,17
             DEFB 108,20
             DEFB 1,20
             DEFB 91,23
             DEFB 1,23
             DEFB 68,20
             DEFB 1,23
             DEFB 136,255
             DEFB 1,227
             DEFB 108,203
             DEFB 1,171
             DEFB 91,151
             DEFB 1,128
             DEFB 68,114
             DEFB 1,102
         DEFB $0
		 
.pat2
         DEFB 230  ; Pattern tempo
             DEFB 121,20
             DEFB 1,20
             DEFB 96,24
             DEFB 1,24
             DEFB 81,30
             DEFB 1,30
             DEFB 61,20
             DEFB 1,20
             DEFB 136,23
             DEFB 1,23
             DEFB 108,27
             DEFB 1,27
             DEFB 91,34
             DEFB 1,34
             DEFB 68,23
             DEFB 1,1
             DEFB 180,23
             DEFB 161,23
             DEFB 144,27
             DEFB 136,27
             DEFB 121,30
             DEFB 108,30
             DEFB 96,36
             DEFB 91,36
             DEFB 1,45
             DEFB 1,1
             DEFB 1,1
             DEFB 1,1
             DEFB 180,23
             DEFB 180,23
             DEFB 1,1
             DEFB 1,1
         DEFB $0

#endasm