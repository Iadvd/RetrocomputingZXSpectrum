del loader.tap
del screen.tap
del %1.tap
del main.tap
zcc +zx -vn %1.c -o %1.bin -lndos -lsplib2 -llibsocket -create-app -zorg=24000
.\utils\bas2tap.exe -a10 -sRADEB .\loader.bas .\loader.tap
.\utils\bin2tap.exe -o .\screen.tap -a 16384 .\loading.bin
.\utils\bin2tap.exe -o .\main.tap -a 24000 .\%1.bin
copy /b .\loader.tap + .\screen.tap + .\main.tap .\%1.tap
echo DONE


