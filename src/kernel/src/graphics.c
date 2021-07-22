
#include "graphics.h"

void clearScreen(Framebuffer* framebuffer, unsigned int colour)
{
    const unsigned int SCREENWIDTH = framebuffer->PixelsPerScanLine; //The width of the screen in pixels
    const unsigned int SCREENHEIGHT = framebuffer->Height; //The height of the screen in pixels
    fillRect(framebuffer, 0, 0, SCREENWIDTH, SCREENHEIGHT, colour); //Fill the rectangular screen with the designated background colour
}
/**
 * Sets a specific pixel
 */
void setPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour)
{
    const unsigned int SCREENWIDTH = framebuffer->PixelsPerScanLine; //The width of the screen in pixels
    const unsigned int SCREENHEIGHT = framebuffer->Height; //The height of the screen in pixels
    
    if ((y < SCREENHEIGHT) && (x < SCREENWIDTH)) //Do not need to check x>=0, y>=0 as unsigned integers are always positive
    { //Check if pixel can draw to a valid point
        unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
        *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;
    }
}
/**
 * 
 */
void fillOutlinedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColour, unsigned int outlineColour)
{
    fillRect(framebuffer, x+lineWidth, y+lineWidth, width-(2*lineWidth), height-(2*lineWidth), fillColour); //Draw the filled in rectangle
    outlineRect(framebuffer, x, y, width, height, lineWidth, outlineColour); //Draw the outlined rectangle

}
/**
 * Draws a filled rectangle where on of the corner points is (x, y) and has height and width specified
 */
void fillRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colour)
{
    
    unsigned int ix, iy; //Declare for looping

    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress; //Position in memory of (0, 0)
    unsigned int pixelWidth = framebuffer->PixelsPerScanLine; //Number of pixels per scan line (think of as 2d array width)

    const unsigned int SCREENWIDTH = framebuffer->PixelsPerScanLine; //The width of the screen in pixels
    const unsigned int SCREENHEIGHT = framebuffer->Height; //The height of the screen in pixels

    if ((y < SCREENHEIGHT) && (x < SCREENWIDTH)) //Do not need to check x>=0, y>=0 as unsigned integers are always positive
    { //Check if the rectangle is on screen

        unsigned int LoopEndX = x + width; //Stores one position further in memory further than the end x position of the rectangle (use < not <= to draw the correct width) 
        unsigned int LoopEndY = (y + height)*pixelWidth; //Stores pixelWidth position in memory further than the end y position of the rectangle (use < not <= to draw the correct height) 
        
        if (LoopEndX > SCREENWIDTH)
        { //If the rectange was going to go off screen
            LoopEndX = SCREENWIDTH;
        }
        if (LoopEndY > SCREENHEIGHT*pixelWidth)
        { //If the rectange was going to go off screen in the y direction
            LoopEndY = SCREENHEIGHT*pixelWidth;
        }
        //Loop through all points
        for (ix = x; ix < LoopEndX; ix++)
        {
            for (iy = y*pixelWidth; iy < LoopEndY; iy += pixelWidth)
            {
                *(unsigned int*)(pixPtr + ix + iy) = colour; //Set colour of pixel
            }
        }
    }
}
/**
 * Draws an outline of a rectangle where on of the corner points is (x, y) and has height and width specified, the outline width can also be specified
 */
/*
Can name functions the smae thign in C big sad
void outlineRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colour)
{
    outlineRect(framebuffer, x, y, width, height, 1, colour);
}
*/
/**
 * Draws an outline of a rectangle where on of the corner points is (x, y) and has height and width specified, the outline width can also be specified
 */
void outlineRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colour)
{
    const unsigned int ENDX = x + width; //Stores one pixel further than the end x position of the rectangle (use < not <= to draw the correct width) 
    const unsigned int ENDY = y + height; //Stores one pixel further than the end y position of the rectangle (use < not <= to draw the correct height) 
    int ix, iy, i; //Declare for looping
    int myX, myY;
    //Draw horizontal lines
    fillRect(framebuffer, x, y, width, lineWidth, colour);
    fillRect(framebuffer, x, ENDY-lineWidth, width, lineWidth, colour);
    //Draw vertical lines
    fillRect(framebuffer, x, y, lineWidth, height, colour);
    fillRect(framebuffer, ENDX-lineWidth, y, lineWidth, height, colour);
}
 /**
  * Draws a line between the points (x0, y0) and (x1, y1)
  */
void drawline(Framebuffer* framebuffer, int x0, int y0, int x1, int y1, unsigned int colour)
{ //Google it (Thats what I did you silly)
    int dx, dy, p, x, y;
    dx=x1-x0;
    dy=y1-y0;
    
    x=x0;
    y=y0;
    
    p=2*dy-dx;
    
    while(x<x1)
    {
        if(p>=0)
        {
            setPixel(framebuffer, x, y, colour);
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else
        {
            setPixel(framebuffer, x, y, colour);
            p=p+2*dy;
        }
        x=x+1;
    }
}

/**
 * 
 */
void drawChar(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff) 
{
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
    char* fontPtr = psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize);
    for (unsigned int y = yOff; y < yOff + 16; y++)
    {
        for (unsigned int x = xOff; x < xOff+8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;
            }

        }
        fontPtr++;
    }
}

void drawString(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int colour, const char* str, unsigned int xOff, unsigned int yOff)
{
    const unsigned int char_width = 8;
    const unsigned int char_height = 16;
    int x = 0, y = 0;
    for (int i = 0; str[i]!='\0'; i++)
    {
       
        if (str[i]!='\n') 
        {
             drawChar(framebuffer, psf1_font, colour, str[i], xOff + x, yOff + y);
            x += char_width;
        } 
        else
        {
            y+= char_height;
            x = 0;
        }
    }
}