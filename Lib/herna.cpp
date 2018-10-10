bool nachalo=false;

int main{
while(!nachalo)
{
draw_main_menu();
}

if( txMouseX>40 && //ÍÎÂÀß ÏËÀÍÈÐÎÂÊÀ
    txMouseX<560 &&
    txMouseY<850 &&
    txMouseY>810 && txMouseButtons() & 1)
    {
     nachalo=true;
    }

   /* if( txMouseX<40 && //ÃÃ®ÃµÃ°Ã Ã­Ã¨Ã²Ã¼
    txMouseX>560 &&
    txMouseY< 880&&
    txMouseY>920 &&  txMouseButtons() & 1)
    {
     saving();
    }*/

    if( txMouseX<40 && //ÃÃ Ã£Ã°Ã³Ã§Ã¨Ã²Ã¼
    txMouseX>560 &&
    txMouseY< 940&&
    txMouseY>980 && txMouseButtons() & 1)
    {
     loading();
    }


    if( txMouseX<40 &&  //ÃÃ Ã±Ã²Ã°Ã®Ã©ÃªÃ¨
    txMouseX>560 &&
    txMouseY< 1040&&
    txMouseY>1000 && txMouseButtons() & 1)
    {
     settings();
    }


    if( txMouseX<40 &&    //ÃÃ»ÃµÃ®Ã¤
    txMouseX>560 &&
    txMouseY< 1070&&
    txMouseY>1010 && txMouseButtons() & 1)
    {
     return 0;
    }
}

