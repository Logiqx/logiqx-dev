/* --------------------------------------------------------------------------
 * ImgChk - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for checking resource images
 * -------------------------------------------------------------------------- */

/* --- Function prototypes --- */

int process_section(struct ini_entry *, struct dat *, char *);
int check_zip(struct dat *, char *, char *, int, int, int, int, int);
int check_dir(struct dat *, char *, char *, int, int, int, int, int);
int check_img(struct dat *, char *, char *, int, int, int, int, int);
