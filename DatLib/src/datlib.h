/* --- This include file is used datlib.c and the external tools --- */

#ifndef _DATLIB_H_
#define _DATLIB_H_


/* --- Include types (if not done already) --- */

#include "type.h"


/* --- Function prototypes for use by external tools --- */

void display_datlib_version(void);
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

#define FORMAT_LISTINFO_ROM(ST, ROM) \
{ \
	char size[10]; \
	char crc[9]; \
\
	if (strchr(ROM->name, ' ')) \
		sprintf(ST, "rom ( name \"%s\"", ROM->name); \
	else \
		sprintf(ST, "rom ( name %s", ROM->name); \
\
	if (ROM->merge) \
	{ \
		strcat(ST, " merge "); \
		if (strchr(ROM->merge, ' ')) \
			strcat(ST, "\""); \
		strcat(ST, ROM->merge); \
		if (strchr(ROM->merge, ' ')) \
			strcat(ST, "\""); \
	} \
	\
	if (ROM->size) \
	{ \
		sprintf(size, "%lu", (unsigned long) ROM->size); \
		strcat(ST, " size "); \
		strcat(ST, size); \
	} \
	if (ROM->crc) \
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
	if (ROM->region) \
	{ \
		strcat(ST, " region "); \
		strcat(ST, ROM->region); \
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

#define FORMAT_LISTINFO_DISK(ST, DISK) \
{ \
	if (strchr(DISK->name, ' ')) \
		sprintf(ST, "disk ( name \"%s\"", DISK->name); \
	else \
		sprintf(ST, "disk ( name %s", DISK->name); \
\
	if (DISK->merge) \
	{ \
		strcat(ST, " merge "); \
		if (strchr(DISK->merge, ' ')) \
			strcat(ST, "\""); \
		strcat(ST, DISK->merge); \
		if (strchr(DISK->merge, ' ')) \
			strcat(ST, "\""); \
	} \
	if (DISK->sha1) \
	{ \
		strcat(ST, " sha1 "); \
		strcat(ST, DISK->sha1); \
	} \
	if (DISK->md5) \
	{ \
		strcat(ST, " md5 "); \
		strcat(ST, DISK->md5); \
	} \
	if (DISK->region) \
	{ \
		strcat(ST, " region "); \
		strcat(ST, DISK->region); \
	} \
	if (DISK->disk_flags & FLAG_DISK_BADDUMP) \
	{ \
		strcat(ST, " flags baddump"); \
	} \
	if (DISK->disk_flags & FLAG_DISK_NODUMP) \
	{ \
		strcat(ST, " flags nodump"); \
	} \
	strcat(ST, " )"); \
}

#define FORMAT_LISTINFO_SAMPLE(ST, SAMPLE) \
{ \
	if (strchr(SAMPLE->name, ' ')) \
		sprintf(ST, "sample \"%s\"", SAMPLE->name); \
	else \
		sprintf(ST, "sample %s", SAMPLE->name); \
}

#endif /* _DATLIB_H_ */
