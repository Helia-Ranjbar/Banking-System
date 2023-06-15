#ifndef loan_h
#define loan_h

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

class Loan 
{
    double amount, return_amount, loan_code;
    string national_code  ;
    bool is_paid= false;
    time_t start_time;

public:
    Loan(double a, double r, double l , string na , time_t s)
    : amount(a), return_amount(r), loan_code(l), national_code(na), start_time(s) {} 

    Loan(){}

    void add()
    {
        ofstream file;
        file.open("loan.csv",ios::app);

        getline(cin,national_code);
        national_code= national_code+',';

        srand(time(NULL));
        loan_code=rand();
        

        cin>>amount;

        start_time = time(0);
        char* dt = ctime(&start_time);

        return_amount=amount*1.2;

        string c=",";

        file<<national_code<<loan_code<<c<<amount<<c<<return_amount<<c<<dt;

        file.close();      
    }
    void paid()
    {
        is_paid=true;
    }
};

int main()
{
    //Loan a;
   // a.add();
        time_t start_time = time(0);
        char* dt = ctime(&start_time);
        char a='5';
        if(*dt!=a)
            cout<<"no";


}

#endif