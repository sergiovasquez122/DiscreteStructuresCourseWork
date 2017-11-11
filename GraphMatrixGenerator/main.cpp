/**
  AUTHOR:SERGIO VASQUEZ
  PROGRAM PURPOSE: Program asks user for size of matrix, how many nodes are connected and weight
                   displays a matrix containing all the information
                   save content into a file format
  DATE CREATED: 11/10/17
  */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#define SIZE 10
using namespace std;

typedef unsigned int uint;

void initialize(bool graph[][SIZE], uint size);
uint getTotalVertices();
void linkVerticies(bool graph[][10],int [][10], uint size);
bool getline(uint &r, uint &c);
void printGraph(bool graph[][SIZE], uint size);
bool getQuery(uint &r, uint &c);
void query(bool graph[][SIZE], int weight[][SIZE]);

int main()
{
    int weightOfGraph[SIZE][SIZE]={0};
    bool graph[SIZE][SIZE];
    uint size = getTotalVertices();
    initialize(graph,size);
    linkVerticies(graph,weightOfGraph,size);
    printGraph(graph,size);
    query(graph,weightOfGraph);
    return 0;
}
/**
 * @brief getline: functions ask user for a respective row, column and weight of the specifed node
 * @param r: Integer value specifed by the userr represents the row of the  matrix
 * @param c: Integer value specifed by the userr represents the column of the  matrix
 * @param w: Integer value specifed by the userr represents the weight of the  node
 * @return true of false depending on whether the user has input content
 */
bool getline(uint &r, uint &c, uint &w)
{
    stringstream ss;
    string line;
    cout<<"Vertices to connect and associated weight (r)ow (c)olumn (w)eight : ";
    getline(cin,line);
    uint pos;
    while((pos = line.find_first_not_of("0123456789 ")) < line.size())
        line[pos] = ' ';
    ss<<line;
    ss>>r>>c>>w;
    return !line.empty();
}

/**
 * @brief linkVerticies: Given the user input the graph will intialize the specified row and column
 * @param graph: 2D boolean array with a fixed size, used to represent whether a node is connected
 * @param weightOfGraph: 2D integer array with a fixed size,used to determine the weight of a node
 * @param size: A integer value specifed by the user, represents the size of the NxN matrix that will be printed
 */
void linkVerticies(bool graph[][SIZE], int weightOfGraph[][SIZE],uint size)
{
    ofstream output("//home//sergio//Desktop//CS45//creditCardFileRead//graph//graph.txt");
    output<<size<<endl;
    uint r,c,w;
    cin.ignore(255,'\n');
    while(getline(r,c,w))
    {
        output<<r<<" "<<c<<" "<<w<<endl;
        graph[r][c] = !graph[r][c];
        weightOfGraph[r][c] = w;
        printGraph(graph,size);
    }
    output.close();
}
/**
 * @brief getTotalVertices: Function determines the NxN matrix the user wants
 * @return integer value with the size of the NxN matrix
 */
uint getTotalVertices()
{
    uint size;
    do
    {
        cout<<"How many vertices are in your graph? ";
        cin>>size;
    }while(size > 10);
    return size;
}
/**
 * @brief initialize The constant 'SIZE' is used to pass an 2D array without pointers,
 *        we will only intialize the actual size we need
 * @param graph: 2D boolean array with a fixed size, used to represent whether a node is connected
 * @param size: A integer value specifed by the user, represents the size of the NxN matrix that will be printed
 */
void initialize(bool graph[][SIZE], uint size)
{
    for(uint i = 0; i < size; ++i)
        for(uint j = 0; j < size; ++j)
            graph[i][j] = false;
}
/**
 * @brief printGraph: Display content of graph to the user
 * @param graph: 2D boolean array with a fixed size, used to represent whether a node is connected
 * @param size: A integer value specifed by the user, represents the size of the NxN matrix that will be printed
 */
void printGraph(bool graph[][SIZE], uint size)
{
    cout<<endl<<endl<<setw(3)<<"|";
    for(uint i = 0; i < size; ++i)
        cout<<setw(3)<<i;
    cout<<endl<<setfill('-')<<setw(3+size*3)<<"-"<<setfill(' ')<<endl;
    for(uint i = 0; i < size; ++i)
    {
        cout<<setw(2)<<i<<"|";
        for(uint j = 0; j < size; ++j)
            if(graph[i][j])
                cout<<setw(3)<<"T";
            else
                cout<<setw(3)<<"F";
        cout<<endl;
    }
    cout<<endl<<endl;
}
/**
 * @brief query: Ask the user if they would like to determine the content of a certain node
 * @param graph: 2D boolean array with a fixed size, used to represent whether a node is connected
 * @param weight: 2D integer array with a fixed size,used to determine the weight of a node
 */
void query(bool graph[][SIZE],int weight [][SIZE]){
    uint r,c;
    while(getQuery(r,c))
        if(graph[r][c])
            cout<<"Graph is connected the weight associated with this graph is : "<<weight[r][c]<<endl;
        else
            cout<<"No connection!"<<endl;

}
/**
 * @brief getQuery: continously ask user for the content of the node until they enter an empty line
 * @param r: integer value used to represent the 'row' of the matrix
 * @param c: integer value used to represent the 'col' of the matrix
 * @return true of false depending on whether the user has entered content
 */
bool getQuery(uint &r, uint &c)
{
    stringstream ss;
    string line;
    cout<<"Query vertice connection (r)ow (c)olumn : ";
    getline(cin,line);
    uint pos;
    while((pos = line.find_first_not_of("0123456789 ")) < line.size())
        line[pos] = ' ';
    ss<<line;
    ss>>r>>c;
    return !line.empty();
}
/*Sample run
How many vertices are in your graph? 3
Vertices to connect and associated weight (r)ow (c)olumn (w)eight : 0 0 1


  |  0  1  2
------------
 0|  T  F  F
 1|  F  F  F
 2|  F  F  F


Vertices to connect and associated weight (r)ow (c)olumn (w)eight : 0 2 4


  |  0  1  2
------------
 0|  T  F  T
 1|  F  F  F
 2|  F  F  F


Vertices to connect and associated weight (r)ow (c)olumn (w)eight : 1 1 9


  |  0  1  2
------------
 0|  T  F  T
 1|  F  T  F
 2|  F  F  F


Vertices to connect and associated weight (r)ow (c)olumn (w)eight : 2 0 8


  |  0  1  2
------------
 0|  T  F  T
 1|  F  T  F
 2|  T  F  F


Vertices to connect and associated weight (r)ow (c)olumn (w)eight :


  |  0  1  2
------------
 0|  T  F  T
 1|  F  T  F
 2|  T  F  F


Query vertice connection (r)ow (c)olumn : 12
No connection!
Query vertice connection (r)ow (c)olumn : 1 2
No connection!
Query vertice connection (r)ow (c)olumn : 0 0
Graph is connected the weight associated with this graph is : 1
Query vertice connection (r)ow (c)olumn : 0 2
Graph is connected the weight associated with this graph is : 4
Query vertice connection (r)ow (c)olumn :
Press <RETURN> to close this window...

*/
