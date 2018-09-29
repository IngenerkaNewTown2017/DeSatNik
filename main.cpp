#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"

bool total_exit ();
void menu_escape();

int main()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenW, screenH);

    HDC fon_menu = txLoadImage ("Pics\\fon_menu.bmp");
    bool isExit = false;

    while (!isExit)
    {
        txBegin();
        drawMenu (screenW, screenH, fon_menu);
        checkMenuFocus();
        if (total_exit ())
        {
            txDisableAutoPause();
            isExit = true;
        };

        txSleep(10);
        txEnd();
    }

    txDeleteDC(fon_menu);

    return 0;
}

bool total_exit ()
{
    if (txMouseX() > exitButton.x  &&
        txMouseX() < exitButton.x1 &&
        txMouseY() > exitButton.y  &&
        txMouseY() < exitButton.y1 &&
        txMouseButtons() & 1)
    {
        return true;
    }

    return false;
}

void menu_escape()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);

    HDC escape= txLoadImage ("Pics\\menu_escape.bmp");
        bool isreturn = false;
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            txSleep(1000);

            while (!isreturn)
            {                     //x   y    шир  выс        x    y
                txBitBlt (txDC(), screenH/2, screenW/2 - 300, 215, 291, escape, 0, 0);
                if (txMouseButtons() & 1 &&
                    txMouseX() > 0 && txMouseX() < 800
                &&  txMouseY() > 0 && txMouseY() < 321)
                {
                    isreturn = true;
                }
                txSleep(10);
            }

        }
        txDeleteDC(escape);
    }

