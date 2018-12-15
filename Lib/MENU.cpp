#pragma once

/*!
\file
\brief Файл Меню

Здесь прописывается меню программы

\authors DeSatNik team
\version 1.0.0
\date 13.11.2018
\bug Неисчеслимы, пока что
\warning Осторожнее
\name То, что связано с меню

*/

#include "TXLib.h"
#include "Button.cpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>


/*!
\brief функция проверки положения мыши

Функция проверяет, что мышь наведена на объект


\param[in] int MinX Минимальная левая граница объекта
\param[in] int MaxX Максимальная правая граница объекта
\param[in] int MinY Минимальная верхняя граница объекта
\param[in] int MaxY Максимальная нижняя граница объекта
*/
bool checkFocus(int MinX, int MaxX, int MinY, int MaxY);
/*!
\brief функция проверки клика

Функция проверяет, что совершён клик по объекту


\param[in] int MinX Минимальная левая граница объекта
\param[in] int MaxX Максимальная правая граница объекта
\param[in] int MinY Минимальная верхняя граница объекта
\param[in] int MaxY Максимальная нижняя граница объекта
*/
bool checkClick(int MinX, int MinY, int MaxX, int MaxY);
/*!
\brief функция рисования иконки

Функция рисует иконку  для кнопки к мебели на панели


\param[in] Button sofaButton Кнопка для которой рисуется иконка
*/
void ikons (Button sofaButton);
/*!
\brief Подсказки в меню

Функция выводит подсказки для кнопок меню
*/
void checkMenuFocus();
/*!
\brief функция рисования меню

Функция рисует меню по размерам экрана


\param[in] int screenW Ширина экрана
\param[in] int screenH Высота экрана
\param[in] HDC fon_menu Картинака. Фон меню
*/
void drawMenu (int screenW, int screenH, HDC fon_menu);
/*!
\brief функция возврата в меню

Функция позволяет вернуться назад в меню


\param[in] bool returnToMenu Переменная которая регулирует возврат
*/
bool nazad (bool returnToMenu);
/*!
\brief функция начала работы

Функция позволяет перейти к работе


\param[in] bool startWork Переменная которая регулирует начало работы
*/
bool startWorkspace (bool startWork);
int SizerX(HDC pic);
int SizerY(HDC pic);
/*!
\brief функция определения размера картинки

Функция возвращает ширину картинки


\param[in] HDC pic Картинка
*/
int SizerX(HDC pic)
{
    HBITMAP hbm=(HBITMAP)Win32::GetCurrentObject(pic, OBJ_BITMAP);
    BITMAP bm;
    Win32::GetObject(hbm,sizeof(bm), (LPVOID)&bm);
    return bm.bmWidth;
}
/*!
\brief функция определения размера картинки

Функция возвращает высоту картинки


\param[in] HDC pic Картинка
*/
int SizerY(HDC pic)
{
    HBITMAP hbm=(HBITMAP)Win32::GetCurrentObject(pic, OBJ_BITMAP);
    BITMAP bm;
    Win32::GetObject(hbm,sizeof(bm), (LPVOID)&bm);
    return bm.bmHeight;
}

bool checkFocus(int MinX, int MinY, int MaxX, int MaxY)
{
    if (
        txMouseX() >= MinX &&
        txMouseX() <= MaxX &&
        txMouseY() <= MaxY &&
        txMouseY() >= MinY
        )
    {
        return true;
    }

    return false;
}

bool checkClick(int MinX, int MinY, int MaxX, int MaxY)
{
    if (
        txMouseX() >= MinX &&
        txMouseX() <= MaxX &&
        txMouseY() <= MaxY &&
        txMouseY() >= MinY &&
        txMouseButtons() & 1
        )
    {
        return true;
    }

    return false;
}

void checkMenuFocus()
{
    if (checkFocus(newplanButton.x, newplanButton.y, newplanButton.x1, newplanButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Создать планировку?" );
    }

    else if (checkFocus(saveButton.x, saveButton.y, saveButton.x1, saveButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Сохраним что имеем?" );
    }

    else if (checkFocus(docButton.x, docButton.y, docButton.x1, docButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Документация" );
    }

    else if (checkFocus(exitButton.x, exitButton.y, exitButton.x1, exitButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Да ну лан, не уходи" );
    }
}

void drawMenu (int screenW, int screenH, HDC fon_menu)
{
    txSetColor(TX_BLACK);
    txClear();
    Win32::TransparentBlt (txDC(), 0, 0, screenW, screenH, fon_menu, 0, 0, 1556, 976, RGB(123,124,1));
    //txBitBlt (txDC(), 0, 0, screenW, screenH, fon_menu, 0, 0);

    txSelectFont("Harlow Solid Italic", 40);
    txSetColor(TX_WHITE);
    txTextOut(newplanButton.x, newplanButton.y, "Новая планировка");
	//txTextOut(saveButton.x, saveButton.y, "Сохранить");
	//txTextOut(loadButton.x, loadButton.y, "Загрузить");
    txTextOut (exitButton.x, exitButton.y, "Выйти");
    //txTextOut(settingsButton.x, settingsButton.y, "Настройки");
    txTextOut(docButton.x, docButton.y, "Документэйшн");
}

bool startWorkspace (bool startWork)
{
    if (checkFocus(newplanButton.x, newplanButton.y, newplanButton.x1, newplanButton.y1) &&
        txMouseButtons() & 1)
    {
		startWork = true;
    }

    return startWork;
}

bool nazad (bool returnToMenu)
{
	if (GetAsyncKeyState('M'))
	{
		returnToMenu = true;
	}

	return returnToMenu;
}

void ikons (Button sofaButton)
{
    Win32::TransparentBlt (txDC(), sofaButton.x, sofaButton.y, sofaButton.x1 - sofaButton.x, sofaButton.y1 - sofaButton.y, sofaButton.picture, 0, 0, sofaButton.width, sofaButton.height, -1);
}

void risovanieMenuWS(int count_buttons, Button* SofaButtons)
{
    for (int i=0; i<count_buttons; i++)
    {
        ikons (SofaButtons[i]);
    }
}

void settings (Button settingsButton)
{
    if (txMouseX() > settingsButton.x  &&
        txMouseX() < settingsButton.x1 &&
        txMouseY() > settingsButton.y  &&
        txMouseY() < settingsButton.y1 &&
        txMouseButtons() & 1)
    {
        txClear();
        txSetColor (TX_WHITE);
        txSelectFont("Harlow Solid Italic", 40);
        txTextOut(settingsButton.x, settingsButton.y, "Звук");
        txTextOut(settingsButton.x, settingsButton.y, "Описание");
     }
}

void doc (Button docButton)
{
    if (txMouseX() > docButton.x  &&
        txMouseX() < docButton.x1 &&
        txMouseY() > docButton.y  &&
        txMouseY() < docButton.y1 &&
        txMouseButtons() & 1)
    {
    system("Documentation.chm");
     }
}


