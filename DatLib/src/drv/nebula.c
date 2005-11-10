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


/* --- Hard-coded resources --- */

struct resource_rom
{
	char *rom_name;
	uint32_t rom_size;
	uint32_t rom_crc;
};

struct resource_rom neogeo_rom[] =
{
	{"neo-geo.rom", 131072, 0x9036d879},
	{"sfix.sfx", 131072, 0x354029fc},
	{"sm1.sm1", 131072, 0x97cf998b},
	{"000-lo.lo", 65536, 0xe09e253c},
	{0, 0, 0}
};


/* --- Identification --- */

int identify_nebula_driver(struct dat *dat)
{
	int i, match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (strchr(TOKEN, ':'))
			LOWER(TOKEN)

		if (!strcmp(TOKEN, "romname:"))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_nebula_driver(struct dat *dat)
{
	int i, in_rom_section=0, neogeo=0, parent=0, errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	if (dat->options->options & OPTION_NEBULA_JUKEBOX)
		dat->options->options|=OPTION_REMOVE_CLONES;

	while (!errflg && BUFFER1_REMAINING)
	{
		BUFFER1_GET_TOKEN

		if (*TOKEN=='[' || strchr(TOKEN, ':'))
			LOWER(TOKEN)

		if (*TOKEN=='[')
		{
			if (!strcmp(TOKEN, "[z80]") || !strcmp(TOKEN, "[samples]"))
				in_rom_section=1;
			else if (!(dat->options->options & OPTION_NEBULA_JUKEBOX) &&
			   	(!strcmp(TOKEN, "[program]") || !strcmp(TOKEN, "[decryption]") ||
				!strcmp(TOKEN, "[text]") || !strcmp(TOKEN, "[graphics]")))
				in_rom_section=1;
			else
				in_rom_section=0;

			if (!(dat->options->options & OPTION_NEBULA_JUKEBOX) && in_rom_section && neogeo)
			{
				if (!strcmp(TOKEN, "[z80]"))
				{
					for (i=0; neogeo_rom[i].rom_name!=0; i++)
					{
						strcpy(TOKEN, neogeo_rom[i].rom_name);
						BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

						sprintf(TOKEN, "%lu", (unsigned long)neogeo_rom[i].rom_size);
						BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)

						sprintf(TOKEN, "%08lx", (unsigned long)neogeo_rom[i].rom_crc);
						BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
					}
				}

				if (!parent)
				{
					sprintf(TOKEN, "neogeo");
					BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
				}
			}

			parent=0;
		}

		else if (!strcmp(TOKEN, "system:"))
		{
			BUFFER1_GET_TOKEN
			UPPER(TOKEN)

			if (!strcmp(TOKEN, "NEO"))
				neogeo++;
			else
				neogeo=0;
		}

		else if (!strcmp(TOKEN, "romname:"))
		{
			BUFFER1_GET_TOKEN
			BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)
		}

		else if (!strcmp(TOKEN, "game:"))
		{
			/* --- Remove leading spaces and tabs --- */

			while (*BUFFER1_PTR==' ' || *BUFFER1_PTR=='\t')
				BUFFER1_PTR++;

			strcpy(TOKEN, BUFFER1_PTR);

			/* --- Remove trailing spaces --- */

			while (TOKEN[strlen(TOKEN)-1]==' ')
				TOKEN[strlen(TOKEN)-1]='\0';

			BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)
		}

		else if (!strcmp(TOKEN, "parent:"))
		{
			BUFFER1_GET_TOKEN
			BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)
			BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)

			parent++;
		}

		else if (in_rom_section && strchr(TOKEN, ',') && *TOKEN!=',')
		{
			/* --- Comments are used in drivers but do not act as comments! --- */

 			if (!strncmp(TOKEN, "//", 2))
				TOKEN+=2;

			/* --- First field is the ROM name --- */

			strtok(TOKEN, ",");
			BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

			/* --- Second field is not of interest --- */

			strtok(NULL, ",");

			/* --- Third field is the ROM size (in hex) --- */

			strcpy(TOKEN, strtok(NULL, ","));
			BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE_HEX)

			/* --- Fourth field is the ROM CRC --- */

			strcpy(TOKEN, strtok(NULL, ","));
			BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
		}

		BUFFER1_ADVANCE_LINE
	}

	if (!(dat->options->options & OPTION_NEBULA_JUKEBOX))
	{
		sprintf(TOKEN, "neogeo");
		BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME)

		sprintf(TOKEN, "Neo-Geo");
		BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_DESCRIPTION)

		for (i=0; neogeo_rom[i].rom_name!=0; i++)
		{
			strcpy(TOKEN, neogeo_rom[i].rom_name);
			BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

			sprintf(TOKEN, "%lu", (unsigned long)neogeo_rom[i].rom_size);
			BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)

			sprintf(TOKEN, "%08lx", (unsigned long)neogeo_rom[i].rom_crc);
			BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
		}
	}

	return(errflg);
}


/* --- Specify --- */

int specify_nebula_driver(struct dat *dat)
{
	return(0);
}


/* --- Save --- */

int save_nebula_driver(struct dat *dat)
{
	return(0);
}

