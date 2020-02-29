#include "btree.h"
#include <iostream>
#include <vector>
using namespace std;

BTree::BTree(BinaryTreeType type):tree_type(type),root(NULL), pBTreeNil(NULL){
	set_btree_nil(pBTreeNil);
}

BTree::BTree(const BTreeElemType& elem, BinaryTreeType type):tree_type(type), pBTreeNil(NULL) {
	set_btree_nil(pBTreeNil);
}

BTree::BTree(const vector<BTreeElemType>& vec_elem, BinaryTreeType type):tree_type(type),pBTreeNil(NULL) {
	set_btree_nil(pBTreeNil);
}

BTree::BTree(const BTreeNode* pNode, BinaryTreeType type):root((BTreeNode*)pNode), tree_type(type),pBTreeNil((BTreeNode*)pNode){
	set_btree_nil(pBTreeNil);
}

BTree::~BTree() {
	if (root != pBTreeNil) {
		destroy_btree(root);
	}
	root = pBTreeNil;
}

void visit_node(const BTreeNode* pBtreeNode)
{
	cout << pBtreeNode->elem << " ";
}

bool BTree::is_leaf_node(const BTreeNode* pNode) const {
	if ((pBTreeNil == pNode->lchild) && (pBTreeNil == pNode->rchild))
	{
		return true;
	}
	return false;
}

bool BTree::is_lchild_node(const BTreeNode* pNode) const{
	return pNode == pNode->parent->lchild;
}

bool BTree::is_rchild_node(const BTreeNode* pNode) const{
	return pNode == pNode->parent->rchild;
}

bool BTree::is_root_node(const BTreeNode* pNode) const{
	return pNode->parent == pBTreeNil;
}

void BTree::set_root(const BTreeNode* pRootNode) {
	root = (BTreeNode*)pRootNode;
}

BTreeNode* BTree::get_root() {
	return root;
}

void BTree::set_tree_type(BinaryTreeType type) {
	tree_type = type;
}

BinaryTreeType BTree::get_tree_type() {
	return tree_type;
}

bool BTree::is_lchild(const BTreeNode* pNode, const BTreeNode* parent) const{
	return parent->lchild == pNode;
}

bool BTree::is_parent(const BTreeNode* pNode, const BTreeNode* parent) const{
	return pNode->parent == parent;
}

bool BTree::is_rchild(const BTreeNode* pNode, const BTreeNode* parent) const{
	return parent->rchild == pNode;
}

bool BTree::is_node_descendant(const BTreeNode* descendant, const BTreeNode* ancestor) const{
	BTreeNode* parent = pBTreeNil;

	if (pBTreeNil == descendant)
	{
		return false;
	}

	parent = descendant->parent;
	while (parent != pBTreeNil)
	{
		if (parent == ancestor)
		{
			return true;
		}

		parent = parent->parent;
	}

	return false;
}

void BTree::btree_inorder_traverse() {
	//btree_inorder_traverse(root);
	btree_inorder_traverse_non_recursive();
}

void BTree::btree_inorder_traverse(const BTreeNode* btree) {
	if (pBTreeNil == btree)
		return;
	/*traverse left child first*/
	if (pBTreeNil != btree->lchild)
	{
		btree_inorder_traverse(btree->lchild);
	} 

	/*traverse current node*/
	visit_node(btree);

	/*traverse right child*/
	if(btree->rchild != pBTreeNil)
	{
		btree_inorder_traverse(btree->rchild);
	}
}

void BTree::btree_inorder_traverse_non_recursive() {
	btree_inorder_traverse_non_recursive_1(root);
}
/*
 *中序遍历：
 *    先访问左子树，再访问当前节点，最后访问右子树
 */
void BTree::btree_inorder_traverse_non_recursive_1(const BTreeNode* btree) {
	vector<BTreeNode*> stack;
	BTreeNode* pNode = pBTreeNil;
	BTreeNode* prevNode = pBTreeNil;

	pNode = (BTreeNode*)btree;

	/*
	 *push the root into stack first
	 */
	stack.push_back(pNode);
	while (!stack.empty())
	{
		pNode = stack.back();

		if (is_node_descendant(prevNode, pNode) || is_leaf_node(pNode))
		{
			/*
			 *当前是叶子节点或者左子树已经访问结束，访问当前节点并且出栈。
			 *如果当前节点有右孩子，右孩子入栈
			 */
			stack.pop_back();
			prevNode = pNode;
			if (pNode->rchild)
			{
				stack.push_back(pNode->rchild);
			}
			visit_node(pNode);
		}
		else
		{
			/*
			 *当前节点不是叶子节点，而且左子树还没有访问，如果有左孩子，左孩子入栈
			 */
			if (pNode->lchild)
			{
				stack.push_back(pNode->lchild);
			}
			else
			{
				/*
				 *如果当前节点没有左子树，但是有右子树，需要访问当前节点并且之后右子树压栈
				 *为了保持程序一致性，通过设置prevNode = pNode->rchild来说明左子树已经访问结束，由于在
				 *is_node_descendant的判断中，prevNode为NULL时，返回false，对于当前节点左子树为空，而右子树不为空的时候
				 *通过一个trickey的方法，设置prevNode = pNode->rchild来表示当前的左子树已经访问结束
				 */
				prevNode = pNode->rchild;
			}
		}
	}
}

void BTree::btree_inorder_traverse_non_recursive(const BTreeNode* btree) {
	vector<BTreeNode*> stack;
	BTreeNode* pNode = pBTreeNil;
	BTreeNode* prevNode = pBTreeNil;

	pNode = (BTreeNode*)btree;

	/*
	 *push the root into stack first
	 */
	stack.push_back(pNode);

	while (!stack.empty())
	{
		pNode = stack.back();
		stack.pop_back();

		/*
		 *root node and right child node
		 */
		if (is_root_node(pNode) || is_rchild_node(pNode))
		{
			if (is_leaf_node(pNode))
			{
				visit_node(pNode);
				continue;
			}


			if (!is_node_descendant(prevNode, pNode))
			{
				/*
                 *当前节点还没有开始访问，所有的左孩子开始压栈
                 */
				while (pNode != pBTreeNil)
				{
					stack.push_back(pNode);
					pNode = pNode->lchild;

				}
			}
			else
			{
				/*
                 *当前节点的左孩子已经访问结束，访问当前节点，如果右孩子有的话，右孩子节点压栈
                 */
				visit_node(pNode);
				if (pNode->rchild != pBTreeNil)
				{
					stack.push_back(pNode->rchild);
				}
				
			}
		}
		else
		{  
			/*
			 *当前是左孩子，直接访问，如果右孩子存在的话，右孩子压栈
			 */
			visit_node(pNode);
			if (pNode->rchild != pBTreeNil)
			{
				stack.push_back(pNode->rchild);
			}
		}
		prevNode = pNode;
	}

	cout << endl;
}

void BTree::btree_postorder_traverse() {
	btree_postorder_traverse(root);
}

void BTree::btree_postorder_traverse(const BTreeNode* btree) {
	if (pBTreeNil == btree)
	{
		return;
	}
	/*visit left child tree*/
	btree_postorder_traverse(btree->lchild);

	/*visit right child tree*/
	btree_postorder_traverse(btree->rchild);

	/*visit current node*/
	visit_node(btree);
}

/*
 *后序遍历：
 *    先遍历左子树，再遍历右子树，最后访问父节点
 */
void BTree::btree_postorder_traverse_non_recursive() {
	vector<BTreeNode*> stack;
	BTreeNode* pNode = pBTreeNil;
	BTreeNode* prevNode = pBTreeNil;

	pNode = (BTreeNode*)root;

	stack.push_back(pNode);
	while (!stack.empty())
	{
		pNode = stack.back();

		if (is_node_descendant(prevNode, pNode) || is_leaf_node(pNode))
		{
			/*
			 *当前节点是叶子节点或者当前节点的后代已经访问结束，访问当前节点和出栈
			 */
			stack.pop_back();
			prevNode = pNode;
			visit_node(pNode);
			continue;
		}
		else 
		{
			/*
			 *当前节点不是叶节点或者子树还没有访问，先压栈右节点，后压栈左节点
			 */
			if (pNode->rchild != pBTreeNil)
			{
				stack.push_back(pNode->rchild);
			}
			if (pNode->lchild != pBTreeNil)
			{
				stack.push_back(pNode->lchild);
			}
		}
	}
}

int BTree::btree_height(const BTreeNode* btree) {

	if (pBTreeNil == btree)
	{
		return -1;
	}

	return max(btree_height(btree->lchild), btree_height(btree->rchild)) + 1;
}

int BTree::btree_height() {
	return btree_height(root);
}

void BTree::btree_build() {

}


/*
 *在类外定义类的静态变量
 */
BTreeNode* BTree::pBTreeNULL = NULL;

/*
 *静态成员函数只能访问静态成员/不能调用非静态成员
 */
void BTree::set_btree_nil(BTreeNode* pNil) {
	pBTreeNULL = pNil;
}

void BTree::btree_release(BTreeNode* pBTree) {
	if (pBTree != pBTreeNULL)
	{
		if (pBTree->lchild)
		{
			btree_release(pBTree->lchild);
			pBTree->lchild = pBTreeNULL;
		}

		if (pBTree->rchild)
		{
			btree_release(pBTree->rchild);
			pBTree->rchild = pBTreeNULL;
		}

		delete pBTree;
	}
}

void BTree::operator delete(void* ptr) {
	BTree* pBTreeObj = static_cast<BTree*>(ptr);
	BTreeNode* btree = pBTreeObj->root;

	btree_release(btree);
	pBTreeObj->root = NULL;
}

void BTree::destroy_btree(BTreeNode* btree) {
	if (btree != pBTreeNil)
	{
		if (btree->lchild)
		{
			destroy_btree(btree->lchild);
			btree->lchild = pBTreeNil;
		}

		if (btree->rchild)
		{
			destroy_btree(btree->rchild);
			btree->rchild = pBTreeNil;
		}

		delete btree;
	}
}


void BTree::btree_traverse_level() {
	vector<BTreeNode*> queue;
	BTreeNode* pNode = pBTreeNil;
	BTreeNode* prevNode = pBTreeNil;

}

ExprTree::ExprTree(const BTreeElemType elem_array[], int len):BTree(BTREE_EXPR) {
	build_expr_tree_postorder(elem_array, len);
}

bool ExprTree::is_operator(BTreeElemType elem) {
	if (elem == '-' || elem == '+' || elem == '/' || elem == '*')
		return true;

	return false;
}

BTreeNode* ExprTree::build_expr_tree_postorder(const vector<BTreeElemType>& vec_elem) {

	return NULL;
}

BTreeNode* ExprTree::build_expr_tree_postorder(const BTreeElemType elem_array[], int len) {
	int i = 0;
	vector<BTreeNode*> stack;
	BTreeNode* pNode = NULL;

	for (i = 0; i < len; i++)
	{
		if (!is_operator(elem_array[i]))
		{
			pNode = new BTreeNode;
			pNode->elem = elem_array[i];
			pNode->parent = pBTreeNil;
			pNode->lchild = pBTreeNil;
			pNode->rchild = pBTreeNil;
			stack.push_back(pNode);
		}
		else 
		{
			pNode = new BTreeNode;
			pNode->elem = elem_array[i];
			pNode->parent = pBTreeNil;
			pNode->rchild = stack.back();
			pNode->rchild->parent = pNode;

			stack.pop_back();
			pNode->lchild = stack.back();
			pNode->lchild->parent = pNode;
			stack.pop_back();
			stack.push_back(pNode);
		}
	}

	pNode = stack.front();
	stack.pop_back();
	set_root(pNode);
	return pNode;
}


BSTree::BSTree(BinaryTreeType type):BTree(type)
{

}

BSTree::~BSTree() {

}

BSTree::BSTree(const BTreeNode* pBSTree, BinaryTreeType type):BTree(pBSTree, type)
{

}

BSTree::BSTree(const BTreeElemType elem_array[], int len):BTree(BTREE_SEARCH) {
	BTreeNode* pNode = pBTreeNil;
	for (int i = 0; i < len; i++)
	{
		pNode = new BTreeNode;
		pNode->elem = elem_array[i];
		pNode->parent = pBTreeNil;
		pNode->lchild = pBTreeNil;
		pNode->rchild = pBTreeNil;
		BSTree_Insert_Recursive(get_root(), pNode);
	}

}

BTreeNode* BSTree::BSTree_search(BTreeElemType key) {
	return BSTree_search(get_root(), key);
}

BTreeNode* BSTree::BSTree_search(const BTreeNode* pBSTree, BTreeElemType key) {
	if ((pBTreeNil == pBSTree) || pBSTree->elem == key )
	{
		return (BTreeNode*)pBSTree;
	}
	else if (pBSTree->elem < key)
	{
		return BSTree_search(pBSTree->rchild,key);
	}
	else
	{
		return BSTree_search(pBSTree->lchild,key);
	}
}

BTreeNode* BSTree::BSTree_search_iteration(BTreeElemType key) {
	BTreeNode* pBSTreeNode = pBTreeNil;

	pBSTreeNode = get_root();
	while ((pBSTreeNode != pBTreeNil) && (pBSTreeNode->elem != key))
	{
		if (pBSTreeNode->elem < key)
		{
			pBSTreeNode = pBSTreeNode->rchild;
		}
		else
		{
			pBSTreeNode = pBSTreeNode->lchild;
		}
	}

	return pBSTreeNode;
}

BTreeNode* BSTree::BSTree_Minimum(BTreeNode* pBSTreeNode) {
	while ((pBSTreeNode != pBTreeNil) && (pBSTreeNode->lchild != pBTreeNil))
	{
		pBSTreeNode = pBSTreeNode->lchild;
	}

	return pBSTreeNode;
}

BTreeNode* BSTree::BSTree_Minimum() {
	BTreeNode* pBSTreeNode = pBTreeNil;
	pBSTreeNode = get_root();

	while ((pBSTreeNode != pBTreeNil) && (pBTreeNil != pBSTreeNode->lchild))
	{
		pBSTreeNode = pBSTreeNode->lchild;
	}

	return pBSTreeNode;
}

BTreeNode* BSTree::BSTree_Maximum() {
	BTreeNode* pBSTreeNode = pBTreeNil;
	pBSTreeNode = get_root();

	while ((pBSTreeNode != pBTreeNil) && (pBTreeNil != pBSTreeNode->rchild))
	{
		pBSTreeNode = pBSTreeNode->rchild;
	}

	return pBSTreeNode;
}

BTreeNode* BSTree::BSTree_Maximum(BTreeNode* pBSTreeNode) {
	while ((pBSTreeNode != pBTreeNil) && (pBTreeNil != pBSTreeNode->rchild))
	{
		pBSTreeNode = pBSTreeNode->rchild;
	}

	return pBSTreeNode;
}

BTreeNode* BSTree::BSTree_Successor(BTreeNode* pNode){
	BTreeNode* pBSTreeNode = pBTreeNil;

	if (pNode->rchild != pBTreeNil)
	{
		return BSTree_Minimum(pNode->rchild);
	}

	pBSTreeNode = pNode->parent;
	while ((pBSTreeNode != pBTreeNil) && (pNode == pBSTreeNode->rchild))
	{
		pNode = pBSTreeNode;
		pBSTreeNode = pBSTreeNode->parent;
	}

	return pBSTreeNode;
}

BTreeNode* BSTree::BSTree_Predecessor(BTreeNode* pNode) {
	BTreeNode* pBSTreeNode = pBTreeNil;

	if (pNode->lchild != pBTreeNil)
	{
		return BSTree_Maximum(pNode->lchild);
	}

	pBSTreeNode = pNode->parent;
	while ((pBSTreeNode != pBTreeNil) && (pNode == pBSTreeNode->lchild))
	{
		pNode = pBSTreeNode;
		pBSTreeNode = pBSTreeNode->parent;
	}

	return pBSTreeNode;
}

void BSTree::BSTree_Insert(BTreeNode* pNode) {
	BTreeNode* pTempNodeX = pBTreeNil;
	BTreeNode* pTempNodeY = pBTreeNil;

	pTempNodeX = get_root();
	while (pTempNodeX != pBTreeNil)
	{
		pTempNodeY = pTempNodeX;
		if (pNode->elem < pTempNodeX->elem)
		{
			pTempNodeX = pTempNodeX->lchild;
		}
		else
		{
			pTempNodeX = pTempNodeX->rchild;
		}
	}
	pNode->parent = pTempNodeY;
	if (pTempNodeY == pBTreeNil)
	{
		set_root(pNode);
	}
	else if (pNode->elem < pTempNodeY->elem)
	{
		pTempNodeY->lchild = pNode;
	}
	else
	{
		pTempNodeY->rchild = pNode;
	}
}

void BSTree::BSTree_Insert_Recursive(BTreeNode* pBSTree, BTreeNode* pNode) {
	if (pBSTree == pBTreeNil)
	{
		set_root(pNode);
		return;
	}

	if (pNode->elem < pBSTree->elem)
	{
		if (pBSTree->lchild != pBTreeNil)
		{
			BSTree_Insert_Recursive(pBSTree->lchild, pNode);
		}
		else
		{
			pBSTree->lchild = pNode;
			pNode->parent = pBSTree;
		}
	}
	else
	{
		if (pBSTree->rchild != pBTreeNil)
		{
			BSTree_Insert_Recursive(pBSTree->rchild, pNode);
		}
		else
		{
			pBSTree->rchild = pNode;
			pNode->parent = pBSTree;
		}
	}
}
/*
 *Tree:
 *    replace subtree pNodeU by subtree pNodeV
 *    pNodeV is child of parent of pNodeU
 */
void BSTree::BSTree_Transplant(BTreeNode* pNodeU, BTreeNode* pNodeV) {
	if (pNodeU->parent == pBTreeNil)
	{
		set_root(pNodeV);
	}
	else if (is_lchild_node(pNodeU))
	{
		pNodeU->parent->lchild = pNodeV;
	}
	else
	{
		pNodeU->parent->rchild = pNodeV;
	}

	if (get_tree_type() == BTREE_RB)
	{
		pNodeV->parent = pNodeU->parent;
	}
	else if (pNodeV != pBTreeNil)
	{
		pNodeV->parent = pNodeU->parent;
	}
}

void BSTree::BSTree_Delete(BTreeNode* pNode, DeleteNodeType replaceBy) {
	BTreeNode* pTempNodeY = pBTreeNil;

	if (pBTreeNil == pNode->lchild)
	{
		BSTree_Transplant(pNode, pNode->rchild);
	}
	else if (pBTreeNil == pNode->rchild)
	{
		BSTree_Transplant(pNode, pNode->lchild);
	}
	else 
	{
		if (replaceBy == DELETED_NODE_BY_PRE)
		{
			/*
			 *Node is replaced by Predecessor
			 */
			pTempNodeY = BSTree_Maximum(pNode->lchild);
			if (pTempNodeY->parent != pNode)
			{
				BSTree_Transplant(pTempNodeY, pTempNodeY->lchild);
				pTempNodeY->lchild = pNode->lchild;
				pTempNodeY->lchild->parent = pTempNodeY;
			}
			BSTree_Transplant(pNode, pTempNodeY);
			pTempNodeY->rchild = pNode->rchild;
			pTempNodeY->rchild->parent = pTempNodeY;

		}
		else
		{
			/*
			 *Node is replaced by successor
			 */
			pTempNodeY = BSTree_Minimum(pNode->rchild);
			if (pTempNodeY->parent != pNode)
			{
				BSTree_Transplant(pTempNodeY, pTempNodeY->rchild);
				pTempNodeY->rchild = pNode->rchild;
				pTempNodeY->rchild->parent = pTempNodeY;
			}

			BSTree_Transplant(pNode, pTempNodeY);
			pTempNodeY->lchild = pNode->lchild;
			pTempNodeY->lchild->parent = pTempNodeY;
		}

	}
}

void BSTree::BSTree_LeftRotate(BTreeNode* pNode) {
	BTreeNode* pTempNodeY = pBTreeNil;
	BTreeNode* pRBTreeRoot = pBTreeNil;

	pRBTreeRoot = get_root();
	pTempNodeY = pNode->rchild;
	if (pTempNodeY == pBTreeNil)
	{
		return;
	}

	pNode->rchild = pTempNodeY->lchild;

	if (pTempNodeY->lchild != pBTreeNil)
	{
		pTempNodeY->lchild->parent = pNode;
	}

	pTempNodeY->parent = pNode->parent;

	if (pNode->parent == pBTreeNil)
	{
		set_root(pTempNodeY);
	}
	else if (is_lchild_node(pNode))
	{
		pNode->parent->lchild = pTempNodeY;
	}
	else
	{
		pNode->parent->rchild = pTempNodeY;
	}

	pTempNodeY->lchild = pNode;
	pNode->parent = pTempNodeY;
}

void BSTree::BSTree_RightRotate(BTreeNode* pNodeX) {
	BTreeNode* pNodeY = pBTreeNil;
	BTreeNode* pRBTreeRoot = pBTreeNil;

	pRBTreeRoot = get_root();

	//step1: 把NodeY的右孩子嫁接到NodeX的左孩子上
	//获取左孩子
	pNodeY = pNodeX->lchild;
	if (pNodeY == pBTreeNil)
	{
		return;
	}

	//NodeX的左孩子修改为NodeY的右孩子
	pNodeX->lchild = pNodeY->rchild;

	//修改NodeY的右孩子的父节点，
	if (pNodeY->rchild != pBTreeNil)
	{
		pNodeY->rchild->parent = pNodeX;
	}

	//修改NodeY的父节点为NodeX的父节点
	pNodeY->parent = pNodeX->parent;

	//修改NodeX的父节点的孩子节点为NodeY
	if (pNodeX->parent == pBTreeNil)
	{
		set_root(pNodeY);
	}
	else if (is_lchild_node(pNodeX))
	{
		pNodeX->parent->lchild = pNodeY;
	}
	else
	{
		pNodeX->parent->rchild = pNodeY;
	}

	//修改NodeY的右孩子节点
	pNodeY->rchild = pNodeX;
	//修改NodeX的父节点
	pNodeX->parent = pNodeY;
}

void BSTree::BSTree_LeftRightRotate(BTreeNode* pNode) {
	if (pNode->parent && pNode->rchild)
	{
		BSTree_LeftRotate(pNode);
		BSTree_RightRotate(pNode->parent->parent);
	}
}

void BSTree::BSTree_RightLeftRotate(BTreeNode* pNode) {
	if (pNode->parent && pNode->lchild)
	{
		BSTree_RightRotate(pNode);
		BSTree_LeftRotate(pNode->parent->parent);
	}
}

/*
 *static成员必须在类外定义,在类里面声明
 *static成员可以作为默认实参
 */
BTreeNode RBTree::RBTreeNIL = { RBTreeNode_Blk, -1, NULL, NULL,NULL };
RBTree::RBTree():RBTreeNil(&(RBTree::RBTreeNIL)), BSTree(&(RBTree::RBTreeNIL), BTREE_RB)
{
	//set_root(RBTreeNil);
}

RBTree::RBTree(const BTreeElemType elem_array[], int len): RBTreeNil(&(RBTree::RBTreeNIL)), BSTree(&(RBTree::RBTreeNIL), BTREE_RB)
{
	int i = 0;
	BTreeNode* pNode = pBTreeNil;
	set_root(RBTreeNil);
	for (i = 0; i < len; i++)
	{
		pNode = new BTreeNode;
		pNode->color = RBTreeNode_Blk;
		pNode->elem = elem_array[i];
		pNode->lchild = RBTreeNil;
		pNode->rchild = RBTreeNil;
		pNode->parent = RBTreeNil;
		BSTree_Insert(pNode);
	}
}

RBTree::~RBTree() 
{

}

void RBTree::RBTreeLeftRotate(BTreeNode* pNode) {
	BTreeNode* pTempNodeY = pBTreeNil;
	BTreeNode* pRBTreeRoot = pBTreeNil;

	pRBTreeRoot = get_root();
	pTempNodeY = pNode->rchild;
	if (pTempNodeY == RBTreeNil)
	{
		return;
	}

	pNode->rchild = pTempNodeY->lchild;

	if (pTempNodeY->lchild != RBTreeNil)
	{
		pTempNodeY->lchild->parent = pNode;
	}

	pTempNodeY->parent = pNode->parent;

	if (pNode->parent == RBTreeNil)
	{
		set_root(pTempNodeY);
	}
	else if (is_lchild_node(pNode))
	{
		pNode->parent->lchild = pTempNodeY;
	}
	else
	{
		pNode->parent->rchild = pTempNodeY;
	}

	pTempNodeY->lchild = pNode;
	pNode->parent = pTempNodeY;
}

void RBTree::RBTreeRightRotate(BTreeNode* pNodeX) {
	BTreeNode* pNodeY = pBTreeNil;
	BTreeNode* pRBTreeRoot = pBTreeNil;

	pRBTreeRoot = get_root();

	//step1: 把NodeY的右孩子嫁接到NodeX的左孩子上
	//获取左孩子
	pNodeY = pNodeX->lchild;
	if (pNodeY == RBTreeNil)
	{
		return;
	}

	//NodeX的左孩子修改为NodeY的右孩子
	pNodeX->lchild = pNodeY->rchild;

	//修改NodeY的右孩子的父节点，
	if (pNodeY->rchild->parent != RBTreeNil)
	{
		pNodeY->rchild->parent = pNodeX; 
	}

	//修改NodeY的父节点为NodeX的父节点
	pNodeY->parent = pNodeX->parent;

	//修改NodeX的父节点的孩子节点为NodeY
	if (pNodeX->parent == RBTreeNil)
	{
		set_root(pNodeY);
	}
	else if (is_lchild_node(pNodeX))
	{
		pNodeX->parent->lchild = pNodeY;
	}
	else
	{
		pNodeX->parent->rchild = pNodeY;
	}

	//修改NodeY的右孩子节点
	pNodeY->rchild = pNodeX;
	//修改NodeX的父节点
	pNodeX->parent = pNodeY;
}

/*
 *红黑树：它是一颗二叉搜索树，有如下性质
 *    1.每个节点是红色或者黑色的
 *    2.根是黑色的
 *    3.每个叶子节点是黑色的
 *    4.如果一个节点是红色的，则它的两个子节点都是黑色的
 *    5.对每个节点，从该节点到其他所有后代叶子节点的简单路径上，均包含相同数目的黑色节点
 *
 *
 *插入一个节点的时候，会把默认的节点颜色设置为Red，这样当插入一个节点到红黑树的时候，性质
 *1.3.5都不会破坏，只会破坏破坏的性质是(2)和(4)，也就是新插入的节点可能会是根节点，但是
 *是红色或者红色节点插入到一个红色节点后，破坏了性质4.因而需要对红黑树进行调整使其保持红黑
 *树的性质。
 *
 *当插入一个节点时，除了第一次是根节点以外，其他的情况都会把节点插入到树里面，这时候树的形状
 *只有如下6种可能：
 *
 *                  case1                                    case2
 *
 *                   Blk(A)                                   Blk(A)
 *                  *  *                                     *   *
 *                 *    *                                   *     *
 *                *      *                                 *       *
 *              (B)Red  (C)Red                           (B)red   (C)red
 *              *                                         *
 *             *                                           *
 *            *                                             *
 *           N(red)                                         N(red)
 *
 *
 *
 *
 *                  case3
 *                  
 *                  Blk(A)
 *                 *   *
 *                *     *
 *               *       *
 *            (B)Red     (C)Blk
 *             *
 *            *
 *           *
 *          N(Red)
 *
 *
 *对于case 1的策略如下：
 *    (a).B/C着色为红色
 *    (b).A着色为黑色
 *    (c).N<-A把N提升到A的位置继续调整红黑树
 *
 *
 *对于case 2:
 *    把B/N做一次左旋转，就变成case 1的形状
 *
 *对于case 3:
 *    对B着色黑色，对A着色红色就解决了性质4的矛盾，但是这时候A的右子树的黑高度
 *由于着色的调整，从而导致A及其右子树的高度都减少1，把着色后的B\A做一次右旋转，
 *这是不改变搜索二叉树的性质，同时恢复了节点A/及其右子树的黑高度，同时由于把B着色
 *为黑色，右旋转后不会改变B及其子树的高度
 *
 */

void RBTree::RBTree_Insert_Fixup(BTreeNode* pNode) {
	BTreeNode* pTempY = RBTreeNil;

	while (pNode->parent->color == RBTreeNode_Red)
	{
		
		if (is_lchild_node(pNode->parent))
		{
			/*case1: parent is left child node*/

			//Y used to record uncle of current node
			pTempY = pNode->parent->parent->rchild;

			
			if (pTempY->color == RBTreeNode_Red)
			{
				//uncle has same color with parent, color parent and uncle with Black
				pNode->parent->color = RBTreeNode_Blk;
				pTempY->color = RBTreeNode_Blk;

				//color grandpa with Red
				pNode->parent->parent->color = RBTreeNode_Red;

				//move pNode to grandpa
				pNode = pNode->parent->parent;
			}
			else 
			{
				/*
				 *uncle's color is black
				 */
				if (pNode == pNode->parent->rchild) 
				{
					/*
					 *current node is right child, left rotate
					 */
					pNode = pNode->parent;
					RBTreeLeftRotate(pNode);
				}

				/*
				 *color parent with black
				 *color sibling with red
				 */
				pNode->parent->color = RBTreeNode_Blk;
				pNode->parent->parent->color = RBTreeNode_Red;
				RBTreeRightRotate(pNode->parent->parent);
			}
		}
		else
		{
			pTempY = pNode->parent->parent->lchild;
			if (pTempY->color == RBTreeNode_Red)
			{
				pNode->parent->color = RBTreeNode_Blk;
				pTempY->color = RBTreeNode_Blk;
				pNode->parent->parent->color = RBTreeNode_Red;
				pNode = pNode->parent->parent;
			}
			else 
			{
				if (pNode == pNode->parent->lchild) 
				{
					pNode = pNode->parent;
					RBTreeRightRotate(pNode);
				}

				pNode->parent->color = RBTreeNode_Blk;
				pNode->parent->parent->color = RBTreeNode_Red;
				RBTreeLeftRotate(pNode->parent->parent);
			}
		}
	}
	pTempY = get_root();
	pTempY->color = RBTreeNode_Blk;
}

void RBTree::RBTreeInsert(BTreeNode* pNodeZ) {
#if 0
	BTreeNode* pTempY = RBTreeNil;
	BTreeNode* pTempX = get_root();
	while ( pTempX != RBTreeNil)
	{
		pTempY = pTempX;
		if (pNodeZ->elem < pTempX->elem)
		{
			pTempX = pTempX->lchild;
		}
		else
		{
			pTempX = pTempX->rchild;
		}
	}

	pNodeZ->parent = pTempY;
	if ( pTempY == RBTreeNil)
	{
		set_root(pNodeZ);
	}
	else if (pNodeZ->elem < pTempY->elem)
	{
		pTempY->lchild = pNodeZ;
	}
	else
	{
		pTempY->rchild = pNodeZ;
	}
#else
	BSTree::BSTree_Insert(pNodeZ);
#endif
	pNodeZ->lchild = RBTreeNil;
	pNodeZ->rchild = RBTreeNil;
	pNodeZ->color = RBTreeNode_Red;
	RBTree_Insert_Fixup(pNodeZ);
}

void RBTree::BSTree_Insert(BTreeNode* pNodeZ) {
	BSTree::BSTree_Insert(pNodeZ);
	pNodeZ->lchild = RBTreeNil;
	pNodeZ->rchild = RBTreeNil;
	pNodeZ->color = RBTreeNode_Red;
	RBTree_Insert_Fixup(pNodeZ);
}


void RBTree::RBTreeDeleteFixUp(BTreeNode* pNodeX) {
	BTreeNode* pNodeW = pBTreeNil;

	while ((pNodeX != get_root()) && (pNodeX->color == RBTreeNode_Blk))
	{
		if (is_lchild_node(pNodeX))
		{
			//由于被替换/删除的节点是一个黑色节点，性质4/5或被破坏
			pNodeW = pNodeX->parent->rchild;
			if (pNodeW->color == RBTreeNode_Red)
			{
				//case 1
				//如果pNodeX的右兄弟是红色，把w着色为黑色，父节点着色为红色，沿着x的父节点把树左旋：
				//1. 左旋可以保持w及其子树的性质不变
				//2. 同时把处理的情况转换成case2/3/4后继续处理
				pNodeW->color = RBTreeNode_Blk;
				pNodeX->parent->color = RBTreeNode_Red;
				RBTreeLeftRotate(pNodeX->parent);
				pNodeW = pNodeX->parent->rchild;
			}
			else if ((pNodeW->lchild->color == RBTreeNode_Blk) && (pNodeW->rchild->color == RBTreeNode_Blk))
			{
				//case 2
				//左右孩子都是黑色，把w置为红色，p设置为父节点，由于父节点为红色，不满足循环条件
				//在退出循环的时候会把父节点置为黑色来补偿
				pNodeW->color = RBTreeNode_Red;
				pNodeX = pNodeX->parent;
			}
			else 
			{
				if (pNodeW->rchild->color == RBTreeNode_Blk) {
					//case3
					//左孩子着色为黑色后，黑高度升高了1，需要右转保持黑高度不变，同时变成case4
					pNodeW->lchild->color = RBTreeNode_Blk;
					pNodeW->color = RBTreeNode_Red;
					RBTreeRightRotate(pNodeW);
					pNodeW = pNodeX->parent->rchild;
				}
				//case4
				//只需要基于x的父节点做一次右旋，同时修改叔节点的颜色
				pNodeW->color = pNodeX->parent->color;
				pNodeX->parent->color = RBTreeNode_Blk;
				pNodeX->rchild->color = RBTreeNode_Blk;
				RBTreeLeftRotate(pNodeX->parent);
				pNodeX = get_root();
			}	
		}
		else
		{
			pNodeW = pNodeX->parent->lchild;
			if (pNodeW->color == RBTreeNode_Red)
			{
				pNodeW->color = RBTreeNode_Blk;
				pNodeX->parent->color = RBTreeNode_Red;
				RBTreeLeftRotate(pNodeX->parent);
				pNodeW = pNodeX->parent->lchild;
			}
			else if ((pNodeW->lchild->color == RBTreeNode_Blk) && (pNodeW->rchild->color == RBTreeNode_Blk))
			{
				pNodeW->color = RBTreeNode_Red;
				pNodeX = pNodeX->parent;
			}
			else
			{
				if (pNodeW->lchild->color == RBTreeNode_Blk) 
				{
					//左孩子着色为黑色后，黑高度升高了1，需要右转保持黑高度不变
					pNodeW->rchild->color = RBTreeNode_Blk;
					pNodeW->color = RBTreeNode_Red;
					RBTreeLeftRotate(pNodeW);
					pNodeW = pNodeX->parent->lchild;

				}
				pNodeW->color = pNodeX->parent->color;
				pNodeX->parent->color = RBTreeNode_Blk;
				pNodeX->lchild->color = RBTreeNode_Blk;
				RBTreeRightRotate(pNodeX->parent);
				pNodeX = get_root();
			}
		}
	}
	pNodeX->color = RBTreeNode_Blk;
}
/*
 *节点Z为待删除的节点
 */
void RBTree::RBTreeDelete(BTreeNode* pNodeZ) {
	BTreeNode* pNodeY = pBTreeNil;
	RBTreeNodeType NodeYOrgColor;
	BTreeNode* pNodeX = pBTreeNil;

	pNodeY = pNodeZ;
	NodeYOrgColor = pNodeY->color;

	
	if (pNodeZ->lchild == pBTreeNil)
	{
		//case 1
		//节点Z只有右孩子的时候，把节点的右子树替代节点Z
		pNodeX = pNodeZ->rchild;
		BSTree_Transplant(pNodeZ, pNodeZ->rchild);
	}
	else if (pNodeZ->rchild == pBTreeNil)
	{
		//case2
		//节点Z只有左孩子的时候，把节点的左子树替代节点Z
		pNodeX = pNodeZ->lchild;
		BSTree_Transplant(pNodeZ, pNodeZ->lchild);
	}
	else
	{
		//节点有左右子树的时候，用它的后继来替代节点Z
		pNodeY = BSTree_Minimum(pNodeZ->rchild);
		NodeYOrgColor = pNodeY->color;

		//X记录后继节点的右孩子，因为X需要去替换节点Y，也会破坏红黑树的性质
		pNodeX = pNodeY->rchild;
		if (pNodeY->parent == pNodeZ)
		{
			pNodeX->parent = pNodeY;
		}
		else
		{
			//后继节点不是Z的右孩子时候，需要用X替换Y，这个过程也会破坏红黑树的性质4/5
			BSTree_Transplant(pNodeY, pNodeY->rchild);
			pNodeY->rchild = pNodeZ->rchild;
			pNodeY->rchild->parent = pNodeY;
		}

		BSTree_Transplant(pNodeZ, pNodeY);
		pNodeY->lchild = pNodeZ->lchild;
		pNodeY->lchild->parent = pNodeY;
		//Y替代了Z，同时把Y的颜色置为Z的颜色，保持Z的左上半部性质不变，情况就变成case1/case2
		pNodeY->color = pNodeZ->color;
	}

	//只有删除一个黑色节点的时候才会破坏红黑树的性质,需要调整红黑树
	if (NodeYOrgColor == RBTreeNode_Blk)
	{
		RBTreeDeleteFixUp(pNodeX);
	}
}

BTreeNode* RBTree::RBTreeRightest() {
	return BSTree_Maximum();
}

BTreeNode* RBTree::RBTreeLeftest()
{
	return BSTree_Minimum();
}


AVLTree::AVLTree():BSTree(BTREE_AVL) {

}

AVLTree::~AVLTree() {
	cout << "\n AVLTree::~AVLTree()" << endl;
}

AVLTree::AVLTree(const vector<BTreeElemType>& elem_vec) {
	for (vector<BTreeElemType>::size_type i = 0; i < elem_vec.size(); i++)
	{
		BTreeNode* pNode = new BTreeNode;
		pNode->color = RBTreeNode_MAX;
		pNode->elem = elem_vec[i];
		pNode->parent = pBTreeNil;
		pNode->rchild = pBTreeNil;
		pNode->lchild = pBTreeNil;
		AVLTreeInsert(pNode);
	}
}

bool AVLTree::AVLTreeIsBalance(BTreeNode* pNode) {
	int ltree_h = 0;
	int rtree_h = 0;
	int diff;

	if (!pNode)
	{
		return true;
	}
	ltree_h = btree_height(pNode->lchild);
	rtree_h = btree_height(pNode->rchild);

	diff = max(ltree_h, rtree_h) - min(ltree_h, rtree_h);
	if (diff >= 2)
	{
		return false;
	}

	return true;
}

void AVLTree::AVLTreeInsert(BTreeNode* pNode) {
	BTreeNode* pTempX = pBTreeNil;
	BTreeNode* pTempY = pBTreeNil;
	BTreeNode* ptemp = NULL;

	if (pNode == pBTreeNil)
	{
		return;
	}
	BSTree_Insert(pNode);

	//对于树高小于2的不需要调整
	if (btree_height() < 2)
	{
		return;
	}

	pTempX = pNode->parent->parent;
	pTempY = pNode->parent;
	while (pTempX)
	{
		if (!AVLTreeIsBalance(pTempX))
		{
			if (btree_height(pTempX->lchild) > btree_height(pTempX->rchild))
			{
				if (is_lchild_node(pNode))
				{
					BSTree_RightRotate(pTempX);
					pTempX = pTempY->parent;
				}
				else
				{
					BSTree_LeftRightRotate(pTempY);
					pTempX = pNode->parent;
					ptemp  = pTempY;
					pTempY = pNode;
					pNode  = pTempY;
				}			
			}
			else
			{
				if (is_rchild_node(pNode))
				{
					BSTree_LeftRotate(pTempX);
					pTempX = pTempY->parent;
				}
				else
				{
					BSTree_RightLeftRotate(pTempY);
					pTempX = pNode->parent;
					ptemp  = pTempY;
					pTempY = pNode;
					pNode  = ptemp;
				}
			}
		}
		else
		{
			pNode = pTempY;
			pTempY = pTempX;
			pTempX = pTempX->parent;
		}

	}
}

void AVLTree::AVLTreeDelete(BTreeNode* pNode) {
	BTreeNode* pTempNodeY = pBTreeNil;
	DeleteNodeType del_type;

	int rh = 0, lh = 0;
	lh = btree_height(pNode->lchild);
	rh = btree_height(pNode->rchild);
	if (lh > rh)
	{
		del_type = DELETED_NODE_BY_PRE;
	}
	else
	{
		del_type = DELETED_NODE_BY_SUCC;
	}
	BSTree_Delete(pNode, del_type);

}

void AVLTree::AVLTreeDelete(BTreeElemType key) {
	BTreeNode* pNode = NULL;

	pNode = BSTree_search(key);
	if (!pNode)
	{
		return;
	}

	AVLTreeDelete(pNode);
	delete pNode;
}

OptimalBSTree::OptimalBSTree() {

}

OptimalBSTree::~OptimalBSTree()
{

}


double w[10][10], expTable[10][10];
int root_table[10][10];
void OptimalBSTree::optimal_bst(vector<double> p, vector<double> q) {

	int n;
	int i, j, l, r;
	double t;

	n = p.size() - 1;
#if 0
	w = new double* [n + 2];
	for (i = 0; i <= n + 1; i++)
	{
		w[i] = new double [n + 1];
	}

	expTable = new double* [n + 2];
	for (i = 0; i <= n + 1; i++) {
		expTable[i] = new double[n + 1];
	}

	root_table = new int* [n + 1];
	for (i = 0; i <= n; i++)
	{
		root_table[i] = new int[n + 1];
	}
#endif
	for (i = 1; i <= n + 1; i++)
	{
		expTable[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}

	for (l = 1; l <= n; l++)
	{
		for (i = 1; i <= n - l + 1; i++)
		{
			j = i + l - 1;
			expTable[i][j] = (double)INT_MAX;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (r = i; r <= j; r++)
			{
				t = expTable[i][r - 1] + expTable[r + 1][j] + w[i][j];
				if (t < expTable[i][j])
				{
					expTable[i][j] = t;
					root_table[i][j] = r;
				}
			}
		}
	}
}

int optimal_build_bst(int rootTable[][10], int i, int j, NodeType &type) {
	int r = -1;
	int left = -1;
	int right = -1;

	if (i - 1  == j)
	{
		type = NODE_PSD;
		return j;
	}
	else 
	{
		//kr 是根节点
		type = NODE_KEY;
		r = rootTable[i][j];
		left = r - 1;
		left = optimal_build_bst(rootTable, i, left, type);
		right = r + 1;
		right = optimal_build_bst(rootTable, right, j, type);
		return r;
	}
}

void optBst_test() {
	double p[] = { 0.00, 0.15, 0.10, 0.05, 0.10, 0.20 };
	double q[] = { 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };
	vector<double> pv(p, p + sizeof(p) / sizeof(p[0]));
	vector<double> qv(q, q + sizeof(q) / sizeof(q[0]));
	NodeType type = NODE_KEY;

	OptimalBSTree optBst;

	optBst.optimal_bst(pv, qv);
	optimal_build_bst(root_table, 1, 5, type);
}


BBTree::BBTree(int deg) :root(NULL), degree(deg),dynamic_mem(false) {
}

BBTree::~BBTree() {
	BBTreeDestroy(root);
	root = NULL;
}

void BBTree::BBTreeCreate() {
	root = BBTreeAllocNode();
	root->keyNum = 0;
	//disk_write(root);
	root->leaf = true;
}

BBTreeNode* BBTree::BBTreeSearch(BBTreeNode* BBTree, BBElemType k, int &idx) {
	int i = 0;
	while (i < BBTree->keyNum && k > BBTree->key[i])
	{
		i++;
	}

	if ((i < BBTree->keyNum) && (k == BBTree->key[i]))
	{
		idx = i;
		return BBTree;
	}
	else if (BBTree->leaf)
	{
		return NULL;
	}
	else
	{
		return BBTreeSearch(BBTree->child[i], k, idx);
	}
}

void BBTree::BBTreeSplitChild(BBTreeNode* pNodeX, int i) {
	BBTreeNode* pNodeZ, * pNodeY;
	int j = 0;
	int t = degree;

	pNodeZ = BBTreeAllocNode();
	pNodeY = pNodeX->child[i];

	pNodeZ->leaf = pNodeY->leaf;
	pNodeZ->keyNum = t - 1;

	//设置key
	for (j = 0; j < pNodeZ->keyNum; j++)
	{
		pNodeZ->key[j] = pNodeY->key[j + t];
		pNodeY->key[j + t] = 0;
	}

	
	if (!pNodeY->leaf)
	{
		//非叶子节点，设置child
		for (j = 0; j <= pNodeZ->keyNum; j++)
		{
			pNodeZ->child[j] = pNodeY->child[j + t];
			pNodeY->child[j + t] = NULL;
		}
	}

	pNodeY->keyNum = t - 1;

	//节点X的第i个关键字/孩子都要后移
	//childNum = keyNum + 1
	for (j = pNodeX->keyNum; j >= i + 1; j--)
	{
		pNodeX->child[j + 1] = pNodeX->child[j];
	}
	pNodeX->child[i + 1] = pNodeZ;

	for (j = pNodeX->keyNum - 1; j >= i; j--)
	{
		pNodeX->key[j + 1] = pNodeX->key[j];
	}
	pNodeX->key[i] = pNodeY->key[t - 1];
	pNodeY->key[t - 1] = 0;

	pNodeX->keyNum++;
	//DiskWrite(x)
	//DiskWrite(y)
	//DiskWrite(z)
}

void BBTree::BBTreeInsertNonFull(BBTreeNode* pBBTree, BBElemType key) {
	int i = 0;

	i = pBBTree->keyNum - 1;

	if (pBBTree->leaf)
	{
		while (i >= 0 && pBBTree->key[i] > key)
		{
			pBBTree->key[i + 1] = pBBTree->key[i];
			i--;
		}

		pBBTree->key[i + 1] = key;
		//
		pBBTree->keyNum++;
		//DiskWrite()
	}
	else
	{
		int t = degree;
		while (i >= 0 && key < pBBTree->key[i])
		{
			i--;
		}

		i++;

		//DiskRead(pBBTree->child[i])
		if (pBBTree->child[i]->keyNum == ((t << 1) - 1))
		{
			BBTreeSplitChild(pBBTree, i);
			if (key > pBBTree->key[i])
			{
				i += 1;
			}
		}
		
		BBTreeInsertNonFull(pBBTree->child[i], key);
	}
}

void BBTree::BBTreeInsert(BBElemType key) {
	BBTreeNode* r = root;
	if (r->keyNum == ((degree << 1) - 1))
	{
		// root 是满的，先把root分裂
		BBTreeNode* s = BBTreeAllocNode();

		root = s;
		s->leaf = false;
		s->keyNum = 0;
		s->child[0] = r;

		BBTreeSplitChild(s, 0);
		BBTreeInsertNonFull(s, key);
	}
	else
	{
		BBTreeInsertNonFull(r, key);
	}
}

BBElemType BBTree::BBTreeSmallest() {
	BBTreeNode* pNode = NULL;

	pNode = root;
	while (pNode && !pNode->leaf)
	{
		pNode = pNode->child[0];
	}

	return pNode->key[0];
}

BBElemType BBTree::BBTreeLargest(BBTreeNode* pBBTree) {
	while (pBBTree->child[pBBTree->keyNum])
	{
		pBBTree = pBBTree->child[pBBTree->keyNum];
	}

	return pBBTree->key[pBBTree->keyNum - 1];
}

BBTreeNode* BBTree::BBTreeParent(BBTreeNode* pBBTree,BBElemType key, int &idx) {
	int i = 0;
	BBTreeNode* pNode;

	pNode = BBTreeSearch(root, key,idx);
	if (!pBBTree || !pNode)
	{
		return NULL;
	}

	if (pNode == pBBTree)
	{
		return pBBTree;
	}

	while ((i < pBBTree->keyNum) && (pBBTree->key[i] <= pNode->key[0]))
	{
		i++;
	}
	//i--;

	if (pBBTree->child[i] == pNode)
	{
		idx = i;
		return pBBTree;
	}
	else
	{
		return BBTreeParent(pBBTree->child[i], key, idx);
	}
}

BBElemType BBTree::BBTreePrecedence(BBTreeNode* pBBTree, BBElemType key) {
	BBTreeNode* pNode = NULL;
	BBTreeNode* parent = NULL;
	int idx = 0;
	int p_idx = 0;

	pNode = BBTreeSearch(pBBTree, key, idx);


	if (pNode && key != BBTreeSmallest())
	{
		if (pNode->leaf)
		{
			return pNode->key[idx - 1];
		}

		return BBTreeLargest(pNode->child[idx]);
	}

	return -1;
}

BBElemType BBTree::BBTreePrecedence(BBElemType key) {
	return BBTreePrecedence(root, key);
}

BBElemType BBTree::BBTreeSucessor(BBTreeNode* pBBTree, BBElemType key) {
	BBTreeNode* pNode = NULL;
	int idx = 0;

	pNode = BBTreeSearch(pBBTree, key, idx);

	if (pNode && key != BBTreeLargest(root))
	{
		if (pNode->leaf)
		{
			return pNode->key[idx + 1];
		}

		return BBTreeLargest(pNode->child[idx + 1]);
	}

	return -1;
}

BBTreeNode* BBTree::BBTreeAllocNode() {
	BBTreeNode* pNode = NULL;

	pNode = new BBTreeNode;
	memset(pNode, 0, sizeof(*pNode));
#ifdef BBTREE_USE_STATIC_MEM
	//
#else
	pNode->key = new BBElemType[(degree << 1) - 1 + 1];
	memset(pNode->key, 0, sizeof(BBElemType) * ((degree << 1) - 1 + 1));
	pNode->child = new struct BBTreeNode* [degree << 1];
	memset(pNode->child, 0, sizeof(BBTreeNode*) * (degree << 1));
	dynamic_mem = true;
#endif
	pNode->leaf = true;
	return pNode;
}

void BBTree::BBTreeInorderTraverse(BBTreeNode* pBBTree) {
	int i = 0;
	if (pBBTree->leaf)
	{
		cout << "*** ";
		for (i = 0; i < pBBTree->keyNum; i++)
		{
			cout << pBBTree->key[i];
		}
		cout << endl;
		return;
	}
	for (i = 0; i < pBBTree->keyNum; i++)
	{
		BBTreeInorderTraverse(pBBTree->child[i]);
		cout << "### " << pBBTree->key[i];
	}
	BBTreeInorderTraverse(pBBTree->child[pBBTree->keyNum]);
}

BBTreeNode* BBTree::BBTreeRoot() {
	return root;
}

BBTreeNode* BBTree::BBTreeMergeChild(BBTreeNode* pNodeX, int i) {
	BBTreeNode* pNodeY, * pNodeZ;
	BBTreeNode* parent = NULL;
	int idx = -1;

	int j = 0;
	pNodeY = pNodeX->child[i];
	pNodeZ = pNodeX->child[i + 1];

	if (pNodeY && pNodeZ)
	{
		if ((pNodeX->keyNum == degree - 1) && (pNodeY->keyNum == degree - 1))
		{
			parent = BBTreeParent(root, pNodeX->key[0], idx);
		}
	}

	j = degree;
	pNodeY->key[degree - 1] = pNodeX->key[i];

	for (j = 0; j < degree - 1; j++)
	{
		pNodeY->key[j + degree] = pNodeZ->key[j];
	}

	if (!pNodeY->leaf)
	{
		for (j = 0; j <= degree - 1; j++)
		{
			pNodeY->child[j + degree] = pNodeZ->child[j];
		}	
	}

	pNodeY->keyNum += degree;

	for (j = i + 1; j < pNodeX->keyNum; j++)
	{
		pNodeX->child[j] = pNodeX->child[j + 1];
		pNodeX->key[j - 1] = pNodeX->key[j];
	}
	pNodeX->child[pNodeX->keyNum] = NULL;
	pNodeX->key[--pNodeX->keyNum] = 0;


	if (dynamic_mem)
	{
		delete [] pNodeZ->child;
		delete[] pNodeZ->key;
	}
	delete pNodeZ;


	if (pNodeX->keyNum == 0)
	{
		if (parent == root)
		{
			root = pNodeX->child[0];
		}
		else
		{
			parent->child[idx] = pNodeX->child[0];
		}
		pNodeZ = pNodeX->child[0];
		
		if (dynamic_mem)
		{
			delete[]pNodeX->child;
			delete[]pNodeX->key;
		}
		delete pNodeX;
		pNodeX = pNodeZ;
	}

	return pNodeX;
}

void BBTree::BBTreeParentDownPreUp(BBTreeNode* pNodeX, int i, BBTreeNode* pNodeY, BBTreeNode* pNode)
{
	int j = 0;

	for (j = pNode->keyNum - 1; j >= 0; j--)
	{
		pNode->key[j + 1] = pNode->key[j];

	}

	if (!pNode->leaf)
	{
		for (j = pNode->keyNum; j >= 0; j--)
		{
			pNode->child[j + 1] = pNode->child[j];
		}
	}

	pNode->key[0] = pNodeX->key[i - 1];
	pNode->child[0] = pNodeY->child[pNodeY->keyNum];
	pNode->keyNum++;
	pNodeX->key[i - 1] = pNodeY->key[pNodeY->keyNum - 1];


	pNodeY->child[pNodeY->keyNum] = NULL;
	pNodeY->key[pNodeY->keyNum - 1] = 0;
	pNodeY->keyNum--;
}

void BBTree::BBTreeParentDownSucUp(BBTreeNode* pNodeX, int i, BBTreeNode* pNodeZ, BBTreeNode* pNode)
{
	int j = -1;
	//case 3.b
	pNode->key[pNode->keyNum] = pNodeX->key[i];
	pNode->keyNum++;
	pNode->child[pNode->keyNum] = pNodeZ->child[0];

	pNodeX->key[i] = pNodeZ->key[0];
	for (j = 0; j < pNodeZ->keyNum - 1; j++)
	{
		pNodeZ->key[j] = pNodeZ->key[j + 1];
	}
	//把最后一个key清零
	pNodeZ->key[j] = 0;

	if (!pNodeZ->leaf)
	{
		for (j = 0; j < pNodeZ->keyNum; j++)
		{
			pNodeZ->child[j] = pNodeZ->child[j + 1];
		}
	}
	pNodeZ->keyNum--;
}

void BBTree::BBTreeDelete(BBTreeNode* pNodeX, BBElemType key) {
	int i = 0;
	int j = 0;
	BBTreeNode* pNodeY, * pNodeZ, *pNode;
	BBElemType key_bar;

	while (i < pNodeX->keyNum && key != pNodeX->key[i])
	{
		i++;
	}

	if (i == pNodeX->keyNum)
	{
		//case 3：关键字不在当前节点X中, 查找包含key的子树child[i]
		i--;
		while (i >= 0 && pNodeX->key[i] > key)
		{
			i--;
		}
		i++;

		pNode = pNodeX->child[i];
		if (i > 0 && i < pNodeX->keyNum)
		{
			pNodeY = pNodeX->child[i - 1];
			pNodeZ = pNodeX->child[i + 1];
		}
		else if( i == 0)
		{
			pNodeZ = pNodeX->child[i + 1];
			pNodeY = NULL;
		}
		else
		{
			pNodeY = pNodeX->child[i - 1];
			pNodeZ = NULL;
		}


		if (pNode && (pNodeY || pNodeZ))
		{
			if (pNode->keyNum == degree - 1)
			{
				if (pNodeY && pNodeZ)
				{
					if ((pNodeY->keyNum == degree - 1) && (pNodeY->keyNum == degree - 1))
					{
						//case 3.a
						BBTreeNode* ptemp = pNodeX;
						pNodeX = BBTreeMergeChild(pNodeX, i);
						if (pNodeX != ptemp)
						{
							BBTreeDelete(ptemp, key);
						}
						else
						{
							BBTreeDelete(pNodeX->child[i], key);
						}
						
					}
					else
					{
						if (pNodeY->keyNum >= degree)
						{
							BBTreeParentDownPreUp(pNodeX, i, pNodeY, pNode);
						}
						else
						{
#if 0
							//case 3.b
							pNode->key[pNode->keyNum] = pNodeX->key[i];
							pNode->keyNum++;
							pNode->child[pNode->keyNum] = pNodeZ->child[0];

							pNodeX->key[i] = pNodeZ->key[0];
							for (j = 0; j < pNodeZ->keyNum - 1; j++)
							{
								pNodeZ->key[j] = pNodeZ->key[j + 1];
							}
							//把最后一个key清零
							pNodeZ->key[j] = 0;

							if (!pNodeZ->leaf)
							{
								for (j = 0; j < pNodeZ->keyNum; j++)
								{
									pNodeZ->child[j] = pNodeZ->child[j + 1];
								}
							}
							pNodeZ->keyNum--;
#else
							BBTreeParentDownSucUp(pNodeX, i, pNodeZ, pNode);
#endif
						}


						BBTreeDelete(pNode, key);
					}
				}
				else if (pNodeY)
				{
					//如果前驱兄弟存在的话
					if (pNodeY->keyNum == degree - 1)
					{
						//case 3.a
						BBTreeNode* ptemp = pNodeX;					
						i--;
						pNodeX = BBTreeMergeChild(pNodeX, i);
						if (pNodeX != ptemp)
						{
							BBTreeDelete(ptemp, key);
						}
						else
						{
							BBTreeDelete(pNodeX->child[i], key);
						}
					}
					else
					{
						//case 3.b
						BBTreeParentDownPreUp(pNodeX, i, pNodeY, pNode);
						BBTreeDelete(pNode, key);
					}
				}
				else if (pNodeZ) 
				{
					if (pNodeZ->keyNum == degree - 1)
					{
						//case 3.a
						BBTreeNode* ptemp = pNodeX;
						pNodeX = BBTreeMergeChild(pNodeX, i);
						if (pNodeX != ptemp)
						{
							BBTreeDelete(ptemp, key);
						}
						else
						{
							BBTreeDelete(pNodeX->child[i], key);
						}
					}
					else
					{
#if 0
						//case 3.b
						pNode->key[pNode->keyNum] = pNodeX->key[i];
						pNode->keyNum++;
						pNode->child[pNode->keyNum] = pNodeZ->child[0];

						pNodeX->key[i] = pNodeZ->key[0];
						for (j = 0; j < pNodeZ->keyNum - 1; j++)
						{		
							pNodeZ->key[j] = pNodeZ->key[j + 1];
						}

						//把最后一个key清零
						pNodeZ->key[j] = 0;

						if (!pNodeZ->leaf)
						{
							for (j = 0; j < pNodeZ->keyNum; j++)
							{
								pNodeZ->child[j] = pNodeZ->child[j + 1];
							}
						}
						pNodeZ->keyNum--;
#else
						BBTreeParentDownSucUp(pNodeX, i, pNodeZ, pNode);
#endif
						BBTreeDelete(pNode, key);
					}
				}
			}
			else
			{
				BBTreeDelete(pNode, key);
			}
		}
	}
	else if (pNodeX->leaf)
	{
		//case 1, X is leaf node
		for (j = i; j < pNodeX->keyNum; j++)
		{
			pNodeX->key[j] = pNodeX->key[j + 1];
		}

		pNodeX->keyNum--;
		return;
	}
	else
	{
		pNodeY = pNodeX->child[i];
		pNodeZ = pNodeX->child[i + 1];
		if (pNodeY->keyNum >= degree)
		{
			//case 2: 在节点Y中找前驱
			//key_bar = pNodeY->key[pNodeY->keyNum - 1];
			key_bar = BBTreePrecedence(key);
			BBTreeDelete(pNodeY, key_bar);
			pNodeX->key[i] = key_bar;
		}
		else if (pNodeZ->keyNum >= degree)
		{
			//case 2: 在节点Z中找后继
			key_bar = pNodeZ->key[0];
			BBTreeDelete(pNodeZ, key_bar);
			pNodeX->key[i] = key_bar;
		}
		else
		{
			BBTreeNode* ptemp = pNodeX;
			pNodeX = BBTreeMergeChild(pNodeX, i);
			if (pNodeX != ptemp)
			{
				BBTreeDelete(ptemp, key);
			}
			else
			{
				BBTreeDelete(pNodeX->child[i], key);
			}
		}
	}
}

void BBTree::BBTreeDestroy(BBTreeNode* pBBTree) {
	int i = 0;
	if (pBBTree->leaf)
	{
		if (pBBTree->child)
		{
			if (dynamic_mem)
			{
				delete[]pBBTree->child;
			}
		}
		
		if (pBBTree->key)
		{
			if (dynamic_mem)
			{
				delete[]pBBTree->key;
			}	
		}
		delete pBBTree;
		return;
	}
	for (i = 0; i < pBBTree->keyNum; i++)
	{
		BBTreeDestroy(pBBTree->child[i]);
	}
	BBTreeDestroy(pBBTree->child[pBBTree->keyNum]);
	delete pBBTree;
}


void BBTreeTest()
{
	string str = "FSQKCLHTVWMRNPABXYDZE";
	//string str = "DCBA";
	BBTree bbtree;
	bbtree.BBTreeCreate();
	int idx;
	BBTreeNode* pNode = NULL;
	for (string::size_type i = 0; i < str.length(); i++)
	{
		bbtree.BBTreeInsert(str[i]);
	}

	pNode = bbtree.BBTreeParent(bbtree.BBTreeRoot(), 'X', idx);

	//bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'D');

#if 1
	bbtree.BBTreeInorderTraverse(bbtree.BBTreeRoot());
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'A');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'B');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'C');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'D');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'E');
	bbtree.BBTreePrecedence('Q');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'Q');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'V');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'L');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'R');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'X');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'Y');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'Z');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'W');
	bbtree.BBTreeDelete(bbtree.BBTreeRoot(), 'K');
#endif
}
