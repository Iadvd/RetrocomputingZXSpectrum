void musicaltouch(void) __naked
{
__asm

_waituntilend: 
			.db #0
_musicstart:
			 LD    HL,#_musicdata 
			 JP _common_engine
_musicend:
			 LD    HL,#_musicdata_end
			 JP _common_engine
_musicstart_iu:
			 LD	   A,#176 ;down 181 up 176 select 169
			 LD (#_musicdata_ifacetype),A
			 LD    HL,#_musicdata_iface 
			 JP _common_engine
_musicstart_id:
			 LD	   A,#181 ;down 181 up 176 select 169
			 LD (#_musicdata_ifacetype),A
			 LD    HL,#_musicdata_iface 
			 JP _common_engine
_musicstart_is:
			 LD	   A,#169 ;down 181 up 176 select 169
			 LD (#_musicdata_ifacetype),A
			 LD    HL,#_musicdata_iface 
_common_engine:			 
             LD   A,(HL)                         ; Get the loop start pointer
             LD   (#_pattern_loop_begin),A
             INC  HL
             LD   A,(HL)                         ; Get the song end pointer
             LD   (#_pattern_loop_end),A
             INC  HL
             LD   E,(HL)
             INC  HL
             LD   D,(HL)
             INC  HL
             LD   (#_instrum_tbl),HL
             LD   (#_current_inst),HL
             ADD  HL,DE
             LD   (#_pattern_addr),HL
             XOR  A
             LD   (#_pattern_ptr),A                ; Set the pattern pointer to zero
             LD   H,A
             LD   L,A
             LD   (#_note_ptr),HL                  ; Set the note offset (within this pattern) to 0

_player:
             DI
             PUSH IY
			 PUSH IX
             xor a
             LD   H,#0
             LD   L,A
             LD   (#_cnt_1a),HL
             LD   (#_cnt_1a),HL
             LD   (#_div_1a),HL
             LD   (#_div_1b),HL
             LD   (#_cnt_2),HL
             LD   (#_div_2),HL
             LD   (#_out_1),A
             LD   (#_out_2),A
			 
			 JR   _main_loop

_next_pattern:
                          LD   A,(_pattern_ptr)
                          INC  A
                          INC  A
                          .db #254                           ; $FE CP n

_pattern_loop_end:         .db #0
                          JR   NZ,_no_pattern_loop
                          ; Handle Pattern Looping at and of song
                          .db #62                           ; $3E LD A,n

_pattern_loop_begin:       .db #0
						  JP   _exit_player_final
_no_pattern_loop:          LD   (#_pattern_ptr),A
                          LD   HL,#0
                          LD   (#_note_ptr),HL   ; Start of pattern (note_ptr = 0)

_main_loop:
			 .db #253,#46,#0 ;LD   IYL,#0 ; Set channel = 0 FD2E00 CODED
			 
_read_loop:
             LD   HL,(#_pattern_addr)
             LD   A,(#_pattern_ptr)
             LD   E,A
             LD   D,#0
             ADD  HL,DE
             LD   E,(HL)
             INC  HL
             LD   D,(HL)                       ; Now DE = Start of Pattern data
             LD   HL,(#_note_ptr)
             INC  HL                           ; Increment the note pointer and...
             LD   (#_note_ptr),HL                ; ..store it
             DEC  HL
             ADD  HL,DE                        ; Now HL = address of note data
             LD   A,(HL)
             OR   A
			 
			 JR   Z,_next_pattern               ; select next pattern

             BIT  #7,A
             JP   Z,_render                     ; Play the currently defined note(S) and drum
			 
			 .db #253,#103 ;LD   IYH,A is FD67 CODED
             
			 AND  #63;$3F
             CP   #60;$3C
             JP   NC,_other                     ; Other parameters
             ADD  A,A
             LD   B,#0
             LD   C,A
             LD   HL,#_freq_table
             ADD  HL,BC
             LD   E,(HL)
             INC  HL
             LD   D,(HL)
			 
			 .db #253,#125 ;LD   A,IYL ; IYL = 0 for channel 1, or = 1 for channel 2  FD7D CODED
             
			 OR   A
             JR   NZ,_set_note2
             LD   (#_div_1a),DE
             EX   DE,HL

             .db #221,#33                      ; $DD $21 LD IX,nn
			 
_current_inst:
             .dw #0
			 
			 .db #221,#126,#0 ; LD   A,(IX+$0)  DD7ENN CODED
             
			 OR   A
             JR   Z,_l809b                      ; Original code jumps into byte 2 of the DJNZ (invalid opcode FD)
             LD   B,A

_l8098:       ADD  HL,HL
             DJNZ _l8098

_l809b:       
			 .db #221,#94,#1 ; LD   E,(IX+$01)  DD5ENN CODED
             .db #221,#86,#2 ; LD   D,(IX+$02)  DD56NN CODED
             
			 ADD  HL,DE
             LD   (#_div_1b),HL
             
			 .db #253,#46,#1 ;LD   IYL,#1  ; Set channel = 1 CODED FD2E01
             
			 .db #253,#124 ;LD   A,IYH ; FD7C CODED
             
			 AND  #64;$40
             JR   Z,_read_loop                  ; No phase reset

             LD   HL,#_out_1                     ; Reset phaser
             RES  #4,(HL)
             LD   HL,#0
             LD   (#_cnt_1a),HL
             
			 .db #221,#102,#3 ; LD   H,(IX+$03) DD66NN CODED
             
			 LD   (#_cnt_1b),HL
             JR   _read_loop

_set_note2:
             LD   (#_div_2),DE
             
			 .db #253,#124 ;LD   A,IYH ; FD7C CODED
             
			 LD   HL,#_out_2
             RES  #4,(HL)
             LD   HL,#0
             LD   (#_cnt_2),HL
             JP   _read_loop

_set_stop:
             LD   HL,#0
             
			 .db #253,#125 ;LD   A,IYL ;FD7D CODED
             
			 OR   A
             JR   NZ,#_set_stop2
             ; Stop channel 1 note
             LD   (#_div_1a),HL
             LD   (#_div_1b),HL
             LD   HL,#_out_1
             RES  #4,(HL)
             
			 .db #253,#46,#1; LD   IYL,#1 FD2E01 CODED
             
			 JP   _read_loop

_set_stop2:
             ; Stop channel 2 note
             LD   (#_div_2),HL
             LD   HL,#_out_2
             RES  #4,(HL)
             JP   _read_loop

_other:       CP   #60;$3C
             JR   Z,_set_stop                   ; Stop note
             CP   #62;$3E
             JR   Z,_skip_ch1                   ; No changes to channel 1
             INC  HL                           ; Instrument change
             LD   L,(HL)
             LD   H,#0
             ADD  HL,HL
             LD   DE,(#_note_ptr)
             INC  DE
             LD   (#_note_ptr),DE                ; Increment the note pointer

             .db #1                          ; $01 LD BC,nn

_instrum_tbl:
             .dw #0

             ADD  HL,BC
             LD   (#_current_inst),HL
             JP   _read_loop

_skip_ch1:
			 .db #253,#46,#1; LD   IYL,$01 FD2E01 CODED
			 
             JP   _read_loop

_exit_player:
			 LD A,(#_waituntilend)
			 CP #1
             JP Z,_continue_playing
_exit_player_final:			 
             ;LD   HL,#10072;$2758
             EXX
			 POP  IX
             POP  IY
             ;EI
             RET
             
_render:
             AND  #127;$7F                          ; L813A
             CP   #118;$76
             JP   NC,_drums
             LD   D,A
             EXX ; paired
             .db #33                          ; $21 LD HL,nn
_cnt_1a:      .dw #0
             .db #221,#33                      ; $DD $21 LD IX,nn
_cnt_1b:      .dw #0
             .db #1                           ; $01 LD BC,nn
_div_1a:      .dw #0
             .db #17                          ; $11 LD DE,nn
_div_1b:      .dw #0
             .db #62                          ; $3E LD A,n

_out_1:      .db #0
             EXX ; paired
             EX   AF,AF ; beware!
             .db #33                          ; $21 LD HL,nn
_cnt_2:       .dw #0
             .db #1                          ; $01 LD BC,nn
_div_2:      .dw #0
             .db #62                          ; $3E LD A,n
_out_2:       .db #0

_play_note:
             ; Read keyboard
             LD   E,A
             XOR  A
             IN   A,(#254) ;$FE
             OR   #224;$E0
             INC  A

_player_wait_key:
			 JR   NZ,_exit_player
_continue_playing:
             LD   A,E
             LD   E,#0

_l8168:       EXX ; paired
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  (#254),A ;$FE
             JR   C,_l8171
             JR   _l8173
_l8171:       XOR  #16 ;$10
_l8173:       ADD  IX,DE
             JR   C,_l8179
             JR   _l817b
_l8179:       XOR  #16; $10
_l817b:       EX   AF,AF ; beware!
             OUT  (#254),A ;$FE
             EXX ; paired
             ADD  HL,BC
             JR   C,_l8184
             JR   _l8186

_l8184:       XOR  #16 ;$10
_l8186:       NOP
             JP   _l818a

_l818a:       EXX ; paired
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  (#254),A ;$FE
             JR   C,_l8193
             JR   _l8195
_l8193:       XOR  #16 ;$10
_l8195:       ADD  IX,DE
             JR   C,_l819b
             JR   _l819d
_l819b:       XOR  #16 ;$10
_l819d:       EX   AF,AF ; beware!
             OUT  (#254),A ;$FE
             EXX ; paired
             ADD  HL,BC
             JR   C,_l81a6
             JR   _l81a8
_l81a6:       XOR  #16 ;$10
_l81a8:       NOP
             JP   _l81ac

_l81ac:       EXX ; paired
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  (#254),A ;$FE
             JR   C,_l81b5
             JR   _l81b7
_l81b5:       XOR  #16 ;$10
_l81b7:       ADD  IX,DE
             JR   C,_l81bd
             JR   _l81bf
_l81bd:       XOR  #16 ;$10
_l81bf:       EX   AF,AF ; beware!
             OUT  (#254),A ;$FE
             EXX ; paired
             ADD  HL,BC
             JR   C,_l81c8
             JR   _l81ca
_l81c8:       XOR  #16 ;$10
_l81ca:       NOP
             JP   _l81ce

_l81ce:       EXX ; paired
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  (#254),A ;$FE
             JR   C,_l81d7
             JR   _l81d9
_l81d7:       XOR  #16 ;$10
_l81d9:       ADD  IX,DE
             JR   C,_l81df
             JR   _l81e1
_l81df:       XOR  #16 ;$10
_l81e1:       EX   AF,AF ; beware!
             OUT  (#254),A ;$FE
             EXX ; paired
             ADD  HL,BC
             JR   C,_l81ea
             JR   _l81ec
_l81ea:       XOR  #16 ;$10

_l81ec:       DEC  E
             JP   NZ,_l8168

             EXX ; paired
             EX   AF,AF ; beware!
             ADD  HL,BC
             OUT  (#254),A ;$FE
             JR   C,_l81f9
             JR   _l81fb
_l81f9:       XOR  #16 ;$10
_l81fb:       ADD  IX,DE
             JR   C,_l8201
             JR   _l8203
_l8201:       XOR  #16 ;$10
_l8203:       EX   AF,AF ; beware!
             OUT  (#254),A ;$FE
             EXX ; paired
             ADD  HL,BC
             JR   C,_l820c
             JR   _l820e
_l820c:       XOR  #16 ;$10

_l820e:       DEC  D
             JP   NZ,_play_note

             LD   (#_cnt_2),HL
             LD   (#_out_2),A
             EXX
             EX   AF,AF ; beware!
             LD   (#_cnt_1a),HL
             LD   (#_cnt_1b),IX
             LD   (#_out_1),A
             JP   _main_loop

_drums:
             ADD  A,A                          ; On entry A=$75+Drum number (i.e. $76 to $7E)
             LD   B,#0
             LD   C,A
             LD   HL,#_drum_table - #236
             ADD  HL,BC
             LD   E,(HL)
             INC  HL
             LD   D,(HL)
             EX   DE,HL
             JP   (HL)

_drum_tone1:  LD   L,#16
             JR   _drum_tone
_drum_tone2:  LD   L,#12
             JR   _drum_tone
_drum_tone3:  LD   L,#8
             JR   _drum_tone
_drum_tone4:  LD   L,#6
             JR   _drum_tone
_drum_tone5:  LD   L,#4
             JR   _drum_tone
_drum_tone6:  LD   L,#2
_drum_tone:
             LD   DE,#3700
             LD   BC,#257 ;$0101
             //LD   A,BORDER_COL
             xor a
_dt_loop0:    OUT  (#254),A ;$FE
             DEC  B
             JR   NZ,_dt_loop1
             XOR  #16
             LD   B,C
             EX   AF,AF ; beware!
             LD   A,C
             ADD  A,L
             LD   C,A
             EX   AF,AF ; beware!

_dt_loop1:    DEC  E
             JR   NZ,_dt_loop0
             DEC  D
             JR   NZ,_dt_loop0
             JP   _main_loop

_drum_noise1: LD   DE,#2480
             
			 .db #221,#46,#1 ; LD   IXL,#1 DD2E1 CODED
             
			 JR   _drum_noise
_drum_noise2: LD   DE,#1070
             
			 .db #221,#46,#10 ; LD   IXL,#10 DD2E10 CODED
             
			 JR   _drum_noise
_drum_noise3: LD   DE,#365
             
			 .db #221,#46,#101 ;LD   IXL,#101 DD2E101 CODED
			 
_drum_noise:
             LD   H,D
             LD   L,E
             xor a
             LD   C,A
_dn_loop0:    LD   A,(HL)
             AND  #16
             OR   C
             OUT  (#254),A ;$FE
             
			 .db #221,#69 ;LD   B,IXL DD45 CODED

_dn_loop1:   DJNZ _dn_loop1
             INC  HL
             DEC  E
             JR   NZ,_dn_loop0
             DEC  D
             JR   NZ,_dn_loop0
             JP   _main_loop

_pattern_addr:   .dw  #0
_pattern_ptr:    .db  #0
_note_ptr:      .dw  #0

_freq_table:
             .dw #178,#189,#200,#212,#225,#238,#252,#267,#283,#300,#318,#337
             .dw #357,#378,#401,#425,#450,#477,#505,#535,#567,#601,#637,#675
             .dw #715,#757,#802,#850,#901,#954,#1011,#1071,#1135,#1202,#1274,#1350
             .dw #1430,#1515,#1605,#1701,#1802,#1909,#2023,#2143,#2270,#2405,#2548,#2700
             .dw #2860,#3030,#3211,#3402,#3604,#3818,#4046,#4286,#4541,#4811,#5097,#5400

_drum_table:
             .dw #_drum_tone1,#_drum_tone2,#_drum_tone3,#_drum_tone4,#_drum_tone5,#_drum_tone6
             .dw #_drum_noise1,#_drum_noise2,#_drum_noise3

_musicdata:
             .db #0  	 ; Pattern loop begin * 2
             .db #8  	 ; Song length * 2
             .dw #4      ; Offset to start of song (length of instrument table)
             .db #1      ; Multiple
             .dw #0      ; Detune
             .db #1      ; Phase

_patterndata:      .dw      #_pat0
					.dw      #_pat0
                    .dw      #_pat0
					.dw      #_pat0

_pat0:
         .db #189,#0 ; $BD
         .db #152
         .db #157
     .db #15
         .db #147
         .db #156
     .db #3
         .db #149
         .db #157
     .db #3
         .db #152
         .db #159
     .db #9
         .db #147
         .db #156
     .db #3
         .db #188
         .db #188
     .db #3
         .db #144
         .db #152
     .db #3
         .db #157
         .db #161
     .db #24
         .db #188
         .db #188
     .db #3
         .db #157
         .db #161
     .db #3
         .db #157
         .db #161
     .db #3
         .db #155
         .db #160
     .db #3
         .db #157
         .db #161
     .db #3
         .db #159
         .db #164
     .db #3
         .db #188
         .db #188
     .db #3
         .db #157
         .db #162
     .db #3
         .db #150
         .db #154
     .db #21
         .db #149
         .db #153
     .db #3
         .db #150
         .db #154
     .db #3
         .db #152
         .db #161
     .db #21
         .db #156
         .db #159
     .db #21
         .db #0

_musicdata_iface:
             .db #0  ; Pattern loop begin * 2
             .db #2  ; Song length * 2
             .dw #4         ; Offset to start of song (length of instrument table)
             .db #1      ; Multiple
             .dw #0      ; Detune
             .db #1      ; Phase

_patterndata_i:        .dw     #_pat0_i

; *** Pattern data - $00 marks the end of a pattern ***
_pat0_i:
         .db #189,#0 ;$DB
         .db #190
_musicdata_ifacetype:
         .db #181 ; down 181 up 176 select 169
     .db #2
         .db #190
         .db #188
     .db #2
         .db #0

_musicdata_end:
             .db #0  ; Pattern loop begin * 2
             .db #2  ; Song length * 2
             .dw #4         ; Offset to start of song (length of instrument table)
             .db #1      ; Multiple
             .dw #0      ; Detune
             .db #1      ; Phase

_patterndataend:        .dw      #_patend

; *** Pattern data - $00 marks the end of a pattern ***
_patend:
         .db #189,#0 ;$BD
         .db #176
         .db #183
     .db #3
         .db #171
         .db #180
     .db #3
         .db #168
         .db #176
     .db #3
         .db #171
         .db #180
     .db #3
         .db #168
         .db #176
     .db #3
         .db #164
         .db #171
     .db #3
         .db #168
         .db #176
     .db #3
         .db #164
         .db #171
     .db #3
         .db #159
         .db #168
     .db #3
         .db #164
         .db #171
     .db #3
         .db #159
         .db #168
     .db #3
         .db #156
         .db #164
     .db #3
         .db #159
         .db #168
     .db #3
         .db #156
         .db #164
     .db #3
         .db #152
         .db #159
     .db #3
         .db #156
         .db #164
     .db #3
         .db #152
         .db #159
     .db #3
         .db #147
         .db #156
     .db #3
         .db #156
         .db #152
     .db #6
         .db #188
         .db #188
     .db #3
         .db #0
		 
__endasm;	
}
