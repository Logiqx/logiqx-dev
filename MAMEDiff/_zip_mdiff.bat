@ECHO OFF

rm -f mdiff.zip
zip -r mdiff.zip src makefile mamediff.exe readme.txt whatsnew.txt -x src/CVS/*

PAUSE
