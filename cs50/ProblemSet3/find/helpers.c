/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 

bool search(int value, int values[], int n)
{
    bool answer=false;
    if (value >= 0 && n > 0)
    {   
        int start=0, position=0, finish=n;
        while (start< finish)
        {
            position = (start + finish) / 2;
            if (value < values[position])
            {
                finish = position;
            }
            else if (value > values[position])
            {
                start = position+1;
            }
            else 
            {
                answer=true;
                break;
            }
        } 
    }
    return answer;
}

/**
 * insert Sort array of n values.
 */
void sort(int values[], int n)
{
    int i, j, tmp;
    for (i = 1; i < n; ++i) 
    {
        tmp = values[i];
        for (j = i; j > 0 && values[j-1] > tmp; --j) 
        {
            values[j] = values[j-1];   
        }
        values[j] = tmp;   
    }
    
    return;
}
