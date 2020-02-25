#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

struct my_pair{
    string s;
    int d;
    my_pair(const string& s,int d):s(s),d(d){}
    friend bool operator<(const my_pair& x,const my_pair& y){
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

            if(c == d)cost = 0;
            else cost = 1;

            A[i][j] = min(min(A[i-1][j]+1,A[i][j-1]+1),A[i-1][j-1]+cost);
        }
    }
    return A[n][m];
}

vector<string> load_from_file(const string& file_name){
    fstream file(file_name);
    if(file.fail())throw runtime_error("file not found");
    string line;
    vector<string> ret;
    while(getline(file,line)){
        ret.push_back(line);
    }
    return ret;
}

bool getLine(const char* title,string &userinput){
    cout<<title;
    getline(cin,userinput);
    return !userinput.empty();
}

deque<string> top_n_choices(const string& target,int n,const vector<string>& database){
    priority_queue<my_pair> pq;
    for(const auto& s : database){
        int distance = edit_distance(s,target);
        if(pq.empty() || pq.size() < n) pq.push({s,distance});
        else if(pq.top().d > distance)pq.pop(),pq.push({s,distance});
    }
    deque<string> ret;
    while(!pq.empty()){
        ret.push_front(pq.top().s);
        pq.pop();
    }
    return ret;
}

int main() {
    vector<string> database = load_from_file("/home/sergio/Desktop/LevehsteinDistance/database.txt");
    string userinput;
    while(getLine("Enter: ",userinput)){
       auto v = top_n_choices(userinput,5,database);
       cout<<"TOP 5 CHOICES ARE: "<<endl;
       for(int i = 0;i<v.size();++i){
           cout<<(i+1)<<": "<<v[i]<<endl;
       }
    }
}