struct Mebel
{
    bool risovat;
    int MOUSE_X;
    int MOUSE_Y;
    HDC pctr;
    int width;
    int height;
};

//Clear workspace
void unichtogitVsyuMebelPodryad (Mebel* Tomb, int count_mebel);
//Draw all workspace parts
void risovatVsyuMebelPodryad(Mebel* Tomb, int count_mebel);

void unichtogitVsyuMebelPodryad (Mebel* Tomb, int count_mebel)
{
    for (int i=0; i<count_mebel; i++)
    {
        Tomb[i] = {false, 0, 0};
    }
}

void risovatVsyuMebelPodryad(Mebel* Tomb, int count_mebel)
{
    for (int i=0; i<count_mebel; i++)
    {
        if (Tomb[i].risovat)
        {
            Win32::TransparentBlt (txDC(), Tomb[i].MOUSE_X, Tomb[i].MOUSE_Y, 200, 200, Tomb[i].pctr, 0, 0, Tomb[i].width, Tomb[i].height, TX_WHITE);
        }
    }
}