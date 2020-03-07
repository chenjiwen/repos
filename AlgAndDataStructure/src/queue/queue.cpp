#include "common.h"
#include "queue.h"

LinearQue::LinearQue(int depth):QueDepth(depth), base(NULL)
{
	base = new QueElemType[QueDepth];
	head = 0;
	tail = 0;
}

LinearQue::~LinearQue()
{
	delete []base;
}

bool LinearQue::QueEmpty()
{
	return head == tail;
}

bool LinearQue::QueFull()
{
	return head == (tail + 1) % QueDepth;
}

void LinearQue::Enqueue(QueElemType elem) 
{
	base[tail] = elem;
	tail = (tail + 1) % QueDepth;
}

QueElemType LinearQue::Dequeue()
{
	int idx = head;
	head = (head + 1) % QueDepth;
	return base[idx];
}