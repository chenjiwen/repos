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
 *�����߱�֤push֮ǰջ����
 */
void stack::push(StackElemType elem) {
	base[top++] = elem;
}

/*
 *�����߱�֤pop֮ǰջ�ǿ�
 */
StackElemType stack::pop() {
	return base[top--];
}

/*
 *�����߱�֤get_top֮ǰջ�ǿ�
 */
StackElemType stack::get_top() {
	return base[top];
}