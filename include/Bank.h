#ifndef BANK_H
#define BANK_H
#include <queue>
using namespace std;
class CustomizeCustomer
{
public:
    bool operator()( Customer& c1,  Customer& c2)
    {
        if (c1.GetArrivalTime() != c2.GetArrivalTime())
        {
            return c1.GetArrivalTime() > c2.GetArrivalTime();
        }
        return c2.GetIsVip();

    }
};

class Bank
{
private:
    priority_queue<Customer, vector<Customer>, CustomizeCustomer> CustomersQueue;
    vector<Teller> tellers;
    int NumOfTellers = 2;
    int NumOfCustomers = 7;

public:
    Bank() {}

    bool addCustomers(Customer c)
    {
        CustomersQueue.push(c);
        return true;
    }

    void displayCustomer()
    {


        fillTellerList();

        if(NumOfCustomers == NumOfTellers * 2 || NumOfCustomers > NumOfTellers * 2)
             {
                 NumOfTellers++;
                 addTeller();
             }

        system("cls");
        cout<<endl;
        cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"\tCustomer\tArrival Time\tService Time\tWaiting Time\tLeaving Time\t  IsVip\t"<<endl;
        cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
        int sumWaitTime = 0;
        int numOfCustomers = CustomersQueue.size();

        while(!CustomersQueue.empty())
        {
            Teller *teller;
            bool isTellerAva = IsTellerAvailable(&teller);//true case ther is an empty teller and return it
            int LastLeavetime;
            Customer customer = CustomersQueue.top();

            bool RegularCustomer = false;
            if(!isTellerAva)
            {
                customer = Rearrange(LastLeavetime, RegularCustomer);
            }
            teller->MaxService += customer.GetServiceTime();
            // false return the min leaving customer
            if(isTellerAva || teller->GetLeavingTime() <= customer.GetArrivalTime())
            {
                customer.SetWaitingTime(0);
                customer.SetLeavingTime( customer.GetArrivalTime() + customer.GetServiceTime() );
                LastLeavetime = customer.GetLeavingTime();
                teller->SetLeavingTime( customer.GetLeavingTime());
                teller->SetState(Busy);
                if(isTellerAva)
                {
                    CustomersQueue.pop();
                }
            }
            else
            {
                customer.SetWaitingTime( (teller->GetLeavingTime()) - customer.GetArrivalTime() );
                customer.SetLeavingTime( customer.GetArrivalTime() + customer.GetServiceTime() + customer.GetWaitingTime() );
                LastLeavetime = customer.GetLeavingTime();
                teller->SetLeavingTime(customer.GetLeavingTime());
                sumWaitTime+=customer.GetWaitingTime();
                if(RegularCustomer)
                {
                    CustomersQueue.pop();
                }
            }
            string vip = customer.GetIsVip() ? "  Vip Customer" : "Regular Customer" ;
            cout<<"\t"<<customer.GetID()<<"\t \t"<<customer.GetArrivalTime()<<"\t \t"<<customer.GetServiceTime()<<"\t \t"<<customer.GetWaitingTime()<<"\t \t"<<customer.GetLeavingTime()<<"\t \t"<<vip<<"\t \t"<<endl;
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;


        }
        int f;
        cout<<"\n\n\n";
        cout<<"\t\t\t\tAverage Waiting Time For customers = "<<sumWaitTime/numOfCustomers<<endl<<endl;

        for(int i = 0; i < NumOfTellers; i++)
        {
            cout<<"\t\t\tTeller Number "<<i+1<<" Servied customers for = "<<tellers[i].MaxService<<" Time Unit"<<endl;
        }
        cin>>f;
    }
protected:

private:

    void addTeller()
    {
        Teller t;
        t.SetState(Available);
        tellers.push_back(t);

    }

    void fillTellerList()
    {
        for(int i = 0; i < NumOfTellers ; i++)
        {
            addTeller();
        }
    }

    bool IsTellerAvailable(Teller ** teller)
    {

        bool flag = 0;
        Teller * minTeller = nullptr;

        if (!tellers.empty())
        {
            minTeller = &(tellers[0]);
        }

        for(int i = 0; i < NumOfTellers; i++ )
        {
            if(tellers[i].GetState() == Available)//case there is an empty teller
            {
                flag = 1;
                *teller = &(tellers[i]);
                return flag;
            }

            if(tellers[i].GetLeavingTime() < minTeller->GetLeavingTime()) //if there is not an empty teller then see the min leaving time teller
            {
                minTeller = &(tellers[i]);
            }
        }

        *teller = minTeller;
        return flag;

    }


    Customer Rearrange(int LastLeavetime, bool & RegularCustomer)
    {
        Customer c = CustomersQueue.top();
        priority_queue<Customer, vector<Customer>, CustomizeCustomer> RearrangeQueue;

        while(LastLeavetime > c.GetArrivalTime() && !CustomersQueue.empty())
        {
            if(!c.GetIsVip())
            {
                RearrangeQueue.push(c);
                CustomersQueue.pop(); //R
                c = CustomersQueue.top();
            }
            else
            {
                CustomersQueue.pop();//remove vip
                while(!RearrangeQueue.empty())
                {
                    Customer d = RearrangeQueue.top();
                    CustomersQueue.push(d);
                    RearrangeQueue.pop();
                }

                return c;
            }
        }
        RegularCustomer = true;

        while(!RearrangeQueue.empty())
        {
            Customer d = RearrangeQueue.top();
            CustomersQueue.push(d);
            RearrangeQueue.pop();
        }
        c = CustomersQueue.top();
        return c;

    }

};

#endif // BANK_H
