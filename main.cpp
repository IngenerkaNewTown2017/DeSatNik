#include "TXLib.h"
#include "MENU.cpp"

int main()
    {
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CXSCREEN);

    txCreateWindow (screenW, screenH);
    menu ();

    return 0;
    }


