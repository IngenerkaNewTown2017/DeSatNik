/*!
\file
\brief Звуки и музыка

Файл в котором прописывается музыка и звук

\authors DeSatNik team
\version 1.0.0
\date 13.11.2018
\bug Неисчеслимы, пока что
\warning Осторожнее
\name Функции отвечающие за звук

*/
#include "TXLib.h"
#include <mmsystem.h>

int main()
    {
    txCreateWindow (800, 600);
      PlaySound (TEXT ("supermario.wav"), NULL, SND_SYNC);


    return 0;
    }
