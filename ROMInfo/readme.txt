-------------------------------------------------------------------------------
                          ROMInfo v2.7 - 11/07/2006

                  Written by Logiqx (http://www.logiqx.com)
-------------------------------------------------------------------------------

Introduction
------------

ROMInfo is for identifying arcade ROMs and checking if they are emulated yet.
It does this using the CMPro dats from the CAESAR database (available at
http://www.logiqx.com) and should cover every arcade game emulated so far.


Usage
-----

1) Edit rominfo.ini to specify all the directories that contain your dats.

ROMInfo will scan all directories beneath the ones you specify so you only
need to specify top level directories.

2) Run rominfo.exe, supplying the CRC(s) that you wish to search for:

e.g. rominfo fee263b3 7f80c5b0

CRCs are case insensitive and do not require leading zeros.

Alternatively, you can specify individual ROM files instead of typing CRCs:

e.g. rominfo pacman.5e pacman.5f

This is also possible with ZIP files, causing ROMInfo to do the search for
every CRC from within the ZIP file.

e.g. rominfo g:\mame\roms\pacman.zip


Useful Tips
-----------

1) ROMInfo supports drag and drop of ROMs/ZIP files in Explorer.

Highlight the files you want to check and drag them onto rominfo.exe

2) Wildcards can be used for specifying filenames on the command line.

e.g. rominfo pacman.*


Source
------

As with all of my tools, I have included the source code so you can make
your own modifications but please do not distribute those versions. If
you make any useful changes then please send them to me so that I can
include them in future releases.

To compile this tool, you will need to get DatLib from http://www.logiqx.com/


Bug reports
-----------

If you find any bugs please let me know about them.


Thanks
------

D-Zine who prompted me to write this and came up with the ZIP file idea.

