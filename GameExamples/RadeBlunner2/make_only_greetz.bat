del %1.tap
zcc +zx -vn %1.c -o %1.bin -lndos -lsplib2 -llibsocket -create-app -zorg=24000
.\utils\bin2tap.exe -o .\%1.tap -a 24000 .\%1.bin
echo DONE


