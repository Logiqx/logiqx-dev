/* --------------------------------------------------------------------------
 * DatLib - Written by Logiqx (http://www.logiqx.com/)
 *
 * A library of routines for use by DatUtil, MAMEDiff, etc.
 *
 * Additional drivers can easily be added if you have know a little C.
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define DATLIB_VERSION "v1.1"
#define DATLIB_DATE "4 July 2004"


/* --- Standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <zlib.h>

#if !defined (__MINGW32_VERSION) && !defined (__CYGWIN__) && !defined (_MSC_VER)
#include <unistd.h>
#endif


/* --- Definitions and macros for DatLib routines --- */

#include "datlib.h"
#include "driver.h"
#include "macro.h"
#include "token.h"


/* --- Definitions for MAME's unzip routines --- */

#include "mame/unzip.h"


/* --- Definitions for hash routines --- */

#include "hash/md5.h"
#include "hash/sha1.h"


/* --- Is debugging enabled? --- */

int datlib_debug=0;


/* --- External structures --- */

extern const struct driver *drivers[];
extern const struct token tokens[];


/* --------------------------------------------------------------------------
 * Function to display the version of DatLib
 * -------------------------------------------------------------------------- */

void display_datlib_version(void)
{
	printf("DatLib %s (%s)\n", DATLIB_VERSION, DATLIB_DATE);
}


/* --------------------------------------------------------------------------
 * Directory scanner - dir_scan()
 * Treats sub-directories and ZIPs in the directory being scanned as games
 * -------------------------------------------------------------------------- */

int output_rom_details(FILE *out, char *name, uint32_t crc, uint32_t size, char *mem)
{
	md5_context md5ctx;
	unsigned char md5sum[16];
	sha1_context sha1ctx;
	unsigned char sha1sum[20];

	uint32_t i;
	int errflg=0;

	/* --- Name and size --- */

	if (strchr(name, ' '))
		fprintf(out, "%s \"%s\"\n", tokens[TOKEN_ROM_NAME].description, name);
	else
		fprintf(out, "%s %s\n", tokens[TOKEN_ROM_NAME].description, name);

	fprintf(out, "%s %d\n", tokens[TOKEN_ROM_SIZE].description, size);

	/* --- CRC32 --- */

	if (mem)
	{
		crc = crc32(0, NULL, 0);
		crc = crc32(crc, mem, size);
	}

	fprintf(out, "%s %08lx\n", tokens[TOKEN_ROM_CRC].description, (unsigned long) crc);

	/* --- MD5 --- */

	if (mem)
	{
		md5_starts(&md5ctx);
		md5_update(&md5ctx, mem, size);
		md5_finish(&md5ctx, md5sum);

		fprintf(out, "%s ", tokens[TOKEN_ROM_MD5].description);
		for (i=0; i<16; i++)
			fprintf(out, "%02x", md5sum[i]);
		fprintf(out, "\n");
	}

	/* --- SHA1 --- */

	if (mem)
	{
		sha1_starts(&sha1ctx);
		sha1_update(&sha1ctx, mem, size);
		sha1_finish(&sha1ctx, sha1sum);

		fprintf(out, "%s ", tokens[TOKEN_ROM_SHA1].description);
		for (i=0; i<20; i++)
			fprintf(out, "%02x", sha1sum[i]);
		fprintf(out, "\n");
	}

	/* --- Done --- */

	return(errflg);
}

int dir_scan(struct dat *dat)
{
	FILE *out=0;

	DIR *dirp=0, *sdirp=0;                                    
	struct dirent *direntp, *sdirentp;                       
	struct stat buf;

	ZIP *zip;
	struct zipent *zipent;

	char fn[MAX_FILENAME_LENGTH+1];
	char st[MAX_FILENAME_LENGTH+1];

	char *mem;

	int errflg=0;

	if (!datlib_debug)
		printf("  Scanning directory and writing details to datlib.tmp...\n");

	FOPEN(out, "datlib.tmp", "w")

	if (!errflg)
		fprintf(out, "*** DatLib Folder Scan ***\n");

	if (!errflg && (dirp=opendir(dat->name))==0)
		errflg++;

	while (!errflg && dirp && ((direntp = readdir(dirp)) != NULL))
	{
		sprintf(fn, "%s/%s", dat->name, direntp->d_name);

		if (stat(fn, &buf) == 0)
		{
			if (!(buf.st_mode & S_IFDIR))
			{
				strcpy(st, fn);
				LOWER(st)

				if (strrchr(st, '.') && !strcmp(strrchr(st, '.'), ".zip"))
				{
					strcpy(st, direntp->d_name);

					LOWER(strrchr(st, '.'))
					if (strstr(st, ".zip"))
						*strstr(st, ".zip")='\0';

					if (strchr(st, ' '))
						fprintf(out, "\n%s \"%s\"\n", tokens[TOKEN_GAME_NAME].description, st);
					else
						fprintf(out, "\n%s %s\n", tokens[TOKEN_GAME_NAME].description, st);

					if ((zip=openzip(fn)))
					{
						while (!errflg && (zipent = readzip(zip)) != 0)
						{
							if (dat->options & OPTION_EXTENDED_CHECKSUMS)
							{
								if (zipent->uncompressed_size && zipent->uncompressed_size<=MAX_ROM_SIZE)
								{
									BYTE_MALLOC(mem, zipent->uncompressed_size)

									if (!errflg)
										errflg=readuncompresszip(zip, zipent, mem);

									if (!errflg)
										output_rom_details(out, zipent->name, 0, zipent->uncompressed_size, mem);

									FREE(mem);
								}
							}
							else
							{
								output_rom_details(out, zipent->name, zipent->crc32, zipent->uncompressed_size, 0);
							}
						}
						closezip(zip);
					}
				}
			}
			else
			{
				if (fn[strlen(fn)-1]!='.')	// Don't try . or .. entries
				{
					fprintf(out, "\n%s \"%s\"\n", tokens[TOKEN_GAME_NAME].description, direntp->d_name);

					sdirp = opendir(fn);                          

					while (!errflg && sdirp && ((sdirentp = readdir(sdirp)) != NULL))
					{
						sprintf(st, "%s/%s", fn, sdirentp->d_name);
						if (stat(st, &buf) == 0)
						{
							if (!(buf.st_mode & S_IFDIR) && buf.st_size && buf.st_size<=MAX_ROM_SIZE)
							{
								BYTE_MALLOC(mem, (int)buf.st_size)
								BYTE_READ(mem, (int)buf.st_size, st);

								if (!errflg)
									output_rom_details(out, sdirentp->d_name, 0, buf.st_size, mem);

								FREE(mem);
							}
						}
						else
						{
							fprintf(stderr, "Error getting attributes of %s\n", sdirentp->d_name);
						}
					}

					if (sdirp)
						closedir(sdirp);                               
				}
			}
		}
		else
		{
			fprintf(stderr, "Error getting attributes of %s\n", direntp->d_name);
		}
	}

	if (dirp)
		closedir(dirp);

	FCLOSE(out)

	return(errflg);
}


/* --------------------------------------------------------------------------
 * Functions for sorting indexes
 * -------------------------------------------------------------------------- */

int rom_crc_idx_sort_function(const void *idx1, const void *idx2)
{
	int result=0;

	if (((struct rom_idx *)idx2)->rom->crc > ((struct rom_idx *)idx1)->rom->crc)
		result=-1;

	if (((struct rom_idx *)idx2)->rom->crc < ((struct rom_idx *)idx1)->rom->crc)
		result=1;

	if (result==0)
		result=strcmp(((struct rom_idx *)idx1)->rom->name, ((struct rom_idx *)idx2)->rom->name);

	return(result);
}

int rom_name_idx_sort_function(const void *idx1, const void *idx2)
{
	int result=strcmp(((struct rom_idx *)idx1)->rom->name, ((struct rom_idx *)idx2)->rom->name);

	if (result==0)
	{
		if (((struct rom_idx *)idx2)->rom->crc > ((struct rom_idx *)idx1)->rom->crc)
			result=-1;

		if (((struct rom_idx *)idx2)->rom->crc < ((struct rom_idx *)idx1)->rom->crc)
			result=1;
	}

	return(result);
}

int disk_name_idx_sort_function(const void *idx1, const void *idx2)
{
	return(strcmp(((struct disk_idx *)idx1)->disk->name, ((struct disk_idx *)idx2)->disk->name));
}

int sample_name_idx_sort_function(const void *idx1, const void *idx2)
{
	return(strcmp(((struct sample_idx *)idx1)->sample->name, ((struct sample_idx *)idx2)->sample->name));
}

int game_crc_idx_sort_function(const void *idx1, const void *idx2)
{
	int result=0;

	if (((struct game_idx *)idx2)->game->crc > ((struct game_idx *)idx1)->game->crc)
		result=-1;

	if (((struct game_idx *)idx2)->game->crc < ((struct game_idx *)idx1)->game->crc)
		result=1;

	if (result==0)
		result=strcmp(((struct game_idx *)idx1)->game->name, ((struct game_idx *)idx2)->game->name);

	return(result);
}

int game_name_idx_sort_function(const void *idx1, const void *idx2)
{
	int result=strcmp(((struct game_idx *)idx1)->game->name, ((struct game_idx *)idx2)->game->name);

	if (result==0)
	{
		if (((struct game_idx *)idx2)->game->crc > ((struct game_idx *)idx1)->game->crc)
			result=-1;

		if (((struct game_idx *)idx2)->game->crc < ((struct game_idx *)idx1)->game->crc)
			result=1;
	}

	return(result);
}

int game_score_idx_sort_function(const void *idx1, const void *idx2)
{
	if (((struct game_idx *)idx2)->game->score < ((struct game_idx *)idx1)->game->score)
		return(-1);

	if (((struct game_idx *)idx2)->game->score > ((struct game_idx *)idx1)->game->score)
		return(1);

	return(0);
}

int game_zip_name_idx_sort_function(const void *idx1, const void *idx2)
{
	return(strcmp(((struct game_zip_idx *)idx1)->game_zip->game->name, ((struct game_zip_idx *)idx2)->game_zip->game->name));
}


/* --------------------------------------------------------------------------
 * Functions for sorting the games by parent name then game name
 * -------------------------------------------------------------------------- */

int game_parent_sort_function(const void *game1, const void *game2)
{
	char *parent1=((struct game *)game1)->cloneof;
	char *parent2=((struct game *)game2)->cloneof;

	int result=0;

	if (parent1==0)
		parent1=((struct game *)game1)->name;
	if (parent2==0)
		parent2=((struct game *)game2)->name;

	/* --- Resources should be after games --- */

	if (!(((struct game *)game1)->game_flags & FLAG_RESOURCE_NAME) && (((struct game *)game2)->game_flags & FLAG_RESOURCE_NAME))
		result=-1;
	else if ((((struct game *)game1)->game_flags & FLAG_RESOURCE_NAME) && !(((struct game *)game2)->game_flags & FLAG_RESOURCE_NAME))
		result=1;
	else
	{
		if (((result=strcmp(parent1, parent2))==0))
		{
			if (((struct game *)game1)->cloneof==0)
				result=-1;
			else if (((struct game *)game2)->cloneof==0)
				result=1;
			else
				result=strcmp(((struct game *)game1)->name, ((struct game *)game2)->name);
		}
	}

	return(result);
}

/* --------------------------------------------------------------------------
 * Function to initialize the dat structure and load the dat - init_dat()
 * -------------------------------------------------------------------------- */

int allocate_dat_memory(struct dat *dat)
{
	char type;
	int game_type=0;

	int errflg=0;

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Counting number of games, roms, disks, samples, etc...\n");
	}

	/* --- Rewind the tokenized dat --- */

	BUFFER2_REWIND

	/* --- Scan through all tokens and count element types --- */

	while (BUFFER2_REMAINING && (type=*BUFFER2_PTR++)!=TOKEN_UNDEFINED)
	{
		if (type==TOKEN_GAME_NAME)
		{
			game_type=FLAG_GAME_NAME;
			dat->num_games++;
		}

		else if (type==TOKEN_RESOURCE_NAME)
		{
			game_type=FLAG_RESOURCE_NAME;
			dat->num_games++;
		}

		else if (type==TOKEN_MACHINE_NAME)
		{
			game_type=FLAG_MACHINE_NAME;
			dat->num_games++;
		}

		else if (type==TOKEN_ROM_NAME && dat->num_games>0)
			dat->num_roms++;

		else if (type==TOKEN_DISK_NAME && dat->num_games>0)
			dat->num_disks++;

		else if (type==TOKEN_SAMPLE_NAME && dat->num_games>0)
			dat->num_samples++;

		BUFFER2_ADVANCE_LINE
	}

	/* --- Allocate memory for the actual dat structures --- */

	if (!errflg)
	{	
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d games identified\n", dat->num_games);
		}

		if (dat->num_games>0)
		{
			STRUCT_CALLOC(dat->games, dat->num_games, sizeof(struct game));
			STRUCT_CALLOC(dat->game_name_idx, dat->num_games, sizeof(struct game_idx));
			STRUCT_CALLOC(dat->game_crc_idx, dat->num_games, sizeof(struct game_idx));
			STRUCT_CALLOC(dat->game_score_idx, dat->num_games, sizeof(struct game_idx));

			STRUCT_CALLOC(dat->game_zips, dat->num_games, sizeof(struct game_zip));
			STRUCT_CALLOC(dat->game_zip_name_idx, dat->num_games, sizeof(struct game_zip_idx));
		}
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d roms identified\n", dat->num_roms);
		}

		if (dat->num_roms>0)
		{
			STRUCT_CALLOC(dat->roms, dat->num_roms, sizeof(struct rom));
			STRUCT_CALLOC(dat->game_rom_name_idx, dat->num_roms, sizeof(struct rom_idx));
			STRUCT_CALLOC(dat->game_rom_crc_idx, dat->num_roms, sizeof(struct rom_idx));
			STRUCT_CALLOC(dat->rom_name_idx, dat->num_roms, sizeof(struct rom_idx));
			STRUCT_CALLOC(dat->rom_crc_idx, dat->num_roms, sizeof(struct rom_idx));

			STRUCT_CALLOC(dat->game_zip_roms, dat->num_roms, sizeof(struct game_zip_rom));
		}
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d disks identified\n", dat->num_disks);
		}

		if (dat->num_disks>0)
		{
			STRUCT_CALLOC(dat->disks, dat->num_disks, sizeof(struct disk));
			STRUCT_CALLOC(dat->game_disk_name_idx, dat->num_disks, sizeof(struct disk_idx));
			STRUCT_CALLOC(dat->disk_name_idx, dat->num_disks, sizeof(struct disk_idx));
		}
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d samples identified\n", dat->num_samples);
		}

		if (dat->num_samples>0)
		{
			STRUCT_CALLOC(dat->samples, dat->num_samples, sizeof(struct sample));
			STRUCT_CALLOC(dat->game_sample_name_idx, dat->num_samples, sizeof(struct sample_idx));
			STRUCT_CALLOC(dat->sample_name_idx, dat->num_samples, sizeof(struct sample_idx));
		}
	}

	return(errflg);
}

int store_tokenized_dat(struct dat *dat)
{
	struct game *curr_game=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;

	char type;

	int errflg=0;

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Storing the tokenized dat within the actual dat structure...\n");
	}
	else
	{
		if (!(dat->options & OPTION_LOAD_QUIETLY))
			printf("  Storing the tokenized dat within the actual dat structure...\n");
	}

	/* --- Rewind the tokenized dat --- */

	BUFFER2_REWIND

	/* --- Initialise pointer variables --- */

	curr_game=dat->games;
	curr_rom=dat->roms;
	curr_disk=dat->disks;
	curr_sample=dat->samples;

	/* --- Scan through all tokens and store everything in the actual dat structure --- */

	while (BUFFER2_REMAINING && (type=*BUFFER2_PTR++)!=TOKEN_UNDEFINED)
	{
		/* --- ClrMamePro header --- */

		if (!(dat->options & OPTION_GAME))
		{
			if (type==TOKEN_CLRMAMEPRO_NAME)
				dat->clrmamepro.name=BUFFER2_PTR;

			else if (type==TOKEN_CLRMAMEPRO_DESCRIPTION)
				dat->clrmamepro.description=BUFFER2_PTR;

			else if (type==TOKEN_CLRMAMEPRO_CATEGORY)
				dat->clrmamepro.category=BUFFER2_PTR;

			else if (type==TOKEN_CLRMAMEPRO_VERSION)
				dat->clrmamepro.version=BUFFER2_PTR;

			else if (type==TOKEN_CLRMAMEPRO_AUTHOR)
				dat->clrmamepro.author=BUFFER2_PTR;

			else if (type==TOKEN_CLRMAMEPRO_FORCEMERGING)
				dat->clrmamepro.forcemerging=BUFFER2_PTR;

			else if (type==TOKEN_CLRMAMEPRO_FORCEZIPPING)
				dat->clrmamepro.forcezipping=BUFFER2_PTR;
		}

		/* --- RomCenter header --- */

		if (!(dat->options & OPTION_GAME))
		{
			if (type==TOKEN_ROMCENTER_CREDITS_AUTHOR)
				dat->romcenter_credits.author=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_CREDITS_EMAIL)
				dat->romcenter_credits.email=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_CREDITS_HOMEPAGE)
				dat->romcenter_credits.homepage=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_CREDITS_URL)
				dat->romcenter_credits.url=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_CREDITS_VERSION)
				dat->romcenter_credits.version=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_CREDITS_DATE)
				dat->romcenter_credits.date=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_CREDITS_COMMENT)
				dat->romcenter_credits.comment=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_DAT_PLUGIN)
				dat->romcenter_dat.plugin=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_DAT_SPLIT)
				dat->romcenter_dat.split=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_DAT_MERGE)
				dat->romcenter_dat.merge=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_EMULATOR_REFNAME)
				dat->romcenter_emulator.refname=BUFFER2_PTR;

			else if (type==TOKEN_ROMCENTER_EMULATOR_VERSION)
				dat->romcenter_emulator.version=BUFFER2_PTR;
		}

		/* --- Game, resource and machine elements --- */

		if (curr_game!=0 && curr_game->name!=0)
		{
			if (type==TOKEN_GAME_NAME || type==TOKEN_RESOURCE_NAME || type==TOKEN_MACHINE_NAME)
				curr_game++;

			else if (type==TOKEN_GAME_DESCRIPTION || type==TOKEN_RESOURCE_DESCRIPTION || type==TOKEN_MACHINE_DESCRIPTION)
				curr_game->description=BUFFER2_PTR;

			else if (type==TOKEN_GAME_YEAR || type==TOKEN_RESOURCE_YEAR || type==TOKEN_MACHINE_YEAR)
				curr_game->year=BUFFER2_PTR;

			else if (type==TOKEN_GAME_MANUFACTURER || type==TOKEN_RESOURCE_MANUFACTURER || type==TOKEN_MACHINE_MANUFACTURER)
				curr_game->manufacturer=BUFFER2_PTR;

			else if (type==TOKEN_GAME_REBUILDTO || type==TOKEN_RESOURCE_REBUILDTO || type==TOKEN_MACHINE_REBUILDTO)
				curr_game->rebuildto=BUFFER2_PTR;

			else if (type==TOKEN_GAME_CLONEOF || type==TOKEN_MACHINE_CLONEOF)
				curr_game->cloneof=BUFFER2_PTR;

			else if (type==TOKEN_GAME_ROMOF || type==TOKEN_MACHINE_ROMOF)
				curr_game->romof=BUFFER2_PTR;

			else if (type==TOKEN_GAME_SAMPLEOF || type==TOKEN_MACHINE_SAMPLEOF)
				curr_game->sampleof=BUFFER2_PTR;

			/* --- ROM elements --- */

			if (curr_rom!=0 && curr_rom->name!=0)
			{
				if (type==TOKEN_ROM_NAME)
					curr_rom++;

				else if (type==TOKEN_ROM_MERGE)
					curr_rom->merge=BUFFER2_PTR;

				else if (type==TOKEN_ROM_SIZE)
					curr_rom->size=strtoul(BUFFER2_PTR, NULL, 10);

				else if (type==TOKEN_ROM_CRC)
				{
					curr_rom->crc=strtoul(BUFFER2_PTR, NULL, 16);

					if (curr_rom->crc==0)
						curr_rom->rom_flags|=FLAG_ROM_NODUMP;
				}

				else if (type==TOKEN_ROM_MD5)
					curr_rom->md5=BUFFER2_PTR;

				else if (type==TOKEN_ROM_SHA1)
					curr_rom->sha1=BUFFER2_PTR;

				else if (type==TOKEN_ROM_REGION)
					curr_rom->region=BUFFER2_PTR;

				else if (type==TOKEN_ROM_FLAGS)
				{
					if (!strcmp(BUFFER2_PTR, "baddump"))
						curr_rom->rom_flags|=FLAG_ROM_BADDUMP;
					else if (!strcmp(BUFFER2_PTR, "nodump"))
						curr_rom->rom_flags|=FLAG_ROM_NODUMP;
				}
			}

			if (type==TOKEN_ROM_NAME)
			{
				/* --- The current ROM must remember keep its name --- */

				curr_rom->name=BUFFER2_PTR;

				/* --- If this is the first rom for the current game then set up the roms pointer --- */

				if (curr_game->roms==0)
					curr_game->roms=curr_rom;

				/* --- Whatever happens, increase the rom count for the current game --- */

				curr_game->num_roms++;
			}

			/* --- Disk elements --- */

			if (curr_disk!=0 && curr_disk->name!=0)
			{
				if (type==TOKEN_DISK_NAME)
					curr_disk++;

				else if (type==TOKEN_DISK_MD5)
					curr_disk->md5=BUFFER2_PTR;

				else if (type==TOKEN_DISK_SHA1)
					curr_disk->sha1=BUFFER2_PTR;

				else if (type==TOKEN_DISK_REGION)
					curr_disk->region=BUFFER2_PTR;
			}

			if (type==TOKEN_DISK_NAME)
			{
				/* --- The current disk must remember keep its name --- */

				curr_disk->name=BUFFER2_PTR;

				/* --- If this is the first disk for the current game then set up the disks pointer --- */

				if (curr_game->disks==0)
					curr_game->disks=curr_disk;

				/* --- Whatever happens, increase the disk count for the current game --- */

				curr_game->num_disks++;
			}

			/* --- Sample elements --- */

			if (curr_sample!=0 && curr_sample->name!=0)
			{
				if (type==TOKEN_SAMPLE_NAME)
					curr_sample++;
			}

			if (type==TOKEN_SAMPLE_NAME)
			{
				/* --- The current sample must remember keep its name --- */

				curr_sample->name=BUFFER2_PTR;

				/* --- If this is the first sample for the current game then set up the samples pointer --- */

				if (curr_game->samples==0)
					curr_game->samples=curr_sample;

				/* --- Whatever happens, increase the sample count for the current game --- */

				curr_game->num_samples++;
			}
		}

		/* --- Game, resource and machine names --- */

		if (type==TOKEN_GAME_NAME || type==TOKEN_RESOURCE_NAME || type==TOKEN_MACHINE_NAME)
		{
			/* --- The current game/resource/machine must remember its name and flags --- */

			curr_game->name=BUFFER2_PTR;

			if (type==TOKEN_GAME_NAME)
				curr_game->game_flags|=FLAG_GAME_NAME;
			else if (type==TOKEN_RESOURCE_NAME)
				curr_game->game_flags|=FLAG_RESOURCE_NAME;
			else if (type==TOKEN_MACHINE_NAME)
				curr_game->game_flags|=FLAG_MACHINE_NAME;
		}

		BUFFER2_ADVANCE_LINE
	}

	/* --- Merging --- */

	if (dat->clrmamepro.forcemerging)
	{
		if (!strcmp(dat->clrmamepro.forcemerging, "full"))
			dat->dat_flags|=FLAG_DAT_FULL_MERGING;
		else if (!strcmp(dat->clrmamepro.forcemerging, "split"))
			dat->dat_flags|=FLAG_DAT_SPLIT_MERGING;
		else if (!strcmp(dat->clrmamepro.forcemerging, "none"))
			dat->dat_flags|=FLAG_DAT_NO_MERGING;
	}

	if (dat->romcenter_dat.merge && dat->romcenter_dat.split)
	{
		if (!strcmp(dat->romcenter_dat.merge, "1") && !strcmp(dat->romcenter_dat.split, "0"))
			dat->dat_flags|=FLAG_DAT_FULL_MERGING;
		else if (!strcmp(dat->romcenter_dat.merge, "1") && !strcmp(dat->romcenter_dat.split, "1"))
			dat->dat_flags|=FLAG_DAT_SPLIT_MERGING;
		else if (!strcmp(dat->romcenter_dat.merge, "0") && !strcmp(dat->romcenter_dat.split, "1"))
			dat->dat_flags|=FLAG_DAT_NO_MERGING;
	}

	return(errflg);
}

int lower_case(struct dat *dat)
{
	struct game *curr_game=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;
	uint32_t i, j;

	int errflg=0;

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Making game, rom, disk and sample names lower case...\n");
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		strcpy(TOKEN, curr_game->name);
		LOWER(TOKEN);
		if (strcmp(curr_game->name, TOKEN))
		{
			strcpy(curr_game->name, TOKEN);
			curr_game->game_fixes|=FLAG_GAME_NAME;
		}

		if (curr_game->cloneof)
		{
			strcpy(TOKEN, curr_game->cloneof);
			LOWER(TOKEN);
			if (strcmp(curr_game->cloneof, TOKEN))
			{
				strcpy(curr_game->cloneof, TOKEN);
				curr_game->game_fixes|=FLAG_GAME_CLONEOF;
			}
		}

		if (curr_game->romof)
		{
			strcpy(TOKEN, curr_game->romof);
			LOWER(TOKEN);
			if (strcmp(curr_game->romof, TOKEN))
			{
				strcpy(curr_game->romof, TOKEN);
				curr_game->game_fixes|=FLAG_GAME_ROMOF;
			}
		}

		if (curr_game->sampleof)
		{
			strcpy(TOKEN, curr_game->sampleof);
			LOWER(TOKEN);
			if (strcmp(curr_game->sampleof, TOKEN))
			{
				strcpy(curr_game->sampleof, TOKEN);
				curr_game->game_fixes|=FLAG_GAME_SAMPLEOF;
			}
		}

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			strcpy(TOKEN, curr_rom->name);
			LOWER(TOKEN);
			if (strcmp(curr_rom->name, TOKEN))
			{
				strcpy(curr_rom->name, TOKEN);
				curr_rom->rom_fixes|=FLAG_ROM_NAME;
			}

			if (curr_rom->merge)
			{
				strcpy(TOKEN, curr_rom->merge);
				LOWER(TOKEN);
				if (strcmp(curr_rom->merge, TOKEN))
				{
					strcpy(curr_rom->merge, TOKEN);
					curr_rom->rom_fixes|=FLAG_ROM_MERGE;
				}
			}
		}

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			strcpy(TOKEN, curr_disk->name);
			LOWER(TOKEN);
			if (strcmp(curr_disk->name, TOKEN))
			{
				strcpy(curr_disk->name, TOKEN);
				curr_disk->disk_fixes|=FLAG_DISK_NAME;
			}
		}

		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
		{
			strcpy(TOKEN, curr_sample->name);
			LOWER(TOKEN);
			if (strcmp(curr_sample->name, TOKEN))
			{
				strcpy(curr_sample->name, TOKEN);
				curr_sample->sample_fixes|=FLAG_SAMPLE_NAME;
			}
		}
	}

	return(errflg);
}

int remove_clones(struct dat *dat)
{
	struct game *orig_game=0;
	struct game *curr_game=0;
	uint32_t num_games=dat->num_games;
	uint32_t i;

	int errflg=0;

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Removing clones...\n");
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
		if (curr_game->cloneof==0)
			curr_game->match=1;

	for (i=0, orig_game=dat->games, curr_game=dat->games; i<num_games; i++, orig_game++)
	{
		if (orig_game->match==0)
		{
			dat->num_games-=1;
		}
		else
		{
			memcpy(curr_game, orig_game, sizeof(struct game));
			curr_game++;
		}
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
		curr_game->match=0;

	return(errflg);
}

int single_game(struct dat *dat, char *game)
{
	struct game_idx *curr_game_name_idx;
	struct game_idx *game_match;
	struct game *orig_game=0;
	struct game *curr_game=0;
	struct game *curr_parent;
	uint32_t num_games=dat->num_games;
	uint32_t i;

	int errflg=0;

	/* --- Need a game name index to run 'single name' --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Creating temporary game name index...\n");
	}

	curr_game_name_idx=dat->game_name_idx;
	
	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
		curr_game_name_idx++->game=curr_game;

	qsort(dat->game_name_idx, dat->num_games, sizeof(struct game_idx), game_name_idx_sort_function);

	/* --- Now the index is available, run 'single game' --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Single game...\n");
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (!strcmp(curr_game->name, game))
			curr_game->match=1;

		if (dat->options & OPTION_GAME_AND_CLONES)
		{
			if (curr_game->cloneof && !strcmp(curr_game->cloneof, game))
				curr_game->match=1;
			if (curr_game->romof && !strcmp(curr_game->romof, game))
				curr_game->match=1;

			if (!curr_game->match && curr_game->cloneof && (game_match=bsearch((void *)curr_game->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
				curr_parent=game_match->game;
			else
				curr_parent=0;

			while (!curr_game->match && curr_parent)
			{
				if (curr_parent->cloneof && !strcmp(curr_parent->cloneof, game))
					curr_game->match=1;
				if (curr_parent->romof && !strcmp(curr_parent->romof, game))
					curr_game->match=1;

				if (!curr_game->match && curr_parent->cloneof && (game_match=bsearch((void *)curr_parent->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
					curr_parent=game_match->game;
				else
					curr_parent=0;
			}
		}
	}

	for (i=0, orig_game=dat->games, curr_game=dat->games; i<num_games; i++, orig_game++)
	{
		if (orig_game->match==0)
		{
			dat->num_games-=1;
		}
		else
		{
			memcpy(curr_game, orig_game, sizeof(struct game));
			curr_game++;
		}
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
		curr_game->match=0;

	return(errflg);
}

int fix_descriptions(struct dat *dat)
{
	struct game *curr_game=0;
	uint32_t i;

	int errflg=0;

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Fixing descriptions...\n");
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (!curr_game->description)
		{
			curr_game->description=curr_game->name;
			curr_game->game_fixes|=FLAG_GAME_DESCRIPTION;
		}
	}

	return(errflg);
}

int fix_merging(struct dat *dat)
{
	struct game *curr_game=0;
	struct game_idx *curr_game_name_idx=0;
	struct rom *curr_rom=0;
	uint32_t i, j, k;

	int errflg=0;

	/* --- Need a game name index to run 'fix merging' --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Creating temporary game name index...\n");
	}

	curr_game_name_idx=dat->game_name_idx;
	
	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
		curr_game_name_idx++->game=curr_game;

	qsort(dat->game_name_idx, dat->num_games, sizeof(struct game_idx), game_name_idx_sort_function);

	/* --- Now the index is available, run 'fix merging' --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Fixing merge information...\n");
	}

	/* --- Fix game level details first (cloneof/romof/sampleof) --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		struct game_idx *game_match;

		if (curr_game->romof)
		{
			if ((game_match=bsearch((void *)curr_game->romof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))==0)
			{
				curr_game->romof=0;
				curr_game->game_fixes|=FLAG_GAME_ROMOF;
			}
			else
			{
				curr_game->merge=game_match->game;
			}
		}

		if (curr_game->cloneof)
		{
			if ((game_match=bsearch((void *)curr_game->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))==0)
			{
				curr_game->cloneof=0;
				curr_game->game_fixes|=FLAG_GAME_CLONEOF;
			}
			else
			{
				curr_game->parent=game_match->game;
				curr_game->parent->num_clones+=1;

				if (!curr_game->romof)
				{
					curr_game->romof=curr_game->cloneof;
					curr_game->merge=curr_game->parent;
					curr_game->game_fixes|=FLAG_GAME_ROMOF;
				}
			}
		}

		if (curr_game->sampleof)
		{
			if ((game_match=bsearch((void *)curr_game->sampleof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))==0)
			{
				curr_game->sampleof=0;
				curr_game->game_fixes|=FLAG_GAME_SAMPLEOF;
			}
		}
	}

	/* --- Fix clones of clones --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (curr_game->parent)
		{
			if (curr_game->parent->parent)
			{
				if (curr_game->romof && !strcmp(curr_game->romof, curr_game->cloneof))
				{
					curr_game->romof=0;
					curr_game->merge=0;
					curr_game->game_fixes|=FLAG_GAME_ROMOF;
				}

				curr_game->parent->num_clones--;

				curr_game->cloneof=0;
				curr_game->parent=0;
				curr_game->game_fixes|=FLAG_GAME_CLONEOF;

				curr_game->game_fixes|=FLAG_GAME_CLONEOFCLONE;
			}
		}
	}

	/* --- First ROM pass corrects merge names and pushes CRCs upwards --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			struct game *merge=curr_game->merge;
			int merged=0;

			while (merge)
			{
				struct rom *merge_rom;

				for (k=0, merge_rom=merge->roms; k<merge->num_roms; k++, merge_rom++)
				{
					if (!strcmp(curr_rom->name, merge_rom->name))
					{
						if (!curr_rom->merge || strcmp(curr_rom->merge, curr_rom->name))
						{
							curr_rom->merge=curr_rom->name;
							curr_rom->rom_fixes|=FLAG_ROM_MERGE;

							if (curr_rom->crc && !merge_rom->crc)
							{
								merge_rom->crc=curr_rom->crc;
								merge_rom->rom_fixes|=FLAG_ROM_CRC;

								if (merge_rom->rom_flags & FLAG_ROM_NODUMP)
								{
									merge_rom->rom_flags&=~FLAG_ROM_NODUMP;
									merge_rom->rom_fixes|=FLAG_ROM_NODUMP;
								}

								if (!(merge_rom->rom_flags & FLAG_ROM_BADDUMP))
								{
									merge_rom->rom_flags|=FLAG_ROM_BADDUMP;
									merge_rom->rom_fixes|=FLAG_ROM_BADDUMP;
								}
							}

							if (curr_rom->sha1 && !merge_rom->sha1)
							{
								merge_rom->sha1=curr_rom->sha1;
								merge_rom->rom_fixes|=FLAG_ROM_SHA1;
							}

							if (curr_rom->md5 && !merge_rom->md5)
							{
								merge_rom->md5=curr_rom->md5;
								merge_rom->rom_fixes|=FLAG_ROM_MD5;
							}
						}

						if (merge->game_flags & FLAG_RESOURCE_NAME)
							curr_rom->rom_flags|=FLAG_ROM_BIOS;

						merged++;
					}
				}

				merge=merge->merge;
			}

			if (!merged && curr_rom->merge)
			{
				curr_rom->merge=0;
				curr_rom->rom_fixes|=FLAG_ROM_MERGE;
			}
		}
	}

	/* --- Second pass pushes CRCs downwards --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			struct game *merge=curr_game->merge;

			while (!curr_rom->crc && curr_rom->merge && merge)
			{
				struct rom *merge_rom;

				for (k=0, merge_rom=merge->roms; !curr_rom->crc && k<merge->num_roms; k++, merge_rom++)
				{
					if (!strcmp(curr_rom->name, merge_rom->name))
					{
						if (!curr_rom->crc && merge_rom->crc)
						{
							curr_rom->crc=merge_rom->crc;
							curr_rom->rom_fixes|=FLAG_ROM_CRC;

							if (curr_rom->rom_flags & FLAG_ROM_NODUMP)
							{
								curr_rom->rom_flags&=~FLAG_ROM_NODUMP;
								curr_rom->rom_fixes|=FLAG_ROM_NODUMP;
							}

							if (!(curr_rom->rom_flags & FLAG_ROM_BADDUMP))
							{
								curr_rom->rom_flags|=FLAG_ROM_BADDUMP;
								curr_rom->rom_fixes|=FLAG_ROM_BADDUMP;
							}
						}

						if (!curr_rom->sha1 && merge_rom->sha1)
						{
							curr_rom->sha1=merge_rom->sha1;
							curr_rom->rom_fixes|=FLAG_ROM_SHA1;
						}

						if (!curr_rom->md5 && merge_rom->md5)
						{
							curr_rom->md5=merge_rom->md5;
							curr_rom->rom_fixes|=FLAG_ROM_MD5;
						}
					}
				}

				merge=merge->merge;
			}
		}
	}

	return(errflg);
}

int remove_duplicates(struct dat *dat)
{
	struct game *curr_game=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;
	uint32_t i, j, k;

	int errflg=0;

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Removing duplicate ROMs...\n");
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		/* --- Remove duplicate ROMs --- */

		j=0;
		curr_rom=curr_game->roms; 

		while (j<curr_game->num_roms)
		{
			struct rom *dup_rom;
			int found_dup=0;

			for (k=0, dup_rom=curr_game->roms; j>0 && k<j; k++, dup_rom++)
			{
				if (!strcmp(curr_rom->name, dup_rom->name))
				{
					memcpy(curr_rom, curr_rom+1, (curr_game->num_roms-j-1)*sizeof(struct rom));
					dup_rom->rom_fixes|=FLAG_ROM_DUPLICATE;

					curr_game->num_roms--;

					found_dup++;
				}
			}

			if (!found_dup)
			{
				j++;
				curr_rom++;
			}
		}

		/* --- Remove duplicate disks --- */

		j=0;
		curr_disk=curr_game->disks; 

		while (j<curr_game->num_disks)
		{
			struct disk *dup_disk;
			int found_dup=0;

			for (k=0, dup_disk=curr_game->disks; j>0 && k<j; k++, dup_disk++)
			{
				if (!strcmp(curr_disk->name, dup_disk->name))
				{
					memcpy(curr_disk, curr_disk+1, (curr_game->num_disks-j-1)*sizeof(struct disk));
					curr_game->disk_fixes|=FLAG_DISK_DUPLICATE;

					curr_game->num_disks--;

					found_dup++;
				}
			}

			if (!found_dup)
			{
				j++;
				curr_disk++;
			}
		}

		/* --- Remove duplicate samples --- */

		j=0;
		curr_sample=curr_game->samples; 

		while (j<curr_game->num_samples)
		{
			struct sample *dup_sample;
			int found_dup=0;

			for (k=0, dup_sample=curr_game->samples; j>0 && k<j; k++, dup_sample++)
			{
				if (!strcmp(curr_sample->name, dup_sample->name))
				{
					memcpy(curr_sample, curr_sample+1, (curr_game->num_samples-j-1)*sizeof(struct sample));
					curr_game->sample_fixes|=FLAG_SAMPLE_DUPLICATE;

					curr_game->num_samples--;

					found_dup++;
				}
			}

			if (!found_dup)
			{
				j++;
				curr_sample++;
			}
		}
	}

	return(errflg);
}

int summarise_dat(struct dat *dat)
{
	struct game *curr_game=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;
	uint32_t i, j;

	int errflg=0;

	/* --- Summarise games --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Summarising data file...\n");
	}

	dat->num_resources=dat->num_machines=0;
	dat->num_roms=dat->num_resource_roms=dat->num_machine_roms=0;
	dat->num_disks=dat->num_resource_disks=dat->num_machine_disks=0;
	dat->num_samples=dat->num_resource_samples=dat->num_machine_samples=0;

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		dat->num_roms+=curr_game->num_roms;
		dat->num_disks+=curr_game->num_disks;
		dat->num_samples+=curr_game->num_samples;

		if (curr_game->game_flags & FLAG_RESOURCE_NAME)
		{
			dat->num_resources++;
			dat->num_resource_roms+=curr_game->num_roms;
			dat->num_resource_disks+=curr_game->num_disks;
			dat->num_resource_samples+=curr_game->num_samples;
		}

		if (curr_game->game_flags & FLAG_MACHINE_NAME)
		{
			dat->num_machines++;
			dat->num_machine_roms+=curr_game->num_roms;
			dat->num_machine_disks+=curr_game->num_disks;
			dat->num_machine_samples+=curr_game->num_samples;
		}

		/* --- Calculate game size and CRC --- */

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			curr_game->size+=curr_rom->size;
			curr_game->crc^=curr_rom->crc;
		}

		/* --- Summarise flags --- */

		// N.B. FLAG_GAME_NAME, FLAG_RESOURCE_NAME, FLAG_MACHINE_NAME already set

		if (curr_game->description)
			curr_game->game_flags|=FLAG_GAME_DESCRIPTION;

		if (curr_game->year)
			curr_game->game_flags|=FLAG_GAME_YEAR;

		if (curr_game->manufacturer)
			curr_game->game_flags|=FLAG_GAME_MANUFACTURER;

		if (curr_game->rebuildto)
			curr_game->game_flags|=FLAG_GAME_REBUILDTO;

		if (curr_game->cloneof)
			curr_game->game_flags|=FLAG_GAME_CLONEOF;

		if (curr_game->romof)
			curr_game->game_flags|=FLAG_GAME_ROMOF;

		if (curr_game->sampleof)
			curr_game->game_flags|=FLAG_GAME_SAMPLEOF;

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			if (curr_rom->name)
				curr_rom->rom_flags|=FLAG_ROM_NAME;

			if (curr_rom->merge)
				curr_rom->rom_flags|=FLAG_ROM_MERGE;

			if (curr_rom->size)
				curr_rom->rom_flags|=FLAG_ROM_SIZE;

			if (curr_rom->crc)
				curr_rom->rom_flags|=FLAG_ROM_CRC;

			if (curr_rom->md5)
				curr_rom->rom_flags|=FLAG_ROM_MD5;

			if (curr_rom->sha1)
				curr_rom->rom_flags|=FLAG_ROM_SHA1;

			if (curr_rom->region)
				curr_rom->rom_flags|=FLAG_ROM_REGION;

			// N.B. FLAG_ROM_BADDUMP, FLAG_ROM_NODUMP already set

			curr_game->rom_flags|=curr_rom->rom_flags;
		}

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			if (curr_disk->name)
				curr_disk->disk_flags|=FLAG_DISK_NAME;

			if (curr_disk->md5)
				curr_disk->disk_flags|=FLAG_DISK_MD5;

			if (curr_disk->sha1)
				curr_disk->disk_flags|=FLAG_DISK_SHA1;

			if (curr_disk->region)
				curr_disk->disk_flags|=FLAG_DISK_REGION;

			curr_game->disk_flags|=curr_disk->disk_flags;
		}

		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
		{
			if (curr_sample->name)
				curr_sample->sample_flags|=FLAG_SAMPLE_NAME;

			curr_game->sample_flags|=curr_sample->sample_flags;
		}

		dat->game_flags|=curr_game->game_flags;
		dat->rom_flags|=curr_game->rom_flags;
		dat->disk_flags|=curr_game->disk_flags;
		dat->sample_flags|=curr_game->sample_flags;

		/* --- Keep count of parents, clones and others --- */

		if (curr_game->cloneof)
			dat->num_clones++;
		else if (curr_game->num_clones)
			dat->num_parents++;
		else if (!(curr_game->game_flags & FLAG_RESOURCE_NAME))
			dat->num_others++;
	}

	/* --- Debug summary --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Game flags=%04x\n", dat->game_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("ROM flags=%04x\n", dat->rom_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Disk flags=%02x\n", dat->disk_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sample flags=%02x\n", dat->sample_flags);
	}

	return(errflg);
}

int report_warnings(struct dat *dat)
{
	struct game *curr_game=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	uint32_t i, j, k;

	int errflg=0;

	/* --- Record warnings --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Recording warnings...\n");
	}

	for (i=0; i<dat->num_roms; i++)
	{
		for (j=i+1; j<dat->num_roms && !strcmp(dat->rom_name_idx[i].rom->name, dat->rom_name_idx[j].rom->name); j++)
		{
			if (dat->rom_name_idx[i].rom->crc != dat->rom_name_idx[j].rom->crc &&
				dat->rom_name_idx[i].rom->crc != ~dat->rom_name_idx[j].rom->crc &&
				((dat->rom_name_idx[i].rom->game->name && dat->rom_name_idx[j].rom->game->name &&
				!strcmp(dat->rom_name_idx[i].rom->game->name, dat->rom_name_idx[j].rom->game->name)) ||
				(dat->rom_name_idx[i].rom->game->name && dat->rom_name_idx[j].rom->game->cloneof &&
				!strcmp(dat->rom_name_idx[i].rom->game->name, dat->rom_name_idx[j].rom->game->cloneof)) ||
				(dat->rom_name_idx[i].rom->game->cloneof && dat->rom_name_idx[j].rom->game->name &&
				!strcmp(dat->rom_name_idx[i].rom->game->cloneof, dat->rom_name_idx[j].rom->game->name)) ||
				(dat->rom_name_idx[i].rom->game->cloneof && dat->rom_name_idx[j].rom->game->cloneof &&
				!strcmp(dat->rom_name_idx[i].rom->game->cloneof, dat->rom_name_idx[j].rom->game->cloneof))))
			{
				dat->rom_name_idx[i].rom->rom_warnings|=FLAG_ROM_CONFLICT;
				dat->rom_name_idx[j].rom->rom_warnings|=FLAG_ROM_CONFLICT;
			}
		}
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		curr_game->game_warnings=(curr_game->game_flags ^ dat->game_flags) &
			(FLAG_GAME_DESCRIPTION | FLAG_GAME_YEAR | FLAG_GAME_MANUFACTURER | FLAG_GAME_REBUILDTO);

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			curr_rom->rom_warnings|=(curr_rom->rom_flags ^ dat->rom_flags) &
				(FLAG_ROM_SIZE | FLAG_ROM_REGION);

			if (!(curr_rom->rom_flags & FLAG_ROM_NODUMP))
				curr_rom->rom_warnings|=(curr_rom->rom_flags ^ dat->rom_flags) &
					(FLAG_ROM_CRC | FLAG_ROM_MD5 | FLAG_ROM_SHA1);

			if (!(dat->options & OPTION_IGNORE_FUNNY_SIZES))
			{
				int bits=0;

				for (k=0; k<32; k++)
					if ((1<<k) & curr_rom->size)
						bits++;

				if (bits>1)
					curr_rom->rom_warnings|=FLAG_ROM_FUNNYSIZE;
			}

			curr_game->rom_warnings|=curr_rom->rom_warnings;
		}

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			curr_disk->disk_warnings=(curr_disk->disk_flags ^ dat->disk_flags) &
				(FLAG_DISK_MD5 | FLAG_DISK_SHA1 | FLAG_DISK_REGION);

			curr_game->disk_warnings|=curr_disk->disk_warnings;
		}

		dat->game_warnings|=curr_game->game_warnings;
		dat->rom_warnings|=curr_game->rom_warnings;
		dat->disk_warnings|=curr_game->disk_warnings;
	}

	/* --- Report warnings --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Game warnings=%04x\n", dat->game_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("ROM warnings=%04x\n", dat->rom_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Disk warnings=%02x\n", dat->disk_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sample warnings=%02x\n", dat->sample_warnings);

		printf("%-16s: ", "Datlib.init_dat");
		printf("Reporting warnings...\n");
	}

	if (dat->game_warnings || dat->rom_warnings || dat->disk_warnings || dat->sample_warnings)
	{
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n");
		fprintf(dat->log_file, "Warning Summary\n");
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n\n");
		/* --- Games --- */

		if (dat->game_warnings)
		{
			fprintf(dat->log_file, "Game warnings:\n\n");

			if (dat->game_warnings & FLAG_GAME_DESCRIPTION)
				fprintf(dat->log_file, "    Missing Description\n");
			if (dat->game_warnings & FLAG_GAME_YEAR)
				fprintf(dat->log_file, "    Missing Year\n");
			if (dat->game_warnings & FLAG_GAME_MANUFACTURER)
				fprintf(dat->log_file, "    Missing Manufacturer\n");
			if (dat->game_warnings & FLAG_GAME_REBUILDTO)
				fprintf(dat->log_file, "    Missing Rebuild To\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- ROMs --- */

		if (dat->rom_warnings)
		{
			fprintf(dat->log_file, "ROM warnings:\n\n");

			if (dat->rom_warnings & FLAG_ROM_SIZE)
				fprintf(dat->log_file, "    Missing Size\n");
			if (dat->rom_warnings & FLAG_ROM_CRC)
				fprintf(dat->log_file, "    Missing CRC\n");
			if (dat->rom_warnings & FLAG_ROM_MD5)
				fprintf(dat->log_file, "    Missing MD5\n");
			if (dat->rom_warnings & FLAG_ROM_SHA1)
				fprintf(dat->log_file, "    Missing SHA1\n");
			if (dat->rom_warnings & FLAG_ROM_REGION)
				fprintf(dat->log_file, "    Missing Region\n");
			if (dat->rom_warnings & FLAG_ROM_CONFLICT)
				fprintf(dat->log_file, "    CRC Conflict\n");
			if (dat->rom_warnings & FLAG_ROM_FUNNYSIZE)
				fprintf(dat->log_file, "    Funny Size\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- Disks --- */

		if (dat->disk_warnings)
		{
			fprintf(dat->log_file, "Disk warnings:\n\n");

			if (dat->disk_warnings & FLAG_DISK_MD5)
				fprintf(dat->log_file, "    Missing MD5\n");
			if (dat->disk_warnings & FLAG_DISK_SHA1)
				fprintf(dat->log_file, "    Missing SHA1\n");
			if (dat->disk_warnings & FLAG_DISK_REGION)
				fprintf(dat->log_file, "    Missing Region\n");

			fprintf(dat->log_file, "\n");
		}
	}

	if ((dat->game_warnings || dat->rom_warnings || dat->disk_warnings || dat->sample_warnings) && dat->options & OPTION_VERBOSE_LOGGING)
	{
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n");
		fprintf(dat->log_file, "Warning Details\n");
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n\n");

		for (i=0, curr_game=dat->games; dat->log_file && i<dat->num_games; i++, curr_game++)
		{
			if (curr_game->game_warnings || curr_game->rom_warnings || curr_game->disk_warnings || curr_game->sample_warnings)
			{
				fprintf(dat->log_file, "%s - %s\n", curr_game->name, curr_game->description);

				if (curr_game->game_warnings )
				{
					if (curr_game->game_warnings & FLAG_GAME_DESCRIPTION)
						fprintf(dat->log_file, "    Missing Description\n");
					if (curr_game->game_warnings & FLAG_GAME_YEAR)
						fprintf(dat->log_file, "    Missing Year\n");
					if (curr_game->game_warnings & FLAG_GAME_MANUFACTURER)
						fprintf(dat->log_file, "    Missing Manufacturer\n");
					if (curr_game->game_warnings & FLAG_GAME_REBUILDTO)
						fprintf(dat->log_file, "    Missing Rebuild To\n");
				}
	
				if (curr_game->rom_warnings)
				{
					for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
					{
						if (curr_rom->rom_warnings & FLAG_ROM_SIZE)
							fprintf(dat->log_file, "    ROM %s - Missing Size\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_CRC)
							fprintf(dat->log_file, "    ROM %s - Missing CRC\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_MD5)
							fprintf(dat->log_file, "    ROM %s - Missing MD5\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_SHA1)
							fprintf(dat->log_file, "    ROM %s - Missing SHA1\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_REGION)
							fprintf(dat->log_file, "    ROM %s - Missing Region\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_CONFLICT)
							fprintf(dat->log_file, "    ROM %s - CRC Conflict (%08lx)\n", curr_rom->name, (unsigned long)curr_rom->crc);
						if (curr_rom->rom_warnings & FLAG_ROM_FUNNYSIZE)
							fprintf(dat->log_file, "    ROM %s - Funny Size (%d bytes)\n", curr_rom->name, curr_rom->size);
					}
				}

				if (curr_game->disk_warnings)
				{
					for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
					{
						if (curr_disk->disk_warnings & FLAG_DISK_MD5)
							fprintf(dat->log_file, "    Disk %s - Missing MD5\n", curr_disk->name);
						if (curr_disk->disk_warnings & FLAG_DISK_SHA1)
							fprintf(dat->log_file, "    Disk %s - Missing SHA1\n", curr_disk->name);
						if (curr_disk->disk_warnings & FLAG_DISK_REGION)
							fprintf(dat->log_file, "    Disk %s - Missing Region\n", curr_disk->name);
					}
				}

				fprintf(dat->log_file, "\n");
			}
		}
	}

	return(errflg);
}

int report_fixes(struct dat *dat)
{
	struct game *curr_game=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;
	uint32_t i, j;

	int errflg=0;

	/* --- Summarise fixes --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Recording fixes...\n");
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
			curr_game->rom_fixes|=curr_rom->rom_fixes;

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
			curr_game->disk_fixes|=curr_disk->disk_fixes;

		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
			curr_game->sample_fixes|=curr_sample->sample_fixes;

		dat->game_fixes|=curr_game->game_fixes;
		dat->rom_fixes|=curr_game->rom_fixes;
		dat->disk_fixes|=curr_game->disk_fixes;
		dat->sample_fixes|=curr_game->sample_fixes;
	}

	/* --- Report fixes --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Game fixes=%04x\n", dat->game_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("ROM fixes=%04x\n", dat->rom_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Disk fixes=%02x\n", dat->disk_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sample fixes=%02x\n", dat->sample_fixes);

		printf("%-16s: ", "Datlib.init_dat");
		printf("Reporting fixes...\n");
	}

	if (dat->game_fixes || dat->rom_fixes || dat->disk_fixes || dat->sample_fixes)
	{
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n");
		fprintf(dat->log_file, "Fix Summary\n");
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n\n");

		/* --- Games --- */

		if (dat->game_fixes)
		{
			fprintf(dat->log_file, "Game information that was changed:\n\n");

			if (dat->game_fixes & FLAG_GAME_NAME)
				fprintf(dat->log_file, "    Name\n");
			if (dat->game_fixes & FLAG_MACHINE_NAME)
				fprintf(dat->log_file, "    Name\n");
			if (dat->game_fixes & FLAG_RESOURCE_NAME)
				fprintf(dat->log_file, "    Name\n");
			if (dat->game_fixes & FLAG_GAME_DESCRIPTION)
				fprintf(dat->log_file, "    Description\n");
			if (dat->game_fixes & FLAG_GAME_CLONEOF)
				fprintf(dat->log_file, "    Clone Of\n");
			if (dat->game_fixes & FLAG_GAME_ROMOF)
				fprintf(dat->log_file, "    ROM Of\n");
			if (dat->game_fixes & FLAG_GAME_SAMPLEOF)
				fprintf(dat->log_file, "    Sample Of\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- ROMs --- */

		if (dat->rom_fixes)
		{
			fprintf(dat->log_file, "ROM information that was changed:\n\n");

			if (dat->rom_fixes & FLAG_ROM_NAME)
				fprintf(dat->log_file, "    Name\n");
			if (dat->rom_fixes & FLAG_ROM_MERGE)
				fprintf(dat->log_file, "    Merge\n");
			if (dat->rom_fixes & FLAG_ROM_SIZE)
				fprintf(dat->log_file, "    Size\n");
			if (dat->rom_fixes & FLAG_ROM_CRC)
				fprintf(dat->log_file, "    CRC\n");
			if (dat->rom_fixes & FLAG_ROM_MD5)
				fprintf(dat->log_file, "    MD5\n");
			if (dat->rom_fixes & FLAG_ROM_SHA1)
				fprintf(dat->log_file, "    SHA1\n");
			if (dat->rom_fixes & FLAG_ROM_REGION)
				fprintf(dat->log_file, "    Region\n");
			if (dat->rom_fixes & FLAG_ROM_BADDUMP)
				fprintf(dat->log_file, "    Bad Dump\n");
			if (dat->rom_fixes & FLAG_ROM_NODUMP)
				fprintf(dat->log_file, "    No Dump\n");
			if (dat->rom_fixes & FLAG_ROM_DUPLICATE)
				fprintf(dat->log_file, "    Duplicate\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- Disks --- */

		if (dat->disk_fixes)
		{
			fprintf(dat->log_file, "Disk information that was changed:\n\n");

			if (dat->disk_fixes & FLAG_DISK_NAME)
				fprintf(dat->log_file, "    Name\n");
			if (dat->disk_fixes & FLAG_DISK_MD5)
				fprintf(dat->log_file, "    MD5\n");
			if (dat->disk_fixes & FLAG_DISK_SHA1)
				fprintf(dat->log_file, "    SHA1\n");
			if (dat->disk_fixes & FLAG_DISK_REGION)
				fprintf(dat->log_file, "    Region\n");
			if (dat->disk_fixes & FLAG_DISK_DUPLICATE)
				fprintf(dat->log_file, "    Duplicate\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- Samples --- */

		if (dat->sample_fixes)
		{
			fprintf(dat->log_file, "Sample information that was changed:\n\n");

			if (dat->sample_fixes & FLAG_SAMPLE_NAME)
				fprintf(dat->log_file, "    Name\n");
			if (dat->sample_fixes & FLAG_SAMPLE_DUPLICATE)
				fprintf(dat->log_file, "    Duplicate\n");

			fprintf(dat->log_file, "\n");
		}
	}

	if ((dat->game_fixes || dat->rom_fixes || dat->disk_fixes || dat->sample_fixes) && dat->options & OPTION_VERBOSE_LOGGING)
	{
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n");
		fprintf(dat->log_file, "Fix Details\n");
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n\n");

		for (i=0, curr_game=dat->games; dat->log_file && i<dat->num_games; i++, curr_game++)
		{
			if (curr_game->game_fixes || curr_game->rom_fixes || curr_game->disk_fixes || curr_game->sample_fixes)
			{
				fprintf(dat->log_file, "%s - %s\n", curr_game->name, curr_game->description);

				if (curr_game->game_fixes )
				{
					if (curr_game->game_fixes & FLAG_GAME_NAME)
					{
						if (curr_game->name)
							fprintf(dat->log_file, "    Name changed to lower case.\n");
					}

					if (curr_game->game_fixes & FLAG_MACHINE_NAME)
					{
						if (curr_game->name)
							fprintf(dat->log_file, "    Name changed to lower case.\n");
					}

					if (curr_game->game_fixes & FLAG_RESOURCE_NAME)
					{
						if (curr_game->name)
							fprintf(dat->log_file, "    Name changed to lower case.\n");
					}

					if (curr_game->game_fixes & FLAG_GAME_DESCRIPTION)
					{
						if (curr_game->description)
							fprintf(dat->log_file, "    Description set to game name.\n");
					}

					if (curr_game->game_fixes & FLAG_GAME_CLONEOF)
					{
						if (curr_game->cloneof)
							fprintf(dat->log_file, "    Clone Of changed to lower case.\n");
						else
							if (curr_game->game_fixes & FLAG_GAME_CLONEOFCLONE)
								fprintf(dat->log_file, "    Clone Of removed (clone of clone).\n");
							else
								fprintf(dat->log_file, "    Clone Of removed (invalid reference).\n");
					}

					if (curr_game->game_fixes & FLAG_GAME_ROMOF)
					{
						if (curr_game->romof)
							fprintf(dat->log_file, "    ROM Of changed to lower case.\n");
						else
							fprintf(dat->log_file, "    ROM Of removed (invalid reference).\n");
					}

					if (curr_game->game_fixes & FLAG_GAME_SAMPLEOF)
						{
						if (curr_game->sampleof)
							fprintf(dat->log_file, "    Sample Of changed to lower case.\n");
						else
							fprintf(dat->log_file, "    Sample Of removed (invalid reference).\n");
					}
				}
	
				if (curr_game->rom_fixes)
				{
					for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
					{
						if (curr_rom->rom_fixes & FLAG_ROM_NAME)
						{
							if (curr_rom->name)
								fprintf(dat->log_file, "    ROM %s - name changed to lower case.\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_MERGE)
						{
							if (curr_rom->merge)
								fprintf(dat->log_file, "    ROM %s - merge name set.\n", curr_rom->name);
							else
								fprintf(dat->log_file, "    ROM %s - merge name removed (ROM name not in parent).\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_NODUMP)
						{
							fprintf(dat->log_file, "    ROM %s - CRC/MD5/SHA1 and 'status baddump' have been set.\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_DUPLICATE)
						{
							fprintf(dat->log_file, "    ROM %s - duplicate removed.\n", curr_rom->name);
						}
					}
				}

				if (curr_game->disk_fixes)
				{
					for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
					{
						if (curr_disk->disk_fixes & FLAG_DISK_NAME)
						{
							if (curr_disk->name)
								fprintf(dat->log_file, "    Disk %s - name changed to lower case.\n", curr_disk->name);
						}

						if (curr_disk->disk_fixes & FLAG_DISK_DUPLICATE)
						{
							fprintf(dat->log_file, "    Disk %s - duplicate removed.\n", curr_disk->name);
						}
					}
				}

				if (curr_game->sample_fixes)
				{
					for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
					{
						if (curr_sample->sample_fixes & FLAG_SAMPLE_NAME)
						{
							if (curr_sample->name)
								fprintf(dat->log_file, "    Sample %s - name changed to lower case.\n", curr_sample->name);
						}

						if (curr_sample->sample_fixes & FLAG_SAMPLE_DUPLICATE)
						{
							fprintf(dat->log_file, "    Sample %s - duplicate removed.\n", curr_sample->name);
						}
					}
				}

				fprintf(dat->log_file, "\n");

			}
		}
	}

	return(errflg);
}

int rebuild_dat_indices(struct dat *dat)
{
	struct game_idx *game_match=0;

	struct game *curr_game=0;
	struct game_idx *curr_game_crc_idx=0;
	struct game_idx *curr_game_name_idx=0;
	struct game_idx *curr_game_score_idx=0;

	struct rom *curr_rom=0;
	struct rom_idx *curr_game_rom_crc_idx=0;
	struct rom_idx *curr_game_rom_name_idx=0;
	struct rom_idx *curr_rom_crc_idx=0;
	struct rom_idx *curr_rom_name_idx=0;

	struct disk *curr_disk=0;
	struct disk_idx *curr_game_disk_name_idx=0;
	struct disk_idx *curr_disk_name_idx=0;

	struct sample *curr_sample=0;
	struct sample_idx *curr_game_sample_name_idx=0;
	struct sample_idx *curr_sample_name_idx=0;

	uint32_t i, j;

	int errflg=0;

	/* --- Sort games by parent (if required) --- */

	if (!errflg && dat->options & OPTION_SORT_GAMES_BY_PARENT)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("Sorting games by parent...\n");
		}

		qsort(dat->games, dat->num_games, sizeof(struct game), game_parent_sort_function);
	}

	/* --- Generate game indexes --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Creating game indexes...\n");
	}

	curr_game_crc_idx=dat->game_crc_idx;
	curr_game_name_idx=dat->game_name_idx;
	curr_game_score_idx=dat->game_score_idx;
	
	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		curr_game_crc_idx++->game=curr_game;
		curr_game_name_idx++->game=curr_game;
		curr_game_score_idx++->game=curr_game;
	}

	qsort(dat->game_crc_idx, dat->num_games, sizeof(struct game_idx), game_crc_idx_sort_function);
	qsort(dat->game_name_idx, dat->num_games, sizeof(struct game_idx), game_name_idx_sort_function);
	qsort(dat->game_score_idx, dat->num_games, sizeof(struct game_idx), game_score_idx_sort_function);

	/* --- Generate ROM/disk/sample indexes --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Creating ROM/disk/sample indexes...\n");
	}

	curr_game_rom_crc_idx=dat->game_rom_crc_idx;
	curr_game_rom_name_idx=dat->game_rom_name_idx;
	curr_rom_crc_idx=dat->rom_crc_idx;
	curr_rom_name_idx=dat->rom_name_idx;

	curr_game_disk_name_idx=dat->game_disk_name_idx;
	curr_disk_name_idx=dat->disk_name_idx;

	curr_game_sample_name_idx=dat->game_sample_name_idx;
	curr_sample_name_idx=dat->sample_name_idx;

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (curr_game->cloneof)
		{
			game_match=bsearch((void *)curr_game->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name);
			curr_game->parent=game_match->game;
		}

		if (curr_game->romof)
		{
			game_match=bsearch((void *)curr_game->romof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name);
			curr_game->merge=game_match->game;
		}

		if (curr_game->num_roms)
		{
			curr_game->rom_crc_idx=curr_game_rom_crc_idx;
			curr_game->rom_name_idx=curr_game_rom_name_idx;

			for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
			{
				//if (dat->options & OPTION_COMPLEMENT_BAD_CRCS && curr_rom->rom_flags & FLAG_ROM_BADDUMP)
					//curr_rom->crc=~curr_rom->crc;

				curr_rom->game=curr_game;

				curr_game_rom_crc_idx++->rom=curr_rom;
				curr_game_rom_name_idx++->rom=curr_rom;
				curr_rom_crc_idx++->rom=curr_rom;
				curr_rom_name_idx++->rom=curr_rom;
			}

			qsort(curr_game->rom_crc_idx, curr_game->num_roms, sizeof(struct rom_idx), rom_crc_idx_sort_function);
			qsort(curr_game->rom_name_idx, curr_game->num_roms, sizeof(struct rom_idx), rom_name_idx_sort_function);
		}

		if (curr_game->num_disks)
		{
			curr_game->disk_name_idx=curr_game_disk_name_idx;

			for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
			{
				curr_disk->game=curr_game;

				curr_game_disk_name_idx++->disk=curr_disk;
				curr_disk_name_idx++->disk=curr_disk;
			}

			qsort(curr_game->disk_name_idx, curr_game->num_disks, sizeof(struct disk_idx), disk_name_idx_sort_function);
		}

		if (curr_game->num_samples)
		{
			curr_game->sample_name_idx=curr_game_sample_name_idx;

			for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
			{
				curr_sample->game=curr_game;

				curr_game_sample_name_idx++->sample=curr_sample;
				curr_sample_name_idx++->sample=curr_sample;
			}

			qsort(curr_game->sample_name_idx, curr_game->num_samples, sizeof(struct sample_idx), sample_name_idx_sort_function);
		}
	}

	qsort(dat->rom_crc_idx, dat->num_roms, sizeof(struct rom_idx), rom_crc_idx_sort_function);
	qsort(dat->rom_name_idx, dat->num_roms, sizeof(struct rom_idx), rom_name_idx_sort_function);
	qsort(dat->disk_name_idx, dat->num_disks, sizeof(struct disk_idx), disk_name_idx_sort_function);
	qsort(dat->sample_name_idx, dat->num_samples, sizeof(struct sample_idx), sample_name_idx_sort_function);

	return(errflg);
}

int game_zip_rom_sort_function(const void *zip_rom1, const void *zip_rom2)
{
	return(strcmp(((struct game_zip_rom *)zip_rom1)->game_zip->game->name, ((struct game_zip_rom *)zip_rom2)->game_zip->game->name));
}

int build_zip_structures(struct dat *dat)
{
	struct game *curr_game;
	struct rom *curr_rom;

	struct game_zip *curr_game_zip;
	struct game_zip_idx *curr_game_zip_name_idx;
	struct game_zip_rom *curr_game_zip_rom;

	uint32_t i, j;

	int errflg=0;

	/* --- Create zip structures --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Creating zip structures...\n");
	}

	/* --- Firstly, override user merging if 'forcemerging' is used in the data file --- */

	if (dat->dat_flags & (FLAG_DAT_FULL_MERGING|FLAG_DAT_SPLIT_MERGING|FLAG_DAT_NO_MERGING))
	{
		dat->options&=~(OPTION_DAT_FULL_MERGING|OPTION_DAT_SPLIT_MERGING|OPTION_DAT_NO_MERGING);

		if (dat->dat_flags & FLAG_DAT_FULL_MERGING)
			dat->options|=OPTION_DAT_FULL_MERGING;
		else if (dat->dat_flags & FLAG_DAT_SPLIT_MERGING)
			dat->options|=OPTION_DAT_SPLIT_MERGING;
		else if (dat->dat_flags & FLAG_DAT_NO_MERGING)
			dat->options|=OPTION_DAT_NO_MERGING;
	}

	if (!(dat->options & (OPTION_DAT_FULL_MERGING|OPTION_DAT_SPLIT_MERGING|OPTION_DAT_NO_MERGING)))
		dat->options|=OPTION_DAT_SPLIT_MERGING;

	/* --- Firstly, build the game_zip array and index --- */

	curr_game_zip=dat->game_zips;
	curr_game_zip_name_idx=dat->game_zip_name_idx;
	
	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (dat->options & OPTION_DAT_FULL_MERGING)
		{
			if (curr_game->cloneof==0)
			{
				curr_game_zip_name_idx++->game_zip=curr_game_zip;
				curr_game_zip++->game=curr_game;
				dat->num_game_zips++;
			}
		}
		else
		{
			curr_game_zip_name_idx++->game_zip=curr_game_zip;
			curr_game_zip++->game=curr_game;
			dat->num_game_zips++;
		}
	}

	qsort(dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), game_zip_name_idx_sort_function);

	/* --- Once the game_zip array has been built, do the game_zip_roms --- */

	curr_game_zip_rom=dat->game_zip_roms;

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (dat->options & OPTION_DAT_FULL_MERGING)
		{
			if (curr_game->cloneof)
				curr_game_zip_name_idx=bsearch((void *)curr_game->cloneof, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);
			else
				curr_game_zip_name_idx=bsearch((void *)curr_game->name, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);
		}
		else
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game->name, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);
		}

		curr_game_zip=curr_game_zip_name_idx->game_zip;

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			if (dat->options & OPTION_DAT_NO_MERGING)
			{
				curr_game_zip_rom->game_zip=curr_game_zip;
				curr_game_zip_rom->rom=curr_rom;

				curr_game_zip->num_game_zip_roms++;
				dat->num_game_zip_roms++;
				curr_game_zip_rom++;
			}
			else
			{
				if (curr_rom->merge==0)
				{
					curr_game_zip_rom->game_zip=curr_game_zip;
					curr_game_zip_rom->rom=curr_rom;

					curr_game_zip->num_game_zip_roms++;
					dat->num_game_zip_roms++;
					curr_game_zip_rom++;
				}
			}
		}
	}

	/* --- Finally, link the game_zip_roms into the game_zips --- */

	qsort(dat->game_zip_roms, dat->num_game_zip_roms, sizeof(struct game_zip_rom), game_zip_rom_sort_function);

	for (i=0, curr_game_zip_rom=dat->game_zip_roms; i<dat->num_game_zip_roms; i++, curr_game_zip_rom++)
	{
		if (i==0 || strcmp(curr_game_zip_rom->game_zip->game->name, (curr_game_zip_rom-1)->game_zip->game->name))
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game_zip_rom->game_zip->game->name, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);
			curr_game_zip=curr_game_zip_name_idx->game_zip;

			curr_game_zip->game_zip_roms=curr_game_zip_rom;
		}
	}

	/* --- Display it for testing purposes! --- */

	/*for (i=0, curr_game_zip=dat->game_zips; i<dat->num_game_zips; i++, curr_game_zip++)
	{
		printf("g: %s\n", curr_game_zip->game->name);

		for (j=0, curr_game_zip_rom=curr_game_zip->game_zip_roms; j<curr_game_zip->num_game_zip_roms; j++, curr_game_zip_rom++)
			printf("   r: %s\n", curr_game_zip_rom->rom->name);
	}*/

	return(errflg);
}

struct dat *init_dat(char *fn, uint32_t options, char *game, char *log_fn)
{
	struct dat *dat=0;
	struct stat buf;
	uint32_t i, line_length=0, num_lines=0;
	int driver_matches=0, errflg=0;

	if (options & OPTION_SHOW_DEBUG_INFO)
		datlib_debug=1;

	if (datlib_debug)
	{
		printf("\n%-16s: ", "Datlib.init_dat");
		printf("Started.\n");
	}
	else
	{
		if (!(options & OPTION_LOAD_QUIETLY))
			printf("Processing %s:\n", fn);
	}

	/* --- Allocate memory for main dat structure --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Allocating memory for dat structure (%lu bytes)...\n", (unsigned long)sizeof(struct dat));
	}

	STRUCT_CALLOC(dat, 1, sizeof(struct dat));

	/* --- Remember the user options --- */

	if (!errflg)
		dat->options=options;

	/* --- Open the log file --- */

	if (!errflg && log_fn)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("Creating log file (%s)...\n", log_fn);
		}

		dat->log_name=log_fn;
		FOPEN(dat->log_file, dat->log_name, "w")
	}

	/* --- Remember the dat name and check the file status --- */

	if (!errflg)
	{
		dat->name=fn;

		if (stat(dat->name, &buf)!=0)
		{
			fprintf(stderr, "Error reading properties of %s\n", dat->name);
			errflg++;
		}
	}

	/* --- Directory scan generates an intermediate data file --- */

	if (!errflg)
	{
		if (buf.st_mode & S_IFDIR)
		{
			errflg=dir_scan(dat);

			if (!errflg)
			{
				dat->name="datlib.tmp";

				if (stat(dat->name, &buf)!=0)
				{
					fprintf(stderr, "Error reading properties of %s\n", dat->name);
					errflg++;
				}
			}
		}
	}

	/* --- Allocate memory for file buffer 1 --- */

	if (!errflg)
	{
		dat->buffer1_size=buf.st_size;

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("File size of '%s' is %d bytes.\n", dat->name, dat->buffer1_size);

			printf("%-16s: ", "Datlib.init_dat");
			printf("Allocating memory for file buffer 1 (%d bytes)...\n", dat->buffer1_size+1);
		}

		BYTE_MALLOC(dat->buffer1_start, dat->buffer1_size+1)

		dat->buffer1_end=dat->buffer1_start+dat->buffer1_size;

		BUFFER1_REWIND
	}

	/* --- Read file into buffer 1 and tidy it up (i.e. remove CR/LF) --- */

	if (!errflg)
	{
		float kb=(float)dat->buffer1_size/1024, mb=kb/1024;

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("Loading dat into file buffer 1 (%d bytes)...\n", dat->buffer1_size);
		}
		else
		{
			if (!(options & OPTION_LOAD_QUIETLY))
			{
				if (kb <= 1023)
					printf("  Loading the file into memory (%.0f.%.0fKB)...\n", floor(kb), ceil(100*(kb-floor(kb))));
				else
					printf("  Loading the file into memory (%.0f.%.0fMB)...\n", floor(mb), ceil(100*(mb-floor(mb))));
			}
		}


		BYTE_READ(dat->buffer1_start, dat->buffer1_size, dat->name)
	}

	if (!errflg)
	{
		/* --- Remove CR/LF characters (use 0 terminator) --- */
		/* --- Find the longest line too --- */

		BUFFER1_REWIND

		while (BUFFER1_REMAINING)
		{
			if (*BUFFER1_PTR==10 || *BUFFER1_PTR==13)
			{
				if (line_length>dat->token_size)
					dat->token_size=line_length;

				while (BUFFER1_REMAINING && (*BUFFER1_PTR==10 || *BUFFER1_PTR==13))
				{
					*BUFFER1_PTR='\0';
					BUFFER1_PTR++;
				}

				if (line_length>0)
				{
					num_lines++;
					line_length=0;
				}
			}
			else
			{
				BUFFER1_PTR++;
				line_length++;
			}
		}

		/* --- Add final termination character --- */

		*BUFFER1_PTR='\0';
	}

	/* --- Allocate memory for token buffer --- */

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("Identified %d non-empty lines.\n", num_lines);

			printf("%-16s: ", "Datlib.init_dat");
			printf("Identified maximum line length as %d characters.\n", dat->token_size);

			printf("%-16s: ", "Datlib.init_dat");
			printf("Allocating memory for token buffer (%d bytes)...\n", dat->token_size+1);
		}

		BYTE_MALLOC(dat->token, dat->token_size+1)
	}

	/* --- For all supported drivers, check which one is suitable --- */

	if (!errflg)
	{
		for (i=0; drivers[i]; i++)
		{
			if ((drivers[i]->identify)(dat))
			{
				if (datlib_debug)
				{
					printf("%-16s: ", "Datlib.init_dat");
					printf("Identified as %s format.\n", drivers[i]->description);
				}

				dat->load=(struct driver *)drivers[i];

				driver_matches++;
			}
		}
	}

	/* --- Check if data file was identified successfully --- */

	if (!errflg)
	{
		switch (driver_matches)
		{
			/* --- If no drivers match, the format is not supported --- */

			case 0:
				if (!datlib_debug)
					fprintf(stderr, "Can't identify type for '%s'\n", fn);
				errflg++;
				break;

			/* --- If the is one driver match, the format is supported --- */

			case 1:
				if (!datlib_debug && !(options & OPTION_LOAD_QUIETLY))
					printf("  Identified the file as being '%s' format.\n", dat->load->description);
				break;

			/* --- If more than one driver match, the format is unknown! --- */

			default:
				fprintf(stderr, "Can't identify type for '%s'. Matches more than one type.\n", fn);
				errflg++;
				break;
		}
	}

	if (!errflg)
	{
		/* --- Choose the first save driver that is different to the load driver --- */

		for (i=0; drivers[i]; i++)
		{
			if (!(dat->save) && (strcmp(drivers[i]->description, dat->load->description)||dat->options & OPTION_GAME))
				dat->save=(struct driver *)drivers[i];
		}
	}

	/* --- Allocate memory for file buffer 2 --- */

	/*
	 * The 'safety' thing is because of the possibility that a tokenised
	 * RomCenter dat can potentially be larger than the original text
	 * version.
	 *
	 * However, this is highly unlikely and is only possible for a huge
	 * dat containing games with only one ROM (i.e. a console or computer
	 * dat).
	 *
	 * The solution is to allocate an extra byte for every possible field
	 * (i.e. the number of lines in the file multiplied by number of fields
	 * in each line of the RomCenter format).
	 */

	if (!errflg)
	{
		dat->buffer2_size=buf.st_size+num_lines*dat->load->safety;

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("Allocating memory for file buffer 2 (%d bytes)...\n", dat->buffer2_size+1);
		}

		BYTE_CALLOC(dat->buffer2_start, dat->buffer2_size+1)

		dat->buffer2_end=dat->buffer2_start+dat->buffer2_size;

		BUFFER2_REWIND
	}

	/* --- Tokenise the dat --- */

	if (!errflg)
	{
		if (datlib_debug)
			printf("%-16s: ", "Datlib.init_dat");
		else if (!(options & OPTION_LOAD_QUIETLY))
			printf("  ");

		if (!(options & OPTION_LOAD_QUIETLY))
			printf("Calling the '%s' pre-parser/tokenizer...\n", dat->load->description);

		errflg+=(dat->load->load)(dat);

		/* --- Can now free up the memory from buffer 1 --- */

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("Freeing memory of file buffer 1...\n");
		}
		FREE(dat->buffer1_start)

		dat->buffer1_end=0;
		dat->buffer1_size=0;
		dat->buffer1_ptr=0;
	}

	/* --- Allocate memory for the actual dat structure, populate it and cleanse it --- */

	if (!errflg)
		errflg=allocate_dat_memory(dat);

	if (!errflg)
		errflg=store_tokenized_dat(dat);

	if (!errflg && (options & OPTION_LOWER_CASE))
		errflg=lower_case(dat);

	if (!errflg && (options & OPTION_REMOVE_CLONES))
		errflg=remove_clones(dat);

	if (!errflg && (options & OPTION_GAME))
		errflg=single_game(dat, game);

	if (dat->num_games==0)
		errflg++;

	if (!errflg)
		errflg=fix_descriptions(dat);

	if (!errflg)
		errflg=fix_merging(dat);

	if (!errflg)
		errflg=remove_duplicates(dat);

	if (!errflg)
		errflg=summarise_dat(dat);

	if (!errflg)
		errflg=rebuild_dat_indices(dat);

	if (!errflg)
		errflg=build_zip_structures(dat);

	if (!errflg && dat->log_file)
		errflg=report_warnings(dat);

	if (!errflg && dat->log_file)
		errflg=report_fixes(dat);

	/* --- If any error occurred then throw everything away --- */

	if (errflg)
	{
		if (!datlib_debug && !(options & OPTION_LOAD_QUIETLY))
			printf("Aborted processing due to errors!\n");

		dat=free_dat(dat);
	}

	/* --- All done --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Finished.\n\n");
	}
	else if (!errflg)
	{
		if (!(options & OPTION_LOAD_QUIETLY))
			printf("Processing complete!\n");

		if (options & OPTION_SHOW_SUMMARY)
			printf("\nLoaded %lu games (%lu parents, %lu clones, %lu others) and %lu resources.\n", (unsigned long)dat->num_games-dat->num_resources, (unsigned long)dat->num_parents, (unsigned long)dat->num_clones, (unsigned long)dat->num_others, (unsigned long)dat->num_resources);

		if (log_fn)
		{
			if (dat->game_warnings || dat->rom_warnings || dat->disk_warnings || dat->sample_warnings)
				printf("\nNote: There are some warnings for this data file (see %s for details).\n", log_fn);

			if (dat->game_fixes || dat->rom_fixes || dat->disk_fixes || dat->sample_fixes)
				printf("\nNote: Fixes were applied to the data file (see %s for details).\n", log_fn);

			printf("-------------------------------------------------------------------------------\n");
		}
	}

	return(dat);
}


/* --------------------------------------------------------------------------
 * Function to save data files
 * -------------------------------------------------------------------------- */

int save_dat(struct dat *dat, char *save_name, char *save_mode, char *save_format)
{
	int i, errflg=0;
	int lost=0;

	if (save_format)
	{
		for (i=0, errflg=1; drivers[i]; i++)
		{
			if (drivers[i]->save_format && !strcmp(drivers[i]->save_format, save_format))
			{
				dat->save=(struct driver *)drivers[i];
				errflg=0;
			}
		}

		if (errflg)
			fprintf(stderr, "Unrecognised output format '%s'\n", save_format);
	}

	if (!errflg)
	{
		if (save_name && save_mode)
		{
			if (datlib_debug)
			{
				printf("%-16s: ", "Datlib.save_dat");
				printf("Creating output file (%s)...\n", save_name);
			}

			FOPEN(dat->out, save_name, save_mode)
		}
		else
		{
			fprintf(stderr, "Save name and/or mode not specified!\n");
			errflg++;
		}
	}

	if (!errflg)
		errflg=(dat->save->save)(dat);

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.save_dat");
			printf("Saved in '%s' format.\n", dat->save->description);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Game losses=%04x.\n", ~dat->game_saved & dat->game_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("ROM losses=%04x.\n", ~dat->rom_saved & dat->rom_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Disk losses=%02x.\n", ~dat->disk_saved & dat->disk_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Sample losses=%02x.\n", ~dat->sample_saved & dat->sample_flags);
		}
		else
		{
			printf("Saved %s in %s format.\n", save_name, dat->save->description);
		}

		/* --- Report information that could not be saved (ignore flags that are derived by DatLib) --- */
		 
		if (dat->log_file && (~dat->game_saved & dat->game_flags ||
			~dat->rom_saved & dat->rom_flags ||
			~dat->disk_saved & dat->disk_flags ||
			~dat->sample_saved & dat->sample_flags))
		{
			fprintf(dat->log_file, "-------------------------------------------------------------------------------\n");
			fprintf(dat->log_file, "Features that were lost by saving in %s format\n", dat->save->description);
			fprintf(dat->log_file, "-------------------------------------------------------------------------------\n\n");

			/* --- Games --- */

			if ((lost=~dat->game_saved & dat->game_flags))
			{
				if (lost & FLAG_GAME_NAME)
					fprintf(dat->log_file, "Games have been lost entirely!\n\n");
				if (lost & FLAG_RESOURCE_NAME)
					fprintf(dat->log_file, "Resources have been lost entirely!\n\n");
				if (lost & FLAG_MACHINE_NAME)
					fprintf(dat->log_file, "Machines have been lost entirely!\n\n");

				if (lost)
				{
					fprintf(dat->log_file, "Game information that has been lost:\n\n");

					if (lost & FLAG_GAME_DESCRIPTION)
						fprintf(dat->log_file, "    Description\n");
					if (lost & FLAG_GAME_YEAR)
						fprintf(dat->log_file, "    Year\n");
					if (lost & FLAG_GAME_MANUFACTURER)
						fprintf(dat->log_file, "    Manufacturer\n");
					if (lost & FLAG_GAME_REBUILDTO)
						fprintf(dat->log_file, "    Rebuild To\n");
					if (lost & FLAG_GAME_CLONEOF)
						fprintf(dat->log_file, "    Clone Of\n");
					if (lost & FLAG_GAME_ROMOF)
						fprintf(dat->log_file, "    ROM Of\n");
					if (lost & FLAG_GAME_SAMPLEOF)
						fprintf(dat->log_file, "    Sample Of\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- ROMs --- */

			if ((lost=~dat->rom_saved & dat->rom_flags))
			{
				if (lost & FLAG_ROM_NAME)
				{
					fprintf(dat->log_file, "ROMs have been lost entirely!\n\n");
				}
				else
				{
					fprintf(dat->log_file, "ROM information that has been lost:\n\n");

					if (lost & FLAG_ROM_MERGE)
						fprintf(dat->log_file, "    Merge\n");
					if (lost & FLAG_ROM_SIZE)
						fprintf(dat->log_file, "    Size\n");
					if (lost & FLAG_ROM_CRC)
						fprintf(dat->log_file, "    CRC\n");
					if (lost & FLAG_ROM_MD5)
						fprintf(dat->log_file, "    MD5\n");
					if (lost & FLAG_ROM_SHA1)
						fprintf(dat->log_file, "    SHA1\n");
					if (lost & FLAG_ROM_REGION)
						fprintf(dat->log_file, "    Region\n");
					if (lost & FLAG_ROM_BADDUMP)
						fprintf(dat->log_file, "    Bad Dump (%s uses complemented CRCs instead)\n", dat->save->description);
					if (lost & FLAG_ROM_NODUMP)
						fprintf(dat->log_file, "    No Dump\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- Disks --- */

			if ((lost=~dat->disk_saved & dat->disk_flags))
			{
				if (lost & FLAG_DISK_NAME)
				{
					fprintf(dat->log_file, "Disks have been lost entirely!\n\n");
				}
				else
				{
					fprintf(dat->log_file, "Disk information that has been lost:\n\n");

					if (lost & FLAG_DISK_MD5)
						fprintf(dat->log_file, "    MD5\n");
					if (lost & FLAG_DISK_SHA1)
						fprintf(dat->log_file, "    SHA1\n");
					if (lost & FLAG_DISK_REGION)
						fprintf(dat->log_file, "    Region\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- Samples --- */

			if ((lost=~dat->sample_saved & dat->sample_flags))
			{
				if (lost & FLAG_SAMPLE_NAME)
					fprintf(dat->log_file, "Samples have been lost entirely!\n\n");
			}

			if (!datlib_debug)
				printf("\nNote: Some game information could not be saved (see %s for details).\n", dat->log_name);
		}
	}

	FCLOSE(dat->out)

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.save_dat");
		printf("Finished.\n\n");
	}

	return(errflg);
}


/* --------------------------------------------------------------------------
 * Rom searching functions (used by bsearch)
 * -------------------------------------------------------------------------- */

int find_game_zip_by_name(const void *name, const void *game_zip_idx)
{
	return(strcmp((char *)name, ((struct game_zip_idx *)game_zip_idx)->game_zip->game->name));
}

int find_rom_by_crc(const void *crc, const void *rom_idx)
{
	if (*((uint32_t *)crc) < ((struct rom_idx *)rom_idx)->rom->crc)
		return(-1);

	if (*((uint32_t *)crc) > ((struct rom_idx *)rom_idx)->rom->crc)
		return(1);

	return(0);
}

int find_rom_by_comp_crc(const void *crc, const void *rom_idx)
{
	if ( ~*((uint32_t *)crc) < ((struct rom_idx *)rom_idx)->rom->crc)
		return(-1);

	if ( ~*((uint32_t *)crc) > ((struct rom_idx *)rom_idx)->rom->crc)
		return(1);

	return(0);
}

int find_rom_by_name(const void *name, const void *rom_idx)
{
	return(strcmp((char *)name, ((struct rom_idx *)rom_idx)->rom->name));
}

int find_disk_by_name(const void *name, const void *disk_idx)
{
	return(strcmp((char *)name, ((struct disk_idx *)disk_idx)->disk->name));
}

int find_sample_by_name(const void *name, const void *sample_idx)
{
	return(strcmp((char *)name, ((struct sample_idx *)sample_idx)->sample->name));
}

int find_game_by_name(const void *name, const void *game_idx)
{
	return(strcmp((char *)name, ((struct game_idx *)game_idx)->game->name));
}

int find_game_by_crc(const void *crc, const void *game_idx)
{
	if (*((uint32_t *)crc) < ((struct game_idx *)game_idx)->game->crc)
		return(-1);

	if (*((uint32_t *)crc) > ((struct game_idx *)game_idx)->game->crc)
		return(1);

	return(0);
}


/* --------------------------------------------------------------------------
 * Function to free memory used by dat structure - free_dat()
 * -------------------------------------------------------------------------- */

struct dat *free_dat(struct dat *dat)
{
	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.free_dat");
		printf("Started.\n");
	}

	if (dat)
	{
 		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Closing log file...\n");
		}
		FCLOSE(dat->log_file)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of samples and sample indices...\n");
		}
		FREE(dat->sample_name_idx)
		FREE(dat->game_sample_name_idx)
		FREE(dat->samples)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of disks and disk indices...\n");
		}
		FREE(dat->disk_name_idx)
		FREE(dat->game_disk_name_idx)
		FREE(dat->disks)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of roms and rom indices...\n");
		}
		FREE(dat->game_zip_roms)
		FREE(dat->rom_crc_idx)
		FREE(dat->rom_name_idx)
		FREE(dat->game_rom_crc_idx)
		FREE(dat->game_rom_name_idx)
		FREE(dat->roms)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of games and game indices...\n");
		}
		FREE(dat->game_zip_name_idx)
		FREE(dat->game_zips)
		FREE(dat->game_score_idx)
		FREE(dat->game_crc_idx)
		FREE(dat->game_name_idx)
		FREE(dat->games)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of file buffer 2...\n");
		}
		FREE(dat->buffer2_start)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of token buffer...\n");
		}
		FREE(dat->token)

		if (!strcmp(dat->name, "datlib.tmp"))
		{
 			if (datlib_debug)
			{
				printf("%-16s: ", "Datlib.free_dat");
				printf("Deleting %s...\n", dat->name);
			}
			unlink(dat->name);
		}

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of dat structure...\n");
		}
		FREE(dat);
	}

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.free_dat");
		printf("Finished.\n\n");
	}

	return(dat);
}


/* --------------------------------------------------------------------------
 * INI File Routines
 * -------------------------------------------------------------------------- */

struct ini_entry *load_ini(char *fn)
{
	struct ini_entry *ini=0;
	FILE *in=0;
	char st[MAX_STRING_LENGTH+1];
	char section[MAX_STRING_LENGTH+1]="";
	int num_entries=0, errflg=0;

	FOPEN(in, fn, "r")

	while (!errflg && fgets(st, MAX_STRING_LENGTH, in))
		num_entries++;

	if (!errflg)
		rewind(in);

	if (!errflg)
		STRUCT_CALLOC(ini, num_entries+1, sizeof(struct ini_entry))

	num_entries=0;

	while (!errflg && fgets(st, MAX_STRING_LENGTH, in))
	{
		REMOVE_CR_LF(st)

		if (strchr(st, ';'))
			*strchr(st, ';')='\0';

		if (strchr(st, '['))
		{
			strcpy(section, strchr(st, '[')+1);
			if (strchr(section, ']')) *strchr(section, ']')='\0';
		}

		if (strchr(st, '='))
		{
			strcpy(ini[num_entries].section, section);
			strcpy(ini[num_entries].value, strchr(st, '=')+1);
			*strchr(st, '=')='\0';	
			strcpy(ini[num_entries].param, st);
			num_entries++;
		}
	}

	FCLOSE(in)

	return(ini);
}

struct ini_entry *free_ini(struct ini_entry *ini)
{
	FREE(ini);

	return(ini);
}

char *find_ini_value(struct ini_entry *ini, char *section, char *param)
{
	char *value=0;
	int i=0;

	while(value==0 && ini[i].section[0])
	{
		if (!strcmp(section, ini[i].section) && !strcmp(param, ini[i].param))
			value=ini[i].value;
		else
			i++;
	}

	return(value);
}

