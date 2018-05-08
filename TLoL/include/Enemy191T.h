#ifndef ENEMY191T_H
#define ENEMY191T_H
#include <player.h>

#include<GlobalDataStructures.h>

class textureLoader;
class timer;

class Enemy191T
{
    public:
        Enemy191T();
        virtual ~Enemy191T();
        cartesian3d vertices[4];
        int waitTime;

        double runspeed;



        void drawObject();
        void objectInit();

        //NM: this is intended to change as it is bad design
        void orientDirection(int direction, cartesian2d retCoord[]);

        double Xpos;
        double Ypos;
        double Zpos;
        double destXPos, destYPos;
        double xVel, yVel;

        double getxVel();
        void setxVel(double x);

        double getyVel();
        void setyVel(double y);

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

        void updateEnemy(player* ply);

    protected:

    private:

};



#endif // ENEMY191T_H
