/**
  AUTHOR: SERGIO VASQUEZ
  PROGRAM PURPOSE: Determines the prime decomposition of positve
                   natural numbers
  DATE CREATED: 11/10/17
  */
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
typedef unsigned int uint;
void sieveOfEratohenes(int arr);
void primeDecomposition(int n, bool prime[]);
bool getLine(string title, int &n);
int main()
{
    int n;
    while(getLine("Enter number: ",n))
    {
        sieveOfEratohenes(n);
    };
}
/**
 * @brief sieveOfEratohenes given an 'n' value
 *        iterate through and determine all prime numbers
 *        in the list
 * @param n integer value specified by the user
 */
void sieveOfEratohenes(int n){
    //make a boolean array to represent the prime values
    //intialize all values as true then set values
    //to false if they're a composition of a
    //previous iteration
    bool prime[n+1];
    int size = sizeof(prime)/sizeof(prime[0]);
    for(int i= 0;i<=size;i++)
        prime[i]=true;
    //Bounding condition as defined in wiki below
    //https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
    for(int i =2;i*i<=n;i++){
        if(prime[i])
            for (int j = i*i; j <= n; j+=i)
                prime[j]=false;
    }
    primeDecomposition(n,prime);
}
/**
 * @brief getLine getuser inputs and determine whether they have entered
 *                a line
 * @param title string that is used to display to the user th
 * @param n integer value address that will take in the content
 *          of the user entered string
 * @return true of false depending if the line contains content */
bool getLine(string title,int &n){
    cout<<title;
    string line;
    getline(cin,line);
    stringstream ss;
    ss<<line;
    ss>>n;
    return !line.empty();
}
/**
 * @brief primeDecomposition the function is determines the prime decomposition of a particular number
 * @param n the value inputted by the user
 * @param prime all the prime number leading to n and possibly including n
 */
void primeDecomposition(int n,bool prime[]){
    vector<int> decomposition;
    while (n>1) {
        int i = 2;
        while(true){
            if(prime[i]){
                if(n%i == 0 ){
                    n/=i;
                    decomposition.push_back(i);
                    break;
                }
            }
            i++;
        }
    }
    for (uint i = 0; i < decomposition.size(); ++i) {
        cout<<decomposition[i]<<"\t";
    }
    cout<<endl;
}
/*
Sample runEnter number: 12
2	2	3
Enter number: 3
3
Enter number: 15
3	5
Enter number: 90
2	3	3	5
Enter number: 24293
17	1429
Enter number: 1241
17	73
Enter number:
*/
