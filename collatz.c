#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int rN;
    int steps;
    int Count;
} myStruct;

int cacheIndex = 0;
int count = 0;
int lruCount = 0;
const int cacheSize = 11;
int mruCount = (cacheSize-1);


/*items* LRU(int RN, int steps, items* cache){
    
    cache[lruCount].rN = RN;
    cache[lruCount].steps = steps;
    cache[lruCount].Count = lruCount;
    lruCount++;
    
    return cache;
}
*/

myStruct* MRU(int RN, int steps, myStruct* cache){
    
    cache[mruCount].rN = RN;
    cache[mruCount].steps = steps;
    cache[mruCount].Count = mruCount;
    mruCount--;
    
    return cache;
}

myStruct* input(int RN, int steps, myStruct *cache)
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
        cache = MRU(RN, steps, cache);
    }
    
    return cache;
}


int collatz(int RN)
{
    int steps = 0;

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
    return steps;
}

myStruct* collatz_wrapper(int N, int Min, int Max, myStruct* cache)
{
    int steps = 0;
    int RN = 0;

    for (int ix = 0; ix < N; ix++)
    {
        RN = rand() % (Max - Min) + Min;

        steps = collatz(RN);

        cache = input(RN, steps, cache);
        
    }

    return cache;
    
}

int main(int __argc, char *__argv[])
{
    int N = 0;
    int Min = 0;
    int Max = 0;

    myStruct *cache = (myStruct*)malloc(sizeof(myStruct) * cacheSize);
    if (__argc == 4)
    {
        N = atoi(__argv[1]);
        Min = atoi(__argv[2]);
        Max = atoi(__argv[3]);

    }
    
    cache = collatz_wrapper(N, Min, Max, cache);
    for(int i = 0; i < cacheSize; i++){
        printf("%d , %d, %d\n ", cache[i].rN, cache[i].steps, cache[i].Count);
    }
    
    free(cache);
    return 0;
}


//I will implement that time counter that he said in lecture. Moreover look at 44:03 in lecture. 