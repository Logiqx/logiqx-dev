/* --------------------------------------------------------------------------
 * AVI2CDVC - Written by Logiqx (http://www.logiqx.com/)
 *
 * A little tool that alters the FourCC of AVI files to 'cdvc' (Canopus DV)
 * -------------------------------------------------------------------------- */

/* --- Scan types --- */

#define PROCESS_DIR    0x0001
#define PROCESS_FILE   0x0002


/* --- Function protoypes --- */

int process_dir(char *, int, char *, char *);
int process_file(char *, char *, char *);
