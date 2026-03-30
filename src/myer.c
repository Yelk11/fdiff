#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coord{
    
}coord;


int* shortest_edit(char *a, char *b)
{
    int N = strlen(a);
    int M = strlen(b);
    int MAX = N + M;
    int V[2 * MAX + 1];
    V[1] = 0;
    int x, y;
    int* trace = calloc(1,2 * MAX + 1);

    for (int D = 0; D < MAX; D++)
    {
        memcpy(trace, V, sizeof(V));
        for (int k = -D; k < D; k++)
        {
            if (
                (k == D) ||
                    ((k != D) && 
                    (V[k - 1] < V[k + 1])))
            {
                x = V[k + 1];
            }
            else
            {
                x = V[k - 1] + 1;
            }
            y = x - k;
            while ((x < N) && 
                    (y < M) && 
                    (a[x + 1] == b[y + 1]))
            {
                x = x + 1;
                y = y + 1;
            }
            V[k] = x;
            if ((x >= N) && (y >= M))
            {
                return trace;
            }
        }
    }
    return trace;
}


char* backtrack(int* shrtedt, char* a, char* b)
{
    int x = strlen(a);
    int y = strlen(b);
    for(int i = 0; i < )
}


