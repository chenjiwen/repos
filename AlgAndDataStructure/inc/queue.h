#ifndef __QUEUE_H__
#define __QUEUE_H__
#pragma once

typedef void* QueElemType;

class LinearQue
{
public:
	LinearQue(int QueDepth = 100);
	~LinearQue();
	void Enqueue(QueElemType);
	QueElemType Dequeue();
	bool QueEmpty();
	bool QueFull();


private:
	QueElemType* base;
	int          head;
	int          tail;
	int          QueDepth;
};

#endif