#include <stdio.h>
#include <stdlib.h>

int collatz(int result)
{
    int N;
    int Max;
    int Min;
    int RN;
    int steps = 0;

    scanf("%d %d %d", N, Min, Max);
    for (int ix = 0; ix <= N; ix++)
    {
        RN = rand() % (Max - Min);
        if (RN % 2 == 0)
        {
            result = RN / 2;
            steps++;
        }
        else if (RN % 2 != 0)
        {
            result = (3 * RN) + 1;
            steps++;
        }
        if (result != 1)
        {
            collatz(result);
        }
        else if (result == 1)
        {
            break;
        }
    }
    return RN, steps;
}


int main()
{
    int collatzResult = 0;
    int RN = 0;
    int steps;

    RN = collatz(collatzResult);
    steps = collatz(collatzResult);
}