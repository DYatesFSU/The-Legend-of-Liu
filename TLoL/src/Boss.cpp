#include "Boss.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

Boss::Boss()
{
    xPos = 0;
    yPos = 0;
    waiting = true;
    setyVel(.002);
    shooting = false;
    objectTimer = new timer();
    shootTimer = new timer();
}

Boss::~Boss()
{
    //dtor
}



void Boss::bossInit(double x, char s)
{

    setxPos(x);
    setFiringDir(s);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    objectTimer->start();
    shootTimer->start();

    waitTime = (rand() % 2000) + 1000;
    shootTime = (rand() % 2000) + 3000;


    vertices[0].x = 0.0;vertices[0].y = 0.0;vertices[0].z = -1.0;
    vertices[1].x = 1.0;vertices[1].y = 0.0;vertices[1].z = -1.0;
    vertices[2].x = 1.0;vertices[2].y = 1.0;vertices[2].z = -1.0;
    vertices[3].x = 0.0;vertices[3].y = 1.0;vertices[3].z = -1.0;

    objectTexture = new textureLoader[1]();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    objectTexture[0].bindTexture("images/player/play.png");
}

void Boss::drawObject()
{
    if (waiting)
    {
       if (objectTimer->getTicks() > waitTime)
       {
           objectTimer->reset();
           waiting = false;
           waitTime = (rand() % 2000) + 1000;
       }
    }
    else
    {
        if (getyPos() + getyVel() < -1.9 || getyPos() + getyVel() > .9)
        {
            setyVel(-1);
        }
        setyPos(getyVel());

        if (objectTimer->getTicks() > waitTime)
        {
            objectTimer->reset();
            waiting = true;
            waitTime = (rand() % 2000) + 1000;
        }
    }
    if (shootTimer->getTicks() > shootTime)
    {
        shootTimer->reset();
        setShooting(true);
        shootTime = (rand() & 1000) + 500;
    }
    glPushMatrix();

    glTranslated(getxPos(), getyPos(), -5);

    glScaled(.33, .33, .33);

    objectTexture[0].binder();

    glBegin(GL_QUADS);


    glTexCoord3f(0, 1, 0);
    glVertex3f(vertices[0].x,vertices[0].y,vertices[0].z);

    glTexCoord3f(1, 1, 0);
    glVertex3f(vertices[1].x,vertices[1].y,vertices[1].z);

    glTexCoord3f(1, 0, 0);
    glVertex3f(vertices[2].x,vertices[2].y,vertices[2].z);

    glTexCoord3f(0, 0, 0);
    glVertex3f(vertices[3].x,vertices[3].y,vertices[3].z);


    glEnd();

    glPopMatrix();
}

double Boss::getxVel()
{
    return xVel;
}

void Boss::setxVel(double x)
{
    if (x < 0)
        xVel *= x;
    else
        xVel = x;
}

double Boss::getxPos()
{
    return xPos;
}

void Boss::setxPos(double x)
{
    xPos += x;
}

double Boss::getyPos()
{
    return yPos;
}

void Boss::setyPos(double x)
{
    yPos += x;
}

double Boss::getyVel()
{
    return yVel;
}

void Boss::setyVel(double y)
{
    if (y < 0)
        yVel *= y;
    else
        yVel = y;
}

void Boss::setShooting(bool x)
{
    shooting = x;
}

bool Boss::getShooting()
{
    return shooting;
}

char Boss::getFiringDir()
{
    return firingDir;
}

void Boss::setFiringDir(char x)
{
    firingDir = x;
}

