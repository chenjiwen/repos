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

BTree::BTree(const BTreeNode* pNode, BinaryTreeType type):root((BTreeNode*)pNode), tree_type(type),pBTreeNil(NULL){

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
	return pNode->parent == NULL;
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
	BTreeNode* parent = NULL;

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
 *���������
 *    �ȷ������������ٷ��ʵ�ǰ�ڵ㣬������������
 */
void BTree::btree_inorder_traverse_non_recursive_1(const BTreeNode* btree) {
	vector<BTreeNode*> stack;
	BTreeNode* pNode = NULL;
	BTreeNode* prevNode = NULL;

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
			 *��ǰ��Ҷ�ӽڵ�����������Ѿ����ʽ��������ʵ�ǰ�ڵ㲢�ҳ�ջ��
			 *�����ǰ�ڵ����Һ��ӣ��Һ�����ջ
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
			 *��ǰ�ڵ㲻��Ҷ�ӽڵ㣬������������û�з��ʣ���������ӣ�������ջ
			 */
			if (pNode->lchild)
			{
				stack.push_back(pNode->lchild);
			}
			else
			{
				/*
				 *�����ǰ�ڵ�û��������������������������Ҫ���ʵ�ǰ�ڵ㲢��֮��������ѹջ
				 *Ϊ�˱��ֳ���һ���ԣ�ͨ������prevNode = pNode->rchild��˵���������Ѿ����ʽ�����������
				 *is_node_descendant���ж��У�prevNodeΪNULLʱ������false�����ڵ�ǰ�ڵ�������Ϊ�գ�����������Ϊ�յ�ʱ��
				 *ͨ��һ��trickey�ķ���������prevNode = pNode->rchild����ʾ��ǰ���������Ѿ����ʽ���
				 */
				prevNode = pNode->rchild;
			}
		}
	}
}

void BTree::btree_inorder_traverse_non_recursive(const BTreeNode* btree) {
	vector<BTreeNode*> stack;
	BTreeNode* pNode = NULL;
	BTreeNode* prevNode = NULL;

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
                 *��ǰ�ڵ㻹û�п�ʼ���ʣ����е����ӿ�ʼѹջ
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
                 *��ǰ�ڵ�������Ѿ����ʽ��������ʵ�ǰ�ڵ㣬����Һ����еĻ����Һ��ӽڵ�ѹջ
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
			 *��ǰ�����ӣ�ֱ�ӷ��ʣ�����Һ��Ӵ��ڵĻ����Һ���ѹջ
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
 *���������
 *    �ȱ������������ٱ����������������ʸ��ڵ�
 */
void BTree::btree_postorder_traverse_non_recursive() {
	vector<BTreeNode*> stack;
	BTreeNode* pNode = NULL;
	BTreeNode* prevNode = NULL;

	pNode = (BTreeNode*)root;

	stack.push_back(pNode);
	while (!stack.empty())
	{
		pNode = stack.back();

		if (is_node_descendant(prevNode, pNode) || is_leaf_node(pNode))
		{
			/*
			 *��ǰ�ڵ���Ҷ�ӽڵ���ߵ�ǰ�ڵ�ĺ���Ѿ����ʽ��������ʵ�ǰ�ڵ�ͳ�ջ
			 */
			stack.pop_back();
			prevNode = pNode;
			visit_node(pNode);
			continue;
		}
		else 
		{
			/*
			 *��ǰ�ڵ㲻��Ҷ�ڵ����������û�з��ʣ���ѹջ�ҽڵ㣬��ѹջ��ڵ�
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
	BTreeNode* pNode = NULL;
	BTreeNode* prevNode = NULL;

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
			pNode->parent = NULL;
			pNode->lchild = NULL;
			pNode->rchild = NULL;
			stack.push_back(pNode);
		}
		else 
		{
			pNode = new BTreeNode;
			pNode->elem = elem_array[i];
			pNode->parent = NULL;
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
	BTreeNode* pBSTreeNode = NULL;

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
	BTreeNode* pBSTreeNode = NULL;
	pBSTreeNode = get_root();

	while ((pBSTreeNode != pBTreeNil) && (pBTreeNil != pBSTreeNode->lchild))
	{
		pBSTreeNode = pBSTreeNode->lchild;
	}

	return pBSTreeNode;
}

BTreeNode* BSTree::BSTree_Maximum() {
	BTreeNode* pBSTreeNode = NULL;
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
	BTreeNode* pBSTreeNode = NULL;

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
	BTreeNode* pBSTreeNode = NULL;

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

void BSTree::BSTree_Insert(BTreeNode* pBSTree, BTreeNode* pNode) {
	BTreeNode* pTempNodeX = NULL;
	BTreeNode* pTempNodeY = NULL;

	pTempNodeX = pBSTree;
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
	if (pTempNodeX == pBTreeNil)
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
	if (pNodeU->parent != pBTreeNil)
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

	if (pNodeV)
	{
		pNodeV->parent = pNodeU->parent;
	}
}

void BSTree::BSTree_Delete(BTreeNode* pNode, DeleteNodeType replaceBy) {
	BTreeNode* pTempNodeY = NULL;

	if (!pNode->lchild)
	{
		BSTree_Transplant(pNode, pNode->rchild);
	}
	else if (!pNode->rchild)
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
 *static��Ա���������ⶨ��,������������
 *static��Ա������ΪĬ��ʵ��
 */
BTreeNode RBTree::RBTreeNIL = { RBTreeNode_Blk, -1, NULL, NULL,NULL };
RBTree::RBTree():RBTreeNil(&(RBTree::RBTreeNIL)), BSTree(NULL, BTREE_RB)
{
	set_root(RBTreeNil);
}

RBTree::RBTree(const BTreeElemType elem_array[], int len): RBTreeNil(&(RBTree::RBTreeNIL)), BSTree(NULL, BTREE_RB)
{
	int i = 0;
	BTreeNode* pNode = NULL;
	set_root(RBTreeNil);
	for (i = 0; i < len; i++)
	{
		pNode = new BTreeNode;
		pNode->color = RBTreeNode_Blk;
		pNode->elem = elem_array[i];
		pNode->lchild = RBTreeNil;
		pNode->rchild = RBTreeNil;
		pNode->parent = RBTreeNil;
		RBTreeInsert(pNode);
	}
}

RBTree::~RBTree() 
{

}

void RBTree::RBTreeLeftRotate(BTreeNode* pNode) {
	BTreeNode* pTempNodeY = NULL;
	BTreeNode* pRBTreeRoot = NULL;

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
	BTreeNode* pNodeY = NULL;
	BTreeNode* pRBTreeRoot = NULL;

	pRBTreeRoot = get_root();

	//step1: ��NodeY���Һ��Ӽ޽ӵ�NodeX��������
	//��ȡ����
	pNodeY = pNodeX->lchild;
	if (pNodeY == RBTreeNil)
	{
		return;
	}

	//NodeX�������޸�ΪNodeY���Һ���
	pNodeX->lchild = pNodeY->rchild;

	//�޸�NodeY���Һ��ӵĸ��ڵ㣬
	if (pNodeY->rchild->parent != RBTreeNil)
	{
		pNodeY->rchild->parent = pNodeX; 
	}

	//�޸�NodeY�ĸ��ڵ�ΪNodeX�ĸ��ڵ�
	pNodeY->parent = pNodeX->parent;

	//�޸�NodeX�ĸ��ڵ�ĺ��ӽڵ�ΪNodeY
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

	//�޸�NodeY���Һ��ӽڵ�
	pNodeY->rchild = pNodeX;
	//�޸�NodeX�ĸ��ڵ�
	pNodeX->parent = pNodeY;
}

/*
 *�����������һ�Ŷ���������������������
 *    1.ÿ���ڵ��Ǻ�ɫ���ߺ�ɫ��
 *    2.���Ǻ�ɫ��
 *    3.ÿ��Ҷ�ӽڵ��Ǻ�ɫ��
 *    4.���һ���ڵ��Ǻ�ɫ�ģ������������ӽڵ㶼�Ǻ�ɫ��
 *    5.��ÿ���ڵ㣬�Ӹýڵ㵽�������к��Ҷ�ӽڵ�ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ�ڵ�
 *
 *
 *����һ���ڵ��ʱ�򣬻��Ĭ�ϵĽڵ���ɫ����ΪRed������������һ���ڵ㵽�������ʱ������
 *1.3.5�������ƻ���ֻ���ƻ��ƻ���������(2)��(4)��Ҳ�����²���Ľڵ���ܻ��Ǹ��ڵ㣬����
 *�Ǻ�ɫ���ߺ�ɫ�ڵ���뵽һ����ɫ�ڵ���ƻ�������4.�����Ҫ�Ժ�������е���ʹ�䱣�ֺ��
 *�������ʡ�
 *
 *������һ���ڵ�ʱ�����˵�һ���Ǹ��ڵ����⣬�������������ѽڵ���뵽�����棬��ʱ��������״
 *ֻ������6�ֿ��ܣ�
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
 *����case 1�Ĳ������£�
 *    (a).B/C��ɫΪ��ɫ
 *    (b).A��ɫΪ��ɫ
 *    (c).N<-A��N������A��λ�ü������������
 *
 *
 *����case 2:
 *    ��B/N��һ������ת���ͱ��case 1����״
 *
 *����case 3:
 *    ��B��ɫ��ɫ����A��ɫ��ɫ�ͽ��������4��ì�ܣ�������ʱ��A���������ĺڸ߶�
 *������ɫ�ĵ������Ӷ�����A�����������ĸ߶ȶ�����1������ɫ���B\A��һ������ת��
 *���ǲ��ı����������������ʣ�ͬʱ�ָ��˽ڵ�A/�����������ĺڸ߶ȣ�ͬʱ���ڰ�B��ɫ
 *Ϊ��ɫ������ת�󲻻�ı�B���������ĸ߶�
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
			else if (pNode == pNode->parent->rchild)
			{
				pNode = pNode->parent;
				RBTreeLeftRotate(pNode);
			}
			else
			{
				//�常�Ǻ�ɫ
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
			else if (pNode == pNode->parent->lchild)
			{
				pNode = pNode->parent;
				RBTreeRightRotate(pNode);
			}
			else
			{
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

	pNodeZ->lchild = RBTreeNil;
	pNodeZ->rchild = RBTreeNil;
	pNodeZ->color = RBTreeNode_Red;
	RBTree_Insert_Fixup(pNodeZ);
}