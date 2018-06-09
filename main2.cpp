/*
#include <iostream>
#include <vector>
#include <iomanip>
#include "rayTraycing.h"

using namespace std;

bool intersect3d(point p, point V, Triangle a){
    point E1, E2, T, P, Q, D;
    E1.x = a.B.x - a.A.x;
    E1.y = a.B.y - a.A.y;
    E1.z = a.B.z - a.A.z;

    E2.x = a.C.x - a.A.x;
    E2.y = a.C.y - a.A.y;
    E2.z = a.C.z - a.A.z;

    T.x = p.x - a.A.x;
    T.y = p.y - a.A.y;
    T.z = p.z - a.A.z;

    D = V;

    P = cross(D, E2);
    Q = cross(T, E1);

    double t, u, v;

    t = 1/dot(P, E1)*dot(Q, E2);
    u = (1/dot(P, E1))*dot(P, T);
    v = (1/dot(P, E1))*dot(Q, D);
    cout << t << endl;
    cout << u+v << endl;
    cout << u << endl;
    cout << v << endl;
    if (u >=0 && v>=0 && (u+v) < 1){
        return true;
    }
    return false;
};

bool intersect3d2(point p, point dir, Triangle T){
    point AC, AB, RA, n, S;
    AB.x = T.B.x - T.A.x;
    AB.y = T.B.y - T.A.y;
    AB.z = T.B.z - T.A.z;

    AC.x = T.C.x - T.A.x;
    AC.y = T.C.y - T.A.y;
    AC.z = T.C.z - T.A.z;


    RA.x = p.x - T.A.x;
    RA.y = p.y - T.A.y;
    RA.z = p.z - T.A.z;

    n = cross(AB, AC);
    double modn = sqrt(n.x*n.x + n.y*n.y+ n.z*n.z);
    n.x = n.x / modn;
    n.y = n.y / modn;
    n.z = n.z / modn;


}


struct box {
    point v1;
    point v2;
    point v3;
    point v4;
    point v5;
    point v6;
    point v7;
    point v8;
};

struct kdNode {
    box bbox;
    kdNode * left;
    kdNode * right;
    vector< Triangle > triangles;
};

box boxSizeCount(vector< Triangle > triangles){
    float minx = triangles[0].A.x;
    float miny = triangles[0].A.y;
    float minz = triangles[0].A.z;

    float maxx = triangles[0].A.x;
    float maxy = triangles[0].A.y;
    float maxz = triangles[0].A.z;

    for (int i = 0; i < triangles.size(); ++i) {
        float min = fmin(fmin(triangles[i].A.x, triangles[i].B.x), triangles[i].C.x);
        if (minx > min){
            minx = min;
        }
        min = fmin(fmin(triangles[i].A.y, triangles[i].B.y), triangles[i].C.y);
        if (miny > min){
            miny = min;
        }

        min = fmin(fmin(triangles[i].A.z, triangles[i].B.z), triangles[i].C.z);
        if (minz > min){
            minz = min;
        }
        float max = fmax(fmax(triangles[i].A.x, triangles[i].B.x), triangles[i].C.x);
        if (maxx < max){
            maxx = max;
        }
        max = fmax(fmax(triangles[i].A.y, triangles[i].B.y), triangles[i].C.y);
        if (maxy < max){
            maxy = max;
        }

        max = fmax(fmax(triangles[i].A.z, triangles[i].B.z), triangles[i].C.z);
        if (maxz < max){
            maxz = max;
        }

    }
    box temp;
    temp.v1.x = minx;
    temp.v1.y = miny;
    temp.v1.z = minz;


    temp.v2.x = minx;
    temp.v2.y = maxy;
    temp.v2.z = minz;


    temp.v3.x = maxx;
    temp.v3.y = maxy;
    temp.v3.z = minz;

    temp.v4.x = maxx;
    temp.v4.y = miny;
    temp.v4.z = minz;


    temp.v5.x = minx;
    temp.v5.y = miny;
    temp.v5.z = maxz;


    temp.v6.x = minx;
    temp.v6.y = maxy;
    temp.v6.z = maxz;


    temp.v7.x = maxx;
    temp.v7.y = maxy;
    temp.v7.z = maxz;

    temp.v8.x = maxx;
    temp.v8.y = miny;
    temp.v8.z = maxz;

    return temp;

};

point get_midpoint(Triangle t){
    point temp;
    temp.x = (t.A.x + t.B.x + t.C.x)/3;
    temp.y = (t.A.y + t.B.y + t.C.y)/3;
    temp.z = (t.A.z + t.B.z + t.C.z)/3;
    //cout << temp.x;
    //cout << temp.y;
    // << temp.z;
    return temp;
}

int longest_axis(box b){
    float x_size = fabs(b.v1.x) + fabs(b.v7.x);
    float y_size = fabs(b.v1.y) + fabs(b.v7.y);
    float z_size = fabs(b.v1.z) + fabs(b.v7.z);
    if (x_size > y_size && x_size > z_size) return 0;
    if (y_size > z_size && y_size > x_size) return 1;
    if (z_size > x_size && z_size > y_size) return 2;
    return 0;
}

kdNode * kdBuild (vector < Triangle > tri, int depth){
    kdNode * node = new kdNode();

    if(tri.size() == 0){
        return node;
    }

    if(tri.size() == 1){
        node->bbox = boxSizeCount(tri);
        node->left = new kdNode();
        node->right = new kdNode();
        node->left->triangles = vector < Triangle > ();
        node->right->triangles = vector < Triangle > ();
        return  node;
    }

    node->triangles = tri;
    node->left = NULL;
    node->right = NULL;
    node->bbox = boxSizeCount(tri);


    point midpt;
    midpt.x = 0;
    midpt.y = 0;
    midpt.z = 0;

    for (int i = 0; i < tri.size(); ++i) {
        point temp = get_midpoint(tri[i]);
        midpt.x += temp.x;
        midpt.y += temp.y;
        midpt.z += temp.z;
    }
    midpt.x /= tri.size();
    midpt.y /= tri.size();
    midpt.z /= tri.size();

    vector < Triangle > left;
    vector < Triangle > right;

    int axis = longest_axis(node->bbox);
    for (int i = 0; i < tri.size(); ++i) {
        switch (axis){
            case 0:{
                midpt.x >= get_midpoint(tri[i]).x ? right.push_back(tri[i]) : left.push_back(tri[i]);
                break;
            }

            case 1:{
                midpt.y >= get_midpoint(tri[i]).y ? right.push_back(tri[i]) : left.push_back(tri[i]);
                break;
            }

            case 2:{
                midpt.z >= get_midpoint(tri[i]).z ? right.push_back(tri[i]) : left.push_back(tri[i]);
                break;
            }
        }
    }
    if (left.size() == 0 && right.size() > 0)left = right;
    if (right.size() == 0 && left.size() > 0)right = left;

    int matches = 0;
    for (int i = 0; i < left.size(); ++i) {
        for (int j = 0; j < right.size(); ++j) {
            if(
                    left[i].A.x == right[j].A.x &&
                    left[i].A.y == right[j].A.y &&
                    left[i].A.z == right[j].A.z &&

                    left[i].B.x == right[j].B.x &&
                    left[i].B.y == right[j].B.y &&
                    left[i].B.z == right[j].B.z &&

                    left[i].C.x == right[j].C.x &&
                    left[i].C.y == right[j].C.y &&
                    left[i].C.z == right[j].C.z
                    ) matches++;
        }
    }
    //cout << matches << endl;
    if((float)matches/left.size() < 0.5 && (float)matches/right.size() < 0.5){
        float a = (float)matches/left.size();
        float b = (float)matches/right.size();

        node->left = kdBuild(left, depth+1);
        node->right = kdBuild(right, depth+1);
    } else {
        node->left = new kdNode();
        node->right = new kdNode();
        node->left->triangles = vector < Triangle >();
        node->right->triangles = vector < Triangle >();
    }

    return node;
};

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

bool intersect(kdNode * node, point ray, point l0){
    point intersection_point;
    point normals[6];
    normals[0] = point(node->bbox.v1.x - node->bbox.v2.x, node->bbox.v1.y - node->bbox.v2.y, node->bbox.v1.z - node->bbox.v2.z);
    normals[1] = point(node->bbox.v2.x - node->bbox.v3.x, node->bbox.v2.y - node->bbox.v3.y, node->bbox.v2.z - node->bbox.v3.z);
    normals[2] = point(node->bbox.v5.x - node->bbox.v1.x, node->bbox.v5.y - node->bbox.v1.y, node->bbox.v5.z - node->bbox.v1.z);
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
                case 0: p0 = node->bbox.v1;break;
                case 1: p0 = node->bbox.v2;break;
                case 2: p0 = node->bbox.v5;break;
                case 3: p0 = node->bbox.v2;break;
                case 4: p0 = node->bbox.v3;break;
                case 5: p0 = node->bbox.v1;break;
            }
            d = dot(subtract(p0,l0),normals[i])/dot(ray,normals[i]);
            intersection_point = add(multiply(d, ray), l0);
            if (    intersection_point.x >= node->bbox.v1.x && intersection_point.x <= node->bbox.v7.x &&
                    intersection_point.y >= node->bbox.v1.y && intersection_point.y <= node->bbox.v7.y &&
                    intersection_point.z >= node->bbox.v1.z && intersection_point.z <= node->bbox.v7.z
                    ){
                return true;
            }
        }
    }
    return false;
}

point get_intersection(kdNode * node, point ray, point l0){
    point intersection_point;
    point normals[6];
    normals[0] = point(node->bbox.v1.x - node->bbox.v2.x, node->bbox.v1.y - node->bbox.v2.y, node->bbox.v1.z - node->bbox.v2.z);
    normals[1] = point(node->bbox.v2.x - node->bbox.v3.x, node->bbox.v2.y - node->bbox.v3.y, node->bbox.v2.z - node->bbox.v3.z);
    normals[2] = point(node->bbox.v5.x - node->bbox.v1.x, node->bbox.v5.y - node->bbox.v1.y, node->bbox.v5.z - node->bbox.v1.z);
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
                case 0: p0 = node->bbox.v1;break;
                case 1: p0 = node->bbox.v2;break;
                case 2: p0 = node->bbox.v5;break;
                case 3: p0 = node->bbox.v2;break;
                case 4: p0 = node->bbox.v3;break;
                case 5: p0 = node->bbox.v1;break;
            }
            d = dot(subtract(p0,l0),normals[i])/dot(ray,normals[i]);
            intersection_point = add(multiply(d, ray), l0);
            if (    intersection_point.x >= node->bbox.v1.x && intersection_point.x <= node->bbox.v7.x &&
                    intersection_point.y >= node->bbox.v1.y && intersection_point.y <= node->bbox.v7.y &&
                    intersection_point.z >= node->bbox.v1.z && intersection_point.z <= node->bbox.v7.z
                    ){
                return intersection_point;
            }
        }
    }
    return {0,0,0};
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


PIXELDATA trace(kdNode * node, point ray, Scene * scene, data* object){
    PIXELDATA res;
    res.r = 255;
    res.g = 255;
    res.b = 255;
    float closest_t;
    float closest_z;
    Triangle * curr_triangle = nullptr;
    for (int i = 0; i < node->triangles.size(); ++i) {
        vector<float> t = intersect3D(scene->camera_position, ray, node->triangles[i]);
        if (t[0] > 0 && (curr_triangle== nullptr || node->triangles[i].A.z < curr_triangle->A.z)){
            closest_t = t[0];
            closest_z = t[3];
            curr_triangle = &node->triangles[i];
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
    scene->map[y][x] = color;
    return;
}

bool hit(kdNode * node, point ray, Scene* scene, data* object, int x, int y){
    if(node->right->triangles.size()>0 && node->left->triangles.size()>0){
        bool intersect_l = intersect(node->left, ray,scene->camera_position);
        bool intersect_r = intersect(node->right, ray,scene->camera_position);
        if(intersect_l && intersect_r){
            float length_l = length(subtract(scene->camera_position,get_intersection(node->left, ray,scene->camera_position)));
            float length_r = length(subtract(scene->camera_position,get_intersection(node->right, ray,scene->camera_position)));
            if (length_l > length_r){
                if(!hit(node->left,ray, scene,object, x, y)) hit(node->right,ray, scene,object, x, y);
            } else if(!hit(node->right,ray, scene,object, x, y)) hit(node->left,ray, scene,object, x, y);

        } else if(intersect_l){
            hit(node->left,ray, scene,object, x, y);
        }else if(intersect_r){
            hit(node->right,ray, scene,object, x, y);
        }
    } else{
        if(node->triangles.size() == 0 )
            return 0;
        PIXELDATA color = trace(node, ray,scene,object);
        putPixel(x,y,color,scene);
    }
}

int main(){

    Scene scene;
    scene.canv.width = 400;
    scene.canv.height = 400;
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


    data object = readObj("sphere.obj");
    object.color.r = 150;
    object.color.g = 150;
    object.color.b = 150;

    vector<data> objects;
    objects.push_back(object);

    kdNode * root = kdBuild(object.poligons,0);

    for (int x = -scene.canv.width/2; x < scene.canv.width/2; x++) {
        for (int y = -scene.canv.height/2; y < scene.canv.height/2; y++) {
            if (x == 0 && y == 0){
                cout << "" << endl;
            }
            point direction = CanvasToViewport(x,y,scene.projection_plane_z,scene.canv,scene.viewport_size);
            hit(root,direction,&scene,&object,x,y);
        }
        cout << x << endl;
    }


    create("res.bmp", scene.canv.width, scene.canv.height, scene.map);
    return 0;
}

*/
