/* --------------------------------------------------------------------------
 * ROMBChk - Written by Logiqx (http://www.logiqx.com/)
 *
 * Support script for ROMBuild
 * -------------------------------------------------------------------------- */

/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"
#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"


/* --- ROMBuild definitions and macros --- */

#include "rombuild/src/rombuild.h"


/* --- ROMBChk definitions and macros --- */

#include "rombchk.h"


/* --- The ROM manipulation definitions --- */

extern struct Emulator ems[];


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

	extern int optind;

	char c;
	int errflg=0;

	printf("===============================================================================\n");
	printf("ROMBChk - using ");
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Get the options specified on the command line --- */

	while ((c = getopt(argc, argv, "?")) != EOF)
	switch (c)
	{
		case '?':
			errflg++;   /* User wants help! */
	}

	/* --- The user must specify a dat files --- */

	if (argc-optind!=1)
		errflg++;

	/* --- Display the help page if required --- */

	if (errflg)
		printf("Usage: rombchk <mame dat>\n");

	/* --- Process the data file if there are no errors --- */

	if (!errflg)
		errflg=process_dat(argv[optind]);

	/* --- All done --- */

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Processing
 * -------------------------------------------------------------------------- */

int process_dat(char *fn)
{
	char base_fn[MAX_FILENAME_LENGTH+1];
	struct options *options=0;
	struct dat *dat=0;
	
	int i=0, j=0, k=0, found;
	int errflg=0;

	struct Rom *roms;
	struct game_idx *game_match;

	/* --- Allocate memory for user options --- */

	STRUCT_CALLOC(options, 1, sizeof(struct options))

	if (!errflg)
	{
		options->options=OPTION_LOAD_QUIETLY;
		options->fn=fn;
	}

	if ((dat=init_dat(options))==0)
	{
		fprintf(stderr, "Error trying to load %s\n", fn);
		errflg++;
	}

	if (!errflg)
	{
		printf("Validating MAME details in ROMBuild...\n");
		i=0;

		while(ems[i].descr)
		{
			roms=ems[i].roms;

			found=j=0;
			while (roms[j].local.game)
			{
				/* Check FULL_COPYs are sequential */
	
				/*if (roms[j].type==FULL_COPY && roms[j].local.offset>0 &&
					((roms[j-1].local.offset+roms[j-1].local.length!=roms[j].local.offset) ||
					(strcmp(roms[j-1].local.game, roms[j].local.game)) ||
					(strcmp(roms[j-1].local.rom, roms[j].local.rom))))
				{
					printf("BAD FULL COPY: %s %s\n", roms[j].local.game, roms[j].local.rom);
				}*/
	
				/* Check ODD_COPY/EVEN_COPYs are sequential */
	
				/*if ((roms[j].type==ODD_COPY || roms[j].type==EVEN_COPY) && roms[j].local.offset>0 &&
					((roms[j-1].local.offset+roms[j-1].local.length!=roms[j].local.offset) ||
					(strcmp(roms[j-1].local.game, roms[j].local.game)) ||
					(strcmp(roms[j-1].local.rom, roms[j].local.rom))))
				{
					printf("BAD ODD/EVEN COPY: %s %s\n", roms[j].local.game, roms[j].local.rom);
				}*/
	
				if (roms[j].type==BLOCK_FILL || !strcmp(roms[j].mame.game, "zzzzzzzz"))
				{	
					/* Ignore because it is a small ROM provided with ROMBuild */
				}
				else if ((game_match=bsearch((void *)roms[j].mame.game, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name)))
				{
					for (found=k=0; k<game_match->game->num_roms; k++)
					{
						if (!strcmp(roms[j].mame.rom, game_match->game->roms[k].name) && roms[j].mame.crc==game_match->game->roms[k].crc)
							found++;
					}
	
					if (!found)
					{
						printf("ROM not in MAME Dat: %s/%s (%ld bytes, %08lx)\n", roms[j].mame.game, roms[j].mame.rom, roms[j].mame.size, roms[j].mame.crc);
					}
				}
				else
				{
						printf("Game not in MAME Dat: %s\n", roms[j].mame.game);
				}
	
				j++;
			}
	
			i++;
		}
	}
	
	dat=free_dat(dat);

	i=0;
	while(!errflg && ems[i].descr)
	{
		for (j=0; j<strlen(ems[i].descr); j++)
		{
			if (ems[i].descr[j]==' ')
				ems[i].descr[j]='_';
		}

		printf("Validating %s details in ROMBuild...\n", ems[i].descr);
		sprintf(base_fn, "%s.dat", ems[i].descr);

		options->fn=base_fn;

		if ((dat=init_dat(options))==0)
		{
			fprintf(stderr, "Error trying to load %s\n", base_fn);
			errflg++;
		}

		roms=ems[i].roms;

		found=j=0;
		while (!errflg && roms[j].local.game)
		{
			if ((game_match=bsearch((void *)roms[j].local.game, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name)))
			{
				for (found=k=0; k<game_match->game->num_roms; k++)
				{
					if (!strcmp(roms[j].local.rom, game_match->game->roms[k].name) && roms[j].local.crc==game_match->game->roms[k].crc)
						found++;
				}
				if (!found)
					printf("ROM not in %s Dat: %s/%s (%ld bytes, %08lx)\n", ems[i].descr, roms[j].local.game, roms[j].local.rom, roms[j].local.size, roms[j].local.crc);
			}
			else
			{
				printf("Game not in %s Dat: %s\n", ems[i].descr, roms[j].local.game);
			}

			j++;
		}

		dat=free_dat(dat);

		i++;
	}

	FREE(options)

	printf("All done!\n");

	return(errflg);
}
