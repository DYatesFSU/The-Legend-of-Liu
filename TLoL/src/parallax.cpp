#include "parallax.h"
#include <textureLoader.h>

//textureLoader *bTex = new textureLoader();
int levels[10][10];
textureLoader floorStyleA;
textureLoader floorStyleB;
textureLoader floorStyleC;
textureLoader floorStyleD;
textureLoader closedDoor;
textureLoader openDoor;

parallax::parallax()
{
    //ctor
    Xmax= 1.0f;
    Ymax= 0.0f;
    Xmin= 0.0f;
    Ymin= 1.0f;
}

parallax::~parallax()
{
    //dtor
}

void parallax::drawSquare(float width, float height)
{
    glColor3f(1.0,1.0,1.0);
    switch (levels[xLevel][yLevel])
    {
    case 0:
        floorStyleA.binder();
        break;
    case 1:
        floorStyleB.binder();
        break;
    case 2:
        floorStyleC.binder();
        break;
    case 3:
        floorStyleD.binder();
        break;
    }
    glBegin(GL_POLYGON);
    glTexCoord2f(Xmin,Ymin);
    glVertex3f(-width/height,-1,-8.0f);

    glTexCoord2f(Xmax,Ymin);
    glVertex3f(width/height,-1,-8.0f);

    glTexCoord2f(Xmax,Ymax);
    glVertex3f(width/height,1,-8.0f);

    glTexCoord2f(Xmin,Ymax);
    glVertex3f(-width/height,1,-8.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2f(Xmin,Ymin);
    glVertex3f(-.5,-1,0.0f);

    glTexCoord2f(Xmax,Ymin);
    glVertex3f(-.5,1,0.0f);

    glTexCoord2f(Xmax,Ymax);
    glVertex3f(-1.5,1,-8.0f);

    glTexCoord2f(Xmin,Ymax);
    glVertex3f(-1.5,-1,-8.0f);
    glEnd();

    drawWalls();
}

void parallax::drawWalls()
{
    drawSWall();
    drawNWall();
    drawEWall();
    drawWWall();
}

void parallax::drawWWall()
{
    glBegin(GL_POLYGON);
    glTexCoord2f(Xmin,Ymin);
    glVertex3f(-.5,-1,0.0f);

    glTexCoord2f(Xmax,Ymin);
    glVertex3f(-.5,1,0.0f);

    glTexCoord2f(Xmax,Ymax);
    glVertex3f(-1.5,1,-8.0f);

    glTexCoord2f(Xmin,Ymax);
    glVertex3f(-1.5,-1,-8.0f);
    glEnd();
}

void parallax::drawNWall()
{
    glBegin(GL_POLYGON);
    glTexCoord2f(Xmin,Ymin);
    glVertex3f(-2,1,0.0f);

    glTexCoord2f(Xmax,Ymin);
    glVertex3f(2,1,0.0f);

    glTexCoord2f(Xmax,Ymax);
    glVertex3f(2,.7,-8.0f);

    glTexCoord2f(Xmin,Ymax);
    glVertex3f(-2,.7,-8.0f);
    glEnd();
}

void parallax::drawSWall()
{
    glBegin(GL_POLYGON);
    glTexCoord2f(Xmin,Ymin);
    glVertex3f(-2,-.8,0.0f);

    glTexCoord2f(Xmax,Ymin);
    glVertex3f(2,-.8,0.0f);

    glTexCoord2f(Xmax,Ymax);
    glVertex3f(2,-.8,-8.0f);

    glTexCoord2f(Xmin,Ymax);
    glVertex3f(-2,-.8,-8.0f);
    glEnd();
}

void parallax::drawEWall()
{
    glBegin(GL_POLYGON);
    glTexCoord2f(Xmin,Ymin);
    glVertex3f(.5,-1,0.0f);

    glTexCoord2f(Xmax,Ymin);
    glVertex3f(.5,1,0.0f);

    glTexCoord2f(Xmax,Ymax);
    glVertex3f(1.5,1,-8.0f);

    glTexCoord2f(Xmin,Ymax);
    glVertex3f(1.5,-1,-8.0f);
    glEnd();
}

void parallax::drawDoor(char c, int x)
{
    if (x)
        closedDoor.binder();
    else
        openDoor.binder();

    glBegin(GL_POLYGON);

    switch (c)
    {
    case 'e':
        glTexCoord2f(Xmin,Ymin);
        glVertex3f(4.7,.25,-7.5f);

        glTexCoord2f(Xmax,Ymin);
        glVertex3f(4.7,-.25,-7.5f);

        glTexCoord2f(Xmax,Ymax);
        glVertex3f(3.9,-.25,-5.5f);

        glTexCoord2f(Xmin,Ymax);
        glVertex3f(3.9,.25,-5.5f);
        break;

    case 'w':
        glTexCoord2f(Xmin,Ymin);
        glVertex3f(-4.7,.25,-7.5f);

        glTexCoord2f(Xmax,Ymin);
        glVertex3f(-4.7,-.25,-7.5f);

        glTexCoord2f(Xmax,Ymax);
        glVertex3f(-3.9,-.25,-5.5f);

        glTexCoord2f(Xmin,Ymax);
        glVertex3f(-3.9,.25,-5.5f);
        break;
    case 'n':
        glTexCoord2f(Xmin,Ymin);
        glVertex3f(-.25,2.2,-7.5f);

        glTexCoord2f(Xmax,Ymin);
        glVertex3f(.25,2.2,-7.5f);

        glTexCoord2f(Xmax,Ymax);
        glVertex3f(.25,2.1,-5.5f);

        glTexCoord2f(Xmin,Ymax);
        glVertex3f(-.25,2.1,-5.5f);
        break;

    case 's':
        glTexCoord2f(Xmin,Ymin);
        glVertex3f(-.25,-2.5,-7.5f);

        glTexCoord2f(Xmax,Ymin);
        glVertex3f(.25,-2.5,-7.5f);

        glTexCoord2f(Xmax,Ymax);
        glVertex3f(.25,-2.3,-5.5f);

        glTexCoord2f(Xmin,Ymax);
        glVertex3f(-.25,-2.3,-5.5f);
        break;
    }



        glEnd();
}


void parallax::parallaxInit(char *FileName)
{
    //bTex->binder();
   // bTex->bindTexture(FileName);

   for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int x = rand() % 4;
            switch (x)
            {
            case 0:
                levels[i][j] = 0;
                break;

            case 1:

                levels[i][j] = 1;
                break;

            case 2:
                levels[i][j] = 2;
                break;
            case 3:
                levels[i][j] = 3;
                break;
            }


        }
    }
    floorStyleA.bindTexture("images/wood.jpg");
    floorStyleB.bindTexture("images/tiles.png");
    floorStyleC.bindTexture("images/stone.jpg");
    floorStyleD.bindTexture("images/dirt.jpg");
    closedDoor.bindTexture("images/closedDoor.png");
    openDoor.bindTexture("images/openDoor.png");
}

void parallax::scroll(bool Auto, string dir, float speed)
{
    if(Auto){

        if(dir == "up")
        {
           Ymin -=speed;
           Ymax -=speed;
        }
        if(dir == "down")
        {
           Ymin +=speed;
           Ymax +=speed;
        }
        if(dir == "left")
        {
           Xmin -=speed;
           Xmax -=speed;
        }
        if(dir == "right")
        {
           Xmin +=speed;
           Xmax +=speed;
        }
    }
}
