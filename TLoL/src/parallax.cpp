#include "parallax.h"
#include <textureLoader.h>

//textureLoader *bTex = new textureLoader();
int levels[10][10];
textureLoader floorStyleA;
textureLoader floorStyleB;
textureLoader floorStyleC;
textureLoader floorStyleD;

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
