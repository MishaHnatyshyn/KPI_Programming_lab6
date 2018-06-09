#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "octree.h"
#include "bmp.h"

using namespace std;

struct data{
    ~data();
    vector < point > vertex;
    vector < Triangle > poligons;
    vector < point > normals;
    vector < int >edges;
    PIXELDATA color;
};

data readObj(string path);
