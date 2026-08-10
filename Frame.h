#ifndef FRAME_H
#define FRAME_H

#include <string.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>

#define S_WIDTH 80
#define S_HEIGHT 80

#pragma comment(lib, "User32.lib")

#define redF FOREGROUND_RED | FOREGROUND_INTENSITY
#define redB BACKGROUND_RED | BACKGROUND_INTENSITY
#define blueF FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define blueB BACKGROUNDGROUND_BLUE | BACKGROUND_INTENSITY
#define greenF FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define greenB BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define dmagentaF 0x0005
#define magentaF 0x000D
#define yellowF 0x000E
#define dyellowF 0x0006
#define dredF 0x0004
#define greyF 0x0008
#define dgreenF 0x0002
#define whiteF 0x000F
#define blackF 0x0000
#define whiteB BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY

struct Frame
{
    HANDLE outhnd;
    HANDLE inhnd;
    SMALL_RECT rect_win;
    CHAR_INFO *buffscreen;
    COORD characterPos;
    COORD buffersize;
    float center_x;
    float center_y;
    float tempCenterx;
    float tempCentery;
    int consoleRangeStartx;
    int consoleRangeStarty;
    POINT p;
    int fontH;
    int fontW;

    short int penWchar;
    short int penColor;
};

typedef struct Frame Frame;

void frameInit( Frame * frame );
void frameDeinit( Frame * frame );
void display( Frame * frame );
void drawBackground( Frame * frame, short col);
float getMouseX( Frame * frame );
float getMouseY( Frame * frame );
void Plot( Frame * frame, float x, float y);
void drawText( Frame * frame, int x, int y, const wchar_t * text,
               int size, short col);

void make2DConsole(Frame * frame, int fontw, int fonth, LPCWSTR title);


#endif
