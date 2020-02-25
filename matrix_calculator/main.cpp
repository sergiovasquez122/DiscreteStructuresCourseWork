#include <iostream>
#include "Fraction.h"
#include "Matrix.h"
#include "fstream"
using namespace std;

void test_output_stream(){
    Fraction fraction(1,2);
    cout<<"Expected: 1/2"<<" output: "<<fraction<<endl;
    fraction = Fraction(1/1);
    cout<<"Expected: 1"<<" output: "<<fraction<<endl;
    fraction = Fraction(-1,2);
    cout<<"Expected: -1/2" << " output: "<<fraction<<endl;
    fraction = Fraction(11,2);
    cout<<"Expected: 5 1/2"<<" output: "<<fraction<<endl;
    fraction = Fraction(-1,1);
    cout<<"Expected: -1"<<" output: "<<fraction<<endl;
}

void test_multiplication(){
    Fraction x(1,2);
    Fraction y(1,2);
    cout<<"Expected: 1/4"<<"output: "<<x*y<<endl;
    y = Fraction(-1,2);
    cout<<"Expected: -1/4"<<" output: "<<x*y<<endl;
}

void test_addition(){
    Fraction x(1,2);
    Fraction y(1,2);
    cout<<"Expected: 1 "<<"output: "<<x+y<<endl;
    y = Fraction(-1,2);
    cout<<"Expected:  0 "<<"output: "<<x+y<<endl;
    x = Fraction(1,1);
    y = Fraction(-1,1);
    cout<<"Expected: 0"<<" output: "<<x+y<<endl;
}

void test_subtraction(){
    Fraction x(1,2);
    Fraction y(1,2);
    cout<<"Expected 0 "<<"output: "<<x-y<<endl;
}

int gcd(int p,int q){
    return p%q==0?q: gcd(q,p%q);
}

void gcd_test(){
    cout<<"expected output: 2 actual: "<<gcd(2,2)<<endl;
    cout<<"expected output: 25 actual: "<<gcd(100,25)<<endl;
    cout<<"expected output: 25 actual: "<<gcd(100,25)<<endl;
}

void division_test(){
    Fraction x(1,1);
    Fraction y(1,1);
    cout<<"expected output: 1 actual: "<<x/y<<endl;
}

void inversion_test(){
    Matrix<Fraction> m(2,2);
    cout<<m<<endl;
    auto m_tranposed = m.transpose();
    cout<<m_tranposed<<endl;

    m = Matrix<Fraction>(3,2);
    cout<<m<<endl;
    m_tranposed = m.transpose();
    cout<<m_tranposed<<endl;
}


void help_screen(){
    cout<<"Welcome to the matrix calculator!"<<endl;
    cout<<"enter a file with a .matrix extension to create,edit or display the current matrix file"<<endl;
    cout<<"enter one matrix file followed by the operation and another matrix file to perform a computation"<<endl;
    cout<<"example mat1.matrix add mat2.matrix"<<endl;
    cout<<"current supported operations are add,multiply and subtract(+,*and -)"<<endl;
    cout<<"enter one matrix file followed by the operation and another matrix file followed by one other matrix file to store the "
          "result of the computation in the preceding file"<<endl;
    cout<<"can enter /h or /? if would like to view this help screen again"<<endl;
}

void edit_and_display(string& filename){
    if(filename.find(".matrix")==string::npos){
        filename.append(".matrix");
    }

    //entered partial or non-valid extension before program append correct one
    if(!regex_match(filename,regex(".*[.]matrix")))
        throw std::runtime_error("invalid file type");

    fstream file(filename);

    if(file.fail()){
        ofstream out(filename);
        cout<<"creating new matrix..."<<endl;
        Matrix<Fraction> m(2,2);
        cin>>m;
        cout<<"Matrix completed and saved in: "<<filename<<endl;
        out<<m<<endl;
        out.close();
    }
    else{
        cout<<"Displaying the matrix in... "<<filename<<endl<<endl;
        Matrix<Fraction> m(2,2);
        file>>m;
        cout<<m<<endl;
        cout<<"Would you like to edit the matrix (Y)es or (N)o "<<filename<<" : ";
        string userinput;
        getline(cin,userinput);
        if(userinput.empty() || toupper(userinput[0])!= 'Y'){
            exit(0);
        }
        else{
            cout<<"Editing the matrix in..."<<filename<<endl<<endl;
            cin>>m;
            ofstream out(filename);
            out<<m<<endl;
            cout<<"successfully edited "<<filename<<" exiting program..."<<endl;
        }
    }
    file.close();
}

bool valid(string& filename){
    if(filename.find(".matrix")==string::npos){
        filename.append(".matrix");
    }

    //entered partial or non-valid extension before program append correct one
    if(!regex_match(filename,regex(".*[.]matrix")))
        return false;

    ifstream file(filename);

    return !file.fail();
}


template<typename T>
Matrix<T> load(const string& filename){
    ifstream file(filename);
    Matrix<Fraction> m(2,2);
    file>>m;
    return m;
}

template<typename T>
Matrix<T> compute(const string& filename1,const string& op,const string& filename2){
    auto m1 = load<Fraction>(filename1);
    auto m2 = load<Fraction>(filename2);
    switch(op[0]){
        case '+':return m1+m2;
        case '-':return m1-m2;
        case '*':return m1*m2;
    }
    throw runtime_error("invalid operation");
}

int main(int argc,char* argv []) {
    if(argc==2){
        string file_name = argv[1];
        edit_and_display(file_name);
    }
    else if(argc == 3){
        help_screen();
    }
    else if(argc==4){
        string filename1 = argv[1];
        string op = argv[2];
        string filename2 = argv[3];

        if(!valid(filename1))throw std::runtime_error("matrix " + filename1+" does not exist");
        if(!valid(filename2))throw std::runtime_error("matrix " + filename2+" does not exist");
        auto m = compute<Fraction>(filename1,op,filename2);
        cout<<m<<endl;
    }

    else if(argc == 5){
        string filename1 = argv[1];
        string op = argv[2];
        string filename2 = argv[3];
        string filename3 = argv[4];

        if(!valid(filename1))throw std::runtime_error("matrix " + filename1+" does not exist");
        if(!valid(filename2))throw std::runtime_error("matrix " + filename2+" does not exist");

        auto m = compute<Fraction>(filename1,op,filename2);
        cout<<"Output of "<<filename1<<" "<<op<<" "<<filename2<<endl<<endl;
        cout<<m<<endl;
        ofstream out(filename3);
        out<<m<<endl;
        cout<<"Saving matrix to "<<filename3<<"..."<<endl;
        out.close();
    }
}

