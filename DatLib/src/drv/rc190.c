/* --------------------------------------------------------------------------
 * RomCenter 1.90 - Load only
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

int identify_romcenter_190(struct dat *dat)
{
	uint32_t i;
	int in_romcenter_dat=0, match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN;

		if (*TOKEN=='[')
		{
			LOWER(TOKEN)

			if (!strcmp(TOKEN, "[dat]"))
				in_romcenter_dat=1;
			else
				in_romcenter_dat=0;
		}
		else if (in_romcenter_dat)
		{
			LOWER(TOKEN)

			if (!strcmp(TOKEN, "version=1.90"))
				match++;
		}

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_romcenter_190(struct dat *dat)
{
	int in_romcenter_credits=0, in_romcenter_emulator=0, in_romcenter_games=0;
	char *parent_name, *parent_title, *game_name, *game_title, *rom_name, *rom_crc, *rom_neogeo, *rom_merge, *rom_size;
	char *prev_game=0;
	char *value;

	int errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		if (*BUFFER1_PTR=='[')
		{
			BUFFER1_GET_TOKEN

			in_romcenter_credits=in_romcenter_emulator=in_romcenter_games=0;

			LOWER(TOKEN)

			if (!strcmp(TOKEN, "[credits]"))
				in_romcenter_credits=1;
			else if (!strcmp(TOKEN, "[emulator]"))
				in_romcenter_emulator=1;
			else if (!strcmp(TOKEN, "[games]"))
				in_romcenter_games=1;
		}
		else if (in_romcenter_credits && strchr(BUFFER1_PTR, '='))
		{
			strcpy(TOKEN, BUFFER1_PTR);

			value=strchr(TOKEN, '=')+1;
			*strchr(TOKEN, '=')='\0';

			LOWER(TOKEN)

			if (!strcmp(TOKEN, "author"))
			{
				strcpy(TOKEN, value);
				BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_AUTHOR)
			}
			else if (!strcmp(TOKEN, "version"))
			{
				strcpy(TOKEN, value);
				BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_VERSION)
			}
			else if (!strcmp(TOKEN, "comment"))
			{
				strcpy(TOKEN, value);
				BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_COMMENT)
			}
		}
		else if (in_romcenter_emulator && strchr(BUFFER1_PTR, '='))
		{
			strcpy(TOKEN, BUFFER1_PTR);

			value=strchr(TOKEN, '=')+1;
			*strchr(TOKEN, '=')='\0';

			LOWER(TOKEN)

			if (!strcmp(TOKEN, "refname"))
			{
				strcpy(TOKEN, value);
				BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_EMULATOR_REFNAME)
			}
			else if (!strcmp(TOKEN, "version"))
			{
				strcpy(TOKEN, value);
				BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_EMULATOR_VERSION)
			}
		}
		else if (in_romcenter_games && *BUFFER1_PTR=='¬')
		{
			parent_name=BUFFER1_PTR+1;
			parent_title=game_name=game_title=rom_name=rom_crc=rom_neogeo=rom_merge=rom_size=0;

			if (parent_name && (parent_title=strchr(parent_name, '¬')))
				*parent_title++='\0';

			if (parent_title && (game_name=strchr(parent_title, '¬')))
				*game_name++='\0';

			if (game_name && (game_title=strchr(game_name, '¬')))
				*game_title++='\0';

			if (game_title && (rom_name=strchr(game_title, '¬')))
				*rom_name++='\0';

			if (rom_name && (rom_crc=strchr(rom_name, '¬')))
				*rom_crc++='\0';

			if (rom_crc && (rom_neogeo=strchr(rom_crc, '¬')))
				*rom_neogeo++='\0';

			if (rom_neogeo && (rom_merge=strchr(rom_neogeo, '¬')))
				*rom_merge++='\0';

			if (rom_merge && (rom_size=strchr(rom_merge, '¬')))
				*rom_size++='\0';

			if (rom_size && strchr(rom_size, '¬'))
			{
				*strchr(rom_size, '¬')='\0';

				if (!prev_game || strcmp(game_name, prev_game))
				{
					if (strcmp(game_name, "neogeo"))
					{
						strcpy(TOKEN, game_name);
						BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

						strcpy(TOKEN, game_title);
						BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)

						if (strcmp(game_name, parent_name))
						{
							strcpy(TOKEN, parent_name);
							BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)
							BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
						}
						else if (!strcmp(rom_neogeo, "O"))
						{
							strcpy(TOKEN, "neogeo");
							BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
						}
					}
					else
					{
						strcpy(TOKEN, game_name);
						BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME)

						strcpy(TOKEN, game_title);
						BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_DESCRIPTION)
					}

					prev_game=game_name;
				}

				strcpy(TOKEN, rom_name);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

				if (!strcmp(rom_merge, "N"))
					BUFFER2_PUT_TOKEN(TOKEN_ROM_MERGE)

				strcpy(TOKEN, rom_size);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)

				strcpy(TOKEN, rom_crc);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	return(0);
}


/* --- Specify --- */

int specify_romcenter_190(struct dat *dat)
{
	return(0);
}


/* --- Save --- */

int save_romcenter_190(struct dat *dat)
{
	return(0);
}

