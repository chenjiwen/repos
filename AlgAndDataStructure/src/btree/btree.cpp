#include "btree.h"
#include <iostream>
#include <vector>
using namespace std;

BTree::BTree(BinaryTreeType type):tree_type(type),root(NULL), pBTreeNil(NULL){

}

BTree::BTree(const BTreeElemType& elem, BinaryTreeType type):tree_type(type), pBTreeNil(NULL) {

}

BTree::BTree(const vector<BTreeElemType>& vec_elem, BinaryTreeType type):tree_type(type),pBTreeNil(NULL) {

}

BTree::BTree(const BTreeNode* pNode, BinaryTreeType type):root((BTreeNode*)pNode), tree_type(type),pBTreeNil((BTreeNode*)pNode){

}

BTree::~BTree() {
    //release the tree
}

void visit_node(const BTreeNode* pBtreeNode)
{
	cout << pBtreeNode->elem << " ";
}

bool BTree::is_leaf_node(const BTreeNode* pNode) {
	if ((pBTreeNil == pNode->lchild) && (pBTreeNil == pNode->rchild))
	{
		return true;
	}
	return false;
}

bool BTree::is_lchild_node(const BTreeNode* pNode) {
	return pNode == pNode->parent->lchild;
}

bool BTree::is_rchild_node(const BTreeNode* pNode) {
	return pNode == pNode->parent->rchild;
}

bool BTree::is_root_node(const BTreeNode* pNode) {
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

bool BTree::is_lchild(const BTreeNode* pNode, const BTreeNode* parent) {
	return parent->lchild == pNode;
}

bool BTree::is_parent(const BTreeNode* pNode, const BTreeNode* parent) {
	return pNode->parent == parent;
}

bool BTree::is_rchild(const BTreeNode* pNode, const BTreeNode* parent) {
	return parent->rchild == pNode;
}

bool BTree::is_node_descendant(const BTreeNode* descendant, const BTreeNode* ancestor) {
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
		return 0;
	}

	return max(btree_height(btree->lchild), btree_height(btree->rchild)) + 1;
}

int BTree::btree_height() {
	return btree_height(root);
}

void BTree::btree_build() {

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


BSTree::BSTree()
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

	if (pBTreeNil != pNode->lchild)
	{
		BSTree_Transplant(pNode, pNode->rchild);
	}
	else if (pBTreeNil != pNode->rchild)
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

			//get uncle 
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
				if (pNode == pNode->parent->rchild) 
				{
					pNode = pNode->parent;
					RBTreeLeftRotate(pNode);
				}
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
				//只需要基于x的父节点做一次右旋，同时修改w->
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
