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

#include <Wall.h>
#include <Map.h>
#include <AudioComponent.h>


#include <Menu.h>
#include <Fonts.h>

/*
const int ENEMYTYPE = 1;
const int WALLTYPE = 0;
const int PLAYERTYPE = 2;
const int PROJECTILETYPE = 3;
const int TYPEVARIETY = 4;
*/
const int PLAYERID = 0;

const int TEAMPLAYER = 0;
const int NOTTEAMPLAYER = 1;

const int MAXPLAYERHEALTH = 7;
const int MAXBOSSHEALTH = 10;
const int KILLSTREAKLIMIT = 15;


//Model *modelTeapot = new Model();
Inputs *KbMs = new Inputs();
parallax *plx = new parallax();
player *ply = new player();
LoadShader *shader = new LoadShader();
ParticleEngine *particle = new ParticleEngine();
//skyBox *sky = new skyBox;
Levels *lvl;
Levels *floor1 = new Levels();
Levels *floor2 = new Levels();
key *floorKey = new key();
UI *ui = new UI();
Menu * men = new Menu();
Fonts *F= new Fonts();
int xLvl = 0;
int yLvl = 2;


Enemy191T *e191Array[10];
int currEnemyCount = 0;

Boss *boss[2];
int currBossCount = 0;

Projectile *projArray[100];
int currProjCount = 0;
timer *projTimer = new timer();

Wall *wallArray[100];
int currWallCount = 0;


Map *gridMap;
//These are used to update the list when an object is destroyed
bool updateEnemyMapList = false;
bool updateProjectileMapList = false;

GLScene::GLScene()
{
    //ctor
    screenHeight= GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    srand(time(0));
    audio_ = new AudioComponent();

    // Register Background Music
    audio_->registerAudioSource("audio/bieber.ogg");
    audio_->registerAudioSource("audio/black.ogg");

    // Register SoundFX
    audio_->registerAudioSource("audio/fx_blast.ogg");
    audio_->registerAudioSource("audio/fx_damage_taken.ogg");
    audio_->registerAudioSource("audio/fx_found_key.ogg");
    audio_->registerAudioSource("audio/fx_you_lose.ogg");
    audio_->registerAudioSource("audio/fx_zombie_death.ogg");

    //e191Array = new Enemy191T[10];
//    e191Array = NULL;
     men->state =0;

}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{

    audio_->play("audio/black.ogg");

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
    floor1->LevelInit();
    floor2->Floor2Init();
    lvl = floor1;

    floorKey->keyInit();

    ui->uiInit();

    return true;
}

GLint GLScene::drawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

    if(men->state==0)                           //Landing page at start of game
    {
        men->MenuInit("images/land.jpg"); //landing page
        // cout<<"Landing Page"<<endl;

        glPushMatrix();
        glScaled(3.33,3.33,1.0);
        men->DrawMenu(screenWidth,screenHeight);
        glPopMatrix();

    }
    else if (men->state == 1)                   // Menu Page
    {
        men->MenuInit("images/mainmenu.jpg"); //landing page

         glPushMatrix();
        glScaled(3.33,3.33,1.0);
        men->DrawMenu(screenWidth,screenHeight);
        glPopMatrix();
        //  cout<<" Main Menu"<<endl;
        //cout<<" Press N for New Game"<<endl;
        //cout<<" Press O for Option"<<endl;
        //cout<< "Press H for How to Play"<<endl;
        //cout<< "Press ESC to quit"<<endl;
    }
    else if (men->state == 2)
    {
        mainGameLogic();
    }
    else if(men->state == 3)
    {
        cout<<"Options"<<endl;
    }
    else if(men->state == 4)
    {
        // cout<<"How to Play"<<endl;
        men->MenuInit("images/how.jpg");

        glPushMatrix();
        glScaled(3.33,3.33,1.0);
        men->DrawMenu(screenWidth,screenHeight);
        glPopMatrix();

    }
    else if (men->state== 5)
    {
        //cout<<"Pause Menu"<<endl;
        men->MenuInit("images/paused.jpg");

        glPushMatrix();
        glScaled(3.33,3.33,1.0);
        men->DrawMenu(screenWidth,screenHeight);
        glPopMatrix();
    }
    else if (men->state == 6)
    {
            men->MenuInit("images/win.jpg");

            glPushMatrix();
            glScaled(3.33,3.33,1.0);
            men->DrawMenu(screenWidth,screenHeight);
            glPopMatrix();
    }
    else if(men->state == 7)
    {
        men->MenuInit("images/loss.jpg");
        //audio_->play("audio/fx_you_lose.mp3");
            glPushMatrix();
            glScaled(3.33,3.33,1.0);
            men->DrawMenu(screenWidth,screenHeight);
            glPopMatrix();

    }

}

void GLScene::mainGameLogic()
{
    glPushMatrix();
    glScaled(3.33,3.33,1.0);
    plx->drawSquare(screenWidth,screenHeight);
    glPopMatrix();

    drawDoors();

    glPushMatrix();
    if (ply->checkMoving())
    ply->actions(1);
    else
    ply->actions(0);

    if (!currEnemyCount && !currBossCount)
    {
        if (ply->checkDoor == 'w' && lvl->getwDoor(xLvl, yLvl))
            transition('w');
        else if (ply->checkDoor == 'e' && lvl->geteDoor(xLvl, yLvl))
            transition('e');
        else if (ply->checkDoor == 's' && lvl->getsDoor(xLvl, yLvl))
            transition('s');
        else if (ply->checkDoor == 'n' && lvl->getnDoor(xLvl, yLvl))
            transition('n');
        else ply->checkDoor = '0';
    } else ply->checkDoor = '0';

    checkProj(TEAMPLAYER);

    manageProj();
    manageEnemies();
    manageKeys();

    ui->drawUI();

    glPopMatrix();

    collisionListPlayerToEnemy();
    collisionListProjectileToEnemy();
    //collisionListProjectileToProjectile();
    collisionListProjectileToPlayer();

    collisionListProjectileToBoss();
    collisionListPlayerToBoss();

    cleanEnemyList();
    cleanProjectileList();
    cleanPlayerList();
    cleanBossList();

    managePlayerKill();
    ui->setHealth(ply->getHealth());
}


void GLScene::drawDoors()
{
    if(lvl->geteDoor(xLvl,yLvl))
    {
        glPushMatrix();
        glScaled(1.0,1.0,1.0);
        if (currBossCount > currEnemyCount)
            plx->drawDoor('e', currBossCount);
        else
            plx->drawDoor('e', currEnemyCount);
        glPopMatrix();
    }
     if(lvl->getwDoor(xLvl,yLvl))
    {
        glPushMatrix();
        glScaled(1.0,1.0,1.0);
        if (currBossCount > currEnemyCount)
            plx->drawDoor('w', currBossCount);
        else
            plx->drawDoor('w', currEnemyCount);
        glPopMatrix();
    }
     if(lvl->getnDoor(xLvl,yLvl))
    {
        glPushMatrix();
        glScaled(1.0,1.0,1.0);
        if (currBossCount > currEnemyCount)
            plx->drawDoor('n', currBossCount);
        else
            plx->drawDoor('n', currEnemyCount);
        glPopMatrix();
    }
     if(lvl->getsDoor(xLvl,yLvl))
    {
        glPushMatrix();
        glScaled(1.0,1.0,1.0);
        if (currBossCount > currEnemyCount)
            plx->drawDoor('s', currBossCount);
        else
            plx->drawDoor('s', currEnemyCount);
        glPopMatrix();
    }
    if (lvl->roomIsExit(xLvl, yLvl))
    {
         glPushMatrix();
        glScaled(1.0,1.0,1.0);
        if (currBossCount > currEnemyCount)
            plx->drawDoor('d', currBossCount);
        else
            plx->drawDoor('d', currEnemyCount);
        glPopMatrix();
    }
}

void GLScene::manageEnemies()
{
    if (lvl->roomIsExit(xLvl, yLvl))
        manageBoss();
    else
    {

        for (int i = 0; i < currEnemyCount; i++)
        {
            e191Array[i]->updateEnemy(ply->getPosition());
            e191Array[i]->drawObject();
        }
    }
}

void GLScene::checkProj(int inpTeam)
{
     if (projTimer->getTicks() >= 300 && ply->getFiring())
    {
        projTimer->reset();
        projArray[currProjCount] = new Projectile();
        projArray[currProjCount]->projInit(ply->getxPos(), ply->getyPos(), ply->getFiringDir(), inpTeam);
        currProjCount++;
        audio_->playOnce("audio/fx_blast.ogg");
    }
}

void GLScene::manageBoss()
{
    if (lvl->roomHasBoss(xLvl, yLvl) && currBossCount)
    {
        for (int i = 0; i < currBossCount; i++)
        {
            boss[i]->drawObject();
            if (boss[i]->getShooting())
            {
                projArray[currProjCount] = new Projectile();
                projArray[currProjCount]->projInit(boss[i]->getxPos(),
                                                   boss[i]->getyPos(),
                                                   boss[i]->getFiringDir(), NOTTEAMPLAYER);
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
                if (lvl == floor2)
                  men->state = 6;
                  //exit(0);
                else
                {
                    lvl = floor2;
                    delete floor1;
                    xLvl = 0;
                    yLvl = 2;
                    ply->modifyHealth(2);
                    ui->setHealth(ply->getHealth());
                    ui->resetKeys();
                    ply->resetPos();

                }
                //men->state = 6;
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
            std::cout << "New Room" << std::endl;
            audio_->playOnce("audio/fx_found_key.ogg");
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
        projArray[i]->doObjectLogic();
        projArray[i]->drawObject();
    //projArray[i]->drawProj();
    }
}

void GLScene::transition(char dir)
{
    clearEnemies();
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

    if (!lvl->getCleared(xLvl, yLvl))
        generateEnemies();
}

void GLScene::generateEnemies()
{
    if (lvl->roomHasBoss(xLvl, yLvl))
    {
        boss[0] = new Boss();
        currBossCount++;
        boss[0]->bossInit(-3, 'e', 0);

        boss[1] = new Boss();
        currBossCount++;
        boss[1]->bossInit(3, 'w', 1);
    }
    else if (!lvl->roomIsStart(xLvl, yLvl))
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
    if (lvl->roomHasBoss(xLvl, yLvl))
    {
        for (int i = 0; i < currEnemyCount; i++)
        {
            delete boss[i];
        }
        currEnemyCount = 0;
    }
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
    lvl->setCleared(xLvl, yLvl);
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
	        KbMs->keyPressed(men);
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

    return 0;
}

bool GLScene::boxCollision (cartesian2d objectLoc0, cart2dDim objectDim0, cartesian2d objectLoc1, cart2dDim objectDim1)
{
	//do box collision calculations
	bool retIsCollision;

	cartesian2d obj0MinBounds = objectLoc0;
	cartesian2d obj0MaxBounds = {objectLoc0.x+objectDim0.width, objectLoc0.y+objectDim0.height};
	cartesian2d obj1MinBounds = objectLoc1;
	cartesian2d obj1MaxBounds = {objectLoc1.x+objectDim1.width, objectLoc1.y+objectDim1.height};

	retIsCollision = true;
	if (obj0MaxBounds.x < obj1MinBounds.x || obj0MinBounds.x > obj1MaxBounds.x)
		retIsCollision = false;
	if (obj0MaxBounds.y < obj1MinBounds.y || obj0MinBounds.y > obj1MaxBounds.y)
		retIsCollision = false;

	return retIsCollision;
}

void GLScene::collisionListProjectileToEnemy()
{
    //uintptr_t objID1;
    //uintptr_t objID2;
    bool tempIsCollision;
    for (int i = 0; i < currEnemyCount; i++)
    {
        //objID1 = pointerToInt(e191Array[i]);

        for (int j = 0; j < currProjCount; j++)
        {
            //objID2 = pointerToInt(projArray[j]);
            //tempIsCollision = collisionEnemyToProjectile(objID1, objID2);
            tempIsCollision = collisionObjectToObject(projArray[j], e191Array[i]);
            if (tempIsCollision)
            {
                std::cout << "Zombie hit! Attempting to play audio" << std::endl;
                audio_->playOnce("audio/fx_zombie_death.ogg");
                projArray[j]->setIsDead(tempIsCollision);
                e191Array[i]->setIsDead(tempIsCollision);
            }
        }
    }
}


void GLScene::collisionListPlayerToEnemy()
{
    //uintptr_t objID1;
    //uintptr_t objID2 = pointerToInt(ply);
    bool tempIsCollision;
    for (int i = 0; i < currEnemyCount; i++)
    {
        //objID1 = pointerToInt(e191Array[i]);
        //tempIsCollision = collisionEnemyToPlayer(objID1, objID2);

        tempIsCollision = collisionObjectToObject(ply, e191Array[i]);

        if (tempIsCollision)
        {
            audio_->playOnce("audio/fx_damage_taken.ogg");
            ply->setIsDead(tempIsCollision);
            e191Array[i]->setIsDead(tempIsCollision);
        }
    }
    //collisionEnemyToPlayer(uintptr_t inpID1, uintptr_t inpID2);
}

void GLScene::collisionListProjectileToProjectile()
{
    //uintptr_t objID1;
    //uintptr_t objID2;
    bool tempIsCollision;
    for (int i = 0; i < currProjCount; i++)
    {
        //objID1 = pointerToInt(projArray[i]);

        for (int j = i+1; j < currProjCount; j++)
        {
            //objID2 = pointerToInt(projArray[j]);
            //tempIsCollision = collisionProjectileToProjectile(objID1, objID2);
            tempIsCollision = collisionObjectToObject(projArray[j], projArray[i]);
            if (tempIsCollision)
            {
                projArray[j]->setIsDead(tempIsCollision);
                projArray[i]->setIsDead(tempIsCollision);
            }
        }
    }
}

void GLScene::collisionListProjectileToPlayer()
{
    //uintptr_t objID1;
    //uintptr_t objID2 = pointerToInt(ply);
    bool tempIsCollision;
    for (int i = 0; i < currProjCount; i++)
    {
        if (projArray[i]->getObjectTeam() != TEAMPLAYER)
        {
        //objID1 = pointerToInt(projArray[i]);
        //tempIsCollision = collisionPlayerToProjectile(objID2, objID1);
        tempIsCollision = collisionObjectToObject(ply, projArray[i]);
        if (tempIsCollision)
        {
            ply->setIsDead(tempIsCollision);
            projArray[i]->setIsDead(tempIsCollision);
        }
        }
    }
    //collisionEnemyToPlayer(uintptr_t inpID1, uintptr_t inpID2);
}

void GLScene::collisionListProjectileToBoss()
{
    bool tempIsCollision;
    for (int i = 0; i < currProjCount; i++)
    {
        for (int j = 0; j < currBossCount; j++)
        {
            if (projArray[i]->getObjectTeam() != NOTTEAMPLAYER)
            {
            //tempIsCollision = collisionProjectileToProjectile(objID1, objID2);
            tempIsCollision = collisionObjectToObject(projArray[i], boss[j]);
            if (tempIsCollision)
            {
                projArray[i]->setIsDead(tempIsCollision);
                boss[j]->setIsDead(tempIsCollision);
            }
            }
        }
    }
}

void GLScene::collisionListPlayerToBoss()
{
    bool tempIsCollision;
    for (int i = 0; i < currBossCount; i++)
    {
        tempIsCollision = collisionObjectToObject(ply, boss[i]);

        if (tempIsCollision)
        {
            ply->setIsDead(tempIsCollision);
            boss[i]->setIsDead(tempIsCollision);
        }
    }
}

template <class T, class U>
bool GLScene::collisionObjectToObject(T* inpObj1, U* inpObj2)
{
    cartesian2d objPos1;
    cart2dDim objDim1;
    cartesian2d objPos2;
    cart2dDim objDim2;

    objPos1 = inpObj1->getPosition();
    objDim1 = inpObj1->getObjectDimensions();
    objPos2 = inpObj2->getPosition();
    objDim2 = inpObj2->getObjectDimensions();

    return boxCollision(objPos1, objDim1, objPos2, objDim2);
}

template <class T, class U>
bool GLScene::collisionObjectBlockedByObject(T* inpObj1, U* inpObj2)
{
    cartesian2d objPos1;
    cart2dDim objDim1;
    cartesian2d objPos2;
    cart2dDim objDim2;

    objPos1 = inpObj1->getDestPosition();
    objDim1 = inpObj1->getObjectDimensions();
    objPos2 = inpObj2->getPosition();
    objDim2 = inpObj2->getObjectDimensions();

    return boxCollision(objPos1, objDim1, objPos2, objDim2);
}



void GLScene::addEnemyListToGridMap()
{

    uintptr_t tempID;

    for (int i = 0; i < currEnemyCount; i++)
    {
        tempID = pointerToInt(e191Array[i]);
        addEnemyToGridMap(tempID);
    }
}

void GLScene::addProjectileListToGridMap()
{
    uintptr_t tempID;
    for (int i = 0; i < currProjCount; i++)
    {
        tempID = pointerToInt(projArray[i]);
        addProjectileToGridMap(i);
    }
}

void GLScene::addWallListToGridMap()
{
    uintptr_t tempID;
    for (int i = 0; i < currWallCount; i++)
    {
        tempID = pointerToInt(wallArray[i]);
        addWallToGridMap(i);
    }
}

void GLScene::addPlayerToGridMap()
{
    vector < grid2d > gridPosList;
    ply->getCurrGridPos(gridPosList);
    gridMap->addGenericElement(PLAYERID, PLAYERTYPE, gridPosList);
}


void GLScene::initGridMap(grid2dDim inpDim)
{
    gridMap->initMap(inpDim, TYPEVARIETY);
    addEnemyListToGridMap();
    addProjectileListToGridMap();
    addWallListToGridMap();
    addPlayerToGridMap();
}
void GLScene::addEnemyToGridMap(uintptr_t inpID)
{
    vector < grid2d > gridPosList;

    Enemy191T *obj1 = (Enemy191T *) inpID;
    obj1->getCurrGridPos(gridPosList);
    //e191Array[inpID]->getCurrGridPos(gridPosList);
    gridMap->addGenericElement(inpID, ENEMYTYPE, gridPosList);
}

void GLScene::addProjectileToGridMap(uintptr_t inpID)
{
    vector < grid2d > gridPosList;

    Projectile *obj1 = (Projectile*) inpID;
    obj1->getCurrGridPos(gridPosList);

    //projArray[inpID]->getCurrGridPos(gridPosList);
    gridMap->addGenericElement(inpID, PROJECTILETYPE, gridPosList);
}

void GLScene::addWallToGridMap(uintptr_t inpID)
{
    vector < grid2d > gridPosList;

    Wall *obj1 = (Wall*) inpID;
    obj1->getCurrGridPos(gridPosList);

    //wallArray[inpID]->getCurrGridPos(gridPosList);
    gridMap->addGenericElement(inpID, WALLTYPE, gridPosList);
}

void GLScene::updateEnemyOnGridMap(uintptr_t inpID)
{
    vector < grid2d > gridPosList;
    vector < grid2d > gridDestList;

    Enemy191T *obj1 = (Enemy191T*) inpID;
    obj1->getCurrGridPos(gridPosList);
    obj1->getDestGridPos(gridDestList);

    //e191Array[inpID]->getCurrGridPos(gridPosList);
    //e191Array[inpID]->getDestGridPos(gridDestList);
    gridMap->updateGenericElement(inpID, ENEMYTYPE, gridPosList, gridDestList);
}

/*
void GLScene::updateProjectileOnGridMap(int inpID)
{
    vector < grid2d > gridPosList;
    vector < grid2d > gridDestList;
    projArray[inpID]->getCurrGridPos(gridPosList);
    projArray[inpID]->getDestGridPos(gridDestList);
    gridMap->updateGenericElement(inpID, PROJECTILETYPE, gridPosList, gridDestList);
}

void GLScene::updateWallOnGridMap(int inpID)
{
    vector < grid2d > gridPosList;
    vector < grid2d > gridDestList;
    wallArray[inpID]->getCurrGridPos(gridPosList);
    wallArray[inpID]->getDestGridPos(gridDestList);
    gridMap->updateGenericElement(inpID, WALLTYPE, gridPosList, gridDestList);
}
*/
void GLScene::updatePlayerOnGridMap()
{
    vector < grid2d > gridPosList;
    vector < grid2d > gridDestList;
    ply->getCurrGridPos(gridPosList);
    ply->getDestGridPos(gridDestList);
    gridMap->updateGenericElement(PLAYERID, PLAYERTYPE, gridPosList, gridDestList);
}

template<class T>
void GLScene::unionVectors(vector <T> frontVec, vector <T> backVec, vector <T> &retVec)
{
    for (int i = 0; i < backVec.size(); i++)
    {
        if (searchVector(frontVec, backVec.at(i)) == -1)
            frontVec.push_back(backVec.at(i));
    }

    retVec = frontVec;
}


template <class T>
uintptr_t GLScene::pointerToInt(T* inpPtr)
{
    //return uintptr_t(inpPtr);
    return reinterpret_cast<uintptr_t>(inpPtr);
}

template <class T>
T* GLScene::pointerToInt(uintptr_t inpInt)
{
    return (T*) inpInt;
}


template <class T>
int GLScene::searchVector(std::vector<T>vecToSearch, T varToFind)
{
    bool done;
	int count00;
	int retIndex;

	retIndex = -1;

	done = false;
	count00 = 0;

	while (!done && count00 < vecToSearch.size())
	{
		if (vecToSearch.at(count00) == varToFind)
		{
			done = true;
			retIndex = count00;
		}
		count00++;
	}

	return retIndex;
}

void GLScene::cleanEnemyList()
{
    for (int i = 0; i < currEnemyCount; i++)
    {
        if (e191Array[i]->getIsDead())
        {
            delete e191Array[i];
            removeArrayElement(e191Array, i, currEnemyCount);
            currEnemyCount--;
            ply->setDidKill(true);
        }
    }
}

void GLScene::cleanProjectileList()
{
    for (int i = 0; i < currProjCount; i++)
    {
        if (projArray[i]->getIsDead())
        {
            delete projArray[i];
            removeArrayElement(projArray, i, currProjCount);
            currProjCount--;
        }
    }
}

void GLScene::cleanPlayerList()
{
    if(ply->getIsDead())
    {
        ply->setIsDead(false);
        ply->modifyHealth(-1);
        ui->setHealth(ply->getHealth());
        if (ply->getHealth() < 0)
        {
           men->state = 7;
        }
    }
}

void GLScene::cleanBossList()
{
    for (int i = 0; i < currBossCount; i++)
    {
        if (boss[i]->getIsDead())
        {
            boss[i]->setIsDead(false);
            boss[i]->modifyHealth(-1);
            if (boss[i]->getHealth() < 0)
            {
                delete boss[i];
                removeArrayElement(boss, i, currBossCount);
                currBossCount--;
                ply->setDidKill(true);
            }
        }
    }
    //managePlayerKill();
}

void GLScene::managePlayerKill()
{
    if (ply->getDidKill())
    {
        ply->setDidKill(false);
        ply->modifyKills(1);
        if (ply->getKills() > KILLSTREAKLIMIT)
        {
            ply->setKills(0);
            if (ply->getHealth() < MAXPLAYERHEALTH)
            {
                ply->modifyHealth(1);
                ui->setHealth(ply->getHealth());
            }
        }
    }
}



template <class T>
void GLScene::removeArrayElement(T inpArr[], int inpIndex, int inpLength)
{
    for (int i = inpIndex + 1; i < inpLength; i++)
    {
        inpArr[i-1] = inpArr[i];
    }
}
