/* --- A little utility to scan a directory for files and output their details --- */

/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


/* --- Dat library includes --- */

#include "datlib/src/macro.h"


/* --- Misc library includes --- */

#include "datlib/src/misc/getopt.h"


/* --- Filelist definitions and macros --- */

#include "filelist.h"


/* --- Is DatLib debugging enabled? --- */

int datlib_debug=0;


/* --- The main code --- */

int main(int argc, char **argv)
{
	int c, images=0, errflg=0;

	while (!errflg && (c = getopt(argc, argv, "i")) != EOF)
	switch (c)
	{
		case 'i':
			images++;
			break;
	}

	errflg=scan_dir(".", images);

	return(errflg);
}

int scan_dir(char *dir, int images)
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
			if (buf.st_mode & S_IFDIR)
			{
				if (direntp->d_name[0]!='.')
					errflg+=scan_dir(fn, images);
			}
			else
			{
				errflg+=file_details(fn, &buf, images);
			}
		}
		else
		{
			printf("Error getting attributes of %s\n", fn);
			errflg++;
		}
	}

	return(errflg);
}


int file_details(char *fn, struct stat *buf, int images)
{
	FILE *in=0;
	unsigned char byte;
	char st[MAX_FILENAME_LENGTH+1];
	long width=0, height=0;
	int i, file_format=0, errflg=0;

	strcpy(st, fn);
	*strrchr(st, '/')='\t';

	if (images)
	{
		if (!strcmp(&fn[strlen(fn)-4], ".png"))
			file_format=PNG_FORMAT;

		if (!strcmp(&fn[strlen(fn)-4], ".jpg"))
			file_format=JPG_FORMAT;
	}

	if (file_format!=0)
		FOPEN(in, fn, "rb")

	if (!errflg)
	{
		if (file_format==PNG_FORMAT)
		{
			fseek(in, 16, 0);
			for (i=0; i<4; i++)
			{
				width=width<<8;
				fread(&byte, 1, 1, in);
				width|=byte;
			}
			
			for (i=0; i<4; i++)
			{
				height=height<<8;
				fread(&byte, 1, 1, in);
				height|=byte;
			}

			if (st[1]=='\t')
				printf("%s\t%ld\t%ld\t%ld\n", st, (long)buf->st_size, width, height);
			else
				printf("%s\t%ld\t%ld\t%ld\n", st+2, (long)buf->st_size, width, height);
		}

		else if (file_format==JPG_FORMAT)
		{
			fseek(in, 163, 0);
			for (i=0; i<2; i++)
			{
				height=height<<8;
				fread(&byte, 1, 1, in);
				height|=byte;
			}
			
			for (i=0; i<2; i++)
			{
				width=width<<8;
				fread(&byte, 1, 1, in);
				width|=byte;
			}

			if (st[1]=='\t')
				printf("%s\t%ld\t%ld\t%ld\n", st, (long)buf->st_size, width, height);
			else
				printf("%s\t%ld\t%ld\t%ld\n", st+2, (long)buf->st_size, width, height);
		}

		else
		{
			if (st[1]=='\t')
				printf("%s\t%ld\n", st, (long)buf->st_size);
			else
				printf("%s\t%ld\n", st+2, (long)buf->st_size);
		}
	}

	FCLOSE(in)

	return(errflg);
}
