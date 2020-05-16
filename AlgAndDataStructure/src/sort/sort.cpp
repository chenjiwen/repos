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
    //ѭ��len��ð��
    for (j = len - 1; j > 0; j--)
    {
        //ÿ��ð�ݵ�ʱ����Ҫ����/�ȽϵĴ���j
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
 *�ϲ������������飺
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
 *���������еĻ����㷨��
 *    ���ְ�����ֳ��������֣�ǰ�벿��С�ڸ�����Ԫ�أ���벿�ֲ�С�ڸ�����Ԫ�أ��ú���ͬʱ���ظ���Ԫ���ڱ��ڻ����е�λ��.
 *    ��ͷ���У��Ѳ�С�ڸ����ڱ�Ԫ�ؽ�����β����
 *    ��β���У���С�ڸ����ڱ�Ԫ�ؽ�����ͷ��
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

    //�ڱ�����ѡȡ����λ��
    sentential_idx = mid;
    sentential = array[sentential_idx];

    for (idx = left_idx; idx < right_idx; )
    {   //�ҳ���벿��С�ڸ����ڱ���Ԫ��
        if (array[idx] < sentential)
        {
            idx++;
            //��ǰ��벿��Ԫ��С�ڸ�����Ԫ�أ�������
            continue;
        }
        else
        {
            //��ǰ��ͷ��Ԫ�ز�С���ڱ�Ԫ�أ���β���ҳ�β��С�ڸ���Ԫ�ص�λ��
            while ((right_idx > idx) && (array[right_idx] >= sentential))
                right_idx--;
            if (sentential == array[right_idx])
                sentential_idx = right_idx;
            //�ҵ���һ��С���ڱ���Ԫ�أ���ǰ�벿��С���ڱ�Ԫ�ؽ���
			if (right_idx != idx)
			{
				temp = array[right_idx];
				array[right_idx] = array[idx];
				array[idx] = temp;
			}

            //���idx == right_idx�����������ǰԪ�����ڱ����,�˳�ѭ����ֱ�ӷ��ص�ǰλ��
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

    //i ���ڱ��浱ǰС��pivot_element = array[right_idx]��λ��
    i = left_idx - 1;//��ʼλ��Ϊleft - 1
    pivot_element = array[right_idx];

    //j ���ڵ�������С��pivot element�����ҵ���array[i+1]<->array[j]
    for (j = left_idx; j <= right_idx - 1; j++)
    {
        //��ǰ��Ԫ��С��pivot��������i + 1��λ��
        if (array[j] <= pivot_element)
        {
            i++;
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    } 

    //iΪС��pivot�ĵ�ǰλ�ã� i ��rihgt_idx���Ǵ��ڵ���pivot��i + 1λ��������pivot����
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


//�ҳ�һ�������ĵ�kС����
//
// k:     ��Ҫ���صĵ�k���Ԫ��
// left:  �������С�±�
// right: ���������±�
//

uint32_t select_kth(int k, int left, int right, uint32_t array[]) {
    
    int i = 0;

    //���ڵ�k���Ԫ�أ��ڴ�С����������е�λ��Ϊ��right - left + 1 - k;
    k = right - left + 1 - k;

    do 
    {
        i = quick_sort_partition(left, right,(int*) array);

        //���ֵ�λ��С��k����˵����ǰ���ص�λ�õ�Ԫ��С�ڵ�k���Ԫ��
        //�ӵ�ǰλ���������Ѱ��
        if (i < k)
        {
            left = i + 1;
        }
        else if (i > k)
        {
            //��ǰ��λ�ñ�k����Ҫ�ӿ�ʼ����ǰλ�ü���Ѱ��
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
	//������Ȼ����һ����ά����    
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
    //i_row���ڼ�¼row
    //j_col���ڼ�¼col
    //������һ����ͬ��Ԫ�ص�ʱ�򣬷ŵ���һ��
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
            //�ѵ�ǰ����λ�ü�¼��row idx������
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
            //�ҵ����У����д�idx����ȡ����
            cur_col = idx[cur_row];
            a[cur_row][cur_col] = nums[m];
            cur_col++;
            idx[cur_row] = cur_col;
        }
        else
        {
            cur_col = idx[cur_row];
			//�����ǰ�����Ѿ���������һ�����ʵ���
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
			//ż����
			if (vec1.size() % 2 == 0)
			{
				mid1_1 = (vec1.size() >> 1) - 1;

			}
			else
			{
				mid1_1 = vec1.size() >> 1;
			}
            //vec1 �ֳ�������: vec1[0]....vec1[mid1_1](��ΪA), vec1[mid1_1 + 1]...vec1[size](��ΪB)
            //vec2 �ֳ�������: vec2[0]....vec2[mid2_1](��ΪC), vec2[mid2_1 + 1]...vec2[size](��ΪD)
            //��λ��һ����[B U C]����[D U A]��???

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
	int pivot = nums[end];//���һ��Ԫ����Ϊ��Ԫ

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
 *��һ������������Ȼ��ֳɴ�С��ͬ�������飬�����鳤����ͬΪK
 *�����鰴��������
 *
 *[1,2,2,3,3,4,4,5]->
 *
 *[1,2,3,4]
 *[2,3,4,5]
 */
bool isPossibleDivide(vector<int>& nums, int k) {
	//������Ȼ����һ����ά����    
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
			//�ѵ�ǰ����λ�ü�¼��row idx������
			idx[cur_row] = cur_col;
			i_row = cur_row;
			cur_row = 0;
			while (1)
			{
				if (idx[cur_row] != col)
				{
                    //��û���������
					if (i_row == cur_row)
					{
                        //��Ҫ�ų���ǰ��
						cur_row++;
						cur_row %= row;
						continue;
					}
					else if (idx[cur_row] && (a[cur_row][idx[cur_row] - 1] == nums[m]))
					{
                        //������е����һ��Ԫ���뵱ǰԪ����ͬҲ��Ҫ�ų�
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
			//�ҵ����У����д�idx����ȡ����
			cur_col = idx[cur_row];
			a[cur_row][cur_col] = nums[m];
			cur_col++;
			idx[cur_row] = cur_col;
		}
		else
		{
			cur_col = idx[cur_row];
			//�����ǰ�����Ѿ���������һ�����ʵ���
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