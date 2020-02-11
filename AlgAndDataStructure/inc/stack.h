#ifndef __STACK_H__
#define __STACK_H__
#pragma once

#include "common.h"

typedef void* StackElemType;

class stack
{
public:
	//stack():top(0), stack_size(0), base(NULL) {};
	explicit stack(int size = 5);
	~stack();

	bool stack_empty();
	bool stack_full();

	StackElemType pop();
	void push(StackElemType elem);
	StackElemType get_top();

private:
	StackElemType *base;
	int      stack_size;
	int      top;
};


#endif
