
/*!
\brief ��������� ��� ������

�������� � ���� ������ ����������� ��� �������� ������


*/
struct Button
{
    const char* adress; ///\brief ����� ��������
    HDC picture; ///\brief ���� ��������
    int x; ///\brief ��������� �
    int y; ///\brief ��������� y
    int x1; ///\brief ��������� �1
    int y1; ///\brief ��������� y1
    int width; ///\brief ������
    int height; ///\brief ������
};

Button exitButton;
Button saveButton;
Button newplanButton;
Button loadButton;
Button continueButton;
Button settingsButton;


struct furnature
{
    int x;
    int y;
    int x1;
    int y1;
    HDC picture;
};

struct model
{
    int sizeX;
    int sizeY;
    string title;
    HDC pic;
};


