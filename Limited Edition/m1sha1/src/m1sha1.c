/* --------------------------------------------------------------------------
 * M1SHA1 - Written by Logiqx (http://www.logiqx.com/)
 *
 * Little tool that tries to find ZIP files that you need!
 * -------------------------------------------------------------------------- */

#define M1SHA1_VERSION "v1.0"
#define M1SHA1_DATE "4 September 2005"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"
#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"


/* --- M1SHA1 definitions and macros --- */

#include "m1sha1.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


/* --------------------------------------------------------------------------
 * The main() function
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	FILE *in=0, *out=0;
	char st[MAX_STRING_LENGTH];

	struct options *options=0;
	struct dat *reference=0;
	struct rom_idx *rom_idx;

	uint32_t crc;
	char *c;

	int errflg=0;

	printf("===============================================================================\n");
	printf("M1SHA1 %s (%s) - using ", M1SHA1_VERSION, M1SHA1_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Display the help page if required --- */

	if (argc<3)
	{
		printf("Usage: m1sha1 <m1.xml> <reference.dat>\n");
		errflg++;
	}

	/* --- Allocate memory for user options --- */

	STRUCT_CALLOC(options, 1, sizeof(struct options))

	if (!errflg)
	{
		options->options=OPTION_SHOW_SUMMARY|OPTION_EXTENDED_CHECKSUMS;
		options->fn=argv[2];
	}

	/* --- Load the 'reference' data file --- */

	if (!errflg && (reference=init_dat(options))==0)
		errflg++;

	if (!errflg)
		printf("\n");

	/* --- Process m1.xml --- */

	if (!errflg)
		FOPEN(in, argv[1], "r")

	if (!errflg)
	{
		sprintf(st, "%s.sha1", argv[1]);
		FOPEN(out, st, "w")
	}

	if (!errflg)
		printf("Processing %s...\n", argv[1]);

	while (!errflg && fgets(st, MAX_STRING_LENGTH, in))
	{
		if (strstr(st, "<rom") && strstr(st, "crc=\"") && !strstr(st, "sha1="))
		{
			crc=strtoul(strstr(st, "crc=\"")+5, NULL, 16);

			if ((rom_idx=bsearch((const void *)&crc, reference->rom_crc_idx, reference->num_roms, sizeof(struct rom_idx), find_rom_by_crc))!=0)
			{
				if (rom_idx->rom->sha1)
				{
					for (c=st; *c; c++)
					{
						if (!strncmp(c, "offset=\"", 8))
							fprintf(out, "sha1=\"%s\" ", rom_idx->rom->sha1);

						fprintf(out, "%c", *c);
					}
				}
				else
				{
					fprintf(out, "%s", st);
				}
			}
			else
			{
				fprintf(out, "%s", st);
			}
		}
		else
		{
			fprintf(out, "%s", st);
		}
	}

	if (!errflg)
		printf("\nAll done (saved as '%s.sha1').\n", argv[1]);

	FCLOSE(out)
	FCLOSE(in)

	/* --- Clean up --- */

	reference=free_dat(reference);

	FREE(options)

	return(errflg);
}

