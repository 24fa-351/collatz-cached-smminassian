#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "collatz.h"

If you want to get the values that i got on my sheet, you need to run it in power shell.

// 11450 is the smallest cache that can get a cache hit rate of 30% for LRU
// 11450 is the smallest cache that can get a cache hit rate of 30% for MRU
unsigned long long cacheIndex = 0;
unsigned long long count = 0;
unsigned long long lruCount = 0;
unsigned long long cacheHit = 0;
unsigned long long cacheMiss = 0;

myStruct *LRU(unsigned long long RN, unsigned long long steps, myStruct *cache, unsigned long long cacheSize)
{
    if (lruCount < cacheSize)
    {
        cache[lruCount].rN = RN;
        cache[lruCount].steps = steps;
        cache[lruCount].Count = lruCount;
        lruCount++;
    }
    return cache;
}

myStruct *MRU(unsigned long long RN, unsigned long long steps, myStruct *cache, unsigned long long mruCount)
{

    cache[mruCount].rN = RN;
    cache[mruCount].steps = steps;
    cache[mruCount].Count = mruCount;
    return cache;
}

myStruct *input(unsigned long long RN, unsigned long long steps, myStruct *cache, unsigned long long cacheSize, unsigned long long mruCount, char* modeChecker)
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
        if(strcmp(modeChecker, "1") == 0){
            cache = LRU(RN, steps, cache, cacheSize);
        }
        else if(strcmp(modeChecker, "2") == 0){
            cache = MRU(RN, steps, cache, mruCount);
        }
    }

    return cache;
}
unsigned long long collatz(unsigned long long RN, myStruct *cache, unsigned long long cacheSize)
{
    unsigned long long steps = 0;

    unsigned long long originalRN = RN;

    if (RN == 0)
    {
        steps = 1;
        return steps;
    }

    if (cacheSize > 0)
    {
        for (int wx = 0; wx < cacheIndex; wx++)
        {
            if (cache[wx].rN == RN)
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
    // printf("%llu\n", originalRN);
    return steps;
}

myStruct *collatz_wrapper(unsigned long long N, unsigned long long Min, unsigned long long Max, myStruct *cache, unsigned long long mruCount, unsigned long long cacheSize, char* modeChecker)
{
    unsigned long long steps = 0;
    unsigned long long RN = 0;
    mruCount--;

    for (unsigned long long ix = 0; ix <= N; ix++)
    {

        RN = rand() % (Max - Min + 1) + Min;

        steps = collatz(RN, cache, cacheSize);
        if (steps != -1)
        {
            cacheMiss++;
            cache = input(RN, steps, cache, cacheSize, mruCount, modeChecker);
        }
        else
        {
            cacheHit++;
        }
    }
    return cache;
}

int main(int argc, char *argv[])
{
    unsigned long long N = 0;
    unsigned long long Min = 0;
    unsigned long long Max = 0;
    double cacheHitPercent = 0;
    unsigned long long cacheSize = 0;
    unsigned long long mruCount = 0;
    char modeChecker[2];
    

    clock_t start;
    clock_t end;
    double timeTaken;

    if (argc == 6)
    {
        cacheSize = atoi(argv[1]);
        N = atoi(argv[2]);
        Min = atoi(argv[3]);
        Max = atoi(argv[4]);
        strcpy(modeChecker, argv[5]);
    }

    if (N == cacheSize)
    {
        N++;
    }

    myStruct *cache = (myStruct *)malloc(sizeof(myStruct) * cacheSize);

    mruCount = cacheSize - 1;

    start = clock();
    cache = collatz_wrapper(N, Min, Max, cache, mruCount, cacheSize, modeChecker);
    end = clock();
    timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    cacheHitPercent = ((double)cacheHit / (cacheHit + (double)cacheMiss)) * 100;

    for (unsigned long long jx = 0; jx < cacheSize; jx++)
    {
        printf("%llu , %llu, %llu, %2.0f percent \n", cache[jx].rN, cache[jx].steps, cache[jx].Count, cacheHitPercent);
    }
    printf("%4.20f seconds\n", timeTaken);
    // for(unsigned long long i = 0; i < cacheSize; i++){
    //     printf("%llu\n", cache[i].steps);
    //     printf("%llu\n", cache[i].rN);
    //  }

    free(cache);
    return 0;
}
