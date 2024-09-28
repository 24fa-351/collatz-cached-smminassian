#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char N;
    int Value;
} items;

int cacheIndex = 0;
items *input(int RN, int steps, items *cache, int cacheSize)
{
   
    if (cacheIndex < cacheSize)
    {
        char key = (char)RN;
        cache[cacheIndex].N = key;
        cache[cacheIndex].Value = steps;
        cacheIndex++;
    }
    return cache;
}

int collatz(int RN)
{
    int steps = 0;
    int oneChecker;
    oneChecker = RN;

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
        else if (oneChecker == 1)
        {
            steps++;
            break;
        }
    }
    return steps;
}

items *collatz_wrapper(int N, int Min, int Max, int cacheSize)
{
  
    items *cache = (items *)malloc(sizeof(items) * cacheSize);
    int steps = 0;
    int RN = 0;

    for (int ix = 0; ix <= N; ix++)
    {
        RN = rand() % (Max - Min);

        steps = collatz(RN);

        cache = input(RN, steps, cache, cacheSize);
        
    }

    return cache;
    
}

int main(int __argc, char *__argv[])
{

    int cacheSize = 20;
    int N = 0;
    int Min = 0;
    int Max = 0;

    items *cache = (items *)malloc(sizeof(items) * cacheSize);
    if (__argc == 4)
    {
        N = atoi(__argv[1]);
        Min = atoi(__argv[2]);
        Max = atoi(__argv[3]);

        
    
    cache = collatz_wrapper(N, Min, Max, cacheSize);
    for(int i = 0; i < cacheSize; i++){
        printf("N: %d  Steps: %d ", cache[i].N, cache[i].Value);
    }
    }
    free(cache);
    return 0;
}