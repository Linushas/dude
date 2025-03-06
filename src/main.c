#include <ncurses.h>
#include <stdbool.h>

#define STATE_STANDARD  0
#define STATE_SPE_DIR   2
#define STATE_HELP      3

#define KEY_QUIT        'q'
#define KEY_HELP_I      'h'
#define KEY_ESC         27

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

void updateInterface(int state) 
{
    static int mx=0, my=0;
    getmaxyx(stdscr, mx, my);

    clear();
    printFrame(mx, my);
    switch(state) {
        case STATE_STANDARD:

            break;
        case STATE_SPE_DIR:

            break;
        case STATE_HELP:
            printStateHelp(mx, my);
            break;
    }

    refresh();
}

int main(int argc, char **argv) 
{
    int active = true;
    int state = STATE_STANDARD;
    if(argc > 1) state = STATE_SPE_DIR;
    /*if(!isValidPath(argv[0]))           --              TODO!
    {
        printf("%s is not a valid path\n", argv[0]);
        return 1;
    }*/

    initscr();
    if(!initColor()) 
    {
        endwin();
        return 1;
    } 

    updateInterface(state);
    while(active) 
    {
        switch(getch()) 
        {
            case KEY_QUIT: 
                active = false;
                break;
            case KEY_HELP_I:
                state = STATE_HELP;
                break;
            case KEY_ESC:
                state = STATE_STANDARD;
                break;
        }

        updateInterface(state);
    }

    endwin();
    return 0;
}