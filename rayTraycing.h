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

struct Scene{
    canvas canv;
    int viewport_size;
    int projection_plane_z;
    vector<vector<PIXELDATA>> map;
    point camera_position;
    vector<light> lights;
};


point CanvasToViewport(int, int, int, canvas, int);

point ViewportToCanvas(point a,canvas canv, int viewport_size, point);

double ComputeLighting(point, point, Scene *);

PIXELDATA trace(Octree* node, point ray, Scene * scene, data* object);

void putPixel(int x_prev, int y_prev, PIXELDATA color, Scene * scene);

bool hit(Octree* tree, point ray, Scene* scene, data* object, int x, int y);