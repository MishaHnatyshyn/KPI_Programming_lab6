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

data readObj(string path)
{
    data res;
    string line;
    vector <points> v;
    vector < vector <int> >edges;

    points temp;
    ifstream myfile (path);
    while(!myfile.eof()){
        getline (myfile,line);
        if (line[0] == 'v' && line[1] == ' ') {
            istringstream iss(line);
            line.replace(0, 1, "");
            std::string::size_type sz;     // alias of size_t
            temp.x = stod(line, &sz);
            temp.y = stod(line.substr(sz));
            temp.z = stod(line.substr(sz));
            cout << temp.x << "\t" << temp.y << "\t" << temp.z << endl;
            v.push_back(temp);
        }
        else if (line[0] == 'f' && line[1] == ' ') {
            istringstream iss(line);
            line.replace(0, 1, "");
            cout << line << endl;
            int n = 0;
            int temp;
            for (int i = 0; i < line.length(); ++i) {
                if(line[i] == ' '){
                    temp = i;
                    while(line[i] != '/' && i < line.length()){i++;}
                    edges.push_back(vector<int>());
                    edges[n].push_back(stoi(line.substr(temp, i-temp )));
                    cout << line.substr(temp, i-temp) << endl;
                    n++;
                }
            }
        }
    }
    res.vertex = v;
    res.edges = edges;
    return res;
}