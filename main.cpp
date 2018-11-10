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
int GetFolderCountFiles(const char* szPath);
void saving (Mebel* Tomb, int count_knopok);


int main()
{
    char s[100];
    string ss;
    int ScreenshotIndex=GetFolderCountFiles("Screenshots\\");

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


    Button knopki_mebeli[200];
    int count_knopok_mebeli = read(knopki_mebeli);
    //coords of first button
    coords_of_first_button(knopki_mebeli, count_knopok_mebeli);

    HDC WSpace = txLoadImage ("Pics\\Workspace.bmp");
    HDC fon_menu = txLoadImage ("Pics\\ClearFonMenu.bmp");
    HDC escape= txLoadImage ("Pics\\menu_escape.bmp");
    HDC WatherMark= txLoadImage ("Pics\\TempWather.bmp");


    bool wather= true;
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


            //Screenshot
            if (GetAsyncKeyState('Q'))
            {
                itoa(ScreenshotIndex,s,10);
                ss = s;
                const char* ScreenshotName = ("Screenshots\\picture" + ss + ".jpg").c_str();

                //txTransparentBlt (txDC(), 0, 0, SizerX(WatherMark), Sizer(WatherMark), WatherMark, 0, 0);

                ScreenCapture(0, 15, screenW, screenH - 310, ScreenshotName); // ETO VACHNO, NE TROGAI! -fpermissive
                txSleep(1000);
                ScreenshotIndex=GetFolderCountFiles("Screenshots\\");
            wather=true;
            }
            if(wather){

                txTransparentBlt (txDC(), 800, 200, 101, 100, WatherMark, 0, 0);
                wather=false;
                }
            draw_all_mebel(Tomb, nomer_tomba);
                if(wather){

                txTransparentBlt (txDC(), 800, 200, 101, 100, WatherMark, 0, 0);
                wather=false;
                }
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
                        button_selection(screenW, screenH, &Tomb[nomer_tomba], knopki_mebeli[nomer_mebeli]);
                        Tomb[nomer_tomba].awidth = SizerX(Tomb[nomer_tomba].pctr);
                        Tomb[nomer_tomba].aheight = SizerY(Tomb[nomer_tomba].pctr);
                        draw_all_mebel(Tomb, count_mebel);

                        checkalka(nomer_tomba, Tomb);

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

                            for (int e = 0; e < nomer_tomba; e++)
                            {
                                checkalka(e, Tomb);
                            }

                            Button Bomzh = {};
                            Bomzh.picture = Tomb[i].pctr;
                            Bomzh.width = Tomb[i].width;
                            Bomzh.height = Tomb[i].height;
                            button_selection(screenW, screenH, &Tomb[i], Bomzh);
                            Tomb[i].awidth = SizerX(Tomb[i].pctr);
                            Tomb[i].aheight = SizerY(Tomb[i].pctr);

                            draw_all_mebel(Tomb, count_mebel);
                            txSleep(10);
                        }
                    }
                    else if (GetAsyncKeyState(VK_LEFT))
                    {
                        while(GetAsyncKeyState(VK_LEFT))
                        {
                            workspace_background();
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                            grid();
                            draw_all_mebel(Tomb, count_mebel);
                            Tomb[i].awidth = Tomb[i].awidth * 1.05;
                            Tomb[i].aheight =Tomb[i].aheight * 1.05;
                            txSleep(100);
                        }
                    }

                    else if (GetAsyncKeyState(VK_RIGHT))
                    {
                        while(GetAsyncKeyState(VK_RIGHT))
                        {
                            workspace_background();
                            risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                            grid();
                            draw_all_mebel(Tomb, count_mebel);
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
            drawMenu (screenW, screenH, fon_menu);
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
    ofstream fout_save;
    fout_save.open("savings.txt");

    for (int i=0; i<count_knopok; i++)
    {
        //if (Tomb[i].risovat)
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
