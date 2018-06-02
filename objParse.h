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

struct data{
    vector < points > vertex;
    vector < vector < int > >edges;
};

data readObj(string path);