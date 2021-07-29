Herramienta para crear juegos con textos in-game en jpones hiragana con el motor MK1 La Churrera

uso:

misaki_converter nombre_archivo_con_pseudohiragana

Por ejemplo 

misaki_converter pseudohiragana_input.txt

Proporciona un array C que debe ser incluido en el archivo definitions.h

Este array contiene los textos que se imprimiran de forma normal con la funcion print_str de printer.h, siempre y cuando 
se este usando el tileset que contiene la fuente de hiragana (que se incluye en esta carpeta). 

Al ser la fuente hiragana mas extensa que el alfabeto, estamos robando espacio a los numeros 0..9, por lo que los hemos reubicado en la zona de tiles del tileset. Para poderlos usar hay que reemplazar la funcion print_number2 de printer.h por la que proporcionamos en este directorio.
