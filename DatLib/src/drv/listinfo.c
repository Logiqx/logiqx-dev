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

extern const struct token tokens[];


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
			BUFFER2_PUT_TOKEN(TOKEN_GAME_COMMENT)
			TOKEN[0]='\0';
		}

		/* --- Elements of a ClrMamePro header that we are interested in --- */

		if (game_type==FLAG_CLRMAMEPRO_HEADER)
		{
			if (!strcmp(TOKEN, "name"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_CLRMAMEPRO_NAME)
			}

			else if (!strcmp(TOKEN, "description"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_CLRMAMEPRO_DESCRIPTION)
			}

			else if (!strcmp(TOKEN, "category"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_CLRMAMEPRO_CATEGORY)
			}

			else if (!strcmp(TOKEN, "version"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_CLRMAMEPRO_VERSION)
			}

			else if (!strcmp(TOKEN, "author"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_CLRMAMEPRO_AUTHOR)
			}

			else if (!strcmp(TOKEN, "forcemerging"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_CLRMAMEPRO_FORCEMERGING)
			}

			else if (!strcmp(TOKEN, "forcezipping"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_CLRMAMEPRO_FORCEZIPPING)
			}
		}

		/* --- Elements of a game that we are interested in --- */

		else if (game_type==FLAG_GAME_NAME)
		{
			if (!strcmp(TOKEN, "name"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_NAME)
			}

			else if (!strcmp(TOKEN, "description"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_DESCRIPTION)
			}

			else if (!strcmp(TOKEN, "year"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_YEAR)
			}

			else if (!strcmp(TOKEN, "manufacturer"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_MANUFACTURER)
			}
	
			else if (!strcmp(TOKEN, "rebuildto"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_REBUILDTO)
			}
	
			else if (!strcmp(TOKEN, "cloneof"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_CLONEOF)
			}

			else if (!strcmp(TOKEN, "romof"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_ROMOF)
			}

			else if (!strcmp(TOKEN, "sampleof"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_GAME_SAMPLEOF)
			}
		}

		/* --- Elements of a resource that we are interested in --- */

		else if (game_type==FLAG_RESOURCE_NAME)
		{
			if (!strcmp(TOKEN, "name"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_NAME)
			}

			else if (!strcmp(TOKEN, "description"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_DESCRIPTION)
			}

			else if (!strcmp(TOKEN, "year"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_YEAR)
			}

			else if (!strcmp(TOKEN, "manufacturer"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_MANUFACTURER)
			}

			else if (!strcmp(TOKEN, "rebuildto"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_RESOURCE_REBUILDTO)
			}
		}

		/* --- Elements of a machine that we are interested in --- */

		else if (game_type==FLAG_MACHINE_NAME)
		{
			if (!strcmp(TOKEN, "name"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_MACHINE_NAME)
			}

			else if (!strcmp(TOKEN, "description"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_MACHINE_DESCRIPTION)
			}

			else if (!strcmp(TOKEN, "year"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_MACHINE_YEAR)
			}

			else if (!strcmp(TOKEN, "manufacturer"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_MACHINE_MANUFACTURER)
			}

			else if (!strcmp(TOKEN, "rebuildto"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_MACHINE_REBUILDTO)
			}

			else if (!strcmp(TOKEN, "cloneof"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_MACHINE_CLONEOF)
			}

			else if (!strcmp(TOKEN, "romof"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_MACHINE_ROMOF)
			}

			else if (!strcmp(TOKEN, "sampleof"))
			{
				BUFFER1_GET_TOKEN
				BUFFER2_PUT_TOKEN(TOKEN_MACHINE_SAMPLEOF)
			}
		}

		/* --- Elements of a rom that we are interested in --- */

		if ((game_type==FLAG_GAME_NAME || game_type==FLAG_RESOURCE_NAME || game_type==FLAG_MACHINE_NAME) &&
		     !strcmp(TOKEN, "rom"))
		{
			while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
			{
				BUFFER1_GET_TOKEN

				if (!strcmp(TOKEN, "name"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_ROM_NAME)
				}

				else if (!strcmp(TOKEN, "merge"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_ROM_MERGE)
				}

				else if (!strcmp(TOKEN, "size"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_ROM_SIZE)
				}

				else if (!strcmp(TOKEN, "crc") || !strcmp(TOKEN, "crc32"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_ROM_CRC)
				}

				else if (!strcmp(TOKEN, "md5"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_ROM_MD5)
				}

				else if (!strcmp(TOKEN, "sha1"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_ROM_SHA1)
				}

				else if (!strcmp(TOKEN, "region"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_ROM_REGION)
				}

				else if (!strcmp(TOKEN, "flags"))
				{
					BUFFER1_GET_TOKEN

					if (!strcmp(TOKEN, "baddump") || !strcmp(TOKEN, "nodump"))
						BUFFER2_PUT_TOKEN(TOKEN_ROM_FLAGS)
				}

				/* --- Support the bad syntax of MAME v0.68 --- */

				else if (!strcmp(TOKEN, "baddump") || !strcmp(TOKEN, "nodump"))
					BUFFER2_PUT_TOKEN(TOKEN_ROM_FLAGS)
			}
		}

		/* --- Elements of a disk that we are interested in --- */

		else if ((game_type==FLAG_GAME_NAME || game_type==FLAG_RESOURCE_NAME || game_type==FLAG_MACHINE_NAME) &&
		          !strcmp(TOKEN, "disk"))
		{
			while (strchr(BUFFER1_PTR, ')') && BUFFER1_REMAINING && strcmp(TOKEN, ")"))
			{
				BUFFER1_GET_TOKEN

				if (!strcmp(TOKEN, "name"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_DISK_NAME)
				}

				else if (!strcmp(TOKEN, "md5"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_DISK_MD5)
				}

				else if (!strcmp(TOKEN, "sha1"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_DISK_SHA1)
				}

				else if (!strcmp(TOKEN, "region"))
				{
					BUFFER1_GET_TOKEN
					BUFFER2_PUT_TOKEN(TOKEN_DISK_REGION)
				}

			}
		}

		/* --- Elements of a sample that we are interested in --- */

		else if ((game_type==FLAG_GAME_NAME || game_type==FLAG_RESOURCE_NAME || game_type==FLAG_MACHINE_NAME) &&
		          !strcmp(TOKEN, "sample"))
		{
			BUFFER1_GET_TOKEN
			BUFFER2_PUT_TOKEN(TOKEN_SAMPLE_NAME)
		}

		BUFFER1_ADVANCE_LINE
	}

	return(errflg);
}


int load_mess_listinfo(struct dat *dat)
{
	return(load_mame_listinfo(dat));
}


/* --- Save --- */

int save_mame_listinfo(struct dat *dat)
{
	struct game *curr_game=0;
	struct comment *curr_comment=0;
	struct rom *curr_rom=0;
	struct disk *curr_disk=0;
	struct sample *curr_sample=0;

	uint32_t i, j;
	int errflg=0;

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

	/* --- Debugging provides a complete output of actual dat structure --- */

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

	for (i=0, curr_game=dat->games; i<dat->num_games; i++, curr_game++)
	{
		if (curr_game->comments!=0)
		{
			for (j=0, curr_comment=curr_game->comments; j<dat->games[i].num_comments; j++, curr_comment++)
				fprintf(dat->out, "//%s\n", curr_comment->comment);

			fprintf(dat->out, "\n");
		}

		if (curr_game->game_flags & FLAG_GAME_NAME)
			fprintf(dat->out, "game (\n");
		else if (curr_game->game_flags & FLAG_RESOURCE_NAME)
			fprintf(dat->out, "resource (\n");
		else if (curr_game->game_flags & FLAG_MACHINE_NAME)
			fprintf(dat->out, "machine (\n");

		if (strchr(curr_game->name, ' '))
			fprintf(dat->out, "\tname \"%s\"\n", curr_game->name);
		else
			fprintf(dat->out, "\tname %s\n", curr_game->name);

		if (curr_game->description!=0)
			fprintf(dat->out, "\tdescription \"%s\"\n", curr_game->description);

		if (curr_game->year!=0)
		{
			if (strchr(curr_game->year, ' '))
				fprintf(dat->out, "\tyear \"%s\"\n", curr_game->year);
			else
				fprintf(dat->out, "\tyear %s\n", curr_game->year);
		}

		if (curr_game->manufacturer!=0)
			fprintf(dat->out, "\tmanufacturer \"%s\"\n", curr_game->manufacturer);

		if (curr_game->cloneof!=0)
		{
			if (strchr(curr_game->cloneof, ' '))
				fprintf(dat->out, "\tcloneof \"%s\"\n", curr_game->cloneof);
			else
				fprintf(dat->out, "\tcloneof %s\n", curr_game->cloneof);
		}

		if (curr_game->romof!=0)
		{
			if (strchr(curr_game->romof, ' '))
				fprintf(dat->out, "\tromof \"%s\"\n", curr_game->romof);
			else
				fprintf(dat->out, "\tromof %s\n", curr_game->romof);
		}

		if (curr_game->rebuildto!=0)
		{
			if (strchr(curr_game->rebuildto, ' '))
				fprintf(dat->out, "\trebuildto \"%s\"\n", curr_game->rebuildto);
			else
				fprintf(dat->out, "\trebuildto %s\n", curr_game->rebuildto);
		}

		for (j=0, curr_rom=curr_game->roms; j<dat->games[i].num_roms; j++, curr_rom++)
		{
			if (strchr(curr_rom->name, ' '))
				fprintf(dat->out, "\trom ( name \"%s\" ", curr_rom->name);
			else
				fprintf(dat->out, "\trom ( name %s ", curr_rom->name);

			if (curr_rom->merge!=0)
			{
				if (strchr(curr_rom->merge, ' '))
					fprintf(dat->out, "merge \"%s\" ", curr_rom->merge);
				else
					fprintf(dat->out, "merge %s ", curr_rom->merge);
			}

			fprintf(dat->out, "size %ld ", (unsigned long) curr_rom->size);

			if (curr_rom->crc!=0)
				fprintf(dat->out, "crc %08lx ", (unsigned long) curr_rom->crc);

			if (curr_rom->sha1!=0)
				fprintf(dat->out, "sha1 %s ", curr_rom->sha1);

			if (curr_rom->md5!=0)
				fprintf(dat->out, "md5 %s ", curr_rom->md5);

			if (curr_rom->region!=0)
				fprintf(dat->out, "region %s ", curr_rom->region);

			if (curr_rom->rom_flags & FLAG_ROM_BADDUMP)
				fprintf(dat->out, "flags baddump ");

			if (curr_rom->rom_flags & FLAG_ROM_NODUMP)
				fprintf(dat->out, "flags nodump ");

			fprintf(dat->out, ")\n");
		}

		for (j=0, curr_disk=curr_game->disks; j<dat->games[i].num_disks; j++, curr_disk++)
		{
			if (strchr(curr_disk->name, ' '))
				fprintf(dat->out, "\tdisk ( name \"%s\" ", curr_disk->name);
			else
				fprintf(dat->out, "\tdisk ( name %s ", curr_disk->name);

			if (curr_disk->sha1!=0)
				fprintf(dat->out, "sha1 %s ", curr_disk->sha1);

			if (curr_disk->md5!=0)
				fprintf(dat->out, "md5 %s ", curr_disk->md5);

			if (curr_disk->region!=0)
				fprintf(dat->out, "region %s ", curr_disk->region);

			fprintf(dat->out, ")\n");
		}

		if (curr_game->sampleof!=0)
		{
			if (strchr(curr_game->sampleof, ' '))
				fprintf(dat->out, "\tsampleof \"%s\"\n", curr_game->sampleof);
			else
				fprintf(dat->out, "\tsampleof %s\n", curr_game->sampleof);
		}

		for (j=0, curr_sample=curr_game->samples; j<dat->games[i].num_samples; j++, curr_sample++)
		{
			if (strchr(curr_sample->name, ' '))
				fprintf(dat->out, "\tsample \"%s\"\n", curr_sample->name);
			else
				fprintf(dat->out, "\tsample %s\n", curr_sample->name);
		}

		fprintf(dat->out, ")\n\n");
	}

	dat->game_saved=FLAG_GAME_NAME|FLAG_RESOURCE_NAME|FLAG_MACHINE_NAME|FLAG_GAME_DESCRIPTION|FLAG_GAME_YEAR|
		        FLAG_GAME_MANUFACTURER|FLAG_GAME_REBUILDTO|FLAG_GAME_CLONEOF|FLAG_GAME_ROMOF|FLAG_GAME_SAMPLEOF|
			FLAG_GAME_COMMENTS;
	dat->rom_saved=FLAG_ROM_NAME|FLAG_ROM_MERGE|FLAG_ROM_SIZE|FLAG_ROM_CRC|FLAG_ROM_MD5|FLAG_ROM_SHA1|
	               FLAG_ROM_REGION|FLAG_ROM_BADDUMP|FLAG_ROM_NODUMP|FLAG_ROM_FUNNYSIZE|FLAG_ROM_BIOS;
	dat->disk_saved=FLAG_DISK_NAME|FLAG_DISK_MD5|FLAG_DISK_SHA1|FLAG_DISK_REGION;
	dat->sample_saved=FLAG_SAMPLE_NAME;

	return(errflg);
}

int save_mess_listinfo(struct dat *dat)
{
	return(0);
}
