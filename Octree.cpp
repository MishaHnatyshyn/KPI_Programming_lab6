#include <iostream>
struct point {
    float x;
    float y;
    float z;
};
struct Octree{
    Octree *child1;
    Octree *child2;
    Octree *child3;
    Octree *child4;
    Octree *child5;
    Octree *child6;
    Octree *child7;
    Octree *child8;
    Point minPoint;
    Point maxPoint;
};
void add_node(point minPoint, point maxPoint, Octree *&MyTree )
{
    int k;
    if (NULL == MyTree)
    {
        MyTree = new Octree;
        MyTree->minPoint.x = minPoint.x;
        MyTree->minPoint.y = minPoint.y;
        MyTree->minPoint.z = minPoint.z;
        MyTree->maxPoint.x = maxPoint.x;
        MyTree->maxPoint.y = maxPoint.y;
        MyTree->maxPoint.z = maxPoint.z;

        MyTree->child1 = MyTree->child2 = MyTree->child3 = MyTree->child4 = MyTree->child5 = MyTree->child6 = MyTree->child7 = MyTree->child8 = NULL;
    }
    float minX = (k-1)*(MyTree->minPoint.x + maxPoint.x)/8;
    float minY = (k-1)*(MyTree->minPoint.y + maxPoint.y)/8;
    float minZ = (k-1)*(MyTree->minPoint.z + maxPoint.z)/8;
    float maxX = k*(MyTree->minPoint.x + maxPoint.x)/8;
    float maxY = k*(MyTree->minPoint.y + maxPoint.y)/8;
    float maxZ = k*(MyTree->minPoint.z + maxPoint.z)/8;
    for (k = 1; k < 9; k ++){
        switch(k){
            case 1:
                if (MyTree->child1 != NULL)
                  add_node(minPoint, maxPoint, MyTree->child1);
                else{
                  MyTree->child1 = new Octree;
                  MyTree->child1->child1 = MyTree->child1->child2 = MyTree->child1->child3 = MyTree->child1->child4 = MyTree->child1->child5 = MyTree->child1->child6 = MyTree->child1->child7 = MyTree->child1->child8 = NULL;
                  MyTree->child1->minPoint.x = minX;
                  MyTree->child1->minPoint.y = minY;
                  MyTree->child1->minPoint.z = minZ;
                  MyTree->child1->maxPoint.x = maxX;
                  MyTree->child1->maxPoint.y = maxY;
                  MyTree->child1->maxPoint.z = maxZ;
                }
            case 2:
                if (MyTree->child2 != NULL)
                    add_node(minPoint, maxPoint, MyTree->child1);
                else{
                    MyTree->child2 = new Octree;
                    MyTree->child2->child1 = MyTree->child2->child2 = MyTree->child2->child3 = MyTree->child2->child4 = MyTree->child2->child5 = MyTree->child2->child6 = MyTree->child2->child7 = MyTree->child2->child8 = NULL;
                    MyTree->child2->minPoint.x = minX;
                    MyTree->child2->minPoint.y = minY;
                    MyTree->child2->minPoint.z = minZ;
                    MyTree->child2->maxPoint.x = maxX;
                    MyTree->child2->maxPoint.y = maxY;
                    MyTree->child2->maxPoint.z = maxZ;
                }
            case 3:
                if (MyTree->child3 != NULL)
                    add_node(minPoint, maxPoint, MyTree->child1);
                else{
                    MyTree->child1 = new Octree;
                    MyTree->child3->child1 = MyTree->child3->child2 = MyTree->child3->child3 = MyTree->child3->child4 = MyTree->child3->child5 = MyTree->child3->child6 = MyTree->child3->child7 = MyTree->child3->child8 = NULL;
                    MyTree->child3->minPoint.x = minX;
                    MyTree->child3->minPoint.y = minY;
                    MyTree->child3->minPoint.z = minZ;
                    MyTree->child3->maxPoint.x = maxX;
                    MyTree->child3->maxPoint.y = maxY;
                    MyTree->child3->maxPoint.z = maxZ;
                }
            case 4:
                if (MyTree->child4 != NULL)
                    add_node(minPoint, maxPoint, MyTree->child1);
                else{
                    MyTree->child4 = new Octree;
                    MyTree->child4->child1 = MyTree->child4->child2 = MyTree->child4->child3 = MyTree->child4->child4 = MyTree->child4->child5 = MyTree->child4->child6 = MyTree->child4->child7 = MyTree->child4->child8 = NULL;
                    MyTree->child4->minPoint.x = minX;
                    MyTree->child4->minPoint.y = minY;
                    MyTree->child4->minPoint.z = minZ;
                    MyTree->child4->maxPoint.x = maxX;
                    MyTree->child4->maxPoint.y = maxY;
                    MyTree->child4->maxPoint.z = maxZ;
                }
            case 5:
                if (MyTree->child5 != NULL)
                    add_node(minPoint, maxPoint, MyTree->child1);
                else{
                    MyTree->child5 = new Octree;
                    MyTree->child5->child1 = MyTree->child5->child2 = MyTree->child5->child3 = MyTree->child5->child4 = MyTree->child5->child5 = MyTree->child5->child6 = MyTree->child5->child7 = MyTree->child5->child8 = NULL;
                    MyTree->child5->minPoint.x = minX;
                    MyTree->child5->minPoint.y = minY;
                    MyTree->child5->minPoint.z = minZ;
                    MyTree->child5->maxPoint.x = maxX;
                    MyTree->child5->maxPoint.y = maxY;
                    MyTree->child5->maxPoint.z = maxZ;
                }
            case 6:
                if (MyTree->child6 != NULL)
                    add_node(minPoint, maxPoint, MyTree->child1);
                else{
                    MyTree->child6 = new Octree;
                    MyTree->child6->child1 = MyTree->child6->child2 = MyTree->child6->child3 = MyTree->child6->child4 = MyTree->child6->child5 = MyTree->child6->child6 = MyTree->child6->child7 = MyTree->child6->child8 = NULL;
                    MyTree->child6->minPoint.x = minX;
                    MyTree->child6->minPoint.y = minY;
                    MyTree->child6->minPoint.z = minZ;
                    MyTree->child6->maxPoint.x = maxX;
                    MyTree->child6->maxPoint.y = maxY;
                    MyTree->child6->maxPoint.z = maxZ;
                }
            case 7:
                if (MyTree->child7 != NULL)
                    add_node(minPoint, maxPoint, MyTree->child1);
                else{
                    MyTree->child7 = new Octree;
                    MyTree->child7->child1 = MyTree->child7->child2 = MyTree->child7->child3 = MyTree->child7->child4 = MyTree->child7->child5 = MyTree->child7->child6 = MyTree->child7->child7 = MyTree->child7->child8 = NULL;
                    MyTree->child7->minPoint.x = minX;
                    MyTree->child7->minPoint.y = minY;
                    MyTree->child7->minPoint.z = minZ;
                    MyTree->child7->maxPoint.x = maxX;
                    MyTree->child7->maxPoint.y = maxY;
                    MyTree->child7->maxPoint.z = maxZ;
                }
            case 8:
                if (MyTree->child8 != NULL)
                    add_node(minPoint, maxPoint, MyTree->child1);
                else{
                    MyTree->child8 = new Octree;
                    MyTree->child8->child1 = MyTree->child8->child2 = MyTree->child8->child3 = MyTree->child8->child4 = MyTree->child8->child5 = MyTree->child8->child6 = MyTree->child8->child7 = MyTree->child8->child8 = NULL;
                    MyTree->child8->minPoint.x = minX;
                    MyTree->child8->minPoint.y = minY;
                    MyTree->child8->minPoint.z = minZ;
                    MyTree->child8->maxPoint.x = maxX;
                    MyTree->child8->maxPoint.y = maxY;
                    MyTree->child8->maxPoint.z = maxZ;
                }

        }

    }

}
int main() {
   Octree *Tree = NULL;
    return 0;
}
