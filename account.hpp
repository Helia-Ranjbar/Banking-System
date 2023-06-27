#ifndef Account_h
#define Account_h
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include "transaction.hpp"

using namespace std;



class Account
{

protected:
    long long balance, number;
    string national_code, account_type, delete_number;
    time_t expire_year, expire_month;
    unsigned int pin;
    int cvv2;
    bool is_national_code, is_card_number = false;

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

        cout<<"Enter your acoount type: 1:current account 2:short term account 3:long term account : ";
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


    void delete_account()
    {
        cout<<"Enter your national code: ";
        cin>>national_code;

        cout<<"Enter the card number want to delete: ";
        cin>>delete_number;
        
        ifstream myfile("account.csv");
        
        string line,line2;

        int n=0;

        while (myfile>>line) 
        {
            stringstream ss(line);
            string read_national_code, card_number, account_type, exp_year, exp_month, cvv2, pin, balance;
            
            getline(ss,read_national_code , ',');
            getline(ss, card_number, ',');
            getline(ss, account_type, ',');
            getline(ss, exp_year, ',');
            getline(ss, exp_month, ',');
            getline(ss, cvv2, ',');
            getline(ss, pin, ',');
            getline(ss, balance);

            
           if(national_code==read_national_code)
            {
                is_national_code= true;
                if(delete_number==card_number)
                {
                    int m=0;
                    ofstream outputFile("temp.csv",ios::app);
                    ifstream inputFile("account.csv");
                    string c=",";
                    
                    //outputFile<<"national code,number,type,exp year,exp month,cvv2,pin,balance"<<endl;
                    while(inputFile>>line2)
                    {
                        
                        if(m!=n)
                        {
                            stringstream ss(line2);

                            getline(ss, read_national_code , ',');
                            getline(ss, card_number, ',');
                            getline(ss, account_type, ',');
                            getline(ss, exp_year, ',');
                            getline(ss, exp_month, ',');
                            getline(ss, cvv2, ',');
                            getline(ss, pin, ',');
                            getline(ss, balance);

                            outputFile<<read_national_code<<c<<card_number<<c<<account_type<<c<<exp_year<<c<<exp_month<<c<<cvv2<<c<<pin<<c<<balance<<endl;
                        }
                        m++;

                    }
                    is_card_number= true;
                    
                    outputFile.close();
                    inputFile.close();
                    myfile.close();

                    // Delete the original file
                    remove("account.csv");
                    
                    // Rename the temporary file to the original file name
                    rename("temp.csv", "account.csv");

                    cout<<"delete successfully.";
                    
                    goto lbl_for;
                }
            }
            n++;
        }   
      
       lbl_for: if(is_national_code == false && is_card_number== false)
            cout<<"The information is wrong!";

    }
};


#endif


