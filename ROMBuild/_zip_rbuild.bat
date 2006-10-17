@ECHO OFF

rm -f rbuild.zip
zip -r rbuild.zip src makefile rombuild.exe readme.txt whatsnew.txt roms_in roms_out -x src/CVS/* roms_in/CVS/* roms_out/CVS/*

PAUSE
