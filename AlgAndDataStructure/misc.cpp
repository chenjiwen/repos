#include "stack.h"

#if 0

const int josephus_people_num = 7;
const int delivery_cnt = 3;

int josephus_game_arary[josephus_people_num];
int left_num = josephus_people_num;

int free_idx(int idx)
{
	int i = (idx + 1)%josephus_people_num;
	int j = 0;

	while (1)
	{
		if (josephus_game_arary[i] != -1)
		{
			j++;
			if (j == delivery_cnt)
			{
				break;
			}
		}
		i++;
		i %= josephus_people_num;
	}

	return i;
}

int next_idx(int idx) {
	while (1)
	{
		idx++;
		idx %= josephus_people_num;
		if (josephus_game_arary[idx] != -1)
		{
			return idx;
		}
	}
}

int josephus_game()
{
	int idx = 0;
	for (idx = 0; idx < josephus_people_num; idx++)
		josephus_game_arary[idx] = idx + 1;

	idx = 0;
	while (left_num != 1)
	{
		idx = free_idx(idx);
		josephus_game_arary[idx] = -1;
		idx = next_idx(idx);
		left_num--;
	}
	return idx;
}

#else
int josephus_game() {
	return 0;
}

LinkList_T* josephus_game(int N, int M) {
	int i = 0; 
	int step = 0;
	LinkList_T* pCList = NULL;
	LinkList_T* prev = NULL;

	for (i = 0; i < N; i++)
	{
		circle_list_add(pCList, i + 1);
	}

	while (pCList->next != pCList)
	{
		step = M;
		while (step)
		{
			prev = pCList;
			pCList = pCList->next;
			step--;
		}

		prev->next = pCList->next;
		pCList->next = NULL;
		delete pCList;
		pCList = prev->next;
	}
	return pCList;
}

/*
 *
 */

LinkList_T* NextNth(LinkList_T* cur, int& n) {
	n--;
	while (cur && cur->next && n)
	{
		cur = cur->next;
		n--;
	}
	return cur;
}

LinkList_T* removeNthFromEnd(LinkList_T* head, int n) {
	LinkList_T* prev_tail = NULL, * cur_tail = NULL, * cur_head = NULL, * prev_head = NULL;
	LinkList_T* cur = NULL;
	int step;

	cur_head = head;
	cur = head;

	do {
		step = n;
		prev_tail = cur_tail;
		prev_head = cur_head;
		cur_head = cur;
		cur_tail = NextNth(cur, step);
		cur = cur_tail->next;
	} while (cur && !step);

	if (!cur && !step)
	{
		if (cur_head == head)
		{
			if (!head->next)
			{
				delete head;
				return NULL;
			}
			else
			{
				cur = head;
				head = head->next;
				delete cur;
			}
		}
		else 
		{
			prev_tail->next = cur_head->next;
			cur_head->next = NULL;
			delete cur_head;
		}
	}
	else
	{
		step = n - step;
		cur_tail = NextNth(prev_head, step);
		cur = cur_tail->next;
		cur_tail->next = cur->next;
		cur->next = NULL;
		delete cur;
	}

	return head;
}

LinkList_T* list_swap_pairs(LinkList_T* head) {
	LinkList_T* prev = NULL, * next = NULL;
	LinkList_T* pNode = NULL;

	if (!head || !head->next)
	{
		return head;
	}
	prev = NULL;

	LinkList_T* pOdd = NULL, * pEven = NULL;
	LinkList_T* pNextOdd = NULL, * pNextEven = NULL;

	pOdd = head;
	pEven = pOdd->next;

	while (pOdd) {
		//当前奇数节点
		pEven = pOdd->next;

		//奇数节点后没有偶数节点，结束
		if (!pEven)
			break;

		if (!prev)
		{
			prev = pEven;
		}
		//有偶数节点
		if (pEven)
		{
			//记录下一个奇数节点
			pNextOdd = pEven->next;

			//要是下一个奇数节点存在的话，记录跟着它的下一个偶数节点
			if (pNextOdd)
				pNextEven = pNextOdd->next;
			else
				pNextEven = NULL;

			//如果存在下一个偶数节点，当前的奇数节点连接到下一个偶数节点
			if (pNextEven)
				pOdd->next = pNextEven;
			else
				pOdd->next = pNextOdd;

			pEven->next = pOdd;
			pOdd = pNextOdd;
		}
	}
	return prev;
}

#endif


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<TreeNode*> generateTrees(int n) {
		if (n) return generate(1, n);
		else return vector<TreeNode*>{};
	}

	vector<TreeNode*> generate(int left, int right) {
		vector<TreeNode*> ans;
		if (left > right) {
			ans.push_back(NULL);
			return ans;
		}
		for (int i = left; i <= right; i++) {
			vector<TreeNode*> left_nodes = generate(left, i - 1);
			vector<TreeNode*> right_nodes = generate(i + 1, right);
			for (TreeNode* left_node : left_nodes) {
				for (TreeNode* right_node : right_nodes) {
					TreeNode* t = new TreeNode(i);
					t->left = left_node;
					t->right = right_node;
					ans.push_back(t);
				}
			}
		}
		return ans;
	}
};

void bst_test()
{
	Solution s;
	s.generateTrees(3);
}