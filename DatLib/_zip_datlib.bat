@ECHO OFF

rm -f dlib.zip
zip -r dlib.zip src makefile -x src/CVS/* src/*/CVS/* src/*/*/CVS/* 

PAUSE
