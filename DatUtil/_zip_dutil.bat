@ECHO OFF

rm -f dutil.zip
zip -r dutil.zip src makefile datutil.exe readme.txt whatsnew.txt delimited.sql -x src/CVS/*

PAUSE
