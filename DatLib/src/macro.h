/* --- This include file is used by DatLib and the external tools --- */

#ifndef _DATLIB_MACRO_H_
#define _DATLIB_MACRO_H_


/* --- Standard includes --- */

#include <string.h>
#include <ctype.h>


/* --- The few hard limits that exist in DatLib and the external tools --- */

#define MAX_ROM_SIZE         1<<26   /* 64MB */
#define MAX_ZIP_ENTRIES      100
#define MAX_STRING_LENGTH    1024
#define MAX_FILENAME_LENGTH  1024


/* --- String routines --- */

#define REMOVE_CR_LF(ST) \
{ \
	while ((ST[strlen(ST)-1]==10) || (ST[strlen(ST)-1]==13)) \
		ST[strlen(ST)-1]='\0'; \
}

#define UPPER(ST) \
{ \
	char *ptr=ST; \
	int i; \
	for (i=0; i<strlen(ptr); i++) \
		ptr[i]=toupper(ptr[i]); \
}

#define LOWER(ST) \
{ \
	char *ptr=ST; \
	int i; \
	for (i=0; i<strlen(ptr); i++) \
		ptr[i]=tolower(ptr[i]); \
}

#define LRPAD(DEST, SRC, CHAR, WIDTH) \
{ \
	int i, j; \
\
	i=(WIDTH-strlen(SRC))/2; \
	j=WIDTH-strlen(SRC)-i; \
\
	*DEST='\0'; \
	for (; i>1; i--) strcat(DEST, CHAR); \
	strcat(DEST, SRC); \
	for (; j>1; j--) strcat(DEST, CHAR); \
}

/* --- Memory routines --- */

#define KB(BYTES) (BYTES/1024)+(BYTES & 1023?1:0)

#define STRUCT_CALLOC(PTR, NUM, BYTES) \
{ \
	if (datlib_debug) \
	{ \
		printf("  %-14s: ", "STRUCT_CALLOC"); \
		printf("  Allocating %lu bytes with calloc (%d items of %lu bytes)...\n", (unsigned long)(NUM)*BYTES, NUM, (unsigned long)BYTES); \
\
	}\
\
	PTR=calloc(NUM, BYTES); \
	if (PTR==0) \
	{ \
		fprintf(stderr, "Error allocating %lu bytes\n", (unsigned long)(NUM)*BYTES); \
		errflg++; \
	} \
}

#define BYTE_CALLOC(PTR, BYTES) \
{ \
	if (datlib_debug) \
	{ \
		printf("  %-14s: ", "BYTE_CALLOC"); \
		printf("  Allocating %d bytes with calloc...\n", BYTES); \
	}\
\
	PTR=calloc(1, BYTES); \
	if (PTR==0) \
	{ \
		fprintf(stderr, "Error allocating %d bytes\n", BYTES); \
		errflg++; \
	} \
}

#define BYTE_MALLOC(PTR, BYTES) \
{ \
	if (datlib_debug) \
	{ \
		printf("  %-14s: ", "BYTE_MALLOC"); \
		printf("  Allocating %d bytes with malloc...\n", BYTES); \
	}\
\
	PTR=malloc(BYTES); \
	if (PTR==0) \
	{ \
		fprintf(stderr, "Error allocating %d bytes\n", BYTES); \
		errflg++; \
	} \
}

#define FREE(PTR) \
{ \
	if (PTR) \
	{ \
		if (datlib_debug) \
		{ \
			printf("  %-14s: ", "FREE"); \
			printf("  Freeing memory...\n"); \
		} \
\
		free(PTR); \
		PTR=0; \
	} \
}


/* --- File routines --- */

#define FOPEN(HANDLE, FN, MODE) \
{ \
	if (datlib_debug) \
	{ \
		printf("  %-14s: ", "FOPEN"); \
		printf("  Opening '%s' in '%s' mode...\n", FN, MODE); \
	} \
\
	if (!(HANDLE=fopen(FN, MODE))) \
	{ \
		fprintf(stderr, "Error opening %s\n", FN); \
		errflg++; \
	} \
}

#define POPEN(HANDLE, FN, MODE) \
{ \
	if (datlib_debug) \
	{ \
		printf("  %-14s: ", "FOPEN"); \
		printf("  Opening pipe for '%s' in '%s' mode...\n", FN, MODE); \
	} \
\
	if (!(HANDLE=popen(FN, MODE))) \
	{ \
		fprintf(stderr, "Error opening pipe for '%s'\n", FN); \
		errflg++; \
	} \
}

#define BYTE_READ(PTR, NUM, FN) \
{ \
	FILE *in=0; \
\
	FOPEN(in, FN, "rb") \
\
	if (!errflg) \
	{ \
		if (datlib_debug) \
		{ \
			printf("  %-14s: ", "BYTE_READ"); \
			printf("  Reading %d bytes from file...\n", NUM); \
		} \
\
		if (fread(PTR, 1, NUM, in)!=NUM) \
		{ \
			fprintf(stderr, "Error reading %d bytes from %s\n", NUM, FN); \
			errflg++; \
		} \
	} \
\
	FCLOSE(in) \
}

#define FCLOSE(HANDLE) \
{ \
	if (HANDLE) \
	{ \
		if (datlib_debug) \
		{ \
			printf("  %-14s: ", "FCLOSE"); \
			printf("  Closing file...\n"); \
		} \
\
		fclose(HANDLE); \
		HANDLE=0; \
	} \
}

#define PCLOSE(HANDLE) \
{ \
	if (HANDLE) \
	{ \
		if (datlib_debug) \
		{ \
			printf("  %-14s: ", "FCLOSE"); \
			printf("  Closing pipe...\n"); \
		} \
\
		pclose(HANDLE); \
		HANDLE=0; \
	} \
}

#if defined (_MSC_VER) || defined (__MINGW32_VERSION)
#define MKDIR(FN, MODE) \
{ \
	if (datlib_debug) \
	{ \
		printf("  %-14s: ", "FOPEN"); \
		printf("  Creating directory '%s'...\n", FN); \
	} \
\
	if (mkdir(FN)) \
	{ \
		fprintf(stderr, "Error creating %s\n", FN); \
		errflg++; \
	} \
}
#else
#define MKDIR(FN, MODE) \
{ \
	if (datlib_debug) \
	{ \
		printf("  %-14s: ", "FOPEN"); \
		printf("  Creating directory '%s'...\n", FN); \
	} \
\
	if (mkdir(FN, MODE)) \
	{ \
		fprintf(stderr, "Error creating %s\n", FN); \
		errflg++; \
	} \
}
#endif



#endif /* _DATLIB_MACRO_H_ */
