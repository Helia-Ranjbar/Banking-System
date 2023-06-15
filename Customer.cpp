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
    time_t date_of_membership;

public:

    //create and delete an account is written in Account class.
    //do transaction is written in Transaction class.
    //request loan is written in Loan class.


};