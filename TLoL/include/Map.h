//This is a class for the Grid that I, Norman, will be implementing
//The purpose of the grid is to help with pathfinding, maze generation, and collision detection

#ifndef MAP_H
#define MAP_H

#include<GlobalDataStructures.h>
//#include <queue>
#include <string>
#include <iostream>

extern "C" {
#include <stdint.h>
}

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

        void searchDijkstras(grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution);
        void searchAStar(grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution);
        cartesian2d getLowRealCoord(grid2d inpGraphCoord, cart2dDim inpWorldDim);
        cartesian2d getHighRealCoord(grid2d inpGraphCoord, cart2dDim inpWorldDim);
        void getRealToGraphCoords(cartesian2d inpObjectCoord, cart2dDim inpObjectDim, cart2dDim inpWorldDim, std::vector < grid2d > &retGraphCoords);

        void initMap(grid2dDim inpDim, int elementVariety);
		void getMapElementGeneric(grid2d inpCoord, vector < vector < uintptr_t > > &retElement);
		bool isGraphCollisionGeneric(vector < grid2d > inpPositions, uintptr_t inpID, int inpType, int cmpType);
		bool isGraphSquareCollisionGeneric(grid2d inpPos, uintptr_t inpID, int inpType, int cmpType);
		void addGenericElement(uintptr_t inpID, int inpType, vector < grid2d > inpPositions);
        void removeGenericElement(uintptr_t inpID, int inpType, vector < grid2d > inpPositions);
        void updateGenericElement(uintptr_t inpID, int inpType, vector < grid2d > oldPositions, vector < grid2d > newPositions);

        void clearIDs(int inpType, vector < grid2d > inpPositions);
        void clearIDsWholeMap(int inpType, vector < grid2d > inpPositions);

        void displayMap();
        void displayElement(grid2d inpCoord);

        Map generateBasicCrudeMap(grid2dDim inpDim, grid2d inpStartPos, vector < grid2d > inpEndPoss, double inpWallToAreaRatio, double inpEnemyToAreaRatio);
        int getBasicCrudeElement(grid2d inpCoord);

    protected:

    private:

        cartesian2d mapToLowRealCoord(grid2d inpGraphCoord, grid2dDim inpGraphDim, cart2dDim inpWorldDim);
        cartesian2d mapToHighRealCoord(grid2d inpGraphCoord, grid2dDim inpGraphDim, cart2dDim inpWorldDim);
        void realCoordToGraph(cartesian2d inpObjectCoord, cart2dDim inpObjectDim, cart2dDim inpWorldDim, grid2dDim inpGraphDim, std::vector < grid2d > &retGraphCoords);

        int calcMinTaxiDist(grid2d inpStartPos, vector < grid2d > inpEndPos);
        int calcMinDiagTaxiDist(grid2d inpStartPos, vector < grid2d > inpEndPos);
        bool isInPriorQueue(priority_queue < priorityCoordObject > inpQueue, grid2d inpElement);

		void basicDijkstrasGeneric(vector < vector < vector < vector < uintptr_t > > > > inpGraph, grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution);
        void basicAStarGeneric(vector < vector < vector < vector < uintptr_t > > > > inpGraph, grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution);
		void expandMapLocGeneric(vector < vector < vector < vector < uintptr_t > > > > inpGraph, grid2d inpCoord, vector < grid2d > &retExpansion);

		template <class T>
		bool doesIntersect1DList2DList(vector < vector < T > > inp2DList, vector < int > inp1DList);

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

        void expandGridSquare(grid2d inpCoord, grid2dDim inpDim, vector < grid2d > &retExpansion);

        template<class T>
        void unionVectors(vector <T> frontVec, vector <T> backVec, vector <T> &retVec);

        grid2dDim classMapDimensions;
        vector < vector < vector < vector < uintptr_t > > > > classMainMap00;

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
