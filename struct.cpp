struct Button
{
    int x;
    int y;
    int x1;
    int y1;
    HDC picture;
    int width;
    int height;
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

struct PicSize
{

    int SizeX;
    int SizeY;
};

struct Mebel
{
    bool risovat;
    int MOUSE_X;
    int MOUSE_Y;
    HDC pctr;
};


