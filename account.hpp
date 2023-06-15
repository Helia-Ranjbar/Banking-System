#ifndef Account_h
#define Account_h
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>


using namespace std;



long long  strhashing(string h1)
{
    hash<string> hash_obj;
    return hash_obj(h1);
}


class Account
{
protected:
    long long number,balance;
    string national_code, account_type;
    time_t expire_year, expire_month;
    long pin;
    int cvv2;
    vector <long long> v_number;
    vector <int> v_expire_year;
    vector <int> v_expire_month;
    vector <int> v_cvv2;
    vector <long> v_pin;
    vector <long long> v_balance;



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
        v_number.push_back(number);

        cout<<"Enter your acoount type: 1:current account 2:short term account 3:long term account"<<endl;
        getline(cin,account_type);
        account_type= account_type+',';


        expire_year= time(nullptr);
        tm* local_time = localtime(&expire_year);
        expire_year=local_time->tm_year+1900 +5;
        v_expire_year.push_back(expire_year);

        expire_month= time(nullptr);
        tm* local_time1 = localtime(&expire_month);
        expire_month=local_time1->tm_mon+1;
        v_expire_month.push_back(expire_month);

        srand(time(NULL));
        pin=rand()/10;
        string pin1=to_string(pin);
        pin1=strhashing(pin1);
        v_pin.push_back(pin);

        srand(time(NULL));
        cvv2=rand();
        v_cvv2.push_back(cvv2);

        cout<<"Enter your balance: ";
        cin>>balance;
        v_balance.push_back(balance);

        string c=",";
        file<<national_code<<number<<c<<account_type<<expire_year<<c<<expire_month<<c<<cvv2<<c<<pin1<<c<<balance<<endl;

        cout<<"your card number:"<<number<<'\n'<<"exp year:"<<expire_year<<'\n'<<"exp month:"<<expire_month<<'\n'<<"cvv2: "<<cvv2<<'\n'<<"pin:"<<pin<<endl;

        file.close();
    }
};
#endif


