#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

//convert pin number to hash for saving into the file.
unsigned int Hash(string & data)
{
    unsigned int result(0);

    for(unsigned int ch: data)
        result = ch + (result<<4) + (result<<10) - result;

    return result;
}


class Account
{

protected:
    long long number,balance;
    string national_code, account_type;
    time_t expire_year, expire_month;
    unsigned int pin;
    int cvv2,lineToRemove;

public:

    Account(long long nu, string na, time_t ey, time_t em, string a, long p, int c)
    : number(nu), national_code(na), expire_year(ey),expire_month(em), account_type(a), pin(p), cvv2(c){}

    Account(){}

    void add()
    {
        ofstream file;
        file.open("account.csv", ios::app);
        
        cout<<"Enter your national code: ";
        getline(cin,national_code);
        national_code= national_code+',';

        srand(time(NULL));
        number=rand()*10;

        cout<<"Enter your acoount type: 1:current account 2:short term account 3:long term account";
        getline(cin,account_type);
        account_type= account_type+',';

        expire_year= time(nullptr);
        tm* local_time = localtime(&expire_year);
        expire_year=local_time->tm_year+1900 +5;

        expire_month= time(nullptr);
        tm* local_time1 = localtime(&expire_month);
        expire_month=local_time1->tm_mon+1;

        srand(time(NULL));
        pin=rand()/10;
        string pin1=to_string(pin);
        unsigned int pin2= Hash(pin1);
        

        srand(time(NULL));
        cvv2=rand();

        cout<<"Enter your balance: ";
        cin>>balance;

        string c=",";
        file<<national_code<<number<<c<<account_type<<expire_year<<c<<expire_month<<c<<cvv2<<c<<pin2<<c<<balance<<endl;

        cout<<"your card number:"<<number<<'\n'<<"exp year:"<<expire_year<<'\n'<<"exp month:"<<expire_month<<'\n'<<"cvv2: "<<cvv2<<'\n'<<"pin:"<<pin<<endl;

        file.close();
    }


    /*void delete_account(string filename)
    {
        cout<<"Enter the card number want to delete: ";
        cin>>number;
        cout<<v_number[0];
        for(int i=0;i<v_number.size();i++)
        {
            cout<<i<<endl;
            if(number==v_number[i])
            {
                
                lineToRemove=i;
            }
        }
        // Open the input and output files
        ifstream inputFile(filename);
        ofstream outputFile(filename + ".tmp");

        // Copy all lines except for the one to be removed
        string line;
        int lineNumber = 1;
        while (getline(inputFile, line)) {
            if (lineNumber != lineToRemove) {
                outputFile << line <<endl;
            }
            ++lineNumber;
        }

        inputFile.close();
        outputFile.close();

        // Delete the original file
        remove(filename.c_str());

        // Rename the temporary file to the original file name
        rename((filename + ".tmp").c_str(), filename.c_str());
    }*/

    

};


int main()
{
    Account a;
    a.add();
   // a.delete_account("account.csv");
}
