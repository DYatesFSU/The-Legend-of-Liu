#include "Projectile.h"
#include <iostream>

using namespace std;

const double VELOCITYSCALE = 0.006;
const double INITIALSIZESCALE = 0.33;

Projectile::Projectile()
{
    //ctor
    isDead = false;
    objectRotation = 0;
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::projInit(float x, float y, char s, int inpProjTeam)
{

    xPos = x;

    yPos = y;
    setxVel(0);
    setyVel(0);

    switch (s)
    {
        case 'n':
        setyVel(VELOCITYSCALE);
        break;
        case 's':
        setyVel(-VELOCITYSCALE);
        break;
        case 'e':
        setxVel(VELOCITYSCALE);
        break;
        case 'w':
        setxVel(-VELOCITYSCALE);
        break;
    }
    lifeTime->start();

    vertices[0].x = 0.0;vertices[0].y = 0.0;vertices[0].z = -1.0;
    vertices[1].x = 1.0;vertices[1].y = 0.0;vertices[1].z = -1.0;
    vertices[2].x = 1.0;vertices[2].y = 1.0;vertices[2].z = -1.0;
    vertices[3].x = 0.0;vertices[3].y = 1.0;vertices[3].z = -1.0;

    objectTexture = new textureLoader[1]();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    objectTexture[0].bindTexture("images/projectile.png");

    objectTeam = inpProjTeam;
    objectRotation = 0;
    isDead = false;

}

void Projectile::doObjectLogic()
{
    setxPos(getxVel());
    setyPos(getyVel());
    rotateObject();
}

void Projectile::drawObject()
{
    glPushMatrix();

    //glRotated(objectRotation, 0, 0, 1);

    glTranslated(getxPos(), getyPos(), -5);
    //glTranslated(objectDimensions.width/2, objectDimensions.height/2, -5);

    glTranslated(INITIALSIZESCALE/2, INITIALSIZESCALE/2, 0);

    glRotated(objectRotation, 0, 0, 1);
    //glRotated(objectRotation, 0, 1, 0);
    //glRotated(objectRotation, 1, 0, 0);

    //glTranslated(INITIALSIZESCALE/2 * VELOCITYSCALE, INITIALSIZESCALE/2 * VELOCITYSCALE, -5);
    //glTranslated(VELOCITYSCALE, VELOCITYSCALE, 0);
    //double xthing = -0.15;
    //double ything = -0.15;
    //glTranslated(xthing, ything, 0);
    glTranslated(-INITIALSIZESCALE/2, -INITIALSIZESCALE/2, 0);

    glScaled(INITIALSIZESCALE, INITIALSIZESCALE, INITIALSIZESCALE);

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

float Projectile::getxPos()
{
    return xPos;
}

float Projectile::getyPos()
{
    return yPos;
}

float Projectile::getxVel()
{
    return xVel;
}

float Projectile::getyVel()
{
    return yVel;
}

void Projectile::setxPos(float x)
{
    xPos += x;
}

void Projectile::setyPos(float y)
{
    yPos += y;
}

void Projectile::setxVel(float x)
{
    xVel = x;
}

void Projectile::setyVel(float y)
{
    yVel = y;
}

cartesian2d Projectile::getPosition()
{
    cartesian2d retCoord = {getxPos(), getyPos()};
    return retCoord;
}

void Projectile::setPosition(cartesian2d inpCoord)
{
    setxPos(inpCoord.x);
    setyPos(inpCoord.y);
}

cart2dDim Projectile::getObjectDimensions()
{
    return objectDimensions;
}

void Projectile::getCurrGridPos(vector<grid2d>& retPos)
{
    retPos = classCurrentGridCoords;
}

void Projectile::setCurrGridPos(vector<grid2d>inpPos)
{
    classCurrentGridCoords = inpPos;
}
void Projectile::setIsDead(bool inpBool)
{
    isDead = inpBool;
}

bool Projectile::getIsDead()
{
    return isDead;
}

void Projectile::setObjectTeam(int inpTeam)
{
    objectTeam = inpTeam;
}

int Projectile::getObjectTeam()
{
    return objectTeam;
}

void Projectile::rotateObject()
{
    objectRotation -= 1.5;
    if (objectRotation > 360)
        objectRotation -= 360;
    if (objectRotation < -360)
        objectRotation += 360;
}
