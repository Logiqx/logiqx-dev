@ECHO OFF

rm -f zfind.zip
zip -r zfind.zip src makefile zipfind.exe readme.txt whatsnew.txt -x src/CVS/*

PAUSE
