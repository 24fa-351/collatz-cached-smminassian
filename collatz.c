#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "collatz.h"


unsigned long long cacheIndex = 0;
unsigned long long count = 0;
unsigned long long lruCount = 0;
unsigned long long mruCount = (cacheSize-1);


myStruct* LRU(unsigned long long RN, unsigned long long steps, myStruct* cache){
    
    cache[lruCount].rN = RN;
    cache[lruCount].steps = steps;
    cache[lruCount].Count = lruCount;
    lruCount++;
    
    return cache;
}


// myStruct* MRU(unsigned long long RN, unsigned long long steps, myStruct* cache){
    
//     cache[mruCount].rN = RN;
//     cache[mruCount].steps = steps;
//     cache[mruCount].Count = mruCount;
//     mruCount--;
    
//     return cache;
// }

myStruct* input(unsigned long long RN, unsigned long long steps, myStruct *cache)
{
    
    if (cacheIndex < cacheSize)
    {
       
        cache[cacheIndex].rN = RN;
        cache[cacheIndex].steps = steps;
        cache[cacheIndex].Count = count;
        cacheIndex++;
        count++;
      
    }
    else if(cacheIndex >= cacheSize){
        //cache = LRU(RN, steps, cache);
        cache = LRU(RN, steps, cache);
    }
    
    return cache;
}

unsigned long long collatz(unsigned long long RN)
{
    unsigned long long steps = 0;
    clock_t start;
    clock_t end;
    double timeTaken;
    unsigned long long originalRN = RN;

    
    // for(int i = 0; i < cacheSize; i++){
    //     if(cache == []){
    //         break;
    // }
    //     else if(cache[i].rN == RN){    my brain is fried and i dont know what to put for 


    //     }
    // }
    start = clock();

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
    end = clock();
    timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%llu\n ", originalRN);
    //printf("%llu\n", steps);
    //printf("%f\n",timeTaken);
    return steps;
}

myStruct* collatz_wrapper(unsigned long long N, unsigned long long Min, unsigned long long Max, myStruct* cache)
{
    unsigned long long steps = 0;
    unsigned long long RN = 0;

    for (unsigned long long ix = 0; ix < N; ix++)
    {
        RN = rand() % (Max - Min) + Min;

        steps = collatz(RN);

        cache = input(RN, steps, cache);
        
    }

    return cache;
    
}

int main(int __argc, char *__argv[])
{
    unsigned long long N = 0;
    unsigned long long Min = 0;
    unsigned long long Max = 0;

    myStruct *cache = (myStruct*)malloc(sizeof(myStruct) * cacheSize);
    if (__argc == 4)
    {
        N = atoi(__argv[1]);
        Min = atoi(__argv[2]);
        Max = atoi(__argv[3]);

    }
    
    cache = collatz_wrapper(N, Min, Max, cache);
    for(unsigned long long i = 0; i < cacheSize; i++){
        printf("%llu , %llu, %llu\n ", cache[i].rN, cache[i].steps, cache[i].Count);
    }
    
    free(cache);
    return 0;
}


//I will implement that time counter that he said in lecture. Moreover look at 44:03 in lecture. 