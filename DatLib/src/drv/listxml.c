/* --------------------------------------------------------------------------
 * MAME ListXML - Load only
 * -------------------------------------------------------------------------- */

/* --- Standard includes --- */

#include <stdio.h>
#include <string.h>
#include <dirent.h>


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

int identify_mess_listxml(struct dat *dat)
{
	uint32_t i;
	int xml=0, match=0;

	BUFFER1_REWIND

	for (i=0; i<100 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "<?xml"))
			xml++;

		if (xml && !strcmp(TOKEN, "<mess>"))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_mame_listxml(struct dat *dat)
{
	int game_type=0, errflg=0;

	BUFFER1_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		if (strstr(BUFFER1_PTR, "<game ") || strstr(BUFFER1_PTR, "<machine "))
		{
			if (strstr(BUFFER1_PTR, "<game "))
			{
				if (strstr(BUFFER1_PTR, "runnable=\"no\""))
					game_type=FLAG_RESOURCE_NAME;
				else
					game_type=FLAG_GAME_NAME;
			}
			else
			{
				game_type=FLAG_MACHINE_NAME;
			}

			if (game_type==FLAG_GAME_NAME)
			{
				GET_XML_ATTRIBUTE("name")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

				GET_XML_ATTRIBUTE("cloneof")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)

				GET_XML_ATTRIBUTE("romof")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)

				GET_XML_ATTRIBUTE("sampleof")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_GAME_SAMPLEOF)
			}
			if (game_type==FLAG_MACHINE_NAME)
			{
				GET_XML_ATTRIBUTE("name")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_MACHINE_NAME)

				GET_XML_ATTRIBUTE("cloneof")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_MACHINE_CLONEOF)

				GET_XML_ATTRIBUTE("romof")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_MACHINE_ROMOF)

				GET_XML_ATTRIBUTE("sampleof")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_MACHINE_SAMPLEOF)
			}
			else if (game_type==FLAG_RESOURCE_NAME)
			{
				GET_XML_ATTRIBUTE("name")
				if (*TOKEN)
					BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME)
			}
		}
		else if (strstr(BUFFER1_PTR, "<rom "))
		{
			GET_XML_ATTRIBUTE("name")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

			GET_XML_ATTRIBUTE("merge")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_ROM_MERGE)

			GET_XML_ATTRIBUTE("size")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)

			GET_XML_ATTRIBUTE("crc")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)

			GET_XML_ATTRIBUTE("sha1")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_ROM_SHA1)

			GET_XML_ATTRIBUTE("md5")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_ROM_MD5)

			GET_XML_ATTRIBUTE("region")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_ROM_REGION)

			GET_XML_ATTRIBUTE("status")
			if (*TOKEN)
			{
				if (!strcmp(TOKEN, "baddump") || !strcmp(TOKEN, "nodump"))
					BUFFER2_PUT_TOKEN(TOKEN_ROM_FLAGS)
			}
		}
		else if (strstr(BUFFER1_PTR, "<disk "))
		{
			GET_XML_ATTRIBUTE("name")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_DISK_NAME)

			GET_XML_ATTRIBUTE("merge")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_DISK_MERGE)

			GET_XML_ATTRIBUTE("sha1")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_DISK_SHA1)

			GET_XML_ATTRIBUTE("md5")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_DISK_MD5)

			GET_XML_ATTRIBUTE("region")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_DISK_REGION)

			GET_XML_ATTRIBUTE("status")
			if (*TOKEN)
			{
				if (!strcmp(TOKEN, "baddump") || !strcmp(TOKEN, "nodump"))
					BUFFER2_PUT_TOKEN(TOKEN_DISK_FLAGS)
			}
		}
		else if (strstr(BUFFER1_PTR, "<sample "))
		{
			GET_XML_ATTRIBUTE("name")
			if (*TOKEN)
				BUFFER2_PUT_TOKEN(TOKEN_SAMPLE_NAME)
		}
		else if (strstr(BUFFER1_PTR, "<description>"))
		{
			GET_XML_ELEMENT
			BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)
		}
		else if (strstr(BUFFER1_PTR, "<year>"))
		{
			GET_XML_ELEMENT
			BUFFER2_PUT_TOKEN(TOKEN_GAME_YEAR)
		}
		else if (strstr(BUFFER1_PTR, "<manufacturer>"))
		{
			GET_XML_ELEMENT
			BUFFER2_PUT_TOKEN(TOKEN_GAME_MANUFACTURER)
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}

int load_mess_listxml(struct dat *dat)
{
	return(load_mame_listxml(dat));
}


/* --- Save --- */

int save_mame_listxml(struct dat *dat)
{
	return(0);
}

int save_mess_listxml(struct dat *dat)
{
	return(0);
}
