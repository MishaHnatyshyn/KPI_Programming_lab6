#include "octree.h"

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
                MyTree->children[k]->minPoint.x = k * (MyTree->minPoint.x + maxPoint.x) / 8 + MyTree->minPoint.x;
                MyTree->children[k]->minPoint.y = k * (MyTree->minPoint.y + maxPoint.y) / 8 + MyTree->minPoint.y;
                MyTree->children[k]->minPoint.z = k * (MyTree->minPoint.z + maxPoint.z) / 8 + MyTree->minPoint.z;
                MyTree->children[k]->maxPoint.x = (k+1) * (MyTree->minPoint.x + maxPoint.x) / 8 + MyTree->minPoint.x;
                MyTree->children[k]->maxPoint.y = (k+1) * (MyTree->minPoint.y + maxPoint.y) / 8 + MyTree->minPoint.y;
                MyTree->children[k]->maxPoint.z = (k+1) * (MyTree->minPoint.z + maxPoint.z) / 8 + MyTree->minPoint.z;
            }
        }
    }
}