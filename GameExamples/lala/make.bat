del loader.tap
del screen.tap
del music.tap
del %1.tap
del main.tap
zcc +zx -vn %1.c -o %1.bin -lndos -lsplib2 -llibsocket -create-app -zorg=24000
del %1.tap
.\utils\bas2tap.exe -a10 -sLOADER .\loader.bas .\loader.tap
.\utils\bin2tap.exe -o .\screen.tap -a 16384 .\loading.bin
.\utils\bin2tap.exe -o .\main.tap -a 24000 .\%1.bin
.\utils\bin2tap.exe -o .\music.tap -a 59000 .\music.bin
copy /b .\loader.tap + .\screen.tap + .\main.tap + .\music.tap .\%1.tap