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

        void setPosition(cartesian2d inpPos);
        cartesian2d getPosition();
        cart2dDim getObjectDimensions();
        void getCurrGridPos(std::vector <grid2d> &retPos);
        void setCurrGridPos(std::vector <grid2d> inpPos);

    protected:

    private:
        std::vector <grid2d> classCurrentGridCoords;

        //for box and graph collisions
        cart2dDim objectDimensions = {.99, .99};
        cartesian2d objectPosition;
};

#endif // WALL_H
