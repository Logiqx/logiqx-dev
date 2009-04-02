-------------------------------------------------------------------------------
                         ROMBuild v2.13 - xx/xx/xxxx

                  Written by Logiqx (http://www.logiqx.com)
-------------------------------------------------------------------------------

Introduction
------------

ROMBuild is a ROM manipulation tool that is capable of creating ROMs for the
older arcade emus using MAME ones. An example of this is by splitting ROMs in
two or joining two together but ROMBuild supports much more than this. It can
can split, join, extract, fill, patch, pad, interleave etc but to you the user
that doesn't really matter. The important thing is that MAME ROMs go in and
ROMs for another emulator come out. :)


Usage
-----

There are two modes of operation:

1) Listing what it supports
2) Rebuilding ROMs

These are both described below.


Listing what ROMBuild supports
------------------------------

1) The simplest listing command is:

   rombuild -l

   This will list all of the emulators that ROMBuild supports.

2) rombuild -l <emu name>

   For example, 'rombuild -l replay'

   This will list the games that ROMBuild supports for Replay.

3) rombuild -l <emu name> <game name>

   For example, 'rombuild -l replay pacman4x'

   This will list the ROMs that ROMBuild will build for pacman4x in Replay.

4) rombuild -L

   This will list all of the ROMs that ROMBUild supports.

Rebuilding ROMs
---------------

1) Copy the MAME ROMs that you wish to convert into the 'roms_in' directory.
   These can be ZIPed or unzipped and in any directory under 'roms_in'.

2) To convert ROMs for a particular emulator, type:

   rombuild <emu name>

   Your new ROMs should now be in the 'roms_out' directory. :)


Extra Rebuild Options
---------------------

1) You can build ROMs for a specific game using the command:

   rombuild <emu name> <game name>

2) You can specify alternative 'in' and 'out' directories. For example:

   rombuild -i d:\mame\roms -o e:\replay\roms replay

   This would scan your MAME ROMs and generate all possible ROMs for Replay.

   This will thrash your HD a bit but scanning a full MAME set only takes 40
   seconds on my P233MMX. I don't think that's too bad!


Source
------

As with all of my tools, I have included the source code so you can make
your own modifications but please do not distribute those versions. If
you make any useful changes then please send them to me so that I can
include them in future releases.

I have included the source for two other reasons:

1) So people can see exactly what conversions take place (see rominfo.h)
2) As example source for people who are trying to learn the C language.

To compile this tool, you will need to get DatLib from http://www.logiqx.com/


Bug reports
-----------

If you find any bugs please let me know about them.


Thanks
------

MAME for ROMCmp (the most excellent ROM comparison tool).
Pi for beta testing ROMBuild.
CAESAR (which although by me, without it I'd never have created ROMBuild).

