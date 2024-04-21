#pragma once
#ifndef Peterson
#define Peterson

#include <atomic>
#include <iostream>

using namespace std;

class PetersonLock {
private:
    atomic<bool> flag[2];
    atomic<int> turn;
    bool isReal;

public:
    PetersonLock(bool initially_locked = false);
    void lock(int threadID);
    void unlock(int threadID);
    void set_real(bool real);


};

#endif 
