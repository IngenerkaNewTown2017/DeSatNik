#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"
#include "Lib\\Mebel.cpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


bool total_exit ();
void menu_escape(HDC escape);
void workspace_background();
void vybratMebelNaPaneli(int screenW, int screenH, Mebel* Tomb, Button knopki_mebeli);
void CheckKavo(int screenW, int screenH, Mebel* Tomb, Button knopki_mebeli);
int read(Button* knopki_mebeli);
void saving (Mebel* Tomb, int count_knopok);

const int RAZMER_KNOPKI = 100;

int main()
{
    int count_mebel = 100;
    Mebel Tomb[count_mebel];
    unichtogitVsyuMebelPodryad (Tomb, count_mebel);

    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenW, screenH);

    settingsButton = {"", nullptr, 0, screenH * 75/100, 200, screenH * 80/100};
    newplanButton = {"", nullptr, 0, screenH * 80/100, 200, screenH * 85/100};
    loadButton = {"", nullptr, 0, screenH * 85/100, 200, screenH * 90/100};
    saveButton = {"", nullptr, 0, screenH * 90/100, 200, screenH * 95/100};
    exitButton = {"", nullptr, 0, screenH * 95/100, 200, screenH};


    Button knopki_mebeli[200];
    int count_knopok_mebeli = read(knopki_mebeli);

    //Coords of first button
    int CurrentX = RAZMER_KNOPKI;
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


//Áåãàåì ïî âñåì êíîïêàì
/*for (int f = 0; f >= count_knopok_mebeli; f++)
{
bool kartinka_byla = false;
int nomer_kartinki_v_kot_bulo = 0;
//Áåãàåì ïî ïðåäûäóùèì êàðòèíêàì


for()
{
//åñëè àäðåñ ñîâïàëÞ, ñîõðàíÿåì kartinka_byla  è nomer_kartinki_v_kot_bulo
}
if (kartinka_byla)
{
knoppki[f].picture = knopki[nomer_kartinki_v_kot_bulo].picture;
}
else
{
txLoadImage()
}
}*/


    HDC WSpace = txLoadImage ("Pics\\Workspace.bmp");
    HDC fon_menu = txLoadImage ("Pics\\ClearFonMenu.bmp");
    HDC escape= txLoadImage ("Pics\\menu_escape.bmp");



    bool isExit = false;
    bool startWS = false;
    bool returnToMenu = false;



    while (!isExit)
    {
        txBegin();

		//Redactor
        if (startWS)
        {
            workspace_background();
            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);

            returnToMenu = nazad (returnToMenu);
            if (returnToMenu)
            {
                unichtogitVsyuMebelPodryad(Tomb, count_mebel);
            }
            startWS = !returnToMenu;
            //menu_escape (escape);

            risovatVsyuMebelPodryad(Tomb, count_mebel);

            //Drag-n-drop from toolstrip to workspace
            for (int nomer_mebeli = 0; nomer_mebeli < count_knopok_mebeli; nomer_mebeli++)
            {
                if (checkClick(knopki_mebeli[nomer_mebeli].x, knopki_mebeli[nomer_mebeli].y, knopki_mebeli[nomer_mebeli].x1, knopki_mebeli[nomer_mebeli].y1))
                {
                    while(txMouseButtons() & 1)
                    {
                        workspace_background();
                        risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                        risovatVsyuMebelPodryad(Tomb, count_mebel);
                        vybratMebelNaPaneli(screenW, screenH, &Tomb[nomer_mebeli], knopki_mebeli[nomer_mebeli]);

                        txSleep(10);
                    }
                }
            }

            //Drag-n-drop in workspace
            for (int nomer_mebeli = 0; nomer_mebeli < count_knopok_mebeli; nomer_mebeli++)
            {
                if (checkClick(Tomb[nomer_mebeli].MOUSE_X, Tomb[nomer_mebeli].MOUSE_Y, Tomb[nomer_mebeli].MOUSE_X + 200, Tomb[nomer_mebeli].MOUSE_Y + 200))
                {
                    while(txMouseButtons() & 1)
                    {
                        workspace_background();
                        risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                        vybratMebelNaPaneli(screenW, screenH, &Tomb[nomer_mebeli], knopki_mebeli[nomer_mebeli]);
                        risovatVsyuMebelPodryad(Tomb, count_mebel);
                        txSleep(10);
                    }
                }
            }
        }

        //MainMenu
        else
        {
            returnToMenu = false;
            drawMenu (screenW, screenH, fon_menu);
            checkMenuFocus();
            //menu_escape(escape);
            startWS = startWorkspace(startWS);
        }

        if (total_exit ())
        {
            txDisableAutoPause();
            isExit = true;
        }

        txSleep(10);
        txEnd();
    }


    //Delete all pics in for
    for (int i=0; i<count_knopok_mebeli; i++)
    {
        txDeleteDC(knopki_mebeli[i].picture);

    }
    txDeleteDC(fon_menu);
    txDeleteDC(escape);
    txDeleteDC(WSpace);

    saving (Tomb, count_knopok_mebeli);

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

void menu_escape(HDC escape)
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);

    bool isreturn = false;
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        txSleep(1000);

        while (!isreturn)
        {

            txBitBlt (txDC(), screenH/2, screenW/2 - 300, 215, 291, escape, 0, 0);

            if ((txMouseButtons() & 1 &&
                txMouseX() > 0 && txMouseX() < 800
            &&  txMouseY() > 0 && txMouseY() < 321) or GetAsyncKeyState(VK_ESCAPE))
            {
                isreturn = true;
            }

            txSleep(10);
        }
    }
}

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
        knopki_mebeli[nomer].picture = txLoadImage(adress);
        nomer++;
    }

    fout.close();
    return nomer;
}

void vybratMebelNaPaneli(int screenW, int screenH, Mebel* Tomb, Button knopki_mebeli)
{
    Tomb->pctr = knopki_mebeli.picture;
    Tomb->MOUSE_X = txMouseX();
    Tomb->MOUSE_Y = txMouseY();
    Tomb->width = knopki_mebeli.width;
    Tomb->height = knopki_mebeli.height;
    Tomb->risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);
}

void saving (Mebel* Tomb, int count_knopok) 
{
    ofstream fout_save;
    fout_save.open("savings.txt");

    for (int i=0; i<count_knopok; i++) {

        if (Tomb[i].risovat)
        {
             fout_save <<   //Tomb[i].adress << ", " <<
                            Tomb[i].MOUSE_X << ", " <<
                            Tomb[i].MOUSE_Y << endl;
        }
    }

    fout_save.close();
}
