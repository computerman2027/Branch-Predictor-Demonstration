#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    const int N = 10000;
    int array[N];
    int sum = 0;

    for (int i = 0; i < N; ++i)
    {
        array[i] = rand() % 255;
    }

    qsort(array, N, sizeof(int), compare);

    clock_t start = clock();

    for (int j = 0; j < 1000000; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            if (array[i] <= 100)
            {
                sum += array[i];
            }
        }
    }

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time: %f sec sum = %d", elapsed,sum);

    return 0;
}