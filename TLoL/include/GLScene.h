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

#include <GlobalDataStructures.h>
#include <AudioComponent.h>
//#include <cstdint.h>
extern "C" {
#include <stdint.h>
}

using namespace std;


class Enemy191T;
class player;
class Wall;
class Projectile;

//class Enemy191T;


class GLScene
{
    public:
        GLScene();
        virtual ~GLScene();
        GLint initGL();
        GLint drawGLScene();
        GLvoid resizeGLScene(GLsizei, GLsizei);

        int windMsg(HWND,UINT, WPARAM,LPARAM);

        void transition(char);

        void clearEnemies();

        void generateEnemies();

        void manageKeys();

        void manageBoss();

        void checkProj(int inpTeam);

        void drawDoors();

        void manageEnemies();

        WPARAM wParam;
        float screenHeight;
        float screenWidth;

        void manageProj();
    protected:

    private:
        AudioComponent* audio_;
        //Enemy191T *e191Array;

        void mainGameLogic();

        bool boxCollision (cartesian2d objectLoc0, cart2dDim objectDim0, cartesian2d objectLoc1, cart2dDim objectDim1);
        void collisionListPlayerToEnemy();
        void collisionListProjectileToEnemy();
        void collisionListProjectileToProjectile();
        void collisionListProjectileToPlayer();

        void collisionListProjectileToBoss();
        void collisionListPlayerToBoss();

        template <class T, class U>
        bool collisionObjectToObject(T *inpObj1, U *inpObj2);

        template <class T, class U>
        bool collisionObjectBlockedByObject(T *inpObj1, U *inpObj2);

        void addEnemyListToGridMap();
        void addProjectileListToGridMap();
        void addWallListToGridMap();
        void addPlayerToGridMap();
        void initGridMap(grid2dDim inpDim);
        void addEnemyToGridMap(uintptr_t inpID);
        void addProjectileToGridMap(uintptr_t inpID);
        void addWallToGridMap(uintptr_t inpID);
        void updateEnemyOnGridMap(uintptr_t inpID);
        //void updateProjectileOnGridMap(int inpID);
        //void updateWallOnGridMap(int inpID);
        void updatePlayerOnGridMap();

        void cleanEnemyList();
        void cleanProjectileList();

        //IMPORANT: this calls exit
        void cleanPlayerList();
        void cleanBossList();

        template<class T>
        void unionVectors(vector <T> frontVec, vector <T> backVec, vector <T> &retVec);

        template<class T>
        int searchVector(std::vector <T> vecToSearch, T varToFind);

        template <class T>
        uintptr_t pointerToInt(T* inpPtr);

        template <class T>
        T* pointerToInt(uintptr_t inpInt);

        template <class T>
        void removeArrayElement(T inpArr[], int inpIndex, int inpLength);
};

#endif // GLSCENE_H
