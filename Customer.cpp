#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "account.hpp"
#include "transaction.hpp"
#include "loan.hpp"

using namespace std;

class Customer: public Account, public Transaction, public Loan
{    
    string national_code,  password,  first_name,  last_name,  gender,  phone,  date_of_birth;
    time_t transaction_year , transaction_month ,transaction_day;
   

public:

    //create and delete an account is written in Account class.
    //do transaction is written in Transaction class.
    //request loan is written in Loan class.

    void signin()
    {
        string b=".";

        cout<<"Enter your national code: ";
        cin>>national_code;

        cout<<"Enter password: ";
        cin>>password;
        unsigned int pass= Hash(password);
        string pass2= to_string(pass);

        cout<<"Enter your first name: ";
        cin>>first_name;

        cout<<"Enter your last name: ";
        cin>>last_name;

        cout<<"Enter your gender: ";
        cin>>gender;

        cout<<"Enter your phone number: ";
        cin>>phone;

        cout<<"Enter your date of birth(exp: 1380/01/01): ";
        cin>>date_of_birth;

        string year = date_of_birth.substr(0,4);
        int int_year;
        istringstream(year)>>int_year;

        if(1402-int_year<18)
        {
            cout<<"you are under 18 year!";
            
        }
        else
        {
            transaction_year = time(nullptr);
            tm* local_time1 = localtime(&transaction_year);
            transaction_year=1900 + local_time1->tm_year;

            transaction_month = time(nullptr);
            tm* local_time2 = localtime(&transaction_month);
            transaction_month=local_time2->tm_mon+1;

            transaction_day = time(nullptr);
            tm* local_time3 = localtime(&transaction_day);
            transaction_day=local_time3->tm_mday;
            
            string c=",";

            ofstream file;
            file.open("customer.csv", ios::app);

            file<<national_code<<c<<pass2<<c<<first_name<<c<<last_name<<c<<gender<<c<<phone<<c<<date_of_birth
            <<c<<transaction_year<<b<<transaction_month<<b<<transaction_day<<'\n';

            file.close();

            cout<<"Sign in successfully!";
        }

    }

};

int main()
{
    Customer c1;
    c1.signin();


}