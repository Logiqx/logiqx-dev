/* --- Include standard headers --- */

#include <stddef.h>


/* --- Include the driver header file --- */

#include "driver.h"


/* --- Declare the drivers for all of the different formats --- */

DECLARE_DRIVER(mame_listinfo, "MAME ListInfo", "listinfo", 0)
DECLARE_DRIVER(romcenter_250, "RomCenter 2.50", "romcenter2", 7)
DECLARE_DRIVER(romcenter_200, "RomCenter 2.00", NULL, 7)
DECLARE_DRIVER(romcenter_190, "RomCenter 1.90", NULL, 7)
DECLARE_DRIVER(mame_listxml, "MAME ListXML", "listxml", 0)
DECLARE_DRIVER(mess_listxml, "MESS ListXML", NULL, 0)
DECLARE_DRIVER(mess_listinfo, "MESS ListInfo", NULL, 0)
DECLARE_DRIVER(nebula_driver, "Nebula Driver", NULL, 0)
DECLARE_DRIVER(calice_driver, "Calice Driver", NULL, 0)
DECLARE_DRIVER(folder_scan, "Folder Scan", NULL, 0)
DECLARE_DRIVER(clrmame_log, "ClrMamePro Log", NULL, 0)
DECLARE_DRIVER(zinc_list_sets, "ZiNc List Sets", NULL, 0)
DECLARE_DRIVER(gngeo_romrc, "GNGEO romrc", NULL, 0)
DECLARE_DRIVER(title_list, "Title List", "titlelist", 0)
DECLARE_DRIVER(allzip, "All Zip", NULL, 5)
DECLARE_DRIVER(ziplist, "ZIP List", NULL, 5)


/* --- List the drivers that have already been declared --- */

const struct datlib_driver *datlib_drivers[] =
{
	DRIVER(mame_listinfo)
	DRIVER(romcenter_250)
	DRIVER(romcenter_200)
	DRIVER(romcenter_190)
	DRIVER(mame_listxml)
	DRIVER(mess_listxml)
	DRIVER(mess_listinfo)
	DRIVER(nebula_driver)
	DRIVER(calice_driver)
	DRIVER(folder_scan)
	DRIVER(clrmame_log)
	DRIVER(zinc_list_sets)
	DRIVER(gngeo_romrc)
	DRIVER(title_list)
	DRIVER(allzip)
	DRIVER(ziplist)
	0
};

