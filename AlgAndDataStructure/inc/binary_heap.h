#ifndef __BINARY_HEAP_H__
#define __BINARY_HEAP_H__
#pragma once

using namespace std;
#include <vector>


/******************************************************************************************************
 *二叉堆的结构描述：
 *   堆是一个数组，它可以被看成一个近似的完全二叉树，树上的每一个节点对应与数组中的一个元素。除了最底层外，该树是满的，而且
 *是从左至右填充/编号的。如下数组构成下述的二叉堆
 *
 *
 * (1)   (2)  (3) (4) (5)  (6) (7) (8) (9) (10)
 *【16】【14】【10】【8】【7】【9】【3】【2】【4】【1】
 *
 *二叉堆：
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
 *   除了最底层外，对于每一层而言，假设该层的高度为h，则该层的节点个数为2^h，对于该层的节点i而言有：
 *                      2^h <= i <=2^(h+1) - 1
 *对于节点i而言，如果它有左孩子和又孩子，那么它的左孩子的编号为2i,右孩子为2i+1，这是因为，对于节点i而言，
 *它的前面有前有i - 2^h个兄弟，对于这i - 2^h给节点有2*(i-2^h)个孩子，所以它的左孩子节点编号为：2^(h+1)+2(i-2^h)=2i
 *右孩子的节点编号为2i+1，对于节点i而言，他们的孩子为[2i, 2i + 1]，从而它的父节点编号为[i/2]
 *
 *******************************************************************************************************/

//只要定义一个对象没有提供初始化式，就会调用默认构造函数
//1.默认构造函数可以没有参数
//2.为所有形参提供默认实参的构造函数也定义了默认构造函数
//
//隐式类类型转换
//可以用单个实参来调用的构造函数定义了从形参类型到该类类型的一个隐式转换
//BinaryHeap(int len = 10)如果没有声明为explict，则定义了一个从 int到该类类型的隐式转换
//对于单形参构造函数而言，除非有明显的理由要定义隐式类型转换，否则应该为explicit
//

/*
 *
 *最大堆的性质:
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
	explicit BinaryHeap(int array[], int len, bool sort = true, bheap_mode mode = MAX_BINARY_HEAP);//默认实参、缺省参数构造函数，explicit抑制int到类类型的转换
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

#endif

