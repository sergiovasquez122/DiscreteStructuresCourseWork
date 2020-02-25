
#include "bfs.h"

BreadthFirstSearch::BreadthFirstSearch(const Graph &G, int s)
{
    marked.resize(G.getVerticesCount());
    //negative one is the 'nullptr'
    edgeTo.resize(G.getVerticesCount(),-1);
    source = s;
    bfs(G,source);
}

void BreadthFirstSearch::bfs(const Graph& G, int s){
    queue<int> vertices;
    vertices.push(s);
    marked[s] = true;
    while(!vertices.empty()){
        int v = vertices.front();
        vertices.pop();
        for(int elem : G.adj(v)){
            if(!marked[elem]){
                edgeTo[elem] = v;
                marked[elem] = true;
                vertices.push(elem);
            }
        }
    }
}

void BreadthFirstSearch::displayMarked()
{
    int counter  = 0;
    cout<<"SOURCE: "<<source<<endl;
    for(const bool& elem:marked)
        cout<<counter++<<": "<<elem<<endl;
}

void BreadthFirstSearch::displayEdgeTo(){
    int counter = 0;
    cout<<"SOURCE: "<<source<<endl;
    for(const int& elem:edgeTo)
        cout<<counter++<<": "<<elem<<endl;
}

bool BreadthFirstSearch::hasPathTo(int vertex)
{
    return marked[vertex];
}

vector<int>  BreadthFirstSearch::pathTo(int v)
{
    vector<int> content;
    if(hasPathTo(v)){
        for(int x = v;x!=source;x=edgeTo[x])
            content.push_back(x);
        content.push_back(source);
    }
    return content;
}

void BreadthFirstSearch::displayPathTo(int v)
{
    vector<int> path = pathTo(v);
    for(const auto& elem:path)
        cout<<elem<<' ';
    cout<<endl;
}

int BreadthFirstSearch::degreeOfSeperation(int v)
{
    return pathTo(v).size()-1;
}


void computeHistogram(BreadthFirstSearch& bfs,const Graph& graph)
{
    vector<int> hist(7);
    for(int i = 0;i<graph.getVerticesCount();++i)
        ++hist[bfs.pathTo(i).size()/2];
    displayHistogram(hist);
}

void displayHistogram(const vector<int> & content)
{
    for(int i = 0;i<content.size();++i)
        cout<<i<<": "<<content[i]<<endl;
}
