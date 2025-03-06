#include <ncurses.h>

#define STATE_HELP 3

void draw(int state) 
{
    static int mx=0, my=0;
    getmaxyx(stdscr, mx, my);

    clear();

    /// FRAME
    attron(COLOR_PAIR(1));
    for(int i = 2; i < mx-2; i++) 
    {
        mvprintw(i, 1, "~");
    }

    /// STATES
    if(!state) 
    {

    }
    else if(state == STATE_HELP) 
    {
        attron(COLOR_PAIR(2));
        mvprintw(mx/2 -4, my/2 - 30, "DUDE - CLI Disk Usage Analyser");
        mvprintw(mx/2 -2, my/2 - 30, "\tlink to docs: https://github.com/Linushas/dude");
        attron(COLOR_PAIR(1));
        mvprintw(mx/2 -3, my/2 - 30, "by Linus\t\t\t\t\t ");
    }

    refresh();
}

int main(int argc, char **argv) 
{
    int active = 1;
    int state = 0;
    initscr();

    if (has_colors() == FALSE) 
    {
        endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    draw(state);

    while(active) 
    {
        switch(getch()) 
        {
            case 'q': 
                active = 0;
                break;
            case 'h':
                state = STATE_HELP;
                break;
            case 27:
                state = 0;
                break;
        }

        draw(state);
    }

    endwin();
    return 0;
}