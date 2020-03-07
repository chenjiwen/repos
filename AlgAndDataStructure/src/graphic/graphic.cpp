#include "common.h"
#include "graphic.h"
#include "queue.h"
#include "binary_heap.h"
#include <iostream>
using namespace std;


GADJTable::GADJTable(int num) :nodeNum(num), table(NULL)
{
	if (nodeNum) {
		table = new GADTNode[nodeNum];
		for (int i = 0; i < nodeNum; i++)
		{
			table[i].nodeKey = i + 1;
		}
	}
}

GADJTable::~GADJTable()
{
	llist_t* plist = NULL, *next = NULL;
	int i = 0;
	GADTNode* pNode = NULL;
	for (i = 0; i < nodeNum; i++)
	{
		//free the pnode linked to table[i].list
		plist = table[i].list.next;
		while (plist)
		{   
			next = plist->next;
			pNode = container_of(plist, GADTNode, list);
			delete pNode;
			plist = next;
		}
#ifndef USE_BITSET	
		//free the pnode linked to table[i].adjlist
		plist = table[i].adjlist.next;
		while (plist)
		{
			next = plist->next;
			pNode = container_of(plist, GADTNode, adjlist);
			delete pNode;
			plist = next;
		}
#else

#endif
	}
	
	delete[] table;
}

/*
 * Add one Edge information into the Adj table
 *
 *
 */

void GADJTable::GAdjtAdd(int toAdd, int nodeKey)
{
	llist_t* plist = NULL;
	GADTNode* pNode = NULL;

	pNode = new GADTNode();
	pNode->nodeKey = nodeKey;
	//node key need transfer to index of table
	plist = &table[toAdd - 1].list;
	while (plist->next)
	{
		plist = plist->next;
	}

	llist_add(plist, &pNode->list);

#ifndef USE_BITSET
	plist = &table[nodeKey - 1].adjlist;
	pNode = new GADTNode();
	pNode->nodeKey = toAdd;
	while (plist->next)
	{
		plist = plist->next;
	}
	llist_add(plist, &pNode->adjlist);
#else
	pNode = &table[toAdd - 1];
	pNode->bitvec.set(toAdd - 1);
#endif
}

int GADJTable::NodeOutDegree(int nodeKey)
{
	int count = 0;
	llist_t* plist = NULL;

	plist = table[nodeKey - 1].list.next;
	while (plist)
	{
		count++;
		plist = plist->next;
	}

	return count;
}

int GADJTable::NodeInDegree(int nodeKey)
{
	int i = 0;
	int count = 0;
	llist_t* plist = NULL;
	GADTNode* node = NULL;

	for (int i = 0; i < nodeNum; i++)
	{
		plist = table[i].list.next;
		while (plist)
		{
			node = container_of(plist, GADTNode, list);
			if (node->nodeKey == nodeKey)
			{
				count++;
			}
			plist = plist->next;
		}
	}

	return count;
}

GADTNode* GADJTable::TransferGADJT()
{
	GADTNode* trans = NULL, *pNode = NULL;
	int i = 0;
	llist_t* plist = NULL;


	trans = new GADTNode[nodeNum];
	for (int i = 0; i < nodeNum; i++)
	{
		//trans[i].nodeKey = i;
		plist = table[i].list.next;
		while (plist)
		{
			pNode = container_of(plist, GADTNode, list);
			trans[pNode->nodeKey - 1].nodeKey = pNode->nodeKey;
			llist_add(&trans[pNode->nodeKey - 1].list, &pNode->list);
		}
	}

	return trans;
}

int GADJTable::PathNum(int from, int to) 
{
	pllist_t plist = NULL;
	GADTNode* pNode = NULL;
	int num = 0;

	plist = table[from - 1].list.next;
	while (plist)
	{
		pNode = container_of(plist, GADTNode, list);
		if (pNode->nodeKey == to)
		{
			num += 1;
		}
		else
		{
			num += PathNum(pNode->nodeKey, to);
		}

		plist = plist->next;
	}

	return num;
}

GADJTable* GADJTable::SquareG() {
	llist_t* plist = NULL;
	GADTNode* pNode = NULL;
	GADJTable *Adjtable = NULL;
	int i = 0;

	Adjtable = new GADJTable(nodeNum);
	for (i = 0; i < nodeNum; i++)
	{
		plist = table[i].list.next;
		while (plist)
		{
			pNode = container_of(plist, GADTNode, list);
			if (PathNum(table[i].nodeKey, pNode->nodeKey) <= 2)
			{
				Adjtable->GAdjtAdd(table[i].nodeKey, pNode->nodeKey);
			}
			plist = plist->next;
		}
	}

	return Adjtable;
}

GADTNode* GADJTable::GetVertexNode(int i)
{
	return table + i;
}

void graphic_test()
{
	GADJTable GAdjT(4);
	GADJTable *pGSquare;
	int inDgree = 0;
	int outDegree = 0;
	int pathNum = 0;

	GAdjT.GAdjtAdd(1, 2);
	GAdjT.GAdjtAdd(1, 3);
	GAdjT.GAdjtAdd(3, 4);
	GAdjT.GAdjtAdd(3, 2);
	GAdjT.GAdjtAdd(4, 2);

	inDgree = GAdjT.NodeInDegree(1);
	outDegree = GAdjT.NodeOutDegree(1);

	inDgree = GAdjT.NodeInDegree(2);
	outDegree = GAdjT.NodeOutDegree(2);

	pathNum = GAdjT.PathNum(1, 2);

	pGSquare = GAdjT.SquareG();
}

Graph::Graph():VNum(0), pGAdjTable(NULL), TopTable(NULL), pBFSTable(NULL)
{

}

Graph::Graph(int num) :VNum(num)
{
	pGAdjTable = new GADJTable(num);
	TopTable = new int[num];
	memset(TopTable, 0, sizeof(*TopTable) * num);
	pBFSTable = new GPATHTable[num];
	memset(pBFSTable, 0, sizeof(*pBFSTable)*num);
}

Graph::~Graph()
{
	delete pGAdjTable;
	if (TopTable)
	{
		delete[] TopTable;
	}
	
	if (pBFSTable)
	{
		delete []pBFSTable;
	}
}

void Graph::GraphBuildADJTable(vector<vector<int>>& vec)
{
	int vertexId = 1;
	vector<vector<int>>::iterator iter = vec.begin();

	while (iter != vec.end())
	{
		vector<int> vect = *iter;
		for (size_t i = 0; i < vect.size(); i++)
		{
			pGAdjTable->GAdjtAdd(vertexId, vect[i]);
		}
		vertexId++;
		iter++;
	}
}

void Graph::GraphBuildWeightTable(int weight, int from, int to)
{
	GWeight* pNode = NULL;
	pNode = new GWeight;

	pNode->nodeKey = to;
	pNode->weight = weight;
	llist_add(&pGAdjTable->GetVertexNode(from - 1)->weight_list, &pNode->list);
}

int Graph::GrapGetWeight(int from, int to)
{
	llist_t* plist = NULL;
	GWeight* wNode = NULL;

	plist = (pGAdjTable->GetVertexNode(from - 1))->weight_list.next;
	while (plist)
	{
		wNode = container_of(plist, GWeight, list);
		if (wNode->nodeKey == to)
		{
			return wNode->weight;
		}
		plist = plist->next;
	}

	return -1;
}

int* Graph::GraphTopSort()
{
	int* InDegTbl = NULL;
	LinearQue LQue(VNum);
	int i = 0;
	int counter = 0;
	llist_t* plist = NULL;
	GADTNode* V, * W;

	InDegTbl = new int[VNum];
	memset(InDegTbl, 0, sizeof(int) * VNum);

	for (i = 0; i < VNum; i++)
	{
		InDegTbl[i] = pGAdjTable->NodeInDegree(i + 1);
		if (InDegTbl[i] == 0)
		{
			LQue.Enqueue(pGAdjTable->GetVertexNode(i));
		}
	}

	while (!LQue.QueEmpty())
	{
		V = (GADTNode*)LQue.Dequeue();
		TopTable[counter++] = V->nodeKey;
		if (counter >= VNum) {
			has_loop = true;
			loop_vertex = V->nodeKey;
			break;
		}

		plist = V->list.next;
		while (plist)
		{
			W = container_of(plist, GADTNode, list);
			plist = plist->next;
			
			if (--InDegTbl[W->nodeKey - 1] == 0)
			{
				LQue.Enqueue(pGAdjTable->GetVertexNode(W->nodeKey - 1));
			}
		}
	}

	if (!has_loop && counter < VNum)
	{
		has_loop = true;
	}

	delete InDegTbl;

	return TopTable;
}

int* Graph::GraphTopSortByStack()
{
	int* OutDegTbl = NULL;
	stack stack(VNum);
	int i = 0;
	int counter = 0;
	llist_t* plist = NULL;
	GADTNode* V, * W;

	OutDegTbl = new int[VNum];
	memset(OutDegTbl, 0, sizeof(int) * VNum);

	for (i = 0; i < VNum; i++)
	{
		OutDegTbl[i] = pGAdjTable->NodeOutDegree(i + 1);
		if (OutDegTbl[i] == 0)
		{
			stack.push(pGAdjTable->GetVertexNode(i));
		}
	}

	while (!stack.stack_empty())
	{
		V = (GADTNode*)stack.pop();
		TopTable[counter++] = V->nodeKey;

		plist = V->adjlist.next;
		while (plist)
		{
			W = container_of(plist, GADTNode, adjlist);
			plist = plist->next;

			if (--OutDegTbl[W->nodeKey - 1] == 0)
			{
				stack.push(pGAdjTable->GetVertexNode(W->nodeKey - 1));
			}
		}
	}

	delete OutDegTbl;

	return TopTable;
}

void* Graph::GraphDijkstra(int start_vetx)
{
	FibHeap fibHeap;
	GPATHTable* pGPATHDijkTable = NULL;
	int i = 0;
	pGPATHDijkTable = new GPATHTable[VNum];
	FibHeapNode* pMinNode = NULL, *pFibTNode = NULL;
	GADTNode* pNodeV = NULL, *pNodeW = NULL;
	llist_t* plist = NULL;
	int weight = 0;

	for (i = 0; i < VNum; i++)
	{
		pGPATHDijkTable[i].visited = false;
		pGPATHDijkTable[i].dist = INT_MAX;
		pGPATHDijkTable[i].path = -1;
	}
	pGPATHDijkTable[start_vetx].dist = 0;

	dijk_vtex = start_vetx;
	fibHeap.FibHeapInsert(pGPATHDijkTable[start_vetx].dist, pGAdjTable->GetVertexNode(start_vetx - 1));

	for (;;)
	{
		pMinNode = fibHeap.FibHeapExtractMin();
		
		if (!pMinNode)
		{
			break;
		}
		pNodeV = static_cast<GADTNode*>(pMinNode->priv);
		pGPATHDijkTable[pNodeV->nodeKey - 1].visited = true;

		plist = pNodeV->list.next;
		while (plist)
		{
			pNodeW = container_of(plist, GADTNode, list);
			if (!pGPATHDijkTable[pNodeW->nodeKey - 1].visited)
			{
				//weight = weightVec[pNodeV->nodeKey - 1][pNodeW->nodeKey - 1];
				weight = GrapGetWeight(pNodeV->nodeKey, pNodeW->nodeKey);
				if (pGPATHDijkTable[pNodeW->nodeKey - 1].dist == INT_MAX)
				{
					fibHeap.FibHeapInsert(pGPATHDijkTable[pNodeW->nodeKey - 1].dist, pGAdjTable->GetVertexNode(pNodeW->nodeKey - 1));
				}
				else if (pGPATHDijkTable[pNodeV->nodeKey - 1].dist + weight < pGPATHDijkTable[pNodeW->nodeKey - 1].dist)
				{
					pGPATHDijkTable[pNodeW->nodeKey - 1].dist = pGPATHDijkTable[pNodeV->nodeKey - 1].dist + weight;
					pGPATHDijkTable[pNodeW->nodeKey].path = pNodeV->nodeKey;
					//fibHeap.FibHeapInsert(pGPATHDijkTable[pNodeW->nodeKey - 1].dist, pGAdjTable->GetVertexNode(pNodeW->nodeKey - 1));
					pFibTNode = container_of(pGAdjTable->GetVertexNode(pNodeW->nodeKey - 1), FibHeapNode, priv);
					fibHeap.FibHeapDecreseKey(pFibTNode, pGPATHDijkTable[pNodeW->nodeKey - 1].dist);
				}
			}
			plist = plist->next;
		}
	}

	return pGPATHDijkTable;
}

void Graph::GraphBFS(int start_vertex)
{
	LinearQue linearQue;
	GADTNode* pNode = NULL, *pTemp = NULL;
	llist_t* plist = NULL;
	int i = 0;

	for (i = 0; i < VNum; i++)
	{
		pBFSTable[i].dist = INT_MAX;
	}
	pBFSTable[start_vertex - 1].dist = 0;
	this->start_vertex = start_vertex;
	linearQue.Enqueue(pGAdjTable->GetVertexNode(start_vertex - 1));
	while (!linearQue.QueEmpty())
	{
		pNode = static_cast<GADTNode*>(linearQue.Dequeue());
		plist = pNode->list.next;
		while (plist)
		{
			pTemp = container_of(plist, GADTNode, list);
			//只有没有处理过的时候，才需要更新，如果处理过，例如图中有环，节点处理过就不要再处理
			if (pBFSTable[pTemp->nodeKey - 1].dist == INT_MAX)
			{
				pBFSTable[pTemp->nodeKey - 1].dist = pBFSTable[pNode->nodeKey - 1].dist + 1;
				pBFSTable[pTemp->nodeKey - 1].path = pNode->nodeKey;
				linearQue.Enqueue(pGAdjTable->GetVertexNode(pTemp->nodeKey - 1));
			}

			plist = plist->next;
		}
	}
}

void Graph::PathPrint(GPATHTable* pathTable, int to_vtex)
{
	cout << to_vtex;
	while(pathTable && pathTable[to_vtex - 1].path)
	{
		cout << "<-" <<pathTable[to_vtex - 1].path;
		to_vtex = pathTable[to_vtex - 1].path;
	}
	cout << endl;
}

void Graph::PathPrint(GraphPathType pathType, int start_vtex)
{
	GPATHTable* pathTable = pBFSTable;

	cout << "Path print:" << endl;
	for (int i = 1; i <= VNum; i++)
	{
		PathPrint(pathTable, i);
		if (i != VNum)
		{
			cout << "Next path:" << endl;
		}	    
	}
}

void graph_test()
{
	Graph graph(7);
	int* ptable = NULL;
	vector<int> vec1, vec2, vec3, vec4, vec5, vec6, vec7;
	vector<vector<int>> adj_vec;
	int i = 0;

	vec1.push_back(2);
	vec1.push_back(4);
	//vec1.push_back(3);

	vec2.push_back(4);
	vec2.push_back(5);

	vec3.push_back(6);
	vec3.push_back(1);

	vec4.push_back(3);
	vec4.push_back(7);
	vec4.push_back(5);
	vec4.push_back(6);

	//vec5.push_back(4);
	vec5.push_back(7);

	//vec6.push_back(4);
	
	vec7.push_back(6);

	adj_vec.push_back(vec1);
	adj_vec.push_back(vec2);
	adj_vec.push_back(vec3);
	adj_vec.push_back(vec4);
	adj_vec.push_back(vec5);
	adj_vec.push_back(vec6);
	adj_vec.push_back(vec7);

	graph.GraphBuildADJTable(adj_vec);
	ptable = graph.GraphTopSort();
	//ptable = graph.GraphTopSortByStack();
	graph.GraphBFS(3);
	cout << "\n Topsort order:" << endl;
	for (i = 0; i < 7; i++)
	{
		cout << " " << ptable[i] <<" ";
	}
	cout << endl;

	graph.PathPrint(GPATH_BFS, 3);
}