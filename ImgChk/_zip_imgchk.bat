@ECHO OFF

rm -f imgchk.zip
zip -r imgchk.zip src makefile imgchk.exe imgchk.ini *.txt -x src/CVS/*

PAUSE
