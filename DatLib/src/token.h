/* --- This include file is used by datlib.c, token.c and the drivers --- */

#ifndef _DATLIB_TOKEN_H_
#define _DATLIB_TOKEN_H_


/* --- Standard includes --- */

#include <string.h>
#include <stdint.h>


/* --- Token structure (the description field is used by the directory scan and for debugging output) --- */

struct datlib_token
{
	uint8_t type;
	char *description;
};


/* --- Token Types --- */

enum {
	TOKEN_UNDEFINED,
	TOKEN_GAME_NAME,
	TOKEN_GAME_SOURCEFILE,
	TOKEN_GAME_CLONEOF,
	TOKEN_GAME_ROMOF,
	TOKEN_GAME_SAMPLEOF,
	TOKEN_GAME_DESCRIPTION,
	TOKEN_GAME_YEAR,
	TOKEN_GAME_MANUFACTURER,
	TOKEN_GAME_HISTORY,
	TOKEN_GAME_REBUILDTO,
	TOKEN_RESOURCE_NAME,
	TOKEN_RESOURCE_SOURCEFILE,
	TOKEN_RESOURCE_DESCRIPTION,
	TOKEN_RESOURCE_YEAR,
	TOKEN_RESOURCE_MANUFACTURER,
	TOKEN_RESOURCE_HISTORY,
	TOKEN_RESOURCE_REBUILDTO,
	TOKEN_MACHINE_NAME,
	TOKEN_MACHINE_SOURCEFILE,
	TOKEN_MACHINE_CLONEOF,
	TOKEN_MACHINE_ROMOF,
	TOKEN_MACHINE_SAMPLEOF,
	TOKEN_MACHINE_DESCRIPTION,
	TOKEN_MACHINE_YEAR,
	TOKEN_MACHINE_MANUFACTURER,
	TOKEN_MACHINE_HISTORY,
	TOKEN_MACHINE_REBUILDTO,
	TOKEN_CLRMAMEPRO_NAME,
	TOKEN_CLRMAMEPRO_DESCRIPTION,
	TOKEN_CLRMAMEPRO_CATEGORY,
	TOKEN_CLRMAMEPRO_VERSION,
	TOKEN_CLRMAMEPRO_AUTHOR,
	TOKEN_CLRMAMEPRO_FORCEMERGING,
	TOKEN_CLRMAMEPRO_FORCEZIPPING,
	TOKEN_ROMCENTER_CREDITS_AUTHOR,
	TOKEN_ROMCENTER_CREDITS_EMAIL,
	TOKEN_ROMCENTER_CREDITS_HOMEPAGE,
	TOKEN_ROMCENTER_CREDITS_URL,
	TOKEN_ROMCENTER_CREDITS_VERSION,
	TOKEN_ROMCENTER_CREDITS_DATE,
	TOKEN_ROMCENTER_CREDITS_COMMENT,
	TOKEN_ROMCENTER_DAT_PLUGIN,
	TOKEN_ROMCENTER_DAT_SPLIT,
	TOKEN_ROMCENTER_DAT_MERGE,
	TOKEN_ROMCENTER_EMULATOR_REFNAME,
	TOKEN_ROMCENTER_EMULATOR_VERSION,
	TOKEN_COMMENT_TEXT,
	TOKEN_BIOSSET_NAME,
	TOKEN_BIOSSET_DESCRIPTION,
	TOKEN_BIOSSET_DEFAULT,
	TOKEN_ROM_NAME,
	TOKEN_ROM_BIOS,
	TOKEN_ROM_SIZE,
	TOKEN_ROM_SIZE_HEX,
	TOKEN_ROM_CRC,
	TOKEN_ROM_MD5,
	TOKEN_ROM_SHA1,
	TOKEN_ROM_MERGE,
	TOKEN_ROM_REGION,
	TOKEN_ROM_OFFSET,
	TOKEN_ROM_STATUS,
	TOKEN_ROM_DISPOSE,
	TOKEN_ROM_SOUNDONLY,
	TOKEN_DISK_NAME,
	TOKEN_DISK_MD5,
	TOKEN_DISK_SHA1,
	TOKEN_DISK_MERGE,
	TOKEN_DISK_REGION,
	TOKEN_DISK_INDEX,
	TOKEN_DISK_STATUS,
	TOKEN_SAMPLE_NAME,
	TOKEN_CHIP_NAME,
	TOKEN_CHIP_TYPE,
	TOKEN_CHIP_SOUNDONLY,
	TOKEN_CHIP_CLOCK,
	TOKEN_VIDEO_SCREEN,
	TOKEN_VIDEO_ORIENTATION,
	TOKEN_VIDEO_WIDTH,
	TOKEN_VIDEO_HEIGHT,
	TOKEN_VIDEO_ASPECTX,
	TOKEN_VIDEO_ASPECTY,
	TOKEN_VIDEO_REFRESH,
	TOKEN_SOUND_CHANNELS,
	TOKEN_INPUT_SERVICE,
	TOKEN_INPUT_TILT,
	TOKEN_INPUT_PLAYERS,
	TOKEN_INPUT_CONTROL,
	TOKEN_INPUT_BUTTONS,
	TOKEN_INPUT_COINS,
	TOKEN_DIPSWITCH_NAME,
	TOKEN_DIPVALUE_NAME,
	TOKEN_DIPVALUE_DEFAULT,
	TOKEN_DRIVER_STATUS,
	TOKEN_DRIVER_EMULATION,
	TOKEN_DRIVER_COLOR,
	TOKEN_DRIVER_SOUND,
	TOKEN_DRIVER_GRAPHIC,
	TOKEN_DRIVER_COCKTAIL,
	TOKEN_DRIVER_PROTECTION,
	TOKEN_DRIVER_PALETTESIZE,
	TOKEN_DEVICE_NAME,
	TOKEN_EXTENSION_NAME,
	NUM_TOKEN_TYPES
};


/* --- Misc token handling routines --- */

#define TOKEN (dat->token)


/* --- Buffer handling routines (buffer 1) --- */

#define BUFFER1_PTR (dat->buffer1_ptr)

#define BUFFER1_REMAINING (BUFFER1_PTR<dat->buffer1_end)

#define BUFFER1_REWIND \
{ \
	BUFFER1_PTR=dat->buffer1_start; \
}

#define BUFFER1_ADVANCE_LINE \
{ \
	BUFFER1_PTR+=strlen(BUFFER1_PTR); \
	while (BUFFER1_REMAINING && *BUFFER1_PTR=='\0') \
		BUFFER1_PTR++; \
}

#define BUFFER1_PUT_TOKEN(TYPE) \
{ \
	if (datlib_tokens[TYPE].type==TYPE) \
	{ \
		if (BUFFER1_REMAINING) \
		{ \
			if (TYPE) \
				*BUFFER1_PTR++=TYPE; \
			if (dat->buffer1_end-BUFFER1_PTR>=strlen(TOKEN)) \
			{ \
				strcpy(BUFFER1_PTR, TOKEN); \
				BUFFER1_PTR+=strlen(TOKEN)+1; \
			} \
			else \
			{ \
				fprintf(stderr, "Buffer 1 ran out of space!\n"); \
				errflg++; \
			} \
		} \
		else \
		{ \
			fprintf(stderr, "Buffer 1 ran out of space!\n"); \
			errflg++; \
		} \
	} \
	else \
	{ \
		fprintf(stderr, "Token ID mismatch - check the datlib_tokens array in token.c!\n"); \
		errflg++; \
	} \
}

#define BUFFER1_GET_TOKEN_TO_DELIMITER(DELIMITER) \
{ \
	int escaped=0; \
	char *tmp_ptr; \
	unsigned long escaped_char; \
\
	while ((escaped || *BUFFER1_PTR!=DELIMITER) && *BUFFER1_PTR!='\0') \
	{ \
		if (escaped) \
		{ \
			switch (*BUFFER1_PTR) \
			{ \
				case 'n' : *token_ptr++='\n'; BUFFER1_PTR++; break; \
				case 't' : *token_ptr++='\t'; BUFFER1_PTR++; break; \
				case '\\' : *token_ptr++='\\'; BUFFER1_PTR++; break; \
				case '\"' : *token_ptr++='\"'; BUFFER1_PTR++; break; \
				case 'x' : \
					escaped_char=strtoul(++BUFFER1_PTR, &tmp_ptr, 16); \
					if (tmp_ptr-BUFFER1_PTR!=2) \
						escaped_char=escaped_char>>(4*(tmp_ptr-BUFFER1_PTR-2)); \
					*token_ptr++=(unsigned char)escaped_char; \
					BUFFER1_PTR+=2; \
					break; \
				default: fprintf(stderr, "  Error: Unrecognised escape sequence '\\%c'!\n", *BUFFER1_PTR); \
					BUFFER1_PTR++; \
			} \
			escaped=0; \
		} \
		else if (*BUFFER1_PTR!='\\') \
		{ \
			*token_ptr++=*BUFFER1_PTR++; \
		} \
		else \
		{ \
			escaped++; \
			BUFFER1_PTR++; \
		} \
	} \
	if (*BUFFER1_PTR==DELIMITER) \
		BUFFER1_PTR++; \
	*token_ptr='\0';  \
}

#define BUFFER1_GET_TOKEN \
{ \
	char *token_ptr=TOKEN; \
\
	while ((*BUFFER1_PTR==' ') || (*BUFFER1_PTR=='\t')) \
		BUFFER1_PTR++; \
\
	if (*BUFFER1_PTR=='\"') \
	{ \
		BUFFER1_PTR++; \
		BUFFER1_GET_TOKEN_TO_DELIMITER('\"')  \
	} \
	else \
	{ \
		while (*BUFFER1_PTR!=' ' && *BUFFER1_PTR!='\t' && *BUFFER1_PTR!='\0') \
		{ \
			*token_ptr++=*BUFFER1_PTR++; \
		} \
		*token_ptr='\0';  \
	} \
}


/* --- Buffer handling routines (buffer 2) --- */

#define BUFFER2_PTR (dat->buffer2_ptr)

#define BUFFER2_REMAINING (BUFFER2_PTR<dat->buffer2_end)

#define BUFFER2_REWIND \
{ \
	BUFFER2_PTR=dat->buffer2_start; \
}

#define BUFFER2_ADVANCE_LINE \
{ \
	BUFFER2_PTR+=strlen(BUFFER2_PTR); \
	while (BUFFER2_REMAINING && *BUFFER2_PTR=='\0') \
		BUFFER2_PTR++; \
}

#define BUFFER2_PUT_TOKEN(TYPE) \
{ \
	if (datlib_tokens[TYPE].type==TYPE) \
	{ \
		if (BUFFER2_REMAINING) \
		{ \
			if (TYPE) \
				*BUFFER2_PTR++=TYPE; \
			if (dat->buffer2_end-BUFFER2_PTR>=strlen(TOKEN)) \
			{ \
				strcpy(BUFFER2_PTR, TOKEN); \
				BUFFER2_PTR+=strlen(TOKEN)+1; \
			} \
			else \
			{ \
				fprintf(stderr, "Buffer 2 ran out of space!\n"); \
				errflg++; \
			} \
		} \
		else \
		{ \
			fprintf(stderr, "Buffer 2 ran out of space!\n"); \
			errflg++; \
		} \
	} \
	else \
	{ \
		fprintf(stderr, "Token ID mismatch - check the datlib_tokens array in token.c!\n"); \
		errflg++; \
	} \
}


#endif /* _DATLIB_TOKEN_H_ */
