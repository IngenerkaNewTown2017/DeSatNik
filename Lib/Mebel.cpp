/*!
\file
\brief Мебель

Файл содержащий весь код, связанный с мебелью

\authors DeSatNik team
\version 1.0.0
\date 15.12.2018
\name Функции связанные с мебелью

*/
#pragma once

#include "Button.cpp"
#include "config.cpp"
#include "TXLib.h"
/*!
\brief функция проверки столкновения

Функция проверяет взаимное расположение мебели


\param[in] double minX1 Первая минимальная координата X
\param[in] double maxX1 Первая максимальная координата X
\param[in] double minX2 Вторая минимальная координата X
\param[in] double maxX2 Вторая максимальная координата X
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
    const char* adressMebeli; ///\brief путь к картинке
    bool risovat; ///\brief рисование
    int MOUSE_X; ///\brief X координата мыши
    int MOUSE_Y; ///\brief Y координата мыши
    HDC pctr; ///\brief Картинка
    int width; ///\brief Ширина сначала
    int height; ///\brief Высота сначала
    int awidth; ///\brief Ширина сначала
    int aheight; ///\brief Высота на данный момент
    bool EtoPol;
};

//Clear workspace
/*!
\brief функция уничтжения

Функция очищает рабочую область


\param[in] Mebel* Tomb Убираемая мебель
\param[in] int count_mebel придел колличества
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
\brief функция рисования мебели

Функция рисует всю мебель

\param[in] Mebel* Tomb Рисуемая мебель
\param[in] int count_mebel придел колличества
\param[in] bool wather рисование водяного знака
\param[in] HDC WatherMark Картинка для водяного знака
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
\brief функция проверки столкновения

Функция проверяет взаимное расположение мебели


\param[in] int nomer_kartinki Номер
\param[in] Mebel* Tomb Мебель
\param[in] int vsego_kart предел
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
