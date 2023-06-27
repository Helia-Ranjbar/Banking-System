#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

class Loan 
{
    double amount, return_amount, loan_code;
    string national_code  ;
    time_t start_year, start_month, start_day;

public:
    /*Loan(double a, double r, double l , string na , time_t s)
    : amount(a), return_amount(r), loan_code(l), national_code(na), start_time(s) {} */

    Loan(){}

    void add()
    {
        ofstream file;
        file.open("loan.csv",ios::app);
        
        string c=",", b=".", d=":";
        
        cout<<"*****************************\n";
        cout<<"Enter your national code: ";
        getline(cin,national_code);
        
        srand(time(NULL));
        loan_code=rand();
        
        cout<<"Enter the loan amount you want: ";
        cin>>amount;

        start_year = time(nullptr);
        tm* local_time1 = localtime(&start_year);
        start_year=1900 + local_time1->tm_year;

        start_month = time(nullptr);
        tm* local_time2 = localtime(&start_month);
        start_month=local_time2->tm_mon+1;

        start_day = time(nullptr);
        tm* local_time3 = localtime(&start_day);
        start_day=local_time3->tm_mday;

        return_amount=amount*1.2;

        file<<national_code<<c<<loan_code<<c<<amount<<c<<return_amount<<c<<start_year<<b<<start_month<<b<<start_day<<endl;

        file.close();  
        cout<<"*****************************\n";
        cout<<"Your request has been registered."<<endl;   
        cout<<"*****************************\n"; 
    }

};

int main()
{
    Loan a;
    a.add();



}