/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // save bounds of list
    int beginning = 0;
    int end = n - 1;
    
    // while length of list > 0
    while (end >= beginning)
    {
        // look at middle of list
        int middle = (beginning + end) / 2;
        
        // if number found, return true
        if (values[middle] == value)
        {
            return true;
        }
        
        // else if middle higher, search left
        else if (values[middle] < value)
        {
            beginning = middle + 1;
        }
        
        // else if middle lower, search right
        else
        {
            end = middle - 1;
        }
    }
    
    // return false
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implement an O(n^2) sorting algorithm (Selection Sort)
    
    // divide list into two, sorted and unsorted
    
    for (int i = 0; i < n; i++)
    {
        // declare a new minimum
        int min = i;
        
        // look through array beyond what has already been sorted
        for (int j = i + 1; j < n; j++)
        {
            if (values[j] < values[min])
            {
                // change the value of the minimum
                min = j;
            }
        }
        if (min != i)
            {
                // create a storage variable to hold the minimum
                int swap = values[min];
                
                // swap the minimum value with the iteration of i
                values[min] = values[i];
                
                // place the storage variable in the iteration of i
                values[i] = swap;
            }
    }
    return;
    
}
