/* --------------------------------------------------------------------------
 * DatUtil - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for converting, cleansing and comparing ROM manager
 * dats (e.g. ClrMamePro, RomCenter).
 * -------------------------------------------------------------------------- */

/* --- DatUtil Options --- */

struct options
{
	struct clrmamepro clrmamepro;
	uint32_t options;
	char *game;

	char *save_name;
	char *save_mode;
	char *save_format;
};

