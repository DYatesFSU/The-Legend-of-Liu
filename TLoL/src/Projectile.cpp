#include "Projectile.h"
#include <iostream>

using namespace std;

Projectile::Projectile()
{
    //ctor
    isDead = false;
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
        setyVel(0.006);
        break;
        case 's':
        setyVel(-0.006);
        break;
        case 'e':
        setxVel(0.006);
        break;
        case 'w':
        setxVel(-0.006);
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


    objectTexture[0].bindTexture("images/player/play.png");

    objectTeam = inpProjTeam;

}

void Projectile::drawProj()
{
    setxPos(getxVel());
    setyPos(getyVel());


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
