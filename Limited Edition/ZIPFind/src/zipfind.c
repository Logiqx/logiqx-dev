/* --------------------------------------------------------------------------
 * ZIPFind - Written by Logiqx (http://www.logiqx.com/)
 *
 * Little tool that tries to find ZIP files that you need!
 * -------------------------------------------------------------------------- */

#define ZIPFIND_VERSION "v2.2"
#define ZIPFIND_DATE "22 July 2004"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"
#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"


/* --- ZIPFind definitions and macros --- */

#include "zipfind.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


/* --------------------------------------------------------------------------
 * The main() function
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	/* --- For getopt function --- */

	extern int optind;
	extern char *optarg;

	struct options *options=0;
	struct dat *missing=0, *ziplist=0;
	int verbose=0;
	char *url=0;

	char c;
	int errflg=0;

	printf("===============================================================================\n");
	printf("ZIPFind %s (%s) - using ", ZIPFIND_VERSION, ZIPFIND_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	while (!errflg && (c = getopt(argc, argv, "vu:?")) != EOF)
	switch (c)
	{
		case 'v':
			verbose++;
			break;
		case 'u':
			url=optarg;
			break;
		case '?':
			errflg++;	/* User wants help! */
	}

	/* --- Display the help page if required --- */

	if (argc-optind<2)
	{
		printf("Usage: zipfind [-v] [-u <url>] <missing.dat> <ziplist.txt>\n");
		errflg++;
	}

	/* --- Allocate memory for user options --- */

	STRUCT_CALLOC(options, 1, sizeof(struct options))

	if (!errflg)
	{
		options->options=OPTION_SHOW_SUMMARY;
		options->fn=argv[optind];
	}

	/* --- Load the 'missing' data file --- */

	if (!errflg && (missing=init_dat(options))==0)
		errflg++;

	if (!errflg)
	{
		printf("\n");
		options->fn=argv[optind+1];
	}

	/* --- Load the 'ziplist' data file --- */

	if (!errflg && (ziplist=init_dat(options))==0)
		errflg++;

	if (!errflg)
		printf("\n");

	/* --- Generate reports --- */

	if (!errflg)
		errflg=game_report(missing, ziplist, verbose);

	if (!errflg)
		errflg=zip_report(missing, ziplist, verbose);

	if (!errflg)
		errflg=url_report(ziplist, url);

	/* --- Clean up --- */

	ziplist=free_dat(ziplist);
	missing=free_dat(missing);

	FREE(options)

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Game Report
 * -------------------------------------------------------------------------- */

int game_report(struct dat *missing, struct dat *ziplist, int verbose)
{
	struct rom_idx *rom_match_idx;

	int i, j, k, l;
	int num_found, num_useful;
	long bytes_found, bytes_useful;
	double usefulness, completeness, score;

	FILE *out=0;

	int errflg=0;

	FOPEN(out, "zf_games.log", "w")

	for (i=0; !errflg && i<missing->num_games; i++)
	{
		for (j=0; j<missing->games[i].num_roms; j++)
		{
			/* --- Search for matching CRCs in ziplist --- */

			rom_match_idx=bsearch((const void *)&missing->games[i].roms[j].crc, ziplist->rom_crc_idx, ziplist->num_roms, sizeof(struct rom_idx), find_rom_by_crc);

			if (rom_match_idx)
			{
				while (rom_match_idx>ziplist->rom_crc_idx && rom_match_idx->rom->crc==(rom_match_idx-1)->rom->crc)
					rom_match_idx--;

				while (rom_match_idx<ziplist->rom_crc_idx+ziplist->num_roms && rom_match_idx->rom->crc==missing->games[i].roms[j].crc)
				{
					missing->games[i].match++;
					missing->games[i].roms[j].match++;
					rom_match_idx->rom->game->match++;
					rom_match_idx++;
				}
			}

			/* --- Search for matching ~CRCs in ziplist --- */

			rom_match_idx=bsearch((const void *)&missing->games[i].roms[j].crc, ziplist->rom_crc_idx, ziplist->num_roms, sizeof(struct rom_idx), find_rom_by_comp_crc);

			if (rom_match_idx)
			{
				while (rom_match_idx>ziplist->rom_crc_idx && rom_match_idx->rom->crc==(rom_match_idx-1)->rom->crc)
					rom_match_idx--;

				while (rom_match_idx<ziplist->rom_crc_idx+ziplist->num_roms && rom_match_idx->rom->crc==~missing->games[i].roms[j].crc)
				{
					missing->games[i].match++;
					missing->games[i].roms[j].match++;
					rom_match_idx->rom->game->match++;
					rom_match_idx++;
				}
			}
		}

		/* --- If some ROMs were found in the ziplist then print game info --- */

		if (missing->games[i].match)
		{
			/* --- Count up totals for ROMs found --- */

			num_found=bytes_found=0;

			for (j=0; j<missing->games[i].num_roms; j++)
			{
				if (missing->games[i].roms[j].match)
				{
					num_found++;
					bytes_found+=missing->games[i].roms[j].size;
				}
			}

			/* --- Report totals for ROMs found --- */

			fprintf(out, "Game          : %s\n", missing->games[i].name);
			if (missing->games[i].description)
				fprintf(out, "Description   : %s\n", missing->games[i].description);
			fprintf(out, "Total Needed  : %d ROMs, %ld bytes\n", missing->games[i].num_roms, (unsigned long)missing->games[i].size);
			fprintf(out, "Total Found   : %d/%d ROMs, %ld/%ld bytes (%.2f%%)\n\n", num_found, missing->games[i].num_roms, bytes_found, (unsigned long)missing->games[i].size, (float)100*bytes_found/missing->games[i].size);

			/* --- Report details of ROMs found (verbose mode) --- */

			if (verbose)
			{
				fprintf(out, "Contents      : ");
				for (j=0; j<missing->games[i].num_roms; j++)
				{
					if (j>0)
						fprintf(out, "                ");

					if (missing->games[i].roms[j].match==1)
						fprintf(out, "%s, %ld bytes, crc %08lx, (1 match)\n",
							missing->games[i].roms[j].name, (unsigned long)missing->games[i].roms[j].size,
							(unsigned long)missing->games[i].roms[j].crc); 
					else
						fprintf(out, "%s, %ld bytes, crc %08lx, (%d matches)\n",
							missing->games[i].roms[j].name, (unsigned long)missing->games[i].roms[j].size,
							(unsigned long)missing->games[i].roms[j].crc, missing->games[i].roms[j].match); 
				}
				fprintf(out, "\n");
			}

			/* --- Report ZIPs that were found --- */

			for (j=0; j<ziplist->num_games; j++)
			{
				if (ziplist->games[j].match)
				{
					/* --- Initialise counts for missing ROMs --- */

					for (k=0; k<missing->games[i].num_roms; k++)
						missing->games[i].roms[k].match=0;

					/* --- Check which CRCs and ~CRCs are available in the ZIP --- */

					for (k=0; k<ziplist->games[j].num_roms; k++)
					{
						for (l=0; l<missing->games[i].num_roms; l++)
						{
							if (missing->games[i].roms[l].crc==ziplist->games[j].roms[k].crc ||
								missing->games[i].roms[l].crc==~ziplist->games[j].roms[k].crc)
							{
								ziplist->games[j].roms[k].match++;
								missing->games[i].roms[l].match++;
							}
						}
					}

					/* --- Count up totals found in ZIP --- */

					num_found=bytes_found=0;

					for (k=0; k<missing->games[i].num_roms; k++)
					{
						if (missing->games[i].roms[k].match)
						{
							num_found++;
							bytes_found+=missing->games[i].roms[k].size;
						}
					}

					/* --- Calculate usefulness of ZIP --- */

					num_useful=bytes_useful=0;

					for (k=0; k<ziplist->games[j].num_roms; k++)
					{
						if (ziplist->games[j].roms[k].match)
						{
							num_useful++;
							bytes_useful+=ziplist->games[j].roms[k].size;
						}
					}

					/* --- Calculate scores and print summary for the ZIP ---  */

					usefulness=(float)bytes_useful/ziplist->games[j].size;
					completeness=(float)bytes_found/missing->games[i].size;
					score=usefulness*completeness;

					fprintf(out, "        File          : %s/%s\n", ziplist->games[j].rebuildto, ziplist->games[j].name);
					fprintf(out, "        Contents      : %d ROMs, %ld bytes\n", ziplist->games[j].num_roms, (unsigned long)ziplist->games[j].size);
					fprintf(out, "        Usefulness    : %d/%d ROMs, %ld/%ld bytes (%.2f%%)\n", num_useful, ziplist->games[j].num_roms, bytes_useful, (unsigned long)ziplist->games[j].size, 100*usefulness);
					fprintf(out, "        Completeness  : %d/%d ROMs, %ld/%ld bytes (%.2f%%)\n", num_found, missing->games[i].num_roms, bytes_found, (unsigned long)missing->games[i].size, 100*completeness);
					fprintf(out, "        Score         : %.2f%%\n\n", 100*score);

					/* --- Report contents of the ZIP (verbose mode) --- */

					if (verbose)
					{
						fprintf(out, "        Contents      : ");
						for (k=0; k<ziplist->games[j].num_roms; k++)
						{
							if (k>0)
								fprintf(out, "                        ");
		
							if (ziplist->games[j].roms[k].match==1)
								fprintf(out, "%s, %ld bytes, crc %08lx, (1 match)\n",
									ziplist->games[j].roms[k].name, (unsigned long)ziplist->games[j].roms[k].size,
									(unsigned long)ziplist->games[j].roms[k].crc); 
							else
								fprintf(out, "%s, %ld bytes, crc %08lx, (%d matches)\n",
									ziplist->games[j].roms[k].name, (unsigned long)ziplist->games[j].roms[k].size,
									(unsigned long)ziplist->games[j].roms[k].crc, ziplist->games[j].roms[k].match); 
						}
						fprintf(out, "\n");
					}

					/* --- Remember the ZIPs score but blank the match fields ---  */

					ziplist->games[j].score+=score;
					ziplist->games[j].match=0;

					for (k=0; k<ziplist->games[j].num_roms; k++)
						ziplist->games[j].roms[k].match=0;
				}
			}
		}
	}

	/* --- Sort the ziplist based on their scores --- */

	for (i=0; i<ziplist->num_games; i++)
		ziplist->game_score_idx[i].game=&ziplist->games[i];
	
	qsort(ziplist->game_score_idx, ziplist->num_games, sizeof(struct game_idx), game_score_idx_sort_function);

	/* --- Close the log and end the function --- */

	FCLOSE(out)

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Zip Report
 * -------------------------------------------------------------------------- */

int zip_report(struct dat *missing, struct dat *ziplist, int verbose)
{
	struct rom_idx *rom_match_idx;

	int i, j, k, l;
	int num_found, num_useful;
	long bytes_found, bytes_useful;
	double completeness;

	FILE *out=0;

	int errflg=0;

	FOPEN(out, "zf_zips.log", "w")

	/* --- Blank counts in the missing data file --- */

	for (i=0; !errflg && i<missing->num_games; i++)
	{
		missing->games[i].match=0;

		for (j=0; j<missing->games[i].num_roms; j++)
			missing->games[i].roms[j].match=0;
	}

	for (i=0; !errflg && i<ziplist->num_games; i++)
	{
		if (ziplist->game_score_idx[i].game->score)
		{
			for (j=0; j<ziplist->game_score_idx[i].game->num_roms; j++)
			{
				/* --- Search for matching CRCs in missing --- */

				rom_match_idx=bsearch((const void *)&ziplist->game_score_idx[i].game->roms[j].crc, missing->rom_crc_idx, missing->num_roms, sizeof(struct rom_idx), find_rom_by_crc);

				if (rom_match_idx)
				{
					while (rom_match_idx>missing->rom_crc_idx && rom_match_idx->rom->crc==(rom_match_idx-1)->rom->crc)
						rom_match_idx--;

					while (rom_match_idx<missing->rom_crc_idx+missing->num_roms && rom_match_idx->rom->crc == ziplist->game_score_idx[i].game->roms[j].crc)
					{
						ziplist->game_score_idx[i].game->match++;
						ziplist->game_score_idx[i].game->roms[j].match++;
						rom_match_idx->rom->game->match++;
						rom_match_idx++;
					}
				}

				/* --- Search for matching ~CRCs in missing --- */

				rom_match_idx=bsearch((const void *)&ziplist->game_score_idx[i].game->roms[j].crc, missing->rom_crc_idx, missing->num_roms, sizeof(struct rom_idx), find_rom_by_comp_crc);

				if (rom_match_idx)
				{
					while (rom_match_idx>missing->rom_crc_idx && rom_match_idx->rom->crc==(rom_match_idx-1)->rom->crc)
						rom_match_idx--;

					while (rom_match_idx<missing->rom_crc_idx+missing->num_roms && rom_match_idx->rom->crc == ~ziplist->game_score_idx[i].game->roms[j].crc)
					{
						ziplist->game_score_idx[i].game->match++;
						ziplist->game_score_idx[i].game->roms[j].match++;
						rom_match_idx->rom->game->match++;
						rom_match_idx++;
					}
				}
			}

			/* --- If some ROMs were found in the missing dat then print game info --- */

			if (ziplist->game_score_idx[i].game->match)
			{
				/* --- Count up totals for ROMs found --- */

				num_useful=bytes_useful=0;

				for (j=0; j<ziplist->game_score_idx[i].game->num_roms; j++)
				{
					if (ziplist->game_score_idx[i].game->roms[j].match)
					{
						num_useful++;
						bytes_useful+=ziplist->game_score_idx[i].game->roms[j].size;
					}
				}

				/* --- Report totals for files found --- */

				fprintf(out, "File          : %s/%s\n", ziplist->game_score_idx[i].game->rebuildto, ziplist->game_score_idx[i].game->name);
				fprintf(out, "Contents      : %d files, %ld bytes\n", ziplist->game_score_idx[i].game->num_roms, (unsigned long)ziplist->game_score_idx[i].game->size);
				fprintf(out, "Usefulness    : %d/%d ROMs, %ld/%ld bytes (%.2f%%)\n", num_useful, ziplist->game_score_idx[i].game->num_roms, bytes_useful, (unsigned long)ziplist->game_score_idx[i].game->size, (float)100*bytes_useful/ziplist->game_score_idx[i].game->size);
				fprintf(out, "Total Score   : %.2f%%\n\n", 100*ziplist->game_score_idx[i].game->score);

				/* --- Report details of files that are useful (verbose mode) --- */

				if (verbose)
				{
					fprintf(out, "Contents      : ");
					for (j=0; j<ziplist->game_score_idx[i].game->num_roms; j++)
					{
						if (j>0)
							fprintf(out, "                ");

						if (ziplist->game_score_idx[i].game->roms[j].match==1)
							fprintf(out, "%s, %ld bytes, crc %08lx, (1 match)\n",
								ziplist->game_score_idx[i].game->roms[j].name, (unsigned long)ziplist->game_score_idx[i].game->roms[j].size,
								(unsigned long)ziplist->game_score_idx[i].game->roms[j].crc); 
						else
							fprintf(out, "%s, %ld bytes, crc %08lx, (%d matches)\n",
								ziplist->game_score_idx[i].game->roms[j].name, (unsigned long)ziplist->game_score_idx[i].game->roms[j].size,
								(unsigned long)ziplist->game_score_idx[i].game->roms[j].crc, ziplist->game_score_idx[i].game->roms[j].match); 
					}
					fprintf(out, "\n");
				}

				/* --- Report files that were found --- */

				for (j=0; j<missing->num_games; j++)
				{
					if (missing->games[j].match)
					{
						/* --- Initialise counts for ziplist ROMs --- */

						for (k=0; k<ziplist->game_score_idx[i].game->num_roms; k++)
							ziplist->game_score_idx[i].game->roms[k].match=0;

						/* --- Check which CRCs and ~CRCs are available in the ZIP --- */

						for (k=0; k<missing->games[j].num_roms; k++)
						{
							for (l=0; l<ziplist->game_score_idx[i].game->num_roms; l++)
							{
								if (ziplist->game_score_idx[i].game->roms[l].crc==missing->games[j].roms[k].crc ||
									ziplist->game_score_idx[i].game->roms[l].crc==~missing->games[j].roms[k].crc)
								{
									missing->games[j].roms[k].match++;
									ziplist->game_score_idx[i].game->roms[l].match++;
								}
							}
						}

						/* --- Calculate usefulness of ZIP --- */
	
						num_found=bytes_found=0;
	
						for (k=0; k<missing->games[j].num_roms; k++)
						{
							if (missing->games[j].roms[k].match)
							{
								num_found++;
								bytes_found+=missing->games[j].roms[k].size;
							}
						}

						/* --- Calculate completeness and print summary for the ZIP ---  */

						completeness=(float)bytes_found/missing->games[j].size;

						fprintf(out, "        Game          : %s\n", missing->games[j].name);
						if (missing->games[j].description)
							fprintf(out, "        Description   : %s\n", missing->games[j].description);
						fprintf(out, "        Total Needed  : %d ROMs, %ld bytes\n", missing->games[j].num_roms, (unsigned long)missing->games[j].size);
						fprintf(out, "        Completeness  : %d/%d ROMs, %ld/%ld bytes (%.2f%%)\n\n", num_found, missing->games[j].num_roms, bytes_found, (unsigned long)missing->games[j].size, (float)100*completeness);

						/* --- Report contents of the ZIP (verbose mode) --- */

						if (verbose)
						{
							fprintf(out, "        Contents      : ");
							for (k=0; k<missing->games[j].num_roms; k++)
							{
								if (k>0)
									fprintf(out, "                        ");
			
								if (missing->games[j].roms[k].match==1)
									fprintf(out, "%s, %ld bytes, crc %08lx, (1 match)\n",
										missing->games[j].roms[k].name, (unsigned long)missing->games[j].roms[k].size,
										(unsigned long)missing->games[j].roms[k].crc); 
								else
									fprintf(out, "%s, %ld bytes, crc %08lx, (%d matches)\n",
										missing->games[j].roms[k].name, (unsigned long)missing->games[j].roms[k].size,
										(unsigned long)missing->games[j].roms[k].crc, missing->games[j].roms[k].match); 
							}
							fprintf(out, "\n");
						}

						/* --- Blank the match fields ---  */

						missing->games[j].match=0;

						for (k=0; k<missing->games[j].num_roms; k++)
							missing->games[j].roms[k].match=0;
					}
				}
			}
		}
	}

	/* --- Close the log and end the function --- */

	FCLOSE(out)

	return(errflg);
}

/* --------------------------------------------------------------------------
 * URL Report
 * -------------------------------------------------------------------------- */

int url_report(struct dat *ziplist, char *url)
{
	FILE *out=0;
	int i, count=0;
	int errflg=0;

	FOPEN(out, "zf_fetch.log", "w")

	if (!errflg)
	{
		for (i=0; i<ziplist->num_games; i++)
		{
			if (ziplist->game_score_idx[i].game->score)
			{
				if (url)
					fprintf(out, "%s", url);
				fprintf(out, "%s/%s\n", ziplist->game_score_idx[i].game->rebuildto, ziplist->game_score_idx[i].game->name);
				count++;
			}
		}

		switch (count)
		{
			case 0:
				printf("No ZIPs found!\n");
				break;
			case 1:
				printf("1 ZIP identified for download - see zf_fetch.log\n");
				break;
			default:
				printf("%d ZIPs identified for download - see zf_fetch.log\n", count);
				break;
		}
	}

	FCLOSE(out)

	return(errflg);
}
