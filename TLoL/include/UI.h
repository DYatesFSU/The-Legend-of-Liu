#ifndef UI_H
#define UI_H

#include<GlobalDataStructures.h>

#include <textureLoader.h>

class textureLoader;

class UI
{
    public:
        UI();
        virtual ~UI();

        cartesian3d vertices[4];

        void orientDirection(int direction, cartesian2d retCoord[]);

        void uiInit();
        void drawUI();
        void showKeys();

        int getHealth();
        void setHealth(int hp);

        void addKey();
        int getKeys();

        textureLoader *playerPic;
        textureLoader *heartPic;
        textureLoader *keysPic;

        void drawPlayerFrame();
        void drawKeysFrame();
        void drawHeartFrame();
        void resetKeys();

    protected:

    private:
        int health;
        int playerKeys;
};

#endif // UI_H
