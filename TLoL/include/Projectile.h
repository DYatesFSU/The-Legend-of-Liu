#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "timer.h"
#include "textureLoader.h"

#include<GlobalDataStructures.h>

class timer;
class textureLoader;

class Projectile
{
    public:
        Projectile();
        virtual ~Projectile();

        cartesian3d vertices[4];

        textureLoader *objectTexture;

        void projInit(float, float, char, int inpProjTeam);
        void drawProj();

        float getxPos();
        float getyPos();
        float getxVel();
        float getyVel();

        void setxPos(float);
        void setyPos(float);
        void setxVel(float);
        void setyVel(float);

        timer *lifeTime = new timer();
        cart2dDim getObjectDimensions();
        cartesian2d getPosition();
        void setPosition(cartesian2d inpCoord);

        void getCurrGridPos(std::vector <grid2d> &retPos);
        void setCurrGridPos(std::vector <grid2d> inpPos);


        void setIsDead(bool inpBool);
        bool getIsDead();

        void setObjectTeam(int inpTeam);
        int getObjectTeam();

    protected:

    private:
        float xPos, yPos, xVel, yVel;

        std::vector <grid2d> classCurrentGridCoords;
        cart2dDim objectDimensions = {.20, .20};

        int objectTeam;

        bool isDead;


};

#endif // PROJECTILE_H
