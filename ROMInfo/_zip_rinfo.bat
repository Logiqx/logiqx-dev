@ECHO OFF

rm -f rinfo.zip
zip -r rinfo.zip src makefile rominfo.exe rominfo.ini readme.txt whatsnew.txt -x src/CVS/*

PAUSE
