#ifndef __BTREE_H__
#define __BTREE_H__
#pragma once

#include <vector>
using namespace std;
#include "common.h"
#include "stack.h"

typedef int BTreeElemType;

typedef enum BinaryTreeType
{
	BTREE_DEFAULT = 0,
	BTREE_SEARCH = BTREE_DEFAULT,
	BTREE_EXPR,
	BTREE_RB,
	BTREE_AVL
}BinaryTreeType;

typedef enum RBTreeNodeType
{
	RBTreeNode_Red,
	RBTreeNode_Blk,
	RBTreeNode_MAX
}RBTreeNodeType;

typedef struct  BTreeNode
{
	RBTreeNodeType color;
	BTreeElemType elem;
	struct BTreeNode* parent;
	struct BTreeNode* rchild;
	struct BTreeNode* lchild;
}BTreeNode;

class BTree {
public:
	BTree(BinaryTreeType type = BTREE_DEFAULT);
	explicit BTree(const BTreeElemType& elem, BinaryTreeType type = BTREE_DEFAULT);
	explicit BTree(const vector<BTreeElemType>& vec_elem, BinaryTreeType type = BTREE_DEFAULT);
	explicit BTree(const BTreeNode* pRootNode, BinaryTreeType type = BTREE_DEFAULT);
	~BTree();

	/*
	 *test if node is leaf node
	 */
	bool is_leaf_node(const BTreeNode* pNode) const;

	/*
	 *test if  node is a right child node
	 */
	bool is_rchild_node(const BTreeNode* pNode) const;

	/*
	 *test if  node is a left child node
	 */
	bool is_lchild_node(const BTreeNode* pNode) const;

	/*
	 *test if the node is root node
	 */
	bool is_root_node(const BTreeNode* pNode)const;

	/*
	 *test if the descendant node is the real descendant of the ancestor
	 */
	bool is_node_descendant(const BTreeNode* descendant, const BTreeNode* ancestor) const;

	/*
	 *test if the pNode is the rchild of parent node
	 */
	bool is_rchild(const BTreeNode* pNode, const BTreeNode* parent) const;

	/*
	 *test if the pNode is the left child of the parent node
	 */
	bool is_lchild(const BTreeNode* pNode, const BTreeNode* parent)const;

	/*
	 *test the parent node is the parent of pNode
	 */
	bool is_parent(const BTreeNode* pNode, const BTreeNode* parent)const;

	/*
	 *traverse the tree in inorder
	 */
	void btree_inorder_traverse();
	void btree_inorder_traverse(const BTreeNode* btree);
	void btree_inorder_traverse_non_recursive();
	void btree_inorder_traverse_non_recursive(const BTreeNode* btree);
	void btree_inorder_traverse_non_recursive_1(const BTreeNode* btree);

	/*
	 *traverse the three in postorder
	 */
	void btree_postorder_traverse();
	void btree_postorder_traverse(const BTreeNode* btree);
	void btree_postorder_traverse_non_recursive();

	void btree_preorder_traverse();
	void btree_preorder_traverse(const BTreeNode* btree);

	/*
	 *return the root of the tree
	 */
	BTreeNode* get_root();

	/*
	 *traverse the tree in level
	 */
	void btree_traverse_level();

	/*
	 *get the height of the tree
	 */
	int btree_height();
	int btree_height(const BTreeNode* btree);

	virtual void btree_build();
	//virtual bool operator!();

	void destroy_btree(BTreeNode* btree);

	/*
	 *对于重载 操作符delete/new是类成员
	 *如果是对象的成员，试想一下成员都还没有如何去new或者成员还在的情况如何去delete自身
	 */
	void operator delete(void*);
	static void set_btree_nil(BTreeNode* pNil);
	static void btree_release(BTreeNode* pNil);

protected:
	void set_root(const BTreeNode* pRootNode);
	void set_tree_type(BinaryTreeType type);
	BinaryTreeType get_tree_type();

	BTreeNode* pBTreeNil;

	static BTreeNode* pBTreeNULL;

private:
	BTreeNode* root;
	BinaryTreeType tree_type;
};



class ExprTree : public BTree
{
public:
	ExprTree() {};
	explicit ExprTree(const vector<BTreeElemType> elem_vect);
	explicit ExprTree(const BTreeElemType elem_array[], int len);
	explicit ExprTree(const string&);
	~ExprTree() {};

	bool is_operator(BTreeElemType elem);

	BTreeNode* build_expr_tree_postorder(const vector<BTreeElemType>& vec_elem);
	BTreeNode* build_expr_tree_postorder(const BTreeElemType array[], int len);
	BTreeNode* build_expr_tree_postorder(const string& postorder_str);
private:

};

/*
 *二叉搜索树：
 *    左子树的任意节点的key不大于当前节点的key
 *    右子树的任意节点的key不小于当前节点的key
 */

typedef enum {
	DELETED_NODE_BY_PRE,
	DELETED_NODE_BY_SUCC
}DeleteNodeType;

class BSTree : public BTree
{
public:
	BSTree(BinaryTreeType type = BTREE_DEFAULT);
	~BSTree();
	explicit BSTree(const BTreeNode* pBSTree, BinaryTreeType type);
	explicit BSTree(const BTreeElemType elem_array[], int len);

	/*
	 *search a key from Binary search tree
	 *return NULL if not present
	 *return Node if present
	 */
	BTreeNode* BSTree_search(BTreeElemType key);
	BTreeNode* BSTree_search(const BTreeNode* pBSTree, BTreeElemType key);
	BTreeNode* BSTree_search_iteration(BTreeElemType key);

	/*
	 *return the minimum of the BSTree
	 */
	BTreeNode* BSTree_Minimum();
	BTreeNode* BSTree_Minimum(BTreeNode*);

	/*
	 *return the maximum of the BSTree 
	 */
	BTreeNode* BSTree_Maximum();
	BTreeNode* BSTree_Maximum(BTreeNode*);

	BTreeNode* BSTree_Successor(BTreeNode *pNode);
	BTreeNode* BSTree_Predecessor(BTreeNode* pNode);

	virtual void BSTree_Insert(BTreeNode* pNode);
	void BSTree_Insert_Recursive(BTreeNode* pBSTree, BTreeNode* pNode);

	void BSTree_Delete(BTreeNode* pNode, DeleteNodeType replace = DELETED_NODE_BY_PRE);

	
protected:
	void BSTree_Transplant(BTreeNode* pNodeU, BTreeNode* pNodeV);
	void BSTree_LeftRotate(BTreeNode* pNode);
	void BSTree_RightRotate(BTreeNode* pNode);
	void BSTree_LeftRightRotate(BTreeNode* pNode);
	void BSTree_RightLeftRotate(BTreeNode* pNode);

};

/*
 *红黑树是一棵满足如下性质的二叉搜索树：
 *    1. 每一个节点是红色或者黑色
 *    2. 根节点是黑色
 *    3. 每个叶子节点是黑色的
 *    4. 如果一个节点是红色的，那么它的两个子节点是黑色的
 *    5. 对每个节点而言，从该节点到其所有后代叶子节点的简单路径上，包含相同的黑节点数目
 */

class RBTree: public BSTree
{
public:
	RBTree();
	RBTree(const BTreeElemType elem_array[], int len);
	~RBTree();
	void RBTreeLeftRotate(BTreeNode *pNode);
	void RBTreeRightRotate(BTreeNode* pNode);
	void RBTreeInsert(BTreeNode* pNodeZ);
	void RBTreeDelete(BTreeNode* pNodeZ);
	void BSTree_Insert(BTreeNode* pNode);

	BTreeNode* RBTreeRightest();
	BTreeNode* RBTreeLeftest();

private:
	void RBTree_Insert_Fixup(BTreeNode* pNode);
	void RBTreeDeleteFixUp(BTreeNode* pNode);

private:
	BTreeNode *RBTreeNil;/*sentential哨兵*/
	static BTreeNode RBTreeNIL; //static成员在类里面声明,在类外定义
};


/*
 *AVL树：
 *    左子树和右子树的高度最多相差1的二叉搜索树
 */

class AVLTree :public BSTree{
public:
	AVLTree();
	~AVLTree();
	explicit AVLTree(const vector<BTreeElemType>&elem_vec);

	void AVLTreeInsert(BTreeNode* pNode);
	void AVLTreeDelete(BTreeNode* pNode);
	void AVLTreeDelete(BTreeElemType elem);

private:
	bool AVLTreeIsBalance(BTreeNode *pNode);
};



/*
 *最优二叉搜索树：
 *
 *d0<k1<d1<k2<d2<...<k(n)<d(n)
 *k1, k2, ... k(n)的概率大于d0, d1, ... d(n)的概率
 *最优二叉搜索树是一颗期望深度最小的二叉搜索树
 *任意一棵二叉搜索树的子树：它必须包含连续的关键字ki, k(i+1),...kj，同时d(i-1), di, ...dj是叶子节点
 *
 */

typedef enum {
	NODE_KEY,
	NODE_PSD
}NodeType;

class OptimalBSTree : public BSTree{
public:
	OptimalBSTree();
	~OptimalBSTree();

	void optimal_bst(vector<double> p, vector<double> q);

private:
	//double** expTable;
	//int** root_table;
	vector<double> key_p;
	vector<double> pskey_p;
	int keyNum;
};

/*
 *B balance tree
 */

#define BBTREE_USE_STATIC_MEM

typedef char BBElemType;

#ifdef BBTREE_USE_STATIC_MEM
typedef struct BBTreeNode {
	static const int degree = 2;
	bool leaf;
	int  keyNum;
	BBElemType key[(degree << 1) -1];
	struct BBTreeNode* child[degree << 1];
}BBTreeNode;
#else
typedef struct BBTreeNode {
	bool leaf;
	int  keyNum;
	BBElemType *key;
	struct BBTreeNode** child;
}BBTreeNode;
#endif

class BBTree
{
public:
	BBTree(int degree = 2);
	~BBTree();
	void BBTreeCreate();
	BBTreeNode* BBTreeSearch(BBTreeNode *BBTree, BBElemType k, int &indx);
	void BBTreeSplitChild(BBTreeNode *pNodeX, int i);
	void BBTreeInsert(BBElemType key);
	void BBTreeInsertNonFull(BBTreeNode* pBBTree, BBElemType key);
	BBElemType BBTreeSmallest();
	BBElemType BBTreeSmallest(BBTreeNode* pBBTree);
	BBElemType BBTreeLargest(BBTreeNode* pBBTree);
	BBElemType BBTreePrecedence(BBElemType key);
	BBElemType BBTreeSucessor(BBTreeNode* pBBTree, BBElemType key);
	BBElemType BBTreePrecedence(BBTreeNode* pBBTree,BBElemType key);
	BBTreeNode* BBTreeParent(BBTreeNode* pBBTree,BBElemType key, int &idx);
	BBTreeNode* BBTreeAllocNode();
	void BBTreeInorderTraverse(BBTreeNode *pBBTree);
	BBTreeNode* BBTreeRoot();
	BBTreeNode* BBTreeMergeChild(BBTreeNode *pNodeX, int i);
	void BBTreeParentDownPreUp(BBTreeNode* pNodeX, int i, BBTreeNode * pNodeY, BBTreeNode *pNodeZ);
	void BBTreeParentDownSucUp(BBTreeNode* pNodeX, int i, BBTreeNode * pNodeY, BBTreeNode* pNodeZ);
	void BBTreeDelete(BBTreeNode* pNodeX, BBElemType key);
	void BBTreeDelete(BBElemType key);
	void BBTreeDestroy(BBTreeNode *pBBTree);

private:
	BBTreeNode* root;
	int degree;
	bool dynamic_mem;
};



typedef struct BPTreeNode {
	static const int degree = 2;
	bool leaf;
	int  keyNum;
	struct BPTreeNode* parent;
#ifdef BBTREE_USE_STATIC_MEM
	BBElemType key[degree << 1];
	struct BPTreeNode* child[degree << 1];
#else
	BBElemType* key;
	struct BPTreeNode** child;
#endif
	struct llist clist;
}BPTreeNode;

class BPTree
{
public:
	BPTree(int degree = 2);
	~BPTree();
	void BPTreeCreate();
	BPTreeNode* BPTreeSearch(BPTreeNode* BBTree, BBElemType k, int& indx);
	BPTreeNode* BPTreeSearch(BBElemType k, int& indx);
	void BPTreeSplitChild(BPTreeNode* pNodeX, int i);
	void BPTreeInsert(BBElemType key);
	void BPTreeInsertNonFull(BPTreeNode* pBBTree, BBElemType key);
	BBElemType BPTreeSmallest();
	BBElemType BPTreeSmallest(BPTreeNode* pBBTree);
	BBElemType BPTreeLargest(BPTreeNode* pBBTree);
	BBElemType BPTreePrecedence(BBElemType key);
	BBElemType BPTreeSucessor(BPTreeNode* pBBTree, BBElemType key);
	BBElemType BPTreePrecedence(BPTreeNode* pBBTree, BBElemType key);
	BPTreeNode* BPTreeParent(BPTreeNode* pBBTree, BBElemType key, int& idx);
	BPTreeNode* BPTreeAllocNode();
	void BPTreeInorderTraverse(BPTreeNode* pBBTree);
	BPTreeNode* BPTreeRoot();
	BPTreeNode* BPTreeMergeChild(BPTreeNode* pNodeX, int i);
	void BPTreeParentDownPreUp(BPTreeNode* pNodeX, int i, BPTreeNode* pNodeY, BPTreeNode* pNodeZ);
	void BPTreeParentDownSucUp(BPTreeNode* pNodeX, int i, BPTreeNode* pNodeY, BPTreeNode* pNodeZ);
	void BPTreeAntiClockwiseRotate(BPTreeNode* pNodeX, int i);
	void BPTreeDelete(BPTreeNode* pNodeX, BBElemType key);
	void BPTreeDelete(BBElemType key);
	void BPTreeDestroy(BPTreeNode* pBBTree);

private:
	BPTreeNode* root;
	int degree;
	bool dynamic_mem;
};

#endif

