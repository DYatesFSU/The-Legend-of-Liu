#include "Wall.h"

using namespace std;

Wall::Wall()
{
    //ctor
}

Wall::~Wall()
{
    //dtor
}

void Wall::setPosition(cartesian2d inpPos)
{
    objectPosition = inpPos;
}

cartesian2d Wall::getPosition()
{
    return objectPosition;
}

cart2dDim Wall::getObjectDimensions()
{
    return objectDimensions;
}

void Wall::getCurrGridPos(vector<grid2d>& retPos)
{
    retPos = classCurrentGridCoords;
}

void Wall::setCurrGridPos(vector<grid2d>inpPos)
{
    classCurrentGridCoords = inpPos;
}
