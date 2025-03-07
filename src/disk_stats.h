#ifndef DISK_STATS_H
#define DISK_STATS_H

typedef struct dStats
{
    unsigned long total;
    unsigned long free;
    unsigned long used;
    unsigned long available;
    char path[1024];
} DStats;

long getDirectorySize(const char *path);
int getDiskUsage(DStats *ds);

#endif