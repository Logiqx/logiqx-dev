/* --------------------------------------------------------------------------
 * ROMBuild - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for re-building ROMs
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define ROMBUILD_VERSION "v2.0"
#define ROMBUILD_DATE "2 July 2004"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <zlib.h>


/* --- Dat library includes --- */

#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"
#include "datlib/src/mame/unzip.h"


/* --- ROMBuild definitions and macros --- */

#include "rombuild.h"


/* --- The ROM manipulation definitions --- */

extern struct Emulator ems[];


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

	extern char *optarg;
	extern int optind;

	char *in_dir="roms_in";
	char *out_dir="roms_out";

	char c;

	int emulator_idx=-1;
	int game_idx=-1;

	int list=0, fulllist=0;
	int errflg=0;

	printf("===============================================================================\n");
	printf("ROMBuild %s (%s)\n", ROMBUILD_VERSION, ROMBUILD_DATE);
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Get the options specified on the command line --- */

	while ((c = getopt(argc, argv, "i:o:l?L")) != EOF)
	switch (c)
	{
		case 'i':
			in_dir=optarg;
			break;
		case 'o':
			out_dir=optarg;
			break;
		case 'l':
			list++;
			break;
		case 'L':
			fulllist++;
			break;
		case '?':
			errflg++;   /* User wants help! */
	}

	/* --- Display the help page if required --- */

	if (!list && !fulllist && argc-optind<1)
		errflg++;

	if (errflg)
	{
		printf("Usage: rombuild [-l] [-i in_dir] [-o out_dir] [emulator [game]]\n\n");
		printf("Using the -l or -L options will list supported emulators/games/roms.\n");
		exit (1);
	}

	/* --- Get going then! --- */

	if (!errflg && argc-optind>=1)
	{
		if ((emulator_idx=find_emulator(argv[optind]))==-1)
			errflg++;
	}

	if (!errflg && argc-optind>=2)
	{
		if ((game_idx=find_game(argv[optind], argv[optind+1]))==-1)
			errflg++;
	}

	if (!errflg && list)
	{
		switch (argc-optind)
		{
			case 0:
				list_ems();
				break;
			case 1:
				list_games(emulator_idx);
				break;
			default:
				list_roms(emulator_idx, game_idx);
				break;
		}
	}

	if (!errflg && fulllist)
	{
		full_list();
	}

	if (!errflg && !list && !fulllist)
	{
		errflg=rebuild_roms(emulator_idx, game_idx, in_dir, out_dir);
	}

	/* --- All done --- */

	exit(errflg);
}

/* --------------------------------------------------------------------------
 * Validation of parameters
 * -------------------------------------------------------------------------- */

int find_emulator(char *emulator)
{
	int emu_idx=-1, i=0;

	while(emu_idx==-1 && ems[i].descr)
	{
		if (!strcmp(ems[i].id, emulator))
			emu_idx=i;
		i++;
	}

	if (emu_idx==-1)
		printf("Invalid emulator (%s)\n", emulator);

	return(emu_idx);
}

int find_game(char *emulator, char *game)
{
	int emu_idx=-1, game_idx=-1, i=0;

	emu_idx=find_emulator(emulator);

	while (emu_idx!=-1 && game_idx==-1 && ems[emu_idx].roms[i].local.game)
	{
		if (!strcmp(ems[emu_idx].roms[i].local.game, game))
			game_idx=i;
		i++;
	}

	if (game_idx==-1)
		printf("Invalid game (%s/%s)\n", emulator, game);

	return(game_idx);
}

/* --------------------------------------------------------------------------
 * Listing supported emulators/games/roms
 * -------------------------------------------------------------------------- */

void list_ems()
{
	int i=0;

	printf("Supported Emulators:\n\n");

	while(ems[i].descr)
	{
		printf("%12s - %s\n", ems[i].id, ems[i].descr);
		i++;
	}
}

void list_games(int emulator_idx)
{
	int i=emulator_idx, j=0;

	printf("Supported Games (of %s):\n\n", ems[i].id);

	while (ems[i].roms[j].local.game)
	{
		if (j==0 || strcmp(ems[i].roms[j].local.game, ems[i].roms[j-1].local.game))
		{
			printf("%s\n", ems[i].roms[j].local.game);
		}
		j++;
	}
}

void list_roms(int emulator_idx, int game_idx)
{
	int i=emulator_idx, j=game_idx;

	printf("Supported ROMs (of %s/%s):\n\n", ems[i].id, ems[i].roms[j].local.game);

	while (!strcmp(ems[i].roms[j].local.game, ems[i].roms[game_idx].local.game))
	{
		if (j==0 || strcmp(ems[i].roms[j].local.rom, ems[i].roms[j-1].local.rom))
		{
			printf("%s (size %ld, crc %08lx)\n", ems[i].roms[j].local.rom, ems[i].roms[j].local.size, ems[i].roms[j].local.crc);
		}
		j++;
	}
}

void full_list()
{
	int i=0, j;

	printf("All supported ROMs:\n\n");

	while(ems[i].descr)
	{
		j=0;
		while (ems[i].roms[j].local.game)
		{
			//if (j==0 || strcmp(ems[i].roms[j].local.game, ems[i].roms[j-1].local.game))
			if (j==0 || strcmp(ems[i].roms[j].local.rom, ems[i].roms[j-1].local.rom))
			{
				printf("%s,", ems[i].id);
				printf("%s,", ems[i].roms[j].local.game);
				printf("%s,%ld,%08lx\n", ems[i].roms[j].local.rom, ems[i].roms[j].local.size, ems[i].roms[j].local.crc);
			}
			j++;
		}
		i++;
	}
}

/* --------------------------------------------------------------------------
 * Processing of 'roms_in' directory
 * -------------------------------------------------------------------------- */

int rebuild_roms(int emulator_idx, int game_idx, char *in_dir, char *out_dir)
{
	struct Cache *rom_cache=0;
	char *mem=0;

	char fn[MAX_FILENAME_LENGTH+1];
	struct stat buf;
	unsigned long crc;

	int i, j=0;
	int found=0, errflg=0;

	/* --- Allocate cache memory --- */

	STRUCT_CALLOC(rom_cache, 1024, sizeof(struct Cache))

	/* --- Generate an array (rom_cache) of ROMs we're looking for --- */

	if (!errflg)
	{
		if (game_idx==-1)
		{
			printf("Rebuilding ROMs for %s:\n\n", ems[emulator_idx].id);

			i=0;
			while (ems[emulator_idx].roms[i].local.game)
			{
				rom_cache[j].rom=&ems[emulator_idx].roms[i];
				rom_cache[j].file[0]='\0';
				i++; j++;
			}
		}
		else
		{
			printf("Rebuilding ROMs for %s/%s:\n\n", ems[emulator_idx].id, ems[emulator_idx].roms[game_idx].local.game);

			i=game_idx;
			while (!strcmp(ems[emulator_idx].roms[i].local.game, ems[emulator_idx].roms[game_idx].local.game))
			{
				rom_cache[j].rom=&ems[emulator_idx].roms[i];
				rom_cache[j].file[0]='\0';
				i++; j++;
			}
		}

		rom_cache[j].rom=NULL;

		/* --- Scan the Input directory --- */

		printf("Scanning...\n");

		scan_dir(in_dir, rom_cache);

		for (i=0; i<j; i++)
		{
			if (((rom_cache[i].file[0]) && ((rom_cache[i].rom->local.offset==0) || (i>0 && rom_cache[i-1].file[0])))
					|| (rom_cache[i].rom->local.offset==0 && rom_cache[i].rom->type==BLOCK_FILL))
				found++;
		}
	}

	/* --- Build the new ROMs --- */

	if (found)
		printf("\nBuilding...\n");
	else
		printf("\nNothing to do!\n");

	for (i=0; found && i<j; i++)
	{
		if ((rom_cache[i].rom->type==ODD_COPY || rom_cache[i].rom->type==EVEN_COPY ||
				rom_cache[i].rom->type==FULL_COPY) &&
				(rom_cache[i].file[0]) &&
				((rom_cache[i].rom->local.offset==0) || (i>0 && rom_cache[i-1].file[0])))
			copy_region(out_dir, &rom_cache[i]);

		if (rom_cache[i].rom->type==COMBINE_EVEN &&
				(rom_cache[i].file[0]) &&
				((rom_cache[i].rom->local.offset==0) || (i>0 && rom_cache[i-1].file[0])))
			combine_region(out_dir, &rom_cache[i], &rom_cache[i+1]);

		if (rom_cache[i].rom->type==COMBINE_ODD)
			rom_cache[i].file[0]='\0';	/* ensure no verification */

		if (rom_cache[i].rom->type==LOWER_COPY &&
				(rom_cache[i].file[0]) &&
				((rom_cache[i].rom->local.offset==0) || (i>0 && rom_cache[i-1].file[0])))
			combine_region_2(out_dir, &rom_cache[i], &rom_cache[i+1]);

		if (rom_cache[i].rom->type==LOWER_SHIFT)
			rom_cache[i].file[0]='\0';	/* ensure no verification */

		if ((rom_cache[i].rom->type==BLOCK_FILL && rom_cache[i].rom->local.offset==0) ||
			(i>0 && rom_cache[i].rom->type==BLOCK_FILL && rom_cache[i-1].file[0]))
		{
			fill_region(out_dir, &rom_cache[i]);
			sprintf(rom_cache[i].file, " ");	/* ensure verification */
		}
	}

	/* --- Verify the new ROMs --- */

	if (found)
		printf("\nVerifying...\n");

	for (i=0; found && i<j; i++)
	{
		if (rom_cache[i].file[0] && rom_cache[i].rom->local.offset==0)
		{
			sprintf(fn, "%s/%s/%s", out_dir, rom_cache[i].rom->local.game, rom_cache[i].rom->local.rom);
			if (stat(fn, &buf) == 0)
			{
				if (buf.st_size == rom_cache[i].rom->local.size)
				{
					crc=crc32(0, NULL, 0);
				
					BYTE_MALLOC(mem, (int)buf.st_size)
					BYTE_READ(mem, (int)buf.st_size, fn);

					if (!errflg)
						crc=crc32(crc, mem, buf.st_size);

					FREE(mem);

					if (crc==rom_cache[i].rom->local.crc)
						printf("%s/%s is ok\n", rom_cache[i].rom->local.game, rom_cache[i].rom->local.rom);
					else
						printf("%s/%s failed CRC check (%08lx instead of %08lx)\n", rom_cache[i].rom->local.game, rom_cache[i].rom->local.rom, crc, rom_cache[i].rom->local.crc);
				}
				else
				{
						printf("%s/%s failed size check\n", rom_cache[i].rom->local.game, rom_cache[i].rom->local.rom);
				}
			}
		}
	}

	FREE(rom_cache)

	return(errflg);
}

/* --------------------------------------------------------------------------
 * The directory scan routine - recursive
 * -------------------------------------------------------------------------- */

int scan_dir(char *dir, struct Cache *rom_cache)
{                                                  
	DIR *dirp;                                    
	struct dirent *direntp;                       
	struct stat buf;

	ZIP *zip;
	struct zipent *zipent;

	char *mem=0;

	char fn[MAX_FILENAME_LENGTH+1];
	unsigned long crc;
	int i, errflg=0;

	dirp = opendir(dir);                          

	while (dirp && ((direntp = readdir(dirp)) != NULL))
	{
		sprintf(fn, "%s/%s", dir, direntp->d_name);
		if (stat(fn, &buf) == 0)
		{
			if (!(buf.st_mode & S_IFDIR))
			{
				if (strrchr(fn, '.') && !strcmp(strrchr(fn, '.'), ".zip"))
				{
					if ((zip = openzip(fn)))
					{
						while ((zipent = readzip(zip)) != 0)
						{
							i=0;
							while (rom_cache[i].rom)
							{
								if ((rom_cache[i].rom->mame.crc==zipent->crc32) && (rom_cache[i].rom->mame.size==zipent->uncompressed_size))
									sprintf(rom_cache[i].file, fn);
								i++;
							}
						}
						closezip(zip);
					}
				}
				else
				{
					crc=crc32(0, NULL, 0);

					if (buf.st_size && buf.st_size<=MAX_ROM_SIZE)
					{
						BYTE_MALLOC(mem, (int)buf.st_size)
						BYTE_READ(mem, (int)buf.st_size, fn);

						if (!errflg)
							crc=crc32(crc, mem, buf.st_size);

						FREE(mem);
					}

					i=0;
					while (rom_cache[i].rom)
					{
						if ((rom_cache[i].rom->mame.crc==crc) && (rom_cache[i].rom->mame.size==buf.st_size))
							sprintf(rom_cache[i].file, fn);
						i++;
					}
				}
			}
			else
			{
				if (fn[strlen(fn)-1]!='.')	/* Don't try . or .. entries */
					scan_dir(fn, rom_cache);
			}
		}
		else
		{
			printf("Error getting attributes of %s\n", direntp->d_name);
		}
	}

	if (dirp)
		closedir(dirp);                               

	return (0);                                   
}                                                  

/* --------------------------------------------------------------------------
 * Load a ROM region from a file or ZIP file
 * -------------------------------------------------------------------------- */

unsigned char *load_region(char *source_fn, struct Rom *region)
{
	FILE *in=0;

	unsigned char *mem=0;

	ZIP *zip;
	struct zipent* zipent;

	int i=0, j=0, errflg=0;

	BYTE_MALLOC(mem, (int)region->mame.size)

	if (!errflg)
	{
		printf("%s/%s (region %05lx-%05lx) using %s", region->local.game, region->local.rom, region->local.offset, region->local.offset+region->local.length-1, source_fn);

		if (strrchr(source_fn, '.') && !strcmp(strrchr(source_fn, '.'), ".zip"))
		{
			if ((zip = openzip(source_fn)))
			{
				while ((zipent = readzip(zip)))
				{
					if ((region->mame.crc==zipent->crc32) && (region->mame.size==zipent->uncompressed_size))
					{
						readuncompresszip(zip, zipent, mem);
						if (region->mame.offset)
							memcpy(mem, mem+region->mame.offset, region->mame.size-region->mame.offset);
					}
				}
				closezip(zip);
			}
			else
			{
				errflg++;
			}
		}
		else
		{
			FOPEN(in, source_fn, "rb")

			if (!errflg)
			{
				fseek(in, region->mame.offset, SEEK_SET);
				fread(mem, 1, region->mame.size, in);
			}

			FCLOSE(in)
		}
	}

	if (!errflg)
	{
		if (region->type==ODD_COPY || region->type==EVEN_COPY)
		{
			if (region->type==ODD_COPY)
				j++;

			for (i=0; i<region->local.length; i++)
			{
				if (i!=j)
					mem[i]=mem[j];
				j+=2;
			}
		}
	
		if (region->patch)
		{
			i=0;
			while(region->patch[i].address)
			{
				mem[region->patch[i].address]=region->patch[i].value;
				i++;
			}
			printf(" (patched)\n");
		}
		else
			printf("\n");
	}

	if (errflg)
		FREE(mem)

	return(mem);
}

/* --------------------------------------------------------------------------
 * Write a block of memory to a ROM file
 * -------------------------------------------------------------------------- */

void write_block(char *out_dir, struct Rom *region, unsigned char *mem)
{
	FILE *out=NULL;
	char fn[MAX_FILENAME_LENGTH+1];
	struct stat buf;
	int errflg=0;

	strcpy(fn, out_dir);
	if (stat(fn, &buf))
		MKDIR(fn, S_IRWXU)

	sprintf(fn, "%s/%s", out_dir, region->local.game);
	if (stat(fn, &buf))
		MKDIR(fn, S_IRWXU)

	sprintf(fn, "%s/%s/%s", out_dir, region->local.game, region->local.rom);
	if (region->local.offset==0)
	{
		FOPEN(out, fn, "wb")
	}
	else
	{
		if (!stat(fn, &buf))
		{
			if (buf.st_size!=region->local.offset)
				printf("%s/%s (region %05lx-%05lx) skipped\n", region->local.game, region->local.rom, region->local.offset, region->local.offset+region->local.length-1);
			else
				FOPEN(out, fn, "ab")
		}
		else
		{
			printf("File does not exist '%s'\n", fn);
		}
	}

	if (mem && out)
	{
		fseek(out, region->local.offset, SEEK_SET);
		fwrite(mem, 1, region->local.length, out);
	}

	FCLOSE(out)
}

/* --------------------------------------------------------------------------
 * ROM manipulation routines
 * -------------------------------------------------------------------------- */

int copy_region(char *out_dir, struct Cache *cache)
{
	unsigned char *mem=0;

	if ((mem=load_region(cache->file, cache->rom)))
		write_block(out_dir, cache->rom, mem);

	FREE(mem)

	return(0);
}

int combine_region(char *out_dir, struct Cache *cache1, struct Cache *cache2)
{
	unsigned char *mem=0, *mem1=0, *mem2=0;
	int i, errflg=0;

	if (!errflg && !(mem1=load_region(cache1->file, cache1->rom)))
		errflg++;

	if (!errflg && !(mem2=load_region(cache2->file, cache2->rom)))
		errflg++;

	if (!errflg)
		BYTE_MALLOC(mem, (int)(cache1->rom->mame.size+cache2->rom->mame.size))

	for (i=0; !errflg && i<cache1->rom->local.length; i++)
		mem[i*2]=mem1[i];

	for (i=0; !errflg && i<cache2->rom->local.length; i++)
		mem[i*2+1]=mem2[i];

	if (!errflg)
		write_block(out_dir, cache1->rom, mem);

	FREE(mem)
	FREE(mem2)
	FREE(mem1)

	return(errflg);
}

int combine_region_2(char *out_dir, struct Cache *cache1, struct Cache *cache2)
{
	unsigned char *mem=0, *mem1=0, *mem2=0;
	int i, errflg=0;

	if (!errflg && !(mem1=load_region(cache1->file, cache1->rom)))
		errflg++;

	if (!errflg && !(mem2=load_region(cache2->file, cache2->rom)))
		errflg++;

	if (!errflg)
		BYTE_MALLOC(mem, (int)(cache1->rom->mame.size+cache2->rom->mame.size))

	for (i=0; !errflg && i<cache1->rom->local.length; i++)
		mem[i]=((mem1[i] & 0x0f) | ((mem2[i] % 8) << 4));

	if (!errflg)
		write_block(out_dir, cache1->rom, mem);

	FREE(mem)
	FREE(mem2)
	FREE(mem1)

	return(errflg);
}

int fill_region(char *out_dir, struct Cache *cache)
{
	struct Rom *region=cache->rom;
	unsigned long *mem=0;
	int i, errflg=0;

	BYTE_MALLOC(mem, (int)region->local.length)

	if (!errflg)
	{
		for (i=0; i<region->local.length/4; i++)
			mem[i]=region->mame.crc;

		printf("%s/%s (region %05lx-%05lx) using fill value 0x%08lx\n", region->local.game, region->local.rom, region->local.offset, region->local.offset+region->local.length-1, region->mame.crc);

		write_block(out_dir, region, (unsigned char *)mem);
	}

	FREE(mem)

	return(errflg);
}
