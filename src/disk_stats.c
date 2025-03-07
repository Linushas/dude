#include <sys/statvfs.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "disk_stats.h"
#include "interface.h"

int getDiskUsage(DStats *ds)
{
    struct statvfs stat;

    if(statvfs(ds->path, &stat) != 0) 
    {
        return 0;
    }

    ds->total = stat.f_blocks * stat.f_frsize;
    ds->free = stat.f_bfree * stat.f_frsize;
    ds->available = stat.f_bavail * stat.f_frsize;
    ds->used = getDirectorySize(ds->path);

    return 1;
}

long getDirectorySize(const char *path)
{
    struct dirent *entry;
    struct stat statbuf;
    long total_size = 0;
    DIR *dir = opendir(path);

    if(dir == NULL)
    {
        return 0;
    }

    while((entry = readdir(dir)) != NULL)
    {
        char full_path[1024];

        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if(stat(full_path, &statbuf) == 0)
        {
            if(S_ISDIR(statbuf.st_mode))
            {
                total_size += getDirectorySize(full_path);
            }
            else 
            {
                total_size += statbuf.st_size;
            }
        }
    }

    closedir(dir);
    return total_size;
}