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

        void projInit(float, float, char);
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


    protected:

    private:
        float xPos, yPos, xVel, yVel;

        std::vector <grid2d> classCurrentGridCoords;
        cart2dDim objectDimensions = {.25, .25};


};

#endif // PROJECTILE_H
