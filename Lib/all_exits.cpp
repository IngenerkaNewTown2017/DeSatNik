/*!
\file
\brief ������

�������� ��������� � �����

\authors DeSatNik team
\version 1.0.0
\date 15.12.2018
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
