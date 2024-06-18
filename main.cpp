#include <iostream>
#include"Teller.h"
#include"Customer.h"
#include"Bank.h"
#include <iostream>
#include <fstream>
#include <string>
#include<queue>
using namespace std;

int main()
{
    fstream CustomerData("CustomerData.txt");
    Bank bank;

    if(CustomerData.is_open())
    {
        int id ;
        int arrivalTime;
        int serviceTime;
        bool isVip;
        while(CustomerData >> id >> arrivalTime >> serviceTime >> isVip)
        {
            Customer customer(id , arrivalTime , serviceTime , isVip);
            bank.addCustomers(customer);
        }
        CustomerData.close();
    }
    else
    {
        cout<<"can't open file";
        return 1;
    }

    bank.displayCustomer();

    return 0;
}
