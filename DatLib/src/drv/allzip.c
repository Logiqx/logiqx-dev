/* --------------------------------------------------------------------------
 * AllZip - Load only
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

int identify_allzip(struct dat *dat)
{
	int i, match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		if (!strncmp(BUFFER1_PTR, "\"./", 3))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_allzip(struct dat *dat)
{
	char *curr_game=0, *curr_rebuildto=0, *prev_game=0, *prev_rebuildto=0;

	int errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	BYTE_MALLOC(prev_game, dat->token_size+1);
	BYTE_MALLOC(prev_rebuildto, dat->token_size+1);
	BYTE_MALLOC(curr_rebuildto, dat->token_size+1);

	*prev_game='\0';
	*prev_rebuildto='\0';

	while (!errflg && BUFFER1_REMAINING)
	{
		/* The ZIP name and path actually need processing in reverse order */

		BUFFER1_GET_TOKEN
		strcpy(curr_rebuildto, TOKEN);

		if ((curr_game=strrchr(curr_rebuildto, '/')))
		{
			*curr_game++='\0';

			if ((*prev_game=='\0' && *prev_rebuildto=='\0') || (*prev_game && strcmp(prev_game, curr_game)) || (*prev_rebuildto && strcmp(prev_rebuildto, curr_rebuildto)))
			{
				strcpy(TOKEN, curr_game);
				if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)
				if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)
				strcpy(prev_game, TOKEN);

				strcpy(TOKEN, curr_rebuildto);
				if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_GAME_REBUILDTO)
				strcpy(prev_rebuildto, TOKEN);
			}
		}

		BUFFER1_GET_TOKEN
		if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

		BUFFER1_GET_TOKEN
		if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)

		BUFFER1_GET_TOKEN
		if (!errflg) BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)

		BUFFER1_ADVANCE_LINE
	}

	FREE(curr_rebuildto)
	FREE(prev_rebuildto)
	FREE(prev_game)

	return(errflg);
}


/* --- Save --- */

int save_allzip(struct dat *dat)
{
	return(0);
}

