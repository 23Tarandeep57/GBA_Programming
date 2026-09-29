#include "toolBox.h"


// GENERIC 16-BPP DRAWING

// Draw a line on a 16-bpp canvas.
void bmp16_line(int x1, int y1,
                int x2, int y2,
                COLOR clr,
                void *dstBase,
                u32 dstPitch) {
    int i;
    int dx, dy;
    int xstep, ystep;
    int dd;

    dstPitch /= 2;

    u16 *dst = (u16 *)dstBase;
    dst += y1 * dstPitch + x1;


    // Normalize X direction.
    if (x1 > x2) {
        xstep = -1;
        dx = x1 - x2;
    }
    else {
        xstep = 1;
        dx = x2 - x1;
    }


    // Normalize Y direction.
    if (y1 > y2) {
        ystep = -dstPitch;
        dy = y1 - y2;
    }
    else {
        ystep = dstPitch;
        dy = y2 - y1;
    }


    // Horizontal line.
    if (dy == 0) {
        for (i = 0; i <= dx; i++) {
            dst[i * xstep] = clr;
        }
    }

    // Vertical line.
    else if (dx == 0) {
        for (i = 0; i <= dy; i++) {
            dst[i * ystep] = clr;
        }
    }

    // Slope <= 1.
    else if (dy <= dx) {
        dd = 2 * dy - dx;

        for (i = 0; i <= dx; i++) {
            *dst = clr;

            if (dd >= 0) {
                dst += ystep;
                dd -= 2 * dx;
            }

            dd += 2 * dy;
            dst += xstep;
        }
    }

    // Slope > 1.
    else {
        dd = 2 * dx - dy;
        for (i = 0; i <= dy; i++) {
            *dst = clr;
            if (dd >= 0) {
                dst += xstep;
                dd -= 2 * dy;
            }
            dd += 2 * dx;
            dst += ystep;
        }
    }
}


// Draw a filled rectangle.
void bmp16_rect(int left, int top,
                int right, int bottom,
                COLOR clr,
                void *dstBase,
                u32 dstPitch) {
    
    int ix, iy;

    u32 width= right-left, height= bottom-top;
    u16 *dst= (u16*)(dstBase+top*dstPitch + left*2);
    dstPitch /= 2;

    for(iy=0; iy<height; iy++)
        for(ix=0; ix<width; ix++)
            dst[iy*dstPitch + ix]= clr;

}

//draw Frame
void bmp16_frame(int left, int top,
                 int right, int bottom,
                 COLOR clr,
                 void *dstBase,
                 u32 dstPitch) {
	//Frames are RB exclusive
    right--;
    bottom--;

    // Horizontal edges.
    bmp16_line(left,  top,
               right, top,
               clr, dstBase, dstPitch);

    bmp16_line(left,  bottom,
               right, bottom,
               clr, dstBase, dstPitch);

    // Vertical edges.
    bmp16_line(left,  top,
               left, bottom,
               clr, dstBase, dstPitch);

    bmp16_line(right, top,
               right, bottom,
               clr, dstBase, dstPitch);
}


// MODE 3

void m3_line(int x1, int y1,
             int x2, int y2,
             COLOR clr)
{
    bmp16_line(
        x1, y1,
        x2, y2,
        clr,
        vid_mem,
        SCREEN_WIDTH * 2
    );
}


void m3_rect(int left, int top,
             int right, int bottom,
             COLOR clr)
{
    bmp16_rect(
        left, top,
        right, bottom,
        clr,
        vid_mem,
        SCREEN_WIDTH * 2
    );
}


void m3_frame(int left, int top,
              int right, int bottom,
              COLOR clr)
{
    bmp16_frame(
        left, top,
        right, bottom,
        clr,
        vid_mem,
        SCREEN_WIDTH * 2
    );
}


void m3_fill(COLOR clr)
{
    u32 ii;

    // Two 16-bit pixels fit into one 32-bit word.
    u32 word = ((u32)clr << 16) | clr;

    u32 *dst = (u32 *)vid_mem;

    for (ii = 0;
         ii < (SCREEN_WIDTH * SCREEN_HEIGHT) / 2;
         ii++)
    {
        dst[ii] = word;
    }
}
