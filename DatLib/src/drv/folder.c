/* --------------------------------------------------------------------------
 * Folder scan - Load only
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

int identify_folder_scan(struct dat *dat)
{
	int match=0;

	BUFFER1_REWIND

	if (!strcmp(BUFFER1_PTR, "*** DatLib Folder Scan ***"))
		match++;

	return(match);
}


/* --- Load --- */

int load_folder_scan(struct dat *dat)
{
	uint32_t i;
	int errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		BUFFER1_GET_TOKEN

		for (i=0; i<NUM_TOKEN_TYPES; i++)
		{
			if (!strcmp(tokens[i].description, TOKEN))
			{
				BUFFER1_GET_TOKEN

				BUFFER2_PUT_TOKEN(tokens[i].type)
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


/* --- Save --- */

int save_folder_scan(struct dat *dat)
{
	return(0);
}

