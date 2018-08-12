#include <iostream>
#include <vector>
#include <iomanip>
#include "rayTraycing.h"

using namespace std;

bool isInBox(data *object, point min, point max, int j){

    if (
            is_inside(min, max, object->boundingBox[j].v1) ||
            is_inside(min, max, object->boundingBox[j].v2) ||
            is_inside(min, max, object->boundingBox[j].v3) ||
            is_inside(min, max, object->boundingBox[j].v4) ||
            is_inside(min, max, object->boundingBox[j].v5) ||
            is_inside(min, max, object->boundingBox[j].v6) ||
            is_inside(min, max, object->boundingBox[j].v7) ||
            is_inside(min, max, object->boundingBox[j].v8)
            ) {
        return true;
    }
    else return false;

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
        for (int j = 0; j < object->boundingBox.size(); ++j) {
            if(isInBox(object, curr_min, curr_max, j)){
                curr->poligons.push_back(&object->poligons[j]);
                curr->flag = true;

            }
            if( curr->poligons.size() > 300){
                curr->flag = false;
                create_tree(curr, object, curr->minPoint, curr->maxPoint,scene);
                break;
            }
        }

    }
    return tree;
}


int main(){

    Scene scene;
    scene.canv.width = 400;
    scene.canv.height = 400;
    scene.projection_plane_z = 1;
    scene.viewport_size = 1;
    scene.camera_position= point(0,0,-2);

    vector<light> lights;

    vector<PIXELDATA> row(scene.canv.width, PIXELDATA(255,255,255));

    for (int i = 0; i < scene.canv.height; ++i) {
        scene.map.push_back(row);
    }

    scene.lights.push_back(light("ambient", 0.4));
    scene.lights.push_back(light("point", 0.3, -1, 0.5, 0));
    scene.lights.push_back(light("point", 0.3, 1, 0.5, 0));

    data object = readObj("3.obj");
    object.color.r = 150;
    object.color.g = 150;
    object.color.b = 150;

    Octree* tree = nullptr;

    tree = create_tree(tree, &object,{-1,-1,-1},{1,1,1}, &scene);

    for (int x = -scene.canv.width/2; x < scene.canv.width/2; x++) {
        for (int y = -scene.canv.height/2; y < scene.canv.height/2; y++) {
            if (x == 0 && y == 0){
                cout << "" << endl;
            }
            vector<Octree*> trees;
            point direction = CanvasToViewport(x,y,scene.projection_plane_z,scene.canv,scene.viewport_size);
            hit(tree,direction,&scene,&object,x,y);
        }
        cout << x << endl;
    }

    create("res.bmp", scene.canv.width, scene.canv.height, scene.map);
    return 0;
}
