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

DLinkList::DLinkList() {
	prev = NULL;
	next = NULL;
}

LinkList::LinkList(LinkListEmemType elem, bool circle):circle_list(circle) {
	if (!circle)
	{
		next = NULL;
	}
	else
	{
		next = this;
	}
	
	this->elem = elem;
}

void list_add(struct DLinkList* pToAdd, struct DLinkList* pNode) {
	pToAdd->next = pNode;
	pToAdd->prev = pNode->prev;
	pNode->prev->next = pToAdd;
	pNode->prev  = pToAdd;
}

void list_add(LinkList_T* &pList, LinkListEmemType elem) {
	LinkList_T* p = NULL, *q = NULL;

	p = new LinkList_T(elem);
	if (!pList)
	{
		pList = p;
		return;
	}

	q = pList;

	while (q->next)
	{
		q = q->next;
	}

	list_add(p, q);
}

void circle_list_add(LinkList_T*& pList, LinkListEmemType elem)
{
	LinkList_T* p = NULL, * q = NULL;

	p = new LinkList_T(elem, true);
	if (!pList)
	{
		pList = p;
		return;
	}

	q = pList;

	while (q->next != pList)
	{
		q = q->next;
	}

	list_add(p, q);
}



void list_add(struct LinkList* pToAdd, struct LinkList* pNode) {
	pToAdd->next = pNode->next;
	pNode->next = pToAdd;
}

void list_del(struct LinkList *pList, struct LinkList* pToDel) {
	LinkList_T* p = pList;
	while (p->next != pToDel)
	{
		p = p->next;
	}

	p->next = pToDel->next;
	pToDel->next = NULL;
}

struct LinkList* list_reverse(struct LinkList* pList, LinkList_T** pListR) {
	LinkList_T* p = NULL;

	if (!pList->next)
	{
		*pListR = pList;
		return pList;
	}

	p = list_reverse(pList->next, pListR);
	pList->next = NULL;
	p->next = pList;
	return pList;
}


LinkList_T* list_intersection(LinkList_T* pList1, LinkList_T* pList2) {
	LinkList_T* p = NULL;
	LinkList_T* q = NULL;
	LinkList_T* t = NULL;
	LinkList_T* list = NULL, *L = NULL;
	LinkList_T* prev = NULL;

	p = pList1;
	q = pList2;

	while (p && q)
	{
		if (p->elem == q->elem)
		{
			if (prev && prev->elem == p->elem)
			{
				p = p->next;
				q = q->next;
				continue;
			}
			t = new LinkList_T();
			t->elem = p->elem;
			if (!list)
			{
				list = t;
				L = list;
			}
			else
			{
				list->next = t;
				list = t;
			}

			p = p->next;
			q = q->next;
			prev = t;
		}
		else if (p->elem < q->elem)
		{
			p = p->next;
		}
		else
		{
			q = q->next;
		}
	}

	return L;
}

LinkList_T* list_union(LinkList_T* pList1, LinkList_T* pList2) {
	LinkList_T *p = NULL, *q = NULL, *r = NULL, *t = NULL, *L = NULL;

	p = pList1;
	q = pList2;
	while (p || q)
	{
		if (p && q)
		{
			//p 和 q非空，当前元素小的排在前面
			if (p->elem < q->elem)
			{
				if (r && p->elem == r->elem)
				{
					p = p->next;
					continue;
				}
				t = new LinkList_T(p->elem);
				p = p->next;
			}
			else if (p->elem > q->elem)
			{
				if (r && q->elem == r->elem)
				{
					q = q->next;
					continue;
				}
				t = new LinkList_T(q->elem);
				q = q->next;
			}
			else
			{
				p = p->next;
				continue;
			}
		}
		else if (p)
		{
			if (r && p->elem == r->elem)
			{
				p = p->next;
				continue;
			}
			t = new LinkList_T(p->elem);
			p = p->next;
		}
		else if (q)
		{
			if (r && q->elem == r->elem)
			{
				q = q->next;
				continue;
			}
			t = new LinkList_T(q->elem);
			q = q->next;
		}
		if (!L)
		{
			L = t;
			r = t;
		}
		else
		{
			r->next = t;
			r = t;
		}
	}
	return L;
}


/*
 * 
 *
 */

#if 1
void list_reverse(struct LinkList* &pList) {

	LinkList_T* p, * q;

	if (!pList)
		return;

	p = pList->next;
	pList->next = NULL;
	while (p)
	{
		q = p->next;
		p->next = pList;
		pList = p;
		p = q;
	}
}
#else
void list_reverse(struct LinkList* &pList) {
	LinkList_T* p1 = NULL, * p2 = NULL, * p3 = NULL;

	if (!pList)
	{
		return;
	}

	p1 = NULL;
	p2 = pList;
	while (p2)
	{
		p3 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}

	pList = p1;
}
#endif

void list_del(struct DLinkList* pToDel) {

}

LinkList_T* list_search(LinkList_T* pList, LinkListEmemType elem) {
	while (pList && pList->elem != elem)
	{
		pList = pList->next;
	}

	return pList;
}


LinkList_T* list_reverse(LinkList_T*& pList, LinkList_T* pList_end)
{

	LinkList_T* p, * q;
	LinkList_T* head;
	LinkList_T* ptemp = pList_end->next;

	if (!pList)
		return NULL;

	head = pList;
	p = pList->next;
	pList->next = NULL;
	while (p != ptemp)
	{
		q = p->next;
		p->next = pList;
		pList = p;
		p = q;
	}
	return head;
}

LinkList_T* reverseKGroup(LinkList_T* head, int k) {
	int step = 0;
	LinkList_T* l_start = NULL, * l_end = NULL, * ptmp = NULL;
	LinkList_T* prev_end = NULL, * cur_end = NULL;
	LinkList_T* ptemp = NULL;

	ptmp = head;
	prev_end = NULL;

	if (!head || !head->next)
	{
		return head;
	}

	while (ptmp) {
		step = 0;

		//start记录要reverse的其实位置/end记录要reverse的结束位置
		l_start = ptmp;
		l_end = l_start;
		while (step < k - 1) {
			l_end = l_end->next;
			ptmp = ptmp->next;
			if (!ptmp)
				break;
			step++;
		}

		if (step < k - 1)
		{
			cur_end->next = ptemp;
			break;
		}

		//记录下一次要reverse的位置
		ptmp = ptmp->next;

		ptemp = l_end->next;
		l_end->next = NULL;
		
		cur_end = list_reverse(l_start, l_end);
		if (prev_end == NULL)
		{
			prev_end = cur_end;
			head = l_start;
		}
		else
		{
			prev_end->next = l_start;
			prev_end = cur_end;
		}
	}

	return head;
}