#include "BucketSort.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

bool aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow) {
    if (x == y) return false; // if the two numbers are the same then one is not less than the other
    unsigned int a = x;
    unsigned int b = y;
    // work out the digit we are currently comparing on.
    if (pow == 0) {
        while (a / 10 > 0) {
            a = a / 10;
        }
        while (b / 10 > 0) {
            b = b / 10;
        }
    }
    else {
        while (a / 10 >= (unsigned int) std::round(std::pow(10,pow))) {
            a = a / 10;
        }
        while (b / 10 >= (unsigned int) std::round(std::pow(10,pow))) {
            b = b / 10;
        }
    }
    if (a == b) return aLessB(x,y,pow + 1);  // recurse if this digit is the same
    else return a < b;
}

// TODO: replace this with a parallel version.
void BucketSort::sort(unsigned int numCores) {
    unsigned long length = numbersToSort.size();
    //if the vector is empty
    if (numbersToSort.empty()) {
        return;
    }

    //if we only have one processor
    if (numCores == 1) {
        std::sort(numbersToSort.begin(),numbersToSort.end(), [](const unsigned int& x, const unsigned int& y){
            return aLessB(x,y,0);
        } );
        return;
    }

    //create start and stop sign for each thread
    unsigned long start[numCores];
    unsigned long stop[numCores];
    unsigned long offset = length/numCores;
    //create reference for lambda functions
    std::vector<unsigned int> &numbers = numbersToSort;
    //get the start and stop sign
    for (unsigned int i = 0; i < numCores; ++i) {
        start[i] = i * offset;
        stop[i] = (i + 1)*offset;
    }
    stop[numCores - 1] = length;

    //create bucket
    std::vector<unsigned int> b{};
    std::vector<std::vector<unsigned int>> resultBucket(9, b);
    std::vector<std::vector<std::vector<unsigned int>>> bucket(numCores, resultBucket);

    //create thread vector
    std::vector<std::thread> threads;

    //create mutex array
    std::mutex bucketMutex[9];

    //create lambda function for divide
    auto divideLambda = ([&] (const unsigned int i) {
        for (unsigned long j = start[i]; j < stop[i]; ++j) {
            //get the number
            unsigned int number = numbers[j];
            unsigned int digit = number;
            //get the first digit
            while (digit / 10 > 0) {
                digit = digit / 10;
            }
            //push back to vector
            bucket[i][digit - 1].push_back(number);
        }
    });

    for (unsigned int i = 0; i < numCores - 1; ++i) {
        threads.push_back(std::thread(divideLambda, i));
    }

    //for main thread
    divideLambda(numCores - 1);
    
    //wait until all threads terminate
    for (unsigned int i = 0; i < numCores - 1; ++i) {
        threads[i].join();
    }
    threads.clear();

    //merge bucket
    auto mergeLambda = ([&] () {
        for (unsigned int i = 0; i < 9; ++i) {
            if (!bucketMutex[i].try_lock()) {
                continue;
            }
            for (unsigned int j = 0; j < numCores; ++j) {
                resultBucket[i].insert(resultBucket[i].end(), bucket[j][i].begin(), bucket[j][i].end());
            }
        }

    });

    for (unsigned int i = 0; i < numCores - 1; ++i) {
        threads.push_back(std::thread(mergeLambda));
    }
    mergeLambda();

    //wait until all threads terminate
    for (unsigned int i = 0; i < numCores - 1; ++i) {
        threads[i].join();
    }
    threads.clear();

    //unlock all mutexs
    for (unsigned int i = 0; i < 9; ++i) {
        bucketMutex[i].unlock();
    }

    //sort each sub_result bucket
    auto sortLambda = ([&] () {
        for (unsigned int i = 0; i < 9; ++i) {
            if (! bucketMutex[i].try_lock()) {
                continue;
            }
            std::sort(resultBucket[i].begin(), resultBucket[i].end(), [](const unsigned int& x, const unsigned int& y){
                return aLessB(x,y,0);
            } );
        }

    });
    for (unsigned int i = 0; i < numCores - 1; ++i) {
        threads.push_back(std::thread(sortLambda));
    }

    //for main thread
    sortLambda();
    //wait until all threads terminate
    for (unsigned int i = 0; i < numCores - 1; ++i) {
        threads[i].join();
    }
    threads.clear();

    //unlock all mutexs
    for (unsigned int i = 0; i < 9; ++i) {
        bucketMutex[i].unlock();
    }

    //merge the final result
    numbersToSort.clear();

    for (unsigned int i = 0; i < 9; ++i) {
        numbersToSort.insert(numbersToSort.end(), resultBucket[i].begin(), resultBucket[i].end());
    }
    return;

}
