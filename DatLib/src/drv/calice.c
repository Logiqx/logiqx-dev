/* --------------------------------------------------------------------------
 * Nebula Driver - Load only
 * -------------------------------------------------------------------------- */

/* --- Standard includes --- */

#include <stdio.h>
#include <string.h>


/* --- My includes --- */

#include "../type.h"
#include "../token.h"


/* --- External structures --- */

extern const struct datlib_token datlib_tokens[];


/* --- Is debugging enabled? --- */

extern int datlib_debug;


/* --- Identification --- */

int identify_calice_driver(struct dat *dat)
{
	int i, match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "GAMENAME"))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_calice_driver(struct dat *dat)
{
	char description[MAX_STRING_LENGTH];
	int in_rom_section=0, has_parent=0, errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		BUFFER1_GET_TOKEN

		if (*TOKEN=='[')
			LOWER(TOKEN)

		if (*TOKEN=='[')
		{
			if (!strcmp(TOKEN, "[bios]") || !strcmp(TOKEN, "[z80]") || !strcmp(TOKEN, "[samples]"))
				in_rom_section=1;
			else
				in_rom_section=0;
		}

		else if (!strcmp(TOKEN, "GAMENAME"))
		{
			/* --- Remove leading spaces and tabs --- */

			while (*BUFFER1_PTR==' ' || *BUFFER1_PTR=='\t' || *BUFFER1_PTR=='"')
				BUFFER1_PTR++;

			strcpy(TOKEN, BUFFER1_PTR);

			/* --- Remove trailing spaces --- */

			while (TOKEN[strlen(TOKEN)-1]==' ' || TOKEN[strlen(TOKEN)-1]=='"')
				TOKEN[strlen(TOKEN)-1]='\0';

			strcpy(description, TOKEN);
		}

		else if (!strcmp(TOKEN, "DIRECTORY"))
		{
			BUFFER1_GET_TOKEN
			LOWER(TOKEN)
			BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

			strcpy(TOKEN, description);
			BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)

			has_parent=0;
		}

		else if (!strcmp(TOKEN, "PARENT"))
		{
			BUFFER1_GET_TOKEN
			LOWER(TOKEN)
			BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)
			BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)

			has_parent=1;
		}

		else if (!strcmp(TOKEN, "DATE"))
		{
			BUFFER1_GET_TOKEN
			LOWER(TOKEN)
			BUFFER2_PUT_TOKEN(TOKEN_GAME_YEAR)
		}

		else if (strlen(TOKEN)!=0)
		{
			if (in_rom_section &&
				strncmp(TOKEN, "ROMSIZE", 7) &&
				strncmp(TOKEN, "TOTAL", 5) &&
				strncmp(TOKEN, "LOAD", 4))
			{
				LOWER(TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

				if (!strcmp(TOKEN, "neo-geo.rom") && !has_parent)
				{
					strcpy(TOKEN, "neogeo");
					BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
				}
			}

			if (!strncmp(TOKEN, "LOAD", 4) ||
				!strcmp(TOKEN, "MERGE"))
			{
				BUFFER1_GET_TOKEN
				LOWER(TOKEN)

				while(strlen(TOKEN)!=0 && strncmp(TOKEN, "0x", 2))
				{
					BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

					BUFFER1_GET_TOKEN
					LOWER(TOKEN)
				}
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	/* --- Neo-Geo Resource --- */

	strcpy(TOKEN, "neogeo");
	BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME)

	strcpy(TOKEN, "Neo-Geo");
	BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_DESCRIPTION)

	strcpy(TOKEN, "1990");
	BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_YEAR)

	strcpy(TOKEN, "neo-geo.rom");
	BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

	strcpy(TOKEN, "ng-sfix.rom");
	BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

	strcpy(TOKEN, "ng-sm1.rom");
	BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

	return(errflg);
}


/* --- Save --- */

int save_calice_driver(struct dat *dat)
{
	return(0);
}

