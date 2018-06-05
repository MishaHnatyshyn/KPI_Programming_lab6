#include <iostream>

struct point {
    float x;
    float y;
    float z;
};

struct Octree{
    Octree * children[8];
    point minPoint;
    point maxPoint;
};

void add_node(point minPoint, point maxPoint, Octree *&MyTree);