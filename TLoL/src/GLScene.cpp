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
#include <Levels.h>
#include <key.h>
#include <cstdlib>
#include <ctime>
#include <Projectile.h>
#include <timer.h>
#include <UI.h>
#include <Boss.h>



//Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
player *ply = new player();
LoadShader *shader = new LoadShader();
ParticleEngine *particle = new ParticleEngine();
//skyBox *sky = new skyBox;
Levels *lvl = new Levels();
key *floorKey = new key();
UI *ui = new UI();

int xLvl = 0;
int yLvl = 2;



Enemy191T *e191Array[10];
int currEnemyCount = 0;

Boss *boss[2];

Projectile *projArray[100];
int currProjCount = 0;
timer *projTimer = new timer();


GLScene::GLScene()
{
    //ctor
    screenHeight= GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    srand(time(0));
    //e191Array = new Enemy191T[10];
//    e191Array = NULL;
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{
    projTimer->start();
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
    lvl->LevelInit();
    floorKey->keyInit();
    ui->uiInit();

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

    if (ply->checkDoor != '0')
    {
        if (ply->checkDoor == 'w' && lvl->getwDoor(xLvl, yLvl))
        {
            transition('w');
        }
        else if (ply->checkDoor == 'e' && lvl->geteDoor(xLvl, yLvl))
        {
            transition('e');
        }
        else if (ply->checkDoor == 's' && lvl->getsDoor(xLvl, yLvl))
        {
            transition('s');
        }
        else if (ply->checkDoor == 'n' && lvl->getnDoor(xLvl, yLvl))
        {
            transition('n');
        }
         else   ply->checkDoor = '0';
    }

    checkProj();
    manageProj();
    manageEnemies();
    manageKeys();

    ui->drawUI();

	glPopMatrix();

}

void GLScene::manageEnemies()
{
    if (lvl->roomHasBoss(xLvl, yLvl))
        manageBoss();
    else
    {

        for (int i = 0; i < currEnemyCount; i++)
        {
            e191Array[i]->updateEnemy(ply);
            e191Array[i]->drawObject();
        }
    }
}

void GLScene::checkProj()
{
     if (projTimer->getTicks() >= 300 && ply->getFiring())
    {
        projTimer->reset();
        projArray[currProjCount] = new Projectile();
        projArray[currProjCount]->projInit(ply->getxPos(), ply->getyPos(), ply->getFiringDir());
        currProjCount++;
    }
}

void GLScene::manageBoss()
{
    if (currEnemyCount)
    {
        for (int i = 0; i < currEnemyCount; i++)
        {
            boss[i]->drawObject();
            if (boss[i]->getShooting())
            {
                projArray[currProjCount] = new Projectile();
                projArray[currProjCount]->projInit(boss[i]->getxPos(),
                                                   boss[i]->getyPos(),
                                                   boss[i]->getFiringDir());
                currProjCount++;
                boss[i]->setShooting(false);
            }
        }
    }
    else
    {
        if (ui->getKeys() >= 3)
        {
            if (ply->getxPos() < .5 && ply->getxPos() > -.5 && ply->getyPos() < .5 && ply->getyPos() > -.5)
            {
                exit(0);
            }
        }
    }
}

void GLScene::manageKeys()
{
     if (lvl->roomHasKey(xLvl, yLvl))
    {
        floorKey->drawKey();
        if (ply->getxPos() < .5 && ply->getxPos() > -.5 && ply->getyPos() < .5 && ply->getyPos() > -.5)
        {
            lvl->gotKey(xLvl, yLvl);
            ui->addKey();
        }
    }
}

void GLScene::manageProj()
{
    for (int i = 0; i < currProjCount; i++)
    {
        if (projArray[i]->lifeTime->getTicks() > 1000)
        {
            delete projArray[i];
            for (int j = i + 1; j < currProjCount; j++)
                projArray[j - 1] = projArray[j];
            currProjCount--;
        }
    projArray[i]->drawProj();
    }
}

void GLScene::transition(char dir)
{
    switch (dir){
case 'w':
    cout << "Going West\n";
                ply->setxPos(6.8);
                plx->xLevel--;
                xLvl--;
                break;
case 'e':
    cout << "Going East\n";
                ply->setxPos(-6.8);
                plx->xLevel++;
                xLvl++;
                break;
case 'n':
    cout << "Going North\n";
                ply->setyPos(-2.7);
                plx->yLevel++;
                yLvl++;
                break;
case 's':
    cout << "Going South\n";
                ply->setyPos(2.7);
                plx->yLevel--;
                yLvl--;
                break;
    }
    ply->checkDoor = '0';
    clearEnemies();
    generateEnemies();
}

void GLScene::generateEnemies()
{
    if (lvl->roomHasBoss(xLvl, yLvl))
    {
        boss[0] = new Boss();
        currEnemyCount++;
        boss[0]->bossInit(-3, 'e');

        boss[1] = new Boss();
        currEnemyCount++;
        boss[1]->bossInit(3, 'w');
    }
    else
    {
        for (int i = 0; i < lvl->getMaxE(xLvl, yLvl); i++)
        {
            e191Array[i] = new Enemy191T;
            //e191Array = new Enemy191T[];
            currEnemyCount++;
            e191Array[i]->objectInit();
            //e191Array[i].objectInit();
        }
    }
}

void GLScene::clearEnemies()
{
    for (int i = 0; i < currEnemyCount; i++)
    {
        delete e191Array[i];
    }
    for (int i = 0; i < currProjCount; i++)
    {
        delete projArray[i];
    }
    currProjCount = 0;
    currEnemyCount = 0;
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
