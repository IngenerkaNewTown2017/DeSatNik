#pragma once

#include "Button.cpp"
#include "TXLib.h"

double oneDimensionalDistance (double minX1, double maxX1, double minX2, double maxX2)
{
    double distance = 0;

    if (minX1  < maxX1 && minX2  < maxX2 &&               //minX1   < maxX1 < minX2  < maxX2
                maxX1  < minX2)
    {
    distance = minX2 - maxX1;
    }
      else if (minX1  < minX2 && maxX1  < maxX2 &&        //minX1   < minX2  < maxX1 < maxX2
                minX2  < maxX1)
    {
    distance = 0;
    }
    else if (minX1  < minX2 && maxX2  < maxX1 &&        //minX1   < minX2  < maxX2 < maxX1
                minX2  < maxX2)
    {
        distance = 0;
    }
        else if (minX2  < minX1 && maxX1  < maxX2 &&        //minX2   < minX1  < maxX1 < maxX2
                minX1  < maxX1) {
        distance = 0;
    } else if (minX2  < minX1 && maxX2  < maxX1 &&        //minX2   < minX1  < maxX2 < maxX1
                minX1  < maxX2)
    {
        distance = 0;
    }
    else if (minX2  < maxX2 && minX1  < maxX1 &&        //minX2   < maxX2  < minX1  < maxX1
                maxX2  < minX1)
    {
        distance = minX1 - maxX2;
    }

    return distance;
}


struct Mebel
{
    const char* adressMebeli;
    bool risovat;
    int MOUSE_X;
    int MOUSE_Y;
    HDC pctr;
    int width;
    int height;
    int awidth;
    int aheight;
};

//Clear workspace
void decor_destruction (Mebel* Tomb, int count_mebel);
//Draw all workspace parts
void draw_all_mebel(Mebel* Tomb, int count_mebel,bool wather, HDC WatherMark);

void decor_destruction (Mebel* Tomb, int count_mebel)
{
    for (int i=0; i<count_mebel; i++)
    {
        Tomb[i] = {false, 0, 0};
    }
}

void draw_all_mebel(Mebel* Tomb, int count_mebel,bool wather, HDC WatherMark)
{
          txSetColor(TX_BLACK, 5);
          if(wather== true){

                txTransparentBlt (txDC(), 800, 200, 101, 100, WatherMark, 0, 0);
                //wather=false;
                }
    for (int i=0; i<count_mebel; i++)
    {
        if (Tomb[i].risovat)
        {
            Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, Tomb[i].awidth, Tomb[i].aheight, Tomb[i].pctr, 0, 0, Tomb[i].width, Tomb[i].height, TX_WHITE);

        }
    }
}

void checkalka( int nomer_kartinki, Mebel* Tomb, int vsego_kart)
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);

    if (txMouseButtons() & 1)
    {
        //Tomb[nomer_kartinki].risovat = true;

        for (int predydushii_nomer = 0; predydushii_nomer < vsego_kart; predydushii_nomer++)
        {
                if ((Tomb[nomer_kartinki].MOUSE_Y + Tomb[predydushii_nomer].aheight < screenH-300
                && (predydushii_nomer != nomer_kartinki)) &&
                    oneDimensionalDistance(Tomb[nomer_kartinki].MOUSE_X + 1,    Tomb[nomer_kartinki].MOUSE_X    + Tomb[nomer_kartinki].awidth,
                                           Tomb[predydushii_nomer].MOUSE_X + 1, Tomb[predydushii_nomer].MOUSE_X + Tomb[predydushii_nomer].awidth) == 0
                    and
                    Tomb[predydushii_nomer].risovat
                    and
                    oneDimensionalDistance(Tomb[nomer_kartinki].MOUSE_Y + 1,    Tomb[nomer_kartinki].MOUSE_Y    + Tomb[nomer_kartinki].aheight,
                                           Tomb[predydushii_nomer].MOUSE_Y + 1, Tomb[predydushii_nomer].MOUSE_Y + Tomb[predydushii_nomer].aheight) == 0)
                {
                Tomb[nomer_kartinki].risovat = false;
            }
        }
    }
}
