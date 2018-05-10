#ifndef LEVELS_H
#define LEVELS_H

#include <ctime>
#include <cstdlib>

typedef struct {
             bool nDoor = false;
             bool sDoor = false;
             bool eDoor = false;
             bool wDoor = false;
             bool hasKey = false;
             bool isBoss = false;
             int maxEnemies = rand() % 10;
             int maxProps = 0;
             bool exists = false;
             bool isStart = false;
             bool isExit = false;
             bool isCleared = false;} properties;

class Levels
{
    public:
        Levels();
        virtual ~Levels();
        bool getwDoor(int x, int y);
        bool geteDoor(int x, int y);
        bool getsDoor(int x, int y);
        bool getnDoor(int x, int y);
        void LevelInit();
        int getMaxE(int x, int y);
        bool roomHasKey(int x, int y);
        void gotKey(int x, int y);
        bool roomHasBoss(int x, int y);
        bool roomIsExit(int x, int y);
        void Floor2Init();
        bool roomIsStart(int x, int y);
        void genKeys();
        bool getCleared(int x, int y);
        void setCleared(int x, int y);

        //int maxEnemies(array);
        //int maxProps(array);
        properties rooms[10][10];

    protected:

    private:
};

#endif // LEVELS_H
