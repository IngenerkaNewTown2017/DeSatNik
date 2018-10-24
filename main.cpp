#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"

bool total_exit ();
void menu_escape(HDC escape);
void workspace_background();
void unichtogitVsyuMebelPodryad (Mebel* Tomb, int count_mebel);
void risovatVsyuMebelPodryad(Mebel* Tomb, int count_mebel);
void savingChetoTam(int screenW, int screenH, Mebel* Tomb, Button knopki_mebeli);
void CheckKavo(int screenW, int screenH, Mebel* Tomb, Button knopki_mebeli);

const int RAZMER_KNOPKI = 100;

int main()
{
    int count_mebel = 4;
    Mebel Tomb[count_mebel];
    //СделаL функцию обнуления
    unichtogitVsyuMebelPodryad (Tomb, count_mebel);

    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenW, screenH);

    settingsButton = {0, screenH * 75/100, 200, screenH * 80/100};
    newplanButton = {0, screenH * 80/100, 200, screenH * 85/100};
    loadButton = {0, screenH * 85/100, 200, screenH * 90/100};
    saveButton = {0, screenH * 90/100, 200, screenH * 95/100};
    exitButton = {0, screenH * 95/100, 200, screenH};

    HDC sofa = txLoadImage ("Pics\\Sofa.bmp");
    HDC tumba = txLoadImage ("Pics\\Toomba.bmp");
    HDC turba = txLoadImage ("Pics\\TurboJet.bmp");

    int count_knopok_mebeli = 4;
    Button knopki_mebeli[count_knopok_mebeli];
    //Брать размеры картинки из функции Демида
    //Получать координаты в зависимости от номера кнопки (см. код Вадима в СтарЛабиринте)
    knopki_mebeli[0] = {    RAZMER_KNOPKI, screenH - 3 * RAZMER_KNOPKI, 2 * RAZMER_KNOPKI, screenH - 2 * RAZMER_KNOPKI, tumba, 300, 300};
    knopki_mebeli[1] = {2 * RAZMER_KNOPKI, screenH - 3 * RAZMER_KNOPKI, 3 * RAZMER_KNOPKI, screenH - 2 * RAZMER_KNOPKI, tumba, 300, 300};
    knopki_mebeli[2] = {3 * RAZMER_KNOPKI, screenH - 3 * RAZMER_KNOPKI, 4 * RAZMER_KNOPKI, screenH - 2 * RAZMER_KNOPKI, sofa, 241, 142};
    knopki_mebeli[3] = {4 * RAZMER_KNOPKI, screenH - 3 * RAZMER_KNOPKI, 5 * RAZMER_KNOPKI, screenH - 2 * RAZMER_KNOPKI, turba, 160, 190};


    HDC WSpace = txLoadImage ("Pics\\Workspace.bmp");
    HDC fon_menu = txLoadImage ("Pics\\ClearFonMenu.bmp");
    HDC escape= txLoadImage ("Pics\\menu_escape.bmp");



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

            returnToMenu = nazad (returnToMenu);
            if (returnToMenu)
            {
                risovatVsyuMebelPodryad(Tomb, count_mebel);
            }
            startWS = !returnToMenu;
            //menu_escape (escape);

            risovatVsyuMebelPodryad(Tomb, count_mebel);

            for (int nomer_mebeli = 0; nomer_mebeli < count_knopok_mebeli; nomer_mebeli++)
            {
                if (checkClick(knopki_mebeli[nomer_mebeli].x, knopki_mebeli[nomer_mebeli].y, knopki_mebeli[nomer_mebeli].x1, knopki_mebeli[nomer_mebeli].y1))
                {
                    while(txMouseButtons() & 1)
                    {
                        workspace_background();
                        risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                        risovatVsyuMebelPodryad(Tomb, count_mebel);
                        savingChetoTam(screenW, screenH, &Tomb[nomer_mebeli], knopki_mebeli[nomer_mebeli]);

                        txSleep(10);
                    }
                }
            }

            //Перемецения внутри ВоркСпейса


            for (int nomer_mebeli = 0; nomer_mebeli < count_knopok_mebeli; nomer_mebeli++)
            {
                if (checkClick(Tomb[nomer_mebeli].MOUSE_X, Tomb[nomer_mebeli].MOUSE_Y, Tomb[nomer_mebeli].MOUSE_X + 200, Tomb[nomer_mebeli].MOUSE_Y + 200))
                {
                    while(txMouseButtons() & 1)
                    {
                        workspace_background();
                        risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                        savingChetoTam(screenW, screenH, &Tomb[nomer_mebeli], knopki_mebeli[nomer_mebeli]);
                        risovatVsyuMebelPodryad(Tomb, count_mebel);
                        txSleep(10);
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

        if (total_exit ())
        {
            txDisableAutoPause();
            isExit = true;
        }

        txSleep(10);
        txEnd();
    }


    //Удалять все картинки из 2 наших массивов (так будет проще)
    txDeleteDC(sofa);
    txDeleteDC(fon_menu);
    txDeleteDC(escape);
    txDeleteDC(WSpace);

    return 0;
}

bool total_exit ()
{
    if (txMouseX() > exitButton.x  &&
        txMouseX() < exitButton.x1 &&
        txMouseY() > exitButton.y  &&
        txMouseY() < exitButton.y1 &&
        txMouseButtons() & 1)
    {
        return true;
    }

    return false;
}

void menu_escape(HDC escape)
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);

    bool isreturn = false;
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        txSleep(1000);

        while (!isreturn)

            txBitBlt (txDC(), screenH/2, screenW/2 - 300, 215, 291, escape, 0, 0);

            if ((txMouseButtons() & 1 &&
                txMouseX() > 0 && txMouseX() < 800
            &&  txMouseY() > 0 && txMouseY() < 321) or GetAsyncKeyState(VK_ESCAPE))
            {
                isreturn = true;
            }

            txSleep(10);
        }
    }


void unichtogitVsyuMebelPodryad (Mebel* Tomb, int count_mebel)
{
    for (int i=0; i<count_mebel; i++)
    {
        Tomb[i] = {false, 0, 0};
    }
}

void risovatVsyuMebelPodryad(Mebel* Tomb, int count_mebel)
{
    for (int i=0; i<count_mebel; i++)
    {
        if (Tomb[i].risovat)
        {
            Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, 200, 200, Tomb[i].pctr, 0, 0, Tomb[i].width, Tomb[i].height, TX_WHITE);
        }
    }
}

 void savingChetoTam(int screenW, int screenH, Mebel* Tomb, Button knopki_mebeli){


                    Tomb->pctr = knopki_mebeli.picture;
                    Tomb->MOUSE_X = txMouseX();
                    Tomb->MOUSE_Y = txMouseY();
                    Tomb->width = knopki_mebeli.width;
                    Tomb->height = knopki_mebeli.height;
                    Tomb->risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);

  }
  void workspace_background()
{
    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txClear();
    txSetColor(TX_BLACK, 5);
    txRectangle(50, 50, screenW - 50, screenH - 350);
    txSetColor(TX_WHITE);

    //Grid
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
