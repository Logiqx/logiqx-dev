/* --------------------------------------------------------------------------
 * AAE RomList
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

int identify_aae_romlist(struct dat *dat)
{
	int match=0;

	BUFFER1_REWIND

	BUFFER1_GET_TOKEN

	if (!strcmp(TOKEN, "AAE"))
		match++;

	return(match);
}


/* --- Load --- */

int load_aae_romlist(struct dat *dat)
{
	int in_game=0, errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		BUFFER1_GET_TOKEN

		if (strchr(TOKEN, ':'))
		{
			*strchr(TOKEN, ':')='\0';

			BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

			in_game++;
		}
		else if (in_game && *TOKEN)
		{
			BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


/* --- Specify --- */

int specify_aae_romlist(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "aaeromlist") &&
		strcmp(dat->options->save_format, "aae") &&
		strcmp(dat->options->save_format, "romlist"))
		return(0);
	else
		return(1);
}


/* --- Save --- */

int save_aae_romlist(struct dat *dat)
{
	struct game *curr_game;
	struct rom *curr_rom;

	int i, j, errflg=0;

	fprintf(dat->out, "AAE All Games RomList");

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		fprintf(dat->out, "\n\n%s:", curr_game->name);

		for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
		{
			fprintf(dat->out, "\n%s", curr_rom->name);
		}
	}

	/* --- User only wants the names so don't report other details that are not saved! --- */

	dat->emulator_saved=0xff;
	dat->header_saved=0xffff;
	dat->clrmamepro_saved=0xff;
	dat->romcenter_saved=0xffff;
	dat->game_saved=0xffff;
	dat->release_saved=0xff;
	dat->biosset_saved=0xff;
	dat->rom_saved=0xffff;
	dat->disk_saved=0xff;
	dat->sample_saved=0xff;
	dat->chip_saved=0xff;
	dat->video_saved=0xff;
	dat->display_saved=0xff;
	dat->sound_saved=0xff;
	dat->input_saved=0xff;
	dat->control_saved=0xff;
	dat->dipswitch_saved=0xff;
	dat->dipvalue_saved=0xff;
	dat->driver_saved=0xff;

	return(errflg);
}

