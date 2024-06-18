#ifndef TELLER_H
#define TELLER_H

enum State
{
    Available,
    Busy,
};
class Teller
{
private:
    int LeavingTime;
    State state;

public:
    int MaxService = 0;

    Teller() {}


    void SetLeavingTime(int leavingTime)
    {
        LeavingTime = leavingTime;
    }

    int GetLeavingTime()
    {
        return LeavingTime;
    }

    void SetState(State s)
    {
        state = s;
    }

    State GetState()
    {
        return state;
    }

protected:


};

#endif
