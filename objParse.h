#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

struct points{
    float x;
    float y;
    float z;
};

struct Triangle{
    points A;
    points B;
    points C;
};

struct data{
    vector < points > vertex;
    vector < Triangle > poligons;
    vector < points > normals;
    vector < int >edges;
};

data readObj(string path);