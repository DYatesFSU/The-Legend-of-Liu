#ifndef GLOBALDATASTRUCTURES_H
#define GLOBALDATASTRUCTURES_H

//#include <vector>
#include <queue>

struct cartesian3d
{
    double x;
    double y;
    double z;
};

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

class GlobalDataStructures
{
    public:
        GlobalDataStructures();
        virtual ~GlobalDataStructures();

    protected:

    private:
};

#endif // GLOBALDATASTRUCTURES_H
