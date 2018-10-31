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
