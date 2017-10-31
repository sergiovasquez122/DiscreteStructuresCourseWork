/**
 AUTHOR:
        Sergio Vasquez
 PURPOSE:
       *Give user 'n' number  of iterations of credit card values
        depending on the credit card type and database the user
        chooses from
 DATE CREATED
        10/25/2017
 DATE LAST MODIFIED & MODIFIER:
        10/25/17, Sergio Vasquez
 KEY UPDATES & UPDATER:
        Sergio Vasquez 10/25/17
                *Made two vectors strings, one holds the visa banks and one holds the banks id
                *Created list function to display all elements of a vector
                *Created command function to ask for userinput
                *Created getLine function to continously  ask for user input until
                 they enter an empty line
                *Created functions to generate credit cards
        Sergio Vasquez 10/27/17
                *Combined the amex dataset with the visa data set
                * Added case to allow for user to select from american
                  express card
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <iomanip>
#include <time.h>
using namespace std;
void randomDigits(string &creditCard);
void reset(string &creditCard,int length);
void generateCreditCards(string &creditCard);
int findIndexPosition(vector<string> &banks,int firstIndex,int lastIndex);
void list(vector<string> &banks,int firstIndex,int lastIndex);
void fillVector(vector<string> &bankID, vector<string> &banks,string fileName);
bool getLine(string &line,string output);
bool displayCommands(string &line, vector<string> &banks, vector<string> &banksID);
char computedCheckDigit(const string &cardNumber);
void displayLegend();
int main() {
    srand(time(0));
    vector<string> banks;
    banks.reserve(1500);
    vector<string> bankID;
    bankID.reserve(1500);
    //The project required a dataset which I included, change the  second parameter of fill vector
    //to the relative path of the file
    fillVector(bankID,banks,"//home//sergio//Desktop//CS45//creditCardFileRead//parsedVisa.txt");
    string input;
    displayLegend();
    while (getLine(input,"Enter cmd: ")){
        displayCommands(input,banks,bankID);
    }
}
void list(vector<string> &banks,int firstIndex,int lastIndex ){
    for(;firstIndex<lastIndex;firstIndex++){
        cout<<firstIndex<<":\t"<<banks.at(firstIndex)<<endl;
    }
    cout<<"Scroll up and choose from the following by entering their index: "<<endl;
}

/**
 * @brief fillVector the dataset was parsed so that in the file content the bankid
 *                   was an odd index and the bank name was an even index
 * @param bankID     6-7 digits taken as a string
 * @param banks      Name of particular bank
 * @param fileName   name of the file vector will be take
 */
void fillVector(vector<string> &bankID,vector<string> &banks,string fileName){
    ifstream in(fileName);
    string number;
    int pos=0;
    if(in.fail())
    {
        cout<<"File not found!"<<endl;
        exit(1);
    }
    while(getline(in,number))
    {
        if(pos%2==0)
            bankID.push_back(number);
        else
            banks.push_back(number);
        pos++;
    }

    in.close();
}

bool displayCommands(string &line,vector<string> &banks,vector<string> &banksID){
    int j=-1;
    int firstIndex,lastIndex;
    int pos;
    if(!islower(line[0])&&line[0]%48<10){
        char stringConverter = line[0];
        j = stringConverter-'0';
    }
    switch (j) {
    //Debit card
    case 0:
        firstIndex = 0, lastIndex = 78;
        pos = findIndexPosition(banks,firstIndex,lastIndex);
        generateCreditCards(banksID[pos]);
        break;
    case 1:
        firstIndex =78, lastIndex = 1293;
        pos = findIndexPosition(banks,firstIndex,lastIndex);
        generateCreditCards(banksID[pos]);
       break;
    default:
        cout << "Not a valid response,below are the available commands,enter any key to continue: " << endl;
        displayLegend();
        break;
    }
    return getLine(line,"");
}
int findIndexPosition(vector<string> &banks,int firstIndex,int lastIndex){
    list(banks,firstIndex,lastIndex);
    int index;
    cin>>index;
    return index;
}
bool getLine(string &line,string output)
{
    cout<<output;
    getline(cin,line);
    return !line.empty();
}
/**
 * @brief computedCheckDigit is the processing function to
 * compute the check digit.Is an implementation of
 * 'Luhn's' algorithm
 * @param cardNumber string entered by user that contains
 * 16 digit credit card number
 * @return computed check digit
 */
char computedCheckDigit(const string &cardNumber)
{
    int numbers[15], total = 0, checkDigit;
    for(int i = 14; i >= 0; --i)
        switch(i%2)
        {
        case 0 : switch(cardNumber[i])
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4': numbers[i] = 2 * (cardNumber[i]-48);
                break;
            case '5': numbers[i] = 1;
                break;
            case '6': numbers[i] = 3;
                break;
            case '7': numbers[i] = 5;
                break;
            case '8': numbers[i] = 7;
                break;
            case '9': numbers[i] = 9;
            }
            break;


        case 1 : numbers[i] = cardNumber[i] - 48;
        };
    for(int i = 0; i < 15; total += numbers[i++]);
    checkDigit =((total * 9)%10)%10;
    return (char)(48 + checkDigit);
}
/**
 * @brief generateCreditCards
 *              The function is used to generate the credit
 *              card values with the database input
 *              specified by the user
 * @param creditCard
 *              'n' digit string < 16 found in database
 *              'mar' bank'
 */
void generateCreditCards(string &creditCard){
    int creditCardLength = creditCard.length();
    int numOfIterations = 100;
    for(int i = 0; i<=numOfIterations;i++){
        randomDigits(creditCard);
        char checkDigit = computedCheckDigit(creditCard);
        creditCard.push_back(checkDigit);
        cout<<"Valid credit card is : "<<creditCard<<endl;
        reset(creditCard,creditCardLength);
    }
}


/**
 * @brief randomDigits makes the remaining 9 random digits
 * for the credit card inputted by the user
 * @param creditCard string specified by the user
 */
void randomDigits(string &creditCard){
    int randomDigitsLength= 15-creditCard.length();
    char value;
    for(char i = 0; i<=randomDigitsLength;i++){
        value= (char) (rand()%9)+48;
        creditCard.push_back(value);
    }
}
/**
 * @brief reset deletes random digits from string to allow
 * for more inputs
 * @param creditCard string specified by the user
 */
void reset(string &creditCard,int length){
    creditCard.erase(length);
}
void displayLegend(){
    cout<<"0:\t Visa Database"<<endl;
    cout<<"1:\t American Express Database"<<endl;
}
/*
0:	 Visa Database
1:	 American Express Database
Enter cmd: 0
0:	STAR_NETWORKS,_INCN/AN/AUNITED_STATES_OF_AMERICA
1:	EFUNDS_CORPORATIONN/AN/AUNITED_STATES_OF_AMERICA
2:	FIFTH_THIRD_BANKN/AN/AUNITED_STATES_OF_AMERICA
3:	FIFTH_THIRD_BANKN/AN/AUNITED_STATES_OF_AMERICA
4:	FIFTH_THIRD_BANKN/AN/AUNITED_STATES_OF_AMERICA
5:	FIFTH_THIRD_BANKN/AN/AUNITED_STATES_OF_AMERICA
6:	STAR_NETWORKS,_INCN/AN/AUNITED_STATES_OF_AMERICA
7:	TRANSALLIANCE,_L.P.N/AN/AUNITED_STATES_OF_AMERICA425-644-5121
8:	MINIBANK_SWITCH_NETWORKN/AN/AUNITED_STATES_OF_AMERICA
9:	WACHOVIA_BANK_N.A.N/AN/AUNITED_STATES_OF_AMERICA
10:	LA_FEDERATION_DES_CAISSES_DESJARDINS_DU_QUEBECN/AN/ACANADA
11:	LA_FEDERATION_DES_CAISSES_DESJARDINS_DU_QUEBECN/AN/ACANADA
12:	BARCLAYS_BANK_PLCCREDITCLASSICPORTUGAL
13:	HYPO_ALPE-ADRIA-BANK_JOINT_STOCK_COMPANYN/AN/ABOSNIA_AND_HERZEGOVINA385-31-231495
14:	PLUS_SYSTEM,_INCN/AN/AUNITED_STATES_OF_AMERICA303-389-7862
15:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
16:	PLUS_SYSTEM,_INCN/AN/AUNITED_STATES_OF_AMERICA303-389-7862
17:	ITS,_INCN/AN/AUNITED_STATES_OF_AMERICA
18:	U.S._BANK_N.A._(USBNS)N/AN/AUNITED_STATES_OF_AMERICA
19:	THE_SOUTHERN_F.C.U.DEBITCLASSICUNITED_STATES_OF_AMERICA800-238-2827
20:	AMINIT_LTDN/AN/AISRAEL972-3-6364788
21:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
22:	OJSC_NAURYZ_BANK_KAZAKHSTANCREDITGOLD/PREMKAZAKHSTAN7-3272-590109
23:	OJSC_NAURYZ_BANK_KAZAKHSTANCREDITBUSINESSKAZAKHSTAN7-3272-590109
24:	CORE_C.U.DEBITCLASSICUNITED_STATES_OF_AMERICA800-215-6280
25:	PINNACLE_C.U.DEBITCLASSICUNITED_STATES_OF_AMERICA800-657-6366
26:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
27:	SCOTT_C.U.CREDITGOLD/PREMUNITED_STATES_OF_AMERICA800-215-6280
28:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
29:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
30:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
31:	WACHOVIA_BANK_N.A.N/AN/AUNITED_STATES_OF_AMERICA
32:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
33:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
34:	ADEL_BANKING_COMPANYDEBITCLASSICUNITED_STATES_OF_AMERICA412-552-2549
35:	THE_CITIZENS_BANKDEBITCLASSICUNITED_STATES_OF_AMERICA412-552-2549
36:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
37:	GENERAL_TECHNOLOGIES_F.C.U.DEBITCLASSICUNITED_STATES_OF_AMERICA303-486-7294
38:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
39:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
40:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
41:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
42:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
43:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
44:	BANCO_DO_BRASIL_S.A.DEBITELECTRONBRAZIL
45:	ASIA_PACIFIC_BANKCREDITCLASSICTAIWAN
46:	PEMCO_CORPORATIONN/AN/AUNITED_STATES_OF_AMERICA
47:	ASIA_PACIFIC_BANKCREDITGOLD/PREMTAIWAN
48:	THE_HONGKONG_AND_SHANGHAI_BANKING_CORPORATION_LIMITEDCREDITCLASSICBRUNEI_DARUSSALAM
49:	THE_HONGKONG_AND_SHANGHAI_BANKING_CORPORATION_LIMITEDCREDITGOLD/PREMBRUNEI_DARUSSALAM
50:	THE_HONGKONG_AND_SHANGHAI_BANKING_CORPORATION_LIMITEDCREDITGOLD/PREMBRUNEI_DARUSSALAM
51:	VISA_NORGE_A/SDEBITPLATINUMNORWAY
52:	BEACON_C.U.DEBITCLASSICUNITED_STATES_OF_AMERICA877-866-7827
53:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
54:	BLACKHAWK_C.U.DEBITCLASSICUNITED_STATES_OF_AMERICA877-715-2299
55:	BANCO_ITAU_S.A.CREDITCLASSICBRAZIL
56:	CAIXA_ECONOMICA_FEDERALCREDITCLASSICBRAZIL
57:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
58:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
59:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
60:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
61:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
62:	BANCO_ITAU_S.A.CREDITCLASSICBRAZIL
63:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
64:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
65:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
66:	BANCO_ITAU_S.A.CREDITCLASSICBRAZIL
67:	CREDICARD_S.A._ADMINISTRADORA_DE_CARTOESDE_CREDITOCREDITCLASSICBRAZIL
68:	BANCO_SUDAMERIS_ARGENTINA_S.A.CREDITCLASSICARGENTINA54-11-43793300
69:	COOP_BANK_ABDEBITCLASSICSWEDEN46-8-7431000
70:	COOP_BANK_ABDEBITELECTRONSWEDEN46-8-7431000
71:	SOUTHTRUST_BANKDEBITCLASSICUNITED_STATES_OF_AMERICA
72:	DRESDNER_BANK_AGN/AN/AGERMANY
73:	BANK_OF_PALESTINE_LTD.DEBITELECTRONJORDAN
74:	BANK_OF_PALESTINE_LTD.N/AN/AJORDAN
75:	FLEET_NATIONAL_BANKCREDITBUSINESSUNITED_STATES_OF_AMERICA
76:	SIDELL_STATE_BANKDEBITCLASSICUNITED_STATES_OF_AMERICA
77:	SERVICES_C.U.N/AN/AUNITED_STATES_OF_AMERICA
Scroll up and choose from the following by entering their index:
45
Valid credit card is : 40020156788762188
Valid credit card is : 40020135857473451
Valid credit card is : 40020157456765286
Valid credit card is : 40020107576361358
Valid credit card is : 40020186870707136
Valid credit card is : 40020144187643271
Valid credit card is : 40020120358883704
Valid credit card is : 40020166453531333
Valid credit card is : 40020147564437737
Valid credit card is : 40020157363051325
Valid credit card is : 40020117664005234
Valid credit card is : 40020164031252032
Valid credit card is : 40020153801204324
Valid credit card is : 40020163047227824
Valid credit card is : 40020185566672779
Valid credit card is : 40020131021850363
Valid credit card is : 40020108071511378
Valid credit card is : 40020141307145103
Valid credit card is : 40020125227181803
Valid credit card is : 40020188865736041
Valid credit card is : 40020122350242549
Valid credit card is : 40020115035724728
Valid credit card is : 40020154821412183
Valid credit card is : 40020153887680659
Valid credit card is : 40020147121584062
Valid credit card is : 40020145136085174
Valid credit card is : 40020146015555521
Valid credit card is : 40020188178037447
Valid credit card is : 40020146731420732
Valid credit card is : 40020170071336677
Valid credit card is : 40020103482385247
Valid credit card is : 40020174146068050
Valid credit card is : 40020128504516281
Valid credit card is : 40020140288208629
Valid credit card is : 40020112506214816
Valid credit card is : 40020178738187701
Valid credit card is : 40020142758778424
Valid credit card is : 40020103553254449
Valid credit card is : 40020142304011787
Valid credit card is : 40020181876532375
Valid credit card is : 40020153186212741
Valid credit card is : 40020140470650812
Valid credit card is : 40020187265606737
Valid credit card is : 40020141430168125
Valid credit card is : 40020133268034003
Valid credit card is : 40020147842222071
Valid credit card is : 40020162884881504
Valid credit card is : 40020117234115409
Valid credit card is : 40020168733733018
Valid credit card is : 40020114474863711
Valid credit card is : 40020118830351671
Valid credit card is : 40020183664748235
Valid credit card is : 40020101720284362
Valid credit card is : 40020155348352334
Valid credit card is : 40020172447710418
Valid credit card is : 40020134205204547
Valid credit card is : 40020101014630742
Valid credit card is : 40020113446027146
Valid credit card is : 40020182812221570
Valid credit card is : 40020153634175030
Valid credit card is : 40020108753453047
Valid credit card is : 40020178557750614
Valid credit card is : 40020152413722302
Valid credit card is : 40020132085111517
Valid credit card is : 40020141004651631
Valid credit card is : 40020121352712743
Valid credit card is : 40020138418020251
Valid credit card is : 40020124704260327
Valid credit card is : 40020114157138380
Valid credit card is : 40020114765666565
Valid credit card is : 40020127105313243
Valid credit card is : 40020133646457362
Valid credit card is : 40020165032306035
Valid credit card is : 40020143831572601
Valid credit card is : 40020150102855665
Valid credit card is : 40020102075223705
Valid credit card is : 40020172165301363
Valid credit card is : 40020186417471727
Valid credit card is : 40020176284784060
Valid credit card is : 40020155660171203
Valid credit card is : 40020150688216304
Valid credit card is : 40020162601177653
Valid credit card is : 40020150104213129
Valid credit card is : 40020136273115541
Valid credit card is : 40020152602588431
Valid credit card is : 40020147347867051
Valid credit card is : 40020101008487043
Valid credit card is : 40020133671720644
Valid credit card is : 40020121255720327
Valid credit card is : 40020133341160847
Valid credit card is : 40020140708671449
Valid credit card is : 40020156353713552
Valid credit card is : 40020160674881865
Valid credit card is : 40020152612550404
Valid credit card is : 40020127751833205
Valid credit card is : 40020168735202173
Valid credit card is : 40020184063008733
Valid credit card is : 40020180143137468
Valid credit card is : 40020158332831228
Valid credit card is : 40020181485786466
Valid credit card is : 40020101486700326
Enter cmd:
*/
