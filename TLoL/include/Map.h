//This is a class for the Grid that I, Norman, will be implementing
//The purpose of the grid is to help with pathfinding, maze generation, and collision detection

#ifndef MAP_H
#define MAP_H

#include<GlobalDataStructures.h>
//#include <queue>
#include <string>
#include <iostream>

using namespace std;

struct priorityCoordObject
{
	queue < grid2d > path;
	int priority;

	bool operator < (const priorityCoordObject &a) const
	{
		return (priority < a.priority);
	}
	bool operator == (const priorityCoordObject &a) const
	{
		return (path.back() == a.path.back());
	}

	friend ostream& operator<<(ostream &out, const priorityCoordObject &a)
	{
		out << a.priority;
		//out << ':';
		//out << gC.y;

		return out; //return a reference to the output stream
	}

};

class Map
{
    public:
        Map();
        virtual ~Map();

        int calcTaxiDistance(grid2d inpStartPos, grid2d inpEndPos);
        int calcDiagonalTaxiDist(grid2d inpStartPos, grid2d inpEndPos);

        void searchDijkstras(grid2d startPos, vector < grid2d > endPos, queue < grid2d > &retSolution);
        void searchAStar(grid2d startPos, vector < grid2d > endPos, queue < grid2d > &retSolution);
        cartesian2d getLowRealCoord(grid2d inpGraphCoord, cart2dDim inpWorldDim);
        cartesian2d getHighRealCoord(grid2d inpGraphCoord, cart2dDim inpWorldDim);
        void getRealToGraphCoords(cartesian2d inpObjectCoord, cart2dDim inpObjectDim, cart2dDim inpWorldDim, std::vector < grid2d > &retGraphCoords);

        void initMap(grid2dDim inpDim, int elementVariety);
		gridElements getMapElement(grid2d inpCoord);
		void getMapElementGeneric(grid2d inpCoord, vector < vector < int > > &retElement);
		bool isGraphCollisionGeneric(vector < grid2d > inpPositions, int inpID, int inpType, int cmpType);
		void addGenericElement(int inpID, int inpType, vector < grid2d > inpPositions);
        void removeGenericElement(int inpID, int inpType, vector < grid2d > inpPositions);
        void updateGenericElement(int inpID, int inpType, vector < grid2d > oldPositions, vector < grid2d > newPositions);

		bool isGraphWallCollision(vector < grid2d > inpPositions, int inpID = -1);
		bool isGraphEnemyCollision(vector < grid2d > inpPositions, int inpID = -1);
		bool isGraphPlayerCollision(vector < grid2d > inpPositions, int inpID = -1);
		//void insertWalls();
		//void insertEnemies();
		//void insertPlayers();
		//void addWallList(vector < int > inpIDList, vector < vector < grid2d > > inpPosList);
		//void addEnemyList(vector < int > inpIDList, vector < vector < grid2d > > inpPosList);
		//void addPlayerList(vector < int > inpIDList, vector < vector < grid2d > > inpPosList);
        void addWall(int inpID, vector < grid2d > inpPositions);
        void addEnemy(int inpID, vector < grid2d > inpPositions);
        void addPlayer(int inpID, vector < grid2d > inpPositions);
        void removeWall(int inpID, vector < grid2d > inpPositions);
        void removeEnemy(int inpID, vector < grid2d > inpPositions);
        void removePlayer(int inpID, vector < grid2d > inpPositions);
        void updateWall(int inpID, vector < grid2d > oldPositions, vector < grid2d > newPositions);
        void updateEnemy(int inpID, vector < grid2d > oldPositions, vector < grid2d > newPositions);
        void updatePlayer(int inpID, vector < grid2d > oldPositions, vector < grid2d > newPositions);


    protected:

    private:

        void basicDijkstras(vector < vector < gridElements > > inpGraph, grid2d startPos, vector < grid2d > endPos, queue < grid2d > &retSolution);
        void basicAStar(vector < vector < gridElements > > inpGraph, grid2d startPos, vector < grid2d > endPos, queue < grid2d > &retSolution);
        cartesian2d mapToLowRealCoord(grid2d inpGraphCoord, grid2dDim inpGraphDim, cart2dDim inpWorldDim);
        cartesian2d mapToHighRealCoord(grid2d inpGraphCoord, grid2dDim inpGraphDim, cart2dDim inpWorldDim);
        void realCoordToGraph(cartesian2d inpObjectCoord, cart2dDim inpObjectDim, cart2dDim inpWorldDim, grid2dDim inpGraphDim, std::vector < grid2d > &retGraphCoords);

        void expandMapLoc(vector < vector < gridElements > > inpGraph, grid2d inpCoord, vector < grid2d > &retExpansion);
        int calcMinTaxiDist(grid2d inpStartPos, vector < grid2d > inpEndPos);
        int calcMinDiagTaxiDist(grid2d inpStartPos, vector < grid2d > inpEndPos);
        bool isInPriorQueue(priority_queue < priorityCoordObject > inpQueue, grid2d inpElement);

		void basicDijkstrasGeneric(vector < vector < vector < vector < int > > > > inpGraph, grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution);
        void basicAStarGeneric(vector < vector < vector < vector < int > > > > inpGraph, grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution);
		void expandMapLocGeneric(vector < vector < vector < vector < int > > > > inpGraph, grid2d inpCoord, vector < grid2d > &retExpansion);
		bool doesIntersect1DList2DList(vector < vector < int > > inp2DList, vector < int > inp1DList);

        template <class T>
        bool isInQueue(queue <T> inpQueue, T inpElement);

        template <class T>
        bool isInPriorityQueue(priority_queue <T> inpQueue, T inpElement);

        template<class T>
        int searchVector(std::vector <T> vecToSearch, T varToFind);

        template <class T>
        void display1DVec(vector <T> inpVector, string inpDelim = "");

        template <class T>
        void display2DVec(vector < vector <T> > inpVector, string inpDelim = "");

        template <class T>
        T getMapElement(vector < vector <T> > inpVector, int inpX, int inpY);

        template <class T>
        void display1DQueue(queue <T> inpQueue, string inpDelim = "");

        template <class T>
        void display1DPriorQueue(priority_queue <T> inpQueue, string inpDelim = "");

        grid2dDim classMapDimensions;
        std::vector < std::vector < gridElements > > classMainMap;
        vector < vector < vector < vector < int > > > > classMainMap00;

        /*
        struct cartesian2d
        {
            double x;
            double y;
        };

        struct cart2dDim
        {
            double width;
            double height;
        };

        struct grid2d
        {
            int x;
            int y;
            bool operator == (const grid2d a) const
            {
                return (a.y == y && a.x == x);
            }
        };

        struct grid2dDim
        {
            int width;
            int height;
        };

        struct gridElements
        {
            std::vector <int> players;
            std::vector <int> enemies;
            std::vector <int> walls;
        };

        */

};

#endif // MAP_H
