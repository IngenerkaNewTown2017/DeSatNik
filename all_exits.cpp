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
