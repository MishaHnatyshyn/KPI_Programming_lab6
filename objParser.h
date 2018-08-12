#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "octree.h"
#include "bmp.h"

using namespace std;
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

struct data{
    ~data();
    vector < point > vertex;
    vector < Triangle > poligons;
    vector < point > normals;
    vector < int >edges;
    PIXELDATA color;
    vector <box> boundingBox;
};

data readObj(string path);