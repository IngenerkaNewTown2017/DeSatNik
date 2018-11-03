#pragma once

#include <iostream>
#include <fstream>

using namespace std;

const int RAZMER_KNOPKI = 100;

void workspace_background()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txClear();
    txSetColor(TX_BLACK, 5);
    txRectangle(50, 50, screenW - 50, screenH - 350);
    txSetColor(TX_WHITE);

    //Grid
    txSetColor(TX_BLACK);
    for (int y = screenH; y >= screenH - 300; y = y - RAZMER_KNOPKI)
    {
        txLine   (0, y, RAZMER_KNOPKI * (screenW / RAZMER_KNOPKI), y);
    }

    for (int x = 0; x <= screenW; x = x + RAZMER_KNOPKI)
    {
        txLine   (x, screenH - 300, x, screenH);
    }

    txSetColor(TX_BLACK, 4);
    for (int x = 0; x <= screenW; x = x + 5 * RAZMER_KNOPKI)
    {
        txLine   (x, screenH - 300, x, screenH);
    }
}

int read(Button* knopki_mebeli)
{
    ifstream fout;
    fout.open("PicsButtons.txt");
    int nomer = 0;
    while (fout.good())
    {
        string picAdress;
        getline(fout, picAdress);
        char* adress = new char[200];
        strcpy(adress, picAdress.c_str());

        knopki_mebeli[nomer].adress = adress;
        nomer++;
    }

    fout.close();
    return nomer;
}

void button_selection(int screenW, int screenH, Mebel* Tomb, Button knopki_mebeli)
{
    Tomb->adress = knopki_mebeli.adress;
    Tomb->pctr = knopki_mebeli.picture;
    Tomb->MOUSE_X = txMouseX();
    Tomb->MOUSE_Y = txMouseY();
    Tomb->width = knopki_mebeli.width;
    Tomb->height = knopki_mebeli.height;
    Tomb->risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);
}

void coords_of_first_button(Button* knopki_mebeli, int count_knopok_mebeli)
{
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    int CurrentX = 0;
    int CurrentY = screenH - 3 * RAZMER_KNOPKI;

    for (int i=0; i<count_knopok_mebeli; i++)
    {
        knopki_mebeli[i].picture = txLoadImage(knopki_mebeli[i].adress);
        knopki_mebeli[i].x = CurrentX;
        knopki_mebeli[i].y = CurrentY;
        knopki_mebeli[i].x1 = CurrentX + RAZMER_KNOPKI;
        knopki_mebeli[i].y1 = CurrentY + RAZMER_KNOPKI;
        knopki_mebeli[i].width = SizerX(knopki_mebeli[i].picture);
        knopki_mebeli[i].height = SizerY(knopki_mebeli[i].picture);

        //Generate coords for next button
        CurrentX = CurrentX + RAZMER_KNOPKI;
        if (CurrentX > screenW - RAZMER_KNOPKI)
        {
            CurrentX =  RAZMER_KNOPKI;
            CurrentY = CurrentY + RAZMER_KNOPKI;
        }
    }
}
