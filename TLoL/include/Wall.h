//The class for the walls
//Currently nothing just to standardize the name

#ifndef WALL_H
#define WALL_H

#include <GlobalDataStructures.h>


class Wall
{
    public:
        Wall();
        virtual ~Wall();

    protected:

    private:
        std::vector <grid2d> classCurrentGridCoords;
        //This is to test if an object can move in a direction
        //I.E. if these coordinates turn out to be bad, then don't update the current grid coordinates
        std::vector <grid2d> classTestGridCoords;

        //for box and graph collisions
        cart2dDim objectDimensions = {.99, .99};
};

#endif // WALL_H
