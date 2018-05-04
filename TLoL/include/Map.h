//This is a class for the Grid that I, Norman, will be implementing
//The purpose of the grid is to help with pathfinding, maze generation, and collision detection

#ifndef MAP_H
#define MAP_H

#include<GlobalDataStructures.h>



class Map
{
    public:
        Map();
        virtual ~Map();

    protected:

    private:

        grid2dDim classMapDimensions;

        /*
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
        */

};

#endif // MAP_H
