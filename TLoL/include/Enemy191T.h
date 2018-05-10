#ifndef ENEMY191T_H
#define ENEMY191T_H
#include <player.h>

#include<GlobalDataStructures.h>

class textureLoader;
class timer;

using namespace std;

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

        //textureLoader *objectTexture;
        vector < vector < textureLoader > > *objectTexture;
        int spriteCharacter;
        int spriteActionType;
        int spriteX;
        timer *objectTimer;

        void updateEnemy(cartesian2d inpTargetLoc);
        cartesian2d getPosition();
        cartesian2d getDestPosition();
        void setPosition(cartesian2d inpCoord);
        void setDestPosition(cartesian2d inpCoord);
        cart2dDim getObjectDimensions();

        void getCurrGridPos(std::vector <grid2d> &retPos);
        void setCurrGridPos(std::vector <grid2d> inpPos);
        void getDestGridPos(std::vector <grid2d> &retPos);
        void setDestGridPos(std::vector <grid2d> inpPos);

        void setIsDead(bool inpBool);
        bool getIsDead();

    protected:

    private:
        void bindObjectTextures(int inpCharacterType);
        void manageSprite();
        void manageGenericTimer();

        double scaleSizeX;
        double scaleSizeY;
        double scaleSizeZ;

        double destXPos;
        double destYPos;

        std::vector <grid2d> classCurrentGridCoords;
        //This is to test if an object can move in a direction
        //I.E. if these coordinates turn out to be bad, then don't update the current grid coordinates
        std::vector <grid2d> classTestGridCoords;

        //for box and graph collisions
        cart2dDim objectDimensions = {.50, .50};

        bool isDead;

        int objectDirection;
        int genericTimerCounter;

};



#endif // ENEMY191T_H
