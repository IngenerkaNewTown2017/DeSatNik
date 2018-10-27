#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"
#include "Lib\\Mebel.cpp"
#include <iostream>
#include <fstream>
#include "Lib\\all_exits.cpp"
#include "Lib\\workspace and etc.cpp"
using namespace std;


int main()
{
    int count_knopok_mebeli = 7;
    int count_mebel = 100;
    Mebel Tomb[count_mebel];
    int nomer_tomba = 0;
    decor_destruction(Tomb, count_mebel);

    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenW, screenH);

    settingsButton = {"", nullptr, 0, screenH * 75/100, 200, screenH * 80/100};
    newplanButton = {"", nullptr, 0, screenH * 80/100, 200, screenH * 85/100};
    loadButton = {"", nullptr, 0, screenH * 85/100, 200, screenH * 90/100};
    saveButton = {"", nullptr, 0, screenH * 90/100, 200, screenH * 95/100};
    exitButton = {"", nullptr, 0, screenH * 95/100, 200, screenH};


    Button knopki_mebeli[count_knopok_mebeli];
    reading_from_file(knopki_mebeli, count_knopok_mebeli);

    //coords of first button
        coords_of_first_button(knopki_mebeli);



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
                decor_destruction(Tomb, nomer_tomba);
            }
            startWS = !returnToMenu;
            //menu_escape (escape);

            draw_all_mebel(Tomb, nomer_tomba);

            //Drag-n-drop from toolstrip to workspace
            for (int nomer_mebeli = 0; nomer_mebeli < count_knopok_mebeli; nomer_mebeli++)
            {
                if (checkClick(knopki_mebeli[nomer_mebeli].x, knopki_mebeli[nomer_mebeli].y, knopki_mebeli[nomer_mebeli].x1, knopki_mebeli[nomer_mebeli].y1))
                {
                    while(txMouseButtons() & 1)
                    {
                        workspace_background();
                        risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                        draw_all_mebel(Tomb, count_mebel);
                        button_selection(screenW, screenH, &Tomb[nomer_tomba], knopki_mebeli[nomer_mebeli]);

                        txSleep(10);
                    }

                    nomer_tomba++;
                }
            }

            //Drag-n-drop in workspace
            for (int i = 0; i < nomer_tomba; i++)
            {
                if (checkClick(Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, Tomb[i].MOUSE_X + 200, Tomb[i].MOUSE_Y + 200))
                {
                    while(txMouseButtons() & 1)
                    {
                        workspace_background();
                        risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                        button_selection(screenW, screenH, &Tomb[i], knopki_mebeli[i]);
                        draw_all_mebel(Tomb, count_mebel);
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

    return 0;
}
