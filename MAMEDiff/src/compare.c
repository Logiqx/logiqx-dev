/* --------------------------------------------------------------------------
 * MAMEDiff - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for comparing different versions of MAME to identify
 * changes required to your ROM sets.
 * -------------------------------------------------------------------------- */

/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"
#include "datlib/src/macro.h"


/* --- MAMEDiff definitions and macros --- */

#include "compare.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


/* --- Original comparison (no dat file generation) --- */

int compare_games(struct game_change *game_change, struct game *game1, struct game *game2)
{
	struct rom_idx *roms_idx1;
	struct rom_idx *roms_idx2;

	int game_flags=0, rom_flags;

	uint32_t i=0, j=0, k;

	int found, diff=0;

	if (game1 && !game2)
		game_flags|=GAME_REMOVED;

	if (!game1 && game2)
		game_flags|=GAME_ADDED;

	if (game1 && game2)
	{
		roms_idx1=game1->rom_crc_idx;
		roms_idx2=game2->rom_crc_idx;

		if (strcmp(game1->name, game2->name))
			game_flags|=GAME_RENAMED;

		if ((game1->cloneof && game2->cloneof && strcmp(game1->cloneof, game2->cloneof)) ||
			(!game1->cloneof && game2->cloneof && strcmp(game1->name, game2->cloneof)) ||
			(game1->cloneof && !game2->cloneof && strcmp(game1->cloneof, game2->name)) ||
			(!game1->cloneof && !game2->cloneof && strcmp(game1->name, game2->name)))
		{
			game_flags|=GAME_NEW_CLONE;
		}

		while (i<game1->num_roms || j<game2->num_roms)
		{
			if (i<game1->num_roms)
				game_change->rom_changes[game_change->num_rom_changes].rom1=roms_idx1[i].rom;
			else
				game_change->rom_changes[game_change->num_rom_changes].rom1=0;

			if (j<game2->num_roms)
				game_change->rom_changes[game_change->num_rom_changes].rom2=roms_idx2[j].rom;
			else
				game_change->rom_changes[game_change->num_rom_changes].rom2=0;

			rom_flags=0;

			if (i>=game1->num_roms) diff=1;
			if (j>=game2->num_roms) diff=-1;
			if (i<game1->num_roms && j<game2->num_roms)
			{
				diff=0;

				if (roms_idx2[j].rom->crc > roms_idx1[i].rom->crc)
					diff=-1;

				if (roms_idx2[j].rom->crc < roms_idx1[i].rom->crc)
					diff=1;
			}

			if (diff==0)
			{
				if (strcmp(roms_idx1[i].rom->name, roms_idx2[j].rom->name))
				{
					if (i<game1->num_roms-1 &&
						roms_idx1[i+1].rom->crc==roms_idx2[j].rom->crc &&
						strcmp(roms_idx1[i+1].rom->name, roms_idx2[j].rom->name)<=0)
					{
						if (roms_idx1[i].rom->merge)
							rom_flags|=P_ROMS_REMOVED;
						else
							rom_flags|=ROMS_REMOVED;
					}
					else if (j<game2->num_roms-1 &&
						roms_idx1[i].rom->crc==roms_idx2[j+1].rom->crc &&
						strcmp(roms_idx1[i].rom->name, roms_idx2[j+1].rom->name)>=0)
					{
						if (roms_idx2[j].rom->merge)
							rom_flags|=P_ROMS_ADDED;
						else
							rom_flags|=ROMS_ADDED;
					}
					else
					{
						if (roms_idx1[i].rom->merge)
							rom_flags|=P_ROMS_RENAMED;
						else
							rom_flags|=ROMS_RENAMED;

						if (roms_idx1[i].rom->merge && !roms_idx2[j].rom->merge)
							rom_flags|=ROMS_UNMERGED;

						if (!roms_idx1[i].rom->merge && roms_idx2[j].rom->merge)
							rom_flags|=ROMS_MERGED;
					}
				}
				else
				{
					if (roms_idx1[i].rom->merge && !roms_idx2[j].rom->merge)
						rom_flags|=ROMS_UNMERGED;

					if (!roms_idx1[i].rom->merge && roms_idx2[j].rom->merge)
						rom_flags|=ROMS_MERGED;
				}

				if (!(rom_flags & (ROMS_ADDED | P_ROMS_ADDED)))
					i++;

				if (!(rom_flags & (ROMS_REMOVED | P_ROMS_REMOVED)))
					j++;
			}

			if (diff<0)
			{
				for (found=k=0; k<game2->num_roms; k++)
				{
					if (roms_idx2[k].rom->crc==~roms_idx1[i].rom->crc)
					{
						game_change->rom_changes[game_change->num_rom_changes].rom2=roms_idx2[k].rom;

						if (roms_idx1[i].rom->merge)
							rom_flags|=P_ROMS_COMP_CRC;
						else
							rom_flags|=ROMS_COMP_CRC;

						if (roms_idx1[i].rom->merge && !roms_idx2[k].rom->merge)
							rom_flags|=ROMS_UNMERGED;

						if (!roms_idx1[i].rom->merge && roms_idx2[k].rom->merge)
							rom_flags|=ROMS_MERGED;

						if (strcmp(roms_idx1[i].rom->name, roms_idx2[k].rom->name))
						{
							if (roms_idx1[i].rom->merge)
								rom_flags|=P_ROMS_RENAMED;
							else
								rom_flags|=ROMS_RENAMED;
						}
						found=1;
					}
				}

				if (!found)
				{
					if (roms_idx1[i].rom->merge)
						rom_flags|=P_ROMS_REMOVED;
					else
						rom_flags|=ROMS_REMOVED;
				}
	
				i++;
			}

			if (diff>0)
			{
				for (found=k=0; k<game1->num_roms; k++)
					if (roms_idx1[k].rom->crc==~roms_idx2[j].rom->crc)
						found=1;

				if (!found)
				{
					if (roms_idx2[j].rom->merge)
						rom_flags|=P_ROMS_ADDED;
					else
						rom_flags|=ROMS_ADDED;
				}

				j++;
			}

			if (rom_flags)
				game_change->rom_changes[game_change->num_rom_changes++].flags=rom_flags;

			game_flags|=rom_flags;
		}
	}

	if (game_flags)
	{
		game_change->game1=game1;
		game_change->game2=game2;
		game_change->flags=game_flags;
	}

	if (game1)
		game1->flags|=PROCESSED;
	if (game2)
		game2->flags|=PROCESSED;

	return(game_flags);
}

#define COMPARE_GAMES(GAME1, GAME2) \
{ \
	if (compare_games(&game_changes[num_game_changes], GAME1, GAME2)) \
	{ \
		game_changes[num_game_changes+1].rom_changes=game_changes[num_game_changes].rom_changes+ \
			game_changes[num_game_changes].num_rom_changes; \
		num_game_changes++; \
	} \
}

int standard_compare(struct dat *dat1, struct dat *dat2, int verbose, int caesar, int set_type)
{
	struct game_change *game_changes=0;
	struct rom_change *rom_changes=0;
	struct game_idx *games_idx1, *games_idx2;
	struct game_idx *idx;
	
	int num_game_changes=0;
	int i=0, j=0;
	int namediff=0;

	FILE *out=0;
	FILE *new=0;
	FILE *grep=0;

	int errflg=0;

	if (!errflg)
		STRUCT_CALLOC(game_changes, dat1->num_games+dat2->num_games, sizeof(struct game_change))

	if (!errflg)
		STRUCT_CALLOC(rom_changes, dat1->num_roms+dat2->num_roms, sizeof(struct rom_change))

	if (!errflg)
		FOPEN(out, "mamediff.log", "w")

	if (!errflg && caesar)
		FOPEN(new, "new.dat", "w")

	if (!errflg && caesar)
		FOPEN(grep, "mapcheck.bat", "w")

	if (!errflg)
	{
		game_changes->rom_changes=rom_changes;

		games_idx1=dat1->game_name_idx; games_idx2=dat2->game_name_idx;

		while (i<dat1->num_games || j<dat2->num_games)
		{
			if (i>=dat1->num_games) namediff=1;
			if (j>=dat2->num_games) namediff=-1;
			if (i<dat1->num_games && j<dat2->num_games)
				namediff=strcmp(games_idx1[i].game->name, games_idx2[j].game->name);

			if (namediff==0)
			{
				if (games_idx1[i].game->crc!=games_idx2[j].game->crc)
				{
					idx=bsearch((const void *)&games_idx1[i].game->crc, dat2->game_crc_idx, dat2->num_games, sizeof(struct game_idx), find_game_by_crc);

					if (idx)
					{
						COMPARE_GAMES(games_idx1[i].game, idx->game)
						i++;
					}
					else
					{
						COMPARE_GAMES(games_idx1[i].game, games_idx2[j].game)
						i++; j++;
					}
				}
				else
				{
					COMPARE_GAMES(games_idx1[i].game, games_idx2[j].game)
					i++; j++;
				}
			}

			if (namediff<0)
			{
				if (games_idx1[i].game->crc)
					idx=bsearch((const void *)&games_idx1[i].game->crc, dat2->game_crc_idx, dat2->num_games, sizeof(struct game_idx), find_game_by_crc);
				else
					idx=0;

				if (idx)
				{
					COMPARE_GAMES(games_idx1[i].game, idx->game)
				}
				else
				{
					COMPARE_GAMES(games_idx1[i].game, 0)
				}
				i++;
			}

			if (namediff>0)
				j++;
		}

		for (i=0; i<dat2->num_games; i++)
		{
			if (!(games_idx2[i].game->flags & PROCESSED))
				COMPARE_GAMES(0, games_idx2[i].game)
		}

		for (i=j=0; caesar && i<num_game_changes; i++)
		{
			if (game_changes[i].flags & GAME_ADDED)
			{
				while (strcmp(games_idx2[j].game->name, game_changes[i].game2->name))
					j++;
				print_game(new, games_idx2[j].game);
			}
		}

		for (i=j=0; caesar && i<num_game_changes; i++)
		{
			if ((game_changes[i].flags & GAME_RENAMED) ||
				(game_changes[i].flags & GAME_REMOVED))
			{
				while (strcmp(games_idx1[j].game->name, game_changes[i].game1->name))
					j++;
				fprintf(grep, "grep \"%s,m$\" */*.map\n", games_idx1[j].game->name);
			}
		}

		if (set_type==0)
		{
			report_game_changes(out,
				GAME_REMOVED,
				" Game removals ",
				0, 0, game_changes, num_game_changes, verbose);

			report_game_changes(out,
				GAME_NEW_CLONE|GAME_RENAMED|
				ROMS_RENAMED|ROMS_MERGED|ROMS_UNMERGED|ROMS_REMOVED|
				P_ROMS_RENAMED|P_ROMS_REMOVED|
				ROMS_COMP_CRC|P_ROMS_COMP_CRC,
				" Games affected by set reorganisation ",
				0, 0, game_changes, num_game_changes, verbose);

			report_game_changes(out,
				ROMS_ADDED|P_ROMS_ADDED,
				" Games requiring additional ROMs ",
				dat1->rom_crc_idx, dat1->num_roms, game_changes, num_game_changes, verbose);

			report_game_changes(out,
				GAME_ADDED,
				" Game additions ",
				0, 0, game_changes, num_game_changes, verbose);
		}
	
		if (set_type==OPTION_DAT_FULL_MERGING)
		{
			errflg=report_required_rebuilds(out, dat1, 0,
				GAME_NEW_CLONE|GAME_REMOVED|
				ROMS_RENAMED|ROMS_REMOVED,
				" Merged set changes (just rebuild the ZIPs) ",
				game_changes, num_game_changes);
		}

		if (set_type==OPTION_DAT_SPLIT_MERGING)
		{
			errflg=report_required_rebuilds(out, dat1,
				GAME_RENAMED|GAME_REMOVED|
				ROMS_RENAMED|ROMS_MERGED|ROMS_REMOVED, ROMS_UNMERGED,
				" Split set changes (just rebuild the ZIPs) ",
				game_changes, num_game_changes);
		}

		if (set_type==OPTION_DAT_NO_MERGING)
		{
			errflg=report_required_rebuilds(out, dat1,
				GAME_RENAMED|GAME_REMOVED|
				ROMS_RENAMED|ROMS_REMOVED|
				P_ROMS_RENAMED|P_ROMS_REMOVED, 0,
				" Non-merged set changes (just rebuild the ZIPs) ",
				game_changes, num_game_changes);
		}

		if (set_type!=0)
		{
			report_required_roms(out, ROMS_ADDED|P_ROMS_ADDED,
				" Games requiring new/fixed ROMs (visit SYS2064!) ",
				game_changes, num_game_changes);

			report_required_roms(out, GAME_ADDED,
				" Game additions (new ROMs required) ",
				game_changes, num_game_changes);
		}

		if (num_game_changes)
			printf("Report has been written to mamediff.log\n");
		else
			printf("No differences found\n");
	}

	if (grep) fclose(grep);
	if (new) fclose(new);
	if (out) fclose(out);

	FREE(rom_changes)
	FREE(game_changes)

	return(errflg);
}

void report_game_changes(FILE *out, unsigned long flags, char *description,
	struct rom_idx *rom_crc_idx, long num_roms,
	struct game_change *game_changes, int num_game_changes, int verbose)
{
	int i, j, k;
	char st[MAX_STRING_LENGTH];

	for (i=j=0; i<num_game_changes; i++)
	{
		if (game_changes[i].flags & (flags))
		{	
			if (!j++)
			{
				LRPAD(st, description, "-", 80)
				fprintf(out, "%s\n\n", st);
			}

			if ((game_changes[i].flags & GAME_RENAMED) ||
				(game_changes[i].flags & GAME_NEW_CLONE) ||
				(game_changes[i].flags & GAME_REMOVED))
			{
				FORMAT_GAME_NAME(st, game_changes[i].game1)
				fprintf(out, "< %s\n", st);
			}
			else if (!(game_changes[i].flags & GAME_ADDED))
			{
				FORMAT_GAME_NAME(st, game_changes[i].game1)
				fprintf(out, "%s\n", st);
			}

			if ((game_changes[i].flags & GAME_RENAMED) ||
				(game_changes[i].flags & GAME_NEW_CLONE) ||
				(game_changes[i].flags & GAME_ADDED))
			{
				FORMAT_GAME_NAME(st, game_changes[i].game2)
				fprintf(out, "> %s\n", st);
			}

			for (k=0; verbose && k<game_changes[i].num_rom_changes; k++)
			{
				if (((game_changes[i].rom_changes[k].flags & ROMS_RENAMED) ||
					(game_changes[i].rom_changes[k].flags & P_ROMS_RENAMED) ||
					(game_changes[i].rom_changes[k].flags & ROMS_COMP_CRC) ||
					(game_changes[i].rom_changes[k].flags & P_ROMS_COMP_CRC) ||
					(game_changes[i].rom_changes[k].flags & ROMS_REMOVED) ||
					(game_changes[i].rom_changes[k].flags & P_ROMS_REMOVED) ||
					(game_changes[i].rom_changes[k].flags & ROMS_MERGED) ||
					(game_changes[i].rom_changes[k].flags & ROMS_UNMERGED)) &&
					!(flags & ROMS_ADDED))
				{
					FORMAT_ROM_NAME(st, game_changes[i].rom_changes[k].rom1)
					fprintf(out, "< %s\n", st);
				}

				if (((game_changes[i].rom_changes[k].flags & ROMS_RENAMED) ||
					(game_changes[i].rom_changes[k].flags & P_ROMS_RENAMED) ||
					(game_changes[i].rom_changes[k].flags & ROMS_COMP_CRC) ||
					(game_changes[i].rom_changes[k].flags & P_ROMS_COMP_CRC) ||
					(game_changes[i].rom_changes[k].flags & ROMS_MERGED) ||
					(game_changes[i].rom_changes[k].flags & ROMS_UNMERGED)) &&
					!(flags & ROMS_ADDED))
				{
					FORMAT_ROM_NAME(st, game_changes[i].rom_changes[k].rom2)
					fprintf(out, "> %s\n", st);
				}

				if (((game_changes[i].rom_changes[k].flags & ROMS_ADDED) &&
					(flags & ROMS_ADDED)) ||
					((game_changes[i].rom_changes[k].flags & P_ROMS_ADDED) &&
					(flags & P_ROMS_ADDED)))
				{
					FORMAT_ROM_NAME(st, game_changes[i].rom_changes[k].rom2)
					fprintf(out, "> %s", st);

					if (game_changes[i].rom_changes[k].rom2->rom_flags & FLAG_ROM_NODUMP)
						fprintf(out, " *just ignore\n");
					else if (bsearch((const void *)&game_changes[i].rom_changes[k].rom2->crc, rom_crc_idx, num_roms, sizeof(struct rom_idx), find_rom_by_crc))
						fprintf(out, " *already in MAME\n");
					else if (bsearch((const void *)&game_changes[i].rom_changes[k].rom2->crc, rom_crc_idx, num_roms, sizeof(struct rom_idx), find_rom_by_comp_crc))
						fprintf(out, " *already in MAME\n");
					else
						fprintf(out, "\n");
				}
			}

			if (!verbose && (flags & game_changes[i].flags &
				(ROMS_RENAMED|P_ROMS_RENAMED|
				ROMS_REMOVED|P_ROMS_REMOVED|
				ROMS_COMP_CRC|P_ROMS_COMP_CRC|
				ROMS_ADDED|P_ROMS_ADDED|
				ROMS_MERGED|ROMS_UNMERGED)))
			{
				k=0;
				fprintf(out, "Changes: ");
				
				if (flags & game_changes[i].flags & ROMS_RENAMED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM renames");
				}

				if (flags & game_changes[i].flags & P_ROMS_RENAMED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM renames (in parent)");
				}

				if (flags & game_changes[i].flags & ROMS_COMP_CRC)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "complemented CRCs");
				}

				if (flags & game_changes[i].flags & P_ROMS_COMP_CRC)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "complemented CRCs (in parent)");
				}

				if (flags & game_changes[i].flags & ROMS_REMOVED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM removals");
				}

				if (flags & game_changes[i].flags & P_ROMS_REMOVED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM removals (in parent)");
				}

				if (flags & game_changes[i].flags & ROMS_ADDED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM additions");
				}

				if (flags & game_changes[i].flags & P_ROMS_ADDED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM additions (in parent)");
				}

				if (flags & game_changes[i].flags & (ROMS_MERGED|ROMS_UNMERGED))
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM merge details");
				}

				fprintf(out, "\n");
			}

			if (!(game_changes[i].flags & (GAME_REMOVED|GAME_ADDED)))
				fprintf(out, "\n");
		}
	}

	if (j && (flags & (GAME_REMOVED|GAME_ADDED)))
		fprintf(out, "\n");
}

void report_required_roms(FILE *out, unsigned long flags, char *description,
	struct game_change *game_changes, int num_game_changes)
{
	int i, j;
	char st[MAX_STRING_LENGTH];

	for (i=j=0; i<num_game_changes; i++)
	{
		if (game_changes[i].flags & (flags))
		{	
			if (!j++)
			{
				LRPAD(st, description, "-", 80)
				fprintf(out, "%s\n\n", st);
			}

			FORMAT_GAME_NAME(st, game_changes[i].game2)

			fprintf(out, "%s\n", st);
		}
	}
	if (j) fprintf(out, "\n");
}

int report_required_rebuilds(FILE *out, struct dat *dat, int child_flags, int parent_flags, char *description,
	struct game_change *game_changes, int num_game_changes)
{
	struct game_idx *rebuild_list=0;
	int num_rebuilds=0;
	int i, j, found;

	char st[MAX_STRING_LENGTH];

	int errflg=0;

	STRUCT_CALLOC(rebuild_list, dat->num_games, sizeof(struct game_idx))

	for (i=0; !errflg && i<num_game_changes; i++)
	{
		if (game_changes[i].flags & (child_flags))
		{
			found=j=0;

			while (!found && j<num_rebuilds)
			{
				if (!strcmp(rebuild_list[j].game->name, game_changes[i].game1->name))
					found++;
				j++;
			}

			if (!found)
				rebuild_list[num_rebuilds++].game=game_changes[i].game1;
		}
	}

	for (i=0; !errflg && i<num_game_changes; i++)
	{
		if (game_changes[i].flags & (parent_flags))
		{
			found=j=0;

			while (!found && j<num_rebuilds)
			{
				if (game_changes[i].game1->cloneof && !strcmp(rebuild_list[j].game->name, game_changes[i].game1->cloneof))
					found++;
				else if (!strcmp(rebuild_list[j].game->name, game_changes[i].game1->name))
					found++;
				j++;
			}

			if (!found)
			{
				if (game_changes[i].game1->parent)
					rebuild_list[num_rebuilds++].game=game_changes[i].game1->parent;
				else
					rebuild_list[num_rebuilds++].game=game_changes[i].game1;
			}
		}
	}

	if (num_rebuilds)
	{
		qsort(rebuild_list, num_rebuilds, sizeof(struct game_idx), game_name_idx_sort_function);

		LRPAD(st, description, "-", 80)
		fprintf(out, "%s\n\n", st);

		for (i=0; i<num_rebuilds; i++)
			fprintf(out, "%s [rebuild %s.zip]\n", rebuild_list[i].game->description, rebuild_list[i].game->name);

		fprintf(out, "\n");
	}

	FREE(rebuild_list)

	return(errflg);
}

void print_game(FILE *new, struct game *game)
{
	int i;

	if (game->game_flags & FLAG_RESOURCE_NAME)
	{
		fprintf(new, "resource (\n");
		fprintf(new, "\tname %s\n", game->name);
		fprintf(new, "\tdescription \"%s\"\n", game->description);
		if (game->year)
			fprintf(new, "\tyear %s\n", game->year);
		if (game->manufacturer)
			fprintf(new, "\tmanufacturer \"%s\"\n", game->manufacturer);
	}
	else
	{
		fprintf(new, "game (\n");
		fprintf(new, "\tname %s\n", game->name);
		fprintf(new, "\tdescription \"%s\"\n", game->description);
		if (game->year)
			fprintf(new, "\tyear %s\n", game->year);
		if (game->manufacturer)
			fprintf(new, "\tmanufacturer \"%s\"\n", game->manufacturer);
	}

	for (i=0; i<game->num_roms; i++)
	{
		if (game->cloneof && game->roms[i].merge)
		{
			fprintf(new, "\trom ( name %s merge %s size %lu ", game->roms[i].name, game->roms[i].merge, (unsigned long) game->roms[i].size);

			if (game->roms[i].crc)
				fprintf(new, "crc %08lx ", (unsigned long) game->roms[i].crc);
			else
				fprintf(new, "flags nodump ");

			fprintf(new, ")\n");
		}
		else
		{
			fprintf(new, "\trom ( name %s size %lu ", game->roms[i].name, (unsigned long) game->roms[i].size);

			if (game->roms[i].crc)
				fprintf(new, "crc %08lx ", (unsigned long) game->roms[i].crc);
			else
				fprintf(new, "flags nodump ");

			fprintf(new, ")\n");
		}
	}

	fprintf(new, ")\n\n");
}
