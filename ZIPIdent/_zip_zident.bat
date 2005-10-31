@ECHO OFF

rm -f zident.zip
zip -r zident.zip src makefile zipident.exe zipident.txt -x src/CVS/*

PAUSE
