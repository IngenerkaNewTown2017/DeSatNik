#include "TXLib.h"



void menu () {
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CXSCREEN);

     HDC fon_menu = txLoadImage ("fon_menu.bmp");
    txBitBlt (txDC(), 0, 0, screenW, screenH, fon_menu, 0, 0);
    txDeleteDC(fon_menu);


}
