#include "graphbuilder.h"

graphBuilder::graphBuilder(const string& filename)
{
    ifstream file(filename);
    string line;
    while(getline(file,line))
    {
        stringstream ss(line);
        string partsOfLine;
        while(getline(ss,partsOfLine,'/'))
            if(!items.count(partsOfLine))
                items[std::move(partsOfLine)] = items.size()-1;
    }
    file.close();
    graph.resizeGraph(items.size());
    file.open(filename);
    while(getline(file,line)){
        vector<string> currentLineMovieAndActors;
        stringstream ss(line);
        string partsOfLine;
        while(getline(ss,partsOfLine,'/'))
            currentLineMovieAndActors.push_back(move(partsOfLine));
        int vertex = items.at(currentLineMovieAndActors[0]);
        for(size_t i = 1;i<currentLineMovieAndActors.size();++i)
            graph.addEdge(vertex,items[currentLineMovieAndActors[i]]);
    }
    keys.reserve(items.size());
    //INVERT THE INDEXS
    for(const std::pair<string,int>& elem:items)
        keys[items[elem.first]] = elem.first;
}

bool graphBuilder::contains(const string& str) const
{
    return items.count(str);
}

int graphBuilder::index(const string &str)const{
    return items.at(str);
}

const string &graphBuilder::getName(const int &index) const
{
    return keys[index];
}

const Graph& graphBuilder::getGraph() const
{
    return graph;
}
