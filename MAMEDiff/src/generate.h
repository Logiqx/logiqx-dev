/* --------------------------------------------------------------------------
 * MAMEDiff - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for comparing different versions of MAME to identify
 * changes required to your ROM sets.
 * -------------------------------------------------------------------------- */

/* --- Function prototypes for the sorting functions --- */

int generate_changes(struct dat *dat1, struct dat *dat2, int diff_type, int renames, int zeros);


/* --- Flags --- */

#define GAME_ZIP_REMOVED	0x00000001
#define GAME_ZIP_ADDED		0x00000002
#define GAME_ZIP_ROM_REMOVED	0x00000004
#define GAME_ZIP_ROM_ADDED	0x00000008
#define GAME_ZIP_ROM_ELSEWHERE	0x00000010

