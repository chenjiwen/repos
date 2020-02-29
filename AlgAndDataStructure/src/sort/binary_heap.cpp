#include "binary_heap.h"
#include <iostream>
#include <iomanip>

//构造函数初始化式
BinaryHeap::BinaryHeap(int array[], int vlen, bool sort, bheap_mode mode):
	vec_len(vlen + 1),heap_size(vlen),vec(vec_len,0),sorted(sort),heap_mode(mode)
{
	vector<int>::size_type idx = 0;
	for (idx = 1; idx < vec_len; idx++)
	{
		vec[idx] = array[idx - 1];
	}

	switch (heap_mode)
	{
	case MAX_BINARY_HEAP:
		build_max_heap();
		break;
	case  MIN_BINARY_HEAP:
		build_min_heap();
		break;
	default:
		break;
	}

	if (sort) 
	{
		heap_sort();
	}

	cout << "BinaryHeap(int array[], int vlen, bool sort)" << endl;
}

BinaryHeap::BinaryHeap(const vector<int> &vect, bool sort, bheap_mode hp_mode): 
	vec_len(vect.size() + 1),heap_size(0),vec(vec_len, 0), sorted(sort),heap_mode(hp_mode)
{
	vector<int>::size_type idx = 0;
	for (idx = 1; idx < vec_len; idx++)
	{
		vec[idx] = vect[idx - 1];
	}
	switch (hp_mode)
	{
	case MAX_BINARY_HEAP:
		build_max_heap();
		break;
	case  MIN_BINARY_HEAP:
		build_min_heap();
		break;
	default:
		break;
	}
	
	if (sort)
	{
		heap_sort();
	}

	cout << "BinaryHeap(const vector<int> &vect, bool sort)" << endl;
}

BinaryHeap::BinaryHeap(bheap_mode mode):vec_len(0), heap_size(0), sorted(false), heap_mode(mode) {
	vec_len = 1;
	vec.push_back(0);
	cout << "BinaryHeap()" << endl;
}

BinaryHeap::~BinaryHeap()
{
	cout << "~BinaryHeap()" << endl;
}

void BinaryHeap::build_max_heap() {
	vector<int>::size_type idx = 0;
	heap_size = vec_len - 1;
	for (idx = heap_size >> 1; idx >= 1; idx--)
	{
		max_heapify(idx);
	}
}

void BinaryHeap::max_heapify(vector<int>::size_type node_id, int recursive) {
	vector<int>::size_type left_node = 0, right_node = 0, largest_node = 0;

	//迭代到叶子节点结束
	while (node_id <= (heap_size >> 1))
	{
		left_node = left_child(node_id);
		right_node = right_child(node_id);


		if ((left_node <= heap_size) && (vec[left_node] > vec[node_id]))
		{
			largest_node = left_node;
		}
		else
		{
			largest_node = node_id;
		}

		if ((right_node <= heap_size) && (vec[largest_node] < vec[right_node]))
		{
			largest_node = right_node;
		}

		if (largest_node != node_id)
		{
			int temp;
			temp = vec[largest_node];
			vec[largest_node] = vec[node_id];
			vec[node_id] = temp;
			node_id = largest_node;
		}
	}

}

void BinaryHeap::max_heapify(vector<int>::size_type node_id) {
	vector<int>::size_type left_node = 0, right_node = 0, largest_node = 0;

	left_node = left_child(node_id);
	right_node = right_child(node_id);

	if ((left_node <= heap_size) && (vec[left_node] > vec[node_id]))
	{
		largest_node = left_node;
	}
	else
	{
		largest_node = node_id;
	}

	if ((right_node <= heap_size) && (vec[largest_node] < vec[right_node]))
	{
		largest_node = right_node;
	} 

	if (largest_node != node_id)
	{
		int temp;
		temp = vec[largest_node];
		vec[largest_node] = vec[node_id];
		vec[node_id] = temp;
		//继续递归调用孩子节点
		max_heapify(largest_node);
	}
}


void BinaryHeap::heap_sort() {
	vector<int>::size_type idx = 0;

	for (idx = heap_size; idx >=2; idx--)
	{
		swap(vec[1], vec[idx]);
		heap_size--;
		max_heapify(1);
	}
}

void BinaryHeap::dump_heap() {
	vector<int>::size_type idx = 0;

	for (idx = 1; idx < vec_len; idx++)
	{
		cout << setw(4) << vec[idx];
		if (idx % 5 == 0)
		{
			cout << endl;
		}
	}
}

vector<int>& BinaryHeap::getHeapContent(vector<int>::size_type& heapSize) {
	heapSize = heap_size;
	return vec;
}

vector<int>& BinaryHeap::getHeapContent() {
	return vec;
}

vector<int>::size_type BinaryHeap::getHeapSize() {
	return heap_size;
}

int BinaryHeap::getHeapMax() {
	if (!heap_sorted() && (getHeapSize() >= 1) && (heap_mode == MAX_BINARY_HEAP))
	{
		return vec[1];
	}
	return 0xdeadbeef;
}

int BinaryHeap::extractMaxFromHeap() {
	int max = -1;

	max = getHeapMax();
	if (max == 0xdeadbeef)
	{
		return 0xdeadbeef;
	}

	vec[1] = vec[heap_size];
	heap_size--;
	max_heapify(1);
	return max;
}

void BinaryHeap::heap_increase_key(int node, int key) {
	if (key < vec[node]) {
		return;
	}

	vec[node] = key;
	while ((node > 1) && (vec[parent(node)] < vec[node]))
	{
		swap(vec[parent(node)], vec[node]);
		node = parent(node);
	}
}

void BinaryHeap::heap_insert(int key) {
	heap_size++;
	vec.push_back(0x8000001);
	heap_increase_key(heap_size, key);
}

void BinaryHeap::heap_delete(vector<int>::size_type node) {
	if (sorted || !heap_size || node > heap_size)
	{
		return;
	}

	swap(vec[node], vec[heap_size]);
	vec.pop_back();
	heap_size--;
	vec_len--;
	max_heapify(node);
}

/*
 *最小堆性质：
 *    A[parent(i)] <= A[i]
 *    最小元素存储在A[1]
 */
void BinaryHeap::min_heapify(vector<int>::size_type idx) {
	vector<int>::size_type left_node = 0, right_node = 0, smallest_node = 0;

	left_node = left_child(idx);
	right_node = right_child(idx);

	if ((left_node <= heap_size) && (vec[left_node] < vec[idx]))
	{
		smallest_node = left_node;
	}
	else
	{
		smallest_node = idx;
	}

	if ((right_node <= heap_size) && (vec[right_node] < vec[smallest_node]))
	{
		smallest_node = right_node;
	}

	if (smallest_node != idx)
	{
		swap(vec[smallest_node], vec[idx]);
		min_heapify(smallest_node);
	}
}

void BinaryHeap::build_min_heap() {
	vector<int>::size_type node_idx = 0;

	heap_size = vec_len - 1;
	for (node_idx = heap_size >> 1; node_idx >= 1; node_idx--)
	{
		min_heapify(node_idx);
	}
}

//降序排列
void BinaryHeap::min_heap_sort() {
	bheap_idx_type node_idx = 0;

	for (node_idx = heap_size; node_idx > 1; node_idx--)
	{
		swap(vec[1], vec[heap_size]);
		heap_size--;
		min_heapify(1);
	}
}

void BinaryHeap::min_heap_insert(int key) {
	vector<int>::size_type node = 0;
	vec.push_back(key);
	heap_size++;
	vec_len++;

	node = heap_size;
	while (node > 1 && vec[parent(node)] > vec[node])
	{
		swap(vec[node], vec[parent(node)]);
		node = parent(node);
	}
}

void BinaryHeap::min_heap_delete(vector<int>::size_type node) {
	if (sorted || !heap_size || node > heap_size)
	{
		return;
	}

	swap(vec[node], vec[heap_size]);
	vec.pop_back();
	heap_size--;
	vec_len--;
	min_heapify(node);
}

int BinaryHeap::getMinFromMinHeap() {
	if (heap_size == 0)
	{
		return -1;
	}

	return vec[1];
}