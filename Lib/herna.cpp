bool nachalo=false;

int main
{
while(!nachalo)
{
draw_main_menu();
}

if( txMouseX<40 && //ÍÎÂÀß ÏËÀÍÈÐÎÂÊÀ
    txMouseX>560 &&
    txMouseY<850 &&
    txMouseY>810 &&)
    {
     nachalo=true;
    }

   /* if( txMouseX<40 && //Ñîõðàíèòü
    txMouseX>560 &&
    txMouseY< 880&&
    txMouseY>920 &&)
    {
     saving();
    }*/

    if( txMouseX<40 && //Çàãðóçèòü
    txMouseX>560 &&
    txMouseY< 940&&
    txMouseY>980 &&)
    {
     loading();
    }


    if( txMouseX<40 &&  //Íàñòðîéêè
    txMouseX>560 &&
    txMouseY< 1040&&
    txMouseY>1000 &&)
    {
     settings();
    }


    if( txMouseX<40 &&    //Âûõîä
    txMouseX>560 &&
    txMouseY< 1070&&
    txMouseY>1010 &&)
    {
     return 0;
    }



}
