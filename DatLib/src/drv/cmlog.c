/* --------------------------------------------------------------------------
 * ClrMamePro Log - Load only
 * -------------------------------------------------------------------------- */

/* --- Standard includes --- */

#include <stdio.h>
#include <string.h>


/* --- My includes --- */

#include "../type.h"
#include "../token.h"


/* --- External structures --- */

extern const struct token tokens[];


/* --- Is debugging enabled? --- */

extern int datlib_debug;


/* --- Identification --- */

int identify_clrmame_log(struct dat *dat)
{
	int i, match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		if (strstr(BUFFER1_PTR, "[folder:"))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_clrmame_log(struct dat *dat)
{
	char *name=0, *description=0, *cloneof=0, *size=0, *crc=0, *chd_md5=0, *chd_sha1=0;
	int output_game=0, errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		if (strstr(BUFFER1_PTR, " [folder: "))
		{
			description=BUFFER1_PTR;

			name=strstr(description, " [folder: ")+10;
			*strstr(description, " [folder: ")='\0';

			if (strrchr(name, ']'))
				*strrchr(name, ']')='\0';

			if (strstr(name, " - parent: "))
			{
				cloneof=strstr(name, " - parent: ")+11;
				*strstr(name, " - parent: ")='\0';
			}
			else
			{
				cloneof=0;
			}

			output_game=0;
		}

		if (!strncmp(BUFFER1_PTR, "missing rom: ", 13) || !strncmp(BUFFER1_PTR, "missing BIOS rom: ", 18))
		{
			if (!strncmp(BUFFER1_PTR, "missing rom: ", 13))
			{
				if (!output_game)
				{
					strcpy(TOKEN, name);
					BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

					if (cloneof)
					{
						strcpy(TOKEN, cloneof);
						BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)
						BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
					}

					strcpy(TOKEN, description);
					BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)
				}

				name=BUFFER1_PTR+13;
			}
			else
			{
				if (!output_game)
				{
					strcpy(TOKEN, name);
					BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME)

					strcpy(TOKEN, description);
					BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_DESCRIPTION)
				}

				name=BUFFER1_PTR+18;
			}

			output_game=1;

			if (strstr(name, " [CRC32: "))
			{
				crc=strstr(name, " [CRC32: ")+9;
				*strstr(name, " [CRC32: ")='\0';

				if (strrchr(crc, ']'))
					*strrchr(crc, ']')='\0';
			}
			else
			{
				crc=0;
			}

			if (strstr(name, " [size: "))
			{
				size=strstr(name, " [size: ")+8;
				*strstr(name, " [size: ")='\0';

				if (strrchr(size, ']'))
					*strrchr(size, ']')='\0';
			}
			else
			{
				size=0;
			}

			strcpy(TOKEN, name);
			BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

			if (size)
			{
				strcpy(TOKEN, size);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)
			}

			if (crc)
			{
				strcpy(TOKEN, crc);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
			}
		}

		if (!strncmp(BUFFER1_PTR, "missing diskimage: ", 19))
		{
			if (!output_game)
			{
				strcpy(TOKEN, name);
				BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

				if (cloneof)
				{
					strcpy(TOKEN, cloneof);
					BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)
					BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
				}

				strcpy(TOKEN, description);
				BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)
			}

			name=BUFFER1_PTR+19;

			output_game=1;

			if (strstr(name, " [chd-md5: "))
			{
				chd_md5=strstr(name, " [chd-md5: ")+11;
				*strstr(name, " [chd-md5: ")='\0';

				if (strrchr(chd_md5, ']'))
					*strrchr(chd_md5, ']')='\0';
			}
			else
			{
				chd_md5=0;
			}

			if (strstr(name, " [chd-sha1: "))
			{
				chd_sha1=strstr(name, " [chd-sha1: ")+12;
				*strstr(name, " [chd-sha1: ")='\0';

				if (strrchr(chd_sha1, ']'))
					*strrchr(chd_sha1, ']')='\0';
			}
			else
			{
				chd_sha1=0;
			}

			strcpy(TOKEN, name);
			BUFFER2_PUT_TOKEN(TOKEN_DISK_NAME)

			if (chd_sha1)
			{
				strcpy(TOKEN, chd_sha1);
				BUFFER2_PUT_TOKEN(TOKEN_DISK_SHA1)
			}

			if (chd_md5)
			{
				strcpy(TOKEN, chd_md5);
				BUFFER2_PUT_TOKEN(TOKEN_DISK_MD5)
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


/* --- Save --- */

int save_clrmame_log(struct dat *dat)
{
	return(0);
}

