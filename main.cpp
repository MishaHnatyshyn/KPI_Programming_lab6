#include <iostream>
#include <vector>
#include "rayTraycing.h"

using namespace std;





/*
vector<vector<PIXELDATA>> create_tree(Octree* tree,
                 data object,
                 point min,
                 point max,
                 canvas canv,
                 vector<light> lights,
                 vector<vector<PIXELDATA>> map){
    tree = add_node(min, max, tree);



    for (int i = 0; i < 8; ++i) {
        Octree *curr = tree->children[i];
        point curr_min = curr->minPoint;
        point curr_max = curr->maxPoint;
        for (int j = 0; j < object.poligons.size(); ++j) {

            if ((object.poligons[j].A.x >= curr_min.x && object.poligons[j].A.x <= curr_max.x &&
                 object.poligons[j].A.y >= curr_min.y && object.poligons[j].A.y <= curr_max.y &&
                 object.poligons[j].A.z >= curr_min.z && object.poligons[j].A.z <= curr_max.x) ||
                (object.poligons[j].B.x >= curr_min.x && object.poligons[j].B.x <= curr_max.x &&
                 object.poligons[j].B.y >= curr_min.y && object.poligons[j].B.y <= curr_max.y &&
                 object.poligons[j].B.z >= curr_min.z && object.poligons[j].B.z <= curr_max.x) ||
                (object.poligons[j].C.x >= curr_min.x && object.poligons[j].C.x <= curr_max.x &&
                 object.poligons[j].C.y >= curr_min.y && object.poligons[j].C.y <= curr_max.y &&
                 object.poligons[j].C.z >= curr_min.z && object.poligons[j].C.z <= curr_max.x)){
                curr->poligons.push_back(j);
                curr->flag = true;
            }

            if(curr->poligons.size() > 4){
                curr->flag = false;
                map = create_tree(curr, object, curr->minPoint, curr->maxPoint, canv, lights, map);
//                if (i == 7) return map;
                break;
            }
        }
        if(curr->poligons.size() <= 4 && curr->poligons.size() > 0){
            curr->flag = true;
        }
        if (curr->flag){
            //tracing
        int start_x;
        int start_y;
        int end_x;
        int end_y;
        point point1 = curr_min;
        point point2 = curr_max;
        point point3(curr_min.x, curr_min.y, curr_max.z);
        point point4(curr_min.x, curr_max.y, curr_max.z);
        point point5(curr_min.x, curr_max.y, curr_min.z);
        point point6(curr_max.x, curr_min.y, curr_min.z);
        point point7(curr_max.x, curr_max.y, curr_min.z);
        point point8(curr_max.x, curr_min.y, curr_max.z);
        point1 = ViewportToCanvas(point1, canv, 1);
        point2 = ViewportToCanvas(point2, canv, 1);
        point3 = ViewportToCanvas(point3, canv, 1);
        point4 = ViewportToCanvas(point4, canv, 1);
        point5 = ViewportToCanvas(point5, canv, 1);
        point6 = ViewportToCanvas(point6, canv, 1);
        point7 = ViewportToCanvas(point7, canv, 1);
        point8 = ViewportToCanvas(point8, canv, 1);

            */
/*
        point2 = CanvasToViewport(point2.x, point2.y, point2.z, canv, 1);
        point3 = CanvasToViewport(point3.x, point3.y, point3.z, canv, 1);
        point4 = CanvasToViewport(point4.x, point4.y, point4.z, canv, 1);
        point5 = CanvasToViewport(point5.x, point5.y, point5.z, canv, 1);
        point6 = CanvasToViewport(point6.x, point6.y, point6.z, canv, 1);
        point7 = CanvasToViewport(point7.x, point7.y, point7.z, canv, 1);
        point8 = CanvasToViewport(point8.x, point8.y, point8.z, canv, 1);*/
/*

            double temp1[8] = {point1.x, point2.x, point3.x, point4.x, point5.x, point6.x, point7.x, point8.x};
            double temp2[8] = {point1.y, point2.y, point3.y, point4.y, point5.y, point6.y, point7.y, point8.y};
            start_x = multy_min(temp1,8);
            start_y = multy_min(temp2,8);
            end_x = multy_max(temp1,8);
            end_y = multy_max(temp2,8);

            for (int x = start_x; x < end_x; x++) {
                for (int y = start_y; y < end_y; y++) {
                    point direction = CanvasToViewport(x,y,1,canv,1);
//            long double **dir_vec = new long double*[3];
//            long double temp_x = (long double)direction.x;
//            35long double temp_y = (long double)direction.y;
//            long double temp_z = (long double)direction.z;
//            dir_vec[0] = &temp_x;
//            dir_vec[1] = &temp_y;
//            dir_vec[2] = &temp_z;
//
//            direction =  matrix_multiplication(rotationMatrixZ(0), dir_vec);;
                    PIXELDATA color = TraceRay({0,0,-1.9}, direction, 1, 100000001, object, lights, curr->poligons);
                    map = putPixel(x,y,color,canv,map);

                }
                cout << x << endl;
            }


        }





        }


    return map;
    }

*/




int main(){
    canvas canv;
    canv.width = 50;
    canv.height = 50;
    int viewport_size = 1;
    int projection_plane_z = 1;
    point camera_position(0,0,-1.9);
//    point camera_position(0,1.5,0);
    vector<light> lights;
    vector<PIXELDATA> row(canv.width);
    vector<vector<PIXELDATA>> map;
    for (int i = 0; i < canv.height; ++i) {
        map.push_back(row);
    }


    lights.push_back(light("ambient", 0.4));
    lights.push_back(light("point", 0.6, 0, 1.3, 0));
//    lights.push_back(light("directional", 0.2, 1, 4, 4));


    data object = readObj("3.obj");
    object.color.r = 150;
    object.color.g = 150;
    object.color.b = 150;

    vector<data> objects;
    objects.push_back(object);
    Triangle triangle;
    triangle.A = point(-6,-1,-3);
    triangle.B = point(0,-1,3);
    triangle.C = point(6,-1,-3);

//
//    triangle.A = point(-3,-1,-1.5);
//    triangle.B = point(3,-1,-1.5);
//    triangle.C = point(0,-1,1.5);
    object.poligons.push_back(triangle);



    for (int x = -canv.width/2; x < canv.width/2; x++) {
        for (int y = -canv.height/2; y < canv.height/2; y++) {
            point direction = CanvasToViewport(x,y,projection_plane_z,canv,viewport_size);
//            long double **dir_vec = new long double*[3];
//            long double temp_x = (long double)direction.x;
//            35long double temp_y = (long double)direction.y;
//            long double temp_z = (long double)direction.z;
//            dir_vec[0] = &temp_x;
//            dir_vec[1] = &temp_y;
//            dir_vec[2] = &temp_z;
//
//            direction =  matrix_multiplication(rotationMatrixZ(0), dir_vec);;
            PIXELDATA color = TraceRay(camera_position, direction, 1, 100000001, object, lights);

            map = putPixel(x,y,color,canv,map);

        }
    cout << x << endl;
    }

//    Octree *tree = nullptr;
//    map = create_tree(tree, object, {-1,-1,0}, {1,1,2}, canv, lights, map);



    create("res.bmp", canv.width, canv.height, map);
    return 0;
}
