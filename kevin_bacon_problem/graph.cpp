#include "graph.h"
Graph::Graph(int v)
{
    vertices = v;
    edges = 0;
    for(size_t i = 0;i<v;++i)
        adjList.push_back(list<int>());
}

Graph::Graph():vertices(0),edges(0)
{
}

void Graph::resizeGraph(int v)
{
    adjList.resize(v);
    vertices = v;
}

int Graph::getEdgeCount()const
{
    return edges;
}

int Graph::getVerticesCount()const
{
    return vertices;
}

void Graph::addEdge(int v, int w)
{
    //undirectional graph
    adjList[w].push_back(v);
    adjList[v].push_back(w);
    edges++;
}

const list<int>& Graph::adj(int v)const {
    return adjList[v];
}
