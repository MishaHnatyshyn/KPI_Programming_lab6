#include <iostream>
#include <vector>
#include "intersect3D.h"


using namespace std;

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

PIXELDATA clamp(point v){
    return {min(255.0, max(0.0,v.x)), min(255, max(0.0,v.y)), min(255, max(0.0,v.z))};
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

long double ** rotationMatrix(double rotation){
    long double ** rotMatrix = new long double * [3];
    for (int i = 0; i < 3; i++)
        rotMatrix[i] = new long double [3];
    for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
        rotMatrix[i][j] = 0;
        }
    }
    rotMatrix[0][0] = rotMatrix[2][2] = cos ( rotation * PI / 180.0 );
    rotMatrix[0][2] = sin ( rotation * PI / 180.0 );
    rotMatrix[2][0] = - rotMatrix[0][2];
    rotMatrix[1][1] = 1;

    return rotMatrix;
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


PIXELDATA TraceRay(point O, point D, int t_min, int t_max, data object, vector<light> lights){
    PIXELDATA res;
    res.r = 255;
    res.g = 255;
    res.b = 255;
    double closest_t = 100000001;
    data* closest_object = nullptr;
    Triangle curr_triangle;
    Triangle triangle;
    for (int j = 0; j < object.poligons.size(); ++j) {
        int t = intersect(O, D, object.poligons[j]);
        if (t){
            closest_t = t;
            closest_object = &object;
            curr_triangle = object.poligons[j];
            break;
        }
    }
    if (closest_object == nullptr)
        return res;
    point point1 = add(O, multiply(closest_t, D));
    point normal = get_normal(curr_triangle);
    normal = multiply(1.0/length(normal), normal);
    double i = ComputeLighting(point1,normal,lights);
    res.r = closest_object->color.r * i;
    res.g = closest_object->color.g * i;
    res.b = closest_object->color.b * i;

    return res;
}


int main(){
    canvas canv;
    canv.width = 200;
    canv.height = 200;
    int viewport_size = 1;
    int projection_plane_z = 1;
    point camera_position(0,0,-10);
    vector<sphere> spheres;
    vector<light> lights;
    vector<PIXELDATA> row(canv.width);
    vector<vector<PIXELDATA>> map;
    for (int i = 0; i < canv.height; ++i) {
        map.push_back(row);
    }

    lights.push_back(light("ambient", 0.2));
    lights.push_back(light("point", 0.6, 2, 1, 0));
    lights.push_back(light("directional", 0.2, 1, 4, 4));


    data object = readObj("cube.obj");
    object.color.r = 0;
    object.color.g = 255;
    object.color.b = 0;


    for (int x = -canv.width/2; x < canv.width/2; x++) {
        for (int y = -canv.height/2; y < canv.height/2; y++) {
            point direction = CanvasToViewport(x,y,projection_plane_z,canv,viewport_size);
            PIXELDATA color = TraceRay(camera_position, direction, 1, 100000001, object, lights);
            map = putPixel(x,y,color,canv,map);

        }
    cout << x << endl;
    }



    create("res.bmp", canv.width, canv.height, map);
    return 0;
}
