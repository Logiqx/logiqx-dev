/* --------------------------------------------------------------------------
 * AVI2CDVC - Written by Logiqx (http://www.logiqx.com/)
 *
 * A little tool that alters the FourCC of AVI files to 'cdvc' (Canopus DV)
 * -------------------------------------------------------------------------- */

#define AVI2CDVC_VERSION "v2.0"
#define AVI2CDVC_DATE "2 July 2004"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>


/* --- Dat library includes --- */

#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"


/* --- AVI2CDVC definitions and macros --- */

#include "avi2cdvc.h"


/* --- Is DatLib debugging enabled? --- */

int datlib_debug=0;


/* --------------------------------------------------------------------------
 * The main() function
 * -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
	/* --- For getopt function --- */

	extern int optind;
	extern char *optarg;

	char c;
	char *newfourcc1="cdvc", *newfourcc2="cdvc";

	struct stat buf;

	int i, recursive=0, errflg=0;

	/* --- Start up message an parameter checking --- */

	printf("===============================================================================\n");
	printf("AVI2CDVC %s (%s)\n", AVI2CDVC_VERSION, AVI2CDVC_DATE);
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	while (!errflg && (c = getopt(argc, argv, "f:hr?")) != EOF)
	switch (c)
	{
		case 'f':
			newfourcc1=optarg;
			newfourcc2=optarg;
			break;
		case 'r':
			recursive++;
			break;
		default:
			errflg++;
	}

	if (!errflg && optind==argc)
		errflg++;

	if (errflg)
	{
		printf("Usage: avi2cdvc [-r] [-f <FourCC>] <files or directories>\n\n");
		printf("Note: The default FourCC that AVI2CDVC applies to AVIs is 'cdvc'.\n");
	}

	/* --- Process all files/dirs in filespec (current directory if no spec) --- */

	for (i=optind; !errflg && i<argc; i++)
	{
		/* --- Swap DOS delimiters to Unix --- */

		while (strchr(argv[i], '\\'))
			*strchr(argv[i], '\\')='/';

		if (stat(argv[i], &buf) == 0)
		{
			if (buf.st_mode & S_IFDIR)
				errflg=process_dir(argv[i], recursive, newfourcc1, newfourcc2);
			else
				errflg=process_file(argv[i], newfourcc1, newfourcc2);
		}
		else
		{
			printf("Error getting attributes of %s\n", argv[i]);
			errflg++;
		}
	}

	return(errflg);
}

/* --------------------------------------------------------------------------
 * Directory scanning is recursive
 * -------------------------------------------------------------------------- */

int process_dir(char *dir, int recursive, char *newfourcc1, char *newfourcc2)
{
	DIR *dirp;
	struct dirent *direntp;
	struct stat buf;
	char fn[MAX_FILENAME_LENGTH+1];
	int errflg=0;

	if ((dirp=opendir(dir))==0)
		errflg++;

	while (!errflg && ((direntp = readdir(dirp)) != NULL))
	{
		sprintf(fn, "%s/%s", dir, direntp->d_name);
		if (stat(fn, &buf) == 0)
		{
			if (!(buf.st_mode & S_IFDIR))
			{
				process_file(fn, newfourcc1, newfourcc2);
			}
			else if (recursive)
			{
				if (fn[strlen(fn)-1]!='.')	/* Don't try . or .. entries */
					errflg=process_dir(fn, recursive, newfourcc1, newfourcc2);
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

int process_file(char *fn, char *newfourcc1, char *newfourcc2)
{
	FILE *avi=0;

	char st[MAX_FILENAME_LENGTH+1];
	char fourcc1[5], fourcc2[5];

	unsigned char buffer[MAX_STRING_LENGTH];
	unsigned char *ptr=buffer;

	int bufsize=0;
	int errflg=0;

	/* --- Before checking if the extension is AVI, make lowercase --- */

	strcpy(st, fn);
	LOWER(st)

	/* --- If the file is an AVI, process it! --- */

	if (strrchr(st, '.') && !strcmp(strrchr(st, '.'), ".avi"))
	{
		printf("Processing %s... ", fn);

		/* --- Open the AVI file and read X bytes --- */

		FOPEN(avi, st, "rb+")

		if (!errflg)
			bufsize=fread(buffer, 1, MAX_STRING_LENGTH, avi);

		if (bufsize!=MAX_STRING_LENGTH)
		{
			printf("failed to read the first %d bytes!\n", MAX_STRING_LENGTH);
			errflg++;
		}

		if (!errflg)
		{
			/* --- Skip to avih --- */

			ptr=ptr+24;

			if (strncmp(ptr, "avih", 4))
			{
				printf("failed to find 'avih' header\n");
				errflg++;
			}
		}
			
		if (!errflg)
		{
			/* --- Skip to LIST --- */

			ptr+=8+(((((ptr[7]<<8)+ptr[6])<<8)+ptr[5])<<8)+ptr[4];

			if (strncmp(ptr, "LIST", 4))
			{
				printf("failed to find 'LIST' header\n");
				errflg++;
			}
		}

		if (!errflg)
		{
			/* --- Skip to strh --- */

			ptr+=12;

			if (strncmp(ptr, "strh", 4))
			{
				printf("failed to find 'strh' header\n");
				errflg++;
			}
			else
			{
				strncpy(fourcc1, ptr+12, 4);
				fourcc1[4]='\0';
				strncpy(ptr+12, newfourcc1, 4);
			}
		}

		if (!errflg)
		{
			/* --- Skip to strf --- */

			ptr+=8+(((((ptr[7]<<8)+ptr[6])<<8)+ptr[5])<<8)+ptr[4];

			if (strncmp(ptr, "strf", 4))
			{
				printf("failed to find 'strf' header\n");
				errflg++;
			}
			else
			{
				strncpy(fourcc2, ptr+24, 4);
				fourcc2[4]='\0';
				strncpy(ptr+24, newfourcc2, 4);
			}
		}

		if (!errflg)
		{
			if (strcmp(fourcc1, newfourcc1) || strcmp(fourcc2, newfourcc2))
			{
				rewind(avi);
				bufsize=fwrite(buffer, 1, MAX_STRING_LENGTH, avi);

				printf("changed the FourCC from '%s' to '%s'.\n", fourcc1, newfourcc1);
			}
			else
			{
				printf("no update required, the FourCC is already '%s'.\n", newfourcc1);
			}
		}

		FCLOSE(avi)
	}

	return(errflg);
}
