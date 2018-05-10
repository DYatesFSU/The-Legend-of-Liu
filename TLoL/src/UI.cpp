#include "UI.h"
#include "textureLoader.h"

using namespace std;

UI::UI()
{
    vertices[0].x = 0.0;vertices[0].y = 0.0;vertices[0].z = -1.0;
    vertices[1].x = 1.0;vertices[1].y = 0.0;vertices[1].z = -1.0;
    vertices[2].x = 1.0;vertices[2].y = 1.0;vertices[2].z = -1.0;
    vertices[3].x = 0.0;vertices[3].y = 1.0;vertices[3].z = -1.0;

    playerPic = new textureLoader[1]();
    keysPic = new textureLoader[1]();
    heartPic = new textureLoader[1]();

}

UI::~UI()
{
    //dtor
}


void UI::uiInit()
{
    setHealth(5);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    playerPic[0].bindTexture("images/liu.png");
    keysPic[0].bindTexture("images/test.png");
    heartPic[0].bindTexture("images/heart.png");

}

void UI::drawUI()
{


    drawPlayerFrame();
    drawHeartFrame();
    drawKeysFrame();


}

void UI::drawKeysFrame()
{
    for (int i = 0; i < playerKeys; i++)
    {
    glPushMatrix();

    glTranslated(-3 + (.3 * i), 1.5, -4.9);

    glScaled(.33, .33, .33);

    keysPic[0].binder();

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
}

void UI::drawHeartFrame()
{
    for (int i = 0; i < health; i++)
    {
    glPushMatrix();

    glTranslated(-3 + (.3 * i), 1.8, -4.9);

    glScaled(.33, .33, .33);

    heartPic[0].binder();

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

}


void UI::drawPlayerFrame()
{
    glPushMatrix();

    glTranslated(-3.9, 1.7, -4.9);

    glScaled(.50, .50, .50);

    playerPic[0].binder();

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


int UI::getHealth()
{
    return health;
}

void UI::setHealth(int hp)
{
    health += hp;
}

void UI::addKey()
{
    playerKeys++;
}

int UI::getKeys()
{
    return playerKeys;
}

void UI::resetKeys()
{
    playerKeys = 0;
}
