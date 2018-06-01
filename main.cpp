#include <iostream>

#include <cmath>
#include "bmp.h"
using namespace std;


struct point{
    double x;
    double y;
    double z;
    point(double a, double b, double c){
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

struct light{
    string type;
    double intensity = 0.6;
    point position;
    point direction;
};


struct sphere{
    point centre;
    double radius;
    sphere(double x, double y, double z, double r){
        centre.x = x;
        centre.y = y;
        centre.z = z;
        radius = r;
    }
};

point CanvasToViewport(int x, int y, int Vw,int Cw, int Vh, int Ch, int d){
    return point(x*Vw/Cw, y*Vh/Ch, d);
}

/*
    ComputeLighting(P, N) {
    i = 0.0
    for light in scene.Lights {
        if light.type == ambient {
            i += light.intensity
        } else {
            if light.type == point
                L = light.position - P
            else
                L = light.direction

            n_dot_l = dot(N, L)
            if n_dot_l > 0
                i += light.intensity*n_dot_l/(length(N)*length(L))
        }
    }
    return i
}
 */

double ComputeLighting(point P, point N, vector<light> lightSources){
    double i = 0;
    for (int j = 0; j < lightSources.size(); ++j) {
        if (lightSources[j].type == "ambient"){
            i+=lightSources[j].intensity;
        } else{
            point L;
            if(lightSources[j].type == "point"){
                L.x = lightSources[j].position.x - P.x;
                L.y = lightSources[j].position.y - P.y;
                L.x = lightSources[j].position.z - P.z;
            }else{
                L.x = lightSources[j].position.x;
                L.y = lightSources[j].position.y;
                L.x = lightSources[j].position.z;
            }
            double lengthN = sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
            double lengthL = sqrt(L.x * L.x + L.y * L.y + L.z * L.z);
            double n_dot_l = N.x * L.x + N.y * L.y + N.z * L.z;
            if (n_dot_l > 0) {
                i += lightSources[j].intensity * n_dot_l / (lengthL * lengthN);
            }
        }

    }
    return i;
}


vector<double> IntersectRaySphere(point O, point D, sphere obj){
    vector<double> res(2);
    point C = obj.centre;
    double r = obj.radius;
    point oc;
    oc.x = O.x - C.x;
    oc.y = O.y - C.y;
    oc.z = O.z - C.z;
    double k1 = D.x*D.x + D.y*D.y + D.z*D.z;
    double k2 = 2 * (oc.x*D.x + oc.y*D.y + oc.z*D.z);
    double k3 = (oc.x*oc.x + oc.y*oc.y + oc.z*oc.z) - r*r;
    double discriminant = k2*k2 - 4*k1*k3;
    if (discriminant < 0) {
        res[0] = 100000001;
        res[1] = 100000001;
        return res;
    }

    double t1 = ((-1)*k2 + sqrt(discriminant)) / (2*k1);
    double t2 = ((-1)*k2 - sqrt(discriminant)) / (2*k1);
    res[0] = t1;
    res[1] = t2;
    return res;
}

PIXELDATA TraceRay(point O, point D, int t_min, int t_max, sphere obj){
    PIXELDATA res;
    res.r = 255;
    res.g = 255;
    res.b = 255;
    double closest_t = 100000001;
    sphere* closest_sphere = nullptr;
    vector<double> t = IntersectRaySphere(O, D, obj);
    double t1 = t[0];
    double t2 = t[1];
    if (t1 > t_min && t1 < t_max && t1 < closest_t){
        closest_t = t1;
        res.r = 0;
        res.g = 0;
        res.b = 0;
    }
    if (t2 > t_min && t2 < t_max && t2 < closest_t){
        closest_t = t2;
        res.r = 0;
        res.g = 0;
        res.b = 0;
    }
    point P(O.x+D.x*closest_t, O.y+D.y*closest_t, O.z+D.z*closest_t);
    point N(P.x - obj.centre.x, P.y - obj.centre.y, P.z - obj.centre.z);
    double lengthN = sqrt(N.x*N.x + N.y*N.y + N.z*N.z);
    point N1(N.x/lengthN, N.y/lengthN, N.z/lengthN);
    light lightSourcePoint;
    light lightSourceAmbient;
    light lightSourceDirectional;
    lightSourceAmbient.type = "ambient";
    lightSourceDirectional.type = "directional";
    lightSourceDirectional.intensity = 0.2;
    lightSourceDirectional.direction = point(3,5,4);
    lightSourceAmbient.intensity = 0.2;
    lightSourcePoint.type = "point";
    lightSourcePoint.intensity = 0.6;
    lightSourcePoint.position.x = 200;
    lightSourcePoint.position.y = 200;
    lightSourcePoint.position.z = 200;
    vector<light> lightSources;
    lightSources.push_back(lightSourcePoint);
    lightSources.push_back(lightSourceDirectional);
    lightSources.push_back(lightSourceAmbient);

    double i = ComputeLighting(P, N1, lightSources);
    PIXELDATA res1(res.r*i, res.g*i, res.b*i);
    return res1;
}


int main() {
    point O(0,0,0);
    int d = 400;
    int Cw = 1000;
    int Ch = 1000;
    int Vh = 400;
    int Vw = 400;
    vector<PIXELDATA> row(Vw);
    sphere mySphere(50,50,600,37);
    vector<vector<PIXELDATA>> viewPort;
    for (int i = 0; i < Vh; ++i) {
        viewPort.push_back(row);
    }
    for (int x = (-1)*Cw/2; x < Cw/2; x++) {
        for (int y = (-1)*Ch/2; y < Ch/2; y++) {
            point D = CanvasToViewport(x,y,Vw,Cw,Vh,Ch,d);
            PIXELDATA color = TraceRay(O,D,0,300,mySphere);
            int matrixXPos = Vw/2 + x;
            int matrixYPos = Vh/2 + y;
            if (matrixXPos >= Vw ||
                matrixYPos >= Vh ||
                matrixXPos < 0 ||
                matrixYPos < 0) continue;
            viewPort[matrixXPos][matrixYPos] = color;
        }
    }
/*
    for (int j = 0; j < Vh; ++j) {
        for (int i = 0; i < Vw; ++i) {
            cout<<viewPort[j][i]<<"  ";
        }
        cout << endl;
    }*/

    create("test.bmp",Vw,Vh,viewPort);

    return 0;
}