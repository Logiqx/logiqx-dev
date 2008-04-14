/* --------------------------------------------------------------------------
 * Map File - Save only
 * -------------------------------------------------------------------------- */

/* --- Standard includes --- */

#include <stdio.h>
#include <string.h>


/* --- My includes --- */

#include "../type.h"
#include "../token.h"


/* --- External structures --- */

extern const struct datlib_token datlib_tokens[];

int game_parent_sort_function(const void *game1, const void *game2);


/* --- Is debugging enabled? --- */

extern int datlib_debug;


/* --- Identification --- */

int identify_map_file(struct dat *dat)
{
	return(0);
}


/* --- Load --- */

int load_map_file(struct dat *dat)
{
	return(0);
}


/* --- Specify --- */

int specify_map_file(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "mapfile") &&
		strcmp(dat->options->save_format, "map"))
		return(0);
	else
		return(1);
}


/* --- Save --- */

int save_map_file(struct dat *dat)
{
	struct game *curr_game;

	int i;

	int errflg=0;

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (curr_game->game_flags & FLAG_GAME_NAME || curr_game->game_flags & FLAG_MACHINE_NAME)
		{
			fprintf(dat->out, "%s.zip|%s\n", curr_game->name, curr_game->description);
		}
	}

	/* --- User only wants the mappings so don't report other details that are not saved! --- */

	dat->emulator_saved=0xff;
	dat->header_saved=0xffff;
	dat->clrmamepro_saved=0xff;
	dat->romcenter_saved=0xffff;
	dat->game_saved=0xffff;
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

