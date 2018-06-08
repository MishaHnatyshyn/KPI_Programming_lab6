#include "rayTraycing.h"

point CanvasToViewport(int x, int y, int d,canvas canv, int viewport_size){
    point res(((double)x*viewport_size)/(double)canv.width, ((double)y*viewport_size)/(double)canv.height, d);
    return res;
}

point ViewportToCanvas(point a, canvas canv, int viewport_size, point camera_pos){
    float x = (((a.x - camera_pos.x))/(a.z - camera_pos.z)) + camera_pos.x;
    float y = (((a.y - camera_pos.y))/(a.z - camera_pos.z)) + camera_pos.y;


    return {x*canv.width, y*canv.height, 1};
}


double ComputeLighting(point O, point N, vector<light> lights){
    double intensity = 0;
    double length_n = 1;
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


PIXELDATA TraceRay(point O, point D, int t_min, int t_max, data object, vector<light> lights, vector<int> poligons){
    PIXELDATA res;
    res.r = 255;
    res.g = 255;
    res.b = 255;

    double closest_t = t_max;
    double closest_z = t_max;
    data* closest_object = nullptr;
    Triangle * curr_triangle = nullptr;
    Triangle triangle;
    point intersection_point;
    for (int j = 0; j < poligons.size(); ++j) {
        vector<float> t = intersect(O, D, object.poligons[poligons[j]]);
        if (t[0] > 0 && (curr_triangle== nullptr || object.poligons[poligons[j]].A.z < curr_triangle->A.z)){
            intersection_point.x = t[1];
            intersection_point.y = t[2];
            intersection_point.z = t[3];
            closest_t = t[0];
            closest_z = t[3];
            closest_object = &object;
            curr_triangle = &object.poligons[poligons[j]];
        }

    }
    if (curr_triangle == nullptr)
        return res;

    point normal = get_normal(*curr_triangle);
    normal = multiply(1.0/length(normal), normal);
    double i = ComputeLighting(intersection_point, normal, lights);
//    double i = ComputeLighting(curr_triangle->A,normal,lights);
    res.r = floor(closest_object->color.r * i);
    res.g = floor(closest_object->color.g * i);
    res.b = floor(closest_object->color.b * i);
    return res;
}

vector<vector<PIXELDATA>> putPixel(int x_prev, int y_prev, PIXELDATA color, canvas viewPort, vector<vector<PIXELDATA>> map){
    int x = viewPort.width/2 + x_prev;
    int y = viewPort.height/2 - y_prev - 1;
    if (x < 0 || x >= viewPort.width || y < 0 || y >= viewPort.height) {
        return map;
    }
    map[y][x] = color;
    return map;
}


long double ** rotationMatrixZ(double rotation){
    long double ** rotMatrix = new long double * [3];
    for (int i = 0; i < 3; i++)
        rotMatrix[i] = new long double [3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            rotMatrix[i][j] = 0;
        }
    }
    rotMatrix[1][1] = rotMatrix[2][2] = cos ( rotation * PI / 180.0 );
    rotMatrix[2][1] = sin ( rotation * PI / 180.0 );
    rotMatrix[1][2] = - rotMatrix[2][1];
    rotMatrix[0][0] = 1;

    return rotMatrix;
}

long double ** rotationMatrixY(double rotation){
    long double ** rotMatrix = new long double * [3];
    for (int i = 0; i < 3; i++)
        rotMatrix[i] = new long double [3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            rotMatrix[i][j] = 0;
        }
    }
    rotMatrix[0][0] = rotMatrix[1][1] = cos ( rotation * PI / 180.0 );
    rotMatrix[1][0] = sin ( rotation * PI / 180.0 );
    rotMatrix[0][1] = - rotMatrix[1][0];
    rotMatrix[2][2] = 1;

    return rotMatrix;
}

long double ** rotationMatrixX(double rotation){
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
