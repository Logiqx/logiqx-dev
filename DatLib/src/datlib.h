/* --- This include file is used datlib.c and the external tools --- */

#ifndef _DATLIB_H_
#define _DATLIB_H_


/* --- Include types (if not done already) --- */

#include "type.h"


/* --- Function prototypes for use by external tools --- */

void display_datlib_version(void);
int init_buffer1(struct dat *dat, int buf_size, char *size_prefix);
struct dat *init_dat(struct options *options);
int save_dat(struct dat *dat);
struct dat *free_dat(struct dat *dat);

int rom_crc_idx_sort_function(const void *idx1, const void *idx2);
int rom_name_idx_sort_function(const void *idx1, const void *idx2);
int disk_name_idx_sort_function(const void *idx1, const void *idx2);
int sample_name_idx_sort_function(const void *idx1, const void *idx2);
int game_crc_idx_sort_function(const void *idx1, const void *idx2);
int game_name_idx_sort_function(const void *idx1, const void *idx2);
int game_score_idx_sort_function(const void *idx1, const void *idx2);

int find_game_zip_by_name(const void *name, const void *game_zip_idx);
int find_rom_by_crc(const void *crc, const void *rom_idx);
int find_rom_by_comp_crc(const void *crc, const void *rom_idx);
int find_rom_by_name(const void *name, const void *rom_idx);
int find_disk_by_crc(const void *crc, const void *disk_idx);
int find_disk_by_name(const void *name, const void *disk_idx);
int find_sample_by_name(const void *name, const void *sample_idx);
int find_game_by_crc(const void *crc, const void *game_idx);
int find_game_by_name(const void *name, const void *game_idx);

struct ini_entry *load_ini(char *fn);
struct ini_entry *free_ini(struct ini_entry *ini);
char *find_ini_value(struct ini_entry *ini, char *section, char *param);


#endif /* _DATLIB_H_ */
