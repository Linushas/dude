#include <sys/statvfs.h>
#include "disk_stats.h"
#include "interface.h"

int getDiskUsage(DStats *ds, const char *path)
{
    struct statvfs stat;

    if(statvfs(path, &stat) != 0) 
    {
        return 0;
    }

    ds->total = stat.f_blocks * stat.f_frsize;
    ds->free = stat.f_bfree * stat.f_frsize;
    ds->available = stat.f_bavail * stat.f_frsize;

    return 1;
}