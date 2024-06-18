#ifndef CUSTOMER_H
#define CUSTOMER_H


class Customer
{

private:

    int ID;
    int ArrivalTime;
    int ServiceTime;
    int WaitingTime;
    int LeavingTime;
    bool IsVip;

public:

    Customer(int id, int arrivalTime, int serviceTime, bool isVip)
    {
        ID = id;
        ArrivalTime = arrivalTime;
        ServiceTime = serviceTime;
        IsVip = isVip;
        LeavingTime = INT_MAX;
    }

    int GetID()
    {
        return ID;
    }

    int GetArrivalTime()
    {
        return ArrivalTime;
    }

    int GetServiceTime()
    {
        return ServiceTime;
    }

    void SetWaitingTime(int waitingTime)
    {
        WaitingTime = waitingTime;
    }

    int GetWaitingTime()
    {
        return WaitingTime;
    }

    void SetLeavingTime(int leavingTime)
    {
        LeavingTime = leavingTime;
    }

    int GetLeavingTime()
    {
        return LeavingTime;
    }

    bool GetIsVip()
    {
        return IsVip;
    }
protected:

};

#endif
