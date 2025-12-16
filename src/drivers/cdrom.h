/*
    T54/drivers
    cdrom.h - ATAPI cdrom driver
*/
#ifndef CDROM_H
#define CDROM_H

#include <stddef.h>

#include "../io.h"

// cdrom_detectDrive
// Is there a drive present
int cdrom_detectDrive();

#endif