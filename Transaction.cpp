#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>


using namespace std;

unsigned int Hash(string & data)
{
    unsigned int result(0);

    for(unsigned int ch: data)
        result = ch + (result<<4) + (result<<10) - result;

    return result;
}

class Transaction
{
    string sender_account, reciever_account ;
    double transaction_code;
    string cvv2;
    string expire_month , expire_year ;
    time_t transaction_time ;
    string pin;
    string amount;
    bool is_reciever , is_successful= true, not_enough_balance = false ;

public:
    
    Transaction(){}

    void do_tranaction(string fileName)
    {
        string c=",";
        string line;
        
        ifstream read_sender_account(fileName);
        ifstream read_reciever_account(fileName);

        
        ofstream file;
        file.open("transaction.csv", ios::app);

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

            cout<<balance<<endl;

            unsigned int  pin2;
            istringstream(pin)>>pin2;

            getline(ss, balance, ',');

            if (sender_account==card_number) 
            {

               if(exp_year==expire_year)
               {

                    if(exp_month==expire_month)
                    {

                        if(enter_pin==pin2)
                        {
   
                            if(is_reciever==true)
                            {

                                cout<<"Enter amount: ";
                                cin>>amount;
                                if(amount>balance)
                                {
                                    cout<<"The account balance is insufficient!";
                                    not_enough_balance=true;

                                }
                                else
                                {
                                    cout<<"Successful.";
                                    is_successful = true;
                                    transaction_time = time(0);
                                    char* dt = ctime(&transaction_time);

                                    srand(time(NULL));
                                    transaction_code=rand();
                                    file<<sender_account<<c<<reciever_account<<c<<amount<<c<<transaction_code<<c<<dt;
                                }
                            }
                        }

                    }
               }
            }
        }

        if(is_successful==false && not_enough_balance==false)
        {
            cout<<"The information is wrong!";
        }    
    }
};

int main()
{
    Transaction a;
    a.do_tranaction("account.csv");
}