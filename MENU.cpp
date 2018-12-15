#pragma once

/*!
\file
\brief ���� ����

����� ������������� ���� ���������

\authors DeSatNik team
\version 1.0.0
\date 13.11.2018
\bug �����������, ���� ���
\warning ����������
\name ��, ��� ������� � ����

*/

#include "TXLib.h"
#include "Button.cpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>


/*!
\brief ������� �������� ��������� ����

������� ���������, ��� ���� �������� �� ������


\param[in] int MinX ����������� ����� ������� �������
\param[in] int MaxX ������������ ������ ������� �������
\param[in] int MinY ����������� ������� ������� �������
\param[in] int MaxY ������������ ������ ������� �������
*/
bool checkFocus(int MinX, int MaxX, int MinY, int MaxY);
/*!
\brief ������� �������� �����

������� ���������, ��� �������� ���� �� �������


\param[in] int MinX ����������� ����� ������� �������
\param[in] int MaxX ������������ ������ ������� �������
\param[in] int MinY ����������� ������� ������� �������
\param[in] int MaxY ������������ ������ ������� �������
*/
bool checkClick(int MinX, int MinY, int MaxX, int MaxY);
/*!
\brief ������� ��������� ������

������� ������ ������  ��� ������ � ������ �� ������


\param[in] Button sofaButton ������ ��� ������� �������� ������
*/
void ikons (Button sofaButton);
/*!
\brief ��������� � ����

������� ������� ��������� ��� ������ ����
*/
void checkMenuFocus();
/*!
\brief ������� ��������� ����

������� ������ ���� �� �������� ������


\param[in] int screenW ������ ������
\param[in] int screenH ������ ������
\param[in] HDC fon_menu ���������. ��� ����
*/
void drawMenu (int screenW, int screenH, HDC fon_menu);
/*!
\brief ������� �������� � ����

������� ��������� ��������� ����� � ����


\param[in] bool returnToMenu ���������� ������� ���������� �������
*/
bool nazad (bool returnToMenu);
/*!
\brief ������� ������ ������

������� ��������� ������� � ������


\param[in] bool startWork ���������� ������� ���������� ������ ������
*/
bool startWorkspace (bool startWork);
int SizerX(HDC pic);
int SizerY(HDC pic);
/*!
\brief ������� ����������� ������� ��������

������� ���������� ������ ��������


\param[in] HDC pic ��������
*/
int SizerX(HDC pic)
{
    HBITMAP hbm=(HBITMAP)Win32::GetCurrentObject(pic, OBJ_BITMAP);
    BITMAP bm;
    Win32::GetObject(hbm,sizeof(bm), (LPVOID)&bm);
    return bm.bmWidth;
}
/*!
\brief ������� ����������� ������� ��������

������� ���������� ������ ��������


\param[in] HDC pic ��������
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
        txTextOut(txMouseX(), txMouseY() - 20, "������� ����������?" );
    }

    else if (checkFocus(saveButton.x, saveButton.y, saveButton.x1, saveButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "�������� ��� �����?" );
    }

    else if (checkFocus(docButton.x, docButton.y, docButton.x1, docButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "������������" );
    }

    else if (checkFocus(exitButton.x, exitButton.y, exitButton.x1, exitButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "�� �� ���, �� �����" );
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
    txTextOut(newplanButton.x, newplanButton.y, "����� ����������");
	//txTextOut(saveButton.x, saveButton.y, "���������");
	//txTextOut(loadButton.x, loadButton.y, "���������");
    txTextOut (exitButton.x, exitButton.y, "�����");
    //txTextOut(settingsButton.x, settingsButton.y, "���������");
    txTextOut(docButton.x, docButton.y, "������������");
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
        txTextOut(settingsButton.x, settingsButton.y, "����");
        txTextOut(settingsButton.x, settingsButton.y, "��������");
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


