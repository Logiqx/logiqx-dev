/* --- Constants --- */

#define PNG_FORMAT 1
#define JPG_FORMAT 2


/* --- Function prototypes --- */

int scan_dir(char *dir, int);
int file_details(char *fn, struct stat *buf, int);
