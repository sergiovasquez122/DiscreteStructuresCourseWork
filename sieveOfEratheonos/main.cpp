/**
  AUTHOR: SERGIO VASQUEZ
  PROGRAM PURPOSE: Implements the 'Sieve of Erathoshenes algorithm
                   to compute all primes of a value n specified by the user
                   https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
  DATE CREATED: 11/10/17
  */
#include <iostream>
#include <sstream>
using namespace std;
void sieveOfEratohenes(int arr);
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
    for (int primes= 2; primes <= n; ++primes) {
        if(prime[primes])
            cout<<primes<<" ";
    }
    cout<<endl;
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
/* Sample run
Enter number: 100
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97
Enter number: 12
2 3 5 7 11
Enter number: 11
2 3 5 7 11
Enter number: 45
2 3 5 7 11 13 17 19 23 29 31 37 41 43
Enter number:
Press <RETURN> to close this window...
*/
