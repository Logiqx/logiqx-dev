/* --------------------------------------------------------------------------
 * DatUtil - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for converting, cleansing and comparing ROM manager
 * dats (e.g. ClrMamePro, RomCenter).
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define DATUTIL_VERSION "v2.1"
#define DATUTIL_DATE "4 July 2004"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

	struct dat *dat=0;
	struct options *options=0;

	int errflg=0;

	/* --- Display version information --- */

	printf("===============================================================================\n");
	printf("DatUtil %s (%s) - using ", DATUTIL_VERSION, DATUTIL_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Allocate memory for user options --- */

	STRUCT_CALLOC(options, 1, sizeof(struct options))

	/* --- Get the options specified on the command line --- */

	while (!errflg && (c = getopt(argc, argv, "g:cro:a:f:lsxzvdA:V:C:R:F:M:Z:m")) != EOF)
	switch (c)
	{
		case 'g':
			options->options|=OPTION_GAME;
			options->game=optarg;
			break;
		case 'c':
			options->options|=OPTION_GAME_AND_CLONES;
			break;
		case 'r':
			options->options|=OPTION_REMOVE_CLONES;
			break;
		case 'o':
			options->save_name=optarg;
			options->save_mode="w";
			break;
		case 'a':
			options->save_name=optarg;
			options->save_mode="a";
			break;
		case 'f':
			LOWER(optarg);
			options->save_format=optarg;
			break;
		case 'l':
			options->options|=OPTION_LOWER_CASE;
			break;
		case 's':
			options->options|=OPTION_SORT_GAMES_BY_PARENT;
			break;
		case 'x':
			options->options|=OPTION_EXTENDED_CHECKSUMS;
			break;
		case 'z':
			options->options|=OPTION_IGNORE_FUNNY_SIZES;
			break;
		case 'v':
			options->options|=OPTION_VERBOSE_LOGGING;
			break;
		case 'd':
			options->options|=OPTION_SHOW_DEBUG_INFO;
			break;
		case 'A':
			options->clrmamepro.author=optarg;
			break;
		case 'V':
			options->clrmamepro.version=optarg;
			break;
		case 'C':
			options->clrmamepro.category=optarg;
			break;
		case 'R':
			options->clrmamepro.name=optarg;
			break;
		case 'F':
			options->clrmamepro.description=optarg;
			break;
		case 'M':
			options->clrmamepro.forcemerging=optarg;
			break;
		case 'Z':
			options->clrmamepro.forcezipping=optarg;
			break;
		case '?':
			errflg++;	/* User wants help! */
			break;

		/* --- Support original switches for backwards compatibility --- */

		case 'm':
			printf("Note: You no longer need to specify the -m option as it is now automatic!\n\n");
			break;
	}

	/* --- The user must specify either one or two dat files --- */

	if (argc-optind!=1)
		errflg++;

	/* --- Display the help page if required --- */

	if (errflg)
	{
		printf("Usage: datutil [-f <format>] [-o|a <outfile>] [-g <game> [-c]] [-s] [-r] [-l]\n");
		printf("               [-x] [-A <author>] [-V <version>] [-C <category>] [-R <refname>]\n");
		printf("               [-F <full name>] [-M <merging>] [-Z <zipping>] [-z] [-v] <dat>\n\n");
		printf("Converts a dat to a different format. The output format can be specified with\nthe -f option (e.g. listinfo, romcenter2 and titlelist).\n\n");
		printf("To specify the output filename use the -o option (or -a for append).\n\n");
		printf("Individual games can be converted using the -g option (using -c will also\nconvert the clones). If required, the -s option can be used to sort the games\nby their parent name and the -r option can be used to remove clones.\nThe -x option can be used to generate SHA1 and MD5 values when scanning ZIPs.\nUse -l to convert all names to lowercase and -z to ignore funny sizes!\n\n");
		printf("The -A, -V, -C, -R, -F, -M and -Z options are used to specify the data file\nheader fields.\n\n");
		printf("For a verbose log file (recommended), use the -v option.\n");
	}

	if (!errflg)
	{
		/* --- Always show a summary after loading --- */

		options->options|=OPTION_SHOW_SUMMARY;

		/* --- Initialise the dat --- */

		if (!errflg && (dat=init_dat(argv[optind], options->options, options->game, "datutil.log"))==0)
			errflg++;

		/* --- Set the ClrMamePro details in the dat --- */

		if (!errflg)
		{
			if (options->clrmamepro.name)
				dat->clrmamepro.name=options->clrmamepro.name;
			if (options->clrmamepro.description)
				dat->clrmamepro.description=options->clrmamepro.description;
			if (options->clrmamepro.category)
				dat->clrmamepro.category=options->clrmamepro.category;
			if (options->clrmamepro.version)
				dat->clrmamepro.version=options->clrmamepro.version;
			if (options->clrmamepro.author)
				dat->clrmamepro.author=options->clrmamepro.author;
			if (options->clrmamepro.forcemerging)
				dat->clrmamepro.forcemerging=options->clrmamepro.forcemerging;
			if (options->clrmamepro.forcezipping)
				dat->clrmamepro.forcezipping=options->clrmamepro.forcezipping;
		}

		/* --- If the user didn't specify an output name, use datutil.dat --- */

		if (!options->save_name)
			options->save_name="datutil.dat";

		/* --- If the user didn't specify an output mode, use overwrite --- */

		if (!(options->save_mode))
			options->save_mode="w";

		/* --- Save dat from memory --- */

		if (!errflg)
			errflg=save_dat(dat, options->save_name, options->save_mode, options->save_format);

		/* --- Release dat from memory --- */

		dat=free_dat(dat);
	}

	if (datlib_debug)
	{
		printf("%-16s: ", "DatUtil.main");
		printf("Freeing memory of options...\n");
	}

	FREE(options);

	return(errflg);
}
