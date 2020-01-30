
#ifndef __SORT_H__
#define __SORT_H__

#include <cstdint>


extern void bubble_sort(int len,  uint32_t array[]);
extern void insertion_sort(int len, uint32_t array[]);
extern void merge_sorted(uint32_t array[], int len_a, uint32_t array_a[], int len_b, uint32_t array_b[]);
extern void merge_sort(int array_len, uint32_t array[]);
extern void quick_sort(int left, int right, uint32_t array[]);
extern void selecion_sort(int len, uint32_t array[]);

#endif /*__SORT_H__*/