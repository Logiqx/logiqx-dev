/* --- Scan types --- */

#define SCAN_DIR    0x0001
#define SCAN_FILE   0x0002

/* --- Function protoypes --- */

int scan_dir(FILE *, char *);
int process_zip(FILE *, char *);
