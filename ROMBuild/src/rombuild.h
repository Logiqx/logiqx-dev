/* --------------------------------------------------------------------------
 * ROMBuild - Written by Logiqx (http://www.logiqx.com)
 *
 * A simple little utility for re-building ROMs
 * -------------------------------------------------------------------------- */

/* --- Dat library includes --- */

#include "datlib/src/macro.h"


/* --- Types of ROMBuild operation --- */

enum
{
	FULL_COPY,
	ODD_COPY,
	EVEN_COPY,
	BLOCK_FILL,
	COMBINE_ODD,
	COMBINE_EVEN,
	LOWER_COPY,
	LOWER_SHIFT
};

/* --- Structures --- */

struct Patch
{
	unsigned long address;
	unsigned char value;
};

struct Region
{
	char *game;
	char *rom;
	unsigned long size;
	unsigned long crc;
	unsigned long offset;
	unsigned long length;
};

struct Rom
{
	int type;
	struct Region local;
	struct Region mame;
	struct Patch *patch;
};

struct Emulator
{
	char *id;
	char *descr;
	struct Rom *roms;
};

struct Cache
{
	struct Rom *rom;
	char file[MAX_FILENAME_LENGTH+1];
};


/* --- Function prototypes --- */

int find_emulator(char *);
int find_game(char *, char *);
void list_ems();
void list_games(int);
void list_roms(int, int);
void full_list();
int rebuild_roms(int, int, char *, char *);
int scan_dir(char *, struct Cache *rom_cache);
int copy_region(char *, struct Cache *cache);
int combine_region(char *, struct Cache *, struct Cache *);
int combine_region_2(char *, struct Cache *, struct Cache *);
int fill_region(char *, struct Cache *);

