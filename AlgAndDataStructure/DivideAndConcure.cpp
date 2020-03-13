#include "common.h"

/*
 *�㷨������
 *    ���������е����ʣ�������������ǰһ������������л����Ǻ�벿�ֵ����������У�����
 *    ���������п�Խǰ�벿�ͺ�벿��
 *    1.�ҳ���벿�����������
 *    2.�ҳ��Ұ벿�����������
 *    3.�ҳ������м�Ԫ�ص����������
 *    �������������������о���ԭʼ���е����������У���벿/�Ұ벿�ķ������������еķ���һ�£�������Եݹ�/�����㷨
 *
 */

static int find_max_sum_accross_sequence(int num_array[], int start, int end, int record_index[2])
{
	int sum_max = 0, temp = 0;
	int mid = 0, low = 0, high = 0;
	int i = 0;

	/*
	 *���м�Ԫ�ؿ�ʼ����Ѱ�Ұ����м�Ԫ�ص���������к�
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
	 *�������м�Ԫ�ؿ�ʼ����Ѱ�Ұ�����������������
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

	//ֻ��һ��Ԫ�ص�������ݹ����
	if (start == end)
	{
		record_index[0] = start;
		record_index[1] = end;
		return num_array[start];
	}

	mid = (start + end) >> 1;

	//�ݹ������벿
	left_sum_max = find_max_sum_subsequence(num_array, start, mid, left_record);

	//�ݹ�����Ұ벿
	right_sum_max = find_max_sum_subsequence(num_array, mid + 1, end, right_record);

	//�ҳ������м�Ԫ�ص��������
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