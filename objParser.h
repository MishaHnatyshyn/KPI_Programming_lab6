#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "geomerty.h"
#include "bmp.h"


using namespace std;



struct data{
    vector < point > vertex;
    vector < Triangle > poligons;
    vector <int>edges;
    PIXELDATA color;
};

data readObj(string path);