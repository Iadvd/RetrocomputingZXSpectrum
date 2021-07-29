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

Cada linea es uno de los textos del juego, por ejemplo,

あれ、ここどこだ？

Se escribe en pseudohiragana como:

A:RE:,:KO:KO:TO:':KO:TA:':?

que es la representacion equivalente a:

あ:れ:、:こ:こ:ど:こ:だ:？

despues, el conversor generara el array C con los textos encapsulados para que tomen correctamente el caracter hiragana de la fuente guardada en el tileset.h

El archivo "Pseudohiragana_writing.txt" explica como se escribe cada hiragana, por ejemplo 

が 

se escribe en pseudohiragana como 

か:'

(ocupara por tando en pantalla dos celdas de 8x8 bits que es el espacio de dos caracteres)
