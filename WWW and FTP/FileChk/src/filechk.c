/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


/* --- Dat library includes --- */

#include "datlib/src/macro.h"


/* --- FileChk definitions and macros --- */

#include "filechk.h"


/* --- Is DatLib debugging enabled? --- */

int datlib_debug=0;


/* The main guts of the program --- */

int main(int argc, char **argv)
{
	struct stat buf;
	char st[MAX_STRING_LENGTH];
	FILE *in;
	int fs, count=0;
	int errflg=0;

	FOPEN(in, "files.lst", "r")

	while (!errflg && fgets(st, 1024, in))
	{
		REMOVE_CR_LF(st)

		if (strchr(st, ','))
		{
			fs=atoi(strrchr(st, ',')+1);
			*strrchr(st, ',')='\0';

			while (strchr(st, '%'))
			{
				strcpy(strchr(st, '%')+1, strchr(st, '%')+3);
				*strchr(st, '%')=' ';
			}

			if (!stat(st, &buf))
			{
				if (fs*1024<buf.st_size ||
					fs*1024-buf.st_size>=1024)
				{
					printf("%s - actual size is %ldKB\n", st,
						KB((long)buf.st_size));
					count++;
				}
			}
			else
			{
				printf("%s - file not found\n", st);
				count++;
			}
		}
		else
		{
			if (st[0])
			{
				printf("%s - missing comma\n", st);
				count++;
			}
		}
	}

	if (!errflg && !count)
		printf("All files in file.lst are okay.\n");

	FCLOSE(in)

	return(errflg);
}
