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
    rooms[1][0].maxEnemies = rand() % 10;

    rooms[0][1].eDoor = true;
    rooms[0][1].exists = true;
    rooms[0][1].maxEnemies = rand() % 10;

    rooms[1][1].nDoor = true;
    rooms[1][1].sDoor = true;
    rooms[1][1].eDoor = true;
    rooms[1][1].wDoor = true;
    rooms[1][1].exists = true;
    rooms[1][1].maxEnemies = rand() % 10;

    rooms[2][1].wDoor = true;
    rooms[2][1].exists = true;
    rooms[2][1].maxEnemies = rand() % 10;

    rooms[0][2].eDoor = true;
    rooms[0][2].exists = true;
    rooms[0][2].isStart = true;

    rooms[1][2].wDoor = true;
    rooms[1][2].sDoor = true;
    rooms[1][2].eDoor = true;
    rooms[1][2].exists = true;
    rooms[1][2].maxEnemies = rand() % 10;

    rooms[2][2].wDoor = true;
    rooms[2][2].nDoor = true;
    rooms[2][2].exists = true;
    rooms[2][2].maxEnemies = rand() % 10;

    rooms[1][3].eDoor = true;
    rooms[1][3].exists = true;
    rooms[1][3].maxEnemies = rand() % 10;

    rooms[2][3].wDoor = true;
    rooms[2][3].sDoor = true;
    rooms[2][3].eDoor = true;
    rooms[2][3].exists = true;
    rooms[2][3].maxEnemies = rand() % 10;

    rooms[3][3].wDoor = true;
    rooms[3][3].eDoor = true;
    rooms[3][3].exists = true;
    rooms[3][3].maxEnemies = rand() % 10;

    rooms[4][3].wDoor = true;
    rooms[4][3].nDoor = true;
    rooms[4][3].sDoor = true;
    rooms[4][3].exists = true;
    rooms[4][3].maxEnemies = rand() % 10;

    rooms[4][2].nDoor = true;
    rooms[4][2].isBoss = true;
    rooms[4][2].exists = true;

    rooms[4][4].sDoor = true;
    rooms[4][4].exists = true;
    rooms[4][4].maxEnemies = rand() % 10;

    int keysPlanted = 0;
    while(keysPlanted < 3)
    {
        int randX = rand() % 5;
        int randY = rand() % 5;
        if (rooms[randX][randY].exists &&
            rooms[randX][randY].hasKey == false &&
            rooms[randX][randY].isBoss == false &&
            rooms[randX][randY].isStart == false)
            {
                rooms[randX][randY].hasKey = true;
                keysPlanted++;
            }

    }

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
