#ifndef transaction_h
#define transaction_h
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class Transaction: public Account
{
    long long sender_account, reciever_account , transaction_number;
    int cvv2;
    int expire_month , expire_year ;
    time_t transaction_time ;
    long pin;
    long long amount;
    bool is_sender, is_reciever, is_exp_mon, is_exp_year, is_cvv2, is_pin ;

public:

    Transaction(){}

    void do_tranaction()
    {
        string c=",";
        ofstream file;
        file.open("transaction.csv", ios::app);

        int r=0;
        
        cout<<"Enter your card number: ";
        cin>>sender_account;
        for(int i=0; i<v_number.size(); i++)
        {
            if(sender_account==v_number[i])
            {
                is_sender=true;
                r=i;
                
                break;
            }
        }

        cout<<"Enter a reciever number: ";
        cin>>reciever_account;
        for(int i=0; i<v_number.size(); i++)
        {
            if(reciever_account==v_number[i])
            {
                is_reciever=true;

                break;
            }
        }

        
        cout<<"Enter cvv2: ";
        cin>>cvv2;
            if(cvv2==v_cvv2[r])
            {   
                is_cvv2=true;
                
            }

        cout<<r;
        cout<<"Enter expire year: ";
        cin>>expire_year;
        
            if(expire_year==v_expire_year[r])
            {
                is_exp_year=true;
               
            }
        
        cout<<"Enter expire month: ";
        cin>>expire_month;
        
            if(expire_month==v_expire_month[r])
            {
                is_exp_mon=true;
                
            }
        
        cout<<"Enter pin number: ";
        cin>>pin;
        
            if(pin==v_pin[r])
            {
                is_pin=true;
                
            }
        

        if(is_sender==true && is_reciever==true && is_cvv2==true && is_pin==true && is_exp_mon==true && is_exp_year==true)
        {
            cin>>amount;
            if(amount<v_balance[r])
                cout<<"The account balance is insufficient!";
            else{
                cout<<"Successful.";
                transaction_time = time(0);
                char* dt = ctime(&transaction_time);

                srand(time(NULL));
                transaction_number=rand();
                file<<sender_account<<c<<reciever_account<<c<<amount<<c<<dt<<c<<transaction_number;
            }
        }
        else
            cout<<"The information is wrong!";
        
    }


};

#endif
