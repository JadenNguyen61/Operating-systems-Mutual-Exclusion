#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>
#include <cmath>
#include "Peterson.h"
#include "TT.h"

using namespace std;

double log2(double n){
  return log(n)/log(2);
}

TournamentTree::TournamentTree(int numProcesses) : numProcesses(numProcesses) {
        int depth = ceil(log2(numProcesses));
        int size = pow(2, depth + 1) - 1; // Full binary tree size
        locks.resize(size);

        // Initialize all nodes in the tree
        for (int i = 0; i < size; ++i) {
            locks[i] = new PetersonLock();
        }
    }

TournamentTree::~TournamentTree() {
        for (auto lock : locks) {
            delete lock;
        }
    }

void TournamentTree::lock(int processID) {
        int id = processID + locks.size() / 2; // Get the leaf position
        while (id > 0) {
            int parent = (id - 1) / 2;
            int is_right_child = id % 2;
            locks[parent]->lock(is_right_child);
            id = parent;
        }
    }

void TournamentTree::unlock(int processID) {
        int id = processID + locks.size() / 2; // Get the leaf position
        vector<int> ancestors;
        while (id > 0) {
            ancestors.push_back(id);
            id = (id - 1) / 2;
        }
        for (auto it = ancestors.rbegin(); it != ancestors.rend(); ++it) {
            int parent = (*it - 1) / 2;
            int is_right_child = *it % 2;
            locks[parent]->unlock(is_right_child);
        }
    }

