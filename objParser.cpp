#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "objParser.h"

using namespace std;

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

// .obj file parsing

data readObj(string path)
{
    data result;
    vector < Triangle > res;
    vector < point> res2;
    string line;
    vector <point> v;
    vector <point> vn;
    vector <int> edges;
    vector <int> normals;
    bool flag = false;
    point temp;
    ifstream myfile (path);

    //file reading and parsing

    while(!myfile.eof()){
        getline (myfile,line);
        if (line[0] == 'v' && line[1] == ' ') {
            istringstream iss(line);
            line.replace(0, 2, "");
            int curr = line.find(' ');
            int prev = 0;
            temp.x = stof(line.substr(prev, curr));
            prev = curr+1;
            curr = line.find(' ', prev);
            temp.y = stof(line.substr(prev, curr));
            prev = curr+1;
            curr = line.find(' ', prev);
            temp.z = stof(line.substr(prev, curr));
            v.push_back(temp);
        }
        else if (line[0] == 'v' && line[1] == 'n') {
            flag = true;
            istringstream iss(line);
            line.replace(0, 3, "");
            int curr = line.find(' ');
            int prev = 0;
            temp.x = stof(line.substr(prev, curr));
            prev = curr+1;
            curr = line.find(' ', prev);
            temp.y = stof(line.substr(prev, curr));
            prev = curr+1;
            curr = line.find(' ', prev);
            temp.z = stof(line.substr(prev, curr));
            vn.push_back(temp);
        }
        else if (line[0] == 'f' && line[1] == ' ') {
            istringstream iss(line);
            line.replace(0, 1, "");
            int temp = 0;
            for (int i = 0; i < line.length(); ++i) {
                if(line[i] == ' ') {
                    temp = i;
                    while (line[i] != '/' && i < line.length()) { i++; }
                    edges.push_back(stoi(line.substr(temp, i - temp)));
                    if (flag) {
                        i++;
                        while (line[i] != '/' && i < line.length()) { i++; };
                        i++;
                        temp = i;
                        while (line[i] != ' ' && i < line.length()) { i++; };
                        normals.push_back(stoi(line.substr(temp, i - temp)));
                        i--;
                    }
                }
            }
        }
    }

    //triangles creating

    Triangle triangles[6];
    triangles[0].A = point(-0.75, 0.25, 0);
    triangles[0].B = point(-0.75, 0, 0);
    triangles[0].C = point(-0.25, 0, 0);

    for (int j = 1; j < 4; ++j) {
        triangles[j].A = point(triangles[j-1].A.x + 0.5, triangles[j-1].A.y, triangles[j-1].A.z);
        triangles[j].B = point(triangles[j-1].B.x + 0.5, triangles[j-1].B.y, triangles[j-1].B.z);
        triangles[j].C = point(triangles[j-1].C.x + 0.5, triangles[j-1].C.y, triangles[j-1].C.z);
    }
    for (int j = 4; j < 5; ++j) {
        triangles[j].A = point(triangles[j-1].A.x - 0.5, triangles[j-1].A.y + 0.5, triangles[j-1].A.z);
        triangles[j].B = point(triangles[j-1].B.x - 0.5, triangles[j-1].B.y + 0.5, triangles[j-1].B.z);
        triangles[j].C = point(triangles[j-1].C.x - 0.5, triangles[j-1].C.y + 0.5, triangles[j-1].C.z);
    }
    for (int j = 5; j < 6; ++j) {
        triangles[j].A = point(triangles[j-1].A.x + 0.5, triangles[j-1].A.y + 0.5, triangles[j-1].A.z + 0.5);
        triangles[j].B = point(triangles[j-1].B.x + 0.5, triangles[j-1].B.y + 0.5, triangles[j-1].B.z+ 0.5);
        triangles[j].C = point(triangles[j-1].C.x + 0.5, triangles[j-1].C.y + 0.5, triangles[j-1].C.z+ 0.5);
    }

    for (int i = 0; i < 6; i++) {
        Triangle temp;
        point temp2;
        temp.A.x = v[edges[i]-1].x;
        temp.A.y = v[edges[i]-1].y;
        temp.A.z = v[edges[i]-1].z;
        i++;
        temp.B.x = v[edges[i]-1].x;
        temp.B.y = v[edges[i]-1].y;
        temp.B.z = v[edges[i]-1].z;
        i++;
        temp.C.x = v[edges[i]-1].x;
        temp.C.y = v[edges[i]-1].y;
        temp.C.z = v[edges[i]-1].z;
        temp = triangles[i];
        res.push_back(temp);
        vector <Triangle> temp3;
        temp3.push_back(temp);
        result.boundingBox.push_back(boxSizeCount(temp3));
        if(flag) {
            temp2.x = vn[normals[i] - 1].x;
            temp2.y = vn[normals[i] - 1].y;
            temp2.z = vn[normals[i] - 1].z;
            res2.push_back(temp2);

        }
    }
    result.edges = edges;
    result.vertex = v;

    res.clear();

    for (int k = 0; k < 6; ++k) {
        res.push_back(triangles[k]);
    }

    result.boundingBox.clear();



    for (int k = 0; k < 6; ++k) {
        vector <Triangle> temp3;
        temp3.push_back(triangles[k]);
        result.boundingBox.push_back(boxSizeCount(temp3));
    }

    result.poligons = res;
    result.normals = res2;

    return result;
}

data::~data() {
    poligons.clear();
    vertex.clear();
    edges.clear();
    normals.clear();
}