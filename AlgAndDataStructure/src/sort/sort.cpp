#include "sort.h"
#include <string.h>
#include "binary_heap.h"

/*
 *bubble sort
 *
 *
 */
void bubble_sort(int len,  uint32_t array[]) {
    uint32_t temp = 0;
    int i = 0, j = 0;
    //循环len次冒泡
    for (j = len - 1; j > 0; j--)
    {
        //每次冒泡的时候需要交换/比较的次数j
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

/*
 *合并两个有序数组：
 *
 *if a[j]<b[i] c[k++]=a[j++]
 *if a[j]>b[i] c[k++]=b[i++]
 *
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

/*
 *快速排序中的划分算法：
 *    划分把数组分成两个部分，前半部分小于给定的元素，后半部分不小于给定的元素，该函数同时返回给定元素哨兵在划分中的位置.
 *    从头部中，把不小于给定哨兵元素交换到尾部，
 *    从尾部中，把小于给定哨兵元素交换到头部
 */
int quick_sort_partition(int left_idx, int right_idx, uint32_t array[]) 
{
    uint32_t sentential = 0;
    int idx = 0;
    int sentential_idx = 0;
    uint32_t temp = 0;
    int mid = 0;

    //
    mid = (left_idx + right_idx) >> 1;

    //哨兵可以选取任意位置
    sentential_idx = mid;
    sentential = array[sentential_idx];

    for (idx = left_idx; idx < right_idx; )
    {   //找出左半部不小于给定哨兵的元素
        if (array[idx] < sentential)
        {
            idx++;
            //当前左半部的元素小于给定的元素，继续找
            continue;
        }
        else
        {
            //当前的头部元素不小于哨兵元素，从尾部找出尾部小于给定元素的位置
            while ((right_idx > idx) && (array[right_idx] >= sentential))
                right_idx--;

            //找到了一个小于哨兵的元素，与前半部的小于哨兵元素交换
			if (right_idx != idx)
			{
				temp = array[right_idx];
				array[right_idx] = array[idx];
				array[idx] = temp;
			}

            //如果idx == right_idx，则表明，当前元素与哨兵相等,退出循环，直接返回当前位置
        }

    }

    return idx;
}

static int quick_sort_tail_partion(int left_idx, int right_idx, uint32_t array[])
{
    uint32_t pivot_element = 0;
    uint32_t temp;
    int i = 0, j = 0;

    //i 用于保存当前小于pivot_element = array[right_idx]的位置
    i = left_idx - 1;//初始位置为left - 1
    pivot_element = array[right_idx];

    //j 用于迭代查找小于pivot element，当找到后array[i+1]<->array[j]
    for (j = left_idx; j < right_idx - 1; j++)
    {
        //当前的元素小于pivot，交换到i + 1的位置
        if (array[j] <= pivot_element)
        {
            i++;
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    } 

    //i为小于pivot的当前文职， i 到rihgt_idx都是大于等于pivot，i + 1位置与最后的pivot交换
    temp = array[right_idx];
    array[right_idx] = array[i + 1];
    array[i + 1] = temp;

    return i + 1;
}

void quick_sort(int left, int right, uint32_t array[])
{
    int idx = 0;

    if (left >= right)
        return;

    idx = quick_sort_partition(left, right, array);

    quick_sort(left, idx - 1, array);
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


//找出一个组数的第k小的数
//
// k:     需要返回的第k大的元素
// left:  数组的最小下标
// right: 数组的最大下标
//

uint32_t select_kth(int k, int left, int right, uint32_t array[]) {
    
    int i = 0;

    //对于第k大的元素，在从小到大的数组中的位置为：right - left + 1 - k;
    k = right - left + 1 - k;

    do 
    {
        i = quick_sort_partition(left, right, array);

        //划分的位置小于k，则说明当前返回的位置的元素小于第k大的元素
        //从当前位置往后继续寻找
        if (i < k)
        {
            left = i + 1;
        }
        else if (i > k)
        {
            //当前的位置比k大，需要从开始到当前位置继续寻找
            right = i;
        }
    } while (i != k);

    return array[i];
}


//
//
//

vector<int> getMid(vector<int> vec1, vector<int> vec2) {
    int mid1_1 = 0, mid1_2 = 0;
    int mid2_1 = 0, mid2_2 = 0;
    vector<int> vec1_mid_idx;
    vector<int> vec2_mid_idx;
    vector<int> vec;

    int mid = mid = vec2.size() + vec1.size();
    if (mid & 0x1)
    {
        
        while (mid != (vec2.size() + vec1.size()) >> 1)
        {
			//偶数，
			if (vec1.size() % 2 == 0)
			{
				mid1_1 = (vec1.size() >> 1) - 1;

			}
			else
			{
				mid1_1 = vec1.size() >> 1;
			}
            //vec1 分成两部分: vec1[0]....vec1[mid1_1](记为A), vec1[mid1_1 + 1]...vec1[size](记为B)
            //vec2 分成两部分: vec2[0]....vec2[mid2_1](记为C), vec2[mid2_1 + 1]...vec2[size](记为D)
            //中位数一定在[B U C]或者[D U A]中???

			if (vec2.size() % 2 == 0)
			{
				mid2_1 = (vec1.size() >> 1) - 1;;
			}
			else
			{
				mid2_1 = vec1.size() >> 1;
			}

            //
            //



        }
    }


    return vec;


}