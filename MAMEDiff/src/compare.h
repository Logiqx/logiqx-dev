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

	uint32_t flags;
};

struct rom_change
{
	struct rom *rom1;
	struct rom *rom2;

	uint32_t flags;
};


/* --- Function prototypes for comparisons --- */

int standard_compare(struct dat *dat1, struct dat *dat2, int verbose, int caesar, int set_type);

void report_game_changes(FILE *, unsigned long, char *, struct rom_idx *, long, struct game_change *, int, int);
void report_required_roms(FILE *, unsigned long, char *, struct game_change *, int);
int report_required_rebuilds(FILE *, struct dat *, int, int, char *, struct game_change *, int);
void print_game(FILE *, struct game *);


/* --- Comparison flags --- */

#define PROCESSED       0x00000001

#define GAME_RENAMED    0x00000002  /* name of game changed */
#define GAME_NEW_CLONE  0x00000004  /* cloneof property of game changed */
#define GAME_ADDED      0x00000008  /* game only exists in 2nd dat */
#define GAME_REMOVED    0x00000010  /* game only exists in 1st dat */

#define ROMS_CHANGED    0x00000020  /* only used by ZIP comparison routines */
#define ROMS_RENAMED    0x00000040  /* name has changed for some ROMs in game */
#define ROMS_MERGED     0x00000080  /* merging now used for some ROMs in game */
#define ROMS_UNMERGED   0x00000100  /* merging stopped for some ROMs in game */
#define ROMS_ADDED      0x00000200  /* ROMs were added to the game in dat2 */
#define ROMS_REMOVED    0x00000400  /* ROMs were removed from the game */

#define P_ROMS_CHANGED  0x00000800  /* currently UNUSED by MameDiff */
#define P_ROMS_RENAMED  0x00001000  /* name has changed for some ROMs in parent */
#define P_ROMS_ADDED    0x00002000  /* ROMs were added to the parent in dat2 */
#define P_ROMS_REMOVED  0x00004000  /* ROMs were removed from the parent */

#define ROMS_COMP_CRC   0x00008000  /* ROMs CRCs were complimented */
#define P_ROMS_COMP_CRC 0x00010000  /* ROMs CRCs were complimented */
