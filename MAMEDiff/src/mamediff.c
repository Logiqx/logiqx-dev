/* --------------------------------------------------------------------------
 * MAMEDiff - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for comparing different versions of MAME to identify
 * changes required to your ROM sets.
 * -------------------------------------------------------------------------- */

#define MAMEDIFF_VERSION "v2.13"
#define MAMEDIFF_DATE "16 January 2005"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"


/* --- MAMEDiff definitions and macros --- */

#include "mamediff.h"
#include "compare.h"
#include "generate.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


/* --------------------------------------------------------------------------
 * The main() function just works out what the user wants to do then calls the
 * appropriate function.
 *
 * Uses the getopt() function from unistd to interpret command line options.
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	/* --- For getopt function --- */

	extern char *optarg;
	extern int optind;
	char c;

	int verbose=0, caesar=0, set_type=0, diff_type=0, renames=0, zeros=0, bios=0, object_type=OPTION_OBJECT_TYPE_ROM;

	struct options *options=0;
	struct dat *dat1=0, *dat2=0;

	int old_syntax=0, errflg=0;

	/* --- Display version information --- */

	printf("===============================================================================\n");
	printf("MAMEDiff %s (%s) - using ", MAMEDIFF_VERSION, MAMEDIFF_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Get the options specified on the command line --- */

	while ((c = getopt(argc, argv, "vcmsnd:rzbo:?MSNtT")) != EOF)
	switch (c)
	{
		case 'v':
			verbose++;
			break;
		case 'c':
			caesar++;
			break;
		case 'm':
			errflg+=set_type;
			set_type=OPTION_DAT_FULL_MERGING;
			break;
		case 's':
			errflg+=set_type;
			set_type=OPTION_DAT_SPLIT_MERGING;
			break;
		case 'n':
			errflg+=set_type;
			set_type=OPTION_DAT_NO_MERGING;
			break;
		case 'd':
			diff_type=atoi(optarg);
			break;
		case 'r':
			renames++;
			break;
		case 'b':
			bios++;
			break;
		case 'z':
			zeros++;
			break;
		case 'o':
			if (!strcmp(optarg, "sample"))
				object_type=OPTION_OBJECT_TYPE_SAMPLE;
			else if (!strcmp(optarg, "disk"))
				object_type=OPTION_OBJECT_TYPE_DISK;
			else
				errflg++;
			break;
		case '?':
			errflg++;   /* User wants help! */
			break;

		/* --- Support original switches for backwards compatibility --- */

		case 'M':
			errflg+=set_type;
			set_type=OPTION_DAT_FULL_MERGING;

			if (diff_type==0)
			{
				diff_type=1;
				renames++;
				zeros++;
			}
			old_syntax++;
			break;
		case 'S':
			errflg+=set_type;
			set_type=OPTION_DAT_SPLIT_MERGING;

			if (diff_type==0)
			{
				diff_type=1;
				renames++;
				zeros++;
			}
			old_syntax++;
			break;
		case 'N':
			errflg+=set_type;
			set_type=OPTION_DAT_NO_MERGING;

			if (diff_type==0)
			{
				diff_type=1;
				zeros++;
				renames++;
			}
			old_syntax++;
			break;
		case 't':
			diff_type=3;
			zeros++;
			renames++;
			old_syntax++;
			break;
		case 'T':
			diff_type=3;
			zeros++;
			renames=0;
			old_syntax++;
			break;
	}

	/* --- The user must specify either one or two dat files --- */

	if (argc-optind!=2)
		errflg++;

	/* --- Display the help page if required --- */

	if (old_syntax)
	{
		printf("Important: You are using the old command syntax, please read the documentation!\n\n");
		printf("Your syntax has been interpreted as ");

		if (set_type==OPTION_DAT_FULL_MERGING)
			printf("-m ");
		else if (set_type==OPTION_DAT_SPLIT_MERGING)
			printf("-s ");
		else if (set_type==OPTION_DAT_NO_MERGING)
			printf("-n ");

		printf("-d%d ", diff_type);

		if (renames)
			printf("-r ");

		if (zeros)
			printf("-z ");

		if (bios)
			printf("-b ");

		printf("instead.\n\n");
	}

	if (errflg)
	{
		printf("Usage: mamediff [-v] | [[-m|-s|-n] [-d[1|2|3] -o[disk|sample] [-r] [-z] [-b]]]\n       <old data file> <new data file 2>\n\n");
		printf("Running MAMEDiff without specifying a type of ROM set will produce a summary of\nchanges made to the ROM sets of individual games. If you specify a type of ROM\nset, MAMEDiff will tell you which ZIP files need rebuilding (if you have them).\n\n");
		printf("The three ROM set types are 'm'erged, 's'plit or 'n'on-merged.\n\n");
		printf("Use verbose mode (the -v option) for a detailed report of ROM changes.\n\n");
		printf("Use -d to generate data files containing ROM changes. When using -d, the -r\noption will consider ROM renames and -z will include zero CRCs (no dumps).\nThe -b option is for use if you like to have non-seperated BIOS ROMs.\n");
		exit (1);
	}

	/* --- Allocate memory for user options --- */

	STRUCT_CALLOC(options, 1, sizeof(struct options))

	if (!errflg)
	{
		options->options=set_type|object_type|OPTION_SHOW_SUMMARY;

		if (bios)
			options->options|=OPTION_NON_SEPERATED_BIOS_ROMS;

		if (zeros)
			options->options|=OPTION_INCLUDE_NODUMPS_IN_ZIPS;

		options->fn=argv[optind];
	}

	/* --- Load the data files --- */

	if (!errflg && (dat1=init_dat(options))==0)
		errflg++;

	if (!errflg)
	{
		printf("\n");
		options->fn=argv[optind+1];
	}

	if (!errflg && (dat2=init_dat(options))==0)
		errflg++;

	if (!errflg)
		printf("\n");

	/* --- Run the comparison --- */

	if (!errflg)
	{
		if (diff_type==0)
			errflg=standard_compare(dat1, dat2, verbose, caesar, set_type);
		else
			errflg=generate_changes(dat1, dat2, diff_type, renames, zeros, object_type);
	}

	/* --- Free memory --- */

	free_dat(dat2);
	free_dat(dat1);

	FREE(options)

	/* --- All done --- */

	return(errflg);
}
