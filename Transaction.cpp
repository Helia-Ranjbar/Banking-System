#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <stdio.h>


using namespace std;

//convert pin number to hash for saving into the file.
unsigned int Hash(string & data)
{
    unsigned int result(0);

    for(unsigned int ch: data)
        result = ch + (result<<4) + (result<<10) - result;

    return result;
}

class Transaction
{
    string sender_account, reciever_account, cvv2, expire_month , expire_year, pin, account_number , national_code ;
    double transaction_code;
    time_t transaction_day, transaction_month, transaction_year, transaction_hour, transaction_min, transaction_sec ;
    unsigned int amount;
    bool is_reciever , is_successful , not_enough_balance = false ;

public:
    
    Transaction(){}

    void do_tranaction(string fileName)
    {
        string c=",",  b=".", d=":";
        string line;
        
        ifstream read_sender_account(fileName);
        ifstream read_reciever_account(fileName);

        ofstream file;
        file.open("transaction.csv", ios::app);

        cout<<"*****************************\n";

        cout<<"Enter your card number: ";
        cin>>sender_account;

        cout<<"Enter a reciever number: ";
        cin>>reciever_account;

        while (read_reciever_account>>line) 
        {
            stringstream ss(line);
            string national_code, card_number;
            getline(ss,national_code , ',');
            getline(ss, card_number, ',');
            if(card_number==reciever_account)
                is_reciever=true;
        }

        cout<<"Enter cvv2: ";
        cin>>cvv2;

        cout<<"Enter expire year: ";
        cin>>expire_year;
        
        cout<<"Enter expire month: ";
        cin>>expire_month;
        
        cout<<"Enter pin number: ";
        cin>>pin;
        unsigned int enter_pin=Hash(pin);

        int n=0;
        while (read_sender_account>>line) 
        {
            stringstream ss(line);
            string national_code, card_number, account_type, exp_year, exp_month, cvv2, pin, balance;
            
            getline(ss,national_code , ',');
            getline(ss, card_number, ',');
            getline(ss, account_type, ',');
            getline(ss, exp_year, ',');
            getline(ss, exp_month, ',');
            getline(ss, cvv2, ',');
            getline(ss, pin, ',');
            getline(ss, balance, ',');

            unsigned int int_balance;
            istringstream(balance)>>int_balance;

            unsigned int  pin2;
            istringstream(pin)>>pin2;

            
            
            /*cout<<card_number<<endl;
            cout<<sender_account<<endl;
            if(sender_account==card_number)
            {
                cout<<"yes";
            }*/

            if (sender_account==card_number && exp_year==expire_year && exp_month==expire_month &&  is_reciever==true ) 
            {
                cout<<"Enter amount: ";
                cin>>amount;

                cout<<"*****************************\n";

                if(amount>int_balance)
                {
                    cout<<"The account balance is insufficient!"<<endl;
                    cout<<"*****************************\n";

                    not_enough_balance=true;

                }
                else
                {
                    cout<<"Successful."<<endl;

                    int_balance=int_balance-amount;
                    cout<<"your balance: "<<int_balance<<endl;
                    cout<<"*****************************\n";

                    int m=0;
                    ofstream outputFile("temp1.csv",ios::app);
                    ifstream inputFile("account.csv");

                    string line2,read_national_code;

                    read_sender_account.close();

                    while(inputFile>>line2)
                    {
                        
                        string read_national_code,card_number,account_type,exp_year,exp_month,cvv2,pin,balance;
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
                            getline(ss, balance, ',');

                            outputFile<<read_national_code<<c<<card_number<<c<<account_type<<c
                            <<exp_year<<c<<exp_month<<c<<cvv2<<c<<pin<<c<<balance<<endl;

                            
                        }
                        else
                        {
                            stringstream ss(line2);

                            getline(ss, read_national_code , ',');
                            getline(ss, card_number, ',');
                            getline(ss, account_type, ',');
                            getline(ss, exp_year, ',');
                            getline(ss, exp_month, ',');
                            getline(ss, cvv2, ',');
                            getline(ss, pin, ',');
                            getline(ss, balance, ',');

                            string now_balance = to_string(int_balance);
                            
                            outputFile<<read_national_code<<c<<card_number<<c<<account_type<<c
                            <<exp_year<<c<<exp_month<<c<<cvv2<<c<<pin<<c<<now_balance<<endl;

                        }
                        m++;

                    }

                    

                    outputFile.close();
                    inputFile.close();

                    // Delete the original file
                    remove("account.csv");
                    
                    // Rename the temporary file to the original file name
                    rename("temp1.csv", "account.csv");
                    

                    

                    is_successful = true;

                    transaction_year = time(nullptr);
                    tm* local_time1 = localtime(&transaction_year);
                    transaction_year=1900 + local_time1->tm_year;

                    transaction_month = time(nullptr);
                    tm* local_time2 = localtime(&transaction_month);
                    transaction_month=local_time2->tm_mon+1;

                    transaction_day = time(nullptr);
                    tm* local_time3 = localtime(&transaction_day);
                    transaction_day=local_time3->tm_mday;

                    transaction_hour = time(nullptr);
                    tm* local_time4 = localtime(&transaction_hour);
                    transaction_hour=1 + local_time4->tm_hour;

                    transaction_min = time(nullptr);
                    tm* local_time5 = localtime(&transaction_min);
                    transaction_min=1 + local_time5->tm_min;

                    transaction_sec = time(nullptr);
                    tm* local_time6 = localtime(&transaction_sec);
                    transaction_sec= 1 + local_time6->tm_sec ;

                    srand(time(NULL));
                    transaction_code=rand();
                    string transaction_code2= to_string(transaction_code);

                    file<<sender_account<<c<<reciever_account<<c<<amount<<c<<transaction_year<<b<<transaction_month<<b<<transaction_day<<c<<transaction_hour<<d<<transaction_min<<d<<transaction_sec<<c<<transaction_code2<<endl;
                    
                }
            }
            n++;
          
        }

        if(is_successful==false && not_enough_balance==false)
        {
            cout<<"*****************************\n";
            cout<<"The information is wrong!"<<endl;
            cout<<"*****************************\n";
        }    

        file.close();
        
       
    }
    
    void view_transaction()
    {
        cout<<"*****************************\n";
        cout<<"Enter your national code: ";
        cin>>national_code;

        cout<<"Enter your account number: ";
        cin>>account_number;

        ifstream accountFile("account.csv");

        string line;

        while(accountFile>>line)
        {
            stringstream ss(line);
            string is_national_code, is_card_number;
            
            getline(ss,is_national_code , ',');
            getline(ss, is_card_number, ',');

            if(national_code==is_national_code && account_number==is_card_number )
            {
                    ifstream transactionFile("transaction.csv");
                    string line2;

                    while(transactionFile>>line2)
                    {
                        
                        stringstream ss(line2);
                        string is_sender_number, reciever_number, amount, code, date, time;
                        getline(ss, is_sender_number, ',');
                        getline(ss, reciever_number, ',');
                        getline(ss, amount, ',');
                        getline(ss, date, ',');
                        getline(ss, time, ',');
                        getline(ss,code);

                        

                        if(is_sender_number==account_number)
                        {
                            cout<<"*****************************\n"<<"sender account: "<<is_sender_number<<'\n'<<"reciever account: "<< reciever_number<<'\n'<<"amount: "<<amount<<'\n'
                            <<"date: "<<date<<'\n'<<"time: "<<time<<'\n'<<"code: "<<code<<'\n'<<"*****************************\n";
                        }
                    }
            }


        }
        
    }



};

int main()
{
    Transaction a;
    a.do_tranaction("account.csv");
    //a.view_transaction();
}