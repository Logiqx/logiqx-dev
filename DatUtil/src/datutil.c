/* --------------------------------------------------------------------------
 * DatUtil - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for converting, cleansing and comparing ROM manager
 * dats (e.g. ClrMamePro, RomCenter).
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define DATUTIL_VERSION "v2.2"
#define DATUTIL_DATE "Private Beta"


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

	struct dat *dat=0, *info=0;
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

	while (!errflg && (c = getopt(argc, argv, "g:cro:a:f:lsxmi:zyvdA:V:C:R:F:M:Z:")) != EOF)
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
		case 'm':
			options->options|=OPTION_MD5_CHECKSUMS;
			break;
		case 'i':
			options->fn=optarg;
			break;
		case 'z':
			options->options|=OPTION_IGNORE_FUNNY_SIZES;
			break;
		case 'y':
			options->options|=OPTION_IGNORE_MISSING_YEARS;
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
	}

	/* --- The user must specify either one or two dat files --- */

	if (argc-optind!=1)
		errflg++;

	/* --- Display the help page if required --- */

	if (errflg)
	{
		printf("Usage: datutil [-f <format>] [-o|a <outfile>] [-g <game> [-c]] [-s] [-r] [-l]\n");
		printf("  [-x] [-m] [-i <info>] [-z] [-y] [-A <author>] [-V <version>] [-C <category>]\n");
		printf("  [-R <refname>] [-F <fullname>] [-M <merging>] [-Z <zipping>] [-v] <infile>\n\n");
		printf("Converts a dat to a different format. The output format can be specified with\nthe -f option (e.g. listinfo, romcenter2 and titlelist).\n");
		printf("To specify the output filename use the -o option (or -a for append).\n\n");
		printf("Individual games can be converted using the -g option (using -c will also\nconvert the clones). If required, the -s option can be used to sort the games\nby their parent name and the -r option can be used to remove clones. Use -l\nto convert all names to lowercase. The -x option can be used to generate SHA1\nor MD5 values when scanning ZIPs. To use MD5 rather than SHA1 (the default),\nspecify the -m option. The -i option will take missing info from another dat.\nThe -z and -y options are used to ignore funny sizes and missing years.\nFor a verbose log file (recommended), use the -v option.\n\n");
		printf("The -A, -V, -C, -R, -F, -M and -Z options are used to specify the data file\nheader fields.\n");
	}

	if (!errflg)
	{
		/* --- Always show a summary after loading --- */

		options->options|=OPTION_SHOW_SUMMARY;

		/* --- If using an 'info' dat, load it into memory --- */

		if (options->fn)
		{
			if ((info=init_dat(options))==0)
				errflg++;
			else
			{
				printf("\n");
				options->info=info;
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
			errflg=save_dat(dat);

		/* --- Release dat(s) from memory --- */

		dat=free_dat(dat);

		if (info)
			info=free_dat(info);
	}

	if (datlib_debug)
	{
		printf("%-16s: ", "DatUtil.main");
		printf("Freeing memory of options...\n");
	}

	FREE(options);

	return(errflg);
}
