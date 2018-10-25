#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"

bool total_exit ();
void menu_escape(HDC escape);
void workspace_background();

const int RAZMER_KNOPKI = 100;

int main()
{
    int count_mebel = 4;
    Mebel Tomb[count_mebel];
    //Сделать функцией обнуления
    for (int i=0; i<count_mebel; i++)
    {
        Tomb[i] = {false, 0, 0};
    }

    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenW, screenH);

    settingsButton = {nullptr, 0, screenH * 75/100, 200, screenH * 80/100};
    newplanButton = {nullptr, 0, screenH * 80/100, 200, screenH * 85/100};
    loadButton = {nullptr, 0, screenH * 85/100, 200, screenH * 90/100};
    saveButton = {nullptr, 0, screenH * 90/100, 200, screenH * 95/100};
    exitButton = {nullptr, 0, screenH * 95/100, 200, screenH};

    HDC sofa = txLoadImage ("Pics\\Sofa.bmp");
    HDC tumba = txLoadImage ("Pics\\Toomba.bmp");
    HDC turba = txLoadImage ("Pics\\TurboJet.bmp");

    int count_knopok_mebeli = 7;
    Button knopki_mebeli[count_knopok_mebeli];
    //Брать размеры картинки из функции Демида
    //Получать координаты в зависимости от номера кнопки (см. код Вадима в СтарЛабиринте)


    knopki_mebeli[0] = {tumba};
    knopki_mebeli[1] = {tumba};
    knopki_mebeli[2] = {sofa};
    knopki_mebeli[3] = {turba};
    knopki_mebeli[4] = {turba};
    knopki_mebeli[5] = {tumba};
    knopki_mebeli[6] = {turba};


    int CurrentX = RAZMER_KNOPKI;//Координата первой кнопки
    int CurrentY = screenH - 3 * RAZMER_KNOPKI;//Координата первой кнопки

    for (int i=0; i<count_knopok_mebeli; i++)
    {
        knopki_mebeli[i].x = CurrentX;
        knopki_mebeli[i].y = CurrentY;
        knopki_mebeli[i].x1 = CurrentX + RAZMER_KNOPKI;
        knopki_mebeli[i].y1 = CurrentY + RAZMER_KNOPKI;
        knopki_mebeli[i].width = vozvrat_wigth(knopki_mebeli[i].picture);
        knopki_mebeli[i].height = vozvrat_hight(knopki_mebeli[i].picture);

        CurrentX = CurrentX + RAZMER_KNOPKI;  //Следующая кнопка чуть правее предыдущей
        //CurrentY = CurrentY + RAZMER_KNOPKI;  //Следующая кнопка чуть правее предыдущей
        if (CurrentX > screenW - RAZMER_KNOPKI)
        {
            CurrentX =  RAZMER_KNOPKI;
            CurrentY = CurrentY + RAZMER_KNOPKI;
        }
    }


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
                for (int i=0; i<count_mebel; i++)
                {
                    Tomb[i] = {false, 0, 0};
                }
            }
            startWS = !returnToMenu;
            menu_escape (escape);

            for (int i=0; i<count_mebel; i++)
            {
                if (Tomb[i].risovat)
                {
                    Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, 200, 200, knopki_mebeli[i].picture, 0, 0, knopki_mebeli[i].width, knopki_mebeli[i].height, TX_WHITE);
                }
            }

            if (checkClick(knopki_mebeli[0].x, knopki_mebeli[0].y, knopki_mebeli[0].x1, knopki_mebeli[0].y1))
            {
                while(txMouseButtons() & 1)
                {
                    workspace_background();
                    risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);
                    Win32::TransparentBlt (txDC(), Tomb[0].MOUSE_X, Tomb[0].MOUSE_Y, 200, 200, Tomb[0].pctr, 0, 0, knopki_mebeli[0].width, knopki_mebeli[0].height, TX_WHITE);

                    //Сделать функцией (очень похоже на risovanieMenuWS)
                    for (int i=0; i<count_mebel; i++)
                    {
                        if (Tomb[i].risovat)
                        {
                            Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, 200, 200, Tomb[i].pctr, 0, 0, knopki_mebeli[i].width, knopki_mebeli[i].height, TX_WHITE);
                        }
                    }

                    //Сделать функцией
                    Tomb[0].pctr = knopki_mebeli[0].picture;
                    Tomb[0].MOUSE_X = txMouseX();
                    Tomb[0].MOUSE_Y = txMouseY();
                    Tomb[0].risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);

                    txSleep(10);
                }
            }

            //Перемецения внутри ВоркСпейса
            if (checkClick(Tomb[0].MOUSE_X, Tomb[0].MOUSE_Y, Tomb[0].MOUSE_X + 200, Tomb[0].MOUSE_Y + 200))
            {
                while(txMouseButtons() & 1)
                {
                    workspace_background();
                    risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);

                    Tomb[0].MOUSE_X = txMouseX();
                    Tomb[0].MOUSE_Y = txMouseY();
                    Tomb[0].risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);

                    for (int i=0; i<count_mebel; i++)
                    {
                        if (Tomb[i].risovat)
                        {
                            Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, 200, 200, knopki_mebeli[i].picture, 0, 0, knopki_mebeli[i].width, knopki_mebeli[i].height, TX_WHITE);
                        }
                    }
                    txSleep(10);
                }
            }

            if (checkClick(knopki_mebeli[2].x, knopki_mebeli[2].y, knopki_mebeli[2].x1, knopki_mebeli[2].y1))
            {
                while(txMouseButtons() & 1)
                {
                    workspace_background();
                    risovanieMenuWS(count_knopok_mebeli, knopki_mebeli);

                    Win32::TransparentBlt (txDC(), Tomb[2].MOUSE_X, Tomb[2].MOUSE_Y, 200, 200, knopki_mebeli[2].picture, 0, 0, 300, 300, TX_WHITE);


                    for (int i=0; i<count_mebel; i++)
                    {
                        if (Tomb[i].risovat)
                        {
                            Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, 200, 200, knopki_mebeli[i].picture, 0, 0, knopki_mebeli[i].width, knopki_mebeli[i].height, TX_WHITE);
                        }
                    }

                    Tomb[2].MOUSE_X = txMouseX();
                    Tomb[2].MOUSE_Y = txMouseY();
                    Tomb[2].pctr = knopki_mebeli[2].picture;
                    Tomb[2].risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);



                    txSleep(10);
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
