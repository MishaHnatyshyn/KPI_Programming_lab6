#include "objParse.h"

struct Triangle{
    points v0;
    points v1;
    points v2;
};

double dot (points a, points b);
points cross (points a, points b);
int intersect (points RayBegin, points dir, Triangle T);