#pragma once


struct Button
{
    const char* adress;
    HDC picture;
    int x;
    int y;
    int x1;
    int y1;
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

struct Mebel
{
    bool risovat;
    int MOUSE_X;
    int MOUSE_Y;
    HDC pctr;
    int width;
    int height;
};


