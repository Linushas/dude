#ifndef DISK_STATS_H
#define DISK_STATS_H

typedef struct dStats
{
    unsigned long total;
    unsigned long free;
    unsigned long available;
    char path[64];
} DStats;

int getDiskUsage(DStats *ds);

#endif