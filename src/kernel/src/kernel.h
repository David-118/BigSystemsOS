void _start(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT);
void putChar(Framebuffer* framebuffer, PSF1_FONT* PSF1_FONT, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff);
void setPixel(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int colour);
void fillRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int colour);
void fillOutlinedRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int fillColour, unsigned int outlineColour);
void outlineRect(Framebuffer* framebuffer, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int lineWidth, unsigned int colour);
void drawline(Framebuffer* framebuffer, int x0, int y0, int x1, int y1, unsigned int colour);