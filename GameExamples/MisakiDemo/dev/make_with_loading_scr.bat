del loader.tap
del screen.tap
del %1.tap
del main.tap
echo z80asm -r22528 -b attrzero.asm
zcc +zx -vn -O3 %1.c -o %1.bin -lndos -lsplib2 -create-app -zorg=24000
.\utils\bas2tap.exe -a10 -sMISAKIDEMO .\loader_with_loading_screen.bas .\loader.tap
.\utils\bin2tap.exe -o .\attrzero.tap -a 22528 .\attrzero.bin
.\utils\bin2tap.exe -o .\main.tap -a 24000 .\%1.bin
copy /b .\loader.tap + .\attrzero.tap + .\main.tap .\%1.tap
echo DONE


