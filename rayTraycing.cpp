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

double ComputeLighting(point O, point N, Scene *scene){
    double intensity = 0;
    double length_n = 1;
    for (int i = 0; i < 3; ++i) {
        light curr_light = scene->lights[i];
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

PIXELDATA trace(Octree* node, point ray, Scene * scene, data* object){
    PIXELDATA res;
    res.r = 255;
    res.g = 255;
    res.b = 255;
    float closest_t;
    float closest_z;
    Triangle * curr_triangle = nullptr;
    for (int i = 0; i < node->poligons.size(); ++i) {
        vector<float> t = intersect3D(scene->camera_position, ray, *node->poligons[i]);
        if (t[0] > 0 && (curr_triangle== nullptr || node->poligons[i]->A.z < curr_triangle->A.z)){
            closest_t = t[0];
            closest_z = t[3];
            curr_triangle = node->poligons[i];
        }
    }
    if (curr_triangle == nullptr) return res;
    point normal = get_normal(*curr_triangle);
    normal = multiply(1.0/length(normal), normal);
    double i = ComputeLighting(curr_triangle->A, normal, scene);
    res.r = floor(object->color.r * i);
    res.g = floor(object->color.g * i);
    res.b = floor(object->color.b * i);
    return res;
}

void putPixel(int x_prev, int y_prev, PIXELDATA color, Scene * scene){
    int x = scene->canv.width/2 + x_prev;
    int y = scene->canv.height/2 - y_prev - 1;
    if (x < 0 || x >= scene->canv.width || y < 0 || y >= scene->canv.height) {
        return;
    }
    if (scene->map[y][x].r == 255 && scene->map[y][x].g ==255 && scene->map[y][x].b == 255)
        scene->map[y][x] = color;
    return;
}

bool hit(Octree* tree, point ray, Scene* scene, data* object, int x, int y) {
    for (int i = 0; i < 8; ++i) {
        if (tree->children[i] && tree->children[i]->poligons.size() != 0) {
            if (intersect(tree->children[i]->minPoint, tree->children[i]->maxPoint, ray, scene->camera_position)) {
                hit(tree->children[i], ray, scene, object, x, y);
            }
        }
    }
    if (tree->poligons.size() == 0)
        return 0;
    PIXELDATA color = trace(tree, ray, scene, object);
    if (color.r == 255 && color.g == 255 && color.b == 255 ) return 0;
    putPixel(x, y, color, scene);
}