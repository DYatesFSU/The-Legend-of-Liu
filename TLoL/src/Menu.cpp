#include "Menu.h"


textureLoader *Tex = new textureLoader();
Menu::Menu()
{
    //ctor
    state = 0;
}

Menu::~Menu()
{
    //dtor
}

void Menu::DrawMenu(float width,float height)
{


    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);

        glTexCoord2f(0,1);
        glVertex3f(-width/height,-1,-8.0f);

        glTexCoord2f(1,1);
        glVertex3f(width/height,-1,-8.0f);

        glTexCoord2f(1,0);
        glVertex3f(width/height,1,-8.0f);

        glTexCoord2f(0,0);
        glVertex3f(-width/height,1,-8.0f);


    glEnd();

}

void Menu::MenuInit(char * FileName)
{
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        Tex->bindTexture(FileName);
}
