#include "stdbool.h"

typedef struct
{
	unsigned int x; //The x position of the window (note this includes the borders (if they exist))
    unsigned int y; //The y position of the window (note this includes the borders (if they exist))
	unsigned int width; //The width of the window (note this includes the borders (if they exist))
    unsigned int height; //The height of the window (note this includes the borders (if they exist))
    bool isFullScreen; //Overrides the standard height and width specified so when "un maximised" it goes back to its original size

    bool isMinimised; //Stores if the window is minismised

    char* NAME[64]; //The name of the window

    bool isResizable; //Is the window resizeable
    bool hasBorders; //Does the window have borders

}Window;

void drawWindow(Framebuffer* framebuffer, Window* window);
Window* makeWindow(char* NAME[50], int x, int y, int width, int height, bool isFullScreen, bool isMinimised, bool isResizable, bool hasBorders);
void resizeWindow(Window* window, unsigned int width, unsigned int height);
void moveWindow(Window* window, unsigned int x, unsigned int y);
unsigned int getWindowWidth(Framebuffer* framebuffer, Window* window);
unsigned int getWindowHeight(Framebuffer* framebuffer, Window* window);
unsigned int getWindowX(Window* window);
unsigned int getWindowY(Window* window);

