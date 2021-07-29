Herramienta para crear juegos con textos in-game en jpones hiragana con el motor MK1 La Churrera

uso:

misaki_converter nombre_archivo_con_pseudohiragana

Por ejemplo 

misaki_converter pseudohiragana_input.txt

Proporciona un array C que debe ser incluido en el archivo definitions.h

Este array contiene los textos que se imprimiran de forma normal con la funcion print_str de printer.h, siempre y cuando 
se este usando el tileset.h que contiene la fuente de hiragana que se incluye en esta carpeta.

Al ser la fuente hiragana mas extensa que el alfabeto, estamos robando espacio a los numeros 0..9, por lo que los hemos reubicado en la zona de tiles del tileset. Para poderlos usar hay que reemplazar la funcion print_number2 de printer.h por la que proporcionamos en este directorio.

El archivo "pseudohiragana_input.txt" contiene como ejemplo los textos del juego Yopparai Sarariiman (https://furilloproductions.itch.io/yopparaisarariiman):

A:RE:,:KO:KO:TO:':KO:TA:':?
KA:MI:SA:N:NI:TE:':N:WA:SHI:NA:I:TO:NA:.:.:.
TO:':SU:KO:I:!:TO:':SU:KO:I:!
I:YA:A:A:!:MA:KE:TA:A:A:!
U:WA:tsu:,:SHI:':KA:N:KA:':YA:HE:':E:-:!:!
MA:SHI:':O:SO:I:tsu:.
SHI:N:KO:':U:NA:KA:':I:NA:A:-:.
KA:E:RI:TE:E:!
A:,:I:I:TO:KO:RO:NI:I:CHI:E:N:TA:':!
MA:SU:':HA:TE:':N:WA:,:TE:':N:WA:.
SU:SHI:WO:KA:tsu:TA:YO:!
KA:MI:SA:N:HA:U:RE:SHI:KU:NA:RU:KA:NA:A:A:?
NI:HO:N:SHI:yu:U:MA:I:NA:A:-:!
KA:N:HA:*:I:!:KA:N:HA:*:I:!
I:TE:TE:TE:E:E:E:!
NA:N:SHI:':ya:KO:RI:ya:A:A:!
MO:SHI:MO:SHI:KO:':ME:N:NE:O:SO:KU:NA:RU:.
I:I:WA:!:MA:tsu:TE:I:RU:NE:!
TA:KO:YA:KI
YA:KI:TO:RI
KA:RA:O:KE
KA:RA:A:KE:'
FU:KU:':!
MO:SHI:MO:SHI:MA:TA:TSU:KA:MA:tsu:CHI:ya:tsu:TA:.
RI:yo:U:KA:O:,:O:MI:YA:KE:':YO:RO:SHI:KU:NE:!
MO:SHI:MO:SHI:CHI:yo:tsu:TO:I:tsu:HA:*:I:HI:tsu:KA:KE:TE:KU:RU:NE:.
WA:KA:tsu:TA:WA:.:O:SO:KU:NA:RA:NA:I:TE:':NE:.

