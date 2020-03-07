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

FibHeap::FibHeap():minNode(NULL), NodeNum(0) {
}

FibHeap::~FibHeap() {
	FibHeapDestroy();
}

void FibHeap::FibHeapInsert(FibHeapNode* pNode) {
	pNode->degree = 0;
	pNode->child = NULL;
	pNode->marked = false;

	if (!minNode)
	{
		minNode = pNode;
		dlist_add(&rootlist, &pNode->list);
	}
	else
	{
		dlist_add_before(&minNode->list, &pNode->list);
		if (pNode->key < minNode->key)
		{
			minNode = pNode;
		}
	}

	NodeNum += 1;
}

void FibHeap::FibHeapInsert(FibHeapElement key, void *priv)
{
	FibHeapNode* pNode = NULL;

	pNode = new FibHeapNode;
	pNode->key = key;
	pNode->priv = priv;
	FibHeapInsert(pNode);
}

FibHeap* FibHeap::FibHeapUnion(FibHeap* pFH1, FibHeap* pFH2) 
{
	FibHeap* pFH = NULL;
	dlist_t* plist = NULL;

	pFH = new FibHeap();
	pFH->minNode = pFH1->minNode;
	pFH->NodeNum = pFH1->NodeNum;

	if (!dlist_empty(&pFH1->rootlist))
	{
		plist = pFH1->rootlist.next;
		//need delete the list head before concatenate
		dlist_del(&pFH1->rootlist);
		dlist_concate(&pFH->rootlist, plist);
	}

	if (!dlist_empty(&pFH2->rootlist))
	{
		plist = pFH2->rootlist.next;
		//need delete the list head before concatenate
		dlist_del(&pFH2->rootlist);
		dlist_concate(&pFH->rootlist, plist);
	}

	if (!pFH->minNode || (pFH1->minNode->key < pFH2->minNode->key))
	{
		pFH->minNode = pFH2->minNode;
	}

	pFH->NodeNum += pFH2->NodeNum;

	pFH1->minNode = NULL;
	pFH2->minNode = NULL;

	delete pFH1;
	delete pFH2;

	return pFH;
}

bool is2Exp(int n) {
	return n ^ (n - 1);
}

int log(int n) {
	int count = 0;
	while (n)
	{
		count++;
		n = n >> 1;
	}

	return count;
}

int FibHeap::FibHeapMaxDegNum()
{
	int n = NodeNum;
	int count = 0;

	if (!is2Exp(n))
	{
		count = 1;
	}

	while (n)
	{
		count++;
		n = n >> 1;
	}

	return count;
}


void FibHeap::FibHeapLink(FibHeapNode* pNodeY, FibHeapNode* pNodeX)
{
	dlist_del(&pNodeY->list);
	dlist_add(&pNodeX->child->list, &pNodeY->list);
	pNodeX->degree++;
	pNodeY->parent = pNodeX;
	pNodeY->marked = false;
}

void FibHeap::FibHeapConsolidate()
{
	int num = FibHeapMaxDegNum() + 1;
	FibHeapNode** table = new FibHeapNode*[num];
	int i = 0;
	FibHeapNode* pNodeW = NULL, * pNodeY = NULL, *pNodeX = NULL;
	dlist_t* plist = NULL;
	int d;

	for (i = 0; i < num; i++)
	{
		table[i] = NULL;
	}

	plist = rootlist.next;
	do
	{
		pNodeW = container_of(plist, FibHeapNode, list);
		pNodeX = pNodeW;
		d = pNodeX->degree;
		while (table[d])
		{
			pNodeY = table[d];
			if (pNodeX->key > pNodeY->key)
			{
				swap(pNodeX, pNodeY);
			}
			FibHeapLink(pNodeY, pNodeX);
			table[d] = NULL;
			d = (d + 1)%num;
		}
		table[d] = pNodeX;
		plist = plist->next;
	} while (plist != &rootlist);

	minNode = NULL;
	for (i = 0; i < num; i++)
	{
		if (table[i])
		{
			if (!minNode)
			{
				minNode = table[i];
			}
			else
			{
				dlist_add_before(&minNode->list, &table[i]->list);
			}
		}
	}

	delete[]table;
}

FibHeapNode* FibHeap::FibHeapExtractMin() 
{
	FibHeapNode* pNodeZ = NULL, *pNodeX = NULL;
	dlist_t* plist = NULL;

	pNodeZ = minNode;
	if (pNodeZ)
	{
		
		do
		{
			plist = pNodeZ->child->list.next;
			pNodeX = container_of(plist, FibHeapNode, list);
			pNodeX->parent = NULL;
			dlist_del(plist);
			dlist_add_before(&minNode->list, plist);
		} while (!dlist_empty(&pNodeZ->child->list));

		if (dlist_empty(&pNodeZ->list))
		{
			minNode = NULL;
		}
		else
		{
			pNodeX = container_of(pNodeZ->list.next, FibHeapNode, list);
			dlist_del(&pNodeZ->list);
			minNode = pNodeX;
			FibHeapConsolidate();
		}

		NodeNum--;
	}

	return pNodeZ;
}

void FibHeap::FibHeapCut(FibHeapNode* pNodeX, FibHeapNode* pNodeY)
{
	dlist_del(&pNodeX->list);
	dlist_add_before(&minNode->list, &pNodeX->list);
	pNodeX->parent = NULL;
	pNodeX->marked = false;
}

void FibHeap::FibHeapCascadingCut(FibHeapNode* pNodeY)
{
	FibHeapNode* pNodeZ = pNodeY->parent;

	if (pNodeZ)
	{
		if (pNodeY->marked)
		{
			pNodeY->marked = false;
		}
		else
		{
			FibHeapCut(pNodeY, pNodeZ);
			FibHeapCascadingCut(pNodeZ);
		}
	}
}

void FibHeap::FibHeapDecreseKey(FibHeapNode* pNodeX, FibHeapElement newKey)
{
	FibHeapNode* pNodeY = NULL;

	if (pNodeX->key >= newKey)
	{
		pNodeX->key = newKey;
		pNodeY = pNodeX->parent;

		if (pNodeY && pNodeX->key < pNodeY->key)
		{
			FibHeapCut(pNodeX, pNodeY);
			FibHeapCascadingCut(pNodeY);
		}

		if (pNodeX->key < minNode->key)
		{
			minNode = pNodeX;
		}
	}
}

void FibHeap::FibHeapDelete(FibHeapNode* pNode)
{
	FibHeapDecreseKey(pNode, INT_MIN);
	FibHeapExtractMin();
}

void FibHeap::FibHeapDestroyMinHeap(FibHeapNode* pMinHeap)
{
	dlist_t *plist = NULL;
	FibHeapNode* pNode = NULL;

	while (!dlist_empty(&pMinHeap->child->list))
	{
		plist = pMinHeap->child->list.next;
		pNode = container_of(plist, FibHeapNode, list);
		FibHeapDestroyMinHeap(pNode);
		dlist_del(plist);
	}
	dlist_del(&pMinHeap->list);
	delete pMinHeap;
}

void FibHeap::FibHeapDestroy() 
{
	pdlist_t plist = NULL;
	FibHeapNode* pNode = NULL;

	do 
	{
		plist = rootlist.next;
		pNode = container_of(plist, FibHeapNode, list);
		FibHeapDestroyMinHeap(pNode);
		dlist_del(plist);
	} while (dlist_empty(&rootlist));
}

void FibHeapTest()
{

}


BNTree::BNTree(int num):nodeNum(num), root(NULL), depth(-1) {
	if (is2Exp(nodeNum))
	{
		depth = log(nodeNum);
	}
	else
	{

	}
}

BNTreeNode* BNTree::BNTreeBuild(int k) 
{
	BNTreeNode* pNode = NULL, *pBNTNode = NULL;
	if (k == 0)
	{
		pBNTNode = new BNTreeNode;
		pBNTNode->child = NULL;
		pBNTNode->parent = NULL;
		pBNTNode->sib = NULL;
		pBNTNode->degree = 0;
		pBNTNode->key = 0;
	}
	else
	{
		BNTreeNode* pTemp = NULL, *pchild = NULL;
		int i = 0;
		pBNTNode = new BNTreeNode;
		pBNTNode->parent = NULL;
		pBNTNode->key = k;
		pBNTNode->sib = NULL;

		for (i = k - 1; i >= 0; i--)
		{
			pNode = BNTreeBuild(i);
			pNode->key = i;
			pNode->parent = pBNTNode;
			if (pTemp)
			{
				pTemp->sib = pNode;
				pTemp = pNode;
			}
			else
			{
				pchild = pNode;
				pTemp  = pNode;
			}
			
		}
		pBNTNode->child = pchild;
		pBNTNode->degree = k;
	}
	root = pBNTNode;
	return pBNTNode;
}

void BNTree::BNTTreeUion(BNTreeNode* pRBNTree, BNTreeNode* pLBNTree)
{
	pRBNTree->parent = pLBNTree;
	pRBNTree->sib = pLBNTree->child;
	pLBNTree->child = pRBNTree;
}

void BNTreeTest()
{
	BNTree bntree;

	bntree.BNTreeBuild(3);
}

BNTree::~BNTree() {

}

BNHeap::BNHeap():minNode(NULL) {

}

BNHeap::~BNHeap() {

}

void BNHeap::BNHeapInsert(BNTreeElemType key) 
{
	BNTreeNode* pNode = NULL;
	BNTreeNode* ptemp = NULL;
	dlist_t *plist = NULL;

	pNode = new BNTreeNode;
	pNode->key = key;
	pNode->parent = NULL;
	pNode->sib = NULL;
	pNode->child = NULL;
	pNode->degree = 0;

	if (!dlist_empty(&rootlist))
	{
		plist = rootlist.prev;
		ptemp = container_of(plist, BNTreeNode, list);
		dlist_add(rootlist.prev, &pNode->list);
		BNHeapScanRootlistAndUnion();
	}
	else
	{
		minNode = pNode;
		dlist_add(&rootlist, &pNode->list);
	}
}

void BNHeap::BNHeapUion(BNTreeNode* pLBNPHeap, BNTreeNode* pRBNPHeap)
{
	if (pLBNPHeap->degree != pRBNPHeap->degree)
	{
		return;
	}
	pRBNPHeap->parent = pLBNPHeap;
	pRBNPHeap->sib = pLBNPHeap->child;
	pLBNPHeap->child = pRBNPHeap;
	pLBNPHeap->degree += 1;
}

void BNHeap::BNHeapScanRootlistAndUnion()
{
#if 0
	dlist_t* plist = NULL;
	BNTreeNode* prevNode = NULL, * curNode = NULL;

	plist = rootlist.prev;
	while (plist != &rootlist)
	{
		curNode = container_of(plist, BNTreeNode, list);
		if (plist->prev == &rootlist)
		{
			if (minNode->key < curNode->key)
			{
				minNode = curNode;
			}
			break;
		}
		prevNode = container_of(plist->prev, BNTreeNode, list);

		if ((prevNode != curNode) && (curNode->degree == prevNode->degree))
		{
			if (curNode->key > prevNode->key)
			{
				plist = plist->prev;
				dlist_del(&curNode->list);
				BNHeapUion(prevNode, curNode);
				minNode = prevNode;
			}
			else
			{
				dlist_del(&prevNode->list);
				BNHeapUion(curNode, prevNode);
				plist = plist->prev;
				minNode = curNode;
			}
		}
		else
		{
			plist = plist->prev;
		}
	}
#else
	if (dlist_empty(&rootlist))
	{
		return;
	}
	BNHeapScanRootlistAndUnion(container_of(rootlist.prev, BNTreeNode, list), true);
#endif
}

void BNHeap::BNHeapScanRootlistAndUnion(BNTreeNode* from, bool need_scan)
{
	dlist_t* plist = NULL;
	BNTreeNode* prevNode = NULL, * curNode = NULL;

	if (!need_scan)
	{
		return;
	}
	plist = &from->list;
	while (plist != &rootlist)
	{
		curNode = container_of(plist, BNTreeNode, list);
		if (plist->prev == &rootlist)
		{
			if (minNode->key < curNode->key)
			{
				minNode = curNode;
			}
			break;
		}
		prevNode = container_of(plist->prev, BNTreeNode, list);

		if ((prevNode != curNode) && (curNode->degree == prevNode->degree))
		{
			if (curNode->key > prevNode->key)
			{
				plist = plist->prev;
				dlist_del(&curNode->list);
				BNHeapUion(prevNode, curNode);
				minNode = prevNode;
			}
			else
			{
				dlist_del(&prevNode->list);
				BNHeapUion(curNode, prevNode);
				plist = plist->prev;
				minNode = curNode;
			}
		}
		else
		{
			plist = plist->prev;
		}
	}
}

void BNHeap::BNHeapInsertToRList(BNTreeNode* pBNHeap, bool need_scan) 
{
	dlist_t* plist = NULL;
	BNTreeNode* pNode = NULL;

	if (dlist_empty(&rootlist))
	{
		dlist_add(rootlist.prev, &pBNHeap->list);
	}
	else
	{
		plist = rootlist.next;
		while (plist != &rootlist)
		{
			pNode = container_of(plist, BNTreeNode, list);
			if (pNode->degree > pBNHeap->degree)
			{
				plist = plist->next;
			}
			else 
			{
				dlist_add_before(&pNode->list ,&pBNHeap->list);
				if (pNode->degree == pBNHeap->degree)
				{
					BNHeapScanRootlistAndUnion(pNode, need_scan);
				}
				break;
			}
		}
	}
}

BNTreeNode* BNHeap::BNHeapExtractMin()
{
	BNTreeNode* child = NULL;

	child = minNode->child;
	while (child)
	{
		child->parent = NULL;
		BNHeapInsertToRList(child,false);
		child = child->sib;
	}
	BNHeapScanRootlistAndUnion();
	return minNode;
}

BNTreeNode* BNHeap::BNHeapSearch(BNTreeNode* pBNHeap, BNTreeElemType key)
{
	BNTreeNode* pNode = NULL, *child = NULL;
	if (!pBNHeap || pBNHeap->key == key)
	{
		return pBNHeap;
	}

	child = pBNHeap->child;
	while (child)
	{
		pNode = BNHeapSearch(child, key);
		if (pNode)
		{
			return pNode;
		}
		else
		{
			child = child->sib;
		}
	}

	return NULL;
}

void BNHeap::BNHeapDecreaseKey(BNTreeNode* pNode, BNTreeElemType key)
{
	if (key < pNode->key)
	{
		pNode->key = key;
		while (pNode->parent && pNode->key < pNode->parent->key)
		{
			swap(pNode->key, pNode->parent->key);
			pNode = pNode->parent;
		}
	}
}

void BNHeap::BNHeapDecreaseKey(BNTreeNode* pNode, BNTreeElemType key, bool need_cut)
{

}

void BNHeapTest()
{
	BNHeap bnheap;
	int i = 0;

	for (i = 0; i <= 3; i++)
	{
		bnheap.BNHeapInsert(i);
	}
}

