/* --------------------------------------------------------------------------
 * ZIPList - Written by Logiqx (http://www.logiqx.com/)
 *
 * Little tool to scan a directory for ZIP files and list their contents
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define ZIPLIST_VERSION "v2.0"
#define ZIPLIST_DATE "9 May 2004"


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

#include "datlib/src/mame/unzip.h"


/* --- ZIPList definitions and macros --- */

#include "ziplist.h"


/* --- Is DatLib debugging enabled? --- */

int datlib_debug=0;


/* --------------------------------------------------------------------------
 * The main() function
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	FILE *out=0;
	int i;

	struct stat buf;

	char st[MAX_FILENAME_LENGTH+1];
	char path[MAX_FILENAME_LENGTH+1];

	int errflg=0;
	int scan_type=0;

	printf("===============================================================================\n");
	printf("ZIPList %s (%s)\n", ZIPLIST_VERSION, ZIPLIST_DATE);
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Initialise logs --- */

	for (i=1; !errflg && i<argc; i++)
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

			sprintf(st, "%s/ziplist.txt", path);
			FOPEN(out, st, "w")

			FCLOSE(out)
		}
		else
		{
			printf("Error getting attributes of %s\n", argv[i]);
			errflg++;
		}
	}

	/* --- Process all files/dirs in filespec --- */

	for (i=1; !errflg && i<argc; i++)
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

			sprintf(st, "%s/ziplist.txt", path);
			FOPEN(out, st, "a")
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
					errflg=scan_dir(out, argv[i]);
					break;
				case SCAN_FILE:
					errflg=process_zip(out, argv[i]);
					break;
			}
		}

		/* --- Cleanup and exit --- */

		FCLOSE(out)
	}

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Directory scanning is recursive
 * -------------------------------------------------------------------------- */

int scan_dir(FILE *out, char *dir)
{
	DIR *dirp;
	struct dirent *direntp;
	struct stat buf;
	char fn[MAX_FILENAME_LENGTH+1];
	int errflg=0;

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
				process_zip(out, fn);
			}
			else
			{
				if (fn[strlen(fn)-1]!='.')	/* Don't try . or .. entries */
					errflg=scan_dir(out, fn);
			}
		}
		else
		{
			printf("Error getting attributes of %s\n", direntp->d_name);
		}
	}

	if (dirp)
		closedir(dirp);

	return(errflg);
}

int process_zip(FILE *out, char *fn)
{
	ZIP *zip;
	struct zipent *zipent;
	char st[MAX_FILENAME_LENGTH+1];
	int errflg=0;

	strcpy(st, fn);
	LOWER(st)

	if (strrchr(st, '.') && !strcmp(strrchr(st, '.'), ".zip"))
	{
		if ((zip = openzip(fn)))
		{
			/* --- Read all entries from the ZIP--- */

			while ((zipent = readzip(zip)) != 0)
			{
				fprintf(out, "%s\t%s\t%d\t%08lx\n", fn, zipent->name, zipent->uncompressed_size, (long)zipent->crc32);
			}
			closezip(zip);
		}
		else
		{
          		fprintf(out,"The zipfile seems to be corrupt, please check it\n\n");
		}
	}

	return(errflg);
}
