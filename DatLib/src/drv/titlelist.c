/* --------------------------------------------------------------------------
 * Title List - Save only
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

int identify_title_list(struct dat *dat)
{
	return(0);
}


/* --- Load --- */

int load_title_list(struct dat *dat)
{
	return(0);
}


/* --- Specify --- */

int specify_title_list(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "titlelist") &&
		strcmp(dat->options->save_format, "titles"))
		return(0);
	else
		return(1);
}


/* --- Save --- */

int save_title_list(struct dat *dat)
{
	struct game *curr_game;

	int i, j, max_width=0;

	int errflg=0;

	qsort(dat->games, dat->num_games, sizeof(struct game), game_parent_sort_function);

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (!(curr_game->game_flags & FLAG_RESOURCE_NAME) && strlen(curr_game->name)>max_width)
			max_width=strlen(curr_game->name);
	}

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (curr_game->game_flags & FLAG_GAME_NAME || curr_game->game_flags & FLAG_MACHINE_NAME)
		{
			if (curr_game->cloneof)
				fprintf(dat->out, "  ");

			fprintf(dat->out, "%s ", curr_game->name);

			if (strlen(curr_game->name)<max_width+2)
				for (j=0; j<max_width+2-strlen(curr_game->name); j++)
					fprintf(dat->out, " ");

			fprintf(dat->out, "%s\n", curr_game->description);
		}
	}

	/* --- User only wants the titles so don't report other details that are not saved! --- */

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

