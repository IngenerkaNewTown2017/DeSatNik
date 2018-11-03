#pragma once

#include "TXLib.h"
#include "Button.cpp"

bool checkFocus(int MinX, int MaxX, int MinY, int MaxY);
bool checkClick(int MinX, int MinY, int MaxX, int MaxY);
void ikons (Button sofaButton);
void checkMenuFocus();
void drawMenu (int screenW, int screenH, HDC fon_menu);
bool nazad (bool returnToMenu);
bool startWorkspace (bool startWork);
int SizerX(HDC pic);
int SizerY(HDC pic);


int SizerX(HDC pic)
{
    HBITMAP hbm=(HBITMAP)Win32::GetCurrentObject(pic, OBJ_BITMAP);
    BITMAP bm;
    Win32::GetObject(hbm,sizeof(bm), (LPVOID)&bm);
    return bm.bmWidth;
}

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

    else if (checkFocus(loadButton.x, loadButton.y, loadButton.x1, loadButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Загрузить что ль?" );
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
	txTextOut(saveButton.x, saveButton.y, "Сохранить");
	txTextOut(loadButton.x, loadButton.y, "Загрузить");
    txTextOut (exitButton.x, exitButton.y, "Выйти");
    txTextOut(settingsButton.x, settingsButton.y, "Настройки");
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
	if (GetAsyncKeyState(VK_RETURN))
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
