#include "Enemy191T.h"
#include <textureLoader.h>
#include <timer.h>
#include <iostream>

using namespace std;

Enemy191T::Enemy191T()
{
    //ctor

    vertices[0].x = 0.0;vertices[0].y = 0.0;vertices[0].z = -1.0;
    vertices[1].x = 1.0;vertices[1].y = 0.0;vertices[1].z = -1.0;
    vertices[2].x = 1.0;vertices[2].y = 1.0;vertices[2].z = -1.0;
    vertices[3].x = 0.0;vertices[3].y = 1.0;vertices[3].z = -1.0;

    runspeed  =0;
    jumpspeed =0;
    actionTrigger =0;

    Xpos = 0;
    Ypos = 0;
    Zpos = -5.0;

    objectTexture = new textureLoader[11]();
    objectTimer = new timer();

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

    objectTexture[0].bindTexture("images/player/play.png");
    objectTexture[1].bindTexture("images/player/player0.png");
    objectTexture[2].bindTexture("images/player/player1.png");
    objectTexture[3].bindTexture("images/player/player2.png");
    objectTexture[4].bindTexture("images/player/player3.png");
    objectTexture[5].bindTexture("images/player/player4.png");
    objectTexture[6].bindTexture("images/player/player5.png");
    objectTexture[7].bindTexture("images/player/player6.png");
    objectTexture[8].bindTexture("images/player/player7.png");
    objectTexture[9].bindTexture("images/player/player8.png");
    objectTexture[10].bindTexture("images/player/player9.png");
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
