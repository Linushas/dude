#include <stdbool.h>
#include <string.h>
#include "disk_stats.h"
#include "interface.h"

#define KEY_QUIT        'q'
#define KEY_HELP_I      'h'
#define KEY_ESC         27

int main(int argc, char **argv) 
{
    int active = true;
    int state = STATE_STANDARD;
    DStats ds = {.path = "/"};
    if(argc > 1) 
    {
        /*if(!isValidPath(argv[1]))           --              TODO!
        {
            printf("%s is not a valid path\n", argv[1]);
            return 1;
        }*/
        state = STATE_SPE_DIR;
        ds.used = getDirectorySize(argv[1]);
        ds.available = 0;
        ds.free = 0;
        ds.total = 0;
        strcpy(ds.path, argv[1]);
    } 
    else 
    {
        state = STATE_STANDARD;
        getDiskUsage(&ds);
    }
    
    
    if(!initInterface()) return 1;
    updateInterface(state, ds);

    while(active) 
    {
        switch(getInput()) 
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

        updateInterface(state, ds);
    }

    cleanupInterface();

    return 0;
}