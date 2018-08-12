#include "geomerty.h"

//scalar product of vectors
double dot(point v1, point v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

//vectors subtraction
point subtract(point v1, point v2){
    return {v1.x-v2.x, v1.y - v2.y, v1.z - v2.z};
}

//vectors addition
point add(point v1, point v2){
    return {v1.x+v2.x, v1.y + v2.y, v1.z + v2.z};
}

//vectors multiplication
point multiply(double k, point v){
    return {v.x*k, v.y*k, v.z*k};
}


//get maximal value
double max(double a, double b){
    if (a>b) return a;
    else return b;
}

//get maximal value from array
double multy_max(double* a, int n){
    double max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > max) max = a[i];
    }
    return max;
}

//get minimal value from array
double multy_min(double* a, int n){
    double max = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < max) max = a[i];
    }
    return max;
}

//get minimal value
double min(double a, double b){
    if (a<b) return a;
    else return b;
}

//vector length
double length(point v1){
    return sqrt(dot(v1,v1));
}

//calculate the coordinates of a normal to triangle
point get_normal(Triangle triangle){
    point v1 = subtract(triangle.B, triangle.A);
    point v2 = subtract(triangle.C, triangle.A);
    float x = v1.y*v2.z - v1.z*v2.y;
    float y = v1.z*v2.x - v1.x*v2.z;
    float z = v1.x*v2.y - v1.y*v2.x;
    return {x, y, z};
}

//vector normalization
void normalize(point * n){
    float vec_length = length(*n);
    n->x = n->x/vec_length;
    n->y = n->y/vec_length;
    n->z = n->z/vec_length;
}


bool is_inside(point min, point max, point v){
    return (v.x >= min.x && v.x <= max.x &&
            v.y >= min.y && v.y <= max.y &&
            v.z >= min.z && v.z <= max.z);
}