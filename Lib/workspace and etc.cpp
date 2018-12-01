/*!
\file
\brief Код рабочей области

Файл в котором прописывается код связаный с рабочей областью редактора

\authors DeSatNik team
\version 1.0.0
\date 13.11.2018
\bug Неисчеслимы, пока что
\warning Осторожнее
\name Функции рабочей области

*/
#pragma once

#include "config.cpp"
#include "Button.cpp"
#include "MENU.cpp"
#include <iostream>
#include <fstream>

using namespace std;
/*!
\brief Сетка

Функция рисования сетки
*/
void grid();
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
\param[in] int count_knopok предел
*/
void saving (Mebel* Tomb, int count_knopok);


/*!
\brief функция проверки клика

Функция читает из файла


\param[in] Button* knopki_mebeli читаемая кнопка
*/
int read(Button* knopki_mebeli);

void menu_escape(HDC escape, int* nomer_tomba, Mebel* Tomb, bool* isExit);

/*!
\brief Фон рабочей области

Функция рисования фона рабочей области
*/
void workspace_background()
{
    int screenX = GetSystemMetrics (SM_CXSCREEN);
    int screenY = GetSystemMetrics (SM_CYSCREEN);
    txSetFillColor(TX_BLACK);
    txClear();
    txSetFillColor(TX_WHITE);
    txRectangle(50, 50, screenX - 50, screenY - 350);
    txSetColor(TX_WHITE);

    //Grid
    grid();
}

void grid()
{
    txSetColor(TX_BLACK);

    for (int y = screenY; y >= screenY - KOLICH_RYADOV_WS * RAZMER_KNOPKI; y = y - RAZMER_KNOPKI)
    {
        txLine   ((screenX - KOLICH_STOLBCOV_WS * RAZMER_KNOPKI) / 2, y,
                  (screenX + KOLICH_STOLBCOV_WS * RAZMER_KNOPKI) / 2, y);
    }

    for (int x  = (screenX - KOLICH_STOLBCOV_WS * RAZMER_KNOPKI) / 2;
             x <= (screenX + KOLICH_STOLBCOV_WS * RAZMER_KNOPKI) / 2;
             x += RAZMER_KNOPKI)
    {
        txLine   (x, screenY - KOLICH_RYADOV_WS * RAZMER_KNOPKI, x, screenY);
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
/*!
\brief Функция выбора кнопки

Функция отвечающая за реакцию кнопки
\param[in] int screenX Ширина экрана
\param[in] int screenY Высота экрана
\param[in] Mebel* Tomb Рисуемая мебель
\param[in] Button knopki_mebeli Кнопка
*/

void button_selection(int screenX, int screenY, Mebel* Tomb, Button knopki_mebeli)
{
    Tomb->pctr = knopki_mebeli.picture;
    Tomb->MOUSE_X = txMouseX();
    Tomb->MOUSE_Y = txMouseY();
    Tomb->width = SizerX(knopki_mebeli.picture);
    Tomb->height = SizerY(knopki_mebeli.picture);
    Tomb->risovat = checkFocus(50, 50, screenX - 50 - 200, screenY - 350 - 200);
    Tomb->adressMebeli = knopki_mebeli.adress;
}
/*!
\brief Функция выбора кнопки

Функция отвечающая за координаты кнопок на панели

\param[in] int count_knopok_mebeli Предел количества кнопок
\param[in] Button knopki_mebeli Кнопка
*/

void coords_of_first_button(Button* knopki_mebeli, int count_knopok_mebeli)
{
    int CurrentX = (screenX - KOLICH_STOLBCOV_WS * RAZMER_KNOPKI) / 2;
    int CurrentY = screenY - KOLICH_RYADOV_WS * RAZMER_KNOPKI;

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
        if (CurrentX >= (screenX + KOLICH_STOLBCOV_WS * RAZMER_KNOPKI) / 2)
        {
            CurrentX = (screenX - KOLICH_STOLBCOV_WS * RAZMER_KNOPKI) / 2;
            CurrentY = CurrentY + RAZMER_KNOPKI;
        }
    }
}

/*!
\brief Загрузка

Функция отвечающая за загрузку планировки из файла номер которого был введён

\param[in] Mebel* knopki_mebeli мебель
*/
int download_mebel(Mebel* knopki_mebeli)
{
    string ss2 = txInputBox ("Nomer save?", "System", "0");
    const char* SaveName = ("Saves\\save" + ss2 + ".txt").c_str();

    int nomer = 0;
    ifstream fout;
    fout.open(SaveName);

    if (fout)
    {
        string get = "1";
        while (fout.good() && strlen(get.c_str()) > 0)
        {
            getline (fout, get);

            if (strlen(get.c_str()) > 0)
            {
                int pos0 = get.find(',');
                get = get.substr(pos0 + 1);

                int pos1 = get.find(',');
                string adress = get.substr(0, pos1 );
                get = get.substr(pos1 + 1);

                int pos2 = get.find(',');
                string x = get.substr(0, pos2);
                get = get.substr(pos2 + 1);

                int pos3 = get.find(',');
                string y = get.substr(0, pos3);
                get = get.substr(pos3 + 1);

                int pos4 = get.find(',');
                string width = get.substr(0, pos4);
                get = get.substr(pos4 + 1);

                int pos5 = get.find(',');
                string height = get.substr(0, pos5);
                get = get.substr(pos5 + 1);

                int pos6 = get.find(',');
                string awidth = get.substr(0, pos6);
                get = get.substr(pos6 + 1);

                int pos7 = get.find(',');
                string aheight = get.substr(0, pos7);

                char* picAdress = new char[195];
                strcpy(picAdress, adress.c_str());

                knopki_mebeli[nomer] = {picAdress, true, atoi(x.c_str()), atoi(y.c_str()), txLoadImage(picAdress), atoi(width.c_str()), atoi(height.c_str()), atoi(awidth.c_str()), atoi(aheight.c_str())};
                nomer++;
            }
        }

        fout.close();
    }

    return nomer;
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



void saving (Mebel* Tomb, int count_knopok)
{
    char s2[100];
    int SaveIndex=GetFolderCountFiles("Saves\\");

    itoa(SaveIndex,s2,10);
    string ss2 = s2;
    const char* SaveName = ("Saves\\save" + ss2 + ".txt").c_str();


    txSleep(300);


    ofstream fout_save;
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

void menu_escape(HDC escape, int* nomer_tomba, Mebel* Tomb, bool* isExit)
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);

    bool isreturn = false;
    if (GetAsyncKeyState('P'))
    {
        txSleep(1000);

        while (!isreturn)
        {

            int x0 = screenW/2 - 300;
            int y0 = screenH/2;
            Button exitButton{"",nullptr,x0 +  30,y0 + 225,x0 + 180,y0 + 255};
            txBitBlt (txDC(), x0, y0, SizerX(escape), SizerY(escape), escape, 0, 0);

            txRectangle(        screenW/2 - 300 +  30, screenH/2 + 105,
                                screenW/2 - 300 + 180, screenH/2 + 135);
            txSleep(20);
            if (     checkClick(x0 +  30, y0 +  65,
                                x0 + 180, y0 +  95))
            {
                isreturn = true;
            }
            else if (checkClick(x0 +  30, y0+105,
                               x0 + 180, y0 + 135))
            {
                *nomer_tomba = download_mebel(Tomb);
                isreturn = true;
            }
            else if (checkClick(x0 +  30, y0 + 145,
                                x0 + 180, y0 + 175))
            {
                saving (Tomb, *nomer_tomba);
                isreturn = true;
            }
            else if (checkClick(x0 +  30, y0 + 225, x0 + 180, y0 + 255))
            {
                txDisableAutoPause();
                *isExit = true;
                isreturn = true;
            }
            txRectangle(        x0 +  30, y0 + 225,x0 + 180, y0 + 255);
        }
    }
}



