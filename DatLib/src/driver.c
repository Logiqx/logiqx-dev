/* --- Include standard headers --- */

#include <stddef.h>


/* --- Include the driver header file --- */

#include "driver.h"


/* --- Declare the drivers for all of the different formats --- */

DECLARE_DRIVER(mame_listinfo, "MAME ListInfo", 0)
DECLARE_DRIVER(romcenter_250, "RomCenter 2.50", 7)
DECLARE_DRIVER(romcenter_200, "RomCenter 2.00", 7)
DECLARE_DRIVER(romcenter_190, "RomCenter 1.90", 7)
DECLARE_DRIVER(mame_listxml, "MAME ListXML", 0)
DECLARE_DRIVER(mess_listxml, "MESS ListXML", 0)
DECLARE_DRIVER(generic_xml, "Generic XML", 0)
DECLARE_DRIVER(mess_listinfo, "MESS ListInfo", 0)
DECLARE_DRIVER(tab_delimited, "Tab Delimited", 0)
DECLARE_DRIVER(nebula_driver, "Nebula Driver", 0)
DECLARE_DRIVER(calice_driver, "Calice Driver", 0)
DECLARE_DRIVER(folder_scan, "Folder Scan", 0)
DECLARE_DRIVER(clrmame_log, "ClrMamePro Log", 0)
DECLARE_DRIVER(zinc_list_sets, "ZiNc List Sets", 0)
DECLARE_DRIVER(m1_xml, "M1 XML", 0)
DECLARE_DRIVER(gngeo_romrc, "GNGEO romrc", 0)
DECLARE_DRIVER(title_list, "Title List", 0)
DECLARE_DRIVER(romcenter_sublist, "RomCenter Sublist", 0)
DECLARE_DRIVER(mame_gamelist, "MAME GameList", 0)
DECLARE_DRIVER(allzip, "All Zip", 5)
DECLARE_DRIVER(ziplist, "ZIP List", 5)
DECLARE_DRIVER(map_file, "Map File", 0)


/* --- List the drivers that have already been declared --- */

const struct datlib_driver *datlib_drivers[] =
{
	DRIVER(mame_listinfo)
	DRIVER(romcenter_250)
	DRIVER(romcenter_200)
	DRIVER(romcenter_190)
	DRIVER(mame_listxml)
	DRIVER(mess_listxml)
	DRIVER(generic_xml)
	DRIVER(mess_listinfo)
	DRIVER(tab_delimited)
	DRIVER(nebula_driver)
	DRIVER(calice_driver)
	DRIVER(folder_scan)
	DRIVER(clrmame_log)
	DRIVER(zinc_list_sets)
	DRIVER(m1_xml)
	DRIVER(gngeo_romrc)
	DRIVER(title_list)
	DRIVER(romcenter_sublist)
	DRIVER(mame_gamelist)
	DRIVER(allzip)
	DRIVER(ziplist)
	DRIVER(map_file)
	0
};

