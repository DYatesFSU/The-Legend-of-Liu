#ifndef MENU_H
#define MENU_H

#include <textureLoader.h>


class Menu
{
    public:
        Menu();
        virtual ~Menu();

        void DrawMenu(float,float);
        void MenuInit(char *);


        int state;

    protected:

    private:
};

#endif // MENU_H
