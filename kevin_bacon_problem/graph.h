#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
using std::cout;
using std::endl;
using std::vector;
using std::list;
//unidirectio a->b b->a
class Graph
{
public:
    Graph();
    Graph(int v);
    void resizeGraph(int v);
    int getVerticesCount()const;
    int getEdgeCount()const;
    void addEdge(int v,int w);
    const list<int>& adj(int v) const;
private:
    vector<list<int>> adjList;
    int vertices;
    int edges;
};

#endif // GRAPH_H
