/* --- This include file is used by every module in DatLib --- */

#ifndef _DATLIB_TYPE_H_
#define _DATLIB_TYPE_H_


/* --- Standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* --- DatLib Includes --- */

#include "macro.h"


/* --- Comment Structures --- */

struct comment
{
	char *comment;
};


/* --- ROM Structures --- */

struct rom
{
	/* --- Fields that appear in data files */

	char *name;
	char *merge;
	uint32_t size;
	uint32_t crc;
	char *md5;
	char *sha1;
	char *region;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint16_t rom_flags;
	uint16_t rom_warnings;
	uint16_t rom_fixes;

	/* --- Fields that are specific to external tools */

	uint32_t match;
};

struct rom_idx
{
	struct rom *rom;
};


/* --- Disk Structures --- */

struct disk
{
	/* --- Fields that appear in data files */

	char *name;
	char *md5;
	char *sha1;
	char *region;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t disk_flags;
	uint8_t disk_warnings;
	uint8_t disk_fixes;

	/* --- Fields that are specific to external tools */

	uint32_t match;
};

struct disk_idx
{
	struct disk *disk;
};


/* --- Sample Structures --- */

struct sample
{
	/* --- Fields that appear in data files */

	char *name;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t sample_flags;
	uint8_t sample_warnings;
	uint8_t sample_fixes;

	/* --- Fields that are specific to external tools */

	uint32_t match;
};

struct sample_idx
{
	struct sample *sample;
};


/* --- Game Structures --- */

struct game
{
	/* --- Fields that appear in data files */

	char *name;
	char *description;
	char *year;
	char *manufacturer;
	char *rebuildto;
	char *cloneof;
	char *romof;
	char *sampleof;

	/* --- Fields that are calculated by DatLib */

	struct game *parent;
	struct game *merge;

	struct comment *comments;

	struct rom *roms;
	struct rom_idx *rom_name_idx;
	struct rom_idx *rom_crc_idx;

	struct disk *disks;
	struct disk_idx *disk_name_idx;

	struct sample *samples;
	struct sample_idx *sample_name_idx;

	uint32_t num_comments;
	uint32_t num_roms;
	uint32_t num_disks;
	uint32_t num_samples;

	uint32_t size;
	uint32_t crc;

	uint32_t num_clones;

	uint16_t game_flags;
	uint16_t rom_flags;
	uint8_t disk_flags;
	uint8_t sample_flags;

	uint16_t game_warnings;
	uint16_t rom_warnings;
	uint8_t disk_warnings;
	uint8_t sample_warnings;

	uint16_t game_fixes;
	uint16_t rom_fixes;
	uint8_t disk_fixes;
	uint8_t sample_fixes;

	/* --- Fields that are specific to external tools */

	uint32_t flags;
	uint32_t match;
	double score;
};

struct game_idx
{
	struct game *game;
};


/* --- ZIP Structures --- */

struct game_zip_rom
{
	/* --- Fields that are calculated by DatLib */

	struct game_zip *game_zip;

	struct rom *rom;

	/* --- Fields that are specific to external tools */

	uint32_t flags;
};

struct game_zip
{
	/* --- Fields that are calculated by DatLib */

	struct game *game;

	struct game_zip_rom *game_zip_roms;

	uint32_t num_game_zip_roms;

	/* --- Fields that are specific to external tools */

	uint32_t flags;
};

struct game_zip_idx
{
	struct game_zip *game_zip;
};


/* --- Header Structures --- */

struct clrmamepro
{
	char *name;           // DatUtil -R option
	char *description;    // DatUtil -F option
	char *category;       // DatUtil -C option (not actually used by CMPro though)
	char *version;        // DatUtil -V option
	char *author;         // DatUtil -A option
	char *forcemerging;   // DatUtil -M option (none, split or full)
	char *forcezipping;   // DatUtil -Z option (zip or unzip)
};

struct romcenter_credits
{
	char *author;         // DatUtil -A option
	char *email;          // DatUtil has no option for this. New in the 2.50 format
	char *homepage;       // DatUtil has no option for this. New in the 2.50 format
	char *url;            // DatUtil has no option for this. New in the 2.50 format
	char *version;        // DatUtil -V option
	char *date;           // DatUtil has no option for this. New in the 2.50 format
	char *comment;        // DatUtil -C option
};

struct romcenter_dat
{
	char *version;        // Default is 2.50
	char *plugin;         // DatUtil -P option. New in the 2.50 format. Default is arcade.dll
	char *split;          // DatUtil -M option. New in the 2.50 format
	char *merge;          // DatUtil -M option. New in the 2.50 format
};

struct romcenter_emulator
{
	char *refname;        // DatUtil -R option
	char *version;        // DatUtil -F option
};


/* --- Options --- */

struct options
{
	char *fn;
	char *log_fn;
	struct dat *info;

	struct clrmamepro clrmamepro;
	uint32_t options;
	char *game;

	char *save_name;
	char *save_mode;
	char *save_format;
};


/* --- Dat Structure --- */

struct dat
{
	/* --- Fields that are used to load and save data files */

	char *name;

	struct options *options;

	struct driver *load;
	struct driver *save;

	char *log_name;
	FILE *log_file;

	FILE *out;

	char *buffer1_start;
	char *buffer1_end;
	uint32_t buffer1_size;
	char *buffer1_ptr;

	char *buffer2_start;
	char *buffer2_end;
	uint32_t buffer2_size;
	char *buffer2_ptr;

	char *token;
	uint32_t token_size;

	/* --- Fields that appear in data files */

	struct clrmamepro clrmamepro;

	struct romcenter_credits romcenter_credits;
	struct romcenter_dat romcenter_dat;
	struct romcenter_emulator romcenter_emulator;

	/* --- Fields that are calculated by DatLib */

	struct game *games;
	struct game_idx *game_name_idx;
	struct game_idx *game_crc_idx;
	struct game_idx *game_score_idx;

	struct comment *comments;

	struct rom *roms;
	struct rom_idx *game_rom_name_idx;
	struct rom_idx *game_rom_crc_idx;
	struct rom_idx *rom_name_idx;
	struct rom_idx *rom_crc_idx;

	struct disk *disks;
	struct disk_idx *game_disk_name_idx;
	struct disk_idx *disk_name_idx;

	struct sample *samples;
	struct sample_idx *game_sample_name_idx;
	struct sample_idx *sample_name_idx;

	struct game_zip *game_zips;
	struct game_zip_idx *game_zip_name_idx;

	struct game_zip_rom *game_zip_roms;

	uint32_t num_comments;
	uint32_t num_games, num_resources, num_machines;
	uint32_t num_roms, num_resource_roms, num_machine_roms;
	uint32_t num_disks, num_resource_disks, num_machine_disks;
	uint32_t num_samples, num_resource_samples, num_machine_samples;

	uint32_t num_game_zips;
	uint32_t num_game_zip_roms;

	uint32_t num_parents, num_clones, num_others;

	uint16_t dat_flags;

	uint16_t game_flags;
	uint16_t rom_flags;
	uint8_t disk_flags;
	uint8_t sample_flags;

	uint16_t game_warnings;
	uint16_t rom_warnings;
	uint8_t disk_warnings;
	uint8_t sample_warnings;

	uint16_t game_fixes;
	uint16_t rom_fixes;
	uint8_t disk_fixes;
	uint8_t sample_fixes;

	uint16_t game_saved;
	uint16_t rom_saved;
	uint8_t disk_saved;
	uint8_t sample_saved;
};


/* --- Ini File Structure --- */

struct ini_entry
{
	char section[MAX_STRING_LENGTH+1];
	char param[MAX_STRING_LENGTH+1];
	char value[MAX_STRING_LENGTH+1];
};


/* --- Options for the loader/cleanser --- */

#define OPTION_LOAD_QUIETLY		0x00000001	// Tool specific
#define OPTION_SHOW_SUMMARY		0x00000002	// Tool specific

#define OPTION_VERBOSE_LOGGING		0x00000010	// DatUtil -v option
#define OPTION_SHOW_DEBUG_INFO		0x00000020	// DatUtil -d option
#define OPTION_IGNORE_FUNNY_SIZES	0x00000040	// DatUtil -z option
#define OPTION_IGNORE_MISSING_YEARS	0x00000080	// DatUtil -y option

#define OPTION_LOWER_CASE		0x00000100	// DatUtil -l option
#define OPTION_SORT_GAMES_BY_PARENT	0x00000200	// DatUtil -s option
#define OPTION_GAME			0x00000400	// DatUtil -g option
#define OPTION_GAME_AND_CLONES		0x00000800	// DatUtil -c option

#define OPTION_REMOVE_CLONES		0x00001000	// DatUtil -r option
#define OPTION_NEBULA_JUKEBOX		0x00002000	// DatUtil -j option

#define OPTION_EXTENDED_CHECKSUMS	0x00010000	// DatUtil -x option
#define OPTION_SHA1_CHECKSUMS		0x00020000	// DatUtil default
#define OPTION_MD5_CHECKSUMS		0x00040000	// DatUtil -m option

#define	OPTION_DAT_FULL_MERGING		0x00100000	// Used by MAMEDiff
#define	OPTION_DAT_SPLIT_MERGING	0x00200000	// Used by MAMEDiff
#define	OPTION_DAT_NO_MERGING		0x00400000	// Used by MAMEDiff


/* --- Parser Flags --- */

#define	FLAG_CLRMAMEPRO_HEADER		0x8000


/* --- Dat Flags --- */

#define	FLAG_DAT_FULL_MERGING		0x0001
#define	FLAG_DAT_SPLIT_MERGING		0x0002
#define	FLAG_DAT_NO_MERGING		0x0004


/* --- Game Flags --- */

#define	FLAG_GAME_NAME			0x0001
#define	FLAG_RESOURCE_NAME		0x0002
#define	FLAG_MACHINE_NAME		0x0004
#define FLAG_GAME_DESCRIPTION		0x0008
#define FLAG_GAME_YEAR			0x0010
#define FLAG_GAME_MANUFACTURER		0x0020
#define FLAG_GAME_REBUILDTO		0x0040
#define FLAG_GAME_CLONEOF		0x0080
#define FLAG_GAME_ROMOF			0x0100
#define FLAG_GAME_SAMPLEOF		0x0200
#define FLAG_GAME_CLONEOFCLONE		0x0400
#define FLAG_GAME_COMMENTS		0x0800


/* --- ROM Flags --- */

#define FLAG_ROM_NAME			0x0001
#define FLAG_ROM_MERGE			0x0002
#define FLAG_ROM_SIZE			0x0004
#define FLAG_ROM_CRC			0x0008
#define FLAG_ROM_MD5			0x0010
#define FLAG_ROM_SHA1			0x0020
#define FLAG_ROM_REGION			0x0040
#define	FLAG_ROM_BADDUMP		0x0080
#define	FLAG_ROM_NODUMP			0x0100
#define FLAG_ROM_DUPLICATE		0x0200
#define FLAG_ROM_CONFLICT		0x0400
#define FLAG_ROM_FUNNYSIZE		0x0800
#define FLAG_ROM_BIOS			0x1000


/* --- Disk Flags --- */

#define FLAG_DISK_NAME			0x01
#define FLAG_DISK_MD5			0x02
#define FLAG_DISK_SHA1			0x04
#define FLAG_DISK_REGION		0x08
#define FLAG_DISK_DUPLICATE		0x10


/* --- Sample Flags --- */

#define FLAG_SAMPLE_NAME		0x01
#define FLAG_SAMPLE_DUPLICATE		0x02


#endif /* _DATLIB_TYPE_H_ */
