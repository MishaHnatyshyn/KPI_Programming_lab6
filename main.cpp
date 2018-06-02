#include <iostream>
#include "bmp.h"
#include <vector>
#include <omp.h>

using namespace std;

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

struct sphere{
    point centre;
    double radius;
    PIXELDATA color;
    sphere(float x, float y, float z, double R, int r, int g, int b){
        centre.x = x;
        centre.y = y;
        centre.z = z;
        radius = R;
        color.r = r;
        color.g = g;
        color.b = b;
    }
};

struct canvas{
    int width;
    int height;
};

vector<vector<PIXELDATA>> putPixel(int x_prev, int y_prev, PIXELDATA color, canvas viewPort, vector<vector<PIXELDATA>> map){
    int x = viewPort.width/2 + x_prev;
    int y = viewPort.height/2 - y_prev - 1;
    if (x < 0 || x >= viewPort.width || y < 0 || y >= viewPort.height) {
        return map;
    }
    map[y][x] = color;
    return map;
}

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

PIXELDATA clamp(point v){
    return {min(255.0, max(0.0,v.x)), min(255, max(0.0,v.y)), min(255, max(0.0,v.z))};
}

double length(point v1){
    return sqrt(dot(v1,v1));
}

point CanvasToViewport(int x, int y, int d,canvas canv, int viewport_size){
    point res(((double)x*viewport_size)/(double)canv.width, ((double)y*viewport_size)/(double)canv.height, d);
    return res;
}

vector<double> IntersectRaySphere(point O, point D, sphere obj){
    vector<double> res(2);
    point C = obj.centre;
    double r = obj.radius;
    point oc = subtract(O,obj.centre);
    double k1 = dot(D,D);
    double k2 = 2 * dot(oc,D);
    double k3 = dot(oc,oc) - r*r;
    double discriminant = k2*k2 - 4*k1*k3;
    if (discriminant < 0) {
        res[0] = 100000001000;
        res[1] = 100000001000;
        return res;
    }

    double t1 = ((-1)*k2 + sqrt(discriminant)) / (2*k1);
    double t2 = ((-1)*k2 - sqrt(discriminant)) / (2*k1);
    res[0] = t1;
    res[1] = t2;
    return res;
}

double ComputeLighting(point O, point N, vector<light> lights){
    double intensity = 0;
    double length_n = length(N);
    for (int i = 0; i < lights.size(); ++i) {
        light curr_light = lights[i];
        if(curr_light.type == "ambient"){
            intensity += curr_light.intensity;
        } else{
            point vec_l;
            if(curr_light.type == "point"){
                vec_l = subtract(curr_light.pos, O);
            } else{
                vec_l = curr_light.pos;
            }
            double n_dot_l = dot(N, vec_l);
            if (n_dot_l > 0){
                intensity += curr_light.intensity*n_dot_l/(length_n * length(vec_l));
            }
        }
    }
    return intensity;
}


PIXELDATA TraceRay(point O, point D, int t_min, int t_max, vector<sphere> obj, vector<light> lights){
    PIXELDATA res;
    res.r = 255;
    res.g = 255;
    res.b = 255;
    double closest_t = 100000001;
    sphere* closest_sphere = nullptr;
    for (int i = 0; i < obj.size(); ++i) {
        vector<double> t = IntersectRaySphere(O, D, obj[i]);
        if (t[0] > t_min && t[0] < t_max && t[0] < closest_t){
            closest_t = t[0];
            closest_sphere = &obj[i];
        }
        if (t[1] > t_min && t[1] < t_max && t[1] < closest_t){
            closest_t = t[1];
            closest_sphere = &obj[i];
        }
    }
    if (closest_sphere == nullptr){
        return res;
    }

    point point1 = add(O, multiply(closest_t, D));
    point normal = subtract(point1, closest_sphere->centre);
    normal = multiply(1.0/length(normal), normal);
    double i = ComputeLighting(point1,normal,lights);
    res.r = closest_sphere->color.r * i;
    res.g = closest_sphere->color.g * i;
    res.b = closest_sphere->color.b * i;

    return res;
}


int main(){
    canvas canv;
    canv.width = 200;
    canv.height = 200;
    int viewport_size = 1;
    int projection_plane_z = 1;
    point camera_position(0,0,0);
    vector<sphere> spheres;
    vector<light> lights;
    vector<PIXELDATA> row(canv.width);
    vector<vector<PIXELDATA>> map;
    for (int i = 0; i < canv.height; ++i) {
        map.push_back(row);
    }

    //omp_set_num_threads(2);
    spheres.push_back(sphere(0, -1, 3 , 1, 255, 0, 0));
    spheres.push_back(sphere(0, 0, 3 , 1, 0, 0, 255));
    spheres.push_back(sphere(-2, 0, 4 , 1, 0, 255, 0));
    lights.push_back(light("ambient", 0.2));
    lights.push_back(light("point", 0.6, 2, 1, 0));
    lights.push_back(light("directional", 0.2, 1, 4, 4));


    #pragma omp parallel private(x, y)
    #pragma omp for collapse(2) schedule(dynamic, CHUNK)

    for (int x = -canv.width/2; x < canv.width/2; x++) {
        for (int y = -canv.height/2; y < canv.height/2; y++) {
            point direction = CanvasToViewport(x,y,projection_plane_z,canv,viewport_size);
            PIXELDATA color = TraceRay(camera_position, direction, 1, 100000001, spheres, lights);
            map = putPixel(x,y,color,canv,map);

        }
    cout << x << endl;
    }



    create("res.bmp", canv.width, canv.height, map);
    return 0;
}
