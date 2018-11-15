/*!
\mainpage Эта программа написана командой молодых, (и не очень) талантливых программистов DeSatNik team. Особая благодарность за поддержку и веру в лучшее в отношении этого кода выражается Beavisabra
\file
\brief main всего кода

Суть да дело программы

\authors DeSatNik team
\version 1.0.0
\date 13.11.2018
\bug Неисчеслимы, пока что
\warning Осторожнее
\name Функции основного файла

*/



#include "Lib\\savingInBMP.cpp"
#include "Lib\\Mebel.cpp"
#include "Lib\\MENU.cpp"
#include "Lib\\all_exits.cpp"
#include "Lib\\TXLib.h"
#include "Lib\\workspace and etc.cpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
/*!
\brief функция подсчёта скриншотов

Считает скриншоты сделаные пользователем в программе


\param[in] const char* szPath Путь к папке со скриншотами
*/
int GetFolderCountFiles(const char* szPath);

/*!
\brief функция сохранения

Сохраняет планировку в файл saving.txt


\param[in] Mebel* Tomb Массив сохраняемой мебели
\param[in] int count_knopok предел мебели
*/

void saving (Mebel* Tomb, int count_knopok);
bool wather = true; ///\brief Показ водяного знака

int main()
{
    ShellExecute(NULL,NULL,"sound.exe",NULL ,NULL,SW_SHOWMINIMIZED);

    char s[100];
    string ss;
    int ScreenshotIndex=GetFolderCountFiles("Screenshots\\");

    char s2[100];
    string ss2;
    int SaveIndex=GetFolderCountFiles("Saves\\");

    int count_mebel = 100;
    Mebel Tomb[count_mebel];
    int nomer_tomba = 0;

    decor_destruction(Tomb, count_mebel);

    int screenX = GetSystemMetrics (SM_CXSCREEN);
    int screenY = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenX, screenY);

    settingsButton = {"", nullptr, 0, screenY * 75/100, 200, screenY * 80/100};
    newplanButton = {"", nullptr, 0, screenY * 80/100, 200, screenY * 85/100};
    loadButton = {"", nullptr, 0, screenY * 85/100, 200, screenY * 90/100};
    saveButton = {"", nullptr, 0, screenY * 90/100, 200, screenY * 95/100};
    exitButton = {"", nullptr, 0, screenY * 95/100, 200, screenY};


    Button knopki_mebeli[200];
    int count_knopok_mebeli = read(knopki_mebeli);
    KOLICH_RYADOV_WS = round((count_knopok_mebeli + 1)/4);
    //coords of first button
    coords_of_first_button(knopki_mebeli, count_knopok_mebeli); /// \brief Координаты первой кнопки

    HDC WSpace = txLoadImage ("Pics\\Workspace.bmp"); /// \brief Картинка. Фон рабочей области редактора
    HDC fon_menu = txLoadImage ("Pics\\ClearFonMenu.bmp"); /// \brief Картинка. Фон меню
    HDC escape= txLoadImage ("Pics\\menu_escape.bmp"); /// \brief Картинка. Меню паузы
    HDC WatherMark= txLoadImage ("Pics\\TempWather.bmp"); /// \brief Водяной знак


    bool isExit = false; /// \brief Выход из программы
    bool startWS = false; /// \brief Начало работы
    bool returnToMenu = false; /// \brief Возврат в меню

    while (!isExit)
    {
        txBegin();

		//Redactor
        if (startWS)
        {
            workspace_background();
            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
            grid();


            returnToMenu = nazad (returnToMenu);
            if (returnToMenu)
            {
                decor_destruction(Tomb, nomer_tomba);
            }
            startWS = !returnToMenu;
            //menu_escape (escape);

            //Save to text
            if (GetAsyncKeyState('S'))
            {
                saving (Tomb, nomer_tomba);
            }

            if (GetAsyncKeyState('L'))
            {
               nomer_tomba = download_mebel(Tomb);
            }

            if (GetAsyncKeyState('F'))
            {
                //drDre(Mebel knopki_mebeli);
}
            //Screenshot
            if (GetAsyncKeyState('Q'))
            {
                itoa(ScreenshotIndex,s,10);
                ss = s;
                const char* ScreenshotName = ("Screenshots\\picture" + ss + ".jpg").c_str();

                ScreenCapture(0, 15, screenX, screenY - 310, ScreenshotName); // ETO VACHNO, NE TROGAI! -fpermissive
                txSleep(300);
                ScreenshotIndex=GetFolderCountFiles("Screenshots\\");
            }

            draw_all_mebel(Tomb, nomer_tomba,wather, WatherMark);

            //Drag-n-drop from toolstrip to workspace
            for (int nomer_mebeli = 0; nomer_mebeli < count_knopok_mebeli; nomer_mebeli++)
            {
                if (checkClick(knopki_mebeli[nomer_mebeli].x, knopki_mebeli[nomer_mebeli].y, knopki_mebeli[nomer_mebeli].x1, knopki_mebeli[nomer_mebeli].y1))
                {
                    while(txMouseButtons() & 1)
                    {
                        workspace_background();
                        risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                        grid();
                        button_selection(screenX, screenY, &Tomb[nomer_tomba], knopki_mebeli[nomer_mebeli]);
                        Tomb[nomer_tomba].awidth = SizerX(Tomb[nomer_tomba].pctr);
                        Tomb[nomer_tomba].aheight = SizerY(Tomb[nomer_tomba].pctr);
                        draw_all_mebel(Tomb, count_mebel,wather, WatherMark);

                        checkalka(nomer_tomba, Tomb, nomer_tomba);

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
                            workspace_background();
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                            grid();
                            checkalka(i, Tomb, nomer_tomba);

                            Button Bomzh = {};
                            Bomzh.picture = Tomb[i].pctr;
                            Bomzh.adress = Tomb[i].adressMebeli;
                            Bomzh.width = Tomb[i].width;
                            Bomzh.height = Tomb[i].height;
                            button_selection(screenX, screenY, &Tomb[i], Bomzh);

                            draw_all_mebel(Tomb, count_mebel,wather, WatherMark);
                            txSleep(10);
                        }
                    }
                    else if (GetAsyncKeyState(VK_LEFT))
                    {
                        while(GetAsyncKeyState(VK_LEFT))
                        {
                            workspace_background();
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                            checkalka(i, Tomb, nomer_tomba);
                            draw_all_mebel(Tomb, count_mebel,wather, WatherMark);
                            Tomb[i].awidth = Tomb[i].awidth * 1.05;
                            Tomb[i].aheight = Tomb[i].awidth * 1.05;
                            txSleep(100);
                        }
                    }

                    else if (GetAsyncKeyState(VK_RIGHT))
                    {
                        while(GetAsyncKeyState(VK_RIGHT))
                        {
                            workspace_background();
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                            checkalka(i, Tomb, nomer_tomba);
                            draw_all_mebel(Tomb, count_mebel,wather, WatherMark);
                            Tomb[i].awidth = Tomb[i].awidth  * 0.95;
                            Tomb[i].aheight = Tomb[i].awidth  * 0.95;
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
            //menu_escape(escape);
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


void saving (Mebel* Tomb, int count_knopok)
{
char s2[100];
string ss2;
int SaveIndex=GetFolderCountFiles("Saves\\");

itoa(SaveIndex,s2,10);
                ss2 = s2;
                const char* SaveName = ("Saves\\save" + ss2 + ".txt").c_str();


                txSleep(300);


    ofstream fout_save;
    ofstream ofs(SaveName);
    fout_save.open(SaveName);

    for (int i=0; i<count_knopok; i++)
    {
        if (Tomb[i].risovat)
        {
             fout_save <<   Tomb[i].risovat << "," <<
                            Tomb[i].adressMebeli << "," <<
                            Tomb[i].MOUSE_X << "," <<
                            Tomb[i].MOUSE_Y <<","<<
                            Tomb[i].width << "," <<
                            Tomb[i].height <<","<<
                            Tomb[i].awidth << "," <<
                            Tomb[i].aheight<<  endl;
        }
    }

    fout_save.close();
}

int GetFolderCountFiles( const char* szPath)
{
      if( !szPath || !*szPath) return 0;
      __int64      i64CountFiles = 0;
      char Path[ _MAX_PATH];
      WIN32_FIND_DATA      data;

      strcpy( Path, szPath);
      if( Path[ strlen( Path) - 1] != '\\')
            strcat( Path, "\\");
      strcat( Path,"*.*");
      HANDLE hFind = FindFirstFile( Path, &data);
      if( hFind != INVALID_HANDLE_VALUE)
      {
            while(1)
            {
                  if( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                  {
                        if( strcmp(data.cFileName, ".") && strcmp(data.cFileName, "..") )
                        {
                              char NewPath[ _MAX_PATH];
                              strcpy( NewPath, szPath);
                              strcat( NewPath, "\\");
                              strcat( NewPath, data.cFileName);
                              i64CountFiles += GetFolderCountFiles( NewPath);
                        }
                  }
                  else
                  {
                        i64CountFiles++;
                  }
                  BOOL bCode = FindNextFile( hFind, &data);
                  if( !bCode && GetLastError() == ERROR_NO_MORE_FILES)
                        break;
            }
            FindClose( hFind);
      }
      return i64CountFiles;
}
