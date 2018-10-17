#include "Lib\\TXLib.h"
#include "Lib\\MENU.cpp"

bool total_exit ();
void menu_escape(HDC escape);
void workspace_background();

const int RAZMER_KNOPKI = 100;

int count_models = 10;

int main()
{
    model Mas_models[count_models];
    for (int i=0; i<count_models; i++)
    {
        Mas_models[i] = {100, 300, "sdf"};
    }

    int screenW = GetSystemMetrics (SM_CXSCREEN);
    int screenH = GetSystemMetrics (SM_CYSCREEN);
    txCreateWindow (screenW, screenH);

    settingsButton = {0, screenH * 75/100, 200, screenH * 80/100};
    newplanButton = {0, screenH * 80/100, 200, screenH * 85/100};
    loadButton = {0, screenH * 85/100, 200, screenH * 90/100};
    saveButton = {0, screenH * 90/100, 200, screenH * 95/100};
    exitButton = {0, screenH * 95/100, 200, screenH};

    HDC sofa = txLoadImage ("Pics\\Sofa.bmp");//Divan
    HDC tumba = txLoadImage ("Pics\\Toomba.bmp");

    int count_mebeli = 3;
    Button mebel[count_mebeli];
    mebel[0] = {    RAZMER_KNOPKI, screenH - 3 * RAZMER_KNOPKI, 2 * RAZMER_KNOPKI, screenH - 2 * RAZMER_KNOPKI, tumba, 300, 300};
    mebel[1] = {4 * RAZMER_KNOPKI, screenH - 3 * RAZMER_KNOPKI, 5 * RAZMER_KNOPKI, screenH - 2 * RAZMER_KNOPKI, tumba, 300, 300};
    mebel[2] = {2 * RAZMER_KNOPKI, screenH - 3 * RAZMER_KNOPKI, 3 * RAZMER_KNOPKI, screenH - 2 * RAZMER_KNOPKI, sofa, 241, 142};

    Mebel Tomb0 = {false, 0, 0};
    Mebel Tomb1 = {false, 0, 0};
    Mebel Tomb2 = {false, 0, 0};


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
            risovanieMenuWS(count_mebeli, mebel);

            returnToMenu = nazad (returnToMenu);
            startWS = !returnToMenu;
            menu_escape (escape);

            if (Tomb0.risovat)
            {
                Win32::TransparentBlt (txDC(), Tomb0.MOUSE_X, Tomb0.MOUSE_Y, 200, 200, Toombs, 0, 0, 300, 300, TX_WHITE);
            }


            if (checkClick(mebel[0].x, mebel[0].y, mebel[0].x1, mebel[0].y1))
            {
                while(txMouseButtons() & 1)
                {
                    workspace_background();
                    risovanieMenuWS(count_mebeli, mebel);
                    Win32::TransparentBlt (txDC(), txMouseX(), txMouseY(), 200, 200, mebel[0].pic, 0, 0, 300, 300, TX_WHITE);

                    Tomb0.MOUSE_X = txMouseX();
                    Tomb0.MOUSE_Y = txMouseY();
                    Tomb0.risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);

                    txSleep(10);
                }
            }

            if (checkClick(mebel[2].x, mebel[2].y, mebel[2].x1, mebel[2].y1))
            {
                while(txMouseButtons() & 1)
                {
                    workspace_background();
                    risovanieMenuWS(count_mebeli, mebel);
                    Win32::TransparentBlt (txDC(), Tomb2.MOUSE_X, Tomb2.MOUSE_Y, 200, 200, mebel[2].pic, 0, 0, 300, 300, TX_WHITE);

                    Tomb2.MOUSE_X = txMouseX();
                    Tomb2.MOUSE_Y = txMouseY();

                    Tomb2.risovat = checkFocus(50, 50, screenW - 50 - 200, screenH - 350 - 200);



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
            //testova(Mas_models, count_models);
        }

        if (total_exit ())
        {
            txDisableAutoPause();
            isExit = true;
        };

        txSleep(10);
        txEnd();
    }

    txDeleteDC(sofa);
    txDeleteDC(fon_menu);
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
        {                     //x   y    Ã¯Â¿Â½Ã¯Â¿Â½Ã¯Â¿Â½  Ã¯Â¿Â½Ã¯Â¿Â½Ã¯Â¿Â½        x    y
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
