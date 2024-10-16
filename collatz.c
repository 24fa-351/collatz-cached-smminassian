#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "collatz.h"

unsigned long long cacheIndex = 0;
unsigned long long count = 0;
unsigned long long lruCount = 0;
unsigned long long mruCount = (cacheSize - 1);
unsigned long long cacheHit = 0;
unsigned long long cacheMiss = 0;

// myStruct *LRU(unsigned long long RN, unsigned long long steps, myStruct *cache)
// {
//     if(lruCount < cacheSize){
//     cache[lruCount].rN = RN;
//     cache[lruCount].steps = steps;
//     cache[lruCount].Count = lruCount;
//     lruCount++;
//     }
//     return cache;
// }

myStruct* MRU(unsigned long long RN, unsigned long long steps, myStruct* cache){

    if(mruCount < cacheSize){

    
    cache[mruCount].rN = RN;
    cache[mruCount].steps = steps;
    cache[mruCount].Count = mruCount;
    mruCount--;

    return cache;
}
}

myStruct *input(unsigned long long RN, unsigned long long steps, myStruct *cache)
{

    if (cacheIndex < cacheSize)
    {

        cache[cacheIndex].rN = RN;
        cache[cacheIndex].steps = steps;
        cache[cacheIndex].Count = count;
        cacheIndex++;
        count++;
    }
    else if (cacheIndex >= cacheSize)
    {
        // cache = LRU(RN, steps, cache);
        cache = MRU(RN, steps, cache);
    }

    return cache;
}

unsigned long long collatz(unsigned long long RN, myStruct *cache)
{
    unsigned long long steps = 0;

    unsigned long long originalRN = RN;

    if(cacheSize > 0){
        for (int i = 0; i < cacheIndex; i++)
    {
        if (cache[i].rN == RN)
        {
           steps = -1;
           return steps;
        }
    }
    }

    while (RN != 1)
    {

        if (RN % 2 == 0)
        {
            RN = RN / 2;
            steps++;
        }
        else if (RN % 2 != 0)
        {
            RN = (3 * RN) + 1;
            steps++;
        }
    }
    printf("%llu\n", originalRN);
    return steps;
}

myStruct *collatz_wrapper(unsigned long long N, unsigned long long Min, unsigned long long Max, myStruct *cache)
{
    unsigned long long steps = 0;
    unsigned long long RN = 0;

    for (unsigned long long ix = 0; ix < N; ix++)
    {
        RN = rand() % (Max - Min + 1) + Min;

        steps = collatz(RN, cache);
        if (steps == -1)
        {
            cacheHit++;
        }
        else
        {
            cacheMiss++;
            cache = input(RN, steps, cache);
        }
    }
    return cache;
}

int main(int __argc, char *__argv[])
{
    unsigned long long N = 0;
    unsigned long long Min = 0;
    unsigned long long Max = 0;
    double cacheHitPercent = 0;

    clock_t start;
    clock_t end;
    double timeTaken;

    myStruct *cache = (myStruct *)malloc(sizeof(myStruct) * cacheSize);
    if (__argc == 4)
    {
        N = atoi(__argv[1]);
        Min = atoi(__argv[2]);
        Max = atoi(__argv[3]);
    }
    start = clock();
    cache = collatz_wrapper(N, Min, Max, cache);
    end = clock();
    timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    //printf("%llu\n ", originalRN);
    //printf("%llu\n", steps);
    cacheHitPercent = ((double)cacheHit / (cacheHit + (double)cacheMiss)) * 1000; 

    for (unsigned long long i = 0; i < cacheSize; i++)
    {
        printf("%llu , %llu, %llu, %2.0f percent \n", cache[i].rN, cache[i].steps, cache[i].Count, cacheHitPercent);
    }
    printf("%4.100f seconds\n",timeTaken);
    free(cache);
    return 0;
}
