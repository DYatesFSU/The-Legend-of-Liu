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


    protected:

    private:
        float xPos, yPos, xVel, yVel;


};

#endif // PROJECTILE_H
