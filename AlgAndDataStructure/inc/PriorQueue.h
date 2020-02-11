#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__
#pragma once

#include "binary_heap.h"

typedef enum {
	MAX_HIGH_PRIOR_QUEUE,
	MIN_SMALL_PRIOR_QUEUE
}prio_queue_type;

class PriorityQueue : public BinaryHeap
{
public:
	PriorityQueue();
	PriorityQueue(int array[], int len, prio_queue_type type = MAX_HIGH_PRIOR_QUEUE);
	explicit PriorityQueue(const vector<int>& vec, prio_queue_type type = MIN_SMALL_PRIOR_QUEUE);
	~PriorityQueue();
	int getMaxPriority();
	int getMinPriority();
	int extractMaxPriorityFromPriorQueue();
	void PrioirityQueueInsertion(int prio);
	void PriorityQueueDelete(int node);
	void PriorityQueueIncreasePriority(int node, int new_high_pro);

private:
	prio_queue_type queue_type;
};

inline bheap_mode queue_type_to_heap_mode (prio_queue_type type) 
{
	return (type == MAX_HIGH_PRIOR_QUEUE) ? MAX_BINARY_HEAP : MIN_BINARY_HEAP;
}

#endif
