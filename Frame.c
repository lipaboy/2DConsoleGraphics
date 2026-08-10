#include "Frame.h"

const float pi = 3.141592653589793238;

void frameInit( Frame * frame )
{
    frame->buffscreen = (CHAR_INFO *)calloc(S_WIDTH * S_HEIGHT, sizeof(CHAR_INFO));
    frame->outhnd = GetStdHandle(STD_OUTPUT_HANDLE);
    frame->inhnd = GetStdHandle(STD_INPUT_HANDLE);

    frame->rect_win = (SMALL_RECT){0, 0, (short)(S_WIDTH - 1),
            (short)(S_HEIGHT - 1)};
    frame->characterPos = (COORD){0, 0};
    frame->buffersize = (COORD){(short)(S_WIDTH), (short)(S_HEIGHT)};
    frame->center_x = 0;
    frame->center_y = 0;
    frame->tempCenterx = frame->tempCentery = 0;
    frame->consoleRangeStartx = frame->consoleRangeStarty = 0;
    frame->p = (POINT){0, 0};

    frame->penWchar = 0x2588;
    frame->penColor = whiteF;

    // Enable the window and mouse input events.
}

void frameDeinit(Frame *frame)
{
    free(frame->buffscreen);
}

void push( Frame * frame )
{
    frame->tempCenterx = frame->center_x;
    frame->tempCentery = frame->center_y;
}

void pop( Frame * frame )
{
    frame->center_x = frame->tempCenterx;
    frame->center_y = frame->tempCentery;
}

float mapBounds(float value, float x1, float x2, float y1, float y2)
{
    float m = (y2 - y1) / (x2 - x1);
    float b = y1 - m * x1;
    value = (value - b) / m;
    return value;
}

void GetWindowPos( Frame * frame )
{
    int x;
    int y;
    RECT rect = (RECT){0, 0};
    GetWindowRect(GetConsoleWindow(), &rect);
    x = rect.left;
    y = rect.top;
    frame->consoleRangeStartx = x;
    frame->consoleRangeStarty = y;
}

float getMouseX( Frame * frame )
{
    GetCursorPos(&(frame->p));
    GetWindowPos( frame );
    frame->p.x = mapBounds(frame->p.x, 0, S_WIDTH, frame->consoleRangeStartx,
                           frame->consoleRangeStartx + (S_WIDTH - 1) * frame->fontW);
    return frame->p.x;
}
float getMouseY( Frame * frame )
{
    GetCursorPos(&(frame->p));
    GetWindowPos(frame);
    frame->p.y = mapBounds(frame->p.y, 0, S_HEIGHT, frame->consoleRangeStarty,
                    frame->consoleRangeStarty + (S_HEIGHT - 1) * frame->fontH);
    return frame->p.y - 3;
}

void display( Frame * frame )
{
    WriteConsoleOutputW(frame->outhnd, frame->buffscreen,
                        frame->buffersize, frame->characterPos, &(frame->rect_win));
}
void drawBackground( Frame * frame, short col)
{
    for (int i = 0; i < S_HEIGHT * S_WIDTH; i++)
    {
        frame->buffscreen[i].Char.UnicodeChar = ' ';
        frame->buffscreen[i].Attributes = col;
    }
}

void Plot( Frame * frame, float x, float y)
{
    x += frame->center_x;
    y += frame->center_y;
    if (x > 1 && x < S_WIDTH - 1 && y > 1 && y < S_HEIGHT - 1)
    {
        frame->buffscreen[(int)(x) + S_WIDTH * (int)(y)].Char.UnicodeChar = frame->penWchar;
        frame->buffscreen[(int)(x) + S_WIDTH * (int)(y)].Attributes = frame->penColor;
    }
}


void drawLine( Frame * frame, float x2, float y2, float x1,
               float y1)
{

}

void translate( Frame * frame, float x, float y)
{
    frame->center_x = x;
    frame->center_y = y;
}

void drawText( Frame * frame, int x, int y, const wchar_t * text, int size, short col)
{
    x += frame->center_x;
    y += frame->center_y;
    int i;
    for (i = 0; i < size; i++)
    {
        frame->buffscreen[x + i + S_WIDTH * y].Char.UnicodeChar = text[i];
        frame->buffscreen[x + i + S_WIDTH * y].Attributes = col;
    }
}

void make2DConsole(Frame *frame, int fontw, int fonth, LPCWSTR title)
{
    CONSOLE_FONT_INFOEX fontStructure = {0};
    fontStructure.cbSize = sizeof(fontStructure);
    fontStructure.dwFontSize.X = fontw;
    fontStructure.dwFontSize.Y = fonth;
    SetConsoleTitleW(title);

    SetCurrentConsoleFontEx(frame->outhnd, 1, &fontStructure);

    SetConsoleWindowInfo(frame->outhnd, TRUE, &(frame->rect_win));
    SetConsoleScreenBufferSize(frame->outhnd, frame->buffersize);

    SetConsoleMode(frame->inhnd, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    frame->fontH = fonth;
    frame->fontW = fontw;
}

void drawRectangle(Frame * frame, float x, float y, int b_width, int b_height)
{
    // float tempx;
    // float tempy;
    // const float xoffset = -b_width / 2;
    // const float yoffset = -b_height / 2;
    // for (float i = 0; i <= b_height; i += 0.1)
    // {
    // 	for (float j = 0; j <= b_width; j += 0.1)
    // 	{
    // 		tempx = ((xoffset + j) * cos(angle) - (yoffset + i) * sin(angle));
    // 		tempy = ((xoffset + j) * sin(angle) + (yoffset + i) * cos(angle));

    // 		Plot(tempx - xoffset + x, tempy - yoffset + y, col);
    // 	}
    // }
    float tempx;
    float tempy;
    for (float i = 0; i <= b_height; i += 0.1)
    {
        for (float j = 0; j <= b_width; j += 0.1)
        {
            tempx = x + j;
            tempy = y + i;

            Plot(frame, tempx, tempy);
        }
    }
}

void clip(int * x, int * y)
{
    if (*x < 0) *x = 0;
    if (*x >= S_WIDTH) *x = S_WIDTH;
    if (*y < 0) *y = 0;
    if (*y >= S_HEIGHT) *y = S_HEIGHT;
}

void fillFrame(Frame * frame, int x1, int y1, int x2, int y2)
{
    clip(&x1, &y1);
    clip(&x2, &y2);
    for (int x = x1; x < x2; x++)
        for (int y = y1; y < y2; y++)
            Plot(frame, x, y);
}

void drawCircle(Frame * frame, float xc, float yc, float r)
{
    float x = -1;
    float y = r;

    Plot(frame, x + xc, y + yc);
    float pk = 3 - 2 * r;
    while (y > x)
    {

        if (pk < 0)
        {
            pk += 4 * x + 6;
            x += 1;
        }
        else
        {
            pk += 4 * (x - y) + 10;
            x = x + 1;
            y -= 1;
        }

        float xCoords[8] = { x, y,  y,  x, -x, -y, -y, -x };
        float yCoords[8] = { y, x, -x, -y, -y, -x,  x,  y };
        int i;
        for (i = 0; i < 8; i++)
            Plot(frame, xCoords[i] + xc, yCoords[i] + yc);
    }
}

void drawTriangle(Frame * frame, float x1, float y1,
                  float x2, float y2, float x3, float y3, float angle,
                  short col)
{
    float tempx, tempy, tempx_a, tempy_a;
    tempx = ((x1)*cos(angle) - (y1)*sin(angle));
    tempy = ((x1)*sin(angle) + (y1)*cos(angle));
    tempx_a = ((x2)*cos(angle) - (y2)*sin(angle));
    tempy_a = ((x2)*sin(angle) + (y2)*cos(angle));

    drawLine(frame, tempx, tempy, tempx_a, tempy_a);
    tempx = ((x3)*cos(angle) - (y3)*sin(angle));
    tempy = ((x3)*sin(angle) + (y3)*cos(angle));

    drawLine(frame, tempx_a, tempy_a, tempx, tempy);

    tempx_a = ((x1)*cos(angle) - (y1)*sin(angle));
    tempy_a = ((x1)*sin(angle) + (y1)*cos(angle));

    drawLine(frame, tempx, tempy, tempx_a, tempy_a);
}
