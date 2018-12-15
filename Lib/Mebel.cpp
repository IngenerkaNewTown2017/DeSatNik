/*!
\file
\brief ������

���� ���������� ���� ���, ��������� � �������

\authors DeSatNik team
\version 1.0.0
\date 15.12.2018
\name ������� ��������� � �������

*/
#pragma once

#include "Button.cpp"
#include "config.cpp"
#include "TXLib.h"
/*!
\brief ������� �������� ������������

������� ��������� �������� ������������ ������


\param[in] double minX1 ������ ����������� ���������� X
\param[in] double maxX1 ������ ������������ ���������� X
\param[in] double minX2 ������ ����������� ���������� X
\param[in] double maxX2 ������ ������������ ���������� X
*/
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
                      minX1  < maxX1)
    {
        distance = 0;
    }
    else if (minX2  < minX1 && maxX2  < maxX1 &&        //minX2   < minX1  < maxX2 < maxX1
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
    const char* adressMebeli; ///\brief ���� � ��������
    bool risovat; ///\brief ���������
    int MOUSE_X; ///\brief X ���������� ����
    int MOUSE_Y; ///\brief Y ���������� ����
    HDC pctr; ///\brief ��������
    int width; ///\brief ������ �������
    int height; ///\brief ������ �������
    int awidth; ///\brief ������ �������
    int aheight; ///\brief ������ �� ������ ������
    bool EtoPol;
};

//Clear workspace
/*!
\brief ������� ����������

������� ������� ������� �������


\param[in] Mebel* Tomb ��������� ������
\param[in] int count_mebel ������ �����������
*/
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
/*!
\brief ������� ��������� ������

������� ������ ��� ������

\param[in] Mebel* Tomb �������� ������
\param[in] int count_mebel ������ �����������
\param[in] bool wather ��������� �������� �����
\param[in] HDC WatherMark �������� ��� �������� �����
*/
void draw_all_mebel(Mebel* Tomb, int count_mebel,bool wather, HDC WatherMark)
{
    txSetColor(TX_BLACK, 5);

    for (int i=0; i<count_mebel; i++)
    {
        if (Tomb[i].risovat && Tomb[i].EtoPol)
        {
            Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, Tomb[i].awidth, Tomb[i].aheight, Tomb[i].pctr, 0, 0, Tomb[i].width, Tomb[i].height, TX_WHITE);
        }
    }

    for (int i=0; i<count_mebel; i++)
    {
        if (Tomb[i].risovat && !Tomb[i].EtoPol)
        {
            Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, Tomb[i].awidth, Tomb[i].aheight, Tomb[i].pctr, 0, 0, Tomb[i].width, Tomb[i].height, TX_WHITE);
        }
    }

    if (wather)
    {
        txTransparentBlt (txDC(), 800, 200, 101, 100, WatherMark, 0, 0, TX_WHITE);
    }
}
/*!
\brief ������� �������� ������������

������� ��������� �������� ������������ ������


\param[in] int nomer_kartinki �����
\param[in] Mebel* Tomb ������
\param[in] int vsego_kart ������
*/
void checkalka( int nomer_kartinki, Mebel* Tomb, int vsego_kart)
{
    if (txMouseButtons() & 1)
    {
        bool risovat = true;

        //Workspace
        if (Tomb[nomer_kartinki].MOUSE_Y + Tomb[nomer_kartinki].aheight > screenY - KOLICH_RYADOV_WS * RAZMER_KNOPKI)
        {
            risovat = false;
        }

        //Black color
        for (int x = Tomb[nomer_kartinki].MOUSE_X; x < Tomb[nomer_kartinki].MOUSE_X + Tomb[nomer_kartinki].awidth; x += 5)
        {
            for (int y = Tomb[nomer_kartinki].MOUSE_Y; y < Tomb[nomer_kartinki].MOUSE_Y + Tomb[nomer_kartinki].aheight; y += 5)
            {
                if (txGetPixel(x, y) == TX_BLACK)
                {
                    risovat = false;
                }
            }
        }

        Tomb[nomer_kartinki].risovat = risovat;

        //Crossing with other pic
        for (int predydushii_nomer = 0; predydushii_nomer < vsego_kart; predydushii_nomer++)
        {
            if (predydushii_nomer != nomer_kartinki &&
                oneDimensionalDistance(Tomb[nomer_kartinki].MOUSE_X + 1,    Tomb[nomer_kartinki].MOUSE_X    + Tomb[nomer_kartinki].awidth,
                                       Tomb[predydushii_nomer].MOUSE_X + 1, Tomb[predydushii_nomer].MOUSE_X + Tomb[predydushii_nomer].awidth) == 0
                and
                Tomb[predydushii_nomer].risovat
                and
                Tomb[predydushii_nomer].EtoPol == false
                and
                Tomb[nomer_kartinki].EtoPol == false
                and
                oneDimensionalDistance(Tomb[nomer_kartinki].MOUSE_Y + 1,    Tomb[nomer_kartinki].MOUSE_Y    + Tomb[nomer_kartinki].aheight,
                                       Tomb[predydushii_nomer].MOUSE_Y + 1, Tomb[predydushii_nomer].MOUSE_Y + Tomb[predydushii_nomer].aheight) == 0)
            {
                /*char str[100];
                sprintf(str, "%d %d %d %d", nomer_kartinki, predydushii_nomer, Tomb[nomer_kartinki].MOUSE_X, Tomb[predydushii_nomer].MOUSE_X);
                txTextOut(100, screenY - 300 + nomer_kartinki * 20, str);*/
                Tomb[nomer_kartinki].risovat = false;
            }
        }
    }
}
