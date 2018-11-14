
/*!
\brief Структура для кнопок

Собирает в себе данные необходимые для создания кнопки


*/
struct Button
{
    const char* adress; ///\brief Адрес картинки
    HDC picture; ///\brief Сама картинка
    int x; ///\brief Координта х
    int y; ///\brief Координта y
    int x1; ///\brief Координта х1
    int y1; ///\brief Координта y1
    int width; ///\brief ширина
    int height; ///\brief Высота
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


