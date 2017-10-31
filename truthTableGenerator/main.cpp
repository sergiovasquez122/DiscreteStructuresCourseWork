/**
* Test1
* DUE: 10/10/17
* NAME: Luz Acevedo, Sergio Vasquez
* PURPOSE: Program allows user to do computerized proofs with truth table, supports adding,printing,storing,loading,and comparing truth tables
*/
#include<iostream>
#include<cstdlib>  //for exit()
#include<string>
#include <map>
#include <sstream>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <iterator>


#define SIZE 100

using namespace std;

bool pop(bool stack[], int &tos, bool &safe);
void push(bool value, bool stack[], int &tos, bool &safe);
double convert(string value);
bool getLine(string &line);
void display(const string &line, string postfix);
void push(string item, string stack[], int &top, bool &safe);
string pop(string stack[], int &top, bool &safe);
bool isOperator(string symbol);
void loadPrecedenceMap(map<string,int> &theMap);
void trimString(string &input);
int precedence(string symbol, map<string, int> theMap, bool &safe);
string getToken(string &line);

bool infixToPostfix(string infixExp, string &postfixExp, map<string,int> precedenceMap);
string process(string infixExp, map<string, int> theMap, string &postfixExp);
bool evaluate(string postfixExp, bool &safe);
void normalize(string &line);
bool getPostFix(string postfix);
int getVariables(string input,vector<char> &listOfVariables);
void displayVariable(const vector<char> &listOfVariables);
void processVariable(string input);
void displayRow(string expression, unsigned int totalRows, vector<char> list, unsigned int row);
bool evaluateVariable(string &expression, int currentRow, vector<char> variables);
void makeTable(string expression, const vector<char> &listOfVariables);
void help();
bool displayCommands(string line, vector<string> &expressions,map<string,int> precedence);
string find(string line, int pos, int commandsize);
inline bool exists(const string& name);
void fileOpen(string &fileName, vector<string> &expressions);
void fileLoad(string &fileName, vector<string> &expressions);
void wexit(string &fileName, vector<string> &expressions);
int isfind(string &line, int pos, int commandsize);
void statement(bool compare,string expression1,string expression2);
bool compare(string &expression1,string &expression2, int currentRow, vector<char> variables);
void processComparesVariable(string input, string input2);
void compareRow(string expression, string expression2, unsigned int totalRows, vector<char> list, unsigned int row);
typedef unsigned int u_int;

/* main function begins */
int main()
{
   string infixExp,postfixExp, expression, input, fileName;
   vector<string> expressions;
   ifstream in;
   ofstream out;
   bool safe;
   map<string,int> precedence;        // Table of operator precedence
   loadPrecedenceMap(precedence);

   while (getLine(input)){
       displayCommands(input,expressions,precedence);
   }

   return 0;
}
/**
* PURPOSE: Takes in user input and perform command if valid
* PARAMETER:
*     str, line
*      line entered by the user
*     vector<string> &expression
*      All expression users have stored
*      map<string,int> precedence
*      An associative array that matches a string values with an integer value
* RETURN VALUE:
* return true or false
*/
bool displayCommands(string line, vector<string> &expressions, map<string,int> precedence){

   bool temp;
   int j=12;
   string infixExp, expression, command, postfixExp, fileName, expression1,expression2,
           postfixExp1, postfixExp2;
   int pos = 0, commandsize, exp_1, exp_2;
   int currentRow;
   vector<char> listOfVariables;
   stringstream ss;
   normalize(line);


   string commands[11] = {"NEW", "DELETE", "TABLE", "IS", "LIST", "STORE", "LOAD", "EDIT", "EXIT", "WEXIT", "HELP"};
   for (int i = 0; i < 11; ++i){
       if ((pos = line.find(commands[i])) < line.size()){
           if (commands[i] == "IS"){
               if (line == "LIST"){ // May only work in certain cases. Easy to break!;
                   i = 4;
               }
           }
           if (commands[i] == "EXIT"){
               if ((pos = line.find("W")) < line.size()){ // May only work in certain cases. Easy to break!;
                   i = 9;
               }
           }

           j = i;
           command = commands[j];
           commandsize = command.size();
           break;
       }
   }
   switch (j) {
       // NEW
       case 0:  expression = find(line,pos,commandsize);
           expressions.push_back(expression);
           cout << expression << " stored as Expression " << expressions.size() << endl;
           break;
           // DELETE
       case 1:  expression = find(line,pos,commandsize);
           if (expression.find("0123456789") < expression.size()-1){
               pos = stoi(expression) - 1;
           }
           if ((expressions.size() > 0) && (pos<=expressions.size())){
               cout << "Expression" << expression << " was deleted!" << endl;
               expressions.erase(expressions.begin() + pos);
           }
           else if (expressions.size() == 0){
               cout << "No expressions stored!" << endl;
           }
           else if (pos>expressions.size()-1){
               cout << pos << endl;
               cout << expressions.size() << endl;
               cout << "No such expression exists!" << endl;
           }
           break;

           // TABLE
       case 2:
           expression = find(line,pos,commandsize);
           ss << expression;
           ss >> pos;
           expression = expressions.at(pos-1);
           process(expression, precedence, postfixExp);   // Process the input

           if(getPostFix(postfixExp)){
               normalize(postfixExp);
               processVariable(postfixExp);
           }

           break;
           //IS
       case 3: exp_1 = isfind(line,pos,commandsize);
           exp_2 = isfind(line,pos,commandsize);
           expression1 = expressions.at(exp_1-1);
           expression2 = expressions.at(exp_2-1);
           process(expression1, precedence, postfixExp1);
           process(expression2, precedence, postfixExp2);
           if(getPostFix(postfixExp1)&&getPostFix(postfixExp2)){
               normalize(postfixExp1);
               normalize(postfixExp2);
               processComparesVariable(postfixExp1,postfixExp2);
           }
           break;
           //LIST
       case 4:

           for (int x = 0; x != expressions.size(); ++x)
           {
               cout << expressions[x] << " is Expression " << x+1 << endl;
           }

           break;
           //STORE
       case 5: fileName = find(line,pos,commandsize);
           fileOpen(fileName, expressions);
           break;
           //LOAD
       case 6: fileName = find(line,pos,commandsize);
           fileLoad(fileName, expressions);
           break;
           //EDIT
       case 7: exp_1 = isfind(line,pos,commandsize);
               char choice;
               expression1 =  expressions.at(temp);

               cout << "Please enter a new expression for expression " << exp_1 << endl;
               getline(cin,expression);

                       if ((pos = expression.find_first_of("new")) < expression.size()){
                           expression = find(expression,0,3);
                       }
                       normalize(expression);
                       for (string a : expressions) {
                           if(a.find(expression) && (a.size() == expression.size()+1)){
                               cout << "Sorry! That expression already exists!" << endl;
                               break;
                           }
                           else {
                               replace(expressions.begin(), expressions.end(), expression1, expression);
                           }
                        }

                       cin.clear();
           break;
           //EXIT
       case 8: cout << "You have exited the program!" << endl;
           exit(0);
           break;
           //WEXIT
       case 9: fileName = find(line,pos,commandsize);
           wexit(fileName,expressions);
           break;
           //HELP
       case 10: help();
           break;

       default: cout << "Do you need help? Please enter HELP!" << endl;
           break;

   }
   return temp;
}
string find(string line, int pos, int commandsize){
   string temp;
   if (pos != string::npos){
       temp = line.substr(commandsize,line.size()-1);
   }
   return temp;
}
int isfind(string &line, int pos, int commandsize) {
   stringstream ss;

   /* Storing the whole string into string stream */

   /* Running loop till the end of the stream */
   string temp,temp2;
   int value;
   pos = 0;

   string separators[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
   for (int i = 0; i < 10; i++){
       if ((pos = line.find(separators[i])) < line.size()){
           ss << line[pos];
           line = line.erase(0,pos);
           ss >> value;
       }
   }
   //  cout << "VALUE!: " << value << endl;
   return value;
}

void wexit(string &fileName, vector<string> &expressions){
   fileOpen(fileName, expressions);
   exit(0);
}

void fileOpen(string &fileName, vector<string> &expressions){
   ofstream out;
   int pos, choice;
   string again;
   do
   {
       again = "N";
       if (again == "Y"){
           cout<<"Enter a filename to store to: ";
           cin>>fileName;
       }

       if ((pos = fileName.find(".truth") < fileName.size()) || (pos = fileName.find(".TRUTH") < fileName.size())){
           if(exists(fileName)){
               out.open(fileName);
               cout << "This file already exists! Do you want to erase it (1) or give it another name? ";
               cin >> choice;

               switch (choice) {
                   case 1:
                       cout << "You have stored your expressions in: " << fileName << endl;
                       for (int x = 0; x != expressions.size(); ++x)
                       {
                           out << expressions[x] << " is Expression " << x+1 << endl;
                       }
                       break;
                   case 2: fileOpen(fileName, expressions);

                       break;

                   default: cout << "Incorrect command!" << endl;
                       break;
               }
           }
           else{
               cout<<"File does not exist! Program will create it for you!"<<endl;
               out.open(fileName);
               for (int x = 0; x != expressions.size(); ++x)
               {
                   out << expressions[x] << " is Expression " << x+1 << endl;
               }

           }

       }
       else {
           for(unsigned int i = 0; i < fileName.size(); ++i)
               fileName[i] = tolower(fileName[i]);

           cout << "FILE NAME: " << fileName << endl;
           fileName += ".truth";
           if(exists(fileName)){
               out.open(fileName);
           }
           else{
               cout<<"File does not exist! Program will create it for you!"<<endl;
               out.open(fileName);
               for (int x = 0; x != expressions.size(); ++x)
               {
                   out << expressions[x] << " is Expression " << x+1 << endl;
               }
           }

       }

       cout<<"Do you want to check another file? ";
       getline(cin,again);
       cin.ignore(255,'\n');
   }while(toupper(again[0]) == 'Y');

}
void fileLoad(string &fileName, vector<string> &expressions){
   ifstream in;
   int pos, choice;
   string again, expression;
   do
   {
       again = "N";
       if (again == "Y"){
           cout<<"Enter a filename to load from: ";
           cin>>fileName;
       }

       if ((pos = fileName.find(".truth") < fileName.size()) || (pos = fileName.find(".TRUTH") < fileName.size())){
           if(exists(fileName)){
               in.open(fileName);
               cout << "This file exists! The program will now load it..." << endl;

               while (!in.eof()){
                   getline(in,expression);
                   cout << expression << endl;
                   expressions.push_back(expression);
               }
           }
           else{
               cout<<"File does not exist!"<<endl;
               //                fileLoad(fileName, expressions);
           }

       }
       else {
           for(unsigned int i = 0; i < fileName.size(); ++i)
               fileName[i] = tolower(fileName[i]);

           fileName += ".truth";
           if(exists(fileName)){
               cout << "This file exists! The program will now load it..." << endl;

               while (!in.eof()){
                   getline(in,expression);
                   cout << expression << endl;
                   expressions.push_back(expression);
               }
           }
           else{
               cout<<"File does not exist!"<<endl;
               //                fileLoad(fileName, expressions);
           }

       }

       cout<<"Do you want to check another file? ";
       getline(cin,again);
       cin.ignore(255,'\n');
   }while(toupper(again[0]) == 'Y');

}
inline bool exists(const string& name) {
   struct stat fileInfo;
   return (stat(name.c_str(), &fileInfo) == 0);
}
/**
* PURPOSE: To inform user of the the possible commands the user can use
* PARAMETER:
*      NONE
* RETURN VALUE:
*       NONE
*/
void help()
{
   cout << "Enter NEW followed by a boolean expression to store an expression" << endl;
   cout << "Enter TABLE followed by the number of variables to print out a truth table" << endl;
   cout << "Enter LOAD followed by a file name to load expressions from a file" << endl;
   cout << "Enter EXIT to exit the program" << endl;
   cout << "Enter WEXIT followed by a file name to write to a file and exit" << endl;
   cout << "Enter DELETE followed by an expression number to delete an expression" << endl;
   cout << "Enter STORE followed by a filename to store expressions in a file" << endl;
   cout << "Enter EDIT followed by an expression number to edit an expression" << endl;
}
/**
* PURPOSE: Makes the table for specified expression
* PARAMETER:
*      String &expression,
*          string containing postfix
*      vector<char>  &lisofvariables
*          variables contained in user postfix expressions
* RETURN VALUE:
* NONE
*/
void makeTable(string expression, const vector<char> &listOfVariables)
{
   unsigned int totalRows = pow(2,listOfVariables.size());
   cout<<endl<<endl;
   for(unsigned int i = 0; i < listOfVariables.size(); ++i)
       cout<<setw(3)<<listOfVariables[i];
   cout<<"|"<<setw(8)<<"Output"<<endl
       <<setw(listOfVariables.size()*3 + 10)
       <<setfill('-')<<"-"<<setfill(' ')<<endl;
   for(unsigned int currentRow = 0; currentRow < totalRows; ++currentRow)
       displayRow(expression, totalRows,listOfVariables,currentRow);
}
/**
* PURPOSE: finds the total amount of rows and iterate through
* PARAMETER:
*     str, &expression
*     str, &expression2
*          two postfix expressions entered by the user
*      const vector<char>
* RETURN VALUE:
*      NONE
*/
void compareTable(string expression,string expression2,const vector<char> &listOfVariables){
   unsigned int totalRows = pow(2,listOfVariables.size());
   for(unsigned int currentRow = 0; currentRow < totalRows; ++currentRow)
       compareRow(expression, expression2,totalRows,listOfVariables,currentRow);
}
int counter = 0;
/**
* PURPOSE: Takes in two post-fix expression string and compare whether they are semantically equivalents
* PARAMETER:
*     str, &expression
*     str, &expression2
*          two postfix expressions entered by the user
*     int currentRow
*          the row the boolean expression is evaluating
*      vector<char> variables
*
* RETURN VALUE:
* Return true or false depending on the expression comparision
*/
bool compareVariable(string &expression,string &expression2, int currentRow, vector<char> variables){
   bitset<26> theBits(currentRow);
   int pos;
   bool safe;
   for(unsigned int i = 0; i < variables.size(); ++i)
   {
       unsigned bitIndex = variables.size()-1 - i;
       while((pos = expression.find(variables[i])) < expression.size()){
           expression[pos] = (char)(48 + theBits[bitIndex]);
           expression2[pos] = (char)(48 + theBits[bitIndex]);
       }
   }
   bool val = evaluate(expression,safe);
   bool val2 = evaluate(expression2,safe);
   if(val != val2 && (currentRow+1)==variables.size()){
       cout<<"Statements are not equivalent"<<endl;
       counter =0;
   }
   else if(val==val2)
       counter++;
   if(variables.size()==counter/2){
       counter =0;
       cout<<"Statements are equivalent"<<endl;
   }
}

/**
* PURPOSE: Iterate through table and outputs 't' or 'f' depending on expression operators
* PARAMETER:
*      String &expression,
*          string containing postfix
*      int currentRow
*          row currently being evaluated
*      vector<char> variables
* RETURN VALUE:
* NONE
*/
bool evaluateVariable(string &expression, int currentRow, vector<char> variables)
{
   bitset<26> theBits(currentRow);
   int pos;
   bool safe;
   for(unsigned int i = 0; i < variables.size(); ++i)
   {
       unsigned bitIndex = variables.size()-1 - i;
       while((pos = expression.find(variables[i])) < expression.size())
           expression[pos] = (char)(48 + theBits[bitIndex]);
   }
   bool val = evaluate(expression,safe);
   //    cout<<expression;
   //    cout << "   |";
   if(val)
       cout<<setw(3)<<"T";
   else
       cout<<setw(3)<<"F";

}

void displayRow(string expression, unsigned int totalRows, vector<char> list, unsigned int row)
{
   bitset<26> current(row);
   for(int i = list.size()-1; i >= 0; --i)
       if(current[i])
           cout<<setw(3)<<"T";
       else
           cout<<setw(3)<<"F";
   cout<<"|";
   evaluateVariable(expression, row, list);
   cout<<endl;
}

void compareRow(string expression, string expression2,unsigned int totalRows, vector<char> list, unsigned int row){
   bitset<26> current(row);
   compareVariable(expression,expression2, row, list);
   cout<<endl;
}
/**
* PURPOSE: Ensure expression is not empty
* PARAMETER:
*      String postfix
*             expression user entered in postfix notation
* RETURN VALUE:
* true or false depending on postfix is empty
*/
bool getPostFix(string postfix)
{
   return !postfix.empty();
}
/**
* PURPOSE: Preprocessing steps to make the table of specifed expression
* PARAMETER:
*      string input,
*              input specified by the user
* RETURN VALUE:
* NONE
*/
void processVariable(string input)
{
   vector<char> listOfVariables;
   int totalVars = getVariables(input, listOfVariables);
   displayVariable(listOfVariables);
   makeTable(input, listOfVariables);
}
/**
* PURPOSE: Handles the preprocessing of two string expression to compare if there are equivalent
* intialize all variables necessary for processing
* PARAMETER:
*      String input
*          input entered by user
*      string input2
*          second input entered by user
* RETURN VALUE:
* NONE
*/
void processComparesVariable(string input,string input2)
{
   vector<char> listOfVariables;
   int totalVars = getVariables(input, listOfVariables);
   compareTable(input,input2, listOfVariables);
}
/**
* PURPOSE: Searches input string specified by the user and
*          finds how many variables are contained
* PARAMETER:
*      string input,
*      string entered by the user
*      Vector <char> &listOfVariables
*              char vector specified in function processVariable,
*              stores uppercase alphabetical variables from
*              input
* RETURN VALUE:
* The amount of alphabetical variables in the user specifed expression
*/
int getVariables(string input,vector<char> &listOfVariables)
{
   char var = 'A';
   for(; var <= 'Z'; ++var)
       if(input.find(var) < input.size())
           listOfVariables.push_back(var);
   return listOfVariables.size();
}
/**
* PURPOSE: Displays to the user the the variables content and total amount of variables in the expression
* PARAMETER:
*     str, line
*      line entered by the user
*     vector<string> &expression
*      All expression users have stored
*      map<string,int> precedence
*      An associative array that matches a string values with an integer value
* RETURN VALUE:
* Return true or false depending on the expression comparision
*/
void displayVariable(const vector<char> &listOfVariables)
{
   cout<<"You have "<<listOfVariables.size()<<" variables in your expression.\nThey are:\n";
   for(unsigned int i = 0; i < listOfVariables.size(); ++i)
       cout<<listOfVariables[i]<<" ";
   cout<<endl<<endl;
}

/**
* PURPOSE: Takes in string entered by the user and removes whitespaces and uppercases characters
* PARAMETER:
*     str, &expression
*     str, &expression2
*          two postfix expressions entered by the user
*     int currentRow
*          the row the boolean expression is evaluating
*      vector<char> variables
*
* RETURN VALUE:
* Return true or false depending on the expression comparision
*/
void normalize(string &line)
{
   for(unsigned int i = 0; i < line.size(); ++i)
       line[i] = toupper(line[i]);
   while(line[0] == ' ')
       line.erase(0,1);
   while(line[line.size()-1] == ' ')
       line.erase(line.size()-1);
}


// define push operation
void push(string item, string stack[], int &top, bool &safe)
{
   safe = true;
   if(++top > SIZE-1)
   {
       cout<<endl<<"Stack Overflow."<<endl;
       safe = false;
   }
   else
       stack[top] = item;
}

void push(bool value, bool stack[],int &tos, bool &safe)
{
   safe = true;
   if(++tos > SIZE-1)
   {
       cout<<"Infix stack overflow!"<<endl;
       safe = false;
   }
   else
       stack[tos] = value;
}


// define pop operation
string pop(string stack[], int &top, bool &safe)
{
   string item ;
   safe = true;
   if(top < 0)
   {
       cout<<"Stack under flow: invalid infix expression has been entered!"<<endl;
       /* underflow may occur for invalid expression */
       /* where ( and ) are not matched */
       safe = false;
   }
   else
       item = stack[top--];
   return item;
}

bool pop(bool stack[], int &tos, bool &safe)
{
   double answer = 0;
   safe = true;
   if(tos < 0)
       safe = false;
   else
       answer = stack[tos--];
   return answer;
}

/**
* PURPOSE: Determine whether an operator is a operator
* PARAMETER:
*      string symbol,
*      Userinput decomposed into a one character string
* RETURN VALUE:
* true or false depending on whether the string is an operator
*/
bool isOperator(string symbol)
{
   const string operators("<=>|&^~@%");
   return operators.find(symbol) < operators.size();
}

/**
* PURPOSE: Makes an associative array of various precedence of operands depending on character
* PARAMETER:
*      map<string,int> &theMap,
*      Associative array created in function int main()
* RETURN VALUE:
* NONE
*/
void loadPrecedenceMap(map<string,int> &theMap)
{
   //Deleted multiple symbols of by implications and switched to '+' and '|' to logical operators
   theMap["="] = 0;
   theMap[">"] = 1;
   theMap["|"] = 2;
   theMap["^"] = 2;
   theMap["%"] = 2;
   theMap["&"] = 3;
   theMap["@"] = 3;
   theMap["~"] = 4;
}
/**
* PURPOSE: Look for whether the symbol entered by the user is found in defined
* associative array
* PARAMETER:
*      string symbol,
*              string entered by user processed on character at a time
*      map<string,int> the map
*              Associative defined by in function int main(),
*              contains single character string mapped to
*              integer values
*      bool safe
*          Determine whether expression is safe
* RETURN VALUE:
*      int value that is the precedence of the specified string
*/
int precedence(string symbol, map<string, int> theMap, bool &safe)
{
   safe = true;
   if(theMap.count(symbol) == 0)
   {

       cout<<"Unknown operator!"<<endl;
       safe = false;
   }
   return theMap[symbol];
}


/**
* PURPOSE: Take in user input and deletes any whitespace
* PARAMETER:
*      string input,
*      string entered by the user
* RETURN VALUE:
* NONE
*/
void trimString(string &input)
{
   while(input[0] == ' ')
       input.erase(0,1);
   while(input[input.size()-1] == ' ')
       input.erase(input.size()-1);
}

// Define a function to get the next token in the input string
string getToken(string &line)
{
   const string seperators(" ()^<=>|&~@%");
   string result;
   u_int pos = 0, pos2 = 0;
   trimString(line);
   if((pos = seperators.find(line[0]) < seperators.size())) // This returns separators
   {
       result = line.substr(0,pos); // Creates substring from seperator to next non-separator
       line.erase(0,pos);

   }
   else if((pos2  = line.find_first_of(seperators)) < line.size()) // This returns integers
   {
       result = line.substr(0,pos2);
       line.erase(0,pos2);
   }
   else
       result = "";
   trimString(result);

   return result;
}

/**
* PURPOSE: Function converts infix expression to postfix expression to
*          make evaluating that function easier
* PARAMETER:
*      string infix,
*          user input normalized and trimmed
*      string postfix,
*          empty string that will contain the user input in postfix notation
*      map<string,int> precedenceMap
*
* RETURN VALUE:
*
*/
bool infixToPostfix(string infixExp, string &postfixExp,  map<string,int> precedenceMap)
{
   string stack[SIZE],    // Declare stack
           item;          // Current item to process
   int tos = -1;          // Set the stack to be empty
   bool safe;

   trimString(infixExp);

   push("(", stack, tos, safe); // Push '(' onto stack so that all expressions are automatically within parens
   infixExp += ")";       // Add ')' to infix expression

   while(safe && ((item = getToken(infixExp)) != "") )        // run loop till end of infix expression
   {
       if(item == "(")
           push(item,stack,tos,safe);
       else
       if(item == ")")                    // if current symbol is ')' then
       {
           string temp = pop(stack,tos,safe);  // pop and keep popping until
           while( temp != "(" )           // a  '(' encounterd
           {
               postfixExp += " " + temp;
               temp = pop(stack,tos,safe);
           }
       }
       else
       if( !isOperator(item) )
           postfixExp += " " + item;          // add operand symbol to postfix expression
       else
       if(isOperator(item))           // means item is operator
       {
           string temp = pop(stack,tos,safe);
           while(isOperator(temp) && ((precedence(temp,precedenceMap,safe) >= precedence(item,precedenceMap,safe)) && safe))
           {
               postfixExp += " " + temp;      // so pop all higher precendence operator and
               temp = pop(stack,tos,safe);            // add them to postfix expresion
           }
           if(safe)
           {
               push(temp,stack,tos,safe);
               /*
       because just above while loop will terminate we have
       poppped one extra item for which condition fails and loop terminates, so that one
       needs to be pushed back onto the stack
     */
               push(item, stack,tos,safe); // push current oprerator symbol onto stack
           }
       }
       else
           return false;
   } // while loop ends here
   if(tos > -1 || !safe)
       return false;
   return true;
}

/**
* PURPOSE: Takes input of user, Is used in the program to continously ask user for inputs and exits
* when user does not enter input
* PARAMETER:
*     str, &line
*          A string entered by the user
* RETURN VALUE:
* Return true or false depending on whether the string is empty
*/
bool getLine(string &line)
{
   cout<<"Command: ";
   getline(cin,line);

   return !line.empty();
}

// Define display function
void display(const string &line, string postfix)
{
   bool safe;
   bool answer = evaluate(postfix,safe);
   //cout<<line<<" in RPN is "<<postfix<<endl;
   //    if(safe)
   //        cout<<" and results into "<<answer;
   //    else
   //        cout<<" and is an invalid postix notation!";
   cout<<endl;

}
/**
* PURPOSE:Turns an infix expression into a postfix expression
* PARAMETER:
*     str, &infixep
*      String user entered in infix notation
*     map<string,int> theMap
*      Associative array containing the the precedence of various operators
* RETURN VALUE:
* Return a string with the value in postfix notation
*/
string process(string infixExp,map<string, int> theMap, string &postfixExp)
{
   if(infixToPostfix(infixExp, postfixExp,theMap))
       display(infixExp,postfixExp);
   else
       cout<<"Invaild infix expression was entered!"<<endl;
   return postfixExp;
}
/**
* PURPOSE: Takes in a post-fix expression string and evaluates expression based on characters in the string
* PARAMETER:
*     str, postfix
*     bool, safe determines whether the expression is valid
* RETURN VALUE:
* Return true or false depending on the expression
*/
bool evaluate(string postfixExp, bool &safe)
{
   string token, item;
   bool operandStack[SIZE];
   int operandStackTos = -1;
   bool value1, value2;
   safe = true;
   while(safe && !(token = getToken(postfixExp)).empty())
   {
       trimString(token);
       if((token == "0") || (token == "1")){
           push(stod(token.c_str()),operandStack, operandStackTos, safe);
       }
       else{
           value1 = pop(operandStack,operandStackTos,safe);
           value2 = pop(operandStack,operandStackTos,safe);

           switch(token[0])
           {
               case '|' : push(value1|value2, operandStack, operandStackTos,safe);
                   break;

               case '&' : push(value1&value2, operandStack, operandStackTos,safe);
                   break;

               case '~' :
                   push(!value1, operandStack, operandStackTos,safe);
                   push(value2, operandStack, operandStackTos, safe);
                   break;

               case '^' : push(value1^value2, operandStack, operandStackTos,safe);
                   break;
               case '%' :
                   push(!(value1|value2), operandStack, operandStackTos,safe);
                   break;
               case '@' : push(!(value1&value2), operandStack, operandStackTos,safe);
                   break;
               case '>':
                   value2 = !value2;
                   push(value1 | value2, operandStack, operandStackTos,safe);
                   break;
               case '=':
                   push((value1&value2)|(!value1&!value2), operandStack, operandStackTos,safe);
           }
       }
   }
   safe = true;
   return operandStack[0];
}
/* Sample Run
Command: a|b
Do you need help? Please enter HELP!
Command: new a|b
 A|B stored as Expression 1
Command: new b&a
 B&A stored as Expression 2
Command: is 1=2



Statements are not equivalent



Command: table 1

You have 2 variables in your expression.
They are:
A B



  A  B|  Output
----------------
  F  F|  F
  F  T|  T
  T  F|  T
  T  T|  T
Command: table 2

You have 2 variables in your expression.
They are:
A B



  A  B|  Output
----------------
  F  F|  F
  F  T|  F
  T  F|  F
  T  T|  T

*/
