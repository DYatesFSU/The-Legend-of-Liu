#ifndef ENEMY191T_H
#define ENEMY191T_H

#include<GlobalDataStructures.h>

class textureLoader;
class timer;

class Enemy191T
{
    public:
        Enemy191T();
        virtual ~Enemy191T();
        cartesian3d vertices[4];

        int runspeed;
        int jumpspeed;
        int actionTrigger;

        void drawObject();
        void objectInit();
        void objectAction();

        //NM: this is intended to change as it is bad design
        void orientDirection(int direction, cartesian2d retCoord[]);

        double Xpos;
        double Ypos;
        double Zpos;

        //void calcSprite();
        //void selectSprite(int x, int y, int spritesHeight, int spritesWidth);

        /*
        int spriteX, spriteY;
        const int sprHeight = 8;
        const int sprWidth = 10;
        int sprRenderCount;
        */

        textureLoader *objectTexture;
        timer *objectTimer;

    protected:

    private:
};

#endif // ENEMY191T_H
