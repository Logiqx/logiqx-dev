/* --------------------------------------------------------------------------
 * ZIPList - Load only
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

int identify_ziplist(struct dat *dat)
{
	int match=0;

	BUFFER1_REWIND

	if (!strncmp(BUFFER1_PTR, "./", 2))
		match++;

	return(match);
}


/* --- Load --- */

int load_ziplist(struct dat *dat)
{
	char delimiter='\t';
	char *next_delimiter, *prev_game=0, *prev_rebuildto=0;

	int errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	if (!strchr(BUFFER1_PTR, delimiter))
		delimiter=' ';

	BYTE_MALLOC(prev_game, dat->token_size+1);
	BYTE_MALLOC(prev_rebuildto, dat->token_size+1);

	*prev_game='\0';
	*prev_rebuildto='\0';

	while (!errflg && BUFFER1_REMAINING)
	{
		if ((next_delimiter=strchr(BUFFER1_PTR, delimiter)))
		{
			*next_delimiter='\0';

			if ((next_delimiter=strrchr(BUFFER1_PTR, '/')))
			{
				*next_delimiter='\0';
				strcpy(TOKEN, next_delimiter+1);

				if ((*prev_game=='\0' && *prev_rebuildto=='\0') || (*prev_game && strcmp(prev_game, TOKEN)) || (*prev_rebuildto && strcmp(prev_rebuildto, BUFFER1_PTR)))
				{
					if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)
					if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)
					strcpy(prev_game, TOKEN);

					strcpy(TOKEN, BUFFER1_PTR);
					if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_GAME_REBUILDTO)
					strcpy(prev_rebuildto, TOKEN);
				}

				BUFFER1_ADVANCE_LINE
				BUFFER1_ADVANCE_LINE
			}
		}

		if ((next_delimiter=strchr(BUFFER1_PTR, delimiter)))
		{
			*next_delimiter='\0';
			strcpy(TOKEN, BUFFER1_PTR);
			if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

			BUFFER1_ADVANCE_LINE
		}

		if ((next_delimiter=strchr(BUFFER1_PTR, delimiter)))
		{
			*next_delimiter='\0';
			strcpy(TOKEN, BUFFER1_PTR);
			if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)

			BUFFER1_ADVANCE_LINE

			strcpy(TOKEN, BUFFER1_PTR);
			if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


/* --- Specify --- */

int specify_ziplist(struct dat *dat)
{
	return(0);
}


/* --- Save --- */

int save_ziplist(struct dat *dat)
{
	return(0);
}

