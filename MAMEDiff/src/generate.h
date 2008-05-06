/* --------------------------------------------------------------------------
 * MAMEDiff - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for comparing different versions of MAME to identify
 * changes required to your ROM sets.
 * -------------------------------------------------------------------------- */

/* --- Function prototypes for the sorting functions --- */

int generate_changes(struct dat *dat1, struct dat *dat2, int diff_type, int renames, int zeros, int exclude_removals, int object_type);


/* --- Flags --- */

#define GAME_ZIP_REMOVED		0x00000001
#define GAME_ZIP_ADDED			0x00000002

#define GAME_ZIP_ROM_REMOVED		0x00000010
#define GAME_ZIP_ROM_ADDED		0x00000020
#define GAME_ZIP_ROM_ELSEWHERE		0x00000040

#define GAME_ZIP_DISK_REMOVED		0x00000100
#define GAME_ZIP_DISK_ADDED		0x00000200
#define GAME_ZIP_DISK_ELSEWHERE		0x00000400

#define GAME_ZIP_SAMPLE_REMOVED		0x00001000
#define GAME_ZIP_SAMPLE_ADDED		0x00002000
#define GAME_ZIP_SAMPLE_ELSEWHERE	0x00004000

