-------------------------------------------------------------------------------
                         ROMBuild v2.8 - 17/10/2006

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


History
-------

05/10/2005  *** v2.7 ***

            Removed M1 ROMs since they are now MAME compatible (from v0.7.6)
            Removed Nebula ROMs since they are now MAME compatible (from v2.25)
            Added support for invaders.rom for SIDE

28/03/2005  *** v2.6 ***

            Updated altbeast ROMs (Calice and System16) to match MAME v0.95.

28/02/2005  *** v2.5 ***

            Internal game renames for Altered Beast (to match MAME v0.92).
            Internal ROM renames for a few CPS-2 games (to match MAME v0.92).
            Fixed a bug that caused the -l option to crash when listing ROMs.

30/01/2005  *** v2.4 ***

            Removed FBA v0.2.94.98 from the source (superceded by v0.2.95.22).
            Added von2 (MAME v0.91) for Nebula Jukebox v2.9 and M1 v0.7.5a3.

06/01/2005  *** v2.3 ***

            Removed ZiNc v0.9 from the source (superceded by v1.0.2).
            Removed WinKawaks v1.49 from the source (superceded by v1.52).
            Internal renames of tnzs and clone ROMs to match MAME v0.90.
            Added an extra option for the benefit of CAESAR.

26/10/2004  *** v2.2 ***

            Added Dynasty Wars support for various emus following MAME v0.87.

10/09/2004  *** v2.1 ***

            Removed the Snow Bros conversions for RAINE (now uses MAME ROMs).

02/07/2004  *** v2.0 ***

            Tidied up the code a bit. Now uses DatLib for common functions.
            Corrected internal filenames that were incorrect (mainly Neo-Geo).

11/04/2004  *** v1.19 ***

            Added 2020bb support (c3 and c4 ROMs changed in MAME v0.81).

09/03/2004  *** v1.18 ***

            Lots of changes around the Neo-Geo redumps of MAME v0.80:
            Removed Nebula
            Added ACE, RCPS
            Changed Calice, FBA, NeoRAGEx

            Also removed S11Emu and Zinc

05/02/2004  *** v1.17 ***

            Added support for Robo Army and Sengoku 2 to various emulators
            (Calice, FBA, M1, NeoRAGEx and Nebula).

19/12/2003  *** v1.16 ***

            Added a quick fix so that it does not process large unzipped files.

22/10/2003  *** v1.15 ***

            Removed support for some Androdun ROMs in NeoRAGEx.
            Changed the internal details for Modeler's harddunk (harddunj in MAME).
            Added Tekken 2 sound ROMs for S11Emu and Zinc.
            Added Gauntlet graphics ROMs for MGE.
            Added Snow Bros graphics ROMs for various emulators.
            Added various games for RAINE.

06/05/2003  *** v1.14 ***

            Added gaiapols/gaiaplis for Hoot and M1.
            Added harddunk for Modeler.

18/01/2003  *** v1.13 ***

            Added ThunderForce AC (Bootleg) for Sega System C2 Emulator v0.2b.

24/03/2002  *** v1.12 ***

            Changed internals for Space Invaders Galactica to match MAME v0.59.
            Added support for Tower of Druaga ROMs (HiVE v1.04).

23/03/2002  *** v1.11 ***

            Changed source to compile without modification on FreeBSD.
            Changed internal Neo-Geo ROM names to match MAME v0.59.
            Added support for Pisces graphics ROMs (changed in MAME v0.59):
              Xcade v0.85, MacMoon v0.86, Arcade Emulator v0.7, GalEmu v40.9,
              PASMulator v0.22, Replay v0.04, Rockulator++ v0.98a, SAGE v1.16,
              Sparcade v2.33b, VAntAGE v1.11

11/11/2001  *** v1.10 ***

            Changed internal details of wboy, wbml and tnzs for MAME v0.56.
            Unfortunately it is also impossible to build alpham2 for NeoRAGEx
            now (due to MAME using a new and completely different dump).

28/08/2001  *** v1.9 ***

            Changed internal details for Pacman clones to match MAME v0.53
            Added Altered Beast for Calice (why does it use old ROM sets)!

22/07/2001  *** v1.8 ***

            Added Super Galaxians for Mimic v1.08.
            MS Pacman was renamed in MAME v0.37b16. Changed ROMBuild to match.

08/06/2001  *** v1.7 ***

            Added Speed Freak for Cinelator 95 Beta.
            Now compiled using MinGW and the -Wall option (for clean code).

17/03/2001  *** v1.6 ***

            Fixed problem affecting NeoRAGEx/Callus builds from unzipped ROMs.
            Added '-L' option to list all of the ROMs that ROMBuild supports.
            Removed Xevious Emulator Demo v1.6 (no longer necessary).
            Changed xevious and sxevious PROMs in HiVE to use clean MAME PROMs.

11/03/2001  *** v1.5 ***

            Added SonSon support for RAGE, Replay, Rockulator++ and SonSon Emu.

01/03/2001  *** v1.4 ***

            Added full support for NeoRAGEx v0.6 (32 games need converting).
            Added support for QSound Player v2.

01/02/2001  *** v1.3 ***

            Added support for Road Runner in Sideway (Desert Gun in MAME).
            Removed RAINE because v0.30 uses MAME ROMs.

18/01/2001  *** v1.2 ***

            Added ClassicEmu v0.01 (because of change in MAME v0.37 b11).
            Changes to galap1 throughout (because of change in MAME v0.37 b11).
            Added superg where necessary (because of change in MAME v0.37 b11).
            Added galagb where necessary (because of change in MAME v0.37 b11).

16/12/2000  *** v1.1 ***

            Added Jump Bug Emulator v0.50.
            Added Kung Fu Master v0.0000001a.

08/12/2000  *** v1.0 ***