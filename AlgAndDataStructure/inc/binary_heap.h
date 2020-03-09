#ifndef __BINARY_HEAP_H__
#define __BINARY_HEAP_H__
#pragma once

using namespace std;
#include <vector>
#include "stack.h"


/******************************************************************************************************
 *����ѵĽṹ������
 *   ����һ�����飬�����Ա�����һ�����Ƶ���ȫ�����������ϵ�ÿһ���ڵ��Ӧ�������е�һ��Ԫ�ء�������ײ��⣬���������ģ�����
 *�Ǵ����������/��ŵġ��������鹹�������Ķ����
 *
 *
 * (1)   (2)  (3) (4) (5)  (6) (7) (8) (9) (10)
 *��16����14����10����8����7����9����3����2����4����1��
 *
 *����ѣ�
 *                               (1)
 *                               16
 *                        (2)             (3)
 *                        14               10
 *                  (4)          (5)   (6)        (7)
 *                   8            7     9          3
 *               (8)    (9)   (10)
 *                2      4      1
 *
 ******************************************************************************************************
 *
 *   ������ײ��⣬����ÿһ����ԣ�����ò�ĸ߶�Ϊh����ò�Ľڵ����Ϊ2^h�����ڸò�Ľڵ�i�����У�
 *                      2^h <= i <=2^(h+1) - 1
 *���ڽڵ�i���ԣ�����������Ӻ��ֺ��ӣ���ô�������ӵı��Ϊ2i,�Һ���Ϊ2i+1��������Ϊ�����ڽڵ�i���ԣ�
 *����ǰ����ǰ��i - 2^h���ֵܣ�������i - 2^h���ڵ���2*(i-2^h)�����ӣ������������ӽڵ���Ϊ��2^(h+1)+2(i-2^h)=2i
 *�Һ��ӵĽڵ���Ϊ2i+1�����ڽڵ�i���ԣ����ǵĺ���Ϊ[2i, 2i + 1]���Ӷ����ĸ��ڵ���Ϊ[i/2]
 *
 *******************************************************************************************************/

//ֻҪ����һ������û���ṩ��ʼ��ʽ���ͻ����Ĭ�Ϲ��캯��
//1.Ĭ�Ϲ��캯������û�в���
//2.Ϊ�����β��ṩĬ��ʵ�εĹ��캯��Ҳ������Ĭ�Ϲ��캯��
//
//��ʽ������ת��
//�����õ���ʵ�������õĹ��캯�������˴��β����͵��������͵�һ����ʽת��
//BinaryHeap(int len = 10)���û������Ϊexplict��������һ���� int���������͵���ʽת��
//���ڵ��βι��캯�����ԣ����������Ե�����Ҫ������ʽ����ת��������Ӧ��Ϊexplicit
//

/*
 *
 *���ѵ�����:
 *    A[parent(i)] >> A[i]
 *
 */

typedef enum {
    MAX_BINARY_HEAP,
    MIN_BINARY_HEAP
}bheap_mode;

typedef vector<int>::size_type bheap_idx_type;

class BinaryHeap
{
public:
	explicit BinaryHeap(int array[], int len, bool sort = true, bheap_mode mode = MAX_BINARY_HEAP);//Ĭ��ʵ�Ρ�ȱʡ�������캯����explicit����int�������͵�ת��
    explicit BinaryHeap(const vector<int> &vec, bool sort = true, bheap_mode mode = MAX_BINARY_HEAP);//
    //BinaryHeap():vec_len(0), heap_size(0),sorted(false){}
    explicit BinaryHeap(bheap_mode mode = MAX_BINARY_HEAP);
	~BinaryHeap();

protected:
    vector<int>::size_type parent(vector<int>::size_type node_id);
    vector<int>::size_type left_child(vector<int>::size_type node_id);
    vector<int>::size_type right_child(vector<int>::size_type node_id);

    //maxheap API
    void max_heapify(vector<int>::size_type idx);
    void max_heapify(vector<int>::size_type idx, int recurs);
    void build_max_heap();

    //minheap API
    void min_heapify(vector<int>::size_type idx);
    void build_min_heap();
    

    

public:
    void dump_heap();
    void heap_sort();
    void min_heap_sort();
    bool heap_sorted() { return sorted; }
    bheap_mode getBHeap_mode() { return heap_mode; }
    vector<int>& getHeapContent(vector<int>::size_type& heap_size);
    vector<int>& getHeapContent();
    vector<int>::size_type getHeapSize();
    int extractMaxFromHeap();
    int getMinFromMinHeap();
    void heap_increase_key(int node, int key);
    void heap_insert(int key);
    void heap_delete(vector<int>::size_type node);
    void min_heap_insert(int key);
    void min_heap_delete(vector<int>::size_type node);
    virtual int getHeapMax();

private:
    vector<int>::size_type vec_len;        // vec_len = size of vec + 1(the first element is used to store the heap size)
    vector<int>::size_type heap_size;      // heap size
	vector<int> vec;                       // vec[0] is used to store the heap size
    bool sorted;                           // Need sort the heap
    bheap_mode heap_mode;
};

inline vector<int>::size_type BinaryHeap::parent(vector<int>::size_type node_id) {
    return node_id >> 1;
}

inline vector<int>::size_type BinaryHeap::left_child(vector<int>::size_type node_id) {
    return node_id << 1;
}

inline vector<int>::size_type BinaryHeap::right_child(vector<int>::size_type node_id) {
    return (node_id << 1) + 1;
}


class MergeableHeap
{

};

typedef int FibHeapElement;

typedef struct FibHeapNode 
{
    FibHeapElement key;
    struct FibHeapNode* parent;//parent of node
    struct FibHeapNode* first_child;//child of node
    dlist   sibling;//sibling of the child
    dlist_t list;  //dlink list used to link in the root list
    int     degree;//child num in list
    bool    marked;
    void* priv;
}FibHeapNode;

class FibHeap
{
public:
    FibHeap();
    ~FibHeap();
    void FibHeapInsert(FibHeapNode *pNode);
    void* FibHeapInsert(FibHeapElement key, void *);
    FibHeap* FibHeapUnion(FibHeap* , FibHeap*);
    int FibHeapMaxDegNum();
    void FibHeapLink(FibHeapNode *pNodeY, FibHeapNode * pNodeX);
    void FibHeapConsolidate();
    FibHeapNode* FibHeapExtractMin();
    void FibHeapCut(FibHeapNode* pNodeX, FibHeapNode* pNodeY);
    void FibHeapCascadingCut(FibHeapNode* pNodeX);
    void FibHeapDecreseKey(FibHeapNode* pNodeX, FibHeapElement k);
    void FibHeapDelete(FibHeapNode *pNode);
    void FibHeapDestroyMinHeap(FibHeapNode*);
    void FibHeapDestroy();
    bool FibCheckRootListDegree();
    void FibHeapDump(FibHeapNode* pFibHeap);

private:
    FibHeapNode* minNode;
    int NodeNum;
};


typedef int BNTreeElemType;

typedef struct BNTreeNode
{
    BNTreeElemType           key;
    struct BNTreeNode*       child;    //child
    struct BNTreeNode*       parent;   //parent
    int                      degree;   //child number
    dlist_t                  list;     //list linked to the heap rootlist
    struct BNTreeNode*       sib;      //sibling list
}BNTreeNode;

class BNTree {

public:
    BNTree(int num = 0);
    ~BNTree();
    BNTreeNode* BNTreeBuild(int k);
    void BNTTreeUion(BNTreeNode*, BNTreeNode*);

private:
    BNTreeNode* root;
    int nodeNum;
    int depth;
    dlist_t list;
};

class BNHeap
{
public:
    BNHeap();
    ~BNHeap();

    void BNHeapInsert(BNTreeElemType key);
    void BNHeapUion(BNTreeNode*, BNTreeNode*);
    void BNHeapScanRootlistAndUnion();
    void BNHeapScanRootlistAndUnion(BNTreeNode *from, bool scan);
    void BNHeapInsertToRList(BNTreeNode*, bool need_scan = true);
    BNTreeNode* BNHeapExtractMin();
    void BNHeapDecreaseKey(BNTreeNode*, BNTreeElemType key);
    void BNHeapDecreaseKey(BNTreeNode* pNode, BNTreeElemType key, bool need_cut);
    BNTreeNode* BNHeapSearch(BNTreeNode* ,BNTreeElemType key);

private:
    BNTreeNode* minNode;
    dlist_t rootlist;
};

#endif

