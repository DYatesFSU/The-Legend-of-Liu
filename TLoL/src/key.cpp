#include "key.h"

key::key()
{
    //ctor
}

key::~key()
{
    //dtor
}


void key::keyInit()
{
    vertices[0].x = 0.0;vertices[0].y = 0.0;vertices[0].z = -1.0;
    vertices[1].x = 1.0;vertices[1].y = 0.0;vertices[1].z = -1.0;
    vertices[2].x = 1.0;vertices[2].y = 1.0;vertices[2].z = -1.0;
    vertices[3].x = 0.0;vertices[3].y = 1.0;vertices[3].z = -1.0;

    objectTexture = new textureLoader[1]();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    objectTexture[0].bindTexture("images/test.png");
}

void key::drawKey()
{


    glPushMatrix();

    glTranslated(0, 0, -5);

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

