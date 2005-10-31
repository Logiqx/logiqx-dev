@ECHO OFF

rm -f zfind.zip
zip -r zfind.zip src makefile zipfind.exe zipfind.txt -x src/CVS/*

PAUSE
