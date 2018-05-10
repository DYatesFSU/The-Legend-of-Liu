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

    //objectTexture = new textureLoader[11]();
    //objectTexture = new **textureLoader[2]();

    objectTexture = new vector < vector < textureLoader > > ();

    objectTimer = new timer();


    objectTimer->start();

    isDead = false;
    objectDirection = 0;
}

Enemy191T::~Enemy191T()
{
    //dtor
    //delete []objectTexture;
    delete objectTexture;
    delete objectTimer;
}

void Enemy191T::drawObject()
{
    //objectTexture[0].binder();


    cartesian2d objOrient[4];

    orientDirection(objectDirection, objOrient);

    glPushMatrix();

    glTranslated(Xpos, Ypos, Zpos);

    glScaled(1.00, 1.00, 1.00);

    //objectTexture[0].binder();
    objectTexture->back().at(spriteX).binder();

    if (genericTimerCounter % 30 == 0)
        manageSprite();

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
    waitTime = (rand() % 2000) + 2000;


    //srand(time(NULL));
    spriteCharacter = rand() % 2;

    spriteX = 0;
    bindObjectTextures(spriteCharacter);

    genericTimerCounter = 0;


}

void Enemy191T::bindObjectTextures(int inpCharacterType)
{
    string actionType;
    string suffix;
    string prefix0;
    string strIndex;

    string tempCurrentAction;

    int index;

    textureLoader tempTL0;
    vector < textureLoader > tempTL1;

    //prefix0 = "images/male/Walk (";
    //prefix1 = "images/female/Walk (";
    suffix = ").png";

    switch (inpCharacterType)
    {
        case 0:
            prefix0 = "images/male/Walk (";
            break;
        case 1:
            prefix0 = "images/female/Walk (";
            break;
    }

    objectTexture->push_back(tempTL1);

    for (int i = 0; i < 10; i++)
    {
        strIndex = to_string(i+1);
        tempCurrentAction = prefix0;
        tempCurrentAction += strIndex;
        tempCurrentAction += suffix;

        objectTexture->back().push_back(tempTL0);
        objectTexture->back().back().bindTexture(const_cast<char*>(tempCurrentAction.c_str()));
    }
}

void Enemy191T::manageSprite()
{
    spriteX++;
    if (spriteX >= objectTexture->back().size())
        spriteX = 0;
}

void Enemy191T::manageGenericTimer()
{
    genericTimerCounter++;
    if (genericTimerCounter >= 1000000)
        genericTimerCounter = 0;
}



void Enemy191T::updateEnemy(cartesian2d inpTargetLoc)
{

    if (objectTimer->getTicks() >= waitTime)
    {
        objectTimer->reset();
        destXPos = inpTargetLoc.x;
        destYPos = inpTargetLoc.y;
        waitTime = (rand() % 2000 + 2000);
    }

    if (destXPos - Xpos > 0)
    {
        setxVel(runspeed);
        objectDirection = 0;
    }
    else if (destXPos - Xpos < - 0)
    {
        setxVel(-runspeed);
        objectDirection = 2;
    }
    if (destYPos - Ypos > 0)
        setyVel(runspeed);
    else if (destYPos - Ypos < -0)
        setyVel(-runspeed);

    Xpos += getxVel();
    Ypos += getyVel();

    manageGenericTimer();

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
