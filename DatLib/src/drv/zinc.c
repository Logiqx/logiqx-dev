/* --------------------------------------------------------------------------
 * Zinc --list-sets - Load only
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

struct resource
{
	char *resource_name;
	char *resource_description;
	char *rom_name;
	uint32_t rom_crc;
};

struct resource resources[] =
{
	{"atluspsx", "Atlus PSX", "coh-1001l.353", 0x6721146b},
	{"cpzn1", "ZN1", "coh-1000c.353", 0x50033af6},
	{"cpzn2", "ZN2", "coh-3002c.353", 0xe860ea8b},
	{"konamigv", "Baby Phoenix/GV System", "999a01.7e", 0xad498d2d},
	{"psarc95", "PS Arcade 95", "coh-1002e.353", 0x910f3a8b},
	{"taitofx1", "Taito FX1", "coh-1000t.353", 0xe3f23b6e},
	{"tps", "TPS", "coh-1002m.353", 0x69ffbcb4},
	{0, 0, 0, 0}
};


/* --- Identification --- */

int identify_zinc_list_sets(struct dat *dat)
{
	int i, match=0;

	BUFFER1_REWIND

	for (i=0; i<1 && BUFFER1_REMAINING; i++)
	{
		if (strstr(BUFFER1_PTR, "ZiNc"))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_zinc_list_sets(struct dat *dat)
{
	int i, sfex2_fix, errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		/* --- game --- */

		if (strstr(BUFFER1_PTR, " ["))
		{
			/* --- name --- */

			strcpy(TOKEN, strstr(BUFFER1_PTR, " [")+2);
			if (strchr(TOKEN, ','))
				*strchr(TOKEN, ',')='\0';
			if (strchr(TOKEN, ']'))
				*strchr(TOKEN, ']')='\0';

			/* --- name of sfex2 (US) is incorrect in ZiNc v1.0.1 (sfex2j) --- */

			if (!strcmp(TOKEN, "sfex2j") && strstr(BUFFER1_PTR, "(US)"))
			{
				strcpy(TOKEN, strstr(BUFFER1_PTR, ", parent ")+9);
				if (strchr(TOKEN, ','))
					*strchr(TOKEN, ',')='\0';
				if (strchr(TOKEN, ']'))
					*strchr(TOKEN, ']')='\0';
				sfex2_fix=1;
			}
			else
			{
				sfex2_fix=0;
			}

			BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

			/* --- description --- */

			strcpy(TOKEN, BUFFER1_PTR);
			*strstr(TOKEN, " [")='\0';
			BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)

			/* --- cloneof and romof (ignore cloneof if current game is sfex2) --- */

			if (sfex2_fix==0 && strstr(BUFFER1_PTR, ", parent "))
			{
				strcpy(TOKEN, strstr(BUFFER1_PTR, ", parent ")+9);
				if (strchr(TOKEN, ','))
					*strchr(TOKEN, ',')='\0';
				if (strchr(TOKEN, ']'))
					*strchr(TOKEN, ']')='\0';
				BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
				BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)
			}
			else if (strstr(BUFFER1_PTR, ", BIOS "))
			{
				strcpy(TOKEN, strstr(BUFFER1_PTR, ", BIOS ")+7);
				if (strchr(TOKEN, ','))
					*strchr(TOKEN, ',')='\0';
				if (strchr(TOKEN, ']'))
					*strchr(TOKEN, ']')='\0';
				BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
			}
		}

		/* --- rom or disk --- */

		else if (strchr(BUFFER1_PTR, ' '))
		{
			if (!strstr(BUFFER1_PTR, "(disk)"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
			}
			else
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_DISK_NAME)
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	/* --- Hard-coded resources --- */

	for (i=0; resources[i].resource_name!=0; i++)
	{
		strcpy(TOKEN, resources[i].resource_name);
		BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME)

		strcpy(TOKEN, resources[i].resource_description);
		BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_DESCRIPTION)

		strcpy(TOKEN, resources[i].rom_name);
		BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

		sprintf(TOKEN, "%08lx", (unsigned long)resources[i].rom_crc);
		BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
	}

	return(errflg);
}


/* --- Save --- */

int save_zinc_list_sets(struct dat *dat)
{
	return(0);
}

