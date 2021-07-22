
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
 * Sets a specific pixel
 */
void paintPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour)
{
    const unsigned int SCREENWIDTH = framebuffer->PixelsPerScanLine; //The width of the screen in pixels
    const unsigned int SCREENHEIGHT = framebuffer->Height; //The height of the screen in pixels
    
    if ((y < SCREENHEIGHT) && (x < SCREENWIDTH)) //Do not need to check x>=0, y>=0 as unsigned integers are always positive
    { //Check if pixel can draw to a valid point
        unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
        unsigned int orginalColour = *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine));
        
        *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = getColourGradient(orginalColour, colour, getAlpha(colour), 255); //Include transparency
    }
}

/**
 * 
 */
void fillCircle(Framebuffer* framebuffer, int centerX, int centerY, int startX, int startY, int endX, int endY, int radius, unsigned int colour)
{
    const int DISTSQUARED = radius*radius;

    int ix, iy; //Declare for looping in the x and y direction respectively

    int x, y;
    for (ix = startX; ix <= endX; ix++)
    {
        for (iy = startY; iy <= endY; iy++)
        {
            x = ix - centerX;
            y = iy - centerY;
            int myDistSquared = (x*x)+(y*y);
            if (myDistSquared <= DISTSQUARED)
            {
                setPixel(framebuffer, ix, iy, colour);
            }
        }
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

void fillOutlinedGradientRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColourTop, unsigned int fillColourBottom, unsigned int outlineColourTop, unsigned int outlineColourBottom)
{
    fillGradientRect(framebuffer, x+lineWidth, y+lineWidth, width-(2*lineWidth), height-(2*lineWidth), fillColourTop, fillColourBottom); //Draw the filled in rectangle
    outlineGradientRect(framebuffer, x, y, width, height, lineWidth, outlineColourTop, outlineColourBottom); //Draw the outlined rectangle
}
/**
 * 
 */
void fillOutlinedCurvedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColour, unsigned int outlineColour, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight)
{
    fillRect(framebuffer, x+lineWidth, y+lineWidth, width-(2*lineWidth), height-(2*lineWidth), fillColour); //Draw the filled in rectangle
    outlineCurvedRect(framebuffer, x, y, width, height, lineWidth, outlineColour, topLeft, topRight, bottomLeft, bottomRight); //Draw the outlined rectangle
}


void fillOutlinedGradientCurvedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColourTop, unsigned int fillColourBottom, unsigned int outlineColourTop, unsigned int outlineColourBottom, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight)
{
    fillGradientRect(framebuffer, x+lineWidth, y+lineWidth, width-(2*lineWidth), height-(2*lineWidth), fillColourTop, fillColourBottom); //Draw the filled in rectangle
    outlineGradientCurvedRect(framebuffer, x, y, width, height, lineWidth, outlineColourTop, outlineColourBottom, topLeft, topRight, bottomLeft, bottomRight); //Draw the outlined rectangle
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

void fillGradientRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colourTop, unsigned int colourBottom)
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
                
                *(unsigned int*)(pixPtr + ix + iy) = getColourGradient(colourTop, colourBottom, iy, LoopEndY); //Set colour of pixel
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

void outlineGradientRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colourTop, unsigned int colourBottom)
{
    const unsigned int ENDX = x + width; //Stores one pixel further than the end x position of the rectangle (use < not <= to draw the correct width) 
    const unsigned int ENDY = y + height; //Stores one pixel further than the end y position of the rectangle (use < not <= to draw the correct height) 
    int ix, iy, i; //Declare for looping
    int myX, myY;
    //Draw horizontal lines
    fillGradientRect(framebuffer, x, y, width, lineWidth, colourTop, getColourGradient(colourTop, colourBottom, lineWidth, height));
    fillGradientRect(framebuffer, x, ENDY-lineWidth, width, lineWidth, getColourGradient(colourTop, colourBottom, ENDY-lineWidth, height), colourBottom);
    //Draw vertical lines
    fillGradientRect(framebuffer, x, y, lineWidth, height, colourTop, colourBottom);
    fillGradientRect(framebuffer, ENDX-lineWidth, y, lineWidth, height, colourTop, colourBottom);
}

void outlineCurvedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colour, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight)
{
    const unsigned int ENDX = x + width; //Stores one pixel further than the end x position of the rectangle (use < not <= to draw the correct width) 
    const unsigned int ENDY = y + height; //Stores one pixel further than the end y position of the rectangle (use < not <= to draw the correct height) 
    int ix, iy, i; //Declare for looping
    int myX, myY;

    int topLeftOffSet =  topLeft * lineWidth;
    int topRightOffSet = topRight * lineWidth;
    int bottomLeftOffSet = bottomLeft * lineWidth;
    int bottomRightOffSet = bottomRight * lineWidth;
    
    //Draw horizontal lines with edges removed
    fillRect(framebuffer, x+topLeftOffSet, y, width-(topLeftOffSet+topRightOffSet), lineWidth, colour);
    fillRect(framebuffer, x+bottomLeftOffSet, ENDY-lineWidth, width-(bottomLeftOffSet+bottomRightOffSet), lineWidth, colour);
    //Draw vertical lines with edges removed
    fillRect(framebuffer, x, y+topLeftOffSet, lineWidth, height-(topLeftOffSet+bottomLeftOffSet), colour);
    fillRect(framebuffer, ENDX-lineWidth, y+topRightOffSet, lineWidth, height-(topRightOffSet+bottomRightOffSet), colour);
    
    if (topLeft == true)
    {
        fillCircle(framebuffer, x+lineWidth, y+lineWidth, x, y, x+lineWidth, y+lineWidth, lineWidth, colour);
    }
    if (topRight == true)
    {
        fillCircle(framebuffer, ENDX-lineWidth-1, y+lineWidth, ENDX-lineWidth, y, ENDX, y+lineWidth, lineWidth, colour);
    }

    if (bottomLeft == true)
    {
        fillCircle(framebuffer, x+lineWidth, ENDY-lineWidth-1, x, ENDY-lineWidth, x+lineWidth, ENDY, lineWidth, colour);
    }
    if (bottomRight == true)
    {
        fillCircle(framebuffer, ENDX-lineWidth-1, ENDY-lineWidth-1, ENDX-lineWidth, ENDY-lineWidth, ENDX, ENDY, lineWidth, colour);
    }
}

void outlineGradientCurvedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colourTop, unsigned int colourBottom, bool topLeft, bool topRight, bool bottomLeft, bool bottomRight)
{
    const unsigned int ENDX = x + width; //Stores one pixel further than the end x position of the rectangle (use < not <= to draw the correct width) 
    const unsigned int ENDY = y + height; //Stores one pixel further than the end y position of the rectangle (use < not <= to draw the correct height) 
    int ix, iy, i; //Declare for looping
    int myX, myY;

    int topLeftOffSet =  topLeft * lineWidth;
    int topRightOffSet = topRight * lineWidth;
    int bottomLeftOffSet = bottomLeft * lineWidth;
    int bottomRightOffSet = bottomRight * lineWidth;
    
    //Draw horizontal lines with edges removed
    fillGradientRect(framebuffer, x+topLeftOffSet, y, width-(topLeftOffSet+topRightOffSet), lineWidth, colourTop, getColourGradient(colourTop, colourBottom, lineWidth, height));
    fillGradientRect(framebuffer, x+bottomLeftOffSet, ENDY-lineWidth, width-(bottomLeftOffSet+bottomRightOffSet), lineWidth, getColourGradient(colourTop, colourBottom, ENDY-lineWidth, height), colourBottom);
    //Draw vertical lines with edges removed
    fillGradientRect(framebuffer, x, y+topLeftOffSet, lineWidth, height-(topLeftOffSet+bottomLeftOffSet), colourTop, colourBottom);
    fillGradientRect(framebuffer, ENDX-lineWidth, y+topRightOffSet, lineWidth, height-(topRightOffSet+bottomRightOffSet), colourTop, colourBottom);
    
    if (topLeft == true)
    {
        fillCircle(framebuffer, x+lineWidth, y+lineWidth, x, y, x+lineWidth, y+lineWidth, lineWidth, colourTop);
    }
    if (topRight == true)
    {
        fillCircle(framebuffer, ENDX-lineWidth-1, y+lineWidth, ENDX-lineWidth, y, ENDX, y+lineWidth, lineWidth, colourTop);
    }

    if (bottomLeft == true)
    {
        fillCircle(framebuffer, x+lineWidth, ENDY-lineWidth-1, x, ENDY-lineWidth, x+lineWidth, ENDY, lineWidth, colourBottom);
    }
    if (bottomRight == true)
    {
        fillCircle(framebuffer, ENDX-lineWidth-1, ENDY-lineWidth-1, ENDX-lineWidth, ENDY-lineWidth, ENDX, ENDY, lineWidth, colourBottom);
    }
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

    const unsigned int CHARWIDTH = getFontCharWidth();
    const unsigned int CHARHEIGHT = getFontCharHeight();

    for (unsigned int y = yOff; y < yOff + CHARHEIGHT; y++)
    {
        for (unsigned int x = xOff; x < xOff+CHARWIDTH; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                setPixel(framebuffer, x, y, colour);
            }

        }
        fontPtr++;
    }
}

unsigned int getFontCharWidth()
{
    return 8;
}

unsigned int getFontCharHeight()
{
    return 16;
}

void drawString(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int colour, const char* str, unsigned int xOff, unsigned int yOff)
{
    const unsigned int char_width = getFontCharWidth();
    const unsigned int char_height = getFontCharHeight();
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

unsigned int changeBrightness(unsigned int colour, int brightness)
{
    int maskedByte = brightness & 0xff;
    return colour + (maskedByte) + (maskedByte<<8) + (maskedByte<<16);
}

unsigned int getColourGradient(unsigned int colourTop, unsigned int colourBottom, unsigned int pos, unsigned int size)
{

    //Split up the top colour into it's 4 channels
    const unsigned int ALPHATOP = getAlpha(colourTop);
    const unsigned int REDTOP = getRed(colourTop);
    const unsigned int GREENTOP = getGreen(colourTop);
    const unsigned int BLUETOP = getBlue(colourTop);
    //Split up the bottom colour into it's 4 channels
    const unsigned int ALPHABOTTOM = getAlpha(colourBottom);
    const unsigned int REDBOTTOM = getRed(colourBottom);
    const unsigned int GREENBOTTOM = getGreen(colourBottom);
    const unsigned int BLUEBOTTOM = getBlue(colourBottom);
    

    unsigned int howCloseToStart = size-pos; //How close to the top
    unsigned int howCloseToEnd = pos; //How close to the bottom
    unsigned int alpha = ((ALPHATOP*howCloseToStart)+(ALPHABOTTOM*howCloseToEnd))/size; //Computer weighted average alpha 
    unsigned int red = ((REDTOP*howCloseToStart)+(REDBOTTOM*howCloseToEnd))/size; //Computer weighted average red 
    unsigned int green = ((GREENTOP*howCloseToStart)+(GREENBOTTOM*howCloseToEnd))/size; //Computer weighted average green 
    unsigned int blue = ((BLUETOP*howCloseToStart)+(BLUEBOTTOM*howCloseToEnd))/size; //Computer weighted average blue 
    return makeColour(red, green, blue, alpha); //re add all components together
}

unsigned int getAlpha(unsigned int colour)
{
    return (colour & 0xff000000)>>24; //return alpha byte
    //If you don't know how bitwsie operators and masking works just google it -Jacob 2021 (quoting Harry's dad)
}

unsigned int getRed(unsigned int colour)
{
    return (colour & 0x00ff0000)>>16; //return red byte
    //If you don't know how bitwsie operators and masking works just google it -Jacob 2021 (quoting Harry's dad)
}

unsigned int getGreen(unsigned int colour)
{
    return (colour & 0x0000ff00)>>8; //return green byte
    //If you don't know how bitwsie operators and masking works just google it -Jacob 2021 (quoting Harry's dad)
}

unsigned int getBlue(unsigned int colour)
{
    return colour & 0x000000ff; //return blue byte
    //If you don't know how bitwsie operators and masking works just google it -Jacob 2021 (quoting Harry's dad)
}

unsigned int makeColour(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
{
    return blue+(green<<8)+(red<<16)+(alpha<<24); //Add all components together (shift components to be in the right place)
}