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

void clip(int * x, int * y)
{
    if (*x < 0) *x = 0;
    if (*x >= S_WIDTH) *x = S_WIDTH;
    if (*y < 0) *y = 0;
    if (*y >= S_HEIGHT) *y = S_HEIGHT;
}

