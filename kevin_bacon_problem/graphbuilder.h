#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H
#include "sstream"
#include "graph.h"
#include <fstream>
#include  <map>
#include <string>
using std::stringstream;
using std::ifstream;
using std::getline;
using std::string;
using std::vector;
using std::map;
class graphBuilder
{
public:
    graphBuilder(const string& filename);
    bool contains(const string& str)const;
    int  index(const string& str)const;
    const string& getName(const int& index)const;
    const Graph& getGraph()const;
private:
    map<string,int> items;
    vector<string> keys;
    vector<int> histo;
    Graph graph;
};

#endif // GRAPHBUILDER_H
