    bool nachalo=false;
    bool CheckFocus(int MinX, int MaxX, int MaxY, int MinY);
{
    if (
        txMouseX() >= MinX && //  мышь находится на кнопке
        txMouseX() <= MaxX &&
        txMouseY() >= MaxY &&
        txMouseY() <= MinY &&
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

    if (CheckFocus(40, 560, 850, 810))

    {
     nachalo = true;
    }


    /* if (CheckFocus(40, 560, 880, 920))
    {
    txTextOut(txMouseX(), txMouseY() - 20, "Сохранение чего-то" );
    }*/


     if (CheckFocus(40, 560, 940, 980))
    {
     txTextOut(txMouseX(), txMouseY() - 20, "Загрузка выбранной планировки" );
    }


     if (CheckFocus(40, 560, 1040, 1000))
    {
     txTextOut(txMouseX(), txMouseY() - 20, "Как ни странно, но это настройки" );
    }

 }
