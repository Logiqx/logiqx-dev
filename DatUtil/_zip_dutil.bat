@ECHO OFF

rm -f dutil.zip
zip -r dutil.zip src makefile datutil.exe datutil.txt -x src/CVS/*

PAUSE
