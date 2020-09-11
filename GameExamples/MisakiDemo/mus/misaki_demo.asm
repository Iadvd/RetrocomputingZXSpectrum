                ORG 40000
; *****************************************************************************
; * The Music Box Engine, with Drums
; *
; * Based on code written by Mark Alexander for the utility, The Music Box.
; * Modified by Chris Cowley
; * Thanks to introspec for help with optimised DRUM_SET routine :)
; *
; * Produced by Beepola v1.08.01
; ******************************************************************************
 
.musicstart
                          LD    HL,MUSICDATA         ;  <- Pointer to Music Data. Change
                                                     ;     this to play a different song
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
                          DI
                          CALL  NEXT_PATTERN
                          EI
                          RET
.nextnote
                          ;DI
						  ;EXX
                          ;PUSH  HL
                          CALL  PLAYNOTE
						  ;POP   HL
                          ;EXX 
                          ;EI
                          RET                                 ; Return from playing tune

.pattern_ptr              DEFB 0
.note_ptr                 DEFB 0


; ********************************************************************************************************
; * NEXT_PATTERN
; *
; * Select the next pattern in sequence (and handle looping if we've reached PATTERN_LOOP_END
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

                          CP   $02                            ; $02 = DRUM ESCAPE CODE, byte in Ch2 identifies the drum type
                          JR   Z,DRUM_ESCAPE

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
                          LD   A,0
                          EX   AF,AF'
                          LD   A,0                   ; So now BC = TEMPO, A and A' = BORDER_COL
                          LD   IXH,D
                          LD   D,$10
.eae5                     NOP
                          NOP
.eae7                     EX   AF,AF'
                          DEC  E
                          OUT  ($FE),A
                          JR   NZ,EB04

                          LD   E,IXH
                          XOR  D
                          EX   AF,AF'
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
                          EX   AF,AF'
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

.drum_escape
                          INC  HL
                          LD   D,(HL)                         ; Put the drum type into D
                          LD   A,(NOTE_PTR)
                          INC  A
                          INC  A
                          LD   (NOTE_PTR),A                   ; Increment the note pointer by 2 (one note per chan)

; $02,$C0 = KICK
; $02,%0yyyxxxx. xxxx is the 4 bits of wave activation, yyy == 0,1,2,3,4,5,6,7 wave type

                          LD   A,D
                          BIT  7,A
                          JR   NZ,IS_KICK
                          LD   H,1
                          AND  $70
                          JR   Z,SET_DRUM_P2
.drumset_nextbit          SCF
                          RL   H
                          SUB  $10
                          JR   NZ,DRUMSET_NEXTBIT

set_drum_p2              LD   A,D
                          OR   %11110000
                          LD   D,H

is_kick                  CALL  DRUM_DELAY
                          CP    $FF
                          JR    Z,WAVE_OUT

                          CP    $C0
                          JP    Z,KICK_DRUM

.wave_silence             LD    B,$04
                          LD    C,E
                          RLA
.l8120                    RLA
                          RLA
                          RLA
.l8123                    RLA
                          CALL  C,WAVE_OUT
                          CALL  NC,SILENCE_LOOP2
                          DJNZ  L8123
                          RET

.drum_delay               PUSH  AF
                          LD    A,(TEMPO)
                          CPL
                          LD    B,A
                          LD    C,A
                          ADD   A,$01
                          SRA   A
                          SRA   A
                          LD    E,A
                          CP    $00
                          JR    NZ,L8140
                          INC   E
.l8140                    POP   AF
                          RET

.wave_out                 PUSH  AF
                          PUSH  HL
                          PUSH  BC
                          LD    A,0
                          LD    B,$00
                          LD    HL,$03E8
.l814d                    RRC   D
                          JP    NC,L8171
                          INC   HL
                          BIT   0,(HL)
                          JP    Z,L816D
                          SET   4,A
                          XOR   $83
                          XOR   $83
.l815e                    OUT   ($FE),A
.l8160                    NOP
                          DEC   B
                          JP    NZ,L814D
                          DEC   C
                          JP    NZ,L814D
                          POP   BC
                          POP   HL
                          POP   AF
                          RET

.l816d                    RES   4,A
                          JR    L815E

.l8171                    SCF
                          JP    NC,$0000
                          JP    NC,$0000
                          JP    NC,$0000
                          NOP
                          NOP
                          JR    L8160

.kick_drum                LD    E,B
                          LD    D,$00
                          LD    HL,KICK_VALUES
                          ADC   HL,DE
                          LD    A,(HL)
                          LD    B,A
                          LD    HL,$0003
.l818c                    PUSH  BC
                          LD    DE,$0001
                          PUSH  HL
                          CALL  L819E
                          POP   HL
                          LD    DE,$00FF
                          ADC   HL,DE
                          POP   BC
                          DJNZ  L818C
                          RET

.l819e                    LD    A,L
                          SRL   L
                          SRL   L
                          CPL
                          AND   $03
                          LD    C,A
                          LD    B,$00
                          LD    IX,$03D1
                          ADD   IX,BC
                          LD    A,0
                          CALL  $03D4
                          DI
                          RET

.kick_values              DEFW  $0C0C
                          DEFW  $0D0D
                          DEFW  $0E0E
                          DEFW  $0F0E
                          DEFW  $0F0F
                          DEFW  $1010
                          DEFW  $1111
                          DEFW  $1212
                          DEFW  $1313
                          DEFW  $1414
                          DEFW  $1515
                          DEFW  $1615
                          DEFW  $1717
                          DEFW  $1818
                          DEFW  $1919

; *** DATA ***
TEMPO:                    DEFB 230

MUSICDATA:
                    DEFB 0   ; Loop start point * 2
                    DEFB 8   ; Song Length * 2
PATTERNDATA:        DEFW      PAT0
                    DEFW      PAT1
                    DEFW      PAT2
                    DEFW      PAT3

; *** Pattern data consists of pairs of frequency values CH1,CH2 with a single $0 to
; *** Mark the end of the pattern, and $01 for a rest
PAT0:
         DEFB 230  ; Pattern tempo
                          DEFB $02,$C0               ; Kick Drum
             DEFB 13,13
             DEFB 1,1
             DEFB 13,13
                          DEFB $02,$2F               ; Waveform Drum
             DEFB 17,17
             DEFB 1,1
                          DEFB $02,$C0               ; Kick Drum
             DEFB 1,1
                          DEFB $02,$C0               ; Kick Drum
             DEFB 1,1
             DEFB 1,1
                          DEFB $02,$2F               ; Waveform Drum
             DEFB 1,1
             DEFB 19,19
             DEFB 17,17
         DEFB $0
PAT1:
         DEFB 230  ; Pattern tempo
                          DEFB $02,$C0               ; Kick Drum
             DEFB 16,16
             DEFB 1,1
             DEFB 16,16
                          DEFB $02,$2F               ; Waveform Drum
             DEFB 21,21
             DEFB 1,1
                          DEFB $02,$C0               ; Kick Drum
             DEFB 1,1
                          DEFB $02,$C0               ; Kick Drum
             DEFB 1,1
             DEFB 1,1
                          DEFB $02,$2F               ; Waveform Drum
             DEFB 1,1
             DEFB 16,16
             DEFB 17,17
         DEFB $0
PAT2:
         DEFB 230  ; Pattern tempo
                          DEFB $02,$C0               ; Kick Drum
             DEFB 19,19
             DEFB 1,1
             DEFB 19,19
                          DEFB $02,$2F               ; Waveform Drum
             DEFB 25,25
             DEFB 1,1
                          DEFB $02,$C0               ; Kick Drum
             DEFB 1,1
                          DEFB $02,$C0               ; Kick Drum
             DEFB 1,1
             DEFB 1,1
                          DEFB $02,$2F               ; Waveform Drum
             DEFB 1,1
             DEFB 21,1
             DEFB 19,1
         DEFB $0
PAT3:
         DEFB 230  ; Pattern tempo
                          DEFB $02,$C0               ; Kick Drum
             DEFB 17,1
             DEFB 1,1
             DEFB 17,1
                          DEFB $02,$2F               ; Waveform Drum
             DEFB 23,1
             DEFB 1,1
                          DEFB $02,$C0               ; Kick Drum
             DEFB 1,1
                          DEFB $02,$C0               ; Kick Drum
             DEFB 1,1
             DEFB 1,1
                          DEFB $02,$2F               ; Waveform Drum
             DEFB 1,1
             DEFB 13,1
             DEFB 14,1
         DEFB $0
