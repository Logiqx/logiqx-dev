@ECHO OFF

rm -f datlib.zip
zip -r datlib.zip src makefile datafile.dtd readme.txt whatsnew.txt -x src/CVS/* src/*/CVS/* src/*/*/CVS/* 

PAUSE
