/*!
\file
\brief ������

�������� ��������� � �����

\authors DeSatNik team
\version 1.0.0
\date 13.11.2018
\bug �����������, ���� ���
\warning ����������
\name ������� ������ �� ���������

*/

bool total_exit (Button exitButton)
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
    if (GetAsyncKeyState('P'))
    {
        txSleep(1000);

        while (!isreturn)
        {

            txBitBlt (txDC(), screenH/2, screenW/2 - 300, SizerX(escape), SizerX(escape), escape, 0, 0);
            txSleep(20);
            if ((txMouseButtons() & 1 &&
                txMouseX() > screenW/2 - 300 +30 && txMouseX() < screenW/2 - 300 + 180
            &&  txMouseY() > screenH/2 +65  && txMouseY() < screenH/2+95) )
            {
                isreturn = true;

            } else if ((txMouseButtons() & 1 &&
                txMouseX() > screenW/2 - 300 +30 && txMouseX() < screenW/2 - 300 + 180
            &&  txMouseY() > screenH/2 +105  && txMouseY() < screenH/2+135) )
            {
              GetAsyncKeyState('L');

            } else if ((txMouseButtons() & 1 &&
                txMouseX() > screenW/2 - 300 +30 && txMouseX() < screenW/2 - 300 + 180
            &&  txMouseY() > screenH/2 +145  && txMouseY() < screenH/2+175) )
            {
             GetAsyncKeyState('S');

            } else if ((txMouseButtons() & 1 &&
                txMouseX() > screenW/2 - 300 +30 && txMouseX() < screenW/2 - 300 + 180
            &&  txMouseY() > screenH/2 +225  && txMouseY() < screenH/2+255) )
            {
             GetAsyncKeyState(VK_ESCAPE);
            }
        }
    }
}
