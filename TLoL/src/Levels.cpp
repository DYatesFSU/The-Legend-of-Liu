#include "Levels.h"
#include <cstdlib>
#include <ctime>

Levels::Levels()
{
    //ctor



}

Levels::~Levels()
{
    //dtor
}

void Levels::LevelInit()
{
    rooms[1][0].nDoor = true;
    rooms[1][0].exists = true;

    rooms[0][1].eDoor = true;
    rooms[0][1].exists = true;

    rooms[1][1].nDoor = true;
    rooms[1][1].sDoor = true;
    rooms[1][1].eDoor = true;
    rooms[1][1].wDoor = true;
    rooms[1][1].exists = true;

    rooms[2][1].wDoor = true;
    rooms[2][1].exists = true;

    rooms[0][2].eDoor = true;
    rooms[0][2].exists = true;
    rooms[0][2].isStart = true;

    rooms[1][2].wDoor = true;
    rooms[1][2].sDoor = true;
    rooms[1][2].eDoor = true;
    rooms[1][2].exists = true;

    rooms[2][2].wDoor = true;
    rooms[2][2].nDoor = true;
    rooms[2][2].exists = true;

    rooms[1][3].eDoor = true;
    rooms[1][3].exists = true;

    rooms[2][3].wDoor = true;
    rooms[2][3].sDoor = true;
    rooms[2][3].eDoor = true;
    rooms[2][3].exists = true;

    rooms[3][3].wDoor = true;
    rooms[3][3].eDoor = true;
    rooms[3][3].exists = true;

    rooms[4][3].wDoor = true;
    rooms[4][3].nDoor = true;
    rooms[4][3].sDoor = true;
    rooms[4][3].exists = true;

    rooms[4][2].nDoor = true;
    rooms[4][2].exists = true;
    rooms[4][2].isExit = true;

    rooms[4][4].sDoor = true;
    rooms[4][4].exists = true;

    genKeys();

}

void Levels::Floor2Init()
{
    rooms[0][2].exists = true;
    rooms[0][2].eDoor = true;

    rooms[1][2].exists = true;
    rooms[1][2].sDoor = true;
    rooms[1][2].eDoor = true;
    rooms[1][2].wDoor = true;

    rooms[1][1].sDoor = true;
    rooms[1][1].exists = true;
    rooms[1][1].nDoor = true;

    rooms[1][0].exists = true;
    rooms[1][0].nDoor = true;
    rooms[1][0].eDoor = true;

    rooms[2][0].exists = true;
    rooms[2][0].wDoor = true;

    rooms[2][2].exists = true;
    rooms[2][2].wDoor = true;
    rooms[2][2].eDoor = true;

    rooms[3][2].exists = true;
    rooms[3][2].wDoor = true;
    rooms[3][2].eDoor = true;

    rooms[3][0].exists = true;
    rooms[3][0].wDoor = true;
    rooms[3][0].eDoor = true;

    rooms[4][2].exists = true;
    rooms[4][2].wDoor = true;
    rooms[4][2].sDoor = true;
    rooms[4][2].nDoor = true;

    rooms[4][1].exists = true;
    rooms[4][1].nDoor = true;
    rooms[4][1].eDoor = true;
    rooms[4][1].sDoor = true;

    rooms[4][0].exists = true;
    rooms[4][0].nDoor = true;

    rooms[4][3].exists = true;
    rooms[4][3].sDoor = true;
    rooms[4][3].eDoor = true;
    rooms[4][3].nDoor = true;

    rooms[5][1].exists = true;
    rooms[5][1].wDoor = true;

    rooms[5][3].exists = true;
    rooms[5][3].wDoor = true;

    rooms[4][4].exists = true;
    rooms[4][4].sDoor = true;
    rooms[4][4].wDoor = true;

    rooms [3][4].exists = true;
    rooms[3][4].eDoor = true;
    rooms[3][4].nDoor = true;

    rooms[3][5].exists = true;
    rooms[3][5].sDoor = true;
    rooms[3][5].wDoor = true;

    rooms[2][5].exists = true;
    rooms[2][5].eDoor = true;
    rooms[2][5].wDoor = true;

    rooms[1][5].exists = true;
    rooms[1][5].eDoor = true;
    rooms[1][5].sDoor = true;

    rooms[1][4].exists = true;
    rooms[1][4].isBoss = true;
    rooms[1][1].nDoor = true;
    rooms[1][4].isExit = true;


    genKeys();



}

void Levels::genKeys()
{
    int keysPlanted = 0;
    while(keysPlanted < 3)
    {
        int randX = rand() % 5;
        int randY = rand() % 5;
        if (rooms[randX][randY].exists &&
            rooms[randX][randY].hasKey == false &&
            rooms[randX][randY].isBoss == false &&
            rooms[randX][randY].isStart == false &&
            rooms[randX][randY].isExit == false)
            {
                rooms[randX][randY].hasKey = true;
                keysPlanted++;
            }

    }
}

bool Levels::getCleared(int x, int y)
{
    return rooms[x][y].isCleared;
}

void Levels::setCleared(int x, int y)
{
    rooms[x][y].isCleared = true;
}

bool Levels::roomIsStart(int x, int y)
{
    return rooms[x][y].isStart;
}

int Levels::getMaxE(int x, int y)
{
    return rooms[x][y].maxEnemies;
}

bool Levels::getwDoor(int x, int y)
{
    return rooms[x][y].wDoor;
}

void Levels::gotKey(int x, int y)
{
    rooms[x][y].hasKey = false;
}

bool Levels::roomHasBoss(int x, int y)
{
    return rooms[x][y].isBoss;
}

bool Levels::geteDoor(int x, int y)
{
    return rooms[x][y].eDoor;
}

bool Levels::getsDoor(int x, int y)
{
    return rooms[x][y].sDoor;
}

bool Levels::getnDoor(int x, int y)
{
    return rooms[x][y].nDoor;
}

bool Levels::roomHasKey(int x, int y)
{
    return rooms[x][y].hasKey;
}

bool Levels::roomIsExit(int x, int y)
{
    return rooms[x][y].isExit;
}
