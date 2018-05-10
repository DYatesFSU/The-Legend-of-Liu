#include "Map.h"
#include <cmath>

Map::Map()
{
    //ctor
    classMapDimensions.width = 0;
    classMapDimensions.height = 0;
}

Map::~Map()
{
    //dtor
}

void Map::initMap(grid2dDim inpDim, int elementVariety)
{
	//gridElements tempElements;
	vector < vector < uintptr_t > > tempElements;
	vector < vector < vector < uintptr_t > > > tempElementsList;
	vector < vector < vector < vector < uintptr_t > > > > tempMap;
	classMapDimensions = inpDim;

	for (int i = 0; i < elementVariety; i++)
	{
		tempElements.push_back(vector < uintptr_t > ());
	}

	for (int i = 0; i < classMapDimensions.width; i++)
	{
		tempElementsList.push_back(tempElements);
	}

	//classMainMap00.clear();
	for (int i = 0; i < classMapDimensions.height; i++)
	{
		tempMap.push_back(tempElementsList);
	}
	classMainMap00 = tempMap;
}

void Map::getMapElementGeneric(grid2d inpCoord, vector < vector < uintptr_t > > &retElement)
{
    vector < vector < uintptr_t > > tempElement;
    tempElement = classMainMap00.at(inpCoord.y).at(inpCoord.x);
    retElement = tempElement;
}

bool Map::isGraphCollisionGeneric(vector < grid2d > inpPositions, uintptr_t inpID, int inpType, int cmpType)
{
    int count00 = 0;
	bool done = false;

	while (count00 < inpPositions.size() && !done)
    {
        done = isGraphSquareCollisionGeneric(inpPositions.at(count00), inpID, inpType, cmpType);
        count00++;
    }
	return done;
}

bool Map::isGraphSquareCollisionGeneric(grid2d inpPos, uintptr_t inpID, int inpType, int cmpType)
{
    int count00 = 0;
	bool done = false;

    int tempInt;
    tempInt = classMainMap00.at(inpPos.y).at(inpPos.x).at(cmpType).size();
    if (tempInt > 0)
    {
        if (inpType != cmpType)
        {
            done = true;
        }
        else if (searchVector(classMainMap00.at(inpPos.y).at(inpPos.x).at(cmpType), inpID) != -1)
        {
            if (tempInt > 1)
            {
                done = true;
            }
        }
    }
	return done;
}

void Map::addGenericElement(uintptr_t inpID, int inpType, vector < grid2d > inpPositions)
{
    vector < grid2d > tempGraphCoords;
    //getRealToGraphCoords(inpPos, inpDimensions, cart2dDim inpWorldDim, std::vector < grid2d > &retGraphCoords);
    for (int i = 0; i < inpPositions.size(); i++)
    {
        if (searchVector(classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType), inpID) == -1)
            classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType).push_back(inpID);
    }
}

void Map::removeGenericElement(uintptr_t inpID, int inpType, vector<grid2d>inpPositions)
{
    int tempLocIndex;
    for (int i = 0; i < inpPositions.size(); i++)
    {
        tempLocIndex = searchVector(classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType), inpID);
        if (tempLocIndex != -1)
            classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType).erase(classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType).begin() + tempLocIndex);
    }
}

void Map::updateGenericElement(uintptr_t inpID, int inpType, vector < grid2d > oldPositions, vector < grid2d > newPositions)
{
    removeGenericElement(inpID, inpType, oldPositions);
    addGenericElement(inpID, inpType, newPositions);
}

void Map::searchDijkstras(grid2d startPos, vector<grid2d>endPos, vector < int > blockList, queue<grid2d>& retSolution)
{
    queue < grid2d > tempSolution;
    vector < int > tempBlockers;
    tempBlockers.push_back(0);
    basicDijkstrasGeneric(classMainMap00, startPos, endPos, blockList, tempSolution);
    retSolution = tempSolution;
}

void Map::searchAStar(grid2d startPos, vector<grid2d>endPos, vector < int > blockList, queue<grid2d>& retSolution)
{
    queue < grid2d > tempSolution;
    vector < int > tempBlockers;
    tempBlockers.push_back(0);
    basicAStarGeneric(classMainMap00, startPos, endPos, blockList, tempSolution);
    retSolution = tempSolution;
}

cartesian2d Map::getLowRealCoord(grid2d inpGraphCoord, cart2dDim inpWorldDim)
{
    return mapToLowRealCoord(inpGraphCoord, classMapDimensions, inpWorldDim);
}

cartesian2d Map::getHighRealCoord(grid2d inpGraphCoord, cart2dDim inpWorldDim)
{
    return mapToHighRealCoord(inpGraphCoord, classMapDimensions, inpWorldDim);
}

void Map::getRealToGraphCoords(cartesian2d inpObjectCoord, cart2dDim inpObjectDim, cart2dDim inpWorldDim, std::vector<grid2d>& retGraphCoords)
{
    vector < grid2d > tempCoords;
    realCoordToGraph(inpObjectCoord, inpObjectDim, inpWorldDim, classMapDimensions, tempCoords);
    retGraphCoords = tempCoords;
}

int Map::calcTaxiDistance(grid2d inpStartPos, grid2d inpEndPos)
{
    return (abs(inpEndPos.x - inpStartPos.x) + abs(inpEndPos.y - inpStartPos.y));
}

int Map::calcDiagonalTaxiDist(grid2d inpStartPos, grid2d inpEndPos)
{
    int distX = abs(inpEndPos.x - inpStartPos.x);
    int distY = abs(inpEndPos.y - inpStartPos.y);
    if (distY < distX)
        distX = distY;
    return distX;
}

cartesian2d Map::mapToLowRealCoord(grid2d inpGraphCoord, grid2dDim inpGraphDim, cart2dDim inpWorldDim)
{
    cartesian2d retCartCoord;

	retCartCoord.x = inpWorldDim.width * inpGraphCoord.x / inpGraphDim.width;
	retCartCoord.y = inpWorldDim.height * inpGraphCoord.y / inpGraphDim.height;

	return retCartCoord;
}

cartesian2d Map::mapToHighRealCoord(grid2d inpGraphCoord, grid2dDim inpGraphDim, cart2dDim inpWorldDim)
{
    cartesian2d retCartCoord;

	retCartCoord.x = inpWorldDim.width * (inpGraphCoord.x + 1) / inpGraphDim.width;
	retCartCoord.y = inpWorldDim.height * (inpGraphCoord.y + 1) / inpGraphDim.height;

	return retCartCoord;
}

void Map::realCoordToGraph(cartesian2d inpObjectCoord, cart2dDim inpObjectDim, cart2dDim inpWorldDim, grid2dDim inpGraphDim, std::vector < grid2d > &retGraphCoords)
{

    int lowX, lowY;
    int highX, highY;

    vector < grid2d > tempGraphCoords;

    lowX = int(inpGraphDim.width * inpObjectCoord.x / inpWorldDim.width);
    lowY = int(inpGraphDim.height * inpObjectCoord.y / inpWorldDim.height);

    highX = int(inpGraphDim.width * (inpObjectCoord.x + inpObjectDim.width) / inpWorldDim.width);
    highY = int(inpGraphDim.height * (inpObjectCoord.y  + inpObjectDim.height) / inpWorldDim.height);


    //retGraphCoords.clear();

    for (int i = 0; i <= highY - lowY; i++)
    {
        for (int j = 0; j <= highX - lowX; j++)
        {
            tempGraphCoords.push_back({lowX + j, lowY + i});
        }
    }

    retGraphCoords = tempGraphCoords;
}

int Map::calcMinTaxiDist(grid2d inpStartPos, vector<grid2d>inpEndPos)
{
    int minDist = -1;
	if (inpEndPos.size() > 0)
	{
		minDist = calcTaxiDistance(inpStartPos, inpEndPos.at(0));
		int tempDist;
		for (int i = 1; i < inpEndPos.size(); i++)
		{
			tempDist = calcTaxiDistance(inpStartPos, inpEndPos.at(i));
			if (tempDist < minDist)
				minDist = tempDist;
		}
	}

	return minDist;
}

int Map::calcMinDiagTaxiDist(grid2d inpStartPos, vector<grid2d>inpEndPos)
{
    int minDist = -1;
	if (inpEndPos.size() > 0)
	{
		minDist = calcDiagonalTaxiDist(inpStartPos, inpEndPos.at(0));
		int tempDist;
		for (int i = 1; i < inpEndPos.size(); i++)
		{
			tempDist = calcDiagonalTaxiDist(inpStartPos, inpEndPos.at(i));
			if (tempDist < minDist)
				minDist = tempDist;
		}
	}

	return minDist;
}

bool Map::isInPriorQueue(priority_queue<priorityCoordObject>inpQueue, grid2d inpElement)
{
    bool found;

	found = false;
	while (!inpQueue.empty() && !found)
	{
		if (inpQueue.top().path.back() == inpElement)
		{
			found = true;
		}
		inpQueue.pop();
	}

	return found;
}

void Map::basicDijkstrasGeneric(vector < vector < vector < vector < uintptr_t > > > > inpGraph, grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution)
{
	priority_queue < priorityCoordObject > frontier;
	queue <grid2d> explored;
	vector <grid2d> tempExpansion;
	priorityCoordObject tempPriorObj;
	priorityCoordObject topPriorObj;
	bool found;
	found = false;

	topPriorObj.path.push(startPos);
	//topPriorObj.priority = -minTaxiDistGC(startPos, endPos);
	topPriorObj.priority = 0;
	frontier.push(topPriorObj);

	while (!frontier.empty() && !found)
	{
		if (searchVector(endPos, frontier.top().path.back()) != -1)
		{
			found = true;
			retSolution = frontier.top().path;
			frontier.pop();
		}
		else
		{
			//Side Note: take average of x and y for basic a star of 8 direction
				//if they do and don't reach a wall add that node to main
					//add all other nodes to unexplored queue
						//the unexplored queue needs to be sorted by closet to start position
			topPriorObj = frontier.top();
			frontier.pop();
			explored.push(topPriorObj.path.back());
			//just checks if in bounds
			expandMapLocGeneric(inpGraph, topPriorObj.path.back(), tempExpansion);
			for (int i = 0; i < tempExpansion.size(); i++)
			{
				//check if not wall
				//if (getMapElement(inpGraph, tempExpansion.at(i).x, tempExpansion.at(i).y) != GWALL)
				bool isBlocker = doesIntersect1DList2DList(inpGraph.at(tempExpansion.at(i).y).at(tempExpansion.at(i).x), blockList);
				//if (inpGraph.at(tempExpansion.at(i).y).at(tempExpansion.at(i).x).walls.size() > 0)
				if (!isBlocker)
				{
					tempPriorObj = topPriorObj;
					tempPriorObj.path.push(tempExpansion.at(i));
					//check if in frontier or explored
					if (!isInQueue(explored, tempExpansion.at(i)) && !isInPriorityQueue(frontier, tempPriorObj))
					{
						//tempPriorObj.priority = -minTaxiDistGC(tempExpansion.at(i), endPos);
						tempPriorObj.priority--;
						frontier.push(tempPriorObj);

					}
				}
			}
		}
	}
}

void Map::basicAStarGeneric(vector < vector < vector < vector < uintptr_t > > > > inpGraph, grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution)
{

	priority_queue < priorityCoordObject > frontier;
	//queue <grid2d> frontier;
	queue <grid2d> explored;
	//queue <grid2d> tempSolution;
	vector <grid2d> tempExpansion;
	priorityCoordObject tempPriorObj;
	priorityCoordObject topPriorObj;
	bool found;
	found = false;


	//frontier.push(startPos);
	//potentialSolutions.push(frontier);
	topPriorObj.path.push(startPos);
	topPriorObj.priority = -calcMinTaxiDist(startPos, endPos);
	frontier.push(topPriorObj);

	while (!frontier.empty() && !found)
	{
		if (searchVector(endPos, frontier.top().path.back()) != -1)
		{
			found = true;
			retSolution = frontier.top().path;
			frontier.pop();
		}
		else
		{

			//first go for the beeLine direction since up down left right check if either horizontal or vertical decreases
				//if they do and don't reach a wall add that node to main
					//add all other nodes to unexplored queue
						//the unexplored queue needs to be sorted by closet to end goal
			topPriorObj = frontier.top();
			frontier.pop();
			explored.push(topPriorObj.path.back());
			//just checks if in bounds
			expandMapLocGeneric(inpGraph, topPriorObj.path.back(), tempExpansion);
			for (int i = 0; i < tempExpansion.size(); i++)
			{
				//check if not wall
				//if (getMapElement(inpGraph, tempExpansion.at(i).x, tempExpansion.at(i).y) != GWALL)
				//if (inpGraph.at(tempExpansion.at(i).y).at(tempExpansion.at(i).x).walls.size() > 0)
                bool isBlocker = doesIntersect1DList2DList(inpGraph.at(tempExpansion.at(i).y).at(tempExpansion.at(i).x), blockList);
				if (!isBlocker)
				{
					tempPriorObj = topPriorObj;
					tempPriorObj.path.push(tempExpansion.at(i));
					//check if in frontier or explored
					//if (!isInQueue(explored, tempExpansion.at(i)) && !isInPQGC(frontier, tempExpansion.at(i)))
					if (!isInQueue(explored, tempExpansion.at(i)) && !isInPriorityQueue(frontier, tempPriorObj))
					{

						//tempPriorObj = topPriorObj;
						//tempPriorObj.path.push(tempExpansion.at(i));
						tempPriorObj.priority = -calcMinTaxiDist(tempExpansion.at(i), endPos);
						frontier.push(tempPriorObj);

					}
				}
			}
		}
	}
}

void Map::expandMapLocGeneric(vector < vector < vector < vector < uintptr_t > > > > inpGraph, grid2d inpCoord, vector < grid2d > &retExpansion)
{
    vector < grid2d > tempVec;
	for (int i = inpCoord.y - 1; i <= inpCoord.y + 1; i++)
	{
		for (int j = inpCoord.x - 1; j <= inpCoord.x + 1; j++)
		{
			if (!(i == inpCoord.y && j == inpCoord.x)) //this makes it so it doesn't include itself
			{
                if (i == inpCoord.y || j == inpCoord.x) //this makes it so that it only moves up and down - without out diagonal is valid
                {
                    if (i >= 0 && i < inpGraph.size())
                    {
                        if (j >= 0 && j < inpGraph.at(i).size())
                        {
                            //cout << "push back" << endl;
                            tempVec.push_back({j, i});
                        }
                    }
                }
			}
		}
	}
	retExpansion = tempVec;
}

template <class T>
bool Map::doesIntersect1DList2DList(vector < vector < T > > inp2DList, vector < int > inp1DList)
{
    int tempInt = inp2DList.size();
    for (int i = 0; i < inp1DList.size(); i++)
    {
        if (inp1DList.at(i) < inp2DList.size())
        {
            if (inp2DList.at(inp1DList.at(i)).size() > 0)
            {
                return true;
            }
        }
    }
    return false;
}

template <class T>
bool Map::isInQueue(queue<T>inpQueue, T inpElement)
{
    bool found;

	found = false;
	while (!inpQueue.empty() && !found)
	{
		if (inpQueue.front() == inpElement)
		{
			found = true;
		}
		inpQueue.pop();
	}

	return found;
}

template <class T>
bool Map::isInPriorityQueue(priority_queue<T>inpQueue, T inpElement)
{
    bool found;

	found = false;
	while (!inpQueue.empty() && !found)
	{
		if (inpQueue.top() == inpElement)
		{
			found = true;
		}
		inpQueue.pop();
	}

	return found;
}

template <class T>
int Map::searchVector(std::vector<T>vecToSearch, T varToFind)
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

template <class T>
void Map::display1DVec(vector<T>inpVector, string inpDelim)
{
    for (int i = 0; i < inpVector.size(); i++)
	{
		cout << inpVector.at(i) << inpDelim;
	}
	cout << endl;
}

template <class T>
void Map::display2DVec(vector< vector < T > > inpVector, string inpDelim)
{
    for (int i = 0; i < inpVector.size(); i++)
	{
		display1DVec(inpVector.at(i), inpDelim);
	}
}

template <class T>
T Map::getMapElement(vector < vector < T > > inpVector, int inpX, int inpY)
{
    T retElement;
	if (inpY < inpVector.size() && inpY >= 0)
	{
		if (inpX < inpVector.at(inpY).size() && inpX >= 0)
		{
			retElement = inpVector.at(inpY).at(inpX);
		}
		else
			cout << "getMapElement error" << endl;
	}
	else
			cout << "getMapElement error" << endl;
	return retElement;
}

template <class T>
void Map::display1DQueue(queue<T>inpQueue, string inpDelim)
{
    while (!inpQueue.empty())
	{
		cout << inpQueue.front() << inpDelim;
		inpQueue.pop();
	}
	cout << endl;
}

template <class T>
void Map::display1DPriorQueue(priority_queue<T>inpQueue, string inpDelim)
{
    while (!inpQueue.empty())
	{
		cout << inpQueue.top() << inpDelim;
		inpQueue.pop();
	}
	cout << endl;
}

void Map::displayMap()
{
    for (int i = 0; i < classMainMap00.size(); i++)
    {
        for (int j = 0; j < classMainMap00.at(i).size(); j++)
        {
            int k = 0;
            int tempInt = -1;
            bool done = false;
            while (k < classMainMap00.at(i).at(j).size() && !done)
            {
                if (classMainMap00.at(i).at(j).at(k).size() > 0)
                {
                    tempInt = k;
                    done = true;
                }
                k++;
            }
            cout << tempInt << "\t";
        }
        cout << endl;
    }
    //cout << endl;
}

void Map::displayElement(grid2d inpCoord)
{
    for (int i = 0; i < classMainMap00.at(inpCoord.y).at(inpCoord.x).size(); i++)
    {
        cout << i << " ";
        //cout << classMainMap00.at(inpCoord.y).at(inpCoord.x).at(i).size() << " ";
        display1DVec(classMainMap00.at(inpCoord.y).at(inpCoord.x).at(i), " ");
    }
    //cout << endl;
}


void Map::clearIDs(int inpType, vector<grid2d>inpPositions)
{
    for (int i = 0; i < inpPositions.size(); i++)
    {
        classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType).clear();
    }
}


void Map::clearIDsWholeMap(int inpType, vector<grid2d>inpPositions)
{
    for (int i = 0; i < inpPositions.size(); i++)
    {
        for (int j = 0; j < inpPositions.size(); j++)
        {
            classMainMap00.at(i).at(j).at(inpType).clear();
        }
    }
}

Map Map::generateBasicCrudeMap(grid2dDim inpDim, grid2d inpStartPos, vector<grid2d>inpEndPoss, double inpWallToAreaRatio, double inpEnemyToAreaRatio)
{
    const int TEMPWALLTYPE = 0;
    const int TEMPENEMYTYPE = 1;

    Map tempGridMaze;
    vector <grid2d> tempLocs;
    grid2d tempLoc;
    //tempGridMaze = new Map();
    tempGridMaze.initMap(inpDim, 1);
    for (int i = 0; i < inpDim.width; i++)
    {
        tempLocs.clear();
        tempLoc = {i, 0};
        tempLocs.push_back(tempLoc);

        //if not end position or start positions
        if (searchVector(inpEndPoss, tempLoc) == -1 && !(tempLoc == inpStartPos) )
            tempGridMaze.addGenericElement(TEMPWALLTYPE, 0, tempLocs);
    }
    tempLocs.clear();

    for (int i = 0; i < inpDim.width; i++)
    {
        tempLocs.clear();
        tempLoc = {i, inpDim.height - 1};
        tempLocs.push_back(tempLoc);

        //if not end position or start positions
        if (searchVector(inpEndPoss, tempLoc) == -1 && !(tempLoc == inpStartPos) )
            tempGridMaze.addGenericElement(TEMPWALLTYPE, 0, tempLocs);
    }
    tempLocs.clear();

    for (int i = 1; i < inpDim.height - 1; i++)
    {
        tempLocs.clear();
        tempLoc = {0, i};
        tempLocs.push_back(tempLoc);

        //if not end position or start positions
        if (searchVector(inpEndPoss, tempLoc) == -1 && !(tempLoc == inpStartPos) )
            tempGridMaze.addGenericElement(TEMPWALLTYPE, 0, tempLocs);
    }
    tempLocs.clear();

    for (int i = 1; i < inpDim.height - 1; i++)
    {
        tempLocs.clear();
        tempLoc = {inpDim.width - 1, i};
        tempLocs.push_back(tempLoc);

        //if not end position or start positions
        if (searchVector(inpEndPoss, tempLoc) == -1 && !(tempLoc == inpStartPos) )
            tempGridMaze.addGenericElement(TEMPWALLTYPE, 0, tempLocs);
    }
    tempLocs.clear();

    int gridArea = inpDim.width * inpDim.height;
    int wallCount = gridArea * inpWallToAreaRatio;
    int enemyCount = gridArea * inpEnemyToAreaRatio;

    vector <grid2d> safeArea;

    safeArea = inpEndPoss;
    safeArea.push_back(inpStartPos);

    int safeAreaLength = safeArea.size();
    for (int i = 0; i < safeAreaLength; i++)
    {
        vector <grid2d> tempLocVec;
        expandGridSquare(safeArea.at(i), inpDim, tempLocVec);
        unionVectors(safeArea, tempLocVec, safeArea);
    }

    for (int i = wallCount; i > 0; i--)
    {
        tempLocs.clear();
        tempLoc = {rand() % inpDim.width, rand() % inpDim.height};
        tempLocs.push_back(tempLoc);

        //if not end position or start positions
        if (searchVector(safeArea, tempLoc) == -1 && !(tempLoc == inpStartPos ))
            tempGridMaze.addGenericElement(TEMPWALLTYPE, 0, tempLocs);
    }
    tempLocs.clear();

    for (int i = enemyCount; i > 0; i--)
    {
        tempLocs.clear();
        tempLoc = {rand() % inpDim.width, rand() % inpDim.height};
        tempLocs.push_back(tempLoc);

        //if not end position or start positions
        if (searchVector(safeArea, tempLoc) == -1 && !(tempLoc == inpStartPos ))
            tempGridMaze.addGenericElement(TEMPENEMYTYPE, 0, tempLocs);
    }
    tempLocs.clear();

    return tempGridMaze;
}

int Map::getBasicCrudeElement(grid2d inpCoord)
{
    int tempElement;
    int retElement;

    tempElement = (int)classMainMap00.at(inpCoord.y).at(inpCoord.x).at(0).at(0);
    retElement = tempElement;

    return retElement;
}


void Map::expandGridSquare(grid2d inpCoord, grid2dDim inpDim, vector < grid2d > &retExpansion)
{
    vector < grid2d > tempVec;
	for (int i = inpCoord.y - 1; i <= inpCoord.y + 1; i++)
	{
		for (int j = inpCoord.x - 1; j <= inpCoord.x + 1; j++)
		{
			if (!(i == inpCoord.y && j == inpCoord.x)) //this makes it so it doesn't include itself
			{
                if (i == inpCoord.y || j == inpCoord.x) //this makes it so that it only moves up and down - without out diagonal is valid
                {
                    if (i >= 0 && i < inpDim.height)
                    {
                        if (j >= 0 && j < inpDim.width)
                        {
                            //cout << "push back" << endl;
                            tempVec.push_back({j, i});
                        }
                    }
                }
			}
		}
	}
	retExpansion = tempVec;
}

template<class T>
void Map::unionVectors(vector <T> frontVec, vector <T> backVec, vector <T> &retVec)
{
    for (int i = 0; i < backVec.size(); i++)
    {
        if (searchVector(frontVec, backVec.at(i)) == -1)
            frontVec.push_back(backVec.at(i));
    }

    retVec = frontVec;
}

