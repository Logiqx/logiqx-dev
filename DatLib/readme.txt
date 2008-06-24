-------------------------------------------------------------------------------
                          DatLib v2.30 - 24/06/2008

                  Written by Logiqx (http://www.logiqx.com)
-------------------------------------------------------------------------------

Introduction
------------

DatLib is a standard library that is used throughout my tools.  It supports a
variety of data file formats and handles the standard loading, cleansing,
converting and saving operations that are required by tools such as DatUtil,
MAMEDiff, ROMBuild, ROMInfo and ZipIdent. It supports a variety of formats...

Load and Save:

  - MAME ListInfo (ClrMamePro, MAME, MESS, RAINE, Shark)
  - RomCenter 2.50
  - MAME ListXML (MAME and MESS)
  - Generic XML
  - Tab Delimited

Load only:

  - RomCenter 1.90
  - RomCenter 2.00
  - Nebula Drivers
  - Calice Drivers
  - Zinc --list-sets
  - GNGEO romrc
  - ClrMame Log
  - Folder Scan (subdirectories and zips)

Save only:

  - MAME GameList
  - Title List (for listing game titles - used by CPS-2 readme and RAINE docs)
  - RomCenter Sublist
  - Game Launcher / GameEx Map File

This package is a source only release and is only required if you want to
compile any of my tools.

You are also free to use it in your own tools but please give me credit where
it is due and also tell your users where the original source can be found!


Setting up the environment
--------------------------

DatLib and my tools can be easily compiled using MinGW and CygWin on Windows
or GCC on Linux. Set up an environment for compiling everything as follows:

1) Create a directory somewhere on your machine for all of my utilities.
   e.g. mkdir d:\logiqx         Windows
        mkdir d:/logiqx         CygWin
        mkdir $HOME/logiqx      Linux

2) Create an environment variable called 'LOGIQX' that points to the directory.
   e.g. set LOGIQX=d:\logiqx            Windows
        export LOGIQX=d:/logiqx         CygWin
        export LOGIQX=$HOME/logiqx      Linux

3) Create a directory called 'dev' inside the Logiqx directory.

4) Create a directory called 'datlib' inside the 'dev' directory.

5) Extract the source for DatLib into the 'datlib' directory.

Repeat steps 4 and 5 for all of the Logiqx tools that you want to compile
(e.g. DatUtil, MAMEDiff, ROMBuild, ROMInfo, ZipIdent).


Required Tools and Libraries
----------------------------

As already stated, DatLib and my tools can be compiled on Windows using MinGW
or CygWin and using GCC on Linux. In addition to these tools, you must ensure
that zlib is installed and UPX is available (preferable but not essential).

Here is a quick summary of the tools that you need:

Windows: MinGW   http://sourceforge.net/projects/mingw
         CygWin  http://www.cygwin.com
         zlib    http://www.gzip.org/zlib/
         UPX     http://upx.sourceforge.net/

Linux:   GCC     Comes with your OS
         zlib    Comes with your OS
         UPX     http://upx.sourceforge.net/


Compiling
---------

If the environment has been set up correctly and your compiler is working then
compilation should be simple. Just 'cd' to the appropriate directory and run
'make'.

e.g. cd d:\logiqx\dev\datutil         Windows
     make

     cd d:/logiqx/dev/datutil         CygWin
     make

     cd $HOME/logiqx/dev/datutil      Linux
     make

If DatLib has not been compiled already, compiling any of the other tool will
automatically force a compilation of DatLib first.

Notes:

1) By default the executables will be created with .exe extensions but this
   obviously isn't desirable on Linux. To remove the extensions, you can just
   edit the makefiles and change the lines 'EXT=.exe' to 'EXT='.

2) UPX is optional on Windows and Linux but the compilcation will seem to fail
   if it is not installed. However, the compile will be fine and re-running
   'make' will tell you that there is nothing more to do.


Adding support for new dat formats
----------------------------------

I may explain this in more detail at a later date but for now I will just say:

1) Add details of your new driver to src/driver.c

2) Create a new source file for your driver in src/drv (e.g. src/drv/xxx.c).
   Tip: I would just copy an existing driver then remove the bulk of the code.

3) Write identify_xxx(), load_xxx() and save_xxx() in src/drv/xxx.c.

Your best best is to just look at some existing drivers and figure out what
yours should do!


Using DatLib in your own programs
---------------------------------

Again, I will take the lazy option here and say that it is easiest to look at
my existing tools as an example! I would recommend that you look at DatUtil,
ROMInfo or ZIPIdent rather than MAMEDiff or ROMBuild. The three tools that I
have suggested have near identical makefiles and demonstrate how DatLib should
be used. DatUtil is by far the simplest because it is basically just a command
line interpreter for DatLib. ROMInfo and ZIPIdent are a little more complicated
but demonstrate how the DatLib structures can be used for ROM searches, etc.


Thanks
------

The MAME team for their unzip routines (found in src/mame).
Christophe Devine for his RFC 1321 compliant MD5 implementation (src/hash).
Christophe Devine for his FIPS-180-1 compliant SHA-1 implementation (src/hash).
Pi for beta testing tools that use DatLib.


Source
------

As with all of my tools, I have included the source code so you can make
your own modifications but please do not distribute those versions. If
you make any useful changes then please send them to me so that I can
include them in future releases.


Limitations
-----------

The XML parser is very primitive and does not utilise a DOM or SAX library.

It has the following limitations (mainly related to the use of line feeds):

1) You can only have one XML element on any single line.

  Supported:

    <description>Aliens (Tempest Prototype)</description>
    <year>2001</year>

  Unsupported:

    <description>Aliens (Tempest Prototype)</description><year>2001</year>

2) Elements containing PCDATA must be contained within a single line.

  Supported:

    <description>Aliens (Tempest Prototype)</description>

  Unsupported:

    <description>Aliens (Tempest
                 Prototype)</description>

3) Attributes must be on the same line as the element that they relate to:

  Supported:

    <rom name="aliens_r3.bin" size="2048" crc="6cabcd08"/>

  Unsupported:

    <rom name="aliens_r3.bin" size="2048"
         crc="6cabcd08"/>

Due to the first limitation, nested elements need to occupy multiple lines.

  For example:

    <game name="alienst">
        <description>Aliens (Tempest Prototype)</description>
        <year>2001</year>
        <manufacturer>Atari</manufacturer>
        <rom name="aliens_r3.bin" size="2048" crc="6cabcd08"/>
        <rom name="aliens_r1.bin" size="2048" crc="555c3070"/>
        <rom name="aliens_p1.bin" size="2048" crc="7c10adbd"/>
        <rom name="aliens_n3.bin" size="2048" crc="5c8fd38b"/>
        <rom name="aliens_n1.bin" size="2048" crc="bd98c5f3"/>
        <rom name="aliens_l1.bin" size="2048" crc="cd246ac2"/>
        <rom name="aliens_k1.bin" size="2048" crc="0ac96e87"/>
        <rom name="aliens_j1.bin" size="2048" crc="5487d531"/>
        <rom name="aliens_d1.bin" size="2048" crc="337e21f6"/>
        <rom name="aliens_f1.bin" size="2048" crc="4d2aabb0"/>
        <rom name="aliens_e1.bin" size="2048" crc="337e21f6"/>
        <rom name="aliens_h1.bin" size="2048" crc="a503f54a"/>
    </game>

Basically, DatLib is able to reliably parse the XML generated by emulators such
as MAME, MESS and M1 but if you load it into an XML editor and it reformats the
document it may not parse correctly afterwards!

At some time I will implement a proper XML parser so that these limitations can
be removed from DatLib.


Bug Reports
-----------

If you find any bugs please let me know about them and provide details such as
your OS version, features that you are using, the dat you are loading, etc.

Feel free to send me any suggestions that you have also. I may be too busy to
do anything with them but I am interested to hear them!

