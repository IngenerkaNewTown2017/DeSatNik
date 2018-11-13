#pragma once

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

#include "Button.cpp"
#include <iostream>
#include <fstream>

using namespace std;
/*!
\brief Сетка

Функция рисования сетки
*/
void grid();
/*!
\brief функция проверки клика

Функция читает из файла


\param[in] Button* knopki_mebeli читаемая кнопка
*/
int read(Button* knopki_mebeli);

const int RAZMER_KNOPKI = 100;
/*!
\brief Фон рабочей области

Функция рисования фона рабочей области
*/
void workspace_background()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txClear();
    txSetColor(TX_BLACK, 5);
    txRectangle(50, 50, screenW - 50, screenH - 350);
    txSetColor(TX_WHITE);

    //Grid
    grid();
}

void grid()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
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
/*!
\brief Функция выбора кнопки

Функция отвечающая за реакцию кнопки
\param[in] int screenW Ширина экрана
\param[in] int screenH Высота экрана
\param[in] Mebel* Tomb Рисуемая мебель
\param[in] Button knopki_mebeli Кнопка
*/
void button_selection(int screenW, int screenH, Mebel* Tomb, Button knopki_mebeli)
{
    Tomb->pctr = knopki_mebeli.picture;
    Tomb->MOUSE_X = txMouseX();
    Tomb->MOUSE_Y = txMouseY();
    Tomb->width = SizerX(knopki_mebeli.picture);
    Tomb->height = SizerY(knopki_mebeli.picture);
    Tomb->risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);
    Tomb->adressMebeli = knopki_mebeli.adress;
}
/*!
\brief Функция выбора кнопки

Функция отвечающая за координаты кнопок на панели

\param[in] int count_knopok_mebeli Предел колличества кнопок
\param[in] Button knopki_mebeli Кнопка
*/
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
//PicSize

                nomer++;
            }
        }

        fout.close();
     }

     return nomer;

}

void drDre(Mebel* knopki_mebeli)
{

    const char* adress = "";
    ifstream fout;
    const char* imya_faila = txInputBox ("Choose Save)", "System", "");

    adress = imya_faila;
    fout.open(imya_faila);

    if (!fout)
    {
        fout.close();
        char* imya_faila2 = new char[195];
        strcpy(imya_faila2, "Saves\\");
        strcat(imya_faila2, imya_faila);
        fout.open(imya_faila2);
        adress = imya_faila2;
    }
    if (!fout)
    {
        fout.close();
        char* imya_faila3 = new char[195];
        strcpy(imya_faila3, "Save\\");
        strcat(imya_faila3, imya_faila);
        strcat(imya_faila3, ".txt");
        fout.open(imya_faila3);
        adress = imya_faila3;
    }






 }
