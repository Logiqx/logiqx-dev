#include <stdio.h>
#include <stdarg.h>

extern int datlib_debug;

void logerror(char *text,...)
{
	va_list arg;
	va_start(arg,text);
	if (datlib_debug)
		fprintf(stderr, text, arg);
	va_end(arg);
}
