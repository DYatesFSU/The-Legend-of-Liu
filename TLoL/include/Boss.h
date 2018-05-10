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
        void bossInit(double x, char s, int i);

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


        void setIsDead(bool inpBool);
        bool getIsDead();

        void modifyHealth(int inpModifier);
        int getHealth();


        cartesian2d getPosition();
        cartesian2d getDestPosition();
        void setPosition(cartesian2d inpCoord);
        void setDestPosition(cartesian2d inpCoord);
        cart2dDim getObjectDimensions();

        void getCurrGridPos(std::vector <grid2d> &retPos);
        void setCurrGridPos(std::vector <grid2d> inpPos);
        void getDestGridPos(std::vector <grid2d> &retPos);
        void setDestGridPos(std::vector <grid2d> inpPos);

    protected:

    private:
        double xPos, yPos, xVel, yVel;
        bool shooting;
        char firingDir;

        cart2dDim objectDimensions = {.50, .50};
        cartesian2d destPosition;

        std::vector <grid2d> classCurrentGridCoords;
        std::vector <grid2d> classTestGridCoords;

        bool isDead;
        int objectHealth;
};

#endif // BOSS_H
