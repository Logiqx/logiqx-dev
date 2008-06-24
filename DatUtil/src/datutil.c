/* --------------------------------------------------------------------------
 * DatUtil - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for converting, cleansing and comparing ROM manager
 * dats (e.g. ClrMamePro, RomCenter).
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define DATUTIL_VERSION "v2.40"
#define DATUTIL_DATE "24 June 2008"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"
#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"


/* --- DatUtil definitions and macros --- */

#include "datutil.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


/* --------------------------------------------------------------------------
 * The main program
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	/* --- For getopt function --- */

	extern char *optarg;
	extern int optind;
	char c;

	struct stat buf;
	struct dat *dat=0, *blend=0;
	struct options *options=0;

	int test=0, incorporate=0, errflg=0;

	/* --- Display version information --- */

	printf("===============================================================================\n");
	printf("DatUtil %s (%s) - using ", DATUTIL_VERSION, DATUTIL_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Allocate memory for user options --- */

	STRUCT_CALLOC(options, 1, sizeof(struct options))

	/* --- Get the options specified on the command line --- */

	while (!errflg && (c = getopt(argc, argv, "f:qkjo:a:tA:V:C:R:F:T:E:H:U:O:M:P:Z:N:g:cG:S:!rlsXDp:i:I:xmvd?")) != EOF)
	switch (c)
	{
		/* --- Saving --- */
		case 'f':
			LOWER(optarg);
			options->save_format=optarg;
			break;
		case 'q':
			options->options|=OPTION_ALWAYS_QUOTE;
			break;
		case 'k':
			options->options|=OPTION_KEEP_FULL_DETAILS;
			break;
		case 'j':
			options->options|=OPTION_NEBULA_JUKEBOX;
			break;
		case 'o':
			options->save_name=optarg;
			options->save_mode="w";
			break;
		case 'a':
			options->save_name=optarg;
			options->save_mode="a";
			break;
		case 't':
			test++;
			break;
		/* --- Header text --- */
		case 'A':
			options->header.author=optarg;
			break;
		case 'V':
			options->header.version=optarg;
			break;
		case 'C':
			options->header.category=optarg;
			break;
		case 'R':
			options->header.name=optarg;
			break;
		case 'F':
			options->header.description=optarg;
			break;
		case 'T':
			options->header.date=optarg;
			break;
		case 'E':
			options->header.email=optarg;
			break;
		case 'H':
			options->header.homepage=optarg;
			break;
		case 'U':
			options->header.url=optarg;
			break;
		case 'O':
			options->header.comment=optarg;
			break;
		case 'M':
			options->clrmamepro.forcemerging=optarg;
			break;
		case 'P':
		case 'Z':
			options->clrmamepro.forcepacking=optarg;
			break;
		case 'N':
			options->clrmamepro.forcenodump=optarg;
			break;
		/* --- Game selection --- */
		case 'g':
			options->options|=OPTION_GAME_SELECTION;
			options->game_selection=optarg;
			break;
		case 'c':
			options->options|=OPTION_CLONE_SELECTION;
			break;
		case 'G':
			options->options|=OPTION_SOURCEFILE_SELECTION;
			options->sourcefile_selection=optarg;
			break;
		case 'S':
			options->options|=OPTION_SUBSTRING_SELECTION;
			options->substring_selection=optarg;
			break;
		case '!':
			options->options|=OPTION_INVERT_SELECTION;
			break;
		case 'r':
			options->options|=OPTION_REMOVE_CLONES;
			break;
		/* --- Cleansing --- */
		case 'l':
			options->options|=OPTION_LOWER_CASE;
			break;
		case 's':
			options->options|=OPTION_SORT_GAMES_BY_PARENT;
			break;
		case 'X':
			options->options|=OPTION_FIX_MERGING_OFF;
			break;
		case 'D':
			options->options|=OPTION_REMOVE_DUPLICATES_OFF;
			break;
		case 'p':
			if (strstr(optarg, "rom"))
				options->prune_roms++;
			if (strstr(optarg, "disk"))
				options->prune_disks++;
			if (strstr(optarg, "sample"))
				options->prune_samples++;
			break;
		/* --- MD5/SHA1 --- */
		case 'i':
			options->fn=optarg;
			break;
		case 'I':
			options->fn=optarg;
			incorporate++;
			break;
		/* --- MD5/SHA1 --- */
		case 'x':
			options->options|=OPTION_EXTENDED_CHECKSUMS;
			break;
		case 'm':
			options->options|=OPTION_MD5_CHECKSUMS;
			break;
		/* --- Information --- */
		case 'v':
			options->options|=OPTION_VERBOSE_LOGGING;
			break;
		case 'd':
			options->options|=OPTION_SHOW_DEBUG_INFO;
			break;
		case '?':
			errflg++;	/* User wants help! */
			break;
	}

	/* --- The user must specify either one or two dat files --- */

	if (argc-optind!=1)
		errflg++;

	/* --- Display the help page if required --- */

	if (errflg)
	{
		printf("The best tool for converting between different ROM manager data file formats!\n");
		printf("For instructions on use, read the documentation that's been provided. Here is\n");
		printf("a brief summary of the options... far greater detail is in the documentation.\n\n");

		printf("Saving          [-f <output format>] [-q] [-k] [-j] [-o|a <output file>] [-t]\n");
		printf("ClrMamePro +    [-R <refname>] [-F <fullname>] [-C <category>]\n");
		printf("  RomCenter       [-V <version>] [-T <date>] [-O <comment>]\n");
		printf("                  [-A <author>] [-E <email>] [-H <homepage>] [-U <url>]\n");
		printf("                  [-M <merging>] [-P <packing>] [-N <nodump>]\n");
		printf("Game Selection  [-g <game names> [-c]] [-G <sourcefile names>]\n");
		printf("                  [-S <substring of description>] [-!] [-r]\n");
		printf("Cleansing       [-l] [-s] [-X] [-D] [-p[rom|disk|sample]]\n");
		printf("Blending        [-i <info file>] [-I <incorporate file>]\n");
		printf("MD5/SHA1        [-x] [-m]\n");
		printf("Information     [-v] [-d]\n\n");

		printf("Output formats and aliases:\n\n");

		printf("MAME ListInfo   listinfo info li clrmamepro clrmame cmpro cmp cm\n");
  		printf("MAME ListXML    listxml xml lx\n");
  		printf("Generic XML     genericxml generic gx\n");
  		printf("RomCenter 2     romcenter2 rc2 romcenter rc\n");
  		printf("Tab Delimited   delimited tab text\n");
  		printf("MAME GameList   gamelist gl\n");
  		printf("TitleList       titlelist titles\n");
  		printf("RC2 Sublist     sublist sub rcsublist rcsub\n");
  		printf("Map File        mapfile map\n\n");

	}

	if (!errflg)
	{
		/* --- Always show a summary after loading --- */

		options->options|=OPTION_SHOW_SUMMARY;

		/* --- If using an 'blend' dat, load it into memory --- */

		if (options->fn)
		{
			if ((blend=init_dat(options))==0)
				errflg++;
			else
			{
				printf("\n");
				if (incorporate)
					options->incorporate=blend;
				else
					options->info=blend;
			}
		}

		/* --- User must have specified an input name --- */

		options->fn=argv[optind];

		/* --- Log name for DatUtil --- */

		options->log_fn="datutil.log";

		/* --- If the user didn't specify an output name, use datutil.dat --- */

		if (!options->save_name)
			options->save_name="datutil.dat";

		/* --- If the user didn't specify an output mode, use overwrite --- */

		if (!(options->save_mode))
			options->save_mode="w";

		/* --- Initialise the main dat --- */

		if (!errflg && (dat=init_dat(options))==0)
			errflg++;

		/* --- Save dat from memory --- */

		if (!errflg)
		{
			if (test==0)
				errflg=save_dat(dat);
			else
				printf("No data file has been saved since 'test mode' is being used.\n");
		}

		/* --- Release dat(s) from memory --- */

		dat=free_dat(dat);

		if (blend)
			blend=free_dat(blend);

		/* --- Delete the log file if it is empty --- */

		if (stat(options->log_fn, &buf)==0 && buf.st_size==0)
			unlink(options->log_fn);
	}

	if (datlib_debug)
	{
		printf("%-16s: ", "DatUtil.main");
		printf("Freeing memory of options...\n");
	}

	FREE(options);

	return(errflg);
}
