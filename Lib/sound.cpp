/*!
\file
\brief ����� � ������

���� � ������� ������������� ������ � ����

\authors DeSatNik team
\version 1.0.0
\date 13.11.2018
\bug �����������, ���� ���
\warning ����������
\name ������� ���������� �� ����

*/
#include "TXLib.h"
#include <mmsystem.h>

int main()
{
    txCreateWindow (600, 315);
    txDisableAutoPause();
    HDC fon = txLoadImage ("��� ������.bmp");
    txBitBlt (txDC(), 0, 0, 600, 315, fon, 0, 0);
    txDeleteDC (fon);
    PlaySound (TEXT ("supermario.wav"), NULL, SND_SYNC);

    return 0;
}
