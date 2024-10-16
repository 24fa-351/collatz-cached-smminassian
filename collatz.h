#ifndef COLLATZ_H
#define COLLATZ_H

typedef struct
{
    unsigned long long rN;
    unsigned long long steps;
    unsigned long long Count;
} myStruct;


const unsigned long long cacheSize = 19000; //19,000 is the smallest cache that can get a cache hit rate of 30%

myStruct* MRU(unsigned long long RN, unsigned long long steps, myStruct* cache);
//myStruct* LRU(unsigned long long RN, unsigned long long steps, myStruct* cache);


myStruct* input(unsigned long long RN, unsigned long long steps, myStruct *cache);
unsigned long long collatz(unsigned long long RN, myStruct *cache);
myStruct* collatz_wrapper(unsigned long long N, unsigned long long Min, unsigned long long Max, myStruct* cache);

#endif