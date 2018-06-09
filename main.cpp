#include <iostream>
#include <vector>
#include <iomanip>
#include "rayTraycing.h"

using namespace std;

struct Scene{
    canvas canv;
    int viewport_size;
    int projection_plane_z;
    vector<vector<PIXELDATA>> map;
    point camera_position;
    vector<light> lights;
};

void normalize(point * n){
    float vec_length = length(*n);
    n->x = n->x/vec_length;
    n->y = n->y/vec_length;
    n->z = n->z/vec_length;
}

bool intersect(point min, point max, point ray, point l0){
    point intersection_point;
    point normals[6];
    point v1(min.x, min.y, min.z);
    point v2(min.x, min.y, max.z);
    point v3(max.x, min.y, max.z);
    point v4(max.x, min.y, min.z);
    point v5(min.x, max.y, min.z);
    point v6(min.x, max.y, max.z);
    point v7(max.x, max.y, max.z);
    point v8(max.x, max.y, min.z);
    normals[0] = point(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    normals[1] = point(v2.x - v3.x, v2.y - v3.y, v2.z - v3.z);
    normals[2] = point(v5.x - v1.x, v5.y - v1.y, v5.z - v1.z);
    normalize(&normals[0]);
    normalize(&normals[1]);
    normalize(&normals[2]);
    normals[3] = normals[0];
    normals[4] = normals[1];
    normals[5] = normals[2];
    float d;
    point p0;
    for (int i = 0; i < 6; ++i) {
        d = dot(ray,normals[i]);
        if(d != 0){
            switch (i){
                case 0: p0 = v1;break;
                case 1: p0 = v2;break;
                case 2: p0 = v5;break;
                case 3: p0 = v2;break;
                case 4: p0 = v3;break;
                case 5: p0 = v1;break;
            }
            d = dot(subtract(p0,l0),normals[i])/dot(ray,normals[i]);
            intersection_point = add(multiply(d, ray), l0);
            if (    intersection_point.x >= v1.x && intersection_point.x <= v7.x &&
                    intersection_point.y >= v1.y && intersection_point.y <= v7.y &&
                    intersection_point.z >= v1.z && intersection_point.z <= v7.z
                    ){
                return true;
            }
        }
    }
    return false;
}

double ComputeLighting(point O, point N, Scene *scene){
    double intensity = 0;
    double length_n = 1;
    for (int i = 0; i < 2; ++i) {
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
    if (scene->map[y][x].r < color.r && scene->map[y][x].g < color.g && scene->map[y][x].b < color.b)
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

Octree* create_tree(Octree* tree,
                                      data* object,
                                      point min,
                                      point max,
                                      Scene * scene
){
    tree = add_node(min, max, tree);
    for (int i = 0; i < 8; ++i) {
        Octree *curr = tree->children[i];
        point curr_min = curr->minPoint;
        point curr_max = curr->maxPoint;
        for (int j = 0; j < object->poligons.size(); ++j) {

            if ((object->poligons[j].A.x >= curr_min.x && object->poligons[j].A.x <= curr_max.x &&
                 object->poligons[j].A.y >= curr_min.y && object->poligons[j].A.y <= curr_max.y &&
                 object->poligons[j].A.z >= curr_min.z && object->poligons[j].A.z <= curr_max.x) ||
                (object->poligons[j].B.x >= curr_min.x && object->poligons[j].B.x <= curr_max.x &&
                 object->poligons[j].B.y >= curr_min.y && object->poligons[j].B.y <= curr_max.y &&
                 object->poligons[j].B.z >= curr_min.z && object->poligons[j].B.z <= curr_max.x) ||
                (object->poligons[j].C.x >= curr_min.x && object->poligons[j].C.x <= curr_max.x &&
                 object->poligons[j].C.y >= curr_min.y && object->poligons[j].C.y <= curr_max.y &&
                 object->poligons[j].C.z >= curr_min.z && object->poligons[j].C.z <= curr_max.x)){
                curr->poligons.push_back(&object->poligons[j]);
                curr->flag = true;
            }

            if(curr->poligons.size() > 300){
                curr->flag = false;
//                curr->poligons.clear();
                create_tree(curr, object, curr->minPoint, curr->maxPoint,scene);
                break;
            }
        }

    }
    return tree;
}



int main(){

    Scene scene;
    scene.canv.width = 800;
    scene.canv.height = 600;
    scene.projection_plane_z = 1;
    scene.viewport_size = 1;
    scene.camera_position= point(0,0,-2);

    vector<light> lights;

    vector<PIXELDATA> row(scene.canv.width, PIXELDATA(0,0,0));
    for (int i = 0; i < scene.canv.height; ++i) {
        scene.map.push_back(row);
    }


    scene.lights.push_back(light("ambient", 0.4));
    scene.lights.push_back(light("point", 0.6, 0, 1.3, 0));
//    lights.push_back(light("directional", 0.2, 1, 4, 4));


    data object = readObj("3.obj");
    object.color.r = 150;
    object.color.g = 150;
    object.color.b = 150;

    vector<data> objects;
    objects.push_back(object);

    Octree* tree = nullptr;

    tree = create_tree(tree, &object,{-1,-1,-1},{1,1,1}, &scene);

    for (int x = -scene.canv.width/2; x < scene.canv.width/2; x++) {
        for (int y = -scene.canv.height/2; y < scene.canv.height/2; y++) {
            if (x == 0 && y == 0){
                cout << "" << endl;
            }
            point direction = CanvasToViewport(x,y,scene.projection_plane_z,scene.canv,scene.viewport_size);
            hit(tree,direction,&scene,&object,x,y);
        }
        cout << x << endl;
    }

    create("res.bmp", scene.canv.width, scene.canv.height, scene.map);
    return 0;
}

