/* --------------------------------------------------------------------------
 * MAMEDiff - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for comparing different versions of MAME to identify
 * changes required to your ROM sets.
 * -------------------------------------------------------------------------- */

/* --- Macros that used to be in DatLib but only used by MAMEDiff now! --- */

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
	char offset[10]; \
\
	if (strchr(ROM->name, ' ')) \
		sprintf(ST, "rom ( name \"%s\"", ROM->name); \
	else \
		sprintf(ST, "rom ( name %s", ROM->name); \
\
	if (ROM->rom_flags & FLAG_ROM_MERGE) \
	{ \
		strcat(ST, " merge "); \
		if (strchr(ROM->merge, ' ')) \
			strcat(ST, "\""); \
		strcat(ST, ROM->merge); \
		if (strchr(ROM->merge, ' ')) \
			strcat(ST, "\""); \
	} \
	if (ROM->rom_flags & FLAG_ROM_BIOS) \
	{ \
		strcat(ST, " bios "); \
		if (strchr(ROM->bios, ' ')) \
			strcat(ST, "\""); \
		strcat(ST, ROM->bios); \
		if (strchr(ROM->bios, ' ')) \
			strcat(ST, "\""); \
	} \
	if (ROM->rom_flags & FLAG_ROM_SIZE) \
	{ \
		sprintf(size, "%lu", (unsigned long) ROM->size); \
		strcat(ST, " size "); \
		strcat(ST, size); \
	} \
	if (ROM->rom_flags & FLAG_ROM_CRC) \
	{ \
		sprintf(crc, "%08lx", (unsigned long) ROM->crc); \
		strcat(ST, " crc "); \
		strcat(ST, crc); \
	} \
	if (ROM->rom_flags & FLAG_ROM_SHA1) \
	{ \
		strcat(ST, " sha1 "); \
		strcat(ST, ROM->sha1); \
	} \
	if (ROM->rom_flags & FLAG_ROM_MD5) \
	{ \
		strcat(ST, " md5 "); \
		strcat(ST, ROM->md5); \
	} \
	if (ROM->rom_flags & FLAG_ROM_REGION) \
	{ \
		strcat(ST, " region "); \
		strcat(ST, ROM->region); \
	} \
	if (strcmp(ROM->status, "")) \
	{ \
		strcat(ST, " flags "); \
		strcat(ST, ROM->status); \
	} \
	if (ROM->rom_flags & FLAG_ROM_DISPOSE) \
	{ \
		if (!strcmp(ROM->dispose, "yes")) \
			strcat(ST, " flags dispose"); \
	} \
	if (ROM->rom_flags & FLAG_ROM_SOUNDONLY) \
	{ \
		if (!strcmp(ROM->soundonly, "yes")) \
			strcat(ST, " flags soundonly"); \
	} \
	if (ROM->rom_flags & FLAG_ROM_OFFSET) \
	{ \
		sprintf(offset, "%lx", (unsigned long) ROM->offset); \
		strcat(ST, " offs "); \
		strcat(ST, offset); \
	} \
	strcat(ST, " )"); \
}

#define FORMAT_LISTINFO_DISK(ST, DISK) \
{ \
	char index[10]; \
\
	if (strchr(DISK->name, ' ')) \
		sprintf(ST, "disk ( name \"%s\"", DISK->name); \
	else \
		sprintf(ST, "disk ( name %s", DISK->name); \
\
	if (DISK->disk_flags & FLAG_DISK_MERGE) \
	{ \
		strcat(ST, " merge "); \
		if (strchr(DISK->merge, ' ')) \
			strcat(ST, "\""); \
		strcat(ST, DISK->merge); \
		if (strchr(DISK->merge, ' ')) \
			strcat(ST, "\""); \
	} \
	if (DISK->disk_flags & FLAG_DISK_SHA1) \
	{ \
		strcat(ST, " sha1 "); \
		strcat(ST, DISK->sha1); \
	} \
	if (DISK->disk_flags & FLAG_DISK_MD5) \
	{ \
		strcat(ST, " md5 "); \
		strcat(ST, DISK->md5); \
	} \
	if (DISK->disk_flags & FLAG_DISK_REGION) \
	{ \
		strcat(ST, " region "); \
		strcat(ST, DISK->region); \
	} \
	if (DISK->disk_flags & FLAG_DISK_INDEX) \
	{ \
		sprintf(index, "%lx", (unsigned long) DISK->index); \
		strcat(ST, " index "); \
		strcat(ST, index); \
	} \
	if (strcmp(DISK->status, "")) \
	{ \
		strcat(ST, " flags "); \
		strcat(ST, DISK->status); \
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

