@ECHO OFF

rm -f zident.zip
zip -r zident.zip src makefile zipident.exe readme.txt whatsnew.txt -x src/CVS/*

PAUSE
