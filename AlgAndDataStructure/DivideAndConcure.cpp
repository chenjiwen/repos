#include "common.h"

/*
 *算法描述：
 *    最大和子序列的性质：最大和子序列是前一半的最大和子序列或者是后半部分的最大和子序列，或者
 *    最大和子序列跨越前半部和后半部。
 *    1.找出左半部的最大子序列
 *    2.找出右半部的最大子序列
 *    3.找出包含中间元素的最大子序列
 *    这三个当中最大的子序列就是原始序列的最大和子序列，左半部/右半部的方法与整个序列的方法一致，因而可以递归/分治算法
 *
 */

static int find_max_sum_accross_sequence(int num_array[], int start, int end, int record_index[2])
{
	int sum_max = 0, temp = 0;
	int mid = 0, low = 0, high = 0;
	int i = 0;

	/*
	 *从中间元素开始往右寻找包含中间元素的最大子序列和
	 */
	mid = (start + end) >> 1;
	sum_max = num_array[mid];
	temp = sum_max;
	high = mid;
	for (i = mid + 1; i <= end; i++)
	{
		temp += num_array[i];
		if (sum_max < temp)
		{
			sum_max = temp;
			high = i;
		}
	}

	/*
	 *继续从中间元素开始往左寻找包含它的最大和子序列
	 */
	low = mid;
	temp = sum_max;
	for (i = mid - 1; i >=0; i--)
	{
		temp += num_array[i];
		if (sum_max < temp)
		{
			sum_max = temp;
			low = i;
		}
	}

	record_index[0] = low;
	record_index[1] = high;
	return sum_max;
}

int find_max_sum_subsequence(int num_array[], int start, int end, int record_index[2])
{
	int left_sum_max = 0;
	int right_sum_max = 0;
	int sum_accross_max = 0;
	int mid = 0;
	int left_record[2];
	int right_record[2];
	int accross_record[2];

	//只有一个元素的情况，递归结束
	if (start == end)
	{
		record_index[0] = start;
		record_index[1] = end;
		return num_array[start];
	}

	mid = (start + end) >> 1;

	//递归调用左半部
	left_sum_max = find_max_sum_subsequence(num_array, start, mid, left_record);

	//递归调用右半部
	right_sum_max = find_max_sum_subsequence(num_array, mid + 1, end, right_record);

	//找出包含中间元素的最大序列
	sum_accross_max = find_max_sum_accross_sequence(num_array, start, end, accross_record);

	if (left_sum_max >= right_sum_max && left_sum_max >= sum_accross_max)
	{
		record_index[0] = left_record[0];
		record_index[1] = left_record[1];
		return left_sum_max;
	} 
	else if(right_sum_max >= left_sum_max && right_sum_max >= sum_accross_max)
	{
		record_index[0] = right_record[0];
		record_index[1] = right_record[1];
		return right_sum_max;
	}
	else
	{
		record_index[0] = accross_record[0];
		record_index[1] = accross_record[1];
		return sum_accross_max;
	}

}

void ComplexNumMultple(double a, double b, double c, double d)
{
	double x = 0, y = 0, z = 0;
	double real = 0, img = 0;

	x = (a - b) * (c + d);
	y = (a + b) * (c - d);
	z = (a + b) * (c + d);

	/*
	 *  (a+bi)*(c+di)=(ac - bd) + (ad + bc)i
	 *   ac - bd = (a - b)*(c + d) - (ad - bc) = x - (y - z)/2
	 *   ad + bc = (a + b)*(c + d) - (ac + bd) = x - (y + z)/2
	 *
	 *   x = (a - b)*(c + d) = ac + ad - bc - bd
	 *   y = (a + b)*(c + d) = ac + ad - bc + bd
	 *   z = (a + b)*(c - d) = ac - ad + bc - bd
	 *   ad - bc = (y - z)/2 = (y - z) >> 1
	 *   ac + bd = (y + z)/2 = (y + z) >> 1
	 */

	real = x - ((y - z)/2);
	img  = x - ((y + z)/2);
}

int maxSubSeq(int array[], int i, int j)
{
	int maxSubSum = 0;
	int sum = 0;
	int idx = 0;

	if (i == j)
	{
		return array[i];
	}

	for (idx = j - 1; idx >= i; idx--)
	{
		sum += array[idx];
		if (maxSubSum < sum)
		{
			maxSubSum = sum;
		}
	}

	maxSubSum += array[j];

	return max(maxSubSeq(array, i, j - 1), maxSubSum);
}