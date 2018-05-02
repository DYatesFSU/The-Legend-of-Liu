#include "GLScene.h"
#include <GLLight.h>
#include <Model.h>
#include <Inputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <LoadShader.h>
#include <Enemy191T.h>
#include <ParticleEngine.h>

//Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
player *ply = new player();
LoadShader *shader = new LoadShader();
ParticleEngine *particle = new ParticleEngine();
//skyBox *sky = new skyBox;

Enemy191T *enemy191t = new Enemy191T();

GLScene::GLScene()
{
    //ctor
    screenHeight= GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glewInit();

   // glEnable(GL_COLOR_MATERIAL);
    GLLight SetLight(GL_LIGHT0);
    GLLight Light(GL_LIGHT0);

    //modelTeapot->modelInit("images/player/player0.png",true);
    plx->parallaxInit("images/bak.jpg");
    ply->playerInit();
    //sky->loadTextures();
    enemy191t->objectInit();

    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix


    glPushMatrix();
      glScaled(3.33,3.33,1.0);
         plx->drawSquare(screenWidth,screenHeight);
     glPopMatrix();
       //plx->scroll(true,"right",0.005);
/*
    glPushMatrix();
        glDisable(GL_LIGHTING);
        glScaled(200,200,200);
        sky->drawBox();
        glEnable(GL_LIGHTING);
    glPopMatrix();
*/
    glPushMatrix();
        //glTranslated(0,0,modelTeapot->Zoom);
        if (ply->checkMoving())
            ply->actions(1);
        else
            ply->actions(0);
        if (ply->getxPos() > 4.5)
        {
            //cout << "xPos: " << ply->getxPos() << ", yPos: " << ply->getyPos() << endl;
            ply->setxPos(-9.5);
            plx->xLevel++;
            //cout << "xPos: " << ply->getxPos() << ", yPos: " << ply->getyPos() << endl;
        }
        if (ply->getxPos() < -5.5)
        {
            ply->setxPos(9.5);
            plx->xLevel--;
        }
        if (ply->getyPos() > 2.5)
        {
            ply->setyPos(-5.5);
            plx->yLevel++;
        }
        if (ply->getyPos() < -3.5)
        {
            ply->setyPos(5.5);
            plx->yLevel--;
        }
    glPopMatrix();

    enemy191t->drawObject();


    	glPushMatrix();
        glUseProgram(shader->program);
        glTranslated(0.70,-2.5,-2.0);
        particle->generateParticle();
        particle->drawParticle();
        particle->lifeTime();
        glUseProgram(0);
	glPopMatrix();


}

GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
   GLfloat aspectRatio = (GLfloat)width/(GLfloat)height;
   glViewport(0,0,width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0,aspectRatio,0.1,1000);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)									// Check For Windows Messages
	{

	    case WM_KEYDOWN:
	        KbMs->wParam = wParam;
	        //KbMs->keyPressed(modelTeapot);
	        //KbMs->keyEnv(plx, 0.005);
	        KbMs->keyPressed(ply);
	        //KbMs->keyPressed(sky);

	    break;

	    case WM_KEYUP:								// Has A Key Been Released?
		{
			KbMs->wParam = wParam;
			KbMs->keyUp(ply);
		break;								// Jump Back
		}

		case WM_LBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            //KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

   		case WM_RBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            //KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

          case WM_MBUTTONDOWN:
        {
            KbMs->wParam = wParam;
            //KbMs->mouseEventDown(modelTeapot,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
//            KbMs->mouseEventUp();
        break;								// Jump Back
        }

        case WM_MOUSEMOVE:
        {
             //KbMs->mouseMove(modelTeapot, LOWORD(lParam),HIWORD(lParam));
             //KbMs->mouseMove(sky,LOWORD(lParam),HIWORD(lParam));
        break;								// Jump Back
        }

        case WM_MOUSEWHEEL:
        {
            //KbMs->mouseWheel(modelTeapot,(double)GET_WHEEL_DELTA_WPARAM(wParam));
        break;								// Jump Back
        }
}
}
