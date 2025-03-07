#ifndef INTERFACE_H
#define INTERFACE_H

#include "disk_stats.h"

#define STATE_STANDARD  0
#define STATE_SPE_DIR   2
#define STATE_HELP      3

int initInterface();
int initColor();
void updateInterface(int state, DStats ds);
int cleanupInterface();
char getInput();

#endif