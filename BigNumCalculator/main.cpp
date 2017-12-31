/**
  PROGRAM PURPOSE: Program allows user to perform arithemtic far beyond the range of the standard c++ integer.
  Program allows user to use standard mathematic operations such as '+','-','\\','*' and other mathematic
  operations such as factorial, greatest common denomator(GCD),Permutations and Combinations.User can save
  work and also load data from previous work. Program also provides added functionality of computing various
  poker hands and probabilities of certain hands.
  AUTHORS: LUZ ACEVEDO, SERGIO VASQUEZ
  DATE CREATED: 11/28/17
  DATE LAST MODIFED: 12/12/17
  */
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
typedef unsigned int u_int;
void listNums(map<char,string> numbers);
void showNum(map<char,string> numbers, char index);
void saveNums(map<char,string> &numbers, string fileName);
void loadNum(map<char,string> &numbers, string fileName);
void reverse(string &line);
string beautifyString(string line);
void help();
void normalize(string &line);
void commands(string userInput, map<char,string> &numbers);
bool getLine(string title, string &line,map<char,string> numbers);
string addition(string low,string high);
void subtract(string operand1, string operand2, string &answer);
void divide(string operand1, string operand2, string &number,string &remainder);
string processLine(string line);
string factorial(string operand);
void storeset(string list[], int index, string input);
string GCD(string n, string m);
string multiply(string operand1,string operand2);
string permutation(string n,string k);
void trimZerosFromHead(string &line);
string combination(string n,string k);
string addition(string low,string high);
bool comparison(string str1, string str2);
void swap(string &n, string &m);
string modulo(string n, string m);
string find(string line, int pos, int commandsize);
string findLetter(string line);
void trimString(string &input);
void trimCommas(string &line);
void storeset(map<char,string> &numbers, char letter, string input);
string findNumber(string temp);
bool numberCheck(string temp);
void sanitize(string &line, int &comma);
void edit(map<char,string> &numbers, char key);
bool savebeforequit(map<char,string> numbers);
void oddsOfPoker();
void possiblePokerHands();
string addForKarasuba(string operand1, string operand2);
string subtractForKarasuba(string operand1, string operand2);
string karasuba(string operand1, string operand2);
int main()
{
    map<char,string> numbers;
    string userInput;
    while(getLine("CMD: ",userInput,numbers)){
        commands(userInput,numbers);
    }
}

/**
 * @brief commands Given a specified userinput perform various commands
 * @param userInput a string that represent the particular command the user would like to perform
 * @param numbers associative array that relates a particular char value to a string of numbers
 */
void commands(string userInput, map<char,string> &numbers){
    u_int pos = 0;
    int commandSelected = -1,size;
    string listOfCommands[10] = {"LET","SHOW","LIST","HELP","LOAD","SAVE","WEXIT","EDIT","OOP","PPH"};
    string temp,fileName, finalexp, answer;
    string letter,exptoedit;
    char alpha;
    normalize(userInput);
    stringstream ss;
    for (int i = 0; i < 10; ++i) {
        if((pos=userInput.find(listOfCommands[i]))<userInput.size()){
            commandSelected = i;
            size = listOfCommands[i].size();
            break;
        }
    }
    switch(commandSelected){
    case 0:
        //LET
        temp = find(userInput,pos,size);
        letter = findLetter(temp);
        if (letter != ""){
            ss << letter;
            ss >> alpha;
            finalexp = findNumber(temp);
            if (numberCheck(finalexp)) {
                answer = processLine(finalexp);
                if (answer !=""){
                    normalize(userInput.erase(0, size));
                    storeset(numbers, alpha, answer);
                }
                else {
                    cout << "Invalid input!" << endl;
                }
            }
            else {
                cout << "Invalid input!" << endl;
            }
        }

        break;
    case 1:
        //SHOW
        normalize(userInput.erase(0,size));
        if (isalpha(userInput[0])) {
            showNum(numbers, userInput[0]);
        }
        break;
    case 2:
        //LIST
        listNums(numbers);
        break;
    case 3:
        //HELP
        help();
        break;
    case 4:
        //LOAD
        userInput.erase(0,size);
        normalize(userInput);
        fileName=userInput;
        loadNum(numbers,fileName);
        break;
    case 5:
        //SAVE
        userInput.erase(0,size);
        normalize(userInput);
        fileName=userInput;
        saveNums(numbers,fileName);
        break;
    case 6:
        //WEXIT
        fileName = userInput.erase(0,size);
        normalize(userInput);
        fileName=userInput;
        saveNums(numbers,fileName);
        exit(0);
        break;
    case 7:
        // EDIT
        exptoedit = userInput.erase(0,size);
        trimString(exptoedit);
        edit(numbers,exptoedit[0]);
    case 8:
        //OOP
        oddsOfPoker();
        break;
    case 9:
        //PPH
        possiblePokerHands();
    default:
        cout << "Do you need help? Enter HELP" << endl;
        break;
    }
}

/**
 * @brief edit allow user to edit a particular memory address
 * @param numbers associative array
 * @param key index of array
 */
void edit(map<char,string> &numbers, char key){
    string letter,finalexp,answer,input;

    cout << "Enter new expression as letter you entered =: ";
    getline(cin,input);

    letter = findLetter(input);
    cout << letter << endl;
    cout << key << endl;
    if (letter[0] == key){
        finalexp = findNumber(input);
        if (numberCheck(finalexp)) {
            answer = processLine(finalexp);
            if (answer !=""){
                numbers[key] = answer;
                cout << "Edit stored!" << endl;
            }
            else {
                cout << "Invalid input!" << endl;
            }
        }
        else {
            cout << "Invalid input!" << endl;
        }
    }
    else {
        cout << "ERROR when editing!" << endl;
    }

}

string findNumber(string temp){
    cout << "TEMP: " << temp << endl;
    trimString(temp);
    temp.erase(0,2);
    string final = temp;
    return final;
}
string find(string line, int pos, int commandsize){
    string temp;
    if (pos != string::npos){
        temp = line.substr(commandsize,line.size()-1);
    }
    return temp;
}
/**
 * @brief trimString deletes any white space of a particular string
 * @param s a string that has unneeded white space
 */
void trimString(string &s)
{
    s.erase( remove( s.begin(), s.end(), ' ' ), s.end() );
}
bool numberCheck(string temp){
    const string junk = ("@#$%^&{}|?\\~`");
    const string alpha = ("GCDP");

    for (u_int i = 0; i < temp.length(); i++){
        if (isalpha(temp[i] && !alpha.find(temp[i])))
        {
            return false;
        }
        if (junk.find(temp[i]) < junk.size()){
            return false;
        }
    }
    return true;
}

/**
 * @brief normalize function standarizes input so that parsing string is much easier
 * @param line an unstandarized string
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
 * @brief trimCommas user will input data that is not useful for parsing delete it to make data extraction easier
 * @param line represent user input
 */
void trimCommas(string &line){
    line.erase( remove( line.begin(), line.end(), ',' ), line.end() );
}

/**
 * @brief listNums list all numbers that currently have values associated with them
 * @param numbers associative array
 */
void listNums(map<char,string> numbers){
    for (auto &p: numbers)
        cout << p.first << ": " << beautifyString(p.second) << endl;
}

/**
 * @brief showNum displays value specifed by the user
 * @param numbers associative array
 * @param key specific index user would like to access
 */
void showNum(map<char,string> numbers,char key){
    if (numbers.count(key)>0)
        cout << key << ": " << beautifyString(numbers.at(key)) << endl;
    else
        cout << "Expression " << key << " not stored." << endl;
}

/**
 * @brief storeset
 * @param numbers
 * @param letter
 * @param input
 */
void storeset(map<char,string> &numbers, char letter, string input){
    pair <map<char, string>::iterator, bool> result;
    if (numbers.size() <= 25){
        result = numbers.insert(pair<char,string>(letter,input));
        if(result.second)
            cout << "Expression was successfully stored!" << endl;
        else
            cout << "Expression already existed" << endl;
    }
    else {
        cout << "No more numbers can be added!" << endl;
    }
}

/**
 * @brief saveNums save user work to a specified file location
 * @param numbers associative array
 * @param fileName specified file name to be made
 */
void saveNums(map<char,string> &numbers, string fileName){
    ofstream file(fileName);
    for (auto &p: numbers){
        file << p.first << p.second << endl;
    }
}

/**
 * @brief loadNum load user previous work
 * @param numbers associative array
 * @param fileName specified file name for content to be loaded from
 */
void loadNum(map<char,string> &numbers,string fileName){
    pair <map<char, string>::iterator, bool> result;
    ifstream file(fileName);
    string value;
    char key;
    int counter =  0;
    if (!file.fail()) {
        while (file >> key >> value) {
            result = numbers.insert(std::pair<char, string>(key, value));
            if (result.second){
                cout << "The expression was inserted!" << endl;
            }
            else {
                cout << "The expression was not inserted! It already exists!" << endl;
            }
        }
        cout << "Save completed!" << endl;
    }
    else {
        cout << "Invalid file!" << endl;
    }
}

/**
 * @brief help displays list of valid commands to the user
 */
void help(){
    cout<<"Hello! Welcome to big num calculator!"<<endl;
    cout<<"You may enter operations for n digits!"<<endl;
    cout<<"The operations are multiplication (*), division (/), subtraction(-), addition(+), " << endl;
    cout<<"greatest common divisor (GCD(x,y), combinations (C(x,y)), and permutations(P(x,y))." << endl;
    cout<<"Expressions must be entered as LET letter = valid operation" << endl;
    cout<<"Valid operations may differ. Please refer to any errors you receive." << endl;
}

/**
 * @brief beautifyString Make the display of the program more appealing to the user
 * @param line a string of digits that needs to look more appealing
 * @return a beautifiedString
 */
string beautifyString(string line){
    int insertPosition = line.length()-3;
    while (insertPosition>0) {
        line.insert(insertPosition,",");
        insertPosition-=3;
    }
    return line;
}

/**
 * @brief reverse Helper function for the divide funtion,reversing string results in easier calculation
 * @param line specified number
 */
void reverse(string &line){
    string temp;
    for(int i = 0; i < line.size(); ++i)
        temp = line[i] + temp;
    line = temp;
}

/**
 * @brief getLine continously ask for userinput
 * @param title the 'legend' that will be displayed to the user
 * @param line a string that represents the userinput
 * @param numbers associative array
 * @return true or false depending on the user input
 */
bool getLine(string title,string &line,map<char,string> numbers){
    cout<<title;
    getline(cin,line);

    if (line.empty()){
        savebeforequit(numbers);
    }

    return !line.empty();
}

/**
 * @brief savebeforequit if user has not saved work previously prompt them if they would like save before they quit the programs
 * @param numbers associative array
 * @return N/A
 */
bool savebeforequit(map<char,string> numbers){
    string input,filename;
    cout << "Would you like to save before quitting? Enter Y for yes and N for no" << endl;
    cin >> input;

    if (input == "Y"){
        cout << "Enter file name to save to: " << endl;
        cin >> filename;
        saveNums(numbers,filename);
        exit(0);
    }

}

string findLetter(string line){
    string temp;
    trimString(line);

    if (isalpha(line[0])){
        temp = line[0];
    }
    else {
        cout << "Incorrect expression entered! LET must be followed by letter!" << endl;
        temp = "";
    }

    return temp;
}

/**
 * @brief processLine processing portion of the 'let' function
 * @param line a string entered by the user containing a desired operation to be performed
 * @return N/A
 */
string processLine(string line)
{
    int pos, pos1,pos2,pos3,pos4;
    int comma,backparen,plus;
    int commacount;
    string answer,operand1,operand2, remainder;
    char op;
    sanitize(line,commacount);

    if ((pos = line.find_first_of("/")) < line.size())
    {

        answer, operand1 = line.substr(0,pos-commacount),
                operand2 = line.substr(pos+1+commacount);

        op = line[pos];
    }
    else if ((pos1 = line.find_first_of("-")) < line.size()){

        answer, operand1 = line.substr(0,pos1),
                operand2 = line.substr(pos1+1);

        op = line[pos1];
    }
    else if ((plus = line.find_first_of("+")) < line.size()){
        answer, operand1 = line.substr(0,plus),
                operand2 = line.substr(plus+1);

        op = line[plus];
    }
    else if ((pos2 = line.find_first_of("*")) < line.size()){

        answer, operand1 = line.substr(0,pos2),
                operand2 = line.substr(pos2+1);

        op = line[pos2];
    }
    else if ((pos3 = line.find_first_of("!")) < line.size()){

        answer, operand1 = line.substr(0,pos3);
        op = line[pos3];
    }
    else if ((pos4 = line.find_first_of("D")) < line.size()){
        if ((comma = line.find_first_of(",")) < line.size()){

            answer, operand1 = line.substr(pos4+2,comma-pos4-2);
            if ((backparen = line.find_first_of(")")) < line.size())
            {
                operand2 = line.substr(comma+1,backparen-comma-1);
                op = line[pos4];
            }
        }
    }
    else if ((pos4 = line.find_first_of("C")) < line.size()){
        if ((comma = line.find_first_of(",")) < line.size()){
            answer, operand1 = line.substr(pos4+2,comma-pos4-2);
            if ((backparen = line.find_first_of(")")) < line.size())
            {
                operand2 = line.substr(comma+1,backparen-comma-1);
                op = line[pos4];
            }
        }
    }
    else if ((pos4 = line.find_first_of("P")) < line.size()){
        if ((comma = line.find_first_of(",")) < line.size()){
            answer, operand1 = line.substr(pos4+2,comma-pos4-2);
            if ((backparen = line.find_first_of(")")) < line.size())
            {
                operand2 = line.substr(comma+1,backparen-comma-1);
                op = line[pos4];
            }
        }
    }


    //    cout<<"Operand1:" << operand1<<" Operand2: "<<operand2<<" op: "<<op<<endl;
    if (op == '-'){
        if (comparison(operand1,operand2)){
            cout << "Subtraction takes smallest one second! Enter new numbers!" << endl;
            answer = "";
        }
        else {
            subtract(operand1,operand2,answer);
        }
    }
    else if (op == '+'){
        if (comparison(operand2,operand1)){
            swap(operand1,operand2);
            answer = addition(operand1,operand2);
        }
        else {
            answer = addition(operand1,operand2);
        }
    }
    else if (op == '/')
    {
        if (comparison(operand1,operand2)){
            cout << "Division takes smallest one second! Enter new numbers!" << endl;
            answer = "";
        }
        else {
            divide(operand1,operand2,answer, remainder);
        }
    }
    else if (op == '*')
    {
        answer = karasuba(operand1,operand2);
    }
    else if (op == '!'){
        answer = factorial(operand1);
    }
    else if (op == 'C'){
        answer = combination(operand1,operand2);
    }
    else if (op == 'D'){
        answer = GCD(operand1,operand2);
    }
    else if (op == 'P'){
        answer = permutation(operand1,operand2);
    }
    return answer;
}

/**
 * @brief sanitize Given special defined operations the user would like to compute sanitize them to make them easy to parse
 * @param line string entered by the user
 * @param comma defines the position of the line
 */
void sanitize(string &line, int &comma)
{
    int pos = 0;
    comma = 0;
    const string special = ("PGCD");
    if (pos = line.find_first_of(special) < line.size()){
        return;
    }
    else {
        while(((pos = line.find_first_of(" ,",pos))) < line.size()) {
            line.erase(pos, 1);
            comma++;
        }
    }
}


/**
 * @brief comparison helper function for permutation and combination
 * @param str1 first string
 * @param str2 second string
 * @return true or false depending if certain conditions are held
 */
bool comparison(string str1, string str2)
{
    // If first one is smaller than second one
    // Return true when first one is smaller, return false when first one is bigger
    int l1 = str1.length(), l2 = str2.length();

    if (l1 < l2){
        return true;
    }
    if (l1 > l2){
        return false;
    }

    for (int i=0; i<l1; i++)
    {
        if (str1[i] < str2[i]){
            return true;
        }
        else if (str1[i] > str2[i]){
            return false;
        }
    }
    return false;
}

/**
 * @brief subtract Given two strings return the mathematical equivalent of difference of two numbers
 * @param operand1 first string of digits
 * @param operand2 second string of digits
 * @param answer string that will represent the difference of two numbers
 */
void subtract(string operand1, string operand2, string &answer)
{
    int shortest = min(operand1.size(),operand2.size()),
            payback = 0;
    answer = "";

    reverse(operand1);
    reverse(operand2);

    for(int i = 0; i < shortest; ++i)
    {
        int result = (operand1[i]-48) - ((operand2[i]-48) + payback);
        if(result < 0)
        {
            payback = 1;
            result = 10 + result;
        }
        else
            payback = 0;
        result = 48 + abs(result);
        answer += (char)result;
    }
    for(int i = shortest; i < operand1.size(); ++i)
    {
        int result = (operand1[i] - 48) - (payback);
        if(result < 0)
        {
            payback = 1;
            result = 10 + result;
        }
        else
            payback = 0;
        result = 48 + abs(result);
        answer += (char)result;
    }
    reverse(answer);
    while(answer.size() > 1 && answer[0] == 48)
        answer.erase(0,1);

}

/**
 * @brief divide gives the mathematical equivalent of division
 * @param operand1 first string of numbers
 * @param operand2 second string of numbers
 * @param answer string that will represent the answer
 * @param remainder string that will represent the remainder of the division
 */
void divide(string operand1, string operand2, string &answer, string &remainder) {
    long long count = 0;
    string counter = "0";
    string one = "1";
    string difference;
    int mod = 0;
    string temp;

    while (difference != "1" && difference != "0" && !(comparison(operand1,operand2))) {
        subtract(operand1, operand2, difference);
        operand1 = difference;
        counter = addition(one, counter);
        count++;
    }
    if (difference == "0"){
        answer = counter;
        remainder = "0";

    }
    else {
        answer = counter;
        remainder = operand1 + "/" + operand2;

    }
}

/**
 * @brief addition Given two valid string expressions entered by the user return the equilivalent of the sum of both elements
 * @param low the smaller element given by the user will be padded
 * @param high the larger element entered by the user
 * @return return the sum of both elements
 */
string addition(string low,string high){
    int sum, carry =0;
    string result= "";
    int difference = high.length()-low.length();
    for(int i =0; i <=difference;i++)
        low="0"+low;
    high="0"+high;
    for (int i = low.length()-1; i >= 0; i--) {
        sum = (high[i]-'0')+(low[i]-'0')+carry;
        carry=0;
        if(sum>9){
            sum-=10;
            carry=1;
        }
        result= to_string(sum)+result;
    }
    while(result[0] == '0')
        result.erase(0,1);
    return result;
}

/**
 * @brief factorial given a string entered by the user give the mathematical equivalent of a factorial
 * @param operanda a string of digits that the user would like to get the factorial from
 * @return factorial
 */
string factorial(string operand){
    string temp = operand;
    string multiplier = "2";
    while(multiplier!=temp){
        operand = multiply(operand,multiplier);
        multiplier = addition("1",multiplier);
    }
    return operand;
}

/**
 * @brief permutation given two string return the mathematical equivalent of a permutation
 * @param n represents the number of 'n' elements
 * @param k represent the number of 'k' elements
 * @return a string that represents a permutation given the previous parameters
 */
string permutation(string n,string k){
    string multiplier;
    if (comparison(n,k))
    {
        cout << "Error! Please enter combination in descending order" << endl;
        n = "";
    }
    else {

        subtract(n, k, multiplier);
        multiplier = addition("1", multiplier);
        string temp = n;
        string operand;
        while (multiplier != temp) {
            n = multiply(n, multiplier);
            multiplier = addition("1", multiplier);
        }
    }
    return n;
}

/**
 * @brief combination given two string return the mathematical equivalent of a combination
 * @param n represents the number of 'n' elements
 * @param k represent the number of 'k' elements
 * @return a string that represents a combination given the previous parameters
 */
string combination(string n,string k){
    string answer = "", remainder = "";
    if (comparison(n,k))
    {
        cout << "Error! Please enter combination in descending order" << endl;
        answer = "";
    }
    else {
        string permutationOfK = permutation(n,k);
        string kFactorial = factorial(k);
        divide(permutationOfK,kFactorial,answer,remainder);
    }
    return answer;
}

/**
 * @brief swap switch two string values
 * @param n first string
 * @param m second string
 */
void swap(string &n, string &m){
    string temp;
    temp = n;
    n = m;
    m = temp;
}

/**
 * @brief GCD Gives the greatest common denomator of two specified strings
 * @param n first string
 * @param m second string
 * @return the GCD of the two previously defined string
 */
string GCD(string n, string m){
    string remainder = "";
    string answer =  "";
    string product;
    string mod;

    while(n != "0"){
        //        dividend - (counter * divisor) = modulus
        if(n=="0") {
            return m;
        }
        else {
            mod = modulo(m,n);
            m = n;
            n = mod;
        }
    }
    return m;
}

/**
 * @brief modulo helper function to the GCD
 * @param m string of digits
 * @param n string of digits
 * @return return the mod of a particular string m and n
 */
string modulo(string m, string n){
    string answer,remainder, product, mod;

    divide(m,n,answer,remainder);
    if (answer=="0"){
        mod = m;
        return mod;
    }
    else{
        product = multiply(answer,n);
        subtract(m,product,mod);
    }

    return mod;
}

/**
 * @brief multiply given two strings multiply them and return their product
 * @param operand1 the first string entered in by the user
 * @param operand2 the second string entered in by the user
 * @return a string containing product of both of their strings
 */
string multiply(string operand1,string operand2){
    if(operand1.size()==0 || operand2.size()== 0)
        return "0";
    vector<int> result(operand1.length()+operand2.length(),0);
    int operand1Index= 0, operand2Index=0;
    for(int i = operand1.size()-1; i>=0;i--){
        int carry = 0;
        int operand1CurrentValue = operand1[i]-48;
        operand2Index =0;
        for(int j = operand2.size()-1;j>=0;j--){
            int operand2CurrentValue = operand2[j]-48;
            int sum = operand1CurrentValue*operand2CurrentValue+result[operand1Index+operand2Index]+carry;
            carry=sum/10;
            result[operand1Index+operand2Index] = sum % 10;
            operand2Index++;
        }
        if(carry>0){
            result[operand1Index+operand2Index]+=carry;
        }
        operand1Index++;
    }
    string finalResult = "";
    for(int i = result.size()-1;i>=0;i--)
        finalResult+=to_string(result[i]);
    trimZerosFromHead(finalResult);
    return finalResult;
}

/**
 * @brief trimZerosFromHead helper function for multiplication and addtion, subtract padding from head of string
 * @param line specified string of numbers
 */
void trimZerosFromHead(string &line){
    while(line[0]=='0')
        line.erase(0,1);
}

/**
 * @brief add function add two strings together
 * @param operand1 string entered by the user containing digits
 * @param operand2 string entered by the user containining digits
 * @return a string that represents the two strings above added
 */
string addForKarasuba(string operand1, string operand2) {
    int length = max(operand1.size(), operand2.size());
    int carry = 0;
    int sum;  // sum of two digits in the same column
    string result;

    // pad the shorter string with zeros
    while (operand1.size() < length)
        operand1 = "0"  + operand1;

    while (operand2.size() < length)
        operand2 = "0"+operand2;

    // build result string from right to left
    for (int i = length-1; i >= 0; i--) {
        sum = (operand1[i]-'0') + (operand2[i]-'0') + carry;
        carry = sum/10;
        result.insert(0,to_string(sum % 10));
    }

    if (carry)
        result.insert(0,to_string(carry));

    // remove leading zeros
    while(result[0] == '0')
        result.erase(0,1);
    return result;
}

/**
 * @brief subtract function subtract two strings together
 * @param operand1 string entered by the user
 * @param operand2 string entered by the user
 * @return string that represents the two string above subtracted
 */
string subtractForKarasuba(string operand1, string operand2) {
    int length = max(operand1.size(), operand2.size());
    int diff;
    string result;

    while (operand1.size() < length)
        operand1= "0"+operand1;

    while (operand2.size() < length)
        operand2 = "0" +operand2;

    for (int i = length-1; i >= 0; i--) {
        diff = (operand1[i]-'0') - (operand2[i]-'0');
        if (diff >= 0)
            result.insert(0, to_string(diff));
        else {

            // borrow from the previous column
            int j = i - 1;
            while (j >= 0) {
                operand1[j] = ((operand1[j]-'0') - 1) % 10 + '0';
                if (operand1[j] != '9')
                    break;
                else
                    j--;
            }
            result.insert(0, to_string(diff+10));
        }

    }

    while(result[0] == '0')
        result.erase(0,1);
    return result;
}

/**
 * @brief karasuba implementation of the karasuba algorithm
 * @param operand1 first string to be multiplied
 * @param operand2 second string to be multiplied
 * @return the strings multiplied
 */
string karasuba(string operand1, string operand2) {
    //Determine the length of the string by the bigger string
    int length = max(operand1.size(), operand2.size());

    //Pad both string to be of equal length
    while (operand1.size() < length)
        operand1 = "0"+operand1;

    while (operand2.size() < length)
        operand2 = "0"+operand2;

    //If the strings are small multiply directly(base case)
    if (length == 1)
        return to_string((operand1[0]-'0')*(operand2[0]-'0'));

    //Split the strings into two half as defined in the
    //karasuba algorithm
    string a = operand1.substr(0,length/2);
    string b = operand1.substr(length/2,length-length/2);
    string c = operand2.substr(0,length/2);
    string d = operand2.substr(length/2,length-length/2);
    //step-by-step of the karasuba algorithm
    //Step 1: compute AC
    //Step 2: compute BD
    //Step 3: compute (A+B)*(C+D)
    //Step 4: Step 3 - Step 2- Step 1
    //Step 5: AC+BD+Step 4
    string ac = karasuba(a,c);
    string bd = karasuba(b,d);
    string abPluscd = karasuba(addForKarasuba(a,b),addForKarasuba(c,d));
    string step4 = subtractForKarasuba(abPluscd,addForKarasuba(ac,bd));
    //pad to get result into merging stage
    for (int i = 0; i < 2*(length-length/2); i++)
        ac.append("0");
    for (int i = 0; i < length-length/2; i++)
        step4.append("0");
    string result = addForKarasuba(addForKarasuba(ac,bd),step4);
    //trim any zeros from the head of the string
    while(result[0] == '0')
        result.erase(0,1);
    return result;
}

/**
 * @brief oddsOfPoker The function displays all the odds of particular poker hands in the game of poker using combinations
 */
void oddsOfPoker(){
    cout<<"The odds of drawing a four of a kind on the first deal is "<<factorial("4")<<"\\"<<permutation("52","48")<<endl;
    cout<<"The odds of drawing a three of a kind on the first deal is "<<factorial("3")<<"\\"<<permutation("52","48")<<endl;
    cout<<"The odds of drawing a two pair on the first deal is "<<factorial("2")<<"\\"<<permutation("52","48")<<endl;
    cout<<"The odds of drawing a royal flush on the first deal is 4 \\ "<<combination("52","5")<<endl;
    cout<<"The odds of drawing a flush on the first deal is "<<multiply(combination("13","5"),"4")<<"\\"<<combination("52","5")<<endl;
    cout<<"The odds of drawing a pair on the first draw is "<<4*2<<" \\ "<<permutation("52","48")<<endl;
}

/**
 * @brief possiblePokerHands The function displays all the possible poker hands in the game of poker using combinations
 */
void possiblePokerHands(){
    cout<<"The total number of poker hands are "<<combination("52","5")<<endl;
    cout<<"The total number of flushes are "<<40<<endl;
    cout<<"The total number of two pair hands are "<<multiply(combination("13","2"),multiply("44","36"))<<endl;
    cout<<"The total number of 3-of-a-kind hands are "<<multiply(multiply(combination("12","2"),"13"),"64")<<endl;
    cout<<"The total number of hands with a pair are "<<multiply(multiply(multiply(combination("12","3"),"13"),"64"),"4")<<endl;
    cout<<"The total number of straights are "<<pow(4,5)*10-40<<endl;
    cout<<"The total number of full houses are "<<13*12*6*4<<endl;
}



