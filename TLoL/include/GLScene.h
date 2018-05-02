#ifndef GLSCENE_H
#define GLSCENE_H

#include <windows.h> // Header File For Windows
#include <string.h>
#define GLEW_STATIC
#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <iostream>

using namespace std;

class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        int windMsg(HWND,UINT, WPARAM,LPARAM);


        WPARAM wParam;
        float screenHeight;
        float screenWidth;
    protected:

    private:
};

#endif // GLSCENE_H
