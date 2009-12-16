/* --------------------------------------------------------------------------
 * ROMBuild - Written by Logiqx (http://www.logiqx.com/)
 *
 * A simple little utility for re-building ROMs
 * -------------------------------------------------------------------------- */

/* --- ROMBuild definitions and macros --- */

#include "rombuild.h"


struct Rom qsound_player_roms[] =
{
	{
		FULL_COPY,
		{"sfa", "sfz_12-a.rom", 524288, 0x207b8d90, 0, 524288},
		{"sfa", "sfz.12m", 2097152, 0x8bdbc4b4, 0, 524288},
	},
	{
		FULL_COPY,
		{"sfa", "sfz_11-a.rom", 524288, 0x5aef5091, 0, 524288},
		{"sfa", "sfz.11m", 2097152, 0xc4b093cd, 0, 524288},
	},
	{
		FULL_COPY,
		{"sfa", "sfz_11-b.rom", 524288, 0x1a7b31a3, 0, 524288},
		{"sfa", "sfz.11m", 2097152, 0xc4b093cd, 524288, 524288},
	},
	{
		FULL_COPY,
		{"sfa", "sfz_12-b.rom", 524288, 0xd2958f9b, 0, 524288},
		{"sfa", "sfz.12m", 2097152, 0x8bdbc4b4, 524288, 524288},
	},
	{
		FULL_COPY,
		{"sfa", "sfz_11-c.rom", 524288, 0xf4540c35, 0, 524288},
		{"sfa", "sfz.11m", 2097152, 0xc4b093cd, 1048576, 524288},
	},
	{
		FULL_COPY,
		{"sfa", "sfz_12-c.rom", 524288, 0x8673691e, 0, 524288},
		{"sfa", "sfz.12m", 2097152, 0x8bdbc4b4, 1048576, 524288},
	},
	{
		FULL_COPY,
		{"sfa", "sfz_11-d.rom", 524288, 0x3a88e8da, 0, 524288},
		{"sfa", "sfz.11m", 2097152, 0xc4b093cd, 1572864, 524288},
	},
	{
		FULL_COPY,
		{"sfa", "sfz_12-d.rom", 524288, 0x545f3cc3, 0, 524288},
		{"sfa", "sfz.12m", 2097152, 0x8bdbc4b4, 1572864, 524288},
	},
	{
		FULL_COPY,
		{"vsavior", "vsavior.11a", 2097152, 0xf2b92cff, 0, 2097152},
		{"vsav", "vm3.11m", 4194304, 0xe80e956e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"vsavior", "vsavior.12a", 2097152, 0x51564e82, 0, 2097152},
		{"vsav", "vm3.12m", 4194304, 0x9cd71557, 0, 2097152},
	},
	{
		FULL_COPY,
		{"vsavior", "vsavior.11b", 2097152, 0x7927e272, 0, 2097152},
		{"vsav", "vm3.11m", 4194304, 0xe80e956e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"vsavior", "vsavior.12b", 2097152, 0xc80293e6, 0, 2097152},
		{"vsav", "vm3.12m", 4194304, 0x9cd71557, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mvscap", "mvsc.12a", 2097152, 0xf255dccb, 0, 2097152},
		{"mvscr1", "mvc.12m", 4194304, 0x7ccb1896, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mvscap", "mvsc.12b", 2097152, 0xd1583593, 0, 2097152},
		{"mvscr1", "mvc.12m", 4194304, 0x7ccb1896, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mvscap", "mvsc.11a", 2097152, 0x1bab466f, 0, 2097152},
		{"mvscr1", "mvc.11m", 4194304, 0x850fe663, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mvscap", "mvsc.11b", 2097152, 0xc2e8c3dc, 0, 2097152},
		{"mvscr1", "mvc.11m", 4194304, 0x850fe663, 2097152, 2097152},
	},
	{0}
};

struct Rom sideway_roms[] =
{
	{
		FULL_COPY,
		{"rr",       "rr.h",       1024, 0xcf44da32,    0, 1024},
		{"desertgu", "9316.1h",    2048, 0xc0030d7c, 1024, 1024},
	},
	{
		FULL_COPY,
		{"rr",       "rr.g",       1024, 0x1c8a04e7,    0, 1024},
		{"desertgu", "9316.1g",    2048, 0x1ddde10b, 1024, 1024},
	},
	{0}
};

struct Rom kungfu_roms[] =
{
	{
		FULL_COPY,
		{"kungfub", "kf9", 16384, 0x05fcce8b, 0, 8192},
		{"kungfub2", "b-3n-.bin", 8192, 0x28a213aa, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf9", 16384, 0x05fcce8b, 8192, 8192},
		{"kungfub2", "b-4n-.bin", 8192, 0xd5228df3, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf14", 16384, 0x1df11d81, 0, 8192},
		{"kungfub2", "b-4c-.bin", 8192, 0x01298885, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf14", 16384, 0x1df11d81, 8192, 8192},
		{"kungfub2", "b-4e-.bin", 8192, 0xc77b87d4, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf13", 16384, 0x2d3b69dd, 0, 8192},
		{"kungfub2", "b-4d-.bin", 8192, 0x6a70615f, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf13", 16384, 0x2d3b69dd, 8192, 8192},
		{"kungfub2", "b-4a-.bin", 8192, 0x6189d626, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf12", 16384, 0xed719d7b, 0, 8192},
		{"kungfub2", "b-4l-.bin", 8192, 0xbd1c2261, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf12", 16384, 0xed719d7b, 8192, 8192},
		{"kungfub2", "b-4h-.bin", 8192, 0x8ac5ed3a, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf11", 16384, 0x85591db2, 0, 8192},
		{"kungfub2", "b-4k-.bin", 8192, 0x16fb5150, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf11", 16384, 0x85591db2, 8192, 8192},
		{"kungfub2", "b-4f-.bin", 8192, 0x67745a33, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf10", 16384, 0xdc675003, 0, 8192},
		{"kungfub2", "b-4m-.bin", 8192, 0xb16de4f2, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf10", 16384, 0xdc675003, 8192, 8192},
		{"kungfub2", "b-3m-.bin", 8192, 0xeba0d66b, 0, 8192},
	},
	{0}
};

struct Rom jumpbug_roms[] =
{
	{
		FULL_COPY,
		{"jumpbug", "jb1.prg", 16384, 0xb223fca9, 0, 4096},
		{"jumpbugb", "jb1", 4096, 0x415aa1b7, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb1.prg", 16384, 0xb223fca9, 4096, 4096},
		{"jumpbugb", "jb2", 4096, 0xb1c27510, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb1.prg", 16384, 0xb223fca9, 8192, 4096},
		{"jumpbugb", "jb3b", 4096, 0xcb8b8a0f, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb1.prg", 16384, 0xb223fca9, 12288, 4096},
		{"jumpbugb", "jb4", 4096, 0x66751d12, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb2.prg", 10240, 0x1b2eb25f, 0, 4096},
		{"jumpbugb", "jb5b", 4096, 0x7553b5e2, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb2.prg", 10240, 0x1b2eb25f, 4096, 4096},
		{"jumpbugb", "jb6b", 4096, 0x47be9843, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb2.prg", 10240, 0x1b2eb25f, 8192, 2048},
		{"jumpbugb", "jb7b", 2048, 0x460aed61, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb3.gfx", 12288, 0x44240cbe, 0, 2048},
		{"jumpbugb", "jbl", 2048, 0x9a091b0a, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb3.gfx", 12288, 0x44240cbe, 2048, 2048},
		{"jumpbugb", "jbm", 2048, 0x8a0fc082, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb3.gfx", 12288, 0x44240cbe, 4096, 2048},
		{"jumpbugb", "jbn", 2048, 0x155186e0, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb3.gfx", 12288, 0x44240cbe, 6144, 2048},
		{"jumpbugb", "jbi", 2048, 0x7749b111, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb3.gfx", 12288, 0x44240cbe, 8192, 2048},
		{"jumpbugb", "jbj", 2048, 0x06e8d7df, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpbug", "jb3.gfx", 12288, 0x44240cbe, 10240, 2048},
		{"jumpbugb", "jbk", 2048, 0xb8dbddf3, 0, 2048},
	},
	{0}
};

struct Rom invadersaver_roms[] =
{
	{
		FULL_COPY,
		{"invaders",  "invaders.rom", 8192, 0xb64ca815,     0, 2048},
		{"invaders",  "invaders.h",   2048, 0x734f5ad8,     0, 2048},
	},
	{
		FULL_COPY,
		{"invaders",  "invaders.rom", 8192, 0xb64ca815,  2048, 2048},
		{"invaders",  "invaders.g",   2048, 0x6bfaca4a,     0, 2048},
	},
	{
		FULL_COPY,
		{"invaders",  "invaders.rom", 8192, 0xb64ca815,  4096, 2048},
		{"invaders",  "invaders.f",   2048, 0x0ccead96,     0, 2048},
	},
	{
		FULL_COPY,
		{"invaders",  "invaders.rom", 8192, 0xb64ca815,  6144, 2048},
		{"invaders",  "invaders.e",   2048, 0x14e538b0,     0, 2048},
	},
	{
		FULL_COPY,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,     0, 2048},
		{"invaddlx",  "invdelux.h",    2048, 0xe690818f,     0, 2048},
	},
	{
		FULL_COPY,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,  2048, 2048},
		{"invaddlx",  "invdelux.g",    2048, 0x4268c12d,     0, 2048},
	},
	{
		FULL_COPY,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,  4096, 2048},
		{"invaddlx",  "invdelux.f",    2048, 0xf4aa1880,     0, 2048},
	},
	{
		FULL_COPY,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,  6144, 2048},
		{"invaddlx",  "invdelux.e",    2048, 0x408849c1,     0, 2048},
	},
	{
		BLOCK_FILL,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,  8192, 2048},
		{"	", "  ",		0, 0x00000000,      0,   0},
	},
	{
		BLOCK_FILL,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,  10240, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		BLOCK_FILL,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,  12288, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		BLOCK_FILL,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,  14336, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		FULL_COPY,
		{"invdelux",  "invdelux.rom", 18432, 0xe3e1683e,  16384, 2048},
		{"invaddlx",  "invdelux.d",    2048, 0xe8d5afcd,      0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,     0, 2048},
		{"lrescue",  "lrescue.1",    2048, 0x2bbc4778,     0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  2048, 2048},
		{"lrescue",  "lrescue.2",    2048, 0x49e79706,     0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  4096, 2048},
		{"lrescue",  "lrescue.3",    2048, 0x1ac969be,     0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  6144, 2048},
		{"lrescue",  "lrescue.4",    2048, 0x782fee3c,     0, 2048},
	},
	{
		BLOCK_FILL,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  8192, 2048},
		{"	", "  ",		0, 0x00000000,      0,   0},
	},
	{
		BLOCK_FILL,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  10240, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		BLOCK_FILL,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  12288, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		BLOCK_FILL,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  14336, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  16384, 2048},
		{"lrescue",  "lrescue.5",    2048, 0x58fde8bc,      0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  18432, 2048},
		{"lrescue",  "lrescue.6",    2048, 0xbfb0f65d,      0, 2048},
	},
	{0}
};

struct Rom side_roms[] =
{
	{
		FULL_COPY,
		{"invaders",  "invaders.rom", 8192, 0xb64ca815,     0, 2048},
		{"invaders",  "invaders.h",   2048, 0x734f5ad8,     0, 2048},
	},
	{
		FULL_COPY,
		{"invaders",  "invaders.rom", 8192, 0xb64ca815,  2048, 2048},
		{"invaders",  "invaders.g",   2048, 0x6bfaca4a,     0, 2048},
	},
	{
		FULL_COPY,
		{"invaders",  "invaders.rom", 8192, 0xb64ca815,  4096, 2048},
		{"invaders",  "invaders.f",   2048, 0x0ccead96,     0, 2048},
	},
	{
		FULL_COPY,
		{"invaders",  "invaders.rom", 8192, 0xb64ca815,  6144, 2048},
		{"invaders",  "invaders.e",   2048, 0x14e538b0,     0, 2048},
	},
	{0}
};

struct Rom vbemusaver_roms[] =
{
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,     0, 2048},
		{"lrescue",  "lrescue.1",    2048, 0x2bbc4778,     0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  2048, 2048},
		{"lrescue",  "lrescue.2",    2048, 0x49e79706,     0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  4096, 2048},
		{"lrescue",  "lrescue.3",    2048, 0x1ac969be,     0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  6144, 2048},
		{"lrescue",  "lrescue.4",    2048, 0x782fee3c,     0, 2048},
	},
	{
		BLOCK_FILL,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  8192, 2048},
		{"	", "  ",		0, 0x00000000,      0,   0},
	},
	{
		BLOCK_FILL,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  10240, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		BLOCK_FILL,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  12288, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		BLOCK_FILL,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  14336, 2048},
		{"	", "  ",		0, 0x00000000,      0,    0},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  16384, 2048},
		{"lrescue",  "lrescue.5",    2048, 0x58fde8bc,      0, 2048},
	},
	{
		FULL_COPY,
		{"lrescue",  "lrescue.rom", 20480, 0x46f5b924,  18432, 2048},
		{"lrescue",  "lrescue.6",    2048, 0xbfb0f65d,      0, 2048},
	},
	{0}
};

struct Rom pacsaver_roms[] =
{
	{
		FULL_COPY,
		{"pacman",   "pacman.rom", 24576, 0x98f58bfc,     0, 4096},
		{"pacman",   "pacman.6e",   4096, 0xc1e6ab10,     0, 4096},
	},
	{
		FULL_COPY,
		{"pacman",   "pacman.rom", 24576, 0x98f58bfc,  4096, 4096},
		{"pacman",   "pacman.6f",   4096, 0x1a6fb2d4,     0, 4096},
	},
	{
		FULL_COPY,
		{"pacman",   "pacman.rom", 24576, 0x98f58bfc,  8192, 4096},
		{"pacman",   "pacman.6h",   4096, 0xbcdd1beb,     0, 4096},
	},
	{
		FULL_COPY,
		{"pacman",   "pacman.rom", 24576, 0x98f58bfc, 12288, 4096},
		{"pacman",   "pacman.6j",   4096, 0x817d94e3,     0, 4096},
	},
	{
		FULL_COPY,
		{"pacman",   "pacman.rom", 24576, 0x98f58bfc, 16384, 4096},
		{"pacman",   "pacman.5e",   4096, 0x0c944964,     0, 4096},
	} ,
	{
		FULL_COPY,
		{"pacman",   "pacman.rom", 24576, 0x98f58bfc, 20480, 4096},
		{"pacman",   "pacman.5f",   4096, 0x958fedf9,     0, 4096},
	},
	{
		FULL_COPY,
		{"mspacman",  "mspacman.rom", 40960, 0xb1062fe0,     0, 4096},
		{"mspacmab",  "boot1",	 4096, 0xd16b31b7,     0, 4096},
	},
	{
		FULL_COPY,
		{"mspacman",  "mspacman.rom", 40960, 0xb1062fe0,  4096, 4096},
		{"mspacmab",  "boot2",	 4096, 0x0d32de5e,     0, 4096},
	},
	{
		FULL_COPY,
		{"mspacman",  "mspacman.rom", 40960, 0xb1062fe0,  8192, 4096},
		{"mspacmab",  "boot3",	 4096, 0x1821ee0b,     0, 4096},
	},
	{
		FULL_COPY,
		{"mspacman",  "mspacman.rom", 40960, 0xb1062fe0, 12288, 4096},
		{"mspacmab",  "boot4",	 4096, 0x165a9dd8,     0, 4096},
	},
	{
		FULL_COPY,
		{"mspacman",  "mspacman.rom", 40960, 0xb1062fe0, 16384, 4096},
		{"mspacmab",  "5e",	    4096, 0x5c281d01,     0, 4096},
	} ,
	{
		FULL_COPY,
		{"mspacman",  "mspacman.rom", 40960, 0xb1062fe0, 20480, 4096},
		{"mspacmab",  "5f",	    4096, 0x615af909,     0, 4096},
	},
	{
		BLOCK_FILL,
		{"mspacman", "mspacman.rom",  40960, 0xb1062fe0, 24576, 4096},
		{"	", "  ",		0, 0x00000000,    0,     0},
	},
	{
		BLOCK_FILL,
		{"mspacman", "mspacman.rom",  40960, 0xb1062fe0, 28672, 4096},
		{"	", "  ",		0, 0x00000000,    0,     0},
	},
	{
		FULL_COPY,
		{"mspacman",  "mspacman.rom", 40960, 0xb1062fe0, 32768, 4096},
		{"mspacmab",  "boot5",	 4096, 0x8c3e6de6,     0, 4096},
	},
	{
		FULL_COPY,
		{"mspacman",  "mspacman.rom", 40960, 0xb1062fe0, 36864, 4096},
		{"mspacmab",  "boot6",	 4096, 0x368cb165,     0, 4096},
	},
	{0}
};

struct Patch patch_nz1[] =
{
	{0x00000002, 0x00},
	{0x00000003, 0x00},
	{0x00000004, 0x00},
	{0}
};

struct Rom tnzs_roms[] =
{
	{
		FULL_COPY,
		{"tnzs_new", "nz17", 65536, 0x9784d443, 0, 65536},
		{"tnzsjo", "b53-11.38", 65536, 0x9784d443, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz18", 65536, 0xd0c447fd, 0, 65536},
		{"tnzsjo", "b53-10.32", 131072, 0xa73745c6, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz2", 65536, 0x4ca902fa, 0, 65536},
		{"tnzsjo", "b53-02.2", 131072, 0x095d0dc0, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz3", 65536, 0x8de4c673, 0, 65536},
		{"tnzsjo", "b53-03.3", 131072, 0x74acfb9b, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz4", 65536, 0x3d6ee15c, 0, 65536},
		{"tnzsjo", "b53-04.4", 131072, 0x59d2aef6, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz5", 65536, 0x13b708ea, 0, 65536},
		{"tnzsjo", "b53-05.5", 131072, 0xedbb9581, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz6", 65536, 0x8f123170, 0, 65536},
		{"tnzsjo", "b53-06.6", 131072, 0x92f35ed9, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz7", 65536, 0x772baddb, 0, 65536},
		{"tnzsjo", "b53-07.7", 131072, 0x2bf199e8, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz8", 65536, 0x2edffcce, 0, 65536},
		{"tnzsjo", "b53-08.8", 131072, 0xc3519c2a, 0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz9", 65536, 0xc7332040, 0, 65536},
		{"tnzsjo", "b53-01.1", 131072, 0x9800c54d, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz10", 65536, 0x708005ac, 0, 65536},
		{"tnzsjo", "b53-02.2", 131072, 0x095d0dc0, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz11", 65536, 0x7fe204da, 0, 65536},
		{"tnzsjo", "b53-03.3", 131072, 0x74acfb9b, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz12", 65536, 0x943a744d, 0, 65536},
		{"tnzsjo", "b53-04.4", 131072, 0x59d2aef6, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz13", 65536, 0x81ed38cb, 0, 65536},
		{"tnzsjo", "b53-05.5", 131072, 0xedbb9581, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz14", 65536, 0x03ee1f1b, 0, 65536},
		{"tnzsjo", "b53-06.6", 131072, 0x92f35ed9, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz15", 65536, 0xfbeda025, 0, 65536},
		{"tnzsjo", "b53-07.7", 131072, 0x2bf199e8, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz16", 65536, 0x665c76f1, 0, 65536},
		{"tnzsjo", "b53-08.8", 131072, 0xc3519c2a, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz19", 65536, 0xaf3e83d5, 0, 65536},
		{"tnzsjo", "b53-10.32", 131072, 0xa73745c6, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tnzs_new", "nz1", 65536, 0xd87fabab, 0, 65536},
		{"tnzsjo", "b53-01.1", 131072, 0x9800c54d, 0, 65536},
		patch_nz1
	},
	{0}
};

struct Rom trombone_roms[] =
{
	{
		FULL_COPY,
		{"shogwarr", "fb002.u44", 524288, 0x05d7c2a9, 0, 524288},
		{"shogwarr", "fb-002.u45", 1048576, 0x010acc17, 524288, 524288},
	},
	{
		FULL_COPY,
		{"shogwarr", "fb003.u45", 524288, 0x405722e9, 0, 524288},
		{"shogwarr", "fb-003.u44", 1048576, 0x0aea4ac5, 524288, 524288},
	},
	{0}
};

struct Rom pacx_roms[] =
{
	{
		FULL_COPY,
		{"pacmanjp", "prg1",	2048, 0xf36e88ab,    0, 2048},
		{"puckmana", "pacman.6e",   4096, 0xc1e6ab10,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg2",	2048, 0x618bd9b3,    0, 2048},
		{"puckmana", "pacman.6e",   4096, 0xc1e6ab10, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg3",	2048, 0x7d177853,    0, 2048},
		{"puckmana", "pacman.6f",   4096, 0x1a6fb2d4,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg4",	2048, 0xd3e8914c,    0, 2048},
		{"puckmana", "pacman.6f",   4096, 0x1a6fb2d4, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg5",	2048, 0x6bf4f625,    0, 2048},
		{"puckmana", "pacman.6h",   4096, 0xbcdd1beb,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg6",	2048, 0xa948ce83,    0, 2048},
		{"puckmana", "pacman.6h",   4096, 0xbcdd1beb, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "chg3",	2048, 0x9e39323a,    0, 2048},
		{"puckmana", "pacman.5f",   4096, 0x958fedf9,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "chg4",	2048, 0x1b1d9096,    0, 2048},
		{"puckmana", "pacman.5f",   4096, 0x958fedf9, 2048, 2048},
	},
	{0}
};

struct Rom arcadeemu_roms[] =
{
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816,    0, 4096},
		{"galap1",   "7f.bin",      4096, 0x4335b1de,    0, 4096},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 4096, 2048},
		{"galap1",   "galaxian.w",  2048, 0x4c7031c0,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 6144, 2048},
		{"galap1",   "galx_1_4.rom",2048, 0xe71e1d9e,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 8192, 2048},
		{"galap1",   "galx_1_5.rom",2048, 0x6e65a3b2,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea,    0, 2048},
		{"galap4",   "galnamco.u",  2048, 0xacfde501,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 2048, 2048},
		{"galap4",   "galnamco.v",  2048, 0x65cf3c77,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 4096, 2048},
		{"galap4",   "galnamco.w",  2048, 0x9eef9ae6,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 6144, 2048},
		{"galap4",   "galnamco.y",  2048, 0x56a5ddd1,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 8192, 2048},
		{"galap4",   "galnamco.z",  2048, 0xf4bc7262,    0, 2048},
	},
	{
		FULL_COPY,
		{"supgalax", "supgalax.u",  2048, 0xe8f3aa67,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"supgalax", "supgalax.v",  2048, 0xf58283e3,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom classicemu_roms[] =
{
	{
		FULL_COPY,
		{"sup_galx", "supergal.u",  2048, 0xe8f3aa67,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"sup_galx", "supergal.v",  2048, 0xf58283e3,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{0}
};

struct Rom salamander_roms[] =
{
	{
		FULL_COPY,
		{"salamand", "17b_l.bin",    65536, 0xb83e8724,     0, 65536},
		{"salamand", "587-c03.17b", 131072, 0xe5caf6e6,     0, 65536},
	},
	{
		FULL_COPY,
		{"salamand", "17b_u.bin",    65536, 0xb4d2fec9,     0, 65536},
		{"salamand", "587-c03.17b", 131072, 0xe5caf6e6, 65536, 65536},
	},
	{
		FULL_COPY,
		{"salamand", "17c_l.bin",    65536, 0xa6ef6dc4,     0, 65536},
		{"salamand", "587-c06.17c", 131072, 0xc2f567ea,     0, 65536},
	},
	{
		FULL_COPY,
		{"salamand", "17c_u.bin",    65536, 0x6ea59643,     0, 65536},
		{"salamand", "587-c06.17c", 131072, 0xc2f567ea, 65536, 65536},
	},
	{0}
};

struct Patch patch_pacman4x[] =
{
	{0x0000080b, 0x01},
	{0x00000ffd, 0xbd},
	{0}
};

struct Rom replay_roms[] =
{
	{
		FULL_COPY,
		{"sonson", "ss7.v12", 16384, 0x32b14b8e, 0, 8192},
		{"sonson", "ss_9.m5", 8192, 0x8cb1cacf, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss7.v12", 16384, 0x32b14b8e, 8192, 8192},
		{"sonson", "ss_10.m6", 8192, 0xf802815e, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss8.v12", 16384, 0x9f59014e, 0, 8192},
		{"sonson", "ss_11.m3", 8192, 0x4dbad88a, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss8.v12", 16384, 0x9f59014e, 8192, 8192},
		{"sonson", "ss_12.m4", 8192, 0xaa05e687, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss9.v12", 16384, 0x517fa26d, 0, 8192},
		{"sonson", "ss_13.m1", 8192, 0x66119bfa, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss9.v12", 16384, 0x517fa26d, 8192, 8192},
		{"sonson", "ss_14.m2", 8192, 0xe14ef54e, 0, 8192},
	},
	{
		FULL_COPY,
		{"amidar",  "amidarus.5f", 4096, 0xe3ada0a8, 0, 2048},
		{"amidaru", "amidarus.5f", 2048, 0x2cfe5ede, 0, 2048},
	},
	{
		FULL_COPY,
		{"amidar",  "amidarus.5f", 4096, 0xe3ada0a8, 2048, 2048},
		{"amidaru", "amidarus.5f", 2048, 0x2cfe5ede,    0, 2048},
	},
	{
		FULL_COPY,
		{"amidar",  "amidarus.5h", 4096, 0x9f27cb8b, 0, 2048},
		{"amidaru", "amidarus.5h", 2048, 0x57c4fd0d, 0, 2048},
	},
	{
		FULL_COPY,
		{"amidar",  "amidarus.5h", 4096, 0x9f27cb8b, 2048, 2048},
		{"amidaru", "amidarus.5h", 2048, 0x57c4fd0d,    0, 2048},
	},
	{
		FULL_COPY,
		{"carnival", "666u1.cpu", 2048, 0x4846ae8b, 0, 1024},
		{"carnival", "666u1.cpu", 1024, 0x4eec7fae, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "666u1.cpu", 2048, 0x4846ae8b, 1024, 1024},
		{"carnival", "666u1.cpu", 1024, 0x4eec7fae, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "652u32.cpu", 2048, 0xacb73519, 0, 1024},
		{"carnival", "652u32.cpu", 1024, 0xa1f58beb, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "652u32.cpu", 2048, 0xacb73519, 1024, 1024},
		{"carnival", "652u32.cpu", 1024, 0xa1f58beb, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "653u31.cpu", 2048, 0xbd179c15, 0, 1024},
		{"carnival", "653u31.cpu", 1024, 0x67b17922, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "653u31.cpu", 2048, 0xbd179c15, 1024, 1024},
		{"carnival", "653u31.cpu", 1024, 0x67b17922, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "654u30.cpu", 2048, 0x59f75cc0, 0, 1024},
		{"carnival", "654u30.cpu", 1024, 0xbefb09a5, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "654u30.cpu", 2048, 0x59f75cc0, 1024, 1024},
		{"carnival", "654u30.cpu", 1024, 0xbefb09a5, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "655u29.cpu", 2048, 0x92f6c07d, 0, 1024},
		{"carnival", "655u29.cpu", 1024, 0x623fcdad, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "655u29.cpu", 2048, 0x92f6c07d, 1024, 1024},
		{"carnival", "655u29.cpu", 1024, 0x623fcdad, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "656u28.cpu", 2048, 0x410914ac, 0, 1024},
		{"carnival", "656u28.cpu", 1024, 0x53040332, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "656u28.cpu", 2048, 0x410914ac, 1024, 1024},
		{"carnival", "656u28.cpu", 1024, 0x53040332, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "657u27.cpu", 2048, 0xc99a9bbd, 0, 1024},
		{"carnival", "657u27.cpu", 1024, 0xf2537467, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "657u27.cpu", 2048, 0xc99a9bbd, 1024, 1024},
		{"carnival", "657u27.cpu", 1024, 0xf2537467, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "658u26.cpu", 2048, 0xd2e4925a, 0, 1024},
		{"carnival", "658u26.cpu", 1024, 0xfcc3854e, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "658u26.cpu", 2048, 0xd2e4925a, 1024, 1024},
		{"carnival", "658u26.cpu", 1024, 0xfcc3854e, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "659u8.cpu", 2048, 0x3a894cfe, 0, 1024},
		{"carnival", "659u8.cpu", 1024, 0x28be8d69, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "659u8.cpu", 2048, 0x3a894cfe, 1024, 1024},
		{"carnival", "659u8.cpu", 1024, 0x28be8d69, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "660u7.cpu", 2048, 0x8b792ab7, 0, 1024},
		{"carnival", "660u7.cpu", 1024, 0x3873ccdb, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "660u7.cpu", 2048, 0x8b792ab7, 1024, 1024},
		{"carnival", "660u7.cpu", 1024, 0x3873ccdb, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "661u6.cpu", 2048, 0x261c3ca0, 0, 1024},
		{"carnival", "661u6.cpu", 1024, 0xd9a96dff, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "661u6.cpu", 2048, 0x261c3ca0, 1024, 1024},
		{"carnival", "661u6.cpu", 1024, 0xd9a96dff, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "662u5.cpu", 2048, 0x59247fa2, 0, 1024},
		{"carnival", "662u5.cpu", 1024, 0xd893ca72, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "662u5.cpu", 2048, 0x59247fa2, 1024, 1024},
		{"carnival", "662u5.cpu", 1024, 0xd893ca72, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "663u4.cpu", 2048, 0x42787079, 0, 1024},
		{"carnival", "663u4.cpu", 1024, 0xdf8c63c5, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "663u4.cpu", 2048, 0x42787079, 1024, 1024},
		{"carnival", "663u4.cpu", 1024, 0xdf8c63c5, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "664u3.cpu", 2048, 0xe0ff6e25, 0, 1024},
		{"carnival", "664u3.cpu", 1024, 0x689a73e8, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "664u3.cpu", 2048, 0xe0ff6e25, 1024, 1024},
		{"carnival", "664u3.cpu", 1024, 0x689a73e8, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "665u2.cpu", 2048, 0xc5868119, 0, 1024},
		{"carnival", "665u2.cpu", 1024, 0x28e7b2b6, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "665u2.cpu", 2048, 0xc5868119, 1024, 1024},
		{"carnival", "665u2.cpu", 1024, 0x28e7b2b6, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "651u33.cpu", 2048, 0xa98d5f3d, 0, 1024},
		{"carnival", "651u33.cpu", 1024, 0x9f2736e6, 0, 1024},
	},
	{
		FULL_COPY,
		{"carnival", "651u33.cpu", 2048, 0xa98d5f3d, 1024, 1024},
		{"carnival", "651u33.cpu", 1024, 0x9f2736e6, 0, 1024},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd,    0, 2048},
		{"galaxian", "galmidw.u",   2048, 0x745e2d61,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd, 2048, 2048},
		{"galaxian", "galmidw.v",   2048, 0x9c999a40,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d,    0, 2048},
		{"galaxian", "galmidw.w",   2048, 0xb5894925,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d, 2048, 2048},
		{"galaxian", "galmidw.y",   2048, 0x6b3ca10b,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7l",	  4096, 0x952c6135,    0, 2048},
		{"galaxian", "7l",	  2048, 0x1b933207,    0, 2048},
	},
	{
		BLOCK_FILL,
		{"galaxian", "7l",	  4096, 0x952c6135, 2048, 2048},
		{"	", "  ",	     0, 0xffffffff,   0,     0},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816,    0, 4096},
		{"galap1",   "7f.bin",      4096, 0x4335b1de,    0, 4096},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 4096, 2048},
		{"galap1",   "galaxian.w",  2048, 0x4c7031c0,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 6144, 2048},
		{"galap1",   "galx_1_4.rom",2048, 0xe71e1d9e,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 8192, 2048},
		{"galap1",   "galx_1_5.rom",2048, 0x6e65a3b2,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea,    0, 2048},
		{"galap4",   "galnamco.u",  2048, 0xacfde501,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 2048, 2048},
		{"galap4",   "galnamco.v",  2048, 0x65cf3c77,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 4096, 2048},
		{"galap4",   "galnamco.w",  2048, 0x9eef9ae6,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 6144, 2048},
		{"galap4",   "galnamco.y",  2048, 0x56a5ddd1,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 8192, 2048},
		{"galap4",   "galnamco.z",  2048, 0xf4bc7262,    0, 2048},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb1.prg", 16384, 0xb223fca9, 0, 4096},
		{"jumpbugb", "jb1", 4096, 0x415aa1b7, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb1.prg", 16384, 0xb223fca9, 4096, 4096},
		{"jumpbugb", "jb2", 4096, 0xb1c27510, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb1.prg", 16384, 0xb223fca9, 8192, 4096},
		{"jumpbugb", "jb3b", 4096, 0xcb8b8a0f, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb1.prg", 16384, 0xb223fca9, 12288, 4096},
		{"jumpbugb", "jb4", 4096, 0x66751d12, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb2.prg", 10240, 0x1b2eb25f, 0, 4096},
		{"jumpbugb", "jb5b", 4096, 0x7553b5e2, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb2.prg", 10240, 0x1b2eb25f, 4096, 4096},
		{"jumpbugb", "jb6b", 4096, 0x47be9843, 0, 4096},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb2.prg", 10240, 0x1b2eb25f, 8192, 2048},
		{"jumpbugb", "jb7b", 2048, 0x460aed61, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb3.gfx", 12288, 0x44240cbe, 0, 2048},
		{"jumpbugb", "jbl", 2048, 0x9a091b0a, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb3.gfx", 12288, 0x44240cbe, 2048, 2048},
		{"jumpbugb", "jbm", 2048, 0x8a0fc082, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb3.gfx", 12288, 0x44240cbe, 4096, 2048},
		{"jumpbugb", "jbn", 2048, 0x155186e0, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb3.gfx", 12288, 0x44240cbe, 6144, 2048},
		{"jumpbugb", "jbi", 2048, 0x7749b111, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb3.gfx", 12288, 0x44240cbe, 8192, 2048},
		{"jumpbugb", "jbj", 2048, 0x06e8d7df, 0, 2048},
	},
	{
		FULL_COPY,
		{"jumpsega", "jb3.gfx", 12288, 0x44240cbe, 10240, 2048},
		{"jumpbugb", "jbk", 2048, 0xb8dbddf3, 0, 2048},
	},
	{
		FULL_COPY,
		{"kungfub", "kf9", 16384, 0x05fcce8b, 0, 8192},
		{"kungfub2", "b-3n-.bin", 8192, 0x28a213aa, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf9", 16384, 0x05fcce8b, 8192, 8192},
		{"kungfub2", "b-4n-.bin", 8192, 0xd5228df3, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf14", 16384, 0x1df11d81, 0, 8192},
		{"kungfub2", "b-4c-.bin", 8192, 0x01298885, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf14", 16384, 0x1df11d81, 8192, 8192},
		{"kungfub2", "b-4e-.bin", 8192, 0xc77b87d4, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf13", 16384, 0x2d3b69dd, 0, 8192},
		{"kungfub2", "b-4d-.bin", 8192, 0x6a70615f, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf13", 16384, 0x2d3b69dd, 8192, 8192},
		{"kungfub2", "b-4a-.bin", 8192, 0x6189d626, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf12", 16384, 0xed719d7b, 0, 8192},
		{"kungfub2", "b-4l-.bin", 8192, 0xbd1c2261, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf12", 16384, 0xed719d7b, 8192, 8192},
		{"kungfub2", "b-4h-.bin", 8192, 0x8ac5ed3a, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf11", 16384, 0x85591db2, 0, 8192},
		{"kungfub2", "b-4k-.bin", 8192, 0x16fb5150, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf11", 16384, 0x85591db2, 8192, 8192},
		{"kungfub2", "b-4f-.bin", 8192, 0x67745a33, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf10", 16384, 0xdc675003, 0, 8192},
		{"kungfub2", "b-4m-.bin", 8192, 0xb16de4f2, 0, 8192},
	},
	{
		FULL_COPY,
		{"kungfub", "kf10", 16384, 0xdc675003, 8192, 8192},
		{"kungfub2", "b-3m-.bin", 8192, 0xeba0d66b, 0, 8192},
	},
	{
		FULL_COPY,
		{"pacman4x", "pacman4x.6f",  4096, 0x720dc3ee,    0, 4096},
		{"pacman",   "pacman.6f",    4096, 0x1a6fb2d4,    0, 4096},
		patch_pacman4x
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg1",	2048, 0xf36e88ab,    0, 2048},
		{"puckmana", "pacman.6e",   4096, 0xc1e6ab10,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg2",	2048, 0x618bd9b3,    0, 2048},
		{"puckmana", "pacman.6e",   4096, 0xc1e6ab10, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg3",	2048, 0x7d177853,    0, 2048},
		{"puckmana", "pacman.6f",   4096, 0x1a6fb2d4,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg4",	2048, 0xd3e8914c,    0, 2048},
		{"puckmana", "pacman.6f",   4096, 0x1a6fb2d4, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg5",	2048, 0x6bf4f625,    0, 2048},
		{"puckmana", "pacman.6h",   4096, 0xbcdd1beb,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg6",	2048, 0xa948ce83,    0, 2048},
		{"puckmana", "pacman.6h",   4096, 0xbcdd1beb, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "chg3",	2048, 0x9e39323a,    0, 2048},
		{"puckmana", "pacman.5f",   4096, 0x958fedf9,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "chg4",	2048, 0x1b1d9096,    0, 2048},
		{"puckmana", "pacman.5f",   4096, 0x958fedf9, 2048, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2m_u.bin", 2048, 0xd3b91f19, 0, 2048},
		{"scobrab", "scobra2l.bin", 4096, 0x6f80f3a9, 0, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2p_u.bin", 2048, 0x1bcc7875, 0, 2048},
		{"scobrab", "scobra2l.bin", 4096, 0x6f80f3a9, 2048, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2f.bin", 2048, 0xa26ded8c, 0, 2048},
		{"scobrab", "scobra2e.bin", 4096, 0xa270e44d, 0, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2h.bin", 2048, 0xdf1a0519, 0, 2048},
		{"scobrab", "scobra2e.bin", 4096, 0xa270e44d, 2048, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2j_l.bin", 2048, 0x2db3e68c, 0, 2048},
		{"scobrab", "scobra2f.bin", 4096, 0xbdd70346, 0, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2l_l.bin", 2048, 0xa40158db, 0, 2048},
		{"scobrab", "scobra2f.bin", 4096, 0xbdd70346, 2048, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2m_l.bin", 2048, 0xb9e07c80, 0, 2048},
		{"scobrab", "scobra2h.bin", 4096, 0xdca5ec31, 0, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2p_l.bin", 2048, 0x96ea7388, 0, 2048},
		{"scobrab", "scobra2h.bin", 4096, 0xdca5ec31, 2048, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2j_u.bin", 2048, 0x97aefb83, 0, 2048},
		{"scobrab", "scobra2j.bin", 4096, 0x0d8f6b6e, 0, 2048},
	},
	{
		FULL_COPY,
		{"scobrab", "vid_2l_u.bin", 2048, 0x72254b10, 0, 2048},
		{"scobrab", "scobra2j.bin", 4096, 0x0d8f6b6e, 2048, 2048},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt1", 32768, 0xd8d85ab7, 0, 16384},
		{"starforc", "starforc.3", 16384, 0x8ba27691, 0, 16384},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt1", 32768, 0xd8d85ab7, 16384, 16384},
		{"starforc", "starforc.2", 16384, 0x0fc4d2d6, 0, 16384},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt2", 16384, 0xf59d941b, 0, 4096},
		{"starforc", "starforc.16", 4096, 0xce20b469, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt2", 16384, 0xf59d941b, 4096, 4096},
		{"starforc", "starforc.17", 4096, 0x68c60d0f, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt2", 16384, 0xf59d941b, 8192, 4096},
		{"starforc", "starforc.18", 4096, 0x6455c3ad, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt2", 16384, 0xf59d941b, 12288, 4096},
		{"starforc", "starforc.4", 16384, 0xdd9d68a4, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt3", 16384, 0x73f4140f, 0, 12288},
		{"starforc", "starforc.4", 16384, 0xdd9d68a4, 4096, 12288},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt3", 16384, 0x73f4140f, 12288, 4096},
		{"starforc", "starforc.5", 16384, 0xf71717f8, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt4", 16384, 0xa9e719c3, 0, 12288},
		{"starforc", "starforc.5", 16384, 0xf71717f8, 4096, 12288},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt4", 16384, 0xa9e719c3, 12288, 4096},
		{"starforc", "starforc.6", 16384, 0x5468a21d, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt5", 16384, 0xcf779ce8, 0, 12288},
		{"starforc", "starforc.6", 16384, 0x5468a21d, 4096, 12288},
	},
	{
		BLOCK_FILL,
		{"starforc", "starforc.dt5", 16384, 0xcf779ce8, 12288, 4096},
		{"	", "	   ", 0, 0x00000000,   0,     0},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt6", 16384, 0xdfe04a7d, 0, 8192},
		{"starforc", "starforc.1", 8192, 0x2735bb22, 0, 8192},
	},
	{
		BLOCK_FILL,
		{"starforc", "starforc.dt6", 16384, 0xdfe04a7d, 8192, 8192},
		{"	", "	   ", 0, 0x00000000,   0,     0},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 0, 4096},
		{"starforc", "starforc.7", 4096, 0xf4803339, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 4096, 4096},
		{"starforc", "starforc.8", 4096, 0x96979684, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 8192, 4096},
		{"starforc", "starforc.9", 4096, 0xeead1d5c, 0, 4096},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 12288, 8192},
		{"starforc", "starforc.10", 8192, 0xc62a19c1, 0, 8192},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 20480, 8192},
		{"starforc", "starforc.11", 8192, 0x668aea14, 0, 8192},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 28672, 8192},
		{"starforc", "starforc.12", 8192, 0xfdd9e38b, 0, 8192},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 36864, 8192},
		{"starforc", "starforc.13", 8192, 0x84603285, 0, 8192},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 45056, 8192},
		{"starforc", "starforc.14", 8192, 0x9e9384fe, 0, 8192},
	},
	{
		FULL_COPY,
		{"starforc", "starforc.dt7", 61440, 0xf3808e6e, 53248, 8192},
		{"starforc", "starforc.15", 8192, 0xc3bda12f, 0, 8192},
	},
	{
		FULL_COPY,
		{"xeviousn",  "xe-1l-a.bin", 8192, 0xbd74609a,    0, 4096},
		{"xevious",   "xvi_3.2m",    4096, 0x79754b7d,    0, 4096},
	},
	{
		FULL_COPY,
		{"xeviousn",  "xe-1l-a.bin", 8192, 0xbd74609a, 4096, 4096},
		{"xevious",   "xvi_4.2l",    4096, 0xc7d4bbf0,    0, 4096},
	},
	{
		FULL_COPY,
		{"xeviousn",  "xe-1m-a.bin", 8192, 0x92fa6cae,    0, 4096},
		{"xevious",   "xvi_1.3p",    4096, 0x09964dda,    0, 4096},
	},
	{
		FULL_COPY,
		{"xeviousn",  "xe-1m-a.bin", 8192, 0x92fa6cae, 4096, 4096},
		{"xevious",   "xvi_2.3m",    4096, 0x60ecce84,    0, 4096},
	},
	{
		FULL_COPY,
		{"xeviousn",  "xe-4c-a.bin", 8192, 0x0ede5706,    0, 4096},
		{"xevious",   "xvi_5.3f",    4096, 0xc85b703f,    0, 4096},
	},
	{
		FULL_COPY,
		{"xeviousn",  "xe-4c-a.bin", 8192, 0x0ede5706, 4096, 4096},
		{"xevious",   "xvi_6.3j",    4096, 0xe18cdaad,    0, 4096},
	},
	{
		FULL_COPY,
		{"superg",   "galaxian.u",  2048, 0xe8f3aa67,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "galaxian.v",  2048, 0xf58283e3,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom neoragex_roms[] =
{
	{
		FULL_COPY,
		{"sengoku2", "n138001c.1f8", 524288, 0x6650bc9a, 0, 524288},
		{"sengoku2", "040-v2.bin", 1048576, 0xc5cece01, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "n138001c.1fc", 524288, 0xc6358d62, 0, 524288},
		{"sengoku2", "040-v2.bin", 1048576, 0xc5cece01, 524288, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "n138001a.1f8", 524288, 0xe6e9d82f, 0, 524288},
		{"sengoku2", "040-v1.bin", 2097152, 0x71cb4b5d, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "n138001a.1fc", 524288, 0x0504e71e, 0, 524288},
		{"sengoku2", "040-v1.bin", 2097152, 0x71cb4b5d, 524288, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "n138001b.1f8", 524288, 0xe6c57d21, 0, 524288},
		{"sengoku2", "040-v1.bin", 2097152, 0x71cb4b5d, 1048576, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "n138001b.1fc", 524288, 0x000d319d, 0, 524288},
		{"sengoku2", "040-v1.bin", 2097152, 0x71cb4b5d, 1572864, 524288},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001b.538", 524288, 0x891b6386, 0, 262144},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001b.53c", 524288, 0x891b6386, 0, 262144},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001b.638", 524288, 0x93d25955, 0, 262144},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001b.63c", 524288, 0x93d25955, 0, 262144},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001d.538", 524288, 0x891b6386, 0, 262144},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001d.53c", 524288, 0x891b6386, 0, 262144},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001d.638", 524288, 0x93d25955, 0, 262144},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001d.63c", 524288, 0x93d25955, 0, 262144},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001a.038", 524288, 0xd1bf3fa5, 0, 262144},
		{"sengoku2", "040-p1.bin", 1048576, 0x6dde02c2, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001a.03c", 524288, 0xee9d0bb4, 0, 262144},
		{"sengoku2", "040-p1.bin", 1048576, 0x6dde02c2, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001a.538", 524288, 0xda18aaed, 0, 262144},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001a.638", 524288, 0x5b27c829, 0, 262144},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001a.53c", 524288, 0x19796c4f, 0, 262144},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001a.63c", 524288, 0xe8b46e26, 0, 262144},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001c.538", 524288, 0xc5eaabe8, 0, 262144},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001c.638", 524288, 0x432bd7d0, 0, 262144},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001c.53c", 524288, 0x22633905, 0, 262144},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 1572864, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku2", "n138001c.63c", 524288, 0xba3f54b2, 0, 262144},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001b.538", 524288, 0x891b6386, 262144, 262144},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001b.53c", 524288, 0x891b6386, 262144, 262144},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001b.638", 524288, 0x93d25955, 262144, 262144},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001b.63c", 524288, 0x93d25955, 262144, 262144},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001d.538", 524288, 0x891b6386, 262144, 262144},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001d.53c", 524288, 0x891b6386, 262144, 262144},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001d.638", 524288, 0x93d25955, 262144, 262144},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001d.63c", 524288, 0x93d25955, 262144, 262144},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001a.038", 524288, 0xd1bf3fa5, 262144, 262144},
		{"sengoku2", "040-p1.bin", 1048576, 0x6dde02c2, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001a.03c", 524288, 0xee9d0bb4, 262144, 262144},
		{"sengoku2", "040-p1.bin", 1048576, 0x6dde02c2, 524288, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001a.538", 524288, 0xda18aaed, 262144, 262144},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001a.638", 524288, 0x5b27c829, 262144, 262144},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001a.53c", 524288, 0x19796c4f, 262144, 262144},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 524288, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001a.63c", 524288, 0xe8b46e26, 262144, 262144},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 524288, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001c.538", 524288, 0xc5eaabe8, 262144, 262144},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001c.638", 524288, 0x432bd7d0, 262144, 262144},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001c.53c", 524288, 0x22633905, 262144, 262144},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"sengoku2", "n138001c.63c", 524288, 0xba3f54b2, 262144, 262144},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 1572864, 262144},
	},
	{
		FULL_COPY,
		{"3countb", "n106001a.1f8", 524288, 0x2abe6ab0, 0, 524288},
		{"3countb", "043-v1.bin", 2097152, 0x63688ce8, 0, 524288},
	},
	{
		FULL_COPY,
		{"3countb", "n106001c.1f8", 524288, 0xf76aa00e, 0, 524288},
		{"3countb", "043-v2.bin", 2097152, 0xc69a827b, 0, 524288},
	},
	{
		FULL_COPY,
		{"3countb", "n106001a.1fc", 524288, 0xd3fa2743, 0, 524288},
		{"3countb", "043-v1.bin", 2097152, 0x63688ce8, 524288, 524288},
	},
	{
		FULL_COPY,
		{"3countb", "n106001c.1fc", 524288, 0x851ce851, 0, 524288},
		{"3countb", "043-v2.bin", 2097152, 0xc69a827b, 524288, 524288},
	},
	{
		FULL_COPY,
		{"3countb", "n106001b.1f8", 524288, 0xf591b0a1, 0, 524288},
		{"3countb", "043-v1.bin", 2097152, 0x63688ce8, 1048576, 524288},
	},
	{
		FULL_COPY,
		{"3countb", "n106001d.1f8", 524288, 0x9e2c8366, 0, 524288},
		{"3countb", "043-v2.bin", 2097152, 0xc69a827b, 1048576, 524288},
	},
	{
		FULL_COPY,
		{"3countb", "n106001b.1fc", 524288, 0x01f3999e, 0, 524288},
		{"3countb", "043-v1.bin", 2097152, 0x63688ce8, 1572864, 524288},
	},
	{
		FULL_COPY,
		{"3countb", "n106001d.1fc", 524288, 0xb1a0ccb0, 0, 524288},
		{"3countb", "043-v2.bin", 2097152, 0xc69a827b, 1572864, 524288},
	},
	/* Commented out whilst doing the CAESAR update for MAME v0.128
	{
		EVEN_COPY,
		{"3countb", "n106001a.038", 524288, 0x10dbe66a, 0, 262144},
		{"3countb", "043-p1.bin", 524288, 0xeb2714c4, 0, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001a.03c", 524288, 0x6d5bfb61, 0, 262144},
		{"3countb", "043-p2.bin", 524288, 0x5e764567, 0, 262144},
	},
	*/
	{
		EVEN_COPY,
		{"3countb", "n106001a.538", 524288, 0xbe0d2fe0, 0, 262144},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 0, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001a.638", 524288, 0xf56dafa5, 0, 262144},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 0, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001b.538", 524288, 0x714c2c01, 0, 262144},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 0, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001b.638", 524288, 0xb15a7f25, 0, 262144},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 0, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001a.53c", 524288, 0xfdb4df65, 0, 262144},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001a.63c", 524288, 0xf2f68b2a, 0, 262144},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001b.53c", 524288, 0xc57ce8b0, 0, 262144},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001b.63c", 524288, 0x25f00cd3, 0, 262144},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001c.538", 524288, 0x2e7e59df, 0, 262144},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001c.638", 524288, 0x341438e4, 0, 262144},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001d.538", 524288, 0x410938c5, 0, 262144},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001d.638", 524288, 0x74d995c5, 0, 262144},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001c.53c", 524288, 0xa93185ce, 0, 262144},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 1572864, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001c.63c", 524288, 0xfb8adce8, 0, 262144},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 1572864, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001d.53c", 524288, 0x50d66909, 0, 262144},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 1572864, 262144},
	},
	{
		EVEN_COPY,
		{"3countb", "n106001d.63c", 524288, 0x521b6df1, 0, 262144},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 1572864, 262144},
	},
	/* Commented out whilst doing the CAESAR update for MAME v0.128
	{
		ODD_COPY,
		{"3countb", "n106001a.038", 524288, 0x10dbe66a, 262144, 262144},
		{"3countb", "043-p1.bin", 524288, 0xeb2714c4, 0, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001a.03c", 524288, 0x6d5bfb61, 262144, 262144},
		{"3countb", "043-p2.bin", 524288, 0x5e764567, 0, 262144},
	},
	*/
	{
		ODD_COPY,
		{"3countb", "n106001a.538", 524288, 0xbe0d2fe0, 262144, 262144},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 0, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001a.638", 524288, 0xf56dafa5, 262144, 262144},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 0, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001b.538", 524288, 0x714c2c01, 262144, 262144},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 0, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001b.638", 524288, 0xb15a7f25, 262144, 262144},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 0, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001a.53c", 524288, 0xfdb4df65, 262144, 262144},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 524288, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001a.63c", 524288, 0xf2f68b2a, 262144, 262144},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 524288, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001b.53c", 524288, 0xc57ce8b0, 262144, 262144},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 524288, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001b.63c", 524288, 0x25f00cd3, 262144, 262144},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 524288, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001c.538", 524288, 0x2e7e59df, 262144, 262144},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001c.638", 524288, 0x341438e4, 262144, 262144},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001d.538", 524288, 0x410938c5, 262144, 262144},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001d.638", 524288, 0x74d995c5, 262144, 262144},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001c.53c", 524288, 0xa93185ce, 262144, 262144},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001c.63c", 524288, 0xfb8adce8, 262144, 262144},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001d.53c", 524288, 0x50d66909, 262144, 262144},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"3countb", "n106001d.63c", 524288, 0x521b6df1, 262144, 262144},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 1572864, 262144},
	},
	{
		FULL_COPY,
		{"kizuna", "ke_c1.rom", 4194304, 0x3c36ca70, 0, 2097152},
		{"kizuna", "059-c1.bin", 2097152, 0x763ba611, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kizuna", "ke_c1.rom", 4194304, 0x3c36ca70, 2097152, 2097152},
		{"kizuna", "059-c1.bin", 2097152, 0x763ba611, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kizuna", "ke_c6.rom", 4194304, 0x5a1087bd, 0, 2097152},
		{"kizuna", "059-c6.bin", 2097152, 0x1c8d5def, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kizuna", "ke_c6.rom", 4194304, 0x5a1087bd, 2097152, 2097152},
		{"kizuna", "059-c6.bin", 2097152, 0x1c8d5def, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kizuna", "ke_c2.rom", 4194304, 0xa3ba866a, 0, 2097152},
		{"kizuna", "059-c2.bin", 2097152, 0xe05e8ca6, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kizuna", "ke_c2.rom", 4194304, 0xa3ba866a, 2097152, 2097152},
		{"kizuna", "059-c2.bin", 2097152, 0xe05e8ca6, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kizuna", "ke_c5.rom", 4194304, 0xd3135644, 0, 2097152},
		{"kizuna", "059-c5.bin", 2097152, 0x59013f9e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kizuna", "ke_c5.rom", 4194304, 0xd3135644, 2097152, 2097152},
		{"kizuna", "059-c5.bin", 2097152, 0x59013f9e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kof95", "kof95_c6.rom", 4194304, 0x5ab5ea75, 0, 2097152},
		{"kof95h", "084-c6.bin", 2097152, 0xf593ac35, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kof95", "kof95_c6.rom", 4194304, 0x5ab5ea75, 2097152, 2097152},
		{"kof95h", "084-c6.bin", 2097152, 0xf593ac35, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kof95", "kof95_v2.rom", 4194304, 0xef8c08c7, 0, 2097152},
		{"kof95h", "084-v2.bin", 2097152, 0xb38a2803, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kof95", "kof95_v2.rom", 4194304, 0xef8c08c7, 2097152, 2097152},
		{"kof95h", "084-v2.bin", 2097152, 0xb38a2803, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kof95", "kof95_c5.rom", 4194304, 0xfd45472a, 0, 2097152},
		{"kof95h", "084-c5.bin", 2097152, 0x8a2c1edc, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kof95", "kof95_c5.rom", 4194304, 0xfd45472a, 2097152, 2097152},
		{"kof95h", "084-c5.bin", 2097152, 0x8a2c1edc, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c6.rom", 4194304, 0x360f3799, 0, 2097152},
		{"whp", "064-c6.bin", 2097152, 0xa43e4766, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c6.rom", 4194304, 0x360f3799, 2097152, 2097152},
		{"whp", "064-c6.bin", 2097152, 0xa43e4766, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c3.rom", 4194304, 0x52ac82aa, 0, 2097152},
		{"whp", "064-c3.bin", 2097152, 0x436d1b31, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c3.rom", 4194304, 0x52ac82aa, 2097152, 2097152},
		{"whp", "064-c3.bin", 2097152, 0x436d1b31, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c5.rom", 4194304, 0xb3b49535, 0, 2097152},
		{"whp", "064-c5.bin", 2097152, 0x8e34a9f4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c5.rom", 4194304, 0xb3b49535, 2097152, 2097152},
		{"whp", "064-c5.bin", 2097152, 0x8e34a9f4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c4.rom", 4194304, 0xe55832d1, 0, 2097152},
		{"whp", "064-c4.bin", 2097152, 0xf9c8dd26, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c4.rom", 4194304, 0xe55832d1, 2097152, 2097152},
		{"whp", "064-c4.bin", 2097152, 0xf9c8dd26, 0, 2097152},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001a.178", 524288, 0x7ec0e76d, 0, 524288},
		{"alpham2", "007-v1.bin", 1048576, 0xcd5db931, 0, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001b.178", 524288, 0x70bc86a5, 0, 524288},
		{"alpham2", "007-v2.bin", 1048576, 0x63e9b574, 0, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001a.17c", 524288, 0x7a796ead, 0, 524288},
		{"alpham2", "007-v1.bin", 1048576, 0xcd5db931, 524288, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001b.17c", 524288, 0x29963a92, 0, 524288},
		{"alpham2", "007-v2.bin", 1048576, 0x63e9b574, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"alpham2", "n082001b.538", 524288, 0x3a7fe4fd, 0, 262144},
		{"alpham2", "007-c3.bin", 524288, 0x68c2994e, 0, 262144},
	},
	{
		ODD_COPY,
		{"alpham2", "n082001b.538", 524288, 0x3a7fe4fd, 262144, 262144},
		{"alpham2", "007-c3.bin", 524288, 0x68c2994e, 0, 262144},
	},
	{
		EVEN_COPY,
		{"alpham2", "n082001a.538", 524288, 0xc516b09e, 0, 262144},
		{"alpham2", "007-c1.bin", 1048576, 0x8fba8ff3, 0, 262144},
	},
	{
		ODD_COPY,
		{"alpham2", "n082001a.538", 524288, 0xc516b09e, 262144, 262144},
		{"alpham2", "007-c1.bin", 1048576, 0x8fba8ff3, 0, 262144},
	},
	{
		EVEN_COPY,
		{"alpham2", "n082001b.638", 524288, 0xd0e8eef3, 0, 262144},
		{"alpham2", "007-c4.bin", 524288, 0x7d588349, 0, 262144},
	},
	{
		ODD_COPY,
		{"alpham2", "n082001b.638", 524288, 0xd0e8eef3, 262144, 262144},
		{"alpham2", "007-c4.bin", 524288, 0x7d588349, 0, 262144},
	},
	{
		EVEN_COPY,
		{"alpham2", "n082001a.638", 524288, 0x6b674581, 0, 262144},
		{"alpham2", "007-c2.bin", 1048576, 0x4dad2945, 0, 262144},
	},
	{
		ODD_COPY,
		{"alpham2", "n082001a.638", 524288, 0x6b674581, 262144, 262144},
		{"alpham2", "007-c2.bin", 1048576, 0x4dad2945, 0, 262144},
	},
	{
		EVEN_COPY,
		{"alpham2", "n082001a.53c", 524288, 0xd9a0ff6c, 0, 262144},
		{"alpham2", "007-c1.bin", 1048576, 0x8fba8ff3, 524288, 262144},
	},
	{
		ODD_COPY,
		{"alpham2", "n082001a.53c", 524288, 0xd9a0ff6c, 262144, 262144},
		{"alpham2", "007-c1.bin", 1048576, 0x8fba8ff3, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"alpham2", "n082001a.63c", 524288, 0x4ff21008, 0, 262144},
		{"alpham2", "007-c2.bin", 1048576, 0x4dad2945, 524288, 262144},
	},
	{
		ODD_COPY,
		{"alpham2", "n082001a.63c", 524288, 0x4ff21008, 262144, 262144},
		{"alpham2", "007-c2.bin", 1048576, 0x4dad2945, 524288, 262144},
	},
	/* MAME changed alpham2 in v0.56 so it is impossible to re-build some of the original ROMs
	{
		FULL_COPY,
		{"alpham2", "n082001a.278", 524288, 0x45f5e914, 0, 524288},
		{"alpham2", "lstg_v21.rom", 1048576, 0xff7ebf79, 0, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001a.478", 65536, 0x0449acf5, 0, 65536},
		{"alpham2", "lstg_m1.rom", 131072, 0xf23d3076, 0, 65536},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001b.278", 524288, 0xc3178623, 0, 524288},
		{"alpham2", "lstg_v22.rom", 1048576, 0xf2028490, 0, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001c.278", 524288, 0x27cd2250, 0, 524288},
		{"alpham2", "lstg_v23.rom", 1048576, 0x2e4f1e48, 0, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001d.278", 524288, 0xae0a679a, 0, 524288},
		{"alpham2", "lstg_v24.rom", 1048576, 0x658ee845, 0, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001a.27c", 524288, 0x07524063, 0, 524288},
		{"alpham2", "lstg_v21.rom", 1048576, 0xff7ebf79, 524288, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001b.27c", 524288, 0x65bca6b7, 0, 524288},
		{"alpham2", "lstg_v22.rom", 1048576, 0xf2028490, 524288, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001c.27c", 524288, 0x43025293, 0, 524288},
		{"alpham2", "lstg_v23.rom", 1048576, 0x2e4f1e48, 524288, 524288},
	},
	{
		FULL_COPY,
		{"alpham2", "n082001d.27c", 524288, 0x6a2e400d, 0, 524288},
		{"alpham2", "lstg_v24.rom", 1048576, 0x658ee845, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"alpham2", "n082001a.038", 524288, 0x4400b34c, 0, 262144},
		{"alpham2", "lstg_p1.rom", 1048576, 0x7b0ebe08, 0, 262144},
	},
	{
		ODD_COPY,
		{"alpham2", "n082001a.038", 524288, 0x4400b34c, 262144, 262144},
		{"alpham2", "lstg_p1.rom", 1048576, 0x7b0ebe08, 0, 262144},
	},
	{
		EVEN_COPY,
		{"alpham2", "n082001a.03c", 524288, 0xb0366875, 0, 262144},
		{"alpham2", "lstg_p1.rom", 1048576, 0x7b0ebe08, 524288, 262144},
	},
	{
		ODD_COPY,
		{"alpham2", "n082001a.03c", 524288, 0xb0366875, 262144, 262144},
		{"alpham2", "lstg_p1.rom", 1048576, 0x7b0ebe08, 524288, 262144},
	},
	*/
	{
		FULL_COPY,
		{"2020bb", "n046001a.1f8", 524288, 0x33e7886e, 0, 524288},
		{"2020bbh", "030-v1.bin", 1048576, 0xd4ca364e, 0, 524288},
	},
	{
		FULL_COPY,
		{"2020bb", "n046001b.1f8", 524288, 0x3cf9a433, 0, 524288},
		{"2020bbh", "030-v2.bin", 1048576, 0x54994455, 0, 524288},
	},
	{
		FULL_COPY,
		{"2020bb", "n046001a.1fc", 524288, 0xe7ca3882, 0, 524288},
		{"2020bbh", "030-v1.bin", 1048576, 0xd4ca364e, 524288, 524288},
	},
	{
		FULL_COPY,
		{"2020bb", "n046001b.1fc", 524288, 0x88b10192, 0, 524288},
		{"2020bbh", "030-v2.bin", 1048576, 0x54994455, 524288, 524288},
	},
	/* I do not recall when these were removed from MAME
	{
		EVEN_COPY,
		{"2020bb", "n046001b.538", 524288, 0x0b054a38, 0, 262144},
		{"2020bbh", "030-c3.bin", 524288, 0x6a87ae30, 0, 262144},
	},
	{
		ODD_COPY,
		{"2020bb", "n046001b.538", 524288, 0x0b054a38, 262144, 262144},
		{"2020bbh", "030-c3.bin", 524288, 0x6a87ae30, 0, 262144},
	},
	{
		EVEN_COPY,
		{"2020bb", "n046001b.638", 524288, 0xb2a86447, 0, 262144},
		{"2020bbh", "030-c4.bin", 524288, 0xbef75dd0, 0, 262144},
	},
	{
		ODD_COPY,
		{"2020bb", "n046001b.638", 524288, 0xb2a86447, 262144, 262144},
		{"2020bbh", "030-c4.bin", 524288, 0xbef75dd0, 0, 262144},
	},*/
	{
		EVEN_COPY,
		{"2020bb", "n046001a.538", 524288, 0x746bf48a, 0, 262144},
		{"2020bbh", "030-c1.bin", 1048576, 0x4f5e19bd, 0, 262144},
	},
	{
		ODD_COPY,
		{"2020bb", "n046001a.538", 524288, 0x746bf48a, 262144, 262144},
		{"2020bbh", "030-c1.bin", 1048576, 0x4f5e19bd, 0, 262144},
	},
	{
		EVEN_COPY,
		{"2020bb", "n046001a.638", 524288, 0x5c123d9c, 0, 262144},
		{"2020bbh", "030-c2.bin", 1048576, 0xd6314bf0, 0, 262144},
	},
	{
		ODD_COPY,
		{"2020bb", "n046001a.638", 524288, 0x5c123d9c, 262144, 262144},
		{"2020bbh", "030-c2.bin", 1048576, 0xd6314bf0, 0, 262144},
	},
	{
		EVEN_COPY,
		{"2020bb", "n046001a.53c", 524288, 0x57bdcec0, 0, 262144},
		{"2020bbh", "030-c1.bin", 1048576, 0x4f5e19bd, 524288, 262144},
	},
	{
		ODD_COPY,
		{"2020bb", "n046001a.53c", 524288, 0x57bdcec0, 262144, 262144},
		{"2020bbh", "030-c1.bin", 1048576, 0x4f5e19bd, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"2020bb", "n046001a.63c", 524288, 0x2f4bb615, 0, 262144},
		{"2020bbh", "030-c2.bin", 1048576, 0xd6314bf0, 524288, 262144},
	},
	{
		ODD_COPY,
		{"2020bb", "n046001a.63c", 524288, 0x2f4bb615, 262144, 262144},
		{"2020bbh", "030-c2.bin", 1048576, 0xd6314bf0, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"2020bb", "n046001a.038", 524288, 0xefb016a2, 0, 262144},
		{"2020bbh", "030-p1h.bin", 524288, 0x12d048d7, 0, 262144},
	},
	{
		ODD_COPY,
		{"2020bb", "n046001a.038", 524288, 0xefb016a2, 262144, 262144},
		{"2020bbh", "030-p1h.bin", 524288, 0x12d048d7, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001a.038", 524288, 0x4639b419, 0, 262144},
		{"androdun", "049-p1.bin", 524288, 0x3b857da2, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001a.03c", 524288, 0x11beb098, 0, 262144},
		{"androdun", "049-p2.bin", 524288, 0x2f062209, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001a.038", 524288, 0x4639b419, 262144, 262144},
		{"androdun", "049-p1.bin", 524288, 0x3b857da2, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001a.03c", 524288, 0x11beb098, 262144, 262144},
		{"androdun", "049-p2.bin", 524288, 0x2f062209, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001a.538", 524288, 0xca08e432, 0, 262144},
		{"androdun", "049-c1.bin", 1048576, 0x7ace6db3, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001a.638", 524288, 0x7a0deb9e, 0, 262144},
		{"androdun", "049-c2.bin", 1048576, 0xb17024f7, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001c.538", 524288, 0xca08e432, 0, 262144},
		{"androdun", "049-c1.bin", 1048576, 0x7ace6db3, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001c.638", 524288, 0x7a0deb9e, 0, 262144},
		{"androdun", "049-c2.bin", 1048576, 0xb17024f7, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001a.53c", 524288, 0xfcbcb305, 0, 262144},
		{"androdun", "049-c1.bin", 1048576, 0x7ace6db3, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001a.63c", 524288, 0xb1c640f5, 0, 262144},
		{"androdun", "049-c2.bin", 1048576, 0xb17024f7, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001c.53c", 524288, 0xfcbcb305, 0, 262144},
		{"androdun", "049-c1.bin", 1048576, 0x7ace6db3, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001c.63c", 524288, 0xb1c640f5, 0, 262144},
		{"androdun", "049-c2.bin", 1048576, 0xb17024f7, 524288, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001a.538", 524288, 0xca08e432, 262144, 262144},
		{"androdun", "049-c1.bin", 1048576, 0x7ace6db3, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001a.638", 524288, 0x7a0deb9e, 262144, 262144},
		{"androdun", "049-c2.bin", 1048576, 0xb17024f7, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001c.538", 524288, 0xca08e432, 262144, 262144},
		{"androdun", "049-c1.bin", 1048576, 0x7ace6db3, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001c.638", 524288, 0x7a0deb9e, 262144, 262144},
		{"androdun", "049-c2.bin", 1048576, 0xb17024f7, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001a.53c", 524288, 0xfcbcb305, 262144, 262144},
		{"androdun", "049-c1.bin", 1048576, 0x7ace6db3, 524288, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001a.63c", 524288, 0xb1c640f5, 262144, 262144},
		{"androdun", "049-c2.bin", 1048576, 0xb17024f7, 524288, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001c.53c", 524288, 0xfcbcb305, 262144, 262144},
		{"androdun", "049-c1.bin", 1048576, 0x7ace6db3, 524288, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001c.63c", 524288, 0xb1c640f5, 262144, 262144},
		{"androdun", "049-c2.bin", 1048576, 0xb17024f7, 524288, 262144},
	},
	/* Since MAME changed androdun in v0.70 it is impossible to re-build some of these ROMs
	{
		EVEN_COPY,
		{"androdun", "n138001b.538", 524288, 0x806ab937, 0, 262144},
		{"androdun", "049-c3.bin", 1048576, 0x2e0f3f9a, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001b.638", 524288, 0x33bee10f, 0, 262144},
		{"androdun", "049-c4.bin", 1048576, 0x4a19fb92, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001b.638", 524288, 0x33bee10f, 262144, 262144},
		{"androdun", "049-c4.bin", 1048576, 0x4a19fb92, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001d.538", 524288, 0x806ab937, 0, 262144},
		{"androdun", "049-c3.bin", 1048576, 0x2e0f3f9a, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001d.638", 524288, 0x33bee10f, 0, 262144},
		{"androdun", "049-c4.bin", 1048576, 0x4a19fb92, 0, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001b.53c", 524288, 0xe7e1a2be, 0, 262144},
		{"androdun", "049-c3.bin", 1048576, 0x2e0f3f9a, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001b.63c", 524288, 0x70f0d263, 0, 262144},
		{"androdun", "049-c4.bin", 1048576, 0x4a19fb92, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001d.53c", 524288, 0xe7e1a2be, 0, 262144},
		{"androdun", "049-c3.bin", 1048576, 0x2e0f3f9a, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"androdun", "n138001d.63c", 524288, 0x70f0d263, 0, 262144},
		{"androdun", "049-c4.bin", 1048576, 0x4a19fb92, 524288, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001b.538", 524288, 0x806ab937, 262144, 262144},
		{"androdun", "049-c3.bin", 1048576, 0x2e0f3f9a, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001b.63c", 524288, 0x70f0d263, 262144, 262144},
		{"androdun", "049-c4.bin", 1048576, 0x4a19fb92, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001d.538", 524288, 0x806ab937, 262144, 262144},
		{"androdun", "049-c3.bin", 1048576, 0x2e0f3f9a, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001d.638", 524288, 0x33bee10f, 262144, 262144},
		{"androdun", "049-c4.bin", 1048576, 0x4a19fb92, 0, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001b.53c", 524288, 0xe7e1a2be, 262144, 262144},
		{"androdun", "049-c3.bin", 1048576, 0x2e0f3f9a, 524288, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001d.53c", 524288, 0xe7e1a2be, 262144, 262144},
		{"androdun", "049-c3.bin", 1048576, 0x2e0f3f9a, 524288, 262144},
	},
	{
		ODD_COPY,
		{"androdun", "n138001d.63c", 524288, 0x70f0d263, 262144, 262144},
		{"androdun", "049-c4.bin", 1048576, 0x4a19fb92, 524288, 262144},
	},
	*/
	{
		EVEN_COPY,
		{"bstars", "n138001a.038", 524288, 0x68ce5b06, 0, 262144},
		{"bstars", "002-p1.bin", 524288, 0x3bc7790e, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bstars", "n138001a.538", 524288, 0xc55a7229, 0, 262144},
		{"bstars", "002-c1.bin", 524288, 0xaaff2a45, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bstars", "n138001a.53c", 524288, 0xa0074bd9, 0, 262144},
		{"bstars", "002-c3.bin", 524288, 0x96f0fdfa, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bstars", "n138001a.638", 524288, 0xcd3eeb2d, 0, 262144},
		{"bstars", "002-c2.bin", 524288, 0x3ba0f7e4, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bstars", "n138001a.63c", 524288, 0xd651fecf, 0, 262144},
		{"bstars", "002-c4.bin", 524288, 0x5fd87f2f, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bstars", "n138001b.538", 524288, 0xd57767e6, 0, 262144},
		{"bstars", "002-c5.bin", 524288, 0x807ed83b, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bstars", "n138001b.638", 524288, 0x5d0a8692, 0, 262144},
		{"bstars", "002-c6.bin", 524288, 0x5a3cad41, 0, 262144},
	},
	{
		ODD_COPY,
		{"bstars", "n138001a.038", 524288, 0x68ce5b06, 262144, 262144},
		{"bstars", "002-p1.bin", 524288, 0x3bc7790e, 0, 262144},
	},
	{
		ODD_COPY,
		{"bstars", "n138001a.538", 524288, 0xc55a7229, 262144, 262144},
		{"bstars", "002-c1.bin", 524288, 0xaaff2a45, 0, 262144},
	},
	{
		ODD_COPY,
		{"bstars", "n138001a.53c", 524288, 0xa0074bd9, 262144, 262144},
		{"bstars", "002-c3.bin", 524288, 0x96f0fdfa, 0, 262144},
	},
	{
		ODD_COPY,
		{"bstars", "n138001a.638", 524288, 0xcd3eeb2d, 262144, 262144},
		{"bstars", "002-c2.bin", 524288, 0x3ba0f7e4, 0, 262144},
	},
	{
		ODD_COPY,
		{"bstars", "n138001a.63c", 524288, 0xd651fecf, 262144, 262144},
		{"bstars", "002-c4.bin", 524288, 0x5fd87f2f, 0, 262144},
	},
	{
		ODD_COPY,
		{"bstars", "n138001b.538", 524288, 0xd57767e6, 262144, 262144},
		{"bstars", "002-c5.bin", 524288, 0x807ed83b, 0, 262144},
	},
	{
		ODD_COPY,
		{"bstars", "n138001b.638", 524288, 0x5d0a8692, 262144, 262144},
		{"bstars", "002-c6.bin", 524288, 0x5a3cad41, 0, 262144},
	},
	{
		FULL_COPY,
		{"eightman", "n046001a.1f8", 524288, 0x0a2299b4, 0, 524288},
		{"eightman", "025-v1.bin", 1048576, 0x4558558a, 0, 524288},
	},
	{
		FULL_COPY,
		{"eightman", "n046001b.1f8", 524288, 0x6c3c3fec, 0, 524288},
		{"eightman", "025-v2.bin", 1048576, 0xc5e052e9, 0, 524288},
	},
	{
		FULL_COPY,
		{"eightman", "n046001a.1fc", 524288, 0xb695e254, 0, 524288},
		{"eightman", "025-v1.bin", 1048576, 0x4558558a, 524288, 524288},
	},
	{
		FULL_COPY,
		{"eightman", "n046001b.1fc", 524288, 0x375764df, 0, 524288},
		{"eightman", "025-v2.bin", 1048576, 0xc5e052e9, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"eightman", "n046001a.038", 524288, 0xe23e2631, 0, 262144},
		{"eightman", "025-p1.bin", 524288, 0x43344cb0, 0, 262144},
	},
	{
		EVEN_COPY,
		{"eightman", "n046001b.538", 524288, 0x12d53af0, 0, 262144},
		{"eightman", "025-c3.bin", 524288, 0x0923d5b0, 0, 262144},
	},
	{
		EVEN_COPY,
		{"eightman", "n046001b.638", 524288, 0x43cf58f9, 0, 262144},
		{"eightman", "025-c4.bin", 524288, 0xe3eca67b, 0, 262144},
	},
	{
		EVEN_COPY,
		{"eightman", "n046001a.538", 524288, 0xc916c9bf, 0, 262144},
		{"eightman", "025-c1.bin", 1048576, 0x555e16a4, 0, 262144},
	},
	{
		EVEN_COPY,
		{"eightman", "n046001a.638", 524288, 0x7114bce3, 0, 262144},
		{"eightman", "025-c2.bin", 1048576, 0xe1ee51c3, 0, 262144},
	},
	{
		EVEN_COPY,
		{"eightman", "n046001a.53c", 524288, 0x4b057b13, 0, 262144},
		{"eightman", "025-c1.bin", 1048576, 0x555e16a4, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"eightman", "n046001a.63c", 524288, 0x51da9a34, 0, 262144},
		{"eightman", "025-c2.bin", 1048576, 0xe1ee51c3, 524288, 262144},
	},
	{
		ODD_COPY,
		{"eightman", "n046001a.038", 524288, 0xe23e2631, 262144, 262144},
		{"eightman", "025-p1.bin", 524288, 0x43344cb0, 0, 262144},
	},
	{
		ODD_COPY,
		{"eightman", "n046001b.538", 524288, 0x12d53af0, 262144, 262144},
		{"eightman", "025-c3.bin", 524288, 0x0923d5b0, 0, 262144},
	},
	{
		ODD_COPY,
		{"eightman", "n046001b.638", 524288, 0x43cf58f9, 262144, 262144},
		{"eightman", "025-c4.bin", 524288, 0xe3eca67b, 0, 262144},
	},
	{
		ODD_COPY,
		{"eightman", "n046001a.538", 524288, 0xc916c9bf, 262144, 262144},
		{"eightman", "025-c1.bin", 1048576, 0x555e16a4, 0, 262144},
	},
	{
		ODD_COPY,
		{"eightman", "n046001a.638", 524288, 0x7114bce3, 262144, 262144},
		{"eightman", "025-c2.bin", 1048576, 0xe1ee51c3, 0, 262144},
	},
	{
		ODD_COPY,
		{"eightman", "n046001a.53c", 524288, 0x4b057b13, 262144, 262144},
		{"eightman", "025-c1.bin", 1048576, 0x555e16a4, 524288, 262144},
	},
	{
		ODD_COPY,
		{"eightman", "n046001a.63c", 524288, 0x51da9a34, 262144, 262144},
		{"eightman", "025-c2.bin", 1048576, 0xe1ee51c3, 524288, 262144},
	},
	{
		FULL_COPY,
		{"fbfrenzy", "n046001a.1f8", 524288, 0xd295da77, 0, 524288},
		{"fbfrenzy", "034-v1.bin", 1048576, 0x50c9d0dd, 0, 524288},
	},
	{
		FULL_COPY,
		{"fbfrenzy", "n046001b.1f8", 524288, 0xe438fb9d, 0, 524288},
		{"fbfrenzy", "034-v2.bin", 1048576, 0x5aa15686, 0, 524288},
	},
	{
		FULL_COPY,
		{"fbfrenzy", "n046001a.1fc", 524288, 0x249b7f52, 0, 524288},
		{"fbfrenzy", "034-v1.bin", 1048576, 0x50c9d0dd, 524288, 524288},
	},
	{
		FULL_COPY,
		{"fbfrenzy", "n046001b.1fc", 524288, 0x4f9bc109, 0, 524288},
		{"fbfrenzy", "034-v2.bin", 1048576, 0x5aa15686, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"fbfrenzy", "n046001a.038", 524288, 0xc9fc879c, 0, 262144},
		{"fbfrenzy", "034-p1.bin", 524288, 0xcdef6b19, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fbfrenzy", "n046001b.538", 524288, 0x9abe41c8, 0, 262144},
		{"fbfrenzy", "034-c3.bin", 524288, 0xe5aa65f5, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fbfrenzy", "n046001b.638", 524288, 0x336540a8, 0, 262144},
		{"fbfrenzy", "034-c4.bin", 524288, 0x0eb138cc, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fbfrenzy", "n046001a.538", 524288, 0xcd377680, 0, 262144},
		{"fbfrenzy", "034-c1.bin", 1048576, 0x91c56e78, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fbfrenzy", "n046001a.638", 524288, 0x8b76358f, 0, 262144},
		{"fbfrenzy", "034-c2.bin", 1048576, 0x9743ea2f, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fbfrenzy", "n046001a.53c", 524288, 0x2f6d09c2, 0, 262144},
		{"fbfrenzy", "034-c1.bin", 1048576, 0x91c56e78, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"fbfrenzy", "n046001a.63c", 524288, 0x77e45dd2, 0, 262144},
		{"fbfrenzy", "034-c2.bin", 1048576, 0x9743ea2f, 524288, 262144},
	},
	{
		ODD_COPY,
		{"fbfrenzy", "n046001a.038", 524288, 0xc9fc879c, 262144, 262144},
		{"fbfrenzy", "034-p1.bin", 524288, 0xcdef6b19, 0, 262144},
	},
	{
		ODD_COPY,
		{"fbfrenzy", "n046001b.538", 524288, 0x9abe41c8, 262144, 262144},
		{"fbfrenzy", "034-c3.bin", 524288, 0xe5aa65f5, 0, 262144},
	},
	{
		ODD_COPY,
		{"fbfrenzy", "n046001b.638", 524288, 0x336540a8, 262144, 262144},
		{"fbfrenzy", "034-c4.bin", 524288, 0x0eb138cc, 0, 262144},
	},
	{
		ODD_COPY,
		{"fbfrenzy", "n046001a.538", 524288, 0xcd377680, 262144, 262144},
		{"fbfrenzy", "034-c1.bin", 1048576, 0x91c56e78, 0, 262144},
	},
	{
		ODD_COPY,
		{"fbfrenzy", "n046001a.638", 524288, 0x8b76358f, 262144, 262144},
		{"fbfrenzy", "034-c2.bin", 1048576, 0x9743ea2f, 0, 262144},
	},
	{
		ODD_COPY,
		{"fbfrenzy", "n046001a.53c", 524288, 0x2f6d09c2, 262144, 262144},
		{"fbfrenzy", "034-c1.bin", 1048576, 0x91c56e78, 524288, 262144},
	},
	{
		ODD_COPY,
		{"fbfrenzy", "n046001a.63c", 524288, 0x77e45dd2, 262144, 262144},
		{"fbfrenzy", "034-c2.bin", 1048576, 0x9743ea2f, 524288, 262144},
	},
	{
		FULL_COPY,
		{"gpilots", "n058001a.178", 524288, 0x8cc44140, 0, 524288},
		{"gpilots", "020-v11.bin", 1048576, 0x1b526c8b, 0, 524288},
	},
	{
		FULL_COPY,
		{"gpilots", "n058001a.478", 65536, 0xfc05fb8b, 0, 65536},
		{"gpilots", "020-m1.bin", 131072, 0x48409377, 0, 65536},
	},
	{
		FULL_COPY,
		{"gpilots", "n058001a.17c", 524288, 0x415c61cd, 0, 524288},
		{"gpilots", "020-v11.bin", 1048576, 0x1b526c8b, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.038", 524288, 0xfc5837c0, 0, 262144},
		{"gpilots", "020-p1.bin", 524288, 0xe6f2fe64, 0, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.538", 524288, 0x92b8ee5f, 0, 262144},
		{"gpilots", "020-c1.bin", 1048576, 0xbd6fe78e, 0, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.638", 524288, 0x05733639, 0, 262144},
		{"gpilots", "020-c2.bin", 1048576, 0x5f4a925c, 0, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001b.538", 524288, 0x4f12268b, 0, 262144},
		{"gpilots", "020-c3.bin", 1048576, 0xd1e42fd0, 0, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001b.638", 524288, 0x2c586176, 0, 262144},
		{"gpilots", "020-c4.bin", 1048576, 0xedde439b, 0, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.53c", 524288, 0x8c8e42e9, 0, 262144},
		{"gpilots", "020-c1.bin", 1048576, 0xbd6fe78e, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.63c", 524288, 0x347fef2b, 0, 262144},
		{"gpilots", "020-c2.bin", 1048576, 0x5f4a925c, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001b.53c", 524288, 0x7c3c9c7e, 0, 262144},
		{"gpilots", "020-c3.bin", 1048576, 0xd1e42fd0, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001b.63c", 524288, 0x9b2eee8b, 0, 262144},
		{"gpilots", "020-c4.bin", 1048576, 0xedde439b, 524288, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.038", 524288, 0xfc5837c0, 262144, 262144},
		{"gpilots", "020-p1.bin", 524288, 0xe6f2fe64, 0, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.538", 524288, 0x92b8ee5f, 262144, 262144},
		{"gpilots", "020-c1.bin", 1048576, 0xbd6fe78e, 0, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.638", 524288, 0x05733639, 262144, 262144},
		{"gpilots", "020-c2.bin", 1048576, 0x5f4a925c, 0, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001b.538", 524288, 0x4f12268b, 262144, 262144},
		{"gpilots", "020-c3.bin", 1048576, 0xd1e42fd0, 0, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001b.638", 524288, 0x2c586176, 262144, 262144},
		{"gpilots", "020-c4.bin", 1048576, 0xedde439b, 0, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.53c", 524288, 0x8c8e42e9, 262144, 262144},
		{"gpilots", "020-c1.bin", 1048576, 0xbd6fe78e, 524288, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.63c", 524288, 0x347fef2b, 262144, 262144},
		{"gpilots", "020-c2.bin", 1048576, 0x5f4a925c, 524288, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001b.53c", 524288, 0x7c3c9c7e, 262144, 262144},
		{"gpilots", "020-c3.bin", 1048576, 0xd1e42fd0, 524288, 262144},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001b.63c", 524288, 0x9b2eee8b, 262144, 262144},
		{"gpilots", "020-c4.bin", 1048576, 0xedde439b, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.03c", 524288, 0x47a641da, 0, 65536},
		{"gpilots", "020-p2.bin", 131072, 0xedcb22ac, 0, 65536},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.03c", 524288, 0x47a641da, 65536, 65536},
		{"gpilots", "020-p2.bin", 131072, 0xedcb22ac, 0, 65536},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.03c", 524288, 0x47a641da, 131072, 65536},
		{"gpilots", "020-p2.bin", 131072, 0xedcb22ac, 0, 65536},
	},
	{
		EVEN_COPY,
		{"gpilots", "n058001a.03c", 524288, 0x47a641da, 196608, 65536},
		{"gpilots", "020-p2.bin", 131072, 0xedcb22ac, 0, 65536},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.03c", 524288, 0x47a641da, 262144, 65536},
		{"gpilots", "020-p2.bin", 131072, 0xedcb22ac, 0, 65536},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.03c", 524288, 0x47a641da, 327680, 65536},
		{"gpilots", "020-p2.bin", 131072, 0xedcb22ac, 0, 65536},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.03c", 524288, 0x47a641da, 393216, 65536},
		{"gpilots", "020-p2.bin", 131072, 0xedcb22ac, 0, 65536},
	},
	{
		ODD_COPY,
		{"gpilots", "n058001a.03c", 524288, 0x47a641da, 458752, 65536},
		{"gpilots", "020-p2.bin", 131072, 0xedcb22ac, 0, 65536},
	},
	{
		EVEN_COPY,
		{"joyjoy", "n022001a.038", 524288, 0xea512c9f, 0, 262144},
		{"joyjoy", "021-p1.bin", 524288, 0x39c3478f, 0, 262144},
	},
	{
		EVEN_COPY,
		{"joyjoy", "n022001a.538", 524288, 0xcb27be65, 0, 262144},
		{"joyjoy", "021-c1.bin", 524288, 0x509250ec, 0, 262144},
	},
	{
		EVEN_COPY,
		{"joyjoy", "n022001a.638", 524288, 0x7e134979, 0, 262144},
		{"joyjoy", "021-c2.bin", 524288, 0x09ed5258, 0, 262144},
	},
	{
		ODD_COPY,
		{"joyjoy", "n022001a.038", 524288, 0xea512c9f, 262144, 262144},
		{"joyjoy", "021-p1.bin", 524288, 0x39c3478f, 0, 262144},
	},
	{
		ODD_COPY,
		{"joyjoy", "n022001a.538", 524288, 0xcb27be65, 262144, 262144},
		{"joyjoy", "021-c1.bin", 524288, 0x509250ec, 0, 262144},
	},
	{
		ODD_COPY,
		{"joyjoy", "n022001a.638", 524288, 0x7e134979, 262144, 262144},
		{"joyjoy", "021-c2.bin", 524288, 0x09ed5258, 0, 262144},
	},
	/* Commented out whilst doing the CAESAR update for MAME v0.128
	{
		FULL_COPY,
		{"lbowling", "n050001a.478", 65536, 0x535ec016, 0, 65536},
		{"lbowling", "019-m1.bin", 131072, 0x589d7f25, 0, 65536},
	},
	*/
	{
		EVEN_COPY,
		{"lbowling", "n050001a.038", 524288, 0x380e358d, 0, 262144},
		{"lbowling", "019-p1.bin", 524288, 0xa2de8445, 0, 262144},
	},
	{
		EVEN_COPY,
		{"lbowling", "n050001a.538", 524288, 0x17df7955, 0, 262144},
		{"lbowling", "019-c1.bin", 524288, 0x4ccdef18, 0, 262144},
	},
	{
		EVEN_COPY,
		{"lbowling", "n050001a.638", 524288, 0x84fd2c90, 0, 262144},
		{"lbowling", "019-c2.bin", 524288, 0xd4dd0802, 0, 262144},
	},
	{
		ODD_COPY,
		{"lbowling", "n050001a.038", 524288, 0x380e358d, 262144, 262144},
		{"lbowling", "019-p1.bin", 524288, 0xa2de8445, 0, 262144},
	},
	{
		ODD_COPY,
		{"lbowling", "n050001a.538", 524288, 0x17df7955, 262144, 262144},
		{"lbowling", "019-c1.bin", 524288, 0x4ccdef18, 0, 262144},
	},
	{
		ODD_COPY,
		{"lbowling", "n050001a.638", 524288, 0x84fd2c90, 262144, 262144},
		{"lbowling", "019-c2.bin", 524288, 0xd4dd0802, 0, 262144},
	},
	{
		FULL_COPY,
		{"lresort", "n046001a.1f8", 524288, 0x0722da38, 0, 524288},
		{"lresort", "024-v1.bin", 1048576, 0xefdfa063, 0, 524288},
	},
	{
		FULL_COPY,
		{"lresort", "n046001b.1f8", 524288, 0x2e39462b, 0, 524288},
		{"lresort", "024-v2.bin", 1048576, 0x3c7997c0, 0, 524288},
	},
	{
		FULL_COPY,
		{"lresort", "n046001a.1fc", 524288, 0x670ce3ec, 0, 524288},
		{"lresort", "024-v1.bin", 1048576, 0xefdfa063, 524288, 524288},
	},
	{
		FULL_COPY,
		{"lresort", "n046001b.1fc", 524288, 0x7944754f, 0, 524288},
		{"lresort", "024-v2.bin", 1048576, 0x3c7997c0, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"lresort", "n046001a.038", 524288, 0x5f0a5a4b, 0, 262144},
		{"lresort", "024-p1.bin", 524288, 0x89c4ab97, 0, 262144},
	},
	{
		EVEN_COPY,
		{"lresort", "n046001b.538", 524288, 0xe7138cb9, 0, 262144},
		{"lresort", "024-c3.bin", 524288, 0xe9f745f8, 0, 262144},
	},
	{
		EVEN_COPY,
		{"lresort", "n046001b.638", 524288, 0x08178e27, 0, 262144},
		{"lresort", "024-c4.bin", 524288, 0x7382fefb, 0, 262144},
	},
	{
		EVEN_COPY,
		{"lresort", "n046001a.538", 524288, 0x9f7995a9, 0, 262144},
		{"lresort", "024-c1.bin", 1048576, 0x3617c2dc, 0, 262144},
	},
	{
		EVEN_COPY,
		{"lresort", "n046001a.638", 524288, 0x68c70bac, 0, 262144},
		{"lresort", "024-c2.bin", 1048576, 0x3f0a7fd8, 0, 262144},
	},
	{
		EVEN_COPY,
		{"lresort", "n046001a.53c", 524288, 0xe122b155, 0, 262144},
		{"lresort", "024-c1.bin", 1048576, 0x3617c2dc, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"lresort", "n046001a.63c", 524288, 0xf18a9b02, 0, 262144},
		{"lresort", "024-c2.bin", 1048576, 0x3f0a7fd8, 524288, 262144},
	},
	{
		ODD_COPY,
		{"lresort", "n046001a.038", 524288, 0x5f0a5a4b, 262144, 262144},
		{"lresort", "024-p1.bin", 524288, 0x89c4ab97, 0, 262144},
	},
	{
		ODD_COPY,
		{"lresort", "n046001b.538", 524288, 0xe7138cb9, 262144, 262144},
		{"lresort", "024-c3.bin", 524288, 0xe9f745f8, 0, 262144},
	},
	{
		ODD_COPY,
		{"lresort", "n046001b.638", 524288, 0x08178e27, 262144, 262144},
		{"lresort", "024-c4.bin", 524288, 0x7382fefb, 0, 262144},
	},
	{
		ODD_COPY,
		{"lresort", "n046001a.538", 524288, 0x9f7995a9, 262144, 262144},
		{"lresort", "024-c1.bin", 1048576, 0x3617c2dc, 0, 262144},
	},
	{
		ODD_COPY,
		{"lresort", "n046001a.638", 524288, 0x68c70bac, 262144, 262144},
		{"lresort", "024-c2.bin", 1048576, 0x3f0a7fd8, 0, 262144},
	},
	{
		ODD_COPY,
		{"lresort", "n046001a.53c", 524288, 0xe122b155, 262144, 262144},
		{"lresort", "024-c1.bin", 1048576, 0x3617c2dc, 524288, 262144},
	},
	{
		ODD_COPY,
		{"lresort", "n046001a.63c", 524288, 0xf18a9b02, 262144, 262144},
		{"lresort", "024-c2.bin", 1048576, 0x3f0a7fd8, 524288, 262144},
	},
	{
		FULL_COPY,
		{"minasan", "n054001a.178", 524288, 0x79d65e8e, 0, 524288},
		{"minasan", "027-v11.bin", 1048576, 0x59ad4459, 0, 524288},
	},
	{
		FULL_COPY,
		{"minasan", "n054001a.278", 524288, 0x0100e548, 0, 524288},
		{"minasan", "027-v21.bin", 1048576, 0xdf5b4eeb, 0, 524288},
	},
	{
		FULL_COPY,
		{"minasan", "n054001a.478", 65536, 0x19ef88ea, 0, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "n054001a.27c", 524288, 0x0c31c5b0, 0, 524288},
		{"minasan", "027-v21.bin", 1048576, 0xdf5b4eeb, 524288, 524288},
	},
	{
		FULL_COPY,
		{"minasan", "n054001a.17c", 524288, 0x0b3854d5, 0, 524288},
		{"minasan", "027-v11.bin", 1048576, 0x59ad4459, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001a.638", 524288, 0xf774d850, 0, 262144},
		{"minasan", "027-c2.bin", 1048576, 0xda61f5a6, 0, 262144},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001b.538", 524288, 0x3dae0a05, 0, 262144},
		{"minasan", "027-c3.bin", 1048576, 0x08df1228, 0, 262144},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001b.638", 524288, 0x0fb30b5b, 0, 262144},
		{"minasan", "027-c4.bin", 1048576, 0x54e87696, 0, 262144},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001a.538", 524288, 0x43f48265, 0, 262144},
		{"minasan", "027-c1.bin", 1048576, 0xd0086f94, 0, 262144},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001a.63c", 524288, 0x14a81e58, 0, 262144},
		{"minasan", "027-c2.bin", 1048576, 0xda61f5a6, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001b.53c", 524288, 0x6979368e, 0, 262144},
		{"minasan", "027-c3.bin", 1048576, 0x08df1228, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001b.63c", 524288, 0xcfa90d59, 0, 262144},
		{"minasan", "027-c4.bin", 1048576, 0x54e87696, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001a.53c", 524288, 0xcbf9eef8, 0, 262144},
		{"minasan", "027-c1.bin", 1048576, 0xd0086f94, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"minasan", "n054001a.038", 524288, 0x86805d5a, 0, 262144},
		{"minasan", "027-p1.bin", 524288, 0xc8381327, 0, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001a.038", 524288, 0x86805d5a, 262144, 262144},
		{"minasan", "027-p1.bin", 524288, 0xc8381327, 0, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001a.638", 524288, 0xf774d850, 262144, 262144},
		{"minasan", "027-c2.bin", 1048576, 0xda61f5a6, 0, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001b.538", 524288, 0x3dae0a05, 262144, 262144},
		{"minasan", "027-c3.bin", 1048576, 0x08df1228, 0, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001b.638", 524288, 0x0fb30b5b, 262144, 262144},
		{"minasan", "027-c4.bin", 1048576, 0x54e87696, 0, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001a.538", 524288, 0x43f48265, 262144, 262144},
		{"minasan", "027-c1.bin", 1048576, 0xd0086f94, 0, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001a.63c", 524288, 0x14a81e58, 262144, 262144},
		{"minasan", "027-c2.bin", 1048576, 0xda61f5a6, 524288, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001b.53c", 524288, 0x6979368e, 262144, 262144},
		{"minasan", "027-c3.bin", 1048576, 0x08df1228, 524288, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001b.63c", 524288, 0xcfa90d59, 262144, 262144},
		{"minasan", "027-c4.bin", 1048576, 0x54e87696, 524288, 262144},
	},
	{
		ODD_COPY,
		{"minasan", "n054001a.53c", 524288, 0xcbf9eef8, 262144, 262144},
		{"minasan", "027-c1.bin", 1048576, 0xd0086f94, 524288, 262144},
	},
	{
		FULL_COPY,
		{"mutnat", "n054001a.1f8", 524288, 0x8db2effe, 0, 524288},
		{"mutnat", "014-v1.bin", 1048576, 0x25419296, 0, 524288},
	},
	{
		FULL_COPY,
		{"mutnat", "n054001b.1f8", 524288, 0x2ba17cb7, 0, 524288},
		{"mutnat", "014-v2.bin", 1048576, 0x0de53d5e, 0, 524288},
	},
	{
		FULL_COPY,
		{"mutnat", "n054001a.1fc", 524288, 0xa49fe238, 0, 524288},
		{"mutnat", "014-v1.bin", 1048576, 0x25419296, 524288, 524288},
	},
	{
		FULL_COPY,
		{"mutnat", "n054001b.1fc", 524288, 0x42419a29, 0, 524288},
		{"mutnat", "014-v2.bin", 1048576, 0x0de53d5e, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001a.038", 524288, 0x30cbd46b, 0, 262144},
		{"mutnat", "014-p1.bin", 524288, 0x6f1699c8, 0, 262144},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001a.538", 524288, 0x83d59ccf, 0, 262144},
		{"mutnat", "014-c1.bin", 1048576, 0x5e4381bf, 0, 262144},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001a.638", 524288, 0x9e115a04, 0, 262144},
		{"mutnat", "014-c2.bin", 1048576, 0x69ba4e18, 0, 262144},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001b.538", 524288, 0xeaa2801a, 0, 262144},
		{"mutnat", "014-c3.bin", 1048576, 0x890327d5, 0, 262144},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001b.638", 524288, 0x32bf4a2d, 0, 262144},
		{"mutnat", "014-c4.bin", 1048576, 0xe4002651, 0, 262144},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001a.53c", 524288, 0xb2f1409d, 0, 262144},
		{"mutnat", "014-c1.bin", 1048576, 0x5e4381bf, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001a.63c", 524288, 0x1bb648c1, 0, 262144},
		{"mutnat", "014-c2.bin", 1048576, 0x69ba4e18, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001b.53c", 524288, 0xc718b731, 0, 262144},
		{"mutnat", "014-c3.bin", 1048576, 0x890327d5, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"mutnat", "n054001b.63c", 524288, 0x7d120067, 0, 262144},
		{"mutnat", "014-c4.bin", 1048576, 0xe4002651, 524288, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001a.038", 524288, 0x30cbd46b, 262144, 262144},
		{"mutnat", "014-p1.bin", 524288, 0x6f1699c8, 0, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001a.538", 524288, 0x83d59ccf, 262144, 262144},
		{"mutnat", "014-c1.bin", 1048576, 0x5e4381bf, 0, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001a.638", 524288, 0x9e115a04, 262144, 262144},
		{"mutnat", "014-c2.bin", 1048576, 0x69ba4e18, 0, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001b.538", 524288, 0xeaa2801a, 262144, 262144},
		{"mutnat", "014-c3.bin", 1048576, 0x890327d5, 0, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001b.638", 524288, 0x32bf4a2d, 262144, 262144},
		{"mutnat", "014-c4.bin", 1048576, 0xe4002651, 0, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001a.53c", 524288, 0xb2f1409d, 262144, 262144},
		{"mutnat", "014-c1.bin", 1048576, 0x5e4381bf, 524288, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001a.63c", 524288, 0x1bb648c1, 262144, 262144},
		{"mutnat", "014-c2.bin", 1048576, 0x69ba4e18, 524288, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001b.53c", 524288, 0xc718b731, 262144, 262144},
		{"mutnat", "014-c3.bin", 1048576, 0x890327d5, 524288, 262144},
	},
	{
		ODD_COPY,
		{"mutnat", "n054001b.63c", 524288, 0x7d120067, 262144, 262144},
		{"mutnat", "014-c4.bin", 1048576, 0xe4002651, 524288, 262144},
	},
	{
		FULL_COPY,
		{"ncommand", "n054001a.1f8", 524288, 0x222e71c8, 0, 524288},
		{"ncommand", "050-v1.bin", 1048576, 0x23c3ab42, 0, 524288},
	},
	{
		FULL_COPY,
		{"ncommand", "n054001a.4f8", 65536, 0x26e93026, 0, 65536},
		{"ncommand", "050-m1.bin", 131072, 0x6fcf07d3, 0, 65536},
	},
	{
		FULL_COPY,
		{"ncommand", "n054001a.1fc", 524288, 0x12acd064, 0, 524288},
		{"ncommand", "050-v1.bin", 1048576, 0x23c3ab42, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001a.038", 524288, 0xfdaaca42, 0, 262144},
		{"ncommand", "050-p1.bin", 1048576, 0x4e097c40, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001a.538", 524288, 0x73acaa79, 0, 262144},
		{"ncommand", "050-c1.bin", 1048576, 0x87421a0a, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001a.638", 524288, 0x7b24359f, 0, 262144},
		{"ncommand", "050-c2.bin", 1048576, 0xc4cf5548, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001b.538", 524288, 0xc8d763cd, 0, 262144},
		{"ncommand", "050-c3.bin", 1048576, 0x03422c1e, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001b.638", 524288, 0x574612ec, 0, 262144},
		{"ncommand", "050-c4.bin", 1048576, 0x0845eadb, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001a.03c", 524288, 0xb34e91fe, 0, 262144},
		{"ncommand", "050-p1.bin", 1048576, 0x4e097c40, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001a.53c", 524288, 0xad56623d, 0, 262144},
		{"ncommand", "050-c1.bin", 1048576, 0x87421a0a, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001a.63c", 524288, 0x0913a784, 0, 262144},
		{"ncommand", "050-c2.bin", 1048576, 0xc4cf5548, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001b.53c", 524288, 0x63829529, 0, 262144},
		{"ncommand", "050-c3.bin", 1048576, 0x03422c1e, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"ncommand", "n054001b.63c", 524288, 0x990d302a, 0, 262144},
		{"ncommand", "050-c4.bin", 1048576, 0x0845eadb, 524288, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001a.038", 524288, 0xfdaaca42, 262144, 262144},
		{"ncommand", "050-p1.bin", 1048576, 0x4e097c40, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001a.538", 524288, 0x73acaa79, 262144, 262144},
		{"ncommand", "050-c1.bin", 1048576, 0x87421a0a, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001a.638", 524288, 0x7b24359f, 262144, 262144},
		{"ncommand", "050-c2.bin", 1048576, 0xc4cf5548, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001b.538", 524288, 0xc8d763cd, 262144, 262144},
		{"ncommand", "050-c3.bin", 1048576, 0x03422c1e, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001b.638", 524288, 0x574612ec, 262144, 262144},
		{"ncommand", "050-c4.bin", 1048576, 0x0845eadb, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001a.03c", 524288, 0xb34e91fe, 262144, 262144},
		{"ncommand", "050-p1.bin", 1048576, 0x4e097c40, 524288, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001a.53c", 524288, 0xad56623d, 262144, 262144},
		{"ncommand", "050-c1.bin", 1048576, 0x87421a0a, 524288, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001a.63c", 524288, 0x0913a784, 262144, 262144},
		{"ncommand", "050-c2.bin", 1048576, 0xc4cf5548, 524288, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001b.53c", 524288, 0x63829529, 262144, 262144},
		{"ncommand", "050-c3.bin", 1048576, 0x03422c1e, 524288, 262144},
	},
	{
		ODD_COPY,
		{"ncommand", "n054001b.63c", 524288, 0x990d302a, 262144, 262144},
		{"ncommand", "050-c4.bin", 1048576, 0x0845eadb, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"ridhero", "n046001a.038", 524288, 0xdabfac95, 0, 262144},
		{"ridheroh", "006-p1h.bin", 524288, 0x52445646, 0, 262144},
	},
	{
		ODD_COPY,
		{"ridhero", "n046001a.038", 524288, 0xdabfac95, 262144, 262144},
		{"ridheroh", "006-p1h.bin", 524288, 0x52445646, 0, 262144},
	},
	/* Commented out whilst doing the CAESAR update for MAME v0.128
	{
		FULL_COPY,
		{"ridhero", "n046001a.478", 65536, 0xf7196558, 0, 65536},
		{"ridheroh", "006-m1.bin", 131072, 0xf0b6425d, 0, 65536},
	},
	*/
	{
		EVEN_COPY,
		{"ridhero", "n046001a.538", 524288, 0x24096241, 0, 262144},
		{"ridheroh", "006-c1.bin", 524288, 0x4a5c7f78, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ridhero", "n046001a.53c", 524288, 0x7026a3a2, 0, 262144},
		{"ridheroh", "006-c3.bin", 524288, 0x8acff765, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ridhero", "n046001a.638", 524288, 0xdf6a5b00, 0, 262144},
		{"ridheroh", "006-c2.bin", 524288, 0xe0b70ece, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ridhero", "n046001a.63c", 524288, 0x15220d51, 0, 262144},
		{"ridheroh", "006-c4.bin", 524288, 0x205e3208, 0, 262144},
	},
	{
		ODD_COPY,
		{"ridhero", "n046001a.538", 524288, 0x24096241, 262144, 262144},
		{"ridheroh", "006-c1.bin", 524288, 0x4a5c7f78, 0, 262144},
	},
	{
		ODD_COPY,
		{"ridhero", "n046001a.53c", 524288, 0x7026a3a2, 262144, 262144},
		{"ridheroh", "006-c3.bin", 524288, 0x8acff765, 0, 262144},
	},
	{
		ODD_COPY,
		{"ridhero", "n046001a.638", 524288, 0xdf6a5b00, 262144, 262144},
		{"ridheroh", "006-c2.bin", 524288, 0xe0b70ece, 0, 262144},
	},
	{
		ODD_COPY,
		{"ridhero", "n046001a.63c", 524288, 0x15220d51, 262144, 262144},
		{"ridheroh", "006-c4.bin", 524288, 0x205e3208, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.038", 524288, 0x4483bae1, 0, 262144},
		{"sengokh", "017-hp1.bin", 524288, 0x33eccae0, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.038", 524288, 0x4483bae1, 262144, 262144},
		{"sengokh", "017-hp1.bin", 524288, 0x33eccae0, 0, 262144},
	},
	{
		FULL_COPY,
		{"sengoku", "n058001a.1f8", 524288, 0x205258a7, 0, 524288},
		{"sengokh", "017-v1.bin", 1048576, 0x23663295, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku", "n058001b.1f8", 524288, 0x6421bdf3, 0, 524288},
		{"sengokh", "017-v2.bin", 1048576, 0xf61e6765, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku", "n058001a.1fc", 524288, 0x6fbe52c8, 0, 524288},
		{"sengokh", "017-v1.bin", 1048576, 0x23663295, 524288, 524288},
	},
	{
		FULL_COPY,
		{"sengoku", "n058001b.1fc", 524288, 0x1f9578fb, 0, 524288},
		{"sengokh", "017-v2.bin", 1048576, 0xf61e6765, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.538", 524288, 0xe834b925, 0, 262144},
		{"sengokh", "017-c1.bin", 1048576, 0xb4eb82a1, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.638", 524288, 0x96de5eb9, 0, 262144},
		{"sengokh", "017-c2.bin", 1048576, 0xd55c550d, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001b.538", 524288, 0x443c552c, 0, 262144},
		{"sengokh", "017-c3.bin", 1048576, 0xed51ef65, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001b.638", 524288, 0xafbd5b0b, 0, 262144},
		{"sengokh", "017-c4.bin", 1048576, 0xf4f3c9cb, 0, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.53c", 524288, 0x66be6d46, 0, 262144},
		{"sengokh", "017-c1.bin", 1048576, 0xb4eb82a1, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.63c", 524288, 0x25f5fd7b, 0, 262144},
		{"sengokh", "017-c2.bin", 1048576, 0xd55c550d, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001b.53c", 524288, 0xecb41adc, 0, 262144},
		{"sengokh", "017-c3.bin", 1048576, 0xed51ef65, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001b.63c", 524288, 0x78b25278, 0, 262144},
		{"sengokh", "017-c4.bin", 1048576, 0xf4f3c9cb, 524288, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.538", 524288, 0xe834b925, 262144, 262144},
		{"sengokh", "017-c1.bin", 1048576, 0xb4eb82a1, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.638", 524288, 0x96de5eb9, 262144, 262144},
		{"sengokh", "017-c2.bin", 1048576, 0xd55c550d, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001b.538", 524288, 0x443c552c, 262144, 262144},
		{"sengokh", "017-c3.bin", 1048576, 0xed51ef65, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001b.638", 524288, 0xafbd5b0b, 262144, 262144},
		{"sengokh", "017-c4.bin", 1048576, 0xf4f3c9cb, 0, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.53c", 524288, 0x66be6d46, 262144, 262144},
		{"sengokh", "017-c1.bin", 1048576, 0xb4eb82a1, 524288, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.63c", 524288, 0x25f5fd7b, 262144, 262144},
		{"sengokh", "017-c2.bin", 1048576, 0xd55c550d, 524288, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001b.53c", 524288, 0xecb41adc, 262144, 262144},
		{"sengokh", "017-c3.bin", 1048576, 0xed51ef65, 524288, 262144},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001b.63c", 524288, 0x78b25278, 262144, 262144},
		{"sengokh", "017-c4.bin", 1048576, 0xf4f3c9cb, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.03c", 524288, 0xd0d55b2a, 0, 65536},
		{"sengokh", "017-p2.bin", 131072, 0x3024bbb3, 0, 65536},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.03c", 524288, 0xd0d55b2a, 65536, 65536},
		{"sengokh", "017-p2.bin", 131072, 0x3024bbb3, 0, 65536},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.03c", 524288, 0xd0d55b2a, 131072, 65536},
		{"sengokh", "017-p2.bin", 131072, 0x3024bbb3, 0, 65536},
	},
	{
		EVEN_COPY,
		{"sengoku", "n058001a.03c", 524288, 0xd0d55b2a, 196608, 65536},
		{"sengokh", "017-p2.bin", 131072, 0x3024bbb3, 0, 65536},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.03c", 524288, 0xd0d55b2a, 262144, 65536},
		{"sengokh", "017-p2.bin", 131072, 0x3024bbb3, 0, 65536},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.03c", 524288, 0xd0d55b2a, 327680, 65536},
		{"sengokh", "017-p2.bin", 131072, 0x3024bbb3, 0, 65536},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.03c", 524288, 0xd0d55b2a, 393216, 65536},
		{"sengokh", "017-p2.bin", 131072, 0x3024bbb3, 0, 65536},
	},
	{
		ODD_COPY,
		{"sengoku", "n058001a.03c", 524288, 0xd0d55b2a, 458752, 65536},
		{"sengokh", "017-p2.bin", 131072, 0x3024bbb3, 0, 65536},
	},
	{
		FULL_COPY,
		{"superspy", "n138001a.178", 524288, 0xb993bc83, 0, 524288},
		{"superspy", "011-v11.bin", 1048576, 0x5c674d5c, 0, 524288},
	},
	/* Not possible from MAME v0.122 onwards
	{
		FULL_COPY,
		{"superspy", "n138001a.278", 524288, 0x426cd040, 0, 524288},
		{"superspy", "011-v21.bin", 1048576, 0x1ebe94c7, 0, 524288},
	},
	{
		FULL_COPY,
		{"superspy", "n138001a.27c", 524288, 0x426cd040, 0, 524288},
		{"superspy", "011-v21.bin", 1048576, 0x1ebe94c7, 0, 524288},
	},
	{
		FULL_COPY,
		{"superspy", "n138001a.478", 65536, 0x64455806, 0, 65536},
		{"superspy", "011-m1.bin", 131072, 0xd59d5d12, 0, 65536},
	},
	{
		FULL_COPY,
		{"superspy", "n138001b.178", 524288, 0x9f513d5a, 0, 524288},
		{"superspy", "011-v12.bin", 1048576, 0x7df8898b, 0, 524288},
	},
	{
		FULL_COPY,
		{"superspy", "n138001b.17c", 524288, 0x9f513d5a, 0, 524288},
		{"superspy", "011-v12.bin", 1048576, 0x7df8898b, 0, 524288},
	},
	{
		FULL_COPY,
		{"superspy", "n138001d.178", 524288, 0x9f513d5a, 0, 524288},
		{"superspy", "011-v12.bin", 1048576, 0x7df8898b, 0, 524288},
	},
	{
		FULL_COPY,
		{"superspy", "n138001d.17c", 524288, 0x9f513d5a, 0, 524288},
		{"superspy", "011-v12.bin", 1048576, 0x7df8898b, 0, 524288},
	},
	*/
	{
		FULL_COPY,
		{"superspy", "n138001c.178", 524288, 0xb993bc83, 0, 524288},
		{"superspy", "011-v11.bin", 1048576, 0x5c674d5c, 0, 524288},
	},
	{
		FULL_COPY,
		{"superspy", "n138001a.17c", 524288, 0xd7a059b1, 0, 524288},
		{"superspy", "011-v11.bin", 1048576, 0x5c674d5c, 524288, 524288},
	},
	{
		FULL_COPY,
		{"superspy", "n138001c.17c", 524288, 0xd7a059b1, 0, 524288},
		{"superspy", "011-v11.bin", 1048576, 0x5c674d5c, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.038", 524288, 0x2e949e32, 0, 262144},
		{"superspy", "011-p1.bin", 524288, 0xc7f944b5, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.538", 524288, 0x239f22c4, 0, 262144},
		{"superspy", "011-c1.bin", 1048576, 0xcae7be57, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.638", 524288, 0x5f2e5184, 0, 262144},
		{"superspy", "011-c2.bin", 1048576, 0x9e29d986, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001b.538", 524288, 0x1edcf268, 0, 262144},
		{"superspy", "011-c3.bin", 1048576, 0x14832ff2, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001b.638", 524288, 0xb2afe822, 0, 262144},
		{"superspy", "011-c4.bin", 1048576, 0xb7f63162, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001c.538", 524288, 0x239f22c4, 0, 262144},
		{"superspy", "011-c1.bin", 1048576, 0xcae7be57, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001c.638", 524288, 0x5f2e5184, 0, 262144},
		{"superspy", "011-c2.bin", 1048576, 0x9e29d986, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001d.538", 524288, 0x1edcf268, 0, 262144},
		{"superspy", "011-c3.bin", 1048576, 0x14832ff2, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001d.638", 524288, 0xb2afe822, 0, 262144},
		{"superspy", "011-c4.bin", 1048576, 0xb7f63162, 0, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.53c", 524288, 0xce80c326, 0, 262144},
		{"superspy", "011-c1.bin", 1048576, 0xcae7be57, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.63c", 524288, 0x79b3e0b1, 0, 262144},
		{"superspy", "011-c2.bin", 1048576, 0x9e29d986, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001b.53c", 524288, 0xa41602a0, 0, 262144},
		{"superspy", "011-c3.bin", 1048576, 0x14832ff2, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001b.63c", 524288, 0xd425f967, 0, 262144},
		{"superspy", "011-c4.bin", 1048576, 0xb7f63162, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001c.53c", 524288, 0xce80c326, 0, 262144},
		{"superspy", "011-c1.bin", 1048576, 0xcae7be57, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001c.63c", 524288, 0x79b3e0b1, 0, 262144},
		{"superspy", "011-c2.bin", 1048576, 0x9e29d986, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001d.53c", 524288, 0xa41602a0, 0, 262144},
		{"superspy", "011-c3.bin", 1048576, 0x14832ff2, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001d.63c", 524288, 0xd425f967, 0, 262144},
		{"superspy", "011-c4.bin", 1048576, 0xb7f63162, 524288, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.038", 524288, 0x2e949e32, 262144, 262144},
		{"superspy", "011-p1.bin", 524288, 0xc7f944b5, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.538", 524288, 0x239f22c4, 262144, 262144},
		{"superspy", "011-c1.bin", 1048576, 0xcae7be57, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.638", 524288, 0x5f2e5184, 262144, 262144},
		{"superspy", "011-c2.bin", 1048576, 0x9e29d986, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001b.538", 524288, 0x1edcf268, 262144, 262144},
		{"superspy", "011-c3.bin", 1048576, 0x14832ff2, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001b.638", 524288, 0xb2afe822, 262144, 262144},
		{"superspy", "011-c4.bin", 1048576, 0xb7f63162, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001c.538", 524288, 0x239f22c4, 262144, 262144},
		{"superspy", "011-c1.bin", 1048576, 0xcae7be57, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001c.638", 524288, 0x5f2e5184, 262144, 262144},
		{"superspy", "011-c2.bin", 1048576, 0x9e29d986, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001d.538", 524288, 0x1edcf268, 262144, 262144},
		{"superspy", "011-c3.bin", 1048576, 0x14832ff2, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001d.638", 524288, 0xb2afe822, 262144, 262144},
		{"superspy", "011-c4.bin", 1048576, 0xb7f63162, 0, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.53c", 524288, 0xce80c326, 262144, 262144},
		{"superspy", "011-c1.bin", 1048576, 0xcae7be57, 524288, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.63c", 524288, 0x79b3e0b1, 262144, 262144},
		{"superspy", "011-c2.bin", 1048576, 0x9e29d986, 524288, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001b.53c", 524288, 0xa41602a0, 262144, 262144},
		{"superspy", "011-c3.bin", 1048576, 0x14832ff2, 524288, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001b.63c", 524288, 0xd425f967, 262144, 262144},
		{"superspy", "011-c4.bin", 1048576, 0xb7f63162, 524288, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001c.53c", 524288, 0xce80c326, 262144, 262144},
		{"superspy", "011-c1.bin", 1048576, 0xcae7be57, 524288, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001c.63c", 524288, 0x79b3e0b1, 262144, 262144},
		{"superspy", "011-c2.bin", 1048576, 0x9e29d986, 524288, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001d.53c", 524288, 0xa41602a0, 262144, 262144},
		{"superspy", "011-c3.bin", 1048576, 0x14832ff2, 524288, 262144},
	},
	{
		ODD_COPY,
		{"superspy", "n138001d.63c", 524288, 0xd425f967, 262144, 262144},
		{"superspy", "011-c4.bin", 1048576, 0xb7f63162, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.03c", 524288, 0x54443d72, 0, 65536},
		{"superspy", "011-sp2.bin", 131072, 0x811a4faf, 0, 65536},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.03c", 524288, 0x54443d72, 65536, 65536},
		{"superspy", "011-sp2.bin", 131072, 0x811a4faf, 0, 65536},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.03c", 524288, 0x54443d72, 131072, 65536},
		{"superspy", "011-sp2.bin", 131072, 0x811a4faf, 0, 65536},
	},
	{
		EVEN_COPY,
		{"superspy", "n138001a.03c", 524288, 0x54443d72, 196608, 65536},
		{"superspy", "011-sp2.bin", 131072, 0x811a4faf, 0, 65536},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.03c", 524288, 0x54443d72, 262144, 65536},
		{"superspy", "011-sp2.bin", 131072, 0x811a4faf, 0, 65536},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.03c", 524288, 0x54443d72, 327680, 65536},
		{"superspy", "011-sp2.bin", 131072, 0x811a4faf, 0, 65536},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.03c", 524288, 0x54443d72, 393216, 65536},
		{"superspy", "011-sp2.bin", 131072, 0x811a4faf, 0, 65536},
	},
	{
		ODD_COPY,
		{"superspy", "n138001a.03c", 524288, 0x54443d72, 458752, 65536},
		{"superspy", "011-sp2.bin", 131072, 0x811a4faf, 0, 65536},
	},
	{
		FULL_COPY,
		{"trally", "n046001a.1f8", 524288, 0x1c93fb89, 0, 524288},
		{"trally", "038-v1.bin", 1048576, 0x5ccd9fd5, 0, 524288},
	},
	{
		FULL_COPY,
		{"trally", "n046001a.4f8", 65536, 0x308c4a8d, 0, 65536},
		{"trally", "038-m1.bin", 131072, 0x0908707e, 0, 65536},
	},
	{
		FULL_COPY,
		{"trally", "n046001a.1fc", 524288, 0x39f18253, 0, 524288},
		{"trally", "038-v1.bin", 1048576, 0x5ccd9fd5, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"trally", "n046001a.038", 524288, 0x400bed38, 0, 262144},
		{"trally", "038-p1.bin", 524288, 0x1e52a576, 0, 262144},
	},
	{
		EVEN_COPY,
		{"trally", "n046001a.03c", 524288, 0x77196e9a, 0, 262144},
		{"trally", "038-p2.bin", 524288, 0xa5193e2f, 0, 262144},
	},
	{
		EVEN_COPY,
		{"trally", "n046001b.538", 524288, 0x2f213750, 0, 262144},
		{"trally", "038-c3.bin", 524288, 0x3bb7b9d6, 0, 262144},
	},
	{
		EVEN_COPY,
		{"trally", "n046001b.638", 524288, 0x268be38b, 0, 262144},
		{"trally", "038-c4.bin", 524288, 0xa4513ecf, 0, 262144},
	},
	{
		EVEN_COPY,
		{"trally", "n046001a.538", 524288, 0x4d002ecb, 0, 262144},
		{"trally", "038-c1.bin", 1048576, 0xc58323d4, 0, 262144},
	},
	{
		EVEN_COPY,
		{"trally", "n046001a.638", 524288, 0x6b2f79de, 0, 262144},
		{"trally", "038-c2.bin", 1048576, 0xbba9c29e, 0, 262144},
	},
	{
		EVEN_COPY,
		{"trally", "n046001a.53c", 524288, 0xb0be56db, 0, 262144},
		{"trally", "038-c1.bin", 1048576, 0xc58323d4, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"trally", "n046001a.63c", 524288, 0x091f38b4, 0, 262144},
		{"trally", "038-c2.bin", 1048576, 0xbba9c29e, 524288, 262144},
	},
	{
		ODD_COPY,
		{"trally", "n046001a.038", 524288, 0x400bed38, 262144, 262144},
		{"trally", "038-p1.bin", 524288, 0x1e52a576, 0, 262144},
	},
	{
		ODD_COPY,
		{"trally", "n046001a.03c", 524288, 0x77196e9a, 262144, 262144},
		{"trally", "038-p2.bin", 524288, 0xa5193e2f, 0, 262144},
	},
	{
		ODD_COPY,
		{"trally", "n046001b.538", 524288, 0x2f213750, 262144, 262144},
		{"trally", "038-c3.bin", 524288, 0x3bb7b9d6, 0, 262144},
	},
	{
		ODD_COPY,
		{"trally", "n046001b.638", 524288, 0x268be38b, 262144, 262144},
		{"trally", "038-c4.bin", 524288, 0xa4513ecf, 0, 262144},
	},
	{
		ODD_COPY,
		{"trally", "n046001a.538", 524288, 0x4d002ecb, 262144, 262144},
		{"trally", "038-c1.bin", 1048576, 0xc58323d4, 0, 262144},
	},
	{
		ODD_COPY,
		{"trally", "n046001a.638", 524288, 0x6b2f79de, 262144, 262144},
		{"trally", "038-c2.bin", 1048576, 0xbba9c29e, 0, 262144},
	},
	{
		ODD_COPY,
		{"trally", "n046001a.53c", 524288, 0xb0be56db, 262144, 262144},
		{"trally", "038-c1.bin", 1048576, 0xc58323d4, 524288, 262144},
	},
	{
		ODD_COPY,
		{"trally", "n046001a.63c", 524288, 0x091f38b4, 262144, 262144},
		{"trally", "038-c2.bin", 1048576, 0xbba9c29e, 524288, 262144},
	},
	{
		FULL_COPY,
		{"aof", "n102001a.1f8", 524288, 0xa4d8747f, 0, 524288},
		{"aof", "044-v2.bin", 2097152, 0x3ec632ea, 0, 524288},
	},
	{
		FULL_COPY,
		{"aof", "n102001c.1f8", 524288, 0xd0c8bcd2, 0, 524288},
		{"aof", "044-v4.bin", 2097152, 0x4b0f8e23, 0, 524288},
	},
	{
		FULL_COPY,
		{"aof", "n102001a.1fc", 524288, 0x55219d13, 0, 524288},
		{"aof", "044-v2.bin", 2097152, 0x3ec632ea, 524288, 524288},
	},
	{
		FULL_COPY,
		{"aof", "n102001c.1fc", 524288, 0x167db9b2, 0, 524288},
		{"aof", "044-v4.bin", 2097152, 0x4b0f8e23, 524288, 524288},
	},
	{
		FULL_COPY,
		{"aof", "n102001b.1f8", 524288, 0x6eae81fa, 0, 524288},
		{"aof", "044-v2.bin", 2097152, 0x3ec632ea, 1048576, 524288},
	},
	{
		FULL_COPY,
		{"aof", "n102001d.1f8", 524288, 0xf03969fe, 0, 524288},
		{"aof", "044-v4.bin", 2097152, 0x4b0f8e23, 1048576, 524288},
	},
	{
		FULL_COPY,
		{"aof", "n102001b.1fc", 524288, 0xf91676e9, 0, 524288},
		{"aof", "044-v2.bin", 2097152, 0x3ec632ea, 1572864, 524288},
	},
	{
		FULL_COPY,
		{"aof", "n102001d.1fc", 524288, 0xa823a19a, 0, 524288},
		{"aof", "044-v4.bin", 2097152, 0x4b0f8e23, 1572864, 524288},
	},
	{
		EVEN_COPY,
		{"aof", "n102001a.038", 524288, 0x95102254, 0, 262144},
		{"aof", "044-p1.bin", 524288, 0xca9f7a6d, 0, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001a.538", 524288, 0xa2e4a168, 0, 262144},
		{"aof", "044-c1.bin", 2097152, 0xddab98a7, 0, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001a.638", 524288, 0xca12c80f, 0, 262144},
		{"aof", "044-c2.bin", 2097152, 0xd8ccd575, 0, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001b.538", 524288, 0x2a0c385b, 0, 262144},
		{"aof", "044-c3.bin", 2097152, 0x403e898a, 0, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001b.638", 524288, 0x8b73b3da, 0, 262144},
		{"aof", "044-c4.bin", 2097152, 0x6235fbaa, 0, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001a.53c", 524288, 0xda389ef7, 0, 262144},
		{"aof", "044-c1.bin", 2097152, 0xddab98a7, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001a.63c", 524288, 0xd59746b0, 0, 262144},
		{"aof", "044-c2.bin", 2097152, 0xd8ccd575, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001b.53c", 524288, 0x4a4317bf, 0, 262144},
		{"aof", "044-c3.bin", 2097152, 0x403e898a, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001b.63c", 524288, 0x9fc3f8ea, 0, 262144},
		{"aof", "044-c4.bin", 2097152, 0x6235fbaa, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001c.538", 524288, 0x471d9e57, 0, 262144},
		{"aof", "044-c1.bin", 2097152, 0xddab98a7, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001c.638", 524288, 0xcbf8a72e, 0, 262144},
		{"aof", "044-c2.bin", 2097152, 0xd8ccd575, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001d.538", 524288, 0x204e7b29, 0, 262144},
		{"aof", "044-c3.bin", 2097152, 0x403e898a, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001d.638", 524288, 0x47763b6d, 0, 262144},
		{"aof", "044-c4.bin", 2097152, 0x6235fbaa, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001c.53c", 524288, 0x23fe5675, 0, 262144},
		{"aof", "044-c1.bin", 2097152, 0xddab98a7, 1572864, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001c.63c", 524288, 0x5ec93c96, 0, 262144},
		{"aof", "044-c2.bin", 2097152, 0xd8ccd575, 1572864, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001d.53c", 524288, 0x7f6d5144, 0, 262144},
		{"aof", "044-c3.bin", 2097152, 0x403e898a, 1572864, 262144},
	},
	{
		EVEN_COPY,
		{"aof", "n102001d.63c", 524288, 0x4408f4eb, 0, 262144},
		{"aof", "044-c4.bin", 2097152, 0x6235fbaa, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001a.038", 524288, 0x95102254, 262144, 262144},
		{"aof", "044-p1.bin", 524288, 0xca9f7a6d, 0, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001a.538", 524288, 0xa2e4a168, 262144, 262144},
		{"aof", "044-c1.bin", 2097152, 0xddab98a7, 0, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001a.638", 524288, 0xca12c80f, 262144, 262144},
		{"aof", "044-c2.bin", 2097152, 0xd8ccd575, 0, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001b.538", 524288, 0x2a0c385b, 262144, 262144},
		{"aof", "044-c3.bin", 2097152, 0x403e898a, 0, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001b.638", 524288, 0x8b73b3da, 262144, 262144},
		{"aof", "044-c4.bin", 2097152, 0x6235fbaa, 0, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001a.53c", 524288, 0xda389ef7, 262144, 262144},
		{"aof", "044-c1.bin", 2097152, 0xddab98a7, 524288, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001a.63c", 524288, 0xd59746b0, 262144, 262144},
		{"aof", "044-c2.bin", 2097152, 0xd8ccd575, 524288, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001b.53c", 524288, 0x4a4317bf, 262144, 262144},
		{"aof", "044-c3.bin", 2097152, 0x403e898a, 524288, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001b.63c", 524288, 0x9fc3f8ea, 262144, 262144},
		{"aof", "044-c4.bin", 2097152, 0x6235fbaa, 524288, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001c.538", 524288, 0x471d9e57, 262144, 262144},
		{"aof", "044-c1.bin", 2097152, 0xddab98a7, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001c.638", 524288, 0xcbf8a72e, 262144, 262144},
		{"aof", "044-c2.bin", 2097152, 0xd8ccd575, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001d.538", 524288, 0x204e7b29, 262144, 262144},
		{"aof", "044-c3.bin", 2097152, 0x403e898a, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001d.638", 524288, 0x47763b6d, 262144, 262144},
		{"aof", "044-c4.bin", 2097152, 0x6235fbaa, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001c.53c", 524288, 0x23fe5675, 262144, 262144},
		{"aof", "044-c1.bin", 2097152, 0xddab98a7, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001c.63c", 524288, 0x5ec93c96, 262144, 262144},
		{"aof", "044-c2.bin", 2097152, 0xd8ccd575, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001d.53c", 524288, 0x7f6d5144, 262144, 262144},
		{"aof", "044-c3.bin", 2097152, 0x403e898a, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"aof", "n102001d.63c", 524288, 0x4408f4eb, 262144, 262144},
		{"aof", "044-c4.bin", 2097152, 0x6235fbaa, 1572864, 262144},
	},
	{
		FULL_COPY,
		{"fatfury1", "n058001a.1f8", 524288, 0x86fabf00, 0, 524288},
		{"fatfury1", "033-v1.bin", 1048576, 0x212fd20d, 0, 524288},
	},
	{
		FULL_COPY,
		{"fatfury1", "n058001b.1f8", 524288, 0xfc3bd6f7, 0, 524288},
		{"fatfury1", "033-v2.bin", 1048576, 0xfa2ae47f, 0, 524288},
	},
	{
		FULL_COPY,
		{"fatfury1", "n058001a.1fc", 524288, 0xead1467b, 0, 524288},
		{"fatfury1", "033-v1.bin", 1048576, 0x212fd20d, 524288, 524288},
	},
	{
		FULL_COPY,
		{"fatfury1", "n058001b.1fc", 524288, 0xd312f6c0, 0, 524288},
		{"fatfury1", "033-v2.bin", 1048576, 0xfa2ae47f, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.038", 524288, 0x47e51379, 0, 262144},
		{"fatfury1", "033-p1.bin", 524288, 0x47ebdc2f, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.538", 524288, 0x9aaa6d73, 0, 262144},
		{"fatfury1", "033-c1.bin", 1048576, 0x74317e54, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.638", 524288, 0x9cae3703, 0, 262144},
		{"fatfury1", "033-c2.bin", 1048576, 0x5bb952f3, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001b.538", 524288, 0x7aefe57d, 0, 262144},
		{"fatfury1", "033-c3.bin", 1048576, 0x9b714a7c, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001b.638", 524288, 0xb39a0cde, 0, 262144},
		{"fatfury1", "033-c4.bin", 1048576, 0x9397476a, 0, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.53c", 524288, 0xa986f4a9, 0, 262144},
		{"fatfury1", "033-c1.bin", 1048576, 0x74317e54, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.63c", 524288, 0x308b619f, 0, 262144},
		{"fatfury1", "033-c2.bin", 1048576, 0x5bb952f3, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001b.53c", 524288, 0xe3057c96, 0, 262144},
		{"fatfury1", "033-c3.bin", 1048576, 0x9b714a7c, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001b.63c", 524288, 0x737bc030, 0, 262144},
		{"fatfury1", "033-c4.bin", 1048576, 0x9397476a, 524288, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.038", 524288, 0x47e51379, 262144, 262144},
		{"fatfury1", "033-p1.bin", 524288, 0x47ebdc2f, 0, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.538", 524288, 0x9aaa6d73, 262144, 262144},
		{"fatfury1", "033-c1.bin", 1048576, 0x74317e54, 0, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.638", 524288, 0x9cae3703, 262144, 262144},
		{"fatfury1", "033-c2.bin", 1048576, 0x5bb952f3, 0, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001b.538", 524288, 0x7aefe57d, 262144, 262144},
		{"fatfury1", "033-c3.bin", 1048576, 0x9b714a7c, 0, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001b.638", 524288, 0xb39a0cde, 262144, 262144},
		{"fatfury1", "033-c4.bin", 1048576, 0x9397476a, 0, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.53c", 524288, 0xa986f4a9, 262144, 262144},
		{"fatfury1", "033-c1.bin", 1048576, 0x74317e54, 524288, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.63c", 524288, 0x308b619f, 262144, 262144},
		{"fatfury1", "033-c2.bin", 1048576, 0x5bb952f3, 524288, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001b.53c", 524288, 0xe3057c96, 262144, 262144},
		{"fatfury1", "033-c3.bin", 1048576, 0x9b714a7c, 524288, 262144},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001b.63c", 524288, 0x737bc030, 262144, 262144},
		{"fatfury1", "033-c4.bin", 1048576, 0x9397476a, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.03c", 524288, 0x19d36805, 0, 65536},
		{"fatfury1", "033-p2.bin", 131072, 0xc473af1c, 0, 65536},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.03c", 524288, 0x19d36805, 65536, 65536},
		{"fatfury1", "033-p2.bin", 131072, 0xc473af1c, 0, 65536},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.03c", 524288, 0x19d36805, 131072, 65536},
		{"fatfury1", "033-p2.bin", 131072, 0xc473af1c, 0, 65536},
	},
	{
		EVEN_COPY,
		{"fatfury1", "n058001a.03c", 524288, 0x19d36805, 196608, 65536},
		{"fatfury1", "033-p2.bin", 131072, 0xc473af1c, 0, 65536},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.03c", 524288, 0x19d36805, 262144, 65536},
		{"fatfury1", "033-p2.bin", 131072, 0xc473af1c, 0, 65536},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.03c", 524288, 0x19d36805, 327680, 65536},
		{"fatfury1", "033-p2.bin", 131072, 0xc473af1c, 0, 65536},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.03c", 524288, 0x19d36805, 393216, 65536},
		{"fatfury1", "033-p2.bin", 131072, 0xc473af1c, 0, 65536},
	},
	{
		ODD_COPY,
		{"fatfury1", "n058001a.03c", 524288, 0x19d36805, 458752, 65536},
		{"fatfury1", "033-p2.bin", 131072, 0xc473af1c, 0, 65536},
	},
	{
		FULL_COPY,
		{"fatfury3", "fury3_c3.rom", 4194304, 0xf6738c87, 0, 2097152},
		{"fatfury3", "069-c3.bin", 4194304, 0x1c0fde2f, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"fatfury3", "fury3_c2.rom", 4194304, 0xbfaf3258, 0, 2097152},
		{"fatfury3", "069-c2.bin", 4194304, 0x1053a455, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"fatfury3", "fury3_c1.rom", 4194304, 0xc73e86e4, 0, 2097152},
		{"fatfury3", "069-c1.bin", 4194304, 0xe302f93c, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"fatfury3", "fury3_c4.rom", 4194304, 0x9c31e334, 0, 2097152},
		{"fatfury3", "069-c4.bin", 4194304, 0xa25fc3d0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"fatfury3", "fury3_c3.rom", 4194304, 0xf6738c87, 2097152, 2097152},
		{"fatfury3", "069-c3.bin", 4194304, 0x1c0fde2f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"fatfury3", "fury3_c2.rom", 4194304, 0xbfaf3258, 2097152, 2097152},
		{"fatfury3", "069-c2.bin", 4194304, 0x1053a455, 0, 2097152},
	},
	{
		FULL_COPY,
		{"fatfury3", "fury3_c1.rom", 4194304, 0xc73e86e4, 2097152, 2097152},
		{"fatfury3", "069-c1.bin", 4194304, 0xe302f93c, 0, 2097152},
	},
	{
		FULL_COPY,
		{"fatfury3", "fury3_c4.rom", 4194304, 0x9c31e334, 2097152, 2097152},
		{"fatfury3", "069-c4.bin", 4194304, 0xa25fc3d0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kotm", "n058001a.1f8", 524288, 0xc3df83ba, 0, 524288},
		{"kotm", "016-v1.bin", 1048576, 0x86c0a502, 0, 524288},
	},
	{
		FULL_COPY,
		{"kotm", "n058001b.1f8", 524288, 0xdf9a4854, 0, 524288},
		{"kotm", "016-v2.bin", 1048576, 0x5bc23ec5, 0, 524288},
	},
	{
		FULL_COPY,
		{"kotm", "n058001a.1fc", 524288, 0x22aa6096, 0, 524288},
		{"kotm", "016-v1.bin", 1048576, 0x86c0a502, 524288, 524288},
	},
	{
		FULL_COPY,
		{"kotm", "n058001b.1fc", 524288, 0x71f53a38, 0, 524288},
		{"kotm", "016-v2.bin", 1048576, 0x5bc23ec5, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.038", 524288, 0xd239c184, 0, 262144},
		{"kotm", "016-p1.bin", 524288, 0x1b818731, 0, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.538", 524288, 0x493db90e, 0, 262144},
		{"kotm", "016-c1.bin", 1048576, 0x71471c25, 0, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.638", 524288, 0x8bc1c3a0, 0, 262144},
		{"kotm", "016-c2.bin", 1048576, 0x320db048, 0, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001b.538", 524288, 0xcabb7b58, 0, 262144},
		{"kotm", "016-c3.bin", 1048576, 0x98de7995, 0, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001b.638", 524288, 0xfde45b59, 0, 262144},
		{"kotm", "016-c4.bin", 1048576, 0x070506e2, 0, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.53c", 524288, 0x0d211945, 0, 262144},
		{"kotm", "016-c1.bin", 1048576, 0x71471c25, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.63c", 524288, 0xcc793bbf, 0, 262144},
		{"kotm", "016-c2.bin", 1048576, 0x320db048, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001b.53c", 524288, 0xc7c20718, 0, 262144},
		{"kotm", "016-c3.bin", 1048576, 0x98de7995, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001b.63c", 524288, 0xb89b4201, 0, 262144},
		{"kotm", "016-c4.bin", 1048576, 0x070506e2, 524288, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.038", 524288, 0xd239c184, 262144, 262144},
		{"kotm", "016-p1.bin", 524288, 0x1b818731, 0, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.538", 524288, 0x493db90e, 262144, 262144},
		{"kotm", "016-c1.bin", 1048576, 0x71471c25, 0, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.638", 524288, 0x8bc1c3a0, 262144, 262144},
		{"kotm", "016-c2.bin", 1048576, 0x320db048, 0, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001b.538", 524288, 0xcabb7b58, 262144, 262144},
		{"kotm", "016-c3.bin", 1048576, 0x98de7995, 0, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001b.638", 524288, 0xfde45b59, 262144, 262144},
		{"kotm", "016-c4.bin", 1048576, 0x070506e2, 0, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.53c", 524288, 0x0d211945, 262144, 262144},
		{"kotm", "016-c1.bin", 1048576, 0x71471c25, 524288, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.63c", 524288, 0xcc793bbf, 262144, 262144},
		{"kotm", "016-c2.bin", 1048576, 0x320db048, 524288, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001b.53c", 524288, 0xc7c20718, 262144, 262144},
		{"kotm", "016-c3.bin", 1048576, 0x98de7995, 524288, 262144},
	},
	{
		ODD_COPY,
		{"kotm", "n058001b.63c", 524288, 0xb89b4201, 262144, 262144},
		{"kotm", "016-c4.bin", 1048576, 0x070506e2, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.03c", 524288, 0x7291a388, 0, 65536},
		{"kotm", "016-p2.bin", 131072, 0x12afdc2b, 0, 65536},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.03c", 524288, 0x7291a388, 65536, 65536},
		{"kotm", "016-p2.bin", 131072, 0x12afdc2b, 0, 65536},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.03c", 524288, 0x7291a388, 131072, 65536},
		{"kotm", "016-p2.bin", 131072, 0x12afdc2b, 0, 65536},
	},
	{
		EVEN_COPY,
		{"kotm", "n058001a.03c", 524288, 0x7291a388, 196608, 65536},
		{"kotm", "016-p2.bin", 131072, 0x12afdc2b, 0, 65536},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.03c", 524288, 0x7291a388, 262144, 65536},
		{"kotm", "016-p2.bin", 131072, 0x12afdc2b, 0, 65536},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.03c", 524288, 0x7291a388, 327680, 65536},
		{"kotm", "016-p2.bin", 131072, 0x12afdc2b, 0, 65536},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.03c", 524288, 0x7291a388, 393216, 65536},
		{"kotm", "016-p2.bin", 131072, 0x12afdc2b, 0, 65536},
	},
	{
		ODD_COPY,
		{"kotm", "n058001a.03c", 524288, 0x7291a388, 458752, 65536},
		{"kotm", "016-p2.bin", 131072, 0x12afdc2b, 0, 65536},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c1.rom", 4194304, 0xc73e86e4, 0, 2097152},
		{"rbff1", "069-c1.bin", 4194304, 0xe302f93c, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c2.rom", 4194304, 0xbfaf3258, 0, 2097152},
		{"rbff1", "069-c2.bin", 4194304, 0x1053a455, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c3.rom", 4194304, 0xf6738c87, 0, 2097152},
		{"rbff1", "069-c3.bin", 4194304, 0x1c0fde2f, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c4.rom", 4194304, 0x9c31e334, 0, 2097152},
		{"rbff1", "069-c4.bin", 4194304, 0xa25fc3d0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c5.rom", 4194304, 0x248ff860, 0, 2097152},
		{"rbff1", "095-c5.bin", 4194304, 0x8b9b65df, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c6.rom", 4194304, 0x0bfb2d1f, 0, 2097152},
		{"rbff1", "095-c6.bin", 4194304, 0x3e164718, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c1.rom", 4194304, 0xc73e86e4, 2097152, 2097152},
		{"rbff1", "069-c1.bin", 4194304, 0xe302f93c, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c2.rom", 4194304, 0xbfaf3258, 2097152, 2097152},
		{"rbff1", "069-c2.bin", 4194304, 0x1053a455, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c3.rom", 4194304, 0xf6738c87, 2097152, 2097152},
		{"rbff1", "069-c3.bin", 4194304, 0x1c0fde2f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c4.rom", 4194304, 0x9c31e334, 2097152, 2097152},
		{"rbff1", "069-c4.bin", 4194304, 0xa25fc3d0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c5.rom", 4194304, 0x248ff860, 2097152, 2097152},
		{"rbff1", "095-c5.bin", 4194304, 0x8b9b65df, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbff1", "rbff1_c6.rom", 4194304, 0x0bfb2d1f, 2097152, 2097152},
		{"rbff1", "095-c6.bin", 4194304, 0x3e164718, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wh1", "n138001c.1f8", 524288, 0xb4ff60d7, 0, 524288},
		{"wh1h", "053-v4.bin", 1048576, 0x7bea8f66, 0, 524288},
	},
	{
		FULL_COPY,
		{"wh1", "n138001c.1fc", 524288, 0xb358e4f5, 0, 524288},
		{"wh1h", "053-v4.bin", 1048576, 0x7bea8f66, 524288, 524288},
	},
	{
		FULL_COPY,
		{"wh1", "n138001a.1f8", 524288, 0x77994663, 0, 524288},
		{"wh1h", "053-v2.bin", 2097152, 0xa68df485, 0, 524288},
	},
	{
		FULL_COPY,
		{"wh1", "n138001a.1fc", 524288, 0xd74ad0da, 0, 524288},
		{"wh1h", "053-v2.bin", 2097152, 0xa68df485, 524288, 524288},
	},
	{
		FULL_COPY,
		{"wh1", "n138001b.1f8", 524288, 0x9d5fe808, 0, 524288},
		{"wh1h", "053-v2.bin", 2097152, 0xa68df485, 1048576, 524288},
	},
	{
		FULL_COPY,
		{"wh1", "n138001b.1fc", 524288, 0x883fb383, 0, 524288},
		{"wh1h", "053-v2.bin", 2097152, 0xa68df485, 1572864, 524288},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001a.038", 524288, 0xab39923d, 0, 262144},
		{"wh1h", "053-p1.bin", 524288, 0x95b574cb, 0, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001a.03c", 524288, 0x5adc98ef, 0, 262144},
		{"wh1h", "053-p2.bin", 524288, 0xf198ed45, 0, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001b.538", 524288, 0xbb807a43, 0, 262144},
		{"wh1h", "053-c3.bin", 1048576, 0x0dd64965, 0, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001b.638", 524288, 0xc9f439f8, 0, 262144},
		{"wh1h", "053-c4.bin", 1048576, 0x9270d954, 0, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001d.538", 524288, 0xbb807a43, 0, 262144},
		{"wh1h", "053-c3.bin", 1048576, 0x0dd64965, 0, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001d.638", 524288, 0xc9f439f8, 0, 262144},
		{"wh1h", "053-c4.bin", 1048576, 0x9270d954, 0, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001b.53c", 524288, 0xe913f93c, 0, 262144},
		{"wh1h", "053-c3.bin", 1048576, 0x0dd64965, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001b.63c", 524288, 0x80441c48, 0, 262144},
		{"wh1h", "053-c4.bin", 1048576, 0x9270d954, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001d.53c", 524288, 0xe913f93c, 0, 262144},
		{"wh1h", "053-c3.bin", 1048576, 0x0dd64965, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001d.63c", 524288, 0x80441c48, 0, 262144},
		{"wh1h", "053-c4.bin", 1048576, 0x9270d954, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001a.538", 524288, 0xad8fcc5d, 0, 262144},
		{"wh1h", "053-c1.bin", 2097152, 0x85eb5bce, 0, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001a.638", 524288, 0x3182b4db, 0, 262144},
		{"wh1h", "053-c2.bin", 2097152, 0xec93b048, 0, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001a.53c", 524288, 0x0dca726e, 0, 262144},
		{"wh1h", "053-c1.bin", 2097152, 0x85eb5bce, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001a.63c", 524288, 0x1cb0a840, 0, 262144},
		{"wh1h", "053-c2.bin", 2097152, 0xec93b048, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001c.538", 524288, 0x3c359a14, 0, 262144},
		{"wh1h", "053-c1.bin", 2097152, 0x85eb5bce, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001c.638", 524288, 0x7c4b85b4, 0, 262144},
		{"wh1h", "053-c2.bin", 2097152, 0xec93b048, 1048576, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001c.53c", 524288, 0xb1327d84, 0, 262144},
		{"wh1h", "053-c1.bin", 2097152, 0x85eb5bce, 1572864, 262144},
	},
	{
		EVEN_COPY,
		{"wh1", "n138001c.63c", 524288, 0x959f29db, 0, 262144},
		{"wh1h", "053-c2.bin", 2097152, 0xec93b048, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001a.038", 524288, 0xab39923d, 262144, 262144},
		{"wh1h", "053-p1.bin", 524288, 0x95b574cb, 0, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001a.03c", 524288, 0x5adc98ef, 262144, 262144},
		{"wh1h", "053-p2.bin", 524288, 0xf198ed45, 0, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001b.538", 524288, 0xbb807a43, 262144, 262144},
		{"wh1h", "053-c3.bin", 1048576, 0x0dd64965, 0, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001b.638", 524288, 0xc9f439f8, 262144, 262144},
		{"wh1h", "053-c4.bin", 1048576, 0x9270d954, 0, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001d.538", 524288, 0xbb807a43, 262144, 262144},
		{"wh1h", "053-c3.bin", 1048576, 0x0dd64965, 0, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001d.638", 524288, 0xc9f439f8, 262144, 262144},
		{"wh1h", "053-c4.bin", 1048576, 0x9270d954, 0, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001b.53c", 524288, 0xe913f93c, 262144, 262144},
		{"wh1h", "053-c3.bin", 1048576, 0x0dd64965, 524288, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001b.63c", 524288, 0x80441c48, 262144, 262144},
		{"wh1h", "053-c4.bin", 1048576, 0x9270d954, 524288, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001d.53c", 524288, 0xe913f93c, 262144, 262144},
		{"wh1h", "053-c3.bin", 1048576, 0x0dd64965, 524288, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001d.63c", 524288, 0x80441c48, 262144, 262144},
		{"wh1h", "053-c4.bin", 1048576, 0x9270d954, 524288, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001a.538", 524288, 0xad8fcc5d, 262144, 262144},
		{"wh1h", "053-c1.bin", 2097152, 0x85eb5bce, 0, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001a.638", 524288, 0x3182b4db, 262144, 262144},
		{"wh1h", "053-c2.bin", 2097152, 0xec93b048, 0, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001a.53c", 524288, 0x0dca726e, 262144, 262144},
		{"wh1h", "053-c1.bin", 2097152, 0x85eb5bce, 524288, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001a.63c", 524288, 0x1cb0a840, 262144, 262144},
		{"wh1h", "053-c2.bin", 2097152, 0xec93b048, 524288, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001c.538", 524288, 0x3c359a14, 262144, 262144},
		{"wh1h", "053-c1.bin", 2097152, 0x85eb5bce, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001c.638", 524288, 0x7c4b85b4, 262144, 262144},
		{"wh1h", "053-c2.bin", 2097152, 0xec93b048, 1048576, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001c.53c", 524288, 0xb1327d84, 262144, 262144},
		{"wh1h", "053-c1.bin", 2097152, 0x85eb5bce, 1572864, 262144},
	},
	{
		ODD_COPY,
		{"wh1", "n138001c.63c", 524288, 0x959f29db, 262144, 262144},
		{"wh1h", "053-c2.bin", 2097152, 0xec93b048, 1572864, 262144},
	},
	{
		FULL_COPY,
		{"bakatono", "n058001a.1f8", 524288, 0xd3edbde6, 0, 524288},
		{"bakatono", "036-v1.bin", 1048576, 0x1c335dce, 0, 524288},
	},
	{
		FULL_COPY,
		{"bakatono", "n058001b.1f8", 524288, 0xe28cf9b3, 0, 524288},
		{"bakatono", "036-v2.bin", 1048576, 0xbbf79342, 0, 524288},
	},
	{
		FULL_COPY,
		{"bakatono", "n058001a.4f8", 65536, 0xa5e05789, 0, 65536},
		{"bakatono", "036-m1.bin", 131072, 0xf1385b96, 0, 65536},
	},
	{
		FULL_COPY,
		{"bakatono", "n058001a.1fc", 524288, 0xcc487705, 0, 524288},
		{"bakatono", "036-v1.bin", 1048576, 0x1c335dce, 524288, 524288},
	},
	{
		FULL_COPY,
		{"bakatono", "n058001b.1fc", 524288, 0x96c3ece9, 0, 524288},
		{"bakatono", "036-v2.bin", 1048576, 0xbbf79342, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001a.038", 524288, 0x083ca651, 0, 262144},
		{"bakatono", "036-p1.bin", 524288, 0x1c66b6fa, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001b.538", 524288, 0xeb751be8, 0, 262144},
		{"bakatono", "036-c3.bin", 1048576, 0x9ac0708e, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001a.638", 524288, 0x647ba28f, 0, 262144},
		{"bakatono", "036-c2.bin", 1048576, 0xbbf003f5, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001a.538", 524288, 0xacb82025, 0, 262144},
		{"bakatono", "036-c1.bin", 1048576, 0xfe7f1010, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001b.638", 524288, 0x6135247a, 0, 262144},
		{"bakatono", "036-c4.bin", 1048576, 0xf2577d22, 0, 262144},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001a.63c", 524288, 0xdffefa4f, 0, 262144},
		{"bakatono", "036-c2.bin", 1048576, 0xbbf003f5, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001b.63c", 524288, 0x0d40c953, 0, 262144},
		{"bakatono", "036-c4.bin", 1048576, 0xf2577d22, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001b.53c", 524288, 0x1d39bad6, 0, 262144},
		{"bakatono", "036-c3.bin", 1048576, 0x9ac0708e, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"bakatono", "n058001a.53c", 524288, 0xc6954f8e, 0, 262144},
		{"bakatono", "036-c1.bin", 1048576, 0xfe7f1010, 524288, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001a.038", 524288, 0x083ca651, 262144, 262144},
		{"bakatono", "036-p1.bin", 524288, 0x1c66b6fa, 0, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001b.538", 524288, 0xeb751be8, 262144, 262144},
		{"bakatono", "036-c3.bin", 1048576, 0x9ac0708e, 0, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001a.638", 524288, 0x647ba28f, 262144, 262144},
		{"bakatono", "036-c2.bin", 1048576, 0xbbf003f5, 0, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001a.538", 524288, 0xacb82025, 262144, 262144},
		{"bakatono", "036-c1.bin", 1048576, 0xfe7f1010, 0, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001b.638", 524288, 0x6135247a, 262144, 262144},
		{"bakatono", "036-c4.bin", 1048576, 0xf2577d22, 0, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001a.63c", 524288, 0xdffefa4f, 262144, 262144},
		{"bakatono", "036-c2.bin", 1048576, 0xbbf003f5, 524288, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001b.63c", 524288, 0x0d40c953, 262144, 262144},
		{"bakatono", "036-c4.bin", 1048576, 0xf2577d22, 524288, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001b.53c", 524288, 0x1d39bad6, 262144, 262144},
		{"bakatono", "036-c3.bin", 1048576, 0x9ac0708e, 524288, 262144},
	},
	{
		ODD_COPY,
		{"bakatono", "n058001a.53c", 524288, 0xc6954f8e, 262144, 262144},
		{"bakatono", "036-c1.bin", 1048576, 0xfe7f1010, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001a.038", 524288, 0x188c5e11, 0, 262144},
		{"burningfh", "018-p1h.bin", 524288, 0xddffcbf4, 0, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001a.038", 524288, 0x188c5e11, 262144, 262144},
		{"burningfh", "018-p1h.bin", 524288, 0xddffcbf4, 0, 262144},
	},
	{
		FULL_COPY,
		{"burningf", "n054001a.1f8", 524288, 0xb55b9670, 0, 524288},
		{"burningfh", "018-v1.bin", 1048576, 0x508c9ffc, 0, 524288},
	},
	{
		FULL_COPY,
		{"burningf", "n054001b.1f8", 524288, 0x270f4707, 0, 524288},
		{"burningfh", "018-v2.bin", 1048576, 0x854ef277, 0, 524288},
	},
	{
		FULL_COPY,
		{"burningf", "n054001a.1fc", 524288, 0xa0bcf260, 0, 524288},
		{"burningfh", "018-v1.bin", 1048576, 0x508c9ffc, 524288, 524288},
	},
	{
		FULL_COPY,
		{"burningf", "n054001b.1fc", 524288, 0x924e3d69, 0, 524288},
		{"burningfh", "018-v2.bin", 1048576, 0x854ef277, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001a.538", 524288, 0x4ddc137b, 0, 262144},
		{"burningfh", "018-c1.bin", 1048576, 0x25a25e9b, 0, 262144},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001a.638", 524288, 0x7d7d87dc, 0, 262144},
		{"burningfh", "018-c2.bin", 1048576, 0xd4378876, 0, 262144},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001b.538", 524288, 0x2b2cb196, 0, 262144},
		{"burningfh", "018-c3.bin", 1048576, 0x862b60da, 0, 262144},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001b.638", 524288, 0x03aa8a36, 0, 262144},
		{"burningfh", "018-c4.bin", 1048576, 0xe2e0aff7, 0, 262144},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001a.53c", 524288, 0x896d8545, 0, 262144},
		{"burningfh", "018-c1.bin", 1048576, 0x25a25e9b, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001a.63c", 524288, 0x39fe5307, 0, 262144},
		{"burningfh", "018-c2.bin", 1048576, 0xd4378876, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001b.53c", 524288, 0x0f49caa9, 0, 262144},
		{"burningfh", "018-c3.bin", 1048576, 0x862b60da, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"burningf", "n054001b.63c", 524288, 0xf759626e, 0, 262144},
		{"burningfh", "018-c4.bin", 1048576, 0xe2e0aff7, 524288, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001a.538", 524288, 0x4ddc137b, 262144, 262144},
		{"burningfh", "018-c1.bin", 1048576, 0x25a25e9b, 0, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001a.638", 524288, 0x7d7d87dc, 262144, 262144},
		{"burningfh", "018-c2.bin", 1048576, 0xd4378876, 0, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001b.538", 524288, 0x2b2cb196, 262144, 262144},
		{"burningfh", "018-c3.bin", 1048576, 0x862b60da, 0, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001b.638", 524288, 0x03aa8a36, 262144, 262144},
		{"burningfh", "018-c4.bin", 1048576, 0xe2e0aff7, 0, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001a.53c", 524288, 0x896d8545, 262144, 262144},
		{"burningfh", "018-c1.bin", 1048576, 0x25a25e9b, 524288, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001a.63c", 524288, 0x39fe5307, 262144, 262144},
		{"burningfh", "018-c2.bin", 1048576, 0xd4378876, 524288, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001b.53c", 524288, 0x0f49caa9, 262144, 262144},
		{"burningfh", "018-c3.bin", 1048576, 0x862b60da, 524288, 262144},
	},
	{
		ODD_COPY,
		{"burningf", "n054001b.63c", 524288, 0xf759626e, 262144, 262144},
		{"burningfh", "018-c4.bin", 1048576, 0xe2e0aff7, 524288, 262144},
	},
	{
		FULL_COPY,
		{"crsword", "n046001a.1f8", 524288, 0x525df5c8, 0, 524288},
		{"crsword", "037-v1.bin", 1048576, 0x61fedf65, 0, 524288},
	},
	{
		FULL_COPY,
		{"crsword", "n046001a.4f8", 65536, 0x66633e5e, 0, 65536},
		{"crsword", "037-m1.bin", 131072, 0x9c384263, 0, 65536},
	},
	{
		FULL_COPY,
		{"crsword", "n046001a.1fc", 524288, 0xa11ecaf4, 0, 524288},
		{"crsword", "037-v1.bin", 1048576, 0x61fedf65, 524288, 524288},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001a.038", 524288, 0x42c78fe1, 0, 262144},
		{"crsword", "037-p1.bin", 524288, 0xe7f2553c, 0, 262144},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001a.538", 524288, 0x4b373de7, 0, 262144},
		{"crsword", "037-c1.bin", 1048576, 0x09df6892, 0, 262144},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001a.638", 524288, 0xe05f5f33, 0, 262144},
		{"crsword", "037-c2.bin", 1048576, 0xac122a78, 0, 262144},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001b.538", 524288, 0x61d25cb3, 0, 262144},
		{"crsword", "037-c3.bin", 1048576, 0x9d7ed1ca, 0, 262144},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001b.638", 524288, 0x01357559, 0, 262144},
		{"crsword", "037-c4.bin", 1048576, 0x4a24395d, 0, 262144},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001a.53c", 524288, 0xcddf6d69, 0, 262144},
		{"crsword", "037-c1.bin", 1048576, 0x09df6892, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001a.63c", 524288, 0x91ab11a4, 0, 262144},
		{"crsword", "037-c2.bin", 1048576, 0xac122a78, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001b.53c", 524288, 0x00bc3d84, 0, 262144},
		{"crsword", "037-c3.bin", 1048576, 0x9d7ed1ca, 524288, 262144},
	},
	{
		EVEN_COPY,
		{"crsword", "n046001b.63c", 524288, 0x28c6d19a, 0, 262144},
		{"crsword", "037-c4.bin", 1048576, 0x4a24395d, 524288, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001a.038", 524288, 0x42c78fe1, 262144, 262144},
		{"crsword", "037-p1.bin", 524288, 0xe7f2553c, 0, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001a.538", 524288, 0x4b373de7, 262144, 262144},
		{"crsword", "037-c1.bin", 1048576, 0x09df6892, 0, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001a.638", 524288, 0xe05f5f33, 262144, 262144},
		{"crsword", "037-c2.bin", 1048576, 0xac122a78, 0, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001b.538", 524288, 0x61d25cb3, 262144, 262144},
		{"crsword", "037-c3.bin", 1048576, 0x9d7ed1ca, 0, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001b.638", 524288, 0x01357559, 262144, 262144},
		{"crsword", "037-c4.bin", 1048576, 0x4a24395d, 0, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001a.53c", 524288, 0xcddf6d69, 262144, 262144},
		{"crsword", "037-c1.bin", 1048576, 0x09df6892, 524288, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001a.63c", 524288, 0x91ab11a4, 262144, 262144},
		{"crsword", "037-c2.bin", 1048576, 0xac122a78, 524288, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001b.53c", 524288, 0x00bc3d84, 262144, 262144},
		{"crsword", "037-c3.bin", 1048576, 0x9d7ed1ca, 524288, 262144},
	},
	{
		ODD_COPY,
		{"crsword", "n046001b.63c", 524288, 0x28c6d19a, 262144, 262144},
		{"crsword", "037-c4.bin", 1048576, 0x4a24395d, 524288, 262144},
	},
	{
		FULL_COPY,
		{"ncombat", "n046001a.478", 65536, 0x83821d6e, 0, 65536},
		{"ncombat", "009-m1.bin", 131072, 0xb5819863, 0, 65536},
	},
	{
		EVEN_COPY,
		{"ncombat", "n046001a.038", 524288, 0x89660a31, 0, 262144},
		{"ncombat", "009-p1.bin", 524288, 0xb45fcfbf, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncombat", "n046001a.538", 524288, 0x0147a4b5, 0, 262144},
		{"ncombat", "009-c1.bin", 524288, 0x33cc838e, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncombat", "n046001a.53c", 524288, 0x4df6123a, 0, 262144},
		{"ncombat", "009-c3.bin", 524288, 0x3b60a05d, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncombat", "n046001a.638", 524288, 0xe3d367f8, 0, 262144},
		{"ncombat", "009-c2.bin", 524288, 0x26877feb, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncombat", "n046001a.63c", 524288, 0x1c1f6101, 0, 262144},
		{"ncombat", "009-c4.bin", 524288, 0x39c2d039, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncombat", "n046001b.538", 524288, 0x19441c78, 0, 262144},
		{"ncombat", "009-c5.bin", 524288, 0x67a4344e, 0, 262144},
	},
	{
		EVEN_COPY,
		{"ncombat", "n046001b.638", 524288, 0xf417f9ac, 0, 262144},
		{"ncombat", "009-c6.bin", 524288, 0x2eca8b19, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncombat", "n046001a.038", 524288, 0x89660a31, 262144, 262144},
		{"ncombat", "009-p1.bin", 524288, 0xb45fcfbf, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncombat", "n046001a.538", 524288, 0x0147a4b5, 262144, 262144},
		{"ncombat", "009-c1.bin", 524288, 0x33cc838e, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncombat", "n046001a.53c", 524288, 0x4df6123a, 262144, 262144},
		{"ncombat", "009-c3.bin", 524288, 0x3b60a05d, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncombat", "n046001a.638", 524288, 0xe3d367f8, 262144, 262144},
		{"ncombat", "009-c2.bin", 524288, 0x26877feb, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncombat", "n046001a.63c", 524288, 0x1c1f6101, 262144, 262144},
		{"ncombat", "009-c4.bin", 524288, 0x39c2d039, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncombat", "n046001b.538", 524288, 0x19441c78, 262144, 262144},
		{"ncombat", "009-c5.bin", 524288, 0x67a4344e, 0, 262144},
	},
	{
		ODD_COPY,
		{"ncombat", "n046001b.638", 524288, 0xf417f9ac, 262144, 262144},
		{"ncombat", "009-c6.bin", 524288, 0x2eca8b19, 0, 262144},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_c1.rom", 524288, 0xe17fa618, 0, 524288},
		{"roboarmy", "032-c1.bin", 1048576, 0x97984c6c, 0, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_c2.rom", 524288, 0xd5ebdb4d, 0, 524288},
		{"roboarmy", "032-c2.bin", 1048576, 0x65773122, 0, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_v1.rom", 524288, 0xdaff9896, 0, 524288},
		{"roboarmy", "032-v1.bin", 1048576, 0x63791533, 0, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_v3.rom", 524288, 0xb69c1da5, 0, 524288},
		{"roboarmy", "032-v2.bin", 1048576, 0xeb95de70, 0, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_c3.rom", 524288, 0xaa4d7695, 0, 524288},
		{"roboarmy", "032-c1.bin", 1048576, 0x97984c6c, 524288, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_c4.rom", 524288, 0x8d4ebbe3, 0, 524288},
		{"roboarmy", "032-c2.bin", 1048576, 0x65773122, 524288, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_v2.rom", 524288, 0x8781b1bc, 0, 524288},
		{"roboarmy", "032-v1.bin", 1048576, 0x63791533, 524288, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_v4.rom", 524288, 0x2c929c17, 0, 524288},
		{"roboarmy", "032-v2.bin", 1048576, 0xeb95de70, 524288, 524288},
	},
	// MAME v0.80 Changes
	{
		FULL_COPY,
		{"aof3", "aof3_c1.rom", 4194304, 0xf6c74731, 0, 2097152},
		{"aof3", "096-c1.bin", 4194304, 0xf17b8d89, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c2.rom", 4194304, 0xf587f149, 0, 2097152},
		{"aof3", "096-c2.bin", 4194304, 0x3840c508, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c3.rom", 4194304, 0x7749f5e6, 0, 2097152},
		{"aof3", "096-c3.bin", 4194304, 0x55f9ee1e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c4.rom", 4194304, 0xcbd58369, 0, 2097152},
		{"aof3", "096-c4.bin", 4194304, 0x585b7e47, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c5.rom", 4194304, 0x1718bdcd, 0, 2097152},
		{"aof3", "096-c5.bin", 4194304, 0xc75a753c, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c6.rom", 4194304, 0x4fca967f, 0, 2097152},
		{"aof3", "096-c6.bin", 4194304, 0x9a9d2f7a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c1.rom", 4194304, 0xf6c74731, 2097152, 2097152},
		{"aof3", "096-c1.bin", 4194304, 0xf17b8d89, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c2.rom", 4194304, 0xf587f149, 2097152, 2097152},
		{"aof3", "096-c2.bin", 4194304, 0x3840c508, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c3.rom", 4194304, 0x7749f5e6, 2097152, 2097152},
		{"aof3", "096-c3.bin", 4194304, 0x55f9ee1e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c4.rom", 4194304, 0xcbd58369, 2097152, 2097152},
		{"aof3", "096-c4.bin", 4194304, 0x585b7e47, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c5.rom", 4194304, 0x1718bdcd, 2097152, 2097152},
		{"aof3", "096-c5.bin", 4194304, 0xc75a753c, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c6.rom", 4194304, 0x4fca967f, 2097152, 2097152},
		{"aof3", "096-c6.bin", 4194304, 0x9a9d2f7a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c1.rom", 4194304, 0x754744e0, 0, 2097152},
		{"blazstar", "239-c1.bin", 4194304, 0x84f6d584, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c2.rom", 4194304, 0xaf98c037, 0, 2097152},
		{"blazstar", "239-c2.bin", 4194304, 0x05a0cb22, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c3.rom", 4194304, 0x7b39b590, 0, 2097152},
		{"blazstar", "239-c3.bin", 4194304, 0x5fb69c9e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c4.rom", 4194304, 0x6e731b30, 0, 2097152},
		{"blazstar", "239-c4.bin", 4194304, 0x0be028c4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c5.rom", 4194304, 0x9ceb113b, 0, 2097152},
		{"blazstar", "239-c5.bin", 4194304, 0x74bae5f8, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c6.rom", 4194304, 0x6a78e810, 0, 2097152},
		{"blazstar", "239-c6.bin", 4194304, 0x4e0700d2, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c7.rom", 4194304, 0x50d28eca, 0, 2097152},
		{"blazstar", "239-c7.bin", 4194304, 0x010ff4fd, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c8.rom", 4194304, 0xcdbbb7d7, 0, 2097152},
		{"blazstar", "239-c8.bin", 4194304, 0xdb60460e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c1.rom", 4194304, 0x754744e0, 2097152, 2097152},
		{"blazstar", "239-c1.bin", 4194304, 0x84f6d584, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c2.rom", 4194304, 0xaf98c037, 2097152, 2097152},
		{"blazstar", "239-c2.bin", 4194304, 0x05a0cb22, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c3.rom", 4194304, 0x7b39b590, 2097152, 2097152},
		{"blazstar", "239-c3.bin", 4194304, 0x5fb69c9e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c4.rom", 4194304, 0x6e731b30, 2097152, 2097152},
		{"blazstar", "239-c4.bin", 4194304, 0x0be028c4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c5.rom", 4194304, 0x9ceb113b, 2097152, 2097152},
		{"blazstar", "239-c5.bin", 4194304, 0x74bae5f8, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c6.rom", 4194304, 0x6a78e810, 2097152, 2097152},
		{"blazstar", "239-c6.bin", 4194304, 0x4e0700d2, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c7.rom", 4194304, 0x50d28eca, 2097152, 2097152},
		{"blazstar", "239-c7.bin", 4194304, 0x010ff4fd, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c8.rom", 4194304, 0xcdbbb7d7, 2097152, 2097152},
		{"blazstar", "239-c8.bin", 4194304, 0xdb60460e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c1.rom", 4194304, 0xd061f1f5, 0, 2097152},
		{"goalx3", "209-c1.bin", 4194304, 0xb49d980e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c2.rom", 4194304, 0x3f63c1a2, 0, 2097152},
		{"goalx3", "209-c2.bin", 4194304, 0x5649b015, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c1.rom", 4194304, 0xd061f1f5, 2097152, 2097152},
		{"goalx3", "209-c1.bin", 4194304, 0xb49d980e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c2.rom", 4194304, 0x3f63c1a2, 2097152, 2097152},
		{"goalx3", "209-c2.bin", 4194304, 0x5649b015, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c1.rom", 4194304, 0x4d896a58, 0, 2097152},
		{"kabukikl", "092-c1.bin", 4194304, 0x2a9fab01, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c2.rom", 4194304, 0x3cf78a18, 0, 2097152},
		{"kabukikl", "092-c2.bin", 4194304, 0x6d2bac02, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c3.rom", 4194304, 0x58c454e7, 0, 2097152},
		{"kabukikl", "092-c3.bin", 4194304, 0x5da735d6, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c4.rom", 4194304, 0xe1a8aa6a, 0, 2097152},
		{"kabukikl", "092-c4.bin", 4194304, 0xde07f997, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c1.rom", 4194304, 0x4d896a58, 2097152, 2097152},
		{"kabukikl", "092-c1.bin", 4194304, 0x2a9fab01, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c2.rom", 4194304, 0x3cf78a18, 2097152, 2097152},
		{"kabukikl", "092-c2.bin", 4194304, 0x6d2bac02, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c3.rom", 4194304, 0x58c454e7, 2097152, 2097152},
		{"kabukikl", "092-c3.bin", 4194304, 0x5da735d6, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c4.rom", 4194304, 0xe1a8aa6a, 2097152, 2097152},
		{"kabukikl", "092-c4.bin", 4194304, 0xde07f997, 0, 2097152},
	},
	{
		FULL_COPY,
		{"lastblad", "lb_c5.rom", 2097152, 0x17bbd7ca, 0, 2097152},
		{"lastblad", "234-c5.bin", 4194304, 0x1ba80cee, 0, 2097152},
	},
	{
		FULL_COPY,
		{"lastblad", "lb_c6.rom", 2097152, 0x5c35d541, 0, 2097152},
		{"lastblad", "234-c6.bin", 4194304, 0xbeafd091, 0, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c1.rom", 4194304, 0x734db3d6, 0, 2097152},
		{"magdrop3", "233-c1.bin", 4194304, 0x65e3f4c4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c2.rom", 4194304, 0xd78f50e5, 0, 2097152},
		{"magdrop3", "233-c2.bin", 4194304, 0x35dea6c9, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c3.rom", 4194304, 0xec65f472, 0, 2097152},
		{"magdrop3", "233-c3.bin", 4194304, 0x0ba2c502, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c4.rom", 4194304, 0xf55dddf3, 0, 2097152},
		{"magdrop3", "233-c4.bin", 4194304, 0x70dbbd6d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c1.rom", 4194304, 0x734db3d6, 2097152, 2097152},
		{"magdrop3", "233-c1.bin", 4194304, 0x65e3f4c4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c2.rom", 4194304, 0xd78f50e5, 2097152, 2097152},
		{"magdrop3", "233-c2.bin", 4194304, 0x35dea6c9, 0, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c3.rom", 4194304, 0xec65f472, 2097152, 2097152},
		{"magdrop3", "233-c3.bin", 4194304, 0x0ba2c502, 0, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c4.rom", 4194304, 0xf55dddf3, 2097152, 2097152},
		{"magdrop3", "233-c4.bin", 4194304, 0x70dbbd6d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c1.rom", 4194304, 0xd00bd152, 0, 2097152},
		{"mslug", "201-c1.bin", 4194304, 0x72813676, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c2.rom", 4194304, 0xddff1dea, 0, 2097152},
		{"mslug", "201-c2.bin", 4194304, 0x96f62574, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c3.rom", 4194304, 0xd3d5f9e5, 0, 2097152},
		{"mslug", "201-c3.bin", 4194304, 0x5121456a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c4.rom", 4194304, 0x5ac1d497, 0, 2097152},
		{"mslug", "201-c4.bin", 4194304, 0xf4ad59a3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c1.rom", 4194304, 0xd00bd152, 2097152, 2097152},
		{"mslug", "201-c1.bin", 4194304, 0x72813676, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c2.rom", 4194304, 0xddff1dea, 2097152, 2097152},
		{"mslug", "201-c2.bin", 4194304, 0x96f62574, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c3.rom", 4194304, 0xd3d5f9e5, 2097152, 2097152},
		{"mslug", "201-c3.bin", 4194304, 0x5121456a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c4.rom", 4194304, 0x5ac1d497, 2097152, 2097152},
		{"mslug", "201-c4.bin", 4194304, 0xf4ad59a3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_c1.rom", 4194304, 0xb90ebed4, 0, 2097152},
		{"neobombe", "093-c1.bin", 4194304, 0xd1f328f8, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_c2.rom", 4194304, 0x41e62b4f, 0, 2097152},
		{"neobombe", "093-c2.bin", 4194304, 0x82c49540, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_v1.rom", 4194304, 0x43057e99, 0, 2097152},
		{"neobombe", "093-v1.bin", 4194304, 0x02abd4b0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_c1.rom", 4194304, 0xb90ebed4, 2097152, 2097152},
		{"neobombe", "093-c1.bin", 4194304, 0xd1f328f8, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_c2.rom", 4194304, 0x41e62b4f, 2097152, 2097152},
		{"neobombe", "093-c2.bin", 4194304, 0x82c49540, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_v1.rom", 4194304, 0x43057e99, 2097152, 2097152},
		{"neobombe", "093-v1.bin", 4194304, 0x02abd4b0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c1.rom", 4194304, 0x62c5edc9, 0, 2097152},
		{"neodrift", "213-c1.bin", 4194304, 0x3edc8bd3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c2.rom", 4194304, 0x9dc9c72a, 0, 2097152},
		{"neodrift", "213-c2.bin", 4194304, 0x46ae5f16, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c1.rom", 4194304, 0x62c5edc9, 2097152, 2097152},
		{"neodrift", "213-c1.bin", 4194304, 0x3edc8bd3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c2.rom", 4194304, 0x9dc9c72a, 2097152, 2097152},
		{"neodrift", "213-c2.bin", 4194304, 0x46ae5f16, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c1.rom", 4194304, 0x58f91ae0, 0, 2097152},
		{"ninjamas", "217-c1.bin", 4194304, 0x5fe97bc4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c2.rom", 4194304, 0x4258147f, 0, 2097152},
		{"ninjamas", "217-c2.bin", 4194304, 0x886e0d66, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c3.rom", 4194304, 0x36c29ce3, 0, 2097152},
		{"ninjamas", "217-c3.bin", 4194304, 0x59e8525f, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c4.rom", 4194304, 0x17e97a6e, 0, 2097152},
		{"ninjamas", "217-c4.bin", 4194304, 0x8521add2, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c5.rom", 4194304, 0x4683ffc0, 0, 2097152},
		{"ninjamas", "217-c5.bin", 4194304, 0xfb1896e5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c6.rom", 4194304, 0xde004f4a, 0, 2097152},
		{"ninjamas", "217-c6.bin", 4194304, 0x1c98c54b, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c7.rom", 4194304, 0x3e1885c0, 0, 2097152},
		{"ninjamas", "217-c7.bin", 4194304, 0x8b0ede2e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c8.rom", 4194304, 0x5a5df034, 0, 2097152},
		{"ninjamas", "217-c8.bin", 4194304, 0xa085bb61, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c1.rom", 4194304, 0x58f91ae0, 2097152, 2097152},
		{"ninjamas", "217-c1.bin", 4194304, 0x5fe97bc4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c2.rom", 4194304, 0x4258147f, 2097152, 2097152},
		{"ninjamas", "217-c2.bin", 4194304, 0x886e0d66, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c3.rom", 4194304, 0x36c29ce3, 2097152, 2097152},
		{"ninjamas", "217-c3.bin", 4194304, 0x59e8525f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c4.rom", 4194304, 0x17e97a6e, 2097152, 2097152},
		{"ninjamas", "217-c4.bin", 4194304, 0x8521add2, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c5.rom", 4194304, 0x4683ffc0, 2097152, 2097152},
		{"ninjamas", "217-c5.bin", 4194304, 0xfb1896e5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c6.rom", 4194304, 0xde004f4a, 2097152, 2097152},
		{"ninjamas", "217-c6.bin", 4194304, 0x1c98c54b, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c7.rom", 4194304, 0x3e1885c0, 2097152, 2097152},
		{"ninjamas", "217-c7.bin", 4194304, 0x8b0ede2e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c8.rom", 4194304, 0x5a5df034, 2097152, 2097152},
		{"ninjamas", "217-c8.bin", 4194304, 0xa085bb61, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c1.rom", 4194304, 0x63020fc6, 0, 2097152},
		{"pulstar", "089-c1.bin", 4194304, 0xf4e97332, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c2.rom", 4194304, 0x260e9d4d, 0, 2097152},
		{"pulstar", "089-c2.bin", 4194304, 0x836d14da, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c3.rom", 4194304, 0x21ef41d7, 0, 2097152},
		{"pulstar", "089-c3.bin", 4194304, 0x913611c4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c4.rom", 4194304, 0x3b9e288f, 0, 2097152},
		{"pulstar", "089-c4.bin", 4194304, 0x44cef0e3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c5.rom", 4194304, 0x6fe9259c, 0, 2097152},
		{"pulstar", "089-c5.bin", 4194304, 0x89baa1d7, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c6.rom", 4194304, 0xdc32f2b4, 0, 2097152},
		{"pulstar", "089-c6.bin", 4194304, 0xb2594d56, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c1.rom", 4194304, 0x63020fc6, 2097152, 2097152},
		{"pulstar", "089-c1.bin", 4194304, 0xf4e97332, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c2.rom", 4194304, 0x260e9d4d, 2097152, 2097152},
		{"pulstar", "089-c2.bin", 4194304, 0x836d14da, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c3.rom", 4194304, 0x21ef41d7, 2097152, 2097152},
		{"pulstar", "089-c3.bin", 4194304, 0x913611c4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c4.rom", 4194304, 0x3b9e288f, 2097152, 2097152},
		{"pulstar", "089-c4.bin", 4194304, 0x44cef0e3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c5.rom", 4194304, 0x6fe9259c, 2097152, 2097152},
		{"pulstar", "089-c5.bin", 4194304, 0x89baa1d7, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c6.rom", 4194304, 0xdc32f2b4, 2097152, 2097152},
		{"pulstar", "089-c6.bin", 4194304, 0xb2594d56, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c1.rom", 4194304, 0x18f61d79, 0, 2097152},
		{"ragnagrd", "218-c1.bin", 4194304, 0xc31500a4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c2.rom", 4194304, 0xdbf4ff4b, 0, 2097152},
		{"ragnagrd", "218-c2.bin", 4194304, 0x98aba1f9, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c3.rom", 4194304, 0x108d5589, 0, 2097152},
		{"ragnagrd", "218-c3.bin", 4194304, 0x833c163a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c4.rom", 4194304, 0x7962d5ac, 0, 2097152},
		{"ragnagrd", "218-c4.bin", 4194304, 0xc1a30f69, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c5.rom", 4194304, 0x4b74021a, 0, 2097152},
		{"ragnagrd", "218-c5.bin", 4194304, 0x6b6de0ff, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c6.rom", 4194304, 0xf5cf90bc, 0, 2097152},
		{"ragnagrd", "218-c6.bin", 4194304, 0x94beefcf, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c7.rom", 4194304, 0x32189762, 0, 2097152},
		{"ragnagrd", "218-c7.bin", 4194304, 0xde6f9b28, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c8.rom", 4194304, 0xd5915828, 0, 2097152},
		{"ragnagrd", "218-c8.bin", 4194304, 0xd9b311f6, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c1.rom", 4194304, 0x18f61d79, 2097152, 2097152},
		{"ragnagrd", "218-c1.bin", 4194304, 0xc31500a4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c2.rom", 4194304, 0xdbf4ff4b, 2097152, 2097152},
		{"ragnagrd", "218-c2.bin", 4194304, 0x98aba1f9, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c3.rom", 4194304, 0x108d5589, 2097152, 2097152},
		{"ragnagrd", "218-c3.bin", 4194304, 0x833c163a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c4.rom", 4194304, 0x7962d5ac, 2097152, 2097152},
		{"ragnagrd", "218-c4.bin", 4194304, 0xc1a30f69, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c5.rom", 4194304, 0x4b74021a, 2097152, 2097152},
		{"ragnagrd", "218-c5.bin", 4194304, 0x6b6de0ff, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c6.rom", 4194304, 0xf5cf90bc, 2097152, 2097152},
		{"ragnagrd", "218-c6.bin", 4194304, 0x94beefcf, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c7.rom", 4194304, 0x32189762, 2097152, 2097152},
		{"ragnagrd", "218-c7.bin", 4194304, 0xde6f9b28, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c8.rom", 4194304, 0xd5915828, 2097152, 2097152},
		{"ragnagrd", "218-c8.bin", 4194304, 0xd9b311f6, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c1.rom", 4194304, 0x436edad4, 0, 2097152},
		{"rbffspec", "223-c1.bin", 4194304, 0xebab05e2, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c2.rom", 4194304, 0xcc7dc384, 0, 2097152},
		{"rbffspec", "223-c2.bin", 4194304, 0x641868c3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c3.rom", 4194304, 0x375954ea, 0, 2097152},
		{"rbffspec", "223-c3.bin", 4194304, 0xca00191f, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c4.rom", 4194304, 0xc1a98dd7, 0, 2097152},
		{"rbffspec", "223-c4.bin", 4194304, 0x1f23d860, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c5.rom", 4194304, 0x12c5418e, 0, 2097152},
		{"rbffspec", "223-c5.bin", 4194304, 0x321e362c, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c6.rom", 4194304, 0xc8ad71d5, 0, 2097152},
		{"rbffspec", "223-c6.bin", 4194304, 0xd8fcef90, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c7.rom", 4194304, 0x5c33d1d8, 0, 2097152},
		{"rbffspec", "223-c7.bin", 4194304, 0xbc80dd2d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c8.rom", 4194304, 0xefdeb140, 0, 2097152},
		{"rbffspec", "223-c8.bin", 4194304, 0x5ad62102, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_p2.rom", 4194304, 0x27e3e54b, 0, 2097152},
		{"rbffspec", "223-p2.bin", 4194304, 0xaddd8f08, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c1.rom", 4194304, 0x436edad4, 2097152, 2097152},
		{"rbffspec", "223-c1.bin", 4194304, 0xebab05e2, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c2.rom", 4194304, 0xcc7dc384, 2097152, 2097152},
		{"rbffspec", "223-c2.bin", 4194304, 0x641868c3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c3.rom", 4194304, 0x375954ea, 2097152, 2097152},
		{"rbffspec", "223-c3.bin", 4194304, 0xca00191f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c4.rom", 4194304, 0xc1a98dd7, 2097152, 2097152},
		{"rbffspec", "223-c4.bin", 4194304, 0x1f23d860, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c5.rom", 4194304, 0x12c5418e, 2097152, 2097152},
		{"rbffspec", "223-c5.bin", 4194304, 0x321e362c, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c6.rom", 4194304, 0xc8ad71d5, 2097152, 2097152},
		{"rbffspec", "223-c6.bin", 4194304, 0xd8fcef90, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c7.rom", 4194304, 0x5c33d1d8, 2097152, 2097152},
		{"rbffspec", "223-c7.bin", 4194304, 0xbc80dd2d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c8.rom", 4194304, 0xefdeb140, 2097152, 2097152},
		{"rbffspec", "223-c8.bin", 4194304, 0x5ad62102, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_p2.rom", 4194304, 0x27e3e54b, 2097152, 2097152},
		{"rbffspec", "223-p2.bin", 4194304, 0xaddd8f08, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c7.rom", 524288, 0x7a01f666, 0, 524288},
		{"samsho3h", "087-c7.bin", 1048576, 0xae450e3d, 0, 524288},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c8.rom", 524288, 0xffd009c2, 0, 524288},
		{"samsho3h", "087-c8.bin", 1048576, 0xa9e82717, 0, 524288},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c1.rom", 4194304, 0xe079f767, 0, 2097152},
		{"samsho3h", "087-c1.bin", 4194304, 0x07a233bc, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c2.rom", 4194304, 0xfc045909, 0, 2097152},
		{"samsho3h", "087-c2.bin", 4194304, 0x7a413592, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c3.rom", 4194304, 0xc61218d7, 0, 2097152},
		{"samsho3h", "087-c3.bin", 4194304, 0x8b793796, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c4.rom", 4194304, 0x054ec754, 0, 2097152},
		{"samsho3h", "087-c4.bin", 4194304, 0x728fbf11, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c5.rom", 4194304, 0x05feee47, 0, 2097152},
		{"samsho3h", "087-c5.bin", 4194304, 0x172ab180, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c6.rom", 4194304, 0xef7d9e29, 0, 2097152},
		{"samsho3h", "087-c6.bin", 4194304, 0x002ff8f3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c1.rom", 4194304, 0xe079f767, 2097152, 2097152},
		{"samsho3h", "087-c1.bin", 4194304, 0x07a233bc, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c2.rom", 4194304, 0xfc045909, 2097152, 2097152},
		{"samsho3h", "087-c2.bin", 4194304, 0x7a413592, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c3.rom", 4194304, 0xc61218d7, 2097152, 2097152},
		{"samsho3h", "087-c3.bin", 4194304, 0x8b793796, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c4.rom", 4194304, 0x054ec754, 2097152, 2097152},
		{"samsho3h", "087-c4.bin", 4194304, 0x728fbf11, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c5.rom", 4194304, 0x05feee47, 2097152, 2097152},
		{"samsho3h", "087-c5.bin", 4194304, 0x172ab180, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c6.rom", 4194304, 0xef7d9e29, 2097152, 2097152},
		{"samsho3h", "087-c6.bin", 4194304, 0x002ff8f3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c1.rom", 4194304, 0x289100fa, 0, 2097152},
		{"samsho4", "222-c1.bin", 4194304, 0x68f2ed95, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c2.rom", 4194304, 0xc2716ea0, 0, 2097152},
		{"samsho4", "222-c2.bin", 4194304, 0xa6e9aff0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c3.rom", 4194304, 0x6659734f, 0, 2097152},
		{"samsho4", "222-c3.bin", 4194304, 0xc91b40f4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c4.rom", 4194304, 0x91ebea00, 0, 2097152},
		{"samsho4", "222-c4.bin", 4194304, 0x359510a4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c5.rom", 4194304, 0xe22254ed, 0, 2097152},
		{"samsho4", "222-c5.bin", 4194304, 0x9cfbb22d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c6.rom", 4194304, 0x00947b2e, 0, 2097152},
		{"samsho4", "222-c6.bin", 4194304, 0x685efc32, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c7.rom", 4194304, 0xe3e3b0cd, 0, 2097152},
		{"samsho4", "222-c7.bin", 4194304, 0xd0f86f0d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c8.rom", 4194304, 0xf33967f1, 0, 2097152},
		{"samsho4", "222-c8.bin", 4194304, 0xadfc50e3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_p2.rom", 4194304, 0x7587f09b, 0, 2097152},
		{"samsho4", "222-p2.bin", 4194304, 0xb023cd8b, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c1.rom", 4194304, 0x289100fa, 2097152, 2097152},
		{"samsho4", "222-c1.bin", 4194304, 0x68f2ed95, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c2.rom", 4194304, 0xc2716ea0, 2097152, 2097152},
		{"samsho4", "222-c2.bin", 4194304, 0xa6e9aff0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c3.rom", 4194304, 0x6659734f, 2097152, 2097152},
		{"samsho4", "222-c3.bin", 4194304, 0xc91b40f4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c4.rom", 4194304, 0x91ebea00, 2097152, 2097152},
		{"samsho4", "222-c4.bin", 4194304, 0x359510a4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c5.rom", 4194304, 0xe22254ed, 2097152, 2097152},
		{"samsho4", "222-c5.bin", 4194304, 0x9cfbb22d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c6.rom", 4194304, 0x00947b2e, 2097152, 2097152},
		{"samsho4", "222-c6.bin", 4194304, 0x685efc32, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c7.rom", 4194304, 0xe3e3b0cd, 2097152, 2097152},
		{"samsho4", "222-c7.bin", 4194304, 0xd0f86f0d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c8.rom", 4194304, 0xf33967f1, 2097152, 2097152},
		{"samsho4", "222-c8.bin", 4194304, 0xadfc50e3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_p2.rom", 4194304, 0x7587f09b, 2097152, 2097152},
		{"samsho4", "222-p2.bin", 4194304, 0xb023cd8b, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c1.rom", 4194304, 0xaad087fc, 0, 2097152},
		{"shocktro", "238-c1.bin", 4194304, 0x90c6a181, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c2.rom", 4194304, 0x7e39df1f, 0, 2097152},
		{"shocktro", "238-c2.bin", 4194304, 0x888720f0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c3.rom", 4194304, 0x6682a458, 0, 2097152},
		{"shocktro", "238-c3.bin", 4194304, 0x2c393aa3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c4.rom", 4194304, 0xcbef1f17, 0, 2097152},
		{"shocktro", "238-c4.bin", 4194304, 0xb9e909eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c5.rom", 4194304, 0xe17762b1, 0, 2097152},
		{"shocktro", "238-c5.bin", 4194304, 0xc22c68eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c6.rom", 4194304, 0x28beab71, 0, 2097152},
		{"shocktro", "238-c6.bin", 4194304, 0x119323cd, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c7.rom", 4194304, 0xa47e62d2, 0, 2097152},
		{"shocktro", "238-c7.bin", 4194304, 0xa72ce7ed, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c8.rom", 4194304, 0xe8e890fb, 0, 2097152},
		{"shocktro", "238-c8.bin", 4194304, 0x1c7c2efb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_p2.rom", 4194304, 0x646f6c76, 0, 2097152},
		{"shocktro", "238-p2.bin", 4194304, 0x5b4a09c5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c1.rom", 4194304, 0xaad087fc, 2097152, 2097152},
		{"shocktro", "238-c1.bin", 4194304, 0x90c6a181, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c2.rom", 4194304, 0x7e39df1f, 2097152, 2097152},
		{"shocktro", "238-c2.bin", 4194304, 0x888720f0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c3.rom", 4194304, 0x6682a458, 2097152, 2097152},
		{"shocktro", "238-c3.bin", 4194304, 0x2c393aa3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c4.rom", 4194304, 0xcbef1f17, 2097152, 2097152},
		{"shocktro", "238-c4.bin", 4194304, 0xb9e909eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c5.rom", 4194304, 0xe17762b1, 2097152, 2097152},
		{"shocktro", "238-c5.bin", 4194304, 0xc22c68eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c6.rom", 4194304, 0x28beab71, 2097152, 2097152},
		{"shocktro", "238-c6.bin", 4194304, 0x119323cd, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c7.rom", 4194304, 0xa47e62d2, 2097152, 2097152},
		{"shocktro", "238-c7.bin", 4194304, 0xa72ce7ed, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c8.rom", 4194304, 0xe8e890fb, 2097152, 2097152},
		{"shocktro", "238-c8.bin", 4194304, 0x1c7c2efb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_p2.rom", 4194304, 0x646f6c76, 2097152, 2097152},
		{"shocktro", "238-p2.bin", 4194304, 0x5b4a09c5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi3", "sonw3_c1.rom", 4194304, 0x3ca97864, 0, 2097152},
		{"sonicwi3", "097-c1.bin", 4194304, 0x33d0d589, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi3", "sonw3_c2.rom", 4194304, 0x1da4b3a9, 0, 2097152},
		{"sonicwi3", "097-c2.bin", 4194304, 0x186f8b43, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi3", "sonw3_c1.rom", 4194304, 0x3ca97864, 2097152, 2097152},
		{"sonicwi3", "097-c1.bin", 4194304, 0x33d0d589, 0, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi3", "sonw3_c2.rom", 4194304, 0x1da4b3a9, 2097152, 2097152},
		{"sonicwi3", "097-c2.bin", 4194304, 0x186f8b43, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c1.rom", 4194304, 0x288a9225, 0, 2097152},
		{"ssideki4", "215-c1.bin", 4194304, 0x8ff444f5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c2.rom", 4194304, 0x3fc9d1c4, 0, 2097152},
		{"ssideki4", "215-c2.bin", 4194304, 0x5b155037, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c3.rom", 4194304, 0xfedfaebe, 0, 2097152},
		{"ssideki4", "215-c3.bin", 4194304, 0x456a073a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c4.rom", 4194304, 0x877a5bb2, 0, 2097152},
		{"ssideki4", "215-c4.bin", 4194304, 0x43c182e1, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_v1.rom", 4194304, 0xc4bfed62, 0, 2097152},
		{"ssideki4", "215-v1.bin", 4194304, 0x877d1409, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c1.rom", 4194304, 0x288a9225, 2097152, 2097152},
		{"ssideki4", "215-c1.bin", 4194304, 0x8ff444f5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c2.rom", 4194304, 0x3fc9d1c4, 2097152, 2097152},
		{"ssideki4", "215-c2.bin", 4194304, 0x5b155037, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c3.rom", 4194304, 0xfedfaebe, 2097152, 2097152},
		{"ssideki4", "215-c3.bin", 4194304, 0x456a073a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c4.rom", 4194304, 0x877a5bb2, 2097152, 2097152},
		{"ssideki4", "215-c4.bin", 4194304, 0x43c182e1, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_v1.rom", 4194304, 0xc4bfed62, 2097152, 2097152},
		{"ssideki4", "215-v1.bin", 4194304, 0x877d1409, 0, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c1.rom", 4194304, 0x8c6733f2, 0, 2097152},
		{"turfmast", "200-c1.bin", 4194304, 0x8e7bf41a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c2.rom", 4194304, 0x596cc256, 0, 2097152},
		{"turfmast", "200-c2.bin", 4194304, 0x5a65a8ce, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c1.rom", 4194304, 0x8c6733f2, 2097152, 2097152},
		{"turfmast", "200-c1.bin", 4194304, 0x8e7bf41a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c2.rom", 4194304, 0x596cc256, 2097152, 2097152},
		{"turfmast", "200-c2.bin", 4194304, 0x5a65a8ce, 0, 2097152},
	},
	{
		FULL_COPY,
		{"twinspri", "sprit_c1.rom", 4194304, 0x73b2a70b, 0, 2097152},
		{"twinspri", "224-c1.bin", 4194304, 0xf7da64ab, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"twinspri", "sprit_c2.rom", 4194304, 0x3a3e506c, 0, 2097152},
		{"twinspri", "224-c2.bin", 4194304, 0x4c09bbfb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"twinspri", "sprit_c1.rom", 4194304, 0x73b2a70b, 2097152, 2097152},
		{"twinspri", "224-c1.bin", 4194304, 0xf7da64ab, 0, 2097152},
	},
	{
		FULL_COPY,
		{"twinspri", "sprit_c2.rom", 4194304, 0x3a3e506c, 2097152, 2097152},
		{"twinspri", "224-c2.bin", 4194304, 0x4c09bbfb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"tws96", "tecmo_c1.rom", 4194304, 0xd301a867, 0, 2097152},
		{"tws96", "086-c1.bin", 4194304, 0x2611bc2a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"tws96", "tecmo_c2.rom", 4194304, 0x305fc74f, 0, 2097152},
		{"tws96", "086-c2.bin", 4194304, 0x6b0d6827, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"tws96", "tecmo_c1.rom", 4194304, 0xd301a867, 2097152, 2097152},
		{"tws96", "086-c1.bin", 4194304, 0x2611bc2a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"tws96", "tecmo_c2.rom", 4194304, 0x305fc74f, 2097152, 2097152},
		{"tws96", "086-c2.bin", 4194304, 0x6b0d6827, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c1.rom", 4194304, 0xd91d386f, 0, 2097152},
		{"wakuwak7", "225-c1.bin", 4194304, 0xee4fea54, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c2.rom", 4194304, 0x36b5cf41, 0, 2097152},
		{"wakuwak7", "225-c2.bin", 4194304, 0x0c549e2d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c3.rom", 4194304, 0x02fcff2f, 0, 2097152},
		{"wakuwak7", "225-c3.bin", 4194304, 0xaf0897c0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c4.rom", 4194304, 0xcd7f1241, 0, 2097152},
		{"wakuwak7", "225-c4.bin", 4194304, 0x4c66527a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c5.rom", 4194304, 0x03d32f25, 0, 2097152},
		{"wakuwak7", "225-c5.bin", 4194304, 0x8ecea2b5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c6.rom", 4194304, 0xd996a90a, 0, 2097152},
		{"wakuwak7", "225-c6.bin", 4194304, 0x0eb11a6d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c1.rom", 4194304, 0xd91d386f, 2097152, 2097152},
		{"wakuwak7", "225-c1.bin", 4194304, 0xee4fea54, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c2.rom", 4194304, 0x36b5cf41, 2097152, 2097152},
		{"wakuwak7", "225-c2.bin", 4194304, 0x0c549e2d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c3.rom", 4194304, 0x02fcff2f, 2097152, 2097152},
		{"wakuwak7", "225-c3.bin", 4194304, 0xaf0897c0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c4.rom", 4194304, 0xcd7f1241, 2097152, 2097152},
		{"wakuwak7", "225-c4.bin", 4194304, 0x4c66527a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c5.rom", 4194304, 0x03d32f25, 2097152, 2097152},
		{"wakuwak7", "225-c5.bin", 4194304, 0x8ecea2b5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c6.rom", 4194304, 0xd996a90a, 2097152, 2097152},
		{"wakuwak7", "225-c6.bin", 4194304, 0x0eb11a6d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c1.rom", 4194304, 0xaecd5bb1, 0, 2097152},
		{"whp", "090-c1.bin", 4194304, 0xcd30ed9b, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c2.rom", 4194304, 0x7566ffc0, 0, 2097152},
		{"whp", "090-c2.bin", 4194304, 0x10eed5ee, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c1.rom", 4194304, 0xaecd5bb1, 2097152, 2097152},
		{"whp", "090-c1.bin", 4194304, 0xcd30ed9b, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c2.rom", 4194304, 0x7566ffc0, 2097152, 2097152},
		{"whp", "090-c2.bin", 4194304, 0x10eed5ee, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wjammers", "windj_p1.rom", 524288, 0xe81e7a31, 0, 524288},
		{"wjammers", "065-p1.bin", 1048576, 0x6692c140, 0, 524288},
	},
	{
		FULL_COPY,
		{"wjammers", "windj_v4.rom", 524288, 0x3740edde, 0, 524288},
		{"wjammers", "065-v4.bin", 1048576, 0x5dee7963, 0, 524288},
	},
	{
		FULL_COPY,
		{"sonicwi2", "afig2_v2.rom", 524288, 0x6d0a728e, 0, 524288},
		{"sonicwi2", "075-v2.bin", 1048576, 0x021760cd, 0, 524288},
	},
	{
		FULL_COPY,
		{"breakrev", "brev_c5.rom", 2097152, 0x28ff1792, 0, 2097152},
		{"breakrev", "245-c5.bin", 4194304, 0xb5f40e7f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"breakrev", "brev_c6.rom", 2097152, 0x23c65644, 0, 2097152},
		{"breakrev", "245-c6.bin", 4194304, 0xd0337328, 0, 2097152},
	},
	{
		FULL_COPY,
		{"gururin", "gurin_m1.rom", 65536, 0x833cdf1b, 0, 65536},
		{"gururin", "067-m1.bin", 131072, 0xe777a234, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "maj_m1.rom", 65536, 0x37965a73, 0, 65536},
		{"mahretsu", "004-m1.bin", 131072, 0xc71fbb3b, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "maj_s1.rom", 65536, 0xb0d16529, 0, 65536},
		{"mahretsu", "004-s1.bin", 131072, 0x4e310702, 0, 65536},
	},
	{
		FULL_COPY,
		{"cyberlip", "cybl_m1.rom", 65536, 0x47980d3a, 0, 65536},
		{"cyberlip", "010-m1.bin", 131072, 0x8be3a078, 0, 65536},
	},
	{
		FULL_COPY,
		{"maglord", "magl_m1.rom", 65536, 0x91ee1f73, 0, 65536},
		{"maglord", "005-m1.bin", 262144, 0x26259f0f, 0, 65536},
	},
	{0}
};

struct Rom pasmulator_roms[] =
{
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd,    0, 2048},
		{"galaxian", "galmidw.u",   2048, 0x745e2d61,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd, 2048, 2048},
		{"galaxian", "galmidw.v",   2048, 0x9c999a40,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d,    0, 2048},
		{"galaxian", "galmidw.w",   2048, 0xb5894925,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d, 2048, 2048},
		{"galaxian", "galmidw.y",   2048, 0x6b3ca10b,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7l",	  4096, 0x952c6135,    0, 2048},
		{"galaxian", "7l",	  2048, 0x1b933207,    0, 2048},
	},
	{
		BLOCK_FILL,
		{"galaxian", "7l",	  4096, 0x952c6135, 2048, 2048},
		{"	", "  ",	     0, 0xffffffff,   0,     0},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816,    0, 4096},
		{"galap1",   "7f.bin",      4096, 0x4335b1de,    0, 4096},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 4096, 2048},
		{"galap1",   "galaxian.w",  2048, 0x4c7031c0,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 6144, 2048},
		{"galap1",   "galx_1_4.rom",2048, 0xe71e1d9e,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 8192, 2048},
		{"galap1",   "galx_1_5.rom",2048, 0x6e65a3b2,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea,    0, 2048},
		{"galap4",   "galnamco.u",  2048, 0xacfde501,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 2048, 2048},
		{"galap4",   "galnamco.v",  2048, 0x65cf3c77,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 4096, 2048},
		{"galap4",   "galnamco.w",  2048, 0x9eef9ae6,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 6144, 2048},
		{"galap4",   "galnamco.y",  2048, 0x56a5ddd1,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 8192, 2048},
		{"galap4",   "galnamco.z",  2048, 0xf4bc7262,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "galaxian.u",  2048, 0xe8f3aa67,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "galaxian.v",  2048, 0xf58283e3,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom galemu_roms[] =
{
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd,    0, 2048},
		{"galaxian", "galmidw.u",   2048, 0x745e2d61,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd, 2048, 2048},
		{"galaxian", "galmidw.v",   2048, 0x9c999a40,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d,    0, 2048},
		{"galaxian", "galmidw.w",   2048, 0xb5894925,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d, 2048, 2048},
		{"galaxian", "galmidw.y",   2048, 0x6b3ca10b,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7l",	  4096, 0x952c6135,    0, 2048},
		{"galaxian", "7l",	  2048, 0x1b933207,    0, 2048},
	},
	{
		BLOCK_FILL,
		{"galaxian", "7l",	  4096, 0x952c6135, 2048, 2048},
		{"	", "  ",	     0, 0xffffffff,   0,     0},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816,    0, 4096},
		{"galap1",   "7f.bin",      4096, 0x4335b1de,    0, 4096},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 4096, 2048},
		{"galap1",   "galaxian.w",  2048, 0x4c7031c0,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 6144, 2048},
		{"galap1",   "galx_1_4.rom",2048, 0xe71e1d9e,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 8192, 2048},
		{"galap1",   "galx_1_5.rom",2048, 0x6e65a3b2,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea,    0, 2048},
		{"galap4",   "galnamco.u",  2048, 0xacfde501,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 2048, 2048},
		{"galap4",   "galnamco.v",  2048, 0x65cf3c77,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 4096, 2048},
		{"galap4",   "galnamco.w",  2048, 0x9eef9ae6,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 6144, 2048},
		{"galap4",   "galnamco.y",  2048, 0x56a5ddd1,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 8192, 2048},
		{"galap4",   "galnamco.z",  2048, 0xf4bc7262,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "superg.u",    2048, 0xe8f3aa67,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "superg.v",    2048, 0xf58283e3,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{
		FULL_COPY,
		{"galaxb",   "cp1",	 2048, 0xe8f3aa67,    0, 2048},
		{"galaxiana", "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxb",   "cp2",	 2048, 0xf58283e3,    0, 2048},
		{"galaxiana", "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{
		FULL_COPY,
		{"galaxb",   "cp3",	 2048, 0x4c7031c0,    0, 2048},
		{"galaxiana", "7j.bin",      4096, 0x4e6f66a1,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxb",   "cp4",	 2048, 0x097d92a2,    0, 2048},
		{"galaxiana", "7j.bin",      4096, 0x4e6f66a1, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom sage_roms[] =
{
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816,    0, 4096},
		{"galap1",   "7f.bin",      4096, 0x4335b1de,    0, 4096},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 4096, 2048},
		{"galap1",   "galaxian.w",  2048, 0x4c7031c0,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 6144, 2048},
		{"galap1",   "galx_1_4.rom",2048, 0xe71e1d9e,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap1",   "galx_1.rom", 10240, 0xb22ee816, 8192, 2048},
		{"galap1",   "galx_1_5.rom",2048, 0x6e65a3b2,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea,    0, 2048},
		{"galap4",   "galnamco.u",  2048, 0xacfde501,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 2048, 2048},
		{"galap4",   "galnamco.v",  2048, 0x65cf3c77,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 4096, 2048},
		{"galap4",   "galnamco.w",  2048, 0x9eef9ae6,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 6144, 2048},
		{"galap4",   "galnamco.y",  2048, 0x56a5ddd1,    0, 2048},
	},
	{
		FULL_COPY,
		{"galap4",   "galx_4.rom", 10240, 0xe88a3eea, 8192, 2048},
		{"galap4",   "galnamco.z",  2048, 0xf4bc7262,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "galaxian.u",  2048, 0xe8f3aa67,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "galaxian.v",  2048, 0xf58283e3,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom grytra_roms[] =
{
	{
		COMBINE_EVEN,
		{"gryzor", "g-7.rom", 65536, 0x57f467d2, 0, 65536},
		{"contraj", "633e04.7d", 262144, 0x14ddc542, 0x00000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-7.rom", 65536, 0x57f467d2, 0, 65536},
		{"contraj", "633e05.7f", 262144, 0x42185044, 0x00000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-10.rom", 65536, 0xe6db9685, 0, 65536},
		{"contraj", "633e04.7d", 262144, 0x14ddc542, 0x08000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-10.rom", 65536, 0xe6db9685, 0, 65536},
		{"contraj", "633e05.7f", 262144, 0x42185044, 0x08000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-9.rom", 65536, 0x875c61de, 0, 65536},
		{"contraj", "633e04.7d", 262144, 0x14ddc542, 0x10000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-9.rom", 65536, 0x875c61de, 0, 65536},
		{"contraj", "633e05.7f", 262144, 0x42185044, 0x10000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-8.rom", 65536, 0x642765d6, 0, 65536},
		{"contraj", "633e04.7d", 262144, 0x14ddc542, 0x18000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-8.rom", 65536, 0x642765d6, 0, 65536},
		{"contraj", "633e05.7f", 262144, 0x42185044, 0x18000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-15.rom", 65536, 0xdaa2324b, 0, 65536},
		{"contraj", "633e04.7d", 262144, 0x14ddc542, 0x20000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-15.rom", 65536, 0xdaa2324b, 0, 65536},
		{"contraj", "633e05.7f", 262144, 0x42185044, 0x20000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-16.rom", 65536, 0xe27cc835, 0, 65536},
		{"contraj", "633e04.7d", 262144, 0x14ddc542, 0x28000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-16.rom", 65536, 0xe27cc835, 0, 65536},
		{"contraj", "633e05.7f", 262144, 0x42185044, 0x28000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-17.rom", 65536, 0xce4330b9, 0x00000, 65536},
		{"contraj", "633e04.7d", 262144, 0x14ddc542, 0x30000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-17.rom", 65536, 0xce4330b9, 0, 65536},
		{"contraj", "633e05.7f", 262144, 0x42185044, 0x30000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-18.rom", 65536, 0x1571ce42, 0, 65536},
		{"contraj", "633e04.7d", 262144, 0x14ddc542, 0x38000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-18.rom", 65536, 0x1571ce42, 0, 65536},
		{"contraj", "633e05.7f", 262144, 0x42185044, 0x38000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-4.rom", 65536, 0x2cc7e52c, 0, 65536},
		{"contraj", "633e06.16d", 262144, 0x9cf6faae, 0x00000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-4.rom", 65536, 0x2cc7e52c, 0, 65536},
		{"contraj", "633e07.16f", 262144, 0xf2d06638, 0x00000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-5.rom", 65536, 0xe01a5b9c, 0, 65536},
		{"contraj", "633e06.16d", 262144, 0x9cf6faae, 0x08000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-5.rom", 65536, 0xe01a5b9c, 0, 65536},
		{"contraj", "633e07.16f", 262144, 0xf2d06638, 0x08000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-6.rom", 65536, 0xaeea6744, 0, 65536},
		{"contraj", "633e06.16d", 262144, 0x9cf6faae, 0x10000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-6.rom", 65536, 0xaeea6744, 0, 65536},
		{"contraj", "633e07.16f", 262144, 0xf2d06638, 0x10000, 32768},
	},
	// g-14.rom was slightly different in the original set. Last 8k is now empty (all 0xff)
	{
		COMBINE_EVEN,
		{"gryzor", "g-14.rom", 65536, 0x765afdc7, 0, 65536},
		{"contraj", "633e06.16d", 262144, 0x9cf6faae, 0x18000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-14.rom", 65536, 0x765afdc7, 0, 65536},
		{"contraj", "633e07.16f", 262144, 0xf2d06638, 0x18000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-11.rom", 65536, 0xbd9ba92c, 0, 65536},
		{"contraj", "633e06.16d", 262144, 0x9cf6faae, 0x20000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-11.rom", 65536, 0xbd9ba92c, 0, 65536},
		{"contraj", "633e07.16f", 262144, 0xf2d06638, 0x20000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-12.rom", 65536, 0xd0be7ec2, 0, 65536},
		{"contraj", "633e06.16d", 262144, 0x9cf6faae, 0x28000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-12.rom", 65536, 0xd0be7ec2, 0, 65536},
		{"contraj", "633e07.16f", 262144, 0xf2d06638, 0x28000, 32768},
	},
	{
		COMBINE_EVEN,
		{"gryzor", "g-13.rom", 65536, 0x2b513d12, 0, 65536},
		{"contraj", "633e06.16d", 262144, 0x9cf6faae, 0x30000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-13.rom", 65536, 0x2b513d12, 0, 65536},
		{"contraj", "633e07.16f", 262144, 0xf2d06638, 0x30000, 32768},
	},
	// This ROM isn't needed by Gryzor (never really existed ;)
	{
		COMBINE_EVEN,
		{"gryzor", "g-19.rom", 65536, 0xdeab7e4e, 0, 65536},
		{"contraj", "633e06.16d", 262144, 0x9cf6faae, 0x38000, 32768},
	},
	{
		COMBINE_ODD,
		{"gryzor", "g-19.rom", 65536, 0xdeab7e4e, 0, 65536},
		{"contraj", "633e07.16f", 262144, 0xf2d06638, 0x38000, 32768},
	},
	{0}
};

struct Rom s11emu_roms[] =
{
	/* I do not recall when these were removed from MAME
	{
		EVEN_COPY,
		{"tk2b", "wavebh", 2097152, 0x344c0c89, 0, 2097152},
		{"tekken2a", "tes1wavb.8k", 4194304, 0xbee9a7e6, 0, 2097152},
	},
	{
		ODD_COPY,
		{"tk2b", "wavebl", 2097152, 0x4b8c5195, 0, 2097152},
		{"tekken2a", "tes1wavb.8k", 4194304, 0xbee9a7e6, 0, 2097152},
	},*/
	{0}
};

struct Rom callus_roms[] =
{
	{
		EVEN_COPY,
		{"1941j", "4109.bin", 131072, 0xbe1b6bc2, 0, 131072},
		{"1941j", "41_gfx5.rom", 524288, 0x01d1cb11, 0, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4113.bin", 131072, 0x2e06d0ec, 0, 131072},
		{"1941j", "41_gfx7.rom", 524288, 0xaeaa3509, 0, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4124.bin", 131072, 0x5aa43cee, 0, 131072},
		{"1941j", "41_gfx1.rom", 524288, 0xff77985a, 0, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4138.bin", 131072, 0x8889c0aa, 0, 131072},
		{"1941j", "41_gfx3.rom", 524288, 0x983be58f, 0, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4140.bin", 131072, 0x3979837d, 0, 131072},
		{"1941j", "41_32.rom", 524288, 0x4e9648ca, 0, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4101.bin", 131072, 0xd8946fc1, 0, 131072},
		{"1941j", "41_gfx5.rom", 524288, 0x01d1cb11, 0, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4105.bin", 131072, 0xd8ba28e0, 0, 131072},
		{"1941j", "41_gfx7.rom", 524288, 0xaeaa3509, 0, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4117.bin", 131072, 0xbbeff902, 0, 131072},
		{"1941j", "41_gfx1.rom", 524288, 0xff77985a, 0, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4132.bin", 131072, 0xf0168249, 0, 131072},
		{"1941j", "41_gfx3.rom", 524288, 0x983be58f, 0, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4134.bin", 131072, 0xb5f341ec, 0, 131072},
		{"1941j", "41_32.rom", 524288, 0x4e9648ca, 0, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4110.bin", 131072, 0xb7eb6a6d, 0, 131072},
		{"1941j", "41_gfx5.rom", 524288, 0x01d1cb11, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4114.bin", 131072, 0x5a33f676, 0, 131072},
		{"1941j", "41_gfx7.rom", 524288, 0xaeaa3509, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4125.bin", 131072, 0x94add360, 0, 131072},
		{"1941j", "41_gfx1.rom", 524288, 0xff77985a, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4139.bin", 131072, 0x5b5c3949, 0, 131072},
		{"1941j", "41_gfx3.rom", 524288, 0x983be58f, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"1941j", "4141.bin", 131072, 0x57496819, 0, 131072},
		{"1941j", "41_32.rom", 524288, 0x4e9648ca, 262144, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4102.bin", 131072, 0x802e8153, 0, 131072},
		{"1941j", "41_gfx5.rom", 524288, 0x01d1cb11, 262144, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4106.bin", 131072, 0x4e53650b, 0, 131072},
		{"1941j", "41_gfx7.rom", 524288, 0xaeaa3509, 262144, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4118.bin", 131072, 0xa5e1c1f3, 0, 131072},
		{"1941j", "41_gfx1.rom", 524288, 0xff77985a, 262144, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4133.bin", 131072, 0x7a31b0e2, 0, 131072},
		{"1941j", "41_gfx3.rom", 524288, 0x983be58f, 262144, 131072},
	},
	{
		ODD_COPY,
		{"1941j", "4135.bin", 131072, 0x95cc979a, 0, 131072},
		{"1941j", "41_32.rom", 524288, 0x4e9648ca, 262144, 131072},
	},
	{
		FULL_COPY,
		{"striderj", "sth09.bin", 131072, 0x4769272a, 0, 65536},
		{"striderj", "sth23.bin", 65536, 0x2ed403bc, 0, 65536},
	},
	{
		BLOCK_FILL,
		{"striderj", "sth09.bin", 131072, 0x4769272a, 65536, 65536},
		{"	", "	 ", 65536, 0xffffffff, 0, 65536},
	},
	{
		EVEN_COPY,
		{"willowj", "wl09.bin", 131072, 0x05aa71b4, 0, 131072},
		{"willowj", "wl_gfx5.rom", 524288, 0xafa74b73, 0, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl13.bin", 131072, 0x1f7c87cd, 0, 131072},
		{"willowj", "wl_gfx7.rom", 524288, 0x12a0dc0b, 0, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl24.bin", 131072, 0xd9d73ba1, 0, 131072},
		{"willowj", "wl_gfx1.rom", 524288, 0xc6f2abce, 0, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl38.bin", 131072, 0xf6f9111b, 0, 131072},
		{"willowj", "wl_gfx3.rom", 524288, 0x4aa4c6d3, 0, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl40.bin", 131072, 0xc7a0ed21, 0, 131072},
		{"willowj", "wl_32.rom", 524288, 0xdfd9f643, 0, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl05.bin", 131072, 0xf5254bf2, 0, 131072},
		{"willowj", "wl_gfx7.rom", 524288, 0x12a0dc0b, 0, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl17.bin", 131072, 0xa652f30c, 0, 131072},
		{"willowj", "wl_gfx1.rom", 524288, 0xc6f2abce, 0, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl32.bin", 131072, 0x10f64027, 0, 131072},
		{"willowj", "wl_gfx3.rom", 524288, 0x4aa4c6d3, 0, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl34.bin", 131072, 0x23a84f7a, 0, 131072},
		{"willowj", "wl_32.rom", 524288, 0xdfd9f643, 0, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl01.bin", 131072, 0x08c2df12, 0, 131072},
		{"willowj", "wl_gfx5.rom", 524288, 0xafa74b73, 0, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl10.bin", 131072, 0xdbba0a3f, 0, 131072},
		{"willowj", "wl_gfx5.rom", 524288, 0xafa74b73, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl14.bin", 131072, 0x7d5798b2, 0, 131072},
		{"willowj", "wl_gfx7.rom", 524288, 0x12a0dc0b, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl25.bin", 131072, 0x857d17d2, 0, 131072},
		{"willowj", "wl_gfx1.rom", 524288, 0xc6f2abce, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl39.bin", 131072, 0xe6fce9b0, 0, 131072},
		{"willowj", "wl_gfx3.rom", 524288, 0x4aa4c6d3, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"willowj", "wl41.bin", 131072, 0x8d6477a3, 0, 131072},
		{"willowj", "wl_32.rom", 524288, 0xdfd9f643, 262144, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl02.bin", 131072, 0x86fba7a5, 0, 131072},
		{"willowj", "wl_gfx5.rom", 524288, 0xafa74b73, 262144, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl06.bin", 131072, 0x1f052948, 0, 131072},
		{"willowj", "wl_gfx7.rom", 524288, 0x12a0dc0b, 262144, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl18.bin", 131072, 0x316c7fbc, 0, 131072},
		{"willowj", "wl_gfx1.rom", 524288, 0xc6f2abce, 262144, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl33.bin", 131072, 0xa15d5517, 0, 131072},
		{"willowj", "wl_gfx3.rom", 524288, 0x4aa4c6d3, 262144, 131072},
	},
	{
		ODD_COPY,
		{"willowj", "wl35.bin", 131072, 0x5eff7951, 0, 131072},
		{"willowj", "wl_32.rom", 524288, 0xdfd9f643, 262144, 131072},
	},
	/* Commented out whilst doing the CAESAR update for MAME v0.128
	{
		EVEN_COPY,
		{"area88", "ar09.bin", 131072, 0xdb9376f8, 0, 131072},
		{"area88", "unsquad.05", 524288, 0xbf4575d8, 0, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar13.bin", 131072, 0x81436481, 0, 131072},
		{"area88", "unsquad.07", 524288, 0xa02945f4, 0, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar24.bin", 131072, 0x9cd6e2a3, 0, 131072},
		{"area88", "unsquad.01", 524288, 0x5965ca8d, 0, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar38.bin", 131072, 0x8b9e75b9, 0, 131072},
		{"area88", "unsquad.03", 524288, 0xac6db17d, 0, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar40.bin", 131072, 0xbe36c145, 0, 131072},
		{"area88", "unsquad.32", 524288, 0xae1d7fb0, 0, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar01.bin", 131072, 0x392151b4, 0, 131072},
		{"area88", "unsquad.05", 524288, 0xbf4575d8, 0, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar05.bin", 131072, 0xe246ed9f, 0, 131072},
		{"area88", "unsquad.07", 524288, 0xa02945f4, 0, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar17.bin", 131072, 0x0b8e0df4, 0, 131072},
		{"area88", "unsquad.01", 524288, 0x5965ca8d, 0, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar32.bin", 131072, 0xdb6acdcf, 0, 131072},
		{"area88", "unsquad.03", 524288, 0xac6db17d, 0, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar34.bin", 131072, 0xf6e80386, 0, 131072},
		{"area88", "unsquad.32", 524288, 0xae1d7fb0, 0, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar10.bin", 131072, 0x4219b622, 0, 131072},
		{"area88", "unsquad.05", 524288, 0xbf4575d8, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar14.bin", 131072, 0xe6bae179, 0, 131072},
		{"area88", "unsquad.07", 524288, 0xa02945f4, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar25.bin", 131072, 0x15ccf981, 0, 131072},
		{"area88", "unsquad.01", 524288, 0x5965ca8d, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar39.bin", 131072, 0x9b8e1363, 0, 131072},
		{"area88", "unsquad.03", 524288, 0xac6db17d, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"area88", "ar41.bin", 131072, 0x758893d3, 0, 131072},
		{"area88", "unsquad.32", 524288, 0xae1d7fb0, 262144, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar02.bin", 131072, 0xbac5dec5, 0, 131072},
		{"area88", "unsquad.05", 524288, 0xbf4575d8, 262144, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar06.bin", 131072, 0xc8f04223, 0, 131072},
		{"area88", "unsquad.07", 524288, 0xa02945f4, 262144, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar18.bin", 131072, 0x9336db6a, 0, 131072},
		{"area88", "unsquad.01", 524288, 0x5965ca8d, 262144, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar33.bin", 131072, 0x3968f4b5, 0, 131072},
		{"area88", "unsquad.03", 524288, 0xac6db17d, 262144, 131072},
	},
	{
		ODD_COPY,
		{"area88", "ar35.bin", 131072, 0x86d98ff3, 0, 131072},
		{"area88", "unsquad.32", 524288, 0xae1d7fb0, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch09.bin", 131072, 0x567ab3ca, 0, 131072},
		{"chikij", "ch_gfx5.rom", 524288, 0x4ec75f15, 0, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch13.bin", 131072, 0x12a7a8ba, 0, 131072},
		{"chikij", "ch_gfx7.rom", 524288, 0xd85d00d6, 0, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch24.bin", 131072, 0x9cb6e6bc, 0, 131072},
		{"chikij", "ch_gfx1.rom", 524288, 0xf33ca9d4, 0, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch38.bin", 131072, 0x6e5c8cb6, 0, 131072},
		{"chikij", "ch_gfx3.rom", 524288, 0x0ba2047f, 0, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch40.bin", 131072, 0xbe0d8301, 0, 131072},
		{"chikij", "ch_32.rom", 524288, 0x9b70bd41, 0, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch01.bin", 131072, 0x7f3b7b56, 0, 131072},
		{"chikij", "ch_gfx5.rom", 524288, 0x4ec75f15, 0, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch05.bin", 131072, 0x6c1afb9a, 0, 131072},
		{"chikij", "ch_gfx7.rom", 524288, 0xd85d00d6, 0, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch17.bin", 131072, 0xfe490846, 0, 131072},
		{"chikij", "ch_gfx1.rom", 524288, 0xf33ca9d4, 0, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch32.bin", 131072, 0x317d27b0, 0, 131072},
		{"chikij", "ch_gfx3.rom", 524288, 0x0ba2047f, 0, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch34.bin", 131072, 0x609ed2f9, 0, 131072},
		{"chikij", "ch_32.rom", 524288, 0x9b70bd41, 0, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch10.bin", 131072, 0xe8251a9b, 0, 131072},
		{"chikij", "ch_gfx5.rom", 524288, 0x4ec75f15, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch14.bin", 131072, 0x4012ec4b, 0, 131072},
		{"chikij", "ch_gfx7.rom", 524288, 0xd85d00d6, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch25.bin", 131072, 0x1dfcbac5, 0, 131072},
		{"chikij", "ch_gfx1.rom", 524288, 0xf33ca9d4, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch39.bin", 131072, 0x872fb2a4, 0, 131072},
		{"chikij", "ch_gfx3.rom", 524288, 0x0ba2047f, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"chikij", "ch41.bin", 131072, 0x8ad96155, 0, 131072},
		{"chikij", "ch_32.rom", 524288, 0x9b70bd41, 262144, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch02.bin", 131072, 0x7c8c88fb, 0, 131072},
		{"chikij", "ch_gfx5.rom", 524288, 0x4ec75f15, 262144, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch06.bin", 131072, 0x81884b2b, 0, 131072},
		{"chikij", "ch_gfx7.rom", 524288, 0xd85d00d6, 262144, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch18.bin", 131072, 0x516a34d1, 0, 131072},
		{"chikij", "ch_gfx1.rom", 524288, 0xf33ca9d4, 262144, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch33.bin", 131072, 0x30dc5ded, 0, 131072},
		{"chikij", "ch_gfx3.rom", 524288, 0x0ba2047f, 262144, 131072},
	},
	{
		ODD_COPY,
		{"chikij", "ch35.bin", 131072, 0xb810867f, 0, 131072},
		{"chikij", "ch_32.rom", 524288, 0x9b70bd41, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"ffightj", "ff40.bin", 131072, 0x8075bab9, 0, 131072},
		{"ffightj", "ff32-32m.bin", 524288, 0xc747696e, 0, 131072},
	},
	{
		ODD_COPY,
		{"ffightj", "ff34.bin", 131072, 0x0c8dc3fc, 0, 131072},
		{"ffightj", "ff32-32m.bin", 524288, 0xc747696e, 0, 131072},
	},
	{
		EVEN_COPY,
		{"ffightj", "ff41.bin", 131072, 0x2af68154, 0, 131072},
		{"ffightj", "ff32-32m.bin", 524288, 0xc747696e, 262144, 131072},
	},
	{
		ODD_COPY,
		{"ffightj", "ff35.bin", 131072, 0x4a934121, 0, 131072},
		{"ffightj", "ff32-32m.bin", 524288, 0xc747696e, 262144, 131072},
	},
	*/
	{
		EVEN_COPY,
		{"knightsj", "krj35.bin", 131072, 0x1172806d, 0, 131072},
		{"knightsj", "kr_22.rom", 524288, 0xd0b671a9, 0, 131072},
	},
	{
		ODD_COPY,
		{"knightsj", "krj28.bin", 131072, 0xfe6eb08d, 0, 131072},
		{"knightsj", "kr_22.rom", 524288, 0xd0b671a9, 0, 131072},
	},
	{
		EVEN_COPY,
		{"knightsj", "krj36.bin", 131072, 0xeb52e78d, 0, 131072},
		{"knightsj", "kr_22.rom", 524288, 0xd0b671a9, 262144, 131072},
	},
	{
		ODD_COPY,
		{"knightsj", "krj29.bin", 131072, 0xf854b020, 0, 131072},
		{"knightsj", "kr_22.rom", 524288, 0xd0b671a9, 262144, 131072},
	},
	/* Commented out whilst doing the CAESAR update for MAME v0.128
	{
		EVEN_COPY,
		{"mercsj", "so2_09.bin", 131072, 0x690c261d, 0, 131072},
		{"mercsj", "so2_gfx6.rom", 524288, 0xaa6102af, 0, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_13.bin", 131072, 0xb5e48282, 0, 131072},
		{"mercsj", "so2_gfx8.rom", 524288, 0x839e6869, 0, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_24.bin", 131072, 0x78b6f0cb, 0, 131072},
		{"mercsj", "so2_gfx2.rom", 524288, 0x597c2875, 0, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_38.bin", 131072, 0x0010a9a2, 0, 131072},
		{"mercsj", "so2_gfx4.rom", 524288, 0x912a9ca0, 0, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_40.bin", 131072, 0xde37771c, 0, 131072},
		{"mercsj", "so2_32.rom", 524288, 0x2eb5cf0c, 0, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_05.bin", 131072, 0x54bed82c, 0, 131072},
		{"mercsj", "so2_gfx8.rom", 524288, 0x839e6869, 0, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_17.bin", 131072, 0xe78bb308, 0, 131072},
		{"mercsj", "so2_gfx2.rom", 524288, 0x597c2875, 0, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_32.bin", 131072, 0x75dffc9a, 0, 131072},
		{"mercsj", "so2_gfx4.rom", 524288, 0x912a9ca0, 0, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_34.bin", 131072, 0xb8dae95f, 0, 131072},
		{"mercsj", "so2_32.rom", 524288, 0x2eb5cf0c, 0, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_01.bin", 131072, 0x31fd2715, 0, 131072},
		{"mercsj", "so2_gfx6.rom", 524288, 0xaa6102af, 0, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_10.bin", 131072, 0x2f871714, 0, 131072},
		{"mercsj", "so2_gfx6.rom", 524288, 0xaa6102af, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_14.bin", 131072, 0x737a744b, 0, 131072},
		{"mercsj", "so2_gfx8.rom", 524288, 0x839e6869, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_25.bin", 131072, 0x6d0e05d6, 0, 131072},
		{"mercsj", "so2_gfx2.rom", 524288, 0x597c2875, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_39.bin", 131072, 0xd52ba336, 0, 131072},
		{"mercsj", "so2_gfx4.rom", 524288, 0x912a9ca0, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"mercsj", "so2_41.bin", 131072, 0x914f85e0, 0, 131072},
		{"mercsj", "so2_32.rom", 524288, 0x2eb5cf0c, 262144, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_02.bin", 131072, 0xb4b2a0b7, 0, 131072},
		{"mercsj", "so2_gfx6.rom", 524288, 0xaa6102af, 262144, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_06.bin", 131072, 0x9d756f51, 0, 131072},
		{"mercsj", "so2_gfx8.rom", 524288, 0x839e6869, 262144, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_18.bin", 131072, 0x96f61f4e, 0, 131072},
		{"mercsj", "so2_gfx2.rom", 524288, 0x597c2875, 262144, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_33.bin", 131072, 0x39b90d25, 0, 131072},
		{"mercsj", "so2_gfx4.rom", 524288, 0x912a9ca0, 262144, 131072},
	},
	{
		ODD_COPY,
		{"mercsj", "so2_35.bin", 131072, 0x7d24394d, 0, 131072},
		{"mercsj", "so2_32.rom", 524288, 0x2eb5cf0c, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm09.bin", 131072, 0x9d60d286, 0, 131072},
		{"nemoj", "nm_gfx5.rom", 524288, 0x487b8747, 0, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm13.bin", 131072, 0xa4909fe0, 0, 131072},
		{"nemoj", "nm_gfx7.rom", 524288, 0x203dc8c6, 0, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm24.bin", 131072, 0x3312c648, 0, 131072},
		{"nemoj", "nm_gfx1.rom", 524288, 0x9e878024, 0, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm38.bin", 131072, 0xae98a997, 0, 131072},
		{"nemoj", "nm_gfx3.rom", 524288, 0xbb01e6b6, 0, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm40.bin", 131072, 0x8a4099f3, 0, 131072},
		{"nemoj", "nm_32.rom", 524288, 0xd6d1add3, 0, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm01.bin", 131072, 0x8a83f7c4, 0, 131072},
		{"nemoj", "nm_gfx5.rom", 524288, 0x487b8747, 0, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm05.bin", 131072, 0x16db1e61, 0, 131072},
		{"nemoj", "nm_gfx7.rom", 524288, 0x203dc8c6, 0, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm17.bin", 131072, 0xccfc50e2, 0, 131072},
		{"nemoj", "nm_gfx1.rom", 524288, 0x9e878024, 0, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm32.bin", 131072, 0xb3704dde, 0, 131072},
		{"nemoj", "nm_gfx3.rom", 524288, 0xbb01e6b6, 0, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm34.bin", 131072, 0x5737feed, 0, 131072},
		{"nemoj", "nm_32.rom", 524288, 0xd6d1add3, 0, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm10.bin", 131072, 0x33c1388c, 0, 131072},
		{"nemoj", "nm_gfx5.rom", 524288, 0x487b8747, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm14.bin", 131072, 0x66612270, 0, 131072},
		{"nemoj", "nm_gfx7.rom", 524288, 0x203dc8c6, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm25.bin", 131072, 0xacfc84d2, 0, 131072},
		{"nemoj", "nm_gfx1.rom", 524288, 0x9e878024, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm39.bin", 131072, 0x6a274ecd, 0, 131072},
		{"nemoj", "nm_gfx3.rom", 524288, 0xbb01e6b6, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"nemoj", "nm41.bin", 131072, 0x6309603d, 0, 131072},
		{"nemoj", "nm_32.rom", 524288, 0xd6d1add3, 262144, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm02.bin", 131072, 0x84c69469, 0, 131072},
		{"nemoj", "nm_gfx5.rom", 524288, 0x487b8747, 262144, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm06.bin", 131072, 0x8b9bcf95, 0, 131072},
		{"nemoj", "nm_gfx7.rom", 524288, 0x203dc8c6, 262144, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm18.bin", 131072, 0x4347deed, 0, 131072},
		{"nemoj", "nm_gfx1.rom", 524288, 0x9e878024, 262144, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm33.bin", 131072, 0xc469dc74, 0, 131072},
		{"nemoj", "nm_gfx3.rom", 524288, 0xbb01e6b6, 262144, 131072},
	},
	{
		ODD_COPY,
		{"nemoj", "nm35.bin", 131072, 0xbd11a7f8, 0, 131072},
		{"nemoj", "nm_32.rom", 524288, 0xd6d1add3, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"varthj", "va09.bin", 131072, 0x183dfaa8, 0, 131072},
		{"varthj", "va_gfx5.rom", 524288, 0xb1fb726e, 0, 131072},
	},
	{
		EVEN_COPY,
		{"varthj", "va13.bin", 131072, 0x45537e69, 0, 131072},
		{"varthj", "va_gfx7.rom", 524288, 0x4c6588cd, 0, 131072},
	},
	{
		EVEN_COPY,
		{"varthj", "va24.bin", 131072, 0x57191ccf, 0, 131072},
		{"varthj", "va_gfx1.rom", 524288, 0x0b1ace37, 0, 131072},
	},
	{
		EVEN_COPY,
		{"varthj", "va38.bin", 131072, 0xe117a17e, 0, 131072},
		{"varthj", "va_gfx3.rom", 524288, 0x44dfe706, 0, 131072},
	},
	{
		ODD_COPY,
		{"varthj", "va01.bin", 131072, 0xc41312b5, 0, 131072},
		{"varthj", "va_gfx5.rom", 524288, 0xb1fb726e, 0, 131072},
	},
	{
		ODD_COPY,
		{"varthj", "va05.bin", 131072, 0x7065d4e9, 0, 131072},
		{"varthj", "va_gfx7.rom", 524288, 0x4c6588cd, 0, 131072},
	},
	{
		ODD_COPY,
		{"varthj", "va17.bin", 131072, 0x054f5a5b, 0, 131072},
		{"varthj", "va_gfx1.rom", 524288, 0x0b1ace37, 0, 131072},
	},
	{
		ODD_COPY,
		{"varthj", "va32.bin", 131072, 0x3b4f40b2, 0, 131072},
		{"varthj", "va_gfx3.rom", 524288, 0x44dfe706, 0, 131072},
	},
	{
		EVEN_COPY,
		{"varthj", "va10.bin", 131072, 0xd62750cd, 0, 131072},
		{"varthj", "va_gfx5.rom", 524288, 0xb1fb726e, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"varthj", "va14.bin", 131072, 0xdc2f4783, 0, 131072},
		{"varthj", "va_gfx7.rom", 524288, 0x4c6588cd, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"varthj", "va25.bin", 131072, 0x51d90690, 0, 131072},
		{"varthj", "va_gfx1.rom", 524288, 0x0b1ace37, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"varthj", "va39.bin", 131072, 0xb0b12f51, 0, 131072},
		{"varthj", "va_gfx3.rom", 524288, 0x44dfe706, 262144, 131072},
	},
	{
		ODD_COPY,
		{"varthj", "va02.bin", 131072, 0x11590325, 0, 131072},
		{"varthj", "va_gfx5.rom", 524288, 0xb1fb726e, 262144, 131072},
	},
	{
		ODD_COPY,
		{"varthj", "va06.bin", 131072, 0x06e833ac, 0, 131072},
		{"varthj", "va_gfx7.rom", 524288, 0x4c6588cd, 262144, 131072},
	},
	{
		ODD_COPY,
		{"varthj", "va18.bin", 131072, 0xa17817c0, 0, 131072},
		{"varthj", "va_gfx1.rom", 524288, 0x0b1ace37, 262144, 131072},
	},
	{
		ODD_COPY,
		{"varthj", "va33.bin", 131072, 0x4b003af7, 0, 131072},
		{"varthj", "va_gfx3.rom", 524288, 0x44dfe706, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt09.bin", 131072, 0x2c40e480, 0, 131072},
		{"wonder3", "3wonders.05", 524288, 0x86aef804, 0, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt11.bin", 131072, 0x04f3c298, 0, 131072},
		{"wonder3", "3wonders.06", 524288, 0x13cb0e7c, 0, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt13.bin", 131072, 0x51009117, 0, 131072},
		{"wonder3", "3wonders.07", 524288, 0x4f057110, 0, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt15.bin", 131072, 0xb6aba565, 0, 131072},
		{"wonder3", "3wonders.08", 524288, 0x1f055014, 0, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt24.bin", 131072, 0xee4484ce, 0, 131072},
		{"wonder3", "3wonders.01", 524288, 0x902489d0, 0, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt26.bin", 131072, 0x532f542e, 0, 131072},
		{"wonder3", "3wonders.02", 524288, 0xe9a034f4, 0, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt28.bin", 131072, 0x6064e499, 0, 131072},
		{"wonder3", "3wonders.04", 524288, 0xdf0eea8b, 0, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt38.bin", 131072, 0xb2940c2d, 0, 131072},
		{"wonder3", "3wonders.03", 524288, 0xe35ce720, 0, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt03.bin", 131072, 0x98087e08, 0, 131072},
		{"wonder3", "3wonders.06", 524288, 0x13cb0e7c, 0, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt05.bin", 131072, 0x283fd470, 0, 131072},
		{"wonder3", "3wonders.07", 524288, 0x4f057110, 0, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt07.bin", 131072, 0xc62defa1, 0, 131072},
		{"wonder3", "3wonders.08", 524288, 0x1f055014, 0, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt17.bin", 131072, 0xe5dcddeb, 0, 131072},
		{"wonder3", "3wonders.01", 524288, 0x902489d0, 0, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt19.bin", 131072, 0x1f0f72bd, 0, 131072},
		{"wonder3", "3wonders.02", 524288, 0xe9a034f4, 0, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt21.bin", 131072, 0x20012ddc, 0, 131072},
		{"wonder3", "3wonders.04", 524288, 0xdf0eea8b, 0, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt32.bin", 131072, 0x08e2b758, 0, 131072},
		{"wonder3", "3wonders.03", 524288, 0xe35ce720, 0, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt01.bin", 131072, 0x3e11f8cd, 0, 131072},
		{"wonder3", "3wonders.05", 524288, 0x86aef804, 0, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt10.bin", 131072, 0xe3f3ff94, 0, 131072},
		{"wonder3", "3wonders.05", 524288, 0x86aef804, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt12.bin", 131072, 0xe54664cc, 0, 131072},
		{"wonder3", "3wonders.06", 524288, 0x13cb0e7c, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt14.bin", 131072, 0x5c546d9a, 0, 131072},
		{"wonder3", "3wonders.07", 524288, 0x4f057110, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt16.bin", 131072, 0x37c96cfc, 0, 131072},
		{"wonder3", "3wonders.08", 524288, 0x1f055014, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt25.bin", 131072, 0x11b28831, 0, 131072},
		{"wonder3", "3wonders.01", 524288, 0x902489d0, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt27.bin", 131072, 0xec6edc0f, 0, 131072},
		{"wonder3", "3wonders.02", 524288, 0xe9a034f4, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt29.bin", 131072, 0x8fa77f9f, 0, 131072},
		{"wonder3", "3wonders.04", 524288, 0xdf0eea8b, 262144, 131072},
	},
	{
		EVEN_COPY,
		{"wonder3", "rt39.bin", 131072, 0xea7ac9ee, 0, 131072},
		{"wonder3", "3wonders.03", 524288, 0xe35ce720, 262144, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt02.bin", 131072, 0xfcffd73c, 0, 131072},
		{"wonder3", "3wonders.05", 524288, 0x86aef804, 262144, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt04.bin", 131072, 0x4d7b9a1a, 0, 131072},
		{"wonder3", "3wonders.06", 524288, 0x13cb0e7c, 262144, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt06.bin", 131072, 0xd9650bc4, 0, 131072},
		{"wonder3", "3wonders.07", 524288, 0x4f057110, 262144, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt08.bin", 131072, 0x75f4975b, 0, 131072},
		{"wonder3", "3wonders.08", 524288, 0x1f055014, 262144, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt18.bin", 131072, 0xce1afb7c, 0, 131072},
		{"wonder3", "3wonders.01", 524288, 0x902489d0, 262144, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt20.bin", 131072, 0x4fe52659, 0, 131072},
		{"wonder3", "3wonders.02", 524288, 0xe9a034f4, 262144, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt22.bin", 131072, 0x228a0d4a, 0, 131072},
		{"wonder3", "3wonders.04", 524288, 0xdf0eea8b, 262144, 131072},
	},
	{
		ODD_COPY,
		{"wonder3", "rt33.bin", 131072, 0xd6a99384, 0, 131072},
		{"wonder3", "3wonders.03", 524288, 0xe35ce720, 262144, 131072},
	},
	*/
	{0}
};

struct Rom jff_roms[] =
{
	{
		FULL_COPY,
		{"psychic5", "p5a", 65536, 0x25bb04e4,     0, 32768},
		{"psychic5", "p5a", 32768, 0x50060ecd,     0, 32768},
	},
	{
		FULL_COPY,
		{"psychic5", "p5a", 65536, 0x25bb04e4, 32768, 32768},
		{"psychic5", "p5a", 32768, 0x50060ecd,     0, 32768},
	},
	{0}
};

struct Rom hive_roms[] =
{
	{
		FULL_COPY,
		{"todruaga", "todruaga.pr3", 256, 0x5bcec186, 0, 256},
		{"todruagao", "td1-7.5k", 1024, 0xa86c74dd, 0, 256},
	},
	{
		FULL_COPY,
		{"todruaga", "todruaga.pr4", 256, 0xf029e5f5, 0, 256},
		{"todruagao", "td1-7.5k", 1024, 0xa86c74dd, 256, 256},
	},
	{
		FULL_COPY,
		{"todruaga", "todruaga.pr5", 256, 0xecdc206c, 0, 256},
		{"todruagao", "td1-7.5k", 1024, 0xa86c74dd, 512, 256},
	},
	{
		FULL_COPY,
		{"todruaga", "todruaga.pr6", 256, 0x57b5ad6d, 0, 256},
		{"todruagao", "td1-7.5k", 1024, 0xa86c74dd, 768, 256},
	},
	{
		FULL_COPY,
		{"xevious",   "xe-1l-a.bin", 8192, 0xbd74609a,    0, 4096},
		{"xevious",   "xvi_3.2m",    4096, 0x79754b7d,    0, 4096},
	},
	{
		FULL_COPY,
		{"xevious",   "xe-1l-a.bin", 8192, 0xbd74609a, 4096, 4096},
		{"xevious",   "xvi_4.2l",    4096, 0xc7d4bbf0,    0, 4096},
	},
	{
		FULL_COPY,
		{"xevious",   "xe-1m-a.bin", 8192, 0x92fa6cae,    0, 4096},
		{"xevious",   "xvi_1.3p",    4096, 0x09964dda,    0, 4096},
	},
	{
		FULL_COPY,
		{"xevious",   "xe-1m-a.bin", 8192, 0x92fa6cae, 4096, 4096},
		{"xevious",   "xvi_2.3m",    4096, 0x60ecce84,    0, 4096},
	},
	{
		FULL_COPY,
		{"xevious",   "xe-4c-a.bin", 8192, 0x0ede5706,    0, 4096},
		{"xevious",   "xvi_5.3f",    4096, 0xc85b703f,    0, 4096},
	},
	{
		FULL_COPY,
		{"xevious",   "xe-4c-a.bin", 8192, 0x0ede5706, 4096, 4096},
		{"xevious",   "xvi_6.3j",    4096, 0xe18cdaad,    0, 4096},
	},
	{
		LOWER_COPY,
		{"xevious",  "3l-3m",	512, 0x90876fdc,    0, 512},
		{"xevious", "xvi-4.3l",   512, 0xfd8b9d91,    0, 512},
	},
	{
		LOWER_SHIFT,
		{"xevious",  "3l-3m",	512, 0x90876fdc,    0, 512},
		{"xevious", "xvi-5.3m",   512, 0xbf906d82,    0, 512},
	},
	{
		LOWER_COPY,
		{"xevious", "4h-4f",	512, 0xc21a65ff,    0, 512},
		{"xevious", "xvi-7.4h",   512, 0x22d98032,    0, 512},
	},
	{
		LOWER_SHIFT,
		{"xevious", "4h-4f",	512, 0xc21a65ff,    0, 512},
		{"xevious", "xvi-6.4f",   512, 0x3a7599f0,    0, 512},
	},
	{
		LOWER_COPY,
		{"sxevious",  "3l-3m",	512, 0x90876fdc,    0, 512},
		{"sxevious", "xvi-4.3l",   512, 0xfd8b9d91,    0, 512},
	},
	{
		LOWER_SHIFT,
		{"sxevious",  "3l-3m",	512, 0x90876fdc,    0, 512},
		{"sxevious", "xvi-5.3m",   512, 0xbf906d82,    0, 512},
	},
	{
		LOWER_COPY,
		{"sxevious", "4h-4f",	512, 0xc21a65ff,    0, 512},
		{"sxevious", "xvi-7.4h",   512, 0x22d98032,    0, 512},
	},
	{
		LOWER_SHIFT,
		{"sxevious", "4h-4f",	512, 0xc21a65ff,    0, 512},
		{"sxevious", "xvi-6.4f",   512, 0x3a7599f0,    0, 512},
	},
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"skykid",   "skysnd.bin",   512, 0x19e2d4b9,    0, 512},
		{"zzzzzzzz", "zzzzzzzz.zzz", 512, 0x19e2d4b9,    0, 512},
	},
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"pacland",  "pl-snd",       512, 0xd3aff2df,    0, 512},
		{"zzzzzzzz", "zzzzzzzz.zzz", 512, 0xd3aff2df,    0, 512},
	},
	{0}
};

struct Rom shark_roms[] =
{
	{
		FULL_COPY,
		{"snowbros", "ch0", 131072, 0x36d84dfe, 0, 131072},
		{"snowbros", "sbros-1.41", 524288, 0x16f06b3a, 0, 131072},
	},
	{
		FULL_COPY,
		{"snowbros", "ch1", 131072, 0x76347256, 0, 131072},
		{"snowbros", "sbros-1.41", 524288, 0x16f06b3a, 131072, 131072},
	},
	{
		FULL_COPY,
		{"snowbros", "ch2", 131072, 0xfdaa634c, 0, 131072},
		{"snowbros", "sbros-1.41", 524288, 0x16f06b3a, 262144, 131072},
	},
	{
		FULL_COPY,
		{"snowbros", "ch3", 131072, 0x34024aef, 0, 131072},
		{"snowbros", "sbros-1.41", 524288, 0x16f06b3a, 393216, 131072},
	},
	{
		FULL_COPY,
		{"kikikaikai",    "a85-08.rom", 128, 0x00fa7ca0,     0, 128},
		{"kikikai",       "a85-08.g15", 256, 0xd15f61a8,     0, 128},
	},
	{
		FULL_COPY,
		{"kikikaikai",    "a85-09.rom", 128, 0x25a369af,     0, 128},
		{"kikikai",       "a85-09.g14", 256, 0xb931c94d,     0, 128},
	},
	{
		FULL_COPY,
		{"kikikaikai",    "a85-10.rom", 128, 0x5e62bab4,     0, 128},
		{"kikikai",       "a85-10.g12", 256, 0x8fc3fa86,     0, 128},
	},
	{
		FULL_COPY,
		{"kyukyokutiger", "b30-06",   32768, 0xda1efca2,     0, 16384},
		{"ktiger",	"tc04",     16384, 0xa599d845,     0, 16384},
	},
	{
		FULL_COPY,
		{"kyukyokutiger", "b30-06",   32768, 0xda1efca2, 16384, 16384},
		{"ktiger",	"tc04",     16384, 0xa599d845,     0, 16384},
	},
	{
		FULL_COPY,
		{"kyukyokutiger", "b30-07",   32768, 0x52ea1c4c,     0, 16384},
		{"ktiger",	"tc03",     16384, 0xe9e2d4b1,     0, 16384},
	},
	{
		FULL_COPY,
		{"kyukyokutiger", "b30-07",   32768, 0x52ea1c4c, 16384, 16384},
		{"ktiger",	"tc03",     16384, 0xe9e2d4b1,     0, 16384},
	},
	{
		FULL_COPY,
		{"kyukyokutiger", "b30-08",   32768, 0xbf4ed7aa,     0, 16384},
		{"ktiger",	"tc11",     16384, 0x0a254133,     0, 16384},
	},
	{
		FULL_COPY,
		{"kyukyokutiger", "b30-08",   32768, 0xbf4ed7aa, 16384, 16384},
		{"ktiger",	"tc11",     16384, 0x0a254133,     0, 16384},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_03l.bin",  65536, 0xd831189b,     0, 65536},
		{"rallybik",   "b45-03.rom", 131072, 0x555344ce,     0, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_03h.bin",  65536, 0xcbf8846c,     0, 65536},
		{"rallybik",   "b45-03.rom", 131072, 0x555344ce, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_04l.bin",  65536, 0xf5705482,     0, 65536},
		{"rallybik",   "b45-04.rom", 131072, 0xe9b005b1,     0, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_04h.bin",  65536, 0xab467050,     0, 65536},
		{"rallybik",   "b45-04.rom", 131072, 0xe9b005b1, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_06l.bin",  65536, 0xc34f02b0,     0, 65536},
		{"rallybik",   "b45-06.bin", 131072, 0x144b085c,     0, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_06h.bin",  65536, 0x4910fd73,     0, 65536},
		{"rallybik",   "b45-06.bin", 131072, 0x144b085c, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_07l.bin",  65536, 0x8f679f11,     0, 65536},
		{"rallybik",   "b45-07.bin", 131072, 0xcd3748b4,     0, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_07h.bin",  65536, 0x161a6ae1,     0, 65536},
		{"rallybik",   "b45-07.bin", 131072, 0xcd3748b4, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_08l.bin",  65536, 0x031678e3,     0, 65536},
		{"rallybik",   "b45-08.bin", 131072, 0xfab661ba,     0, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_08h.bin",  65536, 0xd21eed25,     0, 65536},
		{"rallybik",   "b45-08.bin", 131072, 0xfab661ba, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_09l.bin",  65536, 0x6c07ba36,     0, 65536},
		{"rallybik",   "b45-09.bin", 131072, 0x1dc7b010,     0, 65536},
	},
	{
		FULL_COPY,
		{"rallybike",  "rb_09h.bin",  65536, 0xa54d0e78,     0, 65536},
		{"rallybik",   "b45-09.bin", 131072, 0x1dc7b010, 65536, 65536},
	},
	{
		FULL_COPY,
		{"tigerheli",  "rom18.bin",     512, 0x4e7ede2b,     0, 256},
		{"tigerhb2",   "82s129.12q",    256, 0x2c69350d,     0, 256},
	},
	{
		BLOCK_FILL,
		{"tigerheli",  "rom18.bin",     512, 0x4e7ede2b,   256, 256},
		{"	 ",  "	 ",     256, 0x0f0f0f0f,     0,   0},
	},
	{
		FULL_COPY,
		{"tigerheli",  "rom19.bin",     512, 0x81cc6a63,     0, 256},
		{"tigerhb2",   "82s129.12n",    256, 0x25f273f2,     0, 256},
	},
	{
		BLOCK_FILL,
		{"tigerheli",  "rom19.bin",     512, 0x81cc6a63,   256, 256},
		{"	 ",  "	 ",     256, 0x0f0f0f0f,     0,   0},
	},
	{
		FULL_COPY,
		{"tigerheli",  "rom20.bin",     512, 0x27bb9d8c,     0, 256},
		{"tigerhb2",   "82s129.12m",    256, 0x7142e972,     0, 256},
	},
	{
		BLOCK_FILL,
		{"tigerheli",  "rom20.bin",     512, 0x27bb9d8c,   256, 256},
		{"	 ",  "	 ",     256, 0x0f0f0f0f,     0,   0},
	},
	{
		FULL_COPY,
		{"tnzs2",    "ns_c-11a.rom",  65536, 0x6d5fb32e,     0, 65536},
		{"tnzsop",   "ns_c-11.rom",  131072, 0x3c1dae7b,     0, 65536},
	},
	{
		FULL_COPY,
		{"tnzs2",    "ns_c-11b.rom",  65536, 0xf7fe8b90,     0, 65536},
		{"tnzsop",   "ns_c-11.rom",  131072, 0x3c1dae7b, 65536, 65536},
	},
	{0}
};


struct Rom jas_roms[] =
{
	/* No longer used. JAS can use the small PROMS
	{
		FULL_COPY,
		{"pacland",  "pl1-1.bin",   2048, 0x723a0079,    0, 1024},
		{"paclandm", "pl1-1.bin",   1024, 0xa78ebdaf,    0, 1024},
	},
	{
		BLOCK_FILL,
		{"pacland",  "pl1-1.bin",   2048, 0x723a0079, 1024, 1024},
		{"	", "	 ",      0, 0x0f0f0f0f,    0,    0},
	},
	{
		FULL_COPY,
		{"pacland",  "pl1-3.bin",   2048, 0xced67226,    0, 1024},
		{"paclandm", "pl1-3.bin",   1024, 0x80558da8,    0, 1024},
	},
	{
		BLOCK_FILL,
		{"pacland",  "pl1-3.bin",   2048, 0xced67226, 1024, 1024},
		{"	", "	 ",      0, 0xffffffff,    0,    0},
	},
	{
		FULL_COPY,
		{"pacland",  "pl1-4.bin",   2048, 0xed2b87d5,    0, 1024},
		{"paclandm", "pl1-4.bin",   1024, 0x3a7be418,    0, 1024},
	},
	{
		BLOCK_FILL,
		{"pacland",  "pl1-4.bin",   2048, 0xed2b87d5, 1024, 1024},
		{"	", "	 ",      0, 0xffffffff,    0,    0},
	},
	{
		FULL_COPY,
		{"pacland",  "pl1-5.bin",   2048, 0x2c62b312,    0, 1024},
		{"paclandm", "pl1-5.bin",   1024, 0x4b7ee712,    0, 1024},
	},
	{
		BLOCK_FILL,
		{"pacland",  "pl1-5.bin",   2048, 0x2c62b312, 1024, 1024},
		{"	", "	 ",      0, 0xffffffff,    0,    0},
	},*/
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"gal3",     "g3_8n.bin",     40, 0x6f44e937,    0, 40},
		{"zzzzzzzz", "zzzzzzzz.zzz",  40, 0x6f44e937,    0, 40},
	},
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"pacland",  "pl-snd",       512, 0xd3aff2df,    0, 512},
		{"zzzzzzzz", "zzzzzzzz.zzz", 512, 0xd3aff2df,    0, 512},
	},
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"skykid",   "skysnd.bin",   512, 0x19e2d4b9,    0, 512},
		{"zzzzzzzz", "zzzzzzzz.zzz", 512, 0x19e2d4b9,    0, 512},
	},
	{0}
};

struct Rom mimic_roms[] =
{
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd,    0, 2048},
		{"galaxian", "galmidw.u",   2048, 0x745e2d61,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd, 2048, 2048},
		{"galaxian", "galmidw.v",   2048, 0x9c999a40,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d,    0, 2048},
		{"galaxian", "galmidw.w",   2048, 0xb5894925,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d, 2048, 2048},
		{"galaxian", "galmidw.y",   2048, 0x6b3ca10b,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "superg.u",    2048, 0xe8f3aa67,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"superg",   "superg.v",    2048, 0xf58283e3,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{0}
};

struct Rom rockulator_roms[] =
{
	{
		FULL_COPY,
		{"sonson", "ss7.v12", 16384, 0x32b14b8e, 0, 8192},
		{"sonson", "ss_9.m5", 8192, 0x8cb1cacf, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss7.v12", 16384, 0x32b14b8e, 8192, 8192},
		{"sonson", "ss_10.m6", 8192, 0xf802815e, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss8.v12", 16384, 0x9f59014e, 0, 8192},
		{"sonson", "ss_11.m3", 8192, 0x4dbad88a, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss8.v12", 16384, 0x9f59014e, 8192, 8192},
		{"sonson", "ss_12.m4", 8192, 0xaa05e687, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss9.v12", 16384, 0x517fa26d, 0, 8192},
		{"sonson", "ss_13.m1", 8192, 0x66119bfa, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss9.v12", 16384, 0x517fa26d, 8192, 8192},
		{"sonson", "ss_14.m2", 8192, 0xe14ef54e, 0, 8192},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd,    0, 2048},
		{"galaxian", "galmidw.u",   2048, 0x745e2d61,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd, 2048, 2048},
		{"galaxian", "galmidw.v",   2048, 0x9c999a40,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d,    0, 2048},
		{"galaxian", "galmidw.w",   2048, 0xb5894925,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d, 2048, 2048},
		{"galaxian", "galmidw.y",   2048, 0x6b3ca10b,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7l",	  4096, 0x952c6135,    0, 2048},
		{"galaxian", "7l",	  2048, 0x1b933207,    0, 2048},
	},
	{
		BLOCK_FILL,
		{"galaxian", "7l",	  4096, 0x952c6135, 2048, 2048},
		{"	", "  ",	     0, 0xffffffff,   0,     0},
	},
	{
		FULL_COPY,
		{"supergal", "galaxian.u",  2048, 0xe8f3aa67,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de,    0, 2048},
	},
	{
		FULL_COPY,
		{"supergal", "galaxian.v",  2048, 0xf58283e3,    0, 2048},
		{"superg",   "7f.bin",      4096, 0x4335b1de, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom ace_roms[] =
{
	{
		FULL_COPY,
		{"goalx3", "goal!_c1.rom", 4194304, 0xd061f1f5, 0, 2097152},
		{"goalx3", "209-c1.bin", 4194304, 0xb49d980e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c2.rom", 4194304, 0x3f63c1a2, 0, 2097152},
		{"goalx3", "209-c2.bin", 4194304, 0x5649b015, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c1.rom", 4194304, 0xd061f1f5, 2097152, 2097152},
		{"goalx3", "209-c1.bin", 4194304, 0xb49d980e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c2.rom", 4194304, 0x3f63c1a2, 2097152, 2097152},
		{"goalx3", "209-c2.bin", 4194304, 0x5649b015, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c1.rom", 4194304, 0xd00bd152, 0, 2097152},
		{"mslug", "201-c1.bin", 4194304, 0x72813676, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c2.rom", 4194304, 0xddff1dea, 0, 2097152},
		{"mslug", "201-c2.bin", 4194304, 0x96f62574, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c3.rom", 4194304, 0xd3d5f9e5, 0, 2097152},
		{"mslug", "201-c3.bin", 4194304, 0x5121456a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c4.rom", 4194304, 0x5ac1d497, 0, 2097152},
		{"mslug", "201-c4.bin", 4194304, 0xf4ad59a3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c1.rom", 4194304, 0xd00bd152, 2097152, 2097152},
		{"mslug", "201-c1.bin", 4194304, 0x72813676, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c2.rom", 4194304, 0xddff1dea, 2097152, 2097152},
		{"mslug", "201-c2.bin", 4194304, 0x96f62574, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c3.rom", 4194304, 0xd3d5f9e5, 2097152, 2097152},
		{"mslug", "201-c3.bin", 4194304, 0x5121456a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c4.rom", 4194304, 0x5ac1d497, 2097152, 2097152},
		{"mslug", "201-c4.bin", 4194304, 0xf4ad59a3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c1.rom", 4194304, 0x62c5edc9, 0, 2097152},
		{"neodrift", "213-c1.bin", 4194304, 0x3edc8bd3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c2.rom", 4194304, 0x9dc9c72a, 0, 2097152},
		{"neodrift", "213-c2.bin", 4194304, 0x46ae5f16, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c1.rom", 4194304, 0x62c5edc9, 2097152, 2097152},
		{"neodrift", "213-c1.bin", 4194304, 0x3edc8bd3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c2.rom", 4194304, 0x9dc9c72a, 2097152, 2097152},
		{"neodrift", "213-c2.bin", 4194304, 0x46ae5f16, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c1.rom", 4194304, 0xaad087fc, 0, 2097152},
		{"shocktro", "238-c1.bin", 4194304, 0x90c6a181, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c2.rom", 4194304, 0x7e39df1f, 0, 2097152},
		{"shocktro", "238-c2.bin", 4194304, 0x888720f0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c3.rom", 4194304, 0x6682a458, 0, 2097152},
		{"shocktro", "238-c3.bin", 4194304, 0x2c393aa3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c4.rom", 4194304, 0xcbef1f17, 0, 2097152},
		{"shocktro", "238-c4.bin", 4194304, 0xb9e909eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c5.rom", 4194304, 0xe17762b1, 0, 2097152},
		{"shocktro", "238-c5.bin", 4194304, 0xc22c68eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c6.rom", 4194304, 0x28beab71, 0, 2097152},
		{"shocktro", "238-c6.bin", 4194304, 0x119323cd, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c7.rom", 4194304, 0xa47e62d2, 0, 2097152},
		{"shocktro", "238-c7.bin", 4194304, 0xa72ce7ed, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c8.rom", 4194304, 0xe8e890fb, 0, 2097152},
		{"shocktro", "238-c8.bin", 4194304, 0x1c7c2efb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_p2.rom", 4194304, 0x646f6c76, 0, 2097152},
		{"shocktro", "238-p2.bin", 4194304, 0x5b4a09c5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c1.rom", 4194304, 0xaad087fc, 2097152, 2097152},
		{"shocktro", "238-c1.bin", 4194304, 0x90c6a181, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c2.rom", 4194304, 0x7e39df1f, 2097152, 2097152},
		{"shocktro", "238-c2.bin", 4194304, 0x888720f0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c3.rom", 4194304, 0x6682a458, 2097152, 2097152},
		{"shocktro", "238-c3.bin", 4194304, 0x2c393aa3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c4.rom", 4194304, 0xcbef1f17, 2097152, 2097152},
		{"shocktro", "238-c4.bin", 4194304, 0xb9e909eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c5.rom", 4194304, 0xe17762b1, 2097152, 2097152},
		{"shocktro", "238-c5.bin", 4194304, 0xc22c68eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c6.rom", 4194304, 0x28beab71, 2097152, 2097152},
		{"shocktro", "238-c6.bin", 4194304, 0x119323cd, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c7.rom", 4194304, 0xa47e62d2, 2097152, 2097152},
		{"shocktro", "238-c7.bin", 4194304, 0xa72ce7ed, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c8.rom", 4194304, 0xe8e890fb, 2097152, 2097152},
		{"shocktro", "238-c8.bin", 4194304, 0x1c7c2efb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_p2.rom", 4194304, 0x646f6c76, 2097152, 2097152},
		{"shocktro", "238-p2.bin", 4194304, 0x5b4a09c5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c1.rom", 4194304, 0x8c6733f2, 0, 2097152},
		{"turfmast", "200-c1.bin", 4194304, 0x8e7bf41a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c2.rom", 4194304, 0x596cc256, 0, 2097152},
		{"turfmast", "200-c2.bin", 4194304, 0x5a65a8ce, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c1.rom", 4194304, 0x8c6733f2, 2097152, 2097152},
		{"turfmast", "200-c1.bin", 4194304, 0x8e7bf41a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c2.rom", 4194304, 0x596cc256, 2097152, 2097152},
		{"turfmast", "200-c2.bin", 4194304, 0x5a65a8ce, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c1.rom", 4194304, 0xd91d386f, 0, 2097152},
		{"wakuwak7", "225-c1.bin", 4194304, 0xee4fea54, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c2.rom", 4194304, 0x36b5cf41, 0, 2097152},
		{"wakuwak7", "225-c2.bin", 4194304, 0x0c549e2d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c3.rom", 4194304, 0x02fcff2f, 0, 2097152},
		{"wakuwak7", "225-c3.bin", 4194304, 0xaf0897c0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c4.rom", 4194304, 0xcd7f1241, 0, 2097152},
		{"wakuwak7", "225-c4.bin", 4194304, 0x4c66527a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c5.rom", 4194304, 0x03d32f25, 0, 2097152},
		{"wakuwak7", "225-c5.bin", 4194304, 0x8ecea2b5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c6.rom", 4194304, 0xd996a90a, 0, 2097152},
		{"wakuwak7", "225-c6.bin", 4194304, 0x0eb11a6d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c1.rom", 4194304, 0xd91d386f, 2097152, 2097152},
		{"wakuwak7", "225-c1.bin", 4194304, 0xee4fea54, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c2.rom", 4194304, 0x36b5cf41, 2097152, 2097152},
		{"wakuwak7", "225-c2.bin", 4194304, 0x0c549e2d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c3.rom", 4194304, 0x02fcff2f, 2097152, 2097152},
		{"wakuwak7", "225-c3.bin", 4194304, 0xaf0897c0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c4.rom", 4194304, 0xcd7f1241, 2097152, 2097152},
		{"wakuwak7", "225-c4.bin", 4194304, 0x4c66527a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c5.rom", 4194304, 0x03d32f25, 2097152, 2097152},
		{"wakuwak7", "225-c5.bin", 4194304, 0x8ecea2b5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c6.rom", 4194304, 0xd996a90a, 2097152, 2097152},
		{"wakuwak7", "225-c6.bin", 4194304, 0x0eb11a6d, 0, 2097152},
	},
	{0}
};

struct Rom magex_roms[] =
{
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd,    0, 2048},
		{"galaxian", "galmidw.u",   2048, 0x745e2d61,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd, 2048, 2048},
		{"galaxian", "galmidw.v",   2048, 0x9c999a40,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d,    0, 2048},
		{"galaxian", "galmidw.w",   2048, 0xb5894925,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d, 2048, 2048},
		{"galaxian", "galmidw.y",   2048, 0x6b3ca10b,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7l",	  4096, 0x952c6135,    0, 2048},
		{"galaxian", "7l",	  2048, 0x1b933207,    0, 2048},
	},
	{
		BLOCK_FILL,
		{"galaxian", "7l",	  4096, 0x952c6135, 2048, 2048},
		{"	", "  ",	     0, 0xffffffff,   0,     0},
	},
	{0}
};

struct Rom sonson_roms[] =
{
	{
		FULL_COPY,
		{"sonson", "ss7.v12", 16384, 0x32b14b8e, 0, 8192},
		{"sonson", "ss_9.m5", 8192, 0x8cb1cacf, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss7.v12", 16384, 0x32b14b8e, 8192, 8192},
		{"sonson", "ss_10.m6", 8192, 0xf802815e, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss8.v12", 16384, 0x9f59014e, 0, 8192},
		{"sonson", "ss_11.m3", 8192, 0x4dbad88a, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss8.v12", 16384, 0x9f59014e, 8192, 8192},
		{"sonson", "ss_12.m4", 8192, 0xaa05e687, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss9.v12", 16384, 0x517fa26d, 0, 8192},
		{"sonson", "ss_13.m1", 8192, 0x66119bfa, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss9.v12", 16384, 0x517fa26d, 8192, 8192},
		{"sonson", "ss_14.m2", 8192, 0xe14ef54e, 0, 8192},
	},
	{0}
};

struct Rom sparcade_roms[] =
{
	{
		FULL_COPY,
		{"nam_gal",  "galaxian.7f", 4096, 0xb10533fd,    0, 2048},
		{"galaxian", "galmidw.u",   2048, 0x745e2d61,    0, 2048},
	},
	{
		FULL_COPY,
		{"nam_gal",  "galaxian.7f", 4096, 0xb10533fd, 2048, 2048},
		{"galaxian", "galmidw.v",   2048, 0x9c999a40,    0, 2048},
	},
	{
		FULL_COPY,
		{"nam_gal",  "galaxian.7j", 4096, 0x9163454d,    0, 2048},
		{"galaxian", "galmidw.w",   2048, 0xb5894925,    0, 2048},
	},
	{
		FULL_COPY,
		{"nam_gal",  "galaxian.7j", 4096, 0x9163454d, 2048, 2048},
		{"galaxian", "galmidw.y",   2048, 0x6b3ca10b,    0, 2048},
	},
	{
		FULL_COPY,
		{"nam_gal",  "galaxian.7l", 4096, 0x952c6135,    0, 2048},
		{"galaxian", "7l",	  2048, 0x1b933207,    0, 2048},
	},
	{
		BLOCK_FILL,
		{"nam_gal",  "galaxian.7l", 4096, 0x952c6135, 2048, 2048},
		{"	", "	   ",    0, 0xffffffff,   0,     0},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.1", 32768, 0xd8d85ab7, 0, 16384},
		{"starforc", "starforc.3", 16384, 0x8ba27691, 0, 16384},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.1", 32768, 0xd8d85ab7, 16384, 16384},
		{"starforc", "starforc.2", 16384, 0x0fc4d2d6, 0, 16384},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.2", 16384, 0xf59d941b, 0, 4096},
		{"starforc", "starforc.16", 4096, 0xce20b469, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.2", 16384, 0xf59d941b, 4096, 4096},
		{"starforc", "starforc.17", 4096, 0x68c60d0f, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.2", 16384, 0xf59d941b, 8192, 4096},
		{"starforc", "starforc.18", 4096, 0x6455c3ad, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.2", 16384, 0xf59d941b, 12288, 4096},
		{"starforc", "starforc.4", 16384, 0xdd9d68a4, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.3", 16384, 0x73f4140f, 0, 12288},
		{"starforc", "starforc.4", 16384, 0xdd9d68a4, 4096, 12288},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.3", 16384, 0x73f4140f, 12288, 4096},
		{"starforc", "starforc.5", 16384, 0xf71717f8, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.4", 16384, 0xa9e719c3, 0, 12288},
		{"starforc", "starforc.5", 16384, 0xf71717f8, 4096, 12288},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.4", 16384, 0xa9e719c3, 12288, 4096},
		{"starforc", "starforc.6", 16384, 0x5468a21d, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.5", 16384, 0xcf779ce8, 0, 12288},
		{"starforc", "starforc.6", 16384, 0x5468a21d, 4096, 12288},
	},
	{
		BLOCK_FILL,
		{"starfor2", "starforc.5", 16384, 0xcf779ce8, 12288, 4096},
		{"	", "	   ", 0, 0x00000000,   0,     0},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.6", 16384, 0xdfe04a7d, 0, 8192},
		{"starforc", "starforc.1", 8192, 0x2735bb22, 0, 8192},
	},
	{
		BLOCK_FILL,
		{"starfor2", "starforc.6", 16384, 0xdfe04a7d, 8192, 8192},
		{"	", "	   ", 0, 0x00000000,   0,     0},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 0, 4096},
		{"starforc", "starforc.7", 4096, 0xf4803339, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 4096, 4096},
		{"starforc", "starforc.8", 4096, 0x96979684, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 8192, 4096},
		{"starforc", "starforc.9", 4096, 0xeead1d5c, 0, 4096},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 12288, 8192},
		{"starforc", "starforc.10", 8192, 0xc62a19c1, 0, 8192},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 20480, 8192},
		{"starforc", "starforc.11", 8192, 0x668aea14, 0, 8192},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 28672, 8192},
		{"starforc", "starforc.12", 8192, 0xfdd9e38b, 0, 8192},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 36864, 8192},
		{"starforc", "starforc.13", 8192, 0x84603285, 0, 8192},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 45056, 8192},
		{"starforc", "starforc.14", 8192, 0x9e9384fe, 0, 8192},
	},
	{
		FULL_COPY,
		{"starfor2", "starforc.7", 61440, 0xf3808e6e, 53248, 8192},
		{"starforc", "starforc.15", 8192, 0xc3bda12f, 0, 8192},
	},
	/* These ROMs don't work in Sparcade!
	{
		FULL_COPY,
		{"tazmania", "tazmania.1",  2048, 0x3dca9594,    0, 2048},
		{"tazmani2", "2ck.cpu",     4096, 0xbf0492bf,    0, 2048},
	},
	{
		FULL_COPY,
		{"tazmania", "tazmania.2",  2048, 0x6b6a1126,    0, 2048},
		{"tazmani2", "2ck.cpu",     4096, 0xbf0492bf, 2048, 2048},
	},
	{
		FULL_COPY,
		{"tazmania", "tazmania.3",  2048, 0xa6c798f4,    0, 2048},
		{"tazmani2", "2ek.cpu",     4096, 0x6636c4d0,    0, 2048},
	},
	{
		FULL_COPY,
		{"tazmania", "tazmania.4",  2048, 0xa09c8a48,    0, 2048},
		{"tazmani2", "2ek.cpu",     4096, 0x6636c4d0, 2048, 2048},
	},
	{
		FULL_COPY,
		{"tazmania", "tazmania.5",  2048, 0x0527e513,    0, 2048},
		{"tazmani2", "2fk.cpu",     4096, 0xce59a57b,    0, 2048},
	},
	{
		FULL_COPY,
		{"tazmania", "tazmania.6",  2048, 0x282afadd,    0, 2048},
		{"tazmani2", "2fk.cpu",     4096, 0xce59a57b, 2048, 2048},
	},
	{
		FULL_COPY,
		{"tazmania", "tazmania.7",  2048, 0xbbdc41d3,    0, 2048},
		{"tazmani2", "2hk.cpu",     4096, 0x8bda3380,    0, 2048},
	},
	{
		FULL_COPY,
		{"tazmania", "tazmania.8",  2048, 0xa925da16,    0, 2048},
		{"tazmani2", "2hk.cpu",     4096, 0x8bda3380, 2048, 2048},
	},*/
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"berzerk",  "berzerk.s1c",  2048, 0x2cfe825d,   0, 2048},
		{"zzzzzzzz", "zzzzzzzz.zzz", 2048, 0x2cfe825d,   0, 2048},
	},
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"berzerk",  "berzerk.s2c",  2048, 0xd2b6324e,   0, 2048},
		{"zzzzzzzz", "zzzzzzzz.zzz", 2048, 0xd2b6324e,   0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom vantage_roms[] =
{
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom xcade_roms[] =
{
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 0, 2048},
		{"piscesb", "g09.bin", 2048, 0x9503a23a, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 0, 2048},
		{"piscesb", "g10.bin", 2048, 0x3e61f849, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1j", 4096, 0x2dba9e0e, 2048, 2048},
		{"piscesb", "g11.bin", 2048, 0x0adfc3fe, 0, 2048},
	},
	{
		FULL_COPY,
		{"pisces", "pisces.1k", 4096, 0xcdc5aa26, 2048, 2048},
		{"piscesb", "g12.bin", 2048, 0x7130e9eb, 0, 2048},
	},
	{0}
};

struct Rom retrocade_roms[] =
{
	{
		FULL_COPY,
		{"snowbros", "ch0", 131072, 0x36d84dfe, 0, 131072},
		{"snowbrosa", "sbros-1.41", 524288, 0x16f06b3a, 0, 131072},
	},
	{
		FULL_COPY,
		{"snowbros", "ch1", 131072, 0x76347256, 0, 131072},
		{"snowbrosa", "sbros-1.41", 524288, 0x16f06b3a, 131072, 131072},
	},
	{
		FULL_COPY,
		{"snowbros", "ch2", 131072, 0xfdaa634c, 0, 131072},
		{"snowbrosa", "sbros-1.41", 524288, 0x16f06b3a, 262144, 131072},
	},
	{
		FULL_COPY,
		{"snowbros", "ch3", 131072, 0x34024aef, 0, 131072},
		{"snowbrosa", "sbros-1.41", 524288, 0x16f06b3a, 393216, 131072},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd,    0, 2048},
		{"galaxian", "galmidw.u",   2048, 0x745e2d61,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7f",	  4096, 0xb10533fd, 2048, 2048},
		{"galaxian", "galmidw.v",   2048, 0x9c999a40,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d,    0, 2048},
		{"galaxian", "galmidw.w",   2048, 0xb5894925,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7j",	  4096, 0x9163454d, 2048, 2048},
		{"galaxian", "galmidw.y",   2048, 0x6b3ca10b,    0, 2048},
	},
	{
		FULL_COPY,
		{"galaxian", "7l",	  4096, 0x952c6135,    0, 2048},
		{"galaxian", "7l",	  2048, 0x1b933207,    0, 2048},
	},
	{
		BLOCK_FILL,
		{"galaxian", "7l",	  4096, 0x952c6135, 2048, 2048},
		{"	", "  ",	     0, 0xffffffff,   0,     0},
	},
	{
		FULL_COPY,
		{"dotron",   "loc-cpu4",    16384, 0x0477e9a2,      0, 8192},
		{"dotrone",  "loc-cpu4",     8192, 0xc137383c,      0, 8192},
	},
	{
		/* Extra data that may be important to Retrocade */
		FULL_COPY,
		{"dotron",   "loc-cpu4",     16384, 0x0477e9a2,  8192, 8192},
		{"dotrone",  "loc-a.cp0",     8192, 0xb35f5374,     0, 8192},
	},
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"atarifb",  "034006.l5",     256, 0xc5ac7bf6,      0, 256},
		{"zzzzzzzz", "zzzzzzzz.zzz",  256, 0xc5ac7bf6,      0, 256},
	},
	{
		/* No corresponding ROM in MAME */
		FULL_COPY,
		{"frenzy",   "5c-5",	 4096, 0xc71c0011,      0, 4096},
		{"zzzzzzzz", "zzzzzzzz.zzz", 4096, 0xc71c0011,      0, 4096},
	},
	{
		/* Not sure which ROM this is in MAME so I can't correct CRC info in the dat */
		FULL_COPY,
		{"nibbler",  "ic53",	 2048, 0x34eca7be,      0, 2048},
		{"zzzzzzzz", "zzzzzzzz.zzz", 2048, 0x34eca7be,      0, 2048},
	},
	{0}
};

struct Rom the_arcade_roms[] =
{
	{
		FULL_COPY,
		{"tron", "troncb1.bin",    32768, 0xc2bbb286,    0, 8192},
		{"tron2", "vga.e1",	8192, 0xbc036d1d,    0, 8192},
	},
	{
		FULL_COPY,
		{"tron", "troncb1.bin",    32768, 0xc2bbb286, 8192, 8192},
		{"tron2", "vgb.dc1",	8192, 0x58ee14d3,    0, 8192},
	},
	{
		FULL_COPY,
		{"tron", "troncb1.bin",    32768, 0xc2bbb286, 16384, 8192},
		{"tron2", "vgc.cb1",	8192, 0x3329f9d4,     0, 8192},
	},
	{
		FULL_COPY,
		{"tron", "troncb1.bin",    32768, 0xc2bbb286, 24576, 8192},
		{"tron2", "vga.a1",	8192, 0x9743f873,     0, 8192},
	},
	{0}
};

struct Rom pcslomo_roms[] =
{
	{
		FULL_COPY,
		{"pacmanjp", "prg1",	2048, 0xf36e88ab,    0, 2048},
		{"puckmana", "pacman.6e",   4096, 0xc1e6ab10,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg2",	2048, 0x618bd9b3,    0, 2048},
		{"puckmana", "pacman.6e",   4096, 0xc1e6ab10, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg3",	2048, 0x7d177853,    0, 2048},
		{"puckmana", "pacman.6f",   4096, 0x1a6fb2d4,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg4",	2048, 0xd3e8914c,    0, 2048},
		{"puckmana", "pacman.6f",   4096, 0x1a6fb2d4, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg5",	2048, 0x6bf4f625,    0, 2048},
		{"puckmana", "pacman.6h",   4096, 0xbcdd1beb,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg6",	2048, 0xa948ce83,    0, 2048},
		{"puckmana", "pacman.6h",   4096, 0xbcdd1beb, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "chg3",	2048, 0x9e39323a,    0, 2048},
		{"puckmana", "pacman.5f",   4096, 0x958fedf9,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "chg4",	2048, 0x1b1d9096,    0, 2048},
		{"puckmana", "pacman.5f",   4096, 0x958fedf9, 2048, 2048},
	},
	{0}
};

struct Rom xpac_roms[] =
{
	{
		FULL_COPY,
		{"pacmanjp", "prg1",	2048, 0xf36e88ab,    0, 2048},
		{"puckmana", "pacman.6e",   4096, 0xc1e6ab10,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg2",	2048, 0x618bd9b3,    0, 2048},
		{"puckmana", "pacman.6e",   4096, 0xc1e6ab10, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg3",	2048, 0x7d177853,    0, 2048},
		{"puckmana", "pacman.6f",   4096, 0x1a6fb2d4,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg4",	2048, 0xd3e8914c,    0, 2048},
		{"puckmana", "pacman.6f",   4096, 0x1a6fb2d4, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg5",	2048, 0x6bf4f625,    0, 2048},
		{"puckmana", "pacman.6h",   4096, 0xbcdd1beb,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "prg6",	2048, 0xa948ce83,    0, 2048},
		{"puckmana", "pacman.6h",   4096, 0xbcdd1beb, 2048, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "chg3",	2048, 0x9e39323a,    0, 2048},
		{"puckmana", "pacman.5f",   4096, 0x958fedf9,    0, 2048},
	},
	{
		FULL_COPY,
		{"pacmanjp", "chg4",	2048, 0x1b1d9096,    0, 2048},
		{"puckmana", "pacman.5f",   4096, 0x958fedf9, 2048, 2048},
	},
	{0}
};

struct Rom system8_roms[] =
{
	{
		FULL_COPY,
		{"wbdeluxe", "wb.004",       32768, 0x8b3124e6,      0, 16384},
		{"wbdeluxe", "epr-7485.117",  16384, 0xc2891722,      0, 16384},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.004",       32768, 0x8b3124e6,  16384, 16384},
		{"wbdeluxe", "epr-7486.110",  16384, 0x8d622c50,      0, 16384},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.005",       32768, 0xb75278e7,      0, 16384},
		{"wbdeluxe", "epr-7487.04",   16384, 0x2d3a421b,      0, 16384},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.005",       32768, 0xb75278e7,  16384, 16384},
		{"wbdeluxe", "epr-7488.05",   16384, 0x007c2f1b,      0, 16384},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.006",       16384, 0xe812b3ec,      0, 8192},
		{"wbdeluxe", "epr-7493.66",   8192,  0x89305df4,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.006",       16384, 0xe812b3ec,   8192, 8192},
		{"wbdeluxe", "epr-7492.65",   8192,  0x60f806b1,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.007",       16384, 0x87ecba53,      0, 8192},
		{"wbdeluxe", "epr-7495.64",   8192,  0x6a0d2c2d,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.007",       16384, 0x87ecba53,   8192, 8192},
		{"wbdeluxe", "epr-7494.63",   8192,  0xa8e281c7,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.008",       16384, 0x1685d26a,      0, 8192},
		{"wbdeluxe", "epr-7497.62",   8192,  0x08d609ca,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.008",       16384, 0x1685d26a,   8192, 8192},
		{"wbdeluxe", "epr-7496.61",   8192,  0x6f61fdf1,      0, 8192},
	},
	{0}
};

struct Rom kem_roms[] =
{
	{
		FULL_COPY,
		{"dotron",   "loc-cpu4",    16384, 0x0477e9a2,      0, 8192},
		{"dotrone",  "loc-cpu4",     8192, 0xc137383c,      0, 8192},
	},
	{
		FULL_COPY,
		{"dotron",   "loc-cpu4",     16384, 0x0477e9a2,  8192, 8192},
		{"dotrone",  "loc-a.cp0",     8192, 0xb35f5374,     0, 8192},
	},
	{0}
};

struct Rom system16_roms[] =
{
	{
		FULL_COPY,
		{"altbeast", "ab11674.bin", 131072, 0xa57a66d5, 0, 65536},
		{"altbeast4", "epr-11722.a14", 65536, 0xadaa8db5, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11675.bin", 131072, 0x2ef2f144, 0, 65536},
		{"altbeast4", "epr-11723.a15", 65536, 0x131a3f9a, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11676.bin", 131072, 0x0c04acac, 0, 65536},
		{"altbeast4", "epr-11724.a16", 65536, 0x6f2ed50a, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11674.bin", 131072, 0xa57a66d5, 65536, 65536},
		{"altbeast4", "epr-11736.b14", 65536, 0xe9ad5e89, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11675.bin", 131072, 0x2ef2f144, 65536, 65536},
		{"altbeast4", "epr-11737.b15", 65536, 0x2e420023, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11676.bin", 131072, 0x0c04acac, 65536, 65536},
		{"altbeast4", "epr-11738.b16", 65536, 0xde3d6d02, 0, 65536},
	},
	{0}
};

struct Rom modeler_roms[] =
{
	{
		FULL_COPY,
		{"harddunk", "16506",     1048576, 0x06c52b89, 0, 1048576 },
		{"harddunkj", "mp16506.1", 2097152, 0xe779f5ed, 0, 1048576},
	},
	{
		FULL_COPY,
		{"harddunk", "16507",     1048576, 0x351c0281, 0, 1048576 },
		{"harddunkj", "mp16507.2", 2097152, 0x31e068d3, 0, 1048576},
	},
	{0}
};

struct Rom calice_roms[] =
{
	{
		FULL_COPY,
		{"altbeast", "ab11674.bin", 131072, 0xa57a66d5, 0, 65536},
		{"altbeast4", "epr-11722.a14", 65536, 0xadaa8db5, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11675.bin", 131072, 0x2ef2f144, 0, 65536},
		{"altbeast4", "epr-11723.a15", 65536, 0x131a3f9a, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11676.bin", 131072, 0x0c04acac, 0, 65536},
		{"altbeast4", "epr-11724.a16", 65536, 0x6f2ed50a, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11674.bin", 131072, 0xa57a66d5, 65536, 65536},
		{"altbeast4", "epr-11736.b14", 65536, 0xe9ad5e89, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11675.bin", 131072, 0x2ef2f144, 65536, 65536},
		{"altbeast4", "epr-11737.b15", 65536, 0x2e420023, 0, 65536},
	},
	{
		FULL_COPY,
		{"altbeast", "ab11676.bin", 131072, 0x0c04acac, 65536, 65536},
		{"altbeast4", "epr-11738.b16", 65536, 0xde3d6d02, 0, 65536},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_c1.rom", 524288, 0xe17fa618, 0, 524288},
		{"roboarmy", "032-c1.bin", 1048576, 0x97984c6c, 0, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_c2.rom", 524288, 0xd5ebdb4d, 0, 524288},
		{"roboarmy", "032-c2.bin", 1048576, 0x65773122, 0, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_v1.rom", 524288, 0xdaff9896, 0, 524288},
		{"roboarmy", "032-v1.bin", 1048576, 0x63791533, 0, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_v3.rom", 524288, 0xb69c1da5, 0, 524288},
		{"roboarmy", "032-v2.bin", 1048576, 0xeb95de70, 0, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_c3.rom", 524288, 0xaa4d7695, 0, 524288},
		{"roboarmy", "032-c1.bin", 1048576, 0x97984c6c, 524288, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_c4.rom", 524288, 0x8d4ebbe3, 0, 524288},
		{"roboarmy", "032-c2.bin", 1048576, 0x65773122, 524288, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_v2.rom", 524288, 0x8781b1bc, 0, 524288},
		{"roboarmy", "032-v1.bin", 1048576, 0x63791533, 524288, 524288},
	},
	{
		FULL_COPY,
		{"roboarmy", "rarmy_v4.rom", 524288, 0x2c929c17, 0, 524288},
		{"roboarmy", "032-v2.bin", 1048576, 0xeb95de70, 524288, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_p1.rom", 524288, 0xcc245299, 0, 524288},
		{"sengoku2", "040-p1.bin", 1048576, 0x6dde02c2, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_v1.rom", 1048576, 0xb3725ced, 0, 1048576},
		{"sengoku2", "040-v1.bin", 2097152, 0x71cb4b5d, 0, 1048576},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_p2.rom", 524288, 0x2e466360, 0, 524288},
		{"sengoku2", "040-p1.bin", 1048576, 0x6dde02c2, 524288, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_v2.rom", 1048576, 0xb5e70a0e, 0, 1048576},
		{"sengoku2", "040-v1.bin", 2097152, 0x71cb4b5d, 1048576, 1048576},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c1.rom", 2097152, 0x3cacd552, 0, 1048576},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 0, 1048576},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c1.rom", 2097152, 0x3cacd552, 1048576, 524288},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c1.rom", 2097152, 0x3cacd552, 1572864, 524288},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c2.rom", 2097152, 0xe2aadef3, 0, 1048576},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 0, 1048576},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c2.rom", 2097152, 0xe2aadef3, 1048576, 524288},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c2.rom", 2097152, 0xe2aadef3, 1572864, 524288},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c3.rom", 2097152, 0x037614d5, 0, 1048576},
		{"sengoku2", "040-c1.bin", 2097152, 0xfaa8ea99, 1048576, 1048576},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c3.rom", 2097152, 0x037614d5, 1048576, 524288},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c3.rom", 2097152, 0x037614d5, 1572864, 524288},
		{"sengoku2", "040-c3.bin", 524288, 0x24b5ba80, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c4.rom", 2097152, 0xe9947e5b, 0, 1048576},
		{"sengoku2", "040-c2.bin", 2097152, 0x87d0ec65, 1048576, 1048576},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c4.rom", 2097152, 0xe9947e5b, 1048576, 524288},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 524288},
	},
	{
		FULL_COPY,
		{"sengoku2", "goku2_c4.rom", 2097152, 0xe9947e5b, 1572864, 524288},
		{"sengoku2", "040-c4.bin", 524288, 0x1c9e9930, 0, 524288},
	},
	{
		FULL_COPY,
		{"3countb", "3cb_c1.rom", 2097152, 0xd290cc33, 0, 1048576},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 0, 1048576},
	},
	{
		FULL_COPY,
		{"3countb", "3cb_c2.rom", 2097152, 0x0b28095d, 0, 1048576},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 0, 1048576},
	},
	{
		FULL_COPY,
		{"3countb", "3cb_c3.rom", 2097152, 0xbcc0cb35, 0, 1048576},
		{"3countb", "043-c1.bin", 2097152, 0xbad2d67f, 1048576, 1048576},
	},
	{
		FULL_COPY,
		{"3countb", "3cb_c4.rom", 2097152, 0x4d1ff7b9, 0, 1048576},
		{"3countb", "043-c2.bin", 2097152, 0xa7fbda95, 1048576, 1048576},
	},
	{
		FULL_COPY,
		{"3countb", "3cb_c1.rom", 2097152, 0xd290cc33, 1048576, 1048576},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 0, 1048576},
	},
	{
		FULL_COPY,
		{"3countb", "3cb_c2.rom", 2097152, 0x0b28095d, 1048576, 1048576},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 0, 1048576},
	},
	{
		FULL_COPY,
		{"3countb", "3cb_c3.rom", 2097152, 0xbcc0cb35, 1048576, 1048576},
		{"3countb", "043-c3.bin", 2097152, 0xf00be011, 1048576, 1048576},
	},
	{
		FULL_COPY,
		{"3countb", "3cb_c4.rom", 2097152, 0x4d1ff7b9, 1048576, 1048576},
		{"3countb", "043-c4.bin", 2097152, 0x1887e5c0, 1048576, 1048576},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c1.rom", 4194304, 0xf6c74731, 0, 2097152},
		{"aof3", "096-c1.bin", 4194304, 0xf17b8d89, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c2.rom", 4194304, 0xf587f149, 0, 2097152},
		{"aof3", "096-c2.bin", 4194304, 0x3840c508, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c3.rom", 4194304, 0x7749f5e6, 0, 2097152},
		{"aof3", "096-c3.bin", 4194304, 0x55f9ee1e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c4.rom", 4194304, 0xcbd58369, 0, 2097152},
		{"aof3", "096-c4.bin", 4194304, 0x585b7e47, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c5.rom", 4194304, 0x1718bdcd, 0, 2097152},
		{"aof3", "096-c5.bin", 4194304, 0xc75a753c, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c6.rom", 4194304, 0x4fca967f, 0, 2097152},
		{"aof3", "096-c6.bin", 4194304, 0x9a9d2f7a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c1.rom", 4194304, 0xf6c74731, 2097152, 2097152},
		{"aof3", "096-c1.bin", 4194304, 0xf17b8d89, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c2.rom", 4194304, 0xf587f149, 2097152, 2097152},
		{"aof3", "096-c2.bin", 4194304, 0x3840c508, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c3.rom", 4194304, 0x7749f5e6, 2097152, 2097152},
		{"aof3", "096-c3.bin", 4194304, 0x55f9ee1e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c4.rom", 4194304, 0xcbd58369, 2097152, 2097152},
		{"aof3", "096-c4.bin", 4194304, 0x585b7e47, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c5.rom", 4194304, 0x1718bdcd, 2097152, 2097152},
		{"aof3", "096-c5.bin", 4194304, 0xc75a753c, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c6.rom", 4194304, 0x4fca967f, 2097152, 2097152},
		{"aof3", "096-c6.bin", 4194304, 0x9a9d2f7a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c1.rom", 4194304, 0x754744e0, 0, 2097152},
		{"blazstar", "239-c1.bin", 4194304, 0x84f6d584, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c2.rom", 4194304, 0xaf98c037, 0, 2097152},
		{"blazstar", "239-c2.bin", 4194304, 0x05a0cb22, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c3.rom", 4194304, 0x7b39b590, 0, 2097152},
		{"blazstar", "239-c3.bin", 4194304, 0x5fb69c9e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c4.rom", 4194304, 0x6e731b30, 0, 2097152},
		{"blazstar", "239-c4.bin", 4194304, 0x0be028c4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c5.rom", 4194304, 0x9ceb113b, 0, 2097152},
		{"blazstar", "239-c5.bin", 4194304, 0x74bae5f8, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c6.rom", 4194304, 0x6a78e810, 0, 2097152},
		{"blazstar", "239-c6.bin", 4194304, 0x4e0700d2, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c7.rom", 4194304, 0x50d28eca, 0, 2097152},
		{"blazstar", "239-c7.bin", 4194304, 0x010ff4fd, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c8.rom", 4194304, 0xcdbbb7d7, 0, 2097152},
		{"blazstar", "239-c8.bin", 4194304, 0xdb60460e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c1.rom", 4194304, 0x754744e0, 2097152, 2097152},
		{"blazstar", "239-c1.bin", 4194304, 0x84f6d584, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c2.rom", 4194304, 0xaf98c037, 2097152, 2097152},
		{"blazstar", "239-c2.bin", 4194304, 0x05a0cb22, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c3.rom", 4194304, 0x7b39b590, 2097152, 2097152},
		{"blazstar", "239-c3.bin", 4194304, 0x5fb69c9e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c4.rom", 4194304, 0x6e731b30, 2097152, 2097152},
		{"blazstar", "239-c4.bin", 4194304, 0x0be028c4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c5.rom", 4194304, 0x9ceb113b, 2097152, 2097152},
		{"blazstar", "239-c5.bin", 4194304, 0x74bae5f8, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c6.rom", 4194304, 0x6a78e810, 2097152, 2097152},
		{"blazstar", "239-c6.bin", 4194304, 0x4e0700d2, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c7.rom", 4194304, 0x50d28eca, 2097152, 2097152},
		{"blazstar", "239-c7.bin", 4194304, 0x010ff4fd, 0, 2097152},
	},
	{
		FULL_COPY,
		{"blazstar", "bstar_c8.rom", 4194304, 0xcdbbb7d7, 2097152, 2097152},
		{"blazstar", "239-c8.bin", 4194304, 0xdb60460e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c1.rom", 4194304, 0xd061f1f5, 0, 2097152},
		{"goalx3", "209-c1.bin", 4194304, 0xb49d980e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c2.rom", 4194304, 0x3f63c1a2, 0, 2097152},
		{"goalx3", "209-c2.bin", 4194304, 0x5649b015, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c1.rom", 4194304, 0xd061f1f5, 2097152, 2097152},
		{"goalx3", "209-c1.bin", 4194304, 0xb49d980e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"goalx3", "goal!_c2.rom", 4194304, 0x3f63c1a2, 2097152, 2097152},
		{"goalx3", "209-c2.bin", 4194304, 0x5649b015, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c1.rom", 4194304, 0x4d896a58, 0, 2097152},
		{"kabukikl", "092-c1.bin", 4194304, 0x2a9fab01, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c2.rom", 4194304, 0x3cf78a18, 0, 2097152},
		{"kabukikl", "092-c2.bin", 4194304, 0x6d2bac02, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c3.rom", 4194304, 0x58c454e7, 0, 2097152},
		{"kabukikl", "092-c3.bin", 4194304, 0x5da735d6, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c4.rom", 4194304, 0xe1a8aa6a, 0, 2097152},
		{"kabukikl", "092-c4.bin", 4194304, 0xde07f997, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c1.rom", 4194304, 0x4d896a58, 2097152, 2097152},
		{"kabukikl", "092-c1.bin", 4194304, 0x2a9fab01, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c2.rom", 4194304, 0x3cf78a18, 2097152, 2097152},
		{"kabukikl", "092-c2.bin", 4194304, 0x6d2bac02, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c3.rom", 4194304, 0x58c454e7, 2097152, 2097152},
		{"kabukikl", "092-c3.bin", 4194304, 0x5da735d6, 0, 2097152},
	},
	{
		FULL_COPY,
		{"kabukikl", "klash_c4.rom", 4194304, 0xe1a8aa6a, 2097152, 2097152},
		{"kabukikl", "092-c4.bin", 4194304, 0xde07f997, 0, 2097152},
	},
	{
		FULL_COPY,
		{"lastblad", "lb_c5.rom", 2097152, 0x17bbd7ca, 0, 2097152},
		{"lastblad", "234-c5.bin", 4194304, 0x1ba80cee, 0, 2097152},
	},
	{
		FULL_COPY,
		{"lastblad", "lb_c6.rom", 2097152, 0x5c35d541, 0, 2097152},
		{"lastblad", "234-c6.bin", 4194304, 0xbeafd091, 0, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c1.rom", 4194304, 0x734db3d6, 0, 2097152},
		{"magdrop3", "233-c1.bin", 4194304, 0x65e3f4c4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c2.rom", 4194304, 0xd78f50e5, 0, 2097152},
		{"magdrop3", "233-c2.bin", 4194304, 0x35dea6c9, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c3.rom", 4194304, 0xec65f472, 0, 2097152},
		{"magdrop3", "233-c3.bin", 4194304, 0x0ba2c502, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c4.rom", 4194304, 0xf55dddf3, 0, 2097152},
		{"magdrop3", "233-c4.bin", 4194304, 0x70dbbd6d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c1.rom", 4194304, 0x734db3d6, 2097152, 2097152},
		{"magdrop3", "233-c1.bin", 4194304, 0x65e3f4c4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c2.rom", 4194304, 0xd78f50e5, 2097152, 2097152},
		{"magdrop3", "233-c2.bin", 4194304, 0x35dea6c9, 0, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c3.rom", 4194304, 0xec65f472, 2097152, 2097152},
		{"magdrop3", "233-c3.bin", 4194304, 0x0ba2c502, 0, 2097152},
	},
	{
		FULL_COPY,
		{"magdrop3", "drop3_c4.rom", 4194304, 0xf55dddf3, 2097152, 2097152},
		{"magdrop3", "233-c4.bin", 4194304, 0x70dbbd6d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c1.rom", 4194304, 0xd00bd152, 0, 2097152},
		{"mslug", "201-c1.bin", 4194304, 0x72813676, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c2.rom", 4194304, 0xddff1dea, 0, 2097152},
		{"mslug", "201-c2.bin", 4194304, 0x96f62574, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c3.rom", 4194304, 0xd3d5f9e5, 0, 2097152},
		{"mslug", "201-c3.bin", 4194304, 0x5121456a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c4.rom", 4194304, 0x5ac1d497, 0, 2097152},
		{"mslug", "201-c4.bin", 4194304, 0xf4ad59a3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c1.rom", 4194304, 0xd00bd152, 2097152, 2097152},
		{"mslug", "201-c1.bin", 4194304, 0x72813676, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c2.rom", 4194304, 0xddff1dea, 2097152, 2097152},
		{"mslug", "201-c2.bin", 4194304, 0x96f62574, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c3.rom", 4194304, 0xd3d5f9e5, 2097152, 2097152},
		{"mslug", "201-c3.bin", 4194304, 0x5121456a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c4.rom", 4194304, 0x5ac1d497, 2097152, 2097152},
		{"mslug", "201-c4.bin", 4194304, 0xf4ad59a3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_c1.rom", 4194304, 0xb90ebed4, 0, 2097152},
		{"neobombe", "093-c1.bin", 4194304, 0xd1f328f8, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_c2.rom", 4194304, 0x41e62b4f, 0, 2097152},
		{"neobombe", "093-c2.bin", 4194304, 0x82c49540, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_v1.rom", 4194304, 0x43057e99, 0, 2097152},
		{"neobombe", "093-v1.bin", 4194304, 0x02abd4b0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_c1.rom", 4194304, 0xb90ebed4, 2097152, 2097152},
		{"neobombe", "093-c1.bin", 4194304, 0xd1f328f8, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_c2.rom", 4194304, 0x41e62b4f, 2097152, 2097152},
		{"neobombe", "093-c2.bin", 4194304, 0x82c49540, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neobombe", "bombm_v1.rom", 4194304, 0x43057e99, 2097152, 2097152},
		{"neobombe", "093-v1.bin", 4194304, 0x02abd4b0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c1.rom", 4194304, 0x62c5edc9, 0, 2097152},
		{"neodrift", "213-c1.bin", 4194304, 0x3edc8bd3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c2.rom", 4194304, 0x9dc9c72a, 0, 2097152},
		{"neodrift", "213-c2.bin", 4194304, 0x46ae5f16, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c1.rom", 4194304, 0x62c5edc9, 2097152, 2097152},
		{"neodrift", "213-c1.bin", 4194304, 0x3edc8bd3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c2.rom", 4194304, 0x9dc9c72a, 2097152, 2097152},
		{"neodrift", "213-c2.bin", 4194304, 0x46ae5f16, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c1.rom", 4194304, 0x58f91ae0, 0, 2097152},
		{"ninjamas", "217-c1.bin", 4194304, 0x5fe97bc4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c2.rom", 4194304, 0x4258147f, 0, 2097152},
		{"ninjamas", "217-c2.bin", 4194304, 0x886e0d66, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c3.rom", 4194304, 0x36c29ce3, 0, 2097152},
		{"ninjamas", "217-c3.bin", 4194304, 0x59e8525f, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c4.rom", 4194304, 0x17e97a6e, 0, 2097152},
		{"ninjamas", "217-c4.bin", 4194304, 0x8521add2, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c5.rom", 4194304, 0x4683ffc0, 0, 2097152},
		{"ninjamas", "217-c5.bin", 4194304, 0xfb1896e5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c6.rom", 4194304, 0xde004f4a, 0, 2097152},
		{"ninjamas", "217-c6.bin", 4194304, 0x1c98c54b, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c7.rom", 4194304, 0x3e1885c0, 0, 2097152},
		{"ninjamas", "217-c7.bin", 4194304, 0x8b0ede2e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c8.rom", 4194304, 0x5a5df034, 0, 2097152},
		{"ninjamas", "217-c8.bin", 4194304, 0xa085bb61, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c1.rom", 4194304, 0x58f91ae0, 2097152, 2097152},
		{"ninjamas", "217-c1.bin", 4194304, 0x5fe97bc4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c2.rom", 4194304, 0x4258147f, 2097152, 2097152},
		{"ninjamas", "217-c2.bin", 4194304, 0x886e0d66, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c3.rom", 4194304, 0x36c29ce3, 2097152, 2097152},
		{"ninjamas", "217-c3.bin", 4194304, 0x59e8525f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c4.rom", 4194304, 0x17e97a6e, 2097152, 2097152},
		{"ninjamas", "217-c4.bin", 4194304, 0x8521add2, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c5.rom", 4194304, 0x4683ffc0, 2097152, 2097152},
		{"ninjamas", "217-c5.bin", 4194304, 0xfb1896e5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c6.rom", 4194304, 0xde004f4a, 2097152, 2097152},
		{"ninjamas", "217-c6.bin", 4194304, 0x1c98c54b, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c7.rom", 4194304, 0x3e1885c0, 2097152, 2097152},
		{"ninjamas", "217-c7.bin", 4194304, 0x8b0ede2e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ninjamas", "ninjm_c8.rom", 4194304, 0x5a5df034, 2097152, 2097152},
		{"ninjamas", "217-c8.bin", 4194304, 0xa085bb61, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c1.rom", 4194304, 0x63020fc6, 0, 2097152},
		{"pulstar", "089-c1.bin", 4194304, 0xf4e97332, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c2.rom", 4194304, 0x260e9d4d, 0, 2097152},
		{"pulstar", "089-c2.bin", 4194304, 0x836d14da, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c3.rom", 4194304, 0x21ef41d7, 0, 2097152},
		{"pulstar", "089-c3.bin", 4194304, 0x913611c4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c4.rom", 4194304, 0x3b9e288f, 0, 2097152},
		{"pulstar", "089-c4.bin", 4194304, 0x44cef0e3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c5.rom", 4194304, 0x6fe9259c, 0, 2097152},
		{"pulstar", "089-c5.bin", 4194304, 0x89baa1d7, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c6.rom", 4194304, 0xdc32f2b4, 0, 2097152},
		{"pulstar", "089-c6.bin", 4194304, 0xb2594d56, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c1.rom", 4194304, 0x63020fc6, 2097152, 2097152},
		{"pulstar", "089-c1.bin", 4194304, 0xf4e97332, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c2.rom", 4194304, 0x260e9d4d, 2097152, 2097152},
		{"pulstar", "089-c2.bin", 4194304, 0x836d14da, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c3.rom", 4194304, 0x21ef41d7, 2097152, 2097152},
		{"pulstar", "089-c3.bin", 4194304, 0x913611c4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c4.rom", 4194304, 0x3b9e288f, 2097152, 2097152},
		{"pulstar", "089-c4.bin", 4194304, 0x44cef0e3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c5.rom", 4194304, 0x6fe9259c, 2097152, 2097152},
		{"pulstar", "089-c5.bin", 4194304, 0x89baa1d7, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c6.rom", 4194304, 0xdc32f2b4, 2097152, 2097152},
		{"pulstar", "089-c6.bin", 4194304, 0xb2594d56, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c1.rom", 4194304, 0x18f61d79, 0, 2097152},
		{"ragnagrd", "218-c1.bin", 4194304, 0xc31500a4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c2.rom", 4194304, 0xdbf4ff4b, 0, 2097152},
		{"ragnagrd", "218-c2.bin", 4194304, 0x98aba1f9, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c3.rom", 4194304, 0x108d5589, 0, 2097152},
		{"ragnagrd", "218-c3.bin", 4194304, 0x833c163a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c4.rom", 4194304, 0x7962d5ac, 0, 2097152},
		{"ragnagrd", "218-c4.bin", 4194304, 0xc1a30f69, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c5.rom", 4194304, 0x4b74021a, 0, 2097152},
		{"ragnagrd", "218-c5.bin", 4194304, 0x6b6de0ff, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c6.rom", 4194304, 0xf5cf90bc, 0, 2097152},
		{"ragnagrd", "218-c6.bin", 4194304, 0x94beefcf, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c7.rom", 4194304, 0x32189762, 0, 2097152},
		{"ragnagrd", "218-c7.bin", 4194304, 0xde6f9b28, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c8.rom", 4194304, 0xd5915828, 0, 2097152},
		{"ragnagrd", "218-c8.bin", 4194304, 0xd9b311f6, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c1.rom", 4194304, 0x18f61d79, 2097152, 2097152},
		{"ragnagrd", "218-c1.bin", 4194304, 0xc31500a4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c2.rom", 4194304, 0xdbf4ff4b, 2097152, 2097152},
		{"ragnagrd", "218-c2.bin", 4194304, 0x98aba1f9, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c3.rom", 4194304, 0x108d5589, 2097152, 2097152},
		{"ragnagrd", "218-c3.bin", 4194304, 0x833c163a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c4.rom", 4194304, 0x7962d5ac, 2097152, 2097152},
		{"ragnagrd", "218-c4.bin", 4194304, 0xc1a30f69, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c5.rom", 4194304, 0x4b74021a, 2097152, 2097152},
		{"ragnagrd", "218-c5.bin", 4194304, 0x6b6de0ff, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c6.rom", 4194304, 0xf5cf90bc, 2097152, 2097152},
		{"ragnagrd", "218-c6.bin", 4194304, 0x94beefcf, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c7.rom", 4194304, 0x32189762, 2097152, 2097152},
		{"ragnagrd", "218-c7.bin", 4194304, 0xde6f9b28, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ragnagrd", "rgard_c8.rom", 4194304, 0xd5915828, 2097152, 2097152},
		{"ragnagrd", "218-c8.bin", 4194304, 0xd9b311f6, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c1.rom", 4194304, 0x436edad4, 0, 2097152},
		{"rbffspec", "223-c1.bin", 4194304, 0xebab05e2, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c2.rom", 4194304, 0xcc7dc384, 0, 2097152},
		{"rbffspec", "223-c2.bin", 4194304, 0x641868c3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c3.rom", 4194304, 0x375954ea, 0, 2097152},
		{"rbffspec", "223-c3.bin", 4194304, 0xca00191f, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c4.rom", 4194304, 0xc1a98dd7, 0, 2097152},
		{"rbffspec", "223-c4.bin", 4194304, 0x1f23d860, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c5.rom", 4194304, 0x12c5418e, 0, 2097152},
		{"rbffspec", "223-c5.bin", 4194304, 0x321e362c, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c6.rom", 4194304, 0xc8ad71d5, 0, 2097152},
		{"rbffspec", "223-c6.bin", 4194304, 0xd8fcef90, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c7.rom", 4194304, 0x5c33d1d8, 0, 2097152},
		{"rbffspec", "223-c7.bin", 4194304, 0xbc80dd2d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c8.rom", 4194304, 0xefdeb140, 0, 2097152},
		{"rbffspec", "223-c8.bin", 4194304, 0x5ad62102, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_p2.rom", 4194304, 0x27e3e54b, 0, 2097152},
		{"rbffspec", "223-p2.bin", 4194304, 0xaddd8f08, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c1.rom", 4194304, 0x436edad4, 2097152, 2097152},
		{"rbffspec", "223-c1.bin", 4194304, 0xebab05e2, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c2.rom", 4194304, 0xcc7dc384, 2097152, 2097152},
		{"rbffspec", "223-c2.bin", 4194304, 0x641868c3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c3.rom", 4194304, 0x375954ea, 2097152, 2097152},
		{"rbffspec", "223-c3.bin", 4194304, 0xca00191f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c4.rom", 4194304, 0xc1a98dd7, 2097152, 2097152},
		{"rbffspec", "223-c4.bin", 4194304, 0x1f23d860, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c5.rom", 4194304, 0x12c5418e, 2097152, 2097152},
		{"rbffspec", "223-c5.bin", 4194304, 0x321e362c, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c6.rom", 4194304, 0xc8ad71d5, 2097152, 2097152},
		{"rbffspec", "223-c6.bin", 4194304, 0xd8fcef90, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c7.rom", 4194304, 0x5c33d1d8, 2097152, 2097152},
		{"rbffspec", "223-c7.bin", 4194304, 0xbc80dd2d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_c8.rom", 4194304, 0xefdeb140, 2097152, 2097152},
		{"rbffspec", "223-c8.bin", 4194304, 0x5ad62102, 0, 2097152},
	},
	{
		FULL_COPY,
		{"rbffspec", "rbffs_p2.rom", 4194304, 0x27e3e54b, 2097152, 2097152},
		{"rbffspec", "223-p2.bin", 4194304, 0xaddd8f08, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c7.rom", 524288, 0x7a01f666, 0, 524288},
		{"samsho3", "087-c7.bin", 1048576, 0xae450e3d, 0, 524288},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c8.rom", 524288, 0xffd009c2, 0, 524288},
		{"samsho3", "087-c8.bin", 1048576, 0xa9e82717, 0, 524288},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c1.rom", 4194304, 0xe079f767, 0, 2097152},
		{"samsho3", "087-c1.bin", 4194304, 0x07a233bc, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c2.rom", 4194304, 0xfc045909, 0, 2097152},
		{"samsho3", "087-c2.bin", 4194304, 0x7a413592, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c3.rom", 4194304, 0xc61218d7, 0, 2097152},
		{"samsho3", "087-c3.bin", 4194304, 0x8b793796, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c4.rom", 4194304, 0x054ec754, 0, 2097152},
		{"samsho3", "087-c4.bin", 4194304, 0x728fbf11, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c5.rom", 4194304, 0x05feee47, 0, 2097152},
		{"samsho3", "087-c5.bin", 4194304, 0x172ab180, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c6.rom", 4194304, 0xef7d9e29, 0, 2097152},
		{"samsho3", "087-c6.bin", 4194304, 0x002ff8f3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c1.rom", 4194304, 0xe079f767, 2097152, 2097152},
		{"samsho3", "087-c1.bin", 4194304, 0x07a233bc, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c2.rom", 4194304, 0xfc045909, 2097152, 2097152},
		{"samsho3", "087-c2.bin", 4194304, 0x7a413592, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c3.rom", 4194304, 0xc61218d7, 2097152, 2097152},
		{"samsho3", "087-c3.bin", 4194304, 0x8b793796, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c4.rom", 4194304, 0x054ec754, 2097152, 2097152},
		{"samsho3", "087-c4.bin", 4194304, 0x728fbf11, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c5.rom", 4194304, 0x05feee47, 2097152, 2097152},
		{"samsho3", "087-c5.bin", 4194304, 0x172ab180, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho3", "sams3_c6.rom", 4194304, 0xef7d9e29, 2097152, 2097152},
		{"samsho3", "087-c6.bin", 4194304, 0x002ff8f3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c1.rom", 4194304, 0x289100fa, 0, 2097152},
		{"samsho4", "222-c1.bin", 4194304, 0x68f2ed95, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c2.rom", 4194304, 0xc2716ea0, 0, 2097152},
		{"samsho4", "222-c2.bin", 4194304, 0xa6e9aff0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c3.rom", 4194304, 0x6659734f, 0, 2097152},
		{"samsho4", "222-c3.bin", 4194304, 0xc91b40f4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c4.rom", 4194304, 0x91ebea00, 0, 2097152},
		{"samsho4", "222-c4.bin", 4194304, 0x359510a4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c5.rom", 4194304, 0xe22254ed, 0, 2097152},
		{"samsho4", "222-c5.bin", 4194304, 0x9cfbb22d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c6.rom", 4194304, 0x00947b2e, 0, 2097152},
		{"samsho4", "222-c6.bin", 4194304, 0x685efc32, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c7.rom", 4194304, 0xe3e3b0cd, 0, 2097152},
		{"samsho4", "222-c7.bin", 4194304, 0xd0f86f0d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c8.rom", 4194304, 0xf33967f1, 0, 2097152},
		{"samsho4", "222-c8.bin", 4194304, 0xadfc50e3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_p2.rom", 4194304, 0x7587f09b, 0, 2097152},
		{"samsho4", "222-p2.bin", 4194304, 0xb023cd8b, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c1.rom", 4194304, 0x289100fa, 2097152, 2097152},
		{"samsho4", "222-c1.bin", 4194304, 0x68f2ed95, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c2.rom", 4194304, 0xc2716ea0, 2097152, 2097152},
		{"samsho4", "222-c2.bin", 4194304, 0xa6e9aff0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c3.rom", 4194304, 0x6659734f, 2097152, 2097152},
		{"samsho4", "222-c3.bin", 4194304, 0xc91b40f4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c4.rom", 4194304, 0x91ebea00, 2097152, 2097152},
		{"samsho4", "222-c4.bin", 4194304, 0x359510a4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c5.rom", 4194304, 0xe22254ed, 2097152, 2097152},
		{"samsho4", "222-c5.bin", 4194304, 0x9cfbb22d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c6.rom", 4194304, 0x00947b2e, 2097152, 2097152},
		{"samsho4", "222-c6.bin", 4194304, 0x685efc32, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c7.rom", 4194304, 0xe3e3b0cd, 2097152, 2097152},
		{"samsho4", "222-c7.bin", 4194304, 0xd0f86f0d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_c8.rom", 4194304, 0xf33967f1, 2097152, 2097152},
		{"samsho4", "222-c8.bin", 4194304, 0xadfc50e3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"samsho4", "sams4_p2.rom", 4194304, 0x7587f09b, 2097152, 2097152},
		{"samsho4", "222-p2.bin", 4194304, 0xb023cd8b, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c1.rom", 4194304, 0xaad087fc, 0, 2097152},
		{"shocktro", "238-c1.bin", 4194304, 0x90c6a181, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c2.rom", 4194304, 0x7e39df1f, 0, 2097152},
		{"shocktro", "238-c2.bin", 4194304, 0x888720f0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c3.rom", 4194304, 0x6682a458, 0, 2097152},
		{"shocktro", "238-c3.bin", 4194304, 0x2c393aa3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c4.rom", 4194304, 0xcbef1f17, 0, 2097152},
		{"shocktro", "238-c4.bin", 4194304, 0xb9e909eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c5.rom", 4194304, 0xe17762b1, 0, 2097152},
		{"shocktro", "238-c5.bin", 4194304, 0xc22c68eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c6.rom", 4194304, 0x28beab71, 0, 2097152},
		{"shocktro", "238-c6.bin", 4194304, 0x119323cd, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c7.rom", 4194304, 0xa47e62d2, 0, 2097152},
		{"shocktro", "238-c7.bin", 4194304, 0xa72ce7ed, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c8.rom", 4194304, 0xe8e890fb, 0, 2097152},
		{"shocktro", "238-c8.bin", 4194304, 0x1c7c2efb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_p2.rom", 4194304, 0x646f6c76, 0, 2097152},
		{"shocktro", "238-p2.bin", 4194304, 0x5b4a09c5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c1.rom", 4194304, 0xaad087fc, 2097152, 2097152},
		{"shocktro", "238-c1.bin", 4194304, 0x90c6a181, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c2.rom", 4194304, 0x7e39df1f, 2097152, 2097152},
		{"shocktro", "238-c2.bin", 4194304, 0x888720f0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c3.rom", 4194304, 0x6682a458, 2097152, 2097152},
		{"shocktro", "238-c3.bin", 4194304, 0x2c393aa3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c4.rom", 4194304, 0xcbef1f17, 2097152, 2097152},
		{"shocktro", "238-c4.bin", 4194304, 0xb9e909eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c5.rom", 4194304, 0xe17762b1, 2097152, 2097152},
		{"shocktro", "238-c5.bin", 4194304, 0xc22c68eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c6.rom", 4194304, 0x28beab71, 2097152, 2097152},
		{"shocktro", "238-c6.bin", 4194304, 0x119323cd, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c7.rom", 4194304, 0xa47e62d2, 2097152, 2097152},
		{"shocktro", "238-c7.bin", 4194304, 0xa72ce7ed, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c8.rom", 4194304, 0xe8e890fb, 2097152, 2097152},
		{"shocktro", "238-c8.bin", 4194304, 0x1c7c2efb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_p2.rom", 4194304, 0x646f6c76, 2097152, 2097152},
		{"shocktro", "238-p2.bin", 4194304, 0x5b4a09c5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c1.rom", 4194304, 0xaad087fc, 0, 2097152},
		{"shocktra", "238-c1.bin", 4194304, 0x90c6a181, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c2.rom", 4194304, 0x7e39df1f, 0, 2097152},
		{"shocktra", "238-c2.bin", 4194304, 0x888720f0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c3.rom", 4194304, 0x6682a458, 0, 2097152},
		{"shocktra", "238-c3.bin", 4194304, 0x2c393aa3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c4.rom", 4194304, 0xcbef1f17, 0, 2097152},
		{"shocktra", "238-c4.bin", 4194304, 0xb9e909eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c5.rom", 4194304, 0xe17762b1, 0, 2097152},
		{"shocktra", "238-c5.bin", 4194304, 0xc22c68eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c6.rom", 4194304, 0x28beab71, 0, 2097152},
		{"shocktra", "238-c6.bin", 4194304, 0x119323cd, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c7.rom", 4194304, 0xa47e62d2, 0, 2097152},
		{"shocktra", "238-c7.bin", 4194304, 0xa72ce7ed, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c8.rom", 4194304, 0xe8e890fb, 0, 2097152},
		{"shocktra", "238-c8.bin", 4194304, 0x1c7c2efb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_p2.rom", 4194304, 0x646f6c76, 0, 2097152},
		{"shocktra", "238-p2.bin", 4194304, 0x5b4a09c5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c1.rom", 4194304, 0xaad087fc, 2097152, 2097152},
		{"shocktra", "238-c1.bin", 4194304, 0x90c6a181, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c2.rom", 4194304, 0x7e39df1f, 2097152, 2097152},
		{"shocktra", "238-c2.bin", 4194304, 0x888720f0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c3.rom", 4194304, 0x6682a458, 2097152, 2097152},
		{"shocktra", "238-c3.bin", 4194304, 0x2c393aa3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c4.rom", 4194304, 0xcbef1f17, 2097152, 2097152},
		{"shocktra", "238-c4.bin", 4194304, 0xb9e909eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c5.rom", 4194304, 0xe17762b1, 2097152, 2097152},
		{"shocktra", "238-c5.bin", 4194304, 0xc22c68eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c6.rom", 4194304, 0x28beab71, 2097152, 2097152},
		{"shocktra", "238-c6.bin", 4194304, 0x119323cd, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c7.rom", 4194304, 0xa47e62d2, 2097152, 2097152},
		{"shocktra", "238-c7.bin", 4194304, 0xa72ce7ed, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_c8.rom", 4194304, 0xe8e890fb, 2097152, 2097152},
		{"shocktra", "238-c8.bin", 4194304, 0x1c7c2efb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktrj", "shock_p2.rom", 4194304, 0x646f6c76, 2097152, 2097152},
		{"shocktra", "238-p2.bin", 4194304, 0x5b4a09c5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi3", "sonw3_c1.rom", 4194304, 0x3ca97864, 0, 2097152},
		{"sonicwi3", "097-c1.bin", 4194304, 0x33d0d589, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi3", "sonw3_c2.rom", 4194304, 0x1da4b3a9, 0, 2097152},
		{"sonicwi3", "097-c2.bin", 4194304, 0x186f8b43, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi3", "sonw3_c1.rom", 4194304, 0x3ca97864, 2097152, 2097152},
		{"sonicwi3", "097-c1.bin", 4194304, 0x33d0d589, 0, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi3", "sonw3_c2.rom", 4194304, 0x1da4b3a9, 2097152, 2097152},
		{"sonicwi3", "097-c2.bin", 4194304, 0x186f8b43, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c1.rom", 4194304, 0x288a9225, 0, 2097152},
		{"ssideki4", "215-c1.bin", 4194304, 0x8ff444f5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c2.rom", 4194304, 0x3fc9d1c4, 0, 2097152},
		{"ssideki4", "215-c2.bin", 4194304, 0x5b155037, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c3.rom", 4194304, 0xfedfaebe, 0, 2097152},
		{"ssideki4", "215-c3.bin", 4194304, 0x456a073a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c4.rom", 4194304, 0x877a5bb2, 0, 2097152},
		{"ssideki4", "215-c4.bin", 4194304, 0x43c182e1, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_v1.rom", 4194304, 0xc4bfed62, 0, 2097152},
		{"ssideki4", "215-v1.bin", 4194304, 0x877d1409, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c1.rom", 4194304, 0x288a9225, 2097152, 2097152},
		{"ssideki4", "215-c1.bin", 4194304, 0x8ff444f5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c2.rom", 4194304, 0x3fc9d1c4, 2097152, 2097152},
		{"ssideki4", "215-c2.bin", 4194304, 0x5b155037, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c3.rom", 4194304, 0xfedfaebe, 2097152, 2097152},
		{"ssideki4", "215-c3.bin", 4194304, 0x456a073a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_c4.rom", 4194304, 0x877a5bb2, 2097152, 2097152},
		{"ssideki4", "215-c4.bin", 4194304, 0x43c182e1, 0, 2097152},
	},
	{
		FULL_COPY,
		{"ssideki4", "side4_v1.rom", 4194304, 0xc4bfed62, 2097152, 2097152},
		{"ssideki4", "215-v1.bin", 4194304, 0x877d1409, 0, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c1.rom", 4194304, 0x8c6733f2, 0, 2097152},
		{"turfmast", "200-c1.bin", 4194304, 0x8e7bf41a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c2.rom", 4194304, 0x596cc256, 0, 2097152},
		{"turfmast", "200-c2.bin", 4194304, 0x5a65a8ce, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c1.rom", 4194304, 0x8c6733f2, 2097152, 2097152},
		{"turfmast", "200-c1.bin", 4194304, 0x8e7bf41a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c2.rom", 4194304, 0x596cc256, 2097152, 2097152},
		{"turfmast", "200-c2.bin", 4194304, 0x5a65a8ce, 0, 2097152},
	},
	{
		FULL_COPY,
		{"twinspri", "sprit_c1.rom", 4194304, 0x73b2a70b, 0, 2097152},
		{"twinspri", "224-c1.bin", 4194304, 0xf7da64ab, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"twinspri", "sprit_c2.rom", 4194304, 0x3a3e506c, 0, 2097152},
		{"twinspri", "224-c2.bin", 4194304, 0x4c09bbfb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"twinspri", "sprit_c1.rom", 4194304, 0x73b2a70b, 2097152, 2097152},
		{"twinspri", "224-c1.bin", 4194304, 0xf7da64ab, 0, 2097152},
	},
	{
		FULL_COPY,
		{"twinspri", "sprit_c2.rom", 4194304, 0x3a3e506c, 2097152, 2097152},
		{"twinspri", "224-c2.bin", 4194304, 0x4c09bbfb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"tws96", "tecmo_c1.rom", 4194304, 0xd301a867, 0, 2097152},
		{"tws96", "086-c1.bin", 4194304, 0x2611bc2a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"tws96", "tecmo_c2.rom", 4194304, 0x305fc74f, 0, 2097152},
		{"tws96", "086-c2.bin", 4194304, 0x6b0d6827, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"tws96", "tecmo_c1.rom", 4194304, 0xd301a867, 2097152, 2097152},
		{"tws96", "086-c1.bin", 4194304, 0x2611bc2a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"tws96", "tecmo_c2.rom", 4194304, 0x305fc74f, 2097152, 2097152},
		{"tws96", "086-c2.bin", 4194304, 0x6b0d6827, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c1.rom", 4194304, 0xd91d386f, 0, 2097152},
		{"wakuwak7", "225-c1.bin", 4194304, 0xee4fea54, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c2.rom", 4194304, 0x36b5cf41, 0, 2097152},
		{"wakuwak7", "225-c2.bin", 4194304, 0x0c549e2d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c3.rom", 4194304, 0x02fcff2f, 0, 2097152},
		{"wakuwak7", "225-c3.bin", 4194304, 0xaf0897c0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c4.rom", 4194304, 0xcd7f1241, 0, 2097152},
		{"wakuwak7", "225-c4.bin", 4194304, 0x4c66527a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c5.rom", 4194304, 0x03d32f25, 0, 2097152},
		{"wakuwak7", "225-c5.bin", 4194304, 0x8ecea2b5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c6.rom", 4194304, 0xd996a90a, 0, 2097152},
		{"wakuwak7", "225-c6.bin", 4194304, 0x0eb11a6d, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c1.rom", 4194304, 0xd91d386f, 2097152, 2097152},
		{"wakuwak7", "225-c1.bin", 4194304, 0xee4fea54, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c2.rom", 4194304, 0x36b5cf41, 2097152, 2097152},
		{"wakuwak7", "225-c2.bin", 4194304, 0x0c549e2d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c3.rom", 4194304, 0x02fcff2f, 2097152, 2097152},
		{"wakuwak7", "225-c3.bin", 4194304, 0xaf0897c0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c4.rom", 4194304, 0xcd7f1241, 2097152, 2097152},
		{"wakuwak7", "225-c4.bin", 4194304, 0x4c66527a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c5.rom", 4194304, 0x03d32f25, 2097152, 2097152},
		{"wakuwak7", "225-c5.bin", 4194304, 0x8ecea2b5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wakuwak7", "waku7_c6.rom", 4194304, 0xd996a90a, 2097152, 2097152},
		{"wakuwak7", "225-c6.bin", 4194304, 0x0eb11a6d, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c1.rom", 4194304, 0xaecd5bb1, 0, 2097152},
		{"whp", "090-c1.bin", 4194304, 0xcd30ed9b, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c2.rom", 4194304, 0x7566ffc0, 0, 2097152},
		{"whp", "090-c2.bin", 4194304, 0x10eed5ee, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c1.rom", 4194304, 0xaecd5bb1, 2097152, 2097152},
		{"whp", "090-c1.bin", 4194304, 0xcd30ed9b, 0, 2097152},
	},
	{
		FULL_COPY,
		{"whp", "whp_c2.rom", 4194304, 0x7566ffc0, 2097152, 2097152},
		{"whp", "090-c2.bin", 4194304, 0x10eed5ee, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wjammers", "windj_p1.rom", 524288, 0xe81e7a31, 0, 524288},
		{"wjammers", "065-p1.bin", 1048576, 0x6692c140, 0, 524288},
	},
	{
		FULL_COPY,
		{"wjammers", "windj_v4.rom", 524288, 0x3740edde, 0, 524288},
		{"wjammers", "065-v4.bin", 1048576, 0x5dee7963, 0, 524288},
	},
	{
		FULL_COPY,
		{"2020bb", "2020_c3.rom", 524288, 0x6a87ae30, 0, 524288},
		{"2020bb", "030-c3.bin", 1048576, 0x47fddfee, 0, 524288},
	},
	{
		FULL_COPY,
		{"2020bb", "2020_c4.rom", 524288, 0xbef75dd0, 0, 524288},
		{"2020bb", "030-c4.bin", 1048576, 0x780d1c4e, 0, 524288},
	},
	{
		FULL_COPY,
		{"2020bbh", "2020_c3.rom", 524288, 0x6a87ae30, 0, 524288},
		{"2020bbh", "030-c3.bin", 1048576, 0x47fddfee, 0, 524288},
	},
	{
		FULL_COPY,
		{"2020bbh", "2020_c4.rom", 524288, 0xbef75dd0, 0, 524288},
		{"2020bbh", "030-c4.bin", 1048576, 0x780d1c4e, 0, 524288},
	},
	{
		FULL_COPY,
		{"sonicwi2", "afig2_v2.rom", 524288, 0x6d0a728e, 0, 524288},
		{"sonicwi2", "075-v2.bin", 1048576, 0x021760cd, 0, 524288},
	},
	{
		FULL_COPY,
		{"breakrev", "brev_c5.rom", 2097152, 0x28ff1792, 0, 2097152},
		{"breakrev", "245-c5.bin", 4194304, 0xb5f40e7f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"breakrev", "brev_c6.rom", 2097152, 0x23c65644, 0, 2097152},
		{"breakrev", "245-c6.bin", 4194304, 0xd0337328, 0, 2097152},
	},
	{
		FULL_COPY,
		{"gururin", "gurin_m1.rom", 65536, 0x833cdf1b, 0, 65536},
		{"gururin", "067-m1.bin", 131072, 0xe777a234, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "maj_m1.rom", 65536, 0x37965a73, 0, 65536},
		{"mahretsu", "004-m1.bin", 131072, 0xc71fbb3b, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "maj_s1.rom", 65536, 0xb0d16529, 0, 65536},
		{"mahretsu", "004-s1.bin", 131072, 0x4e310702, 0, 65536},
	},
	{
		FULL_COPY,
		{"cyberlip", "cybl_m1.rom", 65536, 0x47980d3a, 0, 65536},
		{"cyberlip", "010-m1.bin", 131072, 0x8be3a078, 0, 65536},
	},
	{
		FULL_COPY,
		{"maglord", "magl_m1.rom", 65536, 0x91ee1f73, 0, 65536},
		{"maglord", "005-m1.bin", 262144, 0x26259f0f, 0, 65536},
	},
	{
		FULL_COPY,
		{"maglordh", "magl_m1.rom", 65536, 0x91ee1f73, 0, 65536},
		{"maglordh", "005-m1.bin", 262144, 0x26259f0f, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 0, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 65536, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{0}
};

struct Rom nebula_roms[] =
{
	{
		FULL_COPY,
		{"breakrev", "245-c5.bin", 2097152, 0x28ff1792, 0, 2097152},
		{"breakrev", "245-c5.bin", 4194304, 0xb5f40e7f, 0, 2097152},
	},
	{
		FULL_COPY,
		{"breakrev", "245-c6.bin", 2097152, 0x23c65644, 0, 2097152},
		{"breakrev", "245-c6.bin", 4194304, 0xd0337328, 0, 2097152},
	},
	{
		FULL_COPY,
		{"gururin", "067-m1.bin", 65536, 0x833cdf1b, 0, 65536},
		{"gururin", "067-m1.bin", 131072, 0xe777a234, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "004-m1.bin", 65536, 0x37965a73, 0, 65536},
		{"mahretsu", "004-m1.bin", 131072, 0xc71fbb3b, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "004-s1.bin", 65536, 0xb0d16529, 0, 65536},
		{"mahretsu", "004-s1.bin", 131072, 0x4e310702, 0, 65536},
	},
	{
		FULL_COPY,
		{"cyberlip", "010-m1.bin", 65536, 0x47980d3a, 0, 65536},
		{"cyberlip", "010-m1.bin", 131072, 0x8be3a078, 0, 65536},
	},
	{
		FULL_COPY,
		{"maglord", "005-m1.bin", 65536, 0x91ee1f73, 0, 65536},
		{"maglord", "005-m1.bin", 262144, 0x26259f0f, 0, 65536},
	},
	{
		FULL_COPY,
		{"maglordh", "005-m1.bin", 65536, 0x91ee1f73, 0, 65536},
		{"maglordh", "005-m1.bin", 262144, 0x26259f0f, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 0, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 65536, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{0}
};

struct Rom nebula_jukebox_roms[] =
{
	{
		FULL_COPY,
		{"von2", "srom2.u23", 2097152, 0x89f21281, 0, 2097152},
		{"von2", "mpr-20664.23", 4194304, 0x89220782, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"von2", "srom4.u25", 2097152, 0xb7c1bebf, 0, 2097152},
		{"von2", "mpr-20666.25", 4194304, 0x3ecb2606, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"sonicwi2", "075-v2.bin", 524288, 0x6d0a728e, 0, 524288},
		{"sonicwi2", "075-v2.bin", 1048576, 0x021760cd, 0, 524288},
	},
	{
		FULL_COPY,
		{"gururin", "067-m1.bin", 65536, 0x833cdf1b, 0, 65536},
		{"gururin", "067-m1.bin", 131072, 0xe777a234, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "004-m1.bin", 65536, 0x37965a73, 0, 65536},
		{"mahretsu", "004-m1.bin", 131072, 0xc71fbb3b, 0, 65536},
	},
	{
		FULL_COPY,
		{"cyberlip", "010-m1.bin", 65536, 0x47980d3a, 0, 65536},
		{"cyberlip", "010-m1.bin", 131072, 0x8be3a078, 0, 65536},
	},
	{
		FULL_COPY,
		{"maglord", "005-m1.bin", 65536, 0x91ee1f73, 0, 65536},
		{"maglord", "005-m1.bin", 262144, 0x26259f0f, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 0, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 65536, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{0}
};

struct Rom neojukebox_roms[] =
{
	{
		FULL_COPY,
		{"gururin", "067_m1.rom", 65536, 0x833cdf1b, 0, 65536},
		{"gururin", "067-m1.bin", 131072, 0xe777a234, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "004_m1.rom", 65536, 0x37965a73, 0, 65536},
		{"mahretsu", "004-m1.bin", 131072, 0xc71fbb3b, 0, 65536},
	},
	{
		FULL_COPY,
		{"cyberlip", "010_m1.rom", 65536, 0x47980d3a, 0, 65536},
		{"cyberlip", "010-m1.bin", 131072, 0x8be3a078, 0, 65536},
	},
	{
		FULL_COPY,
		{"maglord", "005_m1.rom", 65536, 0x91ee1f73, 0, 65536},
		{"maglord", "005-m1.bin", 262144, 0x26259f0f, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027_m1.rom", 131072, 0xadd5a226, 0, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027_m1.rom", 131072, 0xadd5a226, 65536, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{0}
};

struct Rom rcps_roms[] =
{
	// MAME v0.80 Changes
	{
		FULL_COPY,
		{"aof3", "aof3_c1.rom", 4194304, 0xf6c74731, 0, 2097152},
		{"aof3", "096-c1.bin", 4194304, 0xf17b8d89, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c2.rom", 4194304, 0xf587f149, 0, 2097152},
		{"aof3", "096-c2.bin", 4194304, 0x3840c508, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c3.rom", 4194304, 0x7749f5e6, 0, 2097152},
		{"aof3", "096-c3.bin", 4194304, 0x55f9ee1e, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c4.rom", 4194304, 0xcbd58369, 0, 2097152},
		{"aof3", "096-c4.bin", 4194304, 0x585b7e47, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c5.rom", 4194304, 0x1718bdcd, 0, 2097152},
		{"aof3", "096-c5.bin", 4194304, 0xc75a753c, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c6.rom", 4194304, 0x4fca967f, 0, 2097152},
		{"aof3", "096-c6.bin", 4194304, 0x9a9d2f7a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c1.rom", 4194304, 0xf6c74731, 2097152, 2097152},
		{"aof3", "096-c1.bin", 4194304, 0xf17b8d89, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c2.rom", 4194304, 0xf587f149, 2097152, 2097152},
		{"aof3", "096-c2.bin", 4194304, 0x3840c508, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c3.rom", 4194304, 0x7749f5e6, 2097152, 2097152},
		{"aof3", "096-c3.bin", 4194304, 0x55f9ee1e, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c4.rom", 4194304, 0xcbd58369, 2097152, 2097152},
		{"aof3", "096-c4.bin", 4194304, 0x585b7e47, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c5.rom", 4194304, 0x1718bdcd, 2097152, 2097152},
		{"aof3", "096-c5.bin", 4194304, 0xc75a753c, 0, 2097152},
	},
	{
		FULL_COPY,
		{"aof3", "aof3_c6.rom", 4194304, 0x4fca967f, 2097152, 2097152},
		{"aof3", "096-c6.bin", 4194304, 0x9a9d2f7a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c1.rom", 4194304, 0xd00bd152, 0, 2097152},
		{"mslug", "201-c1.bin", 4194304, 0x72813676, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c2.rom", 4194304, 0xddff1dea, 0, 2097152},
		{"mslug", "201-c2.bin", 4194304, 0x96f62574, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c3.rom", 4194304, 0xd3d5f9e5, 0, 2097152},
		{"mslug", "201-c3.bin", 4194304, 0x5121456a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c4.rom", 4194304, 0x5ac1d497, 0, 2097152},
		{"mslug", "201-c4.bin", 4194304, 0xf4ad59a3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c1.rom", 4194304, 0xd00bd152, 2097152, 2097152},
		{"mslug", "201-c1.bin", 4194304, 0x72813676, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c2.rom", 4194304, 0xddff1dea, 2097152, 2097152},
		{"mslug", "201-c2.bin", 4194304, 0x96f62574, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c3.rom", 4194304, 0xd3d5f9e5, 2097152, 2097152},
		{"mslug", "201-c3.bin", 4194304, 0x5121456a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"mslug", "mslug_c4.rom", 4194304, 0x5ac1d497, 2097152, 2097152},
		{"mslug", "201-c4.bin", 4194304, 0xf4ad59a3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c1.rom", 4194304, 0x62c5edc9, 0, 2097152},
		{"neodrift", "213-c1.bin", 4194304, 0x3edc8bd3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c2.rom", 4194304, 0x9dc9c72a, 0, 2097152},
		{"neodrift", "213-c2.bin", 4194304, 0x46ae5f16, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c1.rom", 4194304, 0x62c5edc9, 2097152, 2097152},
		{"neodrift", "213-c1.bin", 4194304, 0x3edc8bd3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"neodrift", "drift_c2.rom", 4194304, 0x9dc9c72a, 2097152, 2097152},
		{"neodrift", "213-c2.bin", 4194304, 0x46ae5f16, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c1.rom", 4194304, 0x63020fc6, 0, 2097152},
		{"pulstar", "089-c1.bin", 4194304, 0xf4e97332, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c2.rom", 4194304, 0x260e9d4d, 0, 2097152},
		{"pulstar", "089-c2.bin", 4194304, 0x836d14da, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c3.rom", 4194304, 0x21ef41d7, 0, 2097152},
		{"pulstar", "089-c3.bin", 4194304, 0x913611c4, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c4.rom", 4194304, 0x3b9e288f, 0, 2097152},
		{"pulstar", "089-c4.bin", 4194304, 0x44cef0e3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c5.rom", 4194304, 0x6fe9259c, 0, 2097152},
		{"pulstar", "089-c5.bin", 4194304, 0x89baa1d7, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c6.rom", 4194304, 0xdc32f2b4, 0, 2097152},
		{"pulstar", "089-c6.bin", 4194304, 0xb2594d56, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c1.rom", 4194304, 0x63020fc6, 2097152, 2097152},
		{"pulstar", "089-c1.bin", 4194304, 0xf4e97332, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c2.rom", 4194304, 0x260e9d4d, 2097152, 2097152},
		{"pulstar", "089-c2.bin", 4194304, 0x836d14da, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c3.rom", 4194304, 0x21ef41d7, 2097152, 2097152},
		{"pulstar", "089-c3.bin", 4194304, 0x913611c4, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c4.rom", 4194304, 0x3b9e288f, 2097152, 2097152},
		{"pulstar", "089-c4.bin", 4194304, 0x44cef0e3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c5.rom", 4194304, 0x6fe9259c, 2097152, 2097152},
		{"pulstar", "089-c5.bin", 4194304, 0x89baa1d7, 0, 2097152},
	},
	{
		FULL_COPY,
		{"pulstar", "pstar_c6.rom", 4194304, 0xdc32f2b4, 2097152, 2097152},
		{"pulstar", "089-c6.bin", 4194304, 0xb2594d56, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c1.rom", 4194304, 0xaad087fc, 0, 2097152},
		{"shocktro", "238-c1.bin", 4194304, 0x90c6a181, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c2.rom", 4194304, 0x7e39df1f, 0, 2097152},
		{"shocktro", "238-c2.bin", 4194304, 0x888720f0, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c3.rom", 4194304, 0x6682a458, 0, 2097152},
		{"shocktro", "238-c3.bin", 4194304, 0x2c393aa3, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c4.rom", 4194304, 0xcbef1f17, 0, 2097152},
		{"shocktro", "238-c4.bin", 4194304, 0xb9e909eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c5.rom", 4194304, 0xe17762b1, 0, 2097152},
		{"shocktro", "238-c5.bin", 4194304, 0xc22c68eb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c6.rom", 4194304, 0x28beab71, 0, 2097152},
		{"shocktro", "238-c6.bin", 4194304, 0x119323cd, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c7.rom", 4194304, 0xa47e62d2, 0, 2097152},
		{"shocktro", "238-c7.bin", 4194304, 0xa72ce7ed, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c8.rom", 4194304, 0xe8e890fb, 0, 2097152},
		{"shocktro", "238-c8.bin", 4194304, 0x1c7c2efb, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_p2.rom", 4194304, 0x646f6c76, 0, 2097152},
		{"shocktro", "238-p2.bin", 4194304, 0x5b4a09c5, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c1.rom", 4194304, 0xaad087fc, 2097152, 2097152},
		{"shocktro", "238-c1.bin", 4194304, 0x90c6a181, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c2.rom", 4194304, 0x7e39df1f, 2097152, 2097152},
		{"shocktro", "238-c2.bin", 4194304, 0x888720f0, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c3.rom", 4194304, 0x6682a458, 2097152, 2097152},
		{"shocktro", "238-c3.bin", 4194304, 0x2c393aa3, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c4.rom", 4194304, 0xcbef1f17, 2097152, 2097152},
		{"shocktro", "238-c4.bin", 4194304, 0xb9e909eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c5.rom", 4194304, 0xe17762b1, 2097152, 2097152},
		{"shocktro", "238-c5.bin", 4194304, 0xc22c68eb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c6.rom", 4194304, 0x28beab71, 2097152, 2097152},
		{"shocktro", "238-c6.bin", 4194304, 0x119323cd, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c7.rom", 4194304, 0xa47e62d2, 2097152, 2097152},
		{"shocktro", "238-c7.bin", 4194304, 0xa72ce7ed, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_c8.rom", 4194304, 0xe8e890fb, 2097152, 2097152},
		{"shocktro", "238-c8.bin", 4194304, 0x1c7c2efb, 0, 2097152},
	},
	{
		FULL_COPY,
		{"shocktro", "shock_p2.rom", 4194304, 0x646f6c76, 2097152, 2097152},
		{"shocktro", "238-p2.bin", 4194304, 0x5b4a09c5, 0, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c1.rom", 4194304, 0x8c6733f2, 0, 2097152},
		{"turfmast", "200-c1.bin", 4194304, 0x8e7bf41a, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c2.rom", 4194304, 0x596cc256, 0, 2097152},
		{"turfmast", "200-c2.bin", 4194304, 0x5a65a8ce, 2097152, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c1.rom", 4194304, 0x8c6733f2, 2097152, 2097152},
		{"turfmast", "200-c1.bin", 4194304, 0x8e7bf41a, 0, 2097152},
	},
	{
		FULL_COPY,
		{"turfmast", "turfm_c2.rom", 4194304, 0x596cc256, 2097152, 2097152},
		{"turfmast", "200-c2.bin", 4194304, 0x5a65a8ce, 0, 2097152},
	},
	{
		FULL_COPY,
		{"wjammers", "windj_p1.rom", 524288, 0xe81e7a31, 0, 524288},
		{"wjammers", "065-p1.bin", 1048576, 0x6692c140, 0, 524288},
	},
	{
		FULL_COPY,
		{"wjammers", "windj_v4.rom", 524288, 0x3740edde, 0, 524288},
		{"wjammers", "065-v4.bin", 1048576, 0x5dee7963, 0, 524288},
	},
	{
		FULL_COPY,
		{"sonicwi2", "afig2_v2.rom", 524288, 0x6d0a728e, 0, 524288},
		{"sonicwi2", "075-v2.bin", 1048576, 0x021760cd, 0, 524288},
	},
	{
		FULL_COPY,
		{"maglord", "magl_m1.rom", 65536, 0x91ee1f73, 0, 65536},
		{"maglord", "005-m1.bin", 262144, 0x26259f0f, 0, 65536},
	},
	{0}
};

struct Rom junofirst_roms[] =
{
	{
		FULL_COPY,
		{"rtype2", "rt2_g00l.bin", 65536, 0xb79a958e, 0, 65536},
		{"rtype2", "ic50.7s", 131072, 0xf3f8736e, 0, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g00u.bin", 65536, 0x955beb3d, 0, 65536},
		{"rtype2", "ic50.7s", 131072, 0xf3f8736e, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g01l.bin", 65536, 0x9afc5896, 0, 65536},
		{"rtype2", "ic51.7u", 131072, 0xb4c543af, 0, 65536},
	},
	{
		BLOCK_FILL,
		{"rtype2", "rt2_g01u.bin", 65536, 0xd7978eeb, 0, 65536},
		{"      ", "	    ",     0, 0x00000000, 0,     0},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g10l.bin", 65536, 0x8453dca5, 0, 65536},
		{"rtype2", "ic56.8s", 131072, 0x4cb80d66, 0, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g10u.bin", 65536, 0x2bc7cf79, 0, 65536},
		{"rtype2", "ic56.8s", 131072, 0x4cb80d66, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g11l.bin", 65536, 0xd350c2c6, 0, 65536},
		{"rtype2", "ic57.8u", 131072, 0xbee128e0, 0, 65536},
	},
	{
		BLOCK_FILL,
		{"rtype2", "rt2_g11u.bin", 65536, 0xd7978eeb, 0, 65536},
		{"      ", "	    ",     0, 0x00000000, 0,     0},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g20l.bin", 65536, 0x1135b455, 0, 65536},
		{"rtype2", "ic65.9r", 131072, 0x2dc9c71a, 0, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g20u.bin", 65536, 0x48c4a6e0, 0, 65536},
		{"rtype2", "ic65.9r", 131072, 0x2dc9c71a, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g21l.bin", 65536, 0x8a6a29fa, 0, 65536},
		{"rtype2", "ic66.9u", 131072, 0x7533c428, 0, 65536},
	},
	{
		BLOCK_FILL,
		{"rtype2", "rt2_g21u.bin", 65536, 0xd7978eeb, 0, 65536},
		{"      ", "	    ",     0, 0x00000000, 0,     0},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g30l.bin", 65536, 0x77e2e8fc, 0, 65536},
		{"rtype2", "ic63.9m", 131072, 0xa6ad67f2, 0, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g30u.bin", 65536, 0xbff5e464, 0, 65536},
		{"rtype2", "ic63.9m", 131072, 0xa6ad67f2, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_g31l.bin", 65536, 0x5b64cbd5, 0, 65536},
		{"rtype2", "ic64.9p", 131072, 0x3686d555, 0, 65536},
	},
	{
		BLOCK_FILL,
		{"rtype2", "rt2_g31u.bin", 65536, 0xd7978eeb, 0, 65536},
		{"      ", "	    ",     0, 0x00000000, 0,     0},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_n0_l.bin", 65536, 0x78d2c8b2, 0, 65536},
		{"rtype2", "ic31.6l", 131072, 0x2cd8f913, 0, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_n0_u.bin", 65536, 0xb0a42f9c, 0, 65536},
		{"rtype2", "ic31.6l", 131072, 0x2cd8f913, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_n1_l.bin", 65536, 0xe3fcdc8b, 0, 65536},
		{"rtype2", "ic21.4l", 131072, 0x5033066d, 0, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_n1_u.bin", 65536, 0x48dc911e, 0, 65536},
		{"rtype2", "ic21.4l", 131072, 0x5033066d, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_n2_l.bin", 65536, 0x1591294a, 0, 65536},
		{"rtype2", "ic32.6m", 131072, 0xec3a0450, 0, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_n2_u.bin", 65536, 0xe898b182, 0, 65536},
		{"rtype2", "ic32.6m", 131072, 0xec3a0450, 65536, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_n3_l.bin", 65536, 0x696ac2b7, 0, 65536},
		{"rtype2", "ic22.4m", 131072, 0xdb6176fc, 0, 65536},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_n3_u.bin", 65536, 0xbfa202b1, 0, 65536},
		{"rtype2", "ic22.4m", 131072, 0xdb6176fc, 65536, 65536},
	},
	/* Experiment!
	{
		FULL_COPY,
		{"junoboot", "jfg1.cpu", 8192, 0x00000000, 0, 2789},
		{"junofrst", "jfc1_a4.bin",  8192, 0x03ccbf1d, 0, 2789},
	},
	{
		BLOCK_FILL,
		{"junoboot", "jfg1.cpu", 8192, 0x00000000, 2789, 816},
		{"      ", "	    ",     0, 0x00000000, 0,   0},
	},
	{
		FULL_COPY,
		{"junoboot", "jfg1.cpu", 8192, 0x00000000, 3605, 4587},
		{"junofrst", "jfc1_a4.bin",  8192, 0x03ccbf1d, 3605, 4587},
	},*/
	{
		FULL_COPY,
		{"rtype",   "cpu-01.bin", 65536, 0xb28d1a60,     0, 32768},
		{"rtypeu",  "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtype",   "cpu-01.bin", 65536, 0xb28d1a60, 32768, 32768},
		{"rtypeu",  "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtype",   "cpu-11.bin", 65536, 0xbb182f1a,     0, 32768},
		{"rtypeu",  "rt_r-11.1l", 32768, 0x791df4f8,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtype",   "cpu-11.bin", 65536, 0xbb182f1a, 32768, 32768},
		{"rtypeu",  "rt_r-11.1l", 32768, 0x791df4f8,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtype",   "cpu-21.bin", 65536, 0x5b41f5f3,     0, 32768},
		{"rtypeu",  "rt_r-21.3j", 32768, 0xed793841,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtype",   "cpu-21.bin", 65536, 0x5b41f5f3, 32768, 32768},
		{"rtypeu",  "rt_r-21.3j", 32768, 0xed793841,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtype",   "cpu-31.bin", 65536, 0x2bec510a,     0, 32768},
		{"rtypeu",  "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtype",   "cpu-31.bin", 65536, 0x2bec510a, 32768, 32768},
		{"rtypeu",  "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{0}
};


/* These patches are for R-Type II running on a Major Title board */

struct Patch patch_rt2_h1[] =
{
	{0x0001f07c, 0xa4},
	{0x0001f09a, 0xa4},
	{0x0001f09d, 0xcc},
	{0x0001f0b3, 0xb0},
	{0x0001f132, 0xb0},
	{0x0001f1be, 0xd0},
	{0x0001f235, 0xd0},
	{0x0001f34c, 0xb8},
	{0x0001f34d, 0xa0},
	{0x0001f34e, 0xc0},
	{0x0001f34f, 0xc0},
	{0x0001f350, 0xf8},
	{0x0001f351, 0x00},
	{0x0001f352, 0xf3},
	{0x0001f353, 0xb8},
	{0x0001f354, 0xc8},
	{0x0001f355, 0xc0},
	{0x0001f356, 0xc0},
	{0x0001f357, 0xf8},
	{0x0001f358, 0x00},
	{0x0001f359, 0xf3},
	{0x0001f35a, 0xb8},
	{0x0001f35b, 0x00},
	{0x0001f35c, 0x8c},
	{0x0001f35d, 0x13},
	{0x0001f35e, 0x40},
	{0}
};

struct Patch patch_rt2_l1[] =
{
	{0x0001f001, 0xb0},
	{0x0001f007, 0xac},
	{0x0001f058, 0xa4},
	{0x0001f0d3, 0xd0},
	{0x0001f0f7, 0xe0},
	{0x0001f10f, 0xb0},
	{0x0001f1f8, 0xb0},
	{0x0001f1fc, 0xac},
	{0x0001f200, 0xa4},
	{0x0001f204, 0xcc},
	{0x0001f237, 0x33},
	{0x0001f34d, 0x00},
	{0x0001f34e, 0x8e},
	{0x0001f34f, 0x33},
	{0x0001f350, 0x8b},
	{0x0001f351, 0xb9},
	{0x0001f352, 0x02},
	{0x0001f353, 0xab},
	{0x0001f354, 0x00},
	{0x0001f355, 0x8e},
	{0x0001f356, 0x33},
	{0x0001f357, 0x8b},
	{0x0001f358, 0xb9},
	{0x0001f359, 0x02},
	{0x0001f35a, 0xab},
	{0x0001f35b, 0x10},
	{0x0001f35c, 0xe7},
	{0x0001f35d, 0xea},
	{0x0001f35e, 0x00},
	{0x0001f35f, 0x10},
	{0}
};

struct Patch patch_rt2_l0[] =
{
	{0x00008207, 0xea},
	{0x00008208, 0x06},
	{0x00008209, 0x7e},
	{0x00008214, 0xd0},
	{0x0000822c, 0xd0},
	{0x00008275, 0xe0},
	{0x00008287, 0xd0},
	{0x00008294, 0xe0},
	{0x000083d1, 0xe0},
	{0x00008416, 0xe0},
	{0x00008911, 0xb0},
	{0x00008bf8, 0xb0},
	{0x00008c25, 0xb0},
	{0x00008c97, 0xb0},
	{0x00008d61, 0xb0},
	{0x00008eb5, 0xb0},
	{0x00009145, 0xd0},
	{0x0000939b, 0xb0},
	{0x00009442, 0xd0},
	{0x0000988a, 0xd0},
	{0x00009960, 0xd0},
	{0x00009b19, 0xb0},
	{0x00009b23, 0xac},
	{0x00009dc5, 0xac},
	{0x00009dd6, 0xb0},
	{0x0000a456, 0xb0},
	{0x0000a4e2, 0xb0},
	{0x0000a4fb, 0xb0},
	{0x0000a547, 0xb0},
	{0x0000ce38, 0xb0},
	{0x0000cecb, 0xb0},
	{0x0000cf16, 0xb0},
	{0x0000cf6b, 0xb0},
	{0x0000d22d, 0xb0},
	{0x0000e8f6, 0xb0},
	{0x0000e9b2, 0xb0},
	{0x0000eb5e, 0xb0},
	{0x0000f58f, 0xb0},
	{0x0000f5bf, 0xb0},
	{0x0000f5d0, 0xb0},
	{0x0000f5f2, 0xd0},
	{0x0000f658, 0xb0},
	{0x0000f687, 0xb0},
	{0x0000f787, 0xb0},
	{0x0000f793, 0xac},
	{0x0000f8bd, 0xb0},
	{0x0000f8ea, 0xb0},
	{0x0000f929, 0xb0},
	{0x0000f938, 0xb0},
	{0x0000fddf, 0xb0},
	{0x00010247, 0xd0},
	{0x00011007, 0xac},
	{0x000110a8, 0xac},
	{0x00011462, 0xd0},
	{0x0001148d, 0xa4},
	{0x0001228a, 0xd0},
	{0x00012379, 0xa4},
	{0x000123af, 0xd0},
	{0x000123d3, 0xe0},
	{0x00012411, 0xb0},
	{0x00012495, 0xd0},
	{0x000124d2, 0xb0},
	{0x000124df, 0xa4},
	{0x00012528, 0x33},
	{0x00012611, 0xe0},
	{0}
};

struct Patch patch_rt2_h0[] =
{
	{0x00008207, 0x99},
	{0x00008208, 0x00},
	{0x000083a5, 0xe0},
	{0x0000844b, 0xe0},
	{0x00008a1a, 0xb0},
	{0x00008b6a, 0xd0},
	{0x00008c5d, 0xb0},
	{0x00008ce4, 0xb0},
	{0x00008cf7, 0xb0},
	{0x00008ed1, 0xb0},
	{0x00008ee5, 0xb0},
	{0x0000939f, 0xac},
	{0x000095b0, 0xb0},
	{0x00009753, 0xb0},
	{0x000097ef, 0xac},
	{0x00009db8, 0xb0},
	{0x00009de2, 0xac},
	{0x0000a12d, 0xb0},
	{0x0000a1ca, 0xb0},
	{0x0000a2b1, 0xb0},
	{0x0000a45b, 0xac},
	{0x0000a4eb, 0xb0},
	{0x0000a504, 0xb0},
	{0x0000a57f, 0xac},
	{0x0000acbc, 0xb0},
	{0x0000ceb4, 0xb0},
	{0x0000ceff, 0xb0},
	{0x0000cf4a, 0xb0},
	{0x0000cfde, 0xb0},
	{0x0000e90a, 0xb0},
	{0x0000e9c6, 0xb0},
	{0x0000e9e7, 0xb0},
	{0x0000f200, 0xb0},
	{0x0000f599, 0xb0},
	{0x0000f5a2, 0xb0},
	{0x0000f5ab, 0xb0},
	{0x0000f5b4, 0xac},
	{0x0000f5c7, 0xac},
	{0x0000f5dc, 0xac},
	{0x0000f674, 0xb0},
	{0x0000f6f9, 0xb0},
	{0x0000f7fb, 0xb0},
	{0x0000f807, 0xac},
	{0x0000f8a6, 0xb0},
	{0x0000f8fa, 0xb0},
	{0x0000f910, 0xac},
	{0x0000f955, 0xb0},
	{0x0000fb47, 0xb0},
	{0x00010ff0, 0xb0},
	{0x00011091, 0xb0},
	{0x000113cd, 0xb0},
	{0x00011464, 0xcc},
	{0x0001148a, 0xd0},
	{0x000122b8, 0xb0},
	{0x000122be, 0xac},
	{0x00012342, 0xa4},
	{0x00012362, 0xcc},
	{0x0001238f, 0xb0},
	{0x000123ed, 0xb0},
	{0x000124d8, 0xac},
	{0x000124eb, 0xcc},
	{0x00012526, 0xd0},
	{0x00012539, 0xd0},
	{0x00012603, 0xe0},
	{0x00012616, 0xb0},
	{0x00012642, 0xb0},
	{0x0001265a, 0xb0},
	{0}
};

struct Rom rage_roms[] =
{
	{
		FULL_COPY,
		{"sonson", "ss7.v12", 16384, 0x32b14b8e, 0, 8192},
		{"sonson", "ss_9.m5", 8192, 0x8cb1cacf, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss7.v12", 16384, 0x32b14b8e, 8192, 8192},
		{"sonson", "ss_10.m6", 8192, 0xf802815e, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss8.v12", 16384, 0x9f59014e, 0, 8192},
		{"sonson", "ss_11.m3", 8192, 0x4dbad88a, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss8.v12", 16384, 0x9f59014e, 8192, 8192},
		{"sonson", "ss_12.m4", 8192, 0xaa05e687, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss9.v12", 16384, 0x517fa26d, 0, 8192},
		{"sonson", "ss_13.m1", 8192, 0x66119bfa, 0, 8192},
	},
	{
		FULL_COPY,
		{"sonson", "ss9.v12", 16384, 0x517fa26d, 8192, 8192},
		{"sonson", "ss_14.m2", 8192, 0xe14ef54e, 0, 8192},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b0.rom", 131072, 0xfe629815,     0, 65536},
		{"nspirit", "nin-b0.rom",  65536, 0x1b0e08a6,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b0.rom", 131072, 0xfe629815, 65536, 65536},
		{"nspirit", "nin-b0.rom",  65536, 0x1b0e08a6,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b1.rom", 131072, 0x667966af,     0, 65536},
		{"nspirit", "nin-b1.rom",  65536, 0x728727f0,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b1.rom", 131072, 0x667966af, 65536, 65536},
		{"nspirit", "nin-b1.rom",  65536, 0x728727f0,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b2.rom", 131072, 0x3e922f9b,     0, 65536},
		{"nspirit", "nin-b2.rom",  65536, 0xf87efd75,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b2.rom", 131072, 0x3e922f9b, 65536, 65536},
		{"nspirit", "nin-b2.rom",  65536, 0xf87efd75,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b3.rom", 131072, 0x092d6291,     0, 65536},
		{"nspirit", "nin-b3.rom",  65536, 0x98856cb4,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b3.rom", 131072, 0x092d6291, 65536, 65536},
		{"nspirit", "nin-b3.rom",  65536, 0x98856cb4,     0, 65536},
	},
	/* Noticed missing in MAME 0.118 but could have disappeared long ago! No longer required anway.
	{
		FULL_COPY,
		{"rtypejp", "db_d2.bin",   32768, 0x791df4f8,     0, 32768},
		{"rtypejp", "rt_r-11.1l",  65536, 0xbb182f1a,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_c2.bin",   32768, 0xed793841,     0, 32768},
		{"rtypejp", "rt_r-21.3j",  65536, 0x5b41f5f3,     0, 32768},
	},
	*/
	{
		FULL_COPY,
		{"rtype2",  "rt2_c0.bin", 262144, 0xf5bad5f2,      0, 131072},
		{"rtype2",  "ic50.7s",    131072, 0xf3f8736e,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c0.bin", 262144, 0xf5bad5f2, 131072, 131072},
		{"rtype2",  "ic51.7u",    131072, 0xb4c543af,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c1.bin", 262144, 0x71451778,      0, 131072},
		{"rtype2",  "ic56.8s",    131072, 0x4cb80d66,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c1.bin", 262144, 0x71451778, 131072, 131072},
		{"rtype2",  "ic57.8u",    131072, 0xbee128e0,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c2.bin", 262144, 0xc6b0c352,      0, 131072},
		{"rtype2",  "ic65.9r",    131072, 0x2dc9c71a,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c2.bin", 262144, 0xc6b0c352, 131072, 131072},
		{"rtype2",  "ic66.9u",    131072, 0x7533c428,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c3.bin", 262144, 0x6d530a32,      0, 131072},
		{"rtype2",  "ic63.9m",    131072, 0xa6ad67f2,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c3.bin", 262144, 0x6d530a32, 131072, 131072},
		{"rtype2",  "ic64.9p",    131072, 0x3686d555,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_h1.bin", 131072, 0x4b79840c, 0, 131072},
		{"rtype2", "ic53.8b",    131072, 0x4f6e9b15, 0, 131072},
		patch_rt2_h1
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_l1.bin", 131072, 0x6ab3ae42, 0, 131072},
		{"rtype2", "ic59.9b",    131072, 0x0fd123bf, 0, 131072},
		patch_rt2_l1
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_l0.bin", 131072, 0xa1661cdf, 0, 131072},
		{"rtype2", "ic60.9d",    131072, 0x32cfb2e4, 0, 131072},
		patch_rt2_l0
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_h0.bin", 131072, 0x47639a78, 0, 131072},
		{"rtype2", "ic54.8d",    131072, 0xd8ece6f4, 0, 131072},
		patch_rt2_h0
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-01.bin", 65536, 0xb28d1a60,     0, 32768},
		{"rtypeu",  "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-01.bin", 65536, 0xb28d1a60, 32768, 32768},
		{"rtypeu",  "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-11.bin", 65536, 0xbb182f1a,     0, 32768},
		{"rtypeu",  "rt_r-11.1l", 32768, 0x791df4f8,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-11.bin", 65536, 0xbb182f1a, 32768, 32768},
		{"rtypeu",  "rt_r-11.1l", 32768, 0x791df4f8,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-21.bin", 65536, 0x5b41f5f3,     0, 32768},
		{"rtypeu",  "rt_r-21.3j", 32768, 0xed793841,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-21.bin", 65536, 0x5b41f5f3, 32768, 32768},
		{"rtypeu",  "rt_r-21.3j", 32768, 0xed793841,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-31.bin", 65536, 0x2bec510a,     0, 32768},
		{"rtypeu",  "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-31.bin", 65536, 0x2bec510a, 32768, 32768},
		{"rtypeu",  "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_d3.bin",  65536, 0xb28d1a60,     0, 32768},
		{"rtypejp", "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_d3.bin",  65536, 0xb28d1a60, 32768, 32768},
		{"rtypejp", "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_a3.bin",  65536, 0x2bec510a,     0, 32768},
		{"rtypejp", "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_a3.bin",  65536, 0x2bec510a, 32768, 32768},
		{"rtypejp", "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{0}
};

struct Rom hoot_roms[] =
{
	{
		FULL_COPY,
		{"gaiapols", "123e13.9c", 524288,  0x0bc4056c,     0, 262144},
		{"gaiapols", "123e13.9c", 262144,  0xe772f822,     0, 262144},
	},
	{
		FULL_COPY,
		{"gaiapols", "123e13.9c", 524288,  0x0bc4056c, 262144, 262144},
		{"gaiapols", "123e13.9c", 262144,  0xe772f822,      0, 262144},
	},
	{0}
};

struct Rom m1_roms[] =
{
	{
		FULL_COPY,
		{"gururin", "067-m1.bin", 65536, 0x833cdf1b, 0, 65536},
		{"gururin", "067-m1.bin", 131072, 0xe777a234, 0, 65536},
	},
	{
		FULL_COPY,
		{"mahretsu", "004-m1.bin", 65536, 0x37965a73, 0, 65536},
		{"mahretsu", "004-m1.bin", 131072, 0xc71fbb3b, 0, 65536},
	},
	{
		FULL_COPY,
		{"cyberlip", "010-m1.bin", 65536, 0x47980d3a, 0, 65536},
		{"cyberlip", "010-m1.bin", 131072, 0x8be3a078, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 0, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 65536, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{0}
};

struct Rom m72_roms[] =
{
	{
		FULL_COPY,
		{"nspirit", "nin-b0.rom", 131072, 0xfe629815,     0, 65536},
		{"nspirit", "nin-b0.rom",  65536, 0x1b0e08a6,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b0.rom", 131072, 0xfe629815, 65536, 65536},
		{"nspirit", "nin-b0.rom",  65536, 0x1b0e08a6,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b1.rom", 131072, 0x667966af,     0, 65536},
		{"nspirit", "nin-b1.rom",  65536, 0x728727f0,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b1.rom", 131072, 0x667966af, 65536, 65536},
		{"nspirit", "nin-b1.rom",  65536, 0x728727f0,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b2.rom", 131072, 0x3e922f9b,     0, 65536},
		{"nspirit", "nin-b2.rom",  65536, 0xf87efd75,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b2.rom", 131072, 0x3e922f9b, 65536, 65536},
		{"nspirit", "nin-b2.rom",  65536, 0xf87efd75,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b3.rom", 131072, 0x092d6291,     0, 65536},
		{"nspirit", "nin-b3.rom",  65536, 0x98856cb4,     0, 65536},
	},
	{
		FULL_COPY,
		{"nspirit", "nin-b3.rom", 131072, 0x092d6291, 65536, 65536},
		{"nspirit", "nin-b3.rom",  65536, 0x98856cb4,     0, 65536},
	},
	/* Noticed missing in MAME 0.118 but could have disappeared long ago! No longer required anway.
	{
		FULL_COPY,
		{"rtypejp", "db_d2.bin",   32768, 0x791df4f8,     0, 32768},
		{"rtypejp", "rt_r-11.1l",  65536, 0xbb182f1a,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_c2.bin",   32768, 0xed793841,     0, 32768},
		{"rtypejp", "rt_r-21.3j",  65536, 0x5b41f5f3,     0, 32768},
	},
	*/
	{
		FULL_COPY,
		{"rtype2",  "rt2_c0.bin", 262144, 0xf5bad5f2,      0, 131072},
		{"rtype2",  "ic50.7s",    131072, 0xf3f8736e,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c0.bin", 262144, 0xf5bad5f2, 131072, 131072},
		{"rtype2",  "ic51.7u",    131072, 0xb4c543af,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c1.bin", 262144, 0x71451778,      0, 131072},
		{"rtype2",  "ic56.8s",    131072, 0x4cb80d66,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c1.bin", 262144, 0x71451778, 131072, 131072},
		{"rtype2",  "ic57.8u",    131072, 0xbee128e0,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c2.bin", 262144, 0xc6b0c352,      0, 131072},
		{"rtype2",  "ic65.9r",    131072, 0x2dc9c71a,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c2.bin", 262144, 0xc6b0c352, 131072, 131072},
		{"rtype2",  "ic66.9u",    131072, 0x7533c428,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c3.bin", 262144, 0x6d530a32,      0, 131072},
		{"rtype2",  "ic63.9m",    131072, 0xa6ad67f2,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2",  "rt2_c3.bin", 262144, 0x6d530a32, 131072, 131072},
		{"rtype2",  "ic64.9p",    131072, 0x3686d555,      0, 131072},
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_h1.bin", 131072, 0x4b79840c, 0, 131072},
		{"rtype2", "ic53.8b",    131072, 0x4f6e9b15, 0, 131072},
		patch_rt2_h1
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_l1.bin", 131072, 0x6ab3ae42, 0, 131072},
		{"rtype2", "ic59.9b",    131072, 0x0fd123bf, 0, 131072},
		patch_rt2_l1
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_l0.bin", 131072, 0xa1661cdf, 0, 131072},
		{"rtype2", "ic60.9d",    131072, 0x32cfb2e4, 0, 131072},
		patch_rt2_l0
	},
	{
		FULL_COPY,
		{"rtype2", "rt2_h0.bin", 131072, 0x47639a78, 0, 131072},
		{"rtype2", "ic54.8d",    131072, 0xd8ece6f4, 0, 131072},
		patch_rt2_h0
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-01.bin", 65536, 0xb28d1a60,     0, 32768},
		{"rtypeu",  "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-01.bin", 65536, 0xb28d1a60, 32768, 32768},
		{"rtypeu",  "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-11.bin", 65536, 0xbb182f1a,     0, 32768},
		{"rtypeu",  "rt_r-11.1l", 32768, 0x791df4f8,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-11.bin", 65536, 0xbb182f1a, 32768, 32768},
		{"rtypeu",  "rt_r-11.1l", 32768, 0x791df4f8,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-21.bin", 65536, 0x5b41f5f3,     0, 32768},
		{"rtypeu",  "rt_r-21.3j", 32768, 0xed793841,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-21.bin", 65536, 0x5b41f5f3, 32768, 32768},
		{"rtypeu",  "rt_r-21.3j", 32768, 0xed793841,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-31.bin", 65536, 0x2bec510a,     0, 32768},
		{"rtypeu",  "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypeus", "cpu-31.bin", 65536, 0x2bec510a, 32768, 32768},
		{"rtypeu",  "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_d3.bin",  65536, 0xb28d1a60,     0, 32768},
		{"rtypejp", "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_d3.bin",  65536, 0xb28d1a60, 32768, 32768},
		{"rtypejp", "rt_r-01.1j", 32768, 0x5e441e7f,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_a3.bin",  65536, 0x2bec510a,     0, 32768},
		{"rtypejp", "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{
		FULL_COPY,
		{"rtypejp", "db_a3.bin",  65536, 0x2bec510a, 32768, 32768},
		{"rtypejp", "rt_r-31.3l", 32768, 0x8558355d,     0, 32768},
	},
	{0}
};

struct Rom zem_roms[] =
{
	{
		FULL_COPY,
		{"wbdeluxe", "wb.004",       32768, 0x8b3124e6,      0, 16384},
		{"wbdeluxe", "epr-7485.117",  16384, 0xc2891722,      0, 16384},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.004",       32768, 0x8b3124e6,  16384, 16384},
		{"wbdeluxe", "epr-7486.110",  16384, 0x8d622c50,      0, 16384},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.005",       32768, 0xb75278e7,      0, 16384},
		{"wbdeluxe", "epr-7487.04",   16384, 0x2d3a421b,      0, 16384},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.005",       32768, 0xb75278e7,  16384, 16384},
		{"wbdeluxe", "epr-7488.05",   16384, 0x007c2f1b,      0, 16384},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.006",       16384, 0xe812b3ec,      0, 8192},
		{"wbdeluxe", "epr-7493.66",   8192,  0x89305df4,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.006",       16384, 0xe812b3ec,   8192, 8192},
		{"wbdeluxe", "epr-7492.65",   8192,  0x60f806b1,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.007",       16384, 0x87ecba53,      0, 8192},
		{"wbdeluxe", "epr-7495.64",   8192,  0x6a0d2c2d,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.007",       16384, 0x87ecba53,   8192, 8192},
		{"wbdeluxe", "epr-7494.63",   8192,  0xa8e281c7,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.008",       16384, 0x1685d26a,      0, 8192},
		{"wbdeluxe", "epr-7497.62",   8192,  0x08d609ca,      0, 8192},
	},
	{
		FULL_COPY,
		{"wbdeluxe", "wb.008",       16384, 0x1685d26a,   8192, 8192},
		{"wbdeluxe", "epr-7496.61",   8192,  0x6f61fdf1,      0, 8192},
	},
	{
		FULL_COPY,
		{"wb_mland", "ml1a.bin", 32768, 0x39e07286,     0, 32768},
		{"wbmlb",    "wbml.03",  65536, 0xd57ba8aa, 32768, 32768},
	},
	{0}
};

struct Rom segasystemc2_roms[] =
{
	{
		FULL_COPY,
		{"tfacbl",   "2.bin",	131072, 0x07ae0ff9,      0, 131072},
		{"tfrceacb", "ic4.bin",      262144, 0xe09961f6,      0, 131072},
	},
	{
		FULL_COPY,
		{"tfacbl",   "1.bin",	131072, 0x4e2ca65a,      0, 131072},
		{"tfrceacb", "ic4.bin",      262144, 0xe09961f6, 131072, 131072},
	},
	{0}
};

struct Rom besnowbros_roms[] =
{
	{
		FULL_COPY,
		{"snowbroa", "CH0", 131072, 0x36d84dfe, 0, 131072},
		{"snowbrosa", "sbros-1.41", 524288, 0x16f06b3a, 0, 131072},
	},
	{
		FULL_COPY,
		{"snowbroa", "CH1", 131072, 0x76347256, 0, 131072},
		{"snowbrosa", "sbros-1.41", 524288, 0x16f06b3a, 131072, 131072},
	},
	{
		FULL_COPY,
		{"snowbroa", "CH2", 131072, 0xfdaa634c, 0, 131072},
		{"snowbrosa", "sbros-1.41", 524288, 0x16f06b3a, 262144, 131072},
	},
	{
		FULL_COPY,
		{"snowbroa", "CH3", 131072, 0x34024aef, 0, 131072},
		{"snowbrosa", "sbros-1.41", 524288, 0x16f06b3a, 393216, 131072},
	},
	{0}
};

struct Rom cinelator95_roms[] =
{
	{
		FULL_COPY,
		{"speedfrk", "0470-21", 1024, 0x3228d5cf, 0, 1024},
		{"speedfrk", "speedfrk.u7", 2048, 0x616c7cf9, 0, 1024},
	},
	{
		FULL_COPY,
		{"speedfrk", "0470-27", 1024, 0x8bce0552, 0, 1024},
		{"speedfrk", "speedfrk.p7", 2048, 0x4b90cdec, 0, 1024},
	},
	{
		FULL_COPY,
		{"speedfrk", "0470-25", 1024, 0x5090ea03, 0, 1024},
		{"speedfrk", "speedfrk.r7", 2048, 0xfbe90d63, 0, 1024},
	},
	{
		FULL_COPY,
		{"speedfrk", "0470-23", 1024, 0xd79bf1fd, 0, 1024},
		{"speedfrk", "speedfrk.t7", 2048, 0x3552c03f, 0, 1024},
	},
	{
		FULL_COPY,
		{"speedfrk", "0470-26", 1024, 0xd00bb842, 0, 1024},
		{"speedfrk", "speedfrk.r7", 2048, 0xfbe90d63, 1024, 1024},
	},
	{
		FULL_COPY,
		{"speedfrk", "0470-24", 1024, 0xff27a073, 0, 1024},
		{"speedfrk", "speedfrk.t7", 2048, 0x3552c03f, 1024, 1024},
	},
	{
		FULL_COPY,
		{"speedfrk", "0470-22", 1024, 0x3ca350f4, 0, 1024},
		{"speedfrk", "speedfrk.u7", 2048, 0x616c7cf9, 1024, 1024},
	},
	{
		FULL_COPY,
		{"speedfrk", "0470-28", 1024, 0xca8afcbe, 0, 1024},
		{"speedfrk", "speedfrk.p7", 2048, 0x4b90cdec, 1024, 1024},
	},
	{0}
};

struct Rom mge_roms[] =
{
	{
		FULL_COPY,
		{"gaunt",     "gaunt.6p",  16384, 0x6c276a1d, 0, 8192},
		{"gauntlet",  "136037-104.6p", 8192, 0x9e2a5b59, 0, 8192},
	},
	{
		BLOCK_FILL,
		{"gaunt",     "gaunt.6p",  16384, 0x6c276a1d, 8192, 8192},
		{"      ", "	    ",     0, 0x00000000, 0,     0},
	},
	{
		FULL_COPY,
		{"gaunt2",  "gaunt2.6p",   16384, 0xd101905d, 0, 8192},
		{"gaunt2",  "136043-1104.6p", 8192, 0x1343cf6f, 0, 8192},
	},
	{
		BLOCK_FILL,
		{"gaunt2",   "gaunt2.6p",  16384, 0xd101905d, 8192, 8192},
		{"      ", "	    ",     0, 0x00000000, 0,     0},
	},
	{0}
};

struct Rom kawaks_roms[] =
{
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 0, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{
		FULL_COPY,
		{"minasan", "027-m1.bin", 131072, 0xadd5a226, 65536, 65536},
		{"minasan", "027-m1.bin", 131072, 0x6a915482, 0, 65536},
	},
	{0}
};

struct Rom raine_roms[] =
{
	{
		FULL_COPY,
		{"hachamf", "hmf_04.rom", 524288, 0x05a624e3, 0, 524288},
		{"hachamf", "91076-4.101", 1048576, 0xdf9653a4, 524288, 524288},
	},
	{0}
};

struct Emulator ems[] =
{
	{"ace", "ACE v1.9", ace_roms},
	{"arcadeemu", "Arcade Emulator v0.7", arcadeemu_roms},
	{"besnowbros", "BeSnowBros v0.80", besnowbros_roms},
	{"calice", "Calice v0.6.6", calice_roms},
	{"callus", "Callus v0.42", callus_roms},
	{"cinelator95", "Cinelator 95 Beta", cinelator95_roms},
	{"classicemu", "ClassicEmu v0.01", classicemu_roms},
	{"galemu", "GalEmu v40.9", galemu_roms},
	//{"grytra", "Grytra v1.0", grytra_roms},
	{"hive", "HiVE v1.04", hive_roms},
	{"hoot", "Hoot 20011002", hoot_roms},
	{"invadersaver", "Invader Saver v2.00a", invadersaver_roms},
	{"jas", "JAS v1.01", jas_roms},
	{"jff", "JFF v0.24", jff_roms},
	{"jumpbug", "Jump Bug Emulator v0.50", jumpbug_roms},
	{"junofirst", "Juno First v1.23", junofirst_roms},
	{"kawaks", "WinKawaks v1.60", kawaks_roms},
	{"kem", "KEM v1.1", kem_roms},
	{"kungfu", "Kung Fu Master v0.0000001a", kungfu_roms},
	{"m1", "M1 v0.7.8a6", m1_roms},
	{"m72", "M72 v0.33b", m72_roms},
	{"magex", "MageX v0.8a", magex_roms},
	{"mge", "MGE v0.471", mge_roms},
	{"mimic", "Mimic v2.11", mimic_roms},
	{"modeler", "Modeler v0.9.3a", modeler_roms},
	{"nebula", "Nebula v2.25b", nebula_roms},
	{"nebula_jukebox", "Nebula Jukebox v2.9", nebula_jukebox_roms},
	{"neojukebox", "NeoJukeBox v2.7", neojukebox_roms},
	{"neoragex", "NeoRAGEx v0.6b", neoragex_roms},
	{"pacsaver", "Pac Saver v1.00a", pacsaver_roms},
	{"pacx", "Pac-X v0.2", pacx_roms},
	{"pasmulator", "PASMulator v0.22", pasmulator_roms},
	{"pcslomo", "PCSloMo v0.24 Final", pcslomo_roms},
	{"qsound", "QSound Player v2", qsound_player_roms},
	{"rage", "RAGE v0.9", rage_roms},
	{"raine", "RAINE v0.51.0", raine_roms},
	{"rcps", "RCPS", rcps_roms},
	{"replay", "Replay v0.04", replay_roms},
	{"retrocade", "Retrocade v1.2 b2", retrocade_roms},
	{"rockulator", "Rockulator++ v0.98a", rockulator_roms},
	{"s11emu", "S11Emu v0.2", s11emu_roms},
	{"sage", "SAGE v1.16", sage_roms},
	{"salamander", "Salamander Arcade Emulator Preview", salamander_roms},
	{"segasystemc2", "Sega System C2 Emulator v0.2b", segasystemc2_roms},
	{"shark", "Shark v3.1f", shark_roms},
	{"side", "SIDE", side_roms},
	{"sideway", "Sideway v0.22a", sideway_roms},
	{"sonson", "SonSon Emulator v0.1", sonson_roms},
	{"sparcade", "Sparcade v2.33b", sparcade_roms},
	{"system8", "System 8 v0.61b", system8_roms},
	{"system16", "System 16 v0.82a", system16_roms},
	{"thearcade", "The Arcade Machine", the_arcade_roms},
	{"tnzsemu", "TNZS-EMU v2.10b", tnzs_roms},
	{"trombone", "tROMbone v0.11", trombone_roms},
	{"vantage", "VAntAGE v1.12", vantage_roms},
	{"vbemusaver", "VBEmu Screen Saver v1.01a", vbemusaver_roms},
	{"xcade", "Xcade v0.85", xcade_roms},
	{"xpac", "XPac Beta 1-2-3", xpac_roms},
	{"zem", "ZEM v0.001", zem_roms},
	{""}
};
