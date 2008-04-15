/* --------------------------------------------------------------------------
 * MAME ListXML - Load and Save
 * MESS ListXML - Load only
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

int identify_mame_listxml(struct dat *dat)
{
	uint32_t i;
	int xml=0, match=0;

	BUFFER1_REWIND

	for (i=0; i<200 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "<?xml"))
			xml++;

		if (xml && (!strcmp(TOKEN, "<mame>") || !strcmp(TOKEN, "<mame") || !strcmp(TOKEN, "<Raine32>") || !strcmp(TOKEN, "<Raine32")))
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

	for (i=0; i<200 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "<?xml"))
			xml++;

		if (xml && (!strcmp(TOKEN, "<mess>") || !strcmp(TOKEN, "<mess")))
			match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}

int identify_generic_xml(struct dat *dat)
{
	uint32_t i;
	int xml=0, match=0;

	BUFFER1_REWIND

	for (i=0; i<200 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "<?xml"))
			xml++;

		if (xml && (!strcmp(TOKEN, "<datafile>") || !strcmp(TOKEN, "<datafile")))
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

int load_mame_listxml(struct dat *dat)
{
	int in_header=0, game_type=0, errflg=0;

	BUFFER1_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		if (in_header)
		{
			if (strstr(BUFFER1_PTR, "</header>"))
				in_header=0;
			else if (strstr(BUFFER1_PTR, "<name>"))
				GET_XML_ELEMENT(TOKEN_HEADER_NAME)
			else if (strstr(BUFFER1_PTR, "<description>"))
				GET_XML_ELEMENT(TOKEN_HEADER_DESCRIPTION)
			else if (strstr(BUFFER1_PTR, "<category>"))
				GET_XML_ELEMENT(TOKEN_HEADER_CATEGORY)
			else if (strstr(BUFFER1_PTR, "<version>"))
				GET_XML_ELEMENT(TOKEN_HEADER_VERSION)
			else if (strstr(BUFFER1_PTR, "<date>"))
				GET_XML_ELEMENT(TOKEN_HEADER_DATE)
			else if (strstr(BUFFER1_PTR, "<author>"))
				GET_XML_ELEMENT(TOKEN_HEADER_AUTHOR)
			else if (strstr(BUFFER1_PTR, "<email>"))
				GET_XML_ELEMENT(TOKEN_HEADER_EMAIL)
			else if (strstr(BUFFER1_PTR, "<homepage>"))
				GET_XML_ELEMENT(TOKEN_HEADER_HOMEPAGE)
			else if (strstr(BUFFER1_PTR, "<url>"))
				GET_XML_ELEMENT(TOKEN_HEADER_URL)
			else if (strstr(BUFFER1_PTR, "<comment>"))
				GET_XML_ELEMENT(TOKEN_HEADER_COMMENT)

			else if (strstr(BUFFER1_PTR, "<clrmamepro "))
			{
				GET_XML_ATTRIBUTE("header", TOKEN_CLRMAMEPRO_HEADER) 
				GET_XML_ATTRIBUTE("forcemerging", TOKEN_CLRMAMEPRO_FORCEMERGING) 
				GET_XML_ATTRIBUTE("forcenodump", TOKEN_CLRMAMEPRO_FORCENODUMP) 
				GET_XML_ATTRIBUTE("forcepacking", TOKEN_CLRMAMEPRO_FORCEPACKING) 
				GET_XML_ATTRIBUTE("forcezipping", TOKEN_CLRMAMEPRO_FORCEPACKING) 
			}

			else if (strstr(BUFFER1_PTR, "<romcenter "))
			{
				GET_XML_ATTRIBUTE("plugin", TOKEN_ROMCENTER_PLUGIN) 
				GET_XML_ATTRIBUTE("rommode", TOKEN_ROMCENTER_ROMMODE) 
				GET_XML_ATTRIBUTE("biosmode", TOKEN_ROMCENTER_BIOSMODE) 
				GET_XML_ATTRIBUTE("samplemode", TOKEN_ROMCENTER_SAMPLEMODE) 
				GET_XML_ATTRIBUTE("lockrommode", TOKEN_ROMCENTER_LOCKROMMODE) 
				GET_XML_ATTRIBUTE("lockbiosmode", TOKEN_ROMCENTER_LOCKBIOSMODE) 
				GET_XML_ATTRIBUTE("locksamplemode", TOKEN_ROMCENTER_LOCKSAMPLEMODE) 
			}
		}
		else
		{
			if (strstr(BUFFER1_PTR, "<header>"))
			{
				in_header++;
			}
			else if (strstr(BUFFER1_PTR, "<mame "))
			{
				strcpy(TOKEN, "mame");
				BUFFER2_PUT_TOKEN(TOKEN_EMULATOR_NAME)
				GET_XML_ATTRIBUTE("build", TOKEN_EMULATOR_BUILD) 
				GET_XML_ATTRIBUTE("debug", TOKEN_EMULATOR_DEBUG) 
			}
			else if (strstr(BUFFER1_PTR, "<Raine32 "))
			{
				strcpy(TOKEN, "Raine32");
				BUFFER2_PUT_TOKEN(TOKEN_EMULATOR_NAME)
				GET_XML_ATTRIBUTE("build", TOKEN_EMULATOR_BUILD) 
				GET_XML_ATTRIBUTE("debug", TOKEN_EMULATOR_DEBUG) 
			}
			else if (strstr(BUFFER1_PTR, "<mess "))
			{
				strcpy(TOKEN, "mess");
				BUFFER2_PUT_TOKEN(TOKEN_EMULATOR_NAME)
				GET_XML_ATTRIBUTE("build", TOKEN_EMULATOR_BUILD) 
				GET_XML_ATTRIBUTE("debug", TOKEN_EMULATOR_DEBUG) 
			}
			else if (strstr(BUFFER1_PTR, "<datafile "))
			{
				strcpy(TOKEN, "datafile");
				BUFFER2_PUT_TOKEN(TOKEN_EMULATOR_NAME)
				GET_XML_ATTRIBUTE("build", TOKEN_EMULATOR_BUILD) 
				GET_XML_ATTRIBUTE("debug", TOKEN_EMULATOR_DEBUG) 
			}
			else if (strstr(BUFFER1_PTR, "<game ") || strstr(BUFFER1_PTR, "<machine "))
			{
				if (strstr(BUFFER1_PTR, "runnable=\"no\"") || strstr(BUFFER1_PTR, "isbios=\"yes\""))
					game_type=FLAG_RESOURCE_NAME;
				else if (strstr(BUFFER1_PTR, "<game "))
					game_type=FLAG_GAME_NAME;
				else if (strstr(BUFFER1_PTR, "<machine "))
					game_type=FLAG_MACHINE_NAME;

				if (game_type==FLAG_GAME_NAME)
				{
					GET_XML_ATTRIBUTE("name", TOKEN_GAME_NAME)
					GET_XML_ATTRIBUTE("sourcefile", TOKEN_GAME_SOURCEFILE)
					GET_XML_ATTRIBUTE("cloneof", TOKEN_GAME_CLONEOF)
					GET_XML_ATTRIBUTE("romof", TOKEN_GAME_ROMOF)
					GET_XML_ATTRIBUTE("sampleof", TOKEN_GAME_SAMPLEOF)
					GET_XML_ATTRIBUTE("rebuildto", TOKEN_GAME_REBUILDTO)
					GET_XML_ATTRIBUTE("board", TOKEN_GAME_BOARD)
				}
				else if (game_type==FLAG_RESOURCE_NAME)
				{
					GET_XML_ATTRIBUTE("name", TOKEN_RESOURCE_NAME) 
					GET_XML_ATTRIBUTE("sourcefile", TOKEN_RESOURCE_SOURCEFILE) 
					GET_XML_ATTRIBUTE("board", TOKEN_RESOURCE_BOARD) 
				}
				if (game_type==FLAG_MACHINE_NAME)
				{
					GET_XML_ATTRIBUTE("name", TOKEN_MACHINE_NAME) 
					GET_XML_ATTRIBUTE("sourcefile", TOKEN_MACHINE_SOURCEFILE) 
					GET_XML_ATTRIBUTE("cloneof", TOKEN_MACHINE_CLONEOF) 
					GET_XML_ATTRIBUTE("romof", TOKEN_MACHINE_ROMOF) 
					GET_XML_ATTRIBUTE("sampleof", TOKEN_MACHINE_SAMPLEOF)
					GET_XML_ATTRIBUTE("board", TOKEN_MACHINE_BOARD)
				}
			}
			//else if (strstr(BUFFER1_PTR, "<comment>"))
			//{
				//GET_XML_ELEMENT(TOKEN_COMMENT_TEXT)
			//}
			else if (strstr(BUFFER1_PTR, "<description>"))
			{
				if (game_type==FLAG_GAME_NAME)
					GET_XML_ELEMENT(TOKEN_GAME_DESCRIPTION)
				else if (game_type==FLAG_RESOURCE_NAME)
					GET_XML_ELEMENT(TOKEN_RESOURCE_DESCRIPTION)
				else if (game_type==FLAG_MACHINE_NAME)
					GET_XML_ELEMENT(TOKEN_MACHINE_DESCRIPTION)
			}
			else if (strstr(BUFFER1_PTR, "<year>"))
			{
				if (game_type==FLAG_GAME_NAME)
					GET_XML_ELEMENT(TOKEN_GAME_YEAR)
				else if (game_type==FLAG_RESOURCE_NAME)
					GET_XML_ELEMENT(TOKEN_RESOURCE_YEAR)
				else if (game_type==FLAG_MACHINE_NAME)
					GET_XML_ELEMENT(TOKEN_MACHINE_YEAR)
			}
			else if (strstr(BUFFER1_PTR, "<manufacturer>"))
			{
				if (game_type==FLAG_GAME_NAME)
					GET_XML_ELEMENT(TOKEN_GAME_MANUFACTURER)
				else if (game_type==FLAG_RESOURCE_NAME)
					GET_XML_ELEMENT(TOKEN_RESOURCE_MANUFACTURER)
				else if (game_type==FLAG_MACHINE_NAME)
					GET_XML_ELEMENT(TOKEN_MACHINE_MANUFACTURER)
			}
			else if (strstr(BUFFER1_PTR, "<history>"))
			{
				if (game_type==FLAG_GAME_NAME)
					GET_XML_ELEMENT(TOKEN_GAME_HISTORY)
				else if (game_type==FLAG_RESOURCE_NAME)
					GET_XML_ELEMENT(TOKEN_RESOURCE_HISTORY)
				else if (game_type==FLAG_MACHINE_NAME)
					GET_XML_ELEMENT(TOKEN_MACHINE_HISTORY)
			}
			else if (strstr(BUFFER1_PTR, "<release "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_RELEASE_NAME) 
				GET_XML_ATTRIBUTE("region", TOKEN_RELEASE_REGION) 
				GET_XML_ATTRIBUTE("language", TOKEN_RELEASE_LANGUAGE) 
				GET_XML_ATTRIBUTE("date", TOKEN_RELEASE_DATE) 
				GET_XML_ATTRIBUTE("default", TOKEN_RELEASE_DEFAULT)
			}
			else if (strstr(BUFFER1_PTR, "<biosset "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_BIOSSET_NAME) 
				GET_XML_ATTRIBUTE("description", TOKEN_BIOSSET_DESCRIPTION) 
				GET_XML_ATTRIBUTE("default", TOKEN_BIOSSET_DEFAULT)
			}
			else if (strstr(BUFFER1_PTR, "<rom "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_ROM_NAME) 
				GET_XML_ATTRIBUTE("bios", TOKEN_ROM_BIOS) 
				GET_XML_ATTRIBUTE("size", TOKEN_ROM_SIZE) 
				GET_XML_ATTRIBUTE("crc", TOKEN_ROM_CRC) 
				GET_XML_ATTRIBUTE("md5", TOKEN_ROM_MD5) 
				GET_XML_ATTRIBUTE("sha1", TOKEN_ROM_SHA1) 
				GET_XML_ATTRIBUTE("merge", TOKEN_ROM_MERGE) 
				GET_XML_ATTRIBUTE("region", TOKEN_ROM_REGION) 
				GET_XML_ATTRIBUTE("offset", TOKEN_ROM_OFFSET) 
				GET_XML_ATTRIBUTE("status", TOKEN_ROM_STATUS) 
				GET_XML_ATTRIBUTE("dispose", TOKEN_ROM_DISPOSE) 
				GET_XML_ATTRIBUTE("soundonly", TOKEN_ROM_SOUNDONLY)
			}
			else if (strstr(BUFFER1_PTR, "<disk "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_DISK_NAME) 
				GET_XML_ATTRIBUTE("md5", TOKEN_DISK_MD5) 
				GET_XML_ATTRIBUTE("sha1", TOKEN_DISK_SHA1) 
				GET_XML_ATTRIBUTE("merge", TOKEN_DISK_MERGE) 
				GET_XML_ATTRIBUTE("region", TOKEN_DISK_REGION) 
				GET_XML_ATTRIBUTE("index", TOKEN_DISK_INDEX) 
				GET_XML_ATTRIBUTE("status", TOKEN_DISK_STATUS)
			}
			else if (strstr(BUFFER1_PTR, "<sample "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_SAMPLE_NAME)
			}
			else if (strstr(BUFFER1_PTR, "<chip "))
			{
				GET_XML_ATTRIBUTE("type", TOKEN_CHIP_TYPE) 
				GET_XML_ATTRIBUTE("name", TOKEN_CHIP_NAME) 
				GET_XML_ATTRIBUTE("soundonly", TOKEN_CHIP_SOUNDONLY)
				GET_XML_ATTRIBUTE("clock", TOKEN_CHIP_CLOCK) 
			}
			else if (strstr(BUFFER1_PTR, "<video "))
			{
				GET_XML_ATTRIBUTE("screen", TOKEN_VIDEO_SCREEN) 
				GET_XML_ATTRIBUTE("orientation", TOKEN_VIDEO_ORIENTATION) 
				GET_XML_ATTRIBUTE("width", TOKEN_VIDEO_WIDTH) 
				GET_XML_ATTRIBUTE("height", TOKEN_VIDEO_HEIGHT) 
				GET_XML_ATTRIBUTE("aspectx", TOKEN_VIDEO_ASPECTX) 
				GET_XML_ATTRIBUTE("aspecty", TOKEN_VIDEO_ASPECTY) 
				GET_XML_ATTRIBUTE("refresh", TOKEN_VIDEO_REFRESH) 
			}
			else if (strstr(BUFFER1_PTR, "<display "))
			{
				GET_XML_ATTRIBUTE("type", TOKEN_DISPLAY_TYPE) 
				GET_XML_ATTRIBUTE("rotate", TOKEN_DISPLAY_ROTATE) 
				GET_XML_ATTRIBUTE("flipx", TOKEN_DISPLAY_FLIPX) 
				GET_XML_ATTRIBUTE("width", TOKEN_DISPLAY_WIDTH) 
				GET_XML_ATTRIBUTE("height", TOKEN_DISPLAY_HEIGHT) 
				GET_XML_ATTRIBUTE("refresh", TOKEN_DISPLAY_REFRESH) 
			}
			else if (strstr(BUFFER1_PTR, "<sound "))
			{
				GET_XML_ATTRIBUTE("channels", TOKEN_SOUND_CHANNELS)
			}
			else if (strstr(BUFFER1_PTR, "<input "))
			{
				GET_XML_ATTRIBUTE("players", TOKEN_INPUT_PLAYERS)
				GET_XML_ATTRIBUTE("service", TOKEN_INPUT_SERVICE)
				GET_XML_ATTRIBUTE("tilt", TOKEN_INPUT_TILT)
				GET_XML_ATTRIBUTE("control", TOKEN_INPUT_CONTROL)
				GET_XML_ATTRIBUTE("buttons", TOKEN_INPUT_BUTTONS)
				GET_XML_ATTRIBUTE("coins", TOKEN_INPUT_COINS)
				GET_XML_ATTRIBUTE("dipswitches", TOKEN_INPUT_DIPSWITCHES)
			}
			else if (strstr(BUFFER1_PTR, "<control "))
			{
				GET_XML_ATTRIBUTE("type", TOKEN_CONTROL_TYPE)
				GET_XML_ATTRIBUTE("minimum", TOKEN_CONTROL_MINIMUM)
				GET_XML_ATTRIBUTE("maximum", TOKEN_CONTROL_MAXIMUM)
				GET_XML_ATTRIBUTE("sensitivity", TOKEN_CONTROL_SENSITIVITY)
				GET_XML_ATTRIBUTE("keydelta", TOKEN_CONTROL_KEYDELTA)
				GET_XML_ATTRIBUTE("reverse", TOKEN_CONTROL_REVERSE)
			}
			else if (strstr(BUFFER1_PTR, "<dipswitch "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_DIPSWITCH_NAME)
			}
			else if (strstr(BUFFER1_PTR, "<dipvalue "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_DIPVALUE_NAME)
				GET_XML_ATTRIBUTE("default", TOKEN_DIPVALUE_DEFAULT)
			}
			else if (strstr(BUFFER1_PTR, "<driver "))
			{
				GET_XML_ATTRIBUTE("status", TOKEN_DRIVER_STATUS)
				GET_XML_ATTRIBUTE("emulation", TOKEN_DRIVER_EMULATION)
				GET_XML_ATTRIBUTE("color", TOKEN_DRIVER_COLOR)
				GET_XML_ATTRIBUTE("sound", TOKEN_DRIVER_SOUND)
				GET_XML_ATTRIBUTE("graphic", TOKEN_DRIVER_GRAPHIC)
				GET_XML_ATTRIBUTE("cocktail", TOKEN_DRIVER_COCKTAIL)
				GET_XML_ATTRIBUTE("protection", TOKEN_DRIVER_PROTECTION)
				GET_XML_ATTRIBUTE("savestate", TOKEN_DRIVER_SAVESTATE)
				GET_XML_ATTRIBUTE("palettesize", TOKEN_DRIVER_PALETTESIZE)
				GET_XML_ATTRIBUTE("colordeep", TOKEN_DRIVER_COLORDEEP)
				GET_XML_ATTRIBUTE("credits", TOKEN_DRIVER_CREDITS)
			}
			else if (strstr(BUFFER1_PTR, "<device "))
			{
				if (strstr(BUFFER1_PTR, "type="))
				{
					GET_XML_ATTRIBUTE("type", TOKEN_DEVICE_TYPE)
				}
				else
				{
					GET_XML_ATTRIBUTE("name", TOKEN_DEVICE_NAME)
				}
				GET_XML_ATTRIBUTE("tag", TOKEN_DEVICE_TAG)
				GET_XML_ATTRIBUTE("mandatory", TOKEN_DEVICE_MANDATORY)
			}
			else if (strstr(BUFFER1_PTR, "<extension "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_EXTENSION_NAME)
			}
			else if (strstr(BUFFER1_PTR, "<archive "))
			{
				GET_XML_ATTRIBUTE("name", TOKEN_ARCHIVE_NAME)
			}
			else if (strstr(BUFFER1_PTR, "<ramoption ") || strstr(BUFFER1_PTR, "<ramoption>"))
			{
				GET_XML_ELEMENT(TOKEN_RAMOPTION_SIZE)
				GET_XML_ATTRIBUTE("default", TOKEN_RAMOPTION_DEFAULT)
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}

int load_mess_listxml(struct dat *dat)
{
	return(load_mame_listxml(dat));
}

int load_generic_xml(struct dat *dat)
{
	return(load_mame_listxml(dat));
}


/* --- Specify --- */

int specify_mame_listxml(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "listxml") &&
		strcmp(dat->options->save_format, "xml") &&
		strcmp(dat->options->save_format, "lx"))
		return(0);
	else
		return(1);
}

int specify_mess_listxml(struct dat *dat)
{
	return(0);
}

int specify_generic_xml(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "genericxml") &&
		strcmp(dat->options->save_format, "generic") &&
		strcmp(dat->options->save_format, "gx"))
	{
		return(0);
	}
	else
	{
		// Generic XML should not retain full details, even if the user asked for them!
		dat->options->options=dat->options->options & ~OPTION_KEEP_FULL_DETAILS;
		return(1);
	}
}


/* --- Save --- */

#define OUTPUT_XML_STRING(STRING) \
{ \
	unsigned char *ptr=STRING; \
\
	while (*ptr) \
	{ \
		switch (*ptr) \
		{ \
			case '&': \
				fprintf(dat->out, "&amp;"); \
				break; \
			case '<': \
				fprintf(dat->out, "&lt;"); \
				break; \
			case '>': \
				fprintf(dat->out, "&gt;"); \
				break; \
			case '\"': \
				fprintf(dat->out, "&quot;"); \
				break; \
			default: \
				if (*ptr>=' ' && *ptr<='~') \
					fprintf(dat->out, "%c", *ptr); \
				else \
					fprintf(dat->out, "&#%d;", *ptr); \
				break; \
		} \
		ptr++; \
	} \
}

#define OUTPUT_STRING_ATTRIBUTE(OBJECT, ATTRIBUTE, ATTRIBUTE_NAME, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, " %s=\"", ATTRIBUTE_NAME); \
	OUTPUT_XML_STRING(curr_##OBJECT->ATTRIBUTE); \
	fprintf(dat->out, "\""); \
	dat->OBJECT##_saved|=ATTRIBUTE_FLAG; \
}

#define OUTPUT_UNSIGNED_LONG_ATTRIBUTE(OBJECT, ATTRIBUTE, ATTRIBUTE_NAME, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, " %s=\"%lu\"", ATTRIBUTE_NAME, (unsigned long)curr_##OBJECT->ATTRIBUTE); \
	dat->OBJECT##_saved|=ATTRIBUTE_FLAG; \
}

#define OUTPUT_SIGNED_LONG_ATTRIBUTE(OBJECT, ATTRIBUTE, ATTRIBUTE_NAME, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, " %s=\"%ld\"", ATTRIBUTE_NAME, (long)curr_##OBJECT->ATTRIBUTE); \
	dat->OBJECT##_saved|=ATTRIBUTE_FLAG; \
}

#define OUTPUT_0_6_FLOAT_ATTRIBUTE(OBJECT, ATTRIBUTE, ATTRIBUTE_NAME, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, " %s=\"%0.6f\"", ATTRIBUTE_NAME, curr_##OBJECT->ATTRIBUTE); \
	dat->OBJECT##_saved|=ATTRIBUTE_FLAG; \
}

#define OUTPUT_PADDED_HEX_ATTRIBUTE(OBJECT, ATTRIBUTE, ATTRIBUTE_NAME, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, " %s=\"%08lx\"", ATTRIBUTE_NAME, (unsigned long)curr_##OBJECT->ATTRIBUTE); \
	dat->OBJECT##_saved|=ATTRIBUTE_FLAG; \
}

#define OUTPUT_UNPADDED_HEX_ATTRIBUTE(OBJECT, ATTRIBUTE, ATTRIBUTE_NAME, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, " %s=\"%lx\"", ATTRIBUTE_NAME, (unsigned long)curr_##OBJECT->ATTRIBUTE); \
	dat->OBJECT##_saved|=ATTRIBUTE_FLAG; \
}

#define OUTPUT_STRING_ELEMENT(OBJECT, ELEMENT, TABS, ELEMENT_NAME, ELEMENT_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ELEMENT_FLAG) \
{ \
	fprintf(dat->out, "%s<%s>", TABS, ELEMENT_NAME); \
	OUTPUT_XML_STRING(curr_##OBJECT->ELEMENT); \
	fprintf(dat->out, "</%s>\n", ELEMENT_NAME); \
	dat->OBJECT##_saved|=ELEMENT_FLAG; \
}

int save_mame_listxml(struct dat *dat)
{
	char *doc_type;
	char *game_type;

	struct game *curr_game=0;
	struct comment *curr_comment=0;
	struct release *curr_release=0;
	struct biosset *curr_biosset=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;
	struct chip *curr_chip=0;
	struct video *curr_video=0;
	struct display *curr_display=0;
	struct sound *curr_sound=0;
	struct input *curr_input=0;
	struct control *curr_control=0;
	struct dipswitch *curr_dipswitch=0;
	struct dipvalue *curr_dipvalue=0;
	struct driver *curr_driver=0;
	struct device *curr_device=0;
	struct extension *curr_extension=0;
	struct archive *curr_archive=0;
	struct ramoption *curr_ramoption=0;

	uint32_t i, j, k;
	int errflg=0;

	/* --- Determine the type of merging based on dat flags --- */

	if (dat->dat_flags & FLAG_DAT_FULL_MERGING)
	{
		dat->clrmamepro.forcemerging="full";
		dat->romcenter.rommode="merged";
	}
	else if (dat->dat_flags & FLAG_DAT_SPLIT_MERGING)
	{
		dat->clrmamepro.forcemerging="split";
		dat->romcenter.rommode="split";
	}
	else if (dat->dat_flags & FLAG_DAT_NO_MERGING)
	{
		dat->clrmamepro.forcemerging="none";
		dat->romcenter.rommode="unmerged";
	}

	/* --- Determine the document type and game type (n.b. Generic XML only supports games, not machines) --- */

	doc_type=dat->emulator.name;

	if (doc_type && !(strcmp(doc_type, "datafile")))
	{
		game_type="game";
	}
	else
	{
		if (dat->num_machines)
		{
			doc_type=doc_type ? doc_type : "mess";
			game_type="machine";
		}
		else
		{
			doc_type=doc_type ? doc_type : "mame";
			game_type="game";
		}
	}

	/* --- Write XML header --- */

	fprintf(dat->out, "<?xml version=\"1.0\"?>\n");

	/* --- Write the DTD --- */

	if (strcmp(doc_type, "datafile"))
	{
		fprintf(dat->out, "<!DOCTYPE %s [\n", doc_type);
		fprintf(dat->out, "<!ELEMENT %s (%s+)>\n", doc_type, game_type);
		if (dat->emulator.build)
			fprintf(dat->out, "\t<!ATTLIST %s build CDATA #IMPLIED>\n", doc_type);
		if (dat->emulator.debug)
			fprintf(dat->out, "\t<!ATTLIST %s debug (yes|no) \"no\">\n", doc_type);

		fprintf(dat->out, "\t<!ELEMENT %s (", game_type);
		if (dat->num_comments)
			fprintf(dat->out, "comment*, ");
		fprintf(dat->out, "description");
		if (dat->game_flags & FLAG_GAME_YEAR)
			fprintf(dat->out, ", year?");
		if (dat->game_flags & FLAG_GAME_MANUFACTURER)
			fprintf(dat->out, ", manufacturer");
		if (dat->game_flags & FLAG_GAME_HISTORY)
			fprintf(dat->out, ", history?");
		if (dat->num_releases)
			fprintf(dat->out, ", releases*");
		if (dat->num_biossets)
			fprintf(dat->out, ", biosset*");
		if (dat->num_roms)
			fprintf(dat->out, ", rom*");
		if (dat->num_disks)
			fprintf(dat->out, ", disk*");
		if (dat->num_samples)
			fprintf(dat->out, ", sample*");
		if (dat->num_chips)
			fprintf(dat->out, ", chip*");
		if (dat->num_videos)
			fprintf(dat->out, ", video?");
		if (dat->num_displays)
			fprintf(dat->out, ", display*");
		if (dat->num_sounds)
			fprintf(dat->out, ", sound?");
		if (dat->num_inputs)
			fprintf(dat->out, ", input?");
		if (dat->num_dipswitches)
			fprintf(dat->out, ", dipswitch*");
		if (dat->num_drivers)
			fprintf(dat->out, ", driver?");
		if (dat->num_devices)
			fprintf(dat->out, ", device*");
		if (dat->num_archives)
			fprintf(dat->out, ", archive*");
		if (dat->num_ramoptions)
			fprintf(dat->out, ", ramoption*");
		fprintf(dat->out, ")>\n");
		fprintf(dat->out, "\t\t<!ATTLIST %s name CDATA #REQUIRED>\n", game_type);
		if (dat->game_flags & FLAG_GAME_SOURCEFILE)
			fprintf(dat->out, "\t\t<!ATTLIST %s sourcefile CDATA #IMPLIED>\n", game_type);
		if (dat->num_resources)
			fprintf(dat->out, "\t\t<!ATTLIST %s isbios (yes|no) \"no\">\n", game_type);
		if (dat->game_flags & FLAG_GAME_CLONEOF)
			fprintf(dat->out, "\t\t<!ATTLIST %s cloneof CDATA #IMPLIED>\n", game_type);
		if (dat->game_flags & FLAG_GAME_ROMOF)
			fprintf(dat->out, "\t\t<!ATTLIST %s romof CDATA #IMPLIED>\n", game_type);
		if (dat->game_flags & FLAG_GAME_SAMPLEOF)
			fprintf(dat->out, "\t\t<!ATTLIST %s sampleof CDATA #IMPLIED>\n", game_type);
		if (dat->game_flags & FLAG_GAME_REBUILDTO)
			fprintf(dat->out, "\t\t<!ATTLIST %s rebuildto CDATA #IMPLIED>\n", game_type);
		if (dat->game_flags & FLAG_GAME_BOARD)
			fprintf(dat->out, "\t\t<!ATTLIST %s board CDATA #IMPLIED>\n", game_type);

		if (dat->comment_flags & FLAG_COMMENT_TEXT)
			fprintf(dat->out, "\t\t<!ELEMENT comment (#PCDATA)>\n");

		fprintf(dat->out, "\t\t<!ELEMENT description (#PCDATA)>\n");
		if (dat->game_flags & FLAG_GAME_YEAR)
			fprintf(dat->out, "\t\t<!ELEMENT year (#PCDATA)>\n");
		if (dat->game_flags & FLAG_GAME_MANUFACTURER)
			fprintf(dat->out, "\t\t<!ELEMENT manufacturer (#PCDATA)>\n");
		if (dat->game_flags & FLAG_GAME_HISTORY)
			fprintf(dat->out, "\t\t<!ELEMENT history (#PCDATA)>\n");

		if (dat->num_releases)
		{
			fprintf(dat->out, "\t\t<!ELEMENT release EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST release name CDATA #REQUIRED>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST release region CDATA #REQUIRED>\n");
			if (dat->release_flags & FLAG_RELEASE_LANGUAGE)
				fprintf(dat->out, "\t\t\t<!ATTLIST release language CDATA #IMPLIED>\n");
			if (dat->release_flags & FLAG_RELEASE_DATE)
				fprintf(dat->out, "\t\t\t<!ATTLIST release date CDATA #IMPLIED>\n");
			if (dat->release_flags & FLAG_RELEASE_DEFAULT)
				fprintf(dat->out, "\t\t\t<!ATTLIST release default (yes|no) \"no\">\n");
		}

		if (dat->num_biossets)
		{
			fprintf(dat->out, "\t\t<!ELEMENT biosset EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST biosset name CDATA #REQUIRED>\n");
			if (dat->biosset_flags & FLAG_BIOSSET_DESCRIPTION)
				fprintf(dat->out, "\t\t\t<!ATTLIST biosset description CDATA #REQUIRED>\n");
			if (dat->biosset_flags & FLAG_BIOSSET_DEFAULT)
				fprintf(dat->out, "\t\t\t<!ATTLIST biosset default (yes|no) \"no\">\n");
		}

		if (dat->num_roms)
		{
			fprintf(dat->out, "\t\t<!ELEMENT rom EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST rom name CDATA #REQUIRED>\n");
			if (dat->rom_flags & FLAG_ROM_BIOS)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom bios CDATA #IMPLIED>\n");
			if (dat->rom_flags & FLAG_ROM_SIZE)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom size CDATA #REQUIRED>\n");
			if (dat->rom_flags & FLAG_ROM_CRC)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom crc CDATA #IMPLIED>\n");
			if (dat->rom_flags & FLAG_ROM_MD5)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom md5 CDATA #IMPLIED>\n");
			if (dat->rom_flags & FLAG_ROM_SHA1)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom sha1 CDATA #IMPLIED>\n");
			if (dat->rom_flags & FLAG_ROM_MERGE)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom merge CDATA #IMPLIED>\n");
			if (dat->rom_flags & FLAG_ROM_REGION)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom region CDATA #IMPLIED>\n");
			if (dat->rom_flags & FLAG_ROM_OFFSET)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom offset CDATA #IMPLIED>\n");
			if (dat->rom_flags & FLAG_ROM_STATUS)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom status (baddump|nodump|good) \"good\">\n");
			if (dat->rom_flags & FLAG_ROM_DISPOSE)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom dispose (yes|no) \"no\">\n");
			if (dat->rom_flags & FLAG_ROM_SOUNDONLY)
				fprintf(dat->out, "\t\t\t<!ATTLIST rom soundonly (yes|no) \"no\">\n");
		}

		if (dat->num_disks)
		{
			fprintf(dat->out, "\t\t<!ELEMENT disk EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST disk name CDATA #REQUIRED>\n");
			if (dat->disk_flags & FLAG_DISK_MD5)
				fprintf(dat->out, "\t\t\t<!ATTLIST disk md5 CDATA #IMPLIED>\n");
			if (dat->disk_flags & FLAG_DISK_SHA1)
				fprintf(dat->out, "\t\t\t<!ATTLIST disk sha1 CDATA #IMPLIED>\n");
			if (dat->disk_flags & FLAG_DISK_MERGE)
				fprintf(dat->out, "\t\t\t<!ATTLIST disk merge CDATA #IMPLIED>\n");
			if (dat->disk_flags & FLAG_DISK_REGION)
				fprintf(dat->out, "\t\t\t<!ATTLIST disk region CDATA #IMPLIED>\n");
			if (dat->disk_flags & FLAG_DISK_INDEX)
				fprintf(dat->out, "\t\t\t<!ATTLIST disk index CDATA #IMPLIED>\n");
			if (dat->disk_flags & FLAG_DISK_STATUS)
				fprintf(dat->out, "\t\t\t<!ATTLIST disk status (baddump|nodump|good) \"good\">\n");
		}

		if (dat->num_samples)
		{
			fprintf(dat->out, "\t\t<!ELEMENT sample EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST sample name CDATA #REQUIRED>\n");
		}

		if (dat->num_chips)
		{
			fprintf(dat->out, "\t\t<!ELEMENT chip EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST chip name CDATA #REQUIRED>\n");
			if (dat->chip_flags & FLAG_CHIP_TYPE)
				fprintf(dat->out, "\t\t\t<!ATTLIST chip type (cpu|audio) #REQUIRED>\n");
			if (dat->chip_flags & FLAG_CHIP_SOUNDONLY)
				fprintf(dat->out, "\t\t\t<!ATTLIST chip soundonly (yes|no) \"no\">\n");
			if (dat->chip_flags & FLAG_CHIP_CLOCK)
				fprintf(dat->out, "\t\t\t<!ATTLIST chip clock CDATA #IMPLIED>\n");
		}

		if (dat->num_videos)
		{
			fprintf(dat->out, "\t\t<!ELEMENT video EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST video screen (raster|vector) #REQUIRED>\n");
			if (dat->video_flags & FLAG_VIDEO_ORIENTATION)
				fprintf(dat->out, "\t\t\t<!ATTLIST video orientation (vertical|horizontal) #REQUIRED>\n");
			if (dat->video_flags & FLAG_VIDEO_WIDTH)
				fprintf(dat->out, "\t\t\t<!ATTLIST video width CDATA #IMPLIED>\n");
			if (dat->video_flags & FLAG_VIDEO_HEIGHT)
				fprintf(dat->out, "\t\t\t<!ATTLIST video height CDATA #IMPLIED>\n");
			if (dat->video_flags & FLAG_VIDEO_ASPECTX)
				fprintf(dat->out, "\t\t\t<!ATTLIST video aspectx CDATA #IMPLIED>\n");
			if (dat->video_flags & FLAG_VIDEO_ASPECTY)
				fprintf(dat->out, "\t\t\t<!ATTLIST video aspecty CDATA #IMPLIED>\n");
			if (dat->video_flags & FLAG_VIDEO_REFRESH)
				fprintf(dat->out, "\t\t\t<!ATTLIST video refresh CDATA #REQUIRED>\n");
		}

		if (dat->num_displays)
		{
			fprintf(dat->out, "\t\t<!ELEMENT display EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST display type (raster|vector) #REQUIRED>\n");
			if (dat->display_flags & FLAG_DISPLAY_ROTATE)
				fprintf(dat->out, "\t\t\t<!ATTLIST display rotate (0|90|180|270) #REQUIRED>\n");
			if (dat->display_flags & FLAG_DISPLAY_FLIPX)
				fprintf(dat->out, "\t\t\t<!ATTLIST display flipx (yes|no) \"no\">\n");
			if (dat->display_flags & FLAG_DISPLAY_WIDTH)
				fprintf(dat->out, "\t\t\t<!ATTLIST display width CDATA #IMPLIED>\n");
			if (dat->display_flags & FLAG_DISPLAY_HEIGHT)
				fprintf(dat->out, "\t\t\t<!ATTLIST display height CDATA #IMPLIED>\n");
			if (dat->display_flags & FLAG_DISPLAY_REFRESH)
				fprintf(dat->out, "\t\t\t<!ATTLIST display refresh CDATA #REQUIRED>\n");
		}

		if (dat->num_sounds)
		{
			fprintf(dat->out, "\t\t<!ELEMENT sound EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST sound channels CDATA #REQUIRED>\n");
		}

		if (dat->num_inputs)
		{
			if (dat->num_controls)
				fprintf(dat->out, "\t\t<!ELEMENT input (control*)>\n");
			else
				fprintf(dat->out, "\t\t<!ELEMENT input EMPTY>\n");
			if (dat->input_flags & FLAG_INPUT_SERVICE)
				fprintf(dat->out, "\t\t\t<!ATTLIST input service (yes|no) \"no\">\n");
			if (dat->input_flags & FLAG_INPUT_TILT)
				fprintf(dat->out, "\t\t\t<!ATTLIST input tilt (yes|no) \"no\">\n");
			if (dat->input_flags & FLAG_INPUT_PLAYERS)
				fprintf(dat->out, "\t\t\t<!ATTLIST input players CDATA #REQUIRED>\n");
			if (dat->input_flags & FLAG_INPUT_CONTROL)
				fprintf(dat->out, "\t\t\t<!ATTLIST input control CDATA #IMPLIED>\n");
			if (dat->input_flags & FLAG_INPUT_BUTTONS)
				fprintf(dat->out, "\t\t\t<!ATTLIST input buttons CDATA #IMPLIED>\n");
			if (dat->input_flags & FLAG_INPUT_COINS)
				fprintf(dat->out, "\t\t\t<!ATTLIST input coins CDATA #IMPLIED>\n");
			if (dat->input_flags & FLAG_INPUT_DIPSWITCHES)
				fprintf(dat->out, "\t\t\t<!ATTLIST input dipswitches CDATA #IMPLIED>\n");
		}

		if (dat->num_controls)
		{
			fprintf(dat->out, "\t\t\t<!ELEMENT control EMPTY>\n");
			fprintf(dat->out, "\t\t\t\t<!ATTLIST control type CDATA #REQUIRED>\n");
			if (dat->control_flags & FLAG_CONTROL_MINIMUM)
				fprintf(dat->out, "\t\t\t\t<!ATTLIST control minimum CDATA #IMPLIED>\n");
			if (dat->control_flags & FLAG_CONTROL_MAXIMUM)
				fprintf(dat->out, "\t\t\t\t<!ATTLIST control maximum CDATA #IMPLIED>\n");
			if (dat->control_flags & FLAG_CONTROL_SENSITIVITY)
				fprintf(dat->out, "\t\t\t\t<!ATTLIST control sensitivity CDATA #IMPLIED>\n");
			if (dat->control_flags & FLAG_CONTROL_KEYDELTA)
				fprintf(dat->out, "\t\t\t\t<!ATTLIST control keydelta CDATA #IMPLIED>\n");
			if (dat->control_flags & FLAG_CONTROL_REVERSE)
				fprintf(dat->out, "\t\t\t\t<!ATTLIST control reverse (yes|no) \"no\">\n");
		}

		if (dat->num_dipswitches)
		{
			if (dat->num_dipvalues)
				fprintf(dat->out, "\t\t<!ELEMENT dipswitch (dipvalue*)>\n");
			else
				fprintf(dat->out, "\t\t<!ELEMENT dipswitch EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST dipswitch name CDATA #REQUIRED>\n");
		}

		if (dat->num_dipvalues)
		{
			fprintf(dat->out, "\t\t\t<!ELEMENT dipvalue EMPTY>\n");
			fprintf(dat->out, "\t\t\t\t<!ATTLIST dipvalue name CDATA #REQUIRED>\n");
			if (dat->dipvalue_flags & FLAG_DIPVALUE_DEFAULT)
				fprintf(dat->out, "\t\t\t\t<!ATTLIST dipvalue default (yes|no) \"no\">\n");
		}

		if (dat->num_drivers)
		{
			fprintf(dat->out, "\t\t<!ELEMENT driver EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST driver status (good|imperfect|preliminary) #REQUIRED>\n");
			if (dat->driver_flags & FLAG_DRIVER_EMULATION)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver emulation (good|imperfect|preliminary) #REQUIRED>\n");
			if (dat->driver_flags & FLAG_DRIVER_COLOR)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver color (good|imperfect|preliminary) #REQUIRED>\n");
			if (dat->driver_flags & FLAG_DRIVER_SOUND)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver sound (good|imperfect|preliminary) #REQUIRED>\n");
			if (dat->driver_flags & FLAG_DRIVER_GRAPHIC)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver graphic (good|imperfect|preliminary) #REQUIRED>\n");
			if (dat->driver_flags & FLAG_DRIVER_COCKTAIL)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver cocktail (good|imperfect|preliminary) #IMPLIED>\n");
			if (dat->driver_flags & FLAG_DRIVER_PROTECTION)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver protection (good|imperfect|preliminary) #IMPLIED>\n");
			if (dat->driver_flags & FLAG_DRIVER_SAVESTATE)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver savestate (supported|unsupported) #REQUIRED>\n");
			if (dat->driver_flags & FLAG_DRIVER_PALETTESIZE)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver palettesize CDATA #REQUIRED>\n");
			if (dat->driver_flags & FLAG_DRIVER_COLORDEEP)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver colordeep CDATA #REQUIRED>\n");
			if (dat->driver_flags & FLAG_DRIVER_CREDITS)
				fprintf(dat->out, "\t\t\t<!ATTLIST driver credits CDATA #IMPLIED>\n");
		}

		if (dat->num_devices)
		{
			if (dat->num_extensions)
				fprintf(dat->out, "\t\t<!ELEMENT device (extension*)>\n");
			else
				fprintf(dat->out, "\t\t<!ELEMENT device EMPTY>\n");
			if (dat->device_flags & FLAG_DEVICE_TYPE)
				fprintf(dat->out, "\t\t\t<!ATTLIST device type CDATA #REQUIRED>\n");
			if (dat->device_flags & FLAG_DEVICE_NAME)
				fprintf(dat->out, "\t\t\t<!ATTLIST device name CDATA #REQUIRED>\n");
			if (dat->device_flags & FLAG_DEVICE_TAG)
				fprintf(dat->out, "\t\t\t<!ATTLIST device tag CDATA #IMPLIED>\n");
			if (dat->device_flags & FLAG_DEVICE_MANDATORY)
				fprintf(dat->out, "\t\t\t<!ATTLIST device mandatory CDATA #IMPLIED>\n");
		}

		if (dat->num_extensions)
		{
			fprintf(dat->out, "\t\t\t<!ELEMENT extension EMPTY>\n");
			fprintf(dat->out, "\t\t\t\t<!ATTLIST extension name CDATA #REQUIRED>\n");
		}

		if (dat->num_archives)
		{
			fprintf(dat->out, "\t\t<!ELEMENT archive EMPTY>\n");
			fprintf(dat->out, "\t\t\t<!ATTLIST archive name CDATA #REQUIRED>\n");
		}

		if (dat->num_ramoptions)
		{
			fprintf(dat->out, "\t\t<!ELEMENT ramoption (#PCDATA)>\n");
			if (dat->ramoption_flags & FLAG_RAMOPTION_DEFAULT)
				fprintf(dat->out, "\t\t\t<!ATTLIST ramoption default CDATA #IMPLIED>\n");
		}

		fprintf(dat->out, "]>\n\n");
	}
	else
	{
		fprintf(dat->out, "<!DOCTYPE datafile PUBLIC \"-//Logiqx//DTD ROM Management Datafile//EN\" \"http://www.logiqx.com/Dats/datafile.dtd\">\n");
	}

	/* --- Main element --- */

	fprintf(dat->out, "<%s", doc_type);
	dat->emulator_saved|=FLAG_EMULATOR_NAME;

	if (dat->emulator.build)
		fprintf(dat->out, " build=\"%s\"", dat->emulator.build);
	dat->emulator_saved|=FLAG_EMULATOR_BUILD;

	if (dat->emulator.debug)
		fprintf(dat->out, " debug=\"%s\"", dat->emulator.debug);
	dat->emulator_saved|=FLAG_EMULATOR_DEBUG;

	fprintf(dat->out, ">\n");

	/* --- Header element --- */

	if (!strcmp(doc_type, "datafile"))
	{
		if (dat->header_flags || dat->clrmamepro_flags || dat->romcenter_flags)
			fprintf(dat->out, "\t<header>\n");

		if (dat->header.name!=0)
			fprintf(dat->out, "\t\t<name>%s</name>\n", dat->header.name);
		dat->header_saved|=FLAG_HEADER_NAME;

		if (dat->header.description!=0)
			fprintf(dat->out, "\t\t<description>%s</description>\n", dat->header.description);
		dat->header_saved|=FLAG_HEADER_DESCRIPTION;

		if (dat->header.category!=0)
			fprintf(dat->out, "\t\t<category>%s</category>\n", dat->header.category);
		dat->header_saved|=FLAG_HEADER_CATEGORY;

		if (dat->header.version!=0)
			fprintf(dat->out, "\t\t<version>%s</version>\n", dat->header.version);
		dat->header_saved|=FLAG_HEADER_VERSION;

		if (dat->header.date!=0)
			fprintf(dat->out, "\t\t<date>%s</date>\n", dat->header.date);
		dat->header_saved|=FLAG_HEADER_DATE;

		if (dat->header.author!=0)
			fprintf(dat->out, "\t\t<author>%s</author>\n", dat->header.author);
		dat->header_saved|=FLAG_HEADER_AUTHOR;

		if (dat->header.email!=0)
			fprintf(dat->out, "\t\t<email>%s</email>\n", dat->header.email);
		dat->header_saved|=FLAG_HEADER_EMAIL;

		if (dat->header.homepage!=0)
			fprintf(dat->out, "\t\t<homepage>%s</homepage>\n", dat->header.homepage);
		dat->header_saved|=FLAG_HEADER_HOMEPAGE;

		if (dat->header.url!=0)
			fprintf(dat->out, "\t\t<url>%s</url>\n", dat->header.url);
		dat->header_saved|=FLAG_HEADER_URL;

		if (dat->header.comment!=0)
			fprintf(dat->out, "\t\t<comment>%s</comment>\n", dat->header.comment);
		dat->header_saved|=FLAG_HEADER_COMMENT;

		if (dat->clrmamepro.header!= 0 || dat->clrmamepro.forcemerging ||
			dat->clrmamepro.forcenodump || dat->clrmamepro.forcepacking)
		{
			fprintf(dat->out, "\t\t<clrmamepro");
			if (dat->clrmamepro.header!=0)
				fprintf(dat->out, " header=\"%s\"", dat->clrmamepro.header);
			dat->clrmamepro_saved|=FLAG_CLRMAMEPRO_HEADER;

			if (dat->clrmamepro.forcemerging!=0)
				fprintf(dat->out, " forcemerging=\"%s\"", dat->clrmamepro.forcemerging);
			dat->clrmamepro_saved|=FLAG_CLRMAMEPRO_FORCEMERGING;

			if (dat->clrmamepro.forcenodump!=0)
				fprintf(dat->out, " forcenodump=\"%s\"", dat->clrmamepro.forcenodump);
			dat->clrmamepro_saved|=FLAG_CLRMAMEPRO_FORCENODUMP;

			if (dat->clrmamepro.forcepacking!=0)
				fprintf(dat->out, " forcepacking=\"%s\"", dat->clrmamepro.forcepacking);
			dat->clrmamepro_saved|=FLAG_CLRMAMEPRO_FORCEPACKING;

			fprintf(dat->out, "/>\n");
		}

		if (dat->romcenter.plugin!= 0 ||
			dat->romcenter.rommode || dat->romcenter.biosmode || dat->romcenter.samplemode ||
			dat->romcenter.lockrommode || dat->romcenter.lockbiosmode || dat->romcenter.locksamplemode)
		{
			fprintf(dat->out, "\t\t<romcenter");
			if (dat->romcenter.plugin!=0)
				fprintf(dat->out, " plugin=\"%s\"", dat->romcenter.plugin);
			dat->romcenter_saved|=FLAG_ROMCENTER_PLUGIN;

			if (dat->romcenter.rommode!=0)
				fprintf(dat->out, " rommode=\"%s\"", dat->romcenter.rommode);
			dat->romcenter_saved|=FLAG_ROMCENTER_ROMMODE;

			if (dat->romcenter.biosmode!=0)
				fprintf(dat->out, " biosmode=\"%s\"", dat->romcenter.biosmode);
			dat->romcenter_saved|=FLAG_ROMCENTER_BIOSMODE;

			if (dat->romcenter.samplemode!=0)
				fprintf(dat->out, " samplemode=\"%s\"", dat->romcenter.samplemode);
			dat->romcenter_saved|=FLAG_ROMCENTER_SAMPLEMODE;

			if (dat->romcenter.lockrommode!=0)
				fprintf(dat->out, " lockrommode=\"%s\"", dat->romcenter.lockrommode);
			dat->romcenter_saved|=FLAG_ROMCENTER_LOCKROMMODE;

			if (dat->romcenter.lockbiosmode!=0)
				fprintf(dat->out, " lockbiosmode=\"%s\"", dat->romcenter.lockbiosmode);
			dat->romcenter_saved|=FLAG_ROMCENTER_LOCKBIOSMODE;

			if (dat->romcenter.locksamplemode!=0)
				fprintf(dat->out, " locksamplemode=\"%s\"", dat->romcenter.locksamplemode);
			dat->romcenter_saved|=FLAG_ROMCENTER_LOCKSAMPLEMODE;

			fprintf(dat->out, "/>\n");
		}

		if (dat->header_flags || dat->clrmamepro_flags || dat->romcenter_flags)
			fprintf(dat->out, "\t</header>\n");
	}

	/* --- For every game, machine and resource --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		/* --- Game/machine information --- */

		fprintf(dat->out, "\t<%s", game_type);

		if (curr_game->game_flags & FLAG_RESOURCE_NAME)
			fprintf(dat->out, " isbios=\"yes\"");
		OUTPUT_STRING_ATTRIBUTE(game, name, "name", (FLAG_GAME_NAME|FLAG_RESOURCE_NAME|FLAG_MACHINE_NAME))
		OUTPUT_STRING_ATTRIBUTE(game, sourcefile, "sourcefile", FLAG_GAME_SOURCEFILE)
		OUTPUT_STRING_ATTRIBUTE(game, cloneof, "cloneof", FLAG_GAME_CLONEOF)
		OUTPUT_STRING_ATTRIBUTE(game, romof, "romof", FLAG_GAME_ROMOF)
		OUTPUT_STRING_ATTRIBUTE(game, sampleof, "sampleof", FLAG_GAME_SAMPLEOF)
		OUTPUT_STRING_ATTRIBUTE(game, rebuildto, "rebuildto", FLAG_GAME_REBUILDTO)
		OUTPUT_STRING_ATTRIBUTE(game, board, "board", FLAG_GAME_BOARD)

		fprintf(dat->out, ">\n");

		for (j=0, curr_comment=curr_game->comments; j<curr_game->num_comments; j++, curr_comment++)
			OUTPUT_STRING_ELEMENT(comment, text, "\t\t", "comment", FLAG_COMMENT_TEXT)

		OUTPUT_STRING_ELEMENT(game, description, "\t\t", "description", FLAG_GAME_DESCRIPTION)
		OUTPUT_STRING_ELEMENT(game, year, "\t\t", "year", FLAG_GAME_YEAR)
		OUTPUT_STRING_ELEMENT(game, manufacturer, "\t\t", "manufacturer", FLAG_GAME_MANUFACTURER)
		OUTPUT_STRING_ELEMENT(game, history, "\t\t", "history", FLAG_GAME_HISTORY)

		/* --- Release information --- */

		for (j=0, curr_release=curr_game->releases; j<curr_game->num_releases; j++, curr_release++)
		{
			fprintf(dat->out, "\t\t<release");

			OUTPUT_STRING_ATTRIBUTE(release, name, "name", FLAG_RELEASE_NAME)
			OUTPUT_STRING_ATTRIBUTE(release, region, "region", FLAG_RELEASE_REGION)
			OUTPUT_STRING_ATTRIBUTE(release, language, "language", FLAG_RELEASE_LANGUAGE)
			OUTPUT_STRING_ATTRIBUTE(release, date, "date", FLAG_RELEASE_DATE)
			OUTPUT_STRING_ATTRIBUTE(release, _default, "default", FLAG_RELEASE_DEFAULT)

			fprintf(dat->out, "/>\n");
		}

		/* --- BIOS Set information --- */

		for (j=0, curr_biosset=curr_game->biossets; j<curr_game->num_biossets; j++, curr_biosset++)
		{
			fprintf(dat->out, "\t\t<biosset");

			OUTPUT_STRING_ATTRIBUTE(biosset, name, "name", FLAG_BIOSSET_NAME)
			OUTPUT_STRING_ATTRIBUTE(biosset, description, "description", FLAG_BIOSSET_DESCRIPTION)
			OUTPUT_STRING_ATTRIBUTE(biosset, _default, "default", FLAG_BIOSSET_DEFAULT)

			fprintf(dat->out, "/>\n");
		}

		/* --- ROM information --- */

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			fprintf(dat->out, "\t\t<rom");

			OUTPUT_STRING_ATTRIBUTE(rom, name, "name", FLAG_ROM_NAME)
			OUTPUT_STRING_ATTRIBUTE(rom, merge, "merge", FLAG_ROM_MERGE)
			OUTPUT_STRING_ATTRIBUTE(rom, bios, "bios", FLAG_ROM_BIOS)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(rom, size, "size", FLAG_ROM_SIZE)
			OUTPUT_PADDED_HEX_ATTRIBUTE(rom, crc, "crc", FLAG_ROM_CRC)
			OUTPUT_STRING_ATTRIBUTE(rom, sha1, "sha1", FLAG_ROM_SHA1)
			OUTPUT_STRING_ATTRIBUTE(rom, md5, "md5", FLAG_ROM_MD5)
			OUTPUT_STRING_ATTRIBUTE(rom, region, "region", FLAG_ROM_REGION)
			OUTPUT_STRING_ATTRIBUTE(rom, status, "status", FLAG_ROM_STATUS)
			OUTPUT_STRING_ATTRIBUTE(rom, dispose, "dispose", FLAG_ROM_DISPOSE)
			OUTPUT_STRING_ATTRIBUTE(rom, soundonly, "soundonly", FLAG_ROM_SOUNDONLY)
			OUTPUT_UNPADDED_HEX_ATTRIBUTE(rom, offset, "offset", FLAG_ROM_OFFSET)

			fprintf(dat->out, "/>\n");
		}

		/* --- Disk information --- */

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			fprintf(dat->out, "\t\t<disk");

			OUTPUT_STRING_ATTRIBUTE(disk, name, "name", FLAG_DISK_NAME)
			OUTPUT_STRING_ATTRIBUTE(disk, merge, "merge", FLAG_DISK_MERGE)
			OUTPUT_STRING_ATTRIBUTE(disk, sha1, "sha1", FLAG_DISK_SHA1)
			OUTPUT_STRING_ATTRIBUTE(disk, md5, "md5", FLAG_DISK_MD5)
			OUTPUT_STRING_ATTRIBUTE(disk, region, "region", FLAG_DISK_REGION)
			OUTPUT_STRING_ATTRIBUTE(disk, status, "status", FLAG_DISK_STATUS)
			OUTPUT_UNPADDED_HEX_ATTRIBUTE(disk, index, "index", FLAG_DISK_INDEX)

			fprintf(dat->out, "/>\n");
		}

		/* --- Sample information --- */

		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
		{
			fprintf(dat->out, "\t\t<sample");

			OUTPUT_STRING_ATTRIBUTE(sample, name, "name", FLAG_SAMPLE_NAME)

			fprintf(dat->out, "/>\n");
		}

		/* --- Chip information --- */

		for (j=0, curr_chip=curr_game->chips; j<curr_game->num_chips; j++, curr_chip++)
		{
			fprintf(dat->out, "\t\t<chip");

			OUTPUT_STRING_ATTRIBUTE(chip, type, "type", FLAG_CHIP_TYPE)
			OUTPUT_STRING_ATTRIBUTE(chip, soundonly, "soundonly", FLAG_CHIP_SOUNDONLY)
			OUTPUT_STRING_ATTRIBUTE(chip, name, "name", FLAG_CHIP_NAME)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(chip, clock, "clock", FLAG_CHIP_CLOCK)

			fprintf(dat->out, "/>\n");
		}

		/* --- Video information --- */

		for (j=0, curr_video=curr_game->videos; j<curr_game->num_videos; j++, curr_video++)
		{
			fprintf(dat->out, "\t\t<video");

			OUTPUT_STRING_ATTRIBUTE(video, screen, "screen", FLAG_VIDEO_SCREEN)
			OUTPUT_STRING_ATTRIBUTE(video, orientation, "orientation", FLAG_VIDEO_ORIENTATION)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(video, width, "width", FLAG_VIDEO_WIDTH)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(video, height, "height", FLAG_VIDEO_HEIGHT)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(video, aspectx, "aspectx", FLAG_VIDEO_ASPECTX)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(video, aspecty, "aspecty", FLAG_VIDEO_ASPECTY)
			OUTPUT_0_6_FLOAT_ATTRIBUTE(video, refresh, "refresh", FLAG_VIDEO_REFRESH)

			fprintf(dat->out, "/>\n");
		}

		/* --- Display information --- */

		for (j=0, curr_display=curr_game->displays; j<curr_game->num_displays; j++, curr_display++)
		{
			fprintf(dat->out, "\t\t<display");

			OUTPUT_STRING_ATTRIBUTE(display, type, "type", FLAG_DISPLAY_TYPE)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(display, rotate, "rotate", FLAG_DISPLAY_ROTATE)
			OUTPUT_STRING_ATTRIBUTE(display, flipx, "flipx", FLAG_DISPLAY_FLIPX)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(display, width, "width", FLAG_DISPLAY_WIDTH)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(display, height, "height", FLAG_DISPLAY_HEIGHT)
			OUTPUT_0_6_FLOAT_ATTRIBUTE(display, refresh, "refresh", FLAG_DISPLAY_REFRESH)

			fprintf(dat->out, "/>\n");
		}

		/* --- Sound information --- */

		for (j=0, curr_sound=curr_game->sounds; j<curr_game->num_sounds; j++, curr_sound++)
		{
			fprintf(dat->out, "\t\t<sound");

			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(sound, channels, "channels", FLAG_SOUND_CHANNELS)

			fprintf(dat->out, "/>\n");
		}

		/* --- Input information --- */

		for (j=0, curr_input=curr_game->inputs; j<curr_game->num_inputs; j++, curr_input++)
		{
			fprintf(dat->out, "\t\t<input");

			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(input, players, "players", FLAG_INPUT_PLAYERS)
			OUTPUT_STRING_ATTRIBUTE(input, control, "control", FLAG_INPUT_CONTROL)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(input, buttons, "buttons", FLAG_INPUT_BUTTONS)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(input, coins, "coins", FLAG_INPUT_COINS)
			OUTPUT_STRING_ATTRIBUTE(input, service, "service", FLAG_INPUT_SERVICE)
			OUTPUT_STRING_ATTRIBUTE(input, tilt, "tilt", FLAG_INPUT_TILT)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(input, dipswitches, "dipswitches", FLAG_INPUT_DIPSWITCHES)

			fprintf(dat->out, ">\n");

			for (k=0, curr_control=curr_input->controls; k<curr_input->num_controls; k++, curr_control++)
			{
				fprintf(dat->out, "\t\t\t<control");

				OUTPUT_STRING_ATTRIBUTE(control, type, "type", FLAG_CONTROL_TYPE)
				OUTPUT_SIGNED_LONG_ATTRIBUTE(control, minimum, "minimum", FLAG_CONTROL_MINIMUM)
				OUTPUT_SIGNED_LONG_ATTRIBUTE(control, maximum, "maximum", FLAG_CONTROL_MAXIMUM)
				OUTPUT_UNSIGNED_LONG_ATTRIBUTE(control, sensitivity, "sensitivity", FLAG_CONTROL_SENSITIVITY)
				OUTPUT_UNSIGNED_LONG_ATTRIBUTE(control, keydelta, "keydelta", FLAG_CONTROL_KEYDELTA)
				OUTPUT_STRING_ATTRIBUTE(control, reverse, "reverse", FLAG_CONTROL_REVERSE)

				fprintf(dat->out, "/>\n");
			}

			fprintf(dat->out, "\t\t</input>\n");
		}

		/* --- Dipswitch information --- */

		for (j=0, curr_dipswitch=curr_game->dipswitches; j<curr_game->num_dipswitches; j++, curr_dipswitch++)
		{
			fprintf(dat->out, "\t\t<dipswitch");
			OUTPUT_STRING_ATTRIBUTE(dipswitch, name, "name", FLAG_DIPSWITCH_NAME)
			fprintf(dat->out, ">\n");

			for (k=0, curr_dipvalue=curr_dipswitch->dipvalues; k<curr_dipswitch->num_dipvalues; k++, curr_dipvalue++)
			{
				fprintf(dat->out, "\t\t\t<dipvalue");

				OUTPUT_STRING_ATTRIBUTE(dipvalue, name, "name", FLAG_DIPVALUE_NAME)
				OUTPUT_STRING_ATTRIBUTE(dipvalue, _default, "default", FLAG_DIPVALUE_DEFAULT)

				fprintf(dat->out, "/>\n");
			}

			fprintf(dat->out, "\t\t</dipswitch>\n");
		}

		/* --- Driver information --- */

		for (j=0, curr_driver=curr_game->drivers; j<curr_game->num_drivers; j++, curr_driver++)
		{
			fprintf(dat->out, "\t\t<driver");

			OUTPUT_STRING_ATTRIBUTE(driver, status, "status", FLAG_DRIVER_STATUS)
			OUTPUT_STRING_ATTRIBUTE(driver, emulation, "emulation", FLAG_DRIVER_EMULATION)
			OUTPUT_STRING_ATTRIBUTE(driver, color, "color", FLAG_DRIVER_COLOR)
			OUTPUT_STRING_ATTRIBUTE(driver, sound, "sound", FLAG_DRIVER_SOUND)
			OUTPUT_STRING_ATTRIBUTE(driver, graphic, "graphic", FLAG_DRIVER_GRAPHIC)
			OUTPUT_STRING_ATTRIBUTE(driver, cocktail, "cocktail", FLAG_DRIVER_COCKTAIL)
			OUTPUT_STRING_ATTRIBUTE(driver, protection, "protection", FLAG_DRIVER_PROTECTION)
			OUTPUT_STRING_ATTRIBUTE(driver, savestate, "savestate", FLAG_DRIVER_SAVESTATE)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(driver, palettesize, "palettesize", FLAG_DRIVER_PALETTESIZE)
			OUTPUT_UNSIGNED_LONG_ATTRIBUTE(driver, colordeep, "colordeep", FLAG_DRIVER_COLORDEEP)
			OUTPUT_STRING_ATTRIBUTE(driver, credits, "credits", FLAG_DRIVER_CREDITS)

			fprintf(dat->out, "/>\n");
		}

		/* --- Device information --- */

		for (j=0, curr_device=curr_game->devices; j<curr_game->num_devices; j++, curr_device++)
		{
			fprintf(dat->out, "\t\t<device");
			if (curr_device->type)
			{
				OUTPUT_STRING_ATTRIBUTE(device, type, "type", FLAG_DEVICE_TYPE)
			}
			else
			{
				OUTPUT_STRING_ATTRIBUTE(device, name, "name", FLAG_DEVICE_NAME)
			}
			OUTPUT_STRING_ATTRIBUTE(device, tag, "tag", FLAG_DEVICE_TAG)
			OUTPUT_STRING_ATTRIBUTE(device, mandatory, "mandatory", FLAG_DEVICE_MANDATORY)
			fprintf(dat->out, ">\n");

			for (k=0, curr_extension=curr_device->extensions; k<curr_device->num_extensions; k++, curr_extension++)
			{
				fprintf(dat->out, "\t\t\t<extension");

				OUTPUT_STRING_ATTRIBUTE(extension, name, "name", FLAG_EXTENSION_NAME)

				fprintf(dat->out, "/>\n");
			}

			fprintf(dat->out, "\t\t</device>\n");
		}

		/* --- Archive information --- */

		for (j=0, curr_archive=curr_game->archives; j<curr_game->num_archives; j++, curr_archive++)
		{
			fprintf(dat->out, "\t\t<archive");
			OUTPUT_STRING_ATTRIBUTE(archive, name, "name", FLAG_ARCHIVE_NAME)
			fprintf(dat->out, "/>\n");
		}

		/* --- RAM option information --- */

		for (j=0, curr_ramoption=curr_game->ramoptions; j<curr_game->num_ramoptions; j++, curr_ramoption++)
		{
			fprintf(dat->out, "\t\t<ramoption");
			OUTPUT_STRING_ATTRIBUTE(ramoption, _default, "default", FLAG_RAMOPTION_DEFAULT)
			fprintf(dat->out, ">");

			if (curr_ramoption->size)
			{
				fprintf(dat->out, "%d", curr_ramoption->size);
				dat->ramoption_saved|=FLAG_RAMOPTION_SIZE;
			}

			fprintf(dat->out, "</ramoption>\n");
		}

		fprintf(dat->out, "\t</%s>\n", game_type);
	}

	fprintf(dat->out, "</%s>\n", doc_type);

	return(errflg);
}

int save_mess_listxml(struct dat *dat)
{
	return(0);
}

int save_generic_xml(struct dat *dat)
{
	dat->emulator.name="datafile";
	return(save_mame_listxml(dat));
}
