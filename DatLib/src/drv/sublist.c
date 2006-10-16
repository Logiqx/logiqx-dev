/* --------------------------------------------------------------------------
 * RomCenter Sublist - Save only
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

int identify_romcenter_sublist(struct dat *dat)
{
	return(0);
}


/* --- Load --- */

int load_romcenter_sublist(struct dat *dat)
{
	return(0);
}


/* --- Specify --- */

int specify_romcenter_sublist(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "sublist") &&
		strcmp(dat->options->save_format, "sub") &&
		strcmp(dat->options->save_format, "rcsublist") &&
		strcmp(dat->options->save_format, "rcsub"))
		return(0);
	else
		return(1);
}


/* --- Save --- */

int save_romcenter_sublist(struct dat *dat)
{
	struct game *curr_game;

	int i, errflg=0;

	fprintf(dat->out, "[sublist]\n");

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		fprintf(dat->out, "%s\n", curr_game->name);
	}

	/* --- User only wants the names so don't report other details that are not saved! --- */

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

