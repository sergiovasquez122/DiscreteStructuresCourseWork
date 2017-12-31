/**
  AUTHOR: SERGIO VASQUEZ
  PROGRAM PURPOSE: Program implements the karatsuba algorithm, a fast multiplication
  technique that is of big(nlogn) as supposed to the big(n*n) time complexity based on
  clever mathematics and dynamic programming
  DATE CREATED: 12/11/17
  */
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief add function add two strings together
 * @param operand1 string entered by the user containing digits
 * @param operand2 string entered by the user containining digits
 * @return a string that represents the two strings above added
 */
string add(string operand1, string operand2) {
    int length = max(operand1.size(), operand2.size());
    int carry = 0;
    int sum_col;  // sum of two digits in the same column
    string result;

    // pad the shorter string with zeros
    while (operand1.size() < length)
        operand1 = "0"  + operand1;

    while (operand2.size() < length)
        operand2 = "0"+operand2;

    // build result string from right to left
    for (int i = length-1; i >= 0; i--) {
        sum_col = (operand1[i]-'0') + (operand2[i]-'0') + carry;
        carry = sum_col/10;
        result.insert(0,to_string(sum_col % 10));
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
string subtract(string operand1, string operand2) {
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
    string abPluscd = karasuba(add(a,b),add(c,d));
    string step4 = subtract(abPluscd,add(ac,bd));
    //pad to get result into merging stage
    for (int i = 0; i < 2*(length-length/2); i++)
        ac.append("0");
    for (int i = 0; i < length-length/2; i++)
        step4.append("0");
    string result = add(add(ac,bd),step4);
    //trim any zeros from the head of the string
    while(result[0] == '0')
        result.erase(0,1);
    return result;
}


int main() {
    cout<<karasuba("12","24")<<endl;
}
