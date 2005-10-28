@ECHO OFF

rm -f datlib.zip
zip -r datlib.zip src makefile -x src/CVS/* src/*/CVS/* src/*/*/CVS/* 

PAUSE
