#include <iostream>
#include "graphbuilder.h"
#include "graph.h"
#include "bfs.h"
#include <regex>
using namespace std;

bool repeat(const char *title, string &line);
struct my_pair{
    string s;
    int d;

    my_pair(const string& s,int d):s(s),d(d){}

    friend bool operator<(const my_pair&x ,const my_pair& y){
        return x.d<y.d;
    }

    friend bool operator>(const my_pair& x,const my_pair& y){
        return x.d>y.d;
    }
};

int edit_distance(const string& s,const string& t){
    int n = s.size();
    int m = t.size();

    if(n==0)return m;
    if(m==0)return n;
    int cost;

    vector<vector<int>> A(n+1,vector<int>(m+1,0));

    for(int i = 0;i<=n;++i)
        A[i][0] = i;

    for(int j = 0;j<=m;++j)
        A[0][j] = j;

    for(int i = 1;i<=n;++i){
        char c = s[i-1];
        for(int j = 1;j<=m;++j){
            char d = t[j-1];
            if(c==d)cost = 0;
            else cost = 1;
            A[i][j] = min(min(A[i-1][j]+1,A[i][j-1]+1),A[i-1][j-1]+cost);
        }
    }
    return A[n][m];
}

vector<string> load_from_file(const string& file_name){
    ifstream file(filename);
    if(file.fail()) throw runtime_error("file not found");
    string line;
    vector<string> ret;
    while(getline(file,line))ret.push_back(line);
    return ret;
}

dequeue<string> top_n_choices(const string& target,int n,const vector<string>& database){
    priority_queue<my_pair> pq;
    for(const auto& s : database){
        int distance = edit_distance(s,target);
        if(pq.empty() || pq.size() < n)pq.push({s,distance});
        else if(pq.top().d > distance)pq.pop(),pq.push({s,distance});
    }
    deque<string> ret;
    while(!pq.empty()){
        ret.push_front(pq.top().s);
        pq.pop();
    }
    return ret;
}

int user_answer(int range,const deque<string>& v){
    cout<<"Did you mean?"<<endl;
    for(int i = 0;i<v.size();++i)
        cout<<(i+1)<<v[i]<<endl;

    string userinput;
    do{
    cout<<"Enter number desired or press enter to exit: ";
    getline(cin,userinput);
    }
    while(!regex_match(userinput,regex("([0-9]+|)")));
    if(userinput.empty()) return -1;
    int number = stoi(userinput);
    if(number>range)throw runtime_error("invalid");
    return number;
}

bool repeat(const char* title,string& line)
{
    cout<<title;
    getline(cin,line);
    return !line.empty();
}

int main()
{
    graphBuilder theGraph("movies.txt");
    auto database = load_from_file("movies.txt");
    BreadthFirstSearch bfs(theGraph.getGraph(),theGraph.index("Bacon, Kevin"));
    string userinput;
    while(repeat("ENTER: ",userinput)){
        if(theGraph.contains(userinput)){
            int target = theGraph.index(userinput);
            if(bfs.hasPathTo(target))
                cout<<"DEGREE OF SEPERATION: "<<((bfs.pathTo(target).size())/2)<<endl;
            for(int elem : bfs.pathTo(target))
                cout<<theGraph.getName(elem)<<endl;
        }
        else{
            int n = 5;
            auto v = top_n_choices(userinput,n,database);
            int item = user_answer(n,v);
            if(item == -1)exit(0);
            userinput = v[item];
            else{
            int target = theGraph.index(userinput);
            if(bfs.hasPathTo(target))
                cout<<"DEGREE OF SEPERATION: "<<((bfs.pathTo(target).size())/2)<<endl;
            for(int elem : bfs.pathTo(target))
                cout<<theGraph.getName(elem)<<endl;

            }
        }
    }
}
