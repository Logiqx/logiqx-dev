/* --------------------------------------------------------------------------
 * RomCenter 2.50 - Load and Save
 * RomCenter 2.00 - Load only
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

int identify_romcenter_250(struct dat *dat)
{
	uint32_t i;
	int in_romcenter_dat=0, match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN;

		if (*TOKEN=='[')
		{
			LOWER(TOKEN)

			if (!strcmp(TOKEN, "[dat]"))
				in_romcenter_dat=1;
			else
				in_romcenter_dat=0;
		}
		else if (in_romcenter_dat)
		{
			LOWER(TOKEN)

			if (!strcmp(TOKEN, "version=2.50"))
				match++;
		}

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}

int identify_romcenter_200(struct dat *dat)
{
	uint32_t i;
	int in_romcenter_dat=0, match=0;

	BUFFER1_REWIND

	for (i=0; i<50 && BUFFER1_REMAINING; i++)
	{
		BUFFER1_GET_TOKEN;

		if (*TOKEN=='[')
		{
			LOWER(TOKEN)

			if (!strcmp(TOKEN, "[dat]"))
				in_romcenter_dat=1;
			else
				in_romcenter_dat=0;
		}
		else if (in_romcenter_dat)
		{
			LOWER(TOKEN)

			if (!strcmp(TOKEN, "version=2.00"))
				match++;
		}

		BUFFER1_ADVANCE_LINE
	}

	return(match);
}


/* --- Load --- */

int load_romcenter_250(struct dat *dat)
{
	int in_romcenter_credits=0, in_romcenter_dat=0, in_romcenter_emulator=0, in_romcenter_games=0, in_romcenter_resources=0;
	char *parent_name, *parent_title, *game_name, *game_title, *rom_name, *rom_crc, *rom_size, *romof_name, *rom_merge, *rest_of_line;
	char *prev_game=0;
	char *value;

	int errflg=0;

	BUFFER1_REWIND
	BUFFER2_REWIND

	while (!errflg && BUFFER1_REMAINING)
	{
		if (*BUFFER1_PTR=='[')
		{
			BUFFER1_GET_TOKEN

			in_romcenter_credits=in_romcenter_dat=in_romcenter_emulator=in_romcenter_games=0;

			LOWER(TOKEN)

			if (!strcmp(TOKEN, "[credits]"))
				in_romcenter_credits=1;
			if (!strcmp(TOKEN, "[dat]"))
				in_romcenter_dat=1;
			else if (!strcmp(TOKEN, "[emulator]"))
				in_romcenter_emulator=1;
			else if (!strcmp(TOKEN, "[games]"))
				in_romcenter_games=1;
			else if (!strcmp(TOKEN, "[resources]"))
				in_romcenter_resources=1;
		}
		else if (in_romcenter_credits && strchr(BUFFER1_PTR, '='))
		{
			strcpy(TOKEN, BUFFER1_PTR);

			value=strchr(TOKEN, '=')+1;

			if (strlen(value)>0)
			{
				*strchr(TOKEN, '=')='\0';

				LOWER(TOKEN)

				if (!strcmp(TOKEN, "author"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_AUTHOR)
				}
				else if (!strcmp(TOKEN, "email"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_EMAIL)
				}
				else if (!strcmp(TOKEN, "homepage"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_HOMEPAGE)
				}
				else if (!strcmp(TOKEN, "url"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_URL)
				}
				else if (!strcmp(TOKEN, "version"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_VERSION)
				}
				else if (!strcmp(TOKEN, "date"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_DATE)
				}
				else if (!strcmp(TOKEN, "comment"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_CREDITS_COMMENT)
				}
			}
		}
		else if (in_romcenter_dat && strchr(BUFFER1_PTR, '='))
		{
			strcpy(TOKEN, BUFFER1_PTR);

			value=strchr(TOKEN, '=')+1;

			if (strlen(value)>0)
			{
				*strchr(TOKEN, '=')='\0';

				LOWER(TOKEN)

				if (!strcmp(TOKEN, "plugin"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_DAT_PLUGIN)
				}
				else if (!strcmp(TOKEN, "split"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_DAT_SPLIT)
				}
				else if (!strcmp(TOKEN, "merge"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_DAT_MERGE)
				}
			}
		}
		else if (in_romcenter_emulator && strchr(BUFFER1_PTR, '='))
		{
			strcpy(TOKEN, BUFFER1_PTR);

			value=strchr(TOKEN, '=')+1;

			if (strlen(value)>0)
			{
				*strchr(TOKEN, '=')='\0';

				LOWER(TOKEN)

				if (!strcmp(TOKEN, "refname"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_EMULATOR_REFNAME)
				}
				else if (!strcmp(TOKEN, "version"))
				{
					strcpy(TOKEN, value);
					BUFFER2_PUT_TOKEN(TOKEN_ROMCENTER_EMULATOR_VERSION)
				}
			}
		}
		else if ((in_romcenter_games || in_romcenter_resources) && *BUFFER1_PTR=='¬')
		{
			parent_name=BUFFER1_PTR+1;
			parent_title=game_name=game_title=rom_name=rom_crc=rom_size=romof_name=rom_merge=rest_of_line=0;

			if (parent_name && (parent_title=strchr(parent_name, '¬')))
			{
				*parent_title++='\0';
				BUFFER1_PTR=parent_title;
			}

			if (parent_title && (game_name=strchr(parent_title, '¬')))
			{
				*game_name++='\0';
				BUFFER1_PTR=game_name;
			}

			if (game_name && (game_title=strchr(game_name, '¬')))
			{
				*game_title++='\0';
				BUFFER1_PTR=game_title;
			}

			if (game_title && (rom_name=strchr(game_title, '¬')))
			{
				*rom_name++='\0';
				BUFFER1_PTR=rom_name;
			}

			if (rom_name && (rom_crc=strchr(rom_name, '¬')))
			{
				*rom_crc++='\0';
				BUFFER1_PTR=rom_crc;
			}

			if (rom_crc && (rom_size=strchr(rom_crc, '¬')))
			{
				*rom_size++='\0';
				BUFFER1_PTR=rom_size;
			}

			if (rom_size && (romof_name=strchr(rom_size, '¬')))
			{
				*romof_name++='\0';
				BUFFER1_PTR=romof_name;
			}

			if (romof_name && (rom_merge=strchr(romof_name, '¬')))
			{
				*rom_merge++='\0';
				BUFFER1_PTR=rom_merge;
			}

			if (rom_merge && (rest_of_line=strchr(rom_merge, '¬')))
			{
				*rest_of_line++='\0';
				BUFFER1_PTR=rest_of_line;

				if (!prev_game || strcmp(game_name, prev_game))
				{
					if (in_romcenter_games)
					{
						strcpy(TOKEN, game_name);
						BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)

						strcpy(TOKEN, game_title);
						BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)

						if (strcmp(game_name, parent_name))
						{
							strcpy(TOKEN, parent_name);
							BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)
						}
					}
					else
					{
						strcpy(TOKEN, game_name);
						BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME)

						strcpy(TOKEN, game_title);
						BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_DESCRIPTION)
					}

					prev_game=game_name;
				}

				strcpy(TOKEN, rom_name);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)

				if (*rom_merge)
				{
					strcpy(TOKEN, rom_merge);
					BUFFER2_PUT_TOKEN(TOKEN_ROM_MERGE)
				}

				strcpy(TOKEN, rom_size);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)

				strcpy(TOKEN, rom_crc);
				BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)

				if (*romof_name)
				{
					strcpy(TOKEN, romof_name);
					BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
				}
			}
		}

		BUFFER1_ADVANCE_LINE
	}

	return(0);
}

int load_romcenter_200(struct dat *dat)
{
	return(load_romcenter_250(dat));
}


/* --- Specify --- */

int specify_romcenter_250(struct dat *dat)
{
	if (strcmp(dat->options->save_format, "romcenter2") &&
		strcmp(dat->options->save_format, "rc2") &&
		strcmp(dat->options->save_format, "romcenter") &&
		strcmp(dat->options->save_format, "rc"))
		return(0);
	else
		return(1);
}

int specify_romcenter_200(struct dat *dat)
{
	return(0);
}


/* --- Save --- */

int save_romcenter_250(struct dat *dat)
{
	struct game *curr_game;
	struct rom *curr_rom;
	struct disk *curr_disk;

	int i, j;

	int errflg=0, invalid=0;

	/* --- Copy ClrMamePro header to RomCenter header --- */

	if (dat->clrmamepro.name)
		dat->romcenter_emulator.refname=dat->clrmamepro.name;

	if (dat->clrmamepro.description)
		dat->romcenter_emulator.version=dat->clrmamepro.description;

	if (dat->clrmamepro.category)
		dat->romcenter_credits.comment=dat->clrmamepro.category;

	if (dat->clrmamepro.version)
		dat->romcenter_credits.version=dat->clrmamepro.version;

	if (dat->clrmamepro.author)
		dat->romcenter_credits.author=dat->clrmamepro.author;

	if (dat->dat_flags & FLAG_DAT_FULL_MERGING)
	{
		dat->romcenter_dat.merge="1";
		dat->romcenter_dat.split="0";
	}
	else if (dat->dat_flags & FLAG_DAT_SPLIT_MERGING)
	{
		dat->romcenter_dat.merge="1";
		dat->romcenter_dat.split="1";
	}
	else if (dat->dat_flags & FLAG_DAT_NO_MERGING)
	{
		dat->romcenter_dat.merge="0";
		dat->romcenter_dat.split="1";
	}

	if (!dat->romcenter_dat.version)
		dat->romcenter_dat.version="2.50";

	if (!dat->romcenter_dat.plugin)
		dat->romcenter_dat.plugin="arcade.dll";

	/* --- Save RomCenter data file --- */

	fprintf(dat->out, "[CREDITS]");
	fprintf(dat->out, "\nauthor=");
	if (dat->romcenter_credits.author)
		fprintf(dat->out, "%s", dat->romcenter_credits.author);
	fprintf(dat->out, "\nemail=");
	if (dat->romcenter_credits.email)
		fprintf(dat->out, "%s", dat->romcenter_credits.email);
	fprintf(dat->out, "\nhomepage=");
	if (dat->romcenter_credits.homepage)
		fprintf(dat->out, "%s", dat->romcenter_credits.homepage);
	fprintf(dat->out, "\nurl=");
	if (dat->romcenter_credits.url)
		fprintf(dat->out, "%s", dat->romcenter_credits.url);
	fprintf(dat->out, "\nversion=");
	if (dat->romcenter_credits.version)
		fprintf(dat->out, "%s", dat->romcenter_credits.version);
	fprintf(dat->out, "\ndate=");
	if (dat->romcenter_credits.date)
		fprintf(dat->out, "%s", dat->romcenter_credits.date);
	fprintf(dat->out, "\ncomment=");
	if (dat->romcenter_credits.comment)
		fprintf(dat->out, "%s", dat->romcenter_credits.comment);

	fprintf(dat->out, "\n[DAT]");
	fprintf(dat->out, "\nversion=");
	if (dat->romcenter_dat.version)
		fprintf(dat->out, "%s", dat->romcenter_dat.version);
	fprintf(dat->out, "\nplugin=");
	if (dat->romcenter_dat.plugin)
		fprintf(dat->out, "%s", dat->romcenter_dat.plugin);
	fprintf(dat->out, "\nsplit=");
	if (dat->romcenter_dat.split)
		fprintf(dat->out, "%s", dat->romcenter_dat.split);
	fprintf(dat->out, "\nmerge=");
	if (dat->romcenter_dat.merge)
		fprintf(dat->out, "%s", dat->romcenter_dat.merge);

	fprintf(dat->out, "\n[EMULATOR]");
	fprintf(dat->out, "\nrefname=");
	if (dat->romcenter_emulator.refname)
		fprintf(dat->out, "%s", dat->romcenter_emulator.refname);
	fprintf(dat->out, "\nversion=");
	if (dat->romcenter_emulator.version)
		fprintf(dat->out, "%s", dat->romcenter_emulator.version);

	fprintf(dat->out, "\n[GAMES]");

	/* --- For all games --- */

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (curr_game->game_flags & FLAG_GAME_NAME || curr_game->game_flags & FLAG_MACHINE_NAME)
		{
			for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
			{
				if (curr_game->cloneof)
				{
					if (strchr(curr_game->cloneof, '¬'))
						invalid++;

					fprintf(dat->out, "\n¬%s¬", curr_game->cloneof);

					if (curr_game->game_cloneof)
					{
						if (strchr(curr_game->game_cloneof->description, '¬'))
							invalid++;

						fprintf(dat->out, "%s", curr_game->game_cloneof->description);
					}
					else
					{
						fprintf(dat->out, "%s (description unknown)", curr_game->cloneof);
					}
				}
				else
				{
					fprintf(dat->out, "\n¬%s¬%s", curr_game->name, curr_game->description);
				}
	
				if (strchr(curr_game->name, '¬'))
					invalid++;

				if (strchr(curr_game->description, '¬'))
					invalid++;

				fprintf(dat->out, "¬%s¬%s", curr_game->name, curr_game->description);

				if (strchr(curr_rom->name, '¬'))
					invalid++;

				fprintf(dat->out, "¬%s", curr_rom->name);

				if (!strcmp(curr_rom->status, "baddump"))
					fprintf(dat->out, "¬%08lx", (unsigned long)~curr_rom->crc);
				else
					fprintf(dat->out, "¬%08lx", (unsigned long)curr_rom->crc);
				fprintf(dat->out, "¬%lu", (unsigned long)curr_rom->size);
	
				if (curr_game->romof)
				{
					if (strchr(curr_game->romof, '¬'))
						invalid++;

					fprintf(dat->out, "¬%s", curr_game->romof);
				}
				else
				{
					fprintf(dat->out, "¬");
				}
	
				if (curr_rom->merge)
				{
					if (strchr(curr_rom->merge, '¬'))
						invalid++;

					fprintf(dat->out, "¬%s", curr_rom->merge);
				}
				else
				{
					fprintf(dat->out, "¬");
				}
	
				fprintf(dat->out, "¬");
			}
		}
	}

	if (dat->num_resources)
		fprintf(dat->out, "\n[RESOURCES]");

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (curr_game->game_flags & FLAG_RESOURCE_NAME)
		{
			for (j=0, curr_rom=curr_game->roms; j<curr_game->num_roms; j++, curr_rom++)
			{
				if (curr_game->cloneof)
				{
					fprintf(dat->out, "\n¬%s¬", curr_game->cloneof);

					if (curr_game->game_cloneof)
						fprintf(dat->out, "%s", curr_game->game_cloneof->description);
					else
						fprintf(dat->out, "%s (description unknown)", curr_game->cloneof);
				}
				else
				{
					fprintf(dat->out, "\n¬%s¬%s", curr_game->name, curr_game->description);
				}
	
				fprintf(dat->out, "¬%s¬%s", curr_game->name, curr_game->description);

				fprintf(dat->out, "¬%s", curr_rom->name);
				if (!strcmp(curr_rom->status, "baddump"))
					fprintf(dat->out, "¬%08lx", (unsigned long)~curr_rom->crc);
				else
					fprintf(dat->out, "¬%08lx", (unsigned long)curr_rom->crc);
				fprintf(dat->out, "¬%lu", (unsigned long)curr_rom->size);
	
				if (curr_game->romof)
					fprintf(dat->out, "¬%s", curr_game->romof);
				else
					fprintf(dat->out, "¬");
	
				if (curr_rom->merge)
					fprintf(dat->out, "¬%s", curr_rom->merge);
				else
					fprintf(dat->out, "¬");
	
				fprintf(dat->out, "¬");
			}
		}
	}

	if (dat->num_disks && dat->options->options & OPTION_KEEP_FULL_DETAILS)
	{
		fprintf(dat->out, "\n[DISKS]");
		dat->disk_saved=FLAG_DISK_NAME|FLAG_DISK_MERGE|FLAG_DISK_SHA1;
	}

	for (i=0, curr_game=dat->games; dat->options->options & OPTION_KEEP_FULL_DETAILS && i<dat->num_games; i++, curr_game++)
	{
		for (j=0, curr_disk=curr_game->disks; j<curr_game->num_disks; j++, curr_disk++)
		{
			if (curr_game->cloneof)
			{
				fprintf(dat->out, "\n¬%s¬", curr_game->cloneof);

				if (curr_game->game_cloneof)
					fprintf(dat->out, "%s", curr_game->game_cloneof->description);
				else
					fprintf(dat->out, "%s (description unknown)", curr_game->cloneof);
			}
			else
			{
				fprintf(dat->out, "\n¬%s¬%s", curr_game->name, curr_game->description);
			}

			fprintf(dat->out, "¬%s¬%s", curr_game->name, curr_game->description);

			fprintf(dat->out, "¬%s", curr_disk->name);

			/* --- Do not complement SHA1 information --- */
			if (curr_disk->disk_flags & FLAG_DISK_SHA1)
				fprintf(dat->out, "¬%s", curr_disk->sha1);
			else
				fprintf(dat->out, "¬");

			/* --- There is no size --- */
			fprintf(dat->out, "¬");

			if (curr_game->romof)
				fprintf(dat->out, "¬%s", curr_game->romof);
			else
				fprintf(dat->out, "¬");

			if (curr_disk->merge)
				fprintf(dat->out, "¬%s", curr_disk->merge);
			else
				fprintf(dat->out, "¬");

			fprintf(dat->out, "¬");
		}
	}

	dat->game_saved=FLAG_GAME_NAME|FLAG_MACHINE_NAME|FLAG_RESOURCE_NAME|
			FLAG_GAME_DESCRIPTION|FLAG_GAME_CLONEOF|FLAG_GAME_ROMOF;
	dat->rom_saved=FLAG_ROM_NAME|FLAG_ROM_MERGE|FLAG_ROM_SIZE|FLAG_ROM_CRC;

	if (invalid)
	{
		printf("Error - data file is invalid because some games or ROMs contain the '¬' symbol!\n");
		errflg++;
	}

	return(errflg);
}

int save_romcenter_200(struct dat *dat)
{
	return(0);
}

