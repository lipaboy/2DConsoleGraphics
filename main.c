#include "Frame.h"

#include <wchar.h>
#include <stdio.h>

int sqr(int x)
{
    return x * x;
}

void square(Frame *frame, int *per,int x,int y,short Colour,int newline);
void moveXY(int  *const p_x,int  * const p_is_right,int znach);
int main()

{

    Frame *frame = (Frame *)malloc(sizeof(Frame));
    frameInit(frame);

    make2DConsole(frame, 8, 8, L"Your title");

    int xCenter = S_WIDTH / 2;
    int yCenter = S_HEIGHT / 2;

    drawBackground(frame, blackF);
    display(frame);
    int x=12;
    int y=7;
    int x1=40;
    int y1=2;
    int per = 0;
    int is_right=1;
    int is_Up=1;
    int is_right1=0;
    int is_Up1=1;
    int newline=17;
    
    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }

        drawBackground(frame, blackF);

        square(frame,&per,x,y,redF,newline);
        square(frame, &per,x1,y1,yellowF,newline);
        display(frame);
        if (x+newline>=x1)
        {
            is_right1=1-is_right1;
            is_right=1-is_right;
        }
        moveXY(&x,&is_right,74 -newline);
        Sleep(100);
        moveXY(&y,&is_Up,74 -newline);
        moveXY(&x1,&is_right1,74 -newline);
        moveXY(&y1,&is_Up1,74 -newline);


        

    // if (GetAsyncKeyState(VK_LEFT))
    // {
    //     *per -= 1;
    //     Sleep(100);
    // }
    }

    make2DConsole(frame, 10, 16, L"Your title");

    frameDeinit(frame);
    free(frame);
}


void moveXY(int  *const p_coordinate,int  * const p_is_forward,int border)
{
    if ((*p_coordinate)!=border && (*p_is_forward)==1)
    {   
        (*p_coordinate)+=1;
        
    }
    if (*p_coordinate==border)
    {
        (*p_is_forward)=0;
    }
    if ((*p_coordinate)!=1 && (*p_is_forward)==0)
    {   
        (*p_coordinate)-=1;
        
    }
    if (*p_coordinate==1)
    {
        (*p_is_forward)=1;
    }
}




void line(Frame *frame,int x,int y,int x1,int y1)
{
    if (y==y1)// горизонтальная линия
    {
        while (x != x1)
        {
            paint_pixel(frame, x, y);
            x += 1;
        }
    }
    if (x==x1)// вертикальная линия
    {
        while (y != y1)
        {
            paint_pixel(frame, x, y);
            y += 1;
        }
    }
}

void square(Frame *frame, int *per,int x,int y,short Colour,int newline)
{
    
    frame->penColor =Colour;
    frame->penWchar = 0x2588;
    wchar_t debugStr[256];
    swprintf_s(debugStr, 256, L" %d %d %d", x, y, *per);
    drawText(frame, 0, 0, debugStr, wcslen(debugStr), whiteF);
    line(frame, x+ *per,y,x+newline+ *per,y);//X
    line(frame, x+ *per,y,x+ *per,y+newline);//Y
    line(frame, x+ *per,y+newline,x+newline+ *per,y+newline);//X
    line(frame, x+newline+ *per,y,x+newline+ *per,y+newline+1);
}


