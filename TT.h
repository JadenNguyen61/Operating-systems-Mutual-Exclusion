#pragma once
#ifndef TT
#define TT

#include "Peterson.h"
#include <vector>
using namespace std;

class TournamentTree {
private:
    int numProcesses;
    vector<PetersonLock*> locks;

public:
    TournamentTree(int numProcesses);
    ~TournamentTree();
    void lock(int processID);
    void unlock(int processID);


};

#endif 

