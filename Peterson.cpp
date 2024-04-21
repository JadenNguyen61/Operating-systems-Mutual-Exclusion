#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>
#include "Peterson.h"

using namespace std;

PetersonLock::PetersonLock(bool initially_locked) : isReal(true) {
        flag[0].store(false);
        flag[1].store(false);
        turn.store(0);
    }

void PetersonLock::lock(int threadID) {
        int other = 1 - threadID;
        flag[threadID].store(true);
        turn.store(threadID);
        while (flag[other].load() && turn.load() == threadID);
        cout << "Thread " << threadID << " locks.\n";
    }

void PetersonLock::unlock(int threadID) {
        cout << "Thread " << threadID << " unlocks.\n";
        flag[threadID].store(false);
    }

void PetersonLock::set_real(bool real) {
    isReal = real;
}
