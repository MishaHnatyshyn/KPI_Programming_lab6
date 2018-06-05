#include <cmath>

struct point{
    float x;
    float y;
    float z;
    point(float a, float b, float c){
        x = a;
        y = b;
        z = c;
    }
    point(){
        x = 0;
        y = 0;
        z = 0;
    }
};

struct Triangle{
    point A;
    point B;
    point C;
};

point get_normal(Triangle);
double dot(point v1, point v2);
point subtract(point v1, point v2);
point add(point v1, point v2);
point multiply(double k, point v);
double max(double a, double b);
double min(double a, double b);
double length(point v1);
long double ** matrix_multiplication(long double **A, long double **b);
