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
	char *text;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t comment_flags;
	uint8_t comment_warnings;
	uint8_t comment_fixes;
};


/* --- BIOS Set Structures --- */

struct biosset
{
	/* --- Fields that appear in data files */

	char *name;
	char *description;
	char *_default;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t biosset_flags;
	uint8_t biosset_warnings;
	uint8_t biosset_fixes;
};


/* --- ROM Structures --- */

struct rom
{
	/* --- Fields that appear in data files */

	char *name;
	char *bios;
	uint32_t size;
	uint32_t crc;
	char *md5;
	char *sha1;
	char *merge;
	char *region;
	uint32_t offset;
	char *status;
	char *dispose;
	char *soundonly;

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
	char *merge;
	char *region;
	uint32_t index;
	char *status;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint32_t crc;

	uint16_t disk_flags;
	uint16_t disk_warnings;
	uint16_t disk_fixes;

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

	char *merge;

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


/* --- Chip Structures --- */

struct chip
{
	/* --- Fields that appear in data files */

	char *name;
	char *type;
	char *soundonly;
	uint32_t clock;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t chip_flags;
	uint8_t chip_warnings;
	uint8_t chip_fixes;
};


/* --- Video Structures --- */

struct video
{
	/* --- Fields that appear in data files */

	char *screen;
	char *orientation;
	uint16_t width;
	uint16_t height;
	uint16_t aspectx;
	uint16_t aspecty;
	float refresh;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t video_flags;
	uint8_t video_warnings;
	uint8_t video_fixes;
};


/* --- Sound Structures --- */

struct sound
{
	/* --- Fields that appear in data files */

	uint8_t channels;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t sound_flags;
	uint8_t sound_warnings;
	uint8_t sound_fixes;
};


/* --- Input Structures --- */

struct input
{
	/* --- Fields that appear in data files */

	char *service;
	char *tilt;
	uint8_t players;
	char *control;
	uint8_t buttons;
	uint8_t coins;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t input_flags;
	uint8_t input_warnings;
	uint8_t input_fixes;
};


/* --- Dipswitch Structures --- */

struct dipvalue
{
	/* --- Fields that appear in data files */

	char *name;
	char *_default;

	/* --- Fields that are calculated by DatLib */

	struct dipswitch *dipswitch;

	uint8_t dipvalue_flags;
	uint8_t dipvalue_warnings;
	uint8_t dipvalue_fixes;
};

struct dipswitch
{
	/* --- Fields that appear in data files */

	char *name;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	struct dipvalue *dipvalues;

	uint32_t num_dipvalues;

	uint8_t dipswitch_flags;
	uint8_t dipswitch_warnings;
	uint8_t dipswitch_fixes;
};


/* --- Driver Structures --- */

struct driver
{
	/* --- Fields that appear in data files */

	char *status;
	char *emulation;
	char *color;
	char *sound;
	char *graphic;
	char *cocktail;
	char *protection;
	uint32_t palettesize;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	uint8_t driver_flags;
	uint8_t driver_warnings;
	uint8_t driver_fixes;
};


/* --- Dipswitch Structures --- */

struct extension
{
	/* --- Fields that appear in data files */

	char *name;

	/* --- Fields that are calculated by DatLib */

	struct device *device;

	uint8_t extension_flags;
	uint8_t extension_warnings;
	uint8_t extension_fixes;
};

struct device
{
	/* --- Fields that appear in data files */

	char *name;

	/* --- Fields that are calculated by DatLib */

	struct game *game;

	struct extension *extensions;

	uint32_t num_extensions;

	uint8_t device_flags;
	uint8_t device_warnings;
	uint8_t device_fixes;
};


/* --- Game Structures --- */

struct game
{
	/* --- Fields that appear in data files */

	char *name;
	char *sourcefile;
	char *cloneof;
	char *romof;
	char *sampleof;
	char *description;
	char *year;
	char *manufacturer;
	char *history;

	char *rebuildto;

	/* --- Fields that are calculated by DatLib */

	struct game *game_cloneof;
	struct game *game_romof;
	struct game *game_sampleof;

	struct comment *comments;

	struct biosset *biossets;

	struct rom *roms;
	struct rom_idx *rom_name_idx;
	struct rom_idx *rom_crc_idx;

	struct disk *disks;
	struct disk_idx *disk_name_idx;
	struct disk_idx *disk_crc_idx;

	struct sample *samples;
	struct sample_idx *sample_name_idx;

	struct chip *chips;

	struct video *videos;

	struct sound *sounds;

	struct input *inputs;

	struct dipswitch *dipswitches;
	struct dipvalue *dipvalues;

	struct driver *drivers;

	struct device *devices;
	struct extension *extensions;

	uint32_t num_comments;
	uint32_t num_biossets;
	uint32_t num_roms;
	uint32_t num_disks;
	uint32_t num_samples;
	uint32_t num_chips;
	uint32_t num_videos;
	uint32_t num_sounds;
	uint32_t num_inputs;
	uint32_t num_dipswitches;
	uint32_t num_dipvalues;
	uint32_t num_drivers;
	uint32_t num_devices;
	uint32_t num_extensions;

	uint32_t size;
	uint32_t crc;

	uint32_t num_clones;

	uint16_t game_flags;

	uint8_t comment_flags;
	uint8_t biosset_flags;
	uint16_t rom_flags;
	uint16_t disk_flags;
	uint8_t sample_flags;
	uint8_t chip_flags;
	uint8_t video_flags;
	uint8_t sound_flags;
	uint8_t input_flags;
	uint8_t dipswitch_flags;
	uint8_t dipvalue_flags;
	uint8_t driver_flags;
	uint8_t device_flags;
	uint8_t extension_flags;

	uint16_t game_warnings;

	uint8_t comment_warnings;
	uint8_t biosset_warnings;
	uint16_t rom_warnings;
	uint16_t disk_warnings;
	uint8_t sample_warnings;
	uint8_t chip_warnings;
	uint8_t video_warnings;
	uint8_t sound_warnings;
	uint8_t input_warnings;
	uint8_t dipswitch_warnings;
	uint8_t dipvalue_warnings;
	uint8_t driver_warnings;
	uint8_t device_warnings;
	uint8_t extension_warnings;

	uint16_t game_fixes;

	uint8_t comment_fixes;
	uint8_t biosset_fixes;
	uint16_t rom_fixes;
	uint16_t disk_fixes;
	uint8_t sample_fixes;
	uint8_t chip_fixes;
	uint8_t video_fixes;
	uint8_t sound_fixes;
	uint8_t input_fixes;
	uint8_t dipswitch_fixes;
	uint8_t dipvalue_fixes;
	uint8_t driver_fixes;
	uint8_t device_fixes;
	uint8_t extension_fixes;

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

struct game_zip_disk
{
	/* --- Fields that are calculated by DatLib */

	struct game_zip *game_zip;

	struct disk *disk;

	/* --- Fields that are specific to external tools */

	uint32_t flags;
};

struct game_zip_sample
{
	/* --- Fields that are calculated by DatLib */

	struct game_zip *game_zip;

	struct sample *sample;

	/* --- Fields that are specific to external tools */

	uint32_t flags;
};

struct game_zip
{
	/* --- Fields that are calculated by DatLib */

	struct game *game;

	struct game_zip_rom *game_zip_roms;
	struct game_zip_disk *game_zip_disks;
	struct game_zip_sample *game_zip_samples;

	uint32_t num_game_zip_roms;
	uint32_t num_game_zip_disks;
	uint32_t num_game_zip_samples;

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

struct st_idx
{
	char *st;

	uint16_t flags;
};

struct options
{
	char *fn;
	char *log_fn;
	struct dat *info;

	struct clrmamepro clrmamepro;
	uint32_t options;

	char *game_selection;
	char *game_selection_buffer;
	struct st_idx *game_selections;
	uint32_t num_game_selections;

	char *sourcefile_selection;
	char *sourcefile_selection_buffer;
	struct st_idx *sourcefile_selections;
	uint32_t num_sourcefile_selections;

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

	struct datlib_driver *load;
	struct datlib_driver *save;

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
	struct game_idx *game_description_idx;
	struct game_idx *game_crc_idx;
	struct game_idx *game_score_idx;

	struct comment *comments;

	struct biosset *biossets;

	struct rom *roms;
	struct rom_idx *game_rom_name_idx;
	struct rom_idx *game_rom_crc_idx;
	struct rom_idx *rom_name_idx;
	struct rom_idx *rom_crc_idx;

	struct disk *disks;
	struct disk_idx *game_disk_name_idx;
	struct disk_idx *game_disk_crc_idx;
	struct disk_idx *disk_name_idx;
	struct disk_idx *disk_crc_idx;

	struct sample *samples;
	struct sample_idx *game_sample_name_idx;
	struct sample_idx *sample_name_idx;

	struct chip *chips;

	struct video *videos;

	struct sound *sounds;

	struct input *inputs;

	struct dipswitch *dipswitches;
	struct dipvalue *dipvalues;

	struct driver *drivers;

	struct device *devices;
	struct extension *extensions;

	struct game_zip *game_zips;
	struct game_zip_idx *game_zip_name_idx;
	struct game_zip_rom *game_zip_roms;
	struct game_zip_disk *game_zip_disks;
	struct game_zip_sample *game_zip_samples;

	uint32_t num_comments;
	uint32_t num_biossets;
	uint32_t num_games, num_resources, num_machines;
	uint32_t num_roms, num_resource_roms, num_machine_roms;
	uint32_t num_disks, num_resource_disks, num_machine_disks;
	uint32_t num_samples, num_resource_samples, num_machine_samples;
	uint32_t num_chips;
	uint32_t num_videos;
	uint32_t num_sounds;
	uint32_t num_inputs;
	uint32_t num_dipswitches;
	uint32_t num_dipvalues;
	uint32_t num_drivers;
	uint32_t num_devices;
	uint32_t num_extensions;

	uint32_t num_game_zips;
	uint32_t num_game_zip_roms;
	uint32_t num_game_zip_disks;
	uint32_t num_game_zip_samples;

	uint32_t num_parents, num_clones, num_others;

	uint16_t dat_flags;

	uint16_t game_flags;
	uint8_t comment_flags;
	uint8_t biosset_flags;
	uint16_t rom_flags;
	uint16_t disk_flags;
	uint8_t sample_flags;
	uint8_t chip_flags;
	uint8_t video_flags;
	uint8_t sound_flags;
	uint8_t input_flags;
	uint8_t dipswitch_flags;
	uint8_t dipvalue_flags;
	uint8_t driver_flags;
	uint8_t device_flags;
	uint8_t extension_flags;

	uint8_t game_selection_warnings;
	uint8_t sourcefile_selection_warnings;

	uint16_t game_warnings;
	uint8_t comment_warnings;
	uint8_t biosset_warnings;
	uint16_t rom_warnings;
	uint16_t disk_warnings;
	uint8_t sample_warnings;
	uint8_t chip_warnings;
	uint8_t video_warnings;
	uint8_t sound_warnings;
	uint8_t input_warnings;
	uint8_t dipswitch_warnings;
	uint8_t dipvalue_warnings;
	uint8_t driver_warnings;
	uint8_t device_warnings;
	uint8_t extension_warnings;

	uint16_t game_fixes;
	uint8_t comment_fixes;
	uint8_t biosset_fixes;
	uint16_t rom_fixes;
	uint16_t disk_fixes;
	uint8_t sample_fixes;
	uint8_t chip_fixes;
	uint8_t video_fixes;
	uint8_t sound_fixes;
	uint8_t input_fixes;
	uint8_t dipswitch_fixes;
	uint8_t dipvalue_fixes;
	uint8_t driver_fixes;
	uint8_t device_fixes;
	uint8_t extension_fixes;

	uint16_t game_saved;
	uint8_t comment_saved;
	uint8_t biosset_saved;
	uint16_t rom_saved;
	uint16_t disk_saved;
	uint8_t sample_saved;
	uint8_t chip_saved;
	uint8_t video_saved;
	uint8_t sound_saved;
	uint8_t input_saved;
	uint8_t dipswitch_saved;
	uint8_t dipvalue_saved;
	uint8_t driver_saved;
	uint8_t device_saved;
	uint8_t extension_saved;
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
#define OPTION_VERBOSE_LOGGING		0x00000004	// DatUtil -v option
#define OPTION_SHOW_DEBUG_INFO		0x00000008	// DatUtil -d option

#define OPTION_FIX_MERGING_OFF		0x00000010	// DatUtil -x option
#define OPTION_REMOVE_DUPLICATES_OFF	0x00000020	// DatUtil -d option
#define OPTION_LOWER_CASE		0x00000040	// DatUtil -l option
#define OPTION_SORT_GAMES_BY_PARENT	0x00000080	// DatUtil -s option

#define OPTION_GAME_SELECTION		0x00000100	// DatUtil -g option
#define OPTION_CLONE_SELECTION		0x00000200	// DatUtil -c option
#define OPTION_SOURCEFILE_SELECTION	0x00000400	// DatUtil -G option
#define OPTION_INVERT_SELECTION		0x00000800	// DatUtil -! option

#define OPTION_REMOVE_CLONES		0x00001000	// DatUtil -r option
#define OPTION_KEEP_FULL_DETAILS	0x00002000	// DatUtil -k option
#define OPTION_NEBULA_JUKEBOX		0x00004000	// DatUtil -j option
#define OPTION_ALWAYS_QUOTE		0x00008000	// DatUtil -q option

#define OPTION_EXTENDED_CHECKSUMS	0x00010000	// DatUtil -x option
#define OPTION_SHA1_CHECKSUMS		0x00020000	// DatUtil default
#define OPTION_MD5_CHECKSUMS		0x00040000	// DatUtil -m option

#define	OPTION_DAT_FULL_MERGING		0x00100000	// Used by MAMEDiff
#define	OPTION_DAT_SPLIT_MERGING	0x00200000	// Used by MAMEDiff
#define	OPTION_DAT_NO_MERGING		0x00400000	// Used by MAMEDiff
#define	OPTION_NON_SEPERATED_BIOS_ROMS	0x00800000	// Used by MAMEDiff

#define	OPTION_OBJECT_TYPE_ROM		0x01000000	// MAMEDiff -o option
#define	OPTION_OBJECT_TYPE_DISK		0x02000000	// MAMEDiff -o option
#define	OPTION_OBJECT_TYPE_SAMPLE	0x04000000	// MAMEDiff -o option
#define	OPTION_INCLUDE_NODUMPS_IN_ZIPS	0x08000000	// MAMEDiff -z option


/* --- Parser Flags --- */

#define	FLAG_CLRMAMEPRO_HEADER		0x8000


/* --- Dat Flags --- */

#define	FLAG_DAT_FULL_MERGING		0x0001
#define	FLAG_DAT_SPLIT_MERGING		0x0002
#define	FLAG_DAT_NO_MERGING		0x0004


/* --- Selection Flags --- */

#define	FLAG_BAD_GAME_SELECTION		0x01

#define	FLAG_BAD_SOURCEFILE_SELECTION	0x01


/* --- String Index Flags --- */

#define	FLAG_STRING_INDEX_USED		0x0001


/* --- Game Flags --- */

#define	FLAG_GAME_NAME			0x0001
#define	FLAG_RESOURCE_NAME		0x0002
#define	FLAG_MACHINE_NAME		0x0004
#define FLAG_GAME_SOURCEFILE		0x0008
#define FLAG_GAME_CLONEOF		0x0010
#define FLAG_GAME_ROMOF			0x0020
#define FLAG_GAME_SAMPLEOF		0x0040
#define FLAG_GAME_DESCRIPTION		0x0080
#define FLAG_GAME_YEAR			0x0100
#define FLAG_GAME_MANUFACTURER		0x0200
#define FLAG_GAME_HISTORY		0x0400
#define FLAG_GAME_REBUILDTO		0x0800

#define FLAG_GAME_CLONEOFCLONE		0x1000
#define FLAG_GAME_DUPLICATE_NAME	0x2000
#define FLAG_GAME_DUPLICATE_DESCRIPTION	0x4000
#define FLAG_GAME_DUPLICATE_CRC		0x8000


/* --- Comment Flags --- */

#define FLAG_COMMENT_TEXT		0x01


/* --- BIOS Set Flags --- */

#define FLAG_BIOSSET_NAME		0x01
#define FLAG_BIOSSET_DESCRIPTION	0x02
#define FLAG_BIOSSET_DEFAULT		0x04


/* --- ROM Flags --- */

#define FLAG_ROM_NAME			0x0001
#define FLAG_ROM_BIOS			0x0002
#define FLAG_ROM_SIZE			0x0004
#define FLAG_ROM_CRC			0x0008
#define FLAG_ROM_MD5			0x0010
#define FLAG_ROM_SHA1			0x0020
#define FLAG_ROM_MERGE			0x0040
#define FLAG_ROM_REGION			0x0080
#define FLAG_ROM_OFFSET			0x0100
#define FLAG_ROM_STATUS			0x0200
#define FLAG_ROM_DISPOSE		0x0400
#define FLAG_ROM_SOUNDONLY		0x0800

#define FLAG_ROM_DUPLICATE		0x1000
#define FLAG_ROM_SIZE_CONFLICT		0x2000
#define FLAG_ROM_CRC_CONFLICT		0x4000
#define FLAG_ROM_SHA1_MD5_CONFLICT	0x8000


/* --- Disk Flags --- */

#define FLAG_DISK_NAME			0x0001
#define FLAG_DISK_MD5			0x0002
#define FLAG_DISK_SHA1			0x0004
#define FLAG_DISK_MERGE			0x0008
#define FLAG_DISK_REGION		0x0010
#define FLAG_DISK_INDEX			0x0020
#define FLAG_DISK_STATUS		0x0040

#define FLAG_DISK_DUPLICATE		0x1000
#define FLAG_DISK_SIZE_CONFLICT		0x2000
#define FLAG_DISK_CRC_CONFLICT		0x4000
#define FLAG_DISK_SHA1_MD5_CONFLICT	0x8000


/* --- Sample Flags --- */

#define FLAG_SAMPLE_NAME		0x01

#define FLAG_SAMPLE_DUPLICATE		0x02


/* --- Chip Flags --- */

#define FLAG_CHIP_NAME			0x01
#define FLAG_CHIP_TYPE			0x02
#define FLAG_CHIP_SOUNDONLY		0x04
#define FLAG_CHIP_CLOCK			0x08


/* --- Video Flags --- */

#define FLAG_VIDEO_SCREEN		0x01
#define FLAG_VIDEO_ORIENTATION		0x02
#define FLAG_VIDEO_WIDTH		0x04
#define FLAG_VIDEO_HEIGHT		0x08
#define FLAG_VIDEO_ASPECTX		0x10
#define FLAG_VIDEO_ASPECTY		0x20
#define FLAG_VIDEO_REFRESH		0x40


/* --- Sound Flags --- */

#define FLAG_SOUND_CHANNELS		0x01


/* --- Input Flags --- */

#define FLAG_INPUT_SERVICE		0x01
#define FLAG_INPUT_TILT			0x02
#define FLAG_INPUT_PLAYERS		0x04
#define FLAG_INPUT_CONTROL		0x08
#define FLAG_INPUT_BUTTONS		0x10
#define FLAG_INPUT_COINS		0x20


/* --- Dipswitch Flags --- */

#define FLAG_DIPSWITCH_NAME		0x01


/* --- Dipvalue Flags --- */

#define FLAG_DIPVALUE_NAME		0x01
#define FLAG_DIPVALUE_DEFAULT		0x02


/* --- Driver Flags --- */

#define FLAG_DRIVER_STATUS		0x01
#define FLAG_DRIVER_EMULATION		0x02
#define FLAG_DRIVER_COLOR		0x04
#define FLAG_DRIVER_SOUND		0x08
#define FLAG_DRIVER_GRAPHIC		0x10
#define FLAG_DRIVER_COCKTAIL		0x20
#define FLAG_DRIVER_PROTECTION		0x40
#define FLAG_DRIVER_PALETTESIZE		0x80


/* --- Device Flags --- */

#define FLAG_DEVICE_NAME		0x01


/* --- Extension Flags --- */

#define FLAG_EXTENSION_NAME		0x01


#endif /* _DATLIB_TYPE_H_ */
