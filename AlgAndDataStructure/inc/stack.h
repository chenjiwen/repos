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

typedef struct DLinkList 
{
	struct DLinkList* prev;
	struct DLinkList* next;
	DLinkList();
}DLinkList_T;

typedef int LinkListEmemType;

typedef struct llist 
{
	struct llist* next;
	llist():next(NULL){}
}llist_t;

typedef struct dlist {
	struct dlist* prev;
	struct dlist* next;
	dlist()
	{
		prev = this;
		next = this;
	}
}dlist_t, *pdlist_t;

typedef llist_t* pllist_t;

typedef struct LinkList
{
	struct LinkList* next;
	LinkListEmemType elem;
	explicit LinkList(LinkListEmemType elem = -1, bool circle = false);
	bool circle_list;
}LinkList_T;

typedef int QueueElemType;

const int que_len = 5;

typedef struct LinearQueue
{
	QueueElemType queue_fifo[que_len];
	int head;
	int tail;
	int que_size;

}LinearQueue_t;

#define CURSOR_STACK_SIZE (10 + 1)
#define CURSOR_STACK_NUM 3

typedef int PtrToNode;
typedef PtrToNode PositionT;
struct StackNode {
	StackElemType elem;
	PositionT     next;
};



class CursorStack
{
public:
	CursorStack();
	~CursorStack();
	void push(StackElemType elem, int sid);
	StackElemType top(int sid);
	bool empty(int sid);
	void pop(int sid);

protected:
	PositionT CursorStackAlloc();
	void CursorStackFree(PositionT);

private:
	struct StackNode base[CURSOR_STACK_SIZE];
	int stack_size;
	PositionT sbase[CURSOR_STACK_NUM];//stack base, record the base of each stack
	//PositionT top[CURSOR_STACK_NUM];

};


void list_add(LinkList_T*& pList, LinkListEmemType elem);
void list_add(struct DLinkList* pToAdd, struct DLinkList* pNode);
void list_add(struct LinkList* pToAdd, struct LinkList* pNode);
struct LinkList* list_reverse(struct LinkList* pList, LinkList_T** pListR);
//void list_reverse(struct LinkList* pList);
void list_reverse(struct LinkList*& pList);
void list_del(struct DLinkList* pToDel);
LinkList_T* list_intersection(LinkList_T* pList1, LinkList_T* pList2);
LinkList_T* list_union(LinkList_T* pList1, LinkList_T* pList2);
LinkList_T* list_search(LinkList_T* pList, LinkListEmemType elem);
void circle_list_add(LinkList_T*& pList, LinkListEmemType elem);
void llist_add(llist_t *prev, llist_t* pnode);
void dlist_add(dlist_t *prev, dlist_t* pnode);
void dlist_add_before(dlist_t* cur, dlist_t* pnode);
void dlist_del(dlist_t* pnode);
bool dlist_empty(dlist_t *pDlist);

void dlist_concate(dlist_t* pDlist1, dlist_t* pDlist2);

#endif
