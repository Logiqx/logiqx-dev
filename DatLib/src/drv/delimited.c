/* --------------------------------------------------------------------------
 * Tab Delimited - Load and Save
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

int identify_tab_delimited(struct dat *dat)
{
	uint32_t i;
	int match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		if (!strncmp(BUFFER1_PTR, "game\t", 5) ||
			!strncmp(BUFFER1_PTR, "resource\t", 9) ||
			!strncmp(BUFFER1_PTR, "machine\t", 8))
		match++;

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

#define BUFFER1_RECORD_TYPE(TYPE) (!strncmp(BUFFER1_PTR, TYPE, strlen(TYPE)))

#define BUFFER1_SKIP_FIELD \
{ \
	if (strchr(BUFFER1_PTR, '\t')) \
		BUFFER1_PTR=strchr(BUFFER1_PTR, '\t')+1; \
	else \
		BUFFER1_PTR=BUFFER1_PTR+strlen(BUFFER1_PTR); \
}

#define BUFFER1_GET_FIELD(TYPE) \
{ \
	char *token_ptr=TOKEN; \
\
	if (strncmp(BUFFER1_PTR, "\\N", 2)) \
	{ \
		BUFFER1_GET_TOKEN_TO_DELIMITER('\t') \
		if (*TOKEN) \
			BUFFER2_PUT_TOKEN(TYPE) \
	} \
	else \
	{ \
		BUFFER1_SKIP_FIELD \
	} \
}

int load_tab_delimited(struct dat *dat)
{
	char *game_name;
	int errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		/* --- Game/machine information --- */

		if (BUFFER1_RECORD_TYPE("game\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			game_name=BUFFER1_PTR;
			BUFFER1_SKIP_FIELD

			if (!strncmp(BUFFER1_PTR, "no", 2))
			{
				BUFFER1_SKIP_FIELD
				strcpy(TOKEN, game_name);
				if (strchr(TOKEN, '\t'))
					*strchr(TOKEN, '\t')='\0';
				BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME) \
				BUFFER1_GET_FIELD(TOKEN_RESOURCE_SOURCEFILE)
				BUFFER1_SKIP_FIELD
				BUFFER1_SKIP_FIELD
				BUFFER1_SKIP_FIELD
				BUFFER1_GET_FIELD(TOKEN_RESOURCE_DESCRIPTION)
				BUFFER1_GET_FIELD(TOKEN_RESOURCE_YEAR)
				BUFFER1_GET_FIELD(TOKEN_RESOURCE_MANUFACTURER)
				BUFFER1_GET_FIELD(TOKEN_RESOURCE_HISTORY)
				BUFFER1_GET_FIELD(TOKEN_RESOURCE_REBUILDTO)
			}
			else
			{
				BUFFER1_SKIP_FIELD
				strcpy(TOKEN, game_name);
				if (strchr(TOKEN, '\t'))
					*strchr(TOKEN, '\t')='\0';
				BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME) \
				BUFFER1_GET_FIELD(TOKEN_GAME_SOURCEFILE)
				BUFFER1_GET_FIELD(TOKEN_GAME_CLONEOF)
				BUFFER1_GET_FIELD(TOKEN_GAME_ROMOF)
				BUFFER1_GET_FIELD(TOKEN_GAME_SAMPLEOF)
				BUFFER1_GET_FIELD(TOKEN_GAME_DESCRIPTION)
				BUFFER1_GET_FIELD(TOKEN_GAME_YEAR)
				BUFFER1_GET_FIELD(TOKEN_GAME_MANUFACTURER)
				BUFFER1_GET_FIELD(TOKEN_GAME_HISTORY)
				BUFFER1_GET_FIELD(TOKEN_GAME_REBUILDTO)
			}
		}

		/* --- Comment information --- */

		if (BUFFER1_RECORD_TYPE("game_comment\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_COMMENT_TEXT)
		}

		/* --- BIOS Set information --- */

		if (BUFFER1_RECORD_TYPE("game_biosset\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_BIOSSET_NAME)
			BUFFER1_GET_FIELD(TOKEN_BIOSSET_DESCRIPTION)
			BUFFER1_GET_FIELD(TOKEN_BIOSSET_DEFAULT)
		}

		/* --- ROM information --- */

		if (BUFFER1_RECORD_TYPE("game_rom\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_ROM_NAME)
			BUFFER1_GET_FIELD(TOKEN_ROM_MERGE)
			BUFFER1_GET_FIELD(TOKEN_ROM_BIOS)
			BUFFER1_GET_FIELD(TOKEN_ROM_SIZE)
			BUFFER1_GET_FIELD(TOKEN_ROM_CRC)
			BUFFER1_GET_FIELD(TOKEN_ROM_SHA1)
			BUFFER1_GET_FIELD(TOKEN_ROM_MD5)
			BUFFER1_GET_FIELD(TOKEN_ROM_REGION)
			BUFFER1_GET_FIELD(TOKEN_ROM_STATUS)
			BUFFER1_GET_FIELD(TOKEN_ROM_DISPOSE)
			BUFFER1_GET_FIELD(TOKEN_ROM_SOUNDONLY)
			BUFFER1_GET_FIELD(TOKEN_ROM_OFFSET)
		}

		/* --- Disk information --- */

		if (BUFFER1_RECORD_TYPE("game_disk\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_DISK_NAME)
			BUFFER1_GET_FIELD(TOKEN_DISK_MERGE)
			BUFFER1_GET_FIELD(TOKEN_DISK_SHA1)
			BUFFER1_GET_FIELD(TOKEN_DISK_MD5)
			BUFFER1_GET_FIELD(TOKEN_DISK_REGION)
			BUFFER1_GET_FIELD(TOKEN_DISK_STATUS)
			BUFFER1_GET_FIELD(TOKEN_DISK_INDEX)
		}

		/* --- Sample information --- */

		if (BUFFER1_RECORD_TYPE("game_sample\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_SAMPLE_NAME)
		}

		/* --- Chip information --- */

		if (BUFFER1_RECORD_TYPE("game_chip\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_CHIP_TYPE)
			BUFFER1_GET_FIELD(TOKEN_CHIP_SOUNDONLY)
			BUFFER1_GET_FIELD(TOKEN_CHIP_NAME)
			BUFFER1_GET_FIELD(TOKEN_CHIP_CLOCK)
		}

		/* --- Video information --- */

		if (BUFFER1_RECORD_TYPE("game_video\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_VIDEO_SCREEN)
			BUFFER1_GET_FIELD(TOKEN_VIDEO_ORIENTATION)
			BUFFER1_GET_FIELD(TOKEN_VIDEO_WIDTH)
			BUFFER1_GET_FIELD(TOKEN_VIDEO_HEIGHT)
			BUFFER1_GET_FIELD(TOKEN_VIDEO_ASPECTX)
			BUFFER1_GET_FIELD(TOKEN_VIDEO_ASPECTY)
			BUFFER1_GET_FIELD(TOKEN_VIDEO_REFRESH)
		}

		/* --- Sound information --- */

		if (BUFFER1_RECORD_TYPE("game_sound\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_SOUND_CHANNELS)
		}

		/* --- Input information --- */

		if (BUFFER1_RECORD_TYPE("game_input\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_INPUT_PLAYERS)
			BUFFER1_GET_FIELD(TOKEN_INPUT_CONTROL)
			BUFFER1_GET_FIELD(TOKEN_INPUT_BUTTONS)
			BUFFER1_GET_FIELD(TOKEN_INPUT_COINS)
			BUFFER1_GET_FIELD(TOKEN_INPUT_SERVICE)
			BUFFER1_GET_FIELD(TOKEN_INPUT_TILT)
		}

		/* --- Dipswitch information --- */

		if (BUFFER1_RECORD_TYPE("game_dipswitch\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_DIPSWITCH_NAME)
		}

		if (BUFFER1_RECORD_TYPE("game_dipvalue\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_DIPVALUE_NAME)
			BUFFER1_GET_FIELD(TOKEN_DIPVALUE_DEFAULT)
		}

		/* --- Driver information --- */

		if (BUFFER1_RECORD_TYPE("game_driver\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_DRIVER_STATUS)
			BUFFER1_GET_FIELD(TOKEN_DRIVER_EMULATION)
			BUFFER1_GET_FIELD(TOKEN_DRIVER_COLOR)
			BUFFER1_GET_FIELD(TOKEN_DRIVER_SOUND)
			BUFFER1_GET_FIELD(TOKEN_DRIVER_GRAPHIC)
			BUFFER1_GET_FIELD(TOKEN_DRIVER_COCKTAIL)
			BUFFER1_GET_FIELD(TOKEN_DRIVER_PROTECTION)
			BUFFER1_GET_FIELD(TOKEN_DRIVER_PALETTESIZE)
		}

		/* --- Device information --- */

		if (BUFFER1_RECORD_TYPE("game_device\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_DEVICE_NAME)
		}

		if (BUFFER1_RECORD_TYPE("game_extension\t"))
		{
			/* --- Skip record type and data file name --- */

			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD
			BUFFER1_SKIP_FIELD

			/* --- Process the other fields --- */

			BUFFER1_GET_FIELD(TOKEN_EXTENSION_NAME)
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


/* --- Specify --- */

int specify_tab_delimited(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "delimited") &&
		strcmp(dat->options->save_format, "tab") &&
		strcmp(dat->options->save_format, "text"))
		return(0);
	else
		return(1);
}


/* --- Save --- */

void output_delimited_string(FILE *out, unsigned char *ptr)
{
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
}

#define OUTPUT_STRING_FIELD(OBJECT, FIELD, FIELD_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & FIELD_FLAG) \
{ \
	output_delimited_string(dat->out, curr_##OBJECT->FIELD); \
	fprintf(dat->out, "\t"); \
	dat->OBJECT##_saved|=FIELD_FLAG; \
} \
else \
{ \
	fprintf(dat->out, "\\N\t"); \
	dat->OBJECT##_saved|=FIELD_FLAG; \
}

#define OUTPUT_UNSIGNED_LONG_FIELD(OBJECT, FIELD, FIELD_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & FIELD_FLAG) \
{ \
	fprintf(dat->out, "%lu\t", (unsigned long)curr_##OBJECT->FIELD); \
	dat->OBJECT##_saved|=FIELD_FLAG; \
} \
else \
{ \
	fprintf(dat->out, "\\N\t"); \
}

#define OUTPUT_0_6_FLOAT_FIELD(OBJECT, FIELD, FIELD_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & FIELD_FLAG) \
{ \
	fprintf(dat->out, "%0.6f\t", curr_##OBJECT->FIELD); \
	dat->OBJECT##_saved|=FIELD_FLAG; \
} \
else \
{ \
	fprintf(dat->out, "\\N\t"); \
}

#define OUTPUT_PADDED_HEX_FIELD(OBJECT, FIELD, FIELD_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & FIELD_FLAG) \
{ \
	fprintf(dat->out, "%08lx\t", (unsigned long)curr_##OBJECT->FIELD); \
	dat->OBJECT##_saved|=FIELD_FLAG; \
} \
else \
{ \
	fprintf(dat->out, "\\N\t"); \
}

#define OUTPUT_UNPADDED_HEX_FIELD(OBJECT, FIELD, FIELD_FLAG) \
if (curr_##OBJECT->OBJECT##_flags & FIELD_FLAG) \
{ \
	fprintf(dat->out, "%lx\t", (unsigned long)curr_##OBJECT->FIELD); \
	dat->OBJECT##_saved|=FIELD_FLAG; \
} \
else \
{ \
	fprintf(dat->out, "\\N\t"); \
}

int save_tab_delimited(struct dat *dat)
{
	struct game *curr_game;
	struct comment *curr_comment=dat->comments;
	struct biosset *curr_biosset=dat->biossets;
	struct rom *curr_rom=dat->roms;
	struct disk *curr_disk=dat->disks;
	struct sample *curr_sample=dat->samples;
	struct chip *curr_chip=dat->chips;
	struct video *curr_video=dat->videos;
	struct sound *curr_sound=dat->sounds;
	struct input *curr_input=dat->inputs;
	struct dipswitch *curr_dipswitch=dat->dipswitches;
	struct dipvalue *curr_dipvalue=dat->dipvalues;
	struct driver *curr_driver=dat->drivers;
	struct device *curr_device=dat->devices;
	struct extension *curr_extension=dat->extensions;

	char dat_name[MAX_STRING_LENGTH];

	int i, j, k;

	int errflg=0;

	/* --- Work out the name of the data file --- */

	strcpy(dat_name, dat->name);
	if (strrchr(dat_name, '\\'))
		strcpy(dat_name, strrchr(dat_name, '\\')+1);
	if (strrchr(dat_name, '/'))
		strcpy(dat_name, strrchr(dat_name, '/')+1);
	if (strrchr(dat_name, '.'))
		*strrchr(dat_name, '.')='\0';

	/* --- For all games --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		/* --- Game/machine information --- */

		fprintf(dat->out, "game\t%s\t", dat_name);

		OUTPUT_STRING_FIELD(game, name, (FLAG_GAME_NAME|FLAG_MACHINE_NAME|FLAG_RESOURCE_NAME))

		if (curr_game->game_flags & FLAG_RESOURCE_NAME)
			fprintf(dat->out, "no\t");
		else
			fprintf(dat->out, "\\N\t");

		OUTPUT_STRING_FIELD(game, sourcefile, FLAG_GAME_SOURCEFILE)
		OUTPUT_STRING_FIELD(game, cloneof, FLAG_GAME_CLONEOF)
		OUTPUT_STRING_FIELD(game, romof, FLAG_GAME_ROMOF)
		OUTPUT_STRING_FIELD(game, sampleof, FLAG_GAME_SAMPLEOF)
		OUTPUT_STRING_FIELD(game, description, FLAG_GAME_DESCRIPTION)
		OUTPUT_STRING_FIELD(game, year, FLAG_GAME_YEAR)
		OUTPUT_STRING_FIELD(game, manufacturer, FLAG_GAME_MANUFACTURER)
		OUTPUT_STRING_FIELD(game, history, FLAG_GAME_HISTORY)
		OUTPUT_STRING_FIELD(game, rebuildto, FLAG_GAME_REBUILDTO)

		fprintf(dat->out, "\n");

		/* --- Comment information --- */

		for (j=0, curr_comment=curr_game->comments; j<curr_game->num_comments; j++, curr_comment++)
		{
			fprintf(dat->out, "game_comment\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_STRING_FIELD(comment, text, FLAG_COMMENT_TEXT)

			fprintf(dat->out, "\n");
		}

		/* --- BIOS Set information --- */

		for (j=0, curr_biosset=curr_game->biossets; j<curr_game->num_biossets; j++, curr_biosset++)
		{
			fprintf(dat->out, "game_biosset\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_STRING_FIELD(biosset, name, FLAG_BIOSSET_NAME)
			OUTPUT_STRING_FIELD(biosset, description, FLAG_BIOSSET_DESCRIPTION)
			OUTPUT_STRING_FIELD(biosset, _default, FLAG_BIOSSET_DEFAULT)

			fprintf(dat->out, "\n");
		}

		/* --- ROM information --- */

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			fprintf(dat->out, "game_rom\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_STRING_FIELD(rom, name, FLAG_ROM_NAME)
			OUTPUT_STRING_FIELD(rom, merge, FLAG_ROM_MERGE)
			OUTPUT_STRING_FIELD(rom, bios, FLAG_ROM_BIOS)
			OUTPUT_UNSIGNED_LONG_FIELD(rom, size, FLAG_ROM_SIZE)
			OUTPUT_PADDED_HEX_FIELD(rom, crc, FLAG_ROM_CRC)
			OUTPUT_STRING_FIELD(rom, sha1, FLAG_ROM_SHA1)
			OUTPUT_STRING_FIELD(rom, md5, FLAG_ROM_MD5)
			OUTPUT_STRING_FIELD(rom, region, FLAG_ROM_REGION)
			OUTPUT_STRING_FIELD(rom, status, FLAG_ROM_STATUS)
			OUTPUT_STRING_FIELD(rom, dispose, FLAG_ROM_DISPOSE)
			OUTPUT_STRING_FIELD(rom, soundonly, FLAG_ROM_SOUNDONLY)
			OUTPUT_UNPADDED_HEX_FIELD(rom, offset, FLAG_ROM_OFFSET)

			fprintf(dat->out, "\n");
		}

		/* --- Disk information --- */

		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			fprintf(dat->out, "game_disk\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_STRING_FIELD(disk, name, FLAG_DISK_NAME)
			OUTPUT_STRING_FIELD(disk, merge, FLAG_DISK_MERGE)
			OUTPUT_STRING_FIELD(disk, sha1, FLAG_DISK_SHA1)
			OUTPUT_STRING_FIELD(disk, md5, FLAG_DISK_MD5)
			OUTPUT_STRING_FIELD(disk, region, FLAG_DISK_REGION)
			OUTPUT_STRING_FIELD(disk, status, FLAG_DISK_STATUS)
			OUTPUT_UNPADDED_HEX_FIELD(disk, index, FLAG_DISK_INDEX)

			fprintf(dat->out, "\n");
		}

		/* --- Sample information --- */

		for (j=0, curr_sample=curr_game->samples; j<curr_game->num_samples; j++, curr_sample++)
		{
			fprintf(dat->out, "game_sample\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_STRING_FIELD(sample, name, FLAG_SAMPLE_NAME)

			fprintf(dat->out, "\n");
		}

		/* --- Chip information --- */

		for (j=0, curr_chip=curr_game->chips; j<curr_game->num_chips; j++, curr_chip++)
		{
			fprintf(dat->out, "game_chip\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_STRING_FIELD(chip, type, FLAG_CHIP_TYPE)
			OUTPUT_STRING_FIELD(chip, soundonly, FLAG_CHIP_SOUNDONLY)
			OUTPUT_STRING_FIELD(chip, name, FLAG_CHIP_NAME)
			OUTPUT_UNSIGNED_LONG_FIELD(chip, clock, FLAG_CHIP_CLOCK)

			fprintf(dat->out, "\n");
		}

		/* --- Video information --- */

		for (j=0, curr_video=curr_game->videos; j<curr_game->num_videos; j++, curr_video++)
		{
			fprintf(dat->out, "game_video\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_STRING_FIELD(video, screen, FLAG_VIDEO_SCREEN)
			OUTPUT_STRING_FIELD(video, orientation, FLAG_VIDEO_ORIENTATION)
			OUTPUT_UNSIGNED_LONG_FIELD(video, width, FLAG_VIDEO_WIDTH)
			OUTPUT_UNSIGNED_LONG_FIELD(video, height, FLAG_VIDEO_HEIGHT)
			OUTPUT_UNSIGNED_LONG_FIELD(video, aspectx, FLAG_VIDEO_ASPECTX)
			OUTPUT_UNSIGNED_LONG_FIELD(video, aspecty, FLAG_VIDEO_ASPECTY)
			OUTPUT_0_6_FLOAT_FIELD(video, refresh, FLAG_VIDEO_REFRESH)

			fprintf(dat->out, "\n");
		}

		/* --- Sound information --- */

		for (j=0, curr_sound=curr_game->sounds; j<curr_game->num_sounds; j++, curr_sound++)
		{
			fprintf(dat->out, "game_sound\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_UNSIGNED_LONG_FIELD(sound, channels, FLAG_SOUND_CHANNELS)

			fprintf(dat->out, "\n");
		}

		/* --- Input information --- */

		for (j=0, curr_input=curr_game->inputs; j<curr_game->num_inputs; j++, curr_input++)
		{
			fprintf(dat->out, "game_input\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_UNSIGNED_LONG_FIELD(input, players, FLAG_INPUT_PLAYERS)
			OUTPUT_STRING_FIELD(input, control, FLAG_INPUT_CONTROL)
			OUTPUT_UNSIGNED_LONG_FIELD(input, buttons, FLAG_INPUT_BUTTONS)
			OUTPUT_UNSIGNED_LONG_FIELD(input, coins, FLAG_INPUT_COINS)
			OUTPUT_STRING_FIELD(input, service, FLAG_INPUT_SERVICE)
			OUTPUT_STRING_FIELD(input, tilt, FLAG_INPUT_TILT)

			fprintf(dat->out, "\n");
		}

		/* --- Dipswitch information --- */

		for (j=0, curr_dipswitch=curr_game->dipswitches; j<curr_game->num_dipswitches; j++, curr_dipswitch++)
		{
			fprintf(dat->out, "game_dipswitch\t%s\t%s\t", dat_name, curr_game->name);
			OUTPUT_STRING_FIELD(dipswitch, name, FLAG_DIPSWITCH_NAME)
			fprintf(dat->out, "\n");

			for (k=0, curr_dipvalue=curr_dipswitch->dipvalues; k<curr_dipswitch->num_dipvalues; k++, curr_dipvalue++)
			{
				fprintf(dat->out, "game_dipvalue\t%s\t%s\t", dat_name, curr_game->name);

				OUTPUT_STRING_FIELD(dipswitch, name, FLAG_DIPSWITCH_NAME)

				OUTPUT_STRING_FIELD(dipvalue, name, FLAG_DIPVALUE_NAME)
				OUTPUT_STRING_FIELD(dipvalue, _default, FLAG_DIPVALUE_DEFAULT)

				fprintf(dat->out, "\n");
			}
		}

		/* --- Driver information --- */

		for (j=0, curr_driver=curr_game->drivers; j<curr_game->num_drivers; j++, curr_driver++)
		{
			fprintf(dat->out, "game_driver\t%s\t%s\t", dat_name, curr_game->name);

			OUTPUT_STRING_FIELD(driver, status, FLAG_DRIVER_STATUS)
			OUTPUT_STRING_FIELD(driver, emulation, FLAG_DRIVER_EMULATION)
			OUTPUT_STRING_FIELD(driver, color, FLAG_DRIVER_COLOR)
			OUTPUT_STRING_FIELD(driver, sound, FLAG_DRIVER_SOUND)
			OUTPUT_STRING_FIELD(driver, graphic, FLAG_DRIVER_GRAPHIC)
			OUTPUT_STRING_FIELD(driver, cocktail, FLAG_DRIVER_COCKTAIL)
			OUTPUT_STRING_FIELD(driver, protection, FLAG_DRIVER_PROTECTION)
			OUTPUT_UNSIGNED_LONG_FIELD(driver, palettesize, FLAG_DRIVER_PALETTESIZE)

			fprintf(dat->out, "\n");
		}

		/* --- Device information --- */

		for (j=0, curr_device=curr_game->devices; j<curr_game->num_devices; j++, curr_device++)
		{
			fprintf(dat->out, "game_device\t%s\t%s\t", dat_name, curr_game->name);
			OUTPUT_STRING_FIELD(device, name, FLAG_DEVICE_NAME)
			fprintf(dat->out, "\n");

			for (k=0, curr_extension=curr_device->extensions; k<curr_device->num_extensions; k++, curr_extension++)
			{
				fprintf(dat->out, "game_extension\t%s\t%s\t", dat_name, curr_game->name);

				OUTPUT_STRING_FIELD(device, name, FLAG_DEVICE_NAME)

				OUTPUT_STRING_FIELD(extension, name, FLAG_EXTENSION_NAME)

				fprintf(dat->out, "\n");
			}
		}
	}

	return(errflg);
}

