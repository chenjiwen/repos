#include <iostream>
#include <string>
#include "sort.h"
using namespace std;

int main(int argc, char **argv) {
	uint32_t array_a[5] = {2, 3, 5, 4, 1};
	uint32_t array_b[5] = {7, 8, 6, 10, 9};
	//uint32_t array[10];
	int idx = 0;
	int num_array[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int record[2];
	int max_subseq_sum = 0;

	//bubble_sort(5, array);
	//insertion_sort(5, array);
	//bubble_sort(5, array_a);
	//insertion_sort(5, array_b);
	//merge_sorted(array, 5, array_a, 5, array_b);
	//merge_sort(5, array_a);
	//merge_sort(5, array_b);

	//quick_sort(0, 4, array_a);

	selecion_sort(5, array_a);

	max_subseq_sum = find_max_sum_subsequence(num_array, 0, 15, record);

	cout << "max sum of subsequence is " << max_subseq_sum << ", from: " << record[0] << " to " << record[1] << endl;

	cout << "sorted array:" << endl;
	for (idx = 0; idx < sizeof(array_a)/sizeof(array_a[0]); idx++)
	{
		cout << array_a[idx] << " ";
	}
	cout << endl;


	return 0;
}