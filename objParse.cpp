#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;


struct data{
    double x;
    double y;
    double z;
};

vector < data > readV(string path)
{
    string line;
    vector <data> v;
    //vector <data> vn;
    //vector <data> vt;
    //vector < vector <int> >edges;

    data temp;
    ifstream myfile (path);
    while(!myfile.eof())
    {
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
        } /*else if (line[0] == 'v' && line[1] == 't') {
           istringstream iss(line);
           line.replace(0, 2, "");

           std::string::size_type sz;     // alias of size_t

           temp.x = stod (line,&sz);
           temp.y = stod (line.substr(sz));
           temp.z = stod (line.substr(sz));
           cout << temp.x << "\t" << temp.y << "\t" << temp.z << endl;
           vt.push_back(temp);
       }else if (line[0] == 'v' && line[1] == 'n') {
            istringstream iss(line);
            line.replace(0, 2, "");

            std::string::size_type sz;     // alias of size_t

            temp.x = stod (line,&sz);
            temp.y = stod (line.substr(sz));
            temp.z = stod (line.substr(sz));
            cout << temp.x << "\t" << temp.y << "\t" << temp.z << endl;
            vn.push_back(temp);
        }*/

    }
    return v;
}

vector < vector < int > > readF(string path){
    string line;
    vector < vector <int> >edges;
    ifstream myfile (path);
    while(!myfile.eof())
    {
        getline (myfile,line);
        if (line[0] == 'f' && line[1] == ' ') {
            istringstream iss(line);
            line.replace(0, 1, "");
            cout << line << endl;
            int n = 0;
            int temp;
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ' ') {
                    temp = i;
                    while (line[i] != '/' && i < line.length()) { i++; }
                    edges.push_back(vector<int>());
                    edges[n].push_back(stoi(line.substr(temp, i - temp)));
                    cout << line.substr(temp, i - temp) << endl;
                    n++;
                }
            }
        }
    }
    return edges;
};