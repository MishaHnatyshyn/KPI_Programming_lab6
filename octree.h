#include <iostream>
#include <vector>
#include "geomerty.h"


struct Octree{
    Octree * children[8];
    point minPoint;
    point maxPoint;
    bool flag;
    std::vector<int> poligons;

};

Octree * add_node(point minPoint, point maxPoint, Octree *MyTree);
