#include "sort.h"
#include <string.h>
#include "binary_heap.h"
#include <iostream>
using namespace std;
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


int quickPartition(int A[], int left, int right)
{
    int pivot;
    int i, j;

    pivot = A[(right + left) >> 1];//choose the medium as the pivot
    i = left;                    //from the begin of A
    j = right;              //from the end of A

    while (i < j) {
        if (A[i] < pivot)
            i++;
        else if (A[j] > pivot)
            j--;
        else if (A[i] == A[j])
        {
            if(i - left < right - j)
                i++;
            else
                j--;
        }
        else
            swap(A[i], A[j]);
    }
    //A[i] = pivot;
    return i;
}

/*
 *快速排序中的划分算法：
 *    划分把数组分成两个部分，前半部分小于给定的元素，后半部分不小于给定的元素，该函数同时返回给定元素哨兵在划分中的位置.
 *    从头部中，把不小于给定哨兵元素交换到尾部，
 *    从尾部中，把小于给定哨兵元素交换到头部
 */
int quick_sort_partition(int left_idx, int right_idx, int array[]) 
{
    int sentential = 0;
    int idx = 0;
    int sentential_idx = 0;
    int temp = 0;
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
            if (sentential == array[right_idx])
                sentential_idx = right_idx;
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
    if (array[idx] < sentential)
    {
        swap(array[++idx], array[sentential_idx]);
    }
    else
    {
        swap(array[idx], array[sentential_idx]);
    }
    return idx;
}

static int quick_sort_tail_partion(int left_idx, int right_idx, int array[])
{
    int pivot_element = 0;
    int temp;
    int i = 0, j = 0;

    //i 用于保存当前小于pivot_element = array[right_idx]的位置
    i = left_idx - 1;//初始位置为left - 1
    pivot_element = array[right_idx];

    //j 用于迭代查找小于pivot element，当找到后array[i+1]<->array[j]
    for (j = left_idx; j <= right_idx - 1; j++)
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

    //i为小于pivot的当前位置， i 到rihgt_idx都是大于等于pivot，i + 1位置与最后的pivot交换
    temp = array[right_idx];
    array[right_idx] = array[i + 1];
    array[i + 1] = temp;

    return i + 1;
}

void quick_sort(int left, int right, int array[])
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
        i = quick_sort_partition(left, right,(int*) array);

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

int select_kth_with_heap(uint32_t k) {
    BinaryHeap bheap(MIN_BINARY_HEAP);
    int num = -1;

    while (cin >> num)
    {
        if (bheap.getHeapSize() < k)
        {
            bheap.min_heap_insert(num);
        }
        else if (num > bheap.getMinFromMinHeap())
        {
            bheap.min_heap_delete(1);
            bheap.min_heap_insert(num);
        }
    }

    return bheap.getMinFromMinHeap();
}

int a[100][100] = { 0 };
int idx[100];

bool isPossibleDivide(int nums[], int len, int k) {
	//先排序，然后填一个二维数组    
	int i = 0, j = 0, m = 0, n = 0;
	int prev = 0, diff = 0;
	const int col = k;
	const int row = len / k;
	
    bool duplicated = false;


	if (len % k != 0) {
		return false;
	}

	quick_sort(0, len - 1, (int*)nums);

    //fill the table in column
    //i_row用于记录row
    //j_col用于记录col
    //当遇到一个相同的元素的时候，放到下一列
    int cur_row = 0;
    int cur_col = 0;
    int i_row = 0;

    for (m = 0; m < len; m++)
    {
        if (m == 0)
        {
            prev = nums[m];
            a[cur_row][cur_col] = nums[m];
            cur_col++;
            idx[cur_row] = cur_col;
            continue;
        }
        else if (prev == nums[m])
        {
            //把当前的列位置记录在row idx数组中
            idx[cur_row] = cur_col;
            i_row = cur_row;
            cur_row = 0;
            while (1)
            {
                if (idx[cur_row] != col)
                {
                    if (i_row == cur_row)
                    {
						cur_row++;
						cur_row %= row;
                        continue;
                    }
                    else if (idx[cur_row] && (a[cur_row][idx[cur_row] - 1] == nums[m]))
                    {
						cur_row++;
						cur_row %= row;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
      
				cur_row++;
				cur_row %= row;
            }
            //找到了行，把列从idx表里取出来
            cur_col = idx[cur_row];
            a[cur_row][cur_col] = nums[m];
            cur_col++;
            idx[cur_row] = cur_col;
        }
        else
        {
            cur_col = idx[cur_row];
			//如果当前的行已经满，找下一个合适的行
			if (cur_col == col)
			{
                i_row = cur_row;
				cur_row = 0;
				while (1)
				{
					if (idx[cur_row] != col)
					{
						if (i_row == cur_row)
						{
							cur_row++;
							cur_row %= row;
							continue;
						}
						else if (a[cur_row][idx[cur_row] - 1] == nums[m])
						{
							cur_row++;
							cur_row %= row;
							continue;
						}
						else
						{
							break;
						}
					}

					cur_row++;
					cur_row %= row;
				}
                cur_col = idx[cur_row];
			}

            a[cur_row][cur_col] = nums[m];
            prev = nums[m];
            cur_col++;
            idx[cur_row] = cur_col;

        }
    }

    for (i = 0; i < row; i++)
    {
        prev = 0;
        for (j = 0; j < col; j++)
        {
            if (j == 0)
            {
                prev = a[i][j];
                continue;
            }

            if (a[i][j] != prev + 1)
            {
                return false;
            }

            prev = a[i][j];
        }
    }

	return true;
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

int quick_sort_partion(vector<int>& nums, vector<int>::size_type begin, vector<int>::size_type end) {
	int i = begin - 1, j = 0;
	int pivot = nums[end];//最后一个元素作为主元

	for (j = begin; j <= end - 1; j++) {
		if (nums[j] < pivot) {
			swap(nums[++i], nums[j]);
		}
	}

	swap(nums[++i], nums[end]);

	return i;
}

void quick_sort(vector<int>& nums, vector<int>::size_type begin, vector<int>::size_type end) {
	vector<int>::size_type idx = 0;
	if (begin >= end) {
		return;
	}

	idx = quick_sort_partion(nums, begin, end);

	quick_sort(nums, begin, idx - 1);
	quick_sort(nums, idx + 1, end);
}
/*
 *把一个数组先排序，然后分成大小相同的子数组，子数组长度相同为K
 *子数组按升序排列
 *
 *[1,2,2,3,3,4,4,5]->
 *
 *[1,2,3,4]
 *[2,3,4,5]
 */
bool isPossibleDivide(vector<int>& nums, int k) {
	//先排序，然后填一个二维数组    
	int i = 0, j = 0, m = 0;
	int prev = 0, diff = 0;
	const int col = k;
	const int row = nums.size() / k;
	int cur_row = 0;
	int cur_col = 0;
	int len = nums.size();

	if (nums.size() % k != 0) {
		return false;
	}

	quick_sort(nums, 0, nums.size() - 1);


	int i_row = 0;

	for (m = 0; m < len; m++)
	{
		if (m == 0)
		{
			prev = nums[m];
			a[cur_row][cur_col] = nums[m];
			cur_col++;
			idx[cur_row] = cur_col;
			continue;
		}
		else if (prev == nums[m])
		{
			//把当前的列位置记录在row idx数组中
			idx[cur_row] = cur_col;
			i_row = cur_row;
			cur_row = 0;
			while (1)
			{
				if (idx[cur_row] != col)
				{
                    //行没有满的情况
					if (i_row == cur_row)
					{
                        //需要排除当前行
						cur_row++;
						cur_row %= row;
						continue;
					}
					else if (idx[cur_row] && (a[cur_row][idx[cur_row] - 1] == nums[m]))
					{
                        //如果改行的最后一个元素与当前元素相同也需要排除
						cur_row++;
						cur_row %= row;
						continue;
					}
					else
					{
						break;
					}
				}

				cur_row++;
				cur_row %= row;
			}
			//找到了行，把列从idx表里取出来
			cur_col = idx[cur_row];
			a[cur_row][cur_col] = nums[m];
			cur_col++;
			idx[cur_row] = cur_col;
		}
		else
		{
			cur_col = idx[cur_row];
			//如果当前的行已经满，找下一个合适的行
			if (cur_col == col)
			{
				i_row = cur_row;
				cur_row = 0;
				while (1)
				{
					if (idx[cur_row] != col)
					{
						if (i_row == cur_row)
						{
							cur_row++;
							cur_row %= row;
							continue;
						}
						else if (idx[cur_row] && (a[cur_row][idx[cur_row] - 1] == nums[m]))
						{
							cur_row++;
							cur_row %= row;
							continue;
						}
						else
						{
							break;
						}
					}

					cur_row++;
					cur_row %= row;
				}
				cur_col = idx[cur_row];
			}

			a[cur_row][cur_col] = nums[m];
			prev = nums[m];
			cur_col++;
			idx[cur_row] = cur_col;

		}
	}

	for (i = 0; i < row; i++)
	{
		prev = 0;
		for (j = 0; j < col; j++)
		{
			if (j == 0)
			{
				prev = a[i][j];
				continue;
			}

			if (a[i][j] != prev + 1)
			{
				return false;
			}

			prev = a[i][j];
		}
	}

	return true;
}