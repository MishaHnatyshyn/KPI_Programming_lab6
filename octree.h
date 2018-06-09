#include <iostream>
#include <vector>
#include "geomerty.h"


struct Octree{
    int poligons_count;
    Octree * children[8];
    point minPoint;
    point maxPoint;
    bool flag;
    ~Octree();
    std::vector<Triangle*> poligons;
//    std::vector<int> poligons[10];
    Octree(){
        poligons_count = 0;
        flag = false;
//        point minPoint = nullptr;
//        point maxPoint = nullptr;
        for (int i = 0; i < 8; ++i) {
            children[i] = nullptr;
        }
//        for (int i = 0; i < 300; ++i) {
//            poligons[i] = nullptr;
//        }
//        *children = nullptr;
    }

};

Octree * add_node(point minPoint, point maxPoint, Octree *MyTree);
