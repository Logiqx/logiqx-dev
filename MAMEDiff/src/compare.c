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

int compare_games(struct game_change *game_change, struct game *game1, struct game *game2, int set_type)
{
	struct rom_idx *roms_idx1, *roms_idx2;
	struct disk_idx *disks_idx1, *disks_idx2;
	struct sample_idx *samples_idx1, *samples_idx2;

	uint16_t game_flags=0;
	uint16_t game_rom_flags=0, rom_flags=0;
	uint8_t game_disk_flags=0, disk_flags=0;
	uint8_t game_sample_flags=0, sample_flags=0;

	uint32_t i, j, k;

	int found, diff=0;

	if (game1 && !game2)
		game_flags|=GAME_REMOVED;

	if (!game1 && game2)
		game_flags|=GAME_ADDED;

	if (game1 && game2)
	{
		roms_idx1=game1->rom_crc_idx;
		roms_idx2=game2->rom_crc_idx;

		disks_idx1=game1->disk_crc_idx;
		disks_idx2=game2->disk_crc_idx;

		samples_idx1=game1->sample_name_idx;
		samples_idx2=game2->sample_name_idx;

		if (strcmp(game1->name, game2->name))
			game_flags|=GAME_RENAMED;

		if ((game1->cloneof && game2->cloneof && strcmp(game1->cloneof, game2->cloneof)) ||
			(!game1->cloneof && game2->cloneof && strcmp(game1->name, game2->cloneof)) ||
			(game1->cloneof && !game2->cloneof && strcmp(game1->cloneof, game2->name)) ||
			(!game1->cloneof && !game2->cloneof && strcmp(game1->name, game2->name)))
		{
			game_flags|=GAME_NEW_CLONE;
		}

		i=j=0;

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
							rom_flags|=P_ROM_REMOVED;
						else
							rom_flags|=ROM_REMOVED;
					}
					else if (j<game2->num_roms-1 &&
						roms_idx1[i].rom->crc==roms_idx2[j+1].rom->crc &&
						strcmp(roms_idx1[i].rom->name, roms_idx2[j+1].rom->name)>=0)
					{
						if (roms_idx2[j].rom->merge)
							rom_flags|=P_ROM_ADDED;
						else
							rom_flags|=ROM_ADDED;
					}
					else
					{
						if (roms_idx1[i].rom->merge)
							rom_flags|=P_ROM_RENAMED;
						else
							rom_flags|=ROM_RENAMED;

						if (roms_idx1[i].rom->merge && !roms_idx2[j].rom->merge)
							rom_flags|=ROM_UNMERGED;

						if (!roms_idx1[i].rom->merge && roms_idx2[j].rom->merge)
							rom_flags|=ROM_MERGED;
					}
				}
				else
				{
					if (roms_idx1[i].rom->merge && !roms_idx2[j].rom->merge)
						rom_flags|=ROM_UNMERGED;

					if (!roms_idx1[i].rom->merge && roms_idx2[j].rom->merge)
						rom_flags|=ROM_MERGED;
				}

				if (!(rom_flags & (ROM_ADDED | P_ROM_ADDED)))
					i++;

				if (!(rom_flags & (ROM_REMOVED | P_ROM_REMOVED)))
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
							rom_flags|=P_ROM_COMP_CRC;
						else
							rom_flags|=ROM_COMP_CRC;

						if (roms_idx1[i].rom->merge && !roms_idx2[k].rom->merge)
							rom_flags|=ROM_UNMERGED;

						if (!roms_idx1[i].rom->merge && roms_idx2[k].rom->merge)
							rom_flags|=ROM_MERGED;

						if (strcmp(roms_idx1[i].rom->name, roms_idx2[k].rom->name))
						{
							if (roms_idx1[i].rom->merge)
								rom_flags|=P_ROM_RENAMED;
							else
								rom_flags|=ROM_RENAMED;
						}
						found=1;
					}
				}

				if (!found)
				{
					if (roms_idx1[i].rom->merge)
						rom_flags|=P_ROM_REMOVED;
					else
						rom_flags|=ROM_REMOVED;
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
						rom_flags|=P_ROM_ADDED;
					else
						rom_flags|=ROM_ADDED;
				}

				j++;
			}

			if (rom_flags)
			{
				game_change->rom_changes[game_change->num_rom_changes++].rom_flags=rom_flags;
				game_rom_flags|=rom_flags;
			}
		}

		i=j=0;

		while (set_type==0 && (i<game1->num_disks || j<game2->num_disks))
		{
			if (i<game1->num_disks)
				game_change->disk_changes[game_change->num_disk_changes].disk1=disks_idx1[i].disk;
			else
				game_change->disk_changes[game_change->num_disk_changes].disk1=0;

			if (j<game2->num_disks)
				game_change->disk_changes[game_change->num_disk_changes].disk2=disks_idx2[j].disk;
			else
				game_change->disk_changes[game_change->num_disk_changes].disk2=0;

			disk_flags=0;

			if (i>=game1->num_disks) diff=1;
			if (j>=game2->num_disks) diff=-1;
			if (i<game1->num_disks && j<game2->num_disks)
			{
				diff=0;

				if (disks_idx2[j].disk->crc > disks_idx1[i].disk->crc)
					diff=-1;

				if (disks_idx2[j].disk->crc < disks_idx1[i].disk->crc)
					diff=1;
			}

			if (diff==0)
			{
				if (strcmp(disks_idx1[i].disk->name, disks_idx2[j].disk->name))
				{
					if (i<game1->num_disks-1 &&
						disks_idx1[i+1].disk->crc==disks_idx2[j].disk->crc &&
						strcmp(disks_idx1[i+1].disk->name, disks_idx2[j].disk->name)<=0)
					{
						disk_flags|=DISK_REMOVED;
					}
					else if (j<game2->num_disks-1 &&
						disks_idx1[i].disk->crc==disks_idx2[j+1].disk->crc &&
						strcmp(disks_idx1[i].disk->name, disks_idx2[j+1].disk->name)>=0)
					{
						disk_flags|=DISK_ADDED;
					}
					else
					{
						disk_flags|=DISK_RENAMED;
					}
				}

				if (!(disk_flags & DISK_ADDED))
					i++;

				if (!(disk_flags & DISK_REMOVED))
					j++;
			}

			if (diff<0)
			{
				disk_flags|=DISK_REMOVED;
				i++;
			}

			if (diff>0)
			{
				disk_flags|=DISK_ADDED;
				j++;
			}

			if (disk_flags)
			{
				game_change->disk_changes[game_change->num_disk_changes++].disk_flags=disk_flags;
				game_disk_flags|=disk_flags;
			}
		}
		i=j=0;

		while (set_type==0 && (i<game1->num_samples || j<game2->num_samples))
		{
			if (i<game1->num_samples)
				game_change->sample_changes[game_change->num_sample_changes].sample1=samples_idx1[i].sample;
			else
				game_change->sample_changes[game_change->num_sample_changes].sample1=0;

			if (j<game2->num_samples)
				game_change->sample_changes[game_change->num_sample_changes].sample2=samples_idx2[j].sample;
			else
				game_change->sample_changes[game_change->num_sample_changes].sample2=0;

			sample_flags=0;

			if (i>=game1->num_samples) diff=1;
			if (j>=game2->num_samples) diff=-1;
			if (i<game1->num_samples && j<game2->num_samples)
				diff=strcmp(samples_idx1[j].sample->name, samples_idx2[i].sample->name);

			if (diff==0)
			{
				i++;
				j++;
			}

			if (diff<0)
			{
				sample_flags|=SAMPLE_REMOVED;
				i++;
			}

			if (diff>0)
			{
				sample_flags|=SAMPLE_ADDED;
				j++;
			}

			if (sample_flags)
			{
				game_change->sample_changes[game_change->num_sample_changes++].sample_flags=sample_flags;
				game_sample_flags|=sample_flags;
			}
		}
	}

	if (game_flags || game_rom_flags || game_disk_flags || game_sample_flags)
	{
		game_change->game1=game1;
		game_change->game2=game2;
		game_change->game_flags=game_flags;
		game_change->rom_flags=game_rom_flags;
		game_change->disk_flags=game_disk_flags;
		game_change->sample_flags=game_sample_flags;
	}

	if (game1)
		game1->flags|=PROCESSED;
	if (game2)
		game2->flags|=PROCESSED;

	return(game_flags|game_rom_flags|game_disk_flags|game_sample_flags);
}

#define COMPARE_GAMES(GAME1, GAME2) \
{ \
	if (compare_games(&game_changes[num_game_changes], GAME1, GAME2, set_type)) \
	{ \
		game_changes[num_game_changes+1].rom_changes=game_changes[num_game_changes].rom_changes+ \
			game_changes[num_game_changes].num_rom_changes; \
		game_changes[num_game_changes+1].disk_changes=game_changes[num_game_changes].disk_changes+ \
			game_changes[num_game_changes].num_disk_changes; \
		game_changes[num_game_changes+1].sample_changes=game_changes[num_game_changes].sample_changes+ \
			game_changes[num_game_changes].num_sample_changes; \
		num_game_changes++; \
	} \
}

int standard_compare(struct dat *dat1, struct dat *dat2, int verbose, int caesar, int set_type)
{
	struct game_change *game_changes=0;
	struct rom_change *rom_changes=0;
	struct disk_change *disk_changes=0;
	struct sample_change *sample_changes=0;
	struct game_idx *games_idx1, *games_idx2;
	struct game_idx *idx;
	
	uint32_t num_game_changes=0;

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
		STRUCT_CALLOC(disk_changes, dat1->num_disks+dat2->num_disks, sizeof(struct disk_change))

	if (!errflg)
		STRUCT_CALLOC(sample_changes, dat1->num_samples+dat2->num_samples, sizeof(struct sample_change))

	if (!errflg)
		FOPEN(out, "mamediff.log", "w")

	if (!errflg && caesar)
		FOPEN(new, "new.dat", "w")

	if (!errflg && caesar)
		FOPEN(grep, "mapcheck.bat", "w")

	if (!errflg)
	{
		game_changes->rom_changes=rom_changes;
		game_changes->disk_changes=disk_changes;
		game_changes->sample_changes=sample_changes;

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
			if (game_changes[i].game_flags & GAME_ADDED)
			{
				while (strcmp(games_idx2[j].game->name, game_changes[i].game2->name))
					j++;
				print_game(new, games_idx2[j].game);
			}
		}

		for (i=j=0; caesar && i<num_game_changes; i++)
		{
			if ((game_changes[i].game_flags & GAME_RENAMED) ||
				(game_changes[i].game_flags & GAME_REMOVED))
			{
				while (strcmp(games_idx1[j].game->name, game_changes[i].game1->name))
					j++;
				fprintf(grep, "grep \"%s,m$\" */*.map\n", games_idx1[j].game->name);
			}
		}

		if (set_type==0)
		{
			report_game_changes(out,
				GAME_REMOVED, 0, 0, 0,
				" Game removals ",
				dat1, game_changes, num_game_changes, verbose);

			report_game_changes(out,
				GAME_NEW_CLONE|GAME_RENAMED,
				ROM_RENAMED|ROM_MERGED|ROM_UNMERGED|ROM_REMOVED|
				P_ROM_RENAMED|P_ROM_REMOVED|ROM_COMP_CRC|P_ROM_COMP_CRC,
				DISK_RENAMED|DISK_REMOVED, SAMPLE_REMOVED,
				" Games affected by reorganisation of ROMs/Disks/Samples ",
				dat1, game_changes, num_game_changes, verbose);

			report_game_changes(out,
				0, ROM_ADDED|P_ROM_ADDED, DISK_ADDED, SAMPLE_ADDED,
				" Games requiring additional ROMs/Disks/Samples ",
				dat1, game_changes, num_game_changes, verbose);

			report_game_changes(out,
				GAME_ADDED, 0, 0, 0,
				" Game additions ",
				dat1, game_changes, num_game_changes, verbose);
		}
	
		if (set_type==OPTION_DAT_FULL_MERGING)
		{
			errflg=report_required_rebuilds(out, dat1, 0, 0,
				GAME_NEW_CLONE|GAME_REMOVED, ROM_RENAMED|ROM_REMOVED,
				" Merged set changes (just rebuild the ZIPs) ",
				game_changes, num_game_changes);
		}

		if (set_type==OPTION_DAT_SPLIT_MERGING)
		{
			errflg=report_required_rebuilds(out, dat1,
				GAME_RENAMED|GAME_REMOVED, ROM_RENAMED|ROM_MERGED|ROM_REMOVED,
				0, ROM_UNMERGED,
				" Split set changes (just rebuild the ZIPs) ",
				game_changes, num_game_changes);
		}

		if (set_type==OPTION_DAT_NO_MERGING)
		{
			errflg=report_required_rebuilds(out, dat1,
				GAME_RENAMED|GAME_REMOVED, ROM_RENAMED|ROM_REMOVED|P_ROM_RENAMED|P_ROM_REMOVED,
				0, 0,
				" Non-merged set changes (just rebuild the ZIPs) ",
				game_changes, num_game_changes);
		}

		if (set_type!=0)
		{
			report_required_roms(out, 0, ROM_ADDED|P_ROM_ADDED,
				" Games requiring new/fixed ROMs (visit SYS2064!) ",
				game_changes, num_game_changes);

			report_required_roms(out, GAME_ADDED, 0,
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

	FREE(sample_changes)
	FREE(disk_changes)
	FREE(rom_changes)
	FREE(game_changes)

	return(errflg);
}

void report_game_changes(FILE *out, uint16_t game_flags, uint16_t rom_flags, uint8_t disk_flags, uint8_t sample_flags,
	char *description, struct dat *dat1,
	struct game_change *game_changes, int num_game_changes, int verbose)
{
	int i, j, k;
	char st[MAX_STRING_LENGTH];

	for (i=j=0; i<num_game_changes; i++)
	{
		if (game_changes[i].game_flags & (game_flags) ||
			game_changes[i].rom_flags & (rom_flags) ||
			game_changes[i].disk_flags & (disk_flags) ||
			game_changes[i].sample_flags & (sample_flags))
		{	
			if (!j++)
			{
				LRPAD(st, description, "-", 80)
				fprintf(out, "%s\n\n", st);
			}

			if ((game_changes[i].game_flags & GAME_RENAMED) ||
				(game_changes[i].game_flags & GAME_NEW_CLONE) ||
				(game_changes[i].game_flags & GAME_REMOVED))
			{
				FORMAT_GAME_NAME(st, game_changes[i].game1)
				fprintf(out, "< %s\n", st);
			}
			else if (!(game_changes[i].game_flags & GAME_ADDED))
			{
				FORMAT_GAME_NAME(st, game_changes[i].game1)
				fprintf(out, "%s\n", st);
			}

			if ((game_changes[i].game_flags & GAME_RENAMED) ||
				(game_changes[i].game_flags & GAME_NEW_CLONE) ||
				(game_changes[i].game_flags & GAME_ADDED))
			{
				FORMAT_GAME_NAME(st, game_changes[i].game2)
				fprintf(out, "> %s\n", st);
			}

			for (k=0; verbose && k<game_changes[i].num_rom_changes; k++)
			{
				if (((game_changes[i].rom_changes[k].rom_flags & ROM_RENAMED) ||
					(game_changes[i].rom_changes[k].rom_flags & P_ROM_RENAMED) ||
					(game_changes[i].rom_changes[k].rom_flags & ROM_COMP_CRC) ||
					(game_changes[i].rom_changes[k].rom_flags & P_ROM_COMP_CRC) ||
					(game_changes[i].rom_changes[k].rom_flags & ROM_REMOVED) ||
					(game_changes[i].rom_changes[k].rom_flags & P_ROM_REMOVED) ||
					(game_changes[i].rom_changes[k].rom_flags & ROM_MERGED) ||
					(game_changes[i].rom_changes[k].rom_flags & ROM_UNMERGED)) &&
					!(rom_flags & ROM_ADDED))
				{
					FORMAT_ROM_NAME(st, game_changes[i].rom_changes[k].rom1)
					fprintf(out, "< %s\n", st);
				}

				if (((game_changes[i].rom_changes[k].rom_flags & ROM_RENAMED) ||
					(game_changes[i].rom_changes[k].rom_flags & P_ROM_RENAMED) ||
					(game_changes[i].rom_changes[k].rom_flags & ROM_COMP_CRC) ||
					(game_changes[i].rom_changes[k].rom_flags & P_ROM_COMP_CRC) ||
					(game_changes[i].rom_changes[k].rom_flags & ROM_MERGED) ||
					(game_changes[i].rom_changes[k].rom_flags & ROM_UNMERGED)) &&
					!(rom_flags & ROM_ADDED))
				{
					FORMAT_ROM_NAME(st, game_changes[i].rom_changes[k].rom2)
					fprintf(out, "> %s\n", st);
				}

				if (((game_changes[i].rom_changes[k].rom_flags & ROM_ADDED) &&
					(rom_flags & ROM_ADDED)) ||
					((game_changes[i].rom_changes[k].rom_flags & P_ROM_ADDED) &&
					(rom_flags & P_ROM_ADDED)))
				{
					FORMAT_ROM_NAME(st, game_changes[i].rom_changes[k].rom2)
					fprintf(out, "> %s", st);

					if (game_changes[i].rom_changes[k].rom2->rom_flags & FLAG_ROM_NODUMP)
						fprintf(out, " *just ignore\n");
					else if (bsearch((const void *)&game_changes[i].rom_changes[k].rom2->crc, dat1->rom_crc_idx, dat1->num_roms, sizeof(struct rom_idx), find_rom_by_crc))
						fprintf(out, " *already in MAME\n");
					else if (bsearch((const void *)&game_changes[i].rom_changes[k].rom2->crc, dat1->rom_crc_idx, dat1->num_roms, sizeof(struct rom_idx), find_rom_by_comp_crc))
						fprintf(out, " *already in MAME\n");
					else
						fprintf(out, "\n");
				}
			}

			for (k=0; verbose && k<game_changes[i].num_disk_changes; k++)
			{
				if (((game_changes[i].disk_changes[k].disk_flags & DISK_RENAMED) ||
					(game_changes[i].disk_changes[k].disk_flags & DISK_REMOVED)) &&
					!(disk_flags & DISK_ADDED))
				{
					FORMAT_DISK_NAME(st, game_changes[i].disk_changes[k].disk1)
					fprintf(out, "< %s\n", st);
				}

				if ((game_changes[i].disk_changes[k].disk_flags & DISK_RENAMED) &&
					!(disk_flags & DISK_ADDED))
				{
					FORMAT_DISK_NAME(st, game_changes[i].disk_changes[k].disk2)
					fprintf(out, "> %s\n", st);
				}

				if ((game_changes[i].disk_changes[k].disk_flags & DISK_ADDED) &&
					(disk_flags & DISK_ADDED))
				{
					FORMAT_DISK_NAME(st, game_changes[i].disk_changes[k].disk2)
					fprintf(out, "> %s", st);

					if (game_changes[i].disk_changes[k].disk2->crc==0)
						fprintf(out, " *just ignore\n");
					else if (bsearch((const void *)&game_changes[i].disk_changes[k].disk2->crc, dat1->disk_crc_idx, dat1->num_disks, sizeof(struct disk_idx), find_disk_by_crc))
						fprintf(out, " *already in MAME\n");
					else
						fprintf(out, "\n");
				}
			}

			for (k=0; verbose && k<game_changes[i].num_sample_changes; k++)
			{
				if (((game_changes[i].sample_changes[k].sample_flags & SAMPLE_REMOVED)) &&
					!(sample_flags & SAMPLE_ADDED))
				{
					FORMAT_SAMPLE_NAME(st, game_changes[i].sample_changes[k].sample1)
					fprintf(out, "< %s\n", st);
				}

				if ((game_changes[i].sample_changes[k].sample_flags & SAMPLE_ADDED) &&
					(sample_flags & SAMPLE_ADDED))
				{
					FORMAT_SAMPLE_NAME(st, game_changes[i].sample_changes[k].sample2)
					fprintf(out, "> %s\n", st);
				}
			}

			if (!verbose && (rom_flags & game_changes[i].rom_flags &
				(ROM_RENAMED|P_ROM_RENAMED|
				ROM_REMOVED|P_ROM_REMOVED|
				ROM_COMP_CRC|P_ROM_COMP_CRC|
				ROM_ADDED|P_ROM_ADDED|
				ROM_MERGED|ROM_UNMERGED) ||
				disk_flags & game_changes[i].disk_flags &
				(DISK_RENAMED|DISK_REMOVED|DISK_ADDED) ||
				sample_flags & game_changes[i].sample_flags &
				(SAMPLE_REMOVED|SAMPLE_ADDED)))
			{
				k=0;
				fprintf(out, "Changes: ");
				
				if (rom_flags & game_changes[i].rom_flags & ROM_RENAMED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM renames");
				}

				if (rom_flags & game_changes[i].rom_flags & P_ROM_RENAMED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM renames (in parent)");
				}

				if (rom_flags & game_changes[i].rom_flags & ROM_COMP_CRC)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "complemented CRCs");
				}

				if (rom_flags & game_changes[i].rom_flags & P_ROM_COMP_CRC)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "complemented CRCs (in parent)");
				}

				if (rom_flags & game_changes[i].rom_flags & ROM_REMOVED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM removals");
				}

				if (rom_flags & game_changes[i].rom_flags & P_ROM_REMOVED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM removals (in parent)");
				}

				if (rom_flags & game_changes[i].rom_flags & ROM_ADDED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM additions");
				}

				if (rom_flags & game_changes[i].rom_flags & P_ROM_ADDED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM additions (in parent)");
				}

				if (rom_flags & game_changes[i].rom_flags & (ROM_MERGED|ROM_UNMERGED))
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "ROM merge details");
				}

				if (disk_flags & game_changes[i].disk_flags & DISK_RENAMED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "disk renames");
				}

				if (disk_flags & game_changes[i].disk_flags & DISK_REMOVED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "disk removals");
				}

				if (disk_flags & game_changes[i].disk_flags & DISK_ADDED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "disk additions");
				}

				if (sample_flags & game_changes[i].sample_flags & SAMPLE_REMOVED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "sample removals");
				}

				if (sample_flags & game_changes[i].sample_flags & SAMPLE_ADDED)
				{
					if (k++)
						fprintf(out, ", ");
					fprintf(out, "sample additions");
				}

				fprintf(out, "\n");
			}

			if (!(game_changes[i].game_flags & (GAME_REMOVED|GAME_ADDED)))
				fprintf(out, "\n");
		}
	}

	if (j && (game_flags & (GAME_REMOVED|GAME_ADDED)))
		fprintf(out, "\n");
}

void report_required_roms(FILE *out, uint16_t game_flags, uint16_t rom_flags, char *description,
	struct game_change *game_changes, int num_game_changes)
{
	int i, j;
	char st[MAX_STRING_LENGTH];

	for (i=j=0; i<num_game_changes; i++)
	{
		if (game_changes[i].game_flags & (game_flags) ||
			game_changes[i].rom_flags & (rom_flags))
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

int report_required_rebuilds(FILE *out, struct dat *dat, uint16_t child_game_flags, uint16_t child_rom_flags,
	uint16_t parent_game_flags, uint16_t parent_rom_flags, char *description,
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
		if (game_changes[i].game_flags & (child_game_flags) ||
			game_changes[i].rom_flags & (child_rom_flags))
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
		if (game_changes[i].game_flags & (parent_game_flags) ||
			game_changes[i].rom_flags & (parent_rom_flags))
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
				if (game_changes[i].game1->game_cloneof)
					rebuild_list[num_rebuilds++].game=game_changes[i].game1->game_cloneof;
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
