/*!
\mainpage ��� ��������� �������� �������� �������, (� �� �����) ����������� ������������� DeSatNik team. ������ ������������� �� ��������� � ���� � ������ � ��������� ����� ���� ���������� Beavisabra
\file
\brief main ����� ����

���� ���������

\authors DeSatNik team
\version 1.0.0 beta
\date 13.11.2018
\bug �����������, ���� ���
\warning ����������
\name ������� ��������� �����

*/

#include "Lib\\config.cpp"
#include "Lib\\savingInBMP.cpp"
#include "Lib\\Mebel.cpp"
#include "Lib\\MENU.cpp"
#include "Lib\\all_exits.cpp"
#include "Lib\\TXLib.h"
#include "Lib\\workspace and etc.cpp"
#include <fstream>
#include <iostream>
#include <string>


//� ���� ����������� ��������� �� ��������� � ��������� ������� �������. (����� �� ������, � ��� ��� �� ������� ���� ������� ���� �� ������ ���������� �����))))

using namespace std;

int main()
{
    ShellExecute(NULL,NULL,"Lib\\sound.exe",NULL ,NULL,SW_SHOWMINIMIZED);
    screenX = GetSystemMetrics (SM_CXSCREEN);
    screenY = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenX, screenY);

bool debug =true;
    char s[100];
    string ss;
    int ScreenshotIndex=GetFolderCountFiles("Screenshots\\");

    char s2[100];
    string ss2;
    int SaveIndex=GetFolderCountFiles("Saves\\");

    int count_mebel = 100;
    Mebel Tomb[count_mebel];
    int nomer_tomba = 0;

    HDC obst[4];
    obst[0] = txLoadImage("Plans\\users plan.bmp");
    obst[1] = txLoadImage("Plans\\1plan.bmp");
    decor_destruction(Tomb, count_mebel);


    settingsButton = {"", nullptr, 0, screenY * 75/100, 200, screenY * 80/100};
    newplanButton = {"", nullptr, 0, screenY * 80/100, 200, screenY * 85/100};
    loadButton = {"", nullptr, 0, screenY * 85/100, 200, screenY * 90/100};
    saveButton = {"", nullptr, 0, screenY * 90/100, 200, screenY * 95/100};
    exitButton = {"", nullptr, 0, screenY * 95/100, 200, screenY};
    docButton={"", nullptr, RAZMER_KNOPKI,screenY * 50/100, 200, screenY * 80/100};

    //choiceButton = {"",nullptr, 0, screenY * 70/100, 200, screenY * 75/100};

    Button knopki_mebeli[200];
    int count_knopok_mebeli = read(knopki_mebeli);
    //In C++ round (2.5) = 2
    KOLICH_RYADOV_WS = round((count_knopok_mebeli + 0.4999 * KOLICH_STOLBCOV_WS)/KOLICH_STOLBCOV_WS);
    //coords of first button
    coords_of_first_button(knopki_mebeli, count_knopok_mebeli); /// \brief ���������� ������ ������

    HDC WSpace = txLoadImage ("Pics\\Workspace.bmp"); /// \brief ��������. ��� ������� ������� ���������
    HDC fon_menu = txLoadImage ("Pics\\ClearFonMenu.bmp"); /// \brief ��������. ��� ����
    HDC escape= txLoadImage ("Pics\\menu_escape.bmp"); /// \brief ��������. ���� �����
    HDC WatherMark= txLoadImage ("Pics\\TempWather.bmp"); /// \brief ������� ����
    HDC choose_menu = txLoadImage ("Plans\\choose_menu.bmp");

    bool isExit = false; /// \brief ����� �� ���������
    bool startWS = false; /// \brief ������ ������
    bool returnToMenu = false; /// \brief ������� � ����
    bool risovatKnopka = true;

    int plan = -1;
    while (!isExit)
    {
        txBegin();

		//Redactor
        if (startWS)
        {
            if (plan >= 0)
            {
                Win32::TransparentBlt (txDC(), 0, 0, screenX, screenY, obst[plan], 0, 0, 1280, 720, TX_RED);
                grid();
            }
            else
            {
                workspace_background();
            }
            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
            //txBitBlt (txDC(), screenX - 300, screenY - 300, 500, 500, button, 0, 0);

            returnToMenu = nazad (returnToMenu);
            if (returnToMenu)
            {
                decor_destruction(Tomb, nomer_tomba);
            }
            startWS = !returnToMenu;
            //menu_escape (escape);

            //Save to text
            if (GetAsyncKeyState(KEY_SAVE))
            {
                saving (Tomb, nomer_tomba);
            }

            if (GetAsyncKeyState(KEY_DOWNLOAD))
            {
               nomer_tomba = download_mebel(Tomb);
            }

            if (GetAsyncKeyState(KEY_CHOOSE))
            {
                bool nachalo = false;
                while (!nachalo)
                {
                    Win32::TransparentBlt(txDC(), 0, 0, screenX, screenY, choose_menu, 0, 0, 900, 600, TX_RED);

                    txSetFillColor(TX_TRANSPARENT);
                    Win32::TransparentBlt (txDC(), screenX - 670, screenY - 495, 455, 385, obst[0], 0, 0, 1280, 720, TX_WHITE);
                    Win32::TransparentBlt (txDC(), screenX - 670,  screenY - 895, 455, 385, obst[1], 0, 0, 1280, 720, TX_WHITE);
                    txRectangle(screenX - 670,  screenY - 495, screenX - 215, screenY - 110);

                    txRectangle(screenX - 670,  screenY - 895, screenX - 215, screenY - 510);

                    if (checkClick(screenX -  670, screenY - 495, screenX - 215  , screenY - 110))
                    {
                        plan = 0;
                        nachalo = true;
                    }

                    if (checkClick(screenX -  670, screenY - 895, screenX - 215  , screenY - 510))
                    {
                        plan = 1;
                        nachalo = true;
                    }

                    txSleep(10);
                }
            }

            //Screenshot
            if (GetAsyncKeyState(KEY_SCREENSHOT))
            {
                itoa(ScreenshotIndex,s,10);
                ss = s;
                const char* ScreenshotName = ("Screenshots\\picture" + ss + ".jpg").c_str();

                ScreenCapture(0, 15, screenX, screenY - 310, ScreenshotName); // ETO VACHNO, NE TROGAI! -fpermissive
                txSleep(300);
                ScreenshotIndex=GetFolderCountFiles("Screenshots\\");
            }

            menu_escape(escape, &nomer_tomba, Tomb, &isExit);
            draw_all_mebel(Tomb, nomer_tomba,wather, WatherMark);

            //Drag-n-drop from toolstrip to workspace
            for (int nomer_mebeli = 0; nomer_mebeli < count_knopok_mebeli; nomer_mebeli++)
            {
                if (checkClick(knopki_mebeli[nomer_mebeli].x, knopki_mebeli[nomer_mebeli].y, knopki_mebeli[nomer_mebeli].x1, knopki_mebeli[nomer_mebeli].y1))
                {
                    while(txMouseButtons() & 1)
                    {
                        if (plan >= 0)
                        {
                            Win32::TransparentBlt (txDC(), 0, 0, screenX, screenY, obst[plan], 0, 0, 1280, 720, TX_RED);
                            grid();
                        }
                        else
                        {
                            workspace_background();
                        }
                        risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                        button_selection(screenX, screenY, &Tomb[nomer_tomba], knopki_mebeli[nomer_mebeli]);
                        Tomb[nomer_tomba].awidth = SizerX(Tomb[nomer_tomba].pctr);
                        Tomb[nomer_tomba].aheight = SizerY(Tomb[nomer_tomba].pctr);

                        checkalka(nomer_tomba, Tomb, nomer_tomba);//It was higher and what a chaNGE!!!
                        draw_all_mebel(Tomb, count_mebel,wather, WatherMark);


                        txSleep(10);
                    }


                    if (Tomb[nomer_tomba].risovat)
                    {
                        nomer_tomba++;
                    }
                }
            }

            //Drag-n-drop in workspace
            for (int i = 0; i < nomer_tomba; i++)
            {
                if (checkClick(Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, Tomb[i].MOUSE_X + Tomb[i].awidth, Tomb[i].MOUSE_Y + Tomb[i].aheight))
                {
                    txSleep(500);

                    if(txMouseButtons() & 1)
                    {
                        while(txMouseButtons() & 1)
                        {
                            if (plan >= 0)
                            {
                                Win32::TransparentBlt (txDC(), 0, 0, screenX, screenY, obst[plan], 0, 0, 1280, 720, TX_RED);
                                grid();
                            }
                            else
                            {
                                workspace_background();
                            }
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);

                            Button Bomzh = {};
                            Bomzh.EtoPol = Tomb[i].EtoPol;
                            Bomzh.picture = Tomb[i].pctr;
                            Bomzh.adress = Tomb[i].adressMebeli;
                            Bomzh.width = Tomb[i].width;
                            Bomzh.height = Tomb[i].height;
                            button_selection(screenX, screenY, &Tomb[i], Bomzh);
                            checkalka(i, Tomb, nomer_tomba);//It was higher and what a chaNGE!!!

                            draw_all_mebel(Tomb, count_mebel,wather, WatherMark);
                            /*txSetColor(TX_RED);
                            char str[100];
                            sprintf(str, "%d %d %d", count_mebel, nomer_tomba, count_knopok_mebeli);
                            txTextOut(100, screenY - 300 + i * 20, str); */
                            txSleep(10);
                        }
                    }

                    else if (GetAsyncKeyState(VK_LEFT))
                    {
                        while(GetAsyncKeyState(VK_LEFT))
                        {
                            //������� ��������
                            if (plan >= 0)
                            {
                                Win32::TransparentBlt (txDC(), 0, 0, screenX, screenY, obst[plan], 0, 0, 1280, 720, TX_RED);
                                grid();
                            }
                            else
                            {
                                workspace_background();
                            }
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                            checkalka(i, Tomb, nomer_tomba);
                            draw_all_mebel(Tomb, count_mebel,wather, WatherMark);


                            Tomb[i].MOUSE_X = Tomb[i].MOUSE_X - 1;
                            if (!Tomb[i].risovat)
                            {
                                Tomb[i].MOUSE_X = Tomb[i].MOUSE_X + 1;
                            }

                            txSleep(20);
                        }
                    }

                    else if (GetAsyncKeyState(VK_OEM_PLUS) || GetAsyncKeyState(VK_ADD))
                    {
                        while(GetAsyncKeyState(VK_OEM_PLUS) || GetAsyncKeyState(VK_ADD))
                        {
                            if (plan >= 0)
                            {
                                Win32::TransparentBlt (txDC(), 0, 0, screenX, screenY, obst[plan], 0, 0, 1280, 720, TX_RED);
                                grid();
                            }
                            else
                            {
                                workspace_background();
                            }
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                            checkalka(i, Tomb, nomer_tomba);
                            draw_all_mebel(Tomb, count_mebel,wather, WatherMark);
                            Tomb[i].awidth = Tomb[i].awidth * 1.05;
                            Tomb[i].aheight = Tomb[i].aheight * 1.05;
                            txSleep(100);
                        }
                    }

                    else if (GetAsyncKeyState(VK_OEM_MINUS) || GetAsyncKeyState(VK_SUBTRACT))
                    {
                        while(GetAsyncKeyState(VK_OEM_MINUS) || GetAsyncKeyState(VK_SUBTRACT))
                        {
                            if (plan >= 0)
                            {
                                Win32::TransparentBlt (txDC(), 0, 0, screenX, screenY, obst[plan], 0, 0, 1280, 720, TX_RED);
                                grid();
                            }
                            else
                            {
                                workspace_background();
                            }
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                            checkalka(i, Tomb, nomer_tomba);
                            draw_all_mebel(Tomb, count_mebel,wather, WatherMark);
                            Tomb[i].awidth = Tomb[i].awidth  * 0.95;
                            Tomb[i].aheight = Tomb[i].aheight  * 0.95;
                            txSleep(100);
                        }
                    }
                }
            }
        }

        //MainMenu
        else
        {
            returnToMenu = false;
            drawMenu (screenX, screenY, fon_menu);
            checkMenuFocus();
            doc(docButton);

            startWS = startWorkspace(startWS);
        }

        if (total_exit (exitButton))
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
