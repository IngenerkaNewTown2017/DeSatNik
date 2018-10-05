#include "TXLib.h"
#include "struct.cpp"

bool checkFocus(int MinX, int MaxX, int MinY, int MaxY);
void checkMenuFocus();
void drawMenu (int screenW, int screenH, HDC fon_menu);
void testova ( model* Mas_models, int count_Models);
void startWorkspace ();

bool checkFocus(int MinX, int MaxX, int MinY, int MaxY)
{
    if (
        txMouseX() >= MinX && //  iuou iaoiaeony ia eiiiea
        txMouseX() <= MaxX &&
        txMouseY() <= MaxY &&
        txMouseY() >= MinY
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
        txTextOut(txMouseX(), txMouseY() - 20, "Загрузить что ль?" );
    }

    else if (checkFocus(loadButton.x, loadButton.y, loadButton.x1, loadButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Сохраним что имеем?" );
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
    Win32::TransparentBlt (txDC(), 0, 0, screenW, screenH, fon_menu, 0, 0, 1950, 1400, -1);
    //txBitBlt (txDC(), 0, 0, screenW, screenH, fon_menu, 0, 0);

    txSelectFont("Harlow Solid Italic", 40);
    txSetColor(TX_WHITE);
    txTextOut(newplanButton.x, newplanButton.y, "Новая планировка");
	txTextOut(saveButton.x, saveButton.y, "Загрузить");
	txTextOut(loadButton.x, loadButton.y, "Сохранить");
    txTextOut (exitButton.x, exitButton.y, "Выйти");
}


void startWorkspace () {     //DODELAT!!!!}

}

void testova ( model* Mas_models, int count_Models) {     //DODELAT!!!!

 for(int i =0; i<count_Models; i++)
 {
 txSetFillColor(TX_RED);
 txRectangle(10*i, 10*i, 10*i+Mas_models[i].sizeX, 10*i+Mas_models[i].sizeY);
 }

}
