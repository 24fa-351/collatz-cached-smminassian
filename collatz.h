#ifndef COLLATZ_H
#define COLLATZ_H

typedef struct
{
    unsigned long long rN;
    unsigned long long steps;
    unsigned long long Count;
} myStruct;



myStruct* MRU(unsigned long long RN, unsigned long long steps, myStruct* cache, unsigned long long mruCount);
myStruct* LRU(unsigned long long RN, unsigned long long steps, myStruct* cache, unsigned long long cacheSize);


myStruct* input(unsigned long long RN, unsigned long long steps, myStruct *cache, unsigned long long cacheSize, unsigned long long mruCount, char* modeChecker);
unsigned long long collatz(unsigned long long RN, myStruct *cache, unsigned long long cacheSize);
myStruct* collatz_wrapper(unsigned long long N, unsigned long long Min, unsigned long long Max, myStruct* cache, unsigned long long mruCount, unsigned long long cacheSize, char* modeChecker);

#endif