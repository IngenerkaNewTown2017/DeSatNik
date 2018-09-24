#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"

int main()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CXSCREEN);
    txCreateWindow (screenW, screenH);

    HDC fon_menu = txLoadImage ("Pics\\fon_menu.bmp");

    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        drawMenu (screenW, screenH, fon_menu);
        checkMenuFocus();
        txSleep(10);
    }

    txDeleteDC(fon_menu);

    return 0;
}


