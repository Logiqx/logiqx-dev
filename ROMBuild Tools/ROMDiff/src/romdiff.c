/* --------------------------------------------------------------------------
 * ROMDiff - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for re-building ROMs
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define ROMDIFF_VERSION "v2.0"
#define ROMDIFF_DATE "30 June 2004"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>


/* --- Dat library includes --- */

#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"


/* --- ZipIdent definitions and macros --- */

#include "romdiff.h"


/* --- Is DatLib debugging enabled? --- */

int datlib_debug=0;


/* --------------------------------------------------------------------------
 * The main() function just works out what the user wants to do then calls the
 * appropriate function.
 *
 * Uses the getopt() function from unistd to interpret command line options.
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	/* --- For getopt function --- */

	extern int optind;

	char c;
	int errflg=0;

	printf("===============================================================================\n");
	printf("ROMDiff %s (%s)\n", ROMDIFF_VERSION, ROMDIFF_DATE);
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Get the options specified on the command line --- */

	while ((c = getopt(argc, argv, "?")) != EOF)
	switch (c)
	{
		case '?':
			errflg++;   /* User wants help! */
	}

	/* --- Display the help page if required --- */

	if (errflg)
	{
		printf("Usage: %s [file1] [file2]\n\n", argv[0]);
		printf("Using the -l option will list supported emulators/games/roms.\n");
	}

	if (!errflg && argc-optind!=2)
	{
		printf("You must specify two files!\n");
		errflg++;
	}

	/* --- Do the business --- */

	if (!errflg)
		errflg=compare(argv[optind], argv[optind+1]);

	/* --- All done --- */

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Processing of 'roms_in' directory
 * -------------------------------------------------------------------------- */

int compare(char *fn1, char *fn2)
{
	long i=0, j;
	int min=-1, max=-1;
	int count=0, errflg=0;
	
	FILE *file1=0, *file2=0;

	unsigned char buf1[1024], buf2[1024];

	FOPEN(file1, fn1, "rb")

	if (!errflg)
		FOPEN(file2, fn2, "rb")

	while(!errflg && fread(buf1, 1, 1024, file1))
	{
		fread(buf2, 1, 1024, file2);
		for(j=0; j<1024; j++)
		{
			if (buf1[j]!=buf2[j])
			{
				printf("\t{0x%08lx, 0x%02x},\n", i+j, buf1[j]);

				if (min==-1)
					min=i+j;
				max=i+j;
				count++;
			}
		}
		i+=1024;
	}

	if (!errflg)
		printf("Min=%d, max=%d, span=%d, count=%d\n", min, max, max-min+1, count);

	FCLOSE(file2)
	FCLOSE(file1)

	return(errflg);
}

