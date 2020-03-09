#include "stack.h"
#include "misc.h"
#include "queue.h"
#include<iostream>
using namespace std;

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

int a[8][8] = { {1, 1, 1, 0, 1, 1, 1, 0},
				{0, 1, 0, 1, 1, 0, 1, 1},
				{0, 1, 1, 0, 1, 1, 0, 1},
				{0, 0, 1, 1, 0, 1, 1 ,1},
				{0, 0, 0, 1, 0, 1, 1, 0},
				{0, 1, 1, 1, 0, 1, 1, 1},
				{0, 1, 0, 0, 1, 1, 0, 1},
				{0, 1, 1, 1, 1, 0, 0, 1}
};
PuzzleTable puzzleTbl[puzzle_array_size][puzzle_array_size];

void puzzleInit()
{
	int i, j = 0;
	for (i = 0; i < puzzle_array_size; i++)
	{
		for (j = 0; j < puzzle_array_size; j++)
		{
			puzzleTbl[i][j].val = a[i][j];
			puzzleTbl[i][j].path = { -1, -1 };
			puzzleTbl[i][j].color = WHITE;
		}
	}
}

void printPath(PosT& pos)
{
	cout << '(' << pos.x_p << ',' << pos.y_p << ')' << endl;
}

void PuzzlePath(PosT& start, PosT& end)
{
	PosT curPos = end;

	cout << "\nPuzzleBFS Path:" << endl;
	printPath(end);
	while (puzzleTbl[curPos.x_p][curPos.y_p].color == BLACK && !(curPos.x_p == start.x_p && curPos.y_p == start.y_p))
	{
		printPath(puzzleTbl[curPos.x_p][curPos.y_p].path);
		curPos = puzzleTbl[curPos.x_p][curPos.y_p].path;
	}
}

bool validPos(PosT& pos)
{
	if (pos.x_p <= puzzle_array_size - 1 && pos.x_p >= 0 && pos.y_p <= puzzle_array_size - 1 && pos.y_p >= 0)
		return true;

	return false;
}

bool CheckIfNeedEnqueue(PosT& pos_adj, LinearQue& LQue)
{
	PosT* pos;
	if (validPos(pos_adj) && (puzzleTbl[pos_adj.x_p][pos_adj.y_p].color == WHITE))
	{
		//如果左边节点合法且是白色的节点
		if (puzzleTbl[pos_adj.x_p][pos_adj.y_p].val == 0)
		{
			//如果左边的位置上的值为0/不通
			puzzleTbl[pos_adj.x_p][pos_adj.y_p].color = GRAY;
		}
		else
		{
			//如果位置可通，需要入列
			pos = new PosT;
			pos->x_p = pos_adj.x_p;
			pos->y_p = pos_adj.y_p;
			LQue.Enqueue(pos);
			return true;
		}
	}
	return false;
}

void PuzzleSolutionBFS(PosT& start, PosT& end)
{
	LinearQue LQue;
	PosT curPos;
	PosT* pos = NULL;
	PosT left, right, up, bottom;
	bool found = false;

	if (!validPos(start) || !validPos(end))
	{
		return;
	}

	if (puzzleTbl[start.x_p][start.y_p].val == 0 || puzzleTbl[end.x_p][end.y_p].val == 0)
	{
		return;
	}

	pos = new PosT;
	pos->x_p = start.x_p;
	pos->y_p = start.y_p;
	curPos = start;
	puzzleTbl[curPos.x_p][curPos.y_p].color = BLACK;
	LQue.Enqueue(pos);
	while(!LQue.QueEmpty())
	{ 
		//上下左右四个点需要检查
		//初始的颜色都是白色，如果当前值为0涂色为灰色表示不可通达
		//如果当前节点可通，涂色为黑色
		//对于白色且可通的节点入队列，灰色不可通的节点不入列，同时保存路径

		
		pos = (PosT*)LQue.Dequeue();
		curPos = *pos;
		delete pos;

		if (found || (curPos.x_p == end.x_p && curPos.y_p == end.y_p))
		{
			if (!found)
			{
				puzzleTbl[curPos.x_p][curPos.y_p].color = BLACK;
				found = true;
			}
			
			if (found) 
			{
				//release the resource in the queue
				continue;
			}
		}

		//当前位置a[i][j]
		//当前位置的左边，/a[i][j - 1]
		left.x_p = curPos.x_p;
		left.y_p = curPos.y_p - 1;
		if (CheckIfNeedEnqueue(left, LQue))
		{
			puzzleTbl[left.x_p][left.y_p].path = curPos;
		}


		//当前节点的右边的位置
		//a[i][j+ 1]
		right.x_p = curPos.x_p;
		right.y_p = curPos.y_p + 1;
		if (CheckIfNeedEnqueue(right, LQue))
		{
			puzzleTbl[right.x_p][right.y_p].path = curPos;
		}

		//当前节点的上方位置
		//a[i+1][j]
		up.x_p = curPos.x_p + 1;
		up.y_p = curPos.y_p ;

		if (CheckIfNeedEnqueue(up, LQue))
		{
			puzzleTbl[up.x_p][up.y_p].path = curPos;
		}

		//当前节点的下方位置
		//a[i - 1][j]
		bottom.x_p = curPos.x_p - 1;
		bottom.y_p = curPos.y_p;
		if (CheckIfNeedEnqueue(bottom, LQue))
		{
			puzzleTbl[bottom.x_p][bottom.y_p].path = curPos;
		}

		//所有相关联的点/位置都处理完了，设置当前节点的颜色为BLACK/可通
		puzzleTbl[curPos.x_p][curPos.y_p].color = BLACK;
	}
	PuzzlePath(start, end);
}

bool CanThisNodePass(PuzDFSPosT& curPos)
{
	if (!curPos.dir_left || !curPos.val)
		return false;

	return true;
}

DirT getPrevDir(DirT dir)
{
	return (DirT)((int)dir - 1);
}

void PuzzleSolutionDFS(PosT& start, PosT& end)
{
	stack stack(100);
	PuzDFSPosT  nextPos;
	PuzDFSPosT * pos = NULL;
	bool found = false;

	pos = new PuzDFSPosT;
	pos->pos.x_p = start.x_p;
	pos->pos.y_p = start.y_p;
	pos->curDir = DIR_INVALID;
	pos->dir_left = 4;
	pos->val = puzzleTbl[start.x_p][start.y_p].val;
	puzzleTbl[start.x_p][start.y_p].color = BLACK;

	stack.push(pos);

	while (!stack.stack_empty())
	{
		pos = (PuzDFSPosT*)(stack.get_top());
		if (pos->pos.x_p == end.x_p && pos->pos.y_p == end.y_p)
		{
			break;
		}

		if (!pos->dir_left || !pos->val)
		{
			//当前节点的方向已经搜索结束或者当前节点值为不可到达（0）
			stack.pop();
			puzzleTbl[pos->pos.x_p][pos->pos.y_p].color = GRAY;
			delete pos;
		}
		else
		{
			nextPos = *pos;
			//搜索下一个方向
			switch (pos->curDir)
			{
			case DIR_LEFT:
				nextPos.pos.x_p += 1;
				pos->curDir = DIR_UP;
				break;
			case DIR_RIGHT:
				nextPos.pos.x_p -= 1;
				pos->curDir = DIR_BOT;
				break;
			case DIR_UP:
				nextPos.pos.y_p += 1;
				pos->curDir = DIR_RIGHT;
				break;
			case DIR_INVALID:
			case DIR_BOT:
			default://DIR_BOTTOM
				pos->curDir  = DIR_LEFT;
				nextPos.pos.y_p -= 1;
				break;
			}
			pos->dir_left--;
			if (validPos(nextPos.pos))
			{
				if (puzzleTbl[nextPos.pos.x_p][nextPos.pos.y_p].color == WHITE)
				{
					pos = new PuzDFSPosT;
					pos->pos.x_p = nextPos.pos.x_p;
					pos->pos.y_p = nextPos.pos.y_p;
					pos->curDir = nextPos.curDir;
					pos->dir_left = 4;
					pos->val = puzzleTbl[pos->pos.x_p][pos->pos.y_p].val;
					puzzleTbl[nextPos.pos.x_p][nextPos.pos.y_p].color = BLACK;
					stack.push(pos);
				}
			}
		}
	}

	cout << "\npuzzleDFS solution:" << endl;
	while (!stack.stack_empty())
	{
		pos = (PuzDFSPosT*)(stack.pop());
		printPath(pos->pos);
		delete pos;
	}
}



void PuzzleTest()
{
	PosT start = { 0, 0 };
	PosT end = { 7, 7 };
	puzzleInit();
	PuzzleSolutionBFS(start, end);

	puzzleInit();
	PuzzleSolutionDFS(start, end);
	
}