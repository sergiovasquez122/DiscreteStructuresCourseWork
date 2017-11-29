/**
  PROGRAM PURPOSE:
                  Teaches K-12 students basic set theory through the use of a User-friendly application. Provides operations known to set theory
                  such as intersection,union, complement and set difference. Allows user to save and load previous work. Allows user
                  to load from command line if desired.
  AUTHORS:
          Luz Avecado, Sergio Vasquez
  DATE CREATED:
               11/14/17
  DATE LAST MODIFIED
               11/28/17
*/
#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#define MAX_SET 26
#define SIZE 100
#define ALPHA_CHAR_TO_INT
using namespace std;
typedef unsigned int u_int;
bool isEqual(u_int set[], int set1, int set2);
bool isSubSet(u_int set[], int set1, int set2);
bool isSuperSet(u_int set[], int superSet, int subSet);
void saveSet(u_int theSet[], string fileName);
void loadSet(u_int theSet[], string fileName);
void loadSetContentFromCommandLine(u_int theSet[], int argc, char *argv[]);
void displayLegend();
void displayMap(map<int, string> &theMap);
void showSet(u_int array[], int index, map<int, string> &map);
void listSet(u_int array[], map<int, string> &map);
bool getLine(string title, string &line);
void commands(string userInput, u_int theSet[], map<int,string> &displayMap, map<char,unsigned int> &setMap, map<string,int> precedenceMap);
void normalize(string &line);
void trimWhiteSpace(string &line);
int determineRelation(string userInput);
void setUnion(u_int array[], int index1, int index2, map<int,string> &map);
void binToInt(u_int &value);
string getToken(string &line, map<string,int> processMap, map<char,unsigned int> setMap);
void processingMap(map<string,int> &theMap);
void push(string item, string stack[], int &top, bool &safe);
string pop(string stack[], int &top, bool &safe);
u_int pop(u_int stack[], int &tos, bool &safe);
void push(u_int value, u_int stack[], int &tos, bool &safe);
int precedence(string symbol, map<string, int> theMap, bool &safe);
string findLetter(string line);
string findSet(string line,map<char,unsigned int> setMap);
u_int process(string infixExp,map<string, int> theMap, string &postfixExp, map<char,unsigned int> SetMap, map<string,int> processMap);
void loadPrecedenceMap(map<string,int> &theMap);
string preProcess(string &line, map<string,int> processMap, map<char,unsigned int> setMap);
string findColors(string &line, map<string,int> processMap);
bool isOperator(string symbol);
u_int display(const string &line, string postfix, map<string,int> processMap, map<char,unsigned int> setMap);
u_int evaluate(string postfixExp, bool &safe);
string find(string line, int pos, int commandsize);
void initializeSets(u_int theSet[], map<char,unsigned int> &setMap);
bool infixToPostfix(string infixExp, string &postfixExp,  map<string,int> precedenceMap, map<string,int> processMap, map<char,unsigned int> setMap);
bool setExists(char symbol, map<char,unsigned int> &setMap);
bool numberCheck(string temp);
bool alphaCheck(string temp);
bool junknumberCheck(u_int temp);
u_int stringToUInt(string line);


int main(int argc, char *argv[])
{
    u_int set[MAX_SET];
    map<int,string> decodeMap;
    displayMap(decodeMap);
    memset(set,0,sizeof(set));
    map<char,u_int> setMap;
    map<string,int> precedenceMap;
    loadPrecedenceMap(precedenceMap);
    loadSetContentFromCommandLine(set,argc,argv);
    string userInput;

    while(getLine("Enter Command: ",userInput)){
        commands(userInput,set,decodeMap,setMap,precedenceMap);
    }
}
/**
* @brief commands Given userinput, perform the command if valid input
* @param userInput string that represents the user input
* @param theSet unsigned integer array used to represent the sets
* @param displayMap associative array used to decode the array into user-friendly interface
*/
void commands(string userInput, u_int theSet[], map<int,string> &displayMap, map<char,unsigned int> &setMap, map<string,int> precedenceMap){
    u_int pos = 0, commandSelected = -1,size;
    stringstream ss;
    string listOfCommands[7] = {"SET","SHOW","LIST","HELP","IS","LOAD","SAVE"};
    normalize(userInput);
    string temp, postfixExp, fileName;
    u_int value = 0;
    map<string,int> processMap;
    processingMap(processMap);


    char c;

    for (int i = 0; i < 7; ++i) {
        if((pos=userInput.find(listOfCommands[i]))<userInput.size()){
            if (listOfCommands[i] == "IS"){
                if (userInput == "LIST"){
                    i = 2;
                }
            }
            commandSelected = i;
            size = listOfCommands[i].size();
            break;
        }
    }


    switch(commandSelected){
    case 0:
        //SET
        userInput.erase(0,size);
        normalize(userInput);
        trimWhiteSpace(userInput);
        temp = findLetter(userInput);
        ss << temp;
        ss >> c;
        temp = findSet(userInput,setMap);
        if (temp !="")
        {
            // If it does not contain letters or seperators, convert to unsigned int
            if (numberCheck(temp)){
                value = stringToUInt(temp);
            }
            // If it does contain letters or seperators
            else {
                // Process for colors and sets
                preProcess(temp, processMap,setMap);
                // If temp is a number after preprocessing, convert to an unsigned int
                if (numberCheck(temp)){
                    value = stringToUInt(temp);
                }
                // Process through RPN if passes alphaCheck
                else if (alphaCheck(temp)){
                    value = process(temp, precedenceMap, postfixExp, setMap, processMap);
                }

            }
            // If letter has not been stored in the map
            if (setMap.count(c)==0){
                // If value is not zero or ridiculously large number, insert into map set and array set
                if (junknumberCheck(value)){
                    setMap.insert(pair<char,unsigned int>(c,value));
                    theSet[c-65] = value;
                    cout << "SET " << c << " was stored successfully!" << endl;
                }
                else{
                    cout << "Not valid input" << endl;
                }
            }
            // If letter has already been stored
            else {
                cout << "Set " << c << " was already stored!" << endl;
            }
        }
        break;
    case 1:
        //SHOW
        userInput.erase(0,size);
        normalize(userInput);
        showSet(theSet,userInput[0]-65,displayMap);
        break;
    case 2:{
        //LIST
        listSet(theSet,displayMap);
        break;
    }
    case 3:
        //HELP
        displayLegend();
        break;
    case 4:{
        //IS
        userInput.erase(0,size);
        normalize(userInput);
        userInput.erase(remove_if(userInput.begin(),userInput.end(),::isspace),userInput.end());
        int isIndex = determineRelation(userInput);
        switch (isIndex) {
        case 0:
            //EQUAL
            if(isEqual(theSet,userInput[0]-65,userInput[2]-65))
                cout<<userInput[0]<<" EQUAL TO "<<userInput[2]<<endl;
            else
                cout<<"Not equal"<<endl;
            break;
        case 1:
            //SUBSET
            if(isSubSet(theSet,userInput[0]-65,userInput[2]-65))
                cout<<userInput[0]<<" SUBSET TO "<<userInput[2]<<endl;
            else
                cout<<"Not SUBSET"<<endl;
            break;
        case 2:
            //SUPERSET
            if(isSubSet(theSet,userInput[0]-65,userInput[2]-65))
                cout<<userInput[0]<<" SUBSET TO "<<userInput[2]<<endl;
            else
                cout<<"Not SUBSET"<<endl;
            break;
        default:
            cout<<"Invalid Input"<<endl;
            //Invalid
            break;
        }
    }
    case 5:
        //LOAD
        userInput.erase(0,size);
        trimWhiteSpace(userInput);
        loadSet(theSet,userInput);
        initializeSets(theSet,setMap);
        break;
    case 6:
        //SAVE
        userInput.erase(0,size);
        trimWhiteSpace(userInput);
        saveSet(theSet,userInput);
        break;
    default:
        cout<<"Invalid command"<<endl;
    }
}
string find(string line, int pos, int commandsize){
    string temp;
    if (pos != string::npos){
        temp = line.substr(commandsize,line.size()-1);
    }
    return temp;
}
u_int stringToUInt(string line)
{
    stringstream ss;
    u_int value;
    ss << line;
    ss >> value;
    ss.clear();

    return value;
}

/**
 * @brief initializeSets makes a map or 'relation' between sets and their respective character value
 * @param theSet unsigned int array used to represent the sets
 * @param setMap Associative container
 */
void initializeSets(u_int theSet[], map<char,unsigned int> &setMap){

    for (char c = 'A'; c <= 'Z'; ++c)
    {
        for (int i = 0; i < 26; i++){
            setMap.insert(pair<char,int>(c,theSet[c-65]));
        }
    }

}


/**
* @brief isEqual Determine if two sets specified by the user are equal
* @param set unsigned integer array used to represent the sets
* @param set1 integer value that represents the index of the first set the user would like the access
* @param set2  integer value that represents the index of the second set the user would like the access
* @return true or false depending if the content of the sets are equal
*/
bool isEqual(u_int set[],int set1,int set2){
    return set[set1] == set[set2];
}

/**
* @brief isSubSet Determines if a set specified by the user is a subset of another set
* @param set unsigned int array used to represent all of the sets
* @param subSet integer value that is used to represent the index of the set the user would like to access
* @param superSet integer value that is used to represent the index of the set the user would like to access
* @return true or false
*/
bool isSubSet(u_int set[],int subSet, int superSet){
    return set[subSet] == (set[subSet] & set[superSet]);
}

/**
* @brief isSuperSet Determines if a user specified by the user is a superset of another set
* @param set unsigned int array use to represent all of the sets
* @param superSet integer values that is used to represent the index of the set the user would like to access
* @param subSet integer value that is used to represent the index of the set the user would like to access
* @return return true or false
*/
bool isSuperSet(u_int set[],int superSet,int subSet ){
    return set[subSet] == (set[subSet] & set[superSet]);
}

/**
* @brief saveSet save all of the users work to the sets
* @param theSet unsigned integer array used to represent the sets
* @param fileName where the user would like to save the file contents
*/
void saveSet(u_int theSet[], string fileName){
    ofstream file(fileName);
    for(int i = 0; i < 26; i++)
        file<<theSet[i]<<endl;
}

/**
* @brief loadSet load previous work of user if desired
* @param theSet unsigned int array used to represent the sets
* @param fileName Where the user  would like to load the content from
*/
void loadSet(u_int theSet[],string fileName){
    ifstream file(fileName);
    string content;
    stringstream ss;
    int temp;
    int counter =  0;
    while (getline(file,content)) {
        ss<<content;
        ss>>theSet[counter++];
        ss.clear();
    }
}
/**
* @brief loadSetContentFromCommandLine If ran through commandline with proper file, load content
* @param theSet unsigned int array used to represent the bits
* @param argc Number of arguements passed through command line
* @param argv arguement vector
*/
void loadSetContentFromCommandLine(u_int theSet[],int argc, char *argv[]){
    if( argc!=2 )
        cout<<"Usage: "<<argv[0]<< " <filename> "<<endl;
    else{
        ifstream file(argv[1]);
        string content;
        stringstream ss;
        int counter =  0;
        while (getline(file,content)) {
            ss<<content;
            ss>>theSet[counter++];
            ss.clear();
        }
    }
}




/**
* @brief createMap Gives associative array 'relation' to abide by
* @param theMap container
*/
void displayMap(map<int,string> &theMap){
    theMap[0] = "WHITE";
    theMap[1] = "GOLD";
    theMap[2]= "GRAY";
    theMap[3]= "RED";
    theMap[4]= "GREEN";
    theMap[5]= "BLUE";
    theMap[6]= "ORANGE";
    theMap[7]= "PURPLE";
    theMap[8]= "YELLOW";
    theMap[9]= "VIOLET";
    theMap[10]= "MAGENTA";
    theMap[11]= "CYAN";
    theMap[12]= "RUST";
    theMap[13]= "NAVY";
    theMap[14]="BURGUNDY";
    theMap[15]="BLACK";
}

/**
* @brief processingMap used to decode for the processing function
* @param theMap associative array
*/
void processingMap(map<string,int> &theMap){
    theMap["WHITE"] = 1;
    theMap["GOLD"]= 2;
    theMap["GRAY"]=4;
    theMap["RED"]=8;
    theMap["GREEN"]=16;
    theMap["BLUE"]=32;
    theMap["ORANGE"]=64;
    theMap["PURPLE"]=128;
    theMap["YELLOW"]=256;
    theMap["VIOLET"]=512;
    theMap["MANGENTA"]=1024;
    theMap["CYAN"]=2048;
    theMap["RUST"]=4096;
    theMap["NAVY"]=8192;
    theMap["BURGUNDY"]=16384;
    theMap["BLACK"]=32768;
}

/**
* @brief showSet Display the content of a specified set
* @param array unsigned int array used to represent the sets
* @param index integer that represents the specific set user would like to access
* @param map associative container for decoding sets
*/
void showSet(u_int array[] ,int index,map<int,string> &map){
    bitset<16> set = array[index];
    cout<<(char)(index+65)<<": "<<"{";
    for(int i = 0; i<16;i++){
        if(set[i])
            cout<<map[i]<<" ";
    }
    cout<<"}"<<endl;

}

/**
* @brief listSet Display the contents of all the sets
* @param array unsigned int array used to represent the sets
* @param map associative container for decoding sets
*/
void listSet(u_int array[],map<int,string> &map){
    for (int i = 0; i < 26; ++i) {
        bitset<16>set =array[i];
        cout<<(char)(i+65)<<": "<<"{";
        for(int i = 0; i<16;i++){
            if(set[i])
                cout<<map[i]<<" ";
        }
        cout<<"}"<<endl;
    }
}

/**
* @brief help Display list of possible commands to user
*/
void displayLegend(){
    cout<<"Welcome to the set calculator!"<<endl;
    cout<<"Type SET followed by a letter and equal to a valid set in order to create sets" << endl;
    cout<<"Type SHOW followed by a letter in order to show a specific set" << endl;
    cout<<"Type LIST to display all current sets" << endl;
    cout<<"Type IS followed by two sets equal to each other in order to compare sets" << endl;
    cout<<"TYPE LOAD followed by a file name to load sets from a file" << endl;
    cout<<"You may also LOAD via the command file by entering the name of the file" << endl;
    cout<<"Type SAVE followed by a file name to save sets to a file" << endl;
    cout<<"The valid operations for sets are union(+),intersection(*),compliment(~),set difference(\\)" << endl;
    cout<<"You may enter sets as integers or colors" << endl;
    cout<<"The valid colors are WHITE, GOLD, GRAY, RED, GREEN, BLUE, ORANGE, PURPLE, YELLOW, VIOLET, MAGENTA, CYAN, RUST, NAVY, BURGUNDY, BLACK" << endl;
}

/**
 * @brief determineRelation when the user enters is equal determine which relation the user intends
 * @param userInput a line containing the relation the user would like to evaluate
 * @return an integer value that represent the relation the user would like to evaluate
 */
int determineRelation(string userInput){
    if(userInput.length()==3)
        if(userInput[1] == '=')
            return 0;
        else if(userInput[1]== '<')
            return 1;
        else if(userInput[1]== '>')
            return 2;
    return -1;
}

string findLetter(string line){
    string temp;
    if (isalpha(line[0])){
        temp = line[0];

    }
    else {
        cout << "ME!" << endl;
        cout << "Incorrect input!" << endl;
        temp = "";
    }

    return temp;
}
string findSet(string line,map<char,unsigned int> setMap){
    string temp;

    for(int i=0; i<line.length(); i++)
        if(line[i] == ' ') line.erase(i,1);

    if (isalpha(line[0])){
        if (line[1] == '=') {
            temp = line.substr(2, line.size() - 1);

            if (temp.size()==1){
                if (setExists(temp[0],setMap)){
                    return temp;
                }
                else if (isdigit(temp[0])){
                    return temp;
                }
                else {
                    cout << "HEY BOO" << endl;
                    cout << "Incorrect input!" << endl;
                    temp = "";
                }
            }
        }
        else {
            cout << "YOU BAE" << endl;
            cout << "Incorrect input!" << endl;
            temp = "";
        }
    }
    else {
        cout << "DAMN GURL" << endl;
        cout << "Incorrect input!" << endl;
        temp = "";
    }

    return temp;
}

/**
 * @brief numberCheck
 * @param temp
 * @return true or false depending on the expression
 */
bool numberCheck(string temp){
    const string seperators = ("*~+\\");

    for (u_int i = 0; i < temp.length(); i++){
        if (isalpha(temp[i]))
        {
            return false;
        }
        if (seperators.find(temp[i]) < seperators.size()){
            return false;
        }
    }
    return true;
}

/**
 * @brief alphaCheck determines if the character the user has entered is an operator
 * @param temp a temporary string of the user input
 * @return true or false
 */
bool alphaCheck(string temp) {

    for (u_int i = 0; i < temp.length(); i++) {
        if (!isalpha(temp[i])) {
            return true;
        }
    }

    return false;
}

/**
 * @brief junknumberCheck Determines if the user has entered numbers beyond the range of an unsigned int
 * @param temp unsigned int value the user has entered
 * @return true or false depending on the expression that was entered
 */
bool junknumberCheck(u_int temp){

    if (temp >= 4294967295){
        cout << "ERROR! Invalid numbers entered" << endl;
        return false;
    }
    if (temp <= 0){
        cout << "ERROR! Invalid numbers entered" << endl;
        return false;
    }
    return true;
}

/**
 * @brief setExists Determine if the character value entered by the user is a set value
 * @param symbol the specific character value that is being evaluated
 * @param setMap associative container that represents the relation between character value and set
 * @return true or false depending if character value represents a set
 */
bool setExists(char symbol, map<char,unsigned int> &setMap)
{
    if (setMap.count(symbol)){
        return true;
    }
    return false;
}

/**
* @brief getLine: continously ask user for their input
* @param title: The value to print out to the user
* @param line: string to represent users input
* @return true: or false depending on whether user entered empty line
*/
bool getLine(string title,string &line)
{
    cout<<title;
    getline(cin,line);
    return !line.empty();
}

/**
* @brief normalize remove unnecessary data from the string
* @param line a string used to represent userinput
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

/**
* @brief loadPrecedenceMap Defines the precedence of set operations
* @param theMap Associative Array
*/
void loadPrecedenceMap(map<string,int> &theMap)
{
    theMap["\\"] = 1;
    theMap["+"] = 1;
    theMap["*"] = 1;
    theMap["~"] = 2;
}
/**
* @brief TrimWhiteSpace Gets rid of excess spaces
* @param input Takes in a line to trim
*/
void trimWhiteSpace(string &input){
    while(input[0] == ' ')
        input.erase(0,1);
    while(input[input.size()-1] == ' ')
        input.erase(input.size()-1);
}
/**
* @brief findColors Finds valid colors within brackets of set
* @param line Input to search through
* @param processMap Map to search through for colors values
*/
string findColors(string &line, map<string,int> processMap){
    stringstream ss;
    int pos = 0;
    int pos2 = 0;
    int value = 0;
    int temp;
    string result = "";

    string colors[16] =

    {"WHITE", "GOLD", "GRAY", "RED",
     "GREEN", "BLUE", "ORANGE", "PURPLE",
     "YELLOW", "VIOLET", "MAGENTA", "CYAN",
     "RUST", "NAVY", "BURGUNDY", "BLACK"};


    for (int i = 0; i < 16; i++){
        if ((pos = line.find(colors[i])) < line.size()){
            result = line.substr(pos,colors[i].size()); // Creates substring from seperator to next non-separator
            value += processMap[result];
        }
    }
    for (int i = 0; i < line.size(); i++){
        if (isdigit(line[i])){
            ss << line[i];
            ss >> temp;
            ss.clear();
            value += temp;
        }
        //        else if (isalpha(line[i])){
        //            cout << "Set" << line[i] << " has not been stored!" << endl;
        //        }

    }
    if (line.find("MAROON") < line.size()){
        cout << "MAROON is not valid. This set will exclude that color" << endl;
    }


    ss << value;
    ss >> result;

    return result;
}

/**
* @brief preProcess Preprocesses strings to a uniform format
* @param processMap Required for searching for colors
* @param setMap Required for looking for valid sets
* @param line
*/
string preProcess(string &line, map<string,int> processMap, map<char,unsigned int> setMap)
{
    const string seperators("+\\*");
    string result;
    string temp = line;
    stringstream ss;
    u_int pos = 0, pos2 = 0, pos1 = 0;
    trimWhiteSpace(line);
    int counter = 0;


    for (int i = 0; i < line.length(); i++){
        if (((pos = line.find_first_of("{")) < line.size())){
            if ((pos2 = line.find_first_of("}")) < line.size()) {
                string color = line.substr(pos,pos2-pos);
                result = findColors(color, processMap);
                if (result == "0"){
                    cout << "INVALID COLORS! Enter line again!" << endl;
                    line == "";
                    break;
                }
                line.replace(pos,color.length()+1,result);
            }
        }
        if (setMap.count(line[i])){
            ss << setMap.at(line[i]);
            ss >> result;
            ss.clear();
            line.replace(i,1,result);
        }


    }

    return line;
}
/**
* @brief getToken Tokenizes line in order to complete RPN
* @param line Line to tokenize
*/
string getToken(string &line) {
    const string seperators(" ()+*~\\");
    string result;
    u_int pos = 0;
    trimWhiteSpace(line);
    if ((seperators.find(line[0])) < seperators.size()) {
        int pos = line.find_first_not_of(seperators);
        result = line.substr(0, pos);
        line.erase(0, pos);

    }

    else if ((pos = line.find_first_of(seperators)) < line.size()) {
        result = line.substr(0, pos);
        line.erase(0, pos);
    }

    else
        result = "";
    trimWhiteSpace(result);
    return result;
}

/**
 * @brief isOperator functions check if the the user has entered a valid operator
 * @param symbol a single valued string that represents the operator
 * @return true or false depending if it is in the set of valid operators
 */
bool isOperator(string symbol)
{
    const string operators("+\\*~");
    return operators.find(symbol) < operators.size();
}

/**
 * @brief infixToPostfix converts user infix string expression to an easy to compute postfix expression
 * @param infixExp the string originally entered by the user
 * @param postfixExp the string of the user converted to reverse polish notation
 * @param precedenceMap associative array that represent the precendence of a certain operator
 * @param processMap associative array to decode values
 * @param setMap associative container that represents relation of set and char value
 * @return true or false depending if the string contains  valid inputs
 */
bool infixToPostfix(string infixExp, string &postfixExp,  map<string,int> precedenceMap, map<string,int> processMap, map<char,unsigned int> setMap)
{
    string stack[SIZE],    // Declare stack
            item;          // Current item to process
    int tos = -1;          // Set the stack to be empty
    bool safe;

    trimWhiteSpace(infixExp);

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
 * @brief push push item on stack if possible
 * @param item item being pushed
 * @param stack a string array stack
 * @param top the top value of the stack
 * @param safe determine if operation is safe
 */
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

/**
 * @brief push push item on stack if possible
 * @param item item being pushed
 * @param stack a unsigned int  array stack
 * @param top the top value of the stack
 * @param safe determine if operation is safe
 */
void push(u_int value, u_int stack[],int &tos, bool &safe)
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


u_int pop(u_int stack[], int &tos, bool &safe)
{
    u_int answer = 0;
    safe = true;
    if(tos < 0)
        safe = false;
    else
        answer = stack[tos--];
    return answer;
}

/**
 * @brief precedence returns the precedence of a particular operator
 * @param symbol string that represents the symbol that is being decoded
 * @param theMap associative container
 * @param safe determines if user input is valid
 * @return the integer value that represents the precedence of the symbol
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
 * @brief process processes the input the user has entered
 * @param infixExp orignal user expression
 * @param theMap associative container
 * @param postfixExp user expression converted to postfix
 * @param SetMap associative container
 * @param processMap associative container
 * @return an unsigned integer value
 */
u_int process(string infixExp,map<string, int> theMap, string &postfixExp, map<char,unsigned int> SetMap, map<string,int> processMap)
{
    u_int answer = 0;

    if(infixToPostfix(infixExp, postfixExp,theMap,processMap,SetMap))
        answer = display(infixExp,postfixExp,processMap,SetMap);
    else
        cout<<"Invaild infix expression was entered!"<<endl;
    return answer;
}

/**
 * @brief display Used to display the answer of the rpn calculator
 * @param line a string that represents the user originally expression
 * @param postfix a string that represents the user expression converted to reverse polish notation
 * @param processMap associative container
 * @param setMap associative container
 * @return the answer evaluate from rpn
 */
u_int display(const string &line, string postfix, map<string,int> processMap, map<char,unsigned int> setMap)
{
    bool safe;
    u_int answer = evaluate(postfix,safe);
    //    cout<<line<<" in RPN is "<<postfix<<endl;

    return answer;
}

/**
 * @brief evaluate the processing function of the rpn calculator, goes through rpn and evaluates
 * @param postfixExp the user orginally expression converted to postfix
 * @param safe boolean value used to determine if user value is valid
 * @return an unsigned integer of the evaluated expression
 */
u_int evaluate(string postfixExp, bool &safe)
{
    string token;
    u_int operandStack[SIZE];
    int operandStackTos = -1;
    u_int value1, value2;
    safe = true;
    while(safe && !(token = getToken(postfixExp)).empty())
    {
        trimWhiteSpace(token);
        if(!isOperator(token)) {
            push(stoul(token.c_str()), operandStack, operandStackTos, safe);
        }
        else
        {
            value1 = pop(operandStack,operandStackTos,safe);
            value2 = pop(operandStack,operandStackTos,safe);


            switch(token[0])
            {
            case '+' : push(value1|=value2, operandStack, operandStackTos,safe);
                break;

            case '*' : push(value2&value1, operandStack, operandStackTos,safe);
                break;

            case '~' :   push(~value1, operandStack, operandStackTos,safe);
                if (value2 != 0) {
                    push(value2, operandStack, operandStackTos, safe);
                }
                break;

            case '\\' : push(value1^value2, operandStack, operandStackTos,safe);
                break;
            }
        }

    }
    return operandStack[0];
}
/**SAMPLE RUN TO DEMONSTRATE BASIC FUNCTIONALITY
Enter Command: set a = {white}
SET A was stored successfully!
Enter Command: list
A: {WHITE }
B: {}
C: {}
D: {}
E: {}
F: {}
G: {}
H: {}
I: {}
J: {}
K: {}
L: {}
M: {}
N: {}
O: {}
P: {}
Q: {}
R: {}
S: {}
T: {}
U: {}
V: {}
W: {}
X: {}
Y: {}
Z: {}
Enter Command: set c = { blue}
SET C was stored successfully!
Enter Command: list
A: {WHITE }
B: {}
C: {BLUE }
D: {}
E: {}
F: {}
G: {}
H: {}
I: {}
J: {}
K: {}
L: {}
M: {}
N: {}
O: {}
P: {}
Q: {}
R: {}
S: {}
T: {}
U: {}
V: {}
W: {}
X: {}
Y: {}
Z: {}
Enter Command: show a
A: {WHITE }
Enter Command: show c
C: {BLUE }
Enter Command: save SERGIO.txt
Enter Command:
Press <RETURN> to close this window...


Demonstrating the functionality of the load from command line function
sergio@sergio-HP-EliteBook-8470p:~/Desktop/CS45/creditCardFileRead/bitSetRevised$ ./a.out bitSetRevised.pro
bitSetRevised.pro       bitSetRevised.pro.user
sergio@sergio-HP-EliteBook-8470p:~/Desktop/CS45/creditCardFileRead/bitSetRevised$ ./a.out BITSET.txt
Enter Command: list
A: {BLACK }
B: {}
C: {GOLD GRAY RED }
D: {BLUE }
E: {WHITE RED BLUE PURPLE YELLOW }
F: {GOLD GRAY RED }
G: {GOLD GRAY GREEN BLUE }
H: {GOLD GREEN YELLOW VIOLET }
I: {GREEN BLUE VIOLET RUST }
J: {WHITE GOLD }
K: {GRAY }
L: {GOLD GRAY GREEN VIOLET }
M: {GOLD GRAY }
N: {GOLD BLUE }
O: {RED GREEN BLUE }
P: {WHITE RED GREEN ORANGE YELLOW }
Q: {}
R: {}
S: {}
T: {}
U: {}
V: {}
W: {}
X: {}
Y: {}
Z: {}
Enter Command:

Demonstrating the functionality of using integer values
Enter Command: set a = 12
SET A was stored successfully!
Enter Command: set b = 7
SET B was stored successfully!
Enter Command: show a
A: {GRAY RED }
Enter Command: show b
B: {WHITE GOLD GRAY }
Enter Command:

Demonstrating the functionality of relations
Enter Command: set a = 12
SET A was stored successfully!
Enter Command: set b = 45
SET B was stored successfully!
Enter Command: is a = b
Not equal
Enter Command:

Demonstrating the functionlity of set operations
Enter Command: set a = 7 + 12 + 13 *12
SET A was stored successfully!
Enter Command: show a
A: {GRAY RED }
Enter Command: set b = ~1
SET B was stored successfully!
Enter Command: show b
B: {GOLD GRAY RED GREEN BLUE ORANGE PURPLE YELLOW VIOLET MAGENTA CYAN RUST NAVY BURGUNDY BLACK }
Enter Command:

Demonstrating the functionality of the save and load operation
1st session
Enter Command: set a = 12
SET A was stored successfully!
Enter Command: set b = 434
SET B was stored successfully!
Enter Command: set c = 654
SET C was stored successfully!
Enter Command: set d = ~1
SET D was stored successfully!
Enter Command: save content
Enter Command:

2nd session
Enter Command: load content
Enter Command: list
A: {GRAY RED }
B: {GOLD GREEN BLUE PURPLE YELLOW }
C: {GOLD GRAY RED PURPLE VIOLET }
D: {GOLD GRAY RED GREEN BLUE ORANGE PURPLE YELLOW VIOLET MAGENTA CYAN RUST NAVY BURGUNDY BLACK }
E: {}
F: {}
G: {}
H: {}
I: {}
J: {}
K: {}
L: {}
M: {}
N: {}
O: {}
P: {}
Q: {}
R: {}
S: {}
T: {}
U: {}
V: {}
W: {}
X: {}
Z: {}
*/






