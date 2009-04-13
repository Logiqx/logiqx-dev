/* --------------------------------------------------------------------------
 * ZIPIdent - Written by Logiqx (http://www.logiqx.com/)
 *
 * Little tool that tries to identify ZIP files that are emulated by MAME
 * -------------------------------------------------------------------------- */

/* --- ZipIdent structures --- */

struct zip_entry
{
	/* --- Information from the actual ZIP --- */

	char name[MAX_FILENAME_LENGTH+1];
	char lname[MAX_FILENAME_LENGTH+1];
	uint64_t size;
	uint32_t crc;

	/* --- Information derived by ZipIdent --- */

	char *region;
	uint32_t match;
};

struct game_match
{
	struct game *game;
	double score;
};

struct dummy_rom
{
	uint64_t size;
	uint32_t crc;
};

struct dummy_rom dummy_roms[] =
{
	{       1, 0xd202ef8d},
	{       2, 0x41d912ff},
	{       4, 0x2144df1c},
	{       8, 0x6522df69},
	{      16, 0xecbb4b55},
	{      32, 0x190a55ad},
	{      64, 0x758d6336},
	{     128, 0xc2a8fa9d},
	{     256, 0x0d968558},
	{     512, 0xb2aa7578},
	{    1024, 0xefb5af2e},
	{    2048, 0xf1e8ba9e},
	{    4096, 0xc71c0011},
	{    8192, 0xd8f49994},
	{   16384, 0xab54d286},
	{   32768, 0x011ffca6},
	{   65536, 0xd7978eeb},
	{  131072, 0x7ee8cdcd},
	{  262144, 0xe20eea22},
	{  524288, 0x75660aac},
	{ 1048576, 0xa738ea1c},
	{ 2097152, 0x8d89877e},
	{ 4194304, 0x1147406a},
	{ 8388608, 0x1ad2bc45},
	{16777216, 0xa47ca14a},

	/* --- list terminator --- */
	{       0, 0x00000000}
};


/* --- Function protoypes --- */

int scan_dir(FILE *, FILE *, struct dat *, struct game_match *, char *, char *);
int process_text(FILE *, FILE *, struct dat *, struct game_match *, char *, char *);
int process_zip(FILE *, FILE *, struct dat *, struct game_match *, char *, char *);
int process_entries(FILE *, FILE *, struct dat *, struct game_match *, char *, struct zip_entry *, int, char *);


/* --- Scan types --- */

#define SCAN_DIR    0x0001
#define SCAN_TEXT   0x0002
#define SCAN_FILE   0x0003


/* --- Match flags --- */

#define SIZE_MATCH    0x0001
#define NAME_MATCH    0x0002
#define CRC_MATCH     0x0004
#define PERFECT_MATCH (CRC_MATCH+NAME_MATCH+SIZE_MATCH)


/* --- Useful macros --- */

#define FORMAT_GAME_NAME(ST, GAME) \
{ \
	strcpy(ST, GAME->description); \
	strcat(ST, " [name: "); \
	strcat(ST, GAME->name); \
	if (GAME->cloneof) \
	{ \
		strcat(ST, " - parent: "); \
		strcat(ST, GAME->cloneof); \
	} \
	strcat(ST, "]"); \
}

#define MATCH_ROM \
{ \
	match=0; \
	if (rom_match->rom->crc==zip_entry[i].crc || rom_match->rom->crc==~zip_entry[i].crc) \
		match|=CRC_MATCH; \
	if (rom_match->rom->size==zip_entry[i].size) \
		match|=SIZE_MATCH; \
	if (!strcmp(rom_match->rom->name, zip_entry[i].lname)) \
		match|=NAME_MATCH; \
\
	if (match > rom_match->rom->match) \
		rom_match->rom->match=match; \
\
	if (match > zip_entry[i].match) \
	{ \
		zip_entry[i].match=match; \
		zip_entry[i].region=rom_match->rom->region; \
	} \
\
	for (j=found=0; !found && j<num_game_matches; j++) \
	{ \
		if (rom_match->rom->game==game_match[j].game) \
		found++; \
	} \
\
	if (!found) \
	{ \
		game_match[num_game_matches].game=rom_match->rom->game; \
		num_game_matches++; \
	} \
\
	rom_match++; \
}
