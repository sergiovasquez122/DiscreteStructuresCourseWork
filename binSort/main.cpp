/**
  *PURPOSE:
  *    Implements bucket sort to sort list
  *    provided by rng
  *AUTHOR:
  *     Sergio Vasquez
  *CREATED ON:
  *     10/29/17
  *LAST MODIFIED
  *     10/30/17
  */
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

void printTable(string title, const vector<int> &list, int max);
int getInput(string title,int min, int max);
void generateNumbers(int total, int min, int max, vector<int> &list);
vector<int> binSort(const vector<int> &list);
vector<int> mixedSort(const vector<int> &list);

typedef unsigned int u_int;
int main()
{
    vector<int> list, sortedList;
    srand(time(NULL));
    int min = getInput("Lowest number to see: ", -1000, 1000),
            max = getInput("Highest number to see: ", 0, 1000),
            total = getInput("Total random numbers: ",10,1000000000);
    generateNumbers(total, min, max, list);
    printTable("Unsorted Data: ", list, max);
    sortedList = mixedSort(list);
    printTable("Sorted Data", sortedList, max);
    return 0;
}

/**
 * @brief printTable Display 'pretty' table to the user of successful
 *        bucketsort
 * @param title string entered by the programmer
 * @param list  the vector which we are displaying their elements
 * @param max   The largest value the rng can produced
 *              is used to calculate the space between columns
 */
void printTable(string title, const vector<int> &list, int max)
{
    int colWidth = log10(max) + 3,
            numCol = 80/colWidth;
    cout<<endl<<title<<endl;
    for(unsigned int i = 0; i < list.size(); ++i)
    {
        if(i%numCol == 0)
            cout<<endl;
        cout<<setw(colWidth)<<list[i];
    }
    if(list.size()%numCol != 0)
        cout<<endl;
    cout<<endl;
}
/**
 * @brief getInput asks for and verifiy userinput
 * @param title string that will be displayed to the user
 * @param min
 * @param max
 *          min,max are used to ensure the user does not
 *          go beyond the values of our rng calculator
 * @return return an integer of the userinput
 */
int getInput(string title,int min, int max)
{
    int answer;
    bool repeat;
    do
    {
        repeat = false;
        cout<<title;
        cin>>answer;
        if(answer < min || answer > max)
        {
            cout<<"Your input is out of range."<<endl;
            repeat = true;
        }
    }while(repeat);
    return answer;
}
/**
 * @brief generateNumbers rng used to accumilate random values into vector
 * @param total
 *         The number of iterations are generator will go through
 *          Specified by the programmers
 * @param min
 * @param max
 *          integer values specified by the programmer
 * @param list
 *          A modified vector with random values
 */
void generateNumbers(int total, int min, int max, vector<int> &list)
{
    list.clear();
    for( int i = 0; i < total; ++i)
        list.push_back(rand()%(max-min+1) + min);
}
/**
 * @brief binSort processing step of the program, takes in list of vectors and sorts them
 * @param list unordered vector produced by rng
 * @return sorted vector
 */
vector<int> binSort(const vector<int> &list)
{
    vector<int> data, bins[10];
    int digit = 1, binNumber;
    data = list;
    while(data.size() != bins[0].size())
    {
        for(unsigned int i = 0; i < 10; ++i)
            bins[i].clear();
        for(unsigned int i = 0; i < data.size(); ++i)
        {
            binNumber = (data[i]/digit)%10;
            bins[binNumber].push_back(data[i]);
        }
        data.clear();
        for(unsigned int i = 0; i < 10; ++i)
            for(unsigned int j = 0; j < bins[i].size(); ++j)
                data.push_back(bins[i][j]);
        digit *= 10;
    }
    return data;
}
/**
 * @brief mixedSort Preprocessing step for bucketsort,(bucket sort normally can't bucket sort negative values)
 *          takes in list of integer values and sorts all negative and positive values independent from each other
 *          then place them into one sorted vector
 * @param list unsorted list of integers produced by rng
 * @return sorted list of vector
 */
vector<int> mixedSort(const vector<int> &list){
    vector<int> neg;
    vector<int> pos;
    for (u_int i = 0; i < list.size(); ++i) {
        if(list[i]<0)
            neg.push_back(-1*list[i]);
        else
            pos.push_back(list[i]);
    }
    neg = binSort(neg);
    reverse(neg.begin(),neg.end());
    for (u_int var = 0; var < neg.size(); ++var) {
        neg[var]=-1*neg[var];
    }
    pos = binSort(pos);
    for (u_int var = 0; var < pos.size(); ++var) {
        neg.push_back(pos[var]);
    }

    vector<int> sorted = neg;
    return sorted;
}

/*
sample run:
s
Lowest number to see: -10
Highest number to see: 10
Total random numbers: 100

Unsorted Data:

   5   8   5  -4  -3  -9  -2 -10   1   0  10  -2  -7  -5   0   2   0  10  -8   2
  -6   8  -9  -4  -2  -7   5  -3  -4   8   4   9   5  -4  -5 -10  -3   3   9   8
 -10   9  -5  -6  -7   6   4   2   5   4  -7   8   1  -6  -7   9  -5   6  -6   1
   3   6   0  -4  -9   3  -6  -1  -5  -8  -4  -6 -10   0  -4  -8  -7  10   4   6
   2   7   3 -10   9   6   8  -6   1  -9   3  -8   7 -10  -4   6   3   0  -6   7

Sorted Data

 -10 -10 -10 -10 -10 -10  -9  -9  -9  -9  -8  -8  -8  -8  -7  -7  -7  -7  -7  -7
  -6  -6  -6  -6  -6  -6  -6  -6  -5  -5  -5  -5  -5  -4  -4  -4  -4  -4  -4  -4
  -4  -3  -3  -3  -2  -2  -2  -1   0   0   0   0   0   0   1   1   1   1   2   2
   2   2   3   3   3   3   3   3   4   4   4   4   5   5   5   5   5   6   6   6
   6   6   6   7   7   7   8   8   8   8   8   8   9   9   9   9   9  10  10  10
*/
