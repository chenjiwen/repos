
#ifndef __SORT_H__
#define __SORT_H__

#include <cstdint>
#include <string>
using namespace std;
#include "binary_heap.h"

extern void bubble_sort(int len,  uint32_t array[]);
extern void insertion_sort(int len, uint32_t array[]);
extern void merge_sorted(uint32_t array[], int len_a, uint32_t array_a[], int len_b, uint32_t array_b[]);
extern void merge_sort(int array_len, uint32_t array[]);
extern void quick_sort(int left, int right, uint32_t array[]);
extern void selecion_sort(int len, uint32_t array[]);
extern int find_max_sum_subsequence(int num_array[], int start, int end, int record_index[2]);
extern uint32_t select_kth(int k, int left, int right, uint32_t array[]);
extern int select_kth_with_heap(uint32_t k);
extern int maxSubSeq(int array[], int i, int j);

extern string longestPalindrome(string s);

#endif /*__SORT_H__*/