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
void add_node(point minPoint, point maxPoint, Octree *&MyTree ) {
    if (NULL == MyTree) {
        MyTree = new Octree;
        MyTree->minPoint.x = minPoint.x;
        MyTree->minPoint.y = minPoint.y;
        MyTree->minPoint.z = minPoint.z;
        MyTree->maxPoint.x = maxPoint.x;
        MyTree->maxPoint.y = maxPoint.y;
        MyTree->maxPoint.z = maxPoint.z;
        for (int i = 0; i < 8; i++) {
            MyTree->children[i] = NULL;
        }
    }
    for (int k = 0; k < 8; k++) {
        if (MyTree->children[k] != NULL) {
            add_node(minPoint, maxPoint, MyTree->children[k]);
        } else {
            MyTree->children[k] = new Octree;
            for (int i = 0; i < 8; i++) {
                MyTree->children[k]->children[i] = NULL;
                MyTree->children[k]->minPoint.x = (k - 1) * (MyTree->minPoint.x + maxPoint.x) / 8;;
                MyTree->children[k]->minPoint.y = (k - 1) * (MyTree->minPoint.y + maxPoint.y) / 8;;
                MyTree->children[k]->minPoint.z = (k - 1) * (MyTree->minPoint.z + maxPoint.z) / 8;;
                MyTree->children[k]->maxPoint.x = k * (MyTree->minPoint.x + maxPoint.x) / 8;
                MyTree->children[k]->maxPoint.y = k * (MyTree->minPoint.y + maxPoint.y) / 8;;
                MyTree->children[k]->maxPoint.z = k * (MyTree->minPoint.z + maxPoint.z) / 8;;
            }
        }
    }
}
int main() {
   Octree *Tree = NULL;
    return 0;
}
