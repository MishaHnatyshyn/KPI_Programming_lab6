#include "objParser.h"


using namespace std;

data readObj(string path)
{
    data result;
    vector < Triangle > res;
    string line;
    vector <point> v;
    vector <int> edges;

    point temp;
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
            int temp = 0;
            for (int i = 0; i < line.length(); ++i) {
                if(line[i] == ' ') {
                    temp = i;
                    while (line[i] != '/' && i < line.length()) { i++; }
                    edges.push_back(stoi(line.substr(temp, i - temp)));
                    cout << line.substr(temp, i - temp) << endl;
                }
            }
        }
    }
    for (int i = 0; i < edges.size(); i+=3) {
        Triangle temp;
        temp.A.x = v[edges[i]].x;
        temp.A.y = v[edges[i]].y;
        temp.A.z = v[edges[i]].z;
        temp.B.x = v[edges[i+1]].x;
        temp.B.y = v[edges[i+1]].y;
        temp.B.z = v[edges[i+1]].z;
        temp.C.x = v[edges[i+2]].x;
        temp.C.y = v[edges[i+2]].y;
        temp.C.z = v[edges[i+2]].z;
        res.push_back(temp);
    }
    result.edges = edges;
    result.vertex = v;
    result.poligons = res;
    return result;
}