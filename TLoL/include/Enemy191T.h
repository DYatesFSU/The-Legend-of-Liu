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
        double scaleSizeX;
        double scaleSizeY;
        double scaleSizeZ;

        std::vector <grid2d> classCurrentGridCoords;
        //This is to test if an object can move in a direction
        //I.E. if these coordinates turn out to be bad, then don't update the current grid coordinates
        std::vector <grid2d> classTestGridCoords;

};



#endif // ENEMY191T_H
