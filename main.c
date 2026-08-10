#include "Frame.h"

#include <wchar.h>
#include <stdio.h>

int sqr( int x)
{
    return x * x;
}



int main()
{
    Frame * frame = (Frame *)malloc(sizeof(Frame));

    frameInit( frame );

    make2DConsole(frame, 8, 8, L"Your title");

    int xCenter = S_WIDTH / 2;
    int yCenter = S_HEIGHT / 2;

    drawBackground(frame, blackF);
    display(frame);

    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
        drawBackground(frame, blackF);
        int x = getMouseX(frame);
        int y = getMouseY(frame);
        frame->penColor = yellowF;
        frame->penWchar = '.';
        drawLine(frame, x, y, xCenter, yCenter);
        float r = sqr(x - xCenter) + sqr(y - yCenter);
        if ( r > 0 )
        {
            frame->penColor = yellowF;
            frame->penWchar = 0x2588;
            Plot(frame, x, y);
        }
        wchar_t debugStr[256];
        swprintf_s(debugStr, 256, L"%d %d %d %d %d", x, y, xCenter, yCenter, sqr(x - xCenter) );
        drawText(frame, 0, 0, debugStr, wcslen(debugStr), whiteF);
        display(frame);
    }

    make2DConsole(frame, 10, 16, L"Your title");

    frameDeinit(frame);
    free(frame);
}
