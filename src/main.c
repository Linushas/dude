#include <ncurses.h>

void draw() 
{
    static int mx=0, my=0;
    getmaxyx(stdscr, mx, my);

    clear();

    /// FRAME
    mvprintw(mx-2, 1, "*");
    for(int i = 2; i < my-2; i++) 
    {
        mvprintw(mx-2, i, "_");
    }
    mvprintw(mx-2, my-2, "*");
    
    for(int i = 2; i < mx-2; i++) 
    {
        mvprintw(i, 1, "~");
    }

    refresh();
}

int main(int argc, char **argv) 
{
    initscr();

    draw();

    while(1) 
    {
        if(getch() == 'q') break;
        else 
        {
            draw();
        }
    
    }

    endwin();
    return 0;
}