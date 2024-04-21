#pragma once
#ifndef FAI
#define FAI

#include <atomic>
using namespace std;

class TicketLock {
private:
    atomic<int> ticket{ 0 };
    atomic<int> serving{ 0 };

public:
    void lock() {
        int myTicket = ticket.fetch_add(1, memory_order_relaxed);
        while (serving.load(memory_order_acquire) != myTicket) {
        }
    }

    void unlock() {
        serving.fetch_add(1, memory_order_release);
    }
};

#endif 