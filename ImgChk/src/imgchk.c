/* --------------------------------------------------------------------------
 * ImgChk - Written by Logiqx (http://www.logiqx.com)
 *
 * A simple little utility for checking resource images
 * -------------------------------------------------------------------------- */

#define IMGCHK_VERSION "v2.0"
#define IMGCHK_DATE "2 July 2004"


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


/* --- ImgChk definitions and macros --- */

#include "imgchk.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


/* --------------------------------------------------------------------------
 * The main() function
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	struct ini_entry *ini=0;
	struct dat *dat=0;

	char st[MAX_STRING_LENGTH+1];

	int i=1, done=0;
	int errflg=0;

	printf("===============================================================================\n");
	printf("ImgChk %s (%s) - using ", IMGCHK_VERSION, IMGCHK_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com)\n");
	printf("===============================================================================\n");

	/* --- Read INI options --- */

	if (!errflg && !(ini=load_ini("imgchk.ini")))
		errflg++;

	if (!errflg && find_ini_value(ini, "Dat", "Dat"))
	{
		if ((dat=init_dat(find_ini_value(ini, "Dat", "Dat"), OPTION_SHOW_SUMMARY, 0, 0))==0)
			errflg++;
	}
	else
	{
		printf("Error: Dat not declared properly in the INI file!\n");
		errflg++;
	}

	while (!errflg && !done)
	{
		sprintf(st, "Zip%d", i);

		if (find_ini_value(ini, "Zips", st))
			process_section(ini, dat, find_ini_value(ini, "Zips", st));
		else
			done++;

		i++;
	}

	dat=free_dat(dat);
	ini=free_ini(ini);

	return(errflg);
}

int process_section(struct ini_entry *ini, struct dat *dat, char *section)
{
	int report_unknown=0, report_missing=0, allow_clones=1, allow_resources=1;
	char *img_ext=0;

	struct stat buf;

	int i;
	int errflg = 0;

	for (i=0; i<dat->num_games; i++)
		dat->games[i].match=0;

	if (find_ini_value(ini, section, "ImgExt"))
		img_ext=find_ini_value(ini, section, "ImgExt");

	if (find_ini_value(ini, section, "ReportUnknown"))
		report_unknown=atoi(find_ini_value(ini, section, "ReportUnknown"));

	if (find_ini_value(ini, section, "ReportMissing"))
		report_missing=atoi(find_ini_value(ini, section, "ReportMissing"));

	if (find_ini_value(ini, section, "AllowClones"))
		allow_clones=atoi(find_ini_value(ini, section, "AllowClones"));

	if (find_ini_value(ini, section, "AllowResources"))
		allow_resources=atoi(find_ini_value(ini, section, "AllowResources"));

	if ((find_ini_value(ini, section, "ZipFile") && (stat(find_ini_value(ini, section, "ZipFile"), &buf) == 0)) ||
		(find_ini_value(ini, section, "Directory") && (stat(find_ini_value(ini, section, "Directory"), &buf) == 0)))
	{
		printf("\nTesting %s...\n", section);

		if (find_ini_value(ini, section, "ZipFile"))
			check_zip(dat, find_ini_value(ini, section, "ZipFile"), img_ext, report_unknown, report_missing, allow_clones, allow_resources);

		if (find_ini_value(ini, section, "Directory"))
			check_dir(dat, find_ini_value(ini, section, "Directory"), img_ext, report_unknown, report_missing, allow_clones, allow_resources);

		for (i=0; report_missing && i<dat->num_games; i++)
		{
			if (!(dat->game_name_idx[i].game->match))
			{
				if ((allow_clones==1 && dat->game_name_idx[i].game->cloneof) ||
					(allow_resources==1 && dat->game_name_idx[i].game->game_flags & FLAG_RESOURCE_NAME) ||
					(!(dat->game_name_idx[i].game->game_flags & FLAG_RESOURCE_NAME) && !(dat->game_name_idx[i].game->cloneof)))
				printf("   Missing: %s%s\n", dat->game_name_idx[i].game->name, img_ext);
			}
		}

		printf("Done!\n");
	}

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Read file names from ZIP file
 * -------------------------------------------------------------------------- */

int check_zip(struct dat *dat, char *fn, char *img_ext, int report_unknown, int report_missing, int allow_clones, int allow_resources)
{
	ZIP *zip;
	struct zipent *zipent;
	struct game_idx *game_idx;

	char st[MAX_STRING_LENGTH+1];

	int errflg=0;

	if ((zip=openzip(fn)))
	{
		while ((zipent=readzip(zip)))
		{
			strcpy(st, zipent->name);

			if (strstr(st, img_ext))
				*strstr(st, img_ext)='\0';

			game_idx=bsearch(&st, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name);

			if (game_idx==0)
			{
				if (report_unknown)
					printf("   Unknown: %s\n", zipent->name);
			}
			else
			{
				game_idx->game->match++;

				if (allow_clones==0 && game_idx->game->cloneof)
					printf("   Clone: %s\n", zipent->name);

				if (allow_resources==0 && game_idx->game->game_flags & FLAG_RESOURCE_NAME)
					printf("   Resource: %s\n", zipent->name);
			}
		}
	}
	else
	{
		errflg++;
	}

	if (zip)
		closezip(zip);

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Read file names from directory
 * -------------------------------------------------------------------------- */

int check_dir(struct dat *dat, char *fn, char *img_ext, int report_unknown, int report_missing, int allow_clones, int allow_resources)
{
	DIR *dirp=0;                                    
	struct dirent *direntp;                       

	struct game_idx *game_idx;

	char st[MAX_STRING_LENGTH+1];

	int errflg=0;

	if ((dirp=opendir(fn)))
	{
		while ((direntp=readdir(dirp)))
		{
			if (strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, ".."))
			{
				strcpy(st, direntp->d_name);

				if (strstr(st, img_ext))
					*strstr(st, img_ext)='\0';

				game_idx=bsearch(&st, dat->game_name_idx, dat->num_games, sizeof(struct game_idx), find_game_by_name);

				if (game_idx==0)
				{
					if (report_unknown)
						printf("   Unknown: %s\n", direntp->d_name);
				}
				else
				{
					game_idx->game->match++;

					if (allow_clones==0 && game_idx->game->cloneof)
						printf("   Clone: %s\n", direntp->d_name);

					if (allow_resources==0 && game_idx->game->game_flags & FLAG_RESOURCE_NAME)
						printf("   Resource: %s\n", direntp->d_name);
				}
			}
		}
	}
	else
	{
		fprintf(stderr, "Could not open directory '%s'.\n", fn);
		errflg++;
	}

	if (dirp)
		closedir(dirp);

	return(errflg);
}

