@echo off

copy %CAESAR%\data\games\multi\*.dat
copy %CAESAR%\data\games\multi2\*.dat
copy %CAESAR%\data\games\single\*.dat
copy %CAESAR%\data\games\sound\*.dat
copy %CAESAR%\data\games\linux\*.dat
copy %CAESAR%\data\games\mac\*.dat
copy %CAESAR%\data\games\beos\*.dat
copy %CAESAR%\data\games\arm\*.dat
copy "VBEmu v1.00a.dat"+"%CAESAR%\data\games\multi2\VBEmu Screen Saver v1.01a - v1.00a.dat" "VBEmu Screen Saver v1.01a.dat"

rombchk MAME*dat

del *.dat
