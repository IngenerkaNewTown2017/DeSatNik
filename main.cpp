#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"
bool total_exit ();

int main()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CXSCREEN);
    txCreateWindow (screenW, screenH);

    HDC fon_menu = txLoadImage ("Pics\\fon_menu.bmp");

    while (true/*!GetAsyncKeyState(VK_ESCAPE)*/)
    {
        drawMenu (screenW, screenH, fon_menu);
        checkMenuFocus();
        if (total_exit ())
        {
            txDisableAutoPause();
            return 0;
        };
        txSleep(10);
    }

    txDeleteDC(fon_menu);

    return 0;
}



bool total_exit ()  {
if (txMouseX()>30 &&
    txMouseY()> 1066&&
     txMouseX() <818 &&
    txMouseY()<1107 && txMouseButtons() & 1){
    return true;
 }
 return false;
}


