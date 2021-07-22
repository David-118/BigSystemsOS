#include "stdbool.h"

typedef struct
{
	unsigned int x;
    unsigned int y;
	unsigned int width;
    unsigned int height;
    bool isFullScreen; //Overrides the standard height and width specified so when "un maximised" it goes back to its original size

    bool isMinimised; //Stores if the window is minismised

    char* NAME[64]; //The name of the window

    bool isResizable; //Is the window resizeable
    bool hasBorders; //Does the window have borders
    
    

}Window;
