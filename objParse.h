#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

struct data{};
vector < data > readV(string path);
vector < vector < int > > readF(string path);