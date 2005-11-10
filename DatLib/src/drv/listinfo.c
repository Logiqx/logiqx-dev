/* --------------------------------------------------------------------------
 * MAME ListInfo - Load and Save
 * MESS ListInfo - Load only
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

int identify_mame_listinfo(struct dat *dat)
{
	uint32_t i;
	int match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "game") || !strcmp(TOKEN, "resource"))
		{
			if (BUFFER1_REMAINING)
				BUFFER1_GET_TOKEN

			if (!strcmp(TOKEN, "("))
				match++;
		}

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}

int identify_mess_listinfo(struct dat *dat)
{
	uint32_t i;
	int match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN

		if (!strcmp(TOKEN, "machine"))
		{
			if (BUFFER1_REMAINING)
				BUFFER1_GET_TOKEN

			if (!strcmp(TOKEN, "("))
				match++;
		}

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

#define BUFFER2_PUT_INFO_ATTRIBUTE(ATTRIBUTE, FLAG) \
if (!strcmp(TOKEN, ATTRIBUTE)) \
{ \
	BUFFER1_GET_TOKEN \
	BUFFER2_PUT_TOKEN(FLAG) \
}

int load_mame_listinfo(struct dat *dat)
{
	int game_type=0, errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		BUFFER1_GET_TOKEN

		/* --- Need to know whether we are processing a game/resource/machine etc --- */

		if (!strcmp(TOKEN, "game"))
			game_type=FLAG_GAME_NAME;

		else if (!strcmp(TOKEN, "resource"))
			game_type=FLAG_RESOURCE_NAME;

		else if (!strcmp(TOKEN, "machine"))
			game_type=FLAG_MACHINE_NAME;

		else if (!strcmp(TOKEN, "clrmamepro"))
			game_type=FLAG_CLRMAMEPRO_HEADER;

		/* --- Comments --- */

		if (!strcmp(TOKEN, "//"))
		{
			strcpy(TOKEN, BUFFER1_PTR);
			BUFFER2_PUT_TOKEN(TOKEN_COMMENT_TEXT)
			TOKEN[0]='\0';
		}

		/* --- ClrMamePro header --- */

		if (game_type==FLAG_CLRMAMEPRO_HEADER)
		{
			BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_CLRMAMEPRO_NAME)
			else BUFFER2_PUT_INFO_ATTRIBUTE("description", TOKEN_CLRMAMEPRO_DESCRIPTION)
			else BUFFER2_PUT_INFO_ATTRIBUTE("category", TOKEN_CLRMAMEPRO_CATEGORY)
			else BUFFER2_PUT_INFO_ATTRIBUTE("version", TOKEN_CLRMAMEPRO_VERSION)
			else BUFFER2_PUT_INFO_ATTRIBUTE("author", TOKEN_CLRMAMEPRO_AUTHOR)
			else BUFFER2_PUT_INFO_ATTRIBUTE("forcemerging", TOKEN_CLRMAMEPRO_FORCEMERGING)
			else BUFFER2_PUT_INFO_ATTRIBUTE("forcezipping", TOKEN_CLRMAMEPRO_FORCEZIPPING)
		}

		/* --- Games --- */

		else if (game_type==FLAG_GAME_NAME)
		{
			BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_GAME_NAME)
			else BUFFER2_PUT_INFO_ATTRIBUTE("sourcefile", TOKEN_GAME_SOURCEFILE)
			else BUFFER2_PUT_INFO_ATTRIBUTE("cloneof", TOKEN_GAME_CLONEOF)
			else BUFFER2_PUT_INFO_ATTRIBUTE("romof", TOKEN_GAME_ROMOF)
			else BUFFER2_PUT_INFO_ATTRIBUTE("sampleof", TOKEN_GAME_SAMPLEOF)
			else BUFFER2_PUT_INFO_ATTRIBUTE("description", TOKEN_GAME_DESCRIPTION)
			else BUFFER2_PUT_INFO_ATTRIBUTE("year", TOKEN_GAME_YEAR)
			else BUFFER2_PUT_INFO_ATTRIBUTE("manufacturer", TOKEN_GAME_MANUFACTURER)
			else BUFFER2_PUT_INFO_ATTRIBUTE("history", TOKEN_GAME_HISTORY)
			else BUFFER2_PUT_INFO_ATTRIBUTE("rebuildto", TOKEN_GAME_REBUILDTO)
			else BUFFER2_PUT_INFO_ATTRIBUTE("board", TOKEN_GAME_BOARD)
		}

		/* --- Resources --- */

		else if (game_type==FLAG_RESOURCE_NAME)
		{
			BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_RESOURCE_NAME)
			else BUFFER2_PUT_INFO_ATTRIBUTE("sourcefile", TOKEN_RESOURCE_SOURCEFILE)
			else BUFFER2_PUT_INFO_ATTRIBUTE("description", TOKEN_RESOURCE_DESCRIPTION)
			else BUFFER2_PUT_INFO_ATTRIBUTE("year", TOKEN_RESOURCE_YEAR)
			else BUFFER2_PUT_INFO_ATTRIBUTE("manufacturer", TOKEN_RESOURCE_MANUFACTURER)
			else BUFFER2_PUT_INFO_ATTRIBUTE("history", TOKEN_RESOURCE_HISTORY)
			else BUFFER2_PUT_INFO_ATTRIBUTE("rebuildto", TOKEN_RESOURCE_REBUILDTO)
			else BUFFER2_PUT_INFO_ATTRIBUTE("board", TOKEN_RESOURCE_BOARD)
		}

		/* --- Machines --- */

		else if (game_type==FLAG_MACHINE_NAME)
		{
			BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_MACHINE_NAME)
			else BUFFER2_PUT_INFO_ATTRIBUTE("sourcefile", TOKEN_MACHINE_SOURCEFILE)
			else BUFFER2_PUT_INFO_ATTRIBUTE("cloneof", TOKEN_MACHINE_CLONEOF)
			else BUFFER2_PUT_INFO_ATTRIBUTE("romof", TOKEN_MACHINE_ROMOF)
			else BUFFER2_PUT_INFO_ATTRIBUTE("sampleof", TOKEN_MACHINE_SAMPLEOF)
			else BUFFER2_PUT_INFO_ATTRIBUTE("description", TOKEN_MACHINE_DESCRIPTION)
			else BUFFER2_PUT_INFO_ATTRIBUTE("year", TOKEN_MACHINE_YEAR)
			else BUFFER2_PUT_INFO_ATTRIBUTE("manufacturer", TOKEN_MACHINE_MANUFACTURER)
			else BUFFER2_PUT_INFO_ATTRIBUTE("history", TOKEN_MACHINE_HISTORY)
			else BUFFER2_PUT_INFO_ATTRIBUTE("rebuildto", TOKEN_MACHINE_REBUILDTO)
			else BUFFER2_PUT_INFO_ATTRIBUTE("board", TOKEN_MACHINE_BOARD)
		}

		if (game_type==FLAG_GAME_NAME || game_type==FLAG_RESOURCE_NAME || game_type==FLAG_MACHINE_NAME)
		{
			/* --- Biossets --- */

			if (!strcmp(TOKEN, "biosset"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_BIOSSET_NAME)
					else BUFFER2_PUT_INFO_ATTRIBUTE("description", TOKEN_BIOSSET_DESCRIPTION)
					else BUFFER2_PUT_INFO_ATTRIBUTE("default", TOKEN_BIOSSET_DEFAULT)
				}
			}

			/* --- ROMs --- */

			else if (!strcmp(TOKEN, "rom"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_ROM_NAME)
					else BUFFER2_PUT_INFO_ATTRIBUTE("bios", TOKEN_ROM_BIOS)
					else BUFFER2_PUT_INFO_ATTRIBUTE("size", TOKEN_ROM_SIZE)
					else BUFFER2_PUT_INFO_ATTRIBUTE("crc", TOKEN_ROM_CRC)
					else BUFFER2_PUT_INFO_ATTRIBUTE("crc32", TOKEN_ROM_CRC)
					else BUFFER2_PUT_INFO_ATTRIBUTE("md5", TOKEN_ROM_MD5)
					else BUFFER2_PUT_INFO_ATTRIBUTE("sha1", TOKEN_ROM_SHA1)
					else BUFFER2_PUT_INFO_ATTRIBUTE("merge", TOKEN_ROM_MERGE)
					else BUFFER2_PUT_INFO_ATTRIBUTE("region", TOKEN_ROM_REGION)
					else BUFFER2_PUT_INFO_ATTRIBUTE("offs", TOKEN_ROM_OFFSET)

					/* --- Flags need interpreting! --- */

					else if (!strcmp(TOKEN, "flags"))
					{
						BUFFER1_GET_TOKEN

						if (!strcmp(TOKEN, "baddump") || !strcmp(TOKEN, "nodump"))
						{
							BUFFER2_PUT_TOKEN(TOKEN_ROM_STATUS)
						}
						else if (!strcmp(TOKEN, "dispose"))
						{
							strcpy(TOKEN, "yes");
							BUFFER2_PUT_TOKEN(TOKEN_ROM_DISPOSE)
						}
						else if (!strcmp(TOKEN, "soundonly"))
						{
							strcpy(TOKEN, "yes");
							BUFFER2_PUT_TOKEN(TOKEN_ROM_SOUNDONLY)
						}
					}

					/* --- Support the bad syntax of MAME v0.68 --- */

					else if (!strcmp(TOKEN, "baddump") || !strcmp(TOKEN, "nodump"))
						BUFFER2_PUT_TOKEN(TOKEN_ROM_STATUS)
				}
			}

			/* --- Disks --- */

			else if (!strcmp(TOKEN, "disk"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_DISK_NAME)
					else BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_DISK_NAME)
					else BUFFER2_PUT_INFO_ATTRIBUTE("md5", TOKEN_DISK_MD5)
					else BUFFER2_PUT_INFO_ATTRIBUTE("sha1", TOKEN_DISK_SHA1)
					else BUFFER2_PUT_INFO_ATTRIBUTE("merge", TOKEN_DISK_MERGE)
					else BUFFER2_PUT_INFO_ATTRIBUTE("region", TOKEN_DISK_REGION)
					else BUFFER2_PUT_INFO_ATTRIBUTE("index", TOKEN_DISK_INDEX)

					/* --- Flags need interpreting! --- */

					else if (!strcmp(TOKEN, "flags"))
					{
						BUFFER1_GET_TOKEN

						if (!strcmp(TOKEN, "baddump") || !strcmp(TOKEN, "nodump"))
							BUFFER2_PUT_TOKEN(TOKEN_DISK_STATUS)
					}

					/* --- Support the bad syntax of MAME v0.68 --- */

					else if (!strcmp(TOKEN, "baddump") || !strcmp(TOKEN, "nodump"))
						BUFFER2_PUT_TOKEN(TOKEN_DISK_STATUS)
				}
			}

			/* --- Samples --- */

			else BUFFER2_PUT_INFO_ATTRIBUTE("sample", TOKEN_SAMPLE_NAME)

			/* --- Chips --- */

			else if (!strcmp(TOKEN, "chip"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("type", TOKEN_CHIP_TYPE)
					else BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_CHIP_NAME)
					else BUFFER2_PUT_INFO_ATTRIBUTE("clock", TOKEN_CHIP_CLOCK)

					/* --- Flags need interpreting! --- */

					else if (!strcmp(TOKEN, "flags"))
					{
						BUFFER1_GET_TOKEN

						if (!strcmp(TOKEN, "audio"))
						{
							strcpy(TOKEN, "yes");
							BUFFER2_PUT_TOKEN(TOKEN_CHIP_SOUNDONLY)
						}
					}
				}
			}

			/* --- Videos --- */

			else if (!strcmp(TOKEN, "video"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("screen", TOKEN_VIDEO_SCREEN)
					else BUFFER2_PUT_INFO_ATTRIBUTE("orientation", TOKEN_VIDEO_ORIENTATION)
					else BUFFER2_PUT_INFO_ATTRIBUTE("x", TOKEN_VIDEO_WIDTH)
					else BUFFER2_PUT_INFO_ATTRIBUTE("y", TOKEN_VIDEO_HEIGHT)
					else BUFFER2_PUT_INFO_ATTRIBUTE("aspectx", TOKEN_VIDEO_ASPECTX)
					else BUFFER2_PUT_INFO_ATTRIBUTE("aspecty", TOKEN_VIDEO_ASPECTY)
					else BUFFER2_PUT_INFO_ATTRIBUTE("freq", TOKEN_VIDEO_REFRESH)
				}
			}

			/* --- Sounds --- */

			else if (!strcmp(TOKEN, "sound"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("channels", TOKEN_SOUND_CHANNELS)
				}
			}

			/* --- Inputs --- */

			else if (!strcmp(TOKEN, "input"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("service", TOKEN_INPUT_SERVICE)
					else BUFFER2_PUT_INFO_ATTRIBUTE("tilt", TOKEN_INPUT_TILT)
					else BUFFER2_PUT_INFO_ATTRIBUTE("players", TOKEN_INPUT_PLAYERS)
					else BUFFER2_PUT_INFO_ATTRIBUTE("control", TOKEN_INPUT_CONTROL)
					else BUFFER2_PUT_INFO_ATTRIBUTE("buttons", TOKEN_INPUT_BUTTONS)
					else BUFFER2_PUT_INFO_ATTRIBUTE("coins", TOKEN_INPUT_COINS)
					else BUFFER2_PUT_INFO_ATTRIBUTE("dipswitches", TOKEN_INPUT_DIPSWITCHES)
				}
			}

			/* --- Dipswitches --- */

			else if (!strcmp(TOKEN, "dipswitch"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_DIPSWITCH_NAME)
					else BUFFER2_PUT_INFO_ATTRIBUTE("entry", TOKEN_DIPVALUE_NAME)

					/* --- Defaults need interpreting! --- */

					else if (!strcmp(TOKEN, "default"))
					{
						strcpy(TOKEN, "yes");
						BUFFER2_PUT_TOKEN(TOKEN_DIPVALUE_DEFAULT)
					}
				}
			}

			/* --- Drivers --- */

			else if (!strcmp(TOKEN, "driver"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("status", TOKEN_DRIVER_STATUS)
					else BUFFER2_PUT_INFO_ATTRIBUTE("emulation", TOKEN_DRIVER_EMULATION)
					else BUFFER2_PUT_INFO_ATTRIBUTE("color", TOKEN_DRIVER_COLOR)
					else BUFFER2_PUT_INFO_ATTRIBUTE("sound", TOKEN_DRIVER_SOUND)
					else BUFFER2_PUT_INFO_ATTRIBUTE("graphic", TOKEN_DRIVER_GRAPHIC)
					else BUFFER2_PUT_INFO_ATTRIBUTE("cocktail", TOKEN_DRIVER_COCKTAIL)
					else BUFFER2_PUT_INFO_ATTRIBUTE("protection", TOKEN_DRIVER_PROTECTION)
					else BUFFER2_PUT_INFO_ATTRIBUTE("palettesize", TOKEN_DRIVER_PALETTESIZE)
					else BUFFER2_PUT_INFO_ATTRIBUTE("colordeep", TOKEN_DRIVER_COLORDEEP)
					else BUFFER2_PUT_INFO_ATTRIBUTE("credits", TOKEN_DRIVER_CREDITS)
				}
			}

			/* --- Dipswitches --- */

			else if (!strcmp(TOKEN, "device"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_DEVICE_NAME)
					else BUFFER2_PUT_INFO_ATTRIBUTE("extension", TOKEN_EXTENSION_NAME)
				}
			}

			/* --- Archives --- */

			else if (!strcmp(TOKEN, "archive"))
			{
				while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
				{
					BUFFER1_GET_TOKEN

					BUFFER2_PUT_INFO_ATTRIBUTE("name", TOKEN_ARCHIVE_NAME)
				}
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


int load_mess_listinfo(struct dat *dat)
{
	return(load_mame_listinfo(dat));
}


/* --- Specify --- */

int specify_mame_listinfo(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "listinfo") &&
		strcmp(dat->options->save_format, "info") &&
		strcmp(dat->options->save_format, "li") &&
		strcmp(dat->options->save_format, "clrmamepro") &&
		strcmp(dat->options->save_format, "clrmame") &&
		strcmp(dat->options->save_format, "cmpro") &&
		strcmp(dat->options->save_format, "cmp") &&
		strcmp(dat->options->save_format, "cm"))
		return(0);
	else
		return(1);
}

int specify_mess_listinfo(struct dat *dat)
{
	return(0);
}


/* --- Save --- */

void output_info_string(FILE *out, unsigned char *ptr)
{
	fprintf(out, "\"");

	while (*ptr)
	{
		switch (*ptr)
		{
			case '\n' : fprintf(out, "\\n"); break;
			case '\t' : fprintf(out, "\\t"); break;
			case '\\' : fprintf(out, "\\\\"); break;
			case '\"' : fprintf(out, "\\\""); break;
			default: fprintf(out, "%c", *ptr);
		}
		ptr++;
	}

	fprintf(out, "\"");
}

#define OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
{ \
	if (*ATTRIBUTE_TEXT=='\t') \
		fprintf(dat->out, "\n"); \
	else \
		fprintf(dat->out, " "); \
	dat->OBJECT##_saved|=ATTRIBUTE_FLAG; \
}

#define OUTPUT_QUOTED_STRING(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
{ \
	if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
	{ \
		fprintf(dat->out, "%s ", ATTRIBUTE_TEXT); \
		output_info_string(dat->out, curr_##OBJECT->ATTRIBUTE); \
\
		OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
	} \
}

#define OUTPUT_UNQUOTED_STRING(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
{ \
	if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
	{ \
		fprintf(dat->out, "%s ", ATTRIBUTE_TEXT); \
		fprintf(dat->out, "%s", curr_##OBJECT->ATTRIBUTE); \
\
		OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
	} \
}

#define OUTPUT_SMART_STRING(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	if (dat->options->options & OPTION_ALWAYS_QUOTE || strchr(curr_##OBJECT->ATTRIBUTE, ' ')) \
		OUTPUT_QUOTED_STRING(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
	else \
		OUTPUT_UNQUOTED_STRING(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
}

#define OUTPUT_QUOTED_YES(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_VALUE, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	if (!strcmp(curr_##OBJECT->ATTRIBUTE, "yes")) \
	{ \
		fprintf(dat->out, "%s ", ATTRIBUTE_TEXT); \
		output_info_string(dat->out, ATTRIBUTE_VALUE); \
\
		OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
	} \
}

#define OUTPUT_UNQUOTED_YES(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_VALUE, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	if (!strcmp(curr_##OBJECT->ATTRIBUTE, "yes")) \
	{ \
		fprintf(dat->out, "%s ", ATTRIBUTE_TEXT); \
		fprintf(dat->out, "%s", ATTRIBUTE_VALUE); \
\
		OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
	} \
}

#define OUTPUT_UNSIGNED_LONG(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, "%s %lu", ATTRIBUTE_TEXT, (unsigned long)curr_##OBJECT->ATTRIBUTE); \
\
	OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
}

#define OUTPUT_PADDED_HEX(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, "%s %08lx", ATTRIBUTE_TEXT, (unsigned long)curr_##OBJECT->ATTRIBUTE); \
\
	OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
}

#define OUTPUT_NONPADDED_HEX(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, "%s %lx", ATTRIBUTE_TEXT, (unsigned long)curr_##OBJECT->ATTRIBUTE); \
\
	OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
}

#define OUTPUT_0_6_FLOAT(OBJECT, ATTRIBUTE, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & ATTRIBUTE_FLAG) \
{ \
	fprintf(dat->out, "%s %0.6f", ATTRIBUTE_TEXT, curr_##OBJECT->ATTRIBUTE); \
\
	OUTPUT_COMPLETED(OBJECT, ATTRIBUTE_TEXT, ATTRIBUTE_FLAG) \
}

#define LOGIQX_ORDERING 1
#define XML2INFO_ORDERING 2

int save_mame_listinfo(struct dat *dat)
{
	struct game *curr_game=0;
	struct comment *curr_comment=0;
	struct biosset *curr_biosset=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;
	struct chip *curr_chip=0;
	struct video *curr_video=0;
	struct sound *curr_sound=0;
	struct input *curr_input=0;
	struct dipswitch *curr_dipswitch=0;
	struct dipvalue *curr_dipvalue=0;
	struct driver *curr_driver=0;
	struct device *curr_device=0;
	struct extension *curr_extension=0;
	struct archive *curr_archive=0;

	uint32_t ordering=LOGIQX_ORDERING, i, j, k;
	int errflg=0;

	if (dat->options->options & OPTION_KEEP_FULL_DETAILS)
		ordering=XML2INFO_ORDERING;

	/* --- Copy RomCenter header to ClrMamePro header if details are missing --- */

	if (!dat->clrmamepro.name && dat->romcenter_emulator.refname)
		dat->clrmamepro.name=dat->romcenter_emulator.refname;

	if (!dat->clrmamepro.description && dat->romcenter_emulator.version)
		dat->clrmamepro.description=dat->romcenter_emulator.version;

	if (!dat->clrmamepro.category && dat->romcenter_credits.comment)
		dat->clrmamepro.category=dat->romcenter_credits.comment;

	if (!dat->clrmamepro.version && dat->romcenter_credits.version)
		dat->clrmamepro.version=dat->romcenter_credits.version;

	if (!dat->clrmamepro.author && dat->romcenter_credits.author)
		dat->clrmamepro.author=dat->romcenter_credits.author;

	if (dat->dat_flags & FLAG_DAT_FULL_MERGING)
		dat->clrmamepro.forcemerging="full";
	else if (dat->dat_flags & FLAG_DAT_SPLIT_MERGING)
		dat->clrmamepro.forcemerging="split";
	else if (dat->dat_flags & FLAG_DAT_NO_MERGING)
		dat->clrmamepro.forcemerging="none";

	if (dat->romcenter_dat.plugin && strcmp(dat->romcenter_dat.plugin, "arcade.dll"))
	{
		fprintf(stderr, "Warning: The RomCenter plugin for the data file was '%s'.\n", dat->romcenter_dat.plugin);
		fprintf(stderr, "         It is likely that the data file will not work correctly in ClrMamePro!\n\n");
	}

	/* --- Output ClrMamePro Header (no clever macros like everything else!) --- */

	if (dat->clrmamepro.name!=0)
	{
		fprintf(dat->out, "clrmamepro (\n");

		if (strchr(dat->clrmamepro.name, ' '))
			fprintf(dat->out, "\tname \"%s\"\n", dat->clrmamepro.name);
		else
			fprintf(dat->out, "\tname %s\n", dat->clrmamepro.name);

		if (dat->clrmamepro.description!=0)
			fprintf(dat->out, "\tdescription \"%s\"\n", dat->clrmamepro.description);

		if (dat->clrmamepro.category!=0)
			fprintf(dat->out, "\tcategory \"%s\"\n", dat->clrmamepro.category);

		if (dat->clrmamepro.version!=0)
		{
			if (strchr(dat->clrmamepro.version, ' '))
				fprintf(dat->out, "\tversion \"%s\"\n", dat->clrmamepro.version);
			else
				fprintf(dat->out, "\tversion %s\n", dat->clrmamepro.version);
		}

		if (dat->clrmamepro.author!=0)
		{
			if (strchr(dat->clrmamepro.author, ' '))
				fprintf(dat->out, "\tauthor \"%s\"\n", dat->clrmamepro.author);
			else
				fprintf(dat->out, "\tauthor %s\n", dat->clrmamepro.author);
		}

		if (dat->clrmamepro.forcemerging!=0)
		{
			if (strchr(dat->clrmamepro.forcemerging, ' '))
				fprintf(dat->out, "\tforcemerging \"%s\"\n", dat->clrmamepro.forcemerging);
			else
				fprintf(dat->out, "\tforcemerging %s\n", dat->clrmamepro.forcemerging);
		}

		if (dat->clrmamepro.forcezipping!=0)
		{
			if (strchr(dat->clrmamepro.forcezipping, ' '))
				fprintf(dat->out, "\tforcezipping \"%s\"\n", dat->clrmamepro.forcezipping);
			else
				fprintf(dat->out, "\tforcezipping %s\n", dat->clrmamepro.forcezipping);
		}

		fprintf(dat->out, ")\n\n");
	}

	/* --- For every game, machine and resource --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		/* --- Comments --- */

		if (curr_game->comment_flags & FLAG_COMMENT_TEXT)
		{
			for (j=0, curr_comment=curr_game->comments; j<curr_game->num_comments; j++, curr_comment++)
				fprintf(dat->out, "//%s\n", curr_comment->text);

			fprintf(dat->out, "\n");

			dat->comment_saved|=FLAG_COMMENT_TEXT;
		}

		/* --- Game information --- */

		if (curr_game->game_flags & FLAG_GAME_NAME)
			fprintf(dat->out, "game (\n");
		else if (curr_game->game_flags & FLAG_RESOURCE_NAME)
			fprintf(dat->out, "resource (\n");
		else if (curr_game->game_flags & FLAG_MACHINE_NAME)
			fprintf(dat->out, "machine (\n");

		OUTPUT_SMART_STRING(game, name, "\tname", (FLAG_GAME_NAME|FLAG_RESOURCE_NAME|FLAG_MACHINE_NAME))

		if (ordering==XML2INFO_ORDERING)
		{
			OUTPUT_SMART_STRING(game, sourcefile, "\tsourcefile", FLAG_GAME_SOURCEFILE)
			OUTPUT_SMART_STRING(game, cloneof, "\tcloneof", FLAG_GAME_CLONEOF)
			OUTPUT_SMART_STRING(game, romof, "\tromof", FLAG_GAME_ROMOF)
			OUTPUT_SMART_STRING(game, sampleof, "\tsampleof", FLAG_GAME_SAMPLEOF)
		}

		OUTPUT_QUOTED_STRING(game, description, "\tdescription", FLAG_GAME_DESCRIPTION)
		OUTPUT_SMART_STRING(game, year, "\tyear", FLAG_GAME_YEAR)
		OUTPUT_QUOTED_STRING(game, manufacturer, "\tmanufacturer", FLAG_GAME_MANUFACTURER)

		if (ordering==LOGIQX_ORDERING)
		{
			OUTPUT_SMART_STRING(game, sourcefile, "\tsourcefile", FLAG_GAME_SOURCEFILE)
			OUTPUT_SMART_STRING(game, cloneof, "\tcloneof", FLAG_GAME_CLONEOF)
			OUTPUT_SMART_STRING(game, romof, "\tromof", FLAG_GAME_ROMOF)
		}

		OUTPUT_QUOTED_STRING(game, history, "\thistory", FLAG_GAME_HISTORY)
		OUTPUT_SMART_STRING(game, rebuildto, "\trebuildto", FLAG_GAME_REBUILDTO)
		OUTPUT_QUOTED_STRING(game, board, "\tboard", FLAG_GAME_BOARD)

		/* --- BIOS Set information --- */

		for (j=0, curr_biosset=curr_game->biossets; j<curr_game->num_biossets; j++, curr_biosset++)
		{
			fprintf(dat->out, "\tbiosset ( ");

			OUTPUT_SMART_STRING(biosset, name, "name", FLAG_BIOSSET_NAME)
			OUTPUT_QUOTED_STRING(biosset, description, "description", FLAG_BIOSSET_DESCRIPTION)
			OUTPUT_UNQUOTED_STRING(biosset, _default, "default", FLAG_BIOSSET_DEFAULT)

			fprintf(dat->out, ")\n");
		}

		/* --- ROM information --- */

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			fprintf(dat->out, "\trom ( ");

			OUTPUT_SMART_STRING(rom, name, "name", FLAG_ROM_NAME)
			OUTPUT_SMART_STRING(rom, merge, "merge", FLAG_ROM_MERGE)
			OUTPUT_SMART_STRING(rom, bios, "bios", FLAG_ROM_BIOS)
			OUTPUT_UNSIGNED_LONG(rom, size, "size", FLAG_ROM_SIZE)
			OUTPUT_PADDED_HEX(rom, crc, "crc", FLAG_ROM_CRC)
			OUTPUT_UNQUOTED_STRING(rom, sha1, "sha1", FLAG_ROM_SHA1)
			OUTPUT_UNQUOTED_STRING(rom, md5, "md5", FLAG_ROM_MD5)
			OUTPUT_UNQUOTED_STRING(rom, region, "region", FLAG_ROM_REGION)

			if (strcmp(curr_rom->status, ""))
				OUTPUT_UNQUOTED_STRING(rom, status, "flags", FLAG_ROM_STATUS)

			OUTPUT_UNQUOTED_YES(rom, dispose, "flags", "dispose", FLAG_ROM_DISPOSE)
			OUTPUT_UNQUOTED_YES(rom, soundonly, "flags", "soundonly", FLAG_ROM_SOUNDONLY)
			OUTPUT_NONPADDED_HEX(rom, offset, "offs", FLAG_ROM_OFFSET)

			fprintf(dat->out, ")\n");
		}

		/* --- Disk information --- */

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			fprintf(dat->out, "\tdisk ( ");

			OUTPUT_SMART_STRING(disk, name, "name", FLAG_DISK_NAME)
			OUTPUT_SMART_STRING(disk, merge, "merge", FLAG_DISK_MERGE)
			OUTPUT_UNQUOTED_STRING(disk, sha1, "sha1", FLAG_DISK_SHA1)
			OUTPUT_UNQUOTED_STRING(disk, md5, "md5", FLAG_DISK_MD5)
			OUTPUT_UNQUOTED_STRING(disk, region, "region", FLAG_DISK_REGION)

			if (strcmp(curr_disk->status, ""))
				OUTPUT_UNQUOTED_STRING(disk, status, "flags", FLAG_DISK_STATUS)

			OUTPUT_NONPADDED_HEX(disk, index, "index", FLAG_DISK_INDEX)

			fprintf(dat->out, ")\n");
		}

		/* --- Sample information --- */

		if (ordering==LOGIQX_ORDERING)
		{
			OUTPUT_SMART_STRING(game, sampleof, "\tsampleof", FLAG_GAME_SAMPLEOF)
		}

		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
		{
			OUTPUT_SMART_STRING(sample, name, "\tsample", FLAG_SAMPLE_NAME)
		}

		/* --- Chip information --- */

		for (j=0, curr_chip=curr_game->chips; j<curr_game->num_chips; j++, curr_chip++)
		{
			fprintf(dat->out, "\tchip ( ");

			OUTPUT_UNQUOTED_STRING(chip, type, "type", FLAG_CHIP_TYPE)
			OUTPUT_UNQUOTED_YES(chip, soundonly, "flags", "audio", FLAG_CHIP_SOUNDONLY)
			OUTPUT_QUOTED_STRING(chip, name, "name", FLAG_CHIP_NAME)
			OUTPUT_UNSIGNED_LONG(chip, clock, "clock", FLAG_CHIP_CLOCK)

			fprintf(dat->out, ")\n");
		}

		/* --- Video information --- */

		for (j=0, curr_video=curr_game->videos; j<curr_game->num_videos; j++, curr_video++)
		{
			fprintf(dat->out, "\tvideo ( ");

			OUTPUT_UNQUOTED_STRING(video, screen, "screen", FLAG_VIDEO_SCREEN)
			OUTPUT_UNQUOTED_STRING(video, orientation, "orientation", FLAG_VIDEO_ORIENTATION)
			OUTPUT_UNSIGNED_LONG(video, width, "x", FLAG_VIDEO_WIDTH)
			OUTPUT_UNSIGNED_LONG(video, height, "y", FLAG_VIDEO_HEIGHT)
			OUTPUT_UNSIGNED_LONG(video, aspectx, "aspectx", FLAG_VIDEO_ASPECTX)
			OUTPUT_UNSIGNED_LONG(video, aspecty, "aspecty", FLAG_VIDEO_ASPECTY)
			OUTPUT_0_6_FLOAT(video, refresh, "freq", FLAG_VIDEO_REFRESH)

			fprintf(dat->out, ")\n");
		}

		/* --- Sound information --- */

		for (j=0, curr_sound=curr_game->sounds; j<curr_game->num_sounds; j++, curr_sound++)
		{
			fprintf(dat->out, "\tsound ( ");

			OUTPUT_UNSIGNED_LONG(sound, channels, "channels", FLAG_SOUND_CHANNELS)

			fprintf(dat->out, ")\n");
		}

		/* --- Input information --- */

		for (j=0, curr_input=curr_game->inputs; j<curr_game->num_inputs; j++, curr_input++)
		{
			fprintf(dat->out, "\tinput ( ");

			OUTPUT_UNSIGNED_LONG(input, players, "players", FLAG_INPUT_PLAYERS)
			OUTPUT_UNQUOTED_STRING(input, control, "control", FLAG_INPUT_CONTROL)
			OUTPUT_UNSIGNED_LONG(input, buttons, "buttons", FLAG_INPUT_BUTTONS)
			OUTPUT_UNSIGNED_LONG(input, coins, "coins", FLAG_INPUT_COINS)
			OUTPUT_UNQUOTED_STRING(input, service, "service", FLAG_INPUT_SERVICE)
			OUTPUT_UNQUOTED_STRING(input, tilt, "tilt", FLAG_INPUT_TILT)
			OUTPUT_UNSIGNED_LONG(input, dipswitches, "dipswitches", FLAG_INPUT_DIPSWITCHES)

			fprintf(dat->out, ")\n");
		}

		/* --- Dipswitch information --- */

		for (j=0, curr_dipswitch=curr_game->dipswitches; j<curr_game->num_dipswitches; j++, curr_dipswitch++)
		{
			fprintf(dat->out, "\tdipswitch ( ");

			OUTPUT_QUOTED_STRING(dipswitch, name, "name", FLAG_DIPSWITCH_NAME)

			for (k=0, curr_dipvalue=curr_dipswitch->dipvalues; k<curr_dipswitch->num_dipvalues; k++, curr_dipvalue++)
			{
				OUTPUT_QUOTED_STRING(dipvalue, name, "entry", FLAG_DIPVALUE_NAME)
				OUTPUT_QUOTED_YES(dipvalue, _default, "default", curr_dipvalue->name, FLAG_DIPVALUE_DEFAULT)
			}

			fprintf(dat->out, ")\n");
		}

		/* --- Driver information --- */

		for (j=0, curr_driver=curr_game->drivers; j<curr_game->num_drivers; j++, curr_driver++)
		{
			fprintf(dat->out, "\tdriver ( ");

			OUTPUT_UNQUOTED_STRING(driver, status, "status", FLAG_DRIVER_STATUS)
			OUTPUT_UNQUOTED_STRING(driver, emulation, "emulation", FLAG_DRIVER_EMULATION)
			OUTPUT_UNQUOTED_STRING(driver, color, "color", FLAG_DRIVER_COLOR)
			OUTPUT_UNQUOTED_STRING(driver, sound, "sound", FLAG_DRIVER_SOUND)
			OUTPUT_UNQUOTED_STRING(driver, graphic, "graphic", FLAG_DRIVER_GRAPHIC)
			OUTPUT_UNQUOTED_STRING(driver, cocktail, "cocktail", FLAG_DRIVER_COCKTAIL)
			OUTPUT_UNQUOTED_STRING(driver, protection, "protection", FLAG_DRIVER_PROTECTION)
			OUTPUT_UNSIGNED_LONG(driver, palettesize, "palettesize", FLAG_DRIVER_PALETTESIZE)
			OUTPUT_UNSIGNED_LONG(driver, colordeep, "colordeep", FLAG_DRIVER_COLORDEEP)
			OUTPUT_QUOTED_STRING(driver, credits, "credits", FLAG_DRIVER_CREDITS)

			fprintf(dat->out, ")\n");
		}

		/* --- Device information --- */

		for (j=0, curr_device=curr_game->devices; j<curr_game->num_devices; j++, curr_device++)
		{
			fprintf(dat->out, "\tdevice ( ");

			OUTPUT_UNQUOTED_STRING(device, name, "name", FLAG_DEVICE_NAME)

			for (k=0, curr_extension=curr_device->extensions; k<curr_device->num_extensions; k++, curr_extension++)
			{
				OUTPUT_UNQUOTED_STRING(extension, name, "extension", FLAG_EXTENSION_NAME)
			}

			fprintf(dat->out, ")\n");
		}

		/* --- Archive information --- */

		if (curr_game->archives)
			fprintf(dat->out, "\tarchive ( ");

		for (j=0, curr_archive=curr_game->archives; j<curr_game->num_archives; j++, curr_archive++)
		{
			OUTPUT_QUOTED_STRING(archive, name, "name", FLAG_ARCHIVE_NAME)
		}

		if (curr_game->archives)
			fprintf(dat->out, ")\n");

		fprintf(dat->out, ")\n\n");
	}

	return(errflg);
}

int save_mess_listinfo(struct dat *dat)
{
	return(0);
}
