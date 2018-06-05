#include "geomerty.h"


double dot(point v1, point v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

point subtract(point v1, point v2){
    return {v1.x-v2.x, v1.y - v2.y, v1.z - v2.z};
}
point add(point v1, point v2){
    return {v1.x+v2.x, v1.y + v2.y, v1.z + v2.z};
}
point multiply(double k, point v){
    return {v.x*k, v.y*k, v.z*k};
}

double max(double a, double b){
    if (a>b) return a;
    else return b;
}

double min(double a, double b){
    if (a<b) return a;
    else return b;
}

double length(point v1){
    return sqrt(dot(v1,v1));
}

point get_normal(Triangle triangle){
    point v1 = subtract(triangle.B, triangle.A);
    point v2 = subtract(triangle.C, triangle.A);
    float x = v1.y*v2.z - v1.z*v2.y;
    float y = v1.z*v2.x - v1.x*v2.z;
    float z = v1.x*v2.y - v1.y*v2.x;
    return {x, y, z};
}

long double ** matrix_multiplication(long double **A, long double **b){
        int m = 3;
        int q = 1;
        int n = 3;

        int N = 3;
        long double **C = new long double *[N];

        for (int i = 0; i < N; i++)
            C[i] = new long double [q];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < q; j++)
            {
                C[i][j] = 0;
                for(int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * b[k][j];
                }
            }

        return C;
    }
