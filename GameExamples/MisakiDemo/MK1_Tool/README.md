# Generador de hiragana v1.0 para MK1 La Churrera
# Hecho por Furillo Productions https://furilloproductions.itch.io/")

# Hiragana generator v1.0 for MK1 La Churrera")
# By Furillo Productions https://furilloproductions.itch.io/")

(sp) Uso:

misaki_converter nombre_archivo_con_pseudohiragana

(en) Usage:

misaki_converter name_of_file_including_pseudohiragana

Por ejemplo / For instance: 

misaki_converter pseudohiragana_input.txt

(sp) Proporciona un array C que debe ser incluido en el archivo "definitions.h" del motor MK1.
(en) Will provie a C array to be included in the "definitions.h" file from the MK1 engine.

(sp) Este array contiene los textos que se imprimiran de forma normal con la funcion "print_str" de "printer.h", siempre y cuando 
se este usando el "tileset.h" que contiene la fuente de hiragana que se incluye en esta carpeta como base del tileset del juego.

(en) This array contains the texts that will be printed in the usual way by using the funcion "print_str" from "printer.h", having in mind
that the "tileset.h" file must be one based on the one included in this folder. 

(sp) Al ser la fuente hiragana mas extensa que el alfabeto, estamos robando espacio a los numeros 0..9, por lo que los hemos reubicado en la zona de tiles del tileset. Para poderlos usar hay que reemplazar la funcion "print_number2" de "printer.h" por la que proporcionamos en este directorio.

(en) Due to the length of the hiragana alphabet, there is not enough space for the numbers in the usual tileset space of the MK1 engine. Thus, 
the 0..9 numbers are relocated into the tiles section of the tileset.h file. Due to this relocation, the funcion "print_number2" from "printer.h" must be replaced by the one we provide in this folder.

(sp) El archivo "pseudohiragana_input.txt" contiene como ejemplo los textos del juego "Yopparai Sarariiman" 
(en) The file "pseudohiragana_input.txt" contains, as a working example, the texts of the game "Yopparai Sarariiman"  

https://furilloproductions.itch.io/yopparaisarariiman

(sp) Cada linea es uno de los textos del juego, por ejemplo,
(en) Each line is one of the in-game texts, e.g.,

あれ、ここどこだ？

(sp) Se escribe en pseudohiragana como:
(en) Is written in pseudohiragana as:

A:RE:,:KO:KO:TO:':KO:TA:':?

(sp) que es la representacion equivalente a:
(en) which is the equivalent to:

あ:れ:、:こ:こ:ど:こ:だ:？

(sp) despues, el conversor generara el array C con los textos encapsulados para que tomen correctamente el caracter hiragana de la fuente guardada en el tileset.h
(en) after creating this file, the converter will generate the C array with the texts properly encapsulated, so they will take correctly the Hiragana character included into the tileset.h data.

(sp) El archivo "Pseudohiragana_writing.txt" explica como se escribe cada hiragana, por ejemplo 
(en) The file named "Pseudohiragana_writing.txt" explains how is each Hiragana character written in pseudohiragana, e.g.

が 

(sp) se escribe en pseudohiragana como 
(en) is written as

か:'

(sp) ... y ocupara por tanto en pantalla dos celdas de 8x8 bits que es el espacio de dos caracteres.
(en) ... and consequently will use two 8x8 cells of the screen; in other words, it will require two characters to be written.
