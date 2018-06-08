#include <vector>
#include "intersect3D.h"

#define PI 3.14159265

struct canvas{
    int width;
    int height;
};

struct light{
    string type;
    double intensity;
    point pos;
    light(string t, double i){
        type = t;
        intensity = i;
    }
    light(string t, double i, double x, double y, double z){
        type = t;
        intensity = i;
        pos.x = x;
        pos.y = y;
        pos.z = z;
    }
};


point CanvasToViewport(int, int, int, canvas, int);

point ViewportToCanvas(point a,canvas canv, int viewport_size, point);

double ComputeLighting(point, point, vector<light>);

PIXELDATA TraceRay(point, point, int, int, data, vector<light>, vector<int>);

vector<vector<PIXELDATA>> putPixel(int, int, PIXELDATA, canvas, vector<vector<PIXELDATA>>);

long double ** rotationMatrixZ(double rotation);

long double ** rotationMatrixY(double);

long double ** rotationMatrixX(double);
