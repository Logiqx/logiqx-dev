/* --------------------------------------------------------------------------
 * MAME ListXML - Load only
 * -------------------------------------------------------------------------- */

/* --- Standard includes --- */

#include <stdio.h>
#include <string.h>


/* --- My includes --- */

#include "../type.h"
#include "../token.h"


/* --- External structures --- */

extern const struct token tokens[];

int load_mame_listinfo(struct dat *dat);


/* --- Is debugging enabled? --- */

extern int datlib_debug;


/* --- Identification --- */

int identify_mame_listxml(struct dat *dat)
{
	uint32_t i;
	int xml=0, match=0;

	BUFFER1_REWIND

	for (i=0; i<100 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "<?xml"))
			xml++;

		if (xml && !strcmp(TOKEN, "<mame>"))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_mame_listxml(struct dat *dat)
{
	FILE *in;
	char cmd[MAX_STRING_LENGTH+1];

	int errflg=0;

	/* --- Use xml2info to do the hard work --- */

	if (datlib_debug)
		printf("%-16s: ", "Datlib.init_dat");
	else if (!(dat->options & OPTION_LOAD_QUIETLY))
		printf("  ");

	if (!(dat->options & OPTION_LOAD_QUIETLY))
		printf("Using 'xml2info' to convert 'MAME ListXML' to 'MAME ListInfo'...\n");

	BUFFER1_REWIND

	sprintf(cmd, "xml2info <%s", dat->name);
	POPEN(in, cmd, "r")

	while (!errflg && fgets(TOKEN, dat->token_size, in))
	{
		REMOVE_CR_LF(TOKEN)

		BUFFER1_PUT_TOKEN(TOKEN_UNDEFINED)
	}

	PCLOSE(in)

	/* --- Now that buffer 1 contains MAME ListInfo, use the DatLib parser --- */

	if (!errflg)
	{
		/* --- Firstly, clear the end of the buffer that still contains some XML --- */

		memset(BUFFER1_PTR, 0, dat->buffer1_end-BUFFER1_PTR);

		if (datlib_debug)
			printf("%-16s: ", "Datlib.init_dat");
		else if (!(dat->options & OPTION_LOAD_QUIETLY))
			printf("  ");

		if (!(dat->options & OPTION_LOAD_QUIETLY))
			printf("Calling the 'MAME ListInfo' pre-parser/tokenizer...\n");

		errflg=load_mame_listinfo(dat);
	}

	return(errflg);
}


/* --- Save --- */

int save_mame_listxml(struct dat *dat)
{
	return(0);
}
