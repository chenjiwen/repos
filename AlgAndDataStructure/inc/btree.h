#ifndef __BTREE_H__
#define __BTREE_H__
#pragma once

#include <vector>
using namespace std;
#include "common.h"

typedef int BTreeElemType;

typedef enum BinaryTreeType
{
	BTREE_DEFAULT,
	BTREE_SEARCH = BTREE_DEFAULT,
	BTREE_EXPR,
	BTREE_RB
}BinaryTreeType;

typedef enum RBTreeNodeType
{
	RBTreeNode_Red,
	RBTreeNode_Blk
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
	bool is_leaf_node(const BTreeNode* pNode);

	/*
	 *test if  node is a right child node
	 */
	bool is_rchild_node(const BTreeNode* pNode);

	/*
	 *test if  node is a left child node
	 */
	bool is_lchild_node(const BTreeNode* pNode);

	/*
	 *test if the node is root node
	 */
	bool is_root_node(const BTreeNode* pNode);

	/*
	 *test if the descendant node is the real descendant of the ancestor
	 */
	bool is_node_descendant(const BTreeNode* descendant, const BTreeNode* ancestor);

	/*
	 *test if the pNode is the rchild of parent node
	 */
	bool is_rchild(const BTreeNode* pNode, const BTreeNode* parent);

	/*
	 *test if the pNode is the left child of the parent node
	 */
	bool is_lchild(const BTreeNode* pNode, const BTreeNode* parent);

	/*
	 *test the parent node is the parent of pNode
	 */
	bool is_parent(const BTreeNode* pNode, const BTreeNode* parent);

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

protected:
	void set_root(const BTreeNode* pRootNode);
	void set_tree_type(BinaryTreeType type);

	BTreeNode* pBTreeNil;

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
	BSTree();
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

	void BSTree_Insert(BTreeNode* pBSTree, BTreeNode* pNode);
	void BSTree_Insert_Recursive(BTreeNode* pBSTree, BTreeNode* pNode);

	void BSTree_Delete(BTreeNode* pNode, DeleteNodeType replace = DELETED_NODE_BY_PRE);

	
protected:
	void BSTree_Transplant(BTreeNode* pNodeU, BTreeNode* pNodeV);

};

class RBTree: public BSTree
{
public:
	RBTree();
	RBTree(const BTreeElemType elem_array[], int len);
	~RBTree();
	void RBTreeLeftRotate(BTreeNode *pNode);
	void RBTreeRightRotate(BTreeNode* pNode);
	void RBTreeInsert(BTreeNode* pNodeZ);

	static BTreeNode RBTreeNIL; //static成员在类里面声明,在类外定义

private:
	void RBTree_Insert_Fixup(BTreeNode* pNode);

private:
	BTreeNode *RBTreeNil;/*sentential哨兵*/
};


#endif

