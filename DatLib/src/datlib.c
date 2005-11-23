/* --------------------------------------------------------------------------
 * DatLib - Written by Logiqx (http://www.logiqx.com/)
 *
 * A library of routines for use by DatUtil, MAMEDiff, etc.
 *
 * Additional drivers can easily be added if you have know a little C.
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define DATLIB_VERSION "v2.11"
#define DATLIB_DATE "13 November 2005"


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

extern const struct datlib_driver *datlib_drivers[];
extern const struct datlib_token datlib_tokens[];


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

int output_sample_details(FILE *out, char *name)
{
	int errflg=0;

	fprintf(out, "%s \"%s\"\n", datlib_tokens[TOKEN_SAMPLE_NAME].description, name);

	return(errflg);
}

int output_chd_details(FILE *out, char *name, char *fn)
{
	FILE *in=0;

	char tag[8];
	uint32_t length=0;
	uint32_t version=0;
	uint8_t byte;

	int i=0, errflg=0;

	fprintf(out, "%s \"%s\"\n", datlib_tokens[TOKEN_DISK_NAME].description, name);

	FOPEN(in, fn, "rb")

	if (!errflg)
	{
		fread(tag, 1, 8, in);

		if (strncmp(tag, "MComprHD", 8))
		{
			fprintf(stderr, "Error: CHD file did not have expected header\n");
			errflg++;
		}
	}

	if (!errflg)
	{
		for (i=0; i<4; i++)
		{
			fread(&byte, 1, 1, in);
			length=length*256+byte;
		}
	}

	if (!errflg)
	{
		for (i=0; i<4; i++)
		{
			fread(&byte, 1, 1, in);
			version=version*256+byte;
		}
	}

	if (!errflg)
	{
		fprintf(out, "%s ", datlib_tokens[TOKEN_DISK_MD5].description);

		fseek(in, 44, 0);
		for (i=0; i<16; i++)
		{
			fread(&byte, 1, 1, in);
			fprintf(out, "%02x", byte);
		}
		fprintf(out, "\n");
	}

	if (!errflg && version>=3)
	{
		fprintf(out, "%s ", datlib_tokens[TOKEN_DISK_SHA1].description);

		fseek(in, 80, 0);
		for (i=0; i<20; i++)
		{
			fread(&byte, 1, 1, in);
			fprintf(out, "%02x", byte);
		}
		fprintf(out, "\n");
	}

	FCLOSE(in)

	return(errflg);
}

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
		fprintf(out, "%s \"%s\"\n", datlib_tokens[TOKEN_ROM_NAME].description, name);
	else
		fprintf(out, "%s %s\n", datlib_tokens[TOKEN_ROM_NAME].description, name);

	fprintf(out, "%s %d\n", datlib_tokens[TOKEN_ROM_SIZE].description, size);

	/* --- CRC32 --- */

	if (mem)
	{
		crc = crc32(0, NULL, 0);
		crc = crc32(crc, mem, size);
	}

	fprintf(out, "%s %08lx\n", datlib_tokens[TOKEN_ROM_CRC].description, (unsigned long) crc);

	/* --- MD5 --- */

	if (mem)
	{
		md5_starts(&md5ctx);
		md5_update(&md5ctx, mem, size);
		md5_finish(&md5ctx, md5sum);

		fprintf(out, "%s ", datlib_tokens[TOKEN_ROM_MD5].description);
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

		fprintf(out, "%s ", datlib_tokens[TOKEN_ROM_SHA1].description);
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

	if (!datlib_debug && !(dat->options->options & OPTION_LOAD_QUIETLY))
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
						fprintf(out, "\n%s \"%s\"\n", datlib_tokens[TOKEN_GAME_NAME].description, st);
					else
						fprintf(out, "\n%s %s\n", datlib_tokens[TOKEN_GAME_NAME].description, st);

					if ((zip=openzip(fn)))
					{
						while (!errflg && (zipent = readzip(zip)) != 0)
						{
							if (dat->options->options & OPTION_OBJECT_TYPE_SAMPLE)
							{
								errflg=output_sample_details(out, zipent->name);
							}
							else if (dat->options->options & OPTION_EXTENDED_CHECKSUMS)
							{
								if (zipent->uncompressed_size && zipent->uncompressed_size<=MAX_ROM_SIZE)
								{
									BYTE_MALLOC(mem, zipent->uncompressed_size)

									if (!errflg)
										errflg=readuncompresszip(zip, zipent, mem);

									if (!errflg)
										errflg=output_rom_details(out, zipent->name, 0, zipent->uncompressed_size, mem);

									FREE(mem)
								}
							}
							else
							{
								errflg=output_rom_details(out, zipent->name, zipent->crc32, zipent->uncompressed_size, 0);
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
					fprintf(out, "\n%s \"%s\"\n", datlib_tokens[TOKEN_GAME_NAME].description, direntp->d_name);

					sdirp = opendir(fn);                          

					while (!errflg && sdirp && ((sdirentp = readdir(sdirp)) != NULL))
					{
						sprintf(st, "%s/%s", fn, sdirentp->d_name);
						if (stat(st, &buf) == 0)
						{
							if (!(buf.st_mode & S_IFDIR))
							{
								if (dat->options->options & OPTION_OBJECT_TYPE_SAMPLE)
								{
									errflg=output_sample_details(out, sdirentp->d_name);
								}
								else if (strrchr(st, '.') && !strcmp(strrchr(st, '.'), ".chd"))
								{
									errflg=output_chd_details(out, sdirentp->d_name, st);
								}
								else if (buf.st_size && buf.st_size<=MAX_ROM_SIZE)
								{
									BYTE_MALLOC(mem, (int)buf.st_size)

									if (!errflg)
										BYTE_READ(mem, (int)buf.st_size, st)

									if (!errflg)
										errflg=output_rom_details(out, sdirentp->d_name, 0, buf.st_size, mem);

									FREE(mem)
								}
							}
						}
						else
						{
							fprintf(stderr, "File not found - '%s'.\n", sdirentp->d_name);
						}
					}

					if (sdirp)
						closedir(sdirp);                               
				}
			}
		}
		else
		{
			fprintf(stderr, "File not found - '%s'.\n", direntp->d_name);
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

int disk_crc_idx_sort_function(const void *idx1, const void *idx2)
{
	int result=0;

	if (((struct disk_idx *)idx2)->disk->crc > ((struct disk_idx *)idx1)->disk->crc)
		result=-1;

	if (((struct disk_idx *)idx2)->disk->crc < ((struct disk_idx *)idx1)->disk->crc)
		result=1;

	if (result==0)
		result=strcmp(((struct disk_idx *)idx1)->disk->name, ((struct disk_idx *)idx2)->disk->name);

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

int game_description_idx_sort_function(const void *idx1, const void *idx2)
{
	int result=strcmp(((struct game_idx *)idx1)->game->description, ((struct game_idx *)idx2)->game->description);

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

int st_idx_sort_function(const void *idx1, const void *idx2)
{
	return(strcmp(((struct st_idx *)idx1)->st, ((struct st_idx *)idx2)->st));
}

int find_st(const void *st, const void *st_idx)
{
	return(strcmp((char *)st, ((struct st_idx *)st_idx)->st));
}

int load_game_selections(struct dat *dat)
{
	struct st_idx *curr_game_selection;
	struct stat buf;

	char *fn=dat->options->game_selection+1, *ptr;
	int i, fs;

	int errflg=0;

	/* --- Remember the dat name and check the file status --- */

	if (!errflg)
	{
		if (*dat->options->game_selection=='@' && stat(fn, &buf)!=0)
		{
			fprintf(stderr, "File not found - '%s'.\n", fn);
			errflg++;
		}
	}

	/* --- Allocate memory for game selection buffer --- */

	if (!errflg)
	{
		if (*dat->options->game_selection=='@')
		{
			fs=buf.st_size;

			if (datlib_debug)
			{
				printf("%-16s: ", "Datlib.init_dat");
				printf("File size of '%s' is %d bytes.\n", fn, fs);

				printf("%-16s: ", "Datlib.init_dat");
				printf("Allocating memory for game selection buffer (%d bytes)...\n", fs+1);
			}
		}
		else
		{
			fs=strlen(dat->options->game_selection);
		}

		BYTE_MALLOC(dat->options->game_selection_buffer, fs+1)
	}

	/* --- Read file into game selection buffer, tidy it up (i.e. remove CR/LF) and count entries --- */

	if (!errflg)
	{
		if (*dat->options->game_selection=='@')
		{
			float kb=(float)fs/1024, mb=kb/1024;

			if (datlib_debug)
			{
				printf("%-16s: ", "Datlib.init_dat");
				printf("Loading game selections into buffer (%d bytes)...\n", fs);
			}
			else
			{
				if (!(dat->options->options & OPTION_LOAD_QUIETLY))
				{
					if (kb <= 1023)
						printf("  Loading game selection file into memory (%.0f.%.0fKB)...\n", floor(kb), ceil(100*(kb-floor(kb))));
					else
						printf("  Loading game selection file into memory (%.0f.%.0fMB)...\n", floor(mb), ceil(100*(mb-floor(mb))));
				}
			}


			BYTE_READ(dat->options->game_selection_buffer, fs, fn)
		}
		else
		{
			strcpy(dat->options->game_selection_buffer, dat->options->game_selection);
		}
	}

	if (!errflg)
	{
		for (i=0, ptr=dat->options->game_selection_buffer; i<fs; i++, ptr++)
		{
			if (*ptr=='\r' || *ptr=='\n' || *ptr=='\t' || *ptr==',')
				*ptr='\0';
			else if ((i==0 && *ptr!=0) || (i>0 && *(ptr-1)==0 && *ptr!=0))
				dat->options->num_game_selections++;
		}
		if (i==fs)
		{
			*ptr='\0';
		}

		STRUCT_CALLOC(dat->options->game_selections, dat->options->num_game_selections, sizeof(struct st_idx))
	}

	/* --- Create game selection list and sort it for fast reference --- */

	if (!errflg)
	{
		for (i=0, ptr=dat->options->game_selection_buffer, curr_game_selection=dat->options->game_selections;
			i<fs; i++, ptr++)
		{
			if ((i==0 && *ptr!=0) || (i>0 && *(ptr-1)==0 && *ptr!=0))
				curr_game_selection++->st=ptr;
		}
		if (i==fs)
		{
			*ptr='\0';
		}


		qsort(dat->options->game_selections, dat->options->num_game_selections, sizeof(struct st_idx), st_idx_sort_function);
	}

	return(errflg);
}

int load_sourcefile_selections(struct dat *dat)
{
	struct st_idx *curr_sourcefile_selection;
	struct stat buf;

	char *fn=dat->options->sourcefile_selection+1, *ptr;
	int i, fs;

	int errflg=0;

	/* --- Remember the dat name and check the file status --- */

	if (!errflg)
	{
		if (*dat->options->sourcefile_selection=='@' && stat(fn, &buf)!=0)
		{
			fprintf(stderr, "File not found - '%s'.\n", fn);
			errflg++;
		}
	}

	/* --- Allocate memory for sourcefile selection buffer --- */

	if (!errflg)
	{
		if (*dat->options->sourcefile_selection=='@')
		{
			fs=buf.st_size;

			if (datlib_debug)
			{
				printf("%-16s: ", "Datlib.init_dat");
				printf("File size of '%s' is %d bytes.\n", fn, fs);

				printf("%-16s: ", "Datlib.init_dat");
				printf("Allocating memory for sourcefile selection buffer (%d bytes)...\n", fs+1);
			}
		}
		else
		{
			fs=strlen(dat->options->sourcefile_selection);
		}

		BYTE_MALLOC(dat->options->sourcefile_selection_buffer, fs+1)
	}

	/* --- Read file into sourcefile selection buffer, tidy it up (i.e. remove CR/LF) and count entries --- */

	if (!errflg)
	{
		if (*dat->options->sourcefile_selection=='@')
		{
			float kb=(float)fs/1024, mb=kb/1024;

			if (datlib_debug)
			{
				printf("%-16s: ", "Datlib.init_dat");
				printf("Loading sourcefile selections into buffer (%d bytes)...\n", fs);
			}
			else
			{
				if (!(dat->options->options & OPTION_LOAD_QUIETLY))
				{
					if (kb <= 1023)
						printf("  Loading sourcefile selection file into memory (%.0f.%.0fKB)...\n", floor(kb), ceil(100*(kb-floor(kb))));
					else
						printf("  Loading sourcefile selection file into memory (%.0f.%.0fMB)...\n", floor(mb), ceil(100*(mb-floor(mb))));
				}
			}

			BYTE_READ(dat->options->sourcefile_selection_buffer, fs, fn)
		}
		else
		{
			strcpy(dat->options->sourcefile_selection_buffer, dat->options->sourcefile_selection);
		}
	}

	if (!errflg)
	{
		for (i=0, ptr=dat->options->sourcefile_selection_buffer; i<fs; i++, ptr++)
		{
			if (*ptr=='\r' || *ptr=='\n' || *ptr=='\t' || *ptr==',')
				*ptr='\0';
			else if ((i==0 && *ptr!=0) || (i>0 && *(ptr-1)==0 && *ptr!=0))
				dat->options->num_sourcefile_selections++;
		}
		if (i==fs)
		{
			*ptr='\0';
		}

		STRUCT_CALLOC(dat->options->sourcefile_selections, dat->options->num_sourcefile_selections, sizeof(struct st_idx))
	}

	/* --- Create sourcefile selection list and sort it for fast reference --- */

	if (!errflg)
	{
		for (i=0, ptr=dat->options->sourcefile_selection_buffer, curr_sourcefile_selection=dat->options->sourcefile_selections;
			i<fs; i++, ptr++)
		{
			if ((i==0 && *ptr!=0) || (i>0 && *(ptr-1)==0 && *ptr!=0))
				curr_sourcefile_selection++->st=ptr;
		}

		qsort(dat->options->sourcefile_selections, dat->options->num_sourcefile_selections, sizeof(struct st_idx), st_idx_sort_function);
	}

	return(errflg);
}

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

	/* --- Scan through all datlib_tokens and count element types --- */

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

		else if (type==TOKEN_COMMENT_TEXT)
			dat->num_comments++;

		else if (type==TOKEN_BIOSSET_NAME && dat->num_games>0)
			dat->num_biossets++;

		else if (type==TOKEN_ROM_NAME && dat->num_games>0)
			dat->num_roms++;

		else if (type==TOKEN_DISK_NAME && dat->num_games>0)
			dat->num_disks++;

		else if (type==TOKEN_SAMPLE_NAME && dat->num_games>0)
			dat->num_samples++;

		else if (type==TOKEN_CHIP_TYPE && dat->num_games>0)
			dat->num_chips++;

		else if (type==TOKEN_VIDEO_SCREEN && dat->num_games>0)
			dat->num_videos++;

		else if (type==TOKEN_SOUND_CHANNELS && dat->num_games>0)
			dat->num_sounds++;

		else if (type==TOKEN_INPUT_PLAYERS && dat->num_games>0)
			dat->num_inputs++;

		else if (type==TOKEN_DIPSWITCH_NAME && dat->num_games>0)
			dat->num_dipswitches++;

		else if (type==TOKEN_DIPVALUE_NAME && dat->num_games>0)
			dat->num_dipvalues++;

		else if (type==TOKEN_DRIVER_STATUS && dat->num_games>0)
			dat->num_drivers++;

		else if (type==TOKEN_DEVICE_NAME && dat->num_games>0)
			dat->num_devices++;

		else if (type==TOKEN_EXTENSION_NAME && dat->num_games>0)
			dat->num_extensions++;

		else if (type==TOKEN_ARCHIVE_NAME && dat->num_games>0)
			dat->num_archives++;

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
			STRUCT_CALLOC(dat->games, dat->num_games, sizeof(struct game))
			STRUCT_CALLOC(dat->game_name_idx, dat->num_games, sizeof(struct game_idx))
			STRUCT_CALLOC(dat->game_description_idx, dat->num_games, sizeof(struct game_idx))
			STRUCT_CALLOC(dat->game_crc_idx, dat->num_games, sizeof(struct game_idx))
			STRUCT_CALLOC(dat->game_score_idx, dat->num_games, sizeof(struct game_idx))

			STRUCT_CALLOC(dat->game_zips, dat->num_games, sizeof(struct game_zip))
			STRUCT_CALLOC(dat->game_zip_name_idx, dat->num_games, sizeof(struct game_zip_idx))
		}
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d comments identified\n", dat->num_comments);
		}

		if (dat->num_comments>0)
			STRUCT_CALLOC(dat->comments, dat->num_comments, sizeof(struct comment))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d bios sets identified\n", dat->num_biossets);
		}

		if (dat->num_biossets>0)
			STRUCT_CALLOC(dat->biossets, dat->num_biossets, sizeof(struct biosset))
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
			STRUCT_CALLOC(dat->roms, dat->num_roms, sizeof(struct rom))
			STRUCT_CALLOC(dat->game_rom_name_idx, dat->num_roms, sizeof(struct rom_idx))
			STRUCT_CALLOC(dat->game_rom_crc_idx, dat->num_roms, sizeof(struct rom_idx))
			STRUCT_CALLOC(dat->rom_name_idx, dat->num_roms, sizeof(struct rom_idx))
			STRUCT_CALLOC(dat->rom_crc_idx, dat->num_roms, sizeof(struct rom_idx))

			STRUCT_CALLOC(dat->game_zip_roms, dat->num_roms, sizeof(struct game_zip_rom))
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
			STRUCT_CALLOC(dat->disks, dat->num_disks, sizeof(struct disk))
			STRUCT_CALLOC(dat->game_disk_name_idx, dat->num_disks, sizeof(struct disk_idx))
			STRUCT_CALLOC(dat->game_disk_crc_idx, dat->num_disks, sizeof(struct disk_idx))
			STRUCT_CALLOC(dat->disk_name_idx, dat->num_disks, sizeof(struct disk_idx))
			STRUCT_CALLOC(dat->disk_crc_idx, dat->num_disks, sizeof(struct disk_idx))

			STRUCT_CALLOC(dat->game_zip_disks, dat->num_disks, sizeof(struct game_zip_disk))
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
			STRUCT_CALLOC(dat->samples, dat->num_samples, sizeof(struct sample))
			STRUCT_CALLOC(dat->game_sample_name_idx, dat->num_samples, sizeof(struct sample_idx))
			STRUCT_CALLOC(dat->sample_name_idx, dat->num_samples, sizeof(struct sample_idx))

			STRUCT_CALLOC(dat->game_zip_samples, dat->num_samples, sizeof(struct game_zip_sample))
		}
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d chips identified\n", dat->num_chips);
		}

		if (dat->num_chips>0)
			STRUCT_CALLOC(dat->chips, dat->num_chips, sizeof(struct chip))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d videos identified\n", dat->num_videos);
		}

		if (dat->num_videos>0)
			STRUCT_CALLOC(dat->videos, dat->num_videos, sizeof(struct video))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d sounds identified\n", dat->num_sounds);
		}

		if (dat->num_sounds>0)
			STRUCT_CALLOC(dat->sounds, dat->num_sounds, sizeof(struct sound))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d inputs identified\n", dat->num_inputs);
		}

		if (dat->num_inputs>0)
			STRUCT_CALLOC(dat->inputs, dat->num_inputs, sizeof(struct input))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d dipswitches identified\n", dat->num_dipswitches);
		}

		if (dat->num_dipswitches>0)
			STRUCT_CALLOC(dat->dipswitches, dat->num_dipswitches, sizeof(struct dipswitch))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d dipvalues identified\n", dat->num_dipvalues);
		}

		if (dat->num_dipvalues>0)
			STRUCT_CALLOC(dat->dipvalues, dat->num_dipvalues, sizeof(struct dipvalue))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d drivers identified\n", dat->num_drivers);
		}

		if (dat->num_drivers>0)
			STRUCT_CALLOC(dat->drivers, dat->num_drivers, sizeof(struct driver))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d devices identified\n", dat->num_devices);
		}

		if (dat->num_devices>0)
			STRUCT_CALLOC(dat->devices, dat->num_devices, sizeof(struct device))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d extensions identified\n", dat->num_extensions);
		}

		if (dat->num_extensions>0)
			STRUCT_CALLOC(dat->extensions, dat->num_extensions, sizeof(struct extension))
	}

	if (!errflg)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("%d archives identified\n", dat->num_archives);
		}

		if (dat->num_archives>0)
			STRUCT_CALLOC(dat->archives, dat->num_archives, sizeof(struct archive))
	}

	return(errflg);
}

int store_tokenized_dat(struct dat *dat)
{
	struct game *curr_game=dat->games;
	struct comment *curr_comment=dat->comments;
	struct biosset *curr_biosset=dat->biossets;
	struct rom *curr_rom=dat->roms;
	struct disk *curr_disk=dat->disks;
	struct sample *curr_sample=dat->samples;
	struct chip *curr_chip=dat->chips;
	struct video *curr_video=dat->videos;
	struct sound *curr_sound=dat->sounds;
	struct input *curr_input=dat->inputs;
	struct dipswitch *curr_dipswitch=dat->dipswitches;
	struct dipvalue *curr_dipvalue=dat->dipvalues;
	struct driver *curr_driver=dat->drivers;
	struct device *curr_device=dat->devices;
	struct extension *curr_extension=dat->extensions;
	struct archive *curr_archive=dat->archives;

	struct comment *comments=0;
	char type;

	int i, num_comments=0, errflg=0;

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Storing the tokenized dat within the actual dat structure...\n");
	}
	else
	{
		if (!(dat->options->options & OPTION_LOAD_QUIETLY))
			printf("  Storing the tokenized dat within the actual dat structure...\n");
	}

	/* --- Rewind the tokenized dat --- */

	BUFFER2_REWIND

	/* --- Scan through all datlib_tokens and store everything in the actual dat structure --- */

	while (BUFFER2_REMAINING && (type=*BUFFER2_PTR++)!=TOKEN_UNDEFINED)
	{
		/* --- ClrMamePro header --- */

		if (!(dat->options->options & (OPTION_GAME_SELECTION|OPTION_SOURCEFILE_SELECTION)))
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

		if (!(dat->options->options & (OPTION_GAME_SELECTION|OPTION_SOURCEFILE_SELECTION)))
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

			else if (type==TOKEN_GAME_SOURCEFILE || type==TOKEN_RESOURCE_SOURCEFILE || type==TOKEN_MACHINE_SOURCEFILE)
				curr_game->sourcefile=BUFFER2_PTR;

			else if (type==TOKEN_GAME_CLONEOF || type==TOKEN_MACHINE_CLONEOF)
				curr_game->cloneof=BUFFER2_PTR;

			else if (type==TOKEN_GAME_ROMOF || type==TOKEN_MACHINE_ROMOF)
				curr_game->romof=BUFFER2_PTR;

			else if (type==TOKEN_GAME_SAMPLEOF || type==TOKEN_MACHINE_SAMPLEOF)
				curr_game->sampleof=BUFFER2_PTR;

			else if (type==TOKEN_GAME_DESCRIPTION || type==TOKEN_RESOURCE_DESCRIPTION || type==TOKEN_MACHINE_DESCRIPTION)
				curr_game->description=BUFFER2_PTR;

			else if (type==TOKEN_GAME_YEAR || type==TOKEN_RESOURCE_YEAR || type==TOKEN_MACHINE_YEAR)
				curr_game->year=BUFFER2_PTR;

			else if (type==TOKEN_GAME_MANUFACTURER || type==TOKEN_RESOURCE_MANUFACTURER || type==TOKEN_MACHINE_MANUFACTURER)
				curr_game->manufacturer=BUFFER2_PTR;

			else if (dat->options->options & OPTION_KEEP_FULL_DETAILS && (type==TOKEN_GAME_HISTORY || type==TOKEN_RESOURCE_HISTORY || type==TOKEN_MACHINE_HISTORY))
				curr_game->history=BUFFER2_PTR;

			else if (type==TOKEN_GAME_REBUILDTO || type==TOKEN_RESOURCE_REBUILDTO || type==TOKEN_MACHINE_REBUILDTO)
				curr_game->rebuildto=BUFFER2_PTR;

			else if (type==TOKEN_GAME_BOARD || type==TOKEN_RESOURCE_BOARD || type==TOKEN_MACHINE_BOARD)
				curr_game->board=BUFFER2_PTR;

			/* --- ROM elements --- */

			if (curr_rom!=0 && curr_rom->name!=0)
			{
				if (type==TOKEN_ROM_NAME)
					curr_rom++;

				else if (type==TOKEN_ROM_SIZE)
				{
					curr_rom->size=strtoul(BUFFER2_PTR, NULL, 10);

					// Value may be zero so its presence needs remembering!
					curr_rom->rom_flags|=FLAG_ROM_SIZE;
				}

				else if (type==TOKEN_ROM_SIZE_HEX)
				{
					curr_rom->size=strtoul(BUFFER2_PTR, NULL, 16);

					// Value may be zero so its presence needs remembering!
					curr_rom->rom_flags|=FLAG_ROM_SIZE;
				}

				else if (type==TOKEN_ROM_CRC)
					curr_rom->crc=strtoul(BUFFER2_PTR, NULL, 16);

				else if (type==TOKEN_ROM_MD5 && dat->options->options & OPTION_MD5_CHECKSUMS)
					curr_rom->md5=BUFFER2_PTR;

				else if (type==TOKEN_ROM_SHA1 && dat->options->options & OPTION_SHA1_CHECKSUMS)
					curr_rom->sha1=BUFFER2_PTR;

				else if (type==TOKEN_ROM_MERGE)
					curr_rom->merge=BUFFER2_PTR;

				else if (type==TOKEN_ROM_STATUS)
					curr_rom->status=BUFFER2_PTR;

				else if (dat->options->options & OPTION_KEEP_FULL_DETAILS)
				{
					if (type==TOKEN_ROM_BIOS)
						curr_rom->bios=BUFFER2_PTR;

					else if (type==TOKEN_ROM_REGION)
						curr_rom->region=BUFFER2_PTR;

					else if (type==TOKEN_ROM_OFFSET)
					{
						curr_rom->offset=strtoul(BUFFER2_PTR, NULL, 16);

						// Value may be zero so its presence needs remembering!
						curr_rom->rom_flags|=FLAG_ROM_OFFSET;
					}

					else if (type==TOKEN_ROM_DISPOSE)
						curr_rom->dispose=BUFFER2_PTR;

					else if (type==TOKEN_ROM_SOUNDONLY)
						curr_rom->soundonly=BUFFER2_PTR;
				}
			}

			if (type==TOKEN_ROM_NAME)
			{
				/* --- The current ROM must remember its name --- */

				curr_rom->name=BUFFER2_PTR;

				/* --- Ensure that status is initialised so that it can be checked easily --- */

				curr_rom->status="";

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

				else if (type==TOKEN_DISK_MD5 && dat->options->options & OPTION_MD5_CHECKSUMS)
				{
					curr_disk->md5=BUFFER2_PTR;

					/* --- Create a dummy CRC for MAMEDiff --- */

					curr_disk->crc=crc32(0, NULL, 0);
					curr_disk->crc=crc32(curr_disk->crc, curr_disk->md5, strlen(curr_disk->md5));
				}

				else if (type==TOKEN_DISK_SHA1 && dat->options->options & OPTION_SHA1_CHECKSUMS)
				{
					curr_disk->sha1=BUFFER2_PTR;

					/* --- Create a dummy CRC for MAMEDiff --- */

					curr_disk->crc=crc32(0, NULL, 0);
					curr_disk->crc=crc32(curr_disk->crc, curr_disk->sha1, strlen(curr_disk->sha1));
				}

				else if (type==TOKEN_DISK_MERGE)
					curr_disk->merge=BUFFER2_PTR;

				else if (type==TOKEN_DISK_STATUS)
					curr_disk->status=BUFFER2_PTR;

				else if (dat->options->options & OPTION_KEEP_FULL_DETAILS)
				{
					if (type==TOKEN_DISK_REGION)
						curr_disk->region=BUFFER2_PTR;

					else if (type==TOKEN_DISK_INDEX)
					{
						curr_disk->index=strtoul(BUFFER2_PTR, NULL, 16);

						// Value may be zero so its presence needs remembering!
						curr_disk->disk_flags|=FLAG_DISK_INDEX;
					}
				}
			}

			if (type==TOKEN_DISK_NAME)
			{
				/* --- The current disk must remember its name --- */

				curr_disk->name=BUFFER2_PTR;

				/* --- Ensure that status is initialised so that it can be checked easily --- */

				curr_disk->status="";

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
				/* --- The current sample must remember its name --- */

				curr_sample->name=BUFFER2_PTR;

				/* --- If this is the first sample for the current game then set up the samples pointer --- */

				if (curr_game->samples==0)
					curr_game->samples=curr_sample;

				/* --- Whatever happens, increase the sample count for the current game --- */

				curr_game->num_samples++;
			}


			/* --- Archive elements --- */

			if (curr_archive!=0 && curr_archive->name!=0)
			{
				if (type==TOKEN_ARCHIVE_NAME)
					curr_archive++;
			}

			if (type==TOKEN_ARCHIVE_NAME)
			{
				/* --- The current archive must remember its name --- */

				curr_archive->name=BUFFER2_PTR;

				/* --- If this is the first archive for the current game then set up the archives pointer --- */

				if (curr_game->archives==0)
					curr_game->archives=curr_archive;

				/* --- Whatever happens, increase the archive count for the current game --- */

				curr_game->num_archives++;
			}

			if (dat->options->options & OPTION_KEEP_FULL_DETAILS)
			{
				/* --- Biosset elements --- */

				if (curr_biosset!=0 && curr_biosset->name!=0)
				{
					if (type==TOKEN_BIOSSET_NAME)
						curr_biosset++;

					else if (type==TOKEN_BIOSSET_DESCRIPTION)
						curr_biosset->description=BUFFER2_PTR;

					else if (type==TOKEN_BIOSSET_DEFAULT)
						curr_biosset->_default=BUFFER2_PTR;
				}

				if (type==TOKEN_BIOSSET_NAME)
				{
					/* --- The current biosset must remember its name --- */

					curr_biosset->name=BUFFER2_PTR;

					/* --- If this is the first biosset for the current game then set up the biossets pointer --- */

					if (curr_game->biossets==0)
						curr_game->biossets=curr_biosset;

					/* --- Whatever happens, increase the biosset count for the current game --- */

					curr_game->num_biossets++;
				}

				/* --- Chip elements --- */

				if (curr_chip!=0 && curr_chip->type!=0)
				{
					if (type==TOKEN_CHIP_TYPE)
						curr_chip++;

					else if (type==TOKEN_CHIP_NAME)
						curr_chip->name=BUFFER2_PTR;

					else if (type==TOKEN_CHIP_SOUNDONLY)
						curr_chip->soundonly=BUFFER2_PTR;

					else if (type==TOKEN_CHIP_CLOCK)
					{
						curr_chip->clock=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_chip->chip_flags|=FLAG_CHIP_CLOCK;
					}
				}

				if (type==TOKEN_CHIP_TYPE)
				{
					/* --- The current chip must remember its type --- */

					curr_chip->type=BUFFER2_PTR;

					/* --- If this is the first chip for the current game then set up the chips pointer --- */

					if (curr_game->chips==0)
						curr_game->chips=curr_chip;

					/* --- Whatever happens, increase the chip count for the current game --- */

					curr_game->num_chips++;
				}

				/* --- Video elements --- */

				if (curr_video!=0 && curr_video->screen!=0)
				{
					if (type==TOKEN_VIDEO_SCREEN)
						curr_video++;

					else if (type==TOKEN_VIDEO_ORIENTATION)
						curr_video->orientation=BUFFER2_PTR;

					else if (type==TOKEN_VIDEO_WIDTH)
					{
						curr_video->width=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_video->video_flags|=FLAG_VIDEO_WIDTH;
					}

					else if (type==TOKEN_VIDEO_HEIGHT)
					{
						curr_video->height=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_video->video_flags|=FLAG_VIDEO_HEIGHT;
					}

					else if (type==TOKEN_VIDEO_ASPECTX)
					{
						curr_video->aspectx=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_video->video_flags|=FLAG_VIDEO_ASPECTX;
					}

					else if (type==TOKEN_VIDEO_ASPECTY)
					{
						curr_video->aspecty=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_video->video_flags|=FLAG_VIDEO_ASPECTY;
					}

					else if (type==TOKEN_VIDEO_REFRESH)
					{
						curr_video->refresh=atof(BUFFER2_PTR);

						// Value may be zero so its presence needs remembering!
						curr_video->video_flags|=FLAG_VIDEO_REFRESH;
					}
				}

				if (type==TOKEN_VIDEO_SCREEN)
				{
					/* --- The current video must remember its screen --- */

					curr_video->screen=BUFFER2_PTR;

					/* --- If this is the first video for the current game then set up the videos pointer --- */

					if (curr_game->videos==0)
						curr_game->videos=curr_video;

					/* --- Whatever happens, increase the video count for the current game --- */

					curr_game->num_videos++;
				}

				/* --- Sound elements --- */

				if (curr_sound!=0 && curr_sound->sound_flags & FLAG_SOUND_CHANNELS)
				{
					if (type==TOKEN_SOUND_CHANNELS)
						curr_sound++;
				}

				if (type==TOKEN_SOUND_CHANNELS)
				{
					/* --- The current sound must remember its channels --- */

					curr_sound->channels=strtoul(BUFFER2_PTR, NULL, 10);

					// Value may be zero so its presence needs remembering!
					curr_sound->sound_flags|=FLAG_SOUND_CHANNELS;

					/* --- If this is the first sound for the current game then set up the sounds pointer --- */

					if (curr_game->sounds==0)
						curr_game->sounds=curr_sound;

					/* --- Whatever happens, increase the sound count for the current game --- */

					curr_game->num_sounds++;
				}

				/* --- Input elements --- */

				if (curr_input!=0 && curr_input->input_flags & FLAG_INPUT_PLAYERS)
				{
					if (type==TOKEN_INPUT_PLAYERS)
						curr_input++;

					else if (type==TOKEN_INPUT_SERVICE)
						curr_input->service=BUFFER2_PTR;

					else if (type==TOKEN_INPUT_TILT)
						curr_input->tilt=BUFFER2_PTR;

					else if (type==TOKEN_INPUT_CONTROL)
						curr_input->control=BUFFER2_PTR;

					else if (type==TOKEN_INPUT_BUTTONS)
					{
						curr_input->buttons=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_input->input_flags|=FLAG_INPUT_BUTTONS;
					}

					else if (type==TOKEN_INPUT_COINS)
					{
						curr_input->coins=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_input->input_flags|=FLAG_INPUT_COINS;
					}


					else if (type==TOKEN_INPUT_DIPSWITCHES)
					{
						curr_input->dipswitches=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_input->input_flags|=FLAG_INPUT_DIPSWITCHES;
					}
				}

				if (type==TOKEN_INPUT_PLAYERS)
				{
					/* --- The current input must remember its players --- */

					curr_input->players=strtoul(BUFFER2_PTR, NULL, 10);

					// Value may be zero so its presence needs remembering!
					curr_input->input_flags|=FLAG_INPUT_PLAYERS;

					/* --- If this is the first input for the current game then set up the inputs pointer --- */

					if (curr_game->inputs==0)
						curr_game->inputs=curr_input;

					/* --- Whatever happens, increase the input count for the current game --- */

					curr_game->num_inputs++;
				}

				/* --- Dipswitch elements --- */

				if (curr_dipswitch!=0 && curr_dipswitch->name!=0)
				{
					if (type==TOKEN_DIPSWITCH_NAME)
						curr_dipswitch++;
				}

				if (type==TOKEN_DIPSWITCH_NAME)
				{
					/* --- The current dipswitch must remember its name --- */

					curr_dipswitch->name=BUFFER2_PTR;

					/* --- If this is the first dipswitch for the current game then set up the dipswitches pointer --- */

					if (curr_game->dipswitches==0)
						curr_game->dipswitches=curr_dipswitch;

					/* --- Whatever happens, increase the dipswitch count for the current game --- */

					curr_game->num_dipswitches++;
				}

				/* --- Dipvalue elements --- */

				if (curr_dipvalue!=0 && curr_dipvalue->name!=0)
				{
					if (type==TOKEN_DIPVALUE_NAME)
						curr_dipvalue++;

					else if (type==TOKEN_DIPVALUE_DEFAULT)
						curr_dipvalue->_default=BUFFER2_PTR;
				}

				if (type==TOKEN_DIPVALUE_NAME)
				{
					/* --- The current dipvalue must remember its name --- */

					curr_dipvalue->name=BUFFER2_PTR;

					/* --- If this is the first dipvalue for the current dipswitch/game then set up the dipvalues pointer --- */

					if (curr_dipswitch->dipvalues==0)
						curr_dipswitch->dipvalues=curr_dipvalue;
					if (curr_game->dipvalues==0)
						curr_game->dipvalues=curr_dipvalue;

					/* --- Whatever happens, increase the dipvalue count for the current dipswitch/game --- */

					curr_dipswitch->num_dipvalues++;
					curr_game->num_dipvalues++;
				}

				/* --- Driver elements --- */

				if (curr_driver!=0 && curr_driver->status!=0)
				{
					if (type==TOKEN_DRIVER_STATUS)
						curr_driver++;

					else if (type==TOKEN_DRIVER_EMULATION)
						curr_driver->emulation=BUFFER2_PTR;

					else if (type==TOKEN_DRIVER_COLOR)
						curr_driver->color=BUFFER2_PTR;

					else if (type==TOKEN_DRIVER_SOUND)
						curr_driver->sound=BUFFER2_PTR;

					else if (type==TOKEN_DRIVER_GRAPHIC)
						curr_driver->graphic=BUFFER2_PTR;

					else if (type==TOKEN_DRIVER_COCKTAIL)
						curr_driver->cocktail=BUFFER2_PTR;

					else if (type==TOKEN_DRIVER_PROTECTION)
						curr_driver->protection=BUFFER2_PTR;

					else if (type==TOKEN_DRIVER_PALETTESIZE)
					{
						curr_driver->palettesize=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_driver->driver_flags|=FLAG_DRIVER_PALETTESIZE;
					}

					else if (type==TOKEN_DRIVER_COLORDEEP)
					{
						curr_driver->colordeep=strtoul(BUFFER2_PTR, NULL, 10);

						// Value may be zero so its presence needs remembering!
						curr_driver->driver_flags|=FLAG_DRIVER_COLORDEEP;
					}

					else if (type==TOKEN_DRIVER_CREDITS)
						curr_driver->credits=BUFFER2_PTR;
				}

				if (type==TOKEN_DRIVER_STATUS)
				{
					/* --- The current driver must remember its status --- */

					curr_driver->status=BUFFER2_PTR;

					/* --- If this is the first driver for the current game then set up the drivers pointer --- */

					if (curr_game->drivers==0)
						curr_game->drivers=curr_driver;

					/* --- Whatever happens, increase the driver count for the current game --- */

					curr_game->num_drivers++;
				}

				/* --- Device elements --- */

				if (curr_device!=0 && curr_device->name!=0)
				{
					if (type==TOKEN_DEVICE_NAME)
						curr_device++;
				}

				if (type==TOKEN_DEVICE_NAME)
				{
					/* --- The current device must remember its name --- */

					curr_device->name=BUFFER2_PTR;

					/* --- If this is the first device for the current game then set up the devices pointer --- */

					if (curr_game->devices==0)
						curr_game->devices=curr_device;

					/* --- Whatever happens, increase the device count for the current game --- */

					curr_game->num_devices++;
				}

				/* --- Extensions elements --- */

				if (curr_extension!=0 && curr_extension->name!=0)
				{
					if (type==TOKEN_EXTENSION_NAME)
						curr_extension++;
				}

				if (type==TOKEN_EXTENSION_NAME)
				{
					/* --- The current extension must remember its name --- */

					curr_extension->name=BUFFER2_PTR;

					/* --- If this is the first extension for the current device/game then set up the extensions pointer --- */

					if (curr_device->extensions==0)
						curr_device->extensions=curr_extension;
					if (curr_game->extensions==0)
						curr_game->extensions=curr_extension;

					/* --- Whatever happens, increase the extension count for the current device/game --- */

					curr_device->num_extensions++;
					curr_game->num_extensions++;
				}
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

			/* --- Link in any comments that preceded the game --- */

			if (comments)
			{
				curr_game->comments=comments;
				curr_game->num_comments=num_comments;
				comments=0;
				num_comments=0;
			}
		}

		/* --- Comments --- */

		if (type==TOKEN_COMMENT_TEXT)
		{
			if (comments==0)
				comments=curr_comment;

			curr_comment++->text=BUFFER2_PTR;
			num_comments++;
		}

		BUFFER2_ADVANCE_LINE
	}

	/* --- Mark 'no dumps' --- */

	for (i=0; i<dat->num_roms; i++)
	{
		if (dat->roms[i].crc==0 && strcmp(dat->roms[i].status, "nodump"))
		{
			dat->roms[i].status="nodump";
			dat->roms[i].rom_fixes|=FLAG_ROM_STATUS;
		}
	}

	for (i=0; i<dat->num_disks; i++)
	{
		if (dat->disks[i].crc==0 && strcmp(dat->disks[i].status, "nodump"))
		{
			dat->disks[i].status="nodump";
			dat->disks[i].disk_fixes|=FLAG_DISK_STATUS;
		}
	}

	/* --- Override the ClrMamePro header in the dat with user parameters --- */

	if (dat->options->clrmamepro.name)
		dat->clrmamepro.name=dat->options->clrmamepro.name;
	if (dat->options->clrmamepro.description)
		dat->clrmamepro.description=dat->options->clrmamepro.description;
	if (dat->options->clrmamepro.category)
		dat->clrmamepro.category=dat->options->clrmamepro.category;
	if (dat->options->clrmamepro.version)
		dat->clrmamepro.version=dat->options->clrmamepro.version;
	if (dat->options->clrmamepro.author)
		dat->clrmamepro.author=dat->options->clrmamepro.author;
	if (dat->options->clrmamepro.forcemerging)
		dat->clrmamepro.forcemerging=dat->options->clrmamepro.forcemerging;
	if (dat->options->clrmamepro.forcezipping)
		dat->clrmamepro.forcezipping=dat->options->clrmamepro.forcezipping;

	/* --- Copy merge preferences between ClrMamePro and RomCenter headers --- */

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

			if (curr_disk->merge)
			{
				strcpy(TOKEN, curr_disk->merge);
				LOWER(TOKEN);
				if (strcmp(curr_disk->merge, TOKEN))
				{
					strcpy(curr_disk->merge, TOKEN);
					curr_disk->disk_fixes|=FLAG_DISK_MERGE;
				}
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
			if (curr_game!=orig_game)
				memcpy(curr_game, orig_game, sizeof(struct game));

			curr_game++;
		}
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
		curr_game->match=0;

	return(errflg);
}

int game_sourcefile_selections(struct dat *dat)
{
	struct game_idx *curr_game_name_idx;
	struct game_idx *game_match;
	struct game *orig_game=0;
	struct game *curr_game=0;
	struct game *curr_parent;
	struct st_idx *st_idx;
	uint32_t num_games=dat->num_games;
	uint32_t i, match_value=1;

	int errflg=0;

	/* --- Need a game name index to run 'single name' --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Creating temporary game name index...\n");
	}

	curr_game_name_idx=dat->game_name_idx;
	
	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (dat->options->options & OPTION_INVERT_SELECTION)
			curr_game->match=1;
		curr_game_name_idx++->game=curr_game;
	}

	qsort(dat->game_name_idx, dat->num_games, sizeof(struct game_idx), game_name_idx_sort_function);

	/* --- Now the index is available, run 'single game' --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Single game...\n");
	}

	/* --- Flag the games to keep --- */

	if (dat->options->options & OPTION_INVERT_SELECTION)
		match_value=0;

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		/* --- sourcefile check is simple, no iterations need to be handled --- */

		if (dat->options->options & OPTION_SOURCEFILE_SELECTION && curr_game->sourcefile)
		{
			if ((st_idx=bsearch((void *)curr_game->sourcefile, dat->options->sourcefile_selections, dat->options->num_sourcefile_selections, sizeof(struct st_idx), find_st))!=0)
			{
				curr_game->match=match_value;
				st_idx->flags|=FLAG_STRING_INDEX_USED;
			}
		}

		/* --- game names are less simple, iterations need to be handled --- */

		if (dat->options->options & OPTION_GAME_SELECTION)
		{
			if ((st_idx=bsearch((void *)curr_game->name, dat->options->game_selections, dat->options->num_game_selections, sizeof(struct st_idx), find_st))!=0)
			{
				curr_game->match=match_value;
				st_idx->flags|=FLAG_STRING_INDEX_USED;
			}

			if (dat->options->options & OPTION_CLONE_SELECTION)
			{
				if (curr_game->cloneof &&
					(st_idx=bsearch((void *)curr_game->cloneof, dat->options->game_selections, dat->options->num_game_selections, sizeof(struct st_idx), find_st))!=0)
				{
					curr_game->match=match_value;
					st_idx->flags|=FLAG_STRING_INDEX_USED;
				}
				if (curr_game->romof &&
					(st_idx=bsearch((void *)curr_game->romof, dat->options->game_selections, dat->options->num_game_selections, sizeof(struct st_idx), find_st))!=0)
				{
					curr_game->match=match_value;
					st_idx->flags|=FLAG_STRING_INDEX_USED;
				}

				/* --- Support clones of clones (i.e. work up the tree to find the match) --- */

				if (curr_game->match!=match_value && curr_game->cloneof && (game_match=bsearch((void *)curr_game->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
					curr_parent=game_match->game;
				else
					curr_parent=0;

				while (curr_game->match!=match_value && curr_parent)
				{
					if (curr_parent->cloneof &&
						(st_idx=bsearch((void *)curr_parent->cloneof, dat->options->game_selections, dat->options->num_game_selections, sizeof(struct st_idx), find_st))!=0)
					{
						curr_game->match=match_value;
						st_idx->flags|=FLAG_STRING_INDEX_USED;
					}

					if (curr_parent->romof &&
						(st_idx=bsearch((void *)curr_parent->romof, dat->options->game_selections, dat->options->num_game_selections, sizeof(struct st_idx), find_st))!=0)
					{
						curr_game->match=match_value;
						st_idx->flags|=FLAG_STRING_INDEX_USED;
					}

					if (curr_game->match!=match_value && curr_parent->cloneof && (game_match=bsearch((void *)curr_parent->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
						curr_parent=game_match->game;
					else
						curr_parent=0;
				}
			}
		}
	}

	/* --- Do the memory manipulation to remove unneeded games --- */

	for (i=0, orig_game=dat->games, curr_game=dat->games; i<num_games; i++, orig_game++)
	{
		if (orig_game->match==0)
		{
			dat->num_games-=1;
		}
		else
		{
			if (curr_game!=orig_game)
				memcpy(curr_game, orig_game, sizeof(struct game));

			curr_game++;
		}
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
		curr_game->match=0;

	return(errflg);
}

int add_missing_info(struct dat *dat)
{
	struct game *curr_game=0;
	struct rom *curr_rom=0;
	struct game_idx *game_match=0;
	struct rom_idx *rom_match=0;
	uint32_t i, j;

	int errflg=0;

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Adding missing information...\n");
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (dat->dat_flags & FLAG_DAT_FULL_MERGING && curr_game->cloneof)
			game_match=bsearch((void *)curr_game->cloneof, dat->options->info->game_name_idx, dat->options->info->num_games, sizeof(struct game_idx), find_game_by_name);
		else
			game_match=bsearch((void *)curr_game->name, dat->options->info->game_name_idx, dat->options->info->num_games, sizeof(struct game_idx), find_game_by_name);

		if (game_match)
		{
			if (game_match->game->cloneof && curr_game->cloneof==0)
			{
				curr_game->game_fixes|=FLAG_GAME_CLONEOF;
				curr_game->cloneof=game_match->game->cloneof;
			}

			if (game_match->game->romof && curr_game->romof==0)
			{
				curr_game->game_fixes|=FLAG_GAME_ROMOF;
				curr_game->romof=game_match->game->romof;
			}

			if (game_match->game->sampleof && curr_game->sampleof==0)
			{
				curr_game->game_fixes|=FLAG_GAME_SAMPLEOF;
				curr_game->sampleof=game_match->game->sampleof;
			}

			for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
			{
				rom_match=bsearch((void *)curr_rom->name, game_match->game->rom_name_idx, game_match->game->num_roms, sizeof(struct rom_idx), find_rom_by_name);

				if (rom_match)
				{
					if (rom_match->rom->crc==curr_rom->crc || rom_match->rom->crc==~curr_rom->crc)
					{
						if (rom_match->rom->size!=curr_rom->size)
						{
							curr_rom->rom_fixes|=FLAG_ROM_SIZE;
							curr_rom->size=rom_match->rom->size;
						}

						if (rom_match->rom->crc!=curr_rom->crc)
						{
							curr_rom->rom_fixes|=FLAG_ROM_CRC;
							curr_rom->crc=rom_match->rom->crc;

							if (strcmp(curr_rom->status, "baddump"))
							{
								curr_rom->status="baddump";
								curr_rom->rom_fixes|=FLAG_ROM_STATUS;
							}
						}

						if ((rom_match->rom->md5 && curr_rom->md5==0) ||
							(rom_match->rom->md5 && curr_rom->md5 &&
							strcmp(rom_match->rom->md5, curr_rom->md5)))
						{
							curr_rom->rom_fixes|=FLAG_ROM_MD5;
							curr_rom->md5=rom_match->rom->md5;
						}

						if ((rom_match->rom->sha1 && curr_rom->sha1==0) ||
							(rom_match->rom->sha1 && curr_rom->sha1 &&
							strcmp(rom_match->rom->sha1, curr_rom->sha1)))
						{
							curr_rom->rom_fixes|=FLAG_ROM_SHA1;
							curr_rom->sha1=rom_match->rom->sha1;
						}
					}
				}
			}
		}
	}

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

int fix_merging_phase_1(struct dat *dat)
{
	struct game *curr_game=0;
	struct game *parent_game=0;
	struct game **game_stack=0;
	struct game_idx *curr_game_name_idx=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;
	uint32_t i, j, k, stack_idx;

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

		/* --- Game must not reference itself in romof of cloneof --- */

		if (curr_game->cloneof && !strcmp(curr_game->name, curr_game->cloneof))
		{
			curr_game->cloneof=0;
			curr_game->game_fixes|=FLAG_GAME_CLONEOF;
			curr_game->game_flags&=~FLAG_GAME_CLONEOF;
		}

		if (curr_game->romof && !strcmp(curr_game->name, curr_game->romof))
		{
			curr_game->romof=0;
			curr_game->game_fixes|=FLAG_GAME_ROMOF;
			curr_game->game_flags&=~FLAG_GAME_ROMOF;
		}

		/* --- Fix romof --- */

		if (curr_game->romof)
		{
			if (curr_game->cloneof && strcmp(curr_game->romof, curr_game->cloneof))
			{
				curr_game->romof=curr_game->cloneof;
				curr_game->game_fixes|=FLAG_GAME_ROMOF;
			}

			if ((game_match=bsearch((void *)curr_game->romof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))==0)
			{
				curr_game->romof=0;
				curr_game->game_fixes|=FLAG_GAME_ROMOF;
				curr_game->game_flags&=~FLAG_GAME_ROMOF;
			}
			else
			{
				curr_game->game_romof=game_match->game;
			}
		}

		/* --- Fix cloneof --- */

		if (curr_game->cloneof)
		{
			if ((game_match=bsearch((void *)curr_game->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))==0)
			{
				curr_game->cloneof=0;
				curr_game->game_fixes|=FLAG_GAME_CLONEOF;
				curr_game->game_flags&=~FLAG_GAME_CLONEOF;
			}
			else
			{
				curr_game->game_cloneof=game_match->game;

				if (!curr_game->romof)
				{
					curr_game->romof=curr_game->cloneof;
					curr_game->game_romof=curr_game->game_cloneof;
					curr_game->game_fixes|=FLAG_GAME_ROMOF;
				}
			}
		}

		/* --- Fix sampleof --- */

		if (curr_game->sampleof)
		{
			if ((game_match=bsearch((void *)curr_game->sampleof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))==0)
			{
				curr_game->sampleof=0;
				curr_game->game_fixes|=FLAG_GAME_SAMPLEOF;
				curr_game->game_flags&=~FLAG_GAME_SAMPLEOF;
			}
			else
			{
				curr_game->game_sampleof=game_match->game;
			}
		}
	}

	/* --- Fix clones of clones --- */

	STRUCT_CALLOC(game_stack, dat->num_games, sizeof(struct game *))

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		stack_idx=0;

		game_stack[stack_idx++]=curr_game;

		if (curr_game->game_cloneof) // i.e. curr_game is a clone
		{
			if (curr_game->game_cloneof->game_cloneof) // i.e. curr_game is a clone of a clone
			{
				/* --- Walk through the parents --- */

				parent_game=curr_game->game_cloneof;

				while (parent_game->game_cloneof)
				{
					game_stack[stack_idx++]=parent_game;

					/* --- Detect infinite loops and fix them! --- */

					for (j=0; j<stack_idx; j++)
					{
						if (parent_game->game_cloneof==game_stack[j])
						{
							parent_game->cloneof=0;
							parent_game->game_cloneof=0;
							parent_game->game_fixes|=FLAG_GAME_CLONEOF;

							parent_game->romof=0;
							parent_game->game_romof=0;
							parent_game->game_fixes|=FLAG_GAME_ROMOF;
						}
					}

					if (parent_game->game_cloneof)
						parent_game=parent_game->game_cloneof;
				}

				/* --- Only if the cloneof has changed (may not change due to infinite loops) --- */

				if (parent_game!=curr_game->game_cloneof)
				{
					if (curr_game->romof && !strcmp(curr_game->romof, curr_game->cloneof))
					{
						curr_game->romof=parent_game->name;
						curr_game->game_romof=parent_game;
						curr_game->game_fixes|=FLAG_GAME_ROMOF;
					}

					curr_game->cloneof=parent_game->name;
					curr_game->game_cloneof=parent_game;
					curr_game->game_fixes|=FLAG_GAME_CLONEOF;
					curr_game->game_fixes|=FLAG_GAME_CLONEOFCLONE;
				}
			}
		}
	}

	FREE(game_stack)

	/* --- First ROM pass corrects merge names and pushes CRCs upwards --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			struct game *game_romof=curr_game->game_romof;
			int merged=0;

			while (game_romof)
			{
				struct rom *merge_rom;

				for (k=0, merge_rom=game_romof->roms; k<game_romof->num_roms; k++, merge_rom++)
				{
					if (!strcmp(curr_rom->name, merge_rom->name) &&
						(curr_rom->crc==merge_rom->crc || curr_rom->crc==~merge_rom->crc || !merge_rom->crc || !curr_rom->crc ))
					{
						if (!curr_rom->merge || strcmp(curr_rom->merge, curr_rom->name))
						{
							curr_rom->merge=curr_rom->name;
							curr_rom->rom_fixes|=FLAG_ROM_MERGE;
						}

						if (curr_rom->crc && !merge_rom->crc)
						{
							merge_rom->crc=curr_rom->crc;
							merge_rom->rom_fixes|=FLAG_ROM_CRC;

							if (strcmp(merge_rom->status, "baddump"))
							{
								merge_rom->status="baddump";
								merge_rom->rom_fixes|=FLAG_ROM_STATUS;
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

						merged++;
					}
				}

				game_romof=game_romof->game_romof;
			}

			if (!merged && curr_rom->merge)
			{
				curr_rom->merge=0;
				curr_rom->rom_fixes|=FLAG_ROM_MERGE;
				curr_rom->rom_flags&=~FLAG_ROM_MERGE;
			}
		}
	}

	/* --- Second ROM pass pushes CRCs downwards --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			struct game *game_romof=curr_game->game_romof;

			while (curr_rom->merge && game_romof)
			{
				struct rom *merge_rom;

				for (k=0, merge_rom=game_romof->roms; k<game_romof->num_roms; k++, merge_rom++)
				{
					if (!strcmp(curr_rom->name, merge_rom->name) &&
						(curr_rom->crc==merge_rom->crc || curr_rom->crc==~merge_rom->crc || !merge_rom->crc || !curr_rom->crc ))
					{
						if (!curr_rom->crc && merge_rom->crc)
						{
							curr_rom->crc=merge_rom->crc;
							curr_rom->rom_fixes|=FLAG_ROM_CRC;

							if (strcmp(curr_rom->status, "baddump"))
							{
								curr_rom->status="baddump";
								curr_rom->rom_fixes|=FLAG_ROM_STATUS;
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

				game_romof=game_romof->game_romof;
			}
		}
	}

	/* --- First disk pass corrects merge names and pushes CRCs upwards --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			struct game *game_romof=curr_game->game_romof;
			int merged=0;

			while (game_romof)
			{
				struct disk *merge_disk;

				for (k=0, merge_disk=game_romof->disks; k<game_romof->num_disks; k++, merge_disk++)
				{
					if (!strcmp(curr_disk->name, merge_disk->name) &&
						(curr_disk->crc==merge_disk->crc || curr_disk->crc==~merge_disk->crc || !merge_disk->crc || !curr_disk->crc ))
					{
						if (!curr_disk->merge || strcmp(curr_disk->merge, curr_disk->name))
						{
							curr_disk->merge=curr_disk->name;
							curr_disk->disk_fixes|=FLAG_DISK_MERGE;
						}

						if (curr_disk->crc && !merge_disk->crc)
						{
							merge_disk->crc=curr_disk->crc;

							if (strcmp(merge_disk->status, "baddump"))
							{
								merge_disk->status="baddump";
								merge_disk->disk_fixes|=FLAG_DISK_STATUS;
							}
						}

						if (curr_disk->sha1 && !merge_disk->sha1)
						{
							merge_disk->sha1=curr_disk->sha1;
							merge_disk->disk_fixes|=FLAG_DISK_SHA1;
						}

						if (curr_disk->md5 && !merge_disk->md5)
						{
							merge_disk->md5=curr_disk->md5;
							merge_disk->disk_fixes|=FLAG_DISK_MD5;
						}

						merged++;
					}
				}

				game_romof=game_romof->game_romof;
			}

			if (!merged && curr_disk->merge)
			{
				curr_disk->merge=0;
				curr_disk->disk_fixes|=FLAG_DISK_MERGE;
				curr_disk->disk_flags&=~FLAG_DISK_MERGE;
			}
		}
	}

	/* --- Second disk pass pushes CRCs downwards --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			struct game *game_romof=curr_game->game_romof;

			while (curr_disk->merge && game_romof)
			{
				struct disk *merge_disk;

				for (k=0, merge_disk=game_romof->disks; k<game_romof->num_disks; k++, merge_disk++)
				{
					if (!strcmp(curr_disk->name, merge_disk->name) &&
						(curr_disk->crc==merge_disk->crc || curr_disk->crc==~merge_disk->crc || !merge_disk->crc || !curr_disk->crc ))
					{
						if (!curr_disk->crc && merge_disk->crc)
						{
							curr_disk->crc=merge_disk->crc;

							if (strcmp(curr_disk->status, "baddump"))
							{
								curr_disk->status="baddump";
								curr_disk->disk_fixes|=FLAG_DISK_STATUS;
							}
						}

						if (!curr_disk->sha1 && merge_disk->sha1)
						{
							curr_disk->sha1=merge_disk->sha1;
							curr_disk->disk_fixes|=FLAG_DISK_SHA1;
						}

						if (!curr_disk->md5 && merge_disk->md5)
						{
							curr_disk->md5=merge_disk->md5;
							curr_disk->disk_fixes|=FLAG_DISK_MD5;
						}
					}
				}

				game_romof=game_romof->game_romof;
			}
		}
	}

	/* --- Work out merging of samples --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
		{
			struct game *game_sampleof=curr_game->game_sampleof;

			while (game_sampleof)
			{
				struct sample *merge_sample;

				for (k=0, merge_sample=game_sampleof->samples; k<game_sampleof->num_samples; k++, merge_sample++)
				{
					if (!strcmp(curr_sample->name, merge_sample->name))
					{
						if (!curr_sample->merge || strcmp(curr_sample->merge, curr_sample->name))
						{
							curr_sample->merge=curr_sample->name;
						}
					}
				}

				game_sampleof=game_sampleof->game_sampleof;
			}
		}
	}

	return(errflg);
}

int identify_parents(struct dat *dat)
{
	struct game *curr_game=0;
	struct game_idx *curr_game_name_idx=0;
	uint32_t i;

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
		printf("Identifying parents...\n");
	}

	/* --- Fix game level details first (cloneof/romof/sampleof) --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		struct game_idx *game_match;

		/* --- Process romof --- */

		if (curr_game->romof)
		{
			if ((game_match=bsearch((void *)curr_game->romof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
			{
				curr_game->game_romof=game_match->game;
			}
		}

		/* --- Process cloneof --- */

		if (curr_game->cloneof)
		{
			if ((game_match=bsearch((void *)curr_game->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
			{
				curr_game->game_cloneof=game_match->game;
				curr_game->game_cloneof->num_clones++;
			}
		}

		/* --- process sampleof --- */

		if (curr_game->sampleof)
		{
			if ((game_match=bsearch((void *)curr_game->sampleof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
			{
				curr_game->game_sampleof=game_match->game;
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
	struct comment *curr_comment=0;
	struct biosset *curr_biosset=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;
	struct chip *curr_chip=0;
	struct video *curr_video=0;
	struct sound *curr_sound=0;
	struct input *curr_input=0;
	struct dipswitch *curr_dipswitch=0;
	struct dipvalue *curr_dipvalue=0;
	struct driver *curr_driver=0;
	struct device *curr_device=0;
	struct extension *curr_extension=0;
	struct archive *curr_archive=0;
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

		if (curr_game->sourcefile)
			curr_game->game_flags|=FLAG_GAME_SOURCEFILE;

		if (curr_game->cloneof)
			curr_game->game_flags|=FLAG_GAME_CLONEOF;

		if (curr_game->romof)
			curr_game->game_flags|=FLAG_GAME_ROMOF;

		if (curr_game->sampleof)
			curr_game->game_flags|=FLAG_GAME_SAMPLEOF;

		if (curr_game->description)
			curr_game->game_flags|=FLAG_GAME_DESCRIPTION;

		if (curr_game->year)
			curr_game->game_flags|=FLAG_GAME_YEAR;

		if (curr_game->manufacturer)
			curr_game->game_flags|=FLAG_GAME_MANUFACTURER;

		if (curr_game->history)
			curr_game->game_flags|=FLAG_GAME_HISTORY;

		if (curr_game->rebuildto)
			curr_game->game_flags|=FLAG_GAME_REBUILDTO;

		if (curr_game->board)
			curr_game->game_flags|=FLAG_GAME_BOARD;

		for (j=0, curr_comment=curr_game->comments; j<curr_game->num_comments; j++, curr_comment++)
		{
			if (curr_comment->text)
				curr_comment->comment_flags|=FLAG_COMMENT_TEXT;

			curr_game->comment_flags|=curr_comment->comment_flags;
		}

		for (j=0, curr_biosset=curr_game->biossets; j<curr_game->num_biossets; j++, curr_biosset++)
		{
			if (curr_biosset->name)
				curr_biosset->biosset_flags|=FLAG_BIOSSET_NAME;

			if (curr_biosset->description)
				curr_biosset->biosset_flags|=FLAG_BIOSSET_DESCRIPTION;

			if (curr_biosset->_default)
				curr_biosset->biosset_flags|=FLAG_BIOSSET_DEFAULT;

			curr_game->biosset_flags|=curr_biosset->biosset_flags;
		}

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			if (curr_rom->name)
				curr_rom->rom_flags|=FLAG_ROM_NAME;

			if (curr_rom->bios)
				curr_rom->rom_flags|=FLAG_ROM_BIOS;

			if (curr_rom->size)
				curr_rom->rom_flags|=FLAG_ROM_SIZE;

			if (curr_rom->crc)
				curr_rom->rom_flags|=FLAG_ROM_CRC;

			if (curr_rom->md5)
				curr_rom->rom_flags|=FLAG_ROM_MD5;

			if (curr_rom->sha1)
				curr_rom->rom_flags|=FLAG_ROM_SHA1;

			if (curr_rom->merge)
				curr_rom->rom_flags|=FLAG_ROM_MERGE;

			if (curr_rom->region)
				curr_rom->rom_flags|=FLAG_ROM_REGION;

			if (curr_rom->offset)
				curr_rom->rom_flags|=FLAG_ROM_OFFSET;

			if (strcmp(curr_rom->status, ""))
				curr_rom->rom_flags|=FLAG_ROM_STATUS;
			else
				curr_rom->rom_flags&=~FLAG_ROM_STATUS;

			if (curr_rom->dispose)
				curr_rom->rom_flags|=FLAG_ROM_DISPOSE;

			if (curr_rom->soundonly)
				curr_rom->rom_flags|=FLAG_ROM_SOUNDONLY;

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

			if (curr_disk->merge)
				curr_disk->disk_flags|=FLAG_DISK_MERGE;

			if (curr_disk->region)
				curr_disk->disk_flags|=FLAG_DISK_REGION;

			if (curr_disk->index)
				curr_disk->disk_flags|=FLAG_DISK_INDEX;

			if (strcmp(curr_disk->status, ""))
				curr_disk->disk_flags|=FLAG_DISK_STATUS;
			else
				curr_disk->disk_flags&=~FLAG_DISK_STATUS;

			curr_game->disk_flags|=curr_disk->disk_flags;
		}

		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
		{
			if (curr_sample->name)
				curr_sample->sample_flags|=FLAG_SAMPLE_NAME;

			curr_game->sample_flags|=curr_sample->sample_flags;
		}

		for (j=0, curr_chip=curr_game->chips; j<curr_game->num_chips; j++, curr_chip++)
		{
			if (curr_chip->name)
				curr_chip->chip_flags|=FLAG_CHIP_NAME;

			if (curr_chip->type)
				curr_chip->chip_flags|=FLAG_CHIP_TYPE;

			if (curr_chip->soundonly)
				curr_chip->chip_flags|=FLAG_CHIP_SOUNDONLY;

			if (curr_chip->clock)
				curr_chip->chip_flags|=FLAG_CHIP_CLOCK;

			curr_game->chip_flags|=curr_chip->chip_flags;
		}

		for (j=0, curr_video=curr_game->videos; j<curr_game->num_videos; j++, curr_video++)
		{
			if (curr_video->screen)
				curr_video->video_flags|=FLAG_VIDEO_SCREEN;

			if (curr_video->orientation)
				curr_video->video_flags|=FLAG_VIDEO_ORIENTATION;

			if (curr_video->width)
				curr_video->video_flags|=FLAG_VIDEO_WIDTH;

			if (curr_video->height)
				curr_video->video_flags|=FLAG_VIDEO_HEIGHT;

			if (curr_video->aspectx)
				curr_video->video_flags|=FLAG_VIDEO_ASPECTX;

			if (curr_video->aspecty)
				curr_video->video_flags|=FLAG_VIDEO_ASPECTY;

			if (curr_video->refresh)
				curr_video->video_flags|=FLAG_VIDEO_REFRESH;

			curr_game->video_flags|=curr_video->video_flags;
		}

		for (j=0, curr_sound=curr_game->sounds; j<curr_game->num_sounds; j++, curr_sound++)
		{
			if (curr_sound->channels)
				curr_sound->sound_flags|=FLAG_SOUND_CHANNELS;

			curr_game->sound_flags|=curr_sound->sound_flags;
		}

		for (j=0, curr_input=curr_game->inputs; j<curr_game->num_inputs; j++, curr_input++)
		{
			if (curr_input->service)
				curr_input->input_flags|=FLAG_INPUT_SERVICE;

			if (curr_input->tilt)
				curr_input->input_flags|=FLAG_INPUT_TILT;

			if (curr_input->players)
				curr_input->input_flags|=FLAG_INPUT_PLAYERS;

			if (curr_input->control)
				curr_input->input_flags|=FLAG_INPUT_CONTROL;

			if (curr_input->buttons)
				curr_input->input_flags|=FLAG_INPUT_BUTTONS;

			if (curr_input->coins)
				curr_input->input_flags|=FLAG_INPUT_COINS;

			if (curr_input->dipswitches)
				curr_input->input_flags|=FLAG_INPUT_DIPSWITCHES;

			curr_game->input_flags|=curr_input->input_flags;
		}

		for (j=0, curr_dipswitch=curr_game->dipswitches; j<curr_game->num_dipswitches; j++, curr_dipswitch++)
		{
			if (curr_dipswitch->name)
				curr_dipswitch->dipswitch_flags|=FLAG_DIPSWITCH_NAME;

			curr_game->dipswitch_flags|=curr_dipswitch->dipswitch_flags;
		}

		for (j=0, curr_dipvalue=curr_game->dipvalues; j<curr_game->num_dipvalues; j++, curr_dipvalue++)
		{
			if (curr_dipvalue->name)
				curr_dipvalue->dipvalue_flags|=FLAG_DIPVALUE_NAME;

			if (curr_dipvalue->_default)
				curr_dipvalue->dipvalue_flags|=FLAG_DIPVALUE_DEFAULT;

			curr_game->dipvalue_flags|=curr_dipvalue->dipvalue_flags;
		}

		for (j=0, curr_driver=curr_game->drivers; j<curr_game->num_drivers; j++, curr_driver++)
		{
			if (curr_driver->status)
				curr_driver->driver_flags|=FLAG_DRIVER_STATUS;

			if (curr_driver->emulation)
				curr_driver->driver_flags|=FLAG_DRIVER_EMULATION;

			if (curr_driver->color)
				curr_driver->driver_flags|=FLAG_DRIVER_COLOR;

			if (curr_driver->sound)
				curr_driver->driver_flags|=FLAG_DRIVER_SOUND;

			if (curr_driver->graphic)
				curr_driver->driver_flags|=FLAG_DRIVER_GRAPHIC;

			if (curr_driver->cocktail)
				curr_driver->driver_flags|=FLAG_DRIVER_COCKTAIL;

			if (curr_driver->protection)
				curr_driver->driver_flags|=FLAG_DRIVER_PROTECTION;

			if (curr_driver->palettesize)
				curr_driver->driver_flags|=FLAG_DRIVER_PALETTESIZE;

			if (curr_driver->colordeep)
				curr_driver->driver_flags|=FLAG_DRIVER_COLORDEEP;

			if (curr_driver->credits)
				curr_driver->driver_flags|=FLAG_DRIVER_CREDITS;

			curr_game->driver_flags|=curr_driver->driver_flags;
		}

		for (j=0, curr_device=curr_game->devices; j<curr_game->num_devices; j++, curr_device++)
		{
			if (curr_device->name)
				curr_device->device_flags|=FLAG_DEVICE_NAME;

			curr_game->device_flags|=curr_device->device_flags;
		}

		for (j=0, curr_extension=curr_game->extensions; j<curr_game->num_extensions; j++, curr_extension++)
		{
			if (curr_extension->name)
				curr_extension->extension_flags|=FLAG_EXTENSION_NAME;

			curr_game->extension_flags|=curr_extension->extension_flags;
		}

		for (j=0, curr_archive=curr_game->archives; j<curr_game->num_archives; j++, curr_archive++)
		{
			if (curr_archive->name)
				curr_archive->archive_flags|=FLAG_ARCHIVE_NAME;

			curr_game->archive_flags|=curr_archive->archive_flags;
		}

		dat->game_flags|=curr_game->game_flags;
		dat->comment_flags|=curr_game->comment_flags;
		dat->biosset_flags|=curr_game->biosset_flags;
		dat->rom_flags|=curr_game->rom_flags;
		dat->disk_flags|=curr_game->disk_flags;
		dat->sample_flags|=curr_game->sample_flags;
		dat->chip_flags|=curr_game->chip_flags;
		dat->video_flags|=curr_game->video_flags;
		dat->sound_flags|=curr_game->sound_flags;
		dat->input_flags|=curr_game->input_flags;
		dat->dipswitch_flags|=curr_game->dipswitch_flags;
		dat->dipvalue_flags|=curr_game->dipvalue_flags;
		dat->driver_flags|=curr_game->driver_flags;
		dat->device_flags|=curr_game->device_flags;
		dat->extension_flags|=curr_game->extension_flags;
		dat->archive_flags|=curr_game->archive_flags;

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
		printf("Comment flags=%04x\n", dat->comment_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Biosset flags=%04x\n", dat->biosset_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("ROM flags=%04x\n", dat->rom_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Disk flags=%02x\n", dat->disk_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sample flags=%02x\n", dat->sample_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Chip flags=%02x\n", dat->chip_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Video flags=%02x\n", dat->video_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sound flags=%02x\n", dat->sound_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Input flags=%02x\n", dat->input_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Dipswitch flags=%02x\n", dat->dipswitch_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Dipvalue flags=%02x\n", dat->dipvalue_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Driver flags=%02x\n", dat->driver_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Device flags=%02x\n", dat->device_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Extension flags=%02x\n", dat->extension_flags);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Archive flags=%02x\n", dat->archive_flags);
	}

	return(errflg);
}

int fix_merging_phase_2(struct dat *dat)
{
	int i, j;

	int errflg=0;

	/* --- Identify CRC conflicts and do final bit of 'fix merging' --- */

	for (i=0; i<dat->num_roms; i++)
	{
		for (j=i+1; j<dat->num_roms && !strcmp(dat->rom_name_idx[i].rom->name, dat->rom_name_idx[j].rom->name); j++)
		{
			if ((dat->rom_name_idx[i].rom->game->name && dat->rom_name_idx[j].rom->game->name &&
				!strcmp(dat->rom_name_idx[i].rom->game->name, dat->rom_name_idx[j].rom->game->name)) ||
				(dat->rom_name_idx[i].rom->game->name && dat->rom_name_idx[j].rom->game->cloneof &&
				!strcmp(dat->rom_name_idx[i].rom->game->name, dat->rom_name_idx[j].rom->game->cloneof)) ||
				(dat->rom_name_idx[i].rom->game->cloneof && dat->rom_name_idx[j].rom->game->name &&
				!strcmp(dat->rom_name_idx[i].rom->game->cloneof, dat->rom_name_idx[j].rom->game->name)) ||
				(dat->rom_name_idx[i].rom->game->cloneof && dat->rom_name_idx[j].rom->game->cloneof &&
				!strcmp(dat->rom_name_idx[i].rom->game->cloneof, dat->rom_name_idx[j].rom->game->cloneof)))
			{
				if (dat->rom_name_idx[i].rom->crc && !dat->rom_name_idx[j].rom->crc)
				{
					dat->rom_name_idx[j].rom->crc=dat->rom_name_idx[i].rom->crc;
					dat->rom_name_idx[j].rom->rom_fixes|=FLAG_ROM_CRC;
					dat->rom_name_idx[j].rom->rom_flags|=FLAG_ROM_CRC;

					if (strcmp(dat->rom_name_idx[j].rom->status, "baddump"))
					{
						dat->rom_name_idx[j].rom->status="baddump";
						dat->rom_name_idx[j].rom->rom_fixes|=FLAG_ROM_STATUS;
					}
				}
				else if (!dat->rom_name_idx[i].rom->crc && dat->rom_name_idx[j].rom->crc)
				{
					dat->rom_name_idx[i].rom->crc=dat->rom_name_idx[j].rom->crc;
					dat->rom_name_idx[i].rom->rom_fixes|=FLAG_ROM_CRC;
					dat->rom_name_idx[i].rom->rom_flags|=FLAG_ROM_CRC;

					if (strcmp(dat->rom_name_idx[i].rom->status, "baddump"))
					{
						dat->rom_name_idx[i].rom->status="baddump";
						dat->rom_name_idx[i].rom->rom_fixes|=FLAG_ROM_STATUS;
					}
				}
				else if (dat->rom_name_idx[i].rom->crc != dat->rom_name_idx[j].rom->crc)
				{
					dat->rom_name_idx[i].rom->rom_warnings|=FLAG_ROM_CRC_CONFLICT;
					dat->rom_name_idx[j].rom->rom_warnings|=FLAG_ROM_CRC_CONFLICT;
				}

				if (!(dat->rom_name_idx[i].rom->rom_warnings & FLAG_ROM_CRC_CONFLICT) &&
					!(dat->rom_name_idx[j].rom->rom_warnings & FLAG_ROM_CRC_CONFLICT))
				{
					if (dat->rom_name_idx[i].rom->sha1 && !dat->rom_name_idx[j].rom->sha1)
					{
						dat->rom_name_idx[j].rom->sha1=dat->rom_name_idx[i].rom->sha1;
						dat->rom_name_idx[j].rom->rom_fixes|=FLAG_ROM_SHA1;
						dat->rom_name_idx[j].rom->rom_flags|=FLAG_ROM_SHA1;
					}
					else if (!dat->rom_name_idx[i].rom->sha1 && dat->rom_name_idx[j].rom->sha1)
					{
						dat->rom_name_idx[i].rom->sha1=dat->rom_name_idx[j].rom->sha1;
						dat->rom_name_idx[i].rom->rom_fixes|=FLAG_ROM_SHA1;
						dat->rom_name_idx[i].rom->rom_flags|=FLAG_ROM_SHA1;
					}

					if (dat->rom_name_idx[i].rom->md5 && !dat->rom_name_idx[j].rom->md5)
					{
						dat->rom_name_idx[j].rom->md5=dat->rom_name_idx[i].rom->md5;
						dat->rom_name_idx[j].rom->rom_fixes|=FLAG_ROM_MD5;
						dat->rom_name_idx[j].rom->rom_flags|=FLAG_ROM_MD5;
					}
					else if (!dat->rom_name_idx[i].rom->md5 && dat->rom_name_idx[j].rom->md5)
					{
						dat->rom_name_idx[i].rom->md5=dat->rom_name_idx[j].rom->md5;
						dat->rom_name_idx[i].rom->rom_fixes|=FLAG_ROM_MD5;
						dat->rom_name_idx[i].rom->rom_flags|=FLAG_ROM_MD5;
					}
				}

				if (dat->rom_name_idx[i].rom->size != dat->rom_name_idx[j].rom->size)
				{
					dat->rom_name_idx[i].rom->rom_warnings|=FLAG_ROM_SIZE_CONFLICT;
					dat->rom_name_idx[j].rom->rom_warnings|=FLAG_ROM_SIZE_CONFLICT;
				}

				if (dat->rom_name_idx[i].rom->sha1 && dat->rom_name_idx[j].rom->sha1 &&
					strcmp(dat->rom_name_idx[i].rom->sha1, dat->rom_name_idx[j].rom->sha1))
				{
					dat->rom_name_idx[i].rom->rom_warnings|=FLAG_ROM_SHA1_MD5_CONFLICT;
					dat->rom_name_idx[j].rom->rom_warnings|=FLAG_ROM_SHA1_MD5_CONFLICT;
				}

				if (dat->rom_name_idx[i].rom->md5 && dat->rom_name_idx[j].rom->md5 &&
					strcmp(dat->rom_name_idx[i].rom->md5, dat->rom_name_idx[j].rom->md5))
				{
					dat->rom_name_idx[i].rom->rom_warnings|=FLAG_ROM_SHA1_MD5_CONFLICT;
					dat->rom_name_idx[j].rom->rom_warnings|=FLAG_ROM_SHA1_MD5_CONFLICT;
				}
			}
		}
	}

	for (i=0; i<dat->num_disks; i++)
	{
		for (j=i+1; j<dat->num_disks && !strcmp(dat->disk_name_idx[i].disk->name, dat->disk_name_idx[j].disk->name); j++)
		{
			if ((dat->disk_name_idx[i].disk->game->name && dat->disk_name_idx[j].disk->game->name &&
				!strcmp(dat->disk_name_idx[i].disk->game->name, dat->disk_name_idx[j].disk->game->name)) ||
				(dat->disk_name_idx[i].disk->game->name && dat->disk_name_idx[j].disk->game->cloneof &&
				!strcmp(dat->disk_name_idx[i].disk->game->name, dat->disk_name_idx[j].disk->game->cloneof)) ||
				(dat->disk_name_idx[i].disk->game->cloneof && dat->disk_name_idx[j].disk->game->name &&
				!strcmp(dat->disk_name_idx[i].disk->game->cloneof, dat->disk_name_idx[j].disk->game->name)) ||
				(dat->disk_name_idx[i].disk->game->cloneof && dat->disk_name_idx[j].disk->game->cloneof &&
				!strcmp(dat->disk_name_idx[i].disk->game->cloneof, dat->disk_name_idx[j].disk->game->cloneof)))
			{
				if (dat->disk_name_idx[i].disk->crc && !dat->disk_name_idx[j].disk->crc)
				{
					dat->disk_name_idx[j].disk->crc=dat->disk_name_idx[i].disk->crc;

					if (strcmp(dat->disk_name_idx[j].disk->status, "baddump"))
					{
						dat->disk_name_idx[j].disk->status="baddump";
						dat->disk_name_idx[j].disk->disk_fixes|=FLAG_DISK_STATUS;
					}
				}
				else if (!dat->disk_name_idx[i].disk->crc && dat->disk_name_idx[j].disk->crc)
				{
					dat->disk_name_idx[i].disk->crc=dat->disk_name_idx[j].disk->crc;

					if (strcmp(dat->disk_name_idx[i].disk->status, "baddump"))
					{
						dat->disk_name_idx[i].disk->status="baddump";
						dat->disk_name_idx[i].disk->disk_fixes|=FLAG_DISK_STATUS;
					}
				}
				else if (dat->disk_name_idx[i].disk->crc != dat->disk_name_idx[j].disk->crc)
				{
					dat->disk_name_idx[i].disk->disk_warnings|=FLAG_DISK_CRC_CONFLICT;
					dat->disk_name_idx[j].disk->disk_warnings|=FLAG_DISK_CRC_CONFLICT;
				}

				if (!(dat->disk_name_idx[i].disk->disk_warnings & FLAG_DISK_CRC_CONFLICT) &&
					!(dat->disk_name_idx[j].disk->disk_warnings & FLAG_DISK_CRC_CONFLICT))
				{
					if (dat->disk_name_idx[i].disk->sha1 && !dat->disk_name_idx[j].disk->sha1)
					{
						dat->disk_name_idx[j].disk->sha1=dat->disk_name_idx[i].disk->sha1;
						dat->disk_name_idx[j].disk->disk_fixes|=FLAG_DISK_SHA1;
						dat->disk_name_idx[j].disk->disk_flags|=FLAG_DISK_SHA1;
					}
					else if (!dat->disk_name_idx[i].disk->sha1 && dat->disk_name_idx[j].disk->sha1)
					{
						dat->disk_name_idx[i].disk->sha1=dat->disk_name_idx[j].disk->sha1;
						dat->disk_name_idx[i].disk->disk_fixes|=FLAG_DISK_SHA1;
						dat->disk_name_idx[i].disk->disk_flags|=FLAG_DISK_SHA1;
					}

					if (dat->disk_name_idx[i].disk->md5 && !dat->disk_name_idx[j].disk->md5)
					{
						dat->disk_name_idx[j].disk->md5=dat->disk_name_idx[i].disk->md5;
						dat->disk_name_idx[j].disk->disk_fixes|=FLAG_DISK_MD5;
						dat->disk_name_idx[j].disk->disk_flags|=FLAG_DISK_MD5;
					}
					else if (!dat->disk_name_idx[i].disk->md5 && dat->disk_name_idx[j].disk->md5)
					{
						dat->disk_name_idx[i].disk->md5=dat->disk_name_idx[j].disk->md5;
						dat->disk_name_idx[i].disk->disk_fixes|=FLAG_DISK_MD5;
						dat->disk_name_idx[i].disk->disk_flags|=FLAG_DISK_MD5;
					}
				}

				if (dat->disk_name_idx[i].disk->sha1 && dat->disk_name_idx[j].disk->sha1 &&
					strcmp(dat->disk_name_idx[i].disk->sha1, dat->disk_name_idx[j].disk->sha1))
				{
					dat->disk_name_idx[i].disk->disk_warnings|=FLAG_DISK_SHA1_MD5_CONFLICT;
					dat->disk_name_idx[j].disk->disk_warnings|=FLAG_DISK_SHA1_MD5_CONFLICT;
				}

				if (dat->disk_name_idx[i].disk->md5 && dat->disk_name_idx[j].disk->md5 &&
					strcmp(dat->disk_name_idx[i].disk->md5, dat->disk_name_idx[j].disk->md5))
				{
					dat->disk_name_idx[i].disk->disk_warnings|=FLAG_DISK_SHA1_MD5_CONFLICT;
					dat->disk_name_idx[j].disk->disk_warnings|=FLAG_DISK_SHA1_MD5_CONFLICT;
				}
			}
		}
	}

	return(errflg);
}

int report_warnings(struct dat *dat)
{
	struct st_idx *st_idx;
	struct game_idx *curr_game_idx=0;
	struct game *curr_game=0;
	struct biosset *curr_biosset=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct chip *curr_chip=0;
	struct video *curr_video=0;
	struct driver *curr_driver=0;
	uint32_t i, j;

	int errflg=0;

	/* --- Record warnings --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Recording warnings...\n");
	}

	/* --- Calculate warnings --- */

	for (i=0, st_idx=dat->options->game_selections; i<dat->options->num_game_selections; i++, st_idx++)
	{
		if (!(st_idx->flags & FLAG_STRING_INDEX_USED))
			dat->game_selection_warnings|=FLAG_BAD_GAME_SELECTION;
	}

	for (i=0, st_idx=dat->options->sourcefile_selections; i<dat->options->num_sourcefile_selections; i++, st_idx++)
	{
		if (!(st_idx->flags & FLAG_STRING_INDEX_USED))
			dat->sourcefile_selection_warnings|=FLAG_BAD_SOURCEFILE_SELECTION;
	}

	for (i=0, curr_game_idx=dat->game_name_idx; i<dat->num_games; i++, curr_game_idx++)
	{
		if (i>0 && !strcmp(curr_game_idx->game->name, (curr_game_idx-1)->game->name))
		{
			curr_game_idx->game->game_warnings|=FLAG_GAME_DUPLICATE_NAME;
			(curr_game_idx-1)->game->game_warnings|=FLAG_GAME_DUPLICATE_NAME;
		}
	}

	for (i=0, curr_game_idx=dat->game_description_idx; i<dat->num_games; i++, curr_game_idx++)
	{
		if (i>0 && !strcmp(curr_game_idx->game->description, (curr_game_idx-1)->game->description))
		{
			curr_game_idx->game->game_warnings|=FLAG_GAME_DUPLICATE_DESCRIPTION;
			(curr_game_idx-1)->game->game_warnings|=FLAG_GAME_DUPLICATE_DESCRIPTION;
		}
	}

	for (i=0, curr_game_idx=dat->game_crc_idx; i<dat->num_games; i++, curr_game_idx++)
	{
		if (i>0 && curr_game_idx->game->crc && (curr_game_idx-1)->game->crc &&
			curr_game_idx->game->crc==(curr_game_idx-1)->game->crc)
		{
			curr_game_idx->game->game_warnings|=FLAG_GAME_DUPLICATE_CRC;
			(curr_game_idx-1)->game->game_warnings|=FLAG_GAME_DUPLICATE_CRC;
		}
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		curr_game->game_warnings|=(curr_game->game_flags ^ dat->game_flags) &
			(FLAG_GAME_DESCRIPTION | FLAG_GAME_MANUFACTURER | FLAG_GAME_REBUILDTO);

		for (j=0, curr_biosset=curr_game->biossets; j<curr_game->num_biossets; j++, curr_biosset++)
		{
			curr_biosset->biosset_warnings|=(curr_biosset->biosset_flags ^ dat->biosset_flags) &
				(FLAG_BIOSSET_DESCRIPTION);

			curr_game->biosset_warnings|=curr_biosset->biosset_warnings;
		}

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			curr_rom->rom_warnings|=(curr_rom->rom_flags ^ dat->rom_flags) &
				(FLAG_ROM_SIZE | FLAG_ROM_REGION | FLAG_ROM_OFFSET);

			if (strcmp(curr_rom->status, "nodump"))
				curr_rom->rom_warnings|=(curr_rom->rom_flags ^ dat->rom_flags) &
					(FLAG_ROM_CRC | FLAG_ROM_MD5 | FLAG_ROM_SHA1);

			curr_game->rom_warnings|=curr_rom->rom_warnings;
		}

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			curr_disk->disk_warnings|=(curr_disk->disk_flags ^ dat->disk_flags) &
				(FLAG_DISK_REGION | FLAG_DISK_INDEX);

			if (strcmp(curr_disk->status, "nodump"))
				curr_disk->disk_warnings|=(curr_disk->disk_flags ^ dat->disk_flags) &
					(FLAG_DISK_MD5 | FLAG_DISK_SHA1);

			curr_game->disk_warnings|=curr_disk->disk_warnings;
		}

		for (j=0, curr_chip=curr_game->chips; j<curr_game->num_chips; j++, curr_chip++)
		{
			curr_chip->chip_warnings|=(curr_chip->chip_flags ^ dat->chip_flags) &
				(FLAG_CHIP_TYPE);

			curr_game->chip_warnings|=curr_chip->chip_warnings;
		}

		for (j=0, curr_video=curr_game->videos; j<curr_game->num_videos; j++, curr_video++)
		{
			curr_video->video_warnings|=(curr_video->video_flags ^ dat->video_flags) &
				(FLAG_VIDEO_ORIENTATION | FLAG_VIDEO_ASPECTX | FLAG_VIDEO_ASPECTY | FLAG_VIDEO_REFRESH);

			curr_game->video_warnings|=curr_video->video_warnings;
		}

		for (j=0, curr_driver=curr_game->drivers; j<curr_game->num_drivers; j++, curr_driver++)
		{
			curr_driver->driver_warnings|=(curr_driver->driver_flags ^ dat->driver_flags) &
				(FLAG_DRIVER_EMULATION | FLAG_DRIVER_COLOR | FLAG_DRIVER_SOUND | FLAG_DRIVER_GRAPHIC | FLAG_DRIVER_PALETTESIZE |
				 FLAG_DRIVER_COLORDEEP | FLAG_DRIVER_CREDITS);

			curr_game->driver_warnings|=curr_driver->driver_warnings;
		}

		dat->game_warnings|=curr_game->game_warnings;
		dat->comment_warnings|=curr_game->comment_warnings;
		dat->biosset_warnings|=curr_game->biosset_warnings;
		dat->rom_warnings|=curr_game->rom_warnings;
		dat->disk_warnings|=curr_game->disk_warnings;
		dat->sample_warnings|=curr_game->sample_warnings;
		dat->chip_warnings|=curr_game->chip_warnings;
		dat->video_warnings|=curr_game->video_warnings;
		dat->sound_warnings|=curr_game->sound_warnings;
		dat->input_warnings|=curr_game->input_warnings;
		dat->dipswitch_warnings|=curr_game->dipswitch_warnings;
		dat->dipvalue_warnings|=curr_game->dipvalue_warnings;
		dat->driver_warnings|=curr_game->driver_warnings;
		dat->device_warnings|=curr_game->device_warnings;
		dat->extension_warnings|=curr_game->extension_warnings;
		dat->archive_warnings|=curr_game->archive_warnings;
	}

	/* --- Report warnings --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Game selection warnings=%04x\n", dat->game_selection_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sourcefile selection warnings=%04x\n", dat->sourcefile_selection_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Game warnings=%04x\n", dat->game_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Comment warnings=%04x\n", dat->comment_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Biosset warnings=%04x\n", dat->biosset_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("ROM warnings=%04x\n", dat->rom_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Disk warnings=%02x\n", dat->disk_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sample warnings=%02x\n", dat->sample_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Chip warnings=%02x\n", dat->chip_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Video warnings=%02x\n", dat->video_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sound warnings=%02x\n", dat->sound_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Input warnings=%02x\n", dat->input_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Dipswitch warnings=%02x\n", dat->dipswitch_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Dipvalue warnings=%02x\n", dat->dipvalue_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Driver warnings=%02x\n", dat->driver_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Device warnings=%02x\n", dat->device_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Extension warnings=%02x\n", dat->extension_warnings);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Archive warnings=%02x\n", dat->archive_warnings);

		printf("%-16s: ", "Datlib.init_dat");
		printf("Reporting warnings...\n");
	}

	if (dat->game_selection_warnings || dat->sourcefile_selection_warnings || dat->game_warnings || dat->comment_warnings || dat->biosset_warnings || dat->rom_warnings || dat->disk_warnings || dat->sample_warnings ||
		dat->chip_warnings || dat->video_warnings || dat->sound_warnings || dat->input_warnings || dat->dipswitch_warnings ||
		dat->dipvalue_warnings || dat->driver_warnings || dat->device_warnings || dat->extension_warnings || dat->archive_warnings)
	{
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n");
		fprintf(dat->log_file, "Warning Summary\n");
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n\n");

		if (dat->game_selection_warnings & FLAG_BAD_GAME_SELECTION)
		{
			fprintf(dat->log_file, "Invalid game selections were provided to -g.\n\n");
		}

		if (dat->sourcefile_selection_warnings & FLAG_BAD_SOURCEFILE_SELECTION)
		{
			fprintf(dat->log_file, "Invalid sourcefile selections were provided to -G.\n\n");
		}

		/* --- Games --- */

		if (dat->game_warnings)
		{
			fprintf(dat->log_file, "Game warnings:\n\n");

			if (dat->game_warnings & FLAG_GAME_DESCRIPTION)
				fprintf(dat->log_file, "    Missing Description\n");
			if (dat->game_warnings & FLAG_GAME_MANUFACTURER)
				fprintf(dat->log_file, "    Missing Manufacturer\n");
			if (dat->game_warnings & FLAG_GAME_REBUILDTO)
				fprintf(dat->log_file, "    Missing Rebuild To\n");
			if (dat->game_warnings & FLAG_GAME_DUPLICATE_NAME)
				fprintf(dat->log_file, "    Duplicate Name\n");
			if (dat->game_warnings & FLAG_GAME_DUPLICATE_DESCRIPTION)
				fprintf(dat->log_file, "    Duplicate Description\n");
			if (dat->game_warnings & FLAG_GAME_DUPLICATE_CRC)
				fprintf(dat->log_file, "    Duplicate CRC (i.e. all ROMs match another game)\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- BIOS Sets --- */

		if (dat->biosset_warnings)
		{
			fprintf(dat->log_file, "Biosset warnings:\n\n");

			if (dat->biosset_warnings & FLAG_BIOSSET_DESCRIPTION)
				fprintf(dat->log_file, "    Missing Decription\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- ROMs --- */

		if (dat->rom_warnings)
		{
			fprintf(dat->log_file, "ROM warnings:\n\n");

			if (dat->rom_warnings & FLAG_ROM_SIZE)
				fprintf(dat->log_file, "    Missing Size\n");
			if (dat->rom_warnings & FLAG_ROM_REGION)
				fprintf(dat->log_file, "    Missing Region\n");
			if (dat->rom_warnings & FLAG_ROM_OFFSET)
				fprintf(dat->log_file, "    Missing Offset\n");
			if (dat->rom_warnings & FLAG_ROM_CRC)
				fprintf(dat->log_file, "    Missing CRC\n");
			if (dat->rom_warnings & FLAG_ROM_MD5)
				fprintf(dat->log_file, "    Missing MD5\n");
			if (dat->rom_warnings & FLAG_ROM_SHA1)
				fprintf(dat->log_file, "    Missing SHA1\n");
			if (dat->rom_warnings & FLAG_ROM_CRC_CONFLICT)
				fprintf(dat->log_file, "    CRC Conflict\n");
			if (dat->rom_warnings & FLAG_ROM_SHA1_MD5_CONFLICT)
			{
				if (dat->options->options & OPTION_MD5_CHECKSUMS)
					fprintf(dat->log_file, "    MD5 Conflict\n");
				else
					fprintf(dat->log_file, "    SHA1 Conflict\n");
			}

			fprintf(dat->log_file, "\n");
		}

		/* --- Disks --- */

		if (dat->disk_warnings)
		{
			fprintf(dat->log_file, "Disk warnings:\n\n");

			if (dat->disk_warnings & FLAG_DISK_REGION)
				fprintf(dat->log_file, "    Missing Region\n");
			if (dat->disk_warnings & FLAG_DISK_INDEX)
				fprintf(dat->log_file, "    Missing Index\n");
			if (dat->disk_warnings & FLAG_DISK_MD5)
				fprintf(dat->log_file, "    Missing MD5\n");
			if (dat->disk_warnings & FLAG_DISK_SHA1)
				fprintf(dat->log_file, "    Missing SHA1\n");
			if (dat->disk_warnings & FLAG_DISK_SHA1_MD5_CONFLICT)
			{
				if (dat->options->options & OPTION_MD5_CHECKSUMS)
					fprintf(dat->log_file, "    MD5 Conflict\n");
				else
					fprintf(dat->log_file, "    SHA1 Conflict\n");
			}

			fprintf(dat->log_file, "\n");
		}

		/* --- Chips --- */

		if (dat->chip_warnings)
		{
			fprintf(dat->log_file, "Chip warnings:\n\n");

			if (dat->chip_warnings & FLAG_CHIP_TYPE)
				fprintf(dat->log_file, "    Missing Type\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- Videos --- */

		if (dat->video_warnings)
		{
			fprintf(dat->log_file, "Video warnings:\n\n");

			if (dat->video_warnings & FLAG_VIDEO_ORIENTATION)
				fprintf(dat->log_file, "    Missing Orientation\n");
			if (dat->video_warnings & FLAG_VIDEO_ASPECTX)
				fprintf(dat->log_file, "    Missing Aspect X\n");
			if (dat->video_warnings & FLAG_VIDEO_ASPECTY)
				fprintf(dat->log_file, "    Missing Aspect Y\n");
			if (dat->video_warnings & FLAG_VIDEO_REFRESH)
				fprintf(dat->log_file, "    Missing Refresh\n");

			fprintf(dat->log_file, "\n");
		}

		/* --- Drivers --- */

		if (dat->driver_warnings)
		{
			fprintf(dat->log_file, "Driver warnings:\n\n");

			if (dat->driver_warnings & FLAG_DRIVER_EMULATION)
				fprintf(dat->log_file, "    Missing Emulation\n");
			if (dat->driver_warnings & FLAG_DRIVER_COLOR)
				fprintf(dat->log_file, "    Missing Color\n");
			if (dat->driver_warnings & FLAG_DRIVER_SOUND)
				fprintf(dat->log_file, "    Missing Sound\n");
			if (dat->driver_warnings & FLAG_DRIVER_GRAPHIC)
				fprintf(dat->log_file, "    Missing Graphic\n");
			if (dat->driver_warnings & FLAG_DRIVER_PALETTESIZE)
				fprintf(dat->log_file, "    Missing Palettesize\n");
			if (dat->driver_warnings & FLAG_DRIVER_COLORDEEP)
				fprintf(dat->log_file, "    Missing Colordeep\n");
			if (dat->driver_warnings & FLAG_DRIVER_CREDITS)
				fprintf(dat->log_file, "    Missing Credits\n");

			fprintf(dat->log_file, "\n");
		}
	}

	if ((dat->game_selection_warnings || dat->sourcefile_selection_warnings || dat->game_warnings || dat->comment_warnings || dat->biosset_warnings || dat->rom_warnings || dat->disk_warnings || dat->sample_warnings ||
		dat->chip_warnings || dat->video_warnings || dat->sound_warnings || dat->input_warnings || dat->dipswitch_warnings ||
		dat->dipvalue_warnings || dat->driver_warnings || dat->device_warnings || dat->extension_warnings || dat->archive_warnings) &&
		dat->options->options & OPTION_VERBOSE_LOGGING)
	{
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n");
		fprintf(dat->log_file, "Warning Details\n");
		fprintf(dat->log_file, "-------------------------------------------------------------------------------\n\n");

		if (dat->game_selection_warnings & FLAG_BAD_GAME_SELECTION)
		{
			fprintf(dat->log_file, "Invalid game selections provided to -g:\n\n");

			for (i=0, st_idx=dat->options->game_selections; i<dat->options->num_game_selections; i++, st_idx++)
			{
				if (!(st_idx->flags & FLAG_STRING_INDEX_USED))
					fprintf(dat->log_file, "    %s\n", st_idx->st);
			}

			fprintf(dat->log_file, "\n");
		}

		if (dat->sourcefile_selection_warnings & FLAG_BAD_SOURCEFILE_SELECTION)
		{
			fprintf(dat->log_file, "Invalid sourcefile selections provided to -G:\n\n");

			for (i=0, st_idx=dat->options->sourcefile_selections; i<dat->options->num_sourcefile_selections; i++, st_idx++)
			{
				if (!(st_idx->flags & FLAG_STRING_INDEX_USED))
					fprintf(dat->log_file, "    %s\n", st_idx->st);
			}

			fprintf(dat->log_file, "\n");
		}

		for (i=0, curr_game=dat->games; dat->log_file && i<dat->num_games; i++, curr_game++)
		{
			if (curr_game->game_warnings || curr_game->comment_warnings || curr_game->biosset_warnings || curr_game->rom_warnings || curr_game->disk_warnings || curr_game->sample_warnings ||
				curr_game->chip_warnings || curr_game->video_warnings || curr_game->sound_warnings || curr_game->input_warnings ||
				curr_game->dipswitch_warnings || curr_game->dipvalue_warnings || curr_game->driver_warnings  ||
				curr_game->device_warnings || curr_game->extension_warnings || curr_game->archive_warnings)
			{
				fprintf(dat->log_file, "%s - %s\n", curr_game->name, curr_game->description);

				if (curr_game->game_warnings )
				{
					if (curr_game->game_warnings & FLAG_GAME_DESCRIPTION)
						fprintf(dat->log_file, "    Missing Description\n");
					if (curr_game->game_warnings & FLAG_GAME_MANUFACTURER)
						fprintf(dat->log_file, "    Missing Manufacturer\n");
					if (curr_game->game_warnings & FLAG_GAME_REBUILDTO)
						fprintf(dat->log_file, "    Missing Rebuild To\n");
					if (curr_game->game_warnings & FLAG_GAME_DUPLICATE_NAME)
						fprintf(dat->log_file, "    Duplicate Name\n");
					if (curr_game->game_warnings & FLAG_GAME_DUPLICATE_DESCRIPTION)
						fprintf(dat->log_file, "    Duplicate Description\n");
					if (curr_game->game_warnings & FLAG_GAME_DUPLICATE_CRC)
						fprintf(dat->log_file, "    Duplicate CRC (i.e. all ROMs match another game)\n");
				}

				if (curr_game->biosset_warnings)
				{
					for (j=0, curr_biosset=curr_game->biossets; j<curr_game->num_biossets; j++, curr_biosset++)
					{
						if (curr_biosset->biosset_warnings & FLAG_BIOSSET_DESCRIPTION)
							fprintf(dat->log_file, "    Biosset %s - Missing Description\n", curr_biosset->name);
					}
				}
	
				if (curr_game->rom_warnings)
				{
					for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
					{
						if (curr_rom->rom_warnings & FLAG_ROM_SIZE)
							fprintf(dat->log_file, "    ROM %s - Missing Size\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_REGION)
							fprintf(dat->log_file, "    ROM %s - Missing Region\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_OFFSET)
							fprintf(dat->log_file, "    ROM %s - Missing Offset\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_CRC)
							fprintf(dat->log_file, "    ROM %s - Missing CRC\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_MD5)
							fprintf(dat->log_file, "    ROM %s - Missing MD5\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_SHA1)
							fprintf(dat->log_file, "    ROM %s - Missing SHA1\n", curr_rom->name);
						if (curr_rom->rom_warnings & FLAG_ROM_CRC_CONFLICT)
							fprintf(dat->log_file, "    ROM %s - CRC Conflict (%08lx)\n", curr_rom->name, (unsigned long)curr_rom->crc);
						if (curr_rom->rom_warnings & FLAG_ROM_SHA1_MD5_CONFLICT)
						{
							if (dat->options->options & OPTION_MD5_CHECKSUMS)
								fprintf(dat->log_file, "    ROM %s - MD5 Conflict (%s)\n", curr_rom->name, curr_rom->md5);
							else
								fprintf(dat->log_file, "    ROM %s - SHA1 Conflict (%s)\n", curr_rom->name, curr_rom->sha1);
						}
					}
				}

				if (curr_game->disk_warnings)
				{
					for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
					{
						if (curr_disk->disk_warnings & FLAG_DISK_REGION)
							fprintf(dat->log_file, "    Disk %s - Missing Region\n", curr_disk->name);
						if (curr_disk->disk_warnings & FLAG_DISK_INDEX)
							fprintf(dat->log_file, "    Disk %s - Missing Index\n", curr_disk->name);
						if (curr_disk->disk_warnings & FLAG_DISK_MD5)
							fprintf(dat->log_file, "    Disk %s - Missing MD5\n", curr_disk->name);
						if (curr_disk->disk_warnings & FLAG_DISK_SHA1)
							fprintf(dat->log_file, "    Disk %s - Missing SHA1\n", curr_disk->name);
						if (curr_disk->disk_warnings & FLAG_DISK_SHA1_MD5_CONFLICT)
						{
							if (dat->options->options & OPTION_MD5_CHECKSUMS)
								fprintf(dat->log_file, "    Disk %s - MD5 Conflict (%s)\n", curr_disk->name, curr_disk->md5);
							else
								fprintf(dat->log_file, "    Disk %s - SHA1 Conflict (%s)\n", curr_disk->name, curr_disk->sha1);
						}
					}
				}

				if (curr_game->chip_warnings)
				{
					for (j=0, curr_chip=curr_game->chips; j<curr_game->num_chips; j++, curr_chip++)
					{
						if (curr_chip->chip_warnings & FLAG_CHIP_TYPE)
							fprintf(dat->log_file, "    Chip %s - Missing Type\n", curr_chip->name);
					}
				}
	
				if (curr_game->video_warnings)
				{
					for (j=0, curr_video=curr_game->videos; j<curr_game->num_videos; j++, curr_video++)
					{
						if (curr_video->video_warnings & FLAG_VIDEO_ORIENTATION)
							fprintf(dat->log_file, "    Video - Missing Orientation\n");
						if (curr_video->video_warnings & FLAG_VIDEO_ASPECTX)
							fprintf(dat->log_file, "    Video - Missing Aspect X\n");
						if (curr_video->video_warnings & FLAG_VIDEO_ASPECTY)
							fprintf(dat->log_file, "    Video - Missing Aspect Y\n");
						if (curr_video->video_warnings & FLAG_VIDEO_REFRESH)
							fprintf(dat->log_file, "    Video - Missing Refresh\n");
					}
				}
	
				if (curr_game->driver_warnings)
				{
					for (j=0, curr_driver=curr_game->drivers; j<curr_game->num_drivers; j++, curr_driver++)
					{
						if (curr_driver->driver_warnings & FLAG_DRIVER_EMULATION)
							fprintf(dat->log_file, "    Driver - Missing Emulation\n");
						if (curr_driver->driver_warnings & FLAG_DRIVER_COLOR)
							fprintf(dat->log_file, "    Driver - Missing Color\n");
						if (curr_driver->driver_warnings & FLAG_DRIVER_SOUND)
							fprintf(dat->log_file, "    Driver - Missing Sound\n");
						if (curr_driver->driver_warnings & FLAG_DRIVER_GRAPHIC)
							fprintf(dat->log_file, "    Driver - Missing Graphic\n");
						if (curr_driver->driver_warnings & FLAG_DRIVER_PALETTESIZE)
							fprintf(dat->log_file, "    Driver - Missing Palettesize\n");
						if (curr_driver->driver_warnings & FLAG_DRIVER_COLORDEEP)
							fprintf(dat->log_file, "    Driver - Missing Colordeep\n");
						if (curr_driver->driver_warnings & FLAG_DRIVER_CREDITS)
							fprintf(dat->log_file, "    Driver - Missing Credits\n");
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
		printf("Comment fixes=%04x\n", dat->comment_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Biosset fixes=%04x\n", dat->biosset_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("ROM fixes=%04x\n", dat->rom_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Disk fixes=%02x\n", dat->disk_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sample fixes=%02x\n", dat->sample_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Chip fixes=%02x\n", dat->chip_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Video fixes=%02x\n", dat->video_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Sound fixes=%02x\n", dat->sound_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Input fixes=%02x\n", dat->input_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Dipswitch fixes=%02x\n", dat->dipswitch_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Dipvalue fixes=%02x\n", dat->dipvalue_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Driver fixes=%02x\n", dat->driver_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Device fixes=%02x\n", dat->device_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Extension fixes=%02x\n", dat->extension_fixes);
		printf("%-16s: ", "Datlib.init_dat");
		printf("Archive fixes=%02x\n", dat->archive_fixes);

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
			if (dat->rom_fixes & FLAG_ROM_STATUS)
				fprintf(dat->log_file, "    Status\n");
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
			if (dat->disk_fixes & FLAG_DISK_MERGE)
				fprintf(dat->log_file, "    Merge\n");
			if (dat->disk_fixes & FLAG_DISK_MD5)
				fprintf(dat->log_file, "    MD5\n");
			if (dat->disk_fixes & FLAG_DISK_SHA1)
				fprintf(dat->log_file, "    SHA1\n");
			if (dat->disk_fixes & FLAG_DISK_REGION)
				fprintf(dat->log_file, "    Region\n");
			if (dat->disk_fixes & FLAG_DISK_STATUS)
				fprintf(dat->log_file, "    Status\n");
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

	if ((dat->game_fixes || dat->rom_fixes || dat->disk_fixes || dat->sample_fixes) && dat->options->options & OPTION_VERBOSE_LOGGING)
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
						fprintf(dat->log_file, "    Name set/changed.\n");
					}

					if (curr_game->game_fixes & FLAG_MACHINE_NAME)
					{
						fprintf(dat->log_file, "    Name set/changed.\n");
					}

					if (curr_game->game_fixes & FLAG_RESOURCE_NAME)
					{
						fprintf(dat->log_file, "    Name set/changed.\n");
					}

					if (curr_game->game_fixes & FLAG_GAME_DESCRIPTION)
					{
						fprintf(dat->log_file, "    Description set/changed.\n");
					}

					if (curr_game->game_fixes & FLAG_GAME_CLONEOF)
					{
						if (curr_game->cloneof)
						{
							if (curr_game->game_fixes & FLAG_GAME_CLONEOFCLONE)
								fprintf(dat->log_file, "    Clone Of changed (clone of clone).\n");
							else
								fprintf(dat->log_file, "    Clone Of set/changed.\n");
						}
						else
							fprintf(dat->log_file, "    Clone Of removed (invalid reference).\n");
					}

					if (curr_game->game_fixes & FLAG_GAME_ROMOF)
					{
						if (curr_game->romof)
						{
							if (curr_game->game_fixes & FLAG_GAME_CLONEOFCLONE)
								fprintf(dat->log_file, "    ROM Of changed (clone of clone).\n");
							else
								fprintf(dat->log_file, "    ROM Of set/changed.\n");
						}
						else
							fprintf(dat->log_file, "    ROM Of removed (invalid reference).\n");
					}

					if (curr_game->game_fixes & FLAG_GAME_SAMPLEOF)
						{
						if (curr_game->sampleof)
							fprintf(dat->log_file, "    Sample Of set/changed.\n");
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
							fprintf(dat->log_file, "    ROM %s - name set/changed.\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_MERGE)
						{
							if (curr_rom->merge)
								fprintf(dat->log_file, "    ROM %s - merge name set.\n", curr_rom->name);
							else
								fprintf(dat->log_file, "    ROM %s - merge name removed (ROM name not in parent).\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_SIZE)
						{
							fprintf(dat->log_file, "    ROM %s - size set/changed.\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_CRC)
						{
							fprintf(dat->log_file, "    ROM %s - CRC set/changed.\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_MD5)
						{
							if (curr_rom->md5)
								fprintf(dat->log_file, "    ROM %s - MD5 set/changed.\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_SHA1)
						{
							if (curr_rom->sha1)
								fprintf(dat->log_file, "    ROM %s - SHA1 set/changed.\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_REGION)
						{
							if (curr_rom->region)
								fprintf(dat->log_file, "    ROM %s - region set/changed.\n", curr_rom->name);
						}

						if (curr_rom->rom_fixes & FLAG_ROM_STATUS)
						{
							if (strcmp(curr_rom->status, ""))
								fprintf(dat->log_file, "    ROM %s - status set.\n", curr_rom->name);
							else
								fprintf(dat->log_file, "    ROM %s - status cleared.\n", curr_rom->name);
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
							fprintf(dat->log_file, "    Disk %s - name set/changed.\n", curr_disk->name);
						}

						if (curr_disk->disk_fixes & FLAG_DISK_MERGE)
						{
							if (curr_disk->merge)
								fprintf(dat->log_file, "    Disk %s - merge name set.\n", curr_disk->name);
							else
								fprintf(dat->log_file, "    Disk %s - merge name removed (disk name not in parent).\n", curr_disk->name);
						}

						if (curr_disk->disk_fixes & FLAG_DISK_MD5)
						{
							if (curr_disk->md5)
								fprintf(dat->log_file, "    Disk %s - MD5 set/changed.\n", curr_disk->name);
						}

						if (curr_disk->disk_fixes & FLAG_DISK_SHA1)
						{
							if (curr_disk->sha1)
								fprintf(dat->log_file, "    Disk %s - SHA1 set/changed.\n", curr_disk->name);
						}

						if (curr_disk->disk_fixes & FLAG_DISK_REGION)
						{
							if (curr_disk->region)
								fprintf(dat->log_file, "    Disk %s - region set/changed.\n", curr_disk->name);
						}

						if (curr_disk->disk_fixes & FLAG_DISK_STATUS)
						{
							if (strcmp(curr_disk->status, ""))
								fprintf(dat->log_file, "    Disk %s - status set.\n", curr_disk->name);
							else
								fprintf(dat->log_file, "    Disk %s - status cleared.\n", curr_disk->name);
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
							fprintf(dat->log_file, "    Sample %s - name set/changed.\n", curr_sample->name);
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
	struct game_idx *curr_game_description_idx=0;
	struct game_idx *curr_game_score_idx=0;

	struct rom *curr_rom=0;
	struct rom_idx *curr_game_rom_crc_idx=0;
	struct rom_idx *curr_game_rom_name_idx=0;
	struct rom_idx *curr_rom_crc_idx=0;
	struct rom_idx *curr_rom_name_idx=0;

	struct disk *curr_disk=0;
	struct disk_idx *curr_game_disk_crc_idx=0;
	struct disk_idx *curr_game_disk_name_idx=0;
	struct disk_idx *curr_disk_crc_idx=0;
	struct disk_idx *curr_disk_name_idx=0;

	struct sample *curr_sample=0;
	struct sample_idx *curr_game_sample_name_idx=0;
	struct sample_idx *curr_sample_name_idx=0;

	uint32_t i, j;

	int errflg=0;

	/* --- Sort games by parent (if required) --- */

	if (!errflg && dat->options->options & OPTION_SORT_GAMES_BY_PARENT)
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
	curr_game_description_idx=dat->game_description_idx;
	curr_game_score_idx=dat->game_score_idx;
	
	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		curr_game_crc_idx++->game=curr_game;
		curr_game_name_idx++->game=curr_game;
		curr_game_description_idx++->game=curr_game;
		curr_game_score_idx++->game=curr_game;
	}

	qsort(dat->game_crc_idx, dat->num_games, sizeof(struct game_idx), game_crc_idx_sort_function);
	qsort(dat->game_name_idx, dat->num_games, sizeof(struct game_idx), game_name_idx_sort_function);
	qsort(dat->game_description_idx, dat->num_games, sizeof(struct game_idx), game_description_idx_sort_function);
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

	curr_game_disk_crc_idx=dat->game_disk_crc_idx;
	curr_game_disk_name_idx=dat->game_disk_name_idx;
	curr_disk_crc_idx=dat->disk_crc_idx;
	curr_disk_name_idx=dat->disk_name_idx;

	curr_game_sample_name_idx=dat->game_sample_name_idx;
	curr_sample_name_idx=dat->sample_name_idx;

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (curr_game->cloneof)
		{
			if ((game_match=bsearch((void *)curr_game->cloneof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
				curr_game->game_cloneof=game_match->game;
		}

		if (curr_game->romof)
		{
			if ((game_match=bsearch((void *)curr_game->romof, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name))!=0)
				curr_game->game_romof=game_match->game;
		}

		if (curr_game->num_roms)
		{
			curr_game->rom_crc_idx=curr_game_rom_crc_idx;
			curr_game->rom_name_idx=curr_game_rom_name_idx;

			for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
			{
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
			curr_game->disk_crc_idx=curr_game_disk_crc_idx;
			curr_game->disk_name_idx=curr_game_disk_name_idx;

			for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
			{
				curr_disk->game=curr_game;

				curr_game_disk_crc_idx++->disk=curr_disk;
				curr_game_disk_name_idx++->disk=curr_disk;
				curr_disk_crc_idx++->disk=curr_disk;
				curr_disk_name_idx++->disk=curr_disk;
			}

			qsort(curr_game->disk_crc_idx, curr_game->num_disks, sizeof(struct disk_idx), disk_crc_idx_sort_function);
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
	qsort(dat->disk_crc_idx, dat->num_disks, sizeof(struct disk_idx), disk_crc_idx_sort_function);
	qsort(dat->disk_name_idx, dat->num_disks, sizeof(struct disk_idx), disk_name_idx_sort_function);
	qsort(dat->sample_name_idx, dat->num_samples, sizeof(struct sample_idx), sample_name_idx_sort_function);

	return(errflg);
}

int game_zip_rom_sort_function(const void *zip_rom1, const void *zip_rom2)
{
	int diff=strcmp(((struct game_zip_rom *)zip_rom1)->game_zip->game->name, ((struct game_zip_rom *)zip_rom2)->game_zip->game->name);

	if (diff==0)
		diff=strcmp(((struct game_zip_rom *)zip_rom1)->rom->name, ((struct game_zip_rom *)zip_rom2)->rom->name);

	return(diff);
}

int game_zip_disk_sort_function(const void *zip_disk1, const void *zip_disk2)
{
	int diff=strcmp(((struct game_zip_disk *)zip_disk1)->game_zip->game->name, ((struct game_zip_disk *)zip_disk2)->game_zip->game->name);

	if (diff==0)
		diff=strcmp(((struct game_zip_disk *)zip_disk1)->disk->name, ((struct game_zip_disk *)zip_disk2)->disk->name);

	return(diff);
}

int game_zip_sample_sort_function(const void *zip_sample1, const void *zip_sample2)
{
	int diff=strcmp(((struct game_zip_sample *)zip_sample1)->game_zip->game->name, ((struct game_zip_sample *)zip_sample2)->game_zip->game->name);

	if (diff==0)
		diff=strcmp(((struct game_zip_sample *)zip_sample1)->sample->name, ((struct game_zip_sample *)zip_sample2)->sample->name);

	return(diff);
}

int build_zip_structures(struct dat *dat)
{
	struct game *curr_game;
	struct rom *curr_rom;
	struct disk *curr_disk;
	struct sample *curr_sample;

	struct game_zip *curr_game_zip;
	struct game_zip_idx *curr_game_zip_name_idx;
	struct game_zip_rom *curr_game_zip_rom, *orig_game_zip_rom;
	struct game_zip_disk *curr_game_zip_disk, *orig_game_zip_disk;
	struct game_zip_sample *curr_game_zip_sample, *orig_game_zip_sample;

	uint32_t num_game_zip_roms, num_game_zip_disks, num_game_zip_samples;
	uint32_t i, j;

	int errflg=0;

	/* --- Create zip structures --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Creating zip structures...\n");
	}

	/* --- Override user merging if 'forcemerging' is used in the data file --- */

	if (dat->dat_flags & (FLAG_DAT_FULL_MERGING|FLAG_DAT_SPLIT_MERGING|FLAG_DAT_NO_MERGING))
	{
		dat->options->options&=~(OPTION_DAT_FULL_MERGING|OPTION_DAT_SPLIT_MERGING|OPTION_DAT_NO_MERGING);

		if (dat->dat_flags & FLAG_DAT_FULL_MERGING)
			dat->options->options|=OPTION_DAT_FULL_MERGING;
		else if (dat->dat_flags & FLAG_DAT_SPLIT_MERGING)
			dat->options->options|=OPTION_DAT_SPLIT_MERGING;
		else if (dat->dat_flags & FLAG_DAT_NO_MERGING)
			dat->options->options|=OPTION_DAT_NO_MERGING;
	}

	if (!(dat->options->options & (OPTION_DAT_FULL_MERGING|OPTION_DAT_SPLIT_MERGING|OPTION_DAT_NO_MERGING)))
		dat->options->options|=OPTION_DAT_SPLIT_MERGING;

	/* --- Firstly, build the game_zip array and index --- */

	curr_game_zip=dat->game_zips;
	curr_game_zip_name_idx=dat->game_zip_name_idx;
	
	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		curr_game_zip_name_idx++->game_zip=curr_game_zip;
		curr_game_zip++->game=curr_game;
		dat->num_game_zips++;
	}

	qsort(dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), game_zip_name_idx_sort_function);

	/* --- Once the game_zip array has been built, do the game_zip ROMs and disks --- */

	curr_game_zip_rom=dat->game_zip_roms;
	curr_game_zip_disk=dat->game_zip_disks;

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		/* --- Locate ZIP --- */

		if ((dat->options->options & OPTION_DAT_FULL_MERGING) &&
			(curr_game->game_romof && !(curr_game->game_romof->game_flags & FLAG_RESOURCE_NAME)))
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game->romof, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);
		}
		else
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game->name, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);
		}

		/* --- ROMs --- */

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			if (strcmp(curr_rom->status, "nodump") || dat->options->options & OPTION_INCLUDE_NODUMPS_IN_ZIPS)
			{
				if (dat->options->options & OPTION_DAT_NO_MERGING)
				{
					if (!(curr_game->game_flags & FLAG_RESOURCE_NAME))
					{
						curr_game_zip_rom->game_zip=curr_game_zip_name_idx->game_zip;
						curr_game_zip_rom->rom=curr_rom;

						curr_game_zip_name_idx->game_zip->num_game_zip_roms++;
						dat->num_game_zip_roms++;
						curr_game_zip_rom++;
					}
				}
				else
				{
					if ((!(dat->options->options & OPTION_NON_SEPERATED_BIOS_ROMS) && curr_rom->merge==0) ||
						(dat->options->options & OPTION_NON_SEPERATED_BIOS_ROMS &&
						(curr_game->cloneof==0 || curr_rom->merge==0)))
					{
						curr_game_zip_rom->game_zip=curr_game_zip_name_idx->game_zip;
						curr_game_zip_rom->rom=curr_rom;

						curr_game_zip_name_idx->game_zip->num_game_zip_roms++;
						dat->num_game_zip_roms++;
						curr_game_zip_rom++;
					}
				}
			}
		}

		/* --- Disks --- */

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			if (strcmp(curr_disk->status, "nodump") || dat->options->options & OPTION_INCLUDE_NODUMPS_IN_ZIPS)
			{
				if (dat->options->options & OPTION_DAT_NO_MERGING)
				{
					if (!(curr_game->game_flags & FLAG_RESOURCE_NAME))
					{
						curr_game_zip_disk->game_zip=curr_game_zip_name_idx->game_zip;
						curr_game_zip_disk->disk=curr_disk;

						curr_game_zip_name_idx->game_zip->num_game_zip_disks++;
						dat->num_game_zip_disks++;
						curr_game_zip_disk++;
					}
				}
				else
				{
					if ((!(dat->options->options & OPTION_NON_SEPERATED_BIOS_ROMS) && curr_disk->merge==0) ||
						(dat->options->options & OPTION_NON_SEPERATED_BIOS_ROMS &&
						(curr_game->cloneof==0 || curr_disk->merge==0)))
					{
						curr_game_zip_disk->game_zip=curr_game_zip_name_idx->game_zip;
						curr_game_zip_disk->disk=curr_disk;
	
						curr_game_zip_name_idx->game_zip->num_game_zip_disks++;
						dat->num_game_zip_disks++;
						curr_game_zip_disk++;
					}
				}
			}
		}
	}

	/* --- Once the game_zip array has been built, do the game_zip samples --- */

	curr_game_zip_sample=dat->game_zip_samples;

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		/* --- Locate ZIP --- */

		if ((dat->options->options & OPTION_DAT_FULL_MERGING) &&
			(curr_game->game_sampleof && !(curr_game->game_sampleof->game_flags & FLAG_RESOURCE_NAME)))
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game->sampleof, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);
		}
		else
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game->name, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);
		}

		/* --- Samples --- */

		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
		{
			if (dat->options->options & OPTION_DAT_NO_MERGING)
			{
				if (!(curr_game->game_flags & FLAG_RESOURCE_NAME))
				{
					curr_game_zip_sample->game_zip=curr_game_zip_name_idx->game_zip;
					curr_game_zip_sample->sample=curr_sample;

					curr_game_zip_name_idx->game_zip->num_game_zip_samples++;
					dat->num_game_zip_samples++;
					curr_game_zip_sample++;
				}
			}
			else
			{
				if ((!(dat->options->options & OPTION_NON_SEPERATED_BIOS_ROMS) && curr_sample->merge==0) ||
					(dat->options->options & OPTION_NON_SEPERATED_BIOS_ROMS &&
					(curr_game->cloneof==0 || curr_sample->merge==0)))
				{
					curr_game_zip_sample->game_zip=curr_game_zip_name_idx->game_zip;
					curr_game_zip_sample->sample=curr_sample;

					curr_game_zip_name_idx->game_zip->num_game_zip_samples++;
					dat->num_game_zip_samples++;
					curr_game_zip_sample++;
				}
			}
		}
	}

	/* --- Sort the game_zip ROMs, disks and samples --- */

	qsort(dat->game_zip_roms, dat->num_game_zip_roms, sizeof(struct game_zip_rom), game_zip_rom_sort_function);
	qsort(dat->game_zip_disks, dat->num_game_zip_disks, sizeof(struct game_zip_disk), game_zip_disk_sort_function);
	qsort(dat->game_zip_samples, dat->num_game_zip_samples, sizeof(struct game_zip_disk), game_zip_disk_sort_function);

	/* --- Remove duplicate game_zip_roms --- */

	curr_game_zip_rom=dat->game_zip_roms;
	num_game_zip_roms=dat->num_game_zip_roms;

	for (i=0, orig_game_zip_rom=dat->game_zip_roms; i<num_game_zip_roms; i++, orig_game_zip_rom++)
	{
		if (i>0 && !strcmp((curr_game_zip_rom-1)->game_zip->game->name, orig_game_zip_rom->game_zip->game->name) &&
			 !strcmp((curr_game_zip_rom-1)->rom->name, orig_game_zip_rom->rom->name))
		{
			orig_game_zip_rom->game_zip->num_game_zip_roms-=1;
			dat->num_game_zip_roms-=1;
		}
		else
		{
			if (curr_game_zip_rom!=orig_game_zip_rom)
				memcpy(curr_game_zip_rom, orig_game_zip_rom, sizeof(struct game_zip_rom));

			curr_game_zip_rom++;
		}
	}

	/* --- Link the game_zip_roms into the game_zips --- */

	for (i=0, curr_game_zip_rom=dat->game_zip_roms; i<dat->num_game_zip_roms; i++, curr_game_zip_rom++)
	{
		if (i==0 || strcmp(curr_game_zip_rom->game_zip->game->name, (curr_game_zip_rom-1)->game_zip->game->name))
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game_zip_rom->game_zip->game->name, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);

			curr_game_zip_name_idx->game_zip->game_zip_roms=curr_game_zip_rom;
		}
	}

	/* --- Remove duplicate game_zip_disks --- */

	curr_game_zip_disk=dat->game_zip_disks;
	num_game_zip_disks=dat->num_game_zip_disks;

	for (i=0, orig_game_zip_disk=dat->game_zip_disks; i<num_game_zip_disks; i++, orig_game_zip_disk++)
	{
		if (i>0 && !strcmp((curr_game_zip_disk-1)->game_zip->game->name, orig_game_zip_disk->game_zip->game->name) &&
			 !strcmp((curr_game_zip_disk-1)->disk->name, orig_game_zip_disk->disk->name))
		{
			orig_game_zip_disk->game_zip->num_game_zip_disks-=1;
			dat->num_game_zip_disks-=1;
		}
		else
		{
			if (curr_game_zip_disk!=orig_game_zip_disk)
				memcpy(curr_game_zip_disk, orig_game_zip_disk, sizeof(struct game_zip_disk));

			curr_game_zip_disk++;
		}
	}

	/* --- Link the game_zip_disks into the game_zips --- */

	for (i=0, curr_game_zip_disk=dat->game_zip_disks; i<dat->num_game_zip_disks; i++, curr_game_zip_disk++)
	{
		if (i==0 || strcmp(curr_game_zip_disk->game_zip->game->name, (curr_game_zip_disk-1)->game_zip->game->name))
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game_zip_disk->game_zip->game->name, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);

			curr_game_zip_name_idx->game_zip->game_zip_disks=curr_game_zip_disk;
		}
	}

	/* --- Remove duplicate game_zip_samples --- */

	curr_game_zip_sample=dat->game_zip_samples;
	num_game_zip_samples=dat->num_game_zip_samples;

	for (i=0, orig_game_zip_sample=dat->game_zip_samples; i<num_game_zip_samples; i++, orig_game_zip_sample++)
	{
		if (i>0 && !strcmp((curr_game_zip_sample-1)->game_zip->game->name, orig_game_zip_sample->game_zip->game->name) &&
			 !strcmp((curr_game_zip_sample-1)->sample->name, orig_game_zip_sample->sample->name))
		{
			orig_game_zip_sample->game_zip->num_game_zip_samples-=1;
			dat->num_game_zip_samples-=1;
		}
		else
		{
			if (curr_game_zip_sample!=orig_game_zip_sample)
				memcpy(curr_game_zip_sample, orig_game_zip_sample, sizeof(struct game_zip_sample));

			curr_game_zip_sample++;
		}
	}

	/* --- Link the game_zip_samples into the game_zips --- */

	for (i=0, curr_game_zip_sample=dat->game_zip_samples; i<dat->num_game_zip_samples; i++, curr_game_zip_sample++)
	{
		if (i==0 || strcmp(curr_game_zip_sample->game_zip->game->name, (curr_game_zip_sample-1)->game_zip->game->name))
		{
			curr_game_zip_name_idx=bsearch((void *)curr_game_zip_sample->game_zip->game->name, dat->game_zip_name_idx, dat->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);

			curr_game_zip_name_idx->game_zip->game_zip_samples=curr_game_zip_sample;
		}
	}

	/* --- Display it for testing purposes! --- */

	/*for (i=0, curr_game_zip=dat->game_zips; i<dat->num_game_zips; i++, curr_game_zip++)
	{
		printf("g: %s\n", curr_game_zip->game->name);

		for (j=0, curr_game_zip_rom=curr_game_zip->game_zip_roms; j<curr_game_zip->num_game_zip_roms; j++, curr_game_zip_rom++)
			printf("   r: %s (%08lx)\n", curr_game_zip_rom->rom->name, (unsigned long) curr_game_zip_rom->rom->crc);

		for (j=0, curr_game_zip_disk=curr_game_zip->game_zip_disks; j<curr_game_zip->num_game_zip_disks; j++, curr_game_zip_disk++)
			printf("   d: %s\n", curr_game_zip_disk->disk->name);

		for (j=0, curr_game_zip_sample=curr_game_zip->game_zip_samples; j<curr_game_zip->num_game_zip_samples; j++, curr_game_zip_sample++)
			printf("   s: %s\n", curr_game_zip_sample->sample->name);
	}*/

	return(errflg);
}

struct dat *init_dat(struct options *options)
{
	struct dat *dat=0;
	struct stat buf;
	uint32_t i, line_length=0, num_lines=0;
	int datlib_driver_matches=0, errflg=0;

	if (options->options & OPTION_SHOW_DEBUG_INFO)
		datlib_debug=1;

	/* --- Let's get started! --- */

	if (datlib_debug)
	{
		printf("\n%-16s: ", "Datlib.init_dat");
		printf("Started.\n");
	}
	else
	{
		if (!(options->options & OPTION_LOAD_QUIETLY))
			printf("Processing %s:\n", options->fn);
	}

	/* --- Allocate memory for main dat structure --- */

	if (datlib_debug)
	{
		printf("%-16s: ", "Datlib.init_dat");
		printf("Allocating memory for dat structure (%lu bytes)...\n", (unsigned long)sizeof(struct dat));
	}

	STRUCT_CALLOC(dat, 1, sizeof(struct dat))

	/* --- Remember the user options --- */

	if (!errflg)
	{
		/* --- Default extended checksum is SHA1 --- */

		if (!(options->options & OPTION_MD5_CHECKSUMS))
			options->options|=OPTION_SHA1_CHECKSUMS;

		dat->options=options;
	}

	/* --- Open the log file --- */

	if (!errflg && options->log_fn)
	{
		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.init_dat");
			printf("Creating log file (%s)...\n", options->log_fn);
		}

		dat->log_name=options->log_fn;
		FOPEN(dat->log_file, dat->log_name, "w")
	}

	/* --- Remember the dat name and check the file status --- */

	if (!errflg)
	{
		dat->name=options->fn;

		if (stat(dat->name, &buf)!=0)
		{
			fprintf(stderr, "File not found - '%s'.\n", dat->name);
			errflg++;
		}
	}

	/* --- Load game/sourcefile selection lists --- */

	if (!errflg && (dat->options->options & OPTION_GAME_SELECTION))
		errflg=load_game_selections(dat);

	if (!errflg && (dat->options->options & OPTION_SOURCEFILE_SELECTION))
		errflg=load_sourcefile_selections(dat);

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
					fprintf(stderr, "File not found - '%s'.\n", dat->name);
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
			if (!(options->options & OPTION_LOAD_QUIETLY))
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

	/* --- For all supported datlib_drivers, check which one is suitable --- */

	if (!errflg)
	{
		for (i=datlib_driver_matches=0; datlib_drivers[i]; i++)
		{
			if ((datlib_drivers[i]->identify)(dat))
			{
				if (datlib_debug)
				{
					printf("%-16s: ", "Datlib.init_dat");
					printf("Identified as %s format.\n", datlib_drivers[i]->description);
				}

				dat->load=(struct datlib_driver *)datlib_drivers[i];

				datlib_driver_matches++;
			}
		}

		/* --- Check if data file was identified successfully --- */

		switch (datlib_driver_matches)
		{
			/* --- If no datlib_drivers match, the format is not supported --- */

			case 0:
				if (!datlib_debug)
					fprintf(stderr, "Can't identify format of '%s'\n", options->fn);
				errflg++;
				break;

			/* --- If the is one datlib_driver match, the format is supported --- */

			case 1:
				if (!datlib_debug && !(options->options & OPTION_LOAD_QUIETLY))
					printf("  Identified the file as being '%s' format.\n", dat->load->description);
				break;

			/* --- If more than one datlib_driver match, the format is unknown! --- */

			default:
				fprintf(stderr, "Can't identify format of '%s'. Matches more than one type.\n", options->fn);
				errflg++;
				break;
		}
	}

	/* --- Default save format --- */

	if (!errflg)
	{
		/* --- Choose the first save datlib_driver that is different to the load datlib_driver --- */

		for (i=0; datlib_drivers[i]; i++)
		{
			if (!(dat->save) &&
				(strcmp(datlib_drivers[i]->description, dat->load->description) ||
				options->options & (OPTION_GAME_SELECTION|OPTION_SOURCEFILE_SELECTION|OPTION_REMOVE_CLONES))
			)
				dat->save=(struct datlib_driver *)datlib_drivers[i];
		}
	}

	/* --- For all supported datlib_drivers, check which one has been specified --- */

	if (!errflg && dat->options->save_format)
	{
		for (i=datlib_driver_matches=0; datlib_drivers[i]; i++)
		{
			if ((datlib_drivers[i]->specify)(dat))
			{
				if (datlib_debug)
				{
					printf("%-16s: ", "Datlib.init_dat");
					printf("Specified the save format as being '%s'.\n", datlib_drivers[i]->description);
				}

				dat->save=(struct datlib_driver *)datlib_drivers[i];

				datlib_driver_matches++;
			}
		}

		/* --- Check if data file was identified successfully --- */

		switch (datlib_driver_matches)
		{
			/* --- If no datlib_drivers match, the format is not supported --- */

			case 0:
				fprintf(stderr, "Unrecognised output format '%s'\n", options->save_format);
				errflg++;
				break;

			/* --- If the is one datlib_driver match, the format is supported --- */

			case 1:
				if (!datlib_debug && !(options->options & OPTION_LOAD_QUIETLY))
					printf("  Specified the save format as being '%s'.\n", dat->save->description);
				break;

			/* --- If more than one datlib_driver match, the format is unknown! --- */

			default:
				fprintf(stderr, "Can't identify save format '%s'. Matches more than one type.\n", options->save_format);
				errflg++;
				break;
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
		else if (!(options->options & OPTION_LOAD_QUIETLY))
			printf("  ");

		if (!(options->options & OPTION_LOAD_QUIETLY))
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

	if (!errflg && (options->options & OPTION_LOWER_CASE))
		errflg=lower_case(dat);

	if (!errflg && (options->options & OPTION_REMOVE_CLONES))
		errflg=remove_clones(dat);

	if (!errflg && (options->options & (OPTION_GAME_SELECTION|OPTION_SOURCEFILE_SELECTION)))
		errflg=game_sourcefile_selections(dat);

	if (!errflg && dat->num_games==0)
	{
		if (dat->options->game_selection || dat->options->sourcefile_selection)
			fprintf(stderr, "  Error - No games were loaded (check your game/sourcefile selections).\n");
		else
			fprintf(stderr, "  Error - No games were loaded.\n");

		errflg++;
	}

	if (!errflg && dat->options->info)
		errflg=add_missing_info(dat);

	if (!errflg)
		errflg=fix_descriptions(dat);

	if (!errflg && !(options->options & OPTION_FIX_MERGING_OFF))
		errflg=fix_merging_phase_1(dat);

	if (!errflg)
		errflg=identify_parents(dat);

	if (!errflg && !(options->options & OPTION_REMOVE_DUPLICATES_OFF))
		errflg=remove_duplicates(dat);

	if (!errflg)
		errflg=summarise_dat(dat);

	if (!errflg)
		errflg=rebuild_dat_indices(dat);

	if (!errflg && !(options->options & OPTION_FIX_MERGING_OFF))
		errflg=fix_merging_phase_2(dat);

	if (!errflg && dat->log_file)
		errflg=report_warnings(dat);

	if (!errflg && dat->log_file)
		errflg=report_fixes(dat);

	if (!errflg)
		errflg=build_zip_structures(dat);

	/* --- If any error occurred then throw everything away --- */

	if (errflg)
	{
		if (!datlib_debug && !(options->options & OPTION_LOAD_QUIETLY))
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
		if (!(options->options & OPTION_LOAD_QUIETLY))
			printf("Processing complete!\n");

		if (options->options & OPTION_SHOW_SUMMARY)
			printf("\nLoaded %lu games (%lu parents, %lu clones, %lu others) and %lu resources.\n", (unsigned long)dat->num_games-dat->num_resources, (unsigned long)dat->num_parents, (unsigned long)dat->num_clones, (unsigned long)dat->num_others, (unsigned long)dat->num_resources);

		if (options->log_fn)
		{
			if (dat->game_selection_warnings || dat->sourcefile_selection_warnings || dat->game_warnings || dat->comment_warnings || dat->biosset_warnings || dat->rom_warnings || dat->disk_warnings || dat->sample_warnings || dat->chip_warnings || dat->video_warnings || dat->sound_warnings || dat->input_warnings || dat->dipswitch_warnings || dat->dipvalue_warnings || dat->driver_warnings || dat->device_warnings || dat->extension_warnings || dat->archive_warnings)
				printf("\nNote: There are some warnings for the processing (see %s for details).\n", options->log_fn);

			if (dat->game_fixes || dat->rom_fixes || dat->disk_fixes || dat->sample_fixes)
				printf("\nNote: Fixes were applied to the data file (see %s for details).\n", options->log_fn);

			printf("-------------------------------------------------------------------------------\n");
		}
	}

	return(dat);
}


/* --------------------------------------------------------------------------
 * Function to save data files
 * -------------------------------------------------------------------------- */

int save_dat(struct dat *dat)
{
	int lost=0, errflg=0;

	if (!errflg)
	{
		if (dat->options->save_name && dat->options->save_mode)
		{
			if (datlib_debug)
			{
				printf("%-16s: ", "Datlib.save_dat");
				printf("Creating output file (%s)...\n", dat->options->save_name);
			}

			FOPEN(dat->out, dat->options->save_name, dat->options->save_mode)
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
			printf("Comment losses=%04x.\n", ~dat->comment_saved & dat->comment_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Biosset losses=%04x.\n", ~dat->biosset_saved & dat->biosset_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("ROM losses=%04x.\n", ~dat->rom_saved & dat->rom_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Disk losses=%02x.\n", ~dat->disk_saved & dat->disk_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Sample losses=%02x.\n", ~dat->sample_saved & dat->sample_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Chip losses=%02x.\n", ~dat->chip_saved & dat->chip_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Video losses=%02x.\n", ~dat->video_saved & dat->video_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Sound losses=%02x.\n", ~dat->sound_saved & dat->sound_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Input losses=%02x.\n", ~dat->input_saved & dat->input_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Dipswitch losses=%02x.\n", ~dat->dipswitch_saved & dat->dipswitch_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Dipvalue losses=%02x.\n", ~dat->dipvalue_saved & dat->dipvalue_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Driver losses=%02x.\n", ~dat->driver_saved & dat->driver_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Device losses=%02x.\n", ~dat->device_saved & dat->device_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Extension losses=%02x.\n", ~dat->extension_saved & dat->extension_flags);

			printf("%-16s: ", "Datlib.save_dat");
			printf("Archive losses=%02x.\n", ~dat->archive_saved & dat->archive_flags);
		}
		else
		{
			printf("Saved %s in %s format.\n", dat->options->save_name, dat->save->description);
		}

		/* --- Report information that could not be saved (ignore flags that are derived by DatLib) --- */
		 
		if (dat->log_file && (~dat->game_saved & dat->game_flags ||
			~dat->comment_saved & dat->comment_flags ||
			~dat->biosset_saved & dat->biosset_flags ||
			~dat->rom_saved & dat->rom_flags ||
			~dat->disk_saved & dat->disk_flags ||
			~dat->sample_saved & dat->sample_flags ||
			~dat->chip_saved & dat->chip_flags ||
			~dat->video_saved & dat->video_flags ||
			~dat->sound_saved & dat->sound_flags ||
			~dat->input_saved & dat->input_flags ||
			~dat->dipswitch_saved & dat->dipswitch_flags ||
			~dat->dipvalue_saved & dat->dipvalue_flags ||
			~dat->driver_saved & dat->driver_flags ||
			~dat->device_saved & dat->device_flags ||
			~dat->extension_saved & dat->extension_flags ||
			~dat->archive_saved & dat->archive_flags))
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

					if (lost & FLAG_GAME_SOURCEFILE)
						fprintf(dat->log_file, "    Sourcefile\n");
					if (lost & FLAG_GAME_CLONEOF)
						fprintf(dat->log_file, "    Clone Of\n");
					if (lost & FLAG_GAME_ROMOF)
						fprintf(dat->log_file, "    ROM Of\n");
					if (lost & FLAG_GAME_SAMPLEOF)
						fprintf(dat->log_file, "    Sample Of\n");
					if (lost & FLAG_GAME_DESCRIPTION)
						fprintf(dat->log_file, "    Description\n");
					if (lost & FLAG_GAME_YEAR)
						fprintf(dat->log_file, "    Year\n");
					if (lost & FLAG_GAME_MANUFACTURER)
						fprintf(dat->log_file, "    Manufacturer\n");
					if (lost & FLAG_GAME_HISTORY)
						fprintf(dat->log_file, "    History\n");
					if (lost & FLAG_GAME_REBUILDTO)
						fprintf(dat->log_file, "    Rebuild To\n");
					if (lost & FLAG_GAME_BOARD)
						fprintf(dat->log_file, "    Board\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- Comments --- */

			if ((lost=~dat->comment_saved & dat->comment_flags))
			{
				if (lost & FLAG_COMMENT_TEXT)
					fprintf(dat->log_file, "Comments have been lost entirely!\n\n");
			}

			/* --- BIOS Sets --- */

			if ((lost=~dat->biosset_saved & dat->biosset_flags))
			{
				if (lost & FLAG_BIOSSET_NAME)
					fprintf(dat->log_file, "BIOS sets have been lost entirely!\n\n");
				else
				{
					fprintf(dat->log_file, "BIOS set information that has been lost:\n\n");

					if (lost & FLAG_BIOSSET_DESCRIPTION)
						fprintf(dat->log_file, "    Description\n");
					if (lost & FLAG_BIOSSET_DEFAULT)
						fprintf(dat->log_file, "    Default\n");

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

					if (lost & FLAG_ROM_BIOS)
						fprintf(dat->log_file, "    BIOS\n");
					if (lost & FLAG_ROM_SIZE)
						fprintf(dat->log_file, "    Size\n");
					if (lost & FLAG_ROM_CRC)
						fprintf(dat->log_file, "    CRC\n");
					if (lost & FLAG_ROM_MD5)
						fprintf(dat->log_file, "    MD5\n");
					if (lost & FLAG_ROM_SHA1)
						fprintf(dat->log_file, "    SHA1\n");
					if (lost & FLAG_ROM_MERGE)
						fprintf(dat->log_file, "    Merge\n");
					if (lost & FLAG_ROM_OFFSET)
						fprintf(dat->log_file, "    Offset\n");
					if (lost & FLAG_ROM_REGION)
						fprintf(dat->log_file, "    Region\n");
					if (lost & FLAG_ROM_STATUS)
						fprintf(dat->log_file, "    Status (may have used zero and complemented CRCs instead)\n");
					if (lost & FLAG_ROM_DISPOSE)
						fprintf(dat->log_file, "    Dispose\n");
					if (lost & FLAG_ROM_SOUNDONLY)
						fprintf(dat->log_file, "    Sound only\n");

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
					if (lost & FLAG_DISK_MERGE)
						fprintf(dat->log_file, "    Merge\n");
					if (lost & FLAG_DISK_REGION)
						fprintf(dat->log_file, "    Region\n");
					if (lost & FLAG_DISK_INDEX)
						fprintf(dat->log_file, "    Index\n");
					if (lost & FLAG_DISK_STATUS)
						fprintf(dat->log_file, "    Status (may have used zero and complemented checksums instead)\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- Samples --- */

			if ((lost=~dat->sample_saved & dat->sample_flags))
			{
				if (lost & FLAG_SAMPLE_NAME)
					fprintf(dat->log_file, "Samples have been lost entirely!\n\n");
			}

			/* --- Chips --- */

			if ((lost=~dat->chip_saved & dat->chip_flags))
			{
				if (lost & FLAG_CHIP_TYPE)
					fprintf(dat->log_file, "Chips have been lost entirely!\n\n");
				else
				{
					fprintf(dat->log_file, "Chip information that has been lost:\n\n");

					if (lost & FLAG_CHIP_NAME)
						fprintf(dat->log_file, "    Name\n");
					if (lost & FLAG_CHIP_SOUNDONLY)
						fprintf(dat->log_file, "    Sound only\n");
					if (lost & FLAG_CHIP_CLOCK)
						fprintf(dat->log_file, "    Clock\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- Video --- */

			if ((lost=~dat->video_saved & dat->video_flags))
			{
				if (lost & FLAG_VIDEO_SCREEN)
					fprintf(dat->log_file, "Videos have been lost entirely!\n\n");
				else
				{
					fprintf(dat->log_file, "Video information that has been lost:\n\n");

					if (lost & FLAG_VIDEO_ORIENTATION)
						fprintf(dat->log_file, "    Orientation\n");
					if (lost & FLAG_VIDEO_WIDTH)
						fprintf(dat->log_file, "    Width\n");
					if (lost & FLAG_VIDEO_HEIGHT)
						fprintf(dat->log_file, "    Height\n");
					if (lost & FLAG_VIDEO_ASPECTX)
						fprintf(dat->log_file, "    Aspect X\n");
					if (lost & FLAG_VIDEO_ASPECTY)
						fprintf(dat->log_file, "    Aspect Y\n");
					if (lost & FLAG_VIDEO_REFRESH)
						fprintf(dat->log_file, "    Refresh\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- Sounds --- */

			if ((lost=~dat->sound_saved & dat->sound_flags))
			{
				if (lost & FLAG_SOUND_CHANNELS)
					fprintf(dat->log_file, "Sounds have been lost entirely!\n\n");
			}

			/* --- Inputs --- */

			if ((lost=~dat->input_saved & dat->input_flags))
			{
				if (lost & FLAG_INPUT_PLAYERS)
					fprintf(dat->log_file, "Inputs have been lost entirely!\n\n");
				else
				{
					fprintf(dat->log_file, "Input information that has been lost:\n\n");

					if (lost & FLAG_INPUT_SERVICE)
						fprintf(dat->log_file, "    Service\n");
					if (lost & FLAG_INPUT_TILT)
						fprintf(dat->log_file, "    Tilt\n");
					if (lost & FLAG_INPUT_CONTROL)
						fprintf(dat->log_file, "    Control\n");
					if (lost & FLAG_INPUT_BUTTONS)
						fprintf(dat->log_file, "    Buttons\n");
					if (lost & FLAG_INPUT_COINS)
						fprintf(dat->log_file, "    Coins\n");
					if (lost & FLAG_INPUT_DIPSWITCHES)
						fprintf(dat->log_file, "    Dipswitches\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- DIP Switches --- */

			if ((lost=~dat->dipswitch_saved & dat->dipswitch_flags))
			{
				if (lost & FLAG_DIPSWITCH_NAME)
					fprintf(dat->log_file, "DIP switches have been lost entirely!\n\n");
			}

			/* --- DIP Values --- */

			if ((lost=~dat->dipvalue_saved & dat->dipvalue_flags))
			{
				if (lost & FLAG_DIPVALUE_NAME)
					fprintf(dat->log_file, "DIP values have been lost entirely!\n\n");
				else
				{
					fprintf(dat->log_file, "DIP value information that has been lost:\n\n");

					if (lost & FLAG_DIPVALUE_DEFAULT)
						fprintf(dat->log_file, "    Default\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- Driver --- */

			if ((lost=~dat->driver_saved & dat->driver_flags))
			{
				if (lost & FLAG_DRIVER_STATUS)
					fprintf(dat->log_file, "Drivers have been lost entirely!\n\n");
				else
				{
					fprintf(dat->log_file, "Driver information that has been lost:\n\n");

					if (lost & FLAG_DRIVER_EMULATION)
						fprintf(dat->log_file, "    Emulation\n");
					if (lost & FLAG_DRIVER_COLOR)
						fprintf(dat->log_file, "    Color\n");
					if (lost & FLAG_DRIVER_SOUND)
						fprintf(dat->log_file, "    Sound\n");
					if (lost & FLAG_DRIVER_GRAPHIC)
						fprintf(dat->log_file, "    Graphic\n");
					if (lost & FLAG_DRIVER_COCKTAIL)
						fprintf(dat->log_file, "    Cocktail\n");
					if (lost & FLAG_DRIVER_PROTECTION)
						fprintf(dat->log_file, "    Protection\n");
					if (lost & FLAG_DRIVER_PALETTESIZE)
						fprintf(dat->log_file, "    Palettesize\n");
					if (lost & FLAG_DRIVER_COLORDEEP)
						fprintf(dat->log_file, "    Colordeep\n");
					if (lost & FLAG_DRIVER_CREDITS)
						fprintf(dat->log_file, "    Credits\n");

					fprintf(dat->log_file, "\n");
				}
			}

			/* --- Devices --- */

			if ((lost=~dat->device_saved & dat->device_flags))
			{
				if (lost & FLAG_DEVICE_NAME)
					fprintf(dat->log_file, "Devices have been lost entirely!\n\n");
			}

			/* --- Extensions --- */

			if ((lost=~dat->extension_saved & dat->extension_flags))
			{
				if (lost & FLAG_EXTENSION_NAME)
					fprintf(dat->log_file, "Extensions have been lost entirely!\n\n");
			}

			/* --- Extensions --- */

			if ((lost=~dat->archive_saved & dat->archive_flags))
			{
				if (lost & FLAG_ARCHIVE_NAME)
					fprintf(dat->log_file, "Archives have been lost entirely!\n\n");
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

int find_disk_by_crc(const void *crc, const void *disk_idx)
{
	if (*((uint32_t *)crc) < ((struct disk_idx *)disk_idx)->disk->crc)
		return(-1);

	if (*((uint32_t *)crc) > ((struct disk_idx *)disk_idx)->disk->crc)
		return(1);

	return(0);
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
			printf("Freeing memory of archives...\n");
		}
		FREE(dat->archives)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of extensions...\n");
		}
		FREE(dat->extensions)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of devices...\n");
		}
		FREE(dat->devices)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of drivers...\n");
		}
		FREE(dat->drivers)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of dipvalues...\n");
		}
		FREE(dat->dipvalues)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of dipswitches...\n");
		}
		FREE(dat->dipswitches)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of inputs...\n");
		}
		FREE(dat->inputs)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of sounds...\n");
		}
		FREE(dat->sounds)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of videos...\n");
		}
		FREE(dat->videos)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of chips...\n");
		}
		FREE(dat->chips)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of samples and sample indices...\n");
		}
		FREE(dat->game_zip_samples)
		FREE(dat->sample_name_idx)
		FREE(dat->game_sample_name_idx)
		FREE(dat->samples)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of disks and disk indices...\n");
		}
		FREE(dat->game_zip_disks)
		FREE(dat->disk_crc_idx)
		FREE(dat->disk_name_idx)
		FREE(dat->game_disk_crc_idx)
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
			printf("Freeing memory of bios sets...\n");
		}
		FREE(dat->biossets)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of comments...\n");
		}
		FREE(dat->comments)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of games and game indices...\n");
		}
		FREE(dat->game_zip_name_idx)
		FREE(dat->game_zips)
		FREE(dat->game_score_idx)
		FREE(dat->game_crc_idx)
		FREE(dat->game_description_idx)
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

		if (dat->name && !strcmp(dat->name, "datlib.tmp"))
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
			printf("Freeing memory of sourcefile selections...\n");
		}
		FREE(dat->options->sourcefile_selections)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of sourcefile selection buffer...\n");
		}
		FREE(dat->options->sourcefile_selection_buffer)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of game selections...\n");
		}
		FREE(dat->options->game_selections)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of game selection buffer...\n");
		}
		FREE(dat->options->game_selection_buffer)

		if (datlib_debug)
		{
			printf("%-16s: ", "Datlib.free_dat");
			printf("Freeing memory of dat structure...\n");
		}
		FREE(dat)
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
	FREE(ini)

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

