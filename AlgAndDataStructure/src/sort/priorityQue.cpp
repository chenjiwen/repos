#include "PriorQueue.h"
#include <iostream>



PriorityQueue::PriorityQueue(const vector<int>& vec, prio_queue_type type):
	queue_type(type), BinaryHeap(vec, false, queue_type_to_heap_mode(type))
{
	cout << "Derived class constructor:PriorityQueue(const vector<int>& vec)" << endl;
}

PriorityQueue::PriorityQueue(int array[], int len, prio_queue_type type)
	:BinaryHeap(array, len, false, queue_type_to_heap_mode(type)),queue_type(type)
{
	cout << "Derived class constructor:PriorityQueue(int array[], int len)" << endl;
}

PriorityQueue::PriorityQueue():queue_type(MAX_HIGH_PRIOR_QUEUE)
{
	cout << "Derived class constructor:PriorityQueue()" << endl;
}

PriorityQueue::~PriorityQueue()
{
	cout << "Derived class desconstructor:~PriorityQueue()" << endl;
}

int  PriorityQueue::getMaxPriority() {
	return getHeapMax();
}

int PriorityQueue::extractMaxPriorityFromPriorQueue() {
	return extractMaxFromHeap();
}

void PriorityQueue::PrioirityQueueInsertion(int prio) {
	heap_insert(prio);
}

void PriorityQueue::PriorityQueueIncreasePriority(int node, int new_high_pro) {
	heap_increase_key(node, new_high_pro);
}

void PriorityQueue::PriorityQueueDelete(int node) {
	heap_delete(node);
}