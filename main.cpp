#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>
#include <cmath>
#include "Peterson.h"
#include "TT.h"
#include "TAS.h"
#include "FAI.h"


using namespace std;
atomic<int> sharedVariable(0);
TASLock TASlock;
TicketLock FAIlock;

//Tournament Tree thread function
void TTthreadFunction(TournamentTree& tree, int processID) {
    //Lock Threads
    cout << "Thread " << processID << " locked\n";
    tree.lock(processID);
    
    
    // Critical section
    int TTlocalCopy = sharedVariable.load();
    cout << "Thread " << processID << " enters critical section with shared variable = " << TTlocalCopy << ".\n";
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    sharedVariable.store(TTlocalCopy + 1);
    cout << "Thread " << processID << " exits critical section with shared variable = " << sharedVariable.load() << ".\n";
    
    //Unlock threads
    tree.unlock(processID);
    cout << "Thread " << processID << " Unlocked.\n";
}

//Test and set thread function
void TASthreadFunction(int processID) {
    //Lock Threads
    cout << "Thread " << processID << " locked\n";
    TASlock.lock();
    
    
    // Critical section begins
    int TASlocalCopy = sharedVariable.load();
    cout << "Thread " << processID << " enters critical section with shared variable = " << TASlocalCopy << ".\n";
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    sharedVariable.store(TASlocalCopy + 1);
    cout << "Thread " << processID << " exits critical section with shared variable = " << sharedVariable.load() << ".\n";
    
    //Unlock threads
    TASlock.unlock();
    cout << "Thread " << processID << " Unlocked.\n";
}

//Fetch and Increment
void FAIthreadFunction(int processID) {
    //Lock Threads
    cout << "Thread " << processID << " locked\n";
    FAIlock.lock();
    
    
    // Critical section begins
    int FAIlocalCopy = sharedVariable.load();
    cout << "Thread " << processID << " enters critical section with shared variable = " << FAIlocalCopy << ".\n";
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulating work
    sharedVariable.store(FAIlocalCopy + 1);
    cout << "Thread " << processID << " exits critical section with shared variable = " << sharedVariable.load() << ".\n";
    
    //Unlock threads
    FAIlock.unlock();
    cout << "Thread " << processID << " Unlocked.\n";
}

int main(int argc, char *argv[]) {
    //Argument inputs
    int typeAlgo = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    
    //Thread variables
    TournamentTree tree(numThreads);
    vector<thread> TTthreads(numThreads);
    vector<thread> TASthreads;
    vector<thread> FAIthreads;

    switch(typeAlgo) {
    //Tournament Tree case 
    case 0: 
        cout << "Tournament Tree based algorithm starting\n";
        //Creation of threads using Tournament Tree
        for (int i = 0; i < numThreads; ++i) {
            TTthreads[i] = thread(TTthreadFunction, ref(tree), i);
        }
        
        //Join threads
        for (auto& t : TTthreads) {
            t.join(); // Ensure all threads finish before exiting main
        }
        
        cout << "Final value of sharedVariable: " << sharedVariable.load() << endl;
        break;
        
    //Test and set case
    case 1:
    cout << "Test and set based algorithm starting\n";
    //Creation of threads using Test and set
        for (int i = 0; i < numThreads; ++i) {
            TASthreads.push_back(thread(TASthreadFunction, i));
        }
        
        //Join threads
        for (auto& t : TASthreads) {
            t.join();
        }
        cout << "Final value of sharedVariable: " << sharedVariable.load() << endl;
        break;
    //Fetch and Increment case
    case 2:
    cout << "Fetch and Increment based algorithm starting\n";
    //Creation of threads using Fetch and Increment
        for (int i = 0; i < numThreads; ++i) {
            FAIthreads.push_back(thread(FAIthreadFunction, i));
        }
        //Join threads
        for (auto& t : FAIthreads) {
            t.join();
        }

        cout << "Final value of sharedVariable: " << sharedVariable.load() << endl;
        break;

    }
    return 0;
}