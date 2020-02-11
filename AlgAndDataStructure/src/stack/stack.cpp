#include "stack.h"
#include <string.h>

stack::~stack() {
	if (!base)
	{
		delete[]base;
	}
}

stack::stack(int size):top(0),stack_size(size),base(NULL) {
	if (!size)
	{
		base = new StackElemType[size];
		if (!base)
		{
			stack_size = 0;
			return;
		}
		memset(base, 0, size * (sizeof(StackElemType)));
	}
}

bool stack::stack_empty() {
	return !base || !top;
}

bool stack::stack_full() {
	return top == stack_size - 1;
}

/*
 *调用者保证push之前栈不满
 */
void stack::push(StackElemType elem) {
	base[top++] = elem;
}

/*
 *调用者保证pop之前栈非空
 */
StackElemType stack::pop() {
	return base[top--];
}

/*
 *调用者保证get_top之前栈非空
 */
StackElemType stack::get_top() {
	return base[top];
}