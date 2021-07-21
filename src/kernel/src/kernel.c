#include "gop.h"
#include "kernel.h"

/**
 * 
 * JACOB HOW TO COMPILE YOU PLONKER
 * 
 * Paste this in unbuntu
 * cd src/gnu-efi;  make bootloader; cd ../kernel; make kernel; make buildimg;
 * 
 * Run "run2.bat"
 * 
 */

/**
 * 
 */
void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font) 
{
    //clearScreen(framebuffer, 0xffffffff);
    // setPixel(framebuffer, 10, 50, 0xffff0000);
    // fillRect(framebuffer, 10, 10, 50, 50, 0xffffff00);
    // fillRect(framebuffer, 100, 100, 80, 50, 0xff000000);
    drawString(framebuffer, psf1_font, 0xffffffff, int_to_string(-123), 10, 10);
    //setPixel(framebuffer, 10, 10, 0xfffffff);
    //fillRect(framebuffer, 10, 10, 20, 20, 0xffff0000);

    unsigned const BORDERWIDTH = 10;
    //fillOutlinedRect(framebuffer, 10, 10, 1200, 1000, BORDERWIDTH, 0xff909090, 0xff0000ff);

}


char str_buffer[128];
const char* uint_to_string(unsigned int value) {
    unsigned int size;
    unsigned int sizeTest = value;

    while ((sizeTest / 10) > 0) {
        sizeTest /= 10;
        size++;
    }        
    int index = 0;
    while (value > 0) {
        str_buffer[size - index] = (value % 10) + '0';
        index++;
        value /= 10;
    }
    str_buffer[size + 1] = '\0';
    return str_buffer;
}

const char* int_to_string(int value) {
    int size;
    int sizeTest = value;

    while ((sizeTest / 10) != 0) {
        sizeTest /= 10;
        size++;
    }
    if (value < 0) {
        size += 1;
        str_buffer[0] = '-';
        value *= -1;
    }

    int index = 0;
    while (value > 0) {
        str_buffer[size - index] = (value % 10) + '0';
        index++;
        value /= 10;
    }
    str_buffer[size + 1] = '\0';
    return str_buffer;
}

/* This give me compiler erros
void drawWindow(Framebuffer* framebuffer, Window* win)
{
    const BORDERWIDTH = 10;
    fillOutlinedRect(framebuffer, win->x, win->y, win->Width, win->Height, BORDERWIDTH, 0xff909090, 0xff0000ff);
}
*/
void clearScreen(Framebuffer* framebuffer, unsigned int colour)
{
    const unsigned int WIDTH = framebuffer->PixelsPerScanLine;
    const unsigned int HEIGHT = framebuffer->Height;
    fillRect(framebuffer, 0, 0, WIDTH, HEIGHT, colour);
}
/**
 * Sets a specific pixel
 */
void setPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour)
{
    const unsigned int WIDTH = 1920; //Fix this to actually take into account width and height
    const unsigned int HEIGHT = 1080; //Fix this to actually take into account width and height
    if ((x >= 0) && (y >= 0) && (y < HEIGHT) && (x < WIDTH))
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
    const unsigned int ENDX = x + width; //Stores one pixel further than the end x position of the rectangle (use < not <= to draw the correct width) 
    const unsigned int ENDY = y + height; //Stores one pixel further than the end y position of the rectangle (use < not <= to draw the correct height) 
    int ix, iy; //Declare for looping

    //Loop through all points
    for (ix = x; ix < ENDX; ix++)
    {
        for (iy = y; iy < ENDY; iy++)
        {
            setPixel(framebuffer, ix, iy, colour);
        }
    }
}
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
    fillRect(framebuffer, x, ENDY-1-lineWidth, width, lineWidth, colour);
    //Draw vertical lines
    fillRect(framebuffer, x, y, lineWidth, height, colour);
    fillRect(framebuffer, ENDX-1-lineWidth, y, lineWidth, height, colour);
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
    for (unsigned int y = yOff; y < yOff + 16; y++){
        for (unsigned int x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;
                }

        }
        fontPtr++;
    }
}

void drawString(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int colour, const char* str, unsigned int xOff, unsigned int yOff)  {
    const unsigned int char_width = 8;
    const unsigned int char_height = 16;
    int x = 0, y = 0;
    for (int i = 0; str[i]!='\0'; i++) {
       
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