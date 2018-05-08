#include "Levels.h"

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

    rooms[0][1].eDoor = true;
    rooms[0][1].hasKey = true;

    rooms[1][1].nDoor = true;
    rooms[1][1].sDoor = true;
    rooms[1][1].eDoor = true;
    rooms[1][1].wDoor = true;

    rooms[2][1].wDoor = true;

    rooms[0][2].eDoor = true;

    rooms[1][2].wDoor = true;
    rooms[1][2].sDoor = true;
    rooms[1][2].eDoor = true;
    rooms[1][2].maxEnemies = 3;

    rooms[2][2].wDoor = true;
    rooms[2][2].nDoor = true;
    rooms[2][2].maxEnemies = 4;

    rooms[1][3].eDoor = true;

    rooms[2][3].wDoor = true;
    rooms[2][3].sDoor = true;
    rooms[2][3].eDoor = true;

    rooms[3][3].wDoor = true;
    rooms[3][3].eDoor = true;

    rooms[4][3].wDoor = true;
    rooms[4][3].nDoor = true;
    rooms[4][3].sDoor = true;

    rooms[4][2].nDoor = true;
    rooms[4][2].isBoss = true;

    rooms[4][4].sDoor = true;

}

int Levels::getMaxE(int x, int y)
{
    return rooms[x][y].maxEnemies;
}

bool Levels::getwDoor(int x, int y)
{
    return rooms[x][y].wDoor;
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
