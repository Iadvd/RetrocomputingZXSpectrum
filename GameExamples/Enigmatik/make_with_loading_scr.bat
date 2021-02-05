del creepy.bin
del loader.tap
del screen.tap
del attrzero.tap
del main.tap
del %1.tap
zcc +zx -vn -O3 %1.c -o %1.bin -lndos -lsplib2 -create-app -zorg=24000
.\utils\bas2tap.exe -a10 -sENIGMATIK .\loader_with_loading_screen.bas .\loader.tap
echo .\utils\bin2tap.exe -o .\screen.tap -a 16384 .\loading.bin
echo .\utils\bin2tap.exe -o .\screen.tap -a 16384 .\loading_p.bin
.\utils\bin2tap.exe -o .\screen.tap -a 16384 .\loading_r.bin
echo .\utils\bin2tap.exe -o .\screen.tap -a 16384 .\loading_s.bin
.\utils\bin2tap.exe -o .\attrzero.tap -a 22528 .\attrzero.bin
echo creepy_1.bin 512b
echo creepy_2.bin 544b
echo creepy_3.bin 544b
echo creepy_4.bin 544b
echo creepy_5.bin 768b
echo creepy_6.bin 768b
echo creepy_7.bin 768b
copy /b .\creepy_1.bin + .\creepy_2.bin + .\creepy_3.bin + .\creepy_4.bin + .\creepy_5.bin + .\creepy_6.bin .\creepy.bin
.\utils\apack.exe .\creepy.bin .\creepypasta.bin
.\utils\bin2tap.exe -o .\main.tap -a 24000 .\%1.bin
copy /b .\loader.tap + .\attrzero.tap + .\main.tap + .\screen.tap .\%1.tap
echo DONE


