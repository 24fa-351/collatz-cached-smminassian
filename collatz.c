#include <stdio.h>
#include <stdlib.h>

int collatz(int result, int N, int Min, int Max, int steps)
{
    result = 0;
    int RN = 0;

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
            collatz(result, N, Min, Max, steps);
        }
        else if (result == 1)
        {
            ix++;
        }
    }

    return RN, steps;
}

int main(int __argc, char *__argv[])
{
    int collatzResult = 0;
    int steps = 0;
    int N = 0;
    int Min = 0;
    int Max = 0;
    int result = 0;
    int RN = 0;
if(__argc == 4){
    N = atoi(__argv[1]);
    Min = atoi(__argv[2]);
    Max = atoi(__argv[3]);
    RN, steps = collatz(result, N, Min, Max, steps);

    printf("%d", RN);
    printf("%d", steps);
}
}