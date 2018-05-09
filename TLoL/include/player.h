#ifndef PLAYER_H
#define PLAYER_H

#include<Model.h>
#include<gl/gl.h>
//#include<textureLoader.h>

#include <GlobalDataStructures.h>

typedef struct
{
   float x;
   float y;
   float z;
}vec;

class textureLoader;
class timer;

class player:Model
{
    public:
        player();
        virtual ~player();

        float scalesize[3]={1.0,1.0,1.0};
        vec verticies[4];

        int runspeed;
        int jumpspeed;
        int actionTrigger;

        void drawPlayer(bool);
        void playerInit();
        void actions(int);

        float getxPos();
        void setxPos(float);

        float getyPos();
        void setyPos(float);

        void setMoving(int);
        int getMoving();

        void setMovingHorizontal(bool);
        bool getMovingHorizontal();

        void setMovingVertical(bool);
        bool getMovingVertical();

        void setxVel(float);
        float getxVel();

        void setyVel(float);
        float getyVel();

        bool movingUp = false, movingDown = false, movingLeft = false, movingRight = false;
        bool checkMoving();

        bool facingRight = true;

        void calcSprite ();
        void selectSprite(int x, int y, int spritesHeight, int spritesWidth);
        bool compareMoves();

        void moveObject();

        /*
        int spriteX, spriteY;
        const int sprHeight = 8;
        const int sprWidth = 10;
        int sprRenderCount;
        bool sprPrevMovUp, sprPrevMovDown, sprPrevMovLeft, sprPrevMovRight;

        textureLoader *objectTexture;
        timer *objectTimer;
        */

    protected:

    private:

        double scaleSizeX;
        double scaleSizeY;
        double scaleSizeZ;

        int spriteX, spriteY;
        const int sprHeight = 8;
        const int sprWidth = 10;
        int sprRenderCount;
        bool sprPrevMovUp, sprPrevMovDown, sprPrevMovLeft, sprPrevMovRight;

        textureLoader *objectTexture;
        timer *objectTimer;

        float xPos = 0, yPos = 0, xVel = 0, yVel = 0;

        std::vector <grid2d> classCurrentGridCoords;
        //This is to test if an object can move in a direction
        //I.E. if these coordinates turn out to be bad, then don't update the current grid coordinates
        std::vector <grid2d> classTestGridCoords;



};

#endif // PLAYER_H
