#include "Frame.h"

#include <wchar.h>
#include <stdio.h>

int sqr(int x)
{
    return x * x;
}

void square(Frame *frame, int *per);

int main()

{

    Frame *frame = (Frame *)malloc(sizeof(Frame));
    frameInit(frame);

    make2DConsole(frame, 8, 8, L"Your title");

    int xCenter = S_WIDTH / 2;
    int yCenter = S_HEIGHT / 2;

    drawBackground(frame, blackF);
    display(frame);
    int per = 0;
    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }

        drawBackground(frame, blackF);

        square(frame, &per);
        display(frame);
    }

    make2DConsole(frame, 10, 16, L"Your title");

    frameDeinit(frame);
    free(frame);
}
void square(Frame *frame, int *per)
{
    int x = 12;
    int y = 7;

    frame->penColor = yellowF;
    frame->penWchar = 0x2588;
    wchar_t debugStr[256];
    swprintf_s(debugStr, 256, L" %d %d %d", x, y, *per);
    drawText(frame, 0, 0, debugStr, wcslen(debugStr), whiteF);
    while (x != 46 + *per)
    {
        paint_pixel(frame, x, y);
        x += 1;
    }
    while (y != 46)
    {
        paint_pixel(frame, x, y);
        y += 1;
    }
    int f = 12;
    int d = 7;
    while (d != 46)
    {
        paint_pixel(frame, f, d);
        d += 1;
    }
    while (f != 47 + *per)
    {
        paint_pixel(frame, f, d);
        f += 1;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        *per += 1;
    }
}
