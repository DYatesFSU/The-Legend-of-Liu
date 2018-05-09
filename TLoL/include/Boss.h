#ifndef BOSS_H
#define BOSS_H

#include <GlobalDataStructures.h>
#include <timer.h>
#include <textureLoader.h>

class textureLoader;
class timer;

class Boss
{
    public:
        Boss();
        virtual ~Boss();

         cartesian3d vertices[4];

        int waitTime;
        int shootTime;
        bool waiting;

        void drawObject();
        void bossInit(double x, char s);

        double getxVel();
        void setxVel(double x);

        double getxPos();
        void setxPos(double x);

        double getyPos();
        void setyPos(double x);

        double getyVel();
        void setyVel(double y);

        bool getShooting();
        void setShooting(bool);
        char getFiringDir();
        void setFiringDir(char x);

        textureLoader *objectTexture;
        timer *objectTimer;
        timer *shootTimer;

    protected:

    private:
        double xPos, yPos, xVel, yVel;
        bool shooting;
        char firingDir;
};

#endif // BOSS_H
