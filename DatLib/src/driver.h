/* --- This include file is only used by datlib.c and driver.c --- */

#ifndef _DATLIB_DRIVER_H_
#define _DATLIB_DRIVER_H_


/* --- Include types (if not done already) --- */

#include "type.h"


/* --- Driver structure --- */

struct datlib_driver
{
	char *description;
	uint8_t safety;

	int (*identify)(struct dat *);
	int (*load)(struct dat *);
	int (*specify)(struct dat *);
	int (*save)(struct dat *);
};


/* --- Driver macros --- */

#define DECLARE_DRIVER(NAME, DESCRIPTION, SAFETY) \
int identify_##NAME(struct dat *); \
int load_##NAME(struct dat *); \
int specify_##NAME(struct dat *); \
int save_##NAME(struct dat *); \
struct datlib_driver datlib_driver_##NAME = \
{ \
	DESCRIPTION, \
	SAFETY, \
\
	identify_##NAME, \
	load_##NAME, \
	specify_##NAME, \
	save_##NAME \
};

#define DRIVER(NAME) &datlib_driver_##NAME,


#endif /* _DATLIB_DRIVER_H_ */
