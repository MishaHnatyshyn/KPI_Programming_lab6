#include "octree.h"

Octree * add_node(point minPoint, point maxPoint, Octree *MyTree ) {

    //new tree crating

    if (NULL == MyTree) {
        MyTree = new Octree();
        MyTree->flag = false;
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
            Octree* temp = new Octree();
            MyTree->children[k] = temp;
            MyTree->children[k]->flag = false;

            for (int i = 0; i < 8; i++) {
                MyTree->children[k]->children[i] = NULL;
            }

        }
    }
    float half_size = (fabsf(MyTree->minPoint.x) + fabsf(MyTree->maxPoint.x))/2;
    float half_size_x = (MyTree->minPoint.x + fabsf(MyTree->maxPoint.x))/2;
    float half_size_y = (MyTree->minPoint.y + fabsf(MyTree->maxPoint.y))/2;
    float half_size_z = (MyTree->minPoint.z + fabsf(MyTree->maxPoint.z))/2;

    MyTree->children[0]->minPoint.x = MyTree->minPoint.x;
    MyTree->children[0]->minPoint.y = MyTree->minPoint.y;
    MyTree->children[0]->minPoint.z = MyTree->minPoint.z;
    MyTree->children[0]->maxPoint.x = half_size_x;
    MyTree->children[0]->maxPoint.y = half_size_y;
    MyTree->children[0]->maxPoint.z = half_size_z;

    Octree * f = MyTree->children[0];

    //calculate the coordinates of the vertices of the children

    MyTree->children[1]->minPoint.x = f->minPoint.x;
    MyTree->children[1]->minPoint.y = f->minPoint.y;
    MyTree->children[1]->minPoint.z = f->minPoint.z + half_size;
    MyTree->children[1]->maxPoint.x = f->maxPoint.x;
    MyTree->children[1]->maxPoint.y = f->maxPoint.y;
    MyTree->children[1]->maxPoint.z = f->maxPoint.z + half_size;

    MyTree->children[3]->minPoint.x = f->minPoint.x + half_size;
    MyTree->children[3]->minPoint.y = f->minPoint.y;
    MyTree->children[3]->minPoint.z = f->minPoint.z + half_size;
    MyTree->children[3]->maxPoint.x = f->maxPoint.x + half_size;
    MyTree->children[3]->maxPoint.y = f->maxPoint.y;
    MyTree->children[3]->maxPoint.z = f->maxPoint.z + half_size;

    MyTree->children[2]->minPoint.x = f->minPoint.x + half_size;
    MyTree->children[2]->minPoint.y = f->minPoint.y;
    MyTree->children[2]->minPoint.z = f->minPoint.z;
    MyTree->children[2]->maxPoint.x = f->maxPoint.x + half_size;
    MyTree->children[2]->maxPoint.y = f->maxPoint.y;;
    MyTree->children[2]->maxPoint.z = f->maxPoint.z;

    MyTree->children[4]->minPoint.x = f->minPoint.x;
    MyTree->children[4]->minPoint.y = f->minPoint.y + half_size;
    MyTree->children[4]->minPoint.z = f->minPoint.z;
    MyTree->children[4]->maxPoint.x = f->maxPoint.x;
    MyTree->children[4]->maxPoint.y = MyTree->maxPoint.y;
    MyTree->children[4]->maxPoint.z = f->maxPoint.z;

    MyTree->children[5]->minPoint.x = f->minPoint.x;
    MyTree->children[5]->minPoint.y = f->minPoint.y + half_size;
    MyTree->children[5]->minPoint.z = f->minPoint.z + half_size;
    MyTree->children[5]->maxPoint.x = f->maxPoint.x;
    MyTree->children[5]->maxPoint.y = MyTree->maxPoint.y;
    MyTree->children[5]->maxPoint.z = MyTree->children[1]->maxPoint.z;


    MyTree->children[7]->minPoint.x = MyTree->children[0]->maxPoint.x;
    MyTree->children[7]->minPoint.y = MyTree->children[0]->maxPoint.y;
    MyTree->children[7]->minPoint.z = MyTree->children[0]->maxPoint.z;
    MyTree->children[7]->maxPoint.x = MyTree->children[3]->maxPoint.x;
    MyTree->children[7]->maxPoint.y = MyTree->maxPoint.y;
    MyTree->children[7]->maxPoint.z = MyTree->children[3]->maxPoint.z;

    MyTree->children[6]->minPoint.x = f->minPoint.x + half_size;
    MyTree->children[6]->minPoint.y = f->minPoint.y + half_size;
    MyTree->children[6]->minPoint.z = f->minPoint.z;
    MyTree->children[6]->maxPoint.x = MyTree->maxPoint.x;
    MyTree->children[6]->maxPoint.y = MyTree->maxPoint.y;
    MyTree->children[6]->maxPoint.z = f->maxPoint.z;


    return MyTree;
}

Octree::~Octree() {

}
