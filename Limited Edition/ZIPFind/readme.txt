-------------------------------------------------------------------------------
                         ZIPFind v2.4 - 24/03/2008

                  Written by Logiqx (http://www.logiqx.com)
-------------------------------------------------------------------------------

Introduction
------------

ZIPFind is a useful little tool that helps you to find ZIPs that you want from
a friends FTP server (or whatever). In order for it to run, your friend must
provide a list of his ZIPs in the format:

full path + zip name <tab> file name <tab> file size <tab> file crc <eol>

Alternatively, you can also use this format:

"full path + zip name" <sp> "file name" <sp> file size <sp> file crc <eol>

If you need a program to generate your file listing, try my ZipList tool.


Scoring Zips
------------

ZIP matches are measured in two ways and then given a score:

Usefulness   - The percentage of the ZIP contents that you need
Completeness - The percentage of a particular game within the ZIP

Score        - Usefulness * Completeness

Total Score  - Sum of the scores
               Note: It can be >1 if the same ZIP matches more than one game


Basic Usage
-----------

Firstly, you'll need a file that lists everything that you are looking for.
This file must be in MAME listinfo format (a.k.a. CMPro format) but I will
leave it for you to figure out how to generate it!

Given that the file is called 'missing.dat' and the ZIP listing is called
'allzip.txt', you can run ZIPFind using the following syntax:

   zipfind missing.dat allzip.txt


Three files will be generated after processing:

   zf_games.log - List of games found (with corresponding ZIPs shown below)
                  Games are in the order that they appear in missing.dat

   zf_zips.log  - List of ZIPs found (with corresponding games shown below)
                  ZIPs are in order of their total score

   zf_fetch.log - Plain list of ZIP names to download
                  ZIP names are in order of their total score


Advanced Usage
--------------

The -v option:

If you want more detailed information in zf_games.log and zf_zips.log, then
use 'verbose' mode.

Syntax:

   zipfind -v <missing.dat> <allzip.txt>


The -u option:

You can prefix lines in zf_fetch.log using the URL option.

   zipfind -u ftp://user:pass@my.m8.com/ <missing.dat> <allzip.txt>


Both of the above options can be combined should you wish.


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


Future
------

I'm not sure that I plan to take this any further, I'm kind of happy with
what it does already!

