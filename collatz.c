// #include <stdio.h>
// #include <stdlib.h>

// typedef struct
// {
//     char N;
//     int Value;
//     int Count;
// } items;

// int cacheIndex = 0;
// int count = 0;
// items *input(int RN, int steps, items *cache, int cacheSize)
// {
//     if (cacheIndex < cacheSize)
//     {
//         char key = (char)RN;
//         cache[cacheIndex].N = key;
//         cache[cacheIndex].Value = steps;
//         cacheIndex++;
//         count++;
//         cache[cacheIndex].Count = count;
//     }
//     else if(cacheIndex > cacheSize){
//         cache = LRU(cacheSize, cache, count, cacheIndex);
//     }
//     return cache;
// }

// items *LRU(int cacheSize, items* cache, int count, int cacheIndex){
 
    
//// }

// int collatz(int RN)
// {
//     int steps = 0;
//     int oneChecker;
//     oneChecker = RN;

//     while (RN != 1)
//     {

//         if (RN % 2 == 0)
//         {
//             RN = RN / 2;
//             steps++;
//         }
//         else if (RN % 2 != 0)
//         {
//             RN = (3 * RN) + 1;
//             steps++;
//         }
//         else if (oneChecker == 1)
//         {
//             steps++;
//             break;
//         }
//     }
//     return steps;
// }

// items *collatz_wrapper(int N, int Min, int Max, int cacheSize)
// {
  
//     items *cache = (items *)malloc(sizeof(items) * cacheSize);
//     int steps = 0;
//     int RN = 0;

//     for (int ix = 0; ix < N; ix++)
//     {
//         RN = rand() % (Max - Min) + Min;

//         steps = collatz(RN);

//         cache = input(RN, steps, cache, cacheSize);
        
//     }

//     return cache;
    
// }

// int main(int __argc, char *__argv[])
// {

//     int cacheSize = 20;
//     int N = 0;
//     int Min = 0;
//     int Max = 0;

//     items *cache = (items *)malloc(sizeof(items) * cacheSize);
//     if (__argc == 4)
//     {
//         N = atoi(__argv[1]);
//         Min = atoi(__argv[2]);
//         Max = atoi(__argv[3]);

//     }
    
//     cache = collatz_wrapper(N, Min, Max, cacheSize);
//     for(int i = 0; i < cacheSize; i++){
//         printf("%d , %d\n ", cache[i].N, cache[i].Value, cache[i].Count);
//     }
    
//     free(cache);
//     return 0;
// }


//I will implement that time counter that he said in lecture. Moreover look at 44:03 in lecture. 
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int rN;
    int steps;
    int Count;
} items;

int cacheIndex = 0;
int count = 0;
int lruCount = 0;

items* LRU(int RN, int steps, items* cache){
    
    cache[lruCount].rN = RN;
    cache[lruCount].steps = steps;
    cache[lruCount].Count = lruCount;
    lruCount++;
    
    return cache;
}

items *input(int RN, int steps, items *cache, int cacheSize)
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
        cache = LRU(RN, steps, cache);
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

items *collatz_wrapper(int N, int Min, int Max, int cacheSize)
{
  
    items *cache = (items *)malloc(sizeof(items) * cacheSize);
    int steps = 0;
    int RN = 0;

    for (int ix = 0; ix < N; ix++)
    {
        RN = rand() % (Max - Min) + Min;

        steps = collatz(RN);

        cache = input(RN, steps, cache, cacheSize);
        
    }

    return cache;
    
}

int main(int __argc, char *__argv[])
{

    int cacheSize = 11;
    int N = 0;
    int Min = 0;
    int Max = 0;

    items *cache = (items *)malloc(sizeof(items) * cacheSize);
    if (__argc == 4)
    {
        N = atoi(__argv[1]);
        Min = atoi(__argv[2]);
        Max = atoi(__argv[3]);

    }
    
    cache = collatz_wrapper(N, Min, Max, cacheSize);
    for(int i = 0; i < cacheSize; i++){
        printf("%d , %d, %d\n ", cache[i].rN, cache[i].steps, cache[i].Count);
    }
    
    free(cache);
    return 0;
}


//I will implement that time counter that he said in lecture. Moreover look at 44:03 in lecture. 