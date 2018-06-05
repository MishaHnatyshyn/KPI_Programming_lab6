#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

struct points{
    double x;
    double y;
    double z;
};

struct Triangle{
    points A;
    points B;
    points C;
};

struct data{
    vector < points > vertex;
    vector < Triangle > poligons;
    vector < int >edges;
};

data readObj(string path);