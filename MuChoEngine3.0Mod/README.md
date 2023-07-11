#MuCho Engine 3.0 Customization tryouts by IADVD (Furillo Productions)

An example of application of these explanations here: https://furilloproductions.itch.io/the-dark-veil-el-velo-oscuro

This folder will contain my customizations of the MuCho engine 3.0 by Jari Komppa. 

The original versiones are at these links:

https://github.com/jarikomppa/speccy/tree/master/mucho

https://github.com/jarikomppa/speccy/tree/master/mackarel

My customizations will be updated from time to time, and I provide the contents "as is", a work in progress, hoping someone may find it useful.

As these are customizations of Jari Komppa's work, so I am accepting and following the same license agreement:

 * released under the unlicense, see http://unlicense.org
 * (practically public domain)

Basically the initial 3 main objective of my customizations are:

1. Creating a MuCho engine with a Spanish interface
  
2. Create a variation of the English interface of the original engine (just a simple rewording)

3. Add some music to the engine, using Shiru's Beepola engine Phaser 1 type asm player and include a Main Menu (first room, starting game) music, and a final room (bad or good end) music, and interface (up,down,select) sounds. As everybody knows, MuCho is already able to add sounds, but it does not include a music asm player. 

Thus, the initial targer ouput is creating a MuCHo engine 3.0 + Beepola Phaser 1 music that generates MuCho games for ZX Spectrum 48k including some music and menu selection (musical) sound effects. 

The contents will be an example, so the readers can make their own version of the musical contents. 

This customization implies rebuilding the "crt0.ihx" MuCHo engine archive, which is used by the Mackarel application to create the final .tap file.

For this purpose our output will be two files:

crt0.ihx with Spanish language interface texts + Beepola music

crt0.ihx with English language interface texts (our own very simple rewording) + Beepola music

Initially the data of the music is harcoded inside the build of the "crt0.ihx" file, but a possible future enhancemente could be a way of having only the asm of the Beepola player without music data inside the "crt0.ihx"  build and the finding a way to insert only the music data later, so it is not required a rebuild of the core MuCHo engine "crt0.ihx" each time we want to add new music or interface effects to a new game.

As a side note, including this kind of player plus some simple but effective music should not take more that2 or 3K's depending on the music and effects created, so the final game should not suffer many restrictions regarding the texts or images that can be added. A quick comparison is that the size of the player plus music data has approximately the same size than one $I image of the engine (32x10 screen cells), around 2-3K's. So if we add music, probably we will balance texts+images+music again tohave a perfect mix when the final game is released. 

