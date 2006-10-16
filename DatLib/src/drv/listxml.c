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
	int game_type=0, errflg=0;

	BUFFER1_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		if (strstr(BUFFER1_PTR, "<mame "))
		{
			strcpy(TOKEN, "mame");
			BUFFER2_PUT_TOKEN(TOKEN_EMULATOR_NAME)
			GET_XML_ATTRIBUTE("build", TOKEN_EMULATOR_BUILD) 
		}
		if (strstr(BUFFER1_PTR, "<Raine32 "))
		{
			strcpy(TOKEN, "Raine32");
			BUFFER2_PUT_TOKEN(TOKEN_EMULATOR_NAME)
			GET_XML_ATTRIBUTE("build", TOKEN_EMULATOR_BUILD) 
		}
		else if (strstr(BUFFER1_PTR, "<mess "))
		{
			strcpy(TOKEN, "mess");
			BUFFER2_PUT_TOKEN(TOKEN_EMULATOR_NAME)
			GET_XML_ATTRIBUTE("build", TOKEN_EMULATOR_BUILD) 
		}
		else if (strstr(BUFFER1_PTR, "<game ") || strstr(BUFFER1_PTR, "<machine "))
		{
			if (strstr(BUFFER1_PTR, "runnable=\"no\""))
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
			GET_XML_ATTRIBUTE("name", TOKEN_DEVICE_NAME)
		}
		else if (strstr(BUFFER1_PTR, "<extension "))
		{
			GET_XML_ATTRIBUTE("name", TOKEN_EXTENSION_NAME)
		}
		else if (strstr(BUFFER1_PTR, "<archive "))
		{
			GET_XML_ATTRIBUTE("name", TOKEN_ARCHIVE_NAME)
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}

int load_mess_listxml(struct dat *dat)
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

	uint32_t i, j, k;
	int errflg=0;

	/* --- Write the DTD --- */

	if (dat->num_machines>0)
	{
		doc_type="mess";
		game_type="machine";
	}
	else
	{
		doc_type=dat->emulator.name ? dat->emulator.name : "mame";
		game_type="game";
	}

	fprintf(dat->out, "<?xml version=\"1.0\"?>\n");

	fprintf(dat->out, "<!DOCTYPE %s [\n", doc_type);
	fprintf(dat->out, "<!ELEMENT %s (%s+)>\n", doc_type, game_type);
	if (dat->emulator.build)
		fprintf(dat->out, "\t<!ATTLIST %s build CDATA #IMPLIED>\n", doc_type);

	fprintf(dat->out, "\t<!ELEMENT %s (", game_type);
	if (dat->comment_flags & FLAG_COMMENT_TEXT)
		fprintf(dat->out, "comment*, ");
	fprintf(dat->out, "description, year?, manufacturer, ");
	if (dat->game_flags & FLAG_GAME_HISTORY)
		fprintf(dat->out, "history?, ");
	fprintf(dat->out, "biosset*, rom*, disk*, sample*, chip*, video?, display*, sound?, input?, dipswitch*, driver?");
	if (dat->num_machines>0)
		fprintf(dat->out, ", device*");
	fprintf(dat->out, ")>\n");
	fprintf(dat->out, "\t\t<!ATTLIST %s name CDATA #REQUIRED>\n", game_type);
	fprintf(dat->out, "\t\t<!ATTLIST %s sourcefile CDATA #IMPLIED>\n", game_type);
	fprintf(dat->out, "\t\t<!ATTLIST %s runnable (yes|no) \"yes\">\n", game_type);
	fprintf(dat->out, "\t\t<!ATTLIST %s cloneof CDATA #IMPLIED>\n", game_type);
	fprintf(dat->out, "\t\t<!ATTLIST %s romof CDATA #IMPLIED>\n", game_type);
	fprintf(dat->out, "\t\t<!ATTLIST %s sampleof CDATA #IMPLIED>\n", game_type);
	if (dat->game_flags & FLAG_GAME_REBUILDTO)
		fprintf(dat->out, "\t\t<!ATTLIST %s rebuildto (#PCDATA)>\n", game_type);
	if (dat->game_flags & FLAG_GAME_BOARD)
		fprintf(dat->out, "\t\t<!ATTLIST %s board (#PCDATA)>\n", game_type);

	if (dat->comment_flags & FLAG_COMMENT_TEXT)
		fprintf(dat->out, "\t\t<!ELEMENT comment (#PCDATA)>\n");
	fprintf(dat->out, "\t\t<!ELEMENT description (#PCDATA)>\n");
	fprintf(dat->out, "\t\t<!ELEMENT year (#PCDATA)>\n");
	fprintf(dat->out, "\t\t<!ELEMENT manufacturer (#PCDATA)>\n");
	if (dat->game_flags & FLAG_GAME_HISTORY)
		fprintf(dat->out, "\t\t<!ELEMENT history (#PCDATA)>\n");

	fprintf(dat->out, "\t\t<!ELEMENT biosset EMPTY>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST biosset name CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST biosset description CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST biosset default (yes|no) \"no\">\n");

	fprintf(dat->out, "\t\t<!ELEMENT rom EMPTY>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom name CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom bios CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom size CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom crc CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom md5 CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom sha1 CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom merge CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom region CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom offset CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom status (baddump|nodump|good) \"good\">\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST rom dispose (yes|no) \"no\">\n");
	if (dat->rom_flags & FLAG_ROM_SOUNDONLY)
		fprintf(dat->out, "\t\t\t<!ATTLIST rom soundonly (yes|no) \"no\">\n");

	fprintf(dat->out, "\t\t<!ELEMENT disk EMPTY>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST disk name CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST disk md5 CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST disk sha1 CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST disk merge CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST disk region CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST disk index CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST disk status (baddump|nodump|good) \"good\">\n");

	fprintf(dat->out, "\t\t<!ELEMENT sample EMPTY>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST sample name CDATA #REQUIRED>\n");

	fprintf(dat->out, "\t\t<!ELEMENT chip EMPTY>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST chip name CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST chip type (cpu|audio) #REQUIRED>\n");
	if (dat->chip_flags & FLAG_CHIP_SOUNDONLY)
		fprintf(dat->out, "\t\t\t<!ATTLIST chip soundonly (yes|no) \"no\">\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST chip clock CDATA #IMPLIED>\n");

	fprintf(dat->out, "\t\t<!ELEMENT video EMPTY>\n");

	fprintf(dat->out, "\t\t\t<!ATTLIST video screen (raster|vector) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST video orientation (vertical|horizontal) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST video width CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST video height CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST video aspectx CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST video aspecty CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST video refresh CDATA #REQUIRED>\n");

	fprintf(dat->out, "\t\t<!ELEMENT display EMPTY>\n");

	fprintf(dat->out, "\t\t\t<!ATTLIST display type (raster|vector) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST display rotate (0|90|180|270) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST display flipx (yes|no) \"no\">\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST display width CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST display height CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST display refresh CDATA #REQUIRED>\n");

	fprintf(dat->out, "\t\t<!ELEMENT sound EMPTY>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST sound channels CDATA #REQUIRED>\n");

	fprintf(dat->out, "\t\t<!ELEMENT input (control*)>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST input service (yes|no) \"no\">\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST input tilt (yes|no) \"no\">\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST input players CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST input control CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST input buttons CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST input coins CDATA #IMPLIED>\n");
	if (dat->input_flags & FLAG_INPUT_DIPSWITCHES)
		fprintf(dat->out, "\t\t\t<!ATTLIST input dipswitches CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ELEMENT control EMPTY>\n");
	fprintf(dat->out, "\t\t\t\t<!ATTLIST control type CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t\t<!ATTLIST control minimum CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t\t<!ATTLIST control maximum CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t\t<!ATTLIST control sensitivity CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t\t<!ATTLIST control keydelta CDATA #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t\t<!ATTLIST control reverse (yes|no) \"no\">\n");

	fprintf(dat->out, "\t\t<!ELEMENT dipswitch (dipvalue*)>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST dipswitch name CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ELEMENT dipvalue EMPTY>\n");
	fprintf(dat->out, "\t\t\t\t<!ATTLIST dipvalue name CDATA #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t\t<!ATTLIST dipvalue default (yes|no) \"no\">\n");

	fprintf(dat->out, "\t\t<!ELEMENT driver EMPTY>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver status (good|imperfect|preliminary) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver emulation (good|imperfect|preliminary) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver color (good|imperfect|preliminary) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver sound (good|imperfect|preliminary) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver graphic (good|imperfect|preliminary) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver cocktail (good|imperfect|preliminary) #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver protection (good|imperfect|preliminary) #IMPLIED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver savestate (supported|unsupported) #REQUIRED>\n");
	fprintf(dat->out, "\t\t\t<!ATTLIST driver palettesize CDATA #REQUIRED>\n");
	if (dat->driver_flags & FLAG_DRIVER_COLORDEEP)
		fprintf(dat->out, "\t\t\t<!ATTLIST driver colordeep CDATA #REQUIRED>\n");
	if (dat->driver_flags & FLAG_DRIVER_CREDITS)
		fprintf(dat->out, "\t\t\t<!ATTLIST driver credits CDATA #IMPLIED>\n");

	if (dat->num_machines>0)
	{
		fprintf(dat->out, "\t\t<!ELEMENT device (extension*)>\n");
		fprintf(dat->out, "\t\t\t<!ATTLIST device name CDATA #REQUIRED>\n");
		fprintf(dat->out, "\t\t\t<!ELEMENT extension EMPTY>\n");
		fprintf(dat->out, "\t\t\t\t<!ATTLIST extension name CDATA #REQUIRED>\n");
	}

	if (dat->num_archives>0)
	{
		fprintf(dat->out, "\t\t<!ELEMENT archive EMPTY>\n");
		fprintf(dat->out, "\t\t\t<!ATTLIST archive name CDATA #REQUIRED>\n");
	}

	fprintf(dat->out, "]>\n\n");

	/* --- For every game, machine and resource --- */

	if (dat->emulator.build)
		fprintf(dat->out, "<%s build=\"%s\">\n", doc_type, dat->emulator.build);
	else
		fprintf(dat->out, "<%s>\n", doc_type);

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		/* --- Game/machine information --- */

		fprintf(dat->out, "\t<%s", game_type);

		if (curr_game->game_flags & FLAG_RESOURCE_NAME)
			fprintf(dat->out, " runnable=\"no\"");
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
				OUTPUT_UNSIGNED_LONG_ATTRIBUTE(control, minimum, "minimum", FLAG_CONTROL_MINIMUM)
				OUTPUT_UNSIGNED_LONG_ATTRIBUTE(control, maximum, "maximum", FLAG_CONTROL_MAXIMUM)
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
			OUTPUT_STRING_ATTRIBUTE(device, name, "name", FLAG_DEVICE_NAME)
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

		fprintf(dat->out, "\t</%s>\n", game_type);
	}

	fprintf(dat->out, "</%s>\n", doc_type);

	return(errflg);
}

int save_mess_listxml(struct dat *dat)
{
	return(0);
}
