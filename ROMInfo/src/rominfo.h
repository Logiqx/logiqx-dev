/* --------------------------------------------------------------------------
 * ROMInfo - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for identifying emulators that use a specified ROM
 * -------------------------------------------------------------------------- */

/* --- Function prototypes --- */

struct crc *load_crcs(int, char **);
struct crc *free_crcs(struct crc *);

int scan_dirs(struct ini_entry *, struct crc *);
int scan_dir(FILE *, char *, struct crc *);
int scan_dat(FILE *, char *, struct crc *);


/* --- Structures --- */

struct crc
{
	char *fn;
	uint32_t crc;
};
