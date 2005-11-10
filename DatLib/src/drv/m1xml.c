/* --------------------------------------------------------------------------
 * M1 XML - Load only
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

int identify_m1_xml(struct dat *dat)
{
	uint32_t i;
	int xml=0, match=0;

	BUFFER1_REWIND

	for (i=0; i<100 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "<?xml"))
			xml++;

		if (xml && (!strcmp(TOKEN, "<m1>") || !strcmp(TOKEN, "<m1")))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

#define CONVERT_XML_STRING \
{ \
	unsigned char *read_ptr=TOKEN; \
	unsigned char *write_ptr=TOKEN; \
\
	while (*read_ptr) \
	{ \
		if (*read_ptr=='&') \
		{ \
			if (!strncmp(read_ptr, "&amp;", 5)) \
			{ \
				*write_ptr++='&'; \
				read_ptr+=5; \
			} \
			else if (!strncmp(read_ptr, "&lt;", 4)) \
			{ \
				*write_ptr++='<'; \
				read_ptr+=4; \
			} \
			else if (!strncmp(read_ptr, "&gt;", 4)) \
			{ \
				*write_ptr++='>'; \
				read_ptr+=4; \
			} \
			else if (!strncmp(read_ptr, "&quot;", 6)) \
			{ \
				*write_ptr++='\"'; \
				read_ptr+=6; \
			} \
			else \
			{ \
				read_ptr++; \
\
				if (strchr(read_ptr, ';')) \
				{ \
					if (*read_ptr=='#') \
					{ \
						*write_ptr++=(char)atoi(read_ptr+1); \
						read_ptr=strchr(read_ptr, ';')+1; \
					} \
					else \
					{ \
						printf("Panic: Unrecognised XML entity '&"); \
						while (*read_ptr!=';') \
							printf("%c", *read_ptr++); \
						printf("'\n"); \
						*read_ptr++; \
					} \
				} \
				else \
				{ \
					printf("Panic: There was a rogue '&' in the XML - discarded it!\n"); \
				} \
			} \
		} \
		else \
		{ \
			*write_ptr++=*read_ptr++; \
		} \
	} \
	*write_ptr='\0'; \
}

#define GET_XML_ATTRIBUTE(ATTRIBUTE, TYPE) \
{ \
	sprintf(TOKEN, " %s=", ATTRIBUTE); \
\
	if (strstr(BUFFER1_PTR, TOKEN)) \
	{ \
		strcpy(TOKEN, strstr(BUFFER1_PTR, TOKEN)+strlen(TOKEN)+1); \
		if (strchr(TOKEN, '\"')) \
			*strchr(TOKEN, '\"')='\0'; \
		CONVERT_XML_STRING \
		BUFFER2_PUT_TOKEN(TYPE) \
	} \
	else \
	{ \
		*TOKEN='\0'; \
	} \
}

#define GET_XML_ELEMENT(TYPE) \
{ \
	if (strchr(BUFFER1_PTR, '>')) \
	{ \
		strcpy(TOKEN, strchr(BUFFER1_PTR, '>')+1); \
		if (strchr(TOKEN, '<')) \
			*strchr(TOKEN, '<')='\0'; \
		CONVERT_XML_STRING \
		BUFFER2_PUT_TOKEN(TYPE) \
	} \
	else \
	{ \
		*TOKEN='\0'; \
	} \
}

int load_m1_xml(struct dat *dat)
{
	int errflg=0;

	BUFFER1_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		if (strstr(BUFFER1_PTR, "<game "))
		{
			GET_XML_ATTRIBUTE("name", TOKEN_GAME_NAME)
			GET_XML_ATTRIBUTE("romof", TOKEN_GAME_CLONEOF)
			GET_XML_ATTRIBUTE("romof", TOKEN_GAME_ROMOF)
			GET_XML_ATTRIBUTE("board", TOKEN_GAME_BOARD)
		}
		else if (strstr(BUFFER1_PTR, "<description>"))
		{
			GET_XML_ELEMENT(TOKEN_GAME_DESCRIPTION)
		}
		else if (strstr(BUFFER1_PTR, "<year>"))
		{
			GET_XML_ELEMENT(TOKEN_GAME_YEAR)
		}
		else if (strstr(BUFFER1_PTR, "<manufacturer>"))
		{
			GET_XML_ELEMENT(TOKEN_GAME_MANUFACTURER)
		}
		else if (strstr(BUFFER1_PTR, "<rom "))
		{
			GET_XML_ATTRIBUTE("name", TOKEN_ROM_NAME) 
			GET_XML_ATTRIBUTE("size", TOKEN_ROM_SIZE) 
			GET_XML_ATTRIBUTE("crc", TOKEN_ROM_CRC) 
			GET_XML_ATTRIBUTE("sha1", TOKEN_ROM_SHA1) 
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


/* --- Specify --- */

int specify_m1_xml(struct dat *dat)
{
	return(0);
}


/* --- Save --- */

int save_m1_xml(struct dat *dat)
{
	return(0);
}

