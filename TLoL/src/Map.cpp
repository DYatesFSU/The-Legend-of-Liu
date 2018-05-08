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
	vector < vector < int > > tempElements;
	vector < vector < vector < int > > > tempElementsList;
	classMapDimensions = inpDim;

	for (int i = 0; i < elementVariety; i++)
	{
		tempElements.push_back(vector < int > ());
	}

	for (int i = 0; i < classMapDimensions.width; i++)
	{
		tempElementsList.push_back(tempElements);
	}

	for (int i = 0; i < classMapDimensions.height; i++)
	{
		classMainMap00.push_back(tempElementsList);
	}
}

gridElements Map::getMapElement(grid2d inpCoord)
{
	return classMainMap.at(inpCoord.y).at(inpCoord.x);
}

void Map::getMapElementGeneric(grid2d inpCoord, vector < vector < int > > &retElement)
{
    vector < vector < int > > tempElement;
    tempElement = classMainMap00.at(inpCoord.y).at(inpCoord.x);
    retElement = tempElement;
}

bool Map::isGraphCollisionGeneric(vector < grid2d > inpPositions, int inpID, int inpType, int cmpType)
{
    int count00 = 0;
	bool done = false;

	if (inpType != cmpType)
	{
		while (count00 < inpPositions.size() && !done)
		{
			if (classMainMap00.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).at(cmpType).size() > 0)
			{
				done = true;
			}
			count00++;
		}
	}
	else
	{
		int tempInt;
		while (count00 < inpPositions.size() && !done)
		{
			tempInt = classMainMap00.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).at(cmpType).size();
			if (tempInt > 0)
			{
				if (searchVector(classMainMap00.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).at(cmpType), inpID) != -1)
				{
					if (tempInt > 1)
					{
						done = true;
					}
				}
			}
			count00++;
		}
	}
	return done;
}

void Map::addGenericElement(int inpID, int inpType, vector < grid2d > inpPositions)
{
    vector < grid2d > tempGraphCoords;
    //getRealToGraphCoords(inpPos, inpDimensions, cart2dDim inpWorldDim, std::vector < grid2d > &retGraphCoords);
    for (int i = 0; i < inpPositions.size(); i++)
    {
        if (searchVector(classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType), inpID) == -1)
            classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType).push_back(inpID);
    }
}

void Map::removeGenericElement(int inpID, int inpType, vector<grid2d>inpPositions)
{
    int tempLocIndex;
    for (int i = 0; i < inpPositions.size(); i++)
    {
        tempLocIndex = searchVector(classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType), inpID);
        if (tempLocIndex != -1)
            classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType).erase(classMainMap00.at(inpPositions.at(i).y).at(inpPositions.at(i).x).at(inpType).begin() + tempLocIndex);
    }
}

void Map::updateGenericElement(int inpID, int inpType, vector < grid2d > oldPositions, vector < grid2d > newPositions)
{
    removeGenericElement(inpID, inpType, oldPositions);
    addGenericElement(inpID, inpType, newPositions);
}

bool Map::isGraphWallCollision(vector < grid2d > inpPositions, int inpID)
{
	int count00 = 0;
	bool done = false;

	if (inpID == -1)
	{
		while (count00 < inpPositions.size() && !done)
		{
			if (classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).walls.size() > 0)
			{
				done = true;
			}
			count00++;
		}
	}
	else
	{
		int tempInt;
		while (count00 < inpPositions.size() && !done)
		{
			tempInt = classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).walls.size();
			if (tempInt > 0)
			{
				if (searchVector(classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).walls, inpID) != -1)
				{
					if (tempInt > 1)
					{
						done = true;
					}
				}
			}
			count00++;
		}
	}
	return done;
}
bool Map::isGraphEnemyCollision(vector < grid2d > inpPositions, int inpID)
{
	int count00 = 0;
	bool done = false;

	if (inpID == -1)
	{
		while (count00 < inpPositions.size() && !done)
		{
			if (classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).enemies.size() > 0)
			{
				done = true;
			}
			count00++;
		}
	}
	else
	{
		int tempInt;
		while (count00 < inpPositions.size() && !done)
		{
			tempInt = classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).enemies.size();
			if (tempInt > 0)
			{
				if (searchVector(classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).enemies, inpID) != -1)
				{
					if (tempInt > 1)
					{
						done = true;
					}
				}
			}
			count00++;
		}
	}
	return done;
}
bool Map::isGraphPlayerCollision(vector < grid2d > inpPositions, int inpID)
{
	int count00 = 0;
	bool done = false;

	if (inpID == -1)
	{
		while (count00 < inpPositions.size() && !done)
		{
			if (classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).players.size() > 0)
			{
				done = true;
			}
			count00++;
		}
	}
	else
	{
		int tempInt;
		while (count00 < inpPositions.size() && !done)
		{
			tempInt = classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).players.size();
			if (tempInt > 0)
			{
				if (searchVector(classMainMap.at(inpPositions.at(count00).y).at(inpPositions.at(count00).x).players, inpID) != -1)
				{
					if (tempInt > 1)
					{
						done = true;
					}
				}
			}
			count00++;
		}
	}
	return done;
}

void Map::addWall(int inpID, vector < grid2d > inpPositions)
{
    vector < grid2d > tempGraphCoords;
    //getRealToGraphCoords(inpPos, inpDimensions, cart2dDim inpWorldDim, std::vector < grid2d > &retGraphCoords);
    for (int i = 0; i < inpPositions.size(); i++)
    {
        if (searchVector(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).walls, inpID) == -1)
            classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).walls.push_back(inpID);
    }
}

void Map::addEnemy(int inpID, vector < grid2d > inpPositions)
{
    for (int i = 0; i < inpPositions.size(); i++)
    {
        if (searchVector(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).enemies, inpID) == -1)
            classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).enemies.push_back(inpID);
    }
}

void Map::addPlayer(int inpID, vector < grid2d > inpPositions)
{
    for (int i = 0; i < inpPositions.size(); i++)
    {
        if (searchVector(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).players, inpID) == -1)
            classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).players.push_back(inpID);
    }
}

void Map::removeWall(int inpID, vector<grid2d>inpPositions)
{
    int tempLocIndex;
    for (int i = 0; i < inpPositions.size(); i++)
    {
        tempLocIndex = searchVector(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).walls, inpID);
        if (tempLocIndex != -1)
            classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).walls.erase(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).walls.begin() + tempLocIndex);
    }
}

void Map::removeEnemy(int inpID, vector<grid2d>inpPositions)
{
    int tempLocIndex;
    for (int i = 0; i < inpPositions.size(); i++)
    {
        tempLocIndex = searchVector(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).enemies, inpID);
        if (tempLocIndex != -1)
            classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).enemies.erase(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).enemies.begin() + tempLocIndex);
    }
}

void Map::removePlayer(int inpID, vector<grid2d>inpPositions)
{
    int tempLocIndex;
    for (int i = 0; i < inpPositions.size(); i++)
    {
        tempLocIndex = searchVector(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).players, inpID);
        if (tempLocIndex != -1)
            classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).players.erase(classMainMap.at(inpPositions.at(i).y).at(inpPositions.at(i).x).players.begin() + tempLocIndex);
    }
}

void Map::updateWall(int inpID, vector < grid2d > oldPositions, vector < grid2d > newPositions)
{
    removeWall(inpID, oldPositions);
    addWall(inpID, newPositions);
}

void Map::updateEnemy(int inpID, vector < grid2d > oldPositions, vector < grid2d > newPositions)
{
    removeEnemy(inpID, oldPositions);
    addEnemy(inpID, newPositions);
}

void Map::updatePlayer(int inpID, vector < grid2d > oldPositions, vector < grid2d > newPositions)
{
    removePlayer(inpID, oldPositions);
    addPlayer(inpID, newPositions);
}


void Map::searchDijkstras(grid2d startPos, vector<grid2d>endPos, queue<grid2d>& retSolution)
{
    queue < grid2d > tempSolution;
    vector < int > tempBlockers;
    tempBlockers.push_back(0);
    basicDijkstrasGeneric(classMainMap00, startPos, endPos, tempBlockers, tempSolution);
    retSolution = tempSolution;
}

void Map::searchAStar(grid2d startPos, vector<grid2d>endPos, queue<grid2d>& retSolution)
{
    queue < grid2d > tempSolution;
    vector < int > tempBlockers;
    tempBlockers.push_back(0);
    basicAStarGeneric(classMainMap00, startPos, endPos, tempBlockers, tempSolution);
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


void Map::basicDijkstras(vector< vector < gridElements > > inpGraph, grid2d startPos, vector<grid2d>endPos, queue<grid2d>& retSolution)
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
			expandMapLoc(inpGraph, topPriorObj.path.back(), tempExpansion);
			for (int i = 0; i < tempExpansion.size(); i++)
			{
				//check if not wall
				//if (getMapElement(inpGraph, tempExpansion.at(i).x, tempExpansion.at(i).y) != GWALL)
				if (inpGraph.at(tempExpansion.at(i).y).at(tempExpansion.at(i).x).walls.size() > 0)
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

void Map::basicAStar(vector< vector < gridElements > >inpGraph, grid2d startPos, vector<grid2d>endPos, queue<grid2d>& retSolution)
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
			expandMapLoc(inpGraph, topPriorObj.path.back(), tempExpansion);
			for (int i = 0; i < tempExpansion.size(); i++)
			{
				//check if not wall
				//if (getMapElement(inpGraph, tempExpansion.at(i).x, tempExpansion.at(i).y) != GWALL)
				if (inpGraph.at(tempExpansion.at(i).y).at(tempExpansion.at(i).x).walls.size() > 0)
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

void Map::expandMapLoc(vector< vector < gridElements > >inpGraph, grid2d inpCoord, vector<grid2d>& retExpansion)
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

void Map::basicDijkstrasGeneric(vector < vector < vector < vector < int > > > > inpGraph, grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution)
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

void Map::basicAStarGeneric(vector < vector < vector < vector < int > > > > inpGraph, grid2d startPos, vector < grid2d > endPos, vector < int > blockList, queue < grid2d > &retSolution)
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

void Map::expandMapLocGeneric(vector < vector < vector < vector < int > > > > inpGraph, grid2d inpCoord, vector < grid2d > &retExpansion)
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

bool Map::doesIntersect1DList2DList(vector < vector < int > > inp2DList, vector < int > inp1DList)
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
