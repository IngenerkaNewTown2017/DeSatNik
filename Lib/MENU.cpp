#include "TXLib.h"
#include "struct.cpp"

bool checkFocus(int MinX, int MaxX, int MinY, int MaxY);
void ikons (Button sofaButton);
void checkMenuFocus();
void drawMenu (int screenW, int screenH, HDC fon_menu);

void testova ( model* Mas_models, int count_Models);
bool startWorkspace (bool startWork);

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

void checkMenuFocus()
{
    if (checkFocus(newplanButton.x, newplanButton.y, newplanButton.x1, newplanButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Ñîçäàòü ïëàíèðîâêó?" );
    }

    else if (checkFocus(saveButton.x, saveButton.y, saveButton.x1, saveButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Ñîõðàíèì ÷òî èìååì?" );
    }

    else if (checkFocus(loadButton.x, loadButton.y, loadButton.x1, loadButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Çàãðóçèòü ÷òî ëü?" );
    }

    else if (checkFocus(exitButton.x, exitButton.y, exitButton.x1, exitButton.y1))
    {
        txTextOut(txMouseX(), txMouseY() - 20, "Äà íó ëàí, íå óõîäè" );
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
    txTextOut(newplanButton.x, newplanButton.y, "Íîâàÿ ïëàíèðîâêà");
	txTextOut(saveButton.x, saveButton.y, "Ñîõðàíèòü");
	txTextOut(loadButton.x, loadButton.y, "Çàãðóçèòü");
    txTextOut (exitButton.x, exitButton.y, "Âûéòè");
}


void testova ( model* Mas_models, int count_Models)
{

    for(int i =0; i<count_Models; i++)
    {
        //txSetFillColor(TX_RED);
        txRectangle(10*i, 10*i, 10*i+Mas_models[i].sizeX, 10*i+Mas_models[i].sizeY);
    }
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

void nazad ()
{    //dodelat
    return;
}

void ikons (Button sofaButton) {
	         //txBitBlt (txDC(), sofaButton.x, sofaButton.y, sofaButton.x1 - sofaButton.x, sofaButton.y1 - sofaButton.y, sofaButton.picture);
Win32::TransparentBlt (txDC(), sofaButton.x, sofaButton.y, sofaButton.x1 - sofaButton.x, sofaButton.y1 - sofaButton.y, sofaButton.picture, 0, 0, sofaButton.width, sofaButton.height, -1);
}
