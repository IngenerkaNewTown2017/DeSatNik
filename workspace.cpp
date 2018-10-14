#include <fstream>
#include <string>

txSetColor(TX_BLACK);
txRectangle(65, 97, screenW - 100, screenH -334);
txLine(0, 800, screenW, 800);
txLine();


void draw_fon()
{

    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    //txRectangle(0, 0, screenW, screenH);
    txSetColor (TX_BLACK);

    for (int y = 20; y <= MAP_SIZE_Y; y = y + 30)
    {
        txLine   (0, y, MAP_SIZE_X, y);
    }

    for (int x = 0; x <= MAP_SIZE_X; x = x + 30)
    {
        txLine   (x, 0, x, MAP_SIZE_Y);
    }
}

void proMassivovKoordinatov(HDC pic, PicSize* Mas_SizeModels, int n){
    HBITMAP hbm=(HBITMAP)Win32::GetCurrentObject(pic, OBJ_BITMAP);
    BITMAP bm;
    Win32::GetObject(hbm,sizeof(bm), (LPVOID)&bm);
    Mas_SizeModels[n].sizeX= bm.bmWidth;
    Mas_SizeModels[n].sizeY= bm.bmHight;
}
