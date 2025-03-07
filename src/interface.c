#include <ncurses.h>
#include "interface.h"
#include "disk_stats.h"

char getInput() { return getch(); }

int cleanupInterface() 
{
    endwin();
}

int initInterface()
{
    initscr();
    if(!initColor()) 
    {
        endwin();
        return 0;
    } 
    return 1;
}

int initColor() 
{
    if (has_colors() == FALSE) 
    {
        printf("Your terminal does not support color\n");
        return 0;
    }

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    return 1;
}

void printFrame(int mx, int my) 
{
    attron(COLOR_PAIR(1));
    for(int i = 2; i < mx-2; i++) 
    {
        mvprintw(i, 1, "~");
    }
}

void printStateHelp(int mx, int my)
{
    attron(COLOR_PAIR(2));
    mvprintw(mx/2 -4, my/2 - 30, "DUDE - CLI Disk Usage Analyser");
    mvprintw(mx/2 -2, my/2 - 30, "\tlink to docs: https://github.com/Linushas/dude");
    attron(COLOR_PAIR(1));
    mvprintw(mx/2 -3, my/2 - 30, "by Linus\t\t\t\t\t ");
}

void updateInterface(int state, DStats ds) 
{
    static int mx=0, my=0;
    getmaxyx(stdscr, mx, my);

    clear();
    //printFrame(mx, my);
    switch(state) {
        case STATE_STANDARD:
            mvprintw(mx/2 -2, my/2 - 30, "Path: %s", ds.path);
            mvprintw(mx/2 -1, my/2 - 30, "Total: %lu", ds.total);
            mvprintw(mx/2, my/2 - 30, "Free: %lu", ds.free);
            mvprintw(mx/2 +1, my/2 - 30, "Available: %lu", ds.available);
            break;
        case STATE_SPE_DIR:
            mvprintw(mx/2 -2, my/2 - 30, "Path: %s", ds.path);
            mvprintw(mx/2 -1, my/2 - 30, "Total: %lu", ds.total);
            mvprintw(mx/2, my/2 - 30, "Free: %lu", ds.free);
            mvprintw(mx/2 +1, my/2 - 30, "Available: %lu", ds.available);
            break;
        case STATE_HELP:
            printStateHelp(mx, my);
            break;
    }

    refresh();
}