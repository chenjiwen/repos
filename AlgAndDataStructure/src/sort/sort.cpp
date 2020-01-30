#include "sort.h"
#include <string.h>
/*
 *bubble sort
 *
 *
 */
void bubble_sort(int len,  uint32_t array[]) {
    uint32_t temp = 0;
    int i = 0, j = 0;
    for (j = len - 1; j > 0; j--)
    {
		for (i = 0; i < j; i++)
		{
			if (array[i] > array[i + 1])
			{
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
    }

}

/*
 *insertion sort
 *1+2+3+...+n=n(n+1)/2=O(n^2)
 */
void insertion_sort(int len, uint32_t array[]) {
    int i = 0, j = 0;
    uint32_t temp = 0;

    for (i = 0; i < len; i++)
    {
        for (j = i - 1; j >= 0; j--)
        {
            if(array[j + 1] < array[j])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

/*
 *merge sort
 *divide and concur 
 *f(n) = f(n/2)+o(n)
 *f(n)= n*log(n)
*/

void merge_sorted(uint32_t array[], int len_a, uint32_t array_a[], int len_b, uint32_t array_b[]) 
{
    int idx = 0;
    int idx_a = 0;
    int idx_b = 0;

    for (idx = 0; idx < len_a + len_b; idx++)
    {
        if (array_a[idx_a] < array_b[idx_b])
        {
            array[idx] = array_a[idx_a++];
        }
        else
        {
            array[idx] = array_b[idx_b++];
        }

        if ((idx_a == len_a) || (idx_b == len_b))
        {
            break;
        }
    }

    if (idx_a == len_a)
    {
        for (idx++; idx < len_a + len_b; idx++)
        {
            array[idx] = array_b[idx_b++];
        }
    } 
    else
    {
		for (idx++; idx < len_a + len_b; idx++)
		{
			array[idx] = array_a[idx_a++];
		}
    }
}

void static merge_sort_internal(int left, int right, uint32_t array[])
{
    int mid = 0;
    uint32_t* array_left;
    uint32_t* array_right;


    if (left == right)
    {
        return;
    }

	mid = (left + right) >> 1;

    //step1: sort the left part
    merge_sort_internal(left, mid, array);

    //step2: sort the right part
    merge_sort_internal(mid + 1, right, array);


    //step3: merge left part together with right part
    array_left  = new uint32_t[mid - left + 1];
    memcpy((uint32_t*)array_left, (uint32_t*)(array + left), (mid - left + 1)*sizeof(uint32_t));

    array_right = new uint32_t[right - mid];
    memcpy((uint32_t*)array_right, (uint32_t*)(array + mid + 1), (right - mid)*sizeof(uint32_t));

    merge_sorted(array + left, mid - left + 1, array_left, right - mid, array_right);

    delete [] array_left;
    delete [] array_right;
}

void merge_sort(int array_len, uint32_t array[]) {
    merge_sort_internal(0, array_len - 1, array);
}

/*quick sort*/
static int quick_sort_partition(int left_idx, int right_idx, uint32_t array[]) 
{
    uint32_t sentential = 0;
    int idx = 0;
    int sentential_idx = 0;
    uint32_t temp = 0;

    sentential_idx = left_idx;
    sentential = array[sentential_idx];

    for (idx = left_idx; idx <= right_idx; idx++)
    {
        if (array[idx] < sentential)
        {
            array[sentential_idx] = array[idx];
            sentential_idx = idx;          
            array[idx] = sentential;
        }
    }

    return sentential_idx;
}

void quick_sort(int left, int right, uint32_t array[])
{
    int idx = 0;

    if (left >= right)
        return;

    idx = quick_sort_partition(left, right, array);

    quick_sort(0, idx, array);
    quick_sort(idx + 1, right, array);
}

/*
*selection sort
*/

void selecion_sort(int len, uint32_t array[])
{
    int idx = 0, min_idx = 0;
    uint32_t min = 0;
    uint32_t temp = 0;

    for (idx = 0; idx < len; idx++)
    {
        int j = 0;
        min = array[idx];
        min_idx = idx;
        for (j = idx + 1; j < len; j++)
        {
            if (array[j] < min)
            {
                min = array[j];
                min_idx = j;
            }
        }
        if(min_idx == idx)
            continue;
		temp = array[idx];
		array[idx] = array[min_idx];
		array[min_idx] = temp;
    }
}


