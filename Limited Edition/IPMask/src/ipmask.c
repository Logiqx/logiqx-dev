/* --------------------------------------------------------------------------
 * IPMask - Written by Logiqx (http://www.logiqx.com/)
 *
 * A handy utility for maintaining the IP masks at the MAME Testers FTP
 * -------------------------------------------------------------------------- */

/* --- Version information --- */

#define IPMASK_VERSION "v1.0"
#define IPMASK_DATE "Private Beta"


/* --- The standard includes --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* --- Dat library includes --- */

#include "datlib/src/datlib.h"
#include "datlib/src/macro.h"


/* --- ROMInfo definitions and macros --- */

#include "ipmask.h"


/* --- Is DatLib debugging enabled? --- */

extern int datlib_debug;


int main(int argc, char **argv)
{
	FILE *in=0;
	FILE *out=0;

	struct ini_entry *host=0;
	struct ini_entry *ipmask=0;
	struct ini_entry *ipmask_extra=0;

	char st[MAX_STRING_LENGTH];
	char ip_address[MAX_STRING_LENGTH];
	char ip_range[MAX_STRING_LENGTH];
	char ip_mask[MAX_STRING_LENGTH];

	char *value, *ip1, *ip2;

	int found, i, j, k;
	int errflg=0;

	printf("===============================================================================\n");
	printf("IPMask %s (%s) - using ", IPMASK_VERSION, IPMASK_DATE);
	display_datlib_version();
	printf("Written by Logiqx (http://www.logiqx.com/)\n");
	printf("===============================================================================\n");

	/* --- Read INI files --- */

	if (!errflg && !(host=load_ini("host.ini")))
		errflg++;

	if (!errflg && !(ipmask=load_ini("ipmask.ini")))
		errflg++;

	if (!errflg && !(ipmask_extra=load_ini("host.ini")))
		errflg++;

	/* --- Open log file --- */

	if (!errflg)
		FOPEN(out, "ipmask.log", "a");

	/* --- Process host.ini --- */

	for(i=j=0; !errflg && host[i].section[0]; i++)
	{
		*ipmask_extra[i].section='\0';
		*ipmask_extra[i].param='\0';
		*ipmask_extra[i].value='\0';

		if (strcmp(host[i].section, "FTP") && !strcmp(host[i].param, "host"))
		{
			/* --- Find IP address of the host --- */

			if (!errflg)
			{
				sprintf(st, "host %s", host[i].value);
				if ((in=popen(st, "r"))==0)
				{
					fprintf(stderr, "Failed to open pipe for '%s'.\n", st);
					errflg++;
				}
			}

			if (!errflg)
			{
				found=0; while (!found && fgets(st, MAX_STRING_LENGTH, in))
				{
					REMOVE_CR_LF(st)

					if (!strncmp(st, "address   :", 11))
					{
						strcpy(ip_address, st+13);
						found++;
					}
				}

				if (!found)
				{
					fprintf(stderr, "Failed to lookup up host '%s'.\n", host[i].value);
					errflg++;
				}
			}

			if (in)
			{
				pclose(in);
				in=0;
			}

			/* --- Find the IP range --- */

			if (!errflg)
			{
				sprintf(st, "whois %s", ip_address);
				if ((in=popen(st, "r"))==0)
				{
					fprintf(stderr, "Failed to open pipe for '%s'.\n", st);
					errflg++;
				}
			}

			if (!errflg)
			{
				found=0; while (!found && fgets(st, MAX_STRING_LENGTH, in))
				{
					REMOVE_CR_LF(st)

					if (!strncmp(st, "inetnum:", 8))
					{
						strcpy(ip_range, st+14);
						found++;
					}
				}

				if (!found)
				{
					fprintf(stderr, "Failed to lookup up inetnum for %s.\n", ip_address);
					errflg++;
				}
			}

			if (in)
			{
				pclose(in);
				in=0;
			}

			/* --- Determine the IP mask --- */

			if (!errflg)
			{
				strcpy(ip_mask, ip_range);

				ip1=ip_mask;
				ip2=strchr(ip_mask, '-')+2;

				if (strchr(ip_mask, '-'))
					*strchr(ip_mask, '-')='\0';

				while(*ip1 || *ip2)
				{
					if (*ip1==*ip2)
					{
						if (*ip1)
							ip1++;

						if (*ip2)
							ip2++;
					}
					else
					{
						*ip1='\0';
						*ip2='\0';
					}
				}

				if (strrchr(ip_mask, '.'))
				{
					*strrchr(ip_mask, '.')='\0';
				}
				else
				{
					strcpy(ip_mask, ip_address);
					*strchr(ip_mask, '.')='\0';
				}

				for (k=0, ip1=ip_mask; *ip1; ip1++)
				{
					if (*ip1=='.')
						k++;
				}

				for (; k<3; k++)
				{
					strcat(ip_mask, ".*");
				}
			}

			/* --- Check if IP mask is in ipmask.ini, if not add to ipmask_extra array --- */

			if (!errflg)
			{
				sprintf(st, "%s %s", host[i].section, host[i].value);

				for (found=k=0; !found && ipmask[k].section[0]; k++)
				{
					if (!strcmp(ipmask[k].section, st) && !strcmp(ipmask[k].param, "ipmask") &&
						!strcmp(ipmask[k].value, ip_mask))
					{
						found++;
					}
				}

				if (!found)
				{
					fprintf(out, "User         : %s\n", host[i].section);
					fprintf(out, "Host         : %s\n", host[i].value);
					fprintf(out, "IP Address   : %s\n", ip_address);
					fprintf(out, "IP Range     : %s\n", ip_range);
					fprintf(out, "IP Mask      : %s\n\n", ip_mask);
					fprintf(out, "Site Command : site addip %s %s\n\n", host[i].section, ip_mask);

					strcpy(ipmask_extra[j].section, st);
					strcpy(ipmask_extra[j].param, "ipmask");
					strcpy(ipmask_extra[j++].value, ip_mask);

					//printf("site addip %s %s\n", host[i].section, ip_mask);
				}
			}
		}
	}

	/* --- Close log file --- */

	FCLOSE(out)

	/* --- Re-save ipmask.ini --- */

	if (j>0)
	{
		FOPEN(out, "ipmask.ini", "w")

		for (i=0; !errflg && ipmask[i].section[0]; i++)
		{
			if (i==0 || strcmp(ipmask[i].section, ipmask[i-1].section))
				fprintf(out, "[%s]\n", ipmask[i].section);

			fprintf(out, "%s=%s\n", ipmask[i].param, ipmask[i].value);

			if (strcmp(ipmask[i].section, ipmask[i+1].section))
			{
				if ((value=find_ini_value(ipmask_extra, ipmask[i].section, "ipmask")))
				{
					fprintf(out, "%s=%s\n", "ipmask", value);
				}
				fprintf(out, "\n");
			}
		}

		for (i=0; !errflg && ipmask_extra[i].section[0]; i++)
		{
			if ((value=find_ini_value(ipmask, ipmask_extra[i].section, "ipmask"))==0)
			{
				fprintf(out, "[%s]\n", ipmask_extra[i].section);
				fprintf(out, "%s=%s\n\n", ipmask_extra[i].param, ipmask_extra[i].value);
			}
		}

		FCLOSE(out)
	}

	/* --- Free memory --- */

	ipmask_extra=free_ini(ipmask_extra);
	ipmask=free_ini(ipmask);
	host=free_ini(host);

	/* --- All done! --- */

	return(errflg);
}
