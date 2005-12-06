/* --------------------------------------------------------------------------
 * ROMInfo - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for identifying emulators that use a specified ROM
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define ROMINFO_VERSION "v2.6"
#define ROMINFO_DATE "6 December 2005"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <zlib.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"
#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"
#include "datlib/src/mame/unzip.h"


/* --- ROMInfo definitions and macros --- */

#include "rominfo.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


int main(int argc, char **argv)
{
	struct ini_entry *ini=0;
	struct crc *crcs=0;
	char dir[MAX_FILENAME_LENGTH+1];
	int errflg=0;

	printf("===============================================================================\n");
	printf("ROMInfo %s (%s) - using ", ROMINFO_VERSION, ROMINFO_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	if (argc<2)
	{
		printf("Usage: rominfo [crcs] [files] [zips]\n\n");
		printf("Don't forget to set up your paths in rominfo.ini\n");
		errflg++;
	}

	if (strchr(argv[0], '/'))
	{
		strcpy(dir, argv[0]);
		*strrchr(dir, '/')='\0';
		chdir(dir);
	}

	/* --- Read INI options --- */

	if (!errflg && !(ini=load_ini("rominfo.ini")))
		errflg++;

	if (!errflg)
	{
		if ((crcs=load_crcs(argc, argv)))
		{
			if (crcs[0].crc)
				errflg=scan_dirs(ini, crcs);
			else
				printf("Give me something to search for!\n");

			crcs=free_crcs(crcs);
		}
	}

	ini=free_ini(ini);

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Read CRCs from ZIP file
 * -------------------------------------------------------------------------- */

struct crc *load_crcs(int argc, char **argv)
{
	ZIP *zip;
	struct zipent *zipent;
	struct stat buf;

	char *mem;

	struct crc *crcs=0;
	int num_crcs=0;
	int errflg=0;
	int i;

	STRUCT_CALLOC(crcs, MAX_ZIP_ENTRIES+1, sizeof(struct crc))

	for (i=1; !errflg && i<argc; i++)
	{
		if (stat(argv[i], &buf) == 0)
		{
			if (!strstr(argv[i], ".zip"))
			{
				if (buf.st_mode & S_IFDIR)
				{
					printf("Ignoring %s (directory)\n\n",argv[i]);
				}
				else
				{
					/* --- Treat as a File --- */
					if (num_crcs<MAX_ZIP_ENTRIES)
					{
						crcs[num_crcs].fn=argv[i];
						crcs[num_crcs].crc=crc32(0, NULL, 0);

						if (buf.st_size && buf.st_size<=MAX_ROM_SIZE)
						{
							BYTE_MALLOC(mem, (int)buf.st_size)
							BYTE_READ(mem, (int)buf.st_size, argv[i]);

							if (!errflg)
								crcs[num_crcs].crc=crc32(crcs[num_crcs].crc, mem, buf.st_size);

							FREE(mem);
						}
						num_crcs++;
					}
					else
					{
						printf("Too many files specified - max=%d\n", MAX_ZIP_ENTRIES);
						errflg++;
					}
				}
			}
			else
			{
				/* --- Treat as a ZIP --- */
				if ((zip=openzip(argv[i])))
				{
					while ((!errflg) && (zipent=readzip(zip)))
					{
						if (num_crcs<MAX_ZIP_ENTRIES)
						{
							crcs[num_crcs].fn=argv[i];
							crcs[num_crcs++].crc=zipent->crc32;
						}
						else
						{
							printf("Too many files in ZIP - max=%d\n", MAX_ZIP_ENTRIES);
							errflg++;
						}
					}
			
					closezip(zip);
				}
			}
		}
		else
		{ 
			/* --- Treat as a CRC --- */
			if (num_crcs<MAX_ZIP_ENTRIES)
			{
				crcs[num_crcs++].crc=strtoul(argv[i], NULL, 16);
			}
			else
			{
				printf("Too many CRCs specified - max=%d\n", MAX_ZIP_ENTRIES);
				errflg++;
			}
		}
	}

	return(crcs);
}

struct crc *free_crcs(struct crc *crcs)
{
	FREE(crcs)

	return(crcs);
}

/* --------------------------------------------------------------------------
 * Scan all directories specified in INI
 * -------------------------------------------------------------------------- */

int scan_dirs(struct ini_entry *ini, struct crc *crcs)
{
	FILE *out;

	char dir_num[8];
	char dir_name[MAX_FILENAME_LENGTH+1];

	int i=1, done=0;
	int errflg;

	FOPEN(out, "rominfo.log", "w")

	if (out)
	{
		fprintf(out, "===============================================================================\n");
		fprintf(out, "ROMInfo %s (%s)\n", ROMINFO_VERSION, ROMINFO_DATE);
		fprintf(out, "Written by Logiqx (http://www.logiqx.com/)\n");
		fprintf(out, "===============================================================================\n");
	}

	while (!done)
	{
		sprintf(dir_num, "Dir%d", i);

		if (find_ini_value(ini, "Directories", dir_num))
		{
			strcpy(dir_name, find_ini_value(ini, "Directories", dir_num));
			scan_dir(out, dir_name, crcs);
		}
		else
		{
			done++;
		}

		i++;
	}

	FCLOSE(out)

	return(0);
}

/* --------------------------------------------------------------------------
 * Inidividual Directory scan
 * -------------------------------------------------------------------------- */

int scan_dir(FILE *out, char *dir, struct crc *crcs)
{
	DIR *dirp;                                    
	struct dirent *direntp;                       
	struct stat buf;
	int count=0;

	char fn[MAX_FILENAME_LENGTH+1];

	if (!(dirp=opendir(dir)))
	{
		printf("Error: unable to read %s\n", dir);
	}

	while (dirp && ((direntp = readdir(dirp)) != NULL))
	{
		sprintf(fn, "%s\\%s", dir, direntp->d_name);

		if (stat(fn, &buf) == 0)
		{
			if (!(buf.st_mode & S_IFDIR))
			{
				if (strstr(fn, ".dat"))
				{
					scan_dat(out, fn, crcs);
					count++;
				}
			}
			else
			{
				if (fn[strlen(fn)-1]!='.')	/* Don't try . or .. entries */
					scan_dir(out, fn, crcs);
			}
		}
		else
		{
			printf("Error getting attributes of %s\n", direntp->d_name);
		}
	}

	if (dirp)
	{
		if (count)
		{
			printf("Scanned %d DATs in %s\n\n", count, dir);
			if (out) fprintf(out, "Scanned %d DATs in %s\n\n", count, dir);
		}

		closedir(dirp);                               
	}

	return(0);                                   
}

/* --------------------------------------------------------------------------
 * Dat scan - Tokenised parser code ripped from CAESAR
 * -------------------------------------------------------------------------- */

int scan_dat(FILE *out, char *fn, struct crc *crcs)
{
	struct options *options=0;
	struct dat *dat=0;
	struct rom_idx *rom_match;
	int printed_fn=0;
	int printed_game=0;
	int i, errflg=0;

	/* --- Allocate memory for user options --- */

	STRUCT_CALLOC(options, 1, sizeof(struct options))

	if (!errflg)
	{
		options->options=OPTION_LOAD_QUIETLY;
		options->fn=fn;
	}

	/* --- Initialise the data file --- */

	if (!errflg && (dat=init_dat(options))==0)
		errflg++;

	for (i=0; !errflg && i<MAX_ZIP_ENTRIES && crcs[i].crc; i++)
	{
		rom_match=bsearch((const void *)&crcs[i].crc, dat->rom_crc_idx, dat->num_roms, sizeof(struct rom_idx), find_rom_by_crc);

		if (rom_match!=0)
		{
			if (!printed_fn)
			{
				printf("CRC matches in %s\n\n", fn);
				if (out) fprintf(out, "CRC matches in %s\n\n", fn);
				printed_fn++;
			}

			if (!printed_game)
			{
				printf("Game:         %s\n", rom_match->rom->game->name);
				printf("Description:  %s\n", rom_match->rom->game->description);
				if (rom_match->rom->game->manufacturer)
					printf("Manufacturer: %s\n", rom_match->rom->game->manufacturer);
				if (rom_match->rom->game->year)
					printf("Year:         %s\n", rom_match->rom->game->year);

				if (out)
				{
					fprintf(out, "Game:         %s\n", rom_match->rom->game->name);
					fprintf(out, "Description:  %s\n", rom_match->rom->game->description);
					fprintf(out, "Manufacturer: %s\n", rom_match->rom->game->manufacturer);
					fprintf(out, "Year:         %s\n", rom_match->rom->game->year);
				}

				printed_game++;
			}

			printf("ROM:          %s (%08lx) ", rom_match->rom->name, (unsigned long) rom_match->rom->crc);
			if (out) fprintf(out, "ROM:          %s (%08lx) ", rom_match->rom->name, (unsigned long) rom_match->rom->crc);

			if (crcs[i].fn)
			{
				printf("matches %s\n", crcs[i].fn);
				if (out) fprintf(out, "matches %s\n", crcs[i].fn);
			}
			else
			{
				printf("matches specified CRC\n");
				if (out) fprintf(out, "matches specified CRC\n");
			}
		}
	}

	if (printed_fn)
	{
		printf("\n");
		if (out) fprintf(out, "\n");
	}


	dat=free_dat(dat);

	FREE(options)

	return(0);
}

