#ifndef PARALLAX_H
#define PARALLAX_H

#include <iostream>
#include <string.h>
#include <gl/gl.h>
#include <windows.h>
using namespace std;

class parallax
{
    public:
        parallax();
        virtual ~parallax();
        void drawSquare(float,float);
        void parallaxInit(char *);
        void scroll(bool,string,float);
        void drawWalls();

        float Xmax,Ymax,Xmin,Ymin;
        int xLevel = 0, yLevel = 0, floorStyle;

        void drawSWall();
        void drawNWall();
        void drawEWall();
        void drawWWall();
        void drawDoor(char, int);
    protected:

    private:
};

#endif // PARALLAX_H
