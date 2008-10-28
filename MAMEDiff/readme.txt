-------------------------------------------------------------------------------
                          MAMEDiff v2.30 - 28/10/2008

                   Written by Logiqx (http://www.logiqx.com/)
-------------------------------------------------------------------------------

1. Introduction
---------------

MAMEDiff makes it easy to identify ROM related changes in a new release of MAME.
Sometimes sets can just be 'rebuilt' but other times you will need to download
new or fixed ROMs. MAMEDiff will tell you what needs to be done and also gives
instructions specific to merged/split/non-merged sets. It will cut down on
unnecessary ROM downloading and makes it easier to see what sets need fixing.
It also makes it possible to completely fix+update your sets with one pass of
your favorite ROM manager... just rebuild the ZIPs that MAMEDiff tells you and
both the changes and additions can done together. :)

MAMEDiff is far more powerful than a simple text comparison and is even useful
alongside a good ROM manager. It can spot game renames and will not regard them
as one game deleted and another added. When ROMs or games are renamed (or if
there is a change in the way that sets are merged), MAMEDiff will just tell you
how to rebuild the affected sets (i.e. no downloading required). Even if every
game and ROM were renamed, MAMEDiff would know that you don't need to download
a thing. It only takes a fraction of a second to work it out too!

Please note: MAMEDiff is not intended as a "what new games can I leech?" tool.

The purpose of MAMEDiff is to assist in keeping your ROM sets working with the
minimum of effort. It is also good to see what has changed in the new release
(it has even found game additions that aren't mentioned in whatsnew.txt).

MAMEDiff was developed using MinGW and is free to use. But... you use MAMEDiff
at your own risk. I take no responsibility for any loss/damage caused as a
result of its use.


2. Distribution
---------------

The home page for MAMEDiff is http://www.logiqx.com/


3. Using MAMEDiff
-----------------

There are two ways that you may want to use MAMEDiff; one will give a general
overview of changes and the other will tell you how to fix your sets.

Before you use MAMEDiff you will need the listxml output from the versions of
MAME that you are comparing. You can do this with the following command:

mame -listxml >listxml.txt

For older versions of MAME, you may need to use the listinfo option instead:

mame -listinfo >listinfo.xml


3.1. To generate a summary of changes
-------------------------------------

Use the command:

mamediff listxml.1 listxml.2      (using whatever file names you chose)


This will save a report to mamediff.log containing up to 4 sections:

- Game removals. Occasionally this will be a false alarm and there will be a
  corresponding game addition. This problem is explained later in this document.
- General set changes. These include ROM renames, ROM removals, remerging and
  game renames (where the 8 character name changes but not the ROMs themselves).
- Games requiring new/fixed ROMs. These are existing games that need extra ROMs.
- Game additions. These are totally new games to MAME.

If you want a detailed summary (this shows the ROM changes for all the sections
above), use the '-v' option (verbose mode). This gives a deeper insight into the
changes and also says whether the new ROMs can already be found elsewhere in
MAME sets.

i.e. mamediff -v listxml.1 listxml.2

Handy tip: Wildcards can also be used to specify the filenames.


3.2. To generate a customised report for your ROM set type
----------------------------------------------------------

Use the m, s or n options (m=merged sets, s=split sets, n=non-merged sets).

e.g. mamediff -m listxml.1 listxml.2


This will save a report to mamediff.log containing 3 sections:

- Set changes. A list of the ZIP files affected by the new MAME release (this
  is an amalgamation of sections 1 and 2 from the standard report but how they
  effect your set type). Run these ZIPs through your ROM manager's rebuild
  option. It may be that there is a more efficient way to implement the changes
  but a rebuild is by far the easiest.
- Games requiring new/fixed ROMs. These are existing games that need patches.
  It may be that these ROMs are already available in MAME so use the verbose
  option to check.
- Game additions. These are totally new games to MAME.


4. How to use the reports
-------------------------

The syntax of the reports should be fairly self explanatory but I'll give a
couple of examples.

e.g. a game rename looks like this:

< Pole Position II (Atari set 2) [name: poleps2a - parent: polepos2]
> Pole Position II (Atari bootleg 2) [name: poleps2c - parent: polepos2]

e.g. a ROM rename looks like this:

< rom ( name la02 size 2048 crc 43bc65c5 )
> rom ( name spcewarl.2 size 2048 crc 43bc65c5 )

A removal or addition is shown by a line beginning '<' or '>'.


5. Alternative reports and dat creation
---------------------------------------

Before describing the four dat creation options, it is worth pointing out that
the higher the number, the smaller the resultant dat. So, -d1 will generate
the largest dat (and thus ROM set) whilst -d4 will generate the smallest one.

Each mode has a different aim regarding compatibility and they are described
in the following sections of this document.


5.1 Using the -d1 option to show 'ZIPs updates'
-----------------------------------------------

Use the -d1 option in addition to -m, -s, -n (whatever is suitable for your
set type; m=merged sets, s=split sets, n=non-merged sets) and MAMEDiff will
list 'ZIPs Removed', 'ZIPs Changed' and 'ZIPs Added'. It will also create a
CMPro dat that can be used to build these sets in isolation (for speed or for
archiving). If you prefer ROMCenter to CMPro then convert the dat using DatUtil
(available at http://www.logiqx.com/).

This option is ideal for webmasters as it will allow them to build just the new
and changed ROM sets that need uploading to their website following a new MAME
release. The resultant ZIPs will be 100% complete and not miss any ROMs.

Some emulators may require supplements of this nature (i.e. complete ZIPs) and
an example of this is FBA. However, to reduce the size of the supplement ROMs
there is an aditional option -x which will exclude ROM removals from the
algorithm. The result is complete ZIPs where the emulator requires additional
ROMs, rather than when it is just different in some way (e.g. due to removals).

Note: -d1 is the direct equivalent of the old -M, -S and -N options.


5.2 Using the -d2 and -d3 options to produce supplementary dats
---------------------------------------------------------------

In addition to the -d1 option that produce CMPro dats for all of the changed
ZIPs, you can produce 'supplementary dats'. The -d2 and -d3 options create
small supplementary dats for the new emulator that when added to the original
set is 100% suitable for the new emulator (n.b. only useful for emulators that
support multiple ROM paths).

The difference between -d2 and -d3 is the level of compatibility with an
emulator over time. The -d2 option should guarantee ever-lasting forward
compatibility if you create supplementary ROM collections with each release
of the emulator. The -d3 option will create slightly smaller supplements but
they will only be compatible for that one release! Note: -d1 is also fully
compatible over time but much larger than -d2.

Not only can these options be used when upgrading from one version of an emu
to another but they can even be used when trying to use ROMs of one emulator
with another (e.g. trying to use MAME ROMs with RAINE, Kawaks or Nebula). When
used in this way you can use a standard MAME ROM set and a small emulator
specific 'supplementary' ROM set for the emulator of your choice.

-d2 is most suitable for each release of MAME (as -d2 is compatible over time).
-d3 is most suitable for differences between MAME and Nebula/Kawaks, etc.

Note: -d3 is very similar in nature to the old 'tiny' supplements of MAMEDiff.

When using the -d1, -d2 and -d3 options, there are several additional options.
These are detailed after the section describing use of the -d4 option.


5.3 Using the -d4 option for ROM archival
-----------------------------------------

The -d4 option uses the same logic as -d2 and -d3 but ignores the issue of
compatibility completely! It simply checks if a ROM (or disk/sample) exists
in the first data file (ignoring what the name of the game it is in) and if
it does then it will not appear in the output data file.

This has greater benefits for split (-s) and non-merged (-n) sets but also
reduces the size of a merged (-m) supplement.

Note 1: The only intention of this mode is for archival purposes. It cannot be
used to create 100% compatible supplements like -d1, -d2 and -d3.

Note 2: There is a chance that ROMs will be duplicated in the output datfile.
There is no de-duplication across games in the second data file so to minimise
the chance of duplicates occuring, the -m option might be your best option.


5.4 Options for use with -d1, -d2, -d3 and -d4
----------------------------------------------

-r will include ROM renames in the output data file. Use this option if the
   target dat is for an emulator that does not have CRC support.
   
-z will include 'nodump' ROMs in the output data file. If you prefer not to
   have dummy ROMs then do not use -z and conversely, if you like to have
   dummy ROMs then use -z.

-b will include allow you to use non-separated BIOS ROMs just like ClrMamePro.

-o can be used to change the object type (valid types are 'disk' or 'sample')
   that the supplement is for (the default object type is 'rom').

In order for the -d options to work, they interpret the clrmamepro header item
'forcemerging' from the dats (to identify the styles of ROM merging that
are supported by the emulators). Absense of this item is taken to mean that all
types of merging are supported (i.e. ROMs can be in either parent or clone) and
'split merging' is assumed as a default if you do not specify -m, -s or -n.


5.5 ROM auditing using the -d1 option
-------------------------------------

You can scan audit ROMs to a certain degree with the -d1 option (by comparing
a directory against a data file). This can be achieved with a command along
the lines of:

mamediff -s -d1 -r "E:\MAME\ROMs" "MAME v0.84.dat"

The same principal can also be used for disks and samples (using the -o option
of MAMEDiff as described earlier in this document).

mamediff -m -d1 -r -o sample "E:\MAME\Samples" "MAME v0.84.dat"

n.b. ClrMamePro seems to fully merges samples, hence the -m option being used.

mamediff -s -d1 -o disk "E:\MAME\CHDs" "MAME v0.84.dat"

n.b. Some CHDs are missing the '.chd' extension in the MAME XML output, hence
     the -r option is not specified (since renames need to be ignored).


6. Usage changes in v2.0
------------------------

In MAMEDiff v2.0, the options have been changed as part of the rewrite!

The old options convert to the new options as shown below:

v1.x      v2.x              Comment
----      ----              -------
 -v        -v
 -m        -m
 -s        -s
 -n        -n
 -M        -m -d1 -r -z     You may like to remove the -r and -z options now.
 -S        -s -d1 -r -z     You may like to remove the -r and -z options now.
 -N        -n -d1 -r -z     You may like to remove the -r and -z options now.
 -M -t     -m -d3 -r -z     You may like to remove the -z option now.
 -S -t     -s -d3 -r -z     You may like to remove the -z option now.
 -N -t     -n -d3 -r -z     You may like to remove the -z option now.
 -M -T     -m -d3 -z        You may like to remove the -z option now.
 -S -T     -s -d3 -z        You may like to remove the -z option now.
 -N -T     -n -d3 -z        You may like to remove the -z option now.

If you try to use the old syntax, MAMEDiff 2.0 will convert it to the new one
and tell you what it has done. At some point in the future, I will probably
remove this feature so please start using the new syntax.


7. Limitations
--------------

A good tip is to check that for each game removal there isn't a similar game
addition in the last section. This can happen when the 8 character name for a
game is changed at the same time as the ROM content itself. MAMEDiff can spot
game renames by their ROM content. However if both the name and content change
at once then it won't know that the old and new games are related so it comes
up as a deletion and an addition.

The logic that decides on necessary rebuilds is intended to make life simple. It
does not differentiate between simple renames and ROMs physically moving from
one ZIP to another. It just says which ZIPs need rebuilding to fix all of the
ZIPs.

Other than that, I think I've covered most things pretty well...


8. Source
---------

I have included source for anyone who is interested but don't look at it for too
long. Getting your head around it is liable to give you a headache... you have
been warned! :)

To compile this tool, you will need to get DatLib from http://www.logiqx.com/


9. Bug reports
--------------

If you find any bugs please let me know about them.

If a set change fails to appear in the summary output then it is a bug. If an
action isn't given to fix an issue reported in the summary output then it could
also be a bug.


10. Thanks
----------

Thanks to Pi for beta testing MAMEDiff and suggesting some little ideas (like
tiny dat generation). Thanks also to Guru-Choc for doing early beta testing.

