/* --------------------------------------------------------------------------
 * ZIPIdent - Written by Logiqx (http://www.logiqx.com/)
 *
 * Little tool that tries to identify ZIP files that are emulated by MAME
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define ZIPIDENT_VERSION "v2.2"
#define ZIPIDENT_DATE "22 July 2004"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"
#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"
#include "datlib/src/mame/unzip.h"


/* --- ZipIdent definitions and macros --- */

#include "zipident.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


/* --------------------------------------------------------------------------
 * The main() function
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	/* --- For getopt function --- */

	extern int optind;

	struct stat buf;

	FILE *definite=0, *maybe=0;

	struct options *options=0;
	struct dat *dat=0;
	struct game_match *game_match=0;
	char st[MAX_STRING_LENGTH+1];
	char path[MAX_FILENAME_LENGTH+1];
	char defpath[MAX_FILENAME_LENGTH+1]="";

	int i, delete=0, scan_type=0;
	char c;
	int errflg=0;

	printf("===============================================================================\n");
	printf("ZIPIdent %s (%s) - using ", ZIPIDENT_VERSION, ZIPIDENT_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	while (!errflg && (c = getopt(argc, argv, "dt?")) != EOF)
	switch (c)
	{
		case 'd':
			delete++;
			break;
		case 't':
			scan_type=SCAN_TEXT;
			break;
		case '?':
			errflg++;														/* User wants help! */
	}

	/* --- Display the help page if required --- */

	if (argc-optind<1)
	{
		printf("Usage: zipident [-d] [-t] <file spec>\n");
		errflg++;
	}

	/* --- Load the data file --- */

	if (!errflg)
	{
		sprintf(st, ".");

		while (strchr(argv[0], '\\'))
			*strchr(argv[0], '\\')='/';

		if (strchr(argv[0], '/'))
		{
			strcpy(st, argv[0]);
			*strrchr(st, '/')='\0';
		}

		strcat(st, "/zipident.dat");
	}

	/* --- Allocate memory for user options --- */

	STRUCT_CALLOC(options, 1, sizeof(struct options))

	if (!errflg)
	{
		options->options=OPTION_LOWER_CASE|OPTION_SHOW_SUMMARY;
		options->fn=st;
	}

	/* --- Initialise the dat --- */

	if (!errflg && (dat=init_dat(options))==0)
		errflg++;

	if (!errflg)
		STRUCT_CALLOC(game_match, dat->num_games, sizeof(struct game_match))
	
	/* --- Initialise all logs etc --- */

	for (i=optind; !errflg && i<argc; i++)
	{
		/* --- Swap DOS delimiters to Unix --- */

		while (strchr(argv[i], '\\'))
			*strchr(argv[i], '\\')='/';

		while (argv[i][strlen(argv[i])-1]=='/')
			argv[i][strlen(argv[i])-1]='\0';

		if (stat(argv[i], &buf) == 0)
		{
			/* --- If no path specified then use . --- */

			sprintf(path, ".");

			if (buf.st_mode & S_IFDIR)
			{
				strcpy(path, argv[i]);
			}
			else if (strchr(argv[i], '/'))
			{
				strcpy(path, argv[i]);
				*strrchr(path, '/')='\0';
			}

			sprintf(st, "%s/zipident_definite.log", path);
			FOPEN(definite, st, "w")

			if (!errflg)
				fprintf(definite, "ZIPIdent - ZIPs that are definitely safe to remove (i.e. fully identified)\n\n");

			sprintf(st, "%s/zipident_maybe.log", path);
			FOPEN(maybe, st, "w")

			if (!errflg)
				fprintf(maybe, "ZIPIdent - ZIPs that may be safe to remove (i.e. partially identified)\n\n");

			FCLOSE(maybe)
			FCLOSE(definite)

			if (delete)
			{
				sprintf(st, "%s/_zipident_definite", path);
				
				if (stat(st, &buf) == 0)
				{
					if (!(buf.st_mode & S_IFDIR))
					{
						printf("_zipident_deleted could not be created because a file of that name exists!\n");
						errflg++;
					}
				}
				else
				{
					MKDIR(st, S_IRWXU)
					if (stat(st, &buf) != 0)
					{
						printf("_zipident_deleted could not be created!\n");
						errflg++;
					}
				}
			}
		}
		else
		{
			printf("Error getting attributes of %s\n", argv[i]);
			errflg++;
		}
	}

	/* --- Process all files/dirs in filespec --- */

	for (i=optind; !errflg && i<argc; i++)
	{
		if (stat(argv[i], &buf) == 0)
		{
			if (scan_type==0)
			{
				if (buf.st_mode & S_IFDIR)
					scan_type=SCAN_DIR;
				else
					scan_type=SCAN_FILE;
			}

			/* --- If no path specified then use . --- */

			sprintf(path, ".");

			if (buf.st_mode & S_IFDIR)
			{
				strcpy(path, argv[i]);
			}
			else if (strchr(argv[i], '/'))
			{
				strcpy(path, argv[i]);
				*strrchr(path, '/')='\0';
			}

			sprintf(st, "%s/zipident_definite.log", path);
			FOPEN(definite, st, "a")

			sprintf(st, "%s/zipident_maybe.log", path);
			FOPEN(maybe, st, "a")

			if (delete)
			{
				sprintf(st, "%s/_zipident_definite", path);
				strcpy(defpath, st);
			}
		}
		else
		{
			printf("Error getting attributes of %s\n", argv[i]);
			errflg++;
		}

		/* --- Do the clever stuff! --- */

		if (!errflg)
		{
			switch (scan_type)
			{
				case SCAN_DIR:
					errflg=scan_dir(definite, maybe, dat, game_match, argv[i], defpath);
					break;
				case SCAN_TEXT:
					errflg=process_text(definite, maybe, dat, game_match, argv[i], defpath);
					break;
				case SCAN_FILE:
					errflg=process_zip(definite, maybe, dat, game_match, argv[i], defpath);
					break;
			}
		}

		/* --- Cleanup and exit --- */

		FCLOSE(maybe)
		FCLOSE(definite)
	}

	FREE(game_match)

	dat=free_dat(dat);

	FREE(options)

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Directory scanning is recursive
 * -------------------------------------------------------------------------- */

int scan_dir(FILE *definite, FILE *maybe, struct dat *dat, struct game_match *game_match, char *dir, char *defpath)
{
	DIR *dirp;
	struct dirent *direntp;
	struct stat buf;
	char fn[MAX_FILENAME_LENGTH+1];
	int errflg=0;

	if (!strstr(dir, "_zipident_definite"))
	{
		printf("Scanning %s...\n", dir);

		if ((dirp=opendir(dir))==0)
			errflg++;

		while (!errflg && ((direntp = readdir(dirp)) != NULL))
		{
			sprintf(fn, "%s/%s", dir, direntp->d_name);
			if (stat(fn, &buf) == 0)
			{
				if (!(buf.st_mode & S_IFDIR))
				{
					process_zip(definite, maybe, dat, game_match, fn, defpath);
				}
				else
				{
					if (fn[strlen(fn)-1]!='.')	/* Don't try . or .. entries */
						errflg=scan_dir(definite, maybe, dat, game_match, fn, defpath);
				}
			}
			else
			{
				printf("Error getting attributes of %s\n", direntp->d_name);
			}
		}

		if (dirp)
			closedir(dirp);
	}

	return(errflg);
}

int process_text(FILE *definite, FILE *maybe, struct dat *dat, struct game_match *game_match, char *fn, char *defpath)
{
	struct zip_entry *zip_entry;
	
	FILE *in=0;
	char st[MAX_STRING_LENGTH+1];
	char prev_zip[MAX_FILENAME_LENGTH+1]="";
	char zip[MAX_FILENAME_LENGTH+1];
	int num_zip_entries=0, invalid=0, errflg=0;
	char *ptr;

	STRUCT_CALLOC(zip_entry, MAX_ZIP_ENTRIES, sizeof(struct zip_entry))

	FOPEN(in, fn, "r")

	while (!errflg && fgets(st, MAX_STRING_LENGTH, in))
	{
		REMOVE_CR_LF(st)
		invalid=0;

		if ((ptr=strtok(st, " "))!=0)
			strcpy(zip, ptr);
		else
			invalid++;

		if ((ptr=strtok(NULL, " "))!=0)
		{
			strcpy(zip_entry[num_zip_entries].name, ptr);
			strcpy(zip_entry[num_zip_entries].lname, zip_entry[num_zip_entries].name);
			LOWER(zip_entry[num_zip_entries].lname)
		}
		else
			invalid++;

		if ((ptr=strtok(NULL, " "))!=0)
			zip_entry[num_zip_entries].size=strtoul(ptr, NULL, 10);
		else
			invalid++;

		if ((ptr=strtok(NULL, " "))!=0)
			zip_entry[num_zip_entries].crc=strtoul(ptr, NULL, 16);
		else
			invalid++;

		zip_entry[num_zip_entries].region=0;
		zip_entry[num_zip_entries].match=0;

		if (prev_zip[0]==0 || !strcmp(prev_zip, zip))
		{
			if (invalid==0)
			{
				if (num_zip_entries<MAX_ZIP_ENTRIES-1)
					num_zip_entries++;
			}
			else
				printf("Invalid line in %s\n", fn);
		}
		else
		{
			if (invalid==0)
			{
				process_entries(definite, maybe, dat, game_match, prev_zip, zip_entry, num_zip_entries, defpath);
	
				strcpy(zip_entry[0].name, zip_entry[num_zip_entries].name);
				strcpy(zip_entry[0].lname, zip_entry[num_zip_entries].lname);
				zip_entry[0].size=zip_entry[num_zip_entries].size;
				zip_entry[0].crc=zip_entry[num_zip_entries].crc;
				zip_entry[0].region=0;
				zip_entry[0].match=0;

				num_zip_entries=1;
			}
			else
				printf("Invalid line in %s\n", fn);
		}

		strcpy(prev_zip, zip);
	}

	if (num_zip_entries)
	{
		process_entries(definite, maybe, dat, game_match, prev_zip, zip_entry, num_zip_entries, defpath);
	}

	FCLOSE(in)

	FREE(zip_entry)

	return(errflg);
}

int process_zip(FILE *definite, FILE *maybe, struct dat *dat, struct game_match *game_match, char *fn, char *defpath)
{
	struct zip_entry zip_entry[MAX_ZIP_ENTRIES];
	
	ZIP *zip;
	struct zipent *zipent;
	char st[MAX_STRING_LENGTH+1];
	int num_zip_entries=0, errflg=0;

	strcpy(st, fn);
	LOWER(st)

	if (strrchr(st, '.') && !strcmp(strrchr(st, '.'), ".zip"))
	{
		if ((zip = openzip(fn)))
		{
			/* --- Read all entries from the ZIP--- */

			while ((zipent = readzip(zip)) != 0 && num_zip_entries < MAX_ZIP_ENTRIES)
			{
				strcpy(zip_entry[num_zip_entries].name, zipent->name);
				strcpy(zip_entry[num_zip_entries].lname, zipent->name);
				LOWER(zip_entry[num_zip_entries].lname)
				zip_entry[num_zip_entries].size=zipent->uncompressed_size;
				zip_entry[num_zip_entries].crc=zipent->crc32;
				zip_entry[num_zip_entries].region=0;
				zip_entry[num_zip_entries].match=0;

				num_zip_entries++;
			}
			closezip(zip);

			process_entries(definite, maybe, dat, game_match, fn, zip_entry, num_zip_entries, defpath);
		}
		else
		{
			LRPAD(st, fn, "=", 80)
			fprintf(maybe, "%s\n\n", st);
          		fprintf(maybe,"The zipfile seems to be corrupt, please check it\n\n");
		}
	}

	return(errflg);
}

int process_entries(FILE *definite, FILE *maybe, struct dat *dat, struct game_match *game_match, char *fn, struct zip_entry *zip_entry, int num_zip_entries, char *defpath)
{
	FILE *out=0;
	char st[MAX_STRING_LENGTH+1];
	int max_length=0;
	int num_game_matches=0;
	struct rom_idx *rom_match;
	int match;
	int i, j, found, bits;
	int game_size, zip_size;
	double game_score, zip_score, best_score=0;
	int errflg=0;

	strcpy(st, fn);
	LOWER(st)

	if (strrchr(st, '.') && !strcmp(strrchr(st, '.'), ".zip"))
	{
		printf("Processing %s...\n", fn);

		for (i=0; i<num_zip_entries; i++)
			if (strlen(zip_entry[i].name)>max_length)
				max_length=strlen(zip_entry[i].name);

		/* --- Search for ROM matches --- */

		for (i=0; i<num_zip_entries; i++)
		{
			/* --- ZIP entries without a size and CRC are directories --- */

			if (zip_entry[i].crc && zip_entry[i].size)
			{
				/* --- Readme files rarely have binary sizes and are less than 1MB! --- */

				for (bits=j=0; j < 32; j++)
				{
					if ((1<<j) & zip_entry[i].size)
					bits++;
				}
							
				if (bits>1 && zip_entry[i].size<1048576)
				{
					zip_entry[i].region="readme";
					zip_entry[i].match=SIZE_MATCH;
				}

				/* --- Dummy ROMs have a preditable CRC (in the .h source) --- */

				j=0;
				while (dummy_roms[j].size)
				{
					if (zip_entry[i].size==dummy_roms[j].size && zip_entry[i].crc==dummy_roms[j].crc)
					{
						zip_entry[i].region="dummy";
						zip_entry[i].match=CRC_MATCH|SIZE_MATCH;
					}
					j++;
				}

				/* --- CRC match --- */

				rom_match=bsearch((const void *)&zip_entry[i].crc, dat->rom_crc_idx, dat->num_roms, sizeof(struct rom_idx), find_rom_by_crc);

				if (rom_match!=0)
				{
					while(rom_match > dat->rom_crc_idx && rom_match[0].rom->crc==rom_match[-1].rom->crc)
						rom_match--;

					while(rom_match < dat->rom_crc_idx+((dat->num_roms-1)) &&
						rom_match->rom->crc==zip_entry[i].crc)
					{
						MATCH_ROM
					}
				}

				/* --- Complimented CRC match --- */
	
				rom_match=bsearch((const void *)&zip_entry[i].crc, dat->rom_crc_idx, dat->num_roms, sizeof(struct rom_idx), find_rom_by_comp_crc);

				if (rom_match!=0)
				{
					while(rom_match > dat->rom_crc_idx && rom_match[0].rom->crc==rom_match[-1].rom->crc)
						rom_match--;

					while(rom_match < dat->rom_crc_idx+((dat->num_roms-1)) &&
						rom_match->rom->crc==~zip_entry[i].crc)
					{
						MATCH_ROM
					}
				}

				/* --- Name match --- */

				rom_match=bsearch((void *)zip_entry[i].lname, dat->rom_name_idx, dat->num_roms, sizeof(struct rom_idx), find_rom_by_name);

				if (rom_match!=0)
				{
					while(rom_match > dat->rom_name_idx && !strcmp(rom_match[0].rom->name, rom_match[-1].rom->name))
						rom_match--;

					while(rom_match < dat->rom_name_idx+((dat->num_roms-1)) &&
						!strcmp(rom_match->rom->name, zip_entry[i].lname))
					{
						MATCH_ROM
					}
				}
			}
			else
			{
				zip_entry[i].region="folder";
				zip_entry[i].match=CRC_MATCH|SIZE_MATCH;
			}
		}

		/* --- Give the ZIP a CRC-only score for non-dummy/readme/folders --- */

		zip_score=zip_size=0;
		for (j=0; j<num_zip_entries; j++)
		{
			if (zip_entry[j].region==0 ||
				(strcmp(zip_entry[j].region, "dummy") &&
				strcmp(zip_entry[j].region, "readme") &&
				strcmp(zip_entry[j].region, "folder")))
			{
				zip_size+=zip_entry[j].size;

				/* --- We are only counting CRC matches --- */

				if (zip_entry[j].match & CRC_MATCH)
					zip_score+=zip_entry[j].size*PERFECT_MATCH;
			}
		}
		zip_score=zip_score/zip_size/PERFECT_MATCH;

		/* --- Give the ZIP a score if all files are dummy/readme/folder or scored >0.05 --- */

		if (zip_size==0 || zip_score>=0.02)
		{
			if (zip_size==0 || zip_score==1)
			{
				out=definite;
				if (defpath[0])
				{
					if (strchr(fn, '/'))
						sprintf(st, "%s/%s", defpath, strrchr(fn, '/')+1);
					else
						sprintf(st, "%s/%s", defpath, fn);
					rename(fn, st);
				}
			}
			else
				out=maybe;

			zip_score=zip_size=0;
			for (j=0; j<num_zip_entries; j++)
			{
				zip_size+=zip_entry[j].size;

				/* --- count readme files as perfect match --- */

				if (zip_entry[j].region!=0 && !strcmp(zip_entry[j].region, "readme"))
					zip_score+=zip_entry[j].size*PERFECT_MATCH;
				else
					zip_score+=zip_entry[j].size*zip_entry[j].match;
			}
			zip_score=zip_score/zip_size/PERFECT_MATCH;
		}
		else
		{
			/* --- Okay, we've ruled this out! --- */

			zip_score=0;
		}

		if (zip_score>0)
		{
			LRPAD(st, fn, "=", 80)
			fprintf(out, "%s\n\n", st);
	
			//fprintf(out, "Score: %f\n", zip_score);

			/* --- Give each matched game a score --- */
			if (num_game_matches>0)
			{
				for (i=0; i<num_game_matches; i++)
				{
					game_score=game_size=0;
					for (j=0; j<game_match[i].game->num_roms; j++)
					{
						game_size+=game_match[i].game->roms[j].size;

						/* --- Do not include name only matches in the score (too loose) --- */

						if (game_match[i].game->roms[j].match >= CRC_MATCH)
							game_score+=game_match[i].game->roms[j].size*game_match[i].game->roms[j].match;
					}
					game_score=game_score/game_size/PERFECT_MATCH;
					game_match[i].score=game_score;
	
					if (game_score>best_score)
						best_score=game_score;
				}
	
				/* --- Report the best matched game --- */
	
				if (best_score>0)
				{
					fprintf(out, "Most likely match(es):\n\n");
					for (i=0; i<num_game_matches; i++)
					{
						if (game_match[i].score==best_score)
						{
							FORMAT_GAME_NAME(st, game_match[i].game)
	
							fprintf(out, "%s\n", st);
						}
					}
					fprintf(out, "\n");
				}
			}

			/* --- Show information for the individual ZIP entries --- */
	
			fprintf(out, "ZIP summary:\n\n");
			for (i=0; i<max_length-4; i++)
				fprintf(out, " ");
			fprintf(out, "Name     Size       CRC   Region  Matched using\n");
			for (i=0; i<max_length-4; i++)
				fprintf(out, "-");
			fprintf(out, "----  --------  --------  ------  -----------------\n");

			for (i=0; i<num_zip_entries; i++)
			{
				if (zip_entry[i].region!=0)
				{
					sprintf(st, "%%%ds  %%8d  %%08lx %%7s  ", max_length);
					fprintf(out, st,
						zip_entry[i].name, zip_entry[i].size, zip_entry[i].crc, zip_entry[i].region);
				}
				else
				{
					sprintf(st, "%%%ds  %%8d  %%08lx          ", max_length);
					fprintf(out, st,
						zip_entry[i].name, zip_entry[i].size, zip_entry[i].crc);
				}

				switch(zip_entry[i].match)
				{
					case 0:
						fprintf(out, "*** NONE ***");
						break;
					case SIZE_MATCH:
						fprintf(out, "size");
						break;
					case NAME_MATCH:
						fprintf(out, "name");
						break;
					case NAME_MATCH|SIZE_MATCH:
						fprintf(out, "name + size");
						break;
					case CRC_MATCH:
						fprintf(out, "crc");
						break;
					case CRC_MATCH|SIZE_MATCH:
						fprintf(out, "crc + size");
						break;
					case CRC_MATCH|NAME_MATCH:
						fprintf(out, "crc + name");
						break;
					case CRC_MATCH|NAME_MATCH|SIZE_MATCH:
						fprintf(out, "crc + name + size");
						break;
				}

				fprintf(out,"\n");
			}	

			fprintf(out,"\n\n");

			/* --- Clear scores --- */

			for (i=0; i<num_game_matches; i++)
			{
				for (j=0; j<game_match[i].game->num_roms; j++)
					game_match[i].game->roms[j].match=0;
				game_match[i].score=0;
			}
		}
	}

	return(errflg);
}

