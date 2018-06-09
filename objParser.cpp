#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "objParser.h"

using namespace std;

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
    for (int i = 0; i < edges.size(); i++) {
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
        res.push_back(temp);
        if(flag) {
            temp2.x = vn[normals[i] - 1].x;
            temp2.y = vn[normals[i] - 1].y;
            temp2.z = vn[normals[i] - 1].z;
            res2.push_back(temp2);
        }
    }
    result.edges = edges;
    result.vertex = v;
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
