-------------------------------------------------------------------------------
                          ImgChk v2.10 - 24/03/2008
                  Written by Logiqx (http://www.logiqx.com)
-------------------------------------------------------------------------------

Introduction
------------

ImgChk has been created for the use of people that supply images for emulator
frontends (e.g. icons, snaps, cabinets, marquees, flyers). It will verify image
collections against a listinfo format datafile and can report unknown images as
well as missing images. Image checks for clones and resources are optional.


Usage
-----

1) Configure ImgChk by editing the INI file (imgchk.ini).

   This file is pretty straightforward so I will leave you to figure it out!

2) Run imgchk.exe and optionally, redirect output to a log file:

   e.g. imgchk >imgchk.log

3) That's about it, enjoy!


Limitations
-----------

1) It does not generate a log file (just use it as described above).

2) It is not possible to specify 'ignore masks' for the unknown file check.
   By default ImgChk will ignore any files with an extension of '.txt'.


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

