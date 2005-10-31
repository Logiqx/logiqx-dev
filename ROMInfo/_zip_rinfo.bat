@ECHO OFF

rm -f rinfo.zip
zip -r rinfo.zip src makefile rominfo.exe rominfo.ini rominfo.txt -x src/CVS/*

PAUSE
