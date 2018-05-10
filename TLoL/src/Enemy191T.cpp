#include "Enemy191T.h"
#include <textureLoader.h>
#include <timer.h>
#include <iostream>
#include <player.h>
#include <cstdlib>
#include <ctime>

using namespace std;

Enemy191T::Enemy191T()
{
    //ctor

    vertices[0].x = 0.0;vertices[0].y = 0.0;vertices[0].z = -1.0;
    vertices[1].x = 1.0;vertices[1].y = 0.0;vertices[1].z = -1.0;
    vertices[2].x = 1.0;vertices[2].y = 1.0;vertices[2].z = -1.0;
    vertices[3].x = 0.0;vertices[3].y = 1.0;vertices[3].z = -1.0;

    runspeed  = 0.001;

    Xpos = (rand() % 6) - 3;
    Ypos = (rand() % 3) - 1.5;
    Zpos = -5.0;


    destXPos = (rand() % 10) - 5;
    destYPos = (rand() % 5) - 3;



    xVel = 0;
    yVel = 0;

    objectTexture = new textureLoader[11]();
    objectTimer = new timer();


    objectTimer->start();

    isDead = false;
}

Enemy191T::~Enemy191T()
{
    //dtor
    delete []objectTexture;
    delete objectTimer;
}

void Enemy191T::drawObject()
{
    //objectTexture[0].binder();


    cartesian2d objOrient[4];

    orientDirection(0, objOrient);

    glPushMatrix();

    glTranslated(Xpos, Ypos, Zpos);

    glScaled(1.00, 1.00, 1.00);

    objectTexture[0].binder();

    glBegin(GL_QUADS);


    glTexCoord2f(objOrient[0].x, objOrient[0].y);
    glVertex3f(vertices[0].x,vertices[0].y,vertices[0].z);

    glTexCoord2f(objOrient[1].x, objOrient[1].y);
    glVertex3f(vertices[1].x,vertices[1].y,vertices[1].z);

    glTexCoord2f(objOrient[2].x, objOrient[2].y);
    glVertex3f(vertices[2].x,vertices[2].y,vertices[2].z);

    glTexCoord2f(objOrient[3].x, objOrient[3].y);
    glVertex3f(vertices[3].x,vertices[3].y,vertices[3].z);


    glEnd();

    glPopMatrix();

}

void Enemy191T::objectInit()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    objectTimer->start();
    waitTime = (rand() % 100) + 200;

    objectTexture[0].bindTexture("images/boy1.png");
    objectTexture[1].bindTexture("images/girl1.png");
    objectTexture[2].bindTexture("images/boy1.png");
    objectTexture[3].bindTexture("images/girl1.png");
    objectTexture[4].bindTexture("images/girl1.png");
    objectTexture[5].bindTexture("images/boy1.png");
    objectTexture[6].bindTexture("images/girl1.png");
    objectTexture[7].bindTexture("images/boy1.png");
    objectTexture[8].bindTexture("images/girl1.png");
    objectTexture[9].bindTexture("images/boy1.png");
    objectTexture[10].bindTexture("images/girl1.png");
}

void Enemy191T::updateEnemy(cartesian2d inpTargetLoc)
{

    if (objectTimer->getTicks() >= waitTime)
    {
        objectTimer->reset();
        destXPos = inpTargetLoc.x;
        destYPos = inpTargetLoc.y;
        waitTime = (rand() % 150 + 400);
    }

    if (destXPos - Xpos > 0)
        setxVel(runspeed);
    else if (destXPos - Xpos < - 0)
        setxVel(-runspeed);
    if (destYPos - Ypos > 0)
        setyVel(runspeed);
    else if (destYPos - Ypos < -0)
        setyVel(-runspeed);

    Xpos += getxVel();
    Ypos += getyVel();

}

void Enemy191T::orientDirection(int direction, cartesian2d retCoord[])
{
    switch (direction)
    {
        case 0:
            retCoord[0].x = 0.0;
            retCoord[0].y = 1.0;

            retCoord[1].x = 1.0;
            retCoord[1].y = 1.0;

            retCoord[2].x = 1.0;
            retCoord[2].y = 0.0;

            retCoord[3].x = 0.0;
            retCoord[3].y = 0.0;
            break;
        case 1:
            retCoord[0].x = 0.0;
            retCoord[0].y = 0.0;

            retCoord[1].x = 1.0;
            retCoord[1].y = 0.0;

            retCoord[2].x = 1.0;
            retCoord[2].y = 1.0;

            retCoord[3].x = 0.0;
            retCoord[3].y = 1.0;
            break;
        case 2:
            retCoord[0].x = 1.0;
            retCoord[0].y = 1.0;

            retCoord[1].x = 0.0;
            retCoord[1].y = 1.0;

            retCoord[2].x = 0.0;
            retCoord[2].y = 0.0;

            retCoord[3].x = 1.0;
            retCoord[3].y = 0.0;
            break;
        case 3:
            retCoord[0].x = 1.0;
            retCoord[0].y = 0.0;

            retCoord[1].x = 0.0;
            retCoord[1].y = 0.0;

            retCoord[2].x = 0.0;
            retCoord[2].y = 1.0;

            retCoord[3].x = 1.0;
            retCoord[3].y = 1.0;
            break;
        default:
            cout << "error" << endl;
            break;
    }
}


double Enemy191T::getxVel()
{
    return xVel;
}

void Enemy191T::setxVel(double x)
{
    xVel = x;
}

double Enemy191T::getyVel()
{
    return yVel;
}

void Enemy191T::setyVel(double y)
{
    yVel = y;
}


cartesian2d Enemy191T::getPosition()
{
    cartesian2d retCoord = {Xpos, Ypos};
    return retCoord;
}

cartesian2d Enemy191T::getDestPosition()
{
    cartesian2d retCoord = {destXPos, destYPos};
    return retCoord;
}

void Enemy191T::setPosition(cartesian2d inpCoord)
{
    Xpos = inpCoord.x;
    Ypos = inpCoord.y;
}

void Enemy191T::setDestPosition(cartesian2d inpCoord)
{
    destXPos = inpCoord.x;
    destYPos = inpCoord.y;
}

cart2dDim Enemy191T::getObjectDimensions()
{
    return objectDimensions;
}

void Enemy191T::getCurrGridPos(vector<grid2d>& retPos)
{
    retPos = classCurrentGridCoords;
}

void Enemy191T::setCurrGridPos(vector<grid2d>inpPos)
{
    classCurrentGridCoords = inpPos;
}

void Enemy191T::getDestGridPos(vector<grid2d>& retPos)
{
    retPos = classTestGridCoords;
}

void Enemy191T::setDestGridPos(vector<grid2d>inpPos)
{
    classTestGridCoords = inpPos;
}


void Enemy191T::setIsDead(bool inpBool)
{
    isDead = inpBool;
}

bool Enemy191T::getIsDead()
{
    return isDead;
}
