#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "intersect3D.h"
using namespace std;

double SMALL_NUM = 0.00000001;

double dot (points a, points b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

points cross (points a, points b){
    points res;
    res.x = a.y*b.z - a.z*b.y;
    res.y = a.z*b.x - a.x*b.z;
    res.z = a.x*b.y - a.y*b.x;
    return res;
}

int intersect (points RayBegin, points dir, Triangle T) {

    points    u, v, n;              // triangle vectors
    points   w0, w;           // ray vectors
    points I1;//intersection point
    double     r, a, b;              // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    //u = T.V1 - T.V0;
    u.x = T.v1.x - T.v0.x;
    u.y = T.v1.y - T.v0.y;
    u.z = T.v1.z - T.v0.z;
    //v = T.V2 - T.V0;
    v.x = T.v2.x - T.v0.x;
    v.y = T.v2.y - T.v0.y;
    v.z = T.v2.z - T.v0.z;

    n = cross(u, v);              // cross product
    if (n.x == 0 && n.y == 0 && n.z == 0)             // triangle is degenerate
        return -1;                  // do not deal with this case

    //w0 = R.P0 - T.V0;
    w0.x = RayBegin.x - T.v0.x;
    w0.y = RayBegin.y - T.v0.y;
    w0.z = RayBegin.z - T.v0.z;


    a = -dot(n,w0);
    b = dot(n,dir);
    if (fabs(b) < SMALL_NUM) {     // ray is  parallel to triangle plane
        if (a == 0)                 // ray lies in triangle plane
            return 2;
        else return 0;              // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                    // ray goes away from triangle
        return 0;                   // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

    I1.x = RayBegin.x + r * dir.x;            // intersect point of ray and plane
    I1.y = RayBegin.y + r * dir.y;            // intersect point of ray and plane
    I1.z = RayBegin.z + r * dir.z;            // intersect point of ray and plane

    // is I inside T?
    double    uu, uv, vv, wu, wv, D;
    uu = dot(u,u);
    uv = dot(u,v);
    vv = dot(v,v);
    //w = I1 - T.V0
    w.x = I1.x - T.v0.x;
    w.y = I1.y - T.v0.y;
    w.z = I1.z - T.v0.z;
    wu = dot(w,u);
    wv = dot(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    double s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)         // I is outside T
        return 0;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return 0;
    return 1;                       // I is in T
}