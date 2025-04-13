#include <string.h>
#include <diff.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct coord{
    int x;
    int y;
}coord;



char* myer_diff(char* A, char* B)
{
    
    //An implementation of the Myers diff algorithm.
    //See http://www.xmailserver.org/diff2.pdf
    
    
    int y = 0;
    int x = 0;
    int a_max = strlen(A);
    int b_max = strlen(B);
    int go_down = 0;
    int old_x = 0;
    coord* coord = calloc(a_max + b_max, sizeof(coord));
    char* final_str = malloc((a_max + b_max) * 4); // Allocate enough space for the result
    if (!final_str) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    final_str[0] = '\0'; 
    for(int D = 0; D <= a_max + b_max; D++)
    {
        for(int k = -D; k <= D; k += 2)
        {
        
            // This determines whether our next search point will be going down
            // in the edit graph, or to the right.
            //
            // The intuition for this is that we should go down if we're on the
            // left edge (k == -d) to make sure that the left edge is fully
            // explored.
            //
            // If we aren't on the top (k != d), then only go down if going down
            // would take us to territory that hasn't sufficiently been explored
            // yet.
            
            go_down = (k == -D || (k != D && coord[k - 1].x < coord[k + 1].x));

            // Figure out the starting point of this iteration. The diagonal
            // offsets come from the geometry of the edit grid - if you're going
            // down, your diagonal is lower, and if you're going right, your
            // diagonal is higher.
            if(go_down != 0)
            {
                old_x = coord[k + 1].x;
                //history = coord[k + 1];
                x = old_x;
            }
            else
            {
                old_x = coord[k-1].x;
                x = old_x + 1;
            }

                

            // We want to avoid modifying the old history, since some other step
            // may decide to use it.
            // history = history[:]
            y = x - k;

            // We start at the invalid point (0, 0) - we should only start building
            // up history when we move off of it.
            
            if(1 <= y && y <= b_max && go_down)
            {
                char* temp_str = "+++";
                temp_str = realloc(temp_str, sizeof(B) + 3);
                strcat(temp_str, &B[y]);
                strcat(final_str, temp_str);
            }
            else if (1 <= x && x <= a_max)
            {
                char* temp_str = "---";
                temp_str = realloc(temp_str, sizeof(A) + 3);
                strcat(temp_str, &A[y]);
                strcat(final_str, temp_str);
            }

            // Chew up as many diagonal moves as we can - these correspond to common lines,
            // and they're considered "free" by the algorithm because we want to maximize
            // the number of these in the output.
            while (x < a_max && y < b_max && A[x + 1] == B[y + 1])
                x += 1;
                y += 1;
                
                strcat(final_str, &A[x]); // TODO SEGFAULT

            if (x >= a_max && y >= b_max)
            {
                // If we're here, then we've traversed through the bottom-left corner,
                // and are done.
                return final_str;
            }
            else
            {
                coord[k] = coord[x];
            }     
        }
    }
    return final_str;
}