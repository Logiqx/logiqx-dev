/* --- This include file is used by datlib.c, token.c and the drivers --- */

#ifndef _DATLIB_TOKEN_H_
#define _DATLIB_TOKEN_H_


/* --- Standard includes --- */

#include <string.h>
#include <stdint.h>


/* --- Token structure (the description field is used by the directory scan and for debugging output) --- */

struct token
{
	uint8_t type;
	char *description;
};


/* --- Token Types --- */

enum {
	TOKEN_UNDEFINED,
	TOKEN_GAME_NAME,
	TOKEN_GAME_DESCRIPTION,
	TOKEN_GAME_YEAR,
	TOKEN_GAME_MANUFACTURER,
	TOKEN_GAME_REBUILDTO,
	TOKEN_GAME_CLONEOF,
	TOKEN_GAME_ROMOF,
	TOKEN_GAME_SAMPLEOF,
	TOKEN_GAME_COMMENT,
	TOKEN_RESOURCE_NAME,
	TOKEN_RESOURCE_DESCRIPTION,
	TOKEN_RESOURCE_YEAR,
	TOKEN_RESOURCE_MANUFACTURER,
	TOKEN_RESOURCE_REBUILDTO,
	TOKEN_RESOURCE_COMMENT,
	TOKEN_MACHINE_NAME,
	TOKEN_MACHINE_DESCRIPTION,
	TOKEN_MACHINE_YEAR,
	TOKEN_MACHINE_MANUFACTURER,
	TOKEN_MACHINE_REBUILDTO,
	TOKEN_MACHINE_CLONEOF,
	TOKEN_MACHINE_ROMOF,
	TOKEN_MACHINE_SAMPLEOF,
	TOKEN_MACHINE_COMMENT,
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
	TOKEN_ROM_NAME,
	TOKEN_ROM_MERGE,
	TOKEN_ROM_SIZE,
	TOKEN_ROM_CRC,
	TOKEN_ROM_MD5,
	TOKEN_ROM_SHA1,
	TOKEN_ROM_REGION,
	TOKEN_ROM_FLAGS,
	TOKEN_DISK_NAME,
	TOKEN_DISK_MD5,
	TOKEN_DISK_SHA1,
	TOKEN_DISK_REGION,
	TOKEN_SAMPLE_NAME,
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
	if (tokens[TYPE].type==TYPE) \
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
		fprintf(stderr, "Token ID mismatch - check the tokens array in token.c!\n"); \
		errflg++; \
	} \
}

#define BUFFER1_GET_TOKEN \
{ \
	char *token_ptr=TOKEN; \
\
	while ((*BUFFER1_PTR==' ') || (*BUFFER1_PTR=='\t')) \
		BUFFER1_PTR++; \
\
	if (*BUFFER1_PTR=='"') \
	{ \
		BUFFER1_PTR++; \
		while (*BUFFER1_PTR!='"' && *BUFFER1_PTR!='\0') \
		{ \
			*token_ptr++=*BUFFER1_PTR++; \
		} \
		if (*BUFFER1_PTR=='"') \
			BUFFER1_PTR++; \
		*token_ptr='\0';  \
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
	if (tokens[TYPE].type==TYPE) \
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
		fprintf(stderr, "Token ID mismatch - check the tokens array in token.c!\n"); \
		errflg++; \
	} \
}

#define BUFFER2_GET_TOKEN \
{ \
	strcpy(TOKEN, BUFFER2_PTR); \
	BUFFER2_PTR+=strlen(TOKEN)+1; \
}


#endif /* _DATLIB_TOKEN_H_ */
