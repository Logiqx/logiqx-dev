@ECHO OFF

rm -f mdiff.zip
zip -r mdiff.zip src makefile mamediff.exe mamediff.txt -x src/CVS/*

PAUSE
