#include <player.h>
#include <timer.h>
#include <textureLoader.h>
#include <iostream>
#include <Levels.h>

using namespace std;


//timer *objectTimer = new timer();

textureLoader runText[10];
textureLoader stand[2];


player::player()
{
    //ctor
    verticies[0].x = 0.0;verticies[0].y = 0.0;verticies[0].z = -1.0;
    verticies[1].x = 1.0;verticies[1].y = 0.0;verticies[1].z = -1.0;
    verticies[2].x = 1.0;verticies[2].y = 1.0;verticies[2].z = -1.0;
    verticies[3].x = 0.0;verticies[3].y = 1.0;verticies[3].z = -1.0;

    runspeed  =0;
    jumpspeed =0;
    actionTrigger =0;

    spriteX = 0;
    spriteY = 0;

    sprRenderCount = 0;

    sprPrevMovUp = false;
    sprPrevMovDown = false;
    sprPrevMovLeft = false;
    sprPrevMovRight = false;

    objectTexture = new textureLoader[1]();
    objectTimer = new timer();
    checkDoor = '0';
}

player::~player()
{
    //dtor
    delete []objectTexture;
    delete objectTimer;
}
void player::drawPlayer(bool facingRight)
{

    objectTexture[0].binder();
    selectSprite(spriteX, spriteY, sprHeight, sprWidth);
}

void player::playerInit()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    objectTimer->start();

    stand[0].bindTexture("images/player/play.png");

    runText[0].bindTexture("images/player/player0.png");
    runText[1].bindTexture("images/player/player1.png");
    runText[2].bindTexture("images/player/player2.png");
    runText[3].bindTexture("images/player/player3.png");
    runText[4].bindTexture("images/player/player4.png");
    runText[5].bindTexture("images/player/player5.png");
    runText[6].bindTexture("images/player/player6.png");
    runText[7].bindTexture("images/player/player7.png");
    runText[8].bindTexture("images/player/player8.png");
    runText[9].bindTexture("images/player/player9.png");

    objectTexture[0].bindTexture("images/playerSprites00.png");


    //playerSprites00.png

}



void player::actions(int action)
{
    glPushMatrix();

    if (action >= 1)
        {
            moveObject();

            if (getxVel() + getxPos() < -3.9)
             {
                 if (getyVel() + getyPos() > -.1 && getyVel() + getyPos() < .1)
                    checkDoor = 'w';
             }
            else if (getxVel() + getxPos() > 2.9)
            {
                if (getyVel() + getyPos() > -.1 && getyVel() + getyPos() < .1)
                {
                    checkDoor = 'e';
                }

            }
            else
            {

                setxPos(getxVel());
            }

            if (getyVel() + getyPos() < -1.9)
             {
                 if (getxVel() + getxPos() > -.2 && getxVel() + getxPos() < .2)
                    checkDoor = 's';
             }
            else if (getyVel() + getyPos() > .9)
            {
                if (getxVel() + getxPos() > -.2 && getxVel() + getxPos() < .2)
                    checkDoor = 'n';
            }
            else
            {
                setyPos(getyVel());
            }

        }
       glTranslated(getxPos(),getyPos(),-5.0);

       if(objectTimer->getTicks()>15){

        if(action >= 1)
        {
         runspeed++;
        runspeed = runspeed %10;
        }
        objectTimer->reset();

        if (sprRenderCount % 5 == 0)
            calcSprite();
        sprRenderCount++;
       }

       drawPlayer(facingRight);

    glPopMatrix();
    if (sprRenderCount > 1000000)
        sprRenderCount = 0;
}

void player::setxPos(float x)
{
    xPos += x;

}

void player::setyPos(float y)
{
    yPos += y;
}

float player::getxPos()
{
    return xPos;
}

float player::getyPos()
{
    return yPos;
}

void player::setxVel(float x)
{
    xVel = x;
}

float player::getxVel()
{
    return xVel;
}

void player::setyVel(float y)
{
    yVel = y;
}

float player::getyVel()
{
    return yVel;
}

bool player::checkMoving()
{
    return (movingLeft || movingRight || movingUp || movingDown);
}

bool player::getFiring()
{
    return isFiring;
}

void player::setFiring(bool x)
{
    isFiring = x;
}

void player::setFiringDir(char x)
{
    firingDir = x;
}

char player::getFiringDir()
{
    return firingDir;
}

void player::calcSprite()
{

	spriteX++;
	if (spriteX > 9)
		spriteX = 0;
	if (movingLeft)
	{
		spriteY = sprHeight - 1 - 2;
	}
	if (movingRight)
	{
		spriteY = sprHeight - 1 - 0;
	}
	if (movingUp)
	{
		spriteY = sprHeight - 1 - 1;
	}
	if (movingDown)
	{
		spriteY = sprHeight - 1 - 3;
	}
	if (!movingRight && !movingLeft && !movingUp && !movingDown)
	{
	    if (spriteY > 3)
            spriteY -= 4;
		if (spriteY == sprHeight - 1 - 5)
			spriteX = 0;
		else if (spriteX > 2)
			spriteX = 0;
	}

	//spriteY = 0;
	//spriteX = 0;
}


void player::selectSprite(int x, int y, int spritesHeight, int spritesWidth)
{
	double lowBoundX, highBoundX;
	double lowBoundY, highBoundY;

	lowBoundX = double(x)/double(spritesWidth);
	highBoundX = double(x+1)/double(spritesWidth);
	lowBoundY = double(y)/double(spritesHeight);
	highBoundY = double(y+1)/double(spritesHeight);

	glBegin(GL_QUADS);

    glTexCoord2f(lowBoundX + 0.005, highBoundY - 0.005);
    glVertex3f(verticies[0].x,verticies[0].y,verticies[0].z);

    glTexCoord2f(highBoundX - 0.005, highBoundY - 0.005);
    glVertex3f(verticies[1].x,verticies[1].y,verticies[1].z);

    glTexCoord2f(highBoundX - 0.005, lowBoundY + 0.005);
    glVertex3f(verticies[2].x,verticies[2].y,verticies[2].z);

    glTexCoord2f(lowBoundX + 0.005, lowBoundY + 0.005);
    glVertex3f(verticies[3].x,verticies[3].y,verticies[3].z);

    glEnd();
}

//NM: currently not in use
bool player::compareMoves()
{
    return (sprPrevMovUp == movingUp && sprPrevMovDown == movingDown && sprPrevMovLeft == movingLeft && sprPrevMovRight == movingRight);
}

void player::moveObject()
{
    //if (!checkMoving())
    {
        if (movingUp && !movingDown)
        {
            setyVel(.005);
        }
        if (movingDown && !movingUp)
        {
            setyVel(-.005);
        }
        if (movingRight && !movingLeft)
        {
            setxVel(.005);
        }
        if (movingLeft && !movingRight)
        {
            setxVel(-.005);
        }
        //setyVel(.005);
    }
    //return (movingLeft || movingRight || movingUp || movingDown);
}

cartesian2d player::getDestPosition()
{
    return destPosition;
}

cartesian2d player::setDestPosition(cartesian2d inpPos)
{
    destPosition = inpPos;
}

cartesian2d player::getPosition()
{
    cartesian2d retPos = {xPos, yPos};
    return retPos;
}

cart2dDim player::getObjectDimensions()
{
    return objectDimensions;
}

void player::getCurrGridPos(vector<grid2d>& retPos)
{
    retPos = classCurrentGridCoords;
}

void player::setCurrGridPos(vector<grid2d>inpPos)
{
    classCurrentGridCoords = inpPos;
}

void player::getDestGridPos(vector<grid2d>& retPos)
{
    retPos = classTestGridCoords;
}

void player::setDestGridPos(vector<grid2d>inpPos)
{
    classTestGridCoords = inpPos;
}

