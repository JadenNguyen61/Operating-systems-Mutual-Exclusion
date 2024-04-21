#pragma once
#ifndef TAS
#define TAS

#include <atomic>
using namespace std;

class TASLock {
private:
    atomic<bool> lockFlag;

public:
    TASLock() : lockFlag(false) {}

    void lock() {
        bool expected = false;
        // Spin until the lock is acquired
        while (!lockFlag.compare_exchange_strong(expected, true, memory_order_acquire)) {
            expected = false; 
        }
    }

    void unlock() {
        lockFlag.store(false, memory_order_release);
    }
};

#endif
