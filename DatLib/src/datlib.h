/* --- This include file is used datlib.c and the external tools --- */

#ifndef _DATLIB_H_
#define _DATLIB_H_


/* --- Include types (if not done already) --- */

#include "type.h"


/* --- Function prototypes for use by external tools --- */

void display_datlib_version(void);
struct dat *init_dat(char *fn, uint32_t options, char *game, char *log_fn);
int save_dat(struct dat *dat, char *save_name, char *save_mode, char *save_format);
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
int find_disk_by_name(const void *name, const void *disk_idx);
int find_sample_by_name(const void *name, const void *sample_idx);
int find_game_by_crc(const void *crc, const void *game_idx);
int find_game_by_name(const void *name, const void *game_idx);

struct ini_entry *load_ini(char *fn);
struct ini_entry *free_ini(struct ini_entry *ini);
char *find_ini_value(struct ini_entry *ini, char *section, char *param);


/* --- Useful DatLib macros (to be converted to functions) --- */

#define FORMAT_GAME_NAME(ST, GAME) \
{ \
	strcpy(ST, GAME->description); \
	strcat(ST, " [name: "); \
	strcat(ST, GAME->name); \
	if (GAME->cloneof) \
	{ \
		strcat(ST, " - parent: "); \
		strcat(ST, GAME->cloneof); \
	} \
	strcat(ST, "]"); \
}

/*#define FORMAT_ROM_NAME(ST, ROM) \
{ \
	if (ROM->merge) \
		sprintf(ST, "rom ( name %s merge %s size %lu crc %08lx ", ROM->name, ROM->merge, (unsigned long) ROM->size, (unsigned long) ROM->crc); \
	else \
		sprintf(ST, "rom ( name %s size %lu crc %08lx ", ROM->name, (unsigned long) ROM->size, (unsigned long) ROM->crc); \
	strcat(ST, ")"); \
}*/

#define FORMAT_ROM_NAME(ST, ROM) \
{ \
	char crc[9]; \
\
	if (ROM->merge) \
		sprintf(ST, "rom ( name %s merge %s size %lu", ROM->name, ROM->merge, (unsigned long) ROM->size); \
	else \
		sprintf(ST, "rom ( name %s size %lu", ROM->name, (unsigned long) ROM->size); \
	if (!(ROM->rom_flags & FLAG_ROM_NODUMP)) \
	{ \
		sprintf(crc, "%08lx", (unsigned long) ROM->crc); \
		strcat(ST, " crc "); \
		strcat(ST, crc); \
	} \
	if (ROM->sha1) \
	{ \
		strcat(ST, " sha1 "); \
		strcat(ST, ROM->sha1); \
	} \
	if (ROM->md5) \
	{ \
		strcat(ST, " md5 "); \
		strcat(ST, ROM->md5); \
	} \
	if (ROM->rom_flags & FLAG_ROM_BADDUMP) \
	{ \
		strcat(ST, " flags baddump"); \
	} \
	if (ROM->rom_flags & FLAG_ROM_NODUMP) \
	{ \
		strcat(ST, " flags nodump"); \
	} \
	strcat(ST, " )"); \
}

#endif /* _DATLIB_H_ */
