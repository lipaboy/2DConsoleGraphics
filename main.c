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
            drawCircle(frame, xCenter, yCenter, sqrt(r));
        }
        wchar_t debugStr[256];
        swprintf_s(debugStr, 256, L"%d %d %d %d %d", x, y, xCenter, yCenter, sqr(x - xCenter) );
        drawText(frame, 0, 0, debugStr, wcslen(debugStr), whiteF);
        display(frame);
    }

    frameDeinit(frame);
    free(frame);

//    while (1)
//    {

//        drawBackground(&frame);
//        p.FillRays();
//        if (GetAsyncKeyState(VK_SPACE))
//        {
//            button = !button;
//            Sleep(800);
//        }
//        p.update(getMouseX(&frame), getMouseY(&frame));

//        if (GetAsyncKeyState(VK_RETURN))
//        {
//            walls.clear();
//            std::vector<std::pair<int, int>> xcoords{{3, S_WIDTH - 3}, {3, S_WIDTH - 3}, {3, 3}, {S_WIDTH - 3, S_WIDTH - 3}};
//            std::vector<std::pair<int, int>> ycoords{{2, 2}, {S_HEIGHT - 3, S_HEIGHT - 3}, {2, S_HEIGHT - 3}, {2, S_HEIGHT - 3}};
//            for (int i = 0; i < 4; i++)
//            {
//                walls.push_back(Boundary(xcoords[i].first, ycoords[i].first, xcoords[i].second, ycoords[i].second, redF));
//            }
//            Sleep(800);
//        }
//        if (GetAsyncKeyState((VK_LBUTTON)))
//        {
//            drawLineAsBoundary(&frame, walls);
//        }
//        if (GetAsyncKeyState(0x42))
//        {
//            drawBlocksAsBoundary(&frame, walls);
//        }
//        for (Boundary wall : walls)
//        {
//            wall.show(&frame);
//        }
//        if (button)
//            p.look(walls, &frame);

//        display(&frame);

//        CHECK_USER_EXIT
//    }
}
