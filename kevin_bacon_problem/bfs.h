#ifndef BFS_H
#define BFS_H
#include <queue>
#include "graph.h"
using std::queue;
class BreadthFirstSearch
{
public:
    BreadthFirstSearch(const Graph& G, int s);
    void bfs(const Graph& G,int s);
    bool hasPathTo(int vertex);
    void displayMarked();
    void displayEdgeTo();
    int degreeOfSeperation(int v);
    vector<int> pathTo(int v);
    void displayPathTo(int v);
private:
    int source;
    vector<int> edgeTo;
    vector<bool> marked;
};
//Is used to test the validity of data specifically for the kevin bacon problem
void computeHistogram(BreadthFirstSearch &, const Graph &);
void displayHistogram(const vector<int>&);
#endif // BFS_H
