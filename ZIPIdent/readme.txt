-------------------------------------------------------------------------------
                         ZIPIdent v2.9 - 26/11/2007

                  Written by Logiqx (http://www.logiqx.com)
-------------------------------------------------------------------------------

Introduction
------------

ZIPIdent has been created to assist in the management of unemulated or 'needed
soon' ROM collections. Anyone who possesses such a collection (emu developers
for example) may find it difficult to spot games that become emulated and then
remove them from the unemulated collection. ZIPIdent will identify ZIPs that
should not be classified unemulated and if desired will even move them out
of the 'unemulated' collection and into a separate directory.

It is quite similar to MAME's '-romident' function except for the fact that it
processes entire ROM collections, not just an individual ZIP. ZIPIdent probably
has some additional logic that '-romident' doesn't contain too (not checked).

If you have trouble in using this program or interpreting its reports then it
probably isn't for you, please don't question me about it.


Basic Usage
-----------

Firstly, you'll need to put the MAME listxml output into the same directory
as ZIPIdent.exe.

   mame -listxml >zipident.dat

N.B. Old versions of MAME provided 'listinfo' rather than 'listxml'. For those
versions of MAME, use the 'listinfo' output.

To process a directory or ZIP with ZIPIdent, just use the syntax:

   zipident <directory/zip>

Two reports are written to the location of the directory/ZIP that you are
processing:

   zipident_definite.log - ZIPs that are definitely unneeded
   zipident_maybe.log    - ZIPs that _may be_ unneeded

Drag and drop is supported for those who don't like using the command line.


Advanced Usage
--------------

The -d option:

When you are confident about ZIPIdent's functionality, you can use the '-d'
option to move definite matches into a folder called '_zipident_definite'
(created in the same location as the log files).

Syntax:

   zipident -d <directory/zip>


The -t option:

ZIPIdent can process a text file that lists ZIP contents but it must be
in a very specific format (zip name, rom name, size, crc). e.g.

"./unemulated/Acclaim/Judge_Dredd_partial.ZIP" "J-DREAD.U35" 131072 c1e17191
"./unemulated/Acclaim/Judge_Dredd_partial.ZIP" "J-DREAD.U36" 131072 37addbf9
"./unemulated/Acclaim/Judge_Dredd_partial.ZIP" "Judge" 479 d815f218

Tab delimited files are also supported but must not contain quotes as above.

Syntax:

   zipident -t allzip.txt

NB. The -t option is intended for a very specific purpose and I am not
going to explain how such a text file is created. Processing real ZIPs is
very fast anyway so it is very unlikely you will need this option. ;)


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

I have a few ideas but such things only tend to get written when I have
some spare time (what's that then?) or need the feature desperately!


Thanks
------

Thanks to Pi, Tormod and Till for being the guinea pigs (a.k.a. beta testers).


How does it work?
=================

ROM Scoring
-----------

In trying to match ROMs there are three attributes that can match; name, size
and CRC. Each matching attribute is given a value (1=name, 2=size, 4=CRC) and
more than one matching attibute is represented by the sum of the values.

e.g.               CRC = 4
            size + CRC = 6
     name + size + CRC = 7

It can be seen that the higher the value, the better the match (0 meaning none
and 7 meaning perfect). Some values are pretty unlikely such as 5 (which means
that just the CRC and names match but such matches would almost certainly have
a matching size too, i.e. a score of 7).


Step 1 - Identifying readmes
----------------------------

For each file in the ZIP, a decision is made as to whether it is a readme.
This is just a case of checking the ROM size is not a power of 2 (also checks
that the size is less than 1MB - to cater for hard disks in the future). A
readme is considered a size match only.


Step 2 - Identifying dummy ROMs
-------------------------------

For each file in the ZIP, a decision is made as to whether it is a dummy ROM
(i.e. created by CMPro due for a CRC of 00000000). This is a simple task that
is achieved using a straight forward file size and CRC lookup. If the file is
deemed to be a dummy ROM then it is flagged as such and is also regarded as a
size and CRC match.


Step 3 - Searching for ROM matches
----------------------------------

Just matches on the three file attributes CRC, name and size. Zero, one or more
of these attrbiutes may match and every matching ROM in the listxml acquires
a 'best score' (performed against all files in the ZIP).


Step 4 - Interpreting the matches
---------------------------------

If all genuine ROMs in the ZIP (i.e. those that aren't readmes or dummy ROMs)
have at least a CRC match then the ZIP is classified as a 'definite' match.
If not a 'definite' match and at least 2% of the ROMs (based on file size) had
a CRC match then the ZIP is classified as a 'maybe'. If the ZIP is a 'definite'
or 'maybe' then the most likely games are identified by scoring all of the
games that had ROM matches using a rule based on ROM sizes and match scores.

See the source for complete details (it contains few comments though).


Step 5 - Reporting
------------------

This step simply reports the most likely game(s) that match (if the top score
is shared by more than one game then they are all listed) and listing the best
types of match found for each ROM (note that different ROMs may have been
matched against different games).

