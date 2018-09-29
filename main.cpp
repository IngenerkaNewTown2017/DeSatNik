#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"

bool total_exit ();

int main()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenW, screenH);

    exitButton = {0, screenH * 0.95, 200, screenH};

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
