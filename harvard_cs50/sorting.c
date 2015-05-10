// Problem Set 3 - Binary Search | Sorting Algorithms

/****************************************************************************
 * find.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Prompts user for as many as HAY_MAX values until EOF is reached, 
 * then proceeds to search that "haystack" of values for given needle.
 *
 * Usage: find needle
 *
 * where needle is the value to find in a haystack of values
 ***************************************************************************/
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

bool search(int value, int array[], int low, int high);
void sort(int values[], int n);

// maximum amount of hay
const int HAY_MAX = 65536;


int
main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: %s needle\n", argv[0]);
        return 1;
    }

    // remember needle
    int needle = atoi(argv[1]);

    // fill haystack
    int size;
    int haystack[HAY_MAX];
    for (size = 0; size < HAY_MAX; size++)
    {
        // wait for hay until EOF
        printf("\nhaystack[%d] = ", size);
        int straw = GetInt();
        if (straw == INT_MAX)
            break;
        
        // add hay to stack
        haystack[size] = straw;
    }
    printf("\n");

    // sort the haystack
    sort(haystack, size);

    // try to find needle in haystack
    if (search(needle, haystack, 0, size - 1))
        printf("\nFound needle in haystack!\n\n");
    else
        printf("\nDidn't find needle in haystack.\n\n");

    // that's all folks
    return 0;
}

/*
 * bool
 * search(int value, int array[], int n)
 *
 * Returns true if value is in array of n values, else false.
 */

bool 
search(int value, int array[], int low, int high)
{
	int mid;
	
	if(high < low) {
		return false;
	}
	
	mid = low + ((high - low) / 2);
	if(array[mid] > value) {
		return search(value, array, low, mid - 1);
	} else if(array[mid] < value) {
		return search(value, array, mid + 1, high);
	} else {
		return true;
	}
}


/*
 * void
 * sort(int values[], int n)
 *
 * Sorts array of n values.
 */

void
sort(int values[], int n)
{
    int x, y;
    
    // bubble sort
    for(x = 0; x < n; x++) {
    	for(y = 0; y < n; y++) {
    		if(values[y] > values[y + 1]) {
    			int temp = values[y + 1];
    			values[y + 1] = values[y];
    			values[y] = temp;
    		}
    	}
    }
    
    return;
}
