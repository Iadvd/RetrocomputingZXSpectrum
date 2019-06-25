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
.mainengine               LD   A,(HL)                         ; Get the loop start pointer
                          LD   (PATTERN_LOOP_BEGIN),A
                          INC  HL
                          LD   A,(HL)                         ; Get the song end pointer
                          LD   (PATTERN_LOOP_END),A
                          INC  HL
                          LD   (PATTERNDATA1),HL
                          LD   (PATTERNDATA2),HL
                          LD   A,254
                          LD   (PATTERN_PTR),A                ; Set the pattern pointer to zero
                          DI
                          CALL  NEXT_PATTERN
.nextnote
                          CALL  PLAYNOTE
                          XOR   A
                          IN    A,($FE)
                          AND   $1F
                          CP    $1F
                          JR    Z,NEXTNOTE                    ; Play next note if no key pressed

                          EI
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
.tempo                    DEFB 238

.musicdata
                    DEFB 0   ; Loop start point * 2

#ifndef ANDROID_TCP_IP
                    DEFB 8   ; Song Length * 2
#else
					DEFB 4   ; Song Length * 2
#endif

.patterndata        DEFW      PAT0
#ifndef ANDROID_TCP_IP
                    DEFW      PAT1
                    DEFW      PAT2
                    DEFW      PAT1
#else
                    DEFW      PAT2	
#endif

; *** Pattern data consists of pairs of frequency values CH1,CH2 with a single $0 to
; *** Mark the end of the pattern, and $01 for a rest
.pat0
         DEFB 238  ; Pattern tempo
             DEFB 136,1
             DEFB 1,1
             DEFB 180,91
             DEFB 1,1
             DEFB 136,54
             DEFB 1,1
             DEFB 180,91
             DEFB 1,1
             DEFB 136,61
             DEFB 1,1
             DEFB 180,54
             DEFB 1,1
             DEFB 136,68
             DEFB 1,91
             DEFB 180,51
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,54
             DEFB 1,1
             DEFB 136,68
             DEFB 1,1
             DEFB 180,91
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 151,76
             DEFB 1,1
             DEFB 203,1
             DEFB 1,1
             DEFB 151,81
             DEFB 1,1
             DEFB 203,91
             DEFB 1,1
             DEFB 151,102
             DEFB 1,1
             DEFB 203,102
             DEFB 1,1
             DEFB 151,81
             DEFB 1,1
             DEFB 203,1
             DEFB 1,1
             DEFB 136,91
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
         DEFB $0
		 
#ifndef ANDROID_TCP_IP
.pat1
         DEFB 238  ; Pattern tempo
             DEFB 136,1
             DEFB 1,1
             DEFB 180,91
             DEFB 1,1
             DEFB 136,54
             DEFB 1,1
             DEFB 180,91
             DEFB 1,1
             DEFB 136,61
             DEFB 1,1
             DEFB 180,54
             DEFB 1,1
             DEFB 136,68
             DEFB 1,91
             DEFB 180,51
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,54
             DEFB 1,1
             DEFB 136,68
             DEFB 1,1
             DEFB 180,91
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 151,76
             DEFB 1,1
             DEFB 203,1
             DEFB 1,1
             DEFB 151,81
             DEFB 1,1
             DEFB 203,91
             DEFB 1,1
             DEFB 151,102
             DEFB 1,1
             DEFB 203,102
             DEFB 1,1
             DEFB 151,61
             DEFB 1,1
             DEFB 203,1
             DEFB 1,1
             DEFB 136,68
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
             DEFB 180,1
             DEFB 1,1
             DEFB 136,1
             DEFB 1,1
         DEFB $0
#endif

.pat2
         DEFB 238  ; Pattern tempo
             DEFB 102,81
             DEFB 1,1
             DEFB 203,102
             DEFB 1,1
             DEFB 102,68
             DEFB 1,1
             DEFB 203,81
             DEFB 1,1
             DEFB 102,57
             DEFB 1,1
             DEFB 203,68
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,57
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,61
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,68
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,1
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,81
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,102
             DEFB 1,1
             DEFB 102,68
             DEFB 1,1
             DEFB 203,81
             DEFB 1,1
             DEFB 102,57
             DEFB 1,1
             DEFB 203,68
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,1
             DEFB 1,1
             DEFB 102,57
             DEFB 1,1
             DEFB 203,51
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,51
             DEFB 1,1
             DEFB 102,1
             DEFB 1,61
             DEFB 203,57
             DEFB 1,1
             DEFB 102,1
             DEFB 1,1
             DEFB 203,1
             DEFB 1,1
         DEFB $0

#endasm