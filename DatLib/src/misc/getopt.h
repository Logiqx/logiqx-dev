/* --- This include file is only used by the external tools, not DatLib --- */

#ifndef _DATLIB_GETOPT_H_
#define _DATLIB_GETOPT_H_

#include <unistd.h>

#if defined (__MINGW32_VERSION) || defined (__CYGWIN__) || defined (_MSC_VER)
int getopt(int argc, char **argv, char *opts);
#endif


#endif
