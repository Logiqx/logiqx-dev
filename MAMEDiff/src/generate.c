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

#include "generate.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


/* --- Dat generation --- */

int generate_changes(struct dat *dat1, struct dat *dat2, int diff_type, int renames, int zeros)
{
	FILE *changes_log=0, *changes_dat=0;

	char st[MAX_STRING_LENGTH];

	struct game_zip *curr_game_zip1, *curr_game_zip2;
	struct game_zip_idx *curr_game_zip_name_idx1, *curr_game_zip_name_idx2;
	struct game_zip_rom *curr_game_zip_rom1, *curr_game_zip_rom2;

	struct rom *curr_rom;
	struct game *curr_game;
	struct game_idx *curr_game_name_idx;

	uint32_t i, j, k;

	int num_game_zip_removals=0, num_game_zip_additions=0;
	int num_game_zip_rom_removals=0, num_game_zip_rom_additions=0, num_game_zip_rom_elsewheres=0;

	int found, errflg=0;

	/* --- Create the output files --- */

	if (!errflg)
		FOPEN(changes_log, "mamediff.log", "w")

	if (!errflg)
		FOPEN(changes_dat, "mamediff.dat", "w")

	/* --- Search for ZIP and ROM removals --- */

	for (i=0, curr_game_zip1=dat1->game_zips; !errflg && i<dat1->num_game_zips; i++, curr_game_zip1++)
	{
		curr_game_zip_name_idx2=bsearch((void *)curr_game_zip1->game->name, dat2->game_zip_name_idx, dat2->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);

		if (curr_game_zip_name_idx2)
		{
			curr_game_zip2=curr_game_zip_name_idx2->game_zip;

			for (j=0, curr_game_zip_rom1=curr_game_zip1->game_zip_roms; j<curr_game_zip1->num_game_zip_roms; j++, curr_game_zip_rom1++)
			{
				if (!(curr_game_zip_rom1->rom->rom_flags & FLAG_ROM_NODUMP) || zeros>0)
				{
					found=0;

					for (k=0, curr_game_zip_rom2=curr_game_zip2->game_zip_roms; !found && k<curr_game_zip2->num_game_zip_roms; k++, curr_game_zip_rom2++)
					{
						if (((zeros>0 && curr_game_zip_rom2->rom->rom_flags & FLAG_ROM_NODUMP) ||
							curr_game_zip_rom1->rom->crc==curr_game_zip_rom2->rom->crc ||
							curr_game_zip_rom1->rom->crc==~curr_game_zip_rom2->rom->crc) &&
							curr_game_zip_rom1->rom->size==curr_game_zip_rom2->rom->size &&
							((renames==0 && !(curr_game_zip_rom2->rom->rom_flags & FLAG_ROM_NODUMP)) ||
							 !strcmp(curr_game_zip_rom1->rom->name, curr_game_zip_rom2->rom->name)))
						{
							found++;
						}
					}

					if (!found)
					{
						curr_game_zip_rom1->flags|=GAME_ZIP_ROM_REMOVED;
						curr_game_zip1->flags|=GAME_ZIP_ROM_REMOVED;
						num_game_zip_rom_removals++;
					}
				}
			}
		}
		else
		{
			curr_game_zip1->flags|=GAME_ZIP_REMOVED;
			num_game_zip_removals++;
		}
	}

	/* --- Search for ZIP and ROM additions --- */

	for (i=0, curr_game_zip2=dat2->game_zips; !errflg && i<dat2->num_game_zips; i++, curr_game_zip2++)
	{
		curr_game_zip_name_idx1=bsearch((void *)curr_game_zip2->game->name, dat1->game_zip_name_idx, dat1->num_game_zips, sizeof(struct game_zip_idx), find_game_zip_by_name);

		if (curr_game_zip_name_idx1)
		{
			curr_game_zip1=curr_game_zip_name_idx1->game_zip;
			curr_game_zip2->flags|=curr_game_zip1->flags;
		}
		else
		{
			curr_game_zip1=0;

			curr_game_zip2->flags|=GAME_ZIP_ADDED;
			num_game_zip_additions++;
		}

		for (j=0, curr_game_zip_rom2=curr_game_zip2->game_zip_roms; j<curr_game_zip2->num_game_zip_roms; j++, curr_game_zip_rom2++)
		{
			if (!(curr_game_zip_rom2->rom->rom_flags & FLAG_ROM_NODUMP) || zeros>0)
			{
				found=0;

				if (curr_game_zip1)
				{
					for (k=0, curr_game_zip_rom1=curr_game_zip1->game_zip_roms; !found && k<curr_game_zip1->num_game_zip_roms; k++, curr_game_zip_rom1++)
					{
						if (((zeros>0 && curr_game_zip_rom2->rom->rom_flags & FLAG_ROM_NODUMP) ||
							curr_game_zip_rom1->rom->crc==curr_game_zip_rom2->rom->crc ||
							curr_game_zip_rom1->rom->crc==~curr_game_zip_rom2->rom->crc) &&
							curr_game_zip_rom1->rom->size==curr_game_zip_rom2->rom->size &&
							((renames==0 && !(curr_game_zip_rom2->rom->rom_flags & FLAG_ROM_NODUMP)) ||
							 !strcmp(curr_game_zip_rom1->rom->name, curr_game_zip_rom2->rom->name)))
						{
							found++;
						}
					}
				}

				if (!found && diff_type==3)
				{
					curr_game_name_idx=0;

					if (dat2->options->options & OPTION_DAT_FULL_MERGING)
						curr_game_name_idx=bsearch((void *)curr_game_zip_rom2->rom->game->name, dat1->game_name_idx, dat1->num_games, sizeof(struct game_idx), find_game_by_name);
					else if (curr_game_zip_rom2->rom->game->cloneof)
					{
						curr_game_name_idx=bsearch((void *)curr_game_zip_rom2->rom->game->cloneof, dat1->game_name_idx, dat1->num_games, sizeof(struct game_idx), find_game_by_name);
					}

					if (curr_game_name_idx)
					{
						curr_game=curr_game_name_idx->game;

						for (k=0, curr_rom=curr_game->roms; !found && k<curr_game->num_roms; k++, curr_rom++)
						{
							if (((zeros>0 && curr_game_zip_rom2->rom->rom_flags & FLAG_ROM_NODUMP) ||
								curr_rom->crc==curr_game_zip_rom2->rom->crc ||
								curr_rom->crc==~curr_game_zip_rom2->rom->crc) &&
								curr_rom->size==curr_game_zip_rom2->rom->size &&
								((renames==0 && !(curr_game_zip_rom2->rom->rom_flags & FLAG_ROM_NODUMP)) ||
							 	!strcmp(curr_rom->name, curr_game_zip_rom2->rom->name)))
							{
								found++;
							}
						}

						if (found)
						{
							curr_game_zip_rom2->flags|=GAME_ZIP_ROM_ELSEWHERE;
							curr_game_zip2->flags|=GAME_ZIP_ROM_ELSEWHERE;
							num_game_zip_rom_elsewheres++;
						}
					}
				}

				if (!found)
				{
					curr_game_zip_rom2->flags|=GAME_ZIP_ROM_ADDED;
					curr_game_zip2->flags|=GAME_ZIP_ROM_ADDED;
					num_game_zip_rom_additions++;
				}
			}
		}
	}

	/* --- Generate Log --- */

	if (!errflg && diff_type==1)
	{
		if (num_game_zip_removals || num_game_zip_additions ||
			num_game_zip_rom_removals || num_game_zip_rom_additions || num_game_zip_rom_elsewheres)
		{
			strcpy(st, dat2->name);
			if (strstr(st, ".dat")) *strstr(st, ".dat")=0;
			fprintf(changes_log, "Changes dat for use with %s\n", st);

			fprintf(changes_log, "Copy changes over a perfect ");
			if (dat1->options->options & OPTION_DAT_NO_MERGING)
				fprintf(changes_log, "non-merged");
			if (dat1->options->options & OPTION_DAT_SPLIT_MERGING)
				fprintf(changes_log, "split-merged");
			if (dat1->options->options & OPTION_DAT_FULL_MERGING)
				fprintf(changes_log, "fully-merged");

			strcpy(st, dat1->name);
			if (strstr(st, ".dat")) *strstr(st, ".dat")=0;
			if (strchr(st, '/')) strcpy(st, strrchr(st, '/')+1);
			if (strchr(st, '\\')) strcpy(st, strrchr(st, '\\')+1);
			fprintf(changes_log, " set for %s\n\n", st);

			fprintf(changes_log, "Created with the MAMEDiff option(s): -d%d ", diff_type);

			if (renames)
				fprintf(changes_log, "-r ");

			if (zeros)
				fprintf(changes_log, "-z ");

			fprintf(changes_log, "\n\n");

			/* --- Report ZIP removals --- */

			if (dat2->options->options & OPTION_DAT_FULL_MERGING)
				LRPAD(st, " ZIPs Removed (n.b. ZIPs include clones) ", "-", 80)
			else
				LRPAD(st, " ZIPs Removed ", "-", 80)
			fprintf(changes_log, "%s\n\n", st);
			for (j=i=0, curr_game_zip_name_idx1=dat1->game_zip_name_idx; i<dat1->num_game_zips; i++, curr_game_zip_name_idx1++)
			{
				curr_game_zip1=curr_game_zip_name_idx1->game_zip;

				if (curr_game_zip1->flags & GAME_ZIP_REMOVED)
				{
					fprintf(changes_log, "%8s.zip - %s\n", curr_game_zip1->game->name, curr_game_zip1->game->description);
					j++;
				}
			}
			if (!j) fprintf(changes_log, "No ZIPs removed.\n");
			fprintf(changes_log, "\n");

			/* --- Report ZIP changes --- */

			if (dat2->options->options & OPTION_DAT_FULL_MERGING)
				LRPAD(st, " ZIPs Changed (n.b. ZIPs include clones) ", "-", 80)
			else
				LRPAD(st, " ZIPs Changed ", "-", 80)
			fprintf(changes_log, "%s\n\n", st);
			for (j=i=0, curr_game_zip_name_idx2=dat2->game_zip_name_idx; i<dat2->num_game_zips; i++, curr_game_zip_name_idx2++)
			{
				curr_game_zip2=curr_game_zip_name_idx2->game_zip;

				if (!(curr_game_zip2->flags & GAME_ZIP_ADDED) && curr_game_zip2->flags & (GAME_ZIP_ROM_REMOVED | GAME_ZIP_ROM_ADDED | GAME_ZIP_ROM_ELSEWHERE))
				{
					fprintf(changes_log, "%8s.zip - %s\n", curr_game_zip2->game->name, curr_game_zip2->game->description);
					j++;
				}
			}
			if (!j) fprintf(changes_log, "No ZIPs changed.\n");
			fprintf(changes_log, "\n");

			/* --- Report ZIP additions --- */

			if (dat2->options->options & OPTION_DAT_FULL_MERGING)
				LRPAD(st, " ZIPs Added (n.b. ZIPs include clones) ", "-", 80)
			else
				LRPAD(st, " ZIPs Added ", "-", 80)
			fprintf(changes_log, "%s\n\n", st);
			for (j=i=0, curr_game_zip_name_idx2=dat2->game_zip_name_idx; i<dat2->num_game_zips; i++, curr_game_zip_name_idx2++)
			{
				curr_game_zip2=curr_game_zip_name_idx2->game_zip;

				if (curr_game_zip2->flags & GAME_ZIP_ADDED)
				{
					fprintf(changes_log, "%8s.zip - %s\n", curr_game_zip2->game->name, curr_game_zip2->game->description);
					j++;
				}
			}
			if (!j) fprintf(changes_log, "No ZIPs added.\n");
			fprintf(changes_log, "\n");
		}
	}

	if (!errflg && diff_type>1)
	{
		if (num_game_zip_additions ||
			num_game_zip_rom_additions || (diff_type==2 && num_game_zip_rom_elsewheres))
		{
			strcpy(st, dat2->name);
			if (strstr(st, ".dat")) *strstr(st, ".dat")=0;
			fprintf(changes_log, "Supplementary dat for use with %s\n", st);

			fprintf(changes_log, "Use in addition to a perfect ");
			if (dat1->options->options & OPTION_DAT_NO_MERGING)
				fprintf(changes_log, "non-merged");
			if (dat1->options->options & OPTION_DAT_SPLIT_MERGING)
				fprintf(changes_log, "split-merged");
			if (dat1->options->options & OPTION_DAT_FULL_MERGING)
				fprintf(changes_log, "fully-merged");

			strcpy(st, dat1->name);
			if (strstr(st, ".dat")) *strstr(st, ".dat")=0;
			if (strchr(st, '/')) strcpy(st, strrchr(st, '/')+1);
			if (strchr(st, '\\')) strcpy(st, strrchr(st, '\\')+1);
			fprintf(changes_log, " set for %s\n\n", st);

			fprintf(changes_log, "Created with the MAMEDiff option(s): -d%d ", diff_type);

			if (renames)
				fprintf(changes_log, "-r ");

			if (zeros)
				fprintf(changes_log, "-z ");

			fprintf(changes_log, "\n\n");

			for (i=0, curr_game_zip2=dat2->game_zips; i<dat2->num_game_zips; i++, curr_game_zip2++)
			{
				if ((curr_game_zip2->flags & GAME_ZIP_ROM_ADDED) ||
					(diff_type==2 && curr_game_zip2->flags & GAME_ZIP_ROM_ELSEWHERE))
				{
					curr_game=curr_game_zip2->game;

					/* --- Break link to parent as changes dats do not use merging --- */

					curr_game->cloneof=0;
					curr_game->romof=0;

					FORMAT_GAME_NAME(st, curr_game);
					fprintf(changes_log, "%s\n\n", st);

					for (j=0, curr_game_zip_rom2=curr_game_zip2->game_zip_roms; j<curr_game_zip2->num_game_zip_roms; j++, curr_game_zip_rom2++)
					{
						curr_rom=curr_game_zip_rom2->rom;

						if (curr_game_zip_rom2->flags & GAME_ZIP_ROM_ADDED ||
							(diff_type==2 && curr_game_zip_rom2->flags & GAME_ZIP_ROM_ELSEWHERE))
						{
							if (curr_rom->rom_flags & FLAG_ROM_NODUMP)
								fprintf(changes_log, "  ROM: %12s (%7lu bytes, no dump available)", curr_rom->name, (unsigned long) curr_rom->size);
							else
								fprintf(changes_log, "  ROM: %12s (%7lu bytes, crc %08lx)", curr_rom->name, (unsigned long) curr_rom->size, (unsigned long) curr_rom->crc);

							if (dat2->options->options & OPTION_DAT_FULL_MERGING)
								fprintf(changes_log, " - from %s", curr_rom->game->name);

							fprintf(changes_log, "\n");
						}
					}

					fprintf(changes_log, "\n");
				}
			}
		}
	}

	/* --- Generate Dat --- */

	if (!errflg)
	{
		for (i=0, curr_game_zip2=dat2->game_zips; i<dat2->num_game_zips; i++, curr_game_zip2++)
		{
			if ((curr_game_zip2->flags & GAME_ZIP_ROM_ADDED) ||
				(diff_type==1 && curr_game_zip2->flags & GAME_ZIP_ROM_REMOVED) ||
				((diff_type==1 || diff_type==2) && curr_game_zip2->flags & GAME_ZIP_ROM_ELSEWHERE))
			{
				curr_game=curr_game_zip2->game;

				fprintf(changes_dat, "game (\n");

				if (strchr(curr_game->name, ' '))
					fprintf(changes_dat, "\tname \"%s\"\n", curr_game->name);
				else
					fprintf(changes_dat, "\tname %s\n", curr_game->name);

				if (curr_game->description!=0)
				{
					if (dat2->options->options & OPTION_DAT_FULL_MERGING)
						fprintf(changes_dat, "\tdescription \"%s [n.b. includes clones]\"\n", curr_game->description);
					else
						fprintf(changes_dat, "\tdescription \"%s\"\n", curr_game->description);
				}

				if (curr_game->year!=0)
				{
					if (strchr(curr_game->year, ' '))
						fprintf(changes_dat, "\tyear \"%s\"\n", curr_game->year);
					else
						fprintf(changes_dat, "\tyear %s\n", curr_game->year);
				}

				if (curr_game->manufacturer!=0)
					fprintf(changes_dat, "\tmanufacturer \"%s\"\n", curr_game->manufacturer);

				for (j=0, curr_game_zip_rom2=curr_game_zip2->game_zip_roms; j<curr_game_zip2->num_game_zip_roms; j++, curr_game_zip_rom2++)
				{
					curr_rom=curr_game_zip_rom2->rom;

					if ((!(curr_rom->rom_flags & FLAG_ROM_NODUMP) || zeros) &&
						(diff_type==1 || curr_game_zip_rom2->flags & GAME_ZIP_ROM_ADDED ||
						(diff_type==2 && curr_game_zip_rom2->flags & GAME_ZIP_ROM_ELSEWHERE)))
					{
						if (strchr(curr_rom->name, ' '))
							fprintf(changes_dat, "\trom ( name \"%s\" ", curr_rom->name);
						else
							fprintf(changes_dat, "\trom ( name %s ", curr_rom->name);

						fprintf(changes_dat, "size %ld ", (unsigned long) curr_rom->size);

						if (curr_rom->crc!=0)
							fprintf(changes_dat, "crc %08lx ", (unsigned long) curr_rom->crc);

						if (curr_rom->sha1!=0)
							fprintf(changes_dat, "sha1 %s ", curr_rom->sha1);

						if (curr_rom->md5!=0)
							fprintf(changes_dat, "md5 %s ", curr_rom->md5);

						if (curr_rom->region!=0)
							fprintf(changes_dat, "region %s ", curr_rom->region);

						if (curr_rom->rom_flags & FLAG_ROM_BADDUMP)
							fprintf(changes_dat, "flags baddump ");

						if (curr_rom->rom_flags & FLAG_ROM_NODUMP)
							fprintf(changes_dat, "flags nodump ");

						fprintf(changes_dat, ")\n");
					}
				}

				fprintf(changes_dat, ")\n\n");
			}
		}
	}

	if (!errflg)
	{
		if (num_game_zip_rom_additions ||
			(diff_type==1 && num_game_zip_rom_removals) ||
			((diff_type==1 || diff_type==2) && num_game_zip_rom_elsewheres))
		{
			printf("Report has been written to mamediff.log and dat saved as mamediff.dat\n");
		}
		else
		{
			printf("No differences found.\n");
			fprintf(changes_log, "No supplement required\n");
		}
	}

	/* --- Close output files --- */

	FCLOSE(changes_dat)
	FCLOSE(changes_log)

	return(errflg);
}
