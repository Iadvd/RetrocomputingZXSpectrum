
#	genops.awk
#
#	Copyright 2004-2010 Jan Bobrowski <jb@wizard.ae.krakow.pl>
#
#	This program is free software; you can redistribute it and/or
#	modify it under the terms of the GNU General Public License
#	version 2 as published by the Free Software Foundation.

BEGIN {
	reg8n = "BCDE   A"
	alu[0] = "add"
	alu[1] = "adc"
	alu[2] = "sub"
	alu[3] = "sbc"
	alu[4] = "and"
	alu[5] = "xor"
	alu[6] = "or"
	alu[7] = "cp"

	for(n=0;n<256;n++) hex[sprintf("%02X",n)]=n

	tvar = "time"
}

function outop(n, s, t) {
	time += t
	done[n]++
	if(s=="") printf "//"
	printf " case 0x%02X:", n
	if(s!="")
		printf " %s", s
	if(match(s, /continue;$/)) {print ""; return}
	if(time==1) printf " %s++;", tvar
	else if(time>1) printf " %s+=%d;", tvar, time
	time = 0
	print " break;"
}

function fallop(n, s)
{
	printf " case 0x%02X:", n
	if(s!="")
		printf " %s", s
	print ""
	done[n]++
}

function par(s) {
	if(match(s,/^[A-Za-z0-9.]*(\(.*\))?$/)) return s
	return "("s")"
}

function trunc16(s) {
	return "(char)("s")"
}

function nx16(s) {
	return trunc16(s"+1")
}

function get8(n ,c) {
	if(n==4) return mr">>>8"
	if(n==5) return mr"&0xFF"
	c = substr(reg8n, n+1, 1)
	if(c!=" ") return c
	time += 3
	if(mr=="HL") return "env.mem(HL)";
	return "env.mem(getd(xy))";
}

function set8(n,v ,c)
{
	if(n==4) return mr"="mr"&0xFF|"par(v)"<<8;"
	if(n==5) return mr"="mr"&0xFF00|"v";"
	c = substr(reg8n, n+1, 1)
	if(c!=" ") return c"="v";"
	time += 3
	if(mr=="HL") return "env.mem(HL,"v");"
	return "env.mem(getd(xy),"v");"
}

function mod8(n,op ,s,o2) {
	s = index(op,"%")
	o2 = substr(op,s+1)
	op = substr(op,1,s-1)
	if(n!=6)
		return set8(n, op get8(n) o2)
	else if(mr=="HL")
		return "v="op"env.mem(HL)"o2"; "tvar"+=4; env.mem(HL,v); "tvar"+=3;"
	return "{int a; v="op"env.mem(a=getd(xy))"o2"; "tvar"+=4; env.mem(a,v); "tvar"+=3;}"
}

function get16(n, s) {
	if(n==2) return mr
	if(n==3) return "SP"
	if(s && mr!="HL")
		return n ? "de()" : "bc()"
	else
		return n ? "D<<8|E" : "B<<8|C"
}

function set16(n,v ,s) {
	if(n==2) return mr"="v";"
	if(n==3) return "SP="v";"
	if(mr!="HL")
		return (n ? "de" : "bc") "("v");"
	s = "v="v"; %c=v>>>8; %c=v&0xFF;"
	if(n==0) return sprintf(s, "B", "C")
	if(n==1) return sprintf(s, "D", "E")
}

function get16qq(n) {
	if(n==3) return "A<<8|flags()"
	return get16(n,1)
}

function set16qq(n,v) {
	if(n==3) return "af("v");"
	return set16(n,v)
}

function getcond(n) {
	if(n==0) return "Fr!=0"
	if(n==1) return "Fr==0"
	if(n==2) return "(Ff&0x100)==0"
	if(n==3) return "(Ff&0x100)!=0"
	if(n==4) return "(flags()&FP)==0"
	if(n==5) return "(flags()&FP)!=0"
	if(n==6) return "(Ff&FS)==0"
	if(n==7) return "(Ff&FS)!=0"
}

function putgeta(m,d) {
	if(!d) return "MP=(v="m")+1&0xFF|A<<8; env.mem(v,"get8(7)");"
	else return "MP=(v="m")+1; "set8(7, "env.mem(v)")
}

function genbaseop() {
	# 00-3F

	outop(hex["00"], "")
	outop(hex["08"], "ex_af();")

	if(mr=="HL") {
		s = "{"tvar"++; v=PC; byte d=(byte)env.mem(v++); "tvar"+=3;\n\t"
		s=s "if((B=B-1&0xFF)!=0) {"tvar"+=5; MP=v+=d;}\n\t"
		s=s "PC=(char)v;}"
		outop(hex["10"], s)
		outop(hex["18"], "MP=PC=(char)(PC+1+(byte)env.mem(PC));", 8)
	} else {
		outop(hex["10"], tvar"++; if((B=B-1&0xFF)!=0) jr(); else imm8();");
		outop(hex["18"], "jr();");
	}

	for(n=0;n<4;n++)
		outop(hex["09"]+16*n, mr"=add16("mr","get16(n)");")

	for(n=0;n<4;n++) {
		r = get16(n, 1)
		outop(hex["01"]+16*n, set16(n, "imm16()"))
		if(n<2 && group!="xy") continue
		outop(hex["03"]+16*n, set16(n, nx16(par(r))), 2)
		outop(hex["0B"]+16*n, set16(n, trunc16(par(r)"-1")), 2)
	}
	if(group!="xy") {
		outop(hex["03"], "if(++C==256) {B=B+1&0xFF;C=0;}", 2)
		outop(hex["13"], "if(++E==256) {D=D+1&0xFF;E=0;}", 2)
		outop(hex["0B"], "if(--C<0) B=B-1&(C=0xFF);", 2)
		outop(hex["1B"], "if(--E<0) D=D-1&(E=0xFF);", 2)
	}

	outop(hex["02"], putgeta(get16(0,1), 0), 3);
	outop(hex["0A"], putgeta(get16(0,1), 1), 3);
	outop(hex["12"], putgeta(get16(1,1), 0), 3);
	outop(hex["1A"], putgeta(get16(1,1), 1), 3);
	outop(hex["22"], "MP=(v=imm16())+1; env.mem16(v,"mr");",6)
	outop(hex["2A"], "MP=(v=imm16())+1; "mr"=env.mem16(v);",6)
	outop(hex["32"], putgeta("imm16()", 0), 3);
	outop(hex["3A"], putgeta("imm16()", 1), 3);

	for(n=0;n<8;n++) {
		outop(8*n+4, mod8(n,"inc(%)"))
		outop(8*n+5, mod8(n,"dec(%)"))
		if(mr=="HL" || n!=6) {
			outop(8*n+6, set8(n, "imm8()"))
		} else {
			s = "{int a=" trunc16("xy+(byte)env.mem(PC)") "; "tvar"+=3;\n\t"
			s=s "v=env.mem(" nx16("PC") "); "tvar"+=5;\n\t"
			s=s "env.mem(a,v); PC=" trunc16("PC+2") "; "tvar"+=3;}"
			outop(8*n+6, s)
		}
	}

	for(n=0;n<4;n++)
		outop(8*n+32, "if("getcond(n)") jr(); else imm8();")

	outop(hex["07"], "rot(A*0x101>>>7);")
#	outop(hex["0F"], "rot((byte)(A*0x101>>>1));")
	outop(hex["0F"], "rot(A*0x80800000>>24);")
	outop(hex["17"], "rot(A<<1|Ff>>>8&1);")
	outop(hex["1F"], "rot((A*0x201|Ff&0x100)>>>1);")

	outop(hex["27"], "daa();")
	outop(hex["2F"], "cpl();")
	outop(hex["37"], "scf_ccf(0);")
	outop(hex["3F"], "scf_ccf(Ff&0x100);")

	# 40-8F

	n = 64
	for(a=0;a<8;a++) for(b=0;b<8;b++) {
		s=""
		if(a!=b) {
			x=mr; if(a==6) mr="HL"
			s = get8(b)
			mr=x; if(b==6) mr="HL"
			s = set8(a, s)
			mr=x
		} else if(a==6)
			s = "halt();"
		outop(n, s)
		n++
	}

	# 80-BF

	if(mr=="HL") {
		outop(hex["A7"], "Fa=~(Ff=Fr=A); Fb=0;")
		outop(hex["AF"], "A=Ff=Fr=Fb=0; Fa=0x100;")
	}
	for(a=0;a<8;a++) for(b=0;b<8;b++) {
		if(!done[n])
			outop(n, alu[a]"(" get8(b) ");")
		n++
	}

	# C0-FF

	fallop(hex["DD"]);
	if(mr=="HL") {
		outop(hex["FD"], "group_xy(c);")
		outop(hex["CB"], "group_cb();")
	} else {
		outop(hex["FD"], "c0=c; continue;")
		outop(hex["CB"], "group_xy_cb(xy);")
	}
	outop(hex["ED"], "group_ed();")

	for(n=0;n<8;n++) {
		c = getcond(n)
		outop(hex["C0"]+8*n, tvar"++; if("c") MP=PC=pop();")
		outop(hex["C2"]+8*n, "jp("c");")
		outop(hex["C4"]+8*n, "call("c");")
	}

	for(n=0; n<4; n++) {
		outop(hex["C1"]+16*n, set16qq(n, "pop()"))
		outop(hex["C5"]+16*n, "push("get16qq(n)");")
	}

	outop(hex["C3"], "MP=PC=imm16();")

	for(n=0;n<8;n++)
		outop(hex["C6"]+8*n, alu[n]"(imm8());")

	outop(hex["C9"], "MP=PC=pop();")
	if(mr=="HL")
		outop(hex["CD"], "v=imm16(); push(PC); MP=PC=v;")
	else
		outop(hex["CD"], "call(true);")

	outop(hex["D3"], "env.out(v=imm8()|A<<8,A); MP=v+1&0xFF|v&0xFF00;", 4)
	outop(hex["DB"], "MP=(v=imm8()|A<<8)+1; A=env.in(v);", 4)
	outop(hex["D9"], "exx();")
	outop(hex["E3"], "v=pop(); push("mr"); MP="mr"=v;", 2)
	outop(hex["E9"], "PC="mr";")
	if(mr=="HL")
		outop(hex["EB"], "v=HL; HL=D<<8|E; D=v>>>8; E=v&0xFF;")
	else
		outop(hex["EB"], "v=HL; HL=de(); de(v);")
	outop(hex["F3"], "IFF=0;")
	outop(hex["FB"], "IFF=3;")
	outop(hex["F9"], "SP="mr";", 2)

	for(n=0;n<7;n++) fallop(hex["C7"]+8*n)
	outop(hex["FF"], "push(PC); PC=c-199;")
}

function gen_ed_op() {
	mr="HL"

	outop(hex["47"], "i(A);", 1)
	outop(hex["4F"], "r(A);", 1)
	outop(hex["57"], "ld_a_ir(IR>>>8);")
	outop(hex["5F"], "ld_a_ir(r());")
	outop(hex["67"], "rrd();")
	outop(hex["6F"], "rld();")

	for(n=0; n<4; n++) {
		r = substr(reg8n, n+1, 1)
		outop(8*n+hex["40"], "f_szh0n0p("r"=env.in("get16(0)"));", 4)
	}
	outop(hex["60"], "f_szh0n0p(v=env.in("get16(0)")); "set8(4,"v"), 4)
	outop(hex["68"], "f_szh0n0p(v=env.in("get16(0)")); "set8(5,"v"), 4)
	outop(hex["70"], "f_szh0n0p(env.in("get16(0)"));", 4)
	outop(hex["78"], "MP=(v="get16(0)")+1; f_szh0n0p(A=env.in(v));", 4)
	for(n=0; n<6; n++)
		outop(8*n+hex["41"], "env.out("get16(0)"," get8(n) ");", 4)
	outop(hex["71"], "env.out("get16(0)",0);", 4)
	outop(hex["79"], "MP=(v="get16(0)")+1; env.out(v," get8(7) ");", 4)

	for(n=0; n<4; n++) {
		r = get16(n)
		outop(16*n+hex["42"], "sbc_hl("r");")
		outop(16*n+hex["4A"], "adc_hl("r");")
		outop(16*n+hex["43"], "MP=(v=imm16())+1; env.mem16(v,"r");", 6)
		outop(16*n+hex["4B"], "MP=(v=imm16())+1; "set16(n, "env.mem16(v)"), 6)
	}

	for(n=hex["44"]; n<hex["7C"]; n+=8) fallop(n)
	outop(n, "v=A; A=0; sub(v);")

	for(n=hex["45"]; n<hex["7D"]; n+=8) fallop(n)
	outop(n, "IFF|=IFF>>1; MP=PC=pop();")

	for(n=hex["46"]; n<hex["7E"]; n+=8) fallop(n)
	outop(n, "IM = c>>3&3;")

	outop(hex["A0"], "ldir(1,false);")
	outop(hex["A8"], "ldir(-1,false);")
	outop(hex["B0"], "ldir(1,true);")
	outop(hex["B8"], "ldir(-1,true);")

	outop(hex["A1"], "cpir(1,false);")
	outop(hex["A9"], "cpir(-1,false);")
	outop(hex["B1"], "cpir(1,true);")
	outop(hex["B9"], "cpir(-1,true);")

	# 101rd01o
	for(n=hex["A2"]; n<hex["BB"]; n+=(n%2==0?1:7)) fallop(n)
	outop(n, "inir_otir(c);")
}

function gen_cb_op() {
	mr="HL"

	for(n=0;n<8;n++)
		outop(hex["00"]+n, mod8(n, "shifter(o,%)"))
	for(n=0;n<8;n++) {
		s = "bit(o,"get8(n)");"
		if(n==6) {s=s " Ff=Ff&~F53|MP>>>8&F53;"; time++}
		outop(hex["40"]+n, s)
	}
	for(n=0;n<8;n++) {
		if(n==4) s=mr"&=~(0x100<<o);"
		else if(n==5) s=mr"&=~(1<<o);"
		else s = mod8(n,"%&~(1<<o)")
		outop(hex["80"]+n, s)
	}
	for(n=0;n<8;n++) {
		if(n==4) s=mr"|=0x100<<o;"
		else if(n==5) s=mr"|=1<<o;"
		else s = mod8(n,"%|1<<o")
		outop(hex["C0"]+n, s)
	}
}

function chk()
{
	for(n=0;n<256;n++) if(done[n]!=1) {
		printf "%02X %d\n", n, done[n] > "/dev/stderr";
		exit(1);
	}
}

BEGIN {
	if(group=="ed")
		gen_ed_op()
	else if(group=="cb")
		gen_cb_op()
	else {
		mr = group!="xy" ? "HL" : "xy"
		genbaseop()
		chk()
	}
}
