/* --------------------------------------------------------------------------
 * GNGEO romrc - Load only
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

int identify_gngeo_romrc(struct dat *dat)
{
	int i, match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "#"))
		{
			BUFFER1_GET_TOKEN

			if (!strcmp(TOKEN, "ROMRC"))
				match++;
		}

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_gngeo_romrc(struct dat *dat)
{
	unsigned long size;
	int in_rom_section=0, errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		BUFFER1_GET_TOKEN

		LOWER(TOKEN)

		if (!in_rom_section)
		{
			if (!strcmp(TOKEN, "game"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

				// Skip MVS
				BUFFER1_GET_TOKEN

				/* --- Remove leading spaces and tabs --- */

				while (*BUFFER1_PTR==' ' || *BUFFER1_PTR=='\t' || *BUFFER1_PTR=='"')
					BUFFER1_PTR++;

				strcpy(TOKEN, BUFFER1_PTR);

				/* --- Remove trailing spaces --- */

				while (TOKEN[strlen(TOKEN)-1]==' ' || TOKEN[strlen(TOKEN)-1]=='"')
					TOKEN[strlen(TOKEN)-1]='\0';

				BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)
			}
			else if (!strcmp(TOKEN, "cpu") || !strcmp(TOKEN, "sfix") || !strcmp(TOKEN, "sm1") ||
				!strcmp(TOKEN, "sound1") || !strcmp(TOKEN, "sound2") || !strcmp(TOKEN, "gfx"))
			{
				in_rom_section=1;
			}
		}
		else
		{
			if (!strcmp(TOKEN, "end"))
			{
				in_rom_section=0;
			}
			else if (strcmp(TOKEN, "-"))
			{
				BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME);

				// Skip offset
				BUFFER1_GET_TOKEN

				BUFFER1_GET_TOKEN
				size=strtoul(TOKEN, NULL, 16);
				sprintf(TOKEN, "%lu", size);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE);
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


/* --- Save --- */

int save_gngeo_romrc(struct dat *dat)
{
	return(0);
}

