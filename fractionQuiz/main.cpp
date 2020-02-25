#include <fraction.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <regex>
using namespace std;
bool getLine(const char* title,string &line);
void validateEntry(string &line,string &name,int &numOfTimes);
void validateFraction(string &line,int &num,int &denom);
char generateOperation();
int generateDenominator();
int generateNumerator();
void display(const fraction &x, char op, const fraction &y, const fraction &z);
void perform(const fraction &x, char op, const fraction &y, fraction &ans);
bool getLine(const char *title, string &line);
int determineScore(int &num, int &denom, fraction &reduced);
void theGame(int &num, int &denom, int &numOfTimes, int &score);
void getUserFraction(int &num, int &denom);
void displayEndGame(const string &username, const int &numOfTimes, const int &score);
void reset(int &num, int &denominator, int &numOfTimes, int &score);
int main()
{
    srand(time(0));
    int numerator = 0 ,denominator = 1,numOfTimes=1,score = 0;
    string userInput,userName;
    while(getLine("Please enter your name and number of fractions: ",userInput)){
        validateEntry(userInput,userName,numOfTimes);
        theGame(numerator,denominator,numOfTimes,score);
        displayEndGame(userName,numOfTimes,score);
        reset(numerator,denominator,numOfTimes,score);
    }
}

void reset(int &num,int &denominator,int &numOfTimes,int &score){
    num = numOfTimes=score = 0;
    denominator = 1;
}

void displayEndGame(const string &username,const int &numOfTimes,const int &score){
    cout<<username<<" your score was "<<score<<"/"<<numOfTimes*2<<endl;
}

void getUserFraction(int &num,int& denom){
    string line;
    regex validExpression("-?[0-9]+(/([1-9]([0-9])*))?");
    getline(cin,line);
    while(!regex_match(line,validExpression)){
        cout<<"please enter valid number: ";
        getline(cin,line);
    }
    stringstream ss(line);
    ss>>num;
    if(ss.peek()=='/'){
        char junk;
        ss>>junk>>denom;
    }
    cin.clear();
}

void theGame(int &num,int &denom,int &numOfTimes,int &score){
    fraction lhs,rhs,reducedAns;
    char op;
    for(int i =0;i<numOfTimes;++i){
        num =1 ,denom =1;
        lhs.set(generateNumerator(),generateDenominator());
        op = '+';
        rhs.set(generateNumerator(),generateDenominator());
        perform(lhs,op,rhs,reducedAns);
        cout<<lhs<<' '<<op<<' '<<rhs<<" = ??? : ";
        //Only used for testing purposes
        //display(lhs,op,rhs,reducedAns);
        getUserFraction(num,denom);
        score += determineScore(num,denom,reducedAns);
    }
}

int determineScore(int &num, int &denom,fraction &reduced)
{
    if(num == reduced.getNum() && denom==reduced.getDenom())
        return 2;
    else if(fraction(num,denom)==reduced)
        return 1;
    return 0;
}

void validateEntry(string &userInput, string &name, int &numOfTimes){
    regex validExpression("[A-Za-z]+ [0-9]+");
    while(!regex_match(userInput,validExpression)){
        cout<<"Please enter valid name and number of fractions to generate: ";
        getline(cin,userInput);
    }
    stringstream ss(userInput);
    ss>>name>>numOfTimes;
    for(u_int i = 0;i<name.length();i++)
        name[i]= toupper(name[i]);
}

int generateNumerator(){
    return pow(-1,rand()%2)*(rand()%8+1);
}

int generateDenominator(){
    while(rand()%8+1==0);
    return rand()%8+1;
}

char generateOperation(){
    char op;
    switch (rand()%4) {
    case 0:
        op = '+';
        break;
    case 1:
        op = '-';
        break;
    case 2:
        op = '/';
        break;
    case 3:
        op = '*';
        break;
    }
    return op;
}

void perform(const fraction &x, char op, const fraction &y, fraction &ans)
{
    switch(op)
    {
    case '+':
        ans = x+y;
        break;
    case '-':
        ans =  x-y;
        break;
    case '*':
        ans = x*y;
        break;
    case '/':
        ans = x/y;
        break;
    }
}

bool getLine(const char *title, string &line){
    cout<<title;
    getline(cin,line);
    return !line.empty();
}

void display(const fraction &x, char op, const fraction &y, const fraction &z){
    cout<<x<<" "<<op<<" "<<y<<" = "<<z<<endl;
}

