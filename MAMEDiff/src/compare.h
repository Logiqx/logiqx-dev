/* --------------------------------------------------------------------------
 * MAMEDiff - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for comparing different versions of MAME to identify
 * changes required to your ROM sets.
 * -------------------------------------------------------------------------- */

/* --- Comparison structures --- */

struct game_change
{
	struct game *game1;
	struct game *game2;

	struct rom_change *rom_changes;
	uint32_t num_rom_changes;

	struct disk_change *disk_changes;
	uint32_t num_disk_changes;

	struct sample_change *sample_changes;
	uint32_t num_sample_changes;

	uint32_t game_flags;
	uint32_t rom_flags;
	uint32_t disk_flags;
	uint32_t sample_flags;
};

struct rom_change
{
	struct rom *rom1;
	struct rom *rom2;

	uint32_t rom_flags;
};

struct disk_change
{
	struct disk *disk1;
	struct disk *disk2;

	uint32_t disk_flags;
};

struct sample_change
{
	struct sample *sample1;
	struct sample *sample2;

	uint32_t sample_flags;
};


/* --- Function prototypes for comparisons --- */

int standard_compare(struct dat *dat1, struct dat *dat2, int verbose, int caesar, int set_type);

void report_game_changes(FILE *, uint16_t, uint16_t, uint8_t, uint8_t, char *, struct dat *, struct game_change *, int, int);
void report_required_roms(FILE *, uint16_t, uint16_t, char *, struct game_change *, int);
int report_required_rebuilds(FILE *, struct dat *, uint16_t, uint16_t, uint16_t, uint16_t, char *, struct game_change *, int);
void print_game(FILE *, struct game *);


/* --- Game flags --- */

#define PROCESSED       0x0001

#define GAME_RENAMED    0x0010  /* Name of game changed */
#define GAME_ADDED      0x0020  /* Game only exists in 2nd dat */
#define GAME_REMOVED    0x0040  /* Game only exists in 1st dat */
#define GAME_NEW_CLONE  0x0080  /* Cloneof property of game changed */


/* --- ROM flags --- */

#define ROM_RENAMED     0x0001  /* Name has changed for some ROMs in game */
#define ROM_ADDED       0x0002  /* ROMs were added to the game in dat2 */
#define ROM_REMOVED     0x0004  /* ROMs were removed from the game */
#define ROM_COMP_CRC    0x0008  /* ROM CRCs were complimented for some ROMs in the game */

#define P_ROM_RENAMED   0x0010  /* Name has changed for some ROMs in parent */
#define P_ROM_ADDED     0x0020  /* ROMs were added to the parent in dat2 */
#define P_ROM_REMOVED   0x0040  /* ROMs were removed from the parent */
#define P_ROM_COMP_CRC  0x0080  /* ROMs CRCs were complimented */

#define ROM_MERGED      0x0100  /* ROM merging now used for some ROMs in game */
#define ROM_UNMERGED    0x0200  /* ROM merging stopped for some ROMs in game */


/* --- Disk flags --- */

#define DISK_RENAMED    0x01    /* Name has changed for some disks in game */
#define DISK_ADDED      0x02    /* Disks were added to the game in dat2 */
#define DISK_REMOVED    0x04    /* Disks were removed from the game */


/* --- Sample flags --- */

#define SAMPLE_RENAMED  0x01    /* Samples were added to the game in dat2 */
#define SAMPLE_ADDED    0x02    /* Samples were added to the game in dat2 */
#define SAMPLE_REMOVED  0x04    /* Samples were removed from the game */

